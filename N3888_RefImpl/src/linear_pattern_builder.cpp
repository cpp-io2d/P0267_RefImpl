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
, _Matrix(matrix::init_identity())
, _Point0(pt0)
, _Point1(pt1)
, _Color_stops() {
}

pattern linear_pattern_builder::get_pattern() {
    auto pat = cairo_pattern_create_linear(_Point0.x, _Point0.y, _Point1.x, _Point1.y);
    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));

    cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(_Extend));
    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));
    cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(_Filter));
    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));
    cairo_matrix_t mtrx{ _Matrix.xx, _Matrix.yx, _Matrix.xy, _Matrix.yy, _Matrix.x0, _Matrix.y0 };
    cairo_pattern_set_matrix(pat, &mtrx);
    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));
    for (const auto& stop : _Color_stops) {
        cairo_pattern_add_color_stop_rgba(pat, get<0>(stop), get<1>(stop), get<2>(stop), get<3>(stop), get<4>(stop));
    }
    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));

    return pattern(pat);
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

void linear_pattern_builder::set_matrix(const matrix& m) {
    _Matrix = m;
}

matrix linear_pattern_builder::get_matrix() {
    return _Matrix;
}

void linear_pattern_builder::add_color_stop_rgb(double offset, double red, double green, double blue) {
    assert(offset >= 0.0 && offset <= 1.0);
    _Color_stops.push_back(make_tuple(offset, red, green, blue, 1.0));
}

void linear_pattern_builder::add_color_stop_rgba(double offset, double red, double green, double blue, double alpha) {
    assert(offset >= 0.0 && offset <= 1.0);
    _Color_stops.push_back(make_tuple(offset, red, green, blue, alpha));
}

void linear_pattern_builder::get_color_stop_count(int& count) {
    count = static_cast<int>(_Color_stops.size());
}

void linear_pattern_builder::get_color_stop_rgba(int index, double& offset, double& red, double& green, double& blue, double& alpha) {
    const auto& stop = _Color_stops.at(index);
    offset = get<0>(stop);
    red = get<1>(stop);
    green = get<2>(stop);
    blue = get<3>(stop);
    alpha = get<4>(stop);
}

void linear_pattern_builder::get_linear_points(point& pt0, point& pt1) {
    pt0 = _Point0;
    pt1 = _Point1;
}
