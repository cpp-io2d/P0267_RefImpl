#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"
#include <algorithm>
#include <limits>

using namespace std;
using namespace std::experimental::io2d;

namespace {
	const double _Pi = 3.1415926535897932384626433832795;
}

double _Curve_value_for_t(double a, double b, double c, double d, double t) noexcept;
double _Curve_value_for_t(double a, double b, double c, double d, double t) noexcept{
	return pow(1.0 - t, 3.0) * a + 3.0 * pow(1.0 - t, 2.0) * t * b + 3.0 * (1.0 - t) * pow(t, 2.0) * c + pow(t, 3.0) * d;
}

inline vector_2d _Cubic_bezier_derivative_for_t(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, const vector_2d& pt3, double t) noexcept;
inline vector_2d _Cubic_bezier_derivative_for_t(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, const vector_2d& pt3, double t) noexcept{
	return vector_2d{ 3.0 * pow(1.0 - t, 2.0) * (pt1 - pt0).x(), 3.0 * pow(1.0 - t, 2.0) * (pt1 - pt0).y() } +vector_2d{ 6.0 * (1.0 - t) * t * (pt2 - pt1).x(), 6.0 * (1.0 - t) * t * (pt2 - pt1).y() } +vector_2d{ 3.0 * pow(t, 2.0) * (pt3 - pt2).x(), 3.0 * pow(t, 2.0) * (pt3 - pt2).y() };
}

inline bool _Same_sign(double lhs, double rhs) noexcept;
inline bool _Same_sign(double lhs, double rhs) noexcept{
	return ((lhs < 0.0) && (rhs < 0.0)) || ((lhs > 0.0) && (rhs > 0.0));
}

double _Find_t_for_d_of_t_equal_zero(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, const vector_2d& pt3, double t0, double t2, const bool findX, const double epsilon = numeric_limits<double>::epsilon()) noexcept;
double _Find_t_for_d_of_t_equal_zero(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, const vector_2d& pt3, double t0, double t2, const bool findX, const double epsilon) noexcept{
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
		assert(!_Same_sign(dt0.x(), dt2.x()));
	}
	else {
		assert(!_Same_sign(dt0.y(), dt2.y()));
	}

	auto dt1 = _Cubic_bezier_derivative_for_t(pt0, pt1, pt2, pt3, t1);

	// If t0 and t1 are equal or t1 and t1Previous are equal, we can no longer get a meaningful t1 value so the value of t0 will have to be accepted as close enough.
	while (!_Almost_equal_relative(t0, t1, epsilon) && !_Almost_equal_relative(t1, t1Previous, epsilon)) {
		if (findX) {
			if (_Almost_equal_relative(dt1.x(), 0.0, epsilon)) {
				return t1;
			}
			if (_Same_sign(dt0.x(), dt1.x())) {
				// Since t0 and t2 are different signs and t0 and t1 are the same sign, we know our value lies between t1 and t2 so set t0 = t1 and calculate the new t1.
				t0 = t1;
				t1Previous = t1;
				t1 = (t2 - t0) / 2.0 + t0;
			}
			else {
				assert(_Same_sign(dt1.x(), dt2.x()));
				// Since t0 and t2 are different signs and t1 and t2 are the same sign, we know our value lies between t0 and t1 so set t2 = t1 and calculate the new t1.
				t2 = t1;
				t1Previous = t1;
				t1 = (t2 - t0) / 2.0 + t0;
			}
		}
		else {
			if (_Almost_equal_relative(dt1.y(), 0.0, epsilon)) {
				return t1;
			}
			if (_Same_sign(dt0.y(), dt1.y())) {
				// Since t0 and t2 are different signs and t0 and t1 are the same sign, we know our value lies between t1 and t2 so set t0 = t1 and calculate the new t1.
				t0 = t1;
				t1Previous = t1;
				t1 = (t2 - t0) / 2.0 + t0;
			}
			else {
				assert(_Same_sign(dt1.y(), dt2.y()));
				// Since t0 and t2 are different signs and t1 and t2 are the same sign, we know our value lies between t0 and t1 so set t2 = t1 and calculate the new t1.
				t2 = t1;
				t1Previous = t1;
				t1 = (t2 - t0) / 2.0 + t0;
			}
		}
	}
	return t1;
}

