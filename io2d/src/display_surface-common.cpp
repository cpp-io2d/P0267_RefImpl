#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;
using namespace std::chrono;

void display_surface::_All_dimensions(int w, int h, int dw, int dh) {
	dimensions(w, h);
	display_dimensions(dw, dh);
}

// Note: cairo_surface_flush(_Native_surface.get()); must be called after calling this function.
void display_surface::_Render_for_scaling_uniform_or_letterbox() {
	const cairo_filter_t cairoFilter = CAIRO_FILTER_GOOD;
	
// 	static auto previousTime = steady_clock::now();

	if (_Width == _Display_width && _Height == _Display_height) {
		cairo_set_source_surface(_Native_context.get(), _Surface.get(), 0.0, 0.0);
		cairo_paint(_Native_context.get());
	}
	else {
		if (_Scaling == std::experimental::io2d::scaling::letterbox) {
			cairo_pattern_set_extend(_Letterbox_brush.native_handle(), _Extend_to_cairo_extend_t(_Letterbox_brush.extend()));
			cairo_pattern_set_filter(_Letterbox_brush.native_handle(), _Filter_to_cairo_filter_t(_Letterbox_brush.filter()));
			cairo_matrix_t cPttnMatrix;
			cairo_matrix_init(&cPttnMatrix, _Letterbox_brush.matrix().m00(), _Letterbox_brush.matrix().m01(), _Letterbox_brush.matrix().m10(), _Letterbox_brush.matrix().m11(), _Letterbox_brush.matrix().m20(), _Letterbox_brush.matrix().m21());
			cairo_pattern_set_matrix(_Letterbox_brush.native_handle(), &cPttnMatrix);
			cairo_set_source(_Native_context.get(), _Letterbox_brush.native_handle());
			cairo_paint(_Native_context.get());
		}
		const auto whRatio = static_cast<double>(_Width) / static_cast<double>(_Height);
		const auto displayWHRatio = static_cast<double>(_Display_width) / static_cast<double>(_Display_height);
		cairo_matrix_t ctm;
		auto nativeContext = _Native_context.get();
		//cairo_save(nativeContext);
		double rectX, rectY, rectWidth, rectHeight;
		if (whRatio < displayWHRatio) {
			cairo_new_path(nativeContext);
			const auto displayHeightAsDouble = static_cast<double>(_Display_height);
			rectWidth = trunc(displayHeightAsDouble * whRatio);
			rectHeight = displayHeightAsDouble;
			rectX = trunc(abs(rectWidth - static_cast<double>(_Display_width)) / 2.0);
			rectY = 0.0;
			cairo_rectangle(nativeContext, rectX, rectY, rectWidth, rectHeight);

			const auto heightRatio = static_cast<double>(_Height) / static_cast<double>(_Display_height);
			cairo_matrix_init_scale(&ctm, heightRatio, heightRatio);
			cairo_matrix_translate(&ctm, -rectX, 0.0);
		}
		else {
			cairo_new_path(nativeContext);
			const auto displayWidthAsDouble = static_cast<double>(_Display_width);
			rectWidth = displayWidthAsDouble;
			rectHeight = trunc(displayWidthAsDouble / whRatio);
			rectX = 0.0;
			rectY = trunc(abs(rectHeight - static_cast<double>(_Display_height)) / 2.0);
			cairo_rectangle(nativeContext, rectX, rectY, rectWidth, rectHeight);

			const auto widthRatio = static_cast<double>(_Width) / static_cast<double>(_Display_width);
			cairo_matrix_init_scale(&ctm, widthRatio, widthRatio);
			cairo_matrix_translate(&ctm, 0.0, -rectY);
		}
		unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Surface.get()), &cairo_pattern_destroy);
		cairo_pattern_set_matrix(pat.get(), &ctm);
		cairo_pattern_set_extend(pat.get(), CAIRO_EXTEND_NONE);
		cairo_pattern_set_filter(pat.get(), cairoFilter);
		cairo_set_source(_Native_context.get(), pat.get());
		cairo_fill(_Native_context.get());
		//cairo_restore(nativeContext);
	}

// 	auto currentTime = steady_clock::now();
// 	auto elapsedTimeIncrement = static_cast<double>(duration_cast<nanoseconds>(currentTime - previousTime).count());
// 	previousTime = currentTime;
// 	stringstream timingStr;
// 	timingStr << "timing: " << elapsedTimeIncrement / 1'000'000.0 << endl;
// 	cerr << timingStr.str().c_str();
}

