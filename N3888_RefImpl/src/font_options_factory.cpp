#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

font_options_factory::font_options_factory()
	: _Lock()
	, _Antialias(::std::experimental::io2d::antialias::default_antialias)
	, _Subpixel_order(::std::experimental::io2d::subpixel_order::default_subpixel_order) {
}

font_options_factory::font_options_factory(const font_options_factory& other)
	: _Lock()
	, _Antialias()
	, _Subpixel_order() {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	lock_guard<decltype(_Lock)> tlg(_Lock);
	_Antialias = other._Antialias;
	_Subpixel_order = other._Subpixel_order;
}

font_options_factory& font_options_factory::operator=(const font_options_factory& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Antialias = other._Antialias;
		_Subpixel_order = other._Subpixel_order;
	}
	return *this;
}

font_options_factory::font_options_factory(font_options_factory&& other)
	: _Lock()
	, _Antialias()
	, _Subpixel_order() {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Antialias = move(other._Antialias);
	_Subpixel_order = move(other._Subpixel_order);
}

font_options_factory& font_options_factory::operator=(font_options_factory&& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Antialias = move(other._Antialias);
		_Subpixel_order = move(other._Subpixel_order);
	}
	return *this;
}

void font_options_factory::antialias(::std::experimental::io2d::antialias a) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Antialias = a;
}

antialias font_options_factory::antialias() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Antialias;
}

void font_options_factory::subpixel_order(::std::experimental::io2d::subpixel_order so) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Subpixel_order = so;
}

subpixel_order font_options_factory::subpixel_order() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Subpixel_order;
}
