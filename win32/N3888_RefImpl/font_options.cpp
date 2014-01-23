#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

font_options::native_handle_type font_options::native_handle() const {
	return _Font_options.get();
}

font_options::font_options(font_options&& other) {
	_Font_options = move(other._Font_options);
	other._Font_options = nullptr;
}

font_options& font_options::operator=(font_options&& other) {
	if (this != &other) {
		_Font_options = move(other._Font_options);
		other._Font_options = nullptr;
	}
	return *this;
}

font_options::font_options(font_options::native_handle_type nh) {
	_Font_options = shared_ptr<cairo_font_options_t>(nh, &cairo_font_options_destroy);
}

font_options& font_options::operator=(font_options::native_handle_type nh) {
	_Font_options = shared_ptr<cairo_font_options_t>(nh, &cairo_font_options_destroy);
	return *this;
}

status font_options::status() {
	return _Cairo_status_t_to_status(cairo_font_options_status(_Font_options.get()));
}

void font_options::merge(const font_options& other) {
	cairo_font_options_merge(_Font_options.get(), other.native_handle());
}

unsigned long font_options::hash() {
	return cairo_font_options_hash(_Font_options.get());
}

bool font_options::equal(const font_options& other) {
	return cairo_font_options_equal(_Font_options.get(), other.native_handle()) != 0;
}

void font_options::set_antialias(antialias antialias) {
	cairo_font_options_set_antialias(_Font_options.get(), _Antialias_to_cairo_antialias_t(antialias));
}

antialias font_options::get_antialias() {
	return _Cairo_antialias_t_to_antialias(cairo_font_options_get_antialias(_Font_options.get()));
}

void font_options::set_subpixel_order(subpixel_order subpixel_order) {
	cairo_font_options_set_subpixel_order(_Font_options.get(), _Subpixel_order_to_cairo_subpixel_order_t(subpixel_order));
}

subpixel_order font_options::get_subpixel_order() {
	return _Cairo_subpixel_order_t_to_subpixel_order(cairo_font_options_get_subpixel_order(_Font_options.get()));
}

void font_options::set_hint_style(hint_style hint_style) {
	cairo_font_options_set_hint_style(_Font_options.get(), _Hint_style_to_cairo_hint_style_t(hint_style));
}

hint_style font_options::get_hint_style() {
	return _Cairo_hint_style_t_to_hint_style(cairo_font_options_get_hint_style(_Font_options.get()));
}

void font_options::set_hint_metrics(hint_metrics hint_metrics) {
	cairo_font_options_set_hint_metrics(_Font_options.get(), _Hint_metrics_to_cairo_hint_metrics_t(hint_metrics));
}

hint_metrics font_options::get_hint_metrics() {
	return _Cairo_hint_metrics_t_to_hint_metrics(cairo_font_options_get_hint_metrics(_Font_options.get()));
}
