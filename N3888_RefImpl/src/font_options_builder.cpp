#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

font_options_builder::font_options_builder()
	: _Lock()
	, _Antialias(antialias::default_antialias)
	, _Subpixel_order(subpixel_order::default_subpixel_order)
	, _Hint_style(hint_style::default_hint_style)
	, _Hint_metrics(hint_metrics::default_hint_metrics) {
}

font_options_builder::font_options_builder(const font_options_builder& other)
	: _Lock()
	, _Antialias()
	, _Subpixel_order()
	, _Hint_style()
	, _Hint_metrics() {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	lock_guard<decltype(_Lock)> tlg(_Lock);
	_Antialias = other._Antialias;
	_Subpixel_order = other._Subpixel_order;
	_Hint_style = other._Hint_style;
	_Hint_metrics = other._Hint_metrics;
}

font_options_builder& font_options_builder::operator=(const font_options_builder& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Antialias = other._Antialias;
		_Subpixel_order = other._Subpixel_order;
		_Hint_style = other._Hint_style;
		_Hint_metrics = other._Hint_metrics;
	}
	return *this;
}

font_options_builder::font_options_builder(font_options_builder&& other)
	: _Lock()
	, _Antialias()
	, _Subpixel_order()
	, _Hint_style()
	, _Hint_metrics() {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Antialias = move(other._Antialias);
	_Subpixel_order = move(other._Subpixel_order);
	_Hint_style = move(other._Hint_style);
	_Hint_metrics = move(other._Hint_metrics);
}

font_options_builder& font_options_builder::operator=(font_options_builder&& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Antialias = move(other._Antialias);
		_Subpixel_order = move(other._Subpixel_order);
		_Hint_style = move(other._Hint_style);
		_Hint_metrics = move(other._Hint_metrics);
	}
	return *this;
}

font_options font_options_builder::get_font_options() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return font_options(_Antialias, _Subpixel_order, _Hint_style, _Hint_metrics);
}

void font_options_builder::set_antialias(antialias a) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Antialias = a;
}

antialias font_options_builder::get_antialias() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Antialias;
}

void font_options_builder::set_subpixel_order(subpixel_order so) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Subpixel_order = so;
}

subpixel_order font_options_builder::get_subpixel_order() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Subpixel_order;
}

void font_options_builder::set_hint_style(hint_style hs) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Hint_style = hs;
}

hint_style font_options_builder::get_hint_style() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Hint_style;
}

void font_options_builder::set_hint_metrics(hint_metrics hm) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Hint_metrics = hm;
}

hint_metrics font_options_builder::get_hint_metrics() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Hint_metrics;
}
