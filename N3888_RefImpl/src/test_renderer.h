//#include "io2d.h"
//#include "xio2dhelpers.h"
//#include <array>
//#include <stdexcept>
//#include <cstdint>
//
//namespace not_proposed {
//	namespace test_renderer {
//		class fill_line {
//			::std::experimental::io2d::point_2d m_startPoint = { };
//			::std::experimental::io2d::point_2d m_endPoint = { };
//		public:
//			fill_line() = default;
//			fill_line(const ::std::experimental::io2d::point_2d& startPoint, const ::std::experimental::io2d::point_2d& endPoint)
//				: m_startPoint(startPoint)
//				, m_endPoint(endPoint) {}
//			fill_line(const fill_line&) = default;
//			fill_line& operator=(const fill_line&) = default;
//
//			void start_point(const ::std::experimental::io2d::point_2d& startPoint) { m_startPoint = startPoint; }
//			::std::experimental::io2d::point_2d start_point() const { return m_startPoint; }
//
//			void end_point(const ::std::experimental::io2d::point_2d& endPoint) { m_endPoint = endPoint; }
//			::std::experimental::io2d::point_2d end_point() const { return m_endPoint; }
//		};
//
//		class fill_curve {
//			::std::experimental::io2d::point_2d m_startPoint = { };
//			::std::experimental::io2d::point_2d m_controlPoint1 = { };
//			::std::experimental::io2d::point_2d m_controlPoint2 = { };
//			::std::experimental::io2d::point_2d m_endPoint = { };
//		public:
//			fill_curve() = default;
//			fill_curve(const ::std::experimental::io2d::point_2d& startPoint,
//				const ::std::experimental::io2d::point_2d& controlPoint1,
//				const ::std::experimental::io2d::point_2d& controlPoint2,
//				const ::std::experimental::io2d::point_2d& endPoint)
//				: m_startPoint(startPoint)
//				, m_controlPoint1(controlPoint1)
//				, m_controlPoint2(controlPoint2)
//				, m_endPoint(endPoint) {}
//			fill_curve(const fill_curve&) = default;
//			fill_curve& operator=(const fill_curve&) = default;
//
//			void start_point(const ::std::experimental::io2d::point_2d& startPoint) { m_startPoint = startPoint; }
//			::std::experimental::io2d::point_2d start_point() const { return m_startPoint; }
//
//			void control_point_1(const ::std::experimental::io2d::point_2d& controlPoint1) { m_controlPoint1 = controlPoint1; }
//			::std::experimental::io2d::point_2d control_point_1() const { return m_controlPoint1; }
//
//			void control_point_2(const ::std::experimental::io2d::point_2d& controlPoint2) { m_controlPoint2 = controlPoint2; }
//			::std::experimental::io2d::point_2d control_point_2() const { return m_controlPoint2; }
//
//			void end_point(const ::std::experimental::io2d::point_2d& endPoint) { m_endPoint = endPoint; }
//			::std::experimental::io2d::point_2d end_point() const { return m_endPoint; }
//		};
//
//		enum class fill_path_data_item_type {
//			error,
//			line,
//			curve
//		};
//
//		class fill_path_data_item {
//			::std::experimental::io2d::point_2d m_startPoint = { };
//			::std::experimental::io2d::point_2d m_controlPoint1 = { };
//			::std::experimental::io2d::point_2d m_controlPoint2 = { };
//			::std::experimental::io2d::point_2d m_endPoint = { };
//			fill_path_data_item_type m_type = fill_path_data_item_type::error;
//		public:
//			fill_path_data_item() = default;
//			fill_path_data_item(const fill_line& line)
//				: m_startPoint(line.start_point())
//				, m_endPoint(line.end_point())
//				, m_type(fill_path_data_item_type::line) {}
//			fill_path_data_item(const fill_curve& curve)
//				: m_startPoint(curve.start_point())
//				, m_controlPoint1(curve.control_point_1())
//				, m_controlPoint2(curve.control_point_2())
//				, m_endPoint(curve.end_point())
//				, m_type(fill_path_data_item_type::curve) {}
//			fill_path_data_item(const fill_path_data_item&) = default;
//			fill_path_data_item& operator=(const fill_path_data_item&) = default;
//
//			fill_path_data_item_type type() const {
//				return m_type;
//			}
//
//			template <class T>
//			T get() const;
//		};
//
//		template <>
//		inline fill_line fill_path_data_item::get() const {
//			if (m_type != fill_path_data_item_type::line) {
//				throw ::std::logic_error("Wrong type.");
//			}
//			return{ m_startPoint, m_endPoint };
//		}
//
//		template <>
//		inline fill_curve fill_path_data_item::get() const {
//			if (m_type != fill_path_data_item_type::curve) {
//				throw ::std::logic_error("Wrong type.");
//			}
//			return{ m_startPoint, m_controlPoint1, m_controlPoint2, m_endPoint };
//		}
//
//		void render_ellipse(::std::experimental::io2d::display_surface& ds, const ::std::experimental::io2d::point_2d& center, double xRadius, double yRadius, const ::std::experimental::io2d::bgra_color& color);
//
//		void render_fill_rect_radial_gradient(::std::experimental::io2d::display_surface& ds, const ::std::experimental::io2d::rectangle& fillArea, const ::std::experimental::io2d::radial_brush_factory& f, ::std::experimental::io2d::wrap_mode e = ::std::experimental::io2d::wrap_mode::none);
//
//		::std::experimental::io2d::bgra_color get_interpolated_color(const ::std::experimental::io2d::radial_brush_factory& f, double t, ::std::experimental::io2d::wrap_mode e = ::std::experimental::io2d::wrap_mode::none);
//
//		::std::experimental::io2d::point_2d de_casteljau(const ::std::array<::std::experimental::io2d::point_2d, 4>& p, ::std::array<::std::experimental::io2d::point_2d, 4>::size_type j, unsigned int k, double t);
//		
//		::std::array<::std::experimental::io2d::point_2d, 8> split_curve_at_t(const ::std::experimental::io2d::point_2d& startPt, const ::std::experimental::io2d::point_2d& controlPt1, const ::std::experimental::io2d::point_2d& controlPt2, const ::std::experimental::io2d::point_2d& endPt, double t);
//	}
//}
