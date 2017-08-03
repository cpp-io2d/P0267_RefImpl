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

#ifdef _Filesystem_support_test
#include <filesystem>
#endif

#include "xio2d.h"

#if defined BUILD_IO2D_API_DLL 
#define _IO2D_API __declspec(dllexport)
#elif defined USE_IO2D_API_DLL
#define _IO2D_API __declspec(dllimport)
#else
#define _IO2D_API
#endif

#include "xenumclasses.h"
#include "xcolor.h"
#include "xlinear_algebra.h"
#include "xgeometry.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		using dashes = tuple<vector<float>, float>;

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

		class path_group;

		template <class Allocator = allocator<path_data::path_item>>
		class path_builder;

		template <class Allocator>
		bool operator==(const path_builder<Allocator>& lhs,
			const path_builder<Allocator>& rhs) noexcept;
		template <class Allocator>
		bool operator!=(const path_builder<Allocator>& lhs,
			const path_builder<Allocator>& rhs) noexcept;

		template <class Allocator>
		void swap(path_builder<Allocator>& lhs, path_builder<Allocator>& rhs)
			noexcept(noexcept(lhs.swap(rhs)));

		class gradient_stop;
		constexpr bool operator==(const gradient_stop& lhs, const gradient_stop& rhs)
			noexcept;
		constexpr bool operator!=(const gradient_stop& lhs, const gradient_stop& rhs)
			noexcept;
		class brush;

		class render_props;
		class brush_props;
		class clip_props;
		class stroke_props;
		class mask_props;

		class surface;
		class image_surface;
		class display_surface;
		class mapped_surface;

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

		int format_stride_for_width(format format, int width) noexcept;
		display_surface make_display_surface(int preferredWidth,
			int preferredHeight, format preferredFormat,
			scaling scl = scaling::letterbox);
		display_surface make_display_surface(int preferredWidth,
			int preferredHeight, format preferredFormat, error_code& ec,
			scaling scl = scaling::letterbox) noexcept;
		display_surface make_display_surface(int preferredWidth,
			int preferredHeight, format preferredFormat, int preferredDisplayWidth,
			int preferredDisplayHeight, scaling scl = scaling::letterbox);
		display_surface make_display_surface(int preferredWidth,
			int preferredHeight, format preferredFormat, int preferredDisplayWidth,
			int preferredDisplayHeight, error_code& ec,
			scaling scl = scaling::letterbox) noexcept;
		image_surface make_image_surface(format format, int width, int height);
		image_surface make_image_surface(format format, int width, int height,
			error_code& ec) noexcept;
		image_surface copy_image_surface(image_surface& sfc) noexcept;
		float angle_for_point(point_2d ctr, point_2d pt,
			point_2d scl = point_2d{ 1.0f, 1.0f }) noexcept;
		point_2d point_for_angle(float ang, float rad = 1.0f) noexcept;
		point_2d point_for_angle(float ang, point_2d rad) noexcept;
		point_2d arc_start(point_2d ctr, float sang, point_2d rad,
			const matrix_2d& m = matrix_2d{}) noexcept;
		point_2d arc_center(point_2d cpt, float sang, point_2d rad,
			const matrix_2d& m = matrix_2d{}) noexcept;
		point_2d arc_end(point_2d cpt, float eang, point_2d rad,
			const matrix_2d& m = matrix_2d{}) noexcept;
	}
}

#include "xio2d_impl.h"
#endif