void display_surface::_Render_to_native_surface() {
	const cairo_filter_t cairoFilter = CAIRO_FILTER_GOOD;
	cairo_surface_flush(_Surface.get());
// 	cairo_save(_Native_context.get());
	cairo_set_operator(_Native_context.get(), CAIRO_OPERATOR_SOURCE);
	if (_User_scaling_fn != nullptr) {
		bool letterbox = false;
		auto userRect = _User_scaling_fn(*this, letterbox);
		if (letterbox) {
			cairo_pattern_set_extend(_Letterbox_brush.native_handle(), _Extend_to_cairo_extend_t(_Letterbox_brush.extend()));
			cairo_pattern_set_filter(_Letterbox_brush.native_handle(), _Filter_to_cairo_filter_t(_Letterbox_brush.filter()));
			cairo_matrix_t cPttnMatrix;
			cairo_matrix_init(&cPttnMatrix, _Letterbox_brush.matrix().m00(), _Letterbox_brush.matrix().m01(), _Letterbox_brush.matrix().m10(), _Letterbox_brush.matrix().m11(), _Letterbox_brush.matrix().m20(), _Letterbox_brush.matrix().m21());
			cairo_pattern_set_matrix(_Letterbox_brush.native_handle(), &cPttnMatrix);
			cairo_set_source(_Native_context.get(), _Letterbox_brush.native_handle());
			cairo_paint(_Native_context.get());
		}
		cairo_matrix_t ctm;
		cairo_matrix_init_scale(&ctm, 1.0 / (static_cast<double>(_Display_width) / userRect.width()), 1.0 / (static_cast<double>(_Display_height) / userRect.height()));
		cairo_matrix_translate(&ctm, -userRect.x(), -userRect.y());
		unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Surface.get()), &cairo_pattern_destroy);
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
				cairo_set_source_surface(_Native_context.get(), _Surface.get(), 0.0, 0.0);
				cairo_paint(_Native_context.get());
			}
			else {
				auto widthRatio = static_cast<double>(_Display_width) / static_cast<double>(_Width);
				auto heightRatio = static_cast<double>(_Display_height) / static_cast<double>(_Height);
				if (widthRatio < heightRatio) {
					cairo_set_source_rgb(_Native_context.get(), 0.0, 0.0, 0.0);
					cairo_paint(_Native_context.get());
					cairo_matrix_t ctm;
					cairo_matrix_init_scale(&ctm, 1.0 / heightRatio, 1.0 / heightRatio);
					cairo_matrix_translate(&ctm, trunc(abs(static_cast<double>(_Display_width - (_Width * heightRatio)) / 2.0)), 0.0);
					unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Surface.get()), &cairo_pattern_destroy);
					cairo_pattern_set_matrix(pat.get(), &ctm);
					cairo_pattern_set_extend(pat.get(), CAIRO_EXTEND_NONE);
					cairo_pattern_set_filter(pat.get(), cairoFilter);
					cairo_set_source(_Native_context.get(), pat.get());
					cairo_paint(_Native_context.get());
				}
				else {
					cairo_set_source_rgb(_Native_context.get(), 0.0, 0.0, 0.0);
					cairo_paint(_Native_context.get());
					cairo_matrix_t ctm;
					cairo_matrix_init_scale(&ctm, 1.0 / widthRatio, 1.0 / widthRatio);
					cairo_matrix_translate(&ctm, 0.0, trunc(abs(static_cast<double>(_Display_height - (_Height * widthRatio)) / 2.0)));
					unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Surface.get()), &cairo_pattern_destroy);
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
				cairo_set_source_surface(_Native_context.get(), _Surface.get(), 0.0, 0.0);
				cairo_paint(_Native_context.get());
			}
			else {
				auto widthRatio = static_cast<double>(_Display_width) / static_cast<double>(_Width);
				auto heightRatio = static_cast<double>(_Display_height) / static_cast<double>(_Height);
				cairo_matrix_t ctm;
				cairo_matrix_init_scale(&ctm, 1.0 / widthRatio, 1.0 / heightRatio);
				unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Surface.get()), &cairo_pattern_destroy);
				cairo_pattern_set_matrix(pat.get(), &ctm);
				cairo_pattern_set_extend(pat.get(), CAIRO_EXTEND_NONE);
				cairo_pattern_set_filter(pat.get(), cairoFilter);
				cairo_set_source(_Native_context.get(), pat.get());
				cairo_paint(_Native_context.get());
			}
		} break;
		case std::experimental::io2d::scaling::none:
		{
			cairo_set_source_surface(_Native_context.get(), _Surface.get(), 0.0, 0.0);
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

void display_surface::save() {
	surface::save();
	// We shouldn't be saving most of this to begin with (esp. the display width and height) and the rest can be saved by the user and saving it doesn't seem consistent with the purpose of save.
	//_Display_saved_state.push(make_tuple(_Scaling, _Width, _Height, _Display_width, _Display_height, _User_scaling_fn, _Letterbox_brush));
}

void display_surface::save(error_code& ec) noexcept {
	surface::save(ec);
	if (static_cast<bool>(ec)) {
		return;
	}
	ec.clear();
	//try {
	//	_Display_saved_state.push(make_tuple(_Scaling, _Width, _Height, _Display_width, _Display_height, _User_scaling_fn, _Letterbox_brush));
	//}
	//catch (const length_error&) {
	//	ec = make_error_code(errc::not_enough_memory);
	//	return;
	//}
	//catch (const bad_alloc&) {
	//	ec = make_error_code(errc::not_enough_memory);
	//	return;
	//}
	//ec.clear();
}

void display_surface::restore() {
	surface::restore();
	//auto& top = _Display_saved_state.top();
	//_Scaling = get<0>(top);
	//_All_dimensions(get<1>(top), get<2>(top), get<3>(top), get<4>(top));
}

void display_surface::restore(error_code& ec) noexcept {
	surface::restore(ec);
	if (static_cast<bool>(ec)) {
		return;
	}
	ec.clear();
}

void display_surface::draw_callback(const ::std::function<void(display_surface& sfc)>& fn) {
	_Draw_fn = fn;
}

void display_surface::size_change_callback(const ::std::function<void(display_surface& sfc)>& fn) {
	_Size_change_fn = fn;
}

void display_surface::width(int w) {
	dimensions(w, _Width);
}

void display_surface::height(int h) {
	dimensions(_Width, h);
}

void display_surface::display_width(int w) {
	display_dimensions(w, _Display_height);
}

void display_surface::display_height(int h) {
	display_dimensions(_Display_width, h);
}

void display_surface::dimensions(int w, int h) {
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
		_Surface = unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(_Format), _Width, _Height), &cairo_surface_destroy);
		_Context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy);
		_Ensure_state();
	}
}

