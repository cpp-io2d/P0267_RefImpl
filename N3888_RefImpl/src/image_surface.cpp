#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"
#include <cstring>

using namespace std;
using namespace std::experimental::io2d;

image_surface::image_surface(image_surface&& other) : surface(move(other)) {
}

image_surface& image_surface::operator=(image_surface&& other) {
	if (this != &other) {
		surface::operator=(move(other));
	}
	return *this;
}

image_surface::image_surface(surface::native_handle_type nh, surface::native_handle_type map_of)
	: surface({ nullptr, nullptr }, _Cairo_format_t_to_format(cairo_image_surface_get_format(nh.csfce)), _Cairo_content_t_to_content(cairo_surface_get_content(nh.csfce))) {
	_Surface = unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(nh.csfce, [map_of](cairo_surface_t *mapped_surface) { cairo_surface_unmap_image(map_of.csfce, mapped_surface); });
	_Context = unique_ptr<cairo_t, function<void(cairo_t*)>>(cairo_create(_Surface.get()), &cairo_destroy);
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
	cairo_set_miter_limit(_Context.get(), _Line_join_miter_miter_limit);
}

image_surface::image_surface(::std::experimental::io2d::format fmt, int width, int height)
	: surface({ cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), nullptr }, fmt, _Content_for_format(fmt)) {
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
}

image_surface::image_surface(vector<unsigned char>& data, ::std::experimental::io2d::format fmt, int width, int height)
	: surface({ nullptr, nullptr }, fmt, _Content_for_format(fmt)) {
	_Surface = unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), &cairo_surface_destroy);
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	auto expected_size = static_cast<vector<unsigned char>::size_type>(cairo_image_surface_get_stride(_Surface.get()) * cairo_image_surface_get_height(_Surface.get()));
	if (data.size() != expected_size) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_STRIDE);
	}
	_Context = unique_ptr<cairo_t, function<void(cairo_t*)>>(cairo_create(_Surface.get()), &cairo_destroy);
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
	cairo_surface_flush(_Surface.get());
	auto imageData = cairo_image_surface_get_data(_Surface.get());
	if (imageData == nullptr) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
	}
	::std::memcpy(imageData, data.data(), expected_size);
	cairo_surface_mark_dirty(_Surface.get());
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	cairo_set_miter_limit(_Context.get(), _Line_join_miter_miter_limit);
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
}

image_surface::image_surface(const surface& other, ::std::experimental::io2d::format fmt, int width, int height)
	: surface({ nullptr, nullptr }, fmt, _Content_for_format(fmt)) {
	_Surface = unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(cairo_surface_create_similar_image(other.native_handle().csfce, _Format_to_cairo_format_t(fmt), width, height), &cairo_surface_destroy);
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	_Context = unique_ptr<cairo_t, function<void(cairo_t*)>>(cairo_create(_Surface.get()), &cairo_destroy);
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
	cairo_set_miter_limit(_Context.get(), _Line_join_miter_miter_limit);
}

image_surface::image_surface(const string& filename)
	: surface({ nullptr, nullptr }, ::std::experimental::io2d::format::argb32, ::std::experimental::io2d::content::color_alpha) {
	_Surface = unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(cairo_image_surface_create_from_png(filename.c_str()), &cairo_surface_destroy);
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	_Context = unique_ptr<cairo_t, function<void(cairo_t*)>>(cairo_create(_Surface.get()), &cairo_destroy);
	_Format = _Cairo_format_t_to_format(cairo_image_surface_get_format(_Surface.get()));
	_Content = _Content_for_format(_Format);
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
	cairo_set_miter_limit(_Context.get(), _Line_join_miter_miter_limit);
}

image_surface::~image_surface() {
}

void image_surface::data(const vector<unsigned char>& data) {
	auto expected_size = static_cast<size_t>(stride() * height());
	if (data.size() != static_cast<uint64_t>(expected_size)) {
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
	::std::memcpy(imageData, data.data(), expected_size);
	cairo_surface_mark_dirty(_Surface.get());
}

vector<unsigned char> image_surface::data() {
	auto required_size = stride() * height();
	vector<unsigned char> data;
	cairo_surface_flush(_Surface.get());
	auto imageData = cairo_image_surface_get_data(_Surface.get());
	if (imageData == nullptr) {
		data.clear();
	}
	else {
		data.assign(imageData, imageData + required_size);
	}
	return data;
}

format image_surface::format() const {
	return _Cairo_format_t_to_format(cairo_image_surface_get_format(_Surface.get()));
}

int image_surface::width() const {
	return cairo_image_surface_get_width(_Surface.get());
}

int image_surface::height() const {
	return cairo_image_surface_get_height(_Surface.get());
}

int image_surface::stride() const {
	return cairo_image_surface_get_stride(_Surface.get());
}
