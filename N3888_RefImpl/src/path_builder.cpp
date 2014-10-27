#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"
#include <algorithm>
#include <limits>

using namespace std;
using namespace std::experimental::io2d;

path_builder::path_builder()
	: _Lock()
	, _Data()
	, _Has_current_point()
	, _Current_point()
	, _Last_move_to_point()
	, _Extents_pt0()
	, _Extents_pt1()
	, _Transform_matrix(matrix_2d::init_identity())
	, _Origin() {
}

path_builder::path_builder(const path_builder& other)
	: _Lock()
	, _Data()
	, _Has_current_point()
	, _Current_point()
	, _Last_move_to_point()
	, _Extents_pt0()
	, _Extents_pt1()
	, _Transform_matrix()
	, _Origin() {
	lock_guard<decltype(other._Lock)> lg(other._Lock);
	_Data = other._Data;
	_Has_current_point = other._Has_current_point;
	_Current_point = other._Current_point;
	_Last_move_to_point = other._Last_move_to_point;
	_Extents_pt0 = other._Extents_pt0;
	_Extents_pt1 = other._Extents_pt1;
	_Transform_matrix = other._Transform_matrix;
	_Origin = other._Origin;
}

path_builder& path_builder::operator=(const path_builder& other) {
	if (this != &other) {
		lock_guard<decltype(_Lock)> tlg(_Lock);
		lock_guard<decltype(other._Lock)> lg(other._Lock);
		_Data = other._Data;
		_Has_current_point = other._Has_current_point;
		_Current_point = other._Current_point;
		_Last_move_to_point = other._Last_move_to_point;
		_Extents_pt0 = other._Extents_pt0;
		_Extents_pt1 = other._Extents_pt1;
		_Transform_matrix = other._Transform_matrix;
		_Origin = other._Origin;
	}
	return *this;
}

path_builder::path_builder(path_builder&& other)
	: _Lock()
	, _Data()
	, _Has_current_point()
	, _Current_point()
	, _Extents_pt0()
	, _Extents_pt1()
	, _Transform_matrix()
	, _Origin() {
	lock_guard<decltype(_Lock)> lg(other._Lock);
	_Data = move(other._Data);
	_Has_current_point = move(other._Has_current_point);
	_Current_point = move(other._Current_point);
	_Last_move_to_point = move(other._Last_move_to_point);
	_Extents_pt0 = move(other._Extents_pt0);
	_Extents_pt1 = move(other._Extents_pt1);
	_Transform_matrix = move(other._Transform_matrix);
	_Origin = move(other._Origin);
}

path_builder& path_builder::operator=(path_builder&& other) {
	if (this != &other) {
		lock_guard<decltype(_Lock)> tlg(_Lock);
		lock_guard<decltype(other._Lock)> lg(other._Lock);
		_Data = move(other._Data);
		_Has_current_point = move(other._Has_current_point);
		_Current_point = move(other._Current_point);
		_Last_move_to_point = move(other._Last_move_to_point);
		_Extents_pt0 = move(other._Extents_pt0);
		_Extents_pt1 = move(other._Extents_pt1);
		_Transform_matrix = move(other._Transform_matrix);
		_Origin = move(other._Origin);
	}
	return *this;
}

path path_builder::get_path() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return path(*this);
}

void path_builder::append(const path& p) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	const auto& data = p.get_data_ref();
	for (const auto& item : data) {
		_Data.push_back(item);
		if (item.type == path_data_type::change_matrix) {
			_Transform_matrix = item.data.matrix;
		}
		if (item.type == path_data_type::change_origin) {
			_Origin = item.data.origin;
		}
	}
	_Has_current_point = p._Has_current_point;
	_Current_point = p._Current_point;
	_Last_move_to_point = p._Last_move_to_point;
}

void path_builder::append(const path_builder& p) {
	lock_guard<decltype(p._Lock)> plg(p._Lock);
	lock_guard<decltype(_Lock)> lg(_Lock);
	for (const auto& item : p._Data) {
		_Data.push_back(item);
		if (item.type == path_data_type::change_matrix) {
			_Transform_matrix = item.data.matrix;
		}
		if (item.type == path_data_type::change_origin) {
			_Origin = item.data.origin;
		}
	}
	_Has_current_point = p._Has_current_point;
	_Current_point = p._Current_point;
	_Last_move_to_point = p._Last_move_to_point;
}

void path_builder::append(const vector<path_data>& p) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	for (const auto& item : p) {
		auto type = item.type;
		switch (type)
		{
		case path_data_type::move_to:
			_Has_current_point = true;
			_Current_point = item.data.move;
			_Last_move_to_point = item.data.move;
			break;
		case path_data_type::line_to:
			_Has_current_point = true;
			_Current_point = item.data.line;
			break;
		case path_data_type::curve_to:
			_Has_current_point = true;
			_Current_point = item.data.curve.pt3;
			break;
		case path_data_type::new_sub_path:
			_Has_current_point = false;
			break;
		case path_data_type::close_path:
			break;
		case path_data_type::rel_move_to:
			if (!_Has_current_point) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
			}
			_Current_point = item.data.move;
			break;
		case path_data_type::rel_line_to:
			if (!_Has_current_point) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
			}
			_Current_point = item.data.line;
			break;
		case path_data_type::rel_curve_to:
			if (!_Has_current_point) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
			}
			_Current_point = item.data.curve.pt3;
			break;
		case path_data_type::arc:
			_Set_current_point_and_last_move_to_point_for_arc(_Get_arc_as_beziers(item.data.arc.center, item.data.arc.radius, item.data.arc.angle1, item.data.arc.angle2, false, _Has_current_point, _Current_point));
			break;
		case path_data_type::arc_negative:
			_Set_current_point_and_last_move_to_point_for_arc(_Get_arc_as_beziers(item.data.arc.center, item.data.arc.radius, item.data.arc.angle1, item.data.arc.angle2, true, _Has_current_point, _Current_point));
			break;
		case path_data_type::change_matrix:
			_Transform_matrix = item.data.matrix;
			break;
		case path_data_type::change_origin:
			_Origin = item.data.origin;
			break;
		default:
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
			break;
		}
	}
}

