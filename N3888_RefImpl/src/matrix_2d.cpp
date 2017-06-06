//#include "io2d.h"
//#include "xcairoenumhelpers.h"
//
//using namespace std;
//using namespace std::experimental::io2d;
//
//matrix_2d matrix_2d::init_rotate(double radians) noexcept {
//	auto sine = sin(radians);
//	auto cosine = cos(radians);
//	return{ cosine, -sine, sine, cosine, 0.0, 0.0 };
//}
//
//matrix_2d& matrix_2d::translate(const vector_2d& value) noexcept {
//	//*this = init_translate(value) * (*this);
//	*this = (*this)  * init_translate(value);
//	return *this;
//}
//
//matrix_2d& matrix_2d::scale(const vector_2d& value) noexcept {
//	//*this = init_scale(value) * (*this);
//	*this = init_scale(value) * (*this);
//	return *this;
//}
//
//matrix_2d& matrix_2d::rotate(double radians) noexcept {
//	//*this = init_rotate(radians) * (*this);
//	*this = (*this) * init_rotate(radians);
//	return *this;
//}
//
//matrix_2d& matrix_2d::shear_x(double factor) noexcept {
//	//*this = init_shear_x(factor) * (*this);
//	*this = (*this) * init_shear_x(factor);
//	return *this;
//}
//
//matrix_2d& matrix_2d::shear_y(double factor) noexcept {
//	//*this = init_shear_y(factor) * (*this);
//	*this = (*this) * init_shear_y(factor);
//	return *this;
//}
//
////matrix_2d matrix_2d::inverse() const noexcept {
////	// Get the determinant for this matrix_2d.
////	auto inverseDeterminant = 1.0 / determinant();
////
////	double
////		adjugateM00, adjugateM01,
////		adjugateM10, adjugateM11,
////		adjugateM20, adjugateM21;
////
////	// Calculates the determinant of a 2x2 row-major matrix.
////	auto determinant2x2 = [](double dm00, double dm01, double dm10, double dm11) noexcept { return dm00 * dm11 - dm01 * dm10; };
////
////	// The values for the third column of this matrix_2d.
////	const double cM02 = 0.0, cM12 = 0.0, cM22 = 1.0;
////
////	adjugateM00 = determinant2x2(_M11, cM12, _M21, cM22);
////	adjugateM01 = -determinant2x2(_M01, cM02, _M21, cM22);
////	adjugateM10 = -determinant2x2(_M10, cM12, _M20, cM22);
////	adjugateM11 = determinant2x2(_M00, cM02, _M20, cM22);
////	adjugateM20 = determinant2x2(_M10, _M11, _M20, _M21);
////	adjugateM21 = -determinant2x2(_M00, _M01, _M20, _M21);
////	//auto inverseDeterminant = 1.0 / det;
////	//assert("inverse M02 should equal 0.0 " && _Almost_equal_relative(inverseDeterminant * determinant2x2(_M01, cM02, _M11, cM12), 0.0));
////	//assert("inverse M12 should equal 0.0 " && _Almost_equal_relative(inverseDeterminant * -determinant2x2(_M00, cM02, _M10, cM12), 0.0));
////	//assert("inverse M22 should equal 1.0 " && _Almost_equal_relative(inverseDeterminant * determinant2x2(_M00, _M01, _M10, _M11), 1.0));
////	return matrix_2d{
////		inverseDeterminant * adjugateM00,
////		inverseDeterminant * adjugateM01,
////		inverseDeterminant * adjugateM10,
////		inverseDeterminant * adjugateM11,
////		inverseDeterminant * adjugateM20,
////		inverseDeterminant * adjugateM21
////	};
////}
////
////matrix_2d& matrix_2d::operator*=(const matrix_2d& rhs) noexcept {
////	*this = *this * rhs;
////	return *this;
////}
