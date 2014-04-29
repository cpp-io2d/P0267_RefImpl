#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

region::region() {
	_Region = shared_ptr<cairo_region_t>(cairo_region_create(), &cairo_region_destroy);
}

region::region(const region& other) {
	_Region = other._Region;
}

region& region::operator=(const region& other) {
	if (this != &other) {
		_Region = other._Region;
	}
	return *this;
}

region::region(region&& other) {
	_Region = move(other._Region);
	other._Region = nullptr;
}

region& region::operator=(region&& other) {
	if (this != &other) {
		_Region = move(other._Region);
		other._Region = nullptr;
	}
	return *this;
}

region::region(region::native_handle_type nh) {
	_Region = shared_ptr<cairo_region_t>(nh, &cairo_region_destroy);
}

region::region(const rectangle& rect) {
    cairo_rectangle_int_t cRectInt{ _Double_to_int(rect.x), _Double_to_int(rect.y), _Double_to_int(rect.width), _Double_to_int(rect.height) };
	_Region = shared_ptr<cairo_region_t>(cairo_region_create_rectangle(&cRectInt), &cairo_region_destroy);
}

region::region(const vector<rectangle>& rectangles) {
	vector<cairo_rectangle_int_t> vec;
	for (const auto& rect : rectangles) {
        vec.push_back({ _Double_to_int(rect.x), _Double_to_int(rect.y), _Double_to_int(rect.width), _Double_to_int(rect.height) });
	}
	_Region = shared_ptr<cairo_region_t>(cairo_region_create_rectangles(vec.data(), static_cast<int>(vec.size())), &cairo_region_destroy);
}

region region::copy() {
	return region(cairo_region_copy(_Region.get()));
}

status region::status() {
	return _Cairo_status_t_to_status(cairo_region_status(_Region.get()));
}

void region::get_extents(rectangle& extents) {
	cairo_rectangle_int_t cr;
	cairo_region_get_extents(_Region.get(), &cr);
	rectangle result = { static_cast<double>(cr.x), static_cast<double>(cr.y), static_cast<double>(cr.width), static_cast<double>(cr.height) };
	extents = result;
}

int region::num_rectangles() {
	return cairo_region_num_rectangles(_Region.get());
}

void region::get_rectangle(int nth, rectangle& rectangle) {
	cairo_rectangle_int_t cr;
	cairo_region_get_rectangle(_Region.get(), nth, &cr);
    rectangle = { static_cast<double>(cr.x), static_cast<double>(cr.y), static_cast<double>(cr.width), static_cast<double>(cr.height) };
}

bool region::is_empty() {
	return cairo_region_is_empty(_Region.get()) != 0;
}

bool region::contains_point(int x, int y) {
	return cairo_region_contains_point(_Region.get(), x, y) != 0;
}

region_overlap region::contains_rectangle(const rectangle& rect) {
    cairo_rectangle_int_t cr = { _Double_to_int(rect.x), _Double_to_int(rect.y), _Double_to_int(rect.width), _Double_to_int(rect.height) };
	return _Cairo_region_overlap_t_to_region_overlap(cairo_region_contains_rectangle(_Region.get(), &cr));
}

bool region::equal(const region& other) {
	return cairo_region_equal(_Region.get(), other._Region.get()) != 0;
}

void region::translate(int dx, int dy) {
	cairo_region_translate(_Region.get(), dx, dy);
}

void region::intersect_region(const region& other) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_region_intersect(_Region.get(), other._Region.get())));
}

void region::intersect_rectangle(const rectangle& rect) {
    cairo_rectangle_int_t cr = { _Double_to_int(rect.x), _Double_to_int(rect.y), _Double_to_int(rect.width), _Double_to_int(rect.height) };
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_region_intersect_rectangle(_Region.get(), &cr)));
}

void region::subtract_region(const region& other) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_region_subtract(_Region.get(), other._Region.get())));
}

void region::subtract_rectangle(const rectangle& rect) {
    cairo_rectangle_int_t cr = { _Double_to_int(rect.x), _Double_to_int(rect.y), _Double_to_int(rect.width), _Double_to_int(rect.height) };
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_region_subtract_rectangle(_Region.get(), &cr)));
}

void region::union_region(const region& other) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_region_union(_Region.get(), other._Region.get())));
}

void region::union_rectangle(const rectangle& rect) {
    cairo_rectangle_int_t cr = { _Double_to_int(rect.x), _Double_to_int(rect.y), _Double_to_int(rect.width), _Double_to_int(rect.height) };
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_region_union_rectangle(_Region.get(), &cr)));
}

void region::xor_region(const region& other) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_region_xor(_Region.get(), other._Region.get())));
}

void region::xor_rectangle(const rectangle& rect) {
    cairo_rectangle_int_t cr = { _Double_to_int(rect.x), _Double_to_int(rect.y), _Double_to_int(rect.width), _Double_to_int(rect.height) };
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_region_xor_rectangle(_Region.get(), &cr)));
}
