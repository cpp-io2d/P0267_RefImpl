#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

solid_color_brush_factory::solid_color_brush_factory() noexcept
	: _Color(rgba_color::black()) {
}

solid_color_brush_factory::solid_color_brush_factory(solid_color_brush_factory&& other) noexcept
	: _Color() {
	_Color = move(other._Color);
}

solid_color_brush_factory& solid_color_brush_factory::operator=(solid_color_brush_factory&& other) noexcept {
	if (this != &other) {
		_Color = move(other._Color);
	}
	return *this;
}

solid_color_brush_factory::solid_color_brush_factory(const rgba_color& color) noexcept
	: _Color(color){
	assert(color.r() >= 0.0 && color.r() <= 1.0);
	assert(color.g() >= 0.0 && color.g() <= 1.0);
	assert(color.b() >= 0.0 && color.b() <= 1.0);
	assert(color.a() >= 0.0 && color.a() <= 1.0);
}

void solid_color_brush_factory::color(const rgba_color& color) noexcept {
	assert(color.r() >= 0.0 && color.r() <= 1.0);
	assert(color.g() >= 0.0 && color.g() <= 1.0);
	assert(color.b() >= 0.0 && color.b() <= 1.0);
	assert(color.a() >= 0.0 && color.a() <= 1.0);
	_Color = color;
}

rgba_color solid_color_brush_factory::color() const noexcept{
	return _Color;
}
