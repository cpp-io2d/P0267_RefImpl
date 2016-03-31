#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

font_resource_factory::font_resource_factory(const ::std::string& family, ::std::experimental::io2d::font_slant fs, ::std::experimental::io2d::font_weight fw,
	const ::std::experimental::io2d::matrix_2d& fm, const ::std::experimental::io2d::font_options& fo, const ::std::experimental::io2d::matrix_2d& sm)
	: _Family()
	, _Font_slant(fs)
	, _Font_weight(fw)
	, _Font_options(fo)
	, _Font_matrix(fm)
	, _Surface_matrix(sm) {
	// This logic exists to get the name of the font family that the system actually chose rather than just returning the requested family to the user.
	auto font = cairo_toy_font_face_create(family.c_str(), _Font_slant_to_cairo_font_slant_t(fs), _Font_weight_to_cairo_font_weight_t(fw));
	unique_ptr<cairo_font_face_t, decltype(&cairo_font_face_destroy)> ff(font, &cairo_font_face_destroy);
	_Throw_if_failed_cairo_status_t(cairo_font_face_status(font));
	_Family = cairo_toy_font_face_get_family(font);
}

font_resource_factory::font_resource_factory(const ::std::string& family, 
	error_code& ec, ::std::experimental::io2d::font_slant fs, ::std::experimental::io2d::font_weight fw, const ::std::experimental::io2d::matrix_2d& fm, 
	const ::std::experimental::io2d::font_options& fo, const ::std::experimental::io2d::matrix_2d& sm) noexcept
	: _Family()
	, _Font_slant(fs)
	, _Font_weight(fw)
	, _Font_options(fo)
	, _Font_matrix(fm)
	, _Surface_matrix(sm) {
	auto font = cairo_toy_font_face_create(family.c_str(), _Font_slant_to_cairo_font_slant_t(fs), _Font_weight_to_cairo_font_weight_t(fw));
	unique_ptr<cairo_font_face_t, decltype(&cairo_font_face_destroy)> ff(font, &cairo_font_face_destroy);
	ec = _Cairo_status_t_to_std_error_code(cairo_font_face_status(font));
	if (static_cast<bool>(ec)) {
		return;
	}
	::std::string s;
	try {
		s = cairo_toy_font_face_get_family(font);
	}
	catch (const ::std::bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (const ::std::length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Family = move(s);
	ec.clear();
}

void font_resource_factory::font_family(const string& f) {
	auto font = cairo_toy_font_face_create(f.c_str(), _Font_slant_to_cairo_font_slant_t(_Font_slant), _Font_weight_to_cairo_font_weight_t(_Font_weight));
	unique_ptr<cairo_font_face_t, decltype(&cairo_font_face_destroy)> ff(font, &cairo_font_face_destroy);
	_Throw_if_failed_cairo_status_t(cairo_font_face_status(font));
	_Family = cairo_toy_font_face_get_family(font);
}

void font_resource_factory::font_family(const string& f, error_code& ec) noexcept {
	auto font = cairo_toy_font_face_create(f.c_str(), _Font_slant_to_cairo_font_slant_t(_Font_slant), _Font_weight_to_cairo_font_weight_t(_Font_weight));
	unique_ptr<cairo_font_face_t, decltype(&cairo_font_face_destroy)> ff(font, &cairo_font_face_destroy);
	ec = _Cairo_status_t_to_std_error_code(cairo_font_face_status(font));
	if (static_cast<bool>(ec)) {
		return;
	}
	::std::string s;
	try {
		s = cairo_toy_font_face_get_family(font);
	}
	catch (const ::std::bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (const ::std::length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Family = move(s);
	ec.clear();
}

void font_resource_factory::font_slant(const ::std::experimental::io2d::font_slant fs) {
	_Font_slant = fs;
	auto font = cairo_toy_font_face_create(_Family.c_str(), _Font_slant_to_cairo_font_slant_t(_Font_slant), _Font_weight_to_cairo_font_weight_t(_Font_weight));
	unique_ptr<cairo_font_face_t, decltype(&cairo_font_face_destroy)> ff(font, &cairo_font_face_destroy);
	_Throw_if_failed_cairo_status_t(cairo_font_face_status(font));
	_Family = cairo_toy_font_face_get_family(font);
}

void font_resource_factory::font_slant(const ::std::experimental::io2d::font_slant fs, ::std::error_code& ec) noexcept {
	auto font = cairo_toy_font_face_create(_Family.c_str(), _Font_slant_to_cairo_font_slant_t(fs), _Font_weight_to_cairo_font_weight_t(_Font_weight));
	unique_ptr<cairo_font_face_t, decltype(&cairo_font_face_destroy)> ff(font, &cairo_font_face_destroy);
	ec = _Cairo_status_t_to_std_error_code(cairo_font_face_status(font));
	if (static_cast<bool>(ec)) {
		return;
	}
	::std::string s;
	try {
		s = cairo_toy_font_face_get_family(font);
	}
	catch (const ::std::bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (const ::std::length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Family = move(s);
	_Font_slant = fs;
	ec.clear();
}

void font_resource_factory::font_weight(::std::experimental::io2d::font_weight fw) {
	auto font = cairo_toy_font_face_create(_Family.c_str(), _Font_slant_to_cairo_font_slant_t(_Font_slant), _Font_weight_to_cairo_font_weight_t(fw));
	unique_ptr<cairo_font_face_t, decltype(&cairo_font_face_destroy)> ff(font, &cairo_font_face_destroy);
	_Throw_if_failed_cairo_status_t(cairo_font_face_status(font));
	::std::string s(cairo_toy_font_face_get_family(font));
	_Family = move(s);
	_Font_weight = fw;
}

void font_resource_factory::font_weight(::std::experimental::io2d::font_weight fw, ::std::error_code& ec) noexcept {
	auto font = cairo_toy_font_face_create(_Family.c_str(), _Font_slant_to_cairo_font_slant_t(_Font_slant), _Font_weight_to_cairo_font_weight_t(fw));
	unique_ptr<cairo_font_face_t, decltype(&cairo_font_face_destroy)> ff(font, &cairo_font_face_destroy);
	ec = _Cairo_status_t_to_std_error_code(cairo_font_face_status(font));
	if (static_cast<bool>(ec)) {
		return;
	}
	::std::string s;
	try {
		s = cairo_toy_font_face_get_family(font);
	}
	catch (const ::std::bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (const ::std::length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Family = move(s);
	_Font_weight = fw;
	ec.clear();
}

void font_resource_factory::font_options(const ::std::experimental::io2d::font_options& fo) noexcept {
	_Font_options = fo;
}

void font_resource_factory::font_matrix(const matrix_2d& m) noexcept {
	_Font_matrix = m;
}

void font_resource_factory::surface_matrix(const matrix_2d & m) noexcept {
	_Surface_matrix = m;
}

::std::string font_resource_factory::font_family() const {
	return _Family;
}

::std::string font_resource_factory::font_family(::std::error_code& ec) const noexcept {
	::std::string s;
	try {
		s = _Family;
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

::std::experimental::io2d::font_slant font_resource_factory::font_slant() const noexcept {
	return _Font_slant;
}

::std::experimental::io2d::font_weight font_resource_factory::font_weight() const noexcept {
	return _Font_weight;
}

::std::experimental::io2d::font_options font_resource_factory::font_options() const noexcept {
	return _Font_options;
}

matrix_2d font_resource_factory::font_matrix() const noexcept {
	return _Font_matrix;
}

matrix_2d font_resource_factory::surface_matrix() const noexcept {
	return _Surface_matrix;
}
