#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

linear_pattern_builder::linear_pattern_builder()
	: _Lock()
	, _Pattern_type(pattern_type::linear)
	, _Extend(extend::default_extend)
	, _Filter(filter::default_filter)
	, _Matrix(matrix_2d::init_identity())
	, _Point0()
	, _Point1()
	, _Color_stops() {
}

linear_pattern_builder::linear_pattern_builder(const linear_pattern_builder& other)
	: _Pattern_type()
	, _Extend()
	, _Filter()
	, _Matrix()
	, _Point0()
	, _Point1()
	, _Color_stops() {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Pattern_type = other._Pattern_type;
	_Extend = other._Extend;
	_Filter = other._Filter;
	_Matrix = other._Matrix;
	_Point0 = other._Point0;
	_Point1 = other._Point1;
	_Color_stops = other._Color_stops;
}

linear_pattern_builder& linear_pattern_builder::operator=(const linear_pattern_builder& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Pattern_type = other._Pattern_type;
		_Extend = other._Extend;
		_Filter = other._Filter;
		_Matrix = other._Matrix;
		_Point0 = other._Point0;
		_Point1 = other._Point1;
		_Color_stops = other._Color_stops;
	}
	return *this;
}

linear_pattern_builder::linear_pattern_builder(linear_pattern_builder&& other)
	: _Pattern_type()
	, _Extend()
	, _Filter()
	, _Matrix()
	, _Point0()
	, _Point1()
	, _Color_stops() {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Pattern_type = move(other._Pattern_type);
	_Extend = move(other._Extend);
	_Filter = move(other._Filter);
	_Matrix = move(other._Matrix);
	_Point0 = move(other._Point0);
	_Point1 = move(other._Point1);
	_Color_stops = move(other._Color_stops);
}

linear_pattern_builder& linear_pattern_builder::operator=(linear_pattern_builder&& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
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

pattern linear_pattern_builder::get_pattern() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	unique_ptr<cairo_pattern_t, function<void(cairo_pattern_t*)>> pat(cairo_pattern_create_linear(_Point0.x, _Point0.y, _Point1.x, _Point1.y), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));

	cairo_pattern_set_extend(pat.get(), _Extend_to_cairo_extend_t(_Extend));
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));
	cairo_pattern_set_filter(pat.get(), _Filter_to_cairo_filter_t(_Filter));
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));
	cairo_matrix_t mtrx{ _Matrix.m00, _Matrix.m01, _Matrix.m10, _Matrix.m11, _Matrix.m20, _Matrix.m21 };
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
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Extend = e;
}

extend linear_pattern_builder::get_extend() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Extend;
}

void linear_pattern_builder::set_filter(filter f) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Filter = f;
}

filter linear_pattern_builder::get_filter() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Filter;
}

void linear_pattern_builder::set_matrix(const matrix_2d& m) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Matrix = m;
}


matrix_2d linear_pattern_builder::get_matrix() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Matrix;
}

void linear_pattern_builder::add_color_stop_rgba(double offset, const rgba_color& color) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	assert(offset >= 0.0 && offset <= 1.0);
	assert(color.r >= 0.0 && color.r <= 1.0);
	assert(color.g >= 0.0 && color.g <= 1.0);
	assert(color.b >= 0.0 && color.b <= 1.0);
	assert(color.a >= 0.0 && color.a <= 1.0);
	_Color_stops.push_back(make_tuple(offset, color));
}

int linear_pattern_builder::get_color_stop_count() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return static_cast<int>(_Color_stops.size());
}

void linear_pattern_builder::get_color_stop_rgba(unsigned int index, double& offset, rgba_color& color) const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (index >= _Color_stops.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}

	const auto& stop = _Color_stops.at(index);
	offset = get<0>(stop);
	color = get<1>(stop);
}

void linear_pattern_builder::set_color_stop_rgba(unsigned int index, double offset, const rgba_color& color) {
	lock_guard<decltype(_Lock)> lg(_Lock);
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

void linear_pattern_builder::get_linear_points(point& pt0, point& pt1) const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	pt0 = _Point0;
	pt1 = _Point1;
}

void linear_pattern_builder::set_linear_points(const point& pt0, const point& pt1) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Point0 = pt0;
	_Point1 = pt1;
}
