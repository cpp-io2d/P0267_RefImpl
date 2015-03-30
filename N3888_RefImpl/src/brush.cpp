#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

brush::native_handle_type brush::native_handle() const noexcept {
	return _Brush.get();
}

brush::brush(brush::native_handle_type nh) noexcept
	: _Brush(nh, &cairo_pattern_destroy)
	, _Brush_type(_Cairo_pattern_type_t_to_brush_type(cairo_pattern_get_type(nh)))
	, _Extend(::std::experimental::io2d::extend::default_extend)
	, _Filter(::std::experimental::io2d::filter::default_filter)
	, _Matrix(matrix_2d::init_identity()) {
}

brush::brush(brush&& other) noexcept
	: _Brush(move(other._Brush))
	, _Brush_type(move(other._Brush_type))
	, _Extend(move(other._Extend))
	, _Filter(move(other._Filter))
	, _Matrix(move(other._Matrix)) {
	other._Brush = nullptr;
}

brush& brush::operator=(brush&& other) noexcept {
	if (this != &other) {
		_Brush = move(other._Brush);
		_Brush_type = move(other._Brush_type);
		_Extend = move(other._Extend);
		_Filter = move(other._Filter);
		_Matrix = move(other._Matrix);
		other._Brush = nullptr;
	}

	return *this;
}

void brush::extend(::std::experimental::io2d::extend e) noexcept {
	_Extend = e;
}

void brush::filter(::std::experimental::io2d::filter f) noexcept {
	_Filter = f;
}

void brush::matrix(const matrix_2d& m) noexcept {
	_Matrix = m;
}

::std::experimental::io2d::extend brush::extend() const noexcept {
	return _Extend;
}

::std::experimental::io2d::filter brush::filter() const noexcept {
	return _Filter;
}

matrix_2d brush::matrix() const noexcept {
	return _Matrix;
}

brush_type brush::type() const noexcept {
	return _Brush_type;
}
