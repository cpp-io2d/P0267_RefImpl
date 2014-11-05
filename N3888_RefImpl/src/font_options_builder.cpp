#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

font_options_builder::font_options_builder()
	: _Lock()
	, _Antialias(antialias::default_antialias)
	, _Subpixel_order(subpixel_order::default_subpixel_order) {
}

font_options_builder::font_options_builder(const font_options_builder& other)
	: _Lock()
	, _Antialias()
	, _Subpixel_order() {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	lock_guard<decltype(_Lock)> tlg(_Lock);
	_Antialias = other._Antialias;
	_Subpixel_order = other._Subpixel_order;
}

font_options_builder& font_options_builder::operator=(const font_options_builder& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Antialias = other._Antialias;
		_Subpixel_order = other._Subpixel_order;
	}
	return *this;
}

font_options_builder::font_options_builder(font_options_builder&& other)
	: _Lock()
	, _Antialias()
	, _Subpixel_order() {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Antialias = move(other._Antialias);
	_Subpixel_order = move(other._Subpixel_order);
}

font_options_builder& font_options_builder::operator=(font_options_builder&& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Antialias = move(other._Antialias);
		_Subpixel_order = move(other._Subpixel_order);
	}
	return *this;
}

font_options font_options_builder::get_font_options() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return font_options(_Antialias, _Subpixel_order);
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
