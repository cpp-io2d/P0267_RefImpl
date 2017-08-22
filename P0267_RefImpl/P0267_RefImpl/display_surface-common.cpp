#include "io2d.h"
#include "xcairo.h"

#include <sstream>
#include <string>
#include <iostream>

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;
using namespace std::experimental::io2d::v1::cairo;
using namespace std::chrono;

void cairo_display_surface::_All_dimensions(int w, int h, int dw, int dh) {
	dimensions(w, h);
	display_dimensions(dw, dh);
}

// Note: cairo_surface_flush(_Native_surface.get()); must be called after calling this function.
void cairo_display_surface::_Render_for_scaling_uniform_or_letterbox() {
	const cairo_filter_t cairoFilter = CAIRO_FILTER_GOOD;
	
// 	static auto previousTime = steady_clock::now();

	if (_Width == _Display_width && _Height == _Display_height) {
		cairo_set_source_surface(_Native_context.get(), _Cairo_surface->_Surface.get(), 0.0F, 0.0F);
		cairo_paint(_Native_context.get());
	}
	else {
		const auto whRatio = static_cast<float>(_Width) / static_cast<float>(_Height);
		const auto displayWHRatio = static_cast<float>(_Display_width) / static_cast<float>(_Display_height);
		cairo_matrix_t ctm;
		auto nativeContext = _Native_context.get();
		//cairo_save(nativeContext);
		float rectX, rectY, rectWidth, rectHeight;
		if (whRatio < displayWHRatio) {
			cairo_new_path(nativeContext);
			const auto displayHeightAsDouble = static_cast<float>(_Display_height);
			rectWidth = trunc(displayHeightAsDouble * whRatio);
			rectHeight = displayHeightAsDouble;
			rectX = trunc(abs(rectWidth - static_cast<float>(_Display_width)) / 2.0F);
			rectY = 0.0F;
			cairo_rectangle(nativeContext, rectX, rectY, rectWidth, rectHeight);

			const auto heightRatio = static_cast<float>(_Height) / static_cast<float>(_Display_height);
			cairo_matrix_init_scale(&ctm, heightRatio, heightRatio);
			cairo_matrix_translate(&ctm, -rectX, 0.0F);
			unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Cairo_surface->_Surface.get()), &cairo_pattern_destroy);
			cairo_pattern_set_matrix(pat.get(), &ctm);
			cairo_pattern_set_extend(pat.get(), CAIRO_EXTEND_NONE);
			cairo_pattern_set_filter(pat.get(), cairoFilter);
			cairo_set_source(_Native_context.get(), pat.get());
			cairo_fill(_Native_context.get());
			//cairo_restore(nativeContext);
			if (_Scaling == std::experimental::io2d::scaling::letterbox) {
				const auto lboxWidth = trunc((static_cast<float>(_Display_width) - rectWidth) / 2.0F);
				cairo_rectangle(nativeContext, 0.0F, 0.0F, lboxWidth, rectHeight);
				cairo_rectangle(nativeContext, rectWidth + lboxWidth, 0.0F, lboxWidth, rectHeight);
				//cairo_pattern_set_extend(_Letterbox_brush.native_handle(), _Extend_to_cairo_extend_t(_Letterbox_brush.wrap_mode()));
				//cairo_pattern_set_filter(_Letterbox_brush.native_handle(), _Filter_to_cairo_filter_t(_Letterbox_brush.filter()));
				//cairo_matrix_t cPttnMatrix;
				//cairo_matrix_init(&cPttnMatrix, _Letterbox_brush.matrix().m00(), _Letterbox_brush.matrix().m01(), _Letterbox_brush.matrix().m10(), _Letterbox_brush.matrix().m11(), _Letterbox_brush.matrix().m20(), _Letterbox_brush.matrix().m21());
				//cairo_pattern_set_matrix(_Letterbox_brush.native_handle(), &cPttnMatrix);
				//cairo_set_source(_Native_context.get(), _Letterbox_brush.native_handle());
				if (_Letterbox_brush == nullopt) {
					cairo_set_source(_Native_context.get(), _Default_brush._Native_handle());
					//cairo_paint(_Native_context.get());
				}
				else {
					auto pttn = _Letterbox_brush.value()._Native_handle();
					if (_Letterbox_brush_props == nullopt) {
						cairo_pattern_set_extend(pttn, CAIRO_EXTEND_NONE);
						cairo_pattern_set_filter(pttn, CAIRO_FILTER_GOOD);
						cairo_matrix_t cPttnMatrix;
						cairo_matrix_init_identity(&cPttnMatrix);
						cairo_pattern_set_matrix(pttn, &cPttnMatrix);
						cairo_set_source(_Native_context.get(), pttn);
						//cairo_paint(_Native_context.get());
					}
					else {
						const brush_props& props = _Letterbox_brush_props.value();
						cairo_pattern_set_extend(pttn, _Extend_to_cairo_extend_t(props.wrap_mode()));
						cairo_pattern_set_filter(pttn, _Filter_to_cairo_filter_t(props.filter()));
						cairo_matrix_t cPttnMatrix;
						const auto& m = props.brush_matrix();
						cairo_matrix_init(&cPttnMatrix, m.m00, m.m01, m.m10, m.m11, m.m20, m.m21);
						cairo_pattern_set_matrix(pttn, &cPttnMatrix);
						cairo_set_source(_Native_context.get(), pttn);
						//cairo_paint(_Native_context.get());
					}
				}
				cairo_fill(_Native_context.get());
			}
		}
		else {
			cairo_new_path(nativeContext);
			const auto displayWidthAsDouble = static_cast<float>(_Display_width);
			rectWidth = displayWidthAsDouble;
			rectHeight = trunc(displayWidthAsDouble / whRatio);
			rectX = 0.0F;
			rectY = trunc(abs(rectHeight - static_cast<float>(_Display_height)) / 2.0F);
			cairo_rectangle(nativeContext, rectX, rectY, rectWidth, rectHeight);

			const auto widthRatio = static_cast<float>(_Width) / static_cast<float>(_Display_width);
			cairo_matrix_init_scale(&ctm, widthRatio, widthRatio);
			cairo_matrix_translate(&ctm, 0.0F, -rectY);
			unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Cairo_surface->_Surface.get()), &cairo_pattern_destroy);
			cairo_pattern_set_matrix(pat.get(), &ctm);
			cairo_pattern_set_extend(pat.get(), CAIRO_EXTEND_NONE);
			cairo_pattern_set_filter(pat.get(), cairoFilter);
			cairo_set_source(_Native_context.get(), pat.get());
			cairo_fill(_Native_context.get());
			//cairo_restore(nativeContext);
			if (_Scaling == std::experimental::io2d::scaling::letterbox) {
				const auto lboxHeight = trunc((static_cast<float>(_Display_height) - rectHeight) / 2.0F);
				cairo_rectangle(nativeContext, 0.0F, 0.0F, rectWidth, lboxHeight);
				cairo_rectangle(nativeContext, 0.0F, rectHeight + lboxHeight, rectWidth, lboxHeight);
				//cairo_pattern_set_extend(_Letterbox_brush.native_handle(), _Extend_to_cairo_extend_t(_Letterbox_brush.wrap_mode()));
				//cairo_pattern_set_filter(_Letterbox_brush.native_handle(), _Filter_to_cairo_filter_t(_Letterbox_brush.filter()));
				//cairo_matrix_t cPttnMatrix;
				//cairo_matrix_init(&cPttnMatrix, _Letterbox_brush.matrix().m00(), _Letterbox_brush.matrix().m01(), _Letterbox_brush.matrix().m10(), _Letterbox_brush.matrix().m11(), _Letterbox_brush.matrix().m20(), _Letterbox_brush.matrix().m21());
				//cairo_pattern_set_matrix(_Letterbox_brush.native_handle(), &cPttnMatrix);
				//cairo_set_source(_Native_context.get(), _Letterbox_brush.native_handle());
				if (_Letterbox_brush == nullopt) {
					cairo_set_source(_Native_context.get(), _Default_brush._Native_handle());
					//cairo_paint(_Native_context.get());
				}
				else {
					auto pttn = _Letterbox_brush.value()._Native_handle();
					if (_Letterbox_brush_props == nullopt) {
						cairo_pattern_set_extend(pttn, CAIRO_EXTEND_NONE);
						cairo_pattern_set_filter(pttn, CAIRO_FILTER_GOOD);
						cairo_matrix_t cPttnMatrix;
						cairo_matrix_init_identity(&cPttnMatrix);
						cairo_pattern_set_matrix(pttn, &cPttnMatrix);
						cairo_set_source(_Native_context.get(), pttn);
						//cairo_paint(_Native_context.get());
					}
					else {
						const brush_props& props = _Letterbox_brush_props.value();
						cairo_pattern_set_extend(pttn, _Extend_to_cairo_extend_t(props.wrap_mode()));
						cairo_pattern_set_filter(pttn, _Filter_to_cairo_filter_t(props.filter()));
						cairo_matrix_t cPttnMatrix;
						const auto& m = props.brush_matrix();
						cairo_matrix_init(&cPttnMatrix, m.m00, m.m01, m.m10, m.m11, m.m20, m.m21);
						cairo_pattern_set_matrix(pttn, &cPttnMatrix);
						cairo_set_source(_Native_context.get(), pttn);
						//cairo_paint(_Native_context.get());
					}
				}
				cairo_fill(_Native_context.get());
			}
		}
	}

