#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;
using namespace std::placeholders;

cairo_surface_t* raster_source_pattern_builder::_Cairo_acquire(cairo_pattern_t*, void* this_ptr, cairo_surface_t* target, const cairo_rectangle_int_t* extents) {
	auto rsp = static_cast<raster_source_pattern_builder*>(this_ptr);
	rectangle ri_extents{ };
	if (extents == nullptr) {
		ri_extents.x = 0.0;
		ri_extents.y = 0.0;
        ri_extents.width = static_cast<double>(rsp->_Width);
        ri_extents.height = static_cast<double>(rsp->_Height);
	}
	else {
        ri_extents.x = static_cast<double>(extents->x);
        ri_extents.y = static_cast<double>(extents->y);
        ri_extents.width = static_cast<double>(extents->width);
        ri_extents.height = static_cast<double>(extents->height);
	}
	auto acqTarget = surface(target);
	// Increment the reference count of target to avoid its destruction when acqTarget is destroyed.
	cairo_surface_reference(target);
	auto& acquire_fn = *rsp->_Acquire_fn;
	auto result = acquire_fn(rsp->_User_callback_data, acqTarget, ri_extents);
	// Increment the reference count of result to avoid its destruction when we return it.
	cairo_surface_reference(result.native_handle());
	return result.native_handle();
}

void raster_source_pattern_builder::_Cairo_release(cairo_pattern_t*, void* this_ptr, cairo_surface_t* surface) {
	auto rsp = static_cast<raster_source_pattern_builder*>(this_ptr);
	if (*rsp->_Release_fn != nullptr) {
		// If the user has an explicit release function, increment the reference count since it's the user's responsibility to destroy the surface (e.g. by calling cairo_surface_destroy(surface.native_handle()); ).
		cairo_surface_reference(surface);
		auto relSurface = experimental::drawing::surface(surface);
		auto& release_fn = *rsp->_Release_fn;
		release_fn(rsp->_User_callback_data, relSurface);
	}
	else {
		// If there's no release function, just destroy the surface and proceed.
		cairo_surface_destroy(surface);
	}
}

raster_source_pattern_builder::raster_source_pattern_builder(raster_source_pattern_builder&& other)
: _Pattern_type(move(other._Pattern_type))
, _Extend(move(other._Extend))
, _Filter(move(other._Filter))
, _Matrix(move(other._Matrix))
, _User_callback_data(move(other._User_callback_data))
, _Width(move(other._Width))
, _Height(move(other._Height))
, _Content(move(other._Content))
, _Acquire_fn(move(other._Acquire_fn))
, _Release_fn(move(other._Release_fn)) {
}

raster_source_pattern_builder& raster_source_pattern_builder::operator=(raster_source_pattern_builder&& other) {
	if (this != &other) {
        _Pattern_type = move(other._Pattern_type);
        _Extend = move(other._Extend);
        _Filter = move(other._Filter);
        _Matrix = move(other._Matrix);
        _User_callback_data = move(other._User_callback_data);
		_Width = move(other._Width);
		_Height = move(other._Height);
        _Content = move(other._Content);
		_Acquire_fn = move(other._Acquire_fn);
		_Release_fn = move(other._Release_fn);
		other._User_callback_data = nullptr;
		other._Width = { };
		other._Height = { };
		other._Acquire_fn = nullptr;
		other._Release_fn = nullptr;
	}
	return *this;
}

raster_source_pattern_builder::raster_source_pattern_builder(void* user_data, content content, int width, int height)
: _Pattern_type(pattern_type::raster_source)
, _Extend(extend::default_extend)
, _Filter(filter::default_filter)
, _Matrix(matrix::init_identity())
, _User_callback_data(user_data)
, _Width(width)
, _Height(height)
, _Content(content)
, _Acquire_fn(new function<surface(void* callback_data, surface& target, const rectangle& extents)>)
, _Release_fn(new function<void(void* callback_data, surface& surface)>) {
}

pattern raster_source_pattern_builder::get_pattern() {
    auto pat = cairo_pattern_create_raster_source(_User_callback_data, _Content_to_cairo_content_t(_Content), _Width, _Height);
    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));

    cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(_Extend));
    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));
    cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(_Filter));
    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));
    cairo_matrix_t mtrx{ _Matrix.xx, _Matrix.yx, _Matrix.xy, _Matrix.yy, _Matrix.x0, _Matrix.y0 };
    cairo_pattern_set_matrix(pat, &mtrx);
    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));

    cairo_raster_source_pattern_set_acquire(pat, (_Acquire_fn == nullptr) ? nullptr : &raster_source_pattern_builder::_Cairo_acquire,
        &raster_source_pattern_builder::_Cairo_release
        );
    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));
    return pattern(pat);
}

void raster_source_pattern_builder::set_extend(extend e) {
    _Extend = e;
}

extend raster_source_pattern_builder::get_extend() {
    return _Extend;
}

void raster_source_pattern_builder::set_filter(filter f) {
    _Filter = f;
}

filter raster_source_pattern_builder::get_filter() {
    return _Filter;
}

void raster_source_pattern_builder::set_matrix(const matrix& m) {
    _Matrix = m;
}

matrix raster_source_pattern_builder::get_matrix() {
    return _Matrix;
}

void raster_source_pattern_builder::set_callback_data(void* data) {
	_User_callback_data = data;
}

void* raster_source_pattern_builder::get_callback_data() {
	return _User_callback_data;
}

void raster_source_pattern_builder::set_acquire(
	function<surface(void* callback_data, surface& target, const rectangle& extents)> acquire_fn,
	function<void(void* callback_data, surface& surface)> release_fn
	) {
	*_Acquire_fn = acquire_fn;
	*_Release_fn = release_fn;
}

void raster_source_pattern_builder::get_acquire(
	function<surface(void* callback_data, surface& target, const rectangle& extents)>& acquire_fn,
	function<void(void* callback_data, surface& surface)>& release_fn
	) {
	acquire_fn = *_Acquire_fn;
	release_fn = *_Release_fn;
}
