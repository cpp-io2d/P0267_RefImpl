#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

toy_font_face::toy_font_face(const string& family, font_slant slant, font_weight weight) : font_face(nullptr) {
	_Font_face = shared_ptr<cairo_font_face_t>(cairo_toy_font_face_create(family.c_str(), _Font_slant_to_cairo_font_slant_t(slant), _Font_weight_to_cairo_font_weight_t(weight)), &cairo_font_face_destroy);
}

toy_font_face::toy_font_face(toy_font_face&& other) : font_face(nullptr) {
	_Font_face = move(other._Font_face);
	other._Font_face = nullptr;
}

toy_font_face& toy_font_face::operator=(toy_font_face&& other) {
	if (this != &other) {
		_Font_face = move(other._Font_face);
		other._Font_face = nullptr;
	}
	return *this;
}

string toy_font_face::get_family() {
	return string(cairo_toy_font_face_get_family(_Font_face.get()));
}

font_slant toy_font_face::get_slant() {
	return _Cairo_font_slant_t_to_font_slant(cairo_toy_font_face_get_slant(_Font_face.get()));
}

font_weight toy_font_face::get_weight() {
	return _Cairo_font_weight_t_to_font_weight(cairo_toy_font_face_get_weight(_Font_face.get()));
}
