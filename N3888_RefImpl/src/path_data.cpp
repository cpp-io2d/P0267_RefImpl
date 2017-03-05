#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;
using namespace std::experimental::io2d::path_data;

void close_path::to(const vector_2d& value) noexcept {
	_Data = value;
}


void abs_move::to(const vector_2d& to) noexcept {
	_Data = to;
}


void abs_line::to(const vector_2d& to) noexcept {
	_Data = to;
}


void rel_move::to(const vector_2d& to) noexcept {
	_Data = to;
}


void rel_line::to(const vector_2d& to) noexcept {
	_Data = to;
}


void abs_cubic_curve::control_point_1(const vector_2d& value) noexcept {
	_Control_pt1 = value;
}

void abs_cubic_curve::control_point_2(const vector_2d& value) noexcept {
	_Control_pt2 = value;
}

void abs_cubic_curve::end_point(const vector_2d& value) noexcept {
	_End_pt = value;
}


void rel_cubic_curve::control_point_1(const vector_2d& value) noexcept {
	_Control_pt1 = value;
}

void rel_cubic_curve::control_point_2(const vector_2d& value) noexcept {
	_Control_pt2 = value;
}

void rel_cubic_curve::end_point(const vector_2d& value) noexcept {
	_End_pt = value;
}


void abs_quadratic_curve::control_point(const vector_2d& cp) noexcept {
	_Control_pt = cp;
}

void abs_quadratic_curve::end_point(const vector_2d& ep) noexcept {
	_End_pt = ep;
}


void rel_quadratic_curve::control_point(const vector_2d& cp) noexcept {
	_Control_pt = cp;
}

void rel_quadratic_curve::end_point(const vector_2d& ep) noexcept {
	_End_pt = ep;
}

void abs_rectangle::x(double x) noexcept {
	_X = x;
}

void abs_rectangle::y(double value) noexcept {
	_Y = value;
}

void abs_rectangle::width(double value) noexcept {
	_Width = value;
}

void abs_rectangle::height(double value) noexcept {
	_Height = value;
}

void abs_rectangle::top_left(const vector_2d& value) noexcept {
	_X = value.x();
	_Y = value.y();
}

void abs_rectangle::bottom_right(const vector_2d& value) noexcept {
	auto x = value.x();
	auto y = value.y();
	_Width = max(0.0, x - _X);
	_Height = max(0.0, y - _Y);
}

void abs_rectangle::top_left_bottom_right(const vector_2d& tl, const vector_2d& br) noexcept {
	auto tlx = tl.x();
	auto tly = tl.y();
	auto brx = br.x();
	auto bry = br.y();
	_X = tlx;
	_Y = tly;
	_Width = max(0.0, brx - tlx);
	_Height = max(0.0, bry - tly);
}

void rel_rectangle::x(double value) noexcept {
	_X = value;
}

void rel_rectangle::y(double value) noexcept {
	_Y = value;
}

void rel_rectangle::width(double value) noexcept {
	_Width = value;
}

void rel_rectangle::height(double value) noexcept {
	_Height = value;
}

void rel_rectangle::top_left(const vector_2d& value) noexcept {
	_X = value.x();
	_Y = value.y();
}

void rel_rectangle::bottom_right(const vector_2d& value) noexcept {
	auto x = value.x();
	auto y = value.y();
	_Width = max(0.0, x - _X);
	_Height = max(0.0, y - _Y);
}

void rel_rectangle::top_left_bottom_right(const vector_2d& tl, const vector_2d& br) noexcept {
	auto tlx = tl.x();
	auto tly = tl.y();
	auto brx = br.x();
	auto bry = br.y();
	_X = tlx;
	_Y = tly;
	_Width = max(0.0, brx - tlx);
	_Height = max(0.0, bry - tly);
}

void arc_clockwise::circle(const experimental::io2d::circle& c) noexcept {
	_Circle = c;
}

void arc_clockwise::center(const vector_2d& ctr) noexcept {
	_Circle.center(ctr);
}


void arc_clockwise::radius(double rad) noexcept {
	_Circle.radius(rad);
}

void arc_clockwise::angle_1(double radians) noexcept {
	_Angle_1 = radians;
}

void arc_clockwise::angle_2(double radians) noexcept {
	_Angle_2 = radians;
}


void arc_counterclockwise::circle(const experimental::io2d::circle& c) noexcept {
	_Circle = c;
}
void arc_counterclockwise::center(const vector_2d& ctr) noexcept {
	_Circle.center(ctr);
}

void arc_counterclockwise::radius(double rad) noexcept {
	_Circle.radius(rad);
}

void arc_counterclockwise::angle_1(double radians) noexcept {
	_Angle_1 = radians;
}

void arc_counterclockwise::angle_2(double radians) noexcept {
	_Angle_2 = radians;
}


void change_matrix::matrix(const matrix_2d& value) noexcept {
	_Matrix = value;
}


void change_origin::origin(const vector_2d& value) noexcept {
	_Origin = value;
}
