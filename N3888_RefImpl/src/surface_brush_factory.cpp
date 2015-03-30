#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

surface_brush_factory::surface_brush_factory()
	: _Brush_type(brush_type::surface)
	, _Surface(image_surface(format::argb32, 1, 1)) {
}

surface_brush_factory::surface_brush_factory(surface_brush_factory& other)
	: _Brush_type()
	, _Surface(image_surface(format::argb32, 1, 1)) {
	_Brush_type = other._Brush_type;
	_Surface = _Surface_create_image_surface_copy(other._Surface);
}

surface_brush_factory& surface_brush_factory::operator=(surface_brush_factory& other) {
	if (this != &other) {
		_Brush_type = other._Brush_type;
		_Surface = _Surface_create_image_surface_copy(other._Surface);
	}
	return *this;
}

surface_brush_factory::surface_brush_factory(surface_brush_factory&& other)
	: _Brush_type()
	, _Surface(image_surface(format::argb32, 1, 1)) {
	_Brush_type = move(other._Brush_type);
	_Surface = move(other._Surface);
}

surface_brush_factory& surface_brush_factory::operator=(surface_brush_factory&& other) {
	if (this != &other) {
		_Brush_type = move(other._Brush_type);
		_Surface = move(other._Surface);
	}
	return *this;
}

surface_brush_factory::surface_brush_factory(::std::experimental::io2d::surface& s)
	: _Brush_type(brush_type::surface)
	, _Surface(image_surface(format::argb32, 1, 1)) {
	_Surface = _Surface_create_image_surface_copy(s);
}

image_surface surface_brush_factory::surface(::std::experimental::io2d::surface& s) {
	auto sfc = _Surface_create_image_surface_copy(s);
	auto result = move(_Surface);
	_Surface = move(sfc);
	return move(result);
}

const image_surface& surface_brush_factory::surface() const {
	return _Surface;
}
