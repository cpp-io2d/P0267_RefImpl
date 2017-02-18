#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

void rectangle::x(double value) noexcept {
	_X = value;
}

void rectangle::y(double value) noexcept {
	_Y = value;
}

void rectangle::width(double value) noexcept {
	_Width = value;
}

void rectangle::height(double value) noexcept {
	_Height = value;
}

void rectangle::top_left(const vector_2d& value) noexcept {
	_X = value.x();
	_Y = value.y();
}

void rectangle::bottom_right(const vector_2d& value) noexcept {
	auto x = value.x();
	auto y = value.y();
	_Width = max(0.0, x - _X);
	_Height = max(0.0, y - _Y);
}

void rectangle::top_left_bottom_right(const vector_2d& tl, const vector_2d& br) noexcept {
	auto tlx = tl.x();
	auto tly = tl.y();
	auto brx = br.x();
	auto bry = br.y();
	_X = tlx;
	_Y = tly;
	_Width = max(0.0, brx - tlx);
	_Height = max(0.0, bry - tly);
}

//tuple<vector_2d, vector_2d> rectangle::top_left_bottom_right() const noexcept {
//	return make_tuple<vector_2d, vector_2d>({ _X, _Y }, { _X + _Width, _Y + _Height });
//}
