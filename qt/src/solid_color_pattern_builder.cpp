#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

solid_color_pattern_builder::solid_color_pattern_builder(solid_color_pattern_builder&& other)
: _Pattern_type(move(other._Pattern_type))
, _Extend(move(other._Extend))
, _Filter(move(other._Filter))
, _Matrix(move(other._Matrix))
, _Color(move(other._Color)) {
}

solid_color_pattern_builder& solid_color_pattern_builder::operator=(solid_color_pattern_builder&& other) {
	if (this != &other) {
		_Pattern_type = move(other._Pattern_type);
		_Extend = move(other._Extend);
		_Filter = move(other._Filter);
		_Matrix = move(other._Matrix);
		_Color = move(other._Color);
	}
	return *this;
}

solid_color_pattern_builder::solid_color_pattern_builder(const rgba_color& color)
: _Pattern_type(pattern_type::solid_color)
, _Extend(extend::default_extend)
, _Filter(filter::default_filter)
, _Matrix(matrix::init_identity())
, _Color(color){
	assert(color.r >= 0.0 && color.r <= 1.0);
	assert(color.g >= 0.0 && color.g <= 1.0);
	assert(color.b >= 0.0 && color.b <= 1.0);
	assert(color.a >= 0.0 && color.a <= 1.0);
}

pattern solid_color_pattern_builder::get_pattern() {
//	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(_Extend));
//	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(_Filter));
//	cairo_matrix_t mtrx{ _Matrix.xx, _Matrix.yx, _Matrix.xy, _Matrix.yy, _Matrix.x0, _Matrix.y0 };
//	cairo_pattern_set_matrix(pat, &mtrx);

	auto pat = new QBrush(rgba_color_to_QColor(_Color), Qt::SolidPattern);
	return pattern(pat);
}

void solid_color_pattern_builder::set_extend(extend e) {
	_Extend = e;
}

extend solid_color_pattern_builder::get_extend() {
	return _Extend;
}

void solid_color_pattern_builder::set_filter(filter f) {
	_Filter = f;
}

filter solid_color_pattern_builder::get_filter() {
	return _Filter;
}

void solid_color_pattern_builder::set_matrix(const matrix& m) {
	_Matrix = m;
}

matrix solid_color_pattern_builder::get_matrix() {
	return _Matrix;
}

rgba_color solid_color_pattern_builder::get_rgba() {
	return _Color;
}

void solid_color_pattern_builder::set_rgba(const rgba_color& color) {
	assert(color.r >= 0.0 && color.r <= 1.0);
	assert(color.g >= 0.0 && color.g <= 1.0);
	assert(color.b >= 0.0 && color.b <= 1.0);
	assert(color.a >= 0.0 && color.a <= 1.0);
	_Color = color;
}

double solid_color_pattern_builder::get_red() {
	return _Color.r;
}

void solid_color_pattern_builder::set_red(double red) {
	assert(red >= 0.0 && red <= 1.0);
	_Color.r = red;
}

double solid_color_pattern_builder::get_green() {
	return _Color.g;
}

void solid_color_pattern_builder::set_green(double green) {
	assert(green >= 0.0 && green <= 1.0);
	_Color.g = green;
}

double solid_color_pattern_builder::get_blue() {
	return _Color.b;
}

void solid_color_pattern_builder::set_blue(double blue) {
	assert(blue >= 0.0 && blue <= 1.0);
	_Color.b = blue;
}

double solid_color_pattern_builder::get_alpha() {
	return _Color.a;
}

void solid_color_pattern_builder::set_alpha(double alpha) {
	assert(alpha >= 0.0 && alpha <= 1.0);
	_Color.a = alpha;
}
