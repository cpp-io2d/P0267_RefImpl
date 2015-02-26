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
