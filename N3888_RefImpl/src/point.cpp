#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

point::point(point&& other) noexcept
	: _X(move(other._X))
	, _Y(move(other._Y)) {
	other._X = 0.0;
	other._Y = 0.0;
}

point& point::operator=(point&& other) noexcept {
	if (this != &other) {
		_X = move(other._X);
		_Y = move(other._Y);
		other._X = 0.0;
		other._Y = 0.0;
	}
	return *this;
}

point::point(double x, double y) noexcept
	: _X(x)
	, _Y(y) {
}

void point::x(double value) noexcept {
	_X = value;
}

void point::y(double value) noexcept {
	_Y = value;
}

double point::x() const noexcept {
	return _X;
}

double point::y() const noexcept {
	return _Y;
}

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				bool operator==(const point& lhs, const point& rhs) noexcept {
					return _Almost_equal_relative(lhs.x(), rhs.x()) && _Almost_equal_relative(lhs.y(), rhs.y());
				}

				bool operator!=(const point& lhs, const point& rhs) noexcept {
					return !(lhs == rhs);
				}

				point operator+(const point& lhs) {
					return lhs;
				}

				point operator+(const point& lhs, const point& rhs) {
					return point{ lhs.x() + rhs.x(), lhs.y() + rhs.y() };
				}

				point operator+(const point& lhs, double rhs) {
					return point{ lhs.x() + rhs, lhs.y() + rhs };
				}

				point operator+(double lhs, const point& rhs) {
					return point{ lhs + rhs.x(), lhs + rhs.y() };
				}

				point& operator+=(point& lhs, const point& rhs) {
					lhs.x(lhs.x() + rhs.x());
					lhs.y( lhs.y() + rhs.y());
					return lhs;
				}

				point& operator+=(point& lhs, double rhs) {
					lhs.x(lhs.x() + rhs);
					lhs.x(lhs.y() + rhs);
					return lhs;
				}

				point operator-(const point& lhs) {
					return point{ -lhs.x(), -lhs.y() };
				}

				point operator-(const point& lhs, const point& rhs) {
					return point{ lhs.x() - rhs.x(), lhs.y() - rhs.y() };
				}

				point operator-(const point& lhs, double rhs) {
					return point{ lhs.x() - rhs, lhs.y() - rhs };
				}

				point operator-(double lhs, const point& rhs) {
					return point{ lhs - rhs.x(), lhs - rhs.y() };
				}

				point& operator-=(point& lhs, const point& rhs) {
					lhs.x(lhs.x() - rhs.x());
					lhs.y(lhs.y() - rhs.y());
					return lhs;
				}

				point& operator-=(point& lhs, double rhs) {
					lhs.x(lhs.x() - rhs);
					lhs.y(lhs.y() - rhs);
					return lhs;
				}

				point operator*(const point& lhs, const point& rhs) {
					return point{ lhs.x() * rhs.x(), lhs.y() * rhs.y() };
				}

				point operator*(const point& lhs, double rhs) {
					return point{ lhs.x() * rhs, lhs.y() * rhs };
				}

				point operator*(double lhs, const point& rhs) {
					return point{ lhs * rhs.x(), lhs * rhs.y() };
				}

				point& operator*=(point& lhs, const point& rhs) {
					lhs.x(lhs.x() * rhs.x());
					lhs.y(lhs.y() * rhs.y());
					return lhs;
				}

				point& operator*=(point& lhs, double rhs) {
					lhs.x(lhs.x() * rhs);
					lhs.y(lhs.y() * rhs);
					return lhs;
				}

				point operator/(const point& lhs, const point& rhs) {
					return point{ lhs.x() / rhs.x(), lhs.y() / rhs.y() };
				}

				point operator/(const point& lhs, double rhs) {
					return point{ lhs.x() / rhs, lhs.y() / rhs };
				}

				point operator/(double lhs, const point& rhs) {
					return point{ lhs / rhs.x(), lhs / rhs.y() };
				}

				point& operator/=(point& lhs, const point& rhs) {
					lhs.x(lhs.x() / rhs.x());
					lhs.y(lhs.y() / rhs.y());
					return lhs;
				}

				point& operator/=(point& lhs, double rhs) {
					lhs.x(lhs.x() / rhs);
					lhs.y(lhs.y() / rhs);
					return lhs;
				}
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}
