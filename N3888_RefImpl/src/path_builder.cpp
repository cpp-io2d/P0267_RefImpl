#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"
#include <algorithm>

using namespace std;
using namespace std::experimental::drawing;

path_builder::path_builder()
	: _Data()
	, _Has_current_point()
	, _Current_point()
	, _Extents_pt0()
	, _Extents_pt1()
	, _Transform_matrix(matrix::init_identity()) {
}

path_builder::path_builder(path_builder&& other)
	: _Data(move(other._Data))
	, _Has_current_point(move(other._Has_current_point))
	, _Current_point(move(other._Current_point))
	, _Extents_pt0(move(other._Extents_pt0))
	, _Extents_pt1(move(other._Extents_pt1))
	, _Transform_matrix(move(other._Transform_matrix)) {
}

path_builder& path_builder::operator=(path_builder&& other) {
	if (this != &other) {
		_Data = move(other._Data);
		_Has_current_point = move(other._Has_current_point);
		_Current_point = move(other._Current_point);
		_Extents_pt0 = move(other._Extents_pt0);
		_Extents_pt1 = move(other._Extents_pt1);
		_Transform_matrix = move(other._Transform_matrix);
	}
	return *this;
}

path path_builder::get_path() const {
	return path(*this);
}

path path_builder::get_path_flat() const {
	throw runtime_error("Not implemented yet.");
}

bool path_builder::has_current_point() {
	return _Has_current_point;
}

void path_builder::append_path(const path& p) {
	const auto& data = p.get_data_ref();
	for (const auto& item : data) {
		_Data.push_back(item);
	}
}

void path_builder::append_path(const path_builder& p) {
	for (const auto& item : p._Data) {
		_Data.push_back(item);
	}
}

point path_builder::get_current_point() {
	assert(has_current_point());
	return point((*_Data.crend()).point);
}

void path_builder::new_sub_path() {
	path_data pd{ };
	pd.header.type = path_data_type::new_sub_path;
	pd.header.length = 1;
	_Data.push_back(pd);
}

void path_builder::close_path() {
	path_data pd{ };
	pd.header.type = path_data_type::close_path;
	pd.header.length = 1;
	_Data.push_back(pd);
}

point _Rotate_point(const point& pt, double angle, bool clockwise = true) {
	if (clockwise) {
		return{ pt.x * cos(angle) + pt.y * sin(angle), -(pt.x * -(sin(angle)) + pt.y * cos(angle)) };
	}
	else {
		return{ pt.x * cos(angle) + pt.y * sin(angle), pt.x * -(sin(angle)) + pt.y * cos(angle) };
	}
}