void _Curve_to_extents(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, const vector_2d& pt3, vector_2d& extents0, vector_2d& extents1) noexcept;
void _Curve_to_extents(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, const vector_2d& pt3, vector_2d& extents0, vector_2d& extents1) noexcept{
	// We know at a minimum that the extents are the two knots, pt0 and pt3. The only question is whether the extents go beyond those two points.
	extents0.x(min(pt0.x(), pt3.x()));
	extents0.y(min(pt0.y(), pt3.y()));
	extents1.x(max(pt0.x(), pt3.x()));
	extents1.y(max(pt0.y(), pt3.y()));

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
	if (_Almost_equal_relative(dt0.x(), 0.0, epsilon)) {
		assert(numXs == 0);
		// First knot is critical. We already assigned it so we're done with that.
		foundLowX = true;
		numPoints++;
		numXs++;
		if (_Same_sign(dt1.x(), dt2.x())) {
			// No second critical point so the second knot is the other extent and we already assigned it so we're done with that.
			foundHighX = true;
			numPoints++;
			numXs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.5, 1.0, true);
			auto xval = _Curve_value_for_t(pt0.x(), pt1.x(), pt2.x(), pt3.x(), t);
			// We do this min/max assignment because critical points just signal a change in curve direction, not that the critical point is actually a min/max point.
			extents0.x(min(extents0.x(), xval));
			extents1.x(max(extents1.x(), xval));
			foundHighX = true;
			numPoints++;
			numXs++;
		}
	}
	if (_Almost_equal_relative(dt1.x(), 0.0, epsilon)) {
		assert(numXs == 0);
		// Center is only critical.
		auto cxval = _Curve_value_for_t(pt0.x(), pt1.x(), pt2.x(), pt3.x(), 0.5);
		// Arbitrarily use pt3.x() rather than pt0.x(); they are the same value regardless.
		assert(_Almost_equal_relative(pt0.x(), pt3.x(), epsilon));
		extents0.x(min(cxval, pt3.x()));
		extents1.x(max(cxval, pt3.x()));
		numPoints += 2;
		numXs += 2;
	}
	if (_Almost_equal_relative(dt2.x(), 0.0, epsilon)) {
		assert(numXs == 0);
		numPoints++;
		numXs++;
		foundHighX = true;
		if (_Same_sign(dt0.x(), dt1.x())) {
			// No second critical point so the first knot is the other extent and we already assigned it so we're done with that.
			foundLowX = true;
			numPoints++;
			numXs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.0, 0.5, true);
			auto xval = _Curve_value_for_t(pt0.y(), pt1.y(), pt2.y(), pt3.y(), t);
			// We do this min/max assignment because critical points just signal a change in curve direction, not that the critical point is actually a min/max point.
			extents0.x(min(extents0.x(), xval));
			extents1.x(max(extents1.x(), xval));
			foundLowX = true;
			numPoints++;
			numXs++;
		}
	}
	if (numXs == 0) {
		if (_Same_sign(dt0.x(), dt1.x()) && _Same_sign(dt1.x(), dt2.x())) {
			// No critical points on X: use ends.
			extents0.x(min(pt0.x(), pt3.x()));
			extents1.x(max(pt0.x(), pt3.x()));
			foundLowX = true;
			foundHighX = true;
			numPoints += 2;
			numXs += 2;
		}
	}
	if (!foundLowX) {
		if (_Same_sign(dt0.x(), dt1.x())) {
			// There is no critical point between dt0.x() and dt1.x() so the lowX point is pt0.x(), which we already assigned.
			foundLowX = true;
			numPoints++;
			numXs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.0, 0.5, true);
			auto xval = _Curve_value_for_t(pt0.x(), pt1.x(), pt2.x(), pt3.x(), t);
			// We do this min/max assignment because critical points just signal a change in curve direction, not that the critical point is actually a min/max point.
			extents0.x(min(extents0.x(), xval));
			extents1.x(max(extents1.x(), xval));
			foundLowX = true;
			numPoints++;
			numXs++;
		}
	}
	if (!foundHighX) {
		if (_Same_sign(dt1.x(), dt2.x())) {
			// There is no critical point between dt1.x and dt2.x so the highX point is pt3.x, which we already assigned.
			foundHighX = true;
			numPoints++;
			numXs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.5, 1.0, true);
			auto xval = _Curve_value_for_t(pt0.x(), pt1.x(), pt2.x(), pt3.x(), t);
			// We do this min/max assignment because critical points just signal a change in curve direction, not that the critical point is actually a min/max point.
			extents0.x(min(extents0.x(), xval));
			extents1.x(max(extents1.x(), xval));
			foundHighX = true;
			numPoints++;
			numXs++;
		}
	}

	// Y values
	if (_Almost_equal_relative(dt0.y(), 0.0, epsilon)) {
		assert(numYs == 0);
		// First knot is critical. We already assigned it so we're done with that.
		foundLowY = true;
		numPoints++;
		numYs++;
		if (_Same_sign(dt1.y(), dt2.y())) {
			// No second critical point so the second knot is the other extent and we already assigned it so we're done with that.
			foundHighY = true;
			numPoints++;
			numYs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.5, 1.0, false);
			auto yval = _Curve_value_for_t(pt0.y(), pt1.y(), pt2.y(), pt3.y(), t);
			// We do this min/max assignment because critical points just signal a change in curve direction, not that the critical point is actually a min/max point.
			extents0.y(min(extents0.y(), yval));
			extents1.y(max(extents1.y(), yval));
			foundHighY = true;
			numPoints++;
			numYs++;
		}
	}
	if (_Almost_equal_relative(dt1.y(), 0.0, epsilon)) {
		assert(numYs == 0);
		// Center is only critical.
		auto cyval = _Curve_value_for_t(pt0.y(), pt1.y(), pt2.y(), pt3.y(), 0.5);
		// Arbitrarily use pt3.y() rather than pt0.y(); they are the same value regardless.
		assert(_Almost_equal_relative(pt0.y(), pt3.y(), epsilon));
		extents0.y(min(cyval, pt3.y()));
		extents1.y(max(cyval, pt3.y()));
		numPoints += 2;
		numYs += 2;
	}
	if (_Almost_equal_relative(dt2.y(), 0.0, epsilon)) {
		assert(numYs == 0);
		numPoints++;
		numYs++;
		foundHighY = true;
		if (_Same_sign(dt0.y(), dt1.y())) {
			// No second critical point so the first knot is the other extent and we already assigned it so we're done with that.
			foundLowY = true;
			numPoints++;
			numYs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.0, 0.5, false);
			auto yval = _Curve_value_for_t(pt0.y(), pt1.y(), pt2.y(), pt3.y(), t);
			// We do this min/max assignment because critical points just signal a change in curve direction, not that the critical point is actually a min/max point.
			extents0.y(min(extents0.y(), yval));
			extents1.y(max(extents1.y(), yval));
			foundLowY = true;
			numPoints++;
			numYs++;
		}
	}
	if (numYs == 0) {
		if (_Same_sign(dt0.y(), dt1.y()) && _Same_sign(dt1.y(), dt2.y())) {
			// No critical points on Y: use ends.
			extents0.y(min(pt0.y(), pt3.y()));
			extents1.y(max(pt0.y(), pt3.y()));
			foundLowY = true;
			foundHighY = true;
			numPoints += 2;
			numYs += 2;
		}
	}
	if (!foundLowY) {
		if (_Same_sign(dt0.y(), dt1.y())) {
			// There is no critical point between dt0.y() and dt1.y() so the lowY point is pt0.y(), which we already assigned.
			foundLowY = true;
			numPoints++;
			numYs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.0, 0.5, false);
			auto yval = _Curve_value_for_t(pt0.y(), pt1.y(), pt2.y(), pt3.y(), t);
			extents0.y(min(extents0.y(), yval));
			extents1.y(max(extents1.y(), yval));
			foundLowY = true;
			numPoints++;
			numYs++;
		}
	}
	if (!foundHighY) {
		if (_Same_sign(dt1.y(), dt2.y())) {
			// There is no critical point between dt1.y() and dt2.y() so the lowY point is pt3.y(), which we already assigned.
			foundHighY = true;
			numPoints++;
			numYs++;
		}
		else {
			auto t = _Find_t_for_d_of_t_equal_zero(pt0, pt1, pt2, pt3, 0.5, 1.0, false);
			auto yval = _Curve_value_for_t(pt0.y(), pt1.y(), pt2.y(), pt3.y(), t);
			extents0.y(min(extents0.y(), yval));
			extents1.y(max(extents1.y(), yval));
			foundHighY = true;
			numPoints++;
			numYs++;
		}
	}
	assert(foundLowX && foundLowY && foundHighX && foundHighY && numPoints == 4 && numXs == 2 && numYs == 2);
}

