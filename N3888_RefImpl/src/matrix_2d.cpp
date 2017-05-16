#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"
#include <cmath>

using namespace std;
using namespace std::experimental::io2d;

matrix_2d matrix_2d::init_rotate(double radians) noexcept {
	auto sine = sin(radians);
	auto cosine = cos(radians);
	return{ cosine, -sine, sine, cosine, 0.0, 0.0 };
}

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

matrix_2d& matrix_2d::operator*=(const matrix_2d& rhs) noexcept {
	*this = *this * rhs;
	return *this;
}