// 	auto currentTime = steady_clock::now();
// 	auto elapsedTimeIncrement = static_cast<float>(duration_cast<nanoseconds>(currentTime - previousTime).count());
// 	previousTime = currentTime;
// 	stringstream timingStr;
// 	timingStr << "timing: " << elapsedTimeIncrement / 1'000'000.0F << endl;
// 	cerr << timingStr.str().c_str();
}

void cairo_display_surface::_Render_to_native_surface() {
	const cairo_filter_t cairoFilter = CAIRO_FILTER_GOOD;
	cairo_surface_flush(_Cairo_surface->_Surface.get());
// 	cairo_save(_Native_context.get());
	cairo_set_operator(_Native_context.get(), CAIRO_OPERATOR_SOURCE);
	if (_User_scaling_fn != nullptr && _User_scaling_fn != nullptr) {
		bool letterbox = false;
		auto userRect = (*_User_scaling_fn)(*_Display_surface, letterbox);
		if (letterbox) {
			if (_Letterbox_brush == nullopt) {
				cairo_set_source(_Native_context.get(), _Default_brush._Native_handle());
				cairo_paint(_Native_context.get());
			}
			else {
				auto pttn = _Letterbox_brush.value()._Native_handle();
				if (_Letterbox_brush_props == nullopt) {
					cairo_pattern_set_extend(pttn, CAIRO_EXTEND_NONE);
					cairo_pattern_set_filter(pttn, CAIRO_FILTER_GOOD);
					cairo_matrix_t cPttnMatrix;
					cairo_matrix_init_identity(&cPttnMatrix);
					cairo_pattern_set_matrix(pttn, &cPttnMatrix);
					cairo_set_source(_Native_context.get(), pttn);
					cairo_paint(_Native_context.get());
				}
				else {
					const brush_props& props = _Letterbox_brush_props.value();
					cairo_pattern_set_extend(pttn, _Extend_to_cairo_extend_t(props.wrap_mode()));
					cairo_pattern_set_filter(pttn, _Filter_to_cairo_filter_t(props.filter()));
					cairo_matrix_t cPttnMatrix;
					const auto& m = props.brush_matrix();
					cairo_matrix_init(&cPttnMatrix, m.m00, m.m01, m.m10, m.m11, m.m20, m.m21);
					cairo_pattern_set_matrix(pttn, &cPttnMatrix);
					cairo_set_source(_Native_context.get(), pttn);
					cairo_paint(_Native_context.get());
				}
			}
		}
		cairo_matrix_t ctm;
		cairo_matrix_init_scale(&ctm, 1.0F / (static_cast<float>(_Display_width) / userRect.width()), 1.0F / (static_cast<float>(_Display_height) / userRect.height()));
		cairo_matrix_translate(&ctm, -userRect.x(), -userRect.y());
		unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Cairo_surface->_Surface.get()), &cairo_pattern_destroy);
		cairo_pattern_set_matrix(pat.get(), &ctm);
		cairo_pattern_set_extend(pat.get(), CAIRO_EXTEND_NONE);
		cairo_pattern_set_filter(pat.get(), cairoFilter);
		cairo_set_source(_Native_context.get(), pat.get());
		cairo_paint(_Native_context.get());
		cairo_surface_flush(_Native_surface.get());
	}
	else {

		// Calculate the destRect values.
		switch (_Scaling) {
		case std::experimental::io2d::scaling::letterbox:
		{
			_Render_for_scaling_uniform_or_letterbox();
		} break;

		case std::experimental::io2d::scaling::uniform:
		{
			_Render_for_scaling_uniform_or_letterbox();
		} break;

		case std::experimental::io2d::scaling::fill_uniform:
		{
			// Maintain aspect ratio and center, but overflow if needed rather than letterboxing.
			if (_Width == _Display_width && _Height == _Display_height) {
				cairo_set_source_surface(_Native_context.get(), _Cairo_surface->_Surface.get(), 0.0F, 0.0F);
				cairo_paint(_Native_context.get());
			}
			else {
				auto widthRatio = static_cast<float>(_Display_width) / static_cast<float>(_Width);
				auto heightRatio = static_cast<float>(_Display_height) / static_cast<float>(_Height);
				if (widthRatio < heightRatio) {
					cairo_set_source_rgb(_Native_context.get(), 0.0F, 0.0F, 0.0F);
					cairo_paint(_Native_context.get());
					cairo_matrix_t ctm;
					cairo_matrix_init_scale(&ctm, 1.0F / heightRatio, 1.0F / heightRatio);
					cairo_matrix_translate(&ctm, trunc(abs(static_cast<float>(_Display_width - (_Width * heightRatio)) / 2.0F)), 0.0F);
					unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Cairo_surface->_Surface.get()), &cairo_pattern_destroy);
					cairo_pattern_set_matrix(pat.get(), &ctm);
					cairo_pattern_set_extend(pat.get(), CAIRO_EXTEND_NONE);
					cairo_pattern_set_filter(pat.get(), cairoFilter);
					cairo_set_source(_Native_context.get(), pat.get());
					cairo_paint(_Native_context.get());
				}
				else {
					cairo_set_source_rgb(_Native_context.get(), 0.0F, 0.0F, 0.0F);
					cairo_paint(_Native_context.get());
					cairo_matrix_t ctm;
					cairo_matrix_init_scale(&ctm, 1.0F / widthRatio, 1.0F / widthRatio);
					cairo_matrix_translate(&ctm, 0.0F, trunc(abs(static_cast<float>(_Display_height - (_Height * widthRatio)) / 2.0F)));
					unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Cairo_surface->_Surface.get()), &cairo_pattern_destroy);
					cairo_pattern_set_matrix(pat.get(), &ctm);
					cairo_pattern_set_extend(pat.get(), CAIRO_EXTEND_NONE);
					cairo_pattern_set_filter(pat.get(), cairoFilter);
					cairo_set_source(_Native_context.get(), pat.get());
					cairo_paint(_Native_context.get());
				}
			}
		} break;
		case std::experimental::io2d::scaling::fill_exact:
		{
			// Maintain aspect ratio and center, but overflow if needed rather than letterboxing.
			if (_Width == _Display_width && _Height == _Display_height) {
				cairo_set_source_surface(_Native_context.get(), _Cairo_surface->_Surface.get(), 0.0F, 0.0F);
				cairo_paint(_Native_context.get());
			}
			else {
				auto widthRatio = static_cast<float>(_Display_width) / static_cast<float>(_Width);
				auto heightRatio = static_cast<float>(_Display_height) / static_cast<float>(_Height);
				cairo_matrix_t ctm;
				cairo_matrix_init_scale(&ctm, 1.0F / widthRatio, 1.0F / heightRatio);
				unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Cairo_surface->_Surface.get()), &cairo_pattern_destroy);
				cairo_pattern_set_matrix(pat.get(), &ctm);
				cairo_pattern_set_extend(pat.get(), CAIRO_EXTEND_NONE);
				cairo_pattern_set_filter(pat.get(), cairoFilter);
				cairo_set_source(_Native_context.get(), pat.get());
				cairo_paint(_Native_context.get());
			}
		} break;
		case std::experimental::io2d::scaling::none:
		{
			cairo_set_source_surface(_Native_context.get(), _Cairo_surface->_Surface.get(), 0.0F, 0.0F);
			cairo_paint(_Native_context.get());
		} break;
		default:
		{
			assert("Unexpected _Scaling value." && false);
		} break;
		}
	}

	// 	cairo_restore(_Native_context.get());
	// This call to cairo_surface_flush is needed for Win32 surfaces to update.
	cairo_surface_flush(_Native_surface.get());
}