void _Add_arc_as_beziers_to_path_builder(const point& center, double radius, double angle1, double angle2, path_builder& pb, bool arcNegative = false) {
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

	if (pb.has_current_point()) {
		pb.line_to(center + _Rotate_point(pt0 * radius, currentTheta));
	}
	else {
		pb.new_sub_path();
		pb.move_to(center + _Rotate_point(pt0 * radius, currentTheta));
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
	pb.close_path();
}

void path_builder::arc(const point& center, double radius, double angle1, double angle2) {
	//auto startPt = _Rotate_point({ radius, 0.0 }, angle1) + center;
	//if (_Has_current_point) {
	//	line_to(startPt);
	//}
	//else {
	//	//new_sub_path();
	//	move_to(startPt);
	//}
	_Add_arc_as_beziers_to_path_builder(center, radius, angle1, angle2, *this, false);
	close_path();
}

void path_builder::arc_negative(const point& center, double radius, double angle1, double angle2) {
	//auto startPt = _Rotate_point({ radius, 0.0 }, angle1) + center;
	//if (_Has_current_point) {
	//	line_to(startPt);
	//}
	//else {
	//	//new_sub_path();
	//	move_to(startPt);
	//}
	_Add_arc_as_beziers_to_path_builder(center, radius, angle1, angle2, *this, true);
	close_path();
}

void path_builder::curve_to(const point& pt0, const point& pt1, const point& pt2) {
	if (!_Has_current_point) {
		move_to(pt0);
	}
	path_data pd;
	pd.header.type = path_data_type::curve_to;
	pd.header.length = 4;
	_Data.push_back(pd);
	pd = { };
	pd.point = _Transform_matrix.transform_point(pt0);
	_Data.push_back(pd);
	pd.point = _Transform_matrix.transform_point(pt1);
	_Data.push_back(pd);
	pd.point = _Transform_matrix.transform_point(pt2);
	_Data.push_back(pd);
	_Has_current_point = true;
	_Current_point = _Transform_matrix.transform_point(pt2);
}

void path_builder::line_to(const point& pt) {
	path_data pd;
	if (!_Has_current_point) {
		move_to(pt);
		return;
	}
	pd.header.type = path_data_type::line_to;
	pd.header.length = 2;
	_Data.push_back(pd);
	pd = { };
	pd.point = _Transform_matrix.transform_point(pt);
	_Data.push_back(pd);
	_Has_current_point = true;
	_Current_point = _Transform_matrix.transform_point(pt);
}

void path_builder::move_to(const point& pt) {
	path_data pd;
	pd.header.type = path_data_type::move_to;
	pd.header.length = 2;
	_Data.push_back(pd);
	pd = { };
	pd.point = _Transform_matrix.transform_point(pt);
	_Data.push_back(pd);
	_Has_current_point = true;
	_Current_point = _Transform_matrix.transform_point(pt);
}

void path_builder::rectangle(const experimental::drawing::rectangle& rect) {
	move_to({ rect.x, rect.y });
	rel_line_to({ rect.width, 0.0 });
	rel_line_to({ 0.0, rect.height });
	rel_line_to({ -rect.width, 0.0 });
	close_path();
}

void path_builder::rel_curve_to(const point& dpt0, const point& dpt1, const point& dpt2) {
	if (!_Has_current_point) {
		throw drawing_exception(status::no_current_point);
	}
	curve_to(dpt0 + _Current_point, dpt1 + _Current_point, dpt2 + _Current_point);
}

void path_builder::rel_line_to(const point& dpt) {
	if (!_Has_current_point) {
		throw drawing_exception(status::no_current_point);
	}
	line_to(dpt + _Current_point);
}

void path_builder::rel_move_to(const point& dpt) {
	if (!_Has_current_point) {
		throw drawing_exception(status::no_current_point);
	}
	move_to(dpt + _Current_point);
}

void path_builder::set_transform_matrix(const matrix& m) {
	_Transform_matrix = m;
}

matrix path_builder::get_transform_matrix() const {
	return _Transform_matrix;
}

vector<path_data> path_builder::get_data() const {
	return vector<path_data>(_Data);
}

const vector<path_data>& path_builder::get_data_ref() const {
	return _Data;
}

vector<path_data>& path_builder::get_data_ref() {
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
	//wcout << diff << L" : " << a << L" : " << b << L" : " << epsilon << L" : " << largest << L" : " << largest * epsilon << endl;
	if (diff <= largest * epsilon) {
		return true;
	}
	return false;
}

double _Curve_value_for_t(double a, double b, double c, double d, double t) {
	//double result{};
	return pow(1.0 - t, 3.0) * a + 3.0 * pow(1.0 - t, 2.0) * t * b + 3.0 * (1.0 - t) * pow(t, 2.0) * c + pow(t, 3.0) * d;
}

inline point _Cubic_bezier_derivative_for_t(const point& pt0, const point& pt1, const point& pt2, const point& pt3, double t) {
	return 3.0 * pow(1.0 - t, 2.0) * (pt1 - pt0) + 6.0 * (1.0 - t) * t * (pt2 - pt1) + 3.0 * pow(t, 2.0) * (pt3 - pt2);
}

inline bool _Same_sign(double lhs, double rhs) {
	return ((lhs < 0.0) && (rhs < 0.0)) || ((lhs > 0.0) && (rhs > 0.0));
}

double _Find_t_for_d_of_t_equal_zero(const point& pt0, const point& pt1, const point& pt2, const point& pt3, double t0, double t2, const bool findX, const double epsilon = DBL_EPSILON) {
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

	const double epsilon = DBL_EPSILON;

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
		assert(!_Same_sign(dt0.y, dt1.y));
		auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.0, 0.5, true);
		auto yval = _Curve_value_for_t(pt0.y, pt1.y, pt2.y, pt3.y, t);
		extents0.y = min(extents0.y, yval);
		extents1.y = max(extents1.y, yval);
		foundLowY = true;
		numPoints++;
		numYs++;
	}
	if (!foundHighY) {
		assert(!_Same_sign(dt1.y, dt2.y));
		auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.5, 1.0, true);
		auto yval = _Curve_value_for_t(pt0.y, pt1.y, pt2.y, pt3.y, t);
		extents0.y = min(extents0.y, yval);
		extents1.y = max(extents1.y, yval);
		foundHighY = true;
		numPoints++;
		numYs++;
	}
	assert(foundLowX && foundLowY && foundHighX && foundHighY && numPoints == 4 && numXs == 2 && numYs == 2);
	/*
	double tx0 = 0.0, tx1 = 0.0, ty0 = 0.0, ty1 = 0.0, deltaX0 = 1.0, deltaX1 = 1.0, deltaY0 = 1.0, deltaY1 = 1.0;

	if (numXs < 2) {
		// Find the t values where we get either -,+,- or +,-,+ since we're looking for derivative values that are zero in order to find the critical points.
		while (tx1 == 0.0) {
			auto origTx = tx0;
			auto dtx0 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, tx0);
			tx0 = origTx + (deltaX0 / 2.0);
			auto dtx1 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, tx0);
			tx0 = deltaX0;
			auto dtx2 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, tx0);
			if (!_Same_sign(dtx0.x, dtx1.x) && !(_Same_sign(dtx1.x, dtx2.x))) {
				tx0 = origTx;
				tx1 = deltaX0 / 2.0;
			}
			else {
				if (_Same_sign(dtx0.x, dtx1.x)) {
					// If low and middle have the same sign, the sign crossover is between middle and high so up the base.
					tx0 = deltaX0 / 2.0;
				}
				else {
					// The sign crossover is between low and middle so up the delta (effectively lowering the high).
					deltaX0 -= deltaX0 / 2.0;
				}
			}
			deltaX0 /= 2.0;
			deltaX1 /= 2.0;
		}
		// We now have values such that the critical points are between (tx#, tx# + delta# / 2.0) and (tx# + delta# / 2.0, tx# + delta#). Now we just need to find them.
		while (numXs < 2) {
			// zeroing in algorithm is wrong. needs to take account of sign of dtxs on previous run to ensure that the two values stay on the correct sides of the positive-negative divide as we zero in.
			auto& tx = (numXs == 0) ? tx0 : tx1;
			//				auto origTx = tx;
			auto& deltaX = (numXs == 0) ? deltaX0 : deltaX1;
			auto dtx0 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, tx);
			auto dtx1 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, tx + deltaX);
			while ((deltaX != 0.0) && (!_Almost_equal_relative(dtx0.x, 0.0, epsilon))) {
				tx += deltaX / 2.0;
				dtx0 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, tx);
				if (!_Almost_equal_relative(dtx0.x, 0.0, epsilon)) {
					if (_Same_sign(dtx0.x, dtx1.x)) {
						tx -= deltaX / 2.0;
					}
					deltaX /= 2.0;
					if (deltaX == 0.0) {
						break;
					}
				}
				else {
					break;
				}
			}

			auto xval = _Curve_value_for_t(pt0.x, pt1.x, pt2.x, pt3.x, tx);
			auto& extents = (numXs == 0) ? extents0 : extents1;
			extents.x = xval;
			numXs++;
			numPoints++;
		}
	}
	if (numYs < 2) {
		while (ty1 == 0.0) {
			auto origTy = ty0;
			auto dty0 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, ty0);
			ty0 = origTy + (deltaY0 / 2.0);
			auto dty1 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, ty0);
			ty0 = deltaY0;
			auto dty2 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, ty0);
			if (!_Same_sign(dty0.y, dty1.y) && !(_Same_sign(dty1.y, dty2.y))) {
				ty0 = origTy;
				ty1 = deltaY0 / 2.0;
			}
			else {
				if (_Same_sign(dty0.y, dty1.y)) {
					ty0 += deltaY0 / 2.0;
				}
				else {
					deltaY0 -= deltaY0 / 2.0;
				}
			}
			deltaY0 /= 2.0;
			deltaY1 /= 2.0;
		}
		// We now have values such that the critical points are between (ty#, ty# + delta# / 2.0) and (ty# + delta# / 2.0, ty# + delta#). Now we just need to find them.
		while (numYs < 2) {
			auto& ty = (numYs == 0) ? ty0 : ty1;
			//				auto origTx = tx;
			auto& deltaY = (numYs == 0) ? deltaY0 : deltaY1;
			auto dty0 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, ty);
			auto dty1 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, ty + deltaY);
			while ((deltaY != 0) && (!_Almost_equal_relative(dty0.y, 0.0, epsilon))) {
				ty += deltaY / 2.0;
				dty0 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, ty);
				if (!_Almost_equal_relative(dty0.y, 0.0, epsilon)) {
					if (_Same_sign(dty0.y, dty1.y)) {
						ty -= deltaY / 2.0;
					}
					deltaY /= 2.0;
					if (deltaY == 0.0) {
						break;
					}
				}
				else {
					break;
				}
			}

			auto yval = _Curve_value_for_t(pt0.y, pt1.y, pt2.y, pt3.y, ty);
			auto& extents = (numYs == 0) ? extents0 : extents1;
			extents.y = yval;
			numYs++;
			numPoints++;
		}
	}
	*/
}

