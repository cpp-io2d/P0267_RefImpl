#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

double vector_2d::magnitude() const noexcept {
	return sqrt(_X * _X + _Y * _Y);
}

double vector_2d::angular_direction() const noexcept {
	auto v = atan2(-_Y, _X);
	if (v < 0.0) {
		v += two_pi<double>;
	}
	return v;
}

vector_2d vector_2d::to_unit() const noexcept {
	auto leng = magnitude();

	return vector_2d{ _X / leng, _Y / leng };
}
