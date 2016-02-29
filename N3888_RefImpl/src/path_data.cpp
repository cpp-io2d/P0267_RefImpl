#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

path_data_item::path_data::path_data(path_data_item::path_data&& /*other*/) noexcept {
}

path_data_item::path_data& path_data_item::path_data::operator=(path_data_item::path_data&& /*other*/) noexcept {
	return *this;
}

path_data_item::path_data::~path_data() noexcept {
}

_Point::_Point(_Point&& other) noexcept
	: path_data_item::path_data(move(other)) {
	_Data = move(other._Data);
	other._Data = { };
}

_Point& _Point::operator=(_Point&& other) noexcept {
	if (this != &other) {
		path_data_item::path_data::operator=(move(other));
		_Data = move(other._Data);

		other._Data = { };
	}
	return *this;
}

_Point::_Point(const vector_2d& to) noexcept
	: path_data_item::path_data()
	, _Data(to) {
}

_Point::~_Point() noexcept {
}

vector_2d _Point::to() const noexcept {
	return _Data;
}

void _Point::to(const vector_2d& value) noexcept {
	_Data = value;
}

path_data_item::move_to::move_to(path_data_item::move_to&& other) noexcept
	: _Point(move(other)) {
}

path_data_item::move_to& path_data_item::move_to::operator=(path_data_item::move_to&& other) noexcept {
	if (this != &other) {
		_Point::operator=(move(other));
	}
	return *this;
}

path_data_item::move_to::move_to(const vector_2d& to) noexcept
	: _Point(to) {
}

path_data_type path_data_item::move_to::type() const noexcept {
	return path_data_type::move_to;
}

path_data_item::line_to::line_to(path_data_item::line_to&& other) noexcept
	: _Point(move(other)) {
}

path_data_item::line_to& path_data_item::line_to::operator=(path_data_item::line_to&& other) noexcept {
	if (this != &other) {
		_Point::operator=(move(other));
	}
	return *this;
}

path_data_item::line_to::line_to(const vector_2d& to) noexcept
	: _Point(to) {
}

path_data_type path_data_item::line_to::type() const noexcept {
	return path_data_type::line_to;
}

path_data_item::rel_move_to::rel_move_to(path_data_item::rel_move_to&& other) noexcept
	: _Point(move(other)) {
}

path_data_item::rel_move_to& path_data_item::rel_move_to::operator=(path_data_item::rel_move_to&& other) noexcept {
	if (this != &other) {
		_Point::operator=(move(other));
	}
	return *this;
}

path_data_item::rel_move_to::rel_move_to(const vector_2d& to) noexcept
	: _Point(to) {
}

path_data_type path_data_item::rel_move_to::type() const noexcept {
	return path_data_type::rel_move_to;
}

path_data_item::rel_line_to::rel_line_to(path_data_item::rel_line_to&& other) noexcept
	: _Point(move(other)) {
}

path_data_item::rel_line_to& path_data_item::rel_line_to::operator=(path_data_item::rel_line_to&& other) noexcept {
	if (this != &other) {
		_Point::operator=(move(other));
	}
	return *this;
}

path_data_item::rel_line_to::rel_line_to(const vector_2d& to) noexcept
	: _Point(to) {
}

path_data_type path_data_item::rel_line_to::type() const noexcept {
	return path_data_type::rel_line_to;
}

_Curve_to::_Curve_to(_Curve_to&& other) noexcept
	: path_data_item::path_data(move(other))
	, _Control_pt1(move(other._Control_pt1))
	, _Control_pt2(move(other._Control_pt2))
	, _End_pt(move(other._End_pt)) {
	other._Control_pt1 = { };
	other._Control_pt2 = { };
	other._End_pt = { };
}

_Curve_to& _Curve_to::operator=(_Curve_to&& other) noexcept {
	if (this != &other) {
		path_data_item::path_data::operator=(move(other));
		_Control_pt1 = move(other._Control_pt1);
		_Control_pt2 = move(other._Control_pt2);
		_End_pt = move(other._End_pt);

		other._Control_pt1 = { };
		other._Control_pt2 = { };
		other._End_pt = { };
	}
	return *this;
}

_Curve_to::_Curve_to(const vector_2d& controlPoint1, const vector_2d& controlPoint2, const vector_2d& endPoint) noexcept
	: path_data_item::path_data()
	, _Control_pt1(controlPoint1)
	, _Control_pt2(controlPoint2)
	, _End_pt(endPoint) {
}

_Curve_to::~_Curve_to() noexcept {
}

void _Curve_to::control_point_1(const vector_2d& value) noexcept {
	_Control_pt1 = value;
}

void _Curve_to::control_point_2(const vector_2d& value) noexcept {
	_Control_pt2 = value;
}

void _Curve_to::end_point(const vector_2d& value) noexcept {
	_End_pt = value;
}

vector_2d _Curve_to::control_point_1() const noexcept {
	return _Control_pt1;
}

vector_2d _Curve_to::control_point_2() const noexcept {
	return _Control_pt2;
}

vector_2d _Curve_to::end_point() const noexcept {
	return _End_pt;
}

path_data_item::curve_to::curve_to(path_data_item::curve_to&& other) noexcept
	: _Curve_to(move(other)) {
}

path_data_item::curve_to& path_data_item::curve_to::operator=(path_data_item::curve_to&& other) noexcept {
	if (this != &other) {
		_Curve_to::operator=(move(other));
	}
	return *this;
}

path_data_item::curve_to::curve_to(const vector_2d& controlPoint1, const vector_2d& controlPoint2, const vector_2d& endPoint) noexcept
	: _Curve_to(controlPoint1, controlPoint2, endPoint) {
}

