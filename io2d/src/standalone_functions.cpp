#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				const ::std::error_category& io2d_category() noexcept {
					static io2d_error_category ec;
					return ec;
				}

				display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, scaling scl, refresh_rate rr, double desiredFramerate) {
					return display_surface(preferredWidth, preferredHeight, preferredFormat, scl, rr, desiredFramerate);
				}

				display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, scaling scl, refresh_rate rr, double desiredFramerate) {
					return display_surface(preferredWidth, preferredHeight, preferredFormat, preferredDisplayWidth, preferredDisplayHeight,scl, rr, desiredFramerate);
				}

				image_surface make_image_surface(format fmt, int width, int height) {
					return image_surface(fmt, width, height);
				}

				int format_stride_for_width(format format, int width) noexcept {
					return cairo_format_stride_for_width(_Format_to_cairo_format_t(format), width);
				}
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}

namespace std {
	::std::error_condition make_error_condition(io2d_error err) noexcept {
		return ::std::error_condition(static_cast<int>(err), io2d_category());
	}

	::std::error_code make_error_code(io2d_error e) noexcept {
		return ::std::error_code(static_cast<int>(e), io2d_category());
	}

}

namespace {
	// Declarations

	double _Curve_value_for_t(double a, double b, double c, double d, double t) noexcept;
	inline vector_2d _Cubic_bezier_derivative_for_t(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, const vector_2d& pt3, double t) noexcept;
	inline bool _Same_sign(double lhs, double rhs) noexcept;
	double _Find_t_for_d_of_t_equal_zero(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, const vector_2d& pt3, double t0, double t2, const bool findX, const double epsilon = numeric_limits<double>::epsilon()) noexcept;
	vector_2d _Rotate_point(const vector_2d& pt, double angle, bool clockwise = true) noexcept;

	// Definitions

	double _Curve_value_for_t(double a, double b, double c, double d, double t) noexcept {
		return pow(1.0 - t, 3.0) * a + 3.0 * pow(1.0 - t, 2.0) * t * b + 3.0 * (1.0 - t) * pow(t, 2.0) * c + pow(t, 3.0) * d;
	}

	inline vector_2d _Cubic_bezier_derivative_for_t(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, const vector_2d& pt3, double t) noexcept {
		return vector_2d{ 3.0 * pow(1.0 - t, 2.0) * (pt1 - pt0).x(), 3.0 * pow(1.0 - t, 2.0) * (pt1 - pt0).y() } +
			vector_2d{ 6.0 * (1.0 - t) * t * (pt2 - pt1).x(), 6.0 * (1.0 - t) * t * (pt2 - pt1).y() } +
			vector_2d{ 3.0 * pow(t, 2.0) * (pt3 - pt2).x(), 3.0 * pow(t, 2.0) * (pt3 - pt2).y() };
	}

	inline bool _Same_sign(double lhs, double rhs) noexcept {
		return ((lhs < 0.0) && (rhs < 0.0)) || ((lhs > 0.0) && (rhs > 0.0));
	}

	double _Find_t_for_d_of_t_equal_zero(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, const vector_2d& pt3, double t0, double t2, const bool findX, const double epsilon) noexcept {
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

	vector_2d _Rotate_point(const vector_2d& pt, double angle, bool clockwise) noexcept {
		if (clockwise) {
			return{ pt.x() * cos(angle) + pt.y() * sin(angle), -(pt.x() * -(sin(angle)) + pt.y() * cos(angle)) };
		}
		else {
			return{ pt.x() * cos(angle) + pt.y() * sin(angle), pt.x() * -(sin(angle)) + pt.y() * cos(angle) };
		}
	}
}


namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				vector_2d _Curve_point_at_t(const vector_2d& startPt, const vector_2d& controlPt1, const vector_2d& controlPt2, const vector_2d& endPt, double t) noexcept {
					return{ _Curve_value_for_t(startPt.x(), controlPt1.x(), controlPt2.x(), endPt.x(), t), _Curve_value_for_t(startPt.y(), controlPt1.y(), controlPt2.y(), endPt.y(), t) };
				}

