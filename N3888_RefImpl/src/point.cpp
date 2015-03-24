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
					return lhs.x() == rhs.x() && lhs.y() == rhs.y();
				}

				bool operator!=(const point& lhs, const point& rhs) noexcept {
					return !(lhs == rhs);
				}

				point operator+(const point& lhs) noexcept {
					return lhs;
				}

				point operator+(const point& lhs, const point& rhs) noexcept {
					return point{ lhs.x() + rhs.x(), lhs.y() + rhs.y() };
				}

				point& point::operator+=(const point& rhs) noexcept {
					_X = _X + rhs.x();
					_Y = _Y + rhs.y();
					return *this;
				}

				point operator-(const point& lhs) noexcept {
					return point{ -lhs.x(), -lhs.y() };
				}

				point operator-(const point& lhs, const point& rhs) noexcept {
					return point{ lhs.x() - rhs.x(), lhs.y() - rhs.y() };
				}

				point& point::operator-=(const point& rhs) noexcept {
					_X = _X - rhs.x();
					_Y = _Y - rhs.y();
					return *this;
				}
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}
