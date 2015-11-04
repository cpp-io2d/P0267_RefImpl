#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

mapped_surface::mapped_surface(surface::native_handle_type nh, surface::native_handle_type map_of)
	: _Mapped_surface(nh)
	, _Map_of(map_of) {
	assert(_Mapped_surface.csfce != nullptr && _Map_of.csfce != nullptr);
	auto status = cairo_surface_status(_Mapped_surface.csfce);
	if (status != CAIRO_STATUS_SUCCESS) {
		cairo_surface_unmap_image(_Mapped_surface.csfce, _Map_of.csfce);
		_Mapped_surface = { nullptr, nullptr };
		_Map_of = { nullptr, nullptr };
		_Throw_if_failed_cairo_status_t(status);
	}
	// Reference the surface that is mapped to ensure it isn't accidentally destroyed while the map still exists.
	cairo_surface_reference(_Map_of.csfce);
}

mapped_surface::mapped_surface(surface::native_handle_type nh, surface::native_handle_type map_of, error_code& ec) noexcept
	: _Mapped_surface(nh)
	, _Map_of(map_of) {
	assert(_Mapped_surface.csfce != nullptr && _Map_of.csfce != nullptr);
	auto status = cairo_surface_status(_Mapped_surface.csfce);
	if (status != CAIRO_STATUS_SUCCESS) {
		cairo_surface_unmap_image(_Mapped_surface.csfce, _Map_of.csfce);
		_Mapped_surface = { nullptr, nullptr };
		_Map_of = { nullptr, nullptr };
		ec = _Cairo_status_t_to_std_error_code(status);
		return;
	}
	// Reference the surface that is mapped to ensure it isn't accidentally destroyed while the map still exists.
	cairo_surface_reference(_Map_of.csfce);
	ec.clear();
}

mapped_surface::~mapped_surface() {
	if (_Mapped_surface.csfce != nullptr) {
		cairo_surface_unmap_image(_Map_of.csfce, _Mapped_surface.csfce);
		// Remove the reference we added to the surface that was mapped.
		cairo_surface_destroy(_Map_of.csfce);
		_Mapped_surface.csfce = nullptr;
		_Map_of.csfce = nullptr;
	}
}

void mapped_surface::commit_changes() {
	cairo_surface_mark_dirty(_Mapped_surface.csfce);
}

void mapped_surface::commit_changes(::std::error_code& ec) noexcept {
	cairo_surface_mark_dirty(_Mapped_surface.csfce);
	ec.clear();
}

void mapped_surface::commit_changes(const rectangle& area) {
	cairo_surface_mark_dirty_rectangle(_Mapped_surface.csfce, static_cast<int>(area.x()), static_cast<int>(area.y()),
		static_cast<int>(area.width()), static_cast<int>(area.height()));
}

void mapped_surface::commit_changes(const rectangle& area, error_code& ec) noexcept {
	cairo_surface_mark_dirty_rectangle(_Mapped_surface.csfce, static_cast<int>(area.x()), static_cast<int>(area.y()),
		static_cast<int>(area.width()), static_cast<int>(area.height()));
	ec.clear();
}

unsigned char* mapped_surface::data() {
	auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
	if (result == nullptr) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
	}
	return result;
}

unsigned char* mapped_surface::data(error_code& ec) noexcept {
	auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
	if (result == nullptr) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NULL_POINTER);
		return result;
	}
	ec.clear();
	return result;
}

// Observers
const unsigned char* mapped_surface::data() const {
	auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
	if (result == nullptr) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
	}
	return result;
}

const unsigned char* mapped_surface::data(error_code& ec) const noexcept {
	auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
	if (result == nullptr) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NULL_POINTER);
		return result;
	}
	ec.clear();
	return result;
}

::std::experimental::io2d::format mapped_surface::format() const noexcept {
	if (cairo_surface_status(_Mapped_surface.csfce) != CAIRO_STATUS_SUCCESS) {
		return experimental::io2d::format::invalid;
	}
	return _Cairo_format_t_to_format(cairo_image_surface_get_format(_Mapped_surface.csfce));
}

int mapped_surface::width() const noexcept {
	if (format() == experimental::io2d::format::invalid) {
		return 0;
	}
	return cairo_image_surface_get_width(_Mapped_surface.csfce);
}

int mapped_surface::height() const noexcept {
	if (format() == experimental::io2d::format::invalid) {
		return 0;
	}
	return cairo_image_surface_get_height(_Mapped_surface.csfce);
}

int mapped_surface::stride() const noexcept {
	if (format() == experimental::io2d::format::invalid) {
		return 0;
	}
	return cairo_image_surface_get_stride(_Mapped_surface.csfce);
}
