#include "io2d.h"
#include <cairo-xcb.h>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;

display_surface::native_handle_type display_surface::native_handle() const {
	return{ { _Surface.get(), _Context.get() }, { _Native_surface.get(), _Native_context.get() }, _Connection.get(), _Connection_mutex, _Connection_ref_count, _Screen, _Wndw };
}

mutex display_surface::_Connection_mutex;
unique_ptr<xcb_connection_t, decltype(&xcb_disconnect)> display_surface::_Connection{ nullptr, &xcb_disconnect };
int display_surface::_Connection_ref_count = 0;

namespace {
	xcb_atom_t _Wm_protocols;
	xcb_atom_t _Wm_delete_window;
}

void display_surface::_Make_native_surface_and_context() {
	auto depthIter = xcb_screen_allowed_depths_iterator(_Screen);
	xcb_visualtype_t* visual = nullptr;
	for (; depthIter.rem != 0; xcb_depth_next(&depthIter)) {
		auto visualIter = xcb_depth_visuals_iterator(depthIter.data);
		for (; visualIter.rem != 0; xcb_visualtype_next(&visualIter)) {
			if (_Screen->root_visual == visualIter.data->visual_id) {
				visual = visualIter.data;
				break;
			}
		}
	}

	if (visual == nullptr) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
	}
	
	_Native_surface = unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_xcb_surface_create(_Connection.get(), _Wndw, visual, _Display_width, _Display_height), &cairo_surface_destroy);
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Native_surface.get()));
	_Native_context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Native_surface.get()), &cairo_destroy);
	_Throw_if_failed_cairo_status_t(cairo_status(_Native_context.get()));
}

void display_surface::_Resize_window() {
	auto geometryCookie = xcb_get_geometry(_Connection.get(), _Wndw);
	unique_ptr<xcb_get_geometry_reply_t, decltype(&::free)> geometryReply(xcb_get_geometry_reply(_Connection.get(), geometryCookie, nullptr), &::free);
	if (geometryReply == nullptr) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_STATUS);
	}
	
	const uint32_t values[] = { static_cast<uint32_t>(_Display_width), static_cast<uint32_t>(_Display_height) };
	xcb_configure_window(_Connection.get(), _Wndw, XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, values);
	xcb_flush(_Connection.get());
}

display_surface::display_surface(int preferredWidth, int preferredHeight, experimental::io2d::format preferredFormat, experimental::io2d::scaling scl, experimental::io2d::refresh_rate rr, float fps)
	: display_surface(preferredWidth, preferredHeight, preferredFormat, preferredWidth, preferredHeight, scl, rr, fps) {
}

display_surface::display_surface(int preferredWidth, int preferredHeight, experimental::io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, experimental::io2d::scaling scl, experimental::io2d::refresh_rate rr, float fps)
	: surface({ nullptr, nullptr }, preferredFormat)
	, _Display_width(preferredDisplayWidth)
	, _Display_height(preferredDisplayHeight)
	, _Scaling(scl)
	, _Width(preferredWidth)
	, _Height(preferredHeight)
	, _Draw_fn()
	, _Size_change_fn()
	, _User_scaling_fn()
	, _Auto_clear(false)
	, _Screen(nullptr)
	, _Wndw()
	, _Can_draw(false)
	, _Refresh_rate(rr)
	, _Desired_frame_rate(fps)
	, _Redraw_requested(true)
	, _Native_surface(nullptr, &cairo_surface_destroy)
	, _Native_context(nullptr, &cairo_destroy)
	, _Letterbox_brush()
	, _Default_brush(rgba_color::transparent_black) {
	if (preferredDisplayWidth <= 0 || preferredDisplayHeight <= 0 || preferredWidth <= 0 || preferredHeight <= 0 || preferredFormat == experimental::io2d::format::invalid) {
		throw invalid_argument("Invalid parameter.");
	}
	if (fps <= _Minimum_frame_rate || !isfinite(fps)) {
		throw system_error(make_error_code(errc::argument_out_of_domain));
	}
	xcb_connection_t* connection = nullptr;
	// Lock to increment the ref count.
	{
		lock_guard<mutex> lg(_Connection_mutex);
		_Connection_ref_count++;
	}
	int screenNumber = 0;
	if (_Connection == nullptr) {
		lock_guard<mutex> lg(_Connection_mutex);
		if (_Connection == nullptr) {
			connection = xcb_connect(nullptr, &screenNumber);
			if (connection == nullptr) {
				_Connection_ref_count--;
				throw system_error(make_error_code(errc::connection_refused));
			}
			_Connection = unique_ptr<xcb_connection_t, decltype(&::xcb_disconnect)>(connection, &::xcb_disconnect);
		}
	}
	auto setup = xcb_get_setup(connection);
	_Screen = nullptr;
	auto screenIter = xcb_setup_roots_iterator(setup);
	for (; screenIter.rem != 0; --screenNumber, xcb_screen_next(&screenIter)) {
		if (screenNumber == 0) {
			_Screen = screenIter.data;
			break;
		}
	}
	if (_Screen == nullptr) {
		lock_guard<mutex> lg(_Connection_mutex);
		_Connection_ref_count--;
		throw system_error(make_error_code(errc::connection_aborted));
	}
	
}