bool path_builder::has_current_point() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Has_current_point;
}

point path_builder::get_current_point() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (_Has_current_point) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
	}
	return _Current_point;
}

void path_builder::new_sub_path() {
	lock_guard<decltype(_Lock)> lg(_Lock);
	path_data pd{ };
	pd.type = path_data_type::new_sub_path;
	pd.data.unused = 0;
	_Data.push_back(pd);
	_Has_current_point = false;
}

void path_builder::close_path() {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (_Has_current_point) {
		path_data pd{ };
		pd.type = path_data_type::close_path;
		pd.data.unused = 0;
		_Data.push_back(pd);
		_Current_point = _Last_move_to_point;
	}
}

point _Rotate_point(const point& pt, double angle, bool clockwise = true) {
	if (clockwise) {
		return{ pt.x * cos(angle) + pt.y * sin(angle), -(pt.x * -(sin(angle)) + pt.y * cos(angle)) };
	}
	else {
		return{ pt.x * cos(angle) + pt.y * sin(angle), pt.x * -(sin(angle)) + pt.y * cos(angle) };
	}
}

// Returns a path_data composed of 
vector<path_data> _Get_arc_as_beziers(const point& center, double radius, double angle1, double angle2, bool arcNegative, bool hasCurrentPoint, const point& currentPoint, const point& origin, const matrix_2d& matrix) {
	if (arcNegative) {
		while (angle2 > angle1) {
			angle2 -= _PI * 2.0;
		}
	}
	else {
		while (angle2 < angle1) {
			angle2 += _PI * 2.0;
		}
	}
	point pt0, pt1, pt2, pt3;
	int bezierCount = 1;
	double theta;
	if (arcNegative) {
		theta = angle1 - angle2;
	}
	else {
		theta = angle2 - angle1;
	}
	double phi;

	{
		// See: DeVeneza, Richard A., "How to determine the control points of a Bézier curve that approximates a small circular arc" (Nov. 2004) [ http://www.tinaja.com/glib/bezcirc2.pdf ].

		while (theta >= (_PI / 2.0)) {
			theta /= 2.0;
			bezierCount += bezierCount;
		}

		phi = theta / 2.0;

		auto cosinePhi = cos(phi);
		auto sinePhi = sin(phi);

		pt0.x = cosinePhi;
		pt0.y = -sinePhi;

		pt3.x = pt0.x;
		pt3.y = -pt0.y;

		pt1.x = (4.0 - cosinePhi) / 3.0;
		pt1.y = -(((1.0 - cosinePhi) * (3.0 - cosinePhi)) / (3.0 * sinePhi));

		pt2.x = pt1.x;
		pt2.y = -pt1.y;

	}

	{
		if (!arcNegative) {
			phi = -phi;
		}
		// Rotate all points to start with a zero angle.
		pt0 = _Rotate_point(pt0, phi);
		pt1 = _Rotate_point(pt1, phi);
		pt2 = _Rotate_point(pt2, phi);
		pt3 = _Rotate_point(pt3, phi);

		if (arcNegative) {
			auto tempPt = pt3;
			pt3 = pt0;
			pt0 = tempPt;
			tempPt = pt2;
			pt2 = pt1;
			pt1 = tempPt;
		}
	}

	auto currentTheta = angle1;
	path_builder pb;
	pb.set_origin(origin);
	pb.set_transform_matrix(matrix);
	
	const auto startPoint = center + _Rotate_point(pt0 * radius, currentTheta);
	if (hasCurrentPoint) {
		pb.move_to(currentPoint);
		pb.line_to(startPoint);
	}
	else {
		pb.move_to(startPoint);
	}

	// We start at the point derived from angle1 and continue adding beziers until the count reaches zero.
	// The point we have is already rotated by half of theta.
	for (; bezierCount > 0; bezierCount--) {
		pb.curve_to(
			center + _Rotate_point(pt1 * radius, currentTheta),
			center + _Rotate_point(pt2 * radius, currentTheta),
			center + _Rotate_point(pt3 * radius, currentTheta)
			);

		if (arcNegative) {
			currentTheta -= theta;
		}
		else {
			currentTheta += theta;
		}
	}
	return pb.get_data();
}

void path_builder::_Set_current_point_and_last_move_to_point_for_arc(const vector<path_data>& data) {
	if (data.size() > 0) {
		const auto& lastItem = *data.crbegin();
		if (lastItem.type == path_data_type::curve_to) {
			_Has_current_point = true;
			_Current_point = lastItem.data.curve.pt3;
		}
		else if (lastItem.type == path_data_type::line_to) {
			_Has_current_point = true;
			_Current_point = lastItem.data.line;
		}
		else if (lastItem.type == path_data_type::move_to) {
			_Has_current_point = true;
			_Current_point = lastItem.data.move;
			_Last_move_to_point = lastItem.data.move;
		}
		else {
			assert("_Get_arc_as_beziers returned unexpected path_data value." && false);
		}
	}
}

