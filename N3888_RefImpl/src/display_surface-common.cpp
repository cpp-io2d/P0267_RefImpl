#include "io2d.h"

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
		cairo_set_source_surface(_Native_context.get(), _Surface.get(), 0.0F, 0.0F);
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
			unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Surface.get()), &cairo_pattern_destroy);
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
					cairo_set_source(_Native_context.get(), _Default_brush.native_handle());
					//cairo_paint(_Native_context.get());
				}
				else {
					auto pttn = _Letterbox_brush.value().native_handle();
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
						const auto& m = props.matrix();
						cairo_matrix_init(&cPttnMatrix, m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21());
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
			unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Surface.get()), &cairo_pattern_destroy);
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
					cairo_set_source(_Native_context.get(), _Default_brush.native_handle());
					//cairo_paint(_Native_context.get());
				}
				else {
					auto pttn = _Letterbox_brush.value().native_handle();
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
						const auto& m = props.matrix();
						cairo_matrix_init(&cPttnMatrix, m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21());
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

void display_surface::_Render_to_native_surface() {
	const cairo_filter_t cairoFilter = CAIRO_FILTER_GOOD;
	cairo_surface_flush(_Surface.get());
// 	cairo_save(_Native_context.get());
	cairo_set_operator(_Native_context.get(), CAIRO_OPERATOR_SOURCE);
	if (_User_scaling_fn != nullptr && _User_scaling_fn != nullptr) {
		bool letterbox = false;
		auto userRect = (*_User_scaling_fn)(*this, letterbox);
		if (letterbox) {
			if (_Letterbox_brush == nullopt) {
				cairo_set_source(_Native_context.get(), _Default_brush.native_handle());
				cairo_paint(_Native_context.get());
			}
			else {
				auto pttn = _Letterbox_brush.value().native_handle();
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
					const auto& m = props.matrix();
					cairo_matrix_init(&cPttnMatrix, m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21());
					cairo_pattern_set_matrix(pttn, &cPttnMatrix);
					cairo_set_source(_Native_context.get(), pttn);
					cairo_paint(_Native_context.get());
				}
			}
		}
		cairo_matrix_t ctm;
		cairo_matrix_init_scale(&ctm, 1.0F / (static_cast<float>(_Display_width) / userRect.width()), 1.0F / (static_cast<float>(_Display_height) / userRect.height()));
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
				cairo_set_source_surface(_Native_context.get(), _Surface.get(), 0.0F, 0.0F);
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
					unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Surface.get()), &cairo_pattern_destroy);
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
				cairo_set_source_surface(_Native_context.get(), _Surface.get(), 0.0F, 0.0F);
				cairo_paint(_Native_context.get());
			}
			else {
				auto widthRatio = static_cast<float>(_Display_width) / static_cast<float>(_Width);
				auto heightRatio = static_cast<float>(_Display_height) / static_cast<float>(_Height);
				cairo_matrix_t ctm;
				cairo_matrix_init_scale(&ctm, 1.0F / widthRatio, 1.0F / heightRatio);
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
			cairo_set_source_surface(_Native_context.get(), _Surface.get(), 0.0F, 0.0F);
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

void display_surface::draw_callback(const ::std::function<void(display_surface& sfc)>& fn) {
	_Draw_fn = make_unique<::std::function<void(display_surface& sfc)>>(fn);
}

void display_surface::size_change_callback(const ::std::function<void(display_surface& sfc)>& fn) {
	_Size_change_fn = make_unique<::std::function<void(display_surface& sfc)>>(fn);
}

void display_surface::width(int w) noexcept {
	dimensions(w, _Width);
}

void display_surface::height(int h) noexcept {
	dimensions(_Width, h);
}

void display_surface::display_width(int w) noexcept {
	display_dimensions(w, _Display_height);
}

void display_surface::display_height(int h) noexcept {
	display_dimensions(_Display_width, h);
}

void display_surface::dimensions(int w, int h) noexcept {
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
		//_Ensure_state();
	}
}

void display_surface::display_dimensions(int dw, int dh) noexcept {
	_Display_width = dw;
	_Display_height = dh;
	_Resize_window();

	// Ensure that the native surface and context resize correctly.
	_Make_native_surface_and_context();
}

void display_surface::scaling(experimental::io2d::scaling scl) noexcept {
	_Scaling = scl;
}

void display_surface::user_scaling_callback(const function<experimental::io2d::bounding_box(const display_surface&, bool&)>& fn) {
	_User_scaling_fn = make_unique<function<experimental::io2d::bounding_box(const display_surface&, bool&)>>(fn);
}

void display_surface::letterbox_brush(const optional<brush>& b, const optional<brush_props>& bp) noexcept {
	_Letterbox_brush = b;
	_Letterbox_brush_props = bp;
}

void display_surface::auto_clear(bool val) noexcept {
	_Auto_clear = val;
}

void display_surface::refresh_rate(experimental::io2d::refresh_rate rr) noexcept {
	if (rr == experimental::io2d::refresh_rate::fixed && _Refresh_rate != rr) {
		_Elapsed_draw_time = 0.0F;
	}
	_Refresh_rate = rr;
}

bool display_surface::desired_frame_rate(float fps) noexcept {
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
	_Redraw_requested = true;
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

vector_2d display_surface::dimensions() const noexcept {
	return { static_cast<float>(_Width), static_cast<float>(_Height) };
}

vector_2d display_surface::display_dimensions() const noexcept {
	return { static_cast<float>(_Display_width), static_cast<float>(_Display_height) };
}

experimental::io2d::scaling display_surface::scaling() const noexcept {
	return _Scaling;
}

::std::function<::std::experimental::io2d::bounding_box(const display_surface&, bool&)> display_surface::user_scaling_callback() const {
	return *_User_scaling_fn;
}

::std::function<::std::experimental::io2d::bounding_box(const display_surface&, bool&)> display_surface::user_scaling_callback(error_code& ec) const noexcept {
	try {
		ec.clear();
		return *_User_scaling_fn;
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return nullptr;
	}
}

const optional<brush>& display_surface::letterbox_brush() const noexcept {
	return _Letterbox_brush;
}

optional<brush_props> display_surface::letterbox_brush_props() const noexcept {
	return _Letterbox_brush_props;
}

bool display_surface::auto_clear() const noexcept {
	return _Auto_clear;
}

experimental::io2d::refresh_rate display_surface::refresh_rate() const noexcept {
	return _Refresh_rate;
}

float display_surface::desired_frame_rate() const noexcept {
	return _Desired_frame_rate;
}

float display_surface::elapsed_draw_time() const noexcept {
	return _Elapsed_draw_time / 1'000'000.0F;
}
