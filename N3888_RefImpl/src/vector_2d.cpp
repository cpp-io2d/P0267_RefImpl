#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

vector_2d::vector_2d(vector_2d&& other) noexcept
	: _X(move(other._X))
	, _Y(move(other._Y)) {
	other._X = 0.0;
	other._Y = 0.0;
}

vector_2d& vector_2d::operator=(vector_2d&& other) noexcept {
	if (this != &other) {
		_X = move(other._X);
		_Y = move(other._Y);
		other._X = 0.0;
		other._Y = 0.0;
	}
	return *this;
}

vector_2d::vector_2d(double x, double y) noexcept
	: _X(x)
	, _Y(y) {
}

void vector_2d::x(double value) noexcept {
	_X = value;
}

void vector_2d::y(double value) noexcept {
	_Y = value;
}

double vector_2d::x() const noexcept {
	return _X;
}

double vector_2d::y() const noexcept {
	return _Y;
}

double vector_2d::length() const noexcept {
	return sqrt(_X * _X + _Y * _Y);
}

double vector_2d::dot(const vector_2d& other) const noexcept {
	return _X * other._X + _Y * other._Y;
}

vector_2d vector_2d::to_unit() const noexcept {
	auto leng = length();

	return vector_2d{ _X / leng, _Y / leng };
}

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				bool operator==(const vector_2d& lhs, const vector_2d& rhs) noexcept {
					return lhs.x() == rhs.x() && lhs.y() == rhs.y();
				}

				bool operator!=(const vector_2d& lhs, const vector_2d& rhs) noexcept {
					return !(lhs == rhs);
				}

				vector_2d operator+(const vector_2d& lhs) noexcept {
					return lhs;
				}

				vector_2d operator+(const vector_2d& lhs, const vector_2d& rhs) noexcept {
					return vector_2d{ lhs.x() + rhs.x(), lhs.y() + rhs.y() };
				}

				vector_2d& vector_2d::operator+=(const vector_2d& rhs) noexcept {
					_X = _X + rhs.x();
					_Y = _Y + rhs.y();
					return *this;
				}

				vector_2d operator-(const vector_2d& lhs) noexcept {
					return vector_2d{ -lhs.x(), -lhs.y() };
				}

				vector_2d operator-(const vector_2d& lhs, const vector_2d& rhs) noexcept {
					return vector_2d{ lhs.x() - rhs.x(), lhs.y() - rhs.y() };
				}

				vector_2d& vector_2d::operator-=(const vector_2d& rhs) noexcept {
					_X = _X - rhs.x();
					_Y = _Y - rhs.y();
					return *this;
				}

				vector_2d& vector_2d::operator*=(double rhs) noexcept {
					_X *= rhs;
					_Y *= rhs;
					return *this;
				}

				vector_2d operator*(const vector_2d& lhs, double rhs) noexcept{
					return vector_2d{ lhs.x() * rhs, lhs.y() * rhs };
				}

				vector_2d operator*(double lhs, const vector_2d& rhs) noexcept{
					return vector_2d{ lhs * rhs.x(), lhs * rhs.y() };
				}

#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}
