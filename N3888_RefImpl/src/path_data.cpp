#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

path_data::path_data(path_data&& /*other*/) noexcept {
}

path_data& path_data::operator=(path_data&& /*other*/) noexcept {
	return *this;
}

path_data::~path_data() noexcept {
}

_Point::_Point(_Point&& other) noexcept
	: path_data(move(other)) {
	_Data = move(other._Data);
	other._Data = { };
}

_Point& _Point::operator=(_Point&& other) noexcept {
	if (this != &other) {
		path_data::operator=(move(other));
		_Data = move(other._Data);

		other._Data = { };
	}
	return *this;
}

_Point::_Point(const point& to) noexcept
	: path_data()
	, _Data(to) {
}

_Point::~_Point() noexcept {
}

point _Point::to() const noexcept {
	return _Data;
}

void _Point::to(const point& value) noexcept {
	_Data = value;
}

move_to::move_to(move_to&& other) noexcept
	: _Point(move(other)) {
}

move_to& move_to::operator=(move_to&& other) noexcept {
	if (this != &other) {
		_Point::operator=(move(other));
	}
	return *this;
}

move_to::move_to(const point& to) noexcept
	: _Point(to) {
}

path_data_type move_to::type() const noexcept {
	return path_data_type::move_to;
}

line_to::line_to(line_to&& other) noexcept
	: _Point(move(other)) {
}

line_to& line_to::operator=(line_to&& other) noexcept {
	if (this != &other) {
		_Point::operator=(move(other));
	}
	return *this;
}

line_to::line_to(const point& to) noexcept
	: _Point(to) {
}
path_data_type line_to::type() const noexcept {
	return path_data_type::line_to;
}

rel_move_to::rel_move_to(rel_move_to&& other) noexcept
	: _Point(move(other)) {
}

rel_move_to& rel_move_to::operator=(rel_move_to&& other) noexcept {
	if (this != &other) {
		_Point::operator=(move(other));
	}
	return *this;
}

rel_move_to::rel_move_to(const point& to) noexcept
	: _Point(to) {
}

path_data_type rel_move_to::type() const noexcept {
	return path_data_type::rel_move_to;
}

rel_line_to::rel_line_to(rel_line_to&& other) noexcept
	: _Point(move(other)) {
}

rel_line_to& rel_line_to::operator=(rel_line_to&& other) noexcept {
	if (this != &other) {
		_Point::operator=(move(other));
	}
	return *this;
}

rel_line_to::rel_line_to(const point& to) noexcept
	: _Point(to) {
}

path_data_type rel_line_to::type() const noexcept {
	return path_data_type::rel_line_to;
}

_Curve_to::_Curve_to(_Curve_to&& other) noexcept
	: path_data(move(other))
	, _Control_pt1(move(other._Control_pt1))
	, _Control_pt2(move(other._Control_pt2))
	, _End_pt(move(other._End_pt)) {
	other._Control_pt1 = { };
	other._Control_pt2 = { };
	other._End_pt = { };
}

