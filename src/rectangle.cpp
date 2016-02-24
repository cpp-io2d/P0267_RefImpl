#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

rectangle::rectangle(rectangle&& other) noexcept
: _X(move(other._X))
, _Y(move(other._Y))
, _Width(move(other._Width))
, _Height(move(other._Height)){
	other._X = 0.0;
	other._Y = 0.0;
	other._Width = 0.0;
	other._Height = 0.0;
}

rectangle& rectangle::operator=(rectangle&& other) noexcept {
	if (this != &other) {
		_X = move(other._X);
		_Y = move(other._Y);
		_Width = move(other._Width);
		_Height = move(other._Height);

		other._X = 0.0;
		other._Y = 0.0;
		other._Width = 0.0;
		other._Height = 0.0;
	}
	return *this;
}

rectangle::rectangle(double x, double y, double width, double height) noexcept
	: _X(x)
	, _Y(y)
	, _Width(width)
	, _Height(height) {
}

rectangle::rectangle(const vector_2d& tl, const vector_2d& br) noexcept
	: _X(tl.x())
	, _Y(tl.y())
	, _Width(max(0.0, br.x() - tl.x()))
	, _Height(max(0.0, br.y() - tl.y())) {

}

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

double rectangle::x() const noexcept {
	return _X;
}

double rectangle::y() const noexcept {
	return _Y;
}

double rectangle::width() const noexcept {
	return _Width;
}

double rectangle::height() const noexcept {
	return _Height;
}

double rectangle::left() const noexcept {
	return _X;
}

double rectangle::right() const noexcept {
	return _X + _Width;
}

double rectangle::top() const noexcept {
	return _Y;
}

double rectangle::bottom() const noexcept {
	return _Y + _Height;
}

vector_2d rectangle::top_left() const noexcept {
	return{ _X, _Y };
}

vector_2d rectangle::bottom_right() const noexcept {
	return{ _X + _Width, _Y + _Height };
}

tuple<vector_2d, vector_2d> rectangle::top_left_bottom_right() const noexcept {
	return make_tuple<vector_2d, vector_2d>({ _X, _Y }, { _X + _Width, _Y + _Height });
}