void cairo_display_surface::_Make_impl_surface_and_context() {
	// We render to the fixed size surface.
	_Cairo_surface->_Surface = unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(_Cairo_surface->_Format), _Width, _Height), &cairo_surface_destroy);
	_Cairo_surface->_Context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Cairo_surface->_Surface.get()), &cairo_destroy);
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Cairo_surface->_Surface.get()));
	_Throw_if_failed_cairo_status_t(cairo_status(_Cairo_surface->_Context.get()));
}

void cairo_display_surface::_Resize_window()
{
	_Handler_impl.resize_window(_Display_width, _Display_height);
}

cairo_display_surface::cairo_display_surface(display_surface<cairo_renderer>* ds, cairo_surface* cs, int preferredWidth, int preferredHeight, experimental::io2d::format preferredFormat, experimental::io2d::scaling scl, io2d::refresh_rate rr, float fps)
	: cairo_display_surface(ds, cs, preferredWidth, preferredHeight, preferredFormat, preferredWidth, preferredHeight, scl, rr, fps) {
}

cairo_display_surface::cairo_display_surface(display_surface<cairo_renderer>* ds, cairo_surface* cs, int preferredWidth, int preferredHeight, experimental::io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, experimental::io2d::scaling scl, io2d::refresh_rate rr, float fps)
	: _Cairo_surface(cs)
	, _Display_surface(ds)
	, _Display_width(preferredDisplayWidth)
	, _Display_height(preferredDisplayHeight)
	, _Scaling(scl)
	, _Width(preferredWidth)
	, _Height(preferredHeight)
	, _Draw_fn()
	, _Size_change_fn()
	, _User_scaling_fn()
	, _Auto_clear(false)
	, _Handler_impl(rr, fps)
	, _Redraw_requested(true)
	, _Native_surface(nullptr, &cairo_surface_destroy)
	, _Native_context(nullptr, &cairo_destroy)
	, _Letterbox_brush()
	, _Default_brush(rgba_color::transparent_black) {

	// Record the desired client window size
	if (preferredDisplayWidth <= 0 || preferredDisplayHeight <= 0 || preferredWidth <= 0 || preferredHeight <= 0 || preferredFormat == experimental::io2d::format::invalid) {
		throw invalid_argument("Invalid parameter.");
	}
}

