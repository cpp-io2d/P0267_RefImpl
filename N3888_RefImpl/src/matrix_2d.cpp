#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"
#include <cmath>

using namespace std;
using namespace std::experimental::io2d;

//matrix_2d::matrix_2d() noexcept
//	: _M00{ 1.0 }
//	, _M01{ 0.0 }
//	, _M10{ 0.0 }
//	, _M11{ 1.0 }
//	, _M20{ 0.0 }
//	, _M21{ 0.0 } {
//}
//
//matrix_2d::matrix_2d(matrix_2d&& other) noexcept
//	: _M00(move(other._M00))
//	, _M01(move(other._M01))
//	, _M10(move(other._M10))
//	, _M11(move(other._M11))
//	, _M20(move(other._M20))
//	, _M21(move(other._M21)) {
//	other._M00 = 0.0;
//	other._M01 = 0.0;
//	other._M10 = 0.0;
//	other._M11 = 0.0;
//	other._M20 = 0.0;
//	other._M21 = 0.0;
//}
//
//matrix_2d& matrix_2d::operator=(matrix_2d&& other) noexcept {
//	if (this != &other) {
//		_M00 = move(other._M00);
//		_M01 = move(other._M01);
//		_M10 = move(other._M10);
//		_M11 = move(other._M11);
//		_M20 = move(other._M20);
//		_M21 = move(other._M21);
//
//		other._M00 = 0.0;
//		other._M01 = 0.0;
//		other._M10 = 0.0;
//		other._M11 = 0.0;
//		other._M20 = 0.0;
//		other._M21 = 0.0;
//	}
//	return *this;
//}
//
//matrix_2d::matrix_2d(double m00, double m01, double m10, double m11, double m20, double m21) noexcept
//	: _M00{ m00 }
//	, _M01{ m01 }
//	, _M10{ m10 }
//	, _M11{ m11 }
//	, _M20{ m20 }
//	, _M21{ m21 } {
//}

//matrix_2d matrix_2d::init_identity() noexcept {
//	return{ 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
//}
//
//matrix_2d matrix_2d::init_translate(const vector_2d& value) noexcept {
//	return{ 1.0, 0.0, 0.0, 1.0, value.x(), value.y() };
//}
//
//matrix_2d matrix_2d::init_scale(const vector_2d& value) noexcept {
//	return{ value.x(), 0.0, 0.0, value.y(), 0.0, 0.0 };
//}

matrix_2d matrix_2d::init_rotate(double radians) noexcept {
	auto sine = sin(radians);
	auto cosine = cos(radians);
	return{ cosine, sine, -sine, cosine, 0.0, 0.0 };
}
//
//matrix_2d matrix_2d::init_shear_x(double factor) noexcept {
//	return{ 1.0, 0.0, factor, 1.0, 0.0, 0.0 };
//}
//
//matrix_2d matrix_2d::init_shear_y(double factor) noexcept {
//	return{ 1.0, factor, 0.0, 1.0, 0.0, 0.0 };
//}

matrix_2d& matrix_2d::translate(const vector_2d& value) noexcept {
	*this = init_translate(value) * (*this);
	return *this;
}

matrix_2d& matrix_2d::scale(const vector_2d& value) noexcept {
	*this = init_scale(value) * (*this);
	return *this;
}

matrix_2d& matrix_2d::rotate(double radians) noexcept {
	*this = init_rotate(radians) * (*this);
	return *this;
}

matrix_2d& matrix_2d::shear_x(double factor) noexcept {
	*this = init_shear_x(factor) * (*this);
	return *this;
}

matrix_2d& matrix_2d::shear_y(double factor) noexcept {
	*this = init_shear_y(factor) * (*this);
	return *this;
}

matrix_2d& matrix_2d::invert() {
	error_code ec;
	auto lm00 = _M00;
	auto lm01 = _M01;
	auto lm10 = _M10;
	auto lm11 = _M11;
	auto lm20 = _M20;
	auto lm21 = _M21;

	invert(ec);
	if (static_cast<bool>(ec)) {
		_M00 = lm00;
		_M01 = lm01;
		_M10 = lm10;
		_M11 = lm11;
		_M20 = lm20;
		_M21 = lm21;
		throw system_error(ec);
	}
	return *this;
}

