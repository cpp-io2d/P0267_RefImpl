#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

linear_pattern_factory::linear_pattern_factory()
	: _Lock()
	, _Pattern_type(pattern_type::linear)
	, _Extend(extend::default_extend)
	, _Filter(filter::default_filter)
	, _Matrix(matrix_2d::init_identity())
	, _Point0()
	, _Point1()
	, _Color_stops() {
}

linear_pattern_factory::linear_pattern_factory(const linear_pattern_factory& other)
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

linear_pattern_factory& linear_pattern_factory::operator=(const linear_pattern_factory& other) {
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

linear_pattern_factory::linear_pattern_factory(linear_pattern_factory&& other)
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

linear_pattern_factory& linear_pattern_factory::operator=(linear_pattern_factory&& other) {
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

linear_pattern_factory::linear_pattern_factory(const point& pt0, const point& pt1)
: _Pattern_type(pattern_type::linear)
, _Extend(extend::default_extend)
, _Filter(filter::default_filter)
, _Matrix(matrix_2d::init_identity())
, _Point0(pt0)
, _Point1(pt1)
, _Color_stops() {
}

void linear_pattern_factory::set_extend(extend e) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Extend = e;
}

extend linear_pattern_factory::get_extend() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Extend;
}

void linear_pattern_factory::set_filter(filter f) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Filter = f;
}

filter linear_pattern_factory::get_filter() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Filter;
}

void linear_pattern_factory::set_matrix(const matrix_2d& m) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Matrix = m;
}


matrix_2d linear_pattern_factory::get_matrix() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Matrix;
}

void linear_pattern_factory::add_color_stop_rgba(double offset, const rgba_color& color) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	assert(offset >= 0.0 && offset <= 1.0);
	assert(color.r() >= 0.0 && color.r() <= 1.0);
	assert(color.g() >= 0.0 && color.g() <= 1.0);
	assert(color.b() >= 0.0 && color.b() <= 1.0);
	assert(color.a() >= 0.0 && color.a() <= 1.0);
	_Color_stops.push_back(make_tuple(offset, color));
}

int linear_pattern_factory::get_color_stop_count() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return static_cast<int>(_Color_stops.size());
}

void linear_pattern_factory::get_color_stop_rgba(unsigned int index, double& offset, rgba_color& color) const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (index >= _Color_stops.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}

	const auto& stop = _Color_stops.at(index);
	offset = get<0>(stop);
	color = get<1>(stop);
}

void linear_pattern_factory::set_color_stop_rgba(unsigned int index, double offset, const rgba_color& color) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	assert(offset >= 0.0 && offset <= 1.0);
	assert(color.r() >= 0.0 && color.r() <= 1.0);
	assert(color.g() >= 0.0 && color.g() <= 1.0);
	assert(color.b() >= 0.0 && color.b() <= 1.0);
	assert(color.a() >= 0.0 && color.a() <= 1.0);

	if (index >= _Color_stops.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}

	_Color_stops[index] = make_tuple(offset, color);
}

void linear_pattern_factory::get_linear_points(point& pt0, point& pt1) const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	pt0 = _Point0;
	pt1 = _Point1;
}

void linear_pattern_factory::set_linear_points(const point& pt0, const point& pt1) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Point0 = pt0;
	_Point1 = pt1;
}
