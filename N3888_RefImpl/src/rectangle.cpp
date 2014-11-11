#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

rectangle::rectangle(double x, double y, double width, double height)
	: _X(x)
	, _Y(y)
	, _Width(width)
	, _Height(height) {
}

void rectangle::x(double value) {
	_X = value;
}

void rectangle::y(double value) {
	_Y = value;
}

void rectangle::width(double value) {
	_Width = value;
}

void rectangle::height(double value) {
	_Height = value;
}

double rectangle::x() const {
	return _X;
}

double rectangle::y() const {
	return _Y;
}

double rectangle::width() const {
	return _Width;
}

double rectangle::height() const {
	return _Height;
}
