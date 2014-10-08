#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

radial_pattern_builder::radial_pattern_builder(radial_pattern_builder&& other)
: _Pattern_type(move(other._Pattern_type))
, _Extend(move(other._Extend))
, _Filter(move(other._Filter))
, _Matrix(move(other._Matrix))
, _Center0(move(other._Center0))
, _Radius0(move(other._Radius0))
, _Center1(move(other._Center1))
, _Radius1(move(other._Radius1))
, _Color_stops(move(other._Color_stops)) {
}

radial_pattern_builder& radial_pattern_builder::operator=(radial_pattern_builder&& other) {
	if (this != &other) {
		_Pattern_type = move(other._Pattern_type);
		_Extend = move(other._Extend);
		_Filter = move(other._Filter);
		_Matrix = move(other._Matrix);
		_Center0 = move(other._Center0);
		_Radius0 = move(other._Radius0);
		_Center1 = move(other._Center1);
		_Radius1 = move(other._Radius1);
		_Color_stops = move(other._Color_stops);
	}
	return *this;
}

radial_pattern_builder::radial_pattern_builder(const point& center0, double radius0, const point& center1, double radius1)
: _Pattern_type(pattern_type::radial)
, _Extend(extend::default_extend)
, _Filter(filter::default_filter)
, _Matrix(matrix_2d::init_identity())
, _Center0(center0)
, _Radius0(radius0)
, _Center1(center1)
, _Radius1(radius1)
, _Color_stops() {
}

pattern radial_pattern_builder::get_pattern() {
	unique_ptr<cairo_pattern_t, function<void(cairo_pattern_t*)>> pat(cairo_pattern_create_radial(_Center0.x, _Center0.y, _Radius0, _Center1.x, _Center1.y, _Radius1), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));

	cairo_pattern_set_extend(pat.get(), _Extend_to_cairo_extend_t(_Extend));
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));
	cairo_pattern_set_filter(pat.get(), _Filter_to_cairo_filter_t(_Filter));
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));
	cairo_matrix_t mtrx{ _Matrix.xx, _Matrix.yx, _Matrix.xy, _Matrix.yy, _Matrix.x0, _Matrix.y0 };
	cairo_pattern_set_matrix(pat.get(), &mtrx);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));
	for (const auto& stop : _Color_stops) {
		cairo_pattern_add_color_stop_rgba(pat.get(), get<0>(stop), get<1>(stop).r, get<1>(stop).g, get<1>(stop).b, get<1>(stop).a);
	}
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));

	auto pttn = pattern(pat.get());
	pat.release();
	return pttn;
}

void radial_pattern_builder::set_extend(extend e) {
	_Extend = e;
}

extend radial_pattern_builder::get_extend() {
	return _Extend;
}

void radial_pattern_builder::set_filter(filter f) {
	_Filter = f;
}

filter radial_pattern_builder::get_filter() {
	return _Filter;
}

void radial_pattern_builder::set_matrix(const matrix_2d& m) {
	_Matrix = m;
}


matrix_2d radial_pattern_builder::get_matrix() {
	return _Matrix;
}

void radial_pattern_builder::add_color_stop_rgba(double offset, const rgba_color& color) {
	assert(offset >= 0.0 && offset <= 1.0);
	assert(color.r >= 0.0 && color.r <= 1.0);
	assert(color.g >= 0.0 && color.g <= 1.0);
	assert(color.b >= 0.0 && color.b <= 1.0);
	assert(color.a >= 0.0 && color.a <= 1.0);
	_Color_stops.push_back(make_tuple(offset, color));
}

int radial_pattern_builder::get_color_stop_count() {
	return static_cast<int>(_Color_stops.size());
}

void radial_pattern_builder::get_color_stop_rgba(unsigned int index, double& offset, rgba_color& color) {
	if (index >= _Color_stops.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}

	const auto& stop = _Color_stops.at(index);
	offset = get<0>(stop);
	color = get<1>(stop);
}

void radial_pattern_builder::set_color_stop_rgba(unsigned int index, double offset, const rgba_color& color) {
	assert(offset >= 0.0 && offset <= 1.0);
	assert(color.r >= 0.0 && color.r <= 1.0);
	assert(color.g >= 0.0 && color.g <= 1.0);
	assert(color.b >= 0.0 && color.b <= 1.0);
	assert(color.a >= 0.0 && color.a <= 1.0);

	if (index >= _Color_stops.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}

	_Color_stops[index] = make_tuple(offset, color);
}

void radial_pattern_builder::get_radial_circles(point& center0, double& radius0, point& center1, double& radius1) {
	center0 = _Center0;
	radius0 = _Radius0;
	center1 = _Center1;
	radius1 = _Radius1;
}

void radial_pattern_builder::set_radial_circles(const point& center0, double radius0, const point& center1, double radius1) {
	_Center0 = center0;
	_Radius0 = radius0;
	_Center1 = center1;
	_Radius1 = radius1;
}