vector_2d _Rotate_point(const vector_2d& pt, double angle, bool clockwise = true) noexcept;
vector_2d _Rotate_point(const vector_2d& pt, double angle, bool clockwise) noexcept{
	if (clockwise) {
		return{ pt.x() * cos(angle) + pt.y() * sin(angle), -(pt.x() * -(sin(angle)) + pt.y() * cos(angle)) };
	}
	else {
		return{ pt.x() * cos(angle) + pt.y() * sin(angle), pt.x() * -(sin(angle)) + pt.y() * cos(angle) };
	}
}

vector<path_data_item> _Get_arc_as_beziers(const vector_2d& center, double radius, double angle1, double angle2, bool arcNegative, bool hasCurrentPoint, const vector_2d& /*currentPoint*/, const vector_2d& origin, const matrix_2d& matrix) {
	if (arcNegative) {
		while (angle2 > angle1) {
			angle2 -= _Pi * 2.0;
		}
	}
	else {
		while (angle2 < angle1) {
			angle2 += _Pi * 2.0;
		}
	}
	vector_2d pt0, pt1, pt2, pt3;
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

		while (theta >= (_Pi / 2.0)) {
			theta /= 2.0;
			bezierCount += bezierCount;
		}

		phi = theta / 2.0;

		auto cosinePhi = cos(phi);
		auto sinePhi = sin(phi);

		pt0.x(cosinePhi);
		pt0.y(-sinePhi);

		pt3.x(pt0.x());
		pt3.y(-pt0.y());

		pt1.x((4.0 - cosinePhi) / 3.0);
		pt1.y(-(((1.0 - cosinePhi) * (3.0 - cosinePhi)) / (3.0 * sinePhi)));

		pt2.x(pt1.x());
		pt2.y(-pt1.y());

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
	path_factory pb;
	pb.origin(origin);
	pb.transform_matrix(matrix);

	const auto startPoint = center + _Rotate_point({ pt0.x() * radius, pt0.y() * radius }, currentTheta);
	if (hasCurrentPoint) {
//		pb.move_to(currentPoint);
		pb.line_to(startPoint);
	}
	else {
		pb.move_to(startPoint);
	}

	// We start at the point derived from angle1 and continue adding beziers until the count reaches zero.
	// The point we have is already rotated by half of theta.
	for (; bezierCount > 0; bezierCount--) {
		pb.curve_to(
			center + _Rotate_point({ pt1.x() * radius, pt1.y() * radius }, currentTheta),
			center + _Rotate_point({ pt2.x() * radius, pt2.y() * radius }, currentTheta),
			center + _Rotate_point({ pt3.x() * radius, pt3.y() * radius }, currentTheta)
			);

		if (arcNegative) {
			currentTheta -= theta;
		}
		else {
			currentTheta += theta;
		}
	}
	return pb.data();
}

vector<path_data_item> _Get_arc_as_beziers(const vector_2d& center, double radius, double angle1, double angle2, error_code& ec, bool arcNegative, bool hasCurrentPoint, const vector_2d& /*currentPoint*/, const vector_2d& origin, const matrix_2d& matrix) noexcept{
	if (arcNegative) {
		while (angle2 > angle1) {
			angle2 -= _Pi * 2.0;
		}
	}
	else {
		while (angle2 < angle1) {
			angle2 += _Pi * 2.0;
		}
	}
	vector_2d pt0, pt1, pt2, pt3;
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

		while (theta >= (_Pi / 2.0)) {
			theta /= 2.0;
			bezierCount += bezierCount;
		}

		phi = theta / 2.0;

		auto cosinePhi = cos(phi);
		auto sinePhi = sin(phi);

		pt0.x(cosinePhi);
		pt0.y(-sinePhi);

		pt3.x(pt0.x());
		pt3.y(-pt0.y());

		pt1.x((4.0 - cosinePhi) / 3.0);
		pt1.y(-(((1.0 - cosinePhi) * (3.0 - cosinePhi)) / (3.0 * sinePhi)));

		pt2.x(pt1.x());
		pt2.y(-pt1.y());

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
	path_factory pb;
	pb.origin(origin, ec);
	if (static_cast<bool>(ec)) {
		// Relies on C++17 nothrow vector default ctor
		return vector<path_data_item>();
	}
	pb.transform_matrix(matrix, ec);
	if (static_cast<bool>(ec)) {
		// Relies on C++17 nothrow vector default ctor
		return vector<path_data_item>();
	}

	const auto startPoint = center + _Rotate_point({ pt0.x() * radius, pt0.y() * radius }, currentTheta);
	if (hasCurrentPoint) {
		//pb.move_to(currentPoint, ec);
		//if (static_cast<bool>(ec)) {
		//	// Relies on C++17 nothrow vector default ctor
		//	return vector<path_data_item>();
		//}
		pb.line_to(startPoint, ec);
		if (static_cast<bool>(ec)) {
			// Relies on C++17 nothrow vector default ctor
			return vector<path_data_item>();
		}
	}
	else {
		pb.move_to(startPoint, ec);
		if (static_cast<bool>(ec)) {
			// Relies on C++17 nothrow vector default ctor
			return vector<path_data_item>();
		}
	}

	// We start at the point derived from angle1 and continue adding beziers until the count reaches zero.
	// The point we have is already rotated by half of theta.
	for (; bezierCount > 0; bezierCount--) {
		pb.curve_to(
			center + _Rotate_point({ pt1.x() * radius, pt1.y() * radius }, currentTheta),
			center + _Rotate_point({ pt2.x() * radius, pt2.y() * radius }, currentTheta),
			center + _Rotate_point({ pt3.x() * radius, pt3.y() * radius }, currentTheta),
			ec
			);
		if (static_cast<bool>(ec)) {
			// Relies on C++17 nothrow vector default ctor
			return vector<path_data_item>();
		}
		if (arcNegative) {
			currentTheta -= theta;
		}
		else {
			currentTheta += theta;
		}
	}
	try {
		ec.clear();
		return pb.data();
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		// Relies on C++17 nothrow vector default ctor
		return vector<path_data_item>();
	}
}

