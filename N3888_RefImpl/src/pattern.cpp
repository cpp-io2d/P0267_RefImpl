#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

pattern::native_handle_type pattern::native_handle() const noexcept {
	return _Pattern.get();
}

pattern::pattern(pattern::native_handle_type nh) noexcept
	: _Pattern(nh, &cairo_pattern_destroy)
	, _Pattern_type(_Cairo_pattern_type_t_to_pattern_type(cairo_pattern_get_type(nh)))
	, _Extend(::std::experimental::io2d::extend::default_extend)
	, _Filter(::std::experimental::io2d::filter::default_filter)
	, _Matrix(matrix_2d::init_identity()) {
}

pattern::pattern(pattern&& other) noexcept
	: _Pattern(move(other._Pattern))
	, _Pattern_type(move(other._Pattern_type))
	, _Extend(move(other._Extend))
	, _Filter(move(other._Filter))
	, _Matrix(move(other._Matrix)) {
	other._Pattern = nullptr;
}

pattern& pattern::operator=(pattern&& other) noexcept {
	if (this != &other) {
		_Pattern = move(other._Pattern);
		_Pattern_type = move(other._Pattern_type);
		_Extend = move(other._Extend);
		_Filter = move(other._Filter);
		_Matrix = move(other._Matrix);
		other._Pattern = nullptr;
	}

	return *this;
}

void pattern::extend(::std::experimental::io2d::extend e) noexcept {
	_Extend = e;
}

void pattern::filter(::std::experimental::io2d::filter f) noexcept {
	_Filter = f;
}

void pattern::matrix(const matrix_2d& m) noexcept {
	_Matrix = m;
}

::std::experimental::io2d::extend pattern::extend() const noexcept {
	return _Extend;
}

::std::experimental::io2d::filter pattern::filter() const noexcept {
	return _Filter;
}

matrix_2d pattern::matrix() const noexcept {
	return _Matrix;
}

pattern_type pattern::type() const noexcept {
	return _Pattern_type;
}
