//#pragma once
//
//#include <cmath>
//#include <vector>
//#include <variant>
//#include "io2d.h"
//
//
//namespace test_process {
//	using namespace ::std;
//	using namespace ::std::experimental::io2d;
//
//	enum class abs_cubic_curve_sfinae {};
//	constexpr abs_cubic_curve_sfinae abs_cubic_curve_sfinae_val = {};
//	enum class abs_ellipse_sfinae {};
//	constexpr static abs_ellipse_sfinae abs_ellipse_sfinae_val = {};
//	enum class abs_line_sfinae {};
//	constexpr abs_line_sfinae abs_line_sfinae_val = {};
//	enum class abs_move_sfinae {};
//	constexpr abs_move_sfinae abs_move_sfinae_val = {};
//	enum class abs_quadratic_curve_sfinae {};
//	constexpr abs_quadratic_curve_sfinae abs_quadratic_curve_sfinae_val = {};
//	enum class abs_rectangle_sfinae {};
//	constexpr static abs_rectangle_sfinae abs_rectangle_sfinae_val = {};
//	enum class arc_clockwise_sfinae {};
//	constexpr arc_clockwise_sfinae arc_clockwise_sfinae_val = {};
//	enum class arc_counterclockwise_sfinae {};
//	constexpr arc_counterclockwise_sfinae arc_counterclockwise_sfinae_val = {};
//	enum class change_matrix_sfinae {};
//	constexpr change_matrix_sfinae change_matrix_sfinae_val = {};
//	enum class change_origin_sfinae {};
//	constexpr change_origin_sfinae change_origin_sfinae_val = {};
//	enum class close_path_sfinae {};
//	constexpr close_path_sfinae close_path_sfinae_val = {};
//	enum class new_figure_sfinae {};
//	constexpr new_figure_sfinae new_figure_sfinae_val = {};
//	enum class rel_cubic_curve_sfinae {};
//	constexpr rel_cubic_curve_sfinae rel_cubic_curve_sfinae_val = {};
//	enum class rel_ellipse_sfinae {};
//	constexpr static rel_ellipse_sfinae rel_ellipse_sfinae_val = {};
//	enum class rel_line_sfinae {};
//	constexpr rel_line_sfinae rel_line_sfinae_val = {};
//	enum class rel_move_sfinae {};
//	constexpr rel_move_sfinae rel_move_sfinae_val = {};
//	enum class rel_quadratic_curve_sfinae {};
//	constexpr rel_quadratic_curve_sfinae rel_quadratic_curve_sfinae_val = {};
//	enum class rel_rectangle_sfinae {};
//	constexpr static rel_rectangle_sfinae rel_rectangle_sfinae_val = {};
//
//	template <class Allocator>
//	vector<path_data::path_data_types> process_path_data(const path_builder<Allocator>& pf);
//
//	template <class _TItem>
//	struct path_factory_process_visit {
//		constexpr static float twoThirds = 2.0 / 3.0;
//
//		template <class T, enable_if_t<is_same_v<T, path_data::abs_cubic_curve>, abs_cubic_curve_sfinae> = abs_cubic_curve_sfinae_val>
//		static void perform(const T& item, vector<path_data::path_data_types>& v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d& closePoint) {
//			auto pt1 = m.transform_pt(item.control_point_1() - origin) + origin;
//			auto pt2 = m.transform_pt(item.control_point_2() - origin) + origin;
//			auto pt3 = m.transform_pt(item.end_point() - origin) + origin;
//			if (!currentPoint.has_value()) {
//				currentPoint = item.control_point_1();
//				v.emplace_back(in_place_type<path_data::abs_move>, pt1);
//				closePoint = pt1;
//			}
//			v.emplace_back(in_place_type<path_data::abs_cubic_curve>, pt1,
//				pt2, pt3);
//			currentPoint = item.end_point();
//		}
//		template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_ellipse>, abs_ellipse_sfinae> = abs_ellipse_sfinae_val>
//		static void perform(const T& item, ::std::vector<path_data::path_data_types>&v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d& closePoint) {
//			const auto m2 = m;
//			const auto o2 = origin;
//			currentPoint.reset();
//			path_factory_process_visit<path_data::set_origin>::template perform(path_data::set_origin{ item.center() }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit<path_data::set_matrix>::template perform(path_data::abs_matrix{ matrix_2d::init_scale({ item.x_radius() / item.y_radius(), 1.0 }) * m }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit<path_data::arc_clockwise>::template perform(path_data::arc_clockwise{ item.center(), item.y_radius(), 0.0, two_pi<float> }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit<path_data::abs_matrix>::template perform(path_data::abs_matrix{ m2 }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit<path_data::set_origin>::template perform(path_data::set_origin{ o2 }, v, m, origin, currentPoint, closePoint);
//		}
//		template <class T, enable_if_t<is_same_v<T, path_data::abs_line>, abs_line_sfinae> = abs_line_sfinae_val>
//		static void perform(const T& item, vector<path_data::path_data_types>& v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d& closePoint) {
//			if (currentPoint.has_value()) {
//				currentPoint = item.to();
//				auto pt = m.transform_pt(currentPoint.value() - origin) + origin;
//				v.emplace_back(in_place_type<path_data::abs_line>, pt);
//			}
//			else {
//				currentPoint = item.to();
//				auto pt = m.transform_pt(currentPoint.value() - origin) + origin;
//				v.emplace_back(in_place_type<path_data::abs_move>, pt);
//				v.emplace_back(in_place_type<path_data::abs_line>, pt);
//				closePoint = pt;
//			}
//		}
//		template <class T, enable_if_t<is_same_v<T, path_data::abs_move>, abs_move_sfinae> = abs_move_sfinae_val>
//		static void perform(const T& item, vector<path_data::path_data_types>& v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d& closePoint) {
//			currentPoint = item.to();
//			auto pt = m.transform_pt(currentPoint.value() - origin) + origin;
//			v.emplace_back(in_place_type<path_data::abs_move>, pt);
//			closePoint = pt;
//		}
//		template <class T, enable_if_t<is_same_v<T, path_data::abs_quadratic_curve>, abs_quadratic_curve_sfinae> = abs_quadratic_curve_sfinae_val>
//		static void perform(const T& item, vector<path_data::path_data_types>& v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d& closePoint) {
//			// Turn it into a cubic curve since cairo doesn't have quadratic curves.
//			point_2d beginPt;
//			auto controlPt = m.transform_pt(item.control_point() - origin) + origin;
//			auto endPt = m.transform_pt(item.end_point() - origin) + origin;
//			if (!currentPoint.has_value()) {
//				currentPoint = item.control_point();
//				v.emplace_back(in_place_type<path_data::abs_move>, controlPt);
//				closePoint = controlPt;
//				beginPt = controlPt;
//			}
//			else {
//				beginPt = m.transform_pt(currentPoint.value() - origin) + origin;
//			}
//			point_2d cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y() - beginPt.y()) * twoThirds) + beginPt.y() };
//			point_2d cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y() - endPt.y()) * twoThirds) + endPt.y() };
//			v.emplace_back(in_place_type<path_data::abs_cubic_curve>, cpt1, cpt2, endPt);
//			currentPoint = item.end_point();
//		}
//		template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_rectangle>, abs_rectangle_sfinae> = abs_rectangle_sfinae_val>
//		static void perform(const T& item, ::std::vector<path_data::path_data_types>&v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d& closePoint) {
//			path_factory_process_visit::template perform(path_data::abs_move{ { item.x(), item.y() } }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit::template perform(path_data::rel_line{ { item.width(), 0.0 } }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit::template perform(path_data::rel_line{ { 0.0, item.height() } }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit::template perform(path_data::rel_line{ { -item.width(), 0.0 } }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit::template perform(path_data::close_path{ { item.x(), item.y() } }, v, m, origin, currentPoint, closePoint);
//		}
//		template <class T, enable_if_t<is_same_v<T, path_data::arc_clockwise>, arc_clockwise_sfinae> = arc_clockwise_sfinae_val>
//		static void perform(const T& item, vector<path_data::path_data_types>& v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d& closePoint) {
//			{
//				auto ctr = item.center();
//				auto rad = item.radius();
//				auto ang1 = item.angle_1();
//				auto ang2 = item.angle_2();
//				while (ang2 < ang1) {
//					ang2 += two_pi<float>;
//				}
//				point_2d pt0, pt1, pt2, pt3;
//				int bezCount = 1;
//				float theta = ang2 - ang1;
//				float phi{};
//				while (theta >= half_pi<float>) {
//					theta /= 2.0;
//					bezCount += bezCount;
//				}
//				phi = theta / 2.0;
//				auto cosPhi = cos(phi);
//				auto sinPhi = sin(phi);
//				pt0.x(cosPhi);
//				pt0.y(-sinPhi);
//				pt3.x(pt0.x());
//				pt3.y(-pt0.y());
//				pt1.x((4.0 - cosPhi) / 3.0);
//				pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
//				pt2.x(pt1.x());
//				pt2.y(-pt1.y());
//				phi = -phi;
//				auto rotCwFn = [](const point_2d& pt, float a) -> point_2d {
//					return { pt.x() * cos(a) + pt.y() * sin(a),
//						-(pt.x() * -(sin(a)) + pt.y() * cos(a)) };
//				};
//				pt0 = rotCwFn(pt0, phi);
//				pt1 = rotCwFn(pt1, phi);
//				pt2 = rotCwFn(pt2, phi);
//				pt3 = rotCwFn(pt3, phi);
//
//				auto currTheta = ang1;
//				const auto startPt =
//					ctr + rotCwFn({ pt0.x() * rad, pt0.y() * rad }, currTheta);
//				if (currentPoint.has_value()) {
//					currentPoint = startPt;
//					auto pt = m.transform_pt(currentPoint.value() - origin) + origin;
//					v.emplace_back(in_place_type<path_data::abs_line>, pt);
//				}
//				else {
//					currentPoint = startPt;
//					auto pt = m.transform_pt(currentPoint.value() - origin) + origin;
//					v.emplace_back(in_place_type<path_data::abs_move>, pt);
//					closePoint = pt;
//				}
//				for (; bezCount > 0; bezCount--) {
//					auto cpt1 = ctr + rotCwFn({ pt1.x() * rad, pt1.y() * rad }, currTheta);
//					auto cpt2 = ctr + rotCwFn({ pt2.x() * rad, pt2.y() * rad },
//						currTheta);
//					auto cpt3 = ctr + rotCwFn({ pt3.x() * rad, pt3.y() * rad },
//						currTheta);
//					currentPoint = cpt3;
//					cpt1 = m.transform_pt(cpt1 - origin) + origin;
//					cpt2 = m.transform_pt(cpt2 - origin) + origin;
//					cpt3 = m.transform_pt(cpt3 - origin) + origin;
//					v.emplace_back(in_place_type<path_data::abs_cubic_curve>, cpt1,
//						cpt2, cpt3);
//					currTheta += theta;
//				}
//			}
//		}
//		template <class T, enable_if_t<is_same_v<T, path_data::arc_counterclockwise>, arc_counterclockwise_sfinae> = arc_counterclockwise_sfinae_val>
//		static void perform(const T& item, vector<path_data::path_data_types>& v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d& closePoint) {
//			{
//				auto ctr = item.center();
//				auto rad = item.radius();
//				auto ang1 = item.angle_1();
//				auto ang2 = item.angle_2();
//				while (ang2 > ang1) {
//					ang2 -= two_pi<float>;
//				}
//				point_2d pt0, pt1, pt2, pt3;
//				int bezCount = 1;
//				float theta = ang1 - ang2;
//				float phi{};
//				while (theta >= half_pi<float>) {
//					theta /= 2.0;
//					bezCount += bezCount;
//				}
//				phi = theta / 2.0;
//				auto cosPhi = cos(phi);
//				auto sinPhi = sin(phi);
//				pt0.x(cosPhi);
//				pt0.y(-sinPhi);
//				pt3.x(pt0.x());
//				pt3.y(-pt0.y());
//				pt1.x((4.0 - cosPhi) / 3.0);
//				pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
//				pt2.x(pt1.x());
//				pt2.y(-pt1.y());
//				auto rotCwFn = [](const point_2d& pt, float a) -> point_2d {
//					return { pt.x() * cos(a) + pt.y() * sin(a),
//						-(pt.x() * -(sin(a)) + pt.y() * cos(a)) };
//				};
//				pt0 = rotCwFn(pt0, phi);
//				pt1 = rotCwFn(pt1, phi);
//				pt2 = rotCwFn(pt2, phi);
//				pt3 = rotCwFn(pt3, phi);
//				auto shflPt = pt3;
//				pt3 = pt0;
//				pt0 = shflPt;
//				shflPt = pt2;
//				pt2 = pt1;
//				pt1 = shflPt;
//				auto currTheta = ang1;
//				const auto startPt =
//					ctr + rotCwFn({ pt0.x() * rad, pt0.y() * rad }, currTheta);
//				if (currentPoint.has_value()) {
//					currentPoint = startPt;
//					auto pt = m.transform_pt(currentPoint.value() - origin) + origin;
//					v.emplace_back(in_place_type<path_data::abs_line>, pt);
//				}
//				else {
//					currentPoint = startPt;
//					auto pt = m.transform_pt(currentPoint.value() - origin) + origin;
//					v.emplace_back(in_place_type<path_data::abs_move>, pt);
//					closePoint = pt;
//				}
//				for (; bezCount > 0; bezCount--) {
//					auto cpt1 = ctr + rotCwFn({ pt1.x() * rad, pt1.y() * rad },
//						currTheta);
//					auto cpt2 = ctr + rotCwFn({ pt2.x() * rad, pt2.y() * rad },
//						currTheta);
//					auto cpt3 = ctr + rotCwFn({ pt3.x() * rad, pt3.y() * rad },
//						currTheta);
//					currentPoint = cpt3;
//					cpt1 = m.transform_pt(cpt1 - origin) + origin;
//					cpt2 = m.transform_pt(cpt2 - origin) + origin;
//					cpt3 = m.transform_pt(cpt3 - origin) + origin;
//					v.emplace_back(in_place_type<path_data::abs_cubic_curve>, cpt1,
//						cpt2, cpt3);
//					currTheta -= theta;
//				}
//			}
//		}
//		template <class T, enable_if_t<is_same_v<T, path_data::abs_matrix>, change_matrix_sfinae> = change_matrix_sfinae_val>
//		static void perform(const T& item, vector<path_data::path_data_types>&, matrix_2d& m, point_2d&, optional<point_2d>&, point_2d&) {
//			if (!m.is_finite()) {
//				throw system_error(make_error_code(io2d_error::invalid_matrix));
//			}
//			if (!m.is_invertible()) {
//				throw system_error(make_error_code(io2d_error::invalid_matrix));
//				return;
//			}
//			m = item.matrix();
//		}
//		template <class T, enable_if_t<is_same_v<T, path_data::set_origin>, change_origin_sfinae> = change_origin_sfinae_val>
//		static void perform(const T& item, vector<path_data::path_data_types>&, matrix_2d&, point_2d& origin, optional<point_2d>&, point_2d&) {
//			origin = item.origin();
//		}
//		template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::close_path>, close_path_sfinae> = close_path_sfinae_val>
//		static void perform(const T&, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d& closePoint) {
//			if (currentPoint.has_value()) {
//				v.emplace_back(::std::in_place_type<path_data::close_path>, closePoint);
//				v.emplace_back(::std::in_place_type<path_data::abs_move>,
//					closePoint);
//				if (!m.is_finite() || !m.is_invertible()) {
//					throw ::std::system_error(::std::make_error_code(io2d_error::invalid_matrix));
//				}
//				auto invM = matrix_2d{ m }.invert();
//				// Need to assign the untransformed closePoint value to currentPoint.
//				currentPoint = invM.transform_pt(closePoint - origin) + origin;
//			}
//		}
//		template <class T, enable_if_t<is_same_v<T, path_data::new_figure>, new_figure_sfinae> = new_figure_sfinae_val>
//		static void perform(const T&, vector<path_data::path_data_types>&, matrix_2d&, point_2d&, optional<point_2d>& currentPoint, point_2d&) {
//			currentPoint.reset();
//		}
//		template <class T, enable_if_t<is_same_v<T, path_data::rel_cubic_curve>, rel_cubic_curve_sfinae> = rel_cubic_curve_sfinae_val>
//		static void perform(const T& item, vector<path_data::path_data_types>& v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d&) {
//			if (!currentPoint.has_value()) {
//				throw system_error(make_error_code(io2d_error::invalid_path_data));
//			}
//			auto pt1 = m.transform_pt(item.control_point_1() + currentPoint.value() -
//				origin) + origin;
//			auto pt2 = m.transform_pt(item.control_point_2() + currentPoint.value() -
//				origin) + origin;
//			auto pt3 = m.transform_pt(item.end_point() + currentPoint.value() - origin) +
//				origin;
//			v.emplace_back(in_place_type<path_data::abs_cubic_curve>,
//				pt1, pt2, pt3);
//			currentPoint = item.end_point() + currentPoint.value();
//		}
//		template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_ellipse>, rel_ellipse_sfinae> = rel_ellipse_sfinae_val>
//		static void perform(const T& item, ::std::vector<path_data::path_data_types>&v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d& closePoint) {
//			if (!currentPoint.has_value()) {
//				throw ::std::system_error(::std::make_error_code(io2d_error::invalid_path_data));
//			}
//			const auto m2 = m;
//			const auto o2 = origin;
//			const auto cpt2 = currentPoint;
//			currentPoint.reset();
//			path_factory_process_visit::template perform(path_data::set_origin{ item.center() + cpt2.value() }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit::template perform(path_data::abs_matrix{ matrix_2d::init_scale({ item.x_radius() / item.y_radius(), 1.0 }) * m }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit::template perform(path_data::arc_clockwise{ item.center() + cpt2.value(), item.y_radius(), 0.0, two_pi<float> }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit::template perform(path_data::abs_matrix{ m2 }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit::template perform(path_data::set_origin{ o2 }, v, m, origin, currentPoint, closePoint);
//		}
//		template <class T, enable_if_t<is_same_v<T, path_data::rel_line>, rel_line_sfinae> = rel_line_sfinae_val>
//		static void perform(const T& item, vector<path_data::path_data_types>& v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d&) {
//			if (!currentPoint.has_value()) {
//				throw system_error(make_error_code(io2d_error::invalid_path_data));
//			}
//			currentPoint = item.to() + currentPoint.value();
//			auto pt = m.transform_pt(currentPoint.value() - origin) + origin;
//			v.emplace_back(in_place_type<path_data::abs_line>, pt);
//		}
//		template <class T, enable_if_t<is_same_v<T, path_data::rel_move>, rel_move_sfinae> = rel_move_sfinae_val>
//		static void perform(const T& item, vector<path_data::path_data_types>& v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d& closePoint) {
//			if (!currentPoint.has_value()) {
//				throw system_error(make_error_code(io2d_error::invalid_path_data));
//			}
//			currentPoint = item.to() + currentPoint.value();
//			auto pt = m.transform_pt(currentPoint.value() - origin) + origin;
//			v.emplace_back(in_place_type<path_data::abs_move>, pt);
//			closePoint = pt;
//		}
//		template <class T, enable_if_t<is_same_v<T, path_data::rel_quadratic_curve>, rel_quadratic_curve_sfinae> = rel_quadratic_curve_sfinae_val>
//		static void perform(const T& item, vector<path_data::path_data_types>& v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d&) {
//			if (!currentPoint.has_value()) {
//				throw system_error(make_error_code(io2d_error::invalid_path_data));
//			}
//			// Turn it into a cubic curve since cairo doesn't have quadratic curves.
//			point_2d beginPt;
//			auto controlPt = m.transform_pt(item.control_point() + currentPoint.value() -
//				origin) + origin;
//			auto endPt = m.transform_pt(item.end_point() + currentPoint.value() -
//				origin) + origin;
//			beginPt = m.transform_pt(currentPoint.value() - origin) + origin;
//			point_2d cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y() - beginPt.y()) * twoThirds) + beginPt.y() };
//			point_2d cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y() - endPt.y()) * twoThirds) + endPt.y() };
//			v.emplace_back(in_place_type<path_data::abs_cubic_curve>, cpt1, cpt2, endPt);
//			currentPoint = item.end_point() + currentPoint.value();
//		}
//		template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_rectangle>, rel_rectangle_sfinae> = rel_rectangle_sfinae_val>
//		static void perform(const T& item, ::std::vector<path_data::path_data_types>&v, matrix_2d& m, point_2d& origin, optional<point_2d>& currentPoint, point_2d& closePoint) {
//			path_factory_process_visit::template perform(path_data::rel_move{ { item.x(), item.y() } }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit::template perform(path_data::rel_line{ { item.width(), 0.0 } }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit::template perform(path_data::rel_line{ { 0.0, item.height() } }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit::template perform(path_data::rel_line{ { -item.width(), 0.0 } }, v, m, origin, currentPoint, closePoint);
//			path_factory_process_visit::template perform(path_data::close_path{ { item.x(), item.y() } }, v, m, origin, currentPoint, closePoint);
//		}
//	};
//
//	template <class Allocator>
//	inline vector<path_data::path_data_types> process_path_data(const path_builder<Allocator>& pf) {
//		matrix_2d m;
//		point_2d origin;
//		optional<point_2d> currentPoint = optional<point_2d>{}; // Tracks the untransformed current point.
//		point_2d closePoint;   // Tracks the transformed close point.
//		vector<path_data::path_data_types> v;
//
//		for (const path_data::path_data_types& val : pf) {
//			visit([&m, &origin, &currentPoint, &closePoint, &v](auto&& item) {
//				using T = remove_cv_t<remove_reference_t<decltype(item)>>;
//				path_factory_process_visit<T>::template perform<T>(item, v, m, origin, currentPoint, closePoint);
//			}, val);
//		}
//		return v;
//	}
//}
