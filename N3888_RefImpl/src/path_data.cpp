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
