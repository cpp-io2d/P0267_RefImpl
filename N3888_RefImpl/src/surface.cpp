#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

surface::native_handle_type surface::native_handle() const {
	return _Surface.get();
}

surface::surface(surface::native_handle_type native_handle)
: _Surface()
, _User_data_map(new ::std::map<user_data_key, ::std::shared_ptr<void>>)
, _Write_to_png_fn(new ::std::function<void(void* closure, const ::std::vector<unsigned char>& data)>)
, _Write_to_png_closure()
, _Mime_data_destroy_fn_map(new ::std::map<::std::string, ::std::function<void(void* data)>>)
, _Mime_data_destroy_closure_map(new ::std::map<::std::string, void*>) {
	_Surface = shared_ptr<cairo_surface_t>(native_handle, &cairo_surface_destroy);
}

surface::surface(surface&& other) {
	_Surface = move(other._Surface);
	_User_data_map = move(other._User_data_map);
	_Write_to_png_fn = move(other._Write_to_png_fn);
	_Write_to_png_closure = move(other._Write_to_png_closure);
	_Mime_data_destroy_fn_map = move(other._Mime_data_destroy_fn_map);
	_Mime_data_destroy_closure_map = move(other._Mime_data_destroy_closure_map);
	other._Surface = nullptr;
	other._User_data_map = nullptr;
	other._Write_to_png_fn = nullptr;
	other._Write_to_png_closure = nullptr;
	other._Mime_data_destroy_fn_map = nullptr;
	other._Mime_data_destroy_closure_map = nullptr;
}

surface& surface::operator=(surface&& other) {
	if (this != &other) {
		_Surface = move(other._Surface);
		_User_data_map = move(other._User_data_map);
		_Write_to_png_fn = move(other._Write_to_png_fn);
		_Write_to_png_closure = move(other._Write_to_png_closure);
		_Mime_data_destroy_fn_map = move(other._Mime_data_destroy_fn_map);
		_Mime_data_destroy_closure_map = move(other._Mime_data_destroy_closure_map);
		other._Surface = nullptr;
		other._User_data_map = nullptr;
		other._Write_to_png_fn = nullptr;
		other._Write_to_png_closure = nullptr;
		other._Mime_data_destroy_fn_map = nullptr;
		other._Mime_data_destroy_closure_map = nullptr;
	}
	return *this;
}

surface& surface::operator=(surface::native_handle_type nh) {
	_Surface = shared_ptr<cairo_surface_t>(nh, &cairo_surface_destroy);
	return *this;
}

surface::surface(surface& other, content content, int width, int height)
: _Surface()
, _Write_to_png_fn()
, _Write_to_png_closure() {
	_Surface = shared_ptr<cairo_surface_t>(cairo_surface_create_similar(other._Surface.get(), _Content_to_cairo_content_t(content), width, height), &cairo_surface_destroy);
}

surface::surface(surface& target, double x, double y, double width, double height)
: _Surface()
, _Write_to_png_fn()
, _Write_to_png_closure() {
	_Surface = shared_ptr<cairo_surface_t>(cairo_surface_create_for_rectangle(target._Surface.get(), x, y, width, height), &cairo_surface_destroy);
}

surface::~surface() {
	if (_Mime_data_destroy_fn_map != nullptr) {
		// Note that we are by-passing cairo's mime data destruction and doing it ourselves.
		for (auto& kv : *_Mime_data_destroy_fn_map) {
			auto& mimetype = kv.first;
			auto& destroy_fn = kv.second;
			if (destroy_fn != nullptr) {
				destroy_fn((*_Mime_data_destroy_closure_map)[mimetype]);
				destroy_fn = nullptr;
			}
		}
		(*_Mime_data_destroy_fn_map).clear();
	}
}

status surface::status() {
	return _Cairo_status_t_to_status(cairo_surface_status(_Surface.get()));
}

void surface::finish() {
	cairo_surface_finish(_Surface.get());
}

void surface::flush() {
	cairo_surface_flush(_Surface.get());
}

device surface::get_device() {
	return device(cairo_surface_get_device(_Surface.get()));
}

void surface::get_font_options(font_options& options) {
	unique_ptr<cairo_font_options_t, function<void(cairo_font_options_t*)>> value(cairo_font_options_create(), &cairo_font_options_destroy);
	cairo_surface_get_font_options(_Surface.get(), value.get());
	options = value.release();
}

content surface::get_content() {
	return _Cairo_content_t_to_content(cairo_surface_get_content(_Surface.get()));
}

void surface::mark_dirty() {
	cairo_surface_mark_dirty(_Surface.get());
}

void surface::mark_dirty_rectangle(int x, int y, int width, int height) {
	cairo_surface_mark_dirty_rectangle(_Surface.get(), x, y, width, height);
}

void surface::set_device_offset(double x_offset, double y_offset) {
	cairo_surface_set_device_offset(_Surface.get(), x_offset, y_offset);
}