void _Get_arc_extents(const ::std::experimental::io2d::vector_2d& center, double radius, double angle1, double angle2, bool arcNegative, bool& hasCurrentPoint, ::std::experimental::io2d::vector_2d& currentPoint, bool& hasExtents, vector_2d& exPt0, vector_2d& exPt1, ::std::experimental::io2d::vector_2d& origin, ::std::experimental::io2d::matrix_2d& transformMatrix) noexcept{
	if (arcNegative) {
		while (angle2 > angle1) {
			angle2 -= _Pi * 2.0;
		}
	}
	else {
		while (angle2 < angle1) {
			angle2 += _Pi * 2.0;
		}
	}
	vector_2d pt0, pt1, pt2, pt3;
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

		while (theta >= (_Pi / 2.0)) {
			theta /= 2.0;
			bezierCount += bezierCount;
		}

		phi = theta / 2.0;

		auto cosinePhi = cos(phi);
		auto sinePhi = sin(phi);

		pt0.x(cosinePhi);
		pt0.y(-sinePhi);

		pt3.x(pt0.x());
		pt3.y(-pt0.y());

		pt1.x((4.0 - cosinePhi) / 3.0);
		pt1.y(-(((1.0 - cosinePhi) * (3.0 - cosinePhi)) / (3.0 * sinePhi)));

		pt2.x(pt1.x());
		pt2.y(-pt1.y());

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

	const auto startPoint = center + _Rotate_point({ pt0.x() * radius, pt0.y() * radius }, currentTheta);
	if (hasCurrentPoint) {
		// move_to
		currentPoint = transformMatrix.transform_point(currentPoint - origin) + origin;
		hasCurrentPoint = true;
		// line_to
		auto itemPt = transformMatrix.transform_point(startPoint - origin) + origin;
		if (!hasExtents) {
			hasExtents = true;
			exPt0.x(min(currentPoint.x(), itemPt.x()));
			exPt0.y(min(currentPoint.y(), itemPt.y()));
			exPt1.x(max(currentPoint.x(), itemPt.x()));
			exPt1.y(max(currentPoint.y(), itemPt.y()));
		}
		else {
			exPt0.x(min(min(exPt0.x(), currentPoint.x()), itemPt.x()));
			exPt0.y(min(min(exPt0.y(), currentPoint.y()), itemPt.y()));
			exPt1.x(max(max(exPt1.x(), currentPoint.x()), itemPt.x()));
			exPt1.y(max(max(exPt1.y(), currentPoint.y()), itemPt.y()));
		}
	}
	else {
		// move_to
		currentPoint = transformMatrix.transform_point(startPoint - origin) + origin;
		hasCurrentPoint = true;
	}

	// We start at the point derived from angle1 and continue adding beziers until the count reaches zero.
	// The point we have is already rotated by half of theta.
	for (; bezierCount > 0; bezierCount--) {
		// curve_to
		assert(hasCurrentPoint);
		vector_2d cte0{ };
		vector_2d cte1{ };
		auto ctrlPt1 = center + _Rotate_point({ pt1.x() * radius, pt1.y() * radius }, currentTheta);
		auto ctrlPt2 = center + _Rotate_point({ pt2.x() * radius, pt2.y() * radius }, currentTheta);
		auto endPt = center + _Rotate_point({ pt3.x() * radius, pt3.y() * radius }, currentTheta);
		auto itemPt1 = transformMatrix.transform_point(ctrlPt1 - origin) + origin;
		auto itemPt2 = transformMatrix.transform_point(ctrlPt2 - origin) + origin;
		auto itemPt3 = transformMatrix.transform_point(endPt - origin) + origin;
		_Curve_to_extents(currentPoint, itemPt1, itemPt2, itemPt3, cte0, cte1);
		if (!hasExtents) {
			hasExtents = true;
			exPt0.x(min(cte0.x(), cte1.x()));
			exPt0.y(min(cte0.y(), cte1.y()));
			exPt1.x(max(cte0.x(), cte1.x()));
			exPt1.y(max(cte0.y(), cte1.y()));
		}
		else {
			exPt0.x(min(min(pt0.x(), cte0.x()), cte1.x()));
			exPt0.y(min(min(pt0.y(), cte0.y()), cte1.y()));
			exPt1.x(max(max(pt1.x(), cte0.x()), cte1.x()));
			exPt1.y(max(max(pt1.y(), cte0.y()), cte1.y()));
		}

		if (arcNegative) {
			currentTheta -= theta;
		}
		else {
			currentTheta += theta;
		}
	}
}

path_factory::path_factory(path_factory&& other) noexcept
	: _Data()
	, _Has_current_point()
	, _Current_point()
	, _Extents_pt0()
	, _Extents_pt1()
	, _Transform_matrix()
	, _Origin() {
	_Data = move(other._Data);
	_Has_current_point = move(other._Has_current_point);
	_Current_point = move(other._Current_point);
	_Last_move_to_point = move(other._Last_move_to_point);
	_Extents_pt0 = move(other._Extents_pt0);
	_Extents_pt1 = move(other._Extents_pt1);
	_Transform_matrix = move(other._Transform_matrix);
	_Origin = move(other._Origin);
}