void path_builder::arc(const point& center, double radius, double angle1, double angle2) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	path_data pd;
	pd.type = path_data_type::arc;
	pd.data.arc.center = center;
	pd.data.arc.radius = radius;
	pd.data.arc.angle1 = angle1;
	pd.data.arc.angle2 = angle2;
	_Data.push_back(pd);
	// Update the current point.
	_Set_current_point_and_last_move_to_point_for_arc(_Get_arc_as_beziers(center, radius, angle1, angle2, false, _Has_current_point, _Current_point));
}

void path_builder::arc_negative(const point& center, double radius, double angle1, double angle2) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	path_data pd;
	pd.type = path_data_type::arc_negative;
	pd.data.arc.center = center;
	pd.data.arc.radius = radius;
	pd.data.arc.angle1 = angle1;
	pd.data.arc.angle2 = angle2;
	_Data.push_back(pd);
	// Update the current point.
	_Set_current_point_and_last_move_to_point_for_arc(_Get_arc_as_beziers(center, radius, angle1, angle2, true, _Has_current_point, _Current_point));
}

void path_builder::curve_to(const point& pt0, const point& pt1, const point& pt2) {
	if (!_Has_current_point) {
		move_to(pt0);
	}
	lock_guard<decltype(_Lock)> lg(_Lock);
	path_data pd;
	pd.type = path_data_type::curve_to;
	pd.data.curve.pt1 = pt0;
	pd.data.curve.pt2 = pt1;
	pd.data.curve.pt3 = pt2;
	_Data.push_back(pd);
	_Has_current_point = true;
	_Current_point = pd.data.curve.pt3;
}

void path_builder::line_to(const point& pt) {
	if (!_Has_current_point) {
		move_to(pt);
		return;
	}
	lock_guard<decltype(_Lock)> lg(_Lock);
	path_data pd;
	pd.type = path_data_type::line_to;
	pd.data.line = pt;
	_Data.push_back(pd);
	_Has_current_point = true;
	_Current_point = pd.data.line;
}

void path_builder::move_to(const point& pt) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	path_data pd;
	pd.type = path_data_type::move_to;
	pd.data.move = pt;
	_Data.push_back(pd);
	_Has_current_point = true;
	_Current_point = pd.data.move;
}

void path_builder::rect(const experimental::io2d::rectangle& r) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	move_to({ r.x, r.y });
	rel_line_to({ r.width, 0.0 });
	rel_line_to({ 0.0, r.height });
	rel_line_to({ -r.width, 0.0 });
	close_path();
}

void path_builder::rel_curve_to(const point& dpt0, const point& dpt1, const point& dpt2) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (!_Has_current_point) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
	}
	path_data pd;
	pd.type = path_data_type::rel_curve_to;
	pd.data.curve.pt1 = dpt0;
	pd.data.curve.pt2 = dpt1;
	pd.data.curve.pt3 = dpt2;
	_Data.push_back(pd);
	_Has_current_point = true;
	_Current_point = _Current_point + dpt2;
}

void path_builder::rel_line_to(const point& dpt) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (!_Has_current_point) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
	}
	path_data pd;
	pd.type = path_data_type::rel_line_to;
	pd.data.line = dpt;
	_Data.push_back(pd);
	_Has_current_point = true;
	_Current_point = _Current_point + dpt;
}

void path_builder::rel_move_to(const point& dpt) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (!_Has_current_point) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
	}
	path_data pd;
	pd.type = path_data_type::rel_move_to;
	pd.data.move = dpt;
	_Data.push_back(pd);
	_Has_current_point = true;
	_Current_point = _Current_point + dpt;
}

void path_builder::set_transform_matrix(const matrix_2d& m) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Transform_matrix = m;
	path_data pd;
	pd.type = path_data_type::change_matrix;
	pd.data.matrix = m;
	_Data.push_back(pd);
}

matrix_2d path_builder::get_transform_matrix() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Transform_matrix;
}

void path_builder::set_origin(const point& pt) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Origin = pt;
	path_data pd;
	pd.type = path_data_type::change_origin;
	pd.data.origin = pt;
	_Data.push_back(pd);
}

point path_builder::get_origin() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Origin;
}

vector<path_data> path_builder::get_data() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return vector<path_data>(_Data);
}

const vector<path_data>& path_builder::get_data_ref() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Data;
}

point operator*(double lhs, const point& rhs) {
	return{ lhs * rhs.x, lhs * rhs.y };
}

// See: http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
bool _Almost_equal_relative(double a, double b, double epsilon) {
	auto diff = abs(a - b);
	a = abs(a);
	b = abs(b);
	auto largest = (b > a) ? b : a;
	if (diff <= largest * epsilon) {
		return true;
	}
	return false;
}

double _Curve_value_for_t(double a, double b, double c, double d, double t) {
	return pow(1.0 - t, 3.0) * a + 3.0 * pow(1.0 - t, 2.0) * t * b + 3.0 * (1.0 - t) * pow(t, 2.0) * c + pow(t, 3.0) * d;
}

