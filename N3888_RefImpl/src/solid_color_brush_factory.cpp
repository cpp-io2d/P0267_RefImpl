#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

solid_color_brush_factory::solid_color_brush_factory() noexcept
	: _Brush_type(brush_type::solid_color)
	, _Color(rgba_color::black()) {
}

solid_color_brush_factory::solid_color_brush_factory(solid_color_brush_factory&& other) noexcept
	: _Brush_type()
	, _Color() {
	_Brush_type = move(other._Brush_type);
	_Color = move(other._Color);
}

solid_color_brush_factory& solid_color_brush_factory::operator=(solid_color_brush_factory&& other) noexcept {
	if (this != &other) {
		_Brush_type = move(other._Brush_type);
		_Color = move(other._Color);
	}
	return *this;
}

solid_color_brush_factory::solid_color_brush_factory(const rgba_color& color) noexcept
	: _Brush_type(brush_type::solid_color)
	, _Color(color){
	assert(color.r() >= 0.0 && color.r() <= 1.0);
	assert(color.g() >= 0.0 && color.g() <= 1.0);
	assert(color.b() >= 0.0 && color.b() <= 1.0);
	assert(color.a() >= 0.0 && color.a() <= 1.0);
	_Color.r(_Clamp_to_normal(color.r()));
	_Color.g(_Clamp_to_normal(color.g()));
	_Color.b(_Clamp_to_normal(color.b()));
	_Color.a(_Clamp_to_normal(color.a()));
}

rgba_color solid_color_brush_factory::rgba() const noexcept {
	return _Color;
}

void solid_color_brush_factory::rgba(const rgba_color& color) noexcept {
	assert(color.r() >= 0.0 && color.r() <= 1.0);
	assert(color.g() >= 0.0 && color.g() <= 1.0);
	assert(color.b() >= 0.0 && color.b() <= 1.0);
	assert(color.a() >= 0.0 && color.a() <= 1.0);
	_Color = color;
	_Color.r(_Clamp_to_normal(color.r()));
	_Color.g(_Clamp_to_normal(color.g()));
	_Color.b(_Clamp_to_normal(color.b()));
	_Color.a(_Clamp_to_normal(color.a()));
}

double solid_color_brush_factory::red() const noexcept {
	return _Color.r();
}

void solid_color_brush_factory::red(double red) noexcept {
	assert(red >= 0.0 && red <= 1.0);
	_Color.r(_Clamp_to_normal(red));
}

double solid_color_brush_factory::green() const noexcept {
	return _Color.g();
}

void solid_color_brush_factory::green(double green) noexcept {
	assert(green >= 0.0 && green <= 1.0);
	_Color.g(_Clamp_to_normal(green));
}

double solid_color_brush_factory::blue() const noexcept {
	return _Color.b();
}

void solid_color_brush_factory::blue(double blue) noexcept {
	assert(blue >= 0.0 && blue <= 1.0);
	_Color.b(_Clamp_to_normal(blue));
}

double solid_color_brush_factory::alpha() const noexcept {
	return _Color.a();
}

void solid_color_brush_factory::alpha(double alpha) noexcept {
	assert(alpha >= 0.0 && alpha <= 1.0);
	_Color.a(_Clamp_to_normal(alpha));
}
