#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

radial_pattern_factory::radial_pattern_factory()
	: _Lock()
	, _Pattern_type(pattern_type::radial)
	, _Center0()
	, _Radius0()
	, _Center1()
	, _Radius1() {
}

radial_pattern_factory::radial_pattern_factory(const radial_pattern_factory& other)
	: _Lock()
	, _Pattern_type()
	, _Center0()
	, _Radius0()
	, _Center1()
	, _Radius1()
	, _Color_stops() {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Pattern_type = other._Pattern_type;
	_Center0 = other._Center0;
	_Radius0 = other._Radius0;
	_Center1 = other._Center1;
	_Radius1 = other._Radius1;
	_Color_stops = other._Color_stops;
}

radial_pattern_factory& radial_pattern_factory::operator=(const radial_pattern_factory& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Pattern_type = other._Pattern_type;
		_Center0 = other._Center0;
		_Radius0 = other._Radius0;
		_Center1 = other._Center1;
		_Radius1 = other._Radius1;
		_Color_stops = other._Color_stops;
	}
	return *this;
}

radial_pattern_factory::radial_pattern_factory(radial_pattern_factory&& other)
	: _Lock()
	, _Pattern_type()
	, _Center0()
	, _Radius0()
	, _Center1()
	, _Radius1()
	, _Color_stops() {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Pattern_type = move(other._Pattern_type);
	_Center0 = move(other._Center0);
	_Radius0 = move(other._Radius0);
	_Center1 = move(other._Center1);
	_Radius1 = move(other._Radius1);
	_Color_stops = move(other._Color_stops);
}

radial_pattern_factory& radial_pattern_factory::operator=(radial_pattern_factory&& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Pattern_type = move(other._Pattern_type);
		_Center0 = move(other._Center0);
		_Radius0 = move(other._Radius0);
		_Center1 = move(other._Center1);
		_Radius1 = move(other._Radius1);
		_Color_stops = move(other._Color_stops);
	}
	return *this;
}

radial_pattern_factory::radial_pattern_factory(const point& center0, double radius0, const point& center1, double radius1)
: _Lock()
, _Pattern_type(pattern_type::radial)
, _Center0(center0)
, _Radius0(radius0)
, _Center1(center1)
, _Radius1(radius1)
, _Color_stops() {
}

void radial_pattern_factory::add_color_stop_rgba(double offset, const rgba_color& color) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	assert(offset >= 0.0 && offset <= 1.0);
	assert(color.r() >= 0.0 && color.r() <= 1.0);
	assert(color.g() >= 0.0 && color.g() <= 1.0);
	assert(color.b() >= 0.0 && color.b() <= 1.0);
	assert(color.a() >= 0.0 && color.a() <= 1.0);
	_Color_stops.push_back(make_tuple(offset, color));
}

int radial_pattern_factory::color_stop_count() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return static_cast<int>(_Color_stops.size());
}

void radial_pattern_factory::color_stop_rgba(unsigned int index, double& offset, rgba_color& color) const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (index >= _Color_stops.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}

	const auto& stop = _Color_stops.at(index);
	offset = get<0>(stop);
	color = get<1>(stop);
}

void radial_pattern_factory::color_stop_rgba(unsigned int index, double offset, const rgba_color& color) {
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

void radial_pattern_factory::radial_circles(point& center0, double& radius0, point& center1, double& radius1) const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	center0 = _Center0;
	radius0 = _Radius0;
	center1 = _Center1;
	radius1 = _Radius1;
}

void radial_pattern_factory::radial_circles(const point& center0, double radius0, const point& center1, double radius1) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Center0 = center0;
	_Radius0 = radius0;
	_Center1 = center1;
	_Radius1 = radius1;
}
