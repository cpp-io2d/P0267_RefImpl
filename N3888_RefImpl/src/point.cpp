#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

point point::operator+=(const point& rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

point point::operator+=(double rhs) {
	x += rhs;
	y += rhs;
	return *this;
}

point point::operator-=(const point& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

point point::operator-=(double rhs) {
	x -= rhs;
	y -= rhs;
	return *this;
}

point point::operator*=(const point& rhs) {
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

point point::operator*=(double rhs) {
	x *= rhs;
	y *= rhs;
	return *this;
}

point point::operator/=(const point& rhs) {
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

point point::operator/=(double rhs) {
	x /= rhs;
	y /= rhs;
	return *this;
}

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				point operator+(const point& lhs) {
					return lhs;
				}

				point operator+(const point& lhs, const point& rhs) {
					return point{ lhs.x + rhs.x, lhs.y + rhs.y };
				}

				point operator+(const point& lhs, double rhs) {
					return point{ lhs.x + rhs, lhs.y + rhs };
				}

				point operator-(const point& lhs) {
					return point{ -lhs.x, -lhs.y };
				}

				point operator-(const point& lhs, const point& rhs) {
					return point{ lhs.x - rhs.x, lhs.y - rhs.y };
				}

				point operator-(const point& lhs, double rhs) {
					return point{ lhs.x - rhs, lhs.y - rhs };
				}

				point operator*(const point& lhs, const point& rhs) {
					return point{ lhs.x * rhs.x, lhs.y * rhs.y };
				}

				point operator*(const point& lhs, double rhs) {
					return point{ lhs.x * rhs, lhs.y * rhs };
				}

				point operator/(const point& lhs, const point& rhs) {
					return point{ lhs.x / rhs.x, lhs.y / rhs.y };
				}

				point operator/(const point& lhs, double rhs) {
					return point{ lhs.x / rhs, lhs.y / rhs };
				}

				bool operator==(const point& lhs, const point& rhs) {
					return lhs.x == rhs.x && lhs.y == rhs.y;
				}
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}
