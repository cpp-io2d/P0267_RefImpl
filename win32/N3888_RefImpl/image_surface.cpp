#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

image_surface::image_surface(image_surface&& other) : surface(move(other)) {
	_Create_from_png_fn = move(other._Create_from_png_fn);
	_Create_from_png_closure = move(other._Create_from_png_closure);
	_Data = move(other._Data);
	other._Create_from_png_fn = nullptr;
	other._Create_from_png_closure = nullptr;
	other._Data = nullptr;
}

image_surface& image_surface::operator=(image_surface&& other) {
	if (this != &other) {
		surface::operator=(move(other));
		_Create_from_png_fn = move(other._Create_from_png_fn);
		_Create_from_png_closure = move(other._Create_from_png_closure);
		_Data = move(other._Data);
		other._Create_from_png_fn = nullptr;
		other._Create_from_png_closure = nullptr;
		other._Data = nullptr;
	}
	return *this;
}

image_surface::image_surface(surface::native_handle_type nh, surface::native_handle_type map_of)
: surface(nullptr)
, _Create_from_png_fn(new ::std::function<void(void* closure, ::std::vector<unsigned char>& data)>)
, _Create_from_png_closure()
, _Data(nullptr) {
	_Surface = shared_ptr<cairo_surface_t>(nh, [map_of](cairo_surface_t *mapped_surface) {
		cairo_surface_unmap_image(map_of, mapped_surface); }
	);
}

image_surface::image_surface(format format, int width, int height)
: surface(nullptr)
, _Create_from_png_fn(new ::std::function<void(void* closure, ::std::vector<unsigned char>& data)>)
, _Create_from_png_closure()
, _Data(nullptr) {
	_Surface = shared_ptr<cairo_surface_t>(cairo_image_surface_create(_Format_to_cairo_format_t(format), width, height), &cairo_surface_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_surface_status(_Surface.get())));
}

image_surface::image_surface(vector<unsigned char>& data, format format, int width, int height, int stride)
: surface(nullptr)
, _Create_from_png_fn(new ::std::function<void(void* closure, ::std::vector<unsigned char>& data)>)
, _Create_from_png_closure()
, _Data(new vector<unsigned char>) {
	assert(stride == format_stride_for_width(format, width));
	_Data->resize(height * stride);
	_Data->assign(begin(data), end(data));
	_Surface = shared_ptr<cairo_surface_t>(cairo_image_surface_create_for_data(_Data->data(), _Format_to_cairo_format_t(format), width, height, stride), &cairo_surface_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_surface_status(_Surface.get())));
}

image_surface::image_surface(surface& other, format format, int width, int height)
: surface(nullptr)
, _Create_from_png_fn(new ::std::function<void(void* closure, ::std::vector<unsigned char>& data)>)
, _Create_from_png_closure()
, _Data(nullptr) {
	_Surface = shared_ptr<cairo_surface_t>(cairo_surface_create_similar_image(other.native_handle(), _Format_to_cairo_format_t(format), width, height), &cairo_surface_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_surface_status(_Surface.get())));
}

image_surface::image_surface(const string& filename)
: surface(nullptr)
, _Create_from_png_fn(new ::std::function<void(void* closure, ::std::vector<unsigned char>& data)>)
, _Create_from_png_closure()
, _Data(nullptr) {
	_Surface = shared_ptr<cairo_surface_t>(cairo_image_surface_create_from_png(filename.c_str()), &cairo_surface_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_surface_status(_Surface.get())));
}

image_surface::image_surface(::std::function<void(void* closure, vector<unsigned char>& data)> read_fn, void* closure)
: surface(nullptr)
, _Create_from_png_fn(new function<void(void*, vector<unsigned char>&)>(read_fn))
, _Create_from_png_closure(closure)
, _Data(nullptr) {
	_Surface = shared_ptr<cairo_surface_t>(cairo_image_surface_create_from_png_stream(&image_surface::_Cairo_create_from_png_stream, this), &cairo_surface_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_surface_status(_Surface.get())));
	_Create_from_png_closure = nullptr;
	*_Create_from_png_fn = nullptr;
}

void image_surface::set_data(vector<unsigned char>& data) {
	auto expected_size = static_cast<size_t>(get_stride() * get_height());
	if (data.size() != static_cast<uint64_t>(expected_size)) {
		throw drawing_exception(status::invalid_stride);
	}
	if (_Surface.get() == nullptr) {
		throw drawing_exception(status::null_pointer);
	}
	auto imageData = cairo_image_surface_get_data(_Surface.get());
	if (imageData == nullptr) {
		throw drawing_exception(status::null_pointer);
	}
	memcpy(imageData, data.data(), expected_size);
}

vector<unsigned char> image_surface::get_data() {
	auto required_size = get_stride() * get_height();
	vector<unsigned char> data;
	auto imageData = cairo_image_surface_get_data(_Surface.get());
	if (imageData == nullptr) {
		data.clear();
	}
	else {
		data.assign(imageData, imageData + required_size);
	}
	return data;
}

format image_surface::get_format() {
	return _Cairo_format_t_to_format(cairo_image_surface_get_format(_Surface.get()));
}

int image_surface::get_width() {
	return cairo_image_surface_get_width(_Surface.get());
}

int image_surface::get_height() {
	return cairo_image_surface_get_height(_Surface.get());
}

int image_surface::get_stride() {
	return cairo_image_surface_get_stride(_Surface.get());
}

cairo_status_t image_surface::_Cairo_create_from_png_stream(void* this_ptr, unsigned char* data, unsigned int length) {
	auto isp = static_cast<image_surface*>(this_ptr);
	vector<unsigned char> vec(data, data + length);
	auto& fn_ptr = *isp->_Create_from_png_fn;
	fn_ptr(isp->_Create_from_png_closure, vec);

	return CAIRO_STATUS_SUCCESS;
}