path_data_type path_data_item::curve_to::type() const noexcept {
	return path_data_type::curve_to;
}

path_data_item::rel_curve_to::rel_curve_to(path_data_item::rel_curve_to&& other) noexcept
	: _Curve_to(move(other)) {
}

path_data_item::rel_curve_to& path_data_item::rel_curve_to::operator=(path_data_item::rel_curve_to&& other) noexcept {
	if (this != &other) {
		_Curve_to::operator=(move(other));
	}
	return *this;
}

path_data_item::rel_curve_to::rel_curve_to(const vector_2d& controlPoint1, const vector_2d& controlPoint2, const vector_2d& endPoint) noexcept
	: _Curve_to(controlPoint1, controlPoint2, endPoint) {
}

path_data_type path_data_item::rel_curve_to::type() const noexcept {
	return path_data_type::rel_curve_to;
}

_Arc::_Arc() noexcept
	: path_data_item::path_data()
	, _Center()
	, _Radius()
	, _Angle_1()
	, _Angle_2() {
}

_Arc::_Arc(_Arc&& other) noexcept
	: path_data_item::path_data(move(other))
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
		path_data_item::path_data::operator=(move(other));
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

_Arc::_Arc(const vector_2d& center, double radius, double angle1, double angle2) noexcept
	: path_data_item::path_data()
	, _Center(center)
	, _Radius(radius)
	, _Angle_1(angle1)
	, _Angle_2(angle2) {
}

_Arc::~_Arc() noexcept {
}

void _Arc::center(const vector_2d& value) noexcept {
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

vector_2d _Arc::center() const noexcept {
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

path_data_item::arc::arc(path_data_item::arc&& other) noexcept
	: _Arc(move(other)) {
}

path_data_item::arc& path_data_item::arc::operator=(path_data_item::arc&& other) noexcept {
	if (this != &other) {
		_Arc::operator=(move(other));
	}
	return *this;
}

path_data_item::arc::arc(const vector_2d& center, double radius, double angle1, double angle2) noexcept
	: _Arc(center, radius, angle1, angle2) {
}

path_data_type path_data_item::arc::type() const noexcept {
	return path_data_type::arc;
}

path_data_item::arc_negative::arc_negative(path_data_item::arc_negative&& other) noexcept
	: _Arc(move(other)) {
}

path_data_item::arc_negative& path_data_item::arc_negative::operator=(path_data_item::arc_negative&& other) noexcept {
	if (this != &other) {
		_Arc::operator=(move(other));
	}
	return *this;
}

path_data_item::arc_negative::arc_negative(const vector_2d& center, double radius, double angle1, double angle2) noexcept
	: _Arc(center, radius, angle1, angle2) {
}

path_data_type path_data_item::arc_negative::type() const noexcept {
	return path_data_type::arc_negative;
}

path_data_item::new_sub_path::new_sub_path(path_data_item::new_sub_path&& other) noexcept
	: path_data_item::path_data(move(other)) {
}

path_data_item::new_sub_path& path_data_item::new_sub_path::operator=(path_data_item::new_sub_path&& other) noexcept {
	if (this != &other) {
		path_data_item::path_data::operator=(move(other));
	}
	return *this;
}

path_data_type path_data_item::new_sub_path::type() const noexcept {
	return path_data_type::new_sub_path;
}

path_data_item::close_path::close_path(path_data_item::close_path&& other) noexcept
	: path_data_item::path_data(move(other)) {
}

path_data_item::close_path& path_data_item::close_path::operator=(path_data_item::close_path&& other) noexcept {
	if (this != &other) {
		path_data_item::path_data::operator=(move(other));
	}
	return *this;
}

path_data_type path_data_item::close_path::type() const noexcept {
	return path_data_type::close_path;
}

path_data_item::change_matrix::change_matrix(path_data_item::change_matrix&& other) noexcept
	: path_data_item::path_data(move(other))
	, _Matrix(move(other._Matrix)) {
	other._Matrix = { };
}

path_data_item::change_matrix::change_matrix(const matrix_2d& m) noexcept
	: path_data_item::path_data()
	, _Matrix(m) {
}

path_data_item::change_matrix& path_data_item::change_matrix::operator=(path_data_item::change_matrix&& other) noexcept {
	if (this != &other) {
		path_data_item::path_data::operator=(move(other));
		_Matrix = move(other._Matrix);

		other._Matrix = { };
	}
	return *this;
}

void path_data_item::change_matrix::matrix(const matrix_2d& value) noexcept {
	_Matrix = value;
}

matrix_2d path_data_item::change_matrix::matrix() const noexcept {
	return _Matrix;
}

path_data_type path_data_item::change_matrix::type() const noexcept {
	return path_data_type::change_matrix;
}

path_data_item::change_origin::change_origin(path_data_item::change_origin&& other) noexcept
	: path_data_item::path_data(move(other))
	, _Origin(move(other._Origin)) {
}

path_data_item::change_origin& path_data_item::change_origin::operator=(path_data_item::change_origin&& other) noexcept {
	if (this != &other) {
		path_data_item::path_data::operator=(move(other));
		_Origin = move(other._Origin);

		other._Origin = { };
	}
	return *this;
}

path_data_item::change_origin::change_origin(const vector_2d& origin) noexcept
	: path_data_item::path_data()
	, _Origin(origin) {
}

void path_data_item::change_origin::origin(const vector_2d& value) noexcept {
	_Origin = value;
}

vector_2d path_data_item::change_origin::origin() const noexcept {
	return _Origin;
}

path_data_type path_data_item::change_origin::type() const noexcept {
	return path_data_type::change_origin;
}
