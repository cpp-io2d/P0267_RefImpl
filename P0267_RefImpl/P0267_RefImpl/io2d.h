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

				using dashes = tuple<vector<float>, float>;

				enum class wrap_mode;
				enum class filter;
				enum class brush_type;
				enum class antialias;
				enum class fill_rule;
				enum class line_cap;
				enum class line_join;
				enum class compositing_op;
				enum class format;
				enum class scaling;
				enum class refresh_rate;
				enum class image_file_format;

				class bounding_box;
				constexpr bool operator==(const bounding_box& lhs, const bounding_box& rhs)
					noexcept;
				constexpr bool operator!=(const bounding_box& lhs, const bounding_box& rhs)
					noexcept;

				class circle;
				constexpr bool operator==(const circle& lhs, const circle& rhs) noexcept;
				constexpr bool operator!=(const circle& lhs, const circle& rhs) noexcept;

				class rgba_color;
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

				class point_2d;
				constexpr bool operator==(const point_2d& lhs, const point_2d& rhs)
					noexcept;
				constexpr bool operator!=(const point_2d& lhs, const point_2d& rhs)
					noexcept;
				constexpr point_2d operator+(const point_2d& lhs) noexcept;
				constexpr point_2d operator+(const point_2d& lhs, const point_2d& rhs)
					noexcept;
				constexpr point_2d operator-(const point_2d& lhs) noexcept;
				constexpr point_2d operator-(const point_2d& lhs, const point_2d& rhs)
					noexcept;
				constexpr point_2d operator*(const point_2d& lhs, float rhs) noexcept;
				constexpr point_2d operator*(float lhs, const point_2d& rhs) noexcept;

				class matrix_2d;
				constexpr matrix_2d operator*(const matrix_2d& lhs, const matrix_2d& rhs)
					noexcept;
				constexpr bool operator==(const matrix_2d& lhs, const matrix_2d& rhs)
					noexcept;
				constexpr bool operator!=(const matrix_2d& lhs, const matrix_2d& rhs)
					noexcept;

				namespace figure_items {
					class abs_new_figure;
					constexpr bool operator==(const abs_new_figure&, const abs_new_figure&)
						noexcept;
					constexpr bool operator!=(const abs_new_figure&, const abs_new_figure&)
						noexcept;

					class rel_new_figure;
					constexpr bool operator==(const rel_new_figure&, const rel_new_figure&)
						noexcept;
					constexpr bool operator!=(const rel_new_figure&, const rel_new_figure&)
						noexcept;

					class close_figure;
					constexpr bool operator==(const close_figure&, const close_figure&) noexcept;
					constexpr bool operator!=(const close_figure&, const close_figure&) noexcept;

					class abs_matrix;
					constexpr bool operator==(const abs_matrix&, const abs_matrix&) noexcept;
					constexpr bool operator!=(const abs_matrix&, const abs_matrix&) noexcept;

					class rel_matrix;
					constexpr bool operator==(const rel_matrix&, const rel_matrix&) noexcept;
					constexpr bool operator!=(const rel_matrix&, const rel_matrix&) noexcept;

					class revert_matrix;
					constexpr bool operator==(const revert_matrix&, const revert_matrix&)
						noexcept;
					constexpr bool operator!=(const revert_matrix&, const revert_matrix&)
						noexcept;

					class abs_cubic_curve;
					constexpr bool operator==(const abs_cubic_curve&, const abs_cubic_curve&)
						noexcept;
					constexpr bool operator!=(const abs_cubic_curve&, const abs_cubic_curve&)
						noexcept;

					class abs_line;
					constexpr bool operator==(const abs_line&, const abs_line&) noexcept;
					constexpr bool operator!=(const abs_line&, const abs_line&) noexcept;

					class abs_quadratic_curve;
					constexpr bool operator==(const abs_quadratic_curve&,
						const abs_quadratic_curve&) noexcept;
					constexpr bool operator!=(const abs_quadratic_curve&,
						const abs_quadratic_curve&) noexcept;

					class arc;
					constexpr bool operator==(const arc&, const arc&) noexcept;
					constexpr bool operator!=(const arc&, const arc&) noexcept;

					class rel_cubic_curve;
					constexpr bool operator==(const rel_cubic_curve&, const rel_cubic_curve&)
						noexcept;
					constexpr bool operator!=(const rel_cubic_curve&, const rel_cubic_curve&)
						noexcept;

					class rel_line;
					constexpr bool operator==(const rel_line&, const rel_line&) noexcept;
					constexpr bool operator!=(const rel_line&, const rel_line&) noexcept;

					class rel_quadratic_curve;
					constexpr bool operator==(const rel_quadratic_curve&,
						const rel_quadratic_curve&) noexcept;
					constexpr bool operator!=(const rel_quadratic_curve&,
						const rel_quadratic_curve&) noexcept;

					using figure_item = variant<abs_cubic_curve, abs_line, abs_matrix,
						abs_new_figure, abs_quadratic_curve, arc, close_figure,
						rel_cubic_curve, rel_line, rel_matrix, rel_new_figure, rel_quadratic_curve,
						revert_matrix>;
				}

				template <class T>
				class interpreted_path;
				template <class Allocator = allocator<figure_items::figure_items_types>>

				class path_builder;
				template <class Allocator>
				bool operator==(const path_builder<Allocator>& lhs,
					const path_builder<Allocator>& rhs) noexcept;
				template <class Allocator>
				bool operator!=(const path_builder<Allocator>& lhs,
					const path_builder<Allocator>& rhs) noexcept;
				template <class Allocator>
				void swap(path_builder<Allocator>& lhs, path_builder<Allocator>& rhs)
					noexcept(noexcept(lhs.swap(rhs))) {		// Compiler error prevents forwrad declaration
					lhs.swap(rhs);
				}

				class gradient_stop;
				constexpr bool operator==(const gradient_stop& lhs, const gradient_stop& rhs)
					noexcept;
				constexpr bool operator!=(const gradient_stop& lhs, const gradient_stop& rhs)
					noexcept;

				template <class T>
				class brush;
				class render_props;
				class brush_props;
				template <class T>
				class clip_props;
				class stroke_props;
				class mask_props;
				template <class T>
				class handler;
				template <class T>
				class surface;
				template <class T>
				class image_surface;
				template <class T>
				class display_surface;
				template <class T>
				class mapped_surface;

				int format_stride_for_width(format format, int width) noexcept;

				template <class T>
				display_surface<T> make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, scaling scl = scaling::letterbox);

				template <class T>
				display_surface<T> make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, error_code& ec, scaling scl = scaling::letterbox) noexcept;

				template <class T, class U>
				handler<T> make_handler(display_surface<U>&, int preferredDisplayWidth, int preferredDisplayHeight, refresh_rate rr = refresh_rate::as_fast_as_possible, float fps = 30.0f);

				template <class T, class U>
				handler<T> make_handler(display_surface<U>&, int preferredDisplayWidth, int preferredDisplayHeight, error_code& ec, refresh_rate rr = refresh_rate::as_fast_as_possible, float fps = 30.0f) noexcept;

				template <class T>
				image_surface<T> make_image_surface(format format, int width, int height);

				template <class T>
				image_surface<T> make_image_surface(format format, int width, int height, error_code& ec) noexcept;

				template <class T>
				image_surface<T> copy_image_surface(image_surface<T>& sfc) noexcept;

				float angle_for_point(point_2d ctr, point_2d pt) noexcept;

				point_2d point_for_angle(float ang, float rad = 1.0f) noexcept;

				point_2d point_for_angle(float ang, point_2d rad) noexcept;

				point_2d arc_start(point_2d ctr, float sang, point_2d rad, const matrix_2d& m = matrix_2d{}) noexcept;

				point_2d arc_center(point_2d cpt, float sang, point_2d rad, const matrix_2d& m = matrix_2d{}) noexcept;

				point_2d arc_end(point_2d cpt, float eang, point_2d rad, const matrix_2d& m = matrix_2d{}) noexcept;

				// surplus to paper
				float angle_for_point(point_2d ctr, point_2d pt, point_2d scl = point_2d{ 1.0f, 1.0f }) noexcept;
			}
		}
	}
}

#include "xio2d_impl.h"
#endif
