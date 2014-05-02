#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;
using namespace std::placeholders;

cairo_surface_t* raster_source_pattern::_Cairo_acquire(cairo_pattern_t*, void* this_ptr, cairo_surface_t* target, const cairo_rectangle_int_t* extents) {
	auto rsp = static_cast<raster_source_pattern*>(this_ptr);
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

void raster_source_pattern::_Cairo_release(cairo_pattern_t*, void* this_ptr, cairo_surface_t* surface) {
	auto rsp = static_cast<raster_source_pattern*>(this_ptr);
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

cairo_status_t raster_source_pattern::_Cairo_snapshot(cairo_pattern_t* pattern, void* this_ptr) {
	(void)pattern; // Unused parameter.
    (void)this_ptr; // Unused parameter.
	return CAIRO_STATUS_SUCCESS;
}

cairo_status_t raster_source_pattern::_Cairo_copy(cairo_pattern_t* pattern, void* this_ptr, const cairo_pattern_t* other) {
    (void)pattern; // Unused parameter.
    (void)other; // Unused parameter.
    (void)this_ptr; // Unused parameter.
	return CAIRO_STATUS_SUCCESS;
}

void raster_source_pattern::_Cairo_finish(cairo_pattern_t* pattern, void* this_ptr) {
	(void)pattern; // Unused parameter.
    (void)this_ptr; // Unused parameter.
}

raster_source_pattern::raster_source_pattern(raster_source_pattern&& other) : pattern(move(other)) {
	_User_callback_data = move(other._User_callback_data);
	_Width = other._Width;
	_Height = other._Height;
	_Acquire_fn = move(other._Acquire_fn);
	_Release_fn = move(other._Release_fn);
	other._User_callback_data = nullptr;
	other._Width = { };
	other._Height = { };
	other._Acquire_fn = nullptr;
	other._Release_fn = nullptr;
}

raster_source_pattern& raster_source_pattern::operator=(raster_source_pattern&& other) {
	if (this != &other) {
		pattern::operator=(move(other));
		_User_callback_data = move(other._User_callback_data);
		_Width = other._Width;
		_Height = other._Height;
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

raster_source_pattern::raster_source_pattern(void* user_data, content content, int width, int height)
: pattern(nullptr)
, _User_callback_data(user_data)
, _Width(width)
, _Height(height)
, _Acquire_fn(new function<surface(void* callback_data, surface& target, const rectangle& extents)>)
, _Release_fn(new function<void(void* callback_data, surface& surface)>) {
	_Pattern = shared_ptr<cairo_pattern_t>(cairo_pattern_create_raster_source(this, _Content_to_cairo_content_t(content), width, height), &cairo_pattern_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(_Pattern.get())));
}

void raster_source_pattern::set_callback_data(void* data) {
	_User_callback_data = data;
}

void* raster_source_pattern::get_callback_data() {
	return _User_callback_data;
}

void raster_source_pattern::set_acquire(
	function<surface(void* callback_data, surface& target, const rectangle& extents)> acquire_fn,
	function<void(void* callback_data, surface& surface)> release_fn
	) {
	*_Acquire_fn = acquire_fn;
	*_Release_fn = release_fn;
	// If acquire_fn is not set, pass in nullptr so we get cairo's handling behavior for a missing acquire function.
	cairo_raster_source_pattern_set_acquire(_Pattern.get(),
		(acquire_fn == nullptr) ? nullptr : &raster_source_pattern::_Cairo_acquire,
		&raster_source_pattern::_Cairo_release
		);
}

void raster_source_pattern::get_acquire(
	function<surface(void* callback_data, surface& target, const rectangle& extents)>& acquire_fn,
	function<void(void* callback_data, surface& surface)>& release_fn
	) {
	acquire_fn = *_Acquire_fn;
	release_fn = *_Release_fn;
}
