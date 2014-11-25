#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

surface_pattern_factory::surface_pattern_factory()
	: _Lock()
	, _Pattern_type(pattern_type::surface)
	, _Extend(extend::default_extend)
	, _Filter(filter::default_filter)
	, _Matrix(matrix_2d::init_identity())
	, _Surface(image_surface(format::argb32, 1, 1)) {
}

surface_pattern_factory::surface_pattern_factory(surface_pattern_factory& other)
	: _Lock()
	, _Pattern_type()
	, _Extend()
	, _Filter()
	, _Matrix()
	, _Surface(image_surface(format::argb32, 1, 1)) {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Pattern_type = other._Pattern_type;
	_Extend = other._Extend;
	_Filter = other._Filter;
	_Matrix = other._Matrix;
	_Surface = _Surface_create_image_surface_copy(other._Surface);
}

surface_pattern_factory& surface_pattern_factory::operator=(surface_pattern_factory& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Pattern_type = other._Pattern_type;
		_Extend = other._Extend;
		_Filter = other._Filter;
		_Matrix = other._Matrix;
		_Surface = _Surface_create_image_surface_copy(other._Surface);
	}
	return *this;
}

surface_pattern_factory::surface_pattern_factory(surface_pattern_factory&& other)
	: _Lock()
	, _Pattern_type()
	, _Extend()
	, _Filter()
	, _Matrix()
	, _Surface(image_surface(format::argb32, 1, 1)) {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Pattern_type = move(other._Pattern_type);
	_Extend = move(other._Extend);
	_Filter = move(other._Filter);
	_Matrix = move(other._Matrix);
	_Surface = move(other._Surface);
}

surface_pattern_factory& surface_pattern_factory::operator=(surface_pattern_factory&& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Pattern_type = move(other._Pattern_type);
		_Extend = move(other._Extend);
		_Filter = move(other._Filter);
		_Matrix = move(other._Matrix);
		_Surface = move(other._Surface);
	}
	return *this;
}

surface_pattern_factory::surface_pattern_factory(surface& s)
	: _Lock()
	, _Pattern_type(pattern_type::surface)
	, _Extend(extend::default_extend)
	, _Filter(filter::default_filter)
	, _Matrix(matrix_2d::init_identity())
	, _Surface(image_surface(format::argb32, 1, 1)) {
	_Surface = _Surface_create_image_surface_copy(s);
}

void surface_pattern_factory::set_extend(extend e) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Extend = e;
}

extend surface_pattern_factory::get_extend() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Extend;
}

void surface_pattern_factory::set_filter(filter f) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Filter = f;
}

filter surface_pattern_factory::get_filter() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Filter;
}

void surface_pattern_factory::set_matrix(const matrix_2d& m) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Matrix = m;
}


matrix_2d surface_pattern_factory::get_matrix() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Matrix;
}

image_surface surface_pattern_factory::set_surface(surface& s) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	auto result = move(_Surface);
	_Surface = _Surface_create_image_surface_copy(s);
	return move(result);
}

const image_surface& surface_pattern_factory::get_surface() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Surface;
}
