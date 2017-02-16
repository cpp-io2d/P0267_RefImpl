#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"
#include <cstring>

using namespace std;
using namespace std::experimental::io2d;

//image_surface::image_surface(image_surface&& other) noexcept
//	: surface(forward<image_surface>(other)) {
//}
//
//image_surface& image_surface::operator=(image_surface&& other) noexcept {
//	if (this != &other) {
//		surface::operator=(move(other));
//	}
//	return *this;
//}
//
//
image_surface::image_surface(experimental::io2d::format fmt, int width, int height)
	: surface({ cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), nullptr }, fmt, _Content_for_format(fmt)) {
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
}

image_surface::image_surface(experimental::io2d::format fmt, int width, int height, error_code& ec) noexcept
	: surface({ cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), nullptr }, fmt, _Content_for_format(fmt), ec) {
	if (static_cast<bool>(ec)) {
		_Surface = nullptr;
		_Context = nullptr;
		return;
	}
	ec = _Cairo_status_t_to_std_error_code(cairo_surface_status(_Surface.get()));
	if (static_cast<bool>(ec)) {
		_Surface = nullptr;
		_Context = nullptr;
		return;
	}
	ec = _Cairo_status_t_to_std_error_code(cairo_status(_Context.get()));
	if (static_cast<bool>(ec)) {
		_Surface = nullptr;
		_Context = nullptr;
		return;
	}
	ec.clear();
}

template <class InputIt>
image_surface::image_surface(InputIt first, InputIt last, experimental::io2d::format fmt, int width, int height)
	: surface({ nullptr, nullptr }, fmt, _Content_for_format(fmt)) {
	_Surface = unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), &cairo_surface_destroy);
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	auto expectedSize = cairo_image_surface_get_stride(_Surface.get() * cairo_image_surface_get_height(_Surface.get()));
	auto actualSize = ::std::distance(first, last) * sizeof(*first);
	if (actualSize != expectedSize) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_STRIDE);
	}
	_Context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy);
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
	cairo_surface_flush(_Surface.get());
	auto imageData = cairo_image_surface_get_data(_Surface.get());
	if (imageData == nullptr) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
	}
	else {
		::std::copy_n(first, actualSize, imageData);
		//::std::memcpy(imageData, data.data(), expected_size);
	}
	cairo_surface_mark_dirty(_Surface.get());
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	cairo_set_miter_limit(_Context.get(), _Line_join_miter_miter_limit);
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
	_Ensure_state();
}

void image_surface::data(const vector<unsigned char>& data) {
	auto expected_size = static_cast<vector<unsigned char>::size_type>(stride() * height());
	if (data.size() != static_cast<vector<unsigned char>::size_type>(expected_size)) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_STRIDE);
	}
	if (_Surface.get() == nullptr) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
	}
	cairo_surface_flush(_Surface.get());
	auto imageData = cairo_image_surface_get_data(_Surface.get());
	if (imageData == nullptr) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
	}
	else {
		::std::memcpy(imageData, data.data(), expected_size);
	}
	cairo_surface_mark_dirty(_Surface.get());
}

void image_surface::data(const vector<unsigned char>& data, error_code& ec) noexcept {
	auto expected_size = static_cast<vector<unsigned char>::size_type>(stride() * height());
	if (data.size() != static_cast<vector<unsigned char>::size_type>(expected_size)) {
		ec = make_error_code(io2d_error::invalid_stride);
		return;
	}
	if (_Surface.get() == nullptr) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NULL_POINTER);
		return;
	}
	cairo_surface_flush(_Surface.get());
	auto imageData = cairo_image_surface_get_data(_Surface.get());
	if (imageData == nullptr) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NULL_POINTER);
		return;
	}
	::std::memcpy(imageData, data.data(), expected_size);
	cairo_surface_mark_dirty(_Surface.get());
	ec.clear();
}

vector<unsigned char> image_surface::data() {
	auto required_size = static_cast<vector<unsigned char>::size_type>(stride() * height());
	vector<unsigned char> data;
	//if (_Surface.get() == nullptr) {
	//	_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
	//}
	cairo_surface_flush(_Surface.get());
	auto imageData = cairo_image_surface_get_data(_Surface.get());
	assert(imageData != nullptr && "Error calling cairo_image_surface_get_data.");
	data.assign(imageData, imageData + required_size);
	return data;
}

vector<unsigned char> image_surface::data(error_code& ec) noexcept {
	auto required_size = static_cast<vector<unsigned char>::size_type>(stride() * height());
	// Relies on C++17 noexcept guarantee for vector default ctor (N4258, adopted 2014-11).
	vector<unsigned char> data;
	//if (_Surface.get() == nullptr) {
	//	ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NULL_POINTER);
	//	return data;
	//}
	cairo_surface_flush(_Surface.get());
	auto imageData = cairo_image_surface_get_data(_Surface.get());
	assert(imageData != nullptr && "Error calling cairo_image_surface_get_data.");
	try {
		data.reserve(required_size);
		data.assign(imageData, imageData + required_size);
	}
	catch (const length_error&) {
		data.clear();
		ec = make_error_code(errc::not_enough_memory);
		return data;
	}
	catch (const bad_alloc&) {
		data.clear();
		ec = make_error_code(errc::not_enough_memory);
		return data;
	}
	ec.clear();
	return data;
}

format image_surface::format() const noexcept {
	return _Cairo_format_t_to_format(cairo_image_surface_get_format(_Surface.get()));
}

int image_surface::width() const noexcept {
	return cairo_image_surface_get_width(_Surface.get());
}

int image_surface::height() const noexcept {
	return cairo_image_surface_get_height(_Surface.get());
}

int image_surface::stride() const noexcept {
	return cairo_image_surface_get_stride(_Surface.get());
}