inline point _Cubic_bezier_derivative_for_t(const point& pt0, const point& pt1, const point& pt2, const point& pt3, double t) {
	return 3.0 * pow(1.0 - t, 2.0) * (pt1 - pt0) + 6.0 * (1.0 - t) * t * (pt2 - pt1) + 3.0 * pow(t, 2.0) * (pt3 - pt2);
}

inline bool _Same_sign(double lhs, double rhs) {
	return ((lhs < 0.0) && (rhs < 0.0)) || ((lhs > 0.0) && (rhs > 0.0));
}

double _Find_t_for_d_of_t_equal_zero(const point& pt0, const point& pt1, const point& pt2, const point& pt3, double t0, double t2, const bool findX, const double epsilon = numeric_limits<double>::epsilon()) {
	// Validate that t0 is the low value, t2 is the high value, t0 is not equal to t2, and that both are in the range [0.0, 1.0].
	assert(t0 >= 0.0 && t0 < t2 && t2 <= 1.0);
	// Find the midpoint.
	double t1 = (t2 - t0) / 2.0 + t0;

	double t1Previous = -1.0;
	// Short-circuit and return current t0 if t0 and t1 are equal or t1 and t1Previous are equal to avoid infinite looping.
	if (_Almost_equal_relative(t0, t1, epsilon) || _Almost_equal_relative(t1, t1Previous, epsilon)) {
		return t0;
	}
	auto dt0 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, t0);
	auto dt2 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, t2);

	if (findX) {
		assert(!_Same_sign(dt0.x, dt2.x));
	}
	else {
		assert(!_Same_sign(dt0.y, dt2.y));
	}

	auto dt1 = +_Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, t1);

	// If t0 and t1 are equal or t1 and t1Previous are equal, we can no longer get a meaningful t1 value so the value of t0 will have to be accepted as close enough.
	while (!_Almost_equal_relative(t0, t1, epsilon) && !_Almost_equal_relative(t1, t1Previous, epsilon)) {
		if (findX) {
			if (_Almost_equal_relative(dt1.x, 0.0, epsilon)) {
				return t1;
			}
			if (_Same_sign(dt0.x, dt1.x)) {
				// Since t0 and t2 are different signs and t0 and t1 are the same sign, we know our value lies between t1 and t2 so set t0 = t1 and calculate the new t1.
				t0 = t1;
				t1Previous = t1;
				t1 = (t2 - t0) / 2.0 + t0;
			}
			else {
				assert(_Same_sign(dt1.x, dt2.x));
				// Since t0 and t2 are different signs and t1 and t2 are the same sign, we know our value lies between t0 and t1 so set t2 = t1 and calculate the new t1.
				t2 = t1;
				t1Previous = t1;
				t1 = (t2 - t0) / 2.0 + t0;
			}
		}
		else {
			if (_Almost_equal_relative(dt1.y, 0.0, epsilon)) {
				return t1;
			}
			if (_Same_sign(dt0.y, dt1.y)) {
				// Since t0 and t2 are different signs and t0 and t1 are the same sign, we know our value lies between t1 and t2 so set t0 = t1 and calculate the new t1.
				t0 = t1;
				t1Previous = t1;
				t1 = (t2 - t0) / 2.0 + t0;
			}
			else {
				assert(_Same_sign(dt1.y, dt2.y));
				// Since t0 and t2 are different signs and t1 and t2 are the same sign, we know our value lies between t0 and t1 so set t2 = t1 and calculate the new t1.
				t2 = t1;
				t1Previous = t1;
				t1 = (t2 - t0) / 2.0 + t0;
			}
		}
	}
	return t1;
}

