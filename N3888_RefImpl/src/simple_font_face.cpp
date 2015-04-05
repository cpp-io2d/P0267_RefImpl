#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

simple_font_face::simple_font_face(const string& family, ::std::experimental::io2d::font_slant fs, ::std::experimental::io2d::font_weight fw) noexcept : font_face(nullptr) {
	_Font_face = shared_ptr<cairo_font_face_t>(cairo_toy_font_face_create(family.c_str(), _Font_slant_to_cairo_font_slant_t(fs), _Font_weight_to_cairo_font_weight_t(fw)), &cairo_font_face_destroy);
}

simple_font_face::simple_font_face(simple_font_face&& other) noexcept : font_face(nullptr) {
	_Font_face = move(other._Font_face);
	other._Font_face = nullptr;
}

simple_font_face& simple_font_face::operator=(simple_font_face&& other) noexcept {
	if (this != &other) {
		_Font_face = move(other._Font_face);
		other._Font_face = nullptr;
	}
	return *this;
}

simple_font_face::~simple_font_face() {
}

string simple_font_face::font_family() const {
	return string(cairo_toy_font_face_get_family(_Font_face.get()));
}

void simple_font_face::font_family(string& str, error_code& ec) const noexcept {
	try {
		ec.clear();
		str = move(string(cairo_toy_font_face_get_family(_Font_face.get())));
	}
	catch (const length_error&) {
		str.clear();
		ec = make_error_code(errc::not_enough_memory);
	}
	catch (const bad_alloc&) {
		str.clear();
		ec = make_error_code(errc::not_enough_memory);
	}
}

::std::experimental::io2d::font_slant simple_font_face::font_slant() const noexcept {
	return _Cairo_font_slant_t_to_font_slant(cairo_toy_font_face_get_slant(_Font_face.get()));
}

::std::experimental::io2d::font_weight simple_font_face::font_weight() const noexcept {
	return _Cairo_font_weight_t_to_font_weight(cairo_toy_font_face_get_weight(_Font_face.get()));
}
