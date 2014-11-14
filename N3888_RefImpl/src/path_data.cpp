#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

path_data::path_data(path_data&& /*other*/) {
}

path_data& path_data::operator=(path_data&& /*other*/) {
	return *this;
}

path_data::~path_data() {
}

_Point_path_data::_Point_path_data(_Point_path_data&& other)
	: path_data(move(other)) {
	_Data = move(other._Data);
	other._Data = { };
}

_Point_path_data& _Point_path_data::operator=(_Point_path_data&& other) {
	if (this != &other) {
		path_data::operator=(move(other));
		_Data = move(other._Data);

		other._Data = { };
	}
	return *this;
}

_Point_path_data::_Point_path_data(const point& to)
	: path_data()
	, _Data(to) {
}

point _Point_path_data::to() const {
	return _Data;
}

void _Point_path_data::to(const point& value) {
	_Data = value;
}

move_to_path_data::move_to_path_data(move_to_path_data&& other)
	: _Point_path_data(move(other)) {
}

move_to_path_data& move_to_path_data::operator=(move_to_path_data&& other) {
	if (this != &other) {
		_Point_path_data::operator=(move(other));
	}
	return *this;
}

move_to_path_data::move_to_path_data(const point& to)
	: _Point_path_data(to) {
}

path_data_type move_to_path_data::type() const {
	return path_data_type::move_to;
}

line_to_path_data::line_to_path_data(line_to_path_data&& other)
	: _Point_path_data(move(other)) {
}

line_to_path_data& line_to_path_data::operator=(line_to_path_data&& other) {
	if (this != &other) {
		_Point_path_data::operator=(move(other));
	}
	return *this;
}

line_to_path_data::line_to_path_data(const point& to)
	: _Point_path_data(to) {
}
path_data_type line_to_path_data::type() const {
	return path_data_type::line_to;
}

rel_move_to_path_data::rel_move_to_path_data(rel_move_to_path_data&& other)
	: _Point_path_data(move(other)) {
}

rel_move_to_path_data& rel_move_to_path_data::operator=(rel_move_to_path_data&& other) {
	if (this != &other) {
		_Point_path_data::operator=(move(other));
	}
	return *this;
}

rel_move_to_path_data::rel_move_to_path_data(const point& to)
	: _Point_path_data(to) {
}

path_data_type rel_move_to_path_data::type() const {
	return path_data_type::rel_move_to;
}

rel_line_to_path_data::rel_line_to_path_data(rel_line_to_path_data&& other)
	: _Point_path_data(move(other)) {
}

rel_line_to_path_data& rel_line_to_path_data::operator=(rel_line_to_path_data&& other) {
	if (this != &other) {
		_Point_path_data::operator=(move(other));
	}
	return *this;
}

rel_line_to_path_data::rel_line_to_path_data(const point& to)
	: _Point_path_data(to) {
}

path_data_type rel_line_to_path_data::type() const {
	return path_data_type::rel_line_to;
}

_Curve_to_path_data::_Curve_to_path_data(_Curve_to_path_data&& other)
	: path_data(move(other))
	, _Control_pt1(move(other._Control_pt1))
	, _Control_pt2(move(other._Control_pt2))
	, _End_pt(move(other._End_pt)) {
	other._Control_pt1 = { };
	other._Control_pt2 = { };
	other._End_pt = { };
}

_Curve_to_path_data& _Curve_to_path_data::operator=(_Curve_to_path_data&& other) {
	if (this != &other) {
		path_data::operator=(move(other));
		_Control_pt1 = move(other._Control_pt1);
		_Control_pt2 = move(other._Control_pt2);
		_End_pt = move(other._End_pt);

		other._Control_pt1 = { };
		other._Control_pt2 = { };
		other._End_pt = { };
	}
	return *this;
}

_Curve_to_path_data::_Curve_to_path_data(const point& controlPoint1, const point& controlPoint2, const point& endPoint)
	: path_data()
	, _Control_pt1(controlPoint1)
	, _Control_pt2(controlPoint2)
	, _End_pt(endPoint) {
}

void _Curve_to_path_data::control_point_1(const point& value) {
	_Control_pt1 = value;
}

void _Curve_to_path_data::control_point_2(const point& value) {
	_Control_pt2 = value;
}

void _Curve_to_path_data::end_point(const point& value) {
	_End_pt = value;
}

point _Curve_to_path_data::control_point_1() const {
	return _Control_pt1;
}

point _Curve_to_path_data::control_point_2() const {
	return _Control_pt2;
}

point _Curve_to_path_data::end_point() const {
	return _End_pt;
}

curve_to_path_data::curve_to_path_data(curve_to_path_data&& other)
	: _Curve_to_path_data(move(other)) {
}

curve_to_path_data& curve_to_path_data::operator=(curve_to_path_data&& other) {
	if (this != &other) {
		_Curve_to_path_data::operator=(move(other));
	}
	return *this;
}

curve_to_path_data::curve_to_path_data(const point& controlPoint1, const point& controlPoint2, const point& endPoint)
	: _Curve_to_path_data(controlPoint1, controlPoint2, endPoint) {
}

path_data_type curve_to_path_data::type() const {
	return path_data_type::curve_to;
}

rel_curve_to_path_data::rel_curve_to_path_data(rel_curve_to_path_data&& other)
	: _Curve_to_path_data(move(other)) {
}

rel_curve_to_path_data& rel_curve_to_path_data::operator=(rel_curve_to_path_data&& other) {
	if (this != &other) {
		_Curve_to_path_data::operator=(move(other));
	}
	return *this;
}

