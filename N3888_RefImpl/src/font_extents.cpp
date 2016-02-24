#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

font_extents::native_handle_type font_extents::native_handle() noexcept {
	return &_Font_extents;
}

font_extents::font_extents() noexcept
	: _Font_extents({ 0.0, 0.0, 0.0, 0.0, 0.0 }) {
}

font_extents::font_extents(font_extents&& other) noexcept
	: _Font_extents(move(other._Font_extents)) {
	other._Font_extents = { };
}

font_extents& font_extents::operator=(font_extents&& other) noexcept {
	if (this != &other) {
		_Font_extents = move(other._Font_extents);

		other._Font_extents = { };
	}
	return *this;
}

font_extents::font_extents(double ascent, double descent, double height) noexcept
	: _Font_extents({ ascent, descent, height, 0.0, 0.0 }) {
}

void font_extents::ascent(double value) noexcept {
	_Font_extents.ascent = value;
}

void font_extents::descent(double value) noexcept {
	_Font_extents.descent = value;
}

void font_extents::height(double value) noexcept {
	_Font_extents.height = value;
}

double font_extents::ascent() const noexcept {
	return _Font_extents.ascent;
}

double font_extents::descent() const noexcept {
	return _Font_extents.descent;
}

double font_extents::height() const noexcept {
	return _Font_extents.height;
}