void surface::get_device_offset(double& x_offset, double& y_offset) {
	cairo_surface_get_device_offset(_Surface.get(), &x_offset, &y_offset);
}

void surface::set_fallback_resolution(double x_pixels_per_inch, double y_pixels_per_inch) {
	cairo_surface_set_fallback_resolution(_Surface.get(), x_pixels_per_inch, y_pixels_per_inch);
}

void surface::get_fallback_resolution(double& x_pixels_per_inch, double& y_pixels_per_inch) {
	cairo_surface_get_fallback_resolution(_Surface.get(), &x_pixels_per_inch, &y_pixels_per_inch);
}

void surface::write_to_png(const string& filename) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_surface_write_to_png(_Surface.get(), filename.c_str())));
}

void surface::write_to_png_stream(function<void(void* closure, const vector<unsigned char>& data)> write_fn, void* closure) {
	assert((_Write_to_png_closure == nullptr) && (_Write_to_png_fn == nullptr));
	_Write_to_png_closure = closure;
	*_Write_to_png_fn = write_fn;
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_surface_write_to_png_stream(_Surface.get(), &surface::_Cairo_write_to_png_stream, this)));
	_Write_to_png_closure = nullptr;
	*_Write_to_png_fn = nullptr;
}

cairo_status_t surface::_Cairo_write_to_png_stream(void* this_ptr, const unsigned char* data, unsigned int length) {
	shared_ptr<int> a; unique_ptr<int> b;
	auto sp = static_cast<surface*>(this_ptr);
	vector<unsigned char> vec(data, data + length);
	auto& write_to_png_fn = *sp->_Write_to_png_fn;
	write_to_png_fn(sp->_Write_to_png_closure, vec);

	return CAIRO_STATUS_SUCCESS;
}

void surface::set_user_data(const user_data_key& key, shared_ptr<void>& value) {
	assert((sizeof(void *) >= sizeof(int_fast64_t)) || ((sizeof(void *) == 4) && (key._Get_value() <= INT32_MAX)));
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_surface_set_user_data(_Surface.get(), reinterpret_cast<cairo_user_data_key_t*>(key._Get_value()), value.get(), nullptr)));
	(*_User_data_map)[key] = value;
}

shared_ptr<void>& surface::get_user_data(const user_data_key& key) {
	return (*_User_data_map)[key];
}

void surface::copy_page() {
	cairo_surface_copy_page(_Surface.get());
}

void surface::show_page() {
	cairo_surface_show_page(_Surface.get());
}

bool surface::has_show_text_glyphs() {
	return cairo_surface_has_show_text_glyphs(_Surface.get()) != 0;
}

void surface::set_mime_data(const ::std::string& mime_type, const ::std::vector<unsigned char>& data, ::std::function<void(void* data)> destroy, void* closure) {
	// Destroy the old mime data, if any.
	auto previous_destroy = (*_Mime_data_destroy_fn_map).find(mime_type);
	if (previous_destroy != (*_Mime_data_destroy_fn_map).end()) {
		auto& pd_fn = (*previous_destroy).second;
		pd_fn((*_Mime_data_destroy_closure_map)[mime_type]);
	}
	(*_Mime_data_destroy_fn_map)[mime_type] = destroy;
	(*_Mime_data_destroy_closure_map)[mime_type] = closure;

	// Note that we are by-passing cairo's mime data destruction and doing it ourselves.
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_surface_set_mime_data(
		_Surface.get(),
		mime_type.c_str(),
		data.size() == 0 ? nullptr : data.data(),
		static_cast<unsigned long>(data.size()),
		nullptr,
		nullptr
		)));
}

void surface::get_mime_data(const ::std::string& mime_type, ::std::vector<unsigned char>& data) {
	const unsigned char* data_ptr = nullptr;
	unsigned long length = 0;
	// Note: We do not need to free data_ptr since it is just an alias, not a copy.
	cairo_surface_get_mime_data(_Surface.get(), mime_type.c_str(), &data_ptr, &length);
	if (data_ptr == nullptr) {
		data.clear();
	}
	else {
		data.assign(data_ptr, data_ptr + length);
	}
}

bool surface::supports_mime_type(const ::std::string& mime_type) {
	return cairo_surface_supports_mime_type(_Surface.get(), mime_type.c_str()) != 0;
}

image_surface surface::map_to_image(const rectangle_int& extents) {
	cairo_rectangle_int_t cextents;
	cextents.x = extents.x;
	cextents.y = extents.y;
	cextents.width = extents.width;
	cextents.height = extents.height;

	return image_surface(cairo_surface_map_to_image(_Surface.get(), (extents.x == 0 && extents.y == 0 && extents.width == 0 && extents.height == 0) ? nullptr : &cextents), _Surface.get());
}

void surface::unmap_image(image_surface& image) {
	image._Surface = shared_ptr<cairo_surface_t>(cairo_image_surface_create(CAIRO_FORMAT_INVALID, 0, 0), &cairo_surface_destroy);
}
