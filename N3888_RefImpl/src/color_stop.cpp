#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

color_stop::color_stop(double offset, const rgba_color& color)
	: _Offset(offset)
	, _Color(color) {
}

void color_stop::offset(double value) noexcept {
	_Offset = value;
}

void color_stop::color(const rgba_color& value) noexcept {
	_Color = value;
}

double color_stop::offset() const noexcept {
	return _Offset;
}

rgba_color color_stop::color() const noexcept {
	return _Color;
}

