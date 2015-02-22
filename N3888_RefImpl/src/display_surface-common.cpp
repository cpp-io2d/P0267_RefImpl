#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

void display_surface::_All_dimensions(int w, int h, int dw, int dh) {
	dimensions(w, h);
	display_dimensions(dw, dh);
}

// Note: cairo_surface_flush(_Native_surface.get()); must be called after calling this function.
void display_surface::_Render_for_scaling_uniform_or_letterbox() {
	const cairo_filter_t cairoFilter = CAIRO_FILTER_BEST;
	if (_Width == _Display_width && _Height == _Display_height) {
		cairo_set_source_surface(_Native_context.get(), _Surface.get(), 0.0, 0.0);
		cairo_paint(_Native_context.get());
	}
	else {
		if (_Scaling == std::experimental::io2d::scaling::letterbox) {
			cairo_pattern_set_extend(_Letterbox_pttn.native_handle(), _Extend_to_cairo_extend_t(_Letterbox_pttn.extend()));
			cairo_pattern_set_filter(_Letterbox_pttn.native_handle(), _Filter_to_cairo_filter_t(_Letterbox_pttn.filter()));
			cairo_matrix_t cPttnMatrix;
			cairo_matrix_init(&cPttnMatrix, _Letterbox_pttn.matrix().m00(), _Letterbox_pttn.matrix().m01(), _Letterbox_pttn.matrix().m10(), _Letterbox_pttn.matrix().m11(), _Letterbox_pttn.matrix().m20(), _Letterbox_pttn.matrix().m21());
			cairo_pattern_set_matrix(_Letterbox_pttn.native_handle(), &cPttnMatrix);
			cairo_set_source(_Native_context.get(), _Letterbox_pttn.native_handle());
			cairo_paint(_Native_context.get());
		}

		auto widthRatio = static_cast<double>(_Display_width) / static_cast<double>(_Width);
		auto heightRatio = static_cast<double>(_Display_height) / static_cast<double>(_Height);

		cairo_matrix_t ctm;

		if (widthRatio < heightRatio) {
			cairo_matrix_init_scale(&ctm, 1.0 / widthRatio, 1.0 / widthRatio);
			cairo_matrix_translate(&ctm, 0.0, -trunc(abs(static_cast<double>(_Display_height - (_Height * widthRatio)) / 2.0)));
		}
		else {
			cairo_matrix_init_scale(&ctm, 1.0 / heightRatio, 1.0 / heightRatio);
			cairo_matrix_translate(&ctm, -trunc(abs(static_cast<double>(_Display_width - (_Width * heightRatio)) / 2.0)), 0.0);
		}

		unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Surface.get()), &cairo_pattern_destroy);
		cairo_pattern_set_matrix(pat.get(), &ctm);
		cairo_pattern_set_extend(pat.get(), CAIRO_EXTEND_NONE);
		cairo_pattern_set_filter(pat.get(), cairoFilter);
		cairo_set_source(_Native_context.get(), pat.get());
		cairo_paint(_Native_context.get());
	}
}

void display_surface::_Render_to_native_surface() {
	const cairo_filter_t cairoFilter = CAIRO_FILTER_BEST;
	cairo_surface_flush(_Surface.get());

	if (_User_scaling_fn != nullptr) {
		bool letterbox = false;
		auto userRect = _User_scaling_fn(*this, letterbox);
		if (letterbox) {
			cairo_pattern_set_extend(_Letterbox_pttn.native_handle(), _Extend_to_cairo_extend_t(_Letterbox_pttn.extend()));
			cairo_pattern_set_filter(_Letterbox_pttn.native_handle(), _Filter_to_cairo_filter_t(_Letterbox_pttn.filter()));
			cairo_matrix_t cPttnMatrix;
			cairo_matrix_init(&cPttnMatrix, _Letterbox_pttn.matrix().m00(), _Letterbox_pttn.matrix().m01(), _Letterbox_pttn.matrix().m10(), _Letterbox_pttn.matrix().m11(), _Letterbox_pttn.matrix().m20(), _Letterbox_pttn.matrix().m21());
			cairo_pattern_set_matrix(_Letterbox_pttn.native_handle(), &cPttnMatrix);
			cairo_set_source(_Native_context.get(), _Letterbox_pttn.native_handle());
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

	// This call to cairo_surface_flush is needed for Win32 surfaces to update.
	cairo_surface_flush(_Native_surface.get());
}

void display_surface::save() {
	surface::save();
	_Display_saved_state.push(make_tuple(_Scaling, _Width, _Height, _Display_width, _Display_height, _User_scaling_fn, _Letterbox_pttn));
}

void display_surface::restore() {
	surface::restore();
	auto& top = _Display_saved_state.top();
	_Scaling = get<0>(top);
	_All_dimensions(get<1>(top), get<2>(top), get<3>(top), get<4>(top));
}

void display_surface::draw_fn(const ::std::function<void(display_surface& sfc)>& fn) {
	_Draw_fn = fn;
}

void display_surface::size_change_fn(const ::std::function<void(display_surface& sfc)>& fn) {
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
		_Surface = unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(cairo_image_surface_create(_Format_to_cairo_format_t(_Format), _Width, _Height), &cairo_surface_destroy);
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

void display_surface::scaling(experimental::io2d::scaling scl) {
	_Scaling = scl;
}

void display_surface::user_scaling_fn(const function<experimental::io2d::rectangle(const display_surface&, bool&)>& fn) {
	_User_scaling_fn = fn;
}

void display_surface::clear_letterbox_pattern() {
	_Letterbox_pttn = create_pattern(solid_color_pattern_factory(rgba_color::transparent_black()));
}

void display_surface::letterbox_pattern(const rgba_color& c) {
	_Letterbox_pttn = create_pattern(solid_color_pattern_factory(c));
}

void display_surface::letterbox_pattern(const experimental::io2d::pattern& pttn) {
	_Letterbox_pttn = pttn;
}

format display_surface::format() const {
	return _Format;
}

int display_surface::width() const {
	return _Width;
}

int display_surface::height() const {
	return _Height;
}

int display_surface::display_width() const {
	return _Display_width;
}

int display_surface::display_height() const {
	return _Display_height;
}

tuple<int, int> display_surface::dimensions() const {
	return make_tuple(_Width, _Height);
}

tuple<int, int> display_surface::display_dimensions() const {
	return make_tuple(_Display_width, _Display_height);
}

experimental::io2d::scaling display_surface::scaling() const {
	return _Scaling;
}

const ::std::function<::std::experimental::io2d::rectangle(const display_surface&, bool&)>& display_surface::user_scaling_fn() const {
	return _User_scaling_fn;
}

experimental::io2d::pattern display_surface::letterbox_pattern() const {
	return _Letterbox_pttn;
}
