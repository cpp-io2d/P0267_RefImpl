#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"
#include <cmath>

using namespace std;
using namespace std::experimental::io2d;

matrix_2d matrix_2d::init_identity() {
	return{ 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
}

matrix_2d matrix_2d::init_translate(const point& value) {
	return{ 1.0, 0.0, 0.0, 1.0, value.x, value.y };
}

matrix_2d matrix_2d::init_scale(const point& value) {
	return{ value.x, 0.0, 0.0, value.y, 0.0, 0.0 };
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
	cairo_matrix_t cm{ m00, m01, m10, m11, m20, m21 };
	_Throw_if_failed_cairo_status_t(cairo_matrix_invert(&cm));
	m00 = cm.xx;
	m01 = cm.yx;
	m10 = cm.xy;
	m11 = cm.yy;
	m20 = cm.x0;
	m21 = cm.y0;
	return *this;
}

double matrix_2d::determinant() const {
	if (isnan(m20) || isnan(m21)) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MATRIX);
	}
	return m00 * m11 - m01 * m10;
}

point matrix_2d::transform_distance(const point& dist) const {
	return{ m00 * dist.x + m10 * dist.y, m01 * dist.x + m11 * dist.y };
}

point matrix_2d::transform_point(const point& pt) const {
	return transform_distance(pt) + point{ m20, m21 };
}

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				matrix_2d operator*(const matrix_2d& lhs, const matrix_2d& rhs) {
					return matrix_2d{
						(lhs.m00 * rhs.m00) + (lhs.m01 * rhs.m10),
						(lhs.m00 * rhs.m01) + (lhs.m01 * rhs.m11),
						(lhs.m10 * rhs.m00) + (lhs.m11 * rhs.m10),
						(lhs.m10 * rhs.m01) + (lhs.m11 * rhs.m11),
						(lhs.m20 * rhs.m00) + (lhs.m21 * rhs.m10) + lhs.m20,
						(lhs.m20 * rhs.m01) + (lhs.m21 * rhs.m11) + lhs.m21
					};
				}

				matrix_2d& operator*=(matrix_2d& lhs, const matrix_2d& rhs) {
					lhs = lhs * rhs;
					return lhs;
				}

				bool operator==(const matrix_2d& lhs, const matrix_2d& rhs) {
					return
						lhs.m00 == rhs.m00 &&
						lhs.m01 == rhs.m01 &&
						lhs.m10 == rhs.m10 &&
						lhs.m11 == rhs.m11 &&
						lhs.m20 == rhs.m20 &&
						lhs.m21 == rhs.m21;
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