path_factory& path_factory::operator=(path_factory&& other) noexcept{
	if (this != &other) {
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

void path_factory::append(const path& p) {
	const auto& data = p.data_ref();
	for (const auto& item : data) {
		_Data.push_back(item);
	}

	_Has_current_point = p._Has_current_point;
	_Current_point = p._Current_point;
	_Last_move_to_point = p._Last_move_to_point;
}

void path_factory::append(const path& p, error_code& ec) noexcept{
	const auto& data = p.data_ref();
	try {
		_Data.reserve(_Data.size() + data.size());
	}
	catch (const length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	for (const auto& item : data) {
		_Data.push_back(item);
	}

	_Has_current_point = p._Has_current_point;
	_Current_point = p._Current_point;
	_Last_move_to_point = p._Last_move_to_point;
	ec.clear();
}

void path_factory::append(const path_factory& p) {
	for (const auto& item : p._Data) {
		_Data.push_back(item);
	}
	_Has_current_point = p._Has_current_point;
	_Current_point = p._Current_point;
	_Last_move_to_point = p._Last_move_to_point;
}

void path_factory::append(const path_factory& p, error_code& ec) noexcept{
	try {
		_Data.reserve(_Data.size() + p._Data.size());
	}
	catch (const length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	for (const auto& item : p._Data) {
		_Data.push_back(item);
	}
	_Has_current_point = p._Has_current_point;
	_Current_point = p._Current_point;
	_Last_move_to_point = p._Last_move_to_point;
	ec.clear();
}

void path_factory::append(const vector<path_data_item>& p) {
	// Validate data.
	matrix_2d transformMatrix = _Transform_matrix;
	vector_2d origin = _Origin;
	bool hasCurrentPoint = _Has_current_point;
	vector_2d currentPoint = _Current_point;
	// Used to establish the proper current point when a close_path is encountered.
	vector_2d lastMoveToPoint = _Last_move_to_point;

	for (const auto& item : p) {
		auto type = item.type();
		switch (type)
		{
		case std::experimental::io2d::path_data_type::move_to:
		{
			currentPoint = item.get<experimental::io2d::move_to>().to();
			hasCurrentPoint = true;
			lastMoveToPoint = currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::line_to:
		{
			currentPoint = item.get<experimental::io2d::line_to>().to();
			if (!hasCurrentPoint) {
				lastMoveToPoint = currentPoint;
				hasCurrentPoint = true;
			}
		} break;
		case std::experimental::io2d::path_data_type::curve_to:
		{
			auto dataItem = item.get<experimental::io2d::curve_to>();
			if (!hasCurrentPoint) {
				lastMoveToPoint = dataItem.control_point_1();
				hasCurrentPoint = true;
			}
			currentPoint = dataItem.end_point();
		} break;
		case std::experimental::io2d::path_data_type::new_sub_path:
		{
			hasCurrentPoint = false;
		} break;
		case std::experimental::io2d::path_data_type::close_path:
		{
			if (hasCurrentPoint) {
				currentPoint = lastMoveToPoint;
			}
		} break;
		case std::experimental::io2d::path_data_type::rel_move_to:
		{
			if (!hasCurrentPoint) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
			}
			currentPoint = item.get<experimental::io2d::rel_move_to>().to() + currentPoint;
			lastMoveToPoint = currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::rel_line_to:
		{
			if (!hasCurrentPoint) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
			}
			currentPoint = item.get<experimental::io2d::rel_line_to>().to() + currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::rel_curve_to:
		{
			if (!hasCurrentPoint) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
			}
			currentPoint = item.get<experimental::io2d::rel_curve_to>().end_point() + currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::arc:
		{
			auto dataItem = item.get<experimental::io2d::arc>();
			auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), false, hasCurrentPoint, currentPoint);
			if (data.size() > 0) {
				const auto& lastItem = *data.crbegin();
				if (lastItem.type() == path_data_type::curve_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::curve_to>().end_point();
				}
				else if (lastItem.type() == path_data_type::line_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::line_to>().to();
				}
				else if (lastItem.type() == path_data_type::move_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::move_to>().to();
					lastMoveToPoint = _Current_point;
				}
				else {
					assert("_Get_arc_as_beziers returned unexpected path_data value." && false);
				}
			}
		} break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			auto dataItem = item.get<experimental::io2d::arc_negative>();
			auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), true, hasCurrentPoint, currentPoint);
			if (data.size() > 0) {
				const auto& lastItem = *data.crbegin();
				if (lastItem.type() == path_data_type::curve_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::curve_to>().end_point();
				}
				else if (lastItem.type() == path_data_type::line_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::line_to>().to();
				}
				else if (lastItem.type() == path_data_type::move_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::move_to>().to();
					lastMoveToPoint = _Current_point;
				}
				else {
					assert("_Get_arc_as_beziers returned unexpected path_data value." && false);
				}
			}
		} break;
		case std::experimental::io2d::path_data_type::change_matrix:
		{
			transformMatrix = item.get<experimental::io2d::change_matrix>().matrix();
		} break;
		case std::experimental::io2d::path_data_type::change_origin:
		{
			origin = item.get<experimental::io2d::change_origin>().origin();
		} break;
		default:
		{
			assert(false && "Unknown path_data_type.");
		} break;
		}
	}

	_Data.reserve(_Data.size() + p.size());

	// Add items
	for (const auto& item : p) {
		_Data.push_back(item);
	}

	_Has_current_point = hasCurrentPoint;
	_Current_point = currentPoint;
	_Last_move_to_point = lastMoveToPoint;
	_Transform_matrix = transformMatrix;
	_Origin = origin;
}

void path_factory::append(const vector<path_data_item>& p, error_code& ec) noexcept {
	// Validate data.
	matrix_2d transformMatrix = _Transform_matrix;
	vector_2d origin = _Origin;
	bool hasCurrentPoint = _Has_current_point;
	vector_2d currentPoint = _Current_point;
	// Used to establish the proper current point when a close_path is encountered.
	vector_2d lastMoveToPoint = _Last_move_to_point;

	for (const auto& item : p) {
		auto type = item.type();
		switch (type)
		{
		case std::experimental::io2d::path_data_type::move_to:
		{
			currentPoint = item.get<experimental::io2d::move_to>().to();
			hasCurrentPoint = true;
			lastMoveToPoint = currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::line_to:
		{
			currentPoint = item.get<experimental::io2d::line_to>().to();
			if (!hasCurrentPoint) {
				lastMoveToPoint = currentPoint;
				hasCurrentPoint = true;
			}
		} break;
		case std::experimental::io2d::path_data_type::curve_to:
		{
			auto dataItem = item.get<experimental::io2d::curve_to>();
			if (!hasCurrentPoint) {
				lastMoveToPoint = dataItem.control_point_1();
				hasCurrentPoint = true;
			}
			currentPoint = dataItem.end_point();
		} break;
		case std::experimental::io2d::path_data_type::new_sub_path:
		{
			hasCurrentPoint = false;
		} break;
		case std::experimental::io2d::path_data_type::close_path:
		{
			if (hasCurrentPoint) {
				currentPoint = lastMoveToPoint;
			}
		} break;
		case std::experimental::io2d::path_data_type::rel_move_to:
		{
			if (!hasCurrentPoint) {
				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
				return;
			}
			currentPoint = item.get<experimental::io2d::rel_move_to>().to() + currentPoint;
			lastMoveToPoint = currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::rel_line_to:
		{
			if (!hasCurrentPoint) {
				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
				return;
			}
			currentPoint = item.get<experimental::io2d::rel_line_to>().to() + currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::rel_curve_to:
		{
			if (!hasCurrentPoint) {
				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
				return;
			}
			currentPoint = item.get<experimental::io2d::rel_curve_to>().end_point() + currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::arc:
		{
			auto dataItem = item.get<experimental::io2d::arc>();
			auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), ec, false, hasCurrentPoint, currentPoint);
			if (static_cast<bool>(ec)) {
				return;
			}
			if (data.size() > 0) {
				const auto& lastItem = *data.crbegin();
				if (lastItem.type() == path_data_type::curve_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::curve_to>().end_point();
				}
				else if (lastItem.type() == path_data_type::line_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::line_to>().to();
				}
				else if (lastItem.type() == path_data_type::move_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::move_to>().to();
					lastMoveToPoint = _Current_point;
				}
				else {
					assert("_Get_arc_as_beziers returned unexpected path_data value." && false);
				}
			}
		} break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			auto dataItem = item.get<experimental::io2d::arc_negative>();
			auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), ec, true, hasCurrentPoint, currentPoint);
			if (static_cast<bool>(ec)) {
				return;
			}
			if (data.size() > 0) {
				const auto& lastItem = *data.crbegin();
				if (lastItem.type() == path_data_type::curve_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::curve_to>().end_point();
				}
				else if (lastItem.type() == path_data_type::line_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::line_to>().to();
				}
				else if (lastItem.type() == path_data_type::move_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::move_to>().to();
					lastMoveToPoint = _Current_point;
				}
				else {
					assert("_Get_arc_as_beziers returned unexpected path_data value." && false);
				}
			}
		} break;
		case std::experimental::io2d::path_data_type::change_matrix:
		{
			transformMatrix = item.get<experimental::io2d::change_matrix>().matrix();
		} break;
		case std::experimental::io2d::path_data_type::change_origin:
		{
			origin = item.get<experimental::io2d::change_origin>().origin();
		} break;
		default:
		{
			assert(false && "Unknown path_data_type.");
		} break;
		}
	}

	try {
		_Data.reserve(_Data.size() + p.size());
	}
	catch (const length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}

	// Add items
	for (const auto& item : p) {
		_Data.push_back(item);
	}

	_Has_current_point = hasCurrentPoint;
	_Current_point = currentPoint;
	_Last_move_to_point = lastMoveToPoint;
	_Transform_matrix = transformMatrix;
	_Origin = origin;
	ec.clear();
}

