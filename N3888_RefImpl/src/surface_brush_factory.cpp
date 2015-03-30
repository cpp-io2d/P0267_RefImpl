#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

surface_brush_factory::surface_brush_factory()
	: _Surface(image_surface(format::argb32, 1, 1)) {
}

//surface_brush_factory::surface_brush_factory(surface_brush_factory& other)
//	: _Surface(image_surface(format::argb32, 1, 1)) {
//	_Surface = _Surface_create_image_surface_copy(other._Surface);
//}
//
//surface_brush_factory& surface_brush_factory::operator=(surface_brush_factory& other) {
//	if (this != &other) {
//		_Surface = _Surface_create_image_surface_copy(other._Surface);
//	}
//	return *this;
//}

surface_brush_factory::surface_brush_factory(surface_brush_factory&& other)
	: _Surface(image_surface(format::argb32, 1, 1)) {
	_Surface = move(other._Surface);
}

surface_brush_factory& surface_brush_factory::operator=(surface_brush_factory&& other) {
	if (this != &other) {
		_Surface = move(other._Surface);
	}
	return *this;
}

surface_brush_factory::surface_brush_factory(::std::experimental::io2d::surface& s)
	: _Surface(image_surface(format::argb32, 1, 1)) {
	_Surface = _Surface_create_image_surface_copy(s);
}

image_surface surface_brush_factory::surface(::std::experimental::io2d::surface& s) {
	// Create an image_surface copy of the new surface.
	auto sfc = _Surface_create_image_surface_copy(s);
	// Move the old surface to a return value variable.
	auto result = move(_Surface);
	// Move the copy of the new surface to be the current surface
	_Surface = move(sfc);
	// Return the old surface.
	return move(result);
}

const image_surface& surface_brush_factory::surface() const {
	return _Surface;
}
