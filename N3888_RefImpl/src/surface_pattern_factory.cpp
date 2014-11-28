#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

surface_pattern_factory::surface_pattern_factory()
	: _Lock()
	, _Pattern_type(pattern_type::surface)
	, _Surface(image_surface(format::argb32, 1, 1)) {
}

surface_pattern_factory::surface_pattern_factory(surface_pattern_factory& other)
	: _Lock()
	, _Pattern_type()
	, _Surface(image_surface(format::argb32, 1, 1)) {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Pattern_type = other._Pattern_type;
	_Surface = _Surface_create_image_surface_copy(other._Surface);
}

surface_pattern_factory& surface_pattern_factory::operator=(surface_pattern_factory& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Pattern_type = other._Pattern_type;
		_Surface = _Surface_create_image_surface_copy(other._Surface);
	}
	return *this;
}

surface_pattern_factory::surface_pattern_factory(surface_pattern_factory&& other)
	: _Lock()
	, _Pattern_type()
	, _Surface(image_surface(format::argb32, 1, 1)) {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Pattern_type = move(other._Pattern_type);
	_Surface = move(other._Surface);
}

surface_pattern_factory& surface_pattern_factory::operator=(surface_pattern_factory&& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Pattern_type = move(other._Pattern_type);
		_Surface = move(other._Surface);
	}
	return *this;
}

surface_pattern_factory::surface_pattern_factory(surface& s)
	: _Lock()
	, _Pattern_type(pattern_type::surface)
	, _Surface(image_surface(format::argb32, 1, 1)) {
	_Surface = _Surface_create_image_surface_copy(s);
}

image_surface surface_pattern_factory::set_surface(surface& s) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	auto sfc = _Surface_create_image_surface_copy(s);
	auto result = move(_Surface);
	_Surface = move(sfc);
	return move(result);
}

const image_surface& surface_pattern_factory::get_surface() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Surface;
}
