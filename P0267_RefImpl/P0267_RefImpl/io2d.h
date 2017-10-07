#pragma once

#ifndef _IO2D_
#define _IO2D_

#define __cpp_lib_experimental_io2d 201707

#include <memory>
#include <functional>
#include <exception>
#include <vector>
#include <string>
#include <algorithm>
#include <system_error>
#include <cstdint>
#include <atomic>
#include <variant>
#include <optional>
#include <cmath>
#include <type_traits>
#include <initializer_list>
#include <cmath>
#include <chrono>

#include "xio2d.h"

#ifdef _Filesystem_support_test
#include <filesystem>
#endif

#if defined BUILD_IO2D_API_DLL 
#define _IO2D_API __declspec(dllexport)
#elif defined USE_IO2D_API_DLL
#define _IO2D_API __declspec(dllimport)
#else
#define _IO2D_API
#endif

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {

				template <class T>
				constexpr T pi = T(3.14159265358979323846264338327950288L);

				template <class T>
				constexpr T two_pi = T(6.28318530717958647692528676655900577L);

				template <class T>
				constexpr T half_pi = T(1.57079632679489661923132169163975144L);

				template <class T>
				constexpr T three_pi_over_two = T(4.71238898038468985769396507491925432L);

				template <class T>
				constexpr T tau = T(6.28318530717958647692528676655900577L);

				template <class T>
				constexpr T three_quarters_tau = T(4.71238898038468985769396507491925432L);

				template <class T>
				constexpr T half_tau = T(3.14159265358979323846264338327950288L);

				template <class T>
				constexpr T quarter_tau = T(1.57079632679489661923132169163975144L);
			}
		}
	}
}