void cairo_display_surface::draw_callback(const ::std::function<void(display_surface<cairo_renderer>& sfc)>& fn) {
	_Draw_fn = make_unique<::std::function<void(display_surface<cairo_renderer>& sfc)>>(fn);
}

void cairo_display_surface::size_change_callback(const ::std::function<void(display_surface<cairo_renderer>& sfc)>& fn) {
	_Size_change_fn = make_unique<::std::function<void(display_surface<cairo_renderer>& sfc)>>(fn);
}

void cairo_display_surface::width(int w) {
	dimensions(w, _Width);
}

void cairo_display_surface::height(int h) {
	dimensions(_Width, h);
}

void cairo_display_surface::display_width(int w) {
	display_dimensions(w, _Display_height);
}

void cairo_display_surface::display_height(int h) {
	display_dimensions(_Display_width, h);
}

void cairo_display_surface::dimensions(int w, int h) {
	bool recreate = false;

	if (_Width != w) {
		_Width = w;
		recreate = true;
	}
	if (_Height != h) {
		_Height = h;
		recreate = true;
	}

	if (recreate) {
		// Recreate the render target that is drawn to the displayed surface
		_Cairo_surface->_Surface = unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(_Cairo_surface->_Format), _Width, _Height), &cairo_surface_destroy);
		_Cairo_surface->_Context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Cairo_surface->_Surface.get()), &cairo_destroy);
		//_Ensure_state();
	}
}