void _Curve_to_extents(const point& pt0, const point& pt1, const point& pt2, const point& pt3, point& extents0, point& extents1) {
	// We know at a minimum that the extents are the two knots, pt0 and pt3. The only question is whether the extents go beyond those two points.
	extents0.x = min(pt0.x, pt3.x);
	extents0.y = min(pt0.y, pt3.y);
	extents1.x = max(pt0.x, pt3.x);
	extents1.y = max(pt0.y, pt3.y);

	// Find X's and Ys (between 0 and 2).
	int numPoints = 0;
	int numXs = 0;
	int numYs = 0;

	const auto dt0 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, 0.0);
	const auto dt1 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, 0.5);
	const auto dt2 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, 1.0);
	bool foundLowX = false;
	bool foundHighX = false;
	bool foundLowY = false;
	bool foundHighY = false;

	const double epsilon = numeric_limits<double>::epsilon();

	// X values
	if (_Almost_equal_relative(dt0.x, 0.0, epsilon)) {
		assert(numXs == 0);
		// First knot is critical. We already assigned it so we're done with that.
		foundLowX = true;
		numPoints++;
		numXs++;
		if (_Same_sign(dt1.x, dt2.x)) {
			// No second critical point so the second knot is the other extent and we already assigned it so we're done with that.
			foundHighX = true;
			numPoints++;
			numXs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.5, 1.0, true);
			auto xval = _Curve_value_for_t(pt0.x, pt1.x, pt2.x, pt3.x, t);
			// We do this min/max assignment because critical points just signal a change in curve direction, not that the critical point is actually a min/max point.
			extents0.x = min(extents0.x, xval);
			extents1.x = max(extents1.x, xval);
			foundHighX = true;
			numPoints++;
			numXs++;
		}
	}
	if (_Almost_equal_relative(dt1.x, 0.0, epsilon)) {
		assert(numXs == 0);
		// Center is only critical.
		auto cxval = _Curve_value_for_t(pt0.x, pt1.x, pt2.x, pt3.x, 0.5);
		// Arbitrarily use pt3.x rather than pt0.x; they are the same value regardless.
		assert(_Almost_equal_relative(pt0.x, pt3.x, epsilon));
		extents0.x = min(cxval, pt3.x);
		extents1.x = max(cxval, pt3.x);
		numPoints += 2;
		numXs += 2;
	}
	if (_Almost_equal_relative(dt2.x, 0.0, epsilon)) {
		assert(numXs == 0);
		numPoints++;
		numXs++;
		foundHighX = true;
		if (_Same_sign(dt0.x, dt1.x)) {
			// No second critical point so the first knot is the other extent and we already assigned it so we're done with that.
			foundLowX = true;
			numPoints++;
			numXs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.0, 0.5, true);
			auto xval = _Curve_value_for_t(pt0.y, pt1.y, pt2.y, pt3.y, t);
			// We do this min/max assignment because critical points just signal a change in curve direction, not that the critical point is actually a min/max point.
			extents0.x = min(extents0.x, xval);
			extents1.x = max(extents1.x, xval);
			foundLowX = true;
			numPoints++;
			numXs++;
		}
	}
	if (numXs == 0) {
		if (_Same_sign(dt0.x, dt1.x) && _Same_sign(dt1.x, dt2.x)) {
			// No critical points on X: use ends.
			extents0.x = min(pt0.x, pt3.x);
			extents1.x = max(pt0.x, pt3.x);
			foundLowX = true;
			foundHighX = true;
			numPoints += 2;
			numXs += 2;
		}
	}
	if (!foundLowX) {
		if (_Same_sign(dt0.x, dt1.x)) {
			// There is no critical point between dt0.x and dt1.x so the lowX point is pt0.x, which we already assigned.
			foundLowX = true;
			numPoints++;
			numXs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.0, 0.5, true);
			auto xval = _Curve_value_for_t(pt0.x, pt1.x, pt2.x, pt3.x, t);
			// We do this min/max assignment because critical points just signal a change in curve direction, not that the critical point is actually a min/max point.
			extents0.x = min(extents0.x, xval);
			extents1.x = max(extents1.x, xval);
			foundLowX = true;
			numPoints++;
			numXs++;
		}
	}
	if (!foundHighX) {
		if (_Same_sign(dt1.x, dt2.x)) {
			// There is no critical point between dt1.x and dt2.x so the highX point is pt3.x, which we already assigned.
			foundHighX = true;
			numPoints++;
			numXs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.5, 1.0, true);
			auto xval = _Curve_value_for_t(pt0.x, pt1.x, pt2.x, pt3.x, t);
			// We do this min/max assignment because critical points just signal a change in curve direction, not that the critical point is actually a min/max point.
			extents0.x = min(extents0.x, xval);
			extents1.x = max(extents1.x, xval);
			foundHighX = true;
			numPoints++;
			numXs++;
		}
	}

	// Y values
	if (_Almost_equal_relative(dt0.y, 0.0, epsilon)) {
		assert(numYs == 0);
		// First knot is critical. We already assigned it so we're done with that.
		foundLowY = true;
		numPoints++;
		numYs++;
		if (_Same_sign(dt1.y, dt2.y)) {
			// No second critical point so the second knot is the other extent and we already assigned it so we're done with that.
			foundHighY = true;
			numPoints++;
			numYs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.5, 1.0, true);
			auto yval = _Curve_value_for_t(pt0.y, pt1.y, pt2.y, pt3.y, t);
			// We do this min/max assignment because critical points just signal a change in curve direction, not that the critical point is actually a min/max point.
			extents0.y = min(extents0.y, yval);
			extents1.y = max(extents1.y, yval);
			foundHighY = true;
			numPoints++;
			numYs++;
		}
	}
	if (_Almost_equal_relative(dt1.y, 0.0, epsilon)) {
		assert(numYs == 0);
		// Center is only critical.
		auto cyval = _Curve_value_for_t(pt0.y, pt1.y, pt2.y, pt3.y, 0.5);
		// Arbitrarily use pt3.y rather than pt0.y; they are the same value regardless.
		assert(_Almost_equal_relative(pt0.y, pt3.y, epsilon));
		extents0.y = min(cyval, pt3.y);
		extents1.y = max(cyval, pt3.y);
		numPoints += 2;
		numYs += 2;
	}
	if (_Almost_equal_relative(dt2.y, 0.0, epsilon)) {
		assert(numYs == 0);
		numPoints++;
		numYs++;
		foundHighY = true;
		if (_Same_sign(dt0.y, dt1.y)) {
			// No second critical point so the first knot is the other extent and we already assigned it so we're done with that.
			foundLowY = true;
			numPoints++;
			numYs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.0, 0.5, true);
			auto yval = _Curve_value_for_t(pt0.y, pt1.y, pt2.y, pt3.y, t);
			// We do this min/max assignment because critical points just signal a change in curve direction, not that the critical point is actually a min/max point.
			extents0.y = min(extents0.y, yval);
			extents1.y = max(extents1.y, yval);
			foundLowY = true;
			numPoints++;
			numYs++;
		}
	}
	if (numYs == 0) {
		if (_Same_sign(dt0.y, dt1.y) && _Same_sign(dt1.y, dt2.y)) {
			// No critical points on Y: use ends.
			extents0.y = min(pt0.y, pt3.y);
			extents1.y = max(pt0.y, pt3.y);
			foundLowY = true;
			foundHighY = true;
			numPoints += 2;
			numYs += 2;
		}
	}
	if (!foundLowY) {
		if (_Same_sign(dt0.y, dt1.y)) {
			// There is no critical point between dt0.y and dt1.y so the lowY point is pt0.y, which we already assigned.
			foundLowY = true;
			numPoints++;
			numYs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.0, 0.5, false);
			auto yval = _Curve_value_for_t(pt0.y, pt1.y, pt2.y, pt3.y, t);
			extents0.y = min(extents0.y, yval);
			extents1.y = max(extents1.y, yval);
			foundLowY = true;
			numPoints++;
			numYs++;
		}
	}
	if (!foundHighY) {
		if (_Same_sign(dt1.y, dt2.y)) {
			// There is no critical point between dt1.y and dt2.y so the lowY point is pt3.y, which we already assigned.
			foundHighY = true;
			numPoints++;
			numYs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.5, 1.0, false);
			auto yval = _Curve_value_for_t(pt0.y, pt1.y, pt2.y, pt3.y, t);
			extents0.y = min(extents0.y, yval);
			extents1.y = max(extents1.y, yval);
			foundHighY = true;
			numPoints++;
			numYs++;
		}
	}
	assert(foundLowX && foundLowY && foundHighX && foundHighY && numPoints == 4 && numXs == 2 && numYs == 2);
}