void path_builder::get_path_extents(point& pt0, point& pt1) const {
	bool hasLastPoint = false;
	bool hasExtents = false;
	point lastPoint{ };
	// pt0 will hold min values; pt1 will hold max values.
	for (auto i = 0U; i < _Data.size(); i += _Data[i].header.length) {
		auto type = _Data[i].header.type;

		switch (type) {
		case std::experimental::drawing::path_data_type::move_to:
			lastPoint = _Data[i + 1].point;
			hasLastPoint = true;
			break;
		case std::experimental::drawing::path_data_type::line_to:
			if (hasLastPoint) {
				if (!hasExtents) {
					hasExtents = true;
					pt0.x = min(lastPoint.x, _Data[i + 1].point.x);
					pt1.x = max(lastPoint.x, _Data[i + 1].point.x);
					pt0.y = min(lastPoint.y, _Data[i + 1].point.y);
					pt1.y = max(lastPoint.y, _Data[i + 1].point.y);
				}
				else {
					pt0.x = min(min(pt0.x, lastPoint.x), _Data[i + 1].point.x);
					pt0.y = min(min(pt0.y, lastPoint.y), _Data[i + 1].point.y);
					pt1.x = max(max(pt1.x, lastPoint.x), _Data[i + 1].point.x);
					pt1.y = max(max(pt1.y, lastPoint.y), _Data[i + 1].point.y);
				}
			}
			else {
				throw drawing_exception(status::invalid_path_data);
			}
			break;
		case std::experimental::drawing::path_data_type::curve_to:
		{
			point cte0{ }, cte1{ };
			_Curve_to_extents(lastPoint, _Data[i + 1].point, _Data[i + 2].point, _Data[i + 3].point, cte0, cte1);
			if (!hasExtents) {
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
		case std::experimental::drawing::path_data_type::new_sub_path:
			hasLastPoint = false;
			break;
		case std::experimental::drawing::path_data_type::close_path:
			hasLastPoint = false;
			break;
		default:
			throw drawing_exception(status::invalid_path_data);
		}
	}
}

void path_builder::clear() {
	*this = path_builder();
}
