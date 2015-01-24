#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

void display_surface::_All_dimensions(int w, int h, int dw, int dh) {
	if (_Scaling == scaling::lock_to_display) {
		_Width = dw;
		_Height = dh;
		_Display_width = dw;
		_Display_height = dh;
		_Surface = unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(cairo_image_surface_create(_Format_to_cairo_format_t(_Format), _Width, _Height), &cairo_surface_destroy);
		_Context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy);
		_Resize_window();
		_Make_native_surface_and_context();
		_Ensure_state();
	}
	else {
		dimensions(w, h);
		display_dimensions(dw, dh);
	}
}

void display_surface::_Render_to_native_surface() {
	const cairo_filter_t cairoFilter = CAIRO_FILTER_BEST;
	cairo_surface_flush(_Surface.get());
	static_assert(scaling::default_scaling == scaling::uniform, "Failed static_assert 'scaling::default_scaling == scaling::uniform'.");
	switch (_Scaling) {
	case std::experimental::io2d::scaling::none:
	{
		cairo_set_source_surface(_Native_context.get(), _Surface.get(), 0.0, 0.0);
		cairo_paint(_Native_context.get());
		cairo_surface_flush(_Native_surface.get());
	} break;

	case std::experimental::io2d::scaling::uniform:
	{
		if (_Width == _Display_width && _Height == _Display_height) {
			cairo_set_source_surface(_Native_context.get(), _Surface.get(), 0.0, 0.0);
			cairo_paint(_Native_context.get());
			cairo_surface_flush(_Native_surface.get());
		}
		else {
			auto widthRatio = static_cast<double>(_Display_width) / static_cast<double>(_Width);
			auto heightRatio = static_cast<double>(_Display_height) / static_cast<double>(_Height);
			if (widthRatio < heightRatio) {
				cairo_set_source_rgb(_Native_context.get(), 0.0, 0.0, 0.0);
				cairo_paint(_Native_context.get());
				cairo_matrix_t ctm;
				cairo_matrix_init_scale(&ctm, 1.0 / widthRatio, 1.0 / widthRatio);
				cairo_matrix_translate(&ctm, 0.0, -trunc(abs(static_cast<double>(_Display_height - (_Height * widthRatio)) / 2.0)));
				unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Surface.get()), &cairo_pattern_destroy);
				cairo_pattern_set_matrix(pat.get(), &ctm);
				cairo_pattern_set_extend(pat.get(), CAIRO_EXTEND_NONE);
				cairo_pattern_set_filter(pat.get(), cairoFilter);
				cairo_set_source(_Native_context.get(), pat.get());
				cairo_paint(_Native_context.get());
				cairo_surface_flush(_Native_surface.get());
			}
			else {
				cairo_set_source_rgb(_Native_context.get(), 0.0, 0.0, 0.0);
				cairo_paint(_Native_context.get());
				cairo_matrix_t ctm;
				cairo_matrix_init_scale(&ctm, 1.0 / heightRatio, 1.0 / heightRatio);
				cairo_matrix_translate(&ctm, -trunc(abs(static_cast<double>(_Display_width - (_Width * heightRatio)) / 2.0)), 0.0);
				unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(_Surface.get()), &cairo_pattern_destroy);
				cairo_pattern_set_matrix(pat.get(), &ctm);
				cairo_pattern_set_extend(pat.get(), CAIRO_EXTEND_NONE);
				cairo_pattern_set_filter(pat.get(), cairoFilter);
				cairo_set_source(_Native_context.get(), pat.get());
				cairo_paint(_Native_context.get());
				cairo_surface_flush(_Native_surface.get());
			}
		}
	} break;

	case std::experimental::io2d::scaling::fill:
	{
		// Maintain aspect ratio and center, but overflow if needed rather than letterboxing.
		if (_Width == _Display_width && _Height == _Display_height) {
			cairo_set_source_surface(_Native_context.get(), _Surface.get(), 0.0, 0.0);
			cairo_paint(_Native_context.get());
			cairo_surface_flush(_Native_surface.get());
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
				cairo_surface_flush(_Native_surface.get());
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
				cairo_surface_flush(_Native_surface.get());
			}
		}
	} break;
	case std::experimental::io2d::scaling::exact:
	{
		// Maintain aspect ratio and center, but overflow if needed rather than letterboxing.
		if (_Width == _Display_width && _Height == _Display_height) {
			cairo_set_source_surface(_Native_context.get(), _Surface.get(), 0.0, 0.0);
			cairo_paint(_Native_context.get());
			cairo_surface_flush(_Native_surface.get());
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
			cairo_surface_flush(_Native_surface.get());
		}
	} break;
	case std::experimental::io2d::scaling::lock_to_display:
	{
		if (_Width == _Display_width && _Height == _Display_height) {
			cairo_set_source_surface(_Native_context.get(), _Surface.get(), 0.0, 0.0);
			cairo_paint(_Native_context.get());
			cairo_surface_flush(_Native_surface.get());
		}
		else {
			dimensions(_Display_width, _Display_height);
		}
	} break;
	default:
	{
		assert("Unexpected _Scaling value." && false);
	} break;
	}
}

void display_surface::save() {
	surface::save();
	_Display_saved_state.push(make_tuple(_Scaling, _Width, _Height, _Display_width, _Display_height));
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
	bool recreate = false;

	if (_Scaling != scaling::lock_to_display) {
		if (_Width != w) {
			_Width = w;
			recreate = true;
		}
	}
	else {
		if (_Scaling == scaling::lock_to_display && _Width != _Display_width) {
			_Width = _Display_width;
			recreate = true;
		}
	}

	if (recreate) {
		_Surface = unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(cairo_image_surface_create(_Format_to_cairo_format_t(_Format), _Width, _Height), &cairo_surface_destroy);
		_Context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy);
		_Ensure_state();
	}
}

void display_surface::height(int h) {
	bool recreate = false;

	if (_Scaling != scaling::lock_to_display) {
		if (_Height != h) {
			_Height = h;
			recreate = true;
		}
	}
	else {
		if (_Scaling == scaling::lock_to_display && _Height != _Display_height) {
			_Height = _Display_height;
			recreate = true;
		}
	}

	if (recreate) {
		_Surface = unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(cairo_image_surface_create(_Format_to_cairo_format_t(_Format), _Width, _Height), &cairo_surface_destroy);
		_Context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy);
		_Ensure_state();
	}
}

void display_surface::display_width(int w) {
	_Display_width = w;
	_Resize_window();
	_Make_native_surface_and_context();

	if (_Scaling == scaling::lock_to_display) {
		width(w);
	}
}

void display_surface::display_height(int h) {
	_Display_height = h;
	_Resize_window();
	_Make_native_surface_and_context();

	if (_Scaling == scaling::lock_to_display) {
		height(h);
	}
}

void display_surface::dimensions(int w, int h) {
	bool recreate = false;

	if (_Scaling != scaling::lock_to_display) {
		if (_Width != w) {
			_Width = w;
			recreate = true;
		}
		if (_Height != h) {
			_Height = h;
			recreate = true;
		}
	}
	else {
		if (_Scaling == scaling::lock_to_display && (_Width != _Display_width || _Height != _Display_height)) {
			_Width = _Display_width;
			_Height = _Display_height;
			recreate = true;
		}
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

	if (_Scaling == scaling::lock_to_display) {
		dimensions(dw, dh);
	}
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
