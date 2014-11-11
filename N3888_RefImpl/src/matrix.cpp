#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"
#include <cmath>

using namespace std;
using namespace std::experimental::io2d;

matrix_2d::matrix_2d()
	: _M00{ 1.0 }
	, _M01{ 0.0 }
	, _M10{ 0.0 }
	, _M11{ 1.0 }
	, _M20{ 0.0 }
	, _M21{ 0.0 } {
}

matrix_2d::matrix_2d(double m00, double m01, double m10, double m11, double m20, double m21)
	: _M00{ m00 }
	, _M01{ m01 }
	, _M10{ m10 }
	, _M11{ m11 }
	, _M20{ m20 }
	, _M21{ m21 } {
}

matrix_2d matrix_2d::init_identity() {
	return{ 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
}

matrix_2d matrix_2d::init_translate(const point& value) {
	return{ 1.0, 0.0, 0.0, 1.0, value.x(), value.y() };
}

matrix_2d matrix_2d::init_scale(const point& value) {
	return{ value.x(), 0.0, 0.0, value.y(), 0.0, 0.0 };
}

matrix_2d matrix_2d::init_rotate(double radians) {
	auto sine = sin(radians);
	auto cosine = cos(radians);
	return{ cosine, sine, -sine, cosine, 0.0, 0.0 };
}

matrix_2d matrix_2d::init_shear_x(double factor) {
	return{ 1.0, 0.0, factor, 1.0, 0.0, 0.0 };
}

matrix_2d matrix_2d::init_shear_y(double factor) {
	return{ 1.0, factor, 0.0, 1.0, 0.0, 0.0 };
}

matrix_2d& matrix_2d::translate(const point& value) {
	*this = init_translate(value) * (*this);
	return *this;
}

matrix_2d& matrix_2d::scale(const point& value) {
	*this = init_scale(value) * (*this);
	return *this;
}

matrix_2d& matrix_2d::rotate(double radians) {
	*this = init_rotate(radians) * (*this);
	return *this;
}

matrix_2d& matrix_2d::shear_x(double factor) {
	*this = init_shear_x(factor) * (*this);
	return *this;
}

matrix_2d& matrix_2d::shear_y(double factor) {
	*this = init_shear_y(factor) * (*this);
	return *this;
}

matrix_2d& matrix_2d::invert() {
	cairo_matrix_t cm{ _M00, _M01, _M10, _M11, _M20, _M21 };
	_Throw_if_failed_cairo_status_t(cairo_matrix_invert(&cm));
	_M00 = cm.xx;
	_M01 = cm.yx;
	_M10 = cm.xy;
	_M11 = cm.yy;
	_M20 = cm.x0;
	_M21 = cm.y0;
	return *this;
}

double matrix_2d::determinant() const {
	if (isnan(_M20) || isnan(_M21)) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MATRIX);
	}
	return _M00 * _M11 - _M01 * _M10;
}

point matrix_2d::transform_distance(const point& dist) const {
	return{ _M00 * dist.x() + _M10 * dist.y(), _M01 * dist.x() + _M11 * dist.y() };
}

point matrix_2d::transform_point(const point& pt) const {
	return transform_distance(pt) + point{ _M20, _M21 };
}

void matrix_2d::m00(double value) {
	_M00 = value;
}

void matrix_2d::m01(double value) {
	_M01 = value;
}

void matrix_2d::m10(double value) {
	_M10 = value;
}

void matrix_2d::m11(double value) {
	_M11 = value;
}

void matrix_2d::m20(double value) {
	_M20 = value;
}

void matrix_2d::m21(double value) {
	_M21 = value;
}

double matrix_2d::m00() const {
	return _M00;
}

double matrix_2d::m01() const {
	return _M01;
}

double matrix_2d::m10() const {
	return _M10;
}

double matrix_2d::m11() const {
	return _M11;
}

double matrix_2d::m20() const {
	return _M20;
}

double matrix_2d::m21() const {
	return _M21;
}

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				matrix_2d operator*(const matrix_2d& lhs, const matrix_2d& rhs) {
					return matrix_2d{
						(lhs.m00() * rhs.m00()) + (lhs.m01() * rhs.m10()),
						(lhs.m00() * rhs.m01()) + (lhs.m01() * rhs.m11()),
						(lhs.m10() * rhs.m00()) + (lhs.m11() * rhs.m10()),
						(lhs.m10() * rhs.m01()) + (lhs.m11() * rhs.m11()),
						(lhs.m20() * rhs.m00()) + (lhs.m21() * rhs.m10()) + lhs.m20(),
						(lhs.m20() * rhs.m01()) + (lhs.m21() * rhs.m11()) + lhs.m21()
					};
				}

				matrix_2d& operator*=(matrix_2d& lhs, const matrix_2d& rhs) {
					lhs = lhs * rhs;
					return lhs;
				}

				bool operator==(const matrix_2d& lhs, const matrix_2d& rhs) {
					return
						lhs.m00() == rhs.m00() &&
						lhs.m01() == rhs.m01() &&
						lhs.m10() == rhs.m10() &&
						lhs.m11() == rhs.m11() &&
						lhs.m20() == rhs.m20() &&
						lhs.m21() == rhs.m21();
				}

				bool operator!=(const matrix_2d& lhs, const matrix_2d& rhs) {
					return !(lhs == rhs);
				}
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}