void cairo_display_surface::display_dimensions(int dw, int dh) {
	_Display_width = dw;
	_Display_height = dh;
	_Resize_window();

	// Ensure that the native surface and context resize correctly.
	_Make_native_surface_and_context(windows_handler::context(_Handler_impl._Hwnd));
}

void cairo_display_surface::scaling(experimental::io2d::scaling scl) noexcept {
	_Scaling = scl;
}

void cairo_display_surface::user_scaling_callback(const function<experimental::io2d::bounding_box(const display_surface<cairo_renderer>&, bool&)>& fn) {
	_User_scaling_fn = make_unique<function<experimental::io2d::bounding_box(const display_surface<cairo_renderer>&, bool&)>>(fn);
}

void cairo_display_surface::letterbox_brush(const optional<cairo_brush>& b, const optional<brush_props> bp) noexcept {
	_Letterbox_brush = b;
	_Letterbox_brush_props = bp;
}

void cairo_display_surface::auto_clear(bool val) noexcept {
	_Auto_clear = val;
}

void cairo_display_surface::redraw_required() noexcept {
	_Redraw_requested = true;
}

format cairo_display_surface::format() const noexcept {
	return _Cairo_surface->_Format;
}

int cairo_display_surface::width() const noexcept {
	return _Width;
}