display_surface::~display_surface() {
	_Native_context.reset();
	_Native_surface.reset();
	if (_Wndw != 0) {
		xcb_destroy_window(_Connection.get(), _Wndw);
		_Wndw = 0;
	}
	lock_guard<mutex> lg(_Connection_mutex);
	_Connection_ref_count--;
	assert(_Connection_ref_count >= 0);
	if (_Connection_ref_count <= 0) {
		_Connection_ref_count = 0;
		_Connection = nullptr;
	}
}

namespace {
	bool _Poll_for_xcb_event(unique_ptr<xcb_generic_event_t, decltype(&::free)>& event, xcb_connection_t* c) {
		event.reset(xcb_poll_for_event(c));
// 		if (event != nullptr) {
// 			stringstream errorString;
// 			errorString << "response_type: '" << to_string(event->response_type) << "'" << endl;
// 			cerr << errorString.str().c_str();
// 		}
		return event != nullptr;
	}
}

int display_surface::begin_show() {
	xcb_connection_t* connection = _Connection.get();
	_Wndw = xcb_generate_id(connection);
	uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	uint32_t values[2];
	values[0] = _Screen->black_pixel;
	values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_PROPERTY_CHANGE;
	uint16_t x = 0;
	uint16_t y = 0;
	auto windowCookie = xcb_create_window_checked(connection, _Screen->root_depth, _Wndw, _Screen->root, x, y, static_cast<uint16_t>(_Display_width), static_cast<uint16_t>(_Display_height), _Window_border_width, XCB_WINDOW_CLASS_INPUT_OUTPUT, _Screen->root_visual, mask, values);
	
	xcb_generic_error_t* error = xcb_request_check(connection, windowCookie);
	if (error != nullptr) {
		lock_guard<mutex> lg(_Connection_mutex);
		_Connection_ref_count--;
		throw system_error(make_error_code(errc::connection_aborted));
	}
	
	auto mapCookie = xcb_map_window_checked(connection, _Wndw);
	xcb_generic_error_t* mapError = xcb_request_check(connection, mapCookie);
	if (mapError != nullptr) {
		lock_guard<mutex> lg(_Connection_mutex);
		_Connection_ref_count--;
		throw system_error(make_error_code(errc::connection_aborted));
	}
	
	string wmProtocols = "WM_PROTOCOLS";
	auto wmProtocolsCookie = xcb_intern_atom(connection, 0, static_cast<uint16_t>(wmProtocols.size()), wmProtocols.c_str());
	unique_ptr<xcb_intern_atom_reply_t, decltype(&::free)> wmProtocolsReply(xcb_intern_atom_reply(connection, wmProtocolsCookie, nullptr), &::free);
	if (wmProtocolsReply == nullptr) {
		lock_guard<mutex> lg(_Connection_mutex);
		_Connection_ref_count--;
		throw system_error(make_error_code(errc::connection_aborted));
	}
	_Wm_protocols = wmProtocolsReply->atom;
	string wmDelWin = "WM_DELETE_WINDOW";
	auto wmDelWinCookie = xcb_intern_atom(connection, 0, static_cast<uint16_t>(wmDelWin.size()), wmDelWin.c_str());
	unique_ptr<xcb_intern_atom_reply_t, decltype(&::free)> wmDelWinReply(xcb_intern_atom_reply(connection, wmDelWinCookie, nullptr), &::free);
	if (wmDelWinReply == nullptr) {
		lock_guard<mutex> lg(_Connection_mutex);
		_Connection_ref_count--;
		throw system_error(make_error_code(errc::connection_aborted));
	}
	_Wm_delete_window = (wmDelWinReply.get())->atom;
	const uint8_t wmProtocolsDataFormat = 32;
	const uint32_t wmProtocolsNumDataElements = 1;
	xcb_change_property(connection, XCB_PROP_MODE_REPLACE, _Wndw, _Wm_protocols, XCB_ATOM_ATOM, wmProtocolsDataFormat, wmProtocolsNumDataElements, static_cast<void *>(&_Wm_delete_window));
	xcb_flush(connection);

	_Surface = unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(_Format), _Width, _Height), &cairo_surface_destroy);
	_Context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy);

	bool exit = false;
	unique_ptr<xcb_generic_event_t, decltype(&::free)> event{ nullptr, &::free };

	auto previousTime = steady_clock::now();
	_Elapsed_draw_time = 0.0F;
	while (!exit) {
		auto currentTime = steady_clock::now();
		auto elapsedTimeIncrement = static_cast<float>(duration_cast<nanoseconds>(currentTime - previousTime).count());
		_Elapsed_draw_time += elapsedTimeIncrement;
		previousTime = currentTime;
		while (_Poll_for_xcb_event(event, _Connection.get())) {
// 			const uint8_t userGeneratedEventMask = ~0x80;
			switch (event->response_type & ~0x80) {
			case 0:
			{
				xcb_generic_error_t* err = reinterpret_cast<xcb_generic_error_t*>(event.get());
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_STATUS);
			} break;
				// ExposureMask events:
			case XCB_EXPOSE:
			{
				if (!_Can_draw && _Wndw != 0) {
					_Make_native_surface_and_context();
				}
				assert(_Native_surface != nullptr && _Native_context != nullptr);
				_Can_draw = true;
				if (_Draw_fn != nullptr) {
					if (_Auto_clear) {
						clear();
					}
					(*_Draw_fn)(*this);
				}
				else {
					throw system_error(make_error_code(errc::operation_would_block));
				}
				_Render_to_native_surface();

				_Elapsed_draw_time = 0.0F;
				//if (_Refresh_rate == experimental::io2d::refresh_rate::fixed) {
				//	_Elapsed_draw_time -= elapsedTimeIncrement;
				//}
				//else {
				//	_Elapsed_draw_time = 0.0F;
				//}
			} break;
			// StructureNotifyMask events:
			case XCB_CIRCULATE_NOTIFY:
			{
			} break;
			case XCB_CONFIGURE_NOTIFY:
			{
				bool resized = false;
				xcb_configure_notify_event_t* ev = reinterpret_cast<xcb_configure_notify_event_t*>(event.get());
				if (ev->width != _Display_width) {
					_Display_width = ev->width;
					resized = true;
				}
				if (ev->height != _Display_height) {
					_Display_height = ev->height;
					resized = true;
				}
				if (resized) {
					cairo_xcb_surface_set_size(_Native_surface.get(), _Display_width, _Display_height);
					if (_Size_change_fn != nullptr) {
						(*_Size_change_fn)(*this);
					}
				}
			} break;
			case XCB_DESTROY_NOTIFY:
			{
// 				stringstream errorString;
// 				errorString << "XCB_DESTROY_NOTIFY" << endl;
// 				cerr << errorString.str().c_str();
				_Wndw = 0;
				_Can_draw = false;
				_Native_context.reset();
				_Native_surface.reset();
				exit = true;
			} break;
			case XCB_GRAVITY_NOTIFY:
			{
			} break;
			case XCB_MAP_NOTIFY:
			{
			} break;
			case XCB_REPARENT_NOTIFY:
			{
			} break;
			case XCB_UNMAP_NOTIFY:
			{
// 				stringstream errorString;
// 				errorString << "XCB_UNMAP_NOTIFY" << endl;
// 				cerr << errorString.str().c_str();
				// The window still exists, it has just been unmapped.
				_Can_draw = false;
				_Native_context.reset();
				_Native_surface.reset();
			} break;
			// Might get them even though they are unrequested events (see http://www.x.org/releases/X11R7.7/doc/libX11/libX11/libX11.html#Event_Masks ):
			case XCB_GRAPHICS_EXPOSURE:
			{
				if (_Can_draw) {
					if (_Draw_fn != nullptr) {
						if (_Auto_clear) {
							clear();
						}
						(*_Draw_fn)(*this);
					}
					else {
						throw system_error(make_error_code(errc::operation_would_block));
					}
					_Render_to_native_surface();

					_Elapsed_draw_time = 0.0F;
					//if (_Refresh_rate == experimental::io2d::refresh_rate::fixed) {
					//	_Elapsed_draw_time -= elapsedTimeIncrement;
					//}
					//else {
					//	_Elapsed_draw_time = 0.0F;
					//}
				}
			} break;
			case XCB_NO_EXPOSURE:
			{
			} break;
			case XCB_PROPERTY_NOTIFY:
			{
// 				xcb_property_notify_event_t* ev = reinterpret_cast<xcb_property_notify_event_t*>(event.get());
// 				stringstream propStr;
// 				propStr << "Property notify for atom: '" << to_string(ev->atom) << "' with state '" << to_string(ev->state) << "'." << endl;
// 				cerr << propStr.str().c_str();
			} break;
			// Unmasked events
			case XCB_CLIENT_MESSAGE:
			{
				xcb_client_message_event_t* ev = reinterpret_cast<xcb_client_message_event_t*>(event.get());
				if (ev->format == 32 && static_cast<xcb_atom_t>(ev->data.data32[0]) == _Wm_delete_window) {
// 					stringstream errorString;
// 					errorString << "XCB_CLIENT_MESSAGE" << endl;
// 					cerr << errorString.str().c_str();
					_Can_draw = false;
					_Native_context.reset();
					_Native_surface.reset();
					xcb_destroy_window(_Connection.get(), _Wndw);
					xcb_flush(_Connection.get());
					_Wndw = 0;
					exit = true;
				}
				else {
// 					stringstream clientMsgStr;
// 					clientMsgStr << "ClientMessage event type '" << to_string(ev->type) << "' for unknown event type";
// // 					auto atomName = XGetAtomName(_Display.get(), event.xclient.message_type);
// // 					if (atomName != nullptr) {
// // 						try {
// // 							clientMsgStr << " (" << atomName << ")";
// // 						}
// // 						catch (...) {
// // 							XFree(atomName);
// // 						}
// // 						XFree(atomName);
// // 					}
// 					clientMsgStr << ". Format is '" << to_string(ev->format) << "' and first value is '";
// 					switch (ev->format) {
// 					case 8:
// 					{
// 						clientMsgStr << to_string(static_cast<int>(ev->data.data8[0])).c_str();
// 					} break;
// 					case 16:
// 					{
// 						clientMsgStr << to_string(ev->data.data16[0]).c_str();
// 					} break;
// 					case 32:
// 					{
// 						clientMsgStr << to_string(ev->data.data32[0]).c_str();
// 					} break;
// 					default:
// 					{
// 						assert("Unexpected format." && false);
// 						clientMsgStr << "(unexpected format)";
// 					} break;
// 					}
// 					clientMsgStr << "'.";
// 					auto es = clientMsgStr.str().c_str();
// 					cerr << es << endl;
				}
			} break;
			case XCB_MAPPING_NOTIFY:
			{
			} break;
			case XCB_SELECTION_CLEAR:
			{
			} break;
			case XCB_SELECTION_NOTIFY:
			{
			} break;
			case XCB_SELECTION_REQUEST:
			{
			} break;
			default:
			{
// 				stringstream errorString;
// 				errorString << "Unexpected event->response_type. Value is '" << to_string(event->response_type) << "'." << endl;
// 				cerr << errorString.str().c_str();
// // 				assert(event->response_type >= 64 && event->response_type <= 127);
			} break;
			}
		}
		if (_Can_draw) {
			bool redraw = true;
			if (_Refresh_rate == experimental::io2d::refresh_rate::as_needed) {
				redraw = _Redraw_requested;
				_Redraw_requested = false;
			}

			auto desiredElapsed = 1'000'000'000.0F / _Desired_frame_rate;

			if (_Refresh_rate == experimental::io2d::refresh_rate::fixed) {
				// desiredElapsed is the amount of time, in nanoseconds, that must have passed before we should redraw.
				redraw = _Elapsed_draw_time >= desiredElapsed;
			}
			if (redraw) {
				// Run user draw function:
				if (_Draw_fn != nullptr) {
					if (_Auto_clear) {
						clear();
					}
					(*_Draw_fn)(*this);
				}
				else {
					throw system_error(make_error_code(errc::operation_would_block));
				}
				_Render_to_native_surface();
				if (_Refresh_rate == experimental::io2d::refresh_rate::fixed) {
					while (_Elapsed_draw_time >= desiredElapsed) {
						_Elapsed_draw_time -= desiredElapsed;
					}
				}
				else {
					_Elapsed_draw_time = 0.0F;
				}
			}
		}
	}
	_Elapsed_draw_time = 0.0F;
	return 0;
}
