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

font_options::font_options(antialias a, subpixel_order so, hint_style hs, hint_metrics hm)
: _Font_options(shared_ptr<cairo_font_options_t>(cairo_font_options_create(), &cairo_font_options_destroy)) {
	_Throw_if_failed_cairo_status_t(cairo_font_options_status(_Font_options.get()));
	cairo_font_options_set_antialias(_Font_options.get(), _Antialias_to_cairo_antialias_t(a));
	_Throw_if_failed_cairo_status_t(cairo_font_options_status(_Font_options.get()));
	cairo_font_options_set_subpixel_order(_Font_options.get(), _Subpixel_order_to_cairo_subpixel_order_t(so));
	_Throw_if_failed_cairo_status_t(cairo_font_options_status(_Font_options.get()));
	cairo_font_options_set_hint_style(_Font_options.get(), _Hint_style_to_cairo_hint_style_t(hs));
	_Throw_if_failed_cairo_status_t(cairo_font_options_status(_Font_options.get()));
	cairo_font_options_set_hint_metrics(_Font_options.get(), _Hint_metrics_to_cairo_hint_metrics_t(hm));
	_Throw_if_failed_cairo_status_t(cairo_font_options_status(_Font_options.get()));
}

font_options::font_options(font_options::native_handle_type nh) {
	_Font_options = shared_ptr<cairo_font_options_t>(nh, &cairo_font_options_destroy);
}

antialias font_options::get_antialias() const {
	return _Cairo_antialias_t_to_antialias(cairo_font_options_get_antialias(_Font_options.get()));
}

subpixel_order font_options::get_subpixel_order() const {
	return _Cairo_subpixel_order_t_to_subpixel_order(cairo_font_options_get_subpixel_order(_Font_options.get()));
}

hint_style font_options::get_hint_style() const {
	return _Cairo_hint_style_t_to_hint_style(cairo_font_options_get_hint_style(_Font_options.get()));
}

hint_metrics font_options::get_hint_metrics() const {
	return _Cairo_hint_metrics_t_to_hint_metrics(cairo_font_options_get_hint_metrics(_Font_options.get()));
}