rel_curve_to_path_data::rel_curve_to_path_data(const point& controlPoint1, const point& controlPoint2, const point& endPoint)
	: _Curve_to_path_data(controlPoint1, controlPoint2, endPoint) {
}

path_data_type rel_curve_to_path_data::type() const {
	return path_data_type::rel_curve_to;
}

_Arc_path_data::_Arc_path_data(_Arc_path_data&& other)
	: path_data(move(other))
	, _Center(move(other._Center))
	, _Radius(move(other._Radius))
	, _Angle_1(move(other._Angle_1))
	, _Angle_2(move(other._Angle_2)) {
	other._Center = { };
	other._Radius = { };
	other._Angle_1 = { };
	other._Angle_2 = { };
}

_Arc_path_data& _Arc_path_data::operator=(_Arc_path_data&& other) {
	if (this != &other) {
		_Center = move(other._Center);
		_Radius = move(other._Radius);
		_Angle_1 = move(other._Angle_1);
		_Angle_2 = move(other._Angle_2);

		other._Center = { };
		other._Radius = { };
		other._Angle_1 = { };
		other._Angle_2 = { };
	}
	return *this;
}

_Arc_path_data::_Arc_path_data(point center, double radius, double angle1, double angle2)
	: path_data()
	, _Center(center)
	, _Radius(radius)
	, _Angle_1(angle1)
	, _Angle_2(angle2) {
}

void _Arc_path_data::center(const point& value) {
	_Center = value;
}

void _Arc_path_data::radius(double value) {
	_Radius = value;
}

void _Arc_path_data::angle_1(double radians) {
	_Angle_1 = radians;
}

void _Arc_path_data::angle_2(double radians) {
	_Angle_2 = radians;
}

point _Arc_path_data::center() const {
	return _Center;
}

double _Arc_path_data::radius() const {
	return _Radius;
}

double _Arc_path_data::angle_1() const {
	return _Angle_1;
}

double _Arc_path_data::angle_2() const {
	return _Angle_2;
}

arc_path_data::arc_path_data(arc_path_data&& other)
	: _Arc_path_data(move(other)) {
}

arc_path_data& arc_path_data::operator=(arc_path_data&& other) {
	if (this != &other) {
		_Arc_path_data::operator=(move(other));
	}
	return *this;
}

arc_path_data::arc_path_data(point center, double radius, double angle1, double angle2)
	: _Arc_path_data(center, radius, angle1, angle2) {
}

path_data_type arc_path_data::type() const {
	return path_data_type::arc;
}

arc_negative_path_data::arc_negative_path_data(arc_negative_path_data&& other)
	: _Arc_path_data(move(other)) {
}

arc_negative_path_data& arc_negative_path_data::operator=(arc_negative_path_data&& other) {
	if (this != &other) {
		_Arc_path_data::operator=(move(other));
	}
	return *this;
}

arc_negative_path_data::arc_negative_path_data(point center, double radius, double angle1, double angle2)
	: _Arc_path_data(center, radius, angle1, angle2) {
}

path_data_type arc_negative_path_data::type() const {
	return path_data_type::arc_negative;
}

new_sub_path_path_data::new_sub_path_path_data(new_sub_path_path_data&& other)
	: path_data(move(other)) {
}

new_sub_path_path_data& new_sub_path_path_data::operator=(new_sub_path_path_data&& other) {
	if (this != &other) {
		path_data::operator=(move(other));
	}
	return *this;
}

path_data_type new_sub_path_path_data::type() const {
	return path_data_type::new_sub_path;
}

close_path_path_data::close_path_path_data(close_path_path_data&& other)
	: path_data(move(other)) {
}

close_path_path_data& close_path_path_data::operator=(close_path_path_data&& other) {
	if (this != &other) {
		path_data::operator=(move(other));
	}
	return *this;
}

path_data_type close_path_path_data::type() const {
	return path_data_type::close_path;
}

change_matrix_path_data::change_matrix_path_data(change_matrix_path_data&& other)
	: path_data(move(other))
	, _Matrix(move(other._Matrix)) {
	other._Matrix = { };
}

change_matrix_path_data::change_matrix_path_data(const matrix_2d& m)
	: path_data()
	, _Matrix(m) {
}

change_matrix_path_data& change_matrix_path_data::operator=(change_matrix_path_data&& other) {
	if (this != &other) {
		path_data::operator=(move(other));
		_Matrix = move(other._Matrix);

		other._Matrix = { };
	}
	return *this;
}

void change_matrix_path_data::matrix(const matrix_2d& value) {
	_Matrix = value;
}

matrix_2d change_matrix_path_data::matrix() const {
	return _Matrix;
}

path_data_type change_matrix_path_data::type() const {
	return path_data_type::change_matrix;
}

change_origin_path_data::change_origin_path_data(change_origin_path_data&& other)
	: path_data(move(other))
	, _Origin(move(other._Origin)) {
}

change_origin_path_data& change_origin_path_data::operator=(change_origin_path_data&& other) {
	if (this != &other) {
		path_data::operator=(move(other));
		_Origin = move(other._Origin);

		other._Origin = { };
	}
	return *this;
}

change_origin_path_data::change_origin_path_data(const point& origin)
	: path_data()
	, _Origin(origin) {
}

void change_origin_path_data::origin(const point& value) {
	_Origin = value;
}

point change_origin_path_data::origin() const {
	return _Origin;
}

path_data_type change_origin_path_data::type() const {
	return path_data_type::change_origin;
}
