#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

linear_pattern_builder::linear_pattern_builder(linear_pattern_builder&& other)
: _Pattern_type(move(other._Pattern_type))
, _Extend(move(other._Extend))
, _Filter(move(other._Filter))
, _Matrix(move(other._Matrix))
, _Point0(move(other._Point0))
, _Point1(move(other._Point1))
, _Color_stops(move(other._Color_stops)) {
}

linear_pattern_builder& linear_pattern_builder::operator=(linear_pattern_builder&& other) {
	if (this != &other) {
		_Pattern_type = move(other._Pattern_type);
		_Extend = move(other._Extend);
		_Filter = move(other._Filter);
		_Matrix = move(other._Matrix);
		_Point0 = move(other._Point0);
		_Point1 = move(other._Point1);
		_Color_stops = move(other._Color_stops);
	}
	return *this;
}

linear_pattern_builder::linear_pattern_builder(const point& pt0, const point& pt1)
: _Pattern_type(pattern_type::linear)
, _Extend(extend::default_extend)
, _Filter(filter::default_filter)
, _Matrix(matrix_2d::init_identity())
, _Point0(pt0)
, _Point1(pt1)
, _Color_stops() {
}

pattern linear_pattern_builder::get_pattern() {
	unique_ptr<cairo_pattern_t, function<void(cairo_pattern_t*)>> pat(cairo_pattern_create_linear(_Point0.x, _Point0.y, _Point1.x, _Point1.y), &cairo_pattern_destroy);
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

void linear_pattern_builder::set_extend(extend e) {
	_Extend = e;
}

extend linear_pattern_builder::get_extend() {
	return _Extend;
}

void linear_pattern_builder::set_filter(filter f) {
	_Filter = f;
}

filter linear_pattern_builder::get_filter() {
	return _Filter;
}

void linear_pattern_builder::set_matrix(const matrix_2d& m) {
	_Matrix = m;
}


matrix_2d linear_pattern_builder::get_matrix() {
	return _Matrix;
}

void linear_pattern_builder::add_color_stop_rgba(double offset, const rgba_color& color) {
	assert(offset >= 0.0 && offset <= 1.0);
	assert(color.r >= 0.0 && color.r <= 1.0);
	assert(color.g >= 0.0 && color.g <= 1.0);
	assert(color.b >= 0.0 && color.b <= 1.0);
	assert(color.a >= 0.0 && color.a <= 1.0);
	_Color_stops.push_back(make_tuple(offset, color));
}

int linear_pattern_builder::get_color_stop_count() {
	return static_cast<int>(_Color_stops.size());
}

void linear_pattern_builder::get_color_stop_rgba(unsigned int index, double& offset, rgba_color& color) {
	if (index >= _Color_stops.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}

	const auto& stop = _Color_stops.at(index);
	offset = get<0>(stop);
	color = get<1>(stop);
}

void linear_pattern_builder::set_color_stop_rgba(unsigned int index, double offset, const rgba_color& color) {
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

void linear_pattern_builder::get_linear_points(point& pt0, point& pt1) {
	pt0 = _Point0;
	pt1 = _Point1;
}

void linear_pattern_builder::set_linear_points(const point& pt0, const point& pt1) {
	_Point0 = pt0;
	_Point1 = pt1;
}
