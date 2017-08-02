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

namespace std::experimental::io2d {
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

		enum class antialias {
			none,
			fast,
			good,
			best
		};

		enum class fill_rule {
			winding,
			even_odd
		};

		enum class line_cap {
			none,
			round,
			square
		};

		enum class line_join {
			miter,
			round,
			bevel,
			miter_or_bevel
		};

		enum class compositing_op {
			over,
			clear,
			source,
			in,
			out,
			atop,
			dest,
			dest_over,
			dest_in,
			dest_out,
			dest_atop,
			xor_op,
			add,
			saturate,
			multiply,
			screen,
			overlay,
			darken,
			lighten,
			color_dodge,
			color_burn,
			hard_light,
			soft_light,
			difference,
			exclusion,
			hsl_hue,
			hsl_saturation,
			hsl_color,
			hsl_luminosity
		};

		enum class format {
			invalid,
			argb32,
			xrgb32,
			a8,
			rgb16_565,
			rgb30
		};

		enum class wrap_mode {
			none,
			repeat,
			reflect,
			pad
		};

		enum class filter {
			fast,
			good,
			best,
			nearest,
			bilinear
		};

		enum class brush_type {
			solid_color,
			surface,
			linear,
			radial
		};

		enum class scaling {
			letterbox, // Same as uniform except that the display_surface is cleared using the letterbox brush first
			uniform, // Maintain aspect ratio and center as needed, ignoring side areas that are not drawn to
			fill_uniform, // Maintain aspect ratio but fill entire display (some content may not be shown)
			fill_exact, // Ignore aspect ratio and use (possibly non-uniform) scale to fill exactly
			none // Do not scale.
		};

		enum class refresh_rate {
			as_needed,
			as_fast_as_possible,
			fixed
		};

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

		class vector_2d {
			float _X = 0.0f;
			float _Y = 0.0f;
		public:
			// \ref{\iotwod.\pointtwod.cons}, constructors:
			constexpr vector_2d() noexcept;
			constexpr vector_2d(float x, float y) noexcept;

			constexpr void x(float value) noexcept;
			constexpr void y(float value) noexcept;

			constexpr float x() const noexcept;
			constexpr float y() const noexcept;

			// \ref{\iotwod.\pointtwod.observers}, observers:
			constexpr float dot(const vector_2d& other) const noexcept;
			float magnitude() const noexcept;
			constexpr float magnitude_squared() const noexcept;
			float angular_direction() const noexcept;
			vector_2d to_unit() const noexcept;
			constexpr vector_2d zero() const noexcept;

			// \ref{\iotwod.\pointtwod.member.ops}, member operators:
			constexpr vector_2d& operator+=(const vector_2d& rhs) noexcept;
			constexpr vector_2d& operator-=(const vector_2d& rhs) noexcept;
			constexpr vector_2d& operator*=(float rhs) noexcept;
			constexpr vector_2d& operator*=(const vector_2d& rhs) noexcept;
			constexpr vector_2d& operator/=(float rhs) noexcept;
			constexpr vector_2d& operator/=(const vector_2d& rhs) noexcept;
		};
		constexpr bool operator==(const vector_2d& lhs, const vector_2d& rhs)
			noexcept;
		constexpr bool operator!=(const vector_2d& lhs, const vector_2d& rhs)
			noexcept;
		constexpr vector_2d operator+(const vector_2d& lhs) noexcept;
		constexpr vector_2d operator+(const vector_2d& lhs, const vector_2d& rhs)
			noexcept;
		constexpr vector_2d operator-(const vector_2d& lhs) noexcept;
		constexpr vector_2d operator-(const vector_2d& lhs, const vector_2d& rhs)
			noexcept;
		constexpr vector_2d operator*(const vector_2d& lhs, float rhs) noexcept;
		constexpr vector_2d operator*(float lhs, const vector_2d& rhs) noexcept;

		class matrix_2d {
			float _M00 = 1.0F;
			float _M01 = 0.0F;
			float _M10 = 0.0F;
			float _M11 = 1.0F;
			float _M20 = 0.0F;
			float _M21 = 0.0F;

		public:
			constexpr matrix_2d() noexcept
				: matrix_2d(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f) {}
			constexpr matrix_2d(float m00, float m01, float m10, float m11, float m20, float m21) noexcept {
				_M00 = m00;
				_M01 = m01;
				_M10 = m10;
				_M11 = m11;
				_M20 = m20;
				_M21 = m21;
			}