				vector<path_data_item> _Get_arc_as_beziers(const vector_2d& center, double radius, double angle1, double angle2, bool arcNegative, bool hasCurrentPoint, const vector_2d& /*currentPoint*/, const vector_2d& origin, const matrix_2d& matrix) {
					if (arcNegative) {
						while (angle2 > angle1) {
#if _Variable_templates_conditional_support_test
							angle2 -= two_pi<double>;
#else
							angle2 -= two_pi<double>();
#endif
						}
					}
					else {
						while (angle2 < angle1) {
#if _Variable_templates_conditional_support_test
							angle2 += two_pi<double>;
#else
							angle2 += two_pi<double>();
#endif
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

#if _Variable_templates_conditional_support_test
						while (theta >= half_pi<double>) {
							theta /= 2.0;
							bezierCount += bezierCount;
						}
#else
						while (theta >= half_pi<double>()) {
							theta /= 2.0;
							bezierCount += bezierCount;
						}
#endif

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
					pb.change_origin(origin);
					pb.change_matrix(matrix);

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

				vector<path_data_item> _Get_arc_as_beziers(const vector_2d& center, double radius, double angle1, double angle2, error_code& ec, bool arcNegative, bool hasCurrentPoint, const vector_2d& /*currentPoint*/, const vector_2d& origin, const matrix_2d& matrix) noexcept {
					if (arcNegative) {
						while (angle2 > angle1) {
#if _Variable_templates_conditional_support_test
							angle2 -= two_pi<double>;
#else
							angle2 -= two_pi<double>();
#endif
						}
					}
					else {
						while (angle2 < angle1) {
#if _Variable_templates_conditional_support_test
							angle2 += two_pi<double>;
#else
							angle2 += two_pi<double>();
#endif
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

#if _Variable_templates_conditional_support_test
						while (theta >= half_pi<double>) {
							theta /= 2.0;
							bezierCount += bezierCount;
						}
#else
						while (theta >= half_pi<double>()) {
							theta /= 2.0;
							bezierCount += bezierCount;
						}
#endif

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
					pb.change_origin(origin, ec);
					if (static_cast<bool>(ec)) {
						// Relies on C++17 noexcept guarantee for vector default ctor (N4258, adopted 2014-11).
						return vector<path_data_item>();
					}
					pb.change_matrix(matrix, ec);
					if (static_cast<bool>(ec)) {
						// Relies on C++17 noexcept guarantee for vector default ctor (N4258, adopted 2014-11).
						return vector<path_data_item>();
					}

					const auto startPoint = center + _Rotate_point({ pt0.x() * radius, pt0.y() * radius }, currentTheta);
					if (hasCurrentPoint) {
						//pb.move_to(currentPoint, ec);
						//if (static_cast<bool>(ec)) {
						//	// Relies on C++17 noexcept guarantee for vector default ctor (N4258, adopted 2014-11).
						//	return vector<path_data_item>();
						//}
						pb.line_to(startPoint, ec);
						if (static_cast<bool>(ec)) {
							// Relies on C++17 noexcept guarantee for vector default ctor (N4258, adopted 2014-11).
							return vector<path_data_item>();
						}
					}
					else {
						pb.move_to(startPoint, ec);
						if (static_cast<bool>(ec)) {
							// Relies on C++17 noexcept guarantee for vector default ctor (N4258, adopted 2014-11).
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
							// Relies on C++17 noexcept guarantee for vector default ctor (N4258, adopted 2014-11).
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
						// Relies on C++17 noexcept guarantee for vector default ctor (N4258, adopted 2014-11).
						return vector<path_data_item>();
					}
				}

				void _Get_arc_extents(const ::std::experimental::io2d::vector_2d& center, double radius, double angle1, double angle2, bool arcNegative, bool& hasCurrentPoint, ::std::experimental::io2d::vector_2d& currentPoint, ::std::experimental::io2d::vector_2d& transformedCurrentPoint, ::std::experimental::io2d::vector_2d& lastMoveToPoint, bool& hasExtents, vector_2d& exPt0, vector_2d& exPt1, ::std::experimental::io2d::vector_2d& origin, ::std::experimental::io2d::matrix_2d& transformMatrix) noexcept {
					if (arcNegative) {
						while (angle2 > angle1) {
#if _Variable_templates_conditional_support_test
							angle2 -= two_pi<double>;
#else
							angle2 -= two_pi<double>();
#endif
						}
					}
					else {
						while (angle2 < angle1) {
#if _Variable_templates_conditional_support_test
							angle2 += two_pi<double>;
#else
							angle2 += two_pi<double>();
#endif
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

#if _Variable_templates_conditional_support_test
						while (theta >= half_pi<double>) {
							theta /= 2.0;
							bezierCount += bezierCount;
						}
#else
						while (theta >= half_pi<double>()) {
							theta /= 2.0;
							bezierCount += bezierCount;
						}
#endif

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
						// line_to
						auto itemPt = transformMatrix.transform_point(startPoint - origin) + origin;
						if (!hasExtents) {
							hasExtents = true;
							exPt0.x(min(transformedCurrentPoint.x(), itemPt.x()));
							exPt0.y(min(transformedCurrentPoint.y(), itemPt.y()));
							exPt1.x(max(transformedCurrentPoint.x(), itemPt.x()));
							exPt1.y(max(transformedCurrentPoint.y(), itemPt.y()));
						}
						else {
							exPt0.x(min(min(exPt0.x(), transformedCurrentPoint.x()), itemPt.x()));
							exPt0.y(min(min(exPt0.y(), transformedCurrentPoint.y()), itemPt.y()));
							exPt1.x(max(max(exPt1.x(), transformedCurrentPoint.x()), itemPt.x()));
							exPt1.y(max(max(exPt1.y(), transformedCurrentPoint.y()), itemPt.y()));
						}
						currentPoint = startPoint;
						transformedCurrentPoint = itemPt;
					}
					else {
						// move_to
						currentPoint = startPoint;
						transformedCurrentPoint = transformMatrix.transform_point(startPoint - origin) + origin;
						lastMoveToPoint = startPoint;
						hasCurrentPoint = true;
					}

					// We start at the point derived from angle1 and continue adding beziers until the count reaches zero.
					// The point we have is already rotated by half of theta.
					for (; bezierCount > 0; bezierCount--) {
						// curve_to
						assert(hasCurrentPoint);
						vector_2d cte0{};
						vector_2d cte1{};
						auto ctrlPt1 = center + _Rotate_point({ pt1.x() * radius, pt1.y() * radius }, currentTheta);
						auto ctrlPt2 = center + _Rotate_point({ pt2.x() * radius, pt2.y() * radius }, currentTheta);
						auto endPt = center + _Rotate_point({ pt3.x() * radius, pt3.y() * radius }, currentTheta);
						auto itemPt1 = transformMatrix.transform_point(ctrlPt1 - origin) + origin;
						auto itemPt2 = transformMatrix.transform_point(ctrlPt2 - origin) + origin;
						auto itemPt3 = transformMatrix.transform_point(endPt - origin) + origin;
						_Curve_to_extents(transformedCurrentPoint, itemPt1, itemPt2, itemPt3, cte0, cte1);
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
						currentPoint = endPt;
						transformedCurrentPoint = itemPt3;
					}
				}

				void _Curve_to_extents(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, const vector_2d& pt3, vector_2d& extents0, vector_2d& extents1) noexcept {
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

#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}