_Curve_to& _Curve_to::operator=(_Curve_to&& other) noexcept {
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

_Curve_to::_Curve_to(const point& controlPoint1, const point& controlPoint2, const point& endPoint) noexcept
	: path_data()
	, _Control_pt1(controlPoint1)
	, _Control_pt2(controlPoint2)
	, _End_pt(endPoint) {
}

_Curve_to::~_Curve_to() noexcept {
}

void _Curve_to::control_point_1(const point& value) noexcept {
	_Control_pt1 = value;
}

void _Curve_to::control_point_2(const point& value) noexcept {
	_Control_pt2 = value;
}

void _Curve_to::end_point(const point& value) noexcept {
	_End_pt = value;
}

point _Curve_to::control_point_1() const noexcept {
	return _Control_pt1;
}

point _Curve_to::control_point_2() const noexcept {
	return _Control_pt2;
}

point _Curve_to::end_point() const noexcept {
	return _End_pt;
}

curve_to::curve_to(curve_to&& other) noexcept
	: _Curve_to(move(other)) {
}

curve_to& curve_to::operator=(curve_to&& other) noexcept {
	if (this != &other) {
		_Curve_to::operator=(move(other));
	}
	return *this;
}

curve_to::curve_to(const point& controlPoint1, const point& controlPoint2, const point& endPoint) noexcept
	: _Curve_to(controlPoint1, controlPoint2, endPoint) {
}

path_data_type curve_to::type() const noexcept {
	return path_data_type::curve_to;
}

rel_curve_to::rel_curve_to(rel_curve_to&& other) noexcept
	: _Curve_to(move(other)) {
}

rel_curve_to& rel_curve_to::operator=(rel_curve_to&& other) noexcept {
	if (this != &other) {
		_Curve_to::operator=(move(other));
	}
	return *this;
}

rel_curve_to::rel_curve_to(const point& controlPoint1, const point& controlPoint2, const point& endPoint) noexcept
	: _Curve_to(controlPoint1, controlPoint2, endPoint) {
}

path_data_type rel_curve_to::type() const noexcept {
	return path_data_type::rel_curve_to;
}

_Arc::_Arc(_Arc&& other)
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

_Arc& _Arc::operator=(_Arc&& other) noexcept {
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

_Arc::_Arc(point center, double radius, double angle1, double angle2) noexcept
	: path_data()
	, _Center(center)
	, _Radius(radius)
	, _Angle_1(angle1)
	, _Angle_2(angle2) {
}

_Arc::~_Arc() noexcept {
}

void _Arc::center(const point& value) noexcept {
	_Center = value;
}

void _Arc::radius(double value) noexcept {
	_Radius = value;
}

void _Arc::angle_1(double radians) noexcept {
	_Angle_1 = radians;
}

void _Arc::angle_2(double radians) noexcept {
	_Angle_2 = radians;
}

point _Arc::center() const noexcept {
	return _Center;
}

double _Arc::radius() const noexcept {
	return _Radius;
}

double _Arc::angle_1() const noexcept {
	return _Angle_1;
}

double _Arc::angle_2() const noexcept {
	return _Angle_2;
}

arc::arc(arc&& other) noexcept
	: _Arc(move(other)) {
}

arc& arc::operator=(arc&& other) noexcept {
	if (this != &other) {
		_Arc::operator=(move(other));
	}
	return *this;
}

arc::arc(point center, double radius, double angle1, double angle2) noexcept
	: _Arc(center, radius, angle1, angle2) {
}

path_data_type arc::type() const noexcept {
	return path_data_type::arc;
}

arc_negative::arc_negative(arc_negative&& other) noexcept
	: _Arc(move(other)) {
}

arc_negative& arc_negative::operator=(arc_negative&& other) noexcept {
	if (this != &other) {
		_Arc::operator=(move(other));
	}
	return *this;
}

arc_negative::arc_negative(point center, double radius, double angle1, double angle2) noexcept
	: _Arc(center, radius, angle1, angle2) {
}

path_data_type arc_negative::type() const noexcept {
	return path_data_type::arc_negative;
}

new_sub_path::new_sub_path(new_sub_path&& other) noexcept
	: path_data(move(other)) {
}

new_sub_path& new_sub_path::operator=(new_sub_path&& other) noexcept {
	if (this != &other) {
		path_data::operator=(move(other));
	}
	return *this;
}

path_data_type new_sub_path::type() const noexcept {
	return path_data_type::new_sub_path;
}

close_path::close_path(close_path&& other) noexcept
	: path_data(move(other)) {
}

close_path& close_path::operator=(close_path&& other) noexcept {
	if (this != &other) {
		path_data::operator=(move(other));
	}
	return *this;
}

path_data_type close_path::type() const noexcept {
	return path_data_type::close_path;
}

change_matrix::change_matrix(change_matrix&& other) noexcept
	: path_data(move(other))
	, _Matrix(move(other._Matrix)) {
	other._Matrix = { };
}

change_matrix::change_matrix(const matrix_2d& m) noexcept
	: path_data()
	, _Matrix(m) {
}

change_matrix& change_matrix::operator=(change_matrix&& other) noexcept {
	if (this != &other) {
		path_data::operator=(move(other));
		_Matrix = move(other._Matrix);

		other._Matrix = { };
	}
	return *this;
}

void change_matrix::matrix(const matrix_2d& value) noexcept {
	_Matrix = value;
}

matrix_2d change_matrix::matrix() const noexcept {
	return _Matrix;
}

path_data_type change_matrix::type() const noexcept {
	return path_data_type::change_matrix;
}

change_origin::change_origin(change_origin&& other) noexcept
	: path_data(move(other))
	, _Origin(move(other._Origin)) {
}

change_origin& change_origin::operator=(change_origin&& other) noexcept {
	if (this != &other) {
		path_data::operator=(move(other));
		_Origin = move(other._Origin);

		other._Origin = { };
	}
	return *this;
}

change_origin::change_origin(const point& origin) noexcept
	: path_data()
	, _Origin(origin) {
}

void change_origin::origin(const point& value) noexcept {
	_Origin = value;
}

point change_origin::origin() const noexcept {
	return _Origin;
}

path_data_type change_origin::type() const noexcept {
	return path_data_type::change_origin;
}