			constexpr void m00(float value) noexcept;
			constexpr void m01(float value) noexcept;
			constexpr void m10(float value) noexcept;
			constexpr void m11(float value) noexcept;
			constexpr void m20(float value) noexcept;
			constexpr void m21(float value) noexcept;

			constexpr float m00() const noexcept;
			constexpr float m01() const noexcept;
			constexpr float m10() const noexcept;
			constexpr float m11() const noexcept;
			constexpr float m20() const noexcept;
			constexpr float m21() const noexcept;

			// \ref{\iotwod.\matrixtwod.staticfactories}, static factory functions:
			constexpr static matrix_2d init_translate(const vector_2d& value) noexcept {
				return{ 1.0F, 0.0F, 0.0F, 1.0F, value.x(), value.y() };
			}
			constexpr static matrix_2d init_scale(const vector_2d& value) noexcept {
				return{ value.x(), 0.0F, 0.0F, value.y(), 0.0F, 0.0F };
			}
			static matrix_2d init_rotate(float radians) noexcept {
				auto sine = sin(radians);
				auto cosine = cos(radians);
				sine = _Round_floating_point_to_zero(sine);
				cosine = _Round_floating_point_to_zero(cosine);
				return{ cosine, -sine, sine, cosine, 0.0F, 0.0F };
			}
			static matrix_2d init_reflect(float radians) noexcept {
				auto sine = sin(radians * 2.0F);
				auto cosine = cos(radians * 2.0F);
				sine = _Round_floating_point_to_zero(sine);
				cosine = _Round_floating_point_to_zero(cosine);
				return{ cosine, sine, sine, -cosine, 0.0F, 0.0F };
			}
			constexpr static matrix_2d init_shear_x(float factor) noexcept {
				return{ 1.0F, 0.0F, factor, 1.0F, 0.0F, 0.0F };
			}
			constexpr static matrix_2d init_shear_y(float factor) noexcept {
				return{ 1.0F, factor, 0.0F, 1.0F, 0.0F, 0.0F };
			}

			// \ref{\iotwod.\matrixtwod.modifiers}, modifiers:
			constexpr matrix_2d& translate(vector_2d v) noexcept;
			constexpr matrix_2d& scale(vector_2d v) noexcept;
			matrix_2d& rotate(float radians) noexcept;
			matrix_2d& rotate(float radians, vector_2d origin) noexcept;
			matrix_2d& reflect(float radians) noexcept;
			constexpr matrix_2d& shear_x(float factor) noexcept;
			constexpr matrix_2d& shear_y(float factor) noexcept;

			// \ref{\iotwod.\matrixtwod.observers}, observers:
			constexpr bool is_finite() const noexcept;
			constexpr bool is_invertible() const noexcept;
			constexpr float determinant() const noexcept;
			constexpr matrix_2d inverse() const noexcept;
			constexpr vector_2d transform_pt(vector_2d pt) const noexcept;

			// \ref{\iotwod.\matrixtwod.member.ops}, matrix_2d member operators:
			constexpr matrix_2d& operator*=(const matrix_2d& rhs) noexcept;
		};

		// \ref{\iotwod.\matrixtwod.ops}, matrix_2d non-member operators:
		constexpr matrix_2d operator*(const matrix_2d& lhs, const matrix_2d& rhs)
			noexcept;
		constexpr bool operator==(const matrix_2d& lhs, const matrix_2d& rhs)
			noexcept;
		constexpr bool operator!=(const matrix_2d& lhs, const matrix_2d& rhs)
			noexcept;
		constexpr vector_2d operator*(vector_2d v, const matrix_2d& m)
			noexcept;
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
		float angle_for_point(vector_2d ctr, vector_2d pt,
			vector_2d scl = vector_2d{ 1.0f, 1.0f }) noexcept;
		vector_2d point_for_angle(float ang, float rad = 1.0f) noexcept;
		vector_2d point_for_angle(float ang, vector_2d rad) noexcept;
		vector_2d arc_start(vector_2d ctr, float sang, vector_2d rad,
			const matrix_2d& m = matrix_2d{}) noexcept;
		vector_2d arc_center(vector_2d cpt, float sang, vector_2d rad,
			const matrix_2d& m = matrix_2d{}) noexcept;
		vector_2d arc_end(vector_2d cpt, float eang, vector_2d rad,
			const matrix_2d& m = matrix_2d{}) noexcept;
	}
}

#include "xio2d_impl.h"
#endif
