#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

surface_brush_factory::surface_brush_factory() noexcept
	: _Surface() {
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

surface_brush_factory::surface_brush_factory(surface_brush_factory&& other) noexcept
	: _Surface(move(other._Surface)) {
}

surface_brush_factory& surface_brush_factory::operator=(surface_brush_factory&& other) noexcept {
	if (this != &other) {
		_Surface = move(other._Surface);
	}
	return *this;
}

surface_brush_factory::surface_brush_factory(::std::experimental::io2d::surface& s)
	: _Surface() {
	_Surface = make_unique<image_surface>(_Surface_create_image_surface_copy(s));
}

void surface_brush_factory::surface(::std::experimental::io2d::surface& s) {
	// Create an image_surface copy of the new surface.
	auto sfc = _Surface_create_image_surface_copy(s);
	// Move the copy of the new surface to be the current surface
	_Surface = make_unique<image_surface>(move(sfc));
}

void surface_brush_factory::surface(::std::experimental::io2d::surface& s, ::std::error_code & ec) noexcept {
	image_surface sfc{format::argb32, 1, 1, ec};
	if (static_cast<bool>(ec)) {
		return;
	}

	// Create an image_surface copy of the new surface.
	_Surface_create_image_surface_copy(s, sfc, ec);

	if (static_cast<bool>(ec)) {
		return;
	}

	// Move the copy of the new surface to be the current surface
	try {
		auto heapSfc = make_unique<image_surface>(move(sfc));
		swap(heapSfc, _Surface);
	}
	catch (bad_alloc) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	ec.clear();
}

bool surface_brush_factory::has_surface() const noexcept {
	return _Surface.get() != nullptr;
}

const image_surface& surface_brush_factory::surface() const {
	return *_Surface.get();
}