rectangle path_builder::get_path_extents() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	point pt0{ };
	point pt1{ };

	matrix_2d currMatrix = matrix_2d::init_identity();
	point currOrigin{ };

	bool hasLastPoint = false;
	bool hasExtents = false;

	point lastPoint{ };

	// pt0 will hold min values; pt1 will hold max values.
	for (auto i = 0U; i < _Data.size(); i++) {
		const auto& item = _Data[i];
		auto type = item.type;
		switch (type)
		{
		case std::experimental::io2d::path_data_type::move_to:
			lastPoint = currMatrix.transform_point(item.data.move - currOrigin) + currOrigin;
			hasLastPoint = true;
			break;
		case std::experimental::io2d::path_data_type::line_to:
			if (hasLastPoint) {
				auto itemPt = currMatrix.transform_point(item.data.line - currOrigin) + currOrigin;
				if (!hasExtents) {
					hasExtents = true;
					pt0.x = min(lastPoint.x, itemPt.x);
					pt0.y = min(lastPoint.y, itemPt.y);
					pt1.x = max(lastPoint.x, itemPt.x);
					pt1.y = max(lastPoint.y, itemPt.y);
				}
				else {
					pt0.x = min(min(pt0.x, lastPoint.x), itemPt.x);
					pt0.y = min(min(pt0.y, lastPoint.y), itemPt.y);
					pt1.x = max(max(pt1.x, lastPoint.x), itemPt.x);
					pt1.y = max(max(pt1.y, lastPoint.y), itemPt.y);
				}
			}
			else {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
			}
			break;
		case std::experimental::io2d::path_data_type::curve_to:
		{
			if (!hasLastPoint) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
			}
			point cte0{ }, cte1{ };
			auto itemPt1 = currMatrix.transform_point(item.data.curve.pt1 - currOrigin) + currOrigin;
			auto itemPt2 = currMatrix.transform_point(item.data.curve.pt2 - currOrigin) + currOrigin;
			auto itemPt3 = currMatrix.transform_point(item.data.curve.pt3 - currOrigin) + currOrigin;
			_Curve_to_extents(lastPoint, itemPt1, itemPt2, itemPt3, cte0, cte1);
			if (!hasExtents) {
				hasExtents = true;
				pt0.x = min(cte0.x, cte1.x);
				pt0.y = min(cte0.y, cte1.y);
				pt1.x = max(cte0.x, cte1.x);
				pt1.y = max(cte0.y, cte1.y);
			}
			else {
				pt0.x = min(min(pt0.x, cte0.x), cte1.x);
				pt0.y = min(min(pt0.y, cte0.y), cte1.y);
				pt1.x = max(max(pt1.x, cte0.x), cte1.x);
				pt1.y = max(max(pt1.y, cte0.y), cte1.y);
			}
		}
			break;
		case std::experimental::io2d::path_data_type::new_sub_path:
			hasLastPoint = false;
			break;
		case std::experimental::io2d::path_data_type::close_path:
			hasLastPoint = false;
			break;
		case std::experimental::io2d::path_data_type::rel_move_to:
			if (!hasLastPoint) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
			}
			lastPoint = currMatrix.transform_point((item.data.move + lastPoint) - currOrigin) + currOrigin;
			hasLastPoint = true;
			break;
		case std::experimental::io2d::path_data_type::rel_line_to:
			if (hasLastPoint) {
				auto itemPt = currMatrix.transform_point((item.data.line + lastPoint) - currOrigin) + currOrigin;
				if (!hasExtents) {
					hasExtents = true;
					pt0.x = min(lastPoint.x, itemPt.x);
					pt0.y = min(lastPoint.y, itemPt.y);
					pt1.x = max(lastPoint.x, itemPt.x);
					pt1.y = max(lastPoint.y, itemPt.y);
				}
				else {
					pt0.x = min(min(pt0.x, lastPoint.x), itemPt.x);
					pt0.y = min(min(pt0.y, lastPoint.y), itemPt.y);
					pt1.x = max(max(pt1.x, lastPoint.x), itemPt.x);
					pt1.y = max(max(pt1.y, lastPoint.y), itemPt.y);
				}
			}
			else {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
			}
			break;
		case std::experimental::io2d::path_data_type::rel_curve_to:
		{
			if (!hasLastPoint) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
			}
			point cte0{ }, cte1{ };
			auto itemPt1 = currMatrix.transform_point((item.data.curve.pt1 + lastPoint) - currOrigin) + currOrigin;
			auto itemPt2 = currMatrix.transform_point((item.data.curve.pt2 + lastPoint) - currOrigin) + currOrigin;
			auto itemPt3 = currMatrix.transform_point((item.data.curve.pt3 + lastPoint) - currOrigin) + currOrigin;
			_Curve_to_extents(lastPoint, itemPt1, itemPt2, itemPt3, cte0, cte1);
			if (!hasExtents) {
				hasExtents = true;
				pt0.x = min(cte0.x, cte1.x);
				pt0.y = min(cte0.y, cte1.y);
				pt1.x = max(cte0.x, cte1.x);
				pt1.y = max(cte0.y, cte1.y);
			}
			else {
				pt0.x = min(min(pt0.x, cte0.x), cte1.x);
				pt0.y = min(min(pt0.y, cte0.y), cte1.y);
				pt1.x = max(max(pt1.x, cte0.x), cte1.x);
				pt1.y = max(max(pt1.y, cte0.y), cte1.y);
			}
		}
			break;
		case std::experimental::io2d::path_data_type::arc:
		{
			auto data = _Get_arc_as_beziers(item.data.arc.center, item.data.arc.radius, item.data.arc.angle1, item.data.arc.angle2, false, hasLastPoint, lastPoint, currOrigin, currMatrix);
			for (const auto& arcItem : data) {
				switch (arcItem.type) {
				case std::experimental::io2d::path_data_type::move_to:
					lastPoint = currMatrix.transform_point(arcItem.data.move - currOrigin) + currOrigin;
					hasLastPoint = true;
					break;
				case std::experimental::io2d::path_data_type::line_to:
					if (hasLastPoint) {
						auto itemPt = currMatrix.transform_point(arcItem.data.line - currOrigin) + currOrigin;
						if (!hasExtents) {
							hasExtents = true;
							pt0.x = min(lastPoint.x, itemPt.x);
							pt0.y = min(lastPoint.y, itemPt.y);
							pt1.x = max(lastPoint.x, itemPt.x);
							pt1.y = max(lastPoint.y, itemPt.y);
						}
						else {
							pt0.x = min(min(pt0.x, lastPoint.x), itemPt.x);
							pt0.y = min(min(pt0.y, lastPoint.y), itemPt.y);
							pt1.x = max(max(pt1.x, lastPoint.x), itemPt.x);
							pt1.y = max(max(pt1.y, lastPoint.y), itemPt.y);
						}
					}
					else {
						_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
					}
					break;
				case std::experimental::io2d::path_data_type::curve_to:
				{
					if (!hasLastPoint) {
						_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
					}
					point cte0{ }, cte1{ };
					auto itemPt1 = currMatrix.transform_point(arcItem.data.curve.pt1 - currOrigin) + currOrigin;
					auto itemPt2 = currMatrix.transform_point(arcItem.data.curve.pt2 - currOrigin) + currOrigin;
					auto itemPt3 = currMatrix.transform_point(arcItem.data.curve.pt3 - currOrigin) + currOrigin;
					_Curve_to_extents(lastPoint, itemPt1, itemPt2, itemPt3, cte0, cte1);
					if (!hasExtents) {
						hasExtents = true;
						pt0.x = min(cte0.x, cte1.x);
						pt0.y = min(cte0.y, cte1.y);
						pt1.x = max(cte0.x, cte1.x);
						pt1.y = max(cte0.y, cte1.y);
					}
					else {
						pt0.x = min(min(pt0.x, cte0.x), cte1.x);
						pt0.y = min(min(pt0.y, cte0.y), cte1.y);
						pt1.x = max(max(pt1.x, cte0.x), cte1.x);
						pt1.y = max(max(pt1.y, cte0.y), cte1.y);
					}
				}
					break;
				case path_data_type::change_origin:
				{
					// Ignore, we're already dealing with this.
				}
					break;

				case path_data_type::change_matrix:
				{
					// Ignore, we're already dealing with this.
				}
					break;
				case path_data_type::new_sub_path:
				{
					// Ignore, we don't need this.
				}
					break;
				default:
					assert("Unexpected path_data_type in arc." && false);
					break;
				}
			}
		}
			break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			auto data = _Get_arc_as_beziers(item.data.arc.center, item.data.arc.radius, item.data.arc.angle1, item.data.arc.angle2, true, hasLastPoint, lastPoint, currOrigin, currMatrix);
			for (const auto& arcItem : data) {
				switch (arcItem.type) {
				case std::experimental::io2d::path_data_type::move_to:
					lastPoint = currMatrix.transform_point(arcItem.data.move - currOrigin) + currOrigin;
					hasLastPoint = true;
					break;
				case std::experimental::io2d::path_data_type::line_to:
					if (hasLastPoint) {
						auto itemPt = currMatrix.transform_point(arcItem.data.line - currOrigin) + currOrigin;
						if (!hasExtents) {
							hasExtents = true;
							pt0.x = min(lastPoint.x, itemPt.x);
							pt0.y = min(lastPoint.y, itemPt.y);
							pt1.x = max(lastPoint.x, itemPt.x);
							pt1.y = max(lastPoint.y, itemPt.y);
						}
						else {
							pt0.x = min(min(pt0.x, lastPoint.x), itemPt.x);
							pt0.y = min(min(pt0.y, lastPoint.y), itemPt.y);
							pt1.x = max(max(pt1.x, lastPoint.x), itemPt.x);
							pt1.y = max(max(pt1.y, lastPoint.y), itemPt.y);
						}
					}
					else {
						_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
					}
					break;
				case std::experimental::io2d::path_data_type::curve_to:
				{
					if (!hasLastPoint) {
						_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
					}
					point cte0{ }, cte1{ };
					auto itemPt1 = currMatrix.transform_point(arcItem.data.curve.pt1 - currOrigin) + currOrigin;
					auto itemPt2 = currMatrix.transform_point(arcItem.data.curve.pt2 - currOrigin) + currOrigin;
					auto itemPt3 = currMatrix.transform_point(arcItem.data.curve.pt3 - currOrigin) + currOrigin;
					_Curve_to_extents(lastPoint, itemPt1, itemPt2, itemPt3, cte0, cte1);
					if (!hasExtents) {
						hasExtents = true;
						pt0.x = min(cte0.x, cte1.x);
						pt0.y = min(cte0.y, cte1.y);
						pt1.x = max(cte0.x, cte1.x);
						pt1.y = max(cte0.y, cte1.y);
					}
					else {
						pt0.x = min(min(pt0.x, cte0.x), cte1.x);
						pt0.y = min(min(pt0.y, cte0.y), cte1.y);
						pt1.x = max(max(pt1.x, cte0.x), cte1.x);
						pt1.y = max(max(pt1.y, cte0.y), cte1.y);
					}
				}
					break;
				case path_data_type::change_origin:
				{
					// Ignore, we're already dealing with this.
				}
					break;

				case path_data_type::change_matrix:
				{
					// Ignore, we're already dealing with this.
				}
					break;
				case path_data_type::new_sub_path:
				{
					// Ignore, we don't need this.
				}
					break;
				default:
					assert("Unexpected path_data_type in arc." && false);
					break;
				}
			}
		}
			break;
		case std::experimental::io2d::path_data_type::change_matrix:
			currMatrix = item.data.matrix;
			break;
		case std::experimental::io2d::path_data_type::change_origin:
			currOrigin = item.data.origin;
			break;
		default:
			assert("Unknown path_data_type in path_data." && false);
			break;
		}
	}
	return{ pt0.x, pt0.y, pt1.x - pt0.x, pt1.y - pt0.y };
}

