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
, _Red(move(other._Red))
, _Green(move(other._Green))
, _Blue(move(other._Blue))
, _Alpha(move(other._Alpha)) {
}

solid_color_pattern_builder& solid_color_pattern_builder::operator=(solid_color_pattern_builder&& other) {
	if (this != &other) {
		_Pattern_type = move(other._Pattern_type);
		_Extend = move(other._Extend);
		_Filter = move(other._Filter);
		_Matrix = move(other._Matrix);
		_Red = move(other._Red);
		_Green = move(other._Green);
		_Blue = move(other._Blue);
		_Alpha = move(other._Alpha);
	}
	return *this;
}

solid_color_pattern_builder::solid_color_pattern_builder(double red, double green, double blue)
: _Pattern_type(pattern_type::solid_color)
, _Extend(extend::default_extend)
, _Filter(filter::default_filter)
, _Matrix(matrix::init_identity())
, _Red(red)
, _Green(green)
, _Blue(blue)
, _Alpha(1.0) {
}

solid_color_pattern_builder::solid_color_pattern_builder(double red, double green, double blue, double alpha)
: _Pattern_type(pattern_type::solid_color)
, _Extend(extend::default_extend)
, _Filter(filter::default_filter)
, _Matrix(matrix::init_identity())
, _Red(red)
, _Green(green)
, _Blue(blue)
, _Alpha(alpha) {
}

pattern solid_color_pattern_builder::get_pattern() {
	auto pat = cairo_pattern_create_rgba(_Red, _Green, _Blue, _Alpha);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));

	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(_Extend));
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(_Filter));
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));
	cairo_matrix_t mtrx{ _Matrix.xx, _Matrix.yx, _Matrix.xy, _Matrix.yy, _Matrix.x0, _Matrix.y0 };
	cairo_pattern_set_matrix(pat, &mtrx);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));

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

void solid_color_pattern_builder::get_rgba(double& red, double& green, double& blue, double& alpha) {
	red = _Red;
	green = _Green;
	blue = _Blue;
	alpha = _Alpha;
}
