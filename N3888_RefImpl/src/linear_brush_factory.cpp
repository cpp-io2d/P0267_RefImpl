#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

linear_brush_factory::linear_brush_factory() noexcept
	: _Brush_type(brush_type::linear)
	, _Point0()
	, _Point1()
	, _Color_stops() {
}

linear_brush_factory::linear_brush_factory(linear_brush_factory&& other) noexcept
	: _Brush_type()
	, _Point0()
	, _Point1()
	, _Color_stops() {
	_Brush_type = move(other._Brush_type);
	_Point0 = move(other._Point0);
	_Point1 = move(other._Point1);
	_Color_stops = move(other._Color_stops);
}

linear_brush_factory& linear_brush_factory::operator=(linear_brush_factory&& other) noexcept {
	if (this != &other) {
		_Brush_type = move(other._Brush_type);
		_Point0 = move(other._Point0);
		_Point1 = move(other._Point1);
		_Color_stops = move(other._Color_stops);
	}
	return *this;
}

linear_brush_factory::linear_brush_factory(const point& pt0, const point& pt1) noexcept
: _Brush_type(brush_type::linear)
, _Point0(pt0)
, _Point1(pt1)
, _Color_stops() {
}

void linear_brush_factory::add_color_stop_rgba(double offset, const rgba_color& color) {
	assert(offset >= 0.0 && offset <= 1.0);
	assert(color.r() >= 0.0 && color.r() <= 1.0);
	assert(color.g() >= 0.0 && color.g() <= 1.0);
	assert(color.b() >= 0.0 && color.b() <= 1.0);
	assert(color.a() >= 0.0 && color.a() <= 1.0);
	_Color_stops.push_back(make_tuple(offset, color));
}

void linear_brush_factory::add_color_stop_rgba(double offset, const rgba_color& color, error_code& ec) noexcept {
	assert(offset >= 0.0 && offset <= 1.0);
	assert(color.r() >= 0.0 && color.r() <= 1.0);
	assert(color.g() >= 0.0 && color.g() <= 1.0);
	assert(color.b() >= 0.0 && color.b() <= 1.0);
	assert(color.a() >= 0.0 && color.a() <= 1.0);
	try {
		_Color_stops.push_back(make_tuple(offset, color));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	ec.clear();
}

void linear_brush_factory::color_stop_rgba(unsigned int index, double offset, const rgba_color& color) {
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

void linear_brush_factory::color_stop_rgba(unsigned int index, double offset, const rgba_color& color, error_code& ec) noexcept {
	assert(offset >= 0.0 && offset <= 1.0);
	assert(color.r() >= 0.0 && color.r() <= 1.0);
	assert(color.g() >= 0.0 && color.g() <= 1.0);
	assert(color.b() >= 0.0 && color.b() <= 1.0);
	assert(color.a() >= 0.0 && color.a() <= 1.0);

	if (index >= _Color_stops.size()) {
		ec = make_error_code(CAIRO_STATUS_INVALID_INDEX);
	}

	try {
		_Color_stops[index] = make_tuple(offset, color);
	}
	catch (const out_of_range&) {
		ec = make_error_code(CAIRO_STATUS_INVALID_INDEX);
		return;
	}
	ec.clear();
}

void linear_brush_factory::linear_points(const point& pt0, const point& pt1) noexcept {
	_Point0 = pt0;
	_Point1 = pt1;
}

int linear_brush_factory::color_stop_count() const noexcept {
	return static_cast<int>(_Color_stops.size());
}

tuple<double, rgba_color> linear_brush_factory::color_stop_rgba(unsigned int index) const {
	if (index >= _Color_stops.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}

	return _Color_stops.at(index);
}

tuple<double, rgba_color> linear_brush_factory::color_stop_rgba(unsigned int index, error_code& ec) const noexcept {
	if (index >= _Color_stops.size()) {
		ec = make_error_code(CAIRO_STATUS_INVALID_INDEX);
		return make_tuple(0.0, rgba_color::transparent_black());
	}

	try {
		auto stop = _Color_stops.at(index);
		ec.clear();
		return stop;
	}
	catch(const out_of_range&) {
		ec = make_error_code(CAIRO_STATUS_INVALID_INDEX);
		return make_tuple(0.0, rgba_color::transparent_black());
	}
}

tuple<point, point> linear_brush_factory::linear_points() const noexcept {
	return make_tuple(_Point0, _Point1);
}
