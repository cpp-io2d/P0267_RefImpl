#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

point point::operator+=(const point& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

point point::operator-=(const point& rhs) {
    x -= rhs.x;
    y -= rhs.y;
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

point std::experimental::drawing::operator+(const point& lhs) {
    return lhs;
}

point std::experimental::drawing::operator+(const point& lhs, const point& rhs) {
    return point{ lhs.x + rhs.x, lhs.y + rhs.y };
}

point std::experimental::drawing::operator-(const point& lhs) {
    return point{ -lhs.x, -lhs.y };
}

point std::experimental::drawing::operator-(const point& lhs, const point& rhs) {
    return point{ lhs.x - rhs.x, lhs.y - rhs.y };
}

point std::experimental::drawing::operator*(const point& lhs, const point& rhs) {
    return point{ lhs.x * rhs.x, lhs.y * rhs.y };
}

point std::experimental::drawing::operator*(const point& lhs, double rhs) {
    return point{ lhs.x * rhs, lhs.y * rhs };
}

point std::experimental::drawing::operator/(const point& lhs, const point& rhs) {
    return point{ lhs.x / rhs.x, lhs.y / rhs.y };
}

point std::experimental::drawing::operator/(const point& lhs, double rhs) {
    return point{ lhs.x / rhs, lhs.y / rhs };
}
