#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

surface::native_handle_type surface::native_handle() const {
	return _Surface.get();
}

surface::surface(surface::native_handle_type native_handle)
: _Surface(unique_ptr<cairo_surface_t, void(*)(cairo_surface_t*)>(native_handle, &cairo_surface_destroy)) {
}

surface::surface(surface&& other)
: _Surface(move(other._Surface)) {
    other._Surface = nullptr;
}

surface& surface::operator=(surface&& other) {
	if (this != &other) {
		_Surface = move(other._Surface);
		other._Surface = nullptr;
	}
	return *this;
}

surface& surface::operator=(surface::native_handle_type nh) {
    _Surface = unique_ptr<cairo_surface_t, void(*)(cairo_surface_t*)>(nh, &cairo_surface_destroy);
	return *this;
}

surface::surface(const surface& other, content content, double width, double height)
: _Surface(unique_ptr<cairo_surface_t, void(*)(cairo_surface_t*)>(cairo_surface_create_similar(other._Surface.get(), _Content_to_cairo_content_t(content), _Double_to_int(width, false), _Double_to_int(height, false)), &cairo_surface_destroy)) {
}

surface::surface(const surface& target, const rectangle& rect)
: _Surface(unique_ptr<cairo_surface_t, void(*)(cairo_surface_t*)>(cairo_surface_create_for_rectangle(target._Surface.get(), _Double_to_int(rect.x, false), _Double_to_int(rect.y, false), _Double_to_int(rect.width, false), _Double_to_int(rect.height, false)), &cairo_surface_destroy)) {
}

surface::~surface() {
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

void surface::mark_dirty_rectangle(const rectangle& rect) {
	cairo_surface_mark_dirty_rectangle(_Surface.get(), static_cast<int>(rect.x), static_cast<int>(rect.y), static_cast<int>(rect.width), static_cast<int>(rect.height));
}

void surface::set_device_offset(const point& offset) {
	cairo_surface_set_device_offset(_Surface.get(), offset.x, offset.y);
}

void surface::get_device_offset(point& offset) {
	cairo_surface_get_device_offset(_Surface.get(), &offset.x, &offset.y);
}

void surface::write_to_png(const string& filename) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_surface_write_to_png(_Surface.get(), filename.c_str())));
}

image_surface surface::map_to_image(const rectangle& extents) {
    cairo_rectangle_int_t cextents{ _Double_to_int(extents.x), _Double_to_int(extents.y), _Double_to_int(extents.width), _Double_to_int(extents.height) };

	return image_surface(cairo_surface_map_to_image(_Surface.get(), (extents.x == 0 && extents.y == 0 && extents.width == 0 && extents.height == 0) ? nullptr : &cextents), _Surface.get());
}

void surface::unmap_image(image_surface& image) {
    image._Surface = unique_ptr<cairo_surface_t, void(*)(cairo_surface_t*)>(cairo_image_surface_create(CAIRO_FORMAT_INVALID, 0, 0), &cairo_surface_destroy);
}

bool surface::has_surface_resource() const {
    return _Surface != nullptr;
}
