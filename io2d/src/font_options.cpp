#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

font_options::font_options(font_options&& other) noexcept
	: _Antialias(move(other._Antialias))
	, _Subpixel_order(move(other._Subpixel_order)) {
}

font_options& font_options::operator=(font_options&& other) noexcept {
	if (this != &other) {
		_Antialias = move(other._Antialias);
		_Subpixel_order = move(other._Subpixel_order);
	}
	return *this;
}

font_options::font_options(::std::experimental::io2d::antialias a, ::std::experimental::io2d::subpixel_order so) noexcept
	: _Antialias(a)
	, _Subpixel_order(so) {
}

void font_options::antialias(experimental::io2d::antialias a) noexcept {
	_Antialias = a;
}

void font_options::subpixel_order(experimental::io2d::subpixel_order so) noexcept {
	_Subpixel_order = so;
}

experimental::io2d::antialias font_options::antialias() const noexcept {
	return _Antialias;
}

experimental::io2d::subpixel_order font_options::subpixel_order() const noexcept {
	return _Subpixel_order;
}
