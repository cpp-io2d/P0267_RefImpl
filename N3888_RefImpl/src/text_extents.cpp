#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

text_extents::native_handle_type text_extents::native_handle() {
	return &_Text_extents;
}

text_extents::text_extents()
	: _Text_extents({ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }) {
}

text_extents::text_extents(text_extents&& other)
	: _Text_extents() {
	_Text_extents = move(other._Text_extents);
	other._Text_extents = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
}

text_extents& text_extents::operator=(text_extents&& other) {
	if (this != &other) {
		_Text_extents = move(other._Text_extents);
		other._Text_extents = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
	}
	return *this;
}

text_extents::text_extents(double xBearing, double yBearing, double width, double height, double xAdvance, double yAdvance)
	: _Text_extents({ xBearing, yBearing, width, height, xAdvance, yAdvance }) {
}

void text_extents::x_bearing(double value) {
	_Text_extents.x_bearing = value;
}

void text_extents::y_bearing(double value) {
	_Text_extents.y_bearing = value;
}

void text_extents::width(double value) {
	_Text_extents.width = value;
}

void text_extents::height(double value) {
	_Text_extents.height = value;
}

void text_extents::x_advance(double value) {
	_Text_extents.x_advance = value;
}

void text_extents::y_advance(double value) {
	_Text_extents.y_advance = value;
}

double text_extents::x_bearing() const {
	return _Text_extents.x_bearing;
}

double text_extents::y_bearing() const {
	return _Text_extents.y_bearing;
}

double text_extents::width() const {
	return _Text_extents.width;
}

double text_extents::height() const {
	return _Text_extents.height;
}

double text_extents::x_advance() const {
	return _Text_extents.x_advance;
}

double text_extents::y_advance() const {
	return _Text_extents.y_advance;
}