matrix_2d& matrix_2d::invert(error_code& ec) noexcept {
	// Get the determinant for this matrix_2d.
	auto det = determinant();

	if (det == 0.0) {
		// A matrix_2d with a determinant of 0.0 is not invertible.
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MATRIX);
		return *this;
	}

	double
		adjugateM00, adjugateM01,
		adjugateM10, adjugateM11,
		adjugateM20, adjugateM21;

	// Calculates the determinant of a 2x2 row-major matrix.
	auto determinant2x2 = [](double dm00, double dm01, double dm10, double dm11) noexcept { return dm00 * dm11 - dm01 * dm10; };

	// The values for the third column of this matrix_2d.
	const double cM02 = 0.0, cM12 = 0.0, cM22 = 1.0;

	adjugateM00 = determinant2x2(_M11, cM12, _M21, cM22);
	adjugateM01 = -determinant2x2(_M01, cM02, _M21, cM22);
	adjugateM10 = -determinant2x2(_M10, cM12, _M20, cM22);
	adjugateM11 = determinant2x2(_M00, cM02, _M20, cM22);
	adjugateM20 = determinant2x2(_M10, _M11, _M20, _M21);
	adjugateM21 = -determinant2x2(_M00, _M01, _M20, _M21);
	auto inverseDeterminant = 1.0 / det;
	assert("inverse M02 should equal 0.0 " && _Almost_equal_relative(inverseDeterminant * determinant2x2(_M01, cM02, _M11, cM12), 0.0));
	assert("inverse M12 should equal 0.0 " && _Almost_equal_relative(inverseDeterminant * -determinant2x2(_M00, cM02, _M10, cM12), 0.0));
	assert("inverse M22 should equal 1.0 " && _Almost_equal_relative(inverseDeterminant * determinant2x2(_M00, _M01, _M10, _M11), 1.0));
	_M00 = inverseDeterminant * adjugateM00;
	_M01 = inverseDeterminant * adjugateM01;
	_M10 = inverseDeterminant * adjugateM10;
	_M11 = inverseDeterminant * adjugateM11;
	_M20 = inverseDeterminant * adjugateM20;
	_M21 = inverseDeterminant * adjugateM21;

	ec.clear();
	return *this;
}

void matrix_2d::swap(matrix_2d& other) {
	::std::swap(_M00, other._M00);
	::std::swap(_M01, other._M01);
	::std::swap(_M10, other._M10);
	::std::swap(_M11, other._M11);
	::std::swap(_M20, other._M20);
	::std::swap(_M21, other._M21);
}

//double matrix_2d::determinant() const {
//	if (!isfinite(_M00) || !isfinite(_M01) || !isfinite(_M10) || !isfinite(_M11) || !isfinite(_M20) || !isfinite(_M21)) {
//		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MATRIX);
//	}
//	return _M00 * _M11 - _M01 * _M10;
//}
//
//double matrix_2d::determinant(error_code& ec) const noexcept {
//	if (!isfinite(_M00) || !isfinite(_M01) || !isfinite(_M10) || !isfinite(_M11) || !isfinite(_M20) || !isfinite(_M21)) {
//		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MATRIX);
//		return numeric_limits<double>::quiet_NaN();
//	}
//	ec.clear();
//	return _M00 * _M11 - _M01 * _M10;
//}

void matrix_2d::m00(double value) noexcept {
	_M00 = value;
}

void matrix_2d::m01(double value) noexcept {
	_M01 = value;
}

void matrix_2d::m10(double value) noexcept {
	_M10 = value;
}

void matrix_2d::m11(double value) noexcept {
	_M11 = value;
}

void matrix_2d::m20(double value) noexcept {
	_M20 = value;
}

void matrix_2d::m21(double value) noexcept {
	_M21 = value;
}

bool matrix_2d::is_finite() const noexcept {
	if (!isfinite(_M00) || !isfinite(_M01) || !isfinite(_M10) || !isfinite(_M11) || !isfinite(_M20) || !isfinite(_M21)) {
		return false;
	}
	return true;
}

matrix_2d& matrix_2d::operator*=(const matrix_2d& rhs) noexcept {
	*this = *this * rhs;
	return *this;
}