void display_surface::display_dimensions(int dw, int dh) {
	_Display_width = dw;
	_Display_height = dh;
	_Resize_window();

	// Ensure that the native surface and context resize correctly.
	_Make_native_surface_and_context();
}

void display_surface::scaling(experimental::io2d::scaling scl) noexcept {
	_Scaling = scl;
}

void display_surface::user_scaling_callback(const function<experimental::io2d::rectangle(const display_surface&, bool&)>& fn) {
	_User_scaling_fn = fn;
}

void display_surface::letterbox_brush(nullopt_t) noexcept {
	_Letterbox_brush = _Default_brush;
}

void display_surface::letterbox_brush(const rgba_color& c) {
	_Letterbox_brush = experimental::io2d::brush(solid_color_brush_factory(c));
}

void display_surface::letterbox_brush(const experimental::io2d::brush& b) {
	_Letterbox_brush = b;
}

void display_surface::auto_clear(bool val) noexcept {
	_Auto_clear = val;
}

void display_surface::refresh_rate(experimental::io2d::refresh_rate rr) noexcept {
	if (rr == experimental::io2d::refresh_rate::fixed && _Refresh_rate != rr) {
		_Elapsed_draw_time = 0.0;
	}
	_Refresh_rate = rr;
}

bool display_surface::desired_frame_rate(double fps) noexcept {
	if (!isfinite(fps)) {
		return true;
	}
	if (fps < _Minimum_frame_rate) {
		_Desired_frame_rate = _Minimum_frame_rate;
		return true;
	}
	if (fps > _Maximum_frame_rate) {
		_Desired_frame_rate = _Maximum_frame_rate;
		return true;
	}
	_Desired_frame_rate = fps;

	return false;
}

void display_surface::redraw_required() noexcept {
	_Redraw_requested.store(true, std::memory_order_release);
}

format display_surface::format() const noexcept {
	return _Format;
}

int display_surface::width() const noexcept {
	return _Width;
}

int display_surface::height() const noexcept {
	return _Height;
}

int display_surface::display_width() const noexcept {
	return _Display_width;
}

int display_surface::display_height() const noexcept {
	return _Display_height;
}

tuple<int, int> display_surface::dimensions() const noexcept {
	return make_tuple(_Width, _Height);
}

tuple<int, int> display_surface::display_dimensions() const noexcept {
	return make_tuple(_Display_width, _Display_height);
}

experimental::io2d::scaling display_surface::scaling() const noexcept {
	return _Scaling;
}

::std::function<::std::experimental::io2d::rectangle(const display_surface&, bool&)> display_surface::user_scaling_callback() const {
	return _User_scaling_fn;
}

::std::function<::std::experimental::io2d::rectangle(const display_surface&, bool&)> display_surface::user_scaling_callback(error_code& ec) const noexcept {
	try {
		ec.clear();
		return _User_scaling_fn;
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return nullptr;
	}
}

experimental::io2d::brush display_surface::letterbox_brush() const noexcept {
	return _Letterbox_brush;
}

bool display_surface::auto_clear() const noexcept {
	return _Auto_clear;
}

experimental::io2d::refresh_rate display_surface::refresh_rate() const noexcept {
	return _Refresh_rate;
}

double display_surface::desired_frame_rate() const noexcept {
	return _Desired_frame_rate;
}

double display_surface::elapsed_draw_time() const noexcept {
	return _Elapsed_draw_time / 1'000'000.0;
}
