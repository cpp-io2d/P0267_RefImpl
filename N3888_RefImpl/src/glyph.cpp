#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

glyph::native_handle_type glyph::native_handle() noexcept {
	return &_Glyph_data;
}

glyph::glyph() noexcept
	: _Glyph_data({ 0UL, 0.0, 0.0 }) {
}

glyph::glyph(glyph&& other) noexcept
	: _Glyph_data(move(other._Glyph_data)) {
	other._Glyph_data = { };
}

glyph& glyph::operator=(glyph&& other) noexcept {
	if (this != &other) {
		_Glyph_data = move(other._Glyph_data);
		other._Glyph_data = { };
	}
	return *this;
}

glyph::glyph(unsigned long index, double x, double y) noexcept
	: _Glyph_data({ index, x, y }) {
}

void glyph::index(unsigned long index) noexcept {
	_Glyph_data.index = index;
}

void glyph::x(double x) noexcept {
	_Glyph_data.x = x;
}

void glyph::y(double y) noexcept {
	_Glyph_data.y = y;
}

unsigned long glyph::index() const noexcept {
	return _Glyph_data.index;
}

double glyph::x() const noexcept {
	return _Glyph_data.x;
}

double glyph::y() const noexcept {
	return _Glyph_data.y;
}