int cairo_display_surface::height() const noexcept {
	return _Height;
}

int cairo_display_surface::display_width() const noexcept {
	return _Display_width;
}

int cairo_display_surface::display_height() const noexcept {
	return _Display_height;
}

point_2d cairo_display_surface::dimensions() const noexcept {
	return { static_cast<float>(_Width), static_cast<float>(_Height) };
}

point_2d cairo_display_surface::display_dimensions() const noexcept {
	return { static_cast<float>(_Display_width), static_cast<float>(_Display_height) };
}

experimental::io2d::scaling cairo_display_surface::scaling() const noexcept {
	return _Scaling;
}

::std::function<::std::experimental::io2d::bounding_box(const display_surface<cairo_renderer>&, bool&)> cairo_display_surface::user_scaling_callback() const {
	return *_User_scaling_fn;
}

::std::function<::std::experimental::io2d::bounding_box(const display_surface<cairo_renderer>&, bool&)> cairo_display_surface::user_scaling_callback(error_code& ec) const noexcept {
	try {
		ec.clear();
		return *_User_scaling_fn;
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return nullptr;
	}
}

optional<cairo_brush> cairo_display_surface::letterbox_brush() const noexcept {
	return _Letterbox_brush;
}

optional<brush_props> cairo_display_surface::letterbox_brush_props() const noexcept {
	return _Letterbox_brush_props;
}

bool cairo_display_surface::auto_clear() const noexcept {
	return _Auto_clear;
}

int cairo_display_surface::begin_show() {
	return _Handler_impl.begin_show(this);
}

void cairo_display_surface::end_show() {
	_Handler_impl.end_show();
}

#if defined (_WIN32) || (_WIN64)
#include <cairo-win32.h>
void cairo_display_surface::_Make_native_surface_and_context(windows_handler::context&& dc) {
	try {
		_Native_surface = unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_win32_surface_create(dc), &cairo_surface_destroy);
		_Native_context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Native_surface.get()), &cairo_destroy);
		_Throw_if_failed_cairo_status_t(cairo_surface_status(_Native_surface.get()));
		_Throw_if_failed_cairo_status_t(cairo_status(_Native_context.get()));
	}
	catch (...) {
		// Release the DC to avoid a handle leak.
		throw;
	}
	// Release the DC to avoid a handle leak.
}
#endif