void path_builder::reset() {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Data = { };
	_Has_current_point = { };
	_Current_point = { };
	_Extents_pt0 = { };
	_Extents_pt1 = { };
	_Transform_matrix = matrix_2d::init_identity();
	_Origin = { };
}

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				bool operator==(const path_data& lhs, const path_data& rhs) {
					if (lhs.type != rhs.type) {
						return false;
					}
					auto type = lhs.type;
					switch (type)
					{
					case std::experimental::io2d::path_data_type::move_to:
						return lhs.data.move == rhs.data.move;
					case std::experimental::io2d::path_data_type::line_to:
						return lhs.data.line == rhs.data.line;
					case std::experimental::io2d::path_data_type::curve_to:
						return lhs.data.curve.pt1 == rhs.data.curve.pt1 &&
							lhs.data.curve.pt2 == rhs.data.curve.pt2 &&
							lhs.data.curve.pt3 == rhs.data.curve.pt3;
					case std::experimental::io2d::path_data_type::new_sub_path:
						return true;
					case std::experimental::io2d::path_data_type::close_path:
						return true;
					case std::experimental::io2d::path_data_type::rel_move_to:
						return lhs.data.move == rhs.data.move;
					case std::experimental::io2d::path_data_type::rel_line_to:
						return lhs.data.line == rhs.data.line;
					case std::experimental::io2d::path_data_type::rel_curve_to:
						return lhs.data.curve.pt1 == rhs.data.curve.pt1 &&
							lhs.data.curve.pt2 == rhs.data.curve.pt2 &&
							lhs.data.curve.pt3 == rhs.data.curve.pt3;
					case std::experimental::io2d::path_data_type::arc:
						return lhs.data.arc.angle1 == rhs.data.arc.angle1 &&
							lhs.data.arc.angle2 == rhs.data.arc.angle2 &&
							lhs.data.arc.center == rhs.data.arc.center &&
							lhs.data.arc.radius == rhs.data.arc.radius;
					case std::experimental::io2d::path_data_type::arc_negative:
						return lhs.data.arc.angle1 == rhs.data.arc.angle1 &&
							lhs.data.arc.angle2 == rhs.data.arc.angle2 &&
							lhs.data.arc.center == rhs.data.arc.center &&
							lhs.data.arc.radius == rhs.data.arc.radius;
					case std::experimental::io2d::path_data_type::change_matrix:
						return lhs.data.matrix == rhs.data.matrix;
					case std::experimental::io2d::path_data_type::change_origin:
						return lhs.data.origin == rhs.data.origin;
					default:
						assert("Unknown path_data_type!" && false);
						return false;
				}
				}
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}