bool path_factory::has_current_point() const noexcept{
	return _Has_current_point;
}

vector_2d path_factory::current_point() const {
	if (!_Has_current_point) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
	}
	return _Current_point;
}

vector_2d path_factory::current_point(error_code& ec) const noexcept{
	if (!_Has_current_point) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
		return vector_2d{ };
	}
	ec.clear();
	return _Current_point;
}

void path_factory::new_sub_path() {
	_Data.emplace_back(experimental::io2d::new_sub_path());
	_Has_current_point = false;
}

void path_factory::new_sub_path(error_code& ec) noexcept {
	try {
		_Data.emplace_back(experimental::io2d::new_sub_path());
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Has_current_point = false;
	ec.clear();
}

void path_factory::close_path() {
	if (_Has_current_point) {
		_Data.emplace_back(experimental::io2d::close_path());
		_Current_point = _Last_move_to_point;
	}
}

void path_factory::close_path(error_code& ec) noexcept{
	if (_Has_current_point) {
		try {
			_Data.emplace_back(experimental::io2d::close_path());
		}
		catch (const bad_alloc&) {
			ec = make_error_code(errc::not_enough_memory);
			return;
		}
		_Current_point = _Last_move_to_point;
	}
	ec.clear();
}

void path_factory::_Set_current_point_and_last_move_to_point_for_arc(const vector<path_data_item>& data) noexcept{
	if (data.size() > 0) {
		const auto& lastItem = *data.crbegin();
		if (lastItem.type() == path_data_type::curve_to) {
			_Has_current_point = true;
			_Current_point = lastItem.get<experimental::io2d::curve_to>().end_point();
		}
		else if (lastItem.type() == path_data_type::line_to) {
			_Has_current_point = true;
			_Current_point = lastItem.get<experimental::io2d::line_to>().to();
		}
		else if (lastItem.type() == path_data_type::move_to) {
			_Has_current_point = true;
			_Current_point = lastItem.get<experimental::io2d::move_to>().to();
			_Last_move_to_point = _Current_point;
		}
		else {
			assert("_Get_arc_as_beziers returned unexpected path_data value." && false);
		}
	}
}

void path_factory::arc(const vector_2d& center, double radius, double angle1, double angle2) {
	_Data.emplace_back(std::experimental::io2d::arc(center, radius, angle1, angle2));
	// Update the current point.
	try {
		_Set_current_point_and_last_move_to_point_for_arc(_Get_arc_as_beziers(center, radius, angle1, angle2, false, _Has_current_point, _Current_point));
	}
	catch (...) {
		_Data.pop_back();
		throw;
	}
}

void path_factory::arc(const vector_2d& center, double radius, double angle1, double angle2, error_code& ec) noexcept{
	try {
		_Data.emplace_back(std::experimental::io2d::arc(center, radius, angle1, angle2));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}

	// Update the current point.
	auto vec = _Get_arc_as_beziers(center, radius, angle1, angle2, ec, false, _Has_current_point, _Current_point);
	if (static_cast<bool>(ec)) {
		_Data.pop_back(); // Undo the action so that there are no effects in case of failure.
		return;
	}
	_Set_current_point_and_last_move_to_point_for_arc(vec);
	ec.clear();
}

void path_factory::arc_negative(const vector_2d& center, double radius, double angle1, double angle2) {
	_Data.emplace_back(std::experimental::io2d::arc_negative(center, radius, angle1, angle2));
	// Update the current point.
	try {
		_Set_current_point_and_last_move_to_point_for_arc(_Get_arc_as_beziers(center, radius, angle1, angle2, true, _Has_current_point, _Current_point));
	}
	catch (...) {
		_Data.pop_back();
		throw;
	}
}

void path_factory::arc_negative(const vector_2d& center, double radius, double angle1, double angle2, error_code& ec) noexcept {
	try {
		_Data.emplace_back(std::experimental::io2d::arc_negative(center, radius, angle1, angle2));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}

	// Update the current point.
	auto vec = _Get_arc_as_beziers(center, radius, angle1, angle2, ec, true, _Has_current_point, _Current_point);

	if (static_cast<bool>(ec)) {
		_Data.pop_back(); // Undo the action so that there are no effects in case of failure.
		return;
	}
	_Set_current_point_and_last_move_to_point_for_arc(vec);
	ec.clear();
}

void path_factory::curve_to(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2) {
	if (!_Has_current_point) {
		_Data.reserve(_Data.size() + 2U);
		move_to(pt0);
	}
	_Data.emplace_back(std::experimental::io2d::curve_to(pt0, pt1, pt2));
	_Has_current_point = true;
	_Current_point = pt2;
}

void path_factory::curve_to(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, error_code& ec) noexcept {
	if (!_Has_current_point) {
		try {
			_Data.reserve(_Data.size() + 2U);
		}
		catch (const length_error&) {
			ec = make_error_code(errc::not_enough_memory);
			return;
		}
		catch (const bad_alloc&) {
			ec = make_error_code(errc::not_enough_memory);
			return;
		}
		move_to(pt0, ec);
		if (static_cast<bool>(ec)) {
			return;
		}
	}
	try {
		_Data.emplace_back(std::experimental::io2d::curve_to(pt0, pt1, pt2));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Has_current_point = true;
	_Current_point = pt2;
	ec.clear();
}

void path_factory::line_to(const vector_2d& pt) {
	_Data.emplace_back(std::experimental::io2d::line_to(pt));
	_Has_current_point = true;
	_Current_point = pt;
}

void path_factory::line_to(const vector_2d& pt, error_code& ec) noexcept{
	if (!_Has_current_point) {
		move_to(pt, ec);
		// move_to already sets or clears ec for us.
		return;
	}
	try {
		_Data.emplace_back(std::experimental::io2d::line_to(pt));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Has_current_point = true;
	_Current_point = pt;
	ec.clear();
}

void path_factory::move_to(const vector_2d& pt) {
	_Data.emplace_back(std::experimental::io2d::move_to(pt));
	_Has_current_point = true;
	_Current_point = pt;
}

void path_factory::move_to(const vector_2d& pt, error_code& ec) noexcept{
	try {
		_Data.emplace_back(std::experimental::io2d::move_to(pt));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Has_current_point = true;
	_Current_point = pt;
	ec.clear();
}

void path_factory::rect(const experimental::io2d::rectangle& r) {
	_Data.reserve(_Data.size() + 5U);

	move_to({ r.x(), r.y() });
	rel_line_to({ r.width(), 0.0 });
	rel_line_to({ 0.0, r.height() });
	rel_line_to({ -r.width(), 0.0 });
	close_path();
}

void path_factory::rect(const experimental::io2d::rectangle& r, error_code& ec) noexcept{
	try {
		_Data.reserve(_Data.size() + 5U);
	}
	catch (const length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}

	ec.clear();
	move_to({ r.x(), r.y() }, ec);
	assert(!static_cast<bool>(ec));
	rel_line_to({ r.width(), 0.0 }, ec);
	assert(!static_cast<bool>(ec));
	rel_line_to({ 0.0, r.height() }, ec);
	assert(!static_cast<bool>(ec));
	rel_line_to({ -r.width(), 0.0 }, ec);
	assert(!static_cast<bool>(ec));
	close_path(ec);
	assert(!static_cast<bool>(ec));
}

void path_factory::rel_curve_to(const vector_2d& dpt0, const vector_2d& dpt1, const vector_2d& dpt2) {
	if (!_Has_current_point) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
	}
	_Data.emplace_back(std::experimental::io2d::rel_curve_to(dpt0, dpt1, dpt2));
	_Has_current_point = true;
	_Current_point = _Current_point + dpt2;
}

void path_factory::rel_curve_to(const vector_2d& dpt0, const vector_2d& dpt1, const vector_2d& dpt2, error_code& ec) noexcept{
	if (!_Has_current_point) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
		return;
	}
	try {
		_Data.emplace_back(std::experimental::io2d::rel_curve_to(dpt0, dpt1, dpt2));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Has_current_point = true;
	_Current_point = _Current_point + dpt2;
	ec.clear();
}

void path_factory::rel_line_to(const vector_2d& dpt) {
	if (!_Has_current_point) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
	}
	_Data.emplace_back(std::experimental::io2d::rel_line_to(dpt));
	_Has_current_point = true;
	_Current_point = _Current_point + dpt;
}

void path_factory::rel_line_to(const vector_2d& dpt, error_code& ec) noexcept{
	if (!_Has_current_point) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
		return;
	}
	try {
		_Data.emplace_back(std::experimental::io2d::rel_line_to(dpt));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
	}
	_Has_current_point = true;
	_Current_point = _Current_point + dpt;
	ec.clear();
}

void path_factory::rel_move_to(const vector_2d& dpt) {
	if (!_Has_current_point) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
	}
	_Data.emplace_back(std::experimental::io2d::rel_move_to(dpt));
	_Has_current_point = true;
	_Current_point = _Current_point + dpt;
}