#include "xcolor.h"
#include "xlinear_algebra.h"
#include "xgeometry.h"
#include "xtext.h"
#include "xpath.h"
#include "xbrushes.h"
#include "xsurfaces.h"
#include "xinput.h"

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {

				//using dashes = tuple<vector<float>, float>;

				//enum class wrap_mode;
				//enum class filter;
				//enum class brush_type;
				//enum class antialias;
				//enum class fill_rule;
				//enum class line_cap;
				//enum class line_join;
				//enum class compositing_op;
				//enum class format;
				//enum class scaling;
				//enum class refresh_rate;
				//enum class image_file_format;

				//class bounding_box;
				//constexpr bool operator==(const bounding_box& lhs, const bounding_box& rhs)
				//	noexcept;
				//constexpr bool operator!=(const bounding_box& lhs, const bounding_box& rhs)
				//	noexcept;

				//class circle;
				//constexpr bool operator==(const circle& lhs, const circle& rhs) noexcept;
				//constexpr bool operator!=(const circle& lhs, const circle& rhs) noexcept;

				//class rgba_color;
				constexpr bool operator==(const rgba_color& lhs, const rgba_color& rhs)
					noexcept;
				constexpr bool operator!=(const rgba_color& lhs, const rgba_color& rhs)
					noexcept;
				template <class T>
				constexpr rgba_color operator*(const rgba_color& lhs, T rhs) noexcept;
				template <class U>
				constexpr rgba_color operator*(const rgba_color& lhs, U rhs) noexcept;
				template <class T>
				constexpr rgba_color operator*(T lhs, const rgba_color& rhs) noexcept;
				template <class U>
				constexpr rgba_color operator*(U lhs, const rgba_color& rhs) noexcept;

				//template <class T, class U>
				//struct basic_linear_algebra {
				//	class point_2d {
				//		using data_type = typename T::point_2d_data_type;
				//		data_type _Data;

				//	public:
				//		constexpr const data_type& _Get_data() const noexcept;
				//		constexpr point_2d(const data_type& val) noexcept;

				//		// \ref{\iotwod.\pointtwod.cons}, constructors:
				//		constexpr point_2d() noexcept;
				//		constexpr point_2d(float xval, float yval) noexcept;

				//		constexpr void x(float val) noexcept;
				//		constexpr void y(float val) noexcept;
				//		constexpr float x() const noexcept;
				//		constexpr float y() const noexcept;

				//		// \ref{\iotwod.\pointtwod.observers}, observers:
				//		constexpr float dot(const point_2d& other) const noexcept;
				//		float magnitude() const noexcept;
				//		constexpr float magnitude_squared() const noexcept;
				//		float angular_direction() const noexcept;
				//		point_2d to_unit() const noexcept;
				//		constexpr point_2d zero() noexcept;

				//		// \ref{\iotwod.\pointtwod.member.ops}, member operators:
				//		constexpr point_2d& operator+=(const point_2d& rhs) noexcept;
				//		constexpr point_2d& operator+=(float rhs) noexcept;
				//		constexpr point_2d& operator-=(const point_2d& rhs) noexcept;
				//		constexpr point_2d& operator-=(float rhs) noexcept;
				//		constexpr point_2d& operator*=(const point_2d& rhs) noexcept;
				//		constexpr point_2d& operator*=(float rhs) noexcept;
				//		constexpr point_2d& operator/=(const point_2d& rhs) noexcept;
				//		constexpr point_2d& operator/=(float rhs) noexcept;
				//	};

				//	class matrix_2d {
				//		using data_type = typename U::matrix_2d_data_type;
				//		typename data_type _Data;
				//	public:
				//		constexpr const typename data_type& _Get_data() const noexcept;
				//		constexpr matrix_2d(const data_type& val) noexcept;

				//		constexpr matrix_2d() noexcept;
				//		constexpr matrix_2d(float v00, float v01, float v10, float v11, float v20, float v21) noexcept;

				//		constexpr void m00(float val) noexcept;
				//		constexpr void m01(float val) noexcept;
				//		constexpr void m02(float val) noexcept;
				//		constexpr void m10(float val) noexcept;
				//		constexpr void m11(float val) noexcept;
				//		constexpr void m12(float val) noexcept;
				//		constexpr void m20(float val) noexcept;
				//		constexpr void m21(float val) noexcept;
				//		constexpr void m22(float val) noexcept;

				//		constexpr float m00() const noexcept;
				//		constexpr float m01() const noexcept;
				//		constexpr float m02() const noexcept;
				//		constexpr float m10() const noexcept;
				//		constexpr float m11() const noexcept;
				//		constexpr float m12() const noexcept;
				//		constexpr float m20() const noexcept;
				//		constexpr float m21() const noexcept;
				//		constexpr float m22() const noexcept;

				//		// \ref{\iotwod.\matrixtwod.staticfactories}, static factory functions:
				//		constexpr static matrix_2d init_translate(const point_2d& val) noexcept;
				//		constexpr static matrix_2d init_scale(const point_2d& val) noexcept;
				//		static matrix_2d init_rotate(float radians) noexcept;
				//		static matrix_2d init_rotate(float radians, const point_2d& origin) noexcept;
				//		static matrix_2d init_reflect(float radians) noexcept;
				//		constexpr static matrix_2d init_shear_x(float factor) noexcept;
				//		constexpr static matrix_2d init_shear_y(float factor) noexcept;

				//		// \ref{\iotwod.\matrixtwod.modifiers}, modifiers:
				//		constexpr matrix_2d& translate(const point_2d& v) noexcept;
				//		constexpr matrix_2d& scale(const point_2d& v) noexcept;
				//		matrix_2d& rotate(float radians) noexcept;
				//		matrix_2d& rotate(float radians, const point_2d& origin) noexcept;
				//		matrix_2d& reflect(float radians) noexcept;
				//		constexpr matrix_2d& shear_x(float factor) noexcept;
				//		constexpr matrix_2d& shear_y(float factor) noexcept;

				//		// \ref{\iotwod.\matrixtwod.observers}, observers:
				//		constexpr bool is_finite() const noexcept;
				//		constexpr bool is_invertible() const noexcept;
				//		constexpr float determinant() const noexcept;
				//		constexpr matrix_2d inverse() const noexcept;
				//		constexpr point_2d transform_pt(const point_2d& pt) const noexcept;

				//		constexpr matrix_2d& operator*=(const matrix_2d& other) noexcept;
				//	};
				//};

				//template <class T, class U>
				//constexpr bool operator==(const typename basic_linear_algebra<T, U>::point_2d& lhs, const typename basic_linear_algebra<T, U>::point_2d& rhs) noexcept;
				//template <class T, class U>
				//constexpr bool operator!=(const typename basic_linear_algebra<T, U>::point_2d& lhs, const typename basic_linear_algebra<T, U>::point_2d& rhs) noexcept;
				//template <class T, class U>
				//constexpr typename basic_linear_algebra<T, U>::point_2d operator+(const typename basic_linear_algebra<T, U>::point_2d& val) noexcept;
				//template <class T, class U>
				//constexpr typename basic_linear_algebra<T, U>::point_2d operator+(const typename basic_linear_algebra<T, U>::point_2d& lhs, const typename basic_linear_algebra<T, U>::point_2d& rhs) noexcept;
				//template <class T, class U>
				//constexpr typename basic_linear_algebra<T, U>::point_2d operator-(const typename basic_linear_algebra<T, U>::point_2d& val) noexcept;
				//template <class T, class U>
				//constexpr typename basic_linear_algebra<T, U>::point_2d operator-(const typename basic_linear_algebra<T, U>::point_2d& lhs, const typename basic_linear_algebra<T, U>::point_2d& rhs) noexcept;
				//template <class T, class U>
				//constexpr typename basic_linear_algebra<T, U>::point_2d operator*(const typename basic_linear_algebra<T, U>::point_2d& lhs, float rhs) noexcept;
				//template <class T, class U>
				//constexpr typename basic_linear_algebra<T, U>::point_2d operator*(float lhs, const typename basic_linear_algebra<T, U>::point_2d& rhs) noexcept;
				//template <class T, class U>
				//constexpr typename basic_linear_algebra<T, U>::point_2d operator*(const typename basic_linear_algebra<T, U>::point_2d& lhs, const typename basic_linear_algebra<T, U>::point_2d& rhs) noexcept;
				//template <class T, class U>
				//constexpr typename basic_linear_algebra<T, U>::point_2d operator/(const typename basic_linear_algebra<T, U>::point_2d& lhs, float rhs) noexcept;
				//template <class T, class U>
				//constexpr typename basic_linear_algebra<T, U>::point_2d operator/(float lhs, const typename basic_linear_algebra<T, U>::point_2d& rhs) noexcept;
				//template <class T, class U>
				//constexpr typename basic_linear_algebra<T, U>::point_2d operator/(const typename basic_linear_algebra<T, U>::point_2d& lhs, const typename basic_linear_algebra<T, U>::point_2d& rhs) noexcept;

				////using point_2d = typename basic_linear_algebra<_Point_2d_float_impl, _Matrix_2d_float_impl>::point_2d;
				//template <class T, class U>
				//constexpr typename basic_linear_algebra<T, U>::matrix_2d operator*(const typename basic_linear_algebra<T, U>::matrix_2d& lhs, const typename basic_linear_algebra<T, U>::matrix_2d& rhs) noexcept;
				//template <class T, class U>
				//constexpr typename basic_linear_algebra<T, U>::point_2d operator*(const typename basic_linear_algebra<T, U>::point_2d& lhs, const typename basic_linear_algebra<T, U>::matrix_2d& rhs) noexcept;
				//template <class T, class U>
				//constexpr bool operator==(const typename basic_linear_algebra<T, U>::matrix_2d& lhs, const typename basic_linear_algebra<T, U>::matrix_2d& rhs) noexcept;
				//template <class T, class U>
				//constexpr bool operator!=(const typename basic_linear_algebra<T, U>::matrix_2d& lhs, const typename basic_linear_algebra<T, U>::matrix_2d& rhs) noexcept;
				//using linear_algebra = basic_linear_algebra<_Point_2d_float_impl, _Matrix_2d_float_impl>;
				//using point_2d = typename linear_algebra::point_2d;
				//using matrix_2d = typename linear_algebra::matrix_2d;
				//using figure_items = basic_figure_items<linear_algebra>;
				//template <class T>
				//class interpreted_path;
				//template <class GraphicsMath, class Allocator>
				//class path_builder;

				template <class GraphicsMath, class Allocator>
				bool operator==(const path_builder<GraphicsMath, Allocator>& lhs,
					const path_builder<GraphicsMath, Allocator>& rhs) noexcept;
				template <class GraphicsMath, class Allocator>
				bool operator!=(const path_builder<GraphicsMath, Allocator>& lhs,
					const path_builder<GraphicsMath, Allocator>& rhs) noexcept;
				template <class GraphicsMath, class Allocator>
				void swap(path_builder<GraphicsMath, Allocator>& lhs, path_builder<GraphicsMath, Allocator>& rhs)
					noexcept(noexcept(lhs.swap(rhs))) {		// Compiler error prevents forwrad declaration
					lhs.swap(rhs);
				}

				//class gradient_stop;
				constexpr bool operator==(const gradient_stop& lhs, const gradient_stop& rhs)
					noexcept;
				constexpr bool operator!=(const gradient_stop& lhs, const gradient_stop& rhs)
					noexcept;

				//template <class GraphicsMath, class T>
				//class brush;
				//template <class GraphicsMath>
				//class render_props;
				//template <class GraphicsMath>
				//class brush_props;
				//template <class T>
				//class clip_props;
				//class stroke_props;
				//template <class GraphicsMath>
				//class mask_props;
				//template <class T>
				//class handler;
				//template <class GraphicsMath, class T>
				//class surface;
				//template <class GraphicsMath, class T>
				//class image_surface;
				//template <class GraphicsMath, class T>
				//class display_surface;
				//template <class GraphicsMath, class T>
				//class mapped_surface;

				int format_stride_for_width(format fmt, int width) noexcept;

				template <class GraphicsMath, class T>
				display_surface<GraphicsMath, T> make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, scaling scl = scaling::letterbox);

				template <class GraphicsMath, class T>
				display_surface<GraphicsMath, T> make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, error_code& ec, scaling scl = scaling::letterbox) noexcept;

				template <class GraphicsMath, class T, class U>
				handler<T> make_handler(display_surface<GraphicsMath, U>&, int preferredDisplayWidth, int preferredDisplayHeight, refresh_rate rr = refresh_rate::as_fast_as_possible, float fps = 30.0f);

				template <class GraphicsMath, class T, class U>
				handler<T> make_handler(display_surface<GraphicsMath, U>&, int preferredDisplayWidth, int preferredDisplayHeight, error_code& ec, refresh_rate rr = refresh_rate::as_fast_as_possible, float fps = 30.0f) noexcept;

				template <class GraphicsMath, class T>
				image_surface<GraphicsMath, T> make_image_surface(format format, int width, int height);

				template <class GraphicsMath, class T>
				image_surface<GraphicsMath, T> make_image_surface(format format, int width, int height, error_code& ec) noexcept;

				template <class GraphicsMath, class T>
				image_surface<GraphicsMath, T> copy_image_surface(image_surface<GraphicsMath, T>& sfc) noexcept;

				template <class GraphicsMath>
				float angle_for_point(const basic_point_2d<GraphicsMath>& ctr, const basic_point_2d<GraphicsMath>& pt) noexcept;

				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> point_for_angle(float ang, float rad = 1.0f) noexcept;

				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> point_for_angle(float ang, const basic_point_2d<GraphicsMath>& rad) noexcept;

				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> arc_start(const basic_point_2d<GraphicsMath>& ctr, float sang, const basic_point_2d<GraphicsMath>& rad) noexcept;

				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> arc_start(const basic_point_2d<GraphicsMath>& ctr, float sang, const basic_point_2d<GraphicsMath>& rad, const basic_matrix_2d<GraphicsMath>& m) noexcept;

				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> arc_center(const basic_point_2d<GraphicsMath>& cpt, float sang, const basic_point_2d<GraphicsMath>& rad) noexcept;

				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> arc_center(const basic_point_2d<GraphicsMath>& cpt, float sang, const basic_point_2d<GraphicsMath>& rad, const basic_matrix_2d<GraphicsMath>& m) noexcept;

				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> arc_end(const basic_point_2d<GraphicsMath>& cpt, float eang, const basic_point_2d<GraphicsMath>& rad) noexcept;

				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> arc_end(const basic_point_2d<GraphicsMath>& cpt, float eang, const basic_point_2d<GraphicsMath>& rad, const basic_matrix_2d<GraphicsMath>& m) noexcept;
			}
		}
	}
}

#include "xio2d_impl.h"
#endif
