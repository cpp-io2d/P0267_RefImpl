#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

font_resource::font_resource(const font_resource_factory& f)
	: _Scaled_font()
	, _Font_family()
	, _Font_slant(f.font_slant())
	, _Font_weight(f.font_weight())
	, _Font_options() {
	cairo_matrix_t fm{ f.font_matrix().m00(), f.font_matrix().m01(), f.font_matrix().m10(), f.font_matrix().m11(), f.font_matrix().m20(), f.font_matrix().m21() };
	cairo_matrix_t sm{ f.surface_matrix().m00(), f.surface_matrix().m01(), f.surface_matrix().m10(), f.surface_matrix().m11(), f.surface_matrix().m20(), f.surface_matrix().m21() };
	auto fo = cairo_font_options_create();
	_Throw_if_failed_cairo_status_t(cairo_font_options_status(fo));
	_Font_options = shared_ptr<cairo_font_options_t>(fo, &cairo_font_options_destroy);
	cairo_font_options_set_antialias(fo, _Antialias_to_cairo_antialias_t(f.font_options().antialias()));
	cairo_font_options_set_subpixel_order(fo, _Subpixel_order_to_cairo_subpixel_order_t(f.font_options().subpixel_order()));
	_Font_family = make_shared<string>(f.font_family());
	_Throw_if_failed_cairo_status_t(cairo_font_options_status(fo));
	auto sf = cairo_scaled_font_create(cairo_toy_font_face_create(f.font_family().c_str(), _Font_slant_to_cairo_font_slant_t(f.font_slant()),
		_Font_weight_to_cairo_font_weight_t(f.font_weight())), &fm, &sm, fo);
	_Scaled_font = shared_ptr<cairo_scaled_font_t>(sf, &cairo_scaled_font_destroy);
	_Throw_if_failed_cairo_status_t(cairo_scaled_font_status(sf));
}

font_resource::font_resource(const font_resource_factory& f, error_code& ec) noexcept
	: _Scaled_font()
	, _Font_family()
	, _Font_slant(f.font_slant())
	, _Font_weight(f.font_weight())
	, _Font_options() {
	cairo_matrix_t fm{ f.font_matrix().m00(), f.font_matrix().m01(), f.font_matrix().m10(), f.font_matrix().m11(), f.font_matrix().m20(), f.font_matrix().m21() };
	cairo_matrix_t sm{ f.surface_matrix().m00(), f.surface_matrix().m01(), f.surface_matrix().m10(), f.surface_matrix().m11(), f.surface_matrix().m20(), f.surface_matrix().m21() };
	auto fo = cairo_font_options_create();

	ec = _Cairo_status_t_to_std_error_code(cairo_font_options_status(fo));
	if (static_cast<bool>(ec)) {
		return;
	}

	try {
		_Font_options = shared_ptr<cairo_font_options_t>(fo, &cairo_font_options_destroy);
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (...) {
		ec = make_error_code(io2d_error::invalid_status);
		return;
	}
	cairo_font_options_set_antialias(fo, _Antialias_to_cairo_antialias_t(f.font_options().antialias()));
	cairo_font_options_set_subpixel_order(fo, _Subpixel_order_to_cairo_subpixel_order_t(f.font_options().subpixel_order()));

	ec = _Cairo_status_t_to_std_error_code(cairo_font_options_status(fo));
	if (static_cast<bool>(ec)) {
		return;
	}

	try {
		_Font_family = make_shared<string>(f.font_family(ec));
		if (static_cast<bool>(ec)) {
			return;
		}
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (...) {
		ec = make_error_code(io2d_error::invalid_status);
		return;
	}

	if (static_cast<bool>(ec)) {
		return;
	}

	auto sf = cairo_scaled_font_create(cairo_toy_font_face_create(f.font_family().c_str(), _Font_slant_to_cairo_font_slant_t(f.font_slant()),
		_Font_weight_to_cairo_font_weight_t(f.font_weight())), &fm, &sm, fo);
	ec = _Cairo_status_t_to_std_error_code(cairo_scaled_font_status(sf));
	if (static_cast<bool>(ec)) {
		return;
	}
	try {
		_Scaled_font = shared_ptr<cairo_scaled_font_t>(sf, &cairo_scaled_font_destroy);
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (...) {
		ec = make_error_code(io2d_error::invalid_status);
		return;
	}
	ec.clear();
}

string font_resource::font_family() const {
	return *_Font_family.get();
}

string font_resource::font_family(error_code& ec) const noexcept {
	::std::string s;
	try {
		s = *_Font_family.get();
	}
	catch (const ::std::bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return s;
	}
	catch (const ::std::length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		return s;
	}
	ec.clear();
	return s;
}

experimental::io2d::font_slant font_resource::font_slant() const noexcept {
	return _Font_slant;
}

experimental::io2d::font_weight font_resource::font_weight() const noexcept {
	return _Font_weight;
}

experimental::io2d::font_options font_resource::font_options() const noexcept {
	return ::std::experimental::io2d::font_options(_Cairo_antialias_t_to_antialias(cairo_font_options_get_antialias(_Font_options.get())),
		_Cairo_subpixel_order_t_to_subpixel_order(cairo_font_options_get_subpixel_order(_Font_options.get())));
}

matrix_2d font_resource::font_matrix() const noexcept {
	cairo_matrix_t cm;
	cairo_scaled_font_get_font_matrix(_Scaled_font.get(), &cm);
	return matrix_2d(cm.xx, cm.xy, cm.yx, cm.yy, cm.x0, cm.y0);
}

matrix_2d font_resource::surface_matrix() const noexcept {
	cairo_matrix_t cm;
	cairo_scaled_font_get_ctm(_Scaled_font.get(), &cm);
	return matrix_2d(cm.xx, cm.xy, cm.yx, cm.yy, cm.x0, cm.y0);
}

experimental::io2d::font_extents font_resource::font_extents() const noexcept {
	cairo_font_extents_t fe;
	cairo_scaled_font_extents(_Scaled_font.get(), &fe);
	return experimental::io2d::font_extents(fe.ascent, fe.descent, fe.height);
}

experimental::io2d::text_extents font_resource::text_extents(const string& utf8) const noexcept {
	cairo_text_extents_t cte{};
	cairo_scaled_font_text_extents(_Scaled_font.get(), utf8.c_str(), &cte);
	return experimental::io2d::text_extents(cte.x_bearing, cte.y_bearing, cte.width, cte.height, cte.x_advance, cte.y_advance);
}

glyph_run font_resource::make_glyph_run(const string& utf8, const vector_2d& pos) const {
	return glyph_run(*this, utf8, pos);
}