void path_factory::rel_move_to(const vector_2d& dpt, error_code& ec) noexcept{
	if (!_Has_current_point) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
		return;
	}
	try {
		_Data.emplace_back(std::experimental::io2d::rel_move_to(dpt));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Has_current_point = true;
	_Current_point = _Current_point + dpt;
	ec.clear();
}

void path_factory::transform_matrix(const matrix_2d& m) {
	_Data.emplace_back(std::experimental::io2d::change_matrix(m));
	_Transform_matrix = m;
}

void path_factory::transform_matrix(const matrix_2d& m, error_code& ec) noexcept{
	try {
		_Data.emplace_back(std::experimental::io2d::change_matrix(m));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Transform_matrix = m;
	ec.clear();
}

matrix_2d path_factory::transform_matrix() const noexcept{
	return _Transform_matrix;
}

void path_factory::origin(const vector_2d& pt) {
	_Data.emplace_back(std::experimental::io2d::change_origin(pt));
	_Origin = pt;
}

void path_factory::origin(const vector_2d& pt, error_code& ec) noexcept{
	try {
		_Data.emplace_back(std::experimental::io2d::change_origin(pt));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Origin = pt;
	ec.clear();
}

vector_2d path_factory::origin() const noexcept{
	return _Origin;
}

vector<path_data_item> path_factory::data() const {
	vector<path_data_item> result;
	for (const auto& item : _Data) {
		result.push_back(item);
	}
	return result;
}

vector<path_data_item> path_factory::data(error_code& ec) const noexcept{
	vector<path_data_item> result;
	try {
		result.reserve(_Data.size());
	}
	catch (const length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		// Relies on C++17 vector default ctor noexcept.
		return vector<path_data_item>();
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		// Relies on C++17 vector default ctor noexcept.
		return vector<path_data_item>();
	}
	for (const auto& item : _Data) {
		result.push_back(item);
	}
	ec.clear();
	return result;
}

path_data_item path_factory::data_item(unsigned int index) const {
	if (_Data.size() <= index) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	return _Data[index];
}

path_data_item path_factory::data_item(unsigned int index, error_code& ec) const noexcept {
	if (_Data.size() <= index) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_INDEX);
		return path_data_item{ };
	}
	return _Data[index];
}

const vector<path_data_item>& path_factory::data_ref() const noexcept {
	return _Data;
}

