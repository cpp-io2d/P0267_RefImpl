#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;
using namespace std::experimental::io2d::path_data;

close_path::close_path(const vector_2d& to) noexcept
	: _Data(to) {
}

vector_2d close_path::to() const noexcept {
	return _Data;
}

void close_path::to(const vector_2d& value) noexcept {
	_Data = value;
}


abs_move::abs_move(const vector_2d& to) noexcept
	: _Data(to) {
}

vector_2d abs_move::to() const noexcept {
	return _Data;
}

void abs_move::to(const vector_2d& value) noexcept {
	_Data = value;
}


abs_line::abs_line(const vector_2d& to) noexcept
	: _Data(to) {
}

vector_2d abs_line::to() const noexcept {
	return _Data;
}

void abs_line::to(const vector_2d& value) noexcept {
	_Data = value;
}


rel_move::rel_move(const vector_2d& to) noexcept
	: _Data(to) {
}

vector_2d rel_move::to() const noexcept {
	return _Data;
}

void rel_move::to(const vector_2d& value) noexcept {
	_Data = value;
}


rel_line::rel_line(const vector_2d& to) noexcept
	: _Data(to) {
}

vector_2d rel_line::to() const noexcept {
	return _Data;
}

void rel_line::to(const vector_2d& value) noexcept {
	_Data = value;
}


abs_cubic_curve::abs_cubic_curve(const vector_2d& controlPoint1, const vector_2d& controlPoint2, const vector_2d& endPoint) noexcept
	: _Control_pt1(controlPoint1)
	, _Control_pt2(controlPoint2)
	, _End_pt(endPoint) {
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

vector_2d abs_cubic_curve::control_point_1() const noexcept {
	return _Control_pt1;
}

vector_2d abs_cubic_curve::control_point_2() const noexcept {
	return _Control_pt2;
}

vector_2d abs_cubic_curve::end_point() const noexcept {
	return _End_pt;
}


rel_cubic_curve::rel_cubic_curve(const vector_2d& controlPoint1, const vector_2d& controlPoint2, const vector_2d& endPoint) noexcept
	: _Control_pt1(controlPoint1)
	, _Control_pt2(controlPoint2)
	, _End_pt(endPoint) {
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

vector_2d rel_cubic_curve::control_point_1() const noexcept {
	return _Control_pt1;
}

vector_2d rel_cubic_curve::control_point_2() const noexcept {
	return _Control_pt2;
}

vector_2d rel_cubic_curve::end_point() const noexcept {
	return _End_pt;
}


abs_quadratic_curve::abs_quadratic_curve(const vector_2d& cp, const vector_2d& ep) noexcept
	: _Control_pt(cp)
	, _End_pt(ep) {
}

void abs_quadratic_curve::control_point(const vector_2d& cp) noexcept {
	_Control_pt = cp;
}

void abs_quadratic_curve::end_point(const vector_2d& ep) noexcept {
	_End_pt = ep;
}

vector_2d abs_quadratic_curve::control_point() const noexcept {
	return _Control_pt;
}

vector_2d abs_quadratic_curve::end_point() const noexcept {
	return _End_pt;
}


rel_quadratic_curve::rel_quadratic_curve(const vector_2d& cp, const vector_2d& ep) noexcept
	: _Control_pt(cp)
	, _End_pt(ep) {
}

void rel_quadratic_curve::control_point(const vector_2d& cp) noexcept {
	_Control_pt = cp;
}

void rel_quadratic_curve::end_point(const vector_2d& ep) noexcept {
	_End_pt = ep;
}

vector_2d rel_quadratic_curve::control_point() const noexcept {
	return _Control_pt;
}

vector_2d rel_quadratic_curve::end_point() const noexcept {
	return _End_pt;
}


arc_clockwise::arc_clockwise(const vector_2d& center, double radius, double angle1, double angle2) noexcept
	: _Center(center)
	, _Radius(radius)
	, _Angle_1(angle1)
	, _Angle_2(angle2) {
}

void arc_clockwise::center(const vector_2d& value) noexcept {
	_Center = value;
}

void arc_clockwise::radius(double value) noexcept {
	_Radius = value;
}

void arc_clockwise::angle_1(double radians) noexcept {
	_Angle_1 = radians;
}

void arc_clockwise::angle_2(double radians) noexcept {
	_Angle_2 = radians;
}

vector_2d arc_clockwise::center() const noexcept {
	return _Center;
}

double arc_clockwise::radius() const noexcept {
	return _Radius;
}

double arc_clockwise::angle_1() const noexcept {
	return _Angle_1;
}

double arc_clockwise::angle_2() const noexcept {
	return _Angle_2;
}


arc_counterclockwise::arc_counterclockwise(const vector_2d& center, double radius, double angle1, double angle2) noexcept
	: _Center(center)
	, _Radius(radius)
	, _Angle_1(angle1)
	, _Angle_2(angle2) {
}

void arc_counterclockwise::center(const vector_2d& value) noexcept {
	_Center = value;
}

void arc_counterclockwise::radius(double value) noexcept {
	_Radius = value;
}

void arc_counterclockwise::angle_1(double radians) noexcept {
	_Angle_1 = radians;
}

void arc_counterclockwise::angle_2(double radians) noexcept {
	_Angle_2 = radians;
}

vector_2d arc_counterclockwise::center() const noexcept {
	return _Center;
}

double arc_counterclockwise::radius() const noexcept {
	return _Radius;
}

double arc_counterclockwise::angle_1() const noexcept {
	return _Angle_1;
}

double arc_counterclockwise::angle_2() const noexcept {
	return _Angle_2;
}



change_matrix::change_matrix(const matrix_2d& m) noexcept
	: _Matrix(m) {
}

void change_matrix::matrix(const matrix_2d& value) noexcept {
	_Matrix = value;
}

matrix_2d change_matrix::matrix() const noexcept {
	return _Matrix;
}


change_origin::change_origin(const vector_2d& origin) noexcept
	: _Origin(origin) {
}

void change_origin::origin(const vector_2d& value) noexcept {
	_Origin = value;
}

vector_2d change_origin::origin() const noexcept {
	return _Origin;
}
