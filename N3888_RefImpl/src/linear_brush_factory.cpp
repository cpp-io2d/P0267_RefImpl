#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

linear_brush_factory::linear_brush_factory() noexcept
	: _Begin_point()
	, _End_point()
	, _Color_stops() {
}

linear_brush_factory::linear_brush_factory(linear_brush_factory&& other) noexcept
	: _Begin_point()
	, _End_point()
	, _Color_stops() {
	_Begin_point = move(other._Begin_point);
	_End_point = move(other._End_point);
	_Color_stops = move(other._Color_stops);
}

linear_brush_factory& linear_brush_factory::operator=(linear_brush_factory&& other) noexcept {
	if (this != &other) {
		_Begin_point = move(other._Begin_point);
		_End_point = move(other._End_point);
		_Color_stops = move(other._Color_stops);
	}
	return *this;
}

linear_brush_factory::linear_brush_factory(const vector_2d& pt0, const vector_2d& pt1) noexcept
	: _Begin_point(pt0)
	, _End_point(pt1)
	, _Color_stops() {
}

void linear_brush_factory::add_color_stop(double offset, const rgba_color& color) {
	assert(offset >= 0.0 && offset <= 1.0);
	assert(color.r() >= 0.0 && color.r() <= 1.0);
	assert(color.g() >= 0.0 && color.g() <= 1.0);
	assert(color.b() >= 0.0 && color.b() <= 1.0);
	assert(color.a() >= 0.0 && color.a() <= 1.0);
	_Color_stops.push_back(make_tuple(offset, color));
}

void linear_brush_factory::add_color_stop(double offset, const rgba_color& color, error_code& ec) noexcept {
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

void linear_brush_factory::color_stop(linear_brush_factory::size_type index, double offset, const rgba_color& color) {
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

void linear_brush_factory::color_stop(linear_brush_factory::size_type index, double offset, const rgba_color& color, error_code& ec) noexcept {
	assert(offset >= 0.0 && offset <= 1.0);
	assert(color.r() >= 0.0 && color.r() <= 1.0);
	assert(color.g() >= 0.0 && color.g() <= 1.0);
	assert(color.b() >= 0.0 && color.b() <= 1.0);
	assert(color.a() >= 0.0 && color.a() <= 1.0);

	if (index >= _Color_stops.size()) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_INDEX);
		return;
	}

	try {
		_Color_stops[index] = make_tuple(offset, color);
	}
	catch (const out_of_range&) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_INDEX);
		return;
	}
	ec.clear();
}

void linear_brush_factory::remove_color_stop(linear_brush_factory::size_type index) {
	auto size = _Color_stops.size();
	if (index >= size) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}

	_Color_stops.erase(_Color_stops.begin() + index);
	assert(_Color_stops.size() + 1 == size);
}

void linear_brush_factory::remove_color_stop(linear_brush_factory::size_type index, error_code& ec) noexcept {
	auto size = _Color_stops.size();
	if (index >= size) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_INDEX);
		return;
	}

	_Color_stops.erase(_Color_stops.begin() + index);
	assert(_Color_stops.size() + 1 == size);
	ec.clear();
}

void linear_brush_factory::begin_point(const vector_2d& value) noexcept{
	_Begin_point = value;
}

void linear_brush_factory::end_point(const vector_2d& value) noexcept{
	_End_point = value;
}

linear_brush_factory::size_type linear_brush_factory::color_stop_count() const noexcept {
	return _Color_stops.size();
}

tuple<double, rgba_color> linear_brush_factory::color_stop(linear_brush_factory::size_type index) const {
	if (index >= _Color_stops.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}

	return _Color_stops.at(index);
}

tuple<double, rgba_color> linear_brush_factory::color_stop(linear_brush_factory::size_type index, error_code& ec) const noexcept {
	if (index >= _Color_stops.size()) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_INDEX);
		return make_tuple(0.0, rgba_color::transparent_black());
	}

	try {
		auto stop = _Color_stops.at(index);
		ec.clear();
		return stop;
	}
	catch(const out_of_range&) {
		assert(false && "Unexpected invalid index; possible data race?");
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_INDEX);
		return make_tuple(0.0, rgba_color::transparent_black());
	}
}

vector<tuple<double, rgba_color>>& linear_brush_factory::color_stops() noexcept{
	return _Color_stops;
}

const vector<tuple<double, rgba_color>>& linear_brush_factory::color_stops() const noexcept{
	return _Color_stops;
}

vector_2d linear_brush_factory::begin_point() const noexcept{
	return _Begin_point;
}

vector_2d linear_brush_factory::end_point() const noexcept{
	return _End_point;
}