rectangle path_factory::path_extents() const noexcept {
	vector_2d pt0{ };
	vector_2d pt1{ };

	matrix_2d currMatrix = matrix_2d::init_identity();
	vector_2d currOrigin{ };

	bool hasCurrentPoint = false;
	bool hasExtents = false;

	vector_2d currentPoint{ };

	// pt0 will hold min values; pt1 will hold max values.
	for (auto i = 0U; i < _Data.size(); i++) {
		const auto& item = _Data[i];
		auto type = item.type();
		switch (type)
		{
		case std::experimental::io2d::path_data_type::move_to:
		{
			currentPoint = currMatrix.transform_point(item.get<experimental::io2d::move_to>().to() - currOrigin) + currOrigin;
			hasCurrentPoint = true;
		} break;
		case std::experimental::io2d::path_data_type::line_to:
		{
			assert(hasCurrentPoint);
			auto itemPt = currMatrix.transform_point(item.get<experimental::io2d::line_to>().to() - currOrigin) + currOrigin;
			if (!hasExtents) {
				hasExtents = true;
				pt0.x(min(currentPoint.x(), itemPt.x()));
				pt0.y(min(currentPoint.y(), itemPt.y()));
				pt1.x(max(currentPoint.x(), itemPt.x()));
				pt1.y(max(currentPoint.y(), itemPt.y()));
			}
			else {
				pt0.x(min(min(pt0.x(), currentPoint.x()), itemPt.x()));
				pt0.y(min(min(pt0.y(), currentPoint.y()), itemPt.y()));
				pt1.x(max(max(pt1.x(), currentPoint.x()), itemPt.x()));
				pt1.y(max(max(pt1.y(), currentPoint.y()), itemPt.y()));
			}
		} break;
		case std::experimental::io2d::path_data_type::curve_to:
		{
			assert(hasCurrentPoint);
			vector_2d cte0{ };
			vector_2d cte1{ };
			auto dataItem = item.get<experimental::io2d::curve_to>();
			auto itemPt1 = currMatrix.transform_point(dataItem.control_point_1() - currOrigin) + currOrigin;
			auto itemPt2 = currMatrix.transform_point(dataItem.control_point_2() - currOrigin) + currOrigin;
			auto itemPt3 = currMatrix.transform_point(dataItem.end_point() - currOrigin) + currOrigin;
			_Curve_to_extents(currentPoint, itemPt1, itemPt2, itemPt3, cte0, cte1);
			if (!hasExtents) {
				hasExtents = true;
				pt0.x(min(cte0.x(), cte1.x()));
				pt0.y(min(cte0.y(), cte1.y()));
				pt1.x(max(cte0.x(), cte1.x()));
				pt1.y(max(cte0.y(), cte1.y()));
			}
			else {
				pt0.x(min(min(pt0.x(), cte0.x()), cte1.x()));
				pt0.y(min(min(pt0.y(), cte0.y()), cte1.y()));
				pt1.x(max(max(pt1.x(), cte0.x()), cte1.x()));
				pt1.y(max(max(pt1.y(), cte0.y()), cte1.y()));
			}
		}
		break;
		case std::experimental::io2d::path_data_type::new_sub_path:
			hasCurrentPoint = false;
			break;
		case std::experimental::io2d::path_data_type::close_path:
			hasCurrentPoint = false;
			break;
		case std::experimental::io2d::path_data_type::rel_move_to:
			if (!hasCurrentPoint) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
			}
			currentPoint = currMatrix.transform_point((item.get<experimental::io2d::rel_move_to>().to() + currentPoint) - currOrigin) + currOrigin;
			hasCurrentPoint = true;
			break;
		case std::experimental::io2d::path_data_type::rel_line_to:
		{
			assert(hasCurrentPoint);
			auto itemPt = currMatrix.transform_point((item.get<experimental::io2d::rel_line_to>().to() + currentPoint) - currOrigin) + currOrigin;
			if (!hasExtents) {
				hasExtents = true;
				pt0.x(min(currentPoint.x(), itemPt.x()));
				pt0.y(min(currentPoint.y(), itemPt.y()));
				pt1.x(max(currentPoint.x(), itemPt.x()));
				pt1.y(max(currentPoint.y(), itemPt.y()));
			}
			else {
				pt0.x(min(min(pt0.x(), currentPoint.x()), itemPt.x()));
				pt0.y(min(min(pt0.y(), currentPoint.y()), itemPt.y()));
				pt1.x(max(max(pt1.x(), currentPoint.x()), itemPt.x()));
				pt1.y(max(max(pt1.y(), currentPoint.y()), itemPt.y()));
			}
		} break;
		case std::experimental::io2d::path_data_type::rel_curve_to:
		{
			assert(hasCurrentPoint);
			vector_2d cte0{ };
			vector_2d cte1{ };
			auto dataItem = item.get<experimental::io2d::rel_curve_to>();
			auto itemPt1 = currMatrix.transform_point((dataItem.control_point_1() + currentPoint) - currOrigin) + currOrigin;
			auto itemPt2 = currMatrix.transform_point((dataItem.control_point_2() + currentPoint) - currOrigin) + currOrigin;
			auto itemPt3 = currMatrix.transform_point((dataItem.end_point() + currentPoint) - currOrigin) + currOrigin;
			_Curve_to_extents(currentPoint, itemPt1, itemPt2, itemPt3, cte0, cte1);
			if (!hasExtents) {
				hasExtents = true;
				pt0.x(min(cte0.x(), cte1.x()));
				pt0.y(min(cte0.y(), cte1.y()));
				pt1.x(max(cte0.x(), cte1.x()));
				pt1.y(max(cte0.y(), cte1.y()));
			}
			else {
				pt0.x(min(min(pt0.x(), cte0.x()), cte1.x()));
				pt0.y(min(min(pt0.y(), cte0.y()), cte1.y()));
				pt1.x(max(max(pt1.x(), cte0.x()), cte1.x()));
				pt1.y(max(max(pt1.y(), cte0.y()), cte1.y()));
			}
		}
		break;
		case std::experimental::io2d::path_data_type::arc:
		{
			auto dataItem = item.get<experimental::io2d::arc>();
  			_Get_arc_extents(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), false, hasCurrentPoint, currentPoint, hasExtents, pt0, pt1, currOrigin, currMatrix);
		} break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			auto dataItem = item.get<experimental::io2d::arc_negative>();
			_Get_arc_extents(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), true, hasCurrentPoint, currentPoint, hasExtents, pt0, pt1, currOrigin, currMatrix);
		} break;
		case std::experimental::io2d::path_data_type::change_matrix:
		{
			currMatrix = item.get<experimental::io2d::change_matrix>().matrix();
		} break;
		case std::experimental::io2d::path_data_type::change_origin:
		{
			currOrigin = item.get<experimental::io2d::change_origin>().origin();
		} break;
		default:
		{
			assert("Unknown path_data_type in path_data." && false);
		} break;
		}
	}
	return{ pt0.x(), pt0.y(), pt1.x() - pt0.x(), pt1.y() - pt0.y() };
}

void path_factory::clear() noexcept {
	_Data.clear();
	_Has_current_point = { };
	_Current_point = { };
	_Extents_pt0 = { };
	_Extents_pt1 = { };
	_Transform_matrix = matrix_2d::init_identity();
	_Origin = { };
}
