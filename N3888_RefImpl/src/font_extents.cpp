#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

font_extents::native_handle_type font_extents::native_handle() {
	return &_Font_extents;
}

font_extents::font_extents()
	: _Font_extents({ 0.0, 0.0, 0.0, 0.0, 0.0 }) {
}

font_extents::font_extents(font_extents&& other)
	: _Font_extents(move(other._Font_extents)) {
	other._Font_extents = { };
}

font_extents& font_extents::operator=(font_extents&& other) {
	if (this != &other) {
		_Font_extents = move(other._Font_extents);

		other._Font_extents = { };
	}
	return *this;
}

font_extents::font_extents(double ascent, double descent, double height, double maxXAdvance, double maxYAdvance)
	: _Font_extents({ ascent, descent, height, maxXAdvance, maxYAdvance }) {
}

void font_extents::ascent(double value) {
	_Font_extents.ascent = value;
}

void font_extents::descent(double value) {
	_Font_extents.descent = value;
}

void font_extents::height(double value) {
	_Font_extents.height = value;
}

void font_extents::max_x_advance(double value) {
	_Font_extents.max_x_advance = value;
}

void font_extents::max_y_advance(double value) {
	_Font_extents.max_y_advance = value;
}

double font_extents::ascent() const {
	return _Font_extents.ascent;
}

double font_extents::descent() const {
	return _Font_extents.descent;
}

double font_extents::height() const {
	return _Font_extents.height;
}

double font_extents::max_x_advance() const {
	return _Font_extents.max_x_advance;
}

double font_extents::max_y_advance() const {
	return _Font_extents.max_y_advance;
}
