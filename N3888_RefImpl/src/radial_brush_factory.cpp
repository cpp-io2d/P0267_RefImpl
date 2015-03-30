#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

radial_brush_factory::radial_brush_factory() noexcept
	: _Center0()
	, _Radius0()
	, _Center1()
	, _Radius1() {
}

radial_brush_factory::radial_brush_factory(radial_brush_factory&& other) noexcept
	: _Center0()
	, _Radius0()
	, _Center1()
	, _Radius1()
	, _Color_stops() {
	_Center0 = move(other._Center0);
	_Radius0 = move(other._Radius0);
	_Center1 = move(other._Center1);
	_Radius1 = move(other._Radius1);
	_Color_stops = move(other._Color_stops);
}

radial_brush_factory& radial_brush_factory::operator=(radial_brush_factory&& other) noexcept {
	if (this != &other) {
		_Center0 = move(other._Center0);
		_Radius0 = move(other._Radius0);
		_Center1 = move(other._Center1);
		_Radius1 = move(other._Radius1);
		_Color_stops = move(other._Color_stops);
	}
	return *this;
}

radial_brush_factory::radial_brush_factory(const point& center0, double radius0, const point& center1, double radius1) noexcept
	: _Center0(center0)
	, _Radius0(radius0)
	, _Center1(center1)
	, _Radius1(radius1)
	, _Color_stops() {
}

void radial_brush_factory::add_color_stop_rgba(double offset, const rgba_color& color) {
	assert(offset >= 0.0 && offset <= 1.0);
	assert(color.r() >= 0.0 && color.r() <= 1.0);
	assert(color.g() >= 0.0 && color.g() <= 1.0);
	assert(color.b() >= 0.0 && color.b() <= 1.0);
	assert(color.a() >= 0.0 && color.a() <= 1.0);
	_Color_stops.push_back(make_tuple(offset, color));
}

void radial_brush_factory::add_color_stop_rgba(double offset, const rgba_color& color, error_code& ec) noexcept {
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

void radial_brush_factory::color_stop_rgba(unsigned int index, double offset, const rgba_color& color) {
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

void radial_brush_factory::color_stop_rgba(unsigned int index, double offset, const rgba_color& color, error_code& ec) noexcept {
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

void radial_brush_factory::radial_circles(const point& center0, double radius0, const point& center1, double radius1) noexcept {
	_Center0 = center0;
	_Radius0 = radius0;
	_Center1 = center1;
	_Radius1 = radius1;
}

int radial_brush_factory::color_stop_count() const noexcept {
	return static_cast<int>(_Color_stops.size());
}

tuple<double, rgba_color> radial_brush_factory::color_stop_rgba(unsigned int index) const {
	if (index >= _Color_stops.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}

	return _Color_stops.at(index);
}

tuple<double, rgba_color> radial_brush_factory::color_stop_rgba(unsigned int index, error_code& ec) const noexcept {
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

tuple<point, double, point, double> radial_brush_factory::radial_circles() const noexcept {
	return make_tuple(_Center0, _Radius0, _Center1, _Radius1);
}
