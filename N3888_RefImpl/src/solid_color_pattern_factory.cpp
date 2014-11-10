#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

solid_color_pattern_factory::solid_color_pattern_factory()
	: _Lock()
	, _Pattern_type(pattern_type::solid_color)
	, _Extend(extend::default_extend)
	, _Filter(filter::default_filter)
	, _Matrix(matrix_2d::init_identity())
	, _Color(rgba_color::black) {
}

solid_color_pattern_factory::solid_color_pattern_factory(const solid_color_pattern_factory& other)
	: _Lock()
	, _Pattern_type()
	, _Extend()
	, _Filter()
	, _Matrix()
	, _Color() {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Pattern_type = other._Pattern_type;
	_Extend = other._Extend;
	_Filter = other._Filter;
	_Matrix = other._Matrix;
	_Color = other._Color;
}

solid_color_pattern_factory& solid_color_pattern_factory::operator=(const solid_color_pattern_factory& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Pattern_type = other._Pattern_type;
		_Extend = other._Extend;
		_Filter = other._Filter;
		_Matrix = other._Matrix;
		_Color = other._Color;
	}
	return *this;
}

solid_color_pattern_factory::solid_color_pattern_factory(solid_color_pattern_factory&& other)
	: _Lock()
	, _Pattern_type()
	, _Extend()
	, _Filter()
	, _Matrix()
	, _Color() {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Pattern_type = move(other._Pattern_type);
	_Extend = move(other._Extend);
	_Filter = move(other._Filter);
	_Matrix = move(other._Matrix);
	_Color = move(other._Color);
}

solid_color_pattern_factory& solid_color_pattern_factory::operator=(solid_color_pattern_factory&& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Pattern_type = move(other._Pattern_type);
		_Extend = move(other._Extend);
		_Filter = move(other._Filter);
		_Matrix = move(other._Matrix);
		_Color = move(other._Color);
	}
	return *this;
}

solid_color_pattern_factory::solid_color_pattern_factory(const rgba_color& color)
	: _Lock()
	, _Pattern_type(pattern_type::solid_color)
	, _Extend(extend::default_extend)
	, _Filter(filter::default_filter)
	, _Matrix(matrix_2d::init_identity())
	, _Color(color){
	assert(color.r >= 0.0 && color.r <= 1.0);
	assert(color.g >= 0.0 && color.g <= 1.0);
	assert(color.b >= 0.0 && color.b <= 1.0);
	assert(color.a >= 0.0 && color.a <= 1.0);
	_Color.r = _Clamp_to_normal(color.r);
	_Color.g = _Clamp_to_normal(color.g);
	_Color.b = _Clamp_to_normal(color.b);
	_Color.a = _Clamp_to_normal(color.a);
}

pattern solid_color_pattern_factory::get_pattern() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	unique_ptr<cairo_pattern_t, function<void(cairo_pattern_t*)>> pat(cairo_pattern_create_rgba(_Color.r, _Color.g, _Color.b, _Color.a), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));

	cairo_pattern_set_extend(pat.get(), _Extend_to_cairo_extend_t(_Extend));
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));
	cairo_pattern_set_filter(pat.get(), _Filter_to_cairo_filter_t(_Filter));
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));
	cairo_matrix_t mtrx{ _Matrix.m00(), _Matrix.m01(), _Matrix.m10(), _Matrix.m11(), _Matrix.m20(), _Matrix.m21() };
	cairo_pattern_set_matrix(pat.get(), &mtrx);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));

	auto pttn = pattern(pat.get());
	pat.release();
	return pttn;
}

void solid_color_pattern_factory::set_extend(extend e) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Extend = e;
}

extend solid_color_pattern_factory::get_extend() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Extend;
}

void solid_color_pattern_factory::set_filter(filter f) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Filter = f;
}

filter solid_color_pattern_factory::get_filter() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Filter;
}

void solid_color_pattern_factory::set_matrix(const matrix_2d& m) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Matrix = m;
}


matrix_2d solid_color_pattern_factory::get_matrix() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Matrix;
}

rgba_color solid_color_pattern_factory::get_rgba() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Color;
}

void solid_color_pattern_factory::set_rgba(const rgba_color& color) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	assert(color.r >= 0.0 && color.r <= 1.0);
	assert(color.g >= 0.0 && color.g <= 1.0);
	assert(color.b >= 0.0 && color.b <= 1.0);
	assert(color.a >= 0.0 && color.a <= 1.0);
	_Color = color;
	_Color.r = _Clamp_to_normal(color.r);
	_Color.g = _Clamp_to_normal(color.g);
	_Color.b = _Clamp_to_normal(color.b);
	_Color.a = _Clamp_to_normal(color.a);
}

double solid_color_pattern_factory::get_red() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Color.r;
}

void solid_color_pattern_factory::set_red(double red) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	assert(red >= 0.0 && red <= 1.0);
	_Color.r = _Clamp_to_normal(red);
}

double solid_color_pattern_factory::get_green() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Color.g;
}

void solid_color_pattern_factory::set_green(double green) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	assert(green >= 0.0 && green <= 1.0);
	_Color.g = _Clamp_to_normal(green);
}

double solid_color_pattern_factory::get_blue() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Color.b;
}

void solid_color_pattern_factory::set_blue(double blue) {
	assert(blue >= 0.0 && blue <= 1.0);
	_Color.b = _Clamp_to_normal(blue);
}

double solid_color_pattern_factory::get_alpha() const {
	return _Color.a;
}

void solid_color_pattern_factory::set_alpha(double alpha) {
	assert(alpha >= 0.0 && alpha <= 1.0);
	_Color.a = _Clamp_to_normal(alpha);
}
