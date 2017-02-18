#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

void vector_2d::x(double value) noexcept {
	_X = value;
}

void vector_2d::y(double value) noexcept {
	_Y = value;
}

void vector_2d::swap(vector_2d& other) noexcept {
	::std::swap(_X, other._X);
	::std::swap(_Y, other._Y);
}

//void swap(vector_2d& lhs, vector_2d& rhs) noexcept {
//	lhs.swap(rhs);
//}
//
//double vector_2d::x() const noexcept {
//	return _X;
//}
//
//double vector_2d::y() const noexcept {
//	return _Y;
//}

double vector_2d::magnitude() const noexcept {
	return sqrt(_X * _X + _Y * _Y);
}

//constexpr double vector_2d::magnitude_squared() const noexcept {
//	return _X * _X + _Y * _Y;
//}

//constexpr double vector_2d::dot(const vector_2d& other) const noexcept {
//	return _X * other._X + _Y * other._Y;
//}

double vector_2d::angular_direction(const vector_2d& to) const noexcept {
	auto v = to - *this;
	return atan2(v._Y, v._X);
}

vector_2d vector_2d::to_unit() const noexcept {
	auto leng = magnitude();

	return vector_2d{ _X / leng, _Y / leng };
}

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif

#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}
