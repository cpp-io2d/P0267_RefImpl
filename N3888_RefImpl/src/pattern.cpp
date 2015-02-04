#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

pattern::native_handle_type pattern::native_handle() const {
	return _Pattern.get();
}

pattern::pattern(pattern::native_handle_type nh)
	: _Pattern(nh, &cairo_pattern_destroy)
	, _Pattern_type(_Cairo_pattern_type_t_to_pattern_type(cairo_pattern_get_type(nh)))
	, _Extend(extend::default_extend)
	, _Filter(filter::default_filter)
	, _Matrix(matrix_2d::init_identity()) {
}

pattern::pattern(pattern&& other)
	: _Pattern(move(other._Pattern))
	, _Pattern_type(move(other._Pattern_type))
	, _Extend(move(other._Extend))
	, _Filter(move(other._Filter))
	, _Matrix(move(other._Matrix)) {
	other._Pattern = nullptr;
}

pattern& pattern::operator=(pattern&& other) {
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

void pattern::extend(::std::experimental::io2d::extend e) {
	_Extend = e;
}

void pattern::filter(::std::experimental::io2d::filter f) {
	_Filter = f;
}

void pattern::matrix(const matrix_2d& m) {
	_Matrix = m;
}

extend pattern::extend() const {
	return _Extend;
}

filter pattern::filter() const {
	return _Filter;
}

matrix_2d pattern::matrix() const {
	return _Matrix;
}

pattern_type pattern::type() const {
	return _Pattern_type;
}
