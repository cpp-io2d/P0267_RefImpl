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

// Modifiers
void mapped_surface::data(const ::std::vector<unsigned char>& data) {
	auto expected_size = static_cast<size_t>(stride() * height());
	if (data.size() != static_cast<uint64_t>(expected_size)) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_STRIDE);
	}
	if (_Mapped_surface.csfce == nullptr) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
	}
	cairo_surface_flush(_Mapped_surface.csfce);
	auto imageData = cairo_image_surface_get_data(_Mapped_surface.csfce);
	if (imageData == nullptr) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
	}
	::std::memcpy(imageData, data.data(), expected_size);
	cairo_surface_mark_dirty(_Mapped_surface.csfce);
}

void mapped_surface::data(const ::std::vector<unsigned char>& data, ::std::error_code& ec) noexcept {
	auto expected_size = static_cast<size_t>(stride() * height());
	if (data.size() != static_cast<uint64_t>(expected_size)) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_STRIDE);
		return;
	}
	if (_Mapped_surface.csfce == nullptr) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NULL_POINTER);
		return;
	}

	cairo_surface_flush(_Mapped_surface.csfce);
	auto imageData = cairo_image_surface_get_data(_Mapped_surface.csfce);
	if (imageData == nullptr) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NULL_POINTER);
		return;
	}

	::std::memcpy(imageData, data.data(), expected_size);
	cairo_surface_mark_dirty(_Mapped_surface.csfce);
	ec.clear();
}


::std::vector<unsigned char> mapped_surface::data() {
	auto requiredSize = stride() * height();
	vector<unsigned char> data;
	data.reserve(static_cast<size_t>(requiredSize));
	cairo_surface_flush(_Mapped_surface.csfce);
	auto imageData = cairo_image_surface_get_data(_Mapped_surface.csfce);
	if (imageData == nullptr) {
		data.clear();
	}
	else {
		data.assign(imageData, imageData + requiredSize);
	}
	return data;
}

::std::vector<unsigned char> mapped_surface::data(::std::error_code& ec) noexcept {
	auto requiredSize = stride() * height();
	// Relies on C++17 vector noexcept default ctor.
	vector<unsigned char> data;
	try {
		data.reserve(static_cast<size_t>(requiredSize));
		cairo_surface_flush(_Mapped_surface.csfce);
		auto imageData = cairo_image_surface_get_data(_Mapped_surface.csfce);
		if (imageData == nullptr) {
			data.clear();
		}
		else {
			data.assign(imageData, imageData + requiredSize);
		}
	}
	catch (const length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		return data;
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return data;
	}
	ec.clear();
	return data;
}

// Observers
::std::experimental::io2d::format mapped_surface::format() const noexcept {
	return _Cairo_format_t_to_format(cairo_image_surface_get_format(_Mapped_surface.csfce));
}

int mapped_surface::width() const noexcept {
	return cairo_image_surface_get_width(_Mapped_surface.csfce);
}

int mapped_surface::height() const noexcept {
	return cairo_image_surface_get_height(_Mapped_surface.csfce);
}

int mapped_surface::stride() const noexcept {
	return cairo_image_surface_get_stride(_Mapped_surface.csfce);
}
