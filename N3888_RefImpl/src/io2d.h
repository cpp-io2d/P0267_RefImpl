#pragma once

#ifndef _IO2D_
#define _IO2D_

#define __cpp_lib_experimental_io2d 201602

#include "xio2d.h"

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

#ifdef _WIN32_WINNT
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif defined(USE_XCB)
#include <xcb/xcb.h>
#elif defined(USE_XLIB)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#endif

#if !_Noexcept_conditional_support_test
#define noexcept
#endif

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				enum class io2d_error {
					success,
					invalid_restore,
					invalid_matrix,
					invalid_status,
					null_pointer,
					invalid_string,
					invalid_path_data,
					read_error,
					write_error,
					surface_finished,
					invalid_dash,
					invalid_index,
					clip_not_representable,
					invalid_stride,
					user_font_immutable,
					user_font_error,
					invalid_clusters,
					device_error,
					invalid_mesh_construction
				};
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}

	template<>
	struct is_error_condition_enum<::std::experimental::io2d::io2d_error>
		: public ::std::true_type { };

	//template<>
	//struct is_error_code_enum<::cairo_status_t>
	//	: public ::std::true_type{ };

	::std::error_condition make_error_condition(experimental::io2d::io2d_error e) noexcept;

	//	::std::error_code make_error_code(cairo_status_t e) noexcept;

	::std::error_code make_error_code(experimental::io2d::io2d_error e) noexcept;

	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				enum class antialias {
					default_antialias,
					none,
					gray,
					subpixel,
					fast,
					good,
					best
				};

				enum class content {
					color,
					alpha,
					color_alpha
				};

				enum class fill_rule {
					winding,
					even_odd
				};

				enum class line_cap {
					butt,
					round,
					square
				};

				enum class line_join {
					miter,
					round,
					bevel,
					miter_or_bevel
				};

				enum class compositing_operator {
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
					a1,
					rgb16_565,
					rgb30
				};

				enum class tiling {
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

				enum class font_slant {
					normal,
					italic,
					oblique
				};

				enum class font_weight {
					normal,
					bold
				};

				enum class subpixel_order {
					default_subpixel_order,
					horizontal_rgb,
					horizontal_bgr,
					vertical_rgb,
					vertical_bgr
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

				struct nullvalue_t {
					constexpr explicit nullvalue_t(int) noexcept {
					}
				};

				constexpr nullvalue_t nullvalue{ 0 };

#if _Variable_templates_conditional_support_test
				template <class T>
				constexpr T pi = T(3.14159265358979323846264338327950288L);

				template <class T>
				constexpr T two_pi = T(6.28318530717958647692528676655900576L);

				template <class T>
				constexpr T half_pi = T(1.57079632679489661923132169163975144L);

				template <class T>
				constexpr T three_pi_over_two = T(4.71238898038468985769396507491925432L);
#else
				template <class T>
#if _Constexpr_conditional_support_test
				constexpr
#endif
					T pi() noexcept {
					return static_cast<T>(3.14159265358979323846264338327950288L);
				}

				template <class T>
#if _Constexpr_conditional_support_test
				constexpr
#endif
					T two_pi() noexcept {
					return static_cast<T>(6.28318530717958647692528676655900576L);
				}

				template <class T>
#if _Constexpr_conditional_support_test
				constexpr
#endif
					T half_pi() noexcept {
					return static_cast<T>(1.57079632679489661923132169163975144L);
				}

				template <class T>
#if _Constexpr_conditional_support_test
				constexpr
#endif
					T three_pi_over_two() noexcept {
					return static_cast<T>(4.71238898038468985769396507491925432L);
				}
#endif

				// I don't know why Clang/C2 is complaining about weak vtables here since the at least one virtual function is always anchored but for now silence the warnings. I've never seen this using Clang on OpenSUSE.
#ifdef _WIN32
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
#endif

				class io2d_error_category : public ::std::error_category {
				public:
					// Observers
					virtual const char* name() const noexcept override;
					virtual ::std::string message(int errVal) const override;
					virtual bool equivalent(int code, const ::std::error_condition& condition) const noexcept override;
					virtual bool equivalent(const ::std::error_code& ec, int condition) const noexcept override;
				};

				// I don't know why Clang/C2 is complaining about weak vtables here since the at least one virtual function is always anchored but for now silence the warnings. I've never seen this using Clang on OpenSUSE.
#ifdef _WIN32
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif

				const ::std::error_category& io2d_category() noexcept;

				class vector_2d {
					double _X;// = 0.0;
					double _Y;// = 0.0;
				public:
					vector_2d() noexcept = default;
					//vector_2d() noexcept = default;
					//vector_2d(const vector_2d& other) noexcept = default;
					//vector_2d& operator=(const vector_2d& other) noexcept = default;
					//vector_2d(vector_2d&& other) noexcept;
					//vector_2d& operator=(vector_2d&& other) noexcept;
					vector_2d(double x, double y) noexcept;

					void x(double value) noexcept;
					void y(double value) noexcept;
					void swap(vector_2d& x) noexcept;

					double x() const noexcept;
					double y() const noexcept;

					double magnitude() const noexcept;
					double magnitude_squared() const noexcept;
					double dot(const vector_2d& other) const noexcept;
					double angular_direction(const vector_2d& to) const noexcept;

					vector_2d to_unit() const noexcept;

					vector_2d& operator+=(const vector_2d& rhs) noexcept;
					vector_2d& operator-=(const vector_2d& rhs) noexcept;
					vector_2d& operator*=(double rhs) noexcept;
				};

				bool operator==(const vector_2d& lhs, const vector_2d& rhs) noexcept;
				bool operator!=(const vector_2d& lhs, const vector_2d& rhs) noexcept;
				vector_2d operator+(const vector_2d& lhs) noexcept;
				vector_2d operator+(const vector_2d& lhs, const vector_2d& rhs) noexcept;
				vector_2d operator-(const vector_2d& lhs) noexcept;
				vector_2d operator-(const vector_2d& lhs, const vector_2d& rhs) noexcept;
				vector_2d operator*(const vector_2d& lhs, double rhs) noexcept;
				vector_2d operator*(double lhs, const vector_2d& rhs) noexcept;
				//void swap(vector_2d& lhs, vector_2d& rhs);

				class rectangle {
					double _X = 0.0;
					double _Y = 0.0;
					double _Width = 0.0;
					double _Height = 0.0;
				public:
					rectangle() noexcept = default;
					rectangle(const rectangle& other) noexcept = default;
					rectangle& operator=(const rectangle& other) noexcept = default;
					rectangle(rectangle&& other) noexcept;
					rectangle& operator=(rectangle&& other) noexcept;
					rectangle(double x, double y, double width, double height) noexcept;
					rectangle(const vector_2d& tl, const vector_2d& br) noexcept;

					void x(double value) noexcept;
					void y(double value) noexcept;
					void width(double value) noexcept;
					void height(double value) noexcept;
					void top_left(const vector_2d& value) noexcept;
					void bottom_right(const vector_2d& value) noexcept;
					void top_left_bottom_right(const vector_2d& tl, const vector_2d& br) noexcept;

					double x() const noexcept;
					double y() const noexcept;
					double width() const noexcept;
					double height() const noexcept;
					double left() const noexcept;
					double right() const noexcept;
					double top() const noexcept;
					double bottom() const noexcept;
					vector_2d top_left() const noexcept;
					vector_2d bottom_right() const noexcept;
					tuple<vector_2d, vector_2d> top_left_bottom_right() const noexcept;
				};

				class circle {
				public:
					circle(const vector_2d& ctr, double rad) noexcept;

					void center(const vector_2d& ctr) noexcept;
					void radius(double rad) noexcept;

					vector_2d center() const noexcept;
					double radius() const noexcept;
				};

				class rgba_color {
					double _R = 0.0;
					double _G = 0.0;
					double _B = 0.0;
					double _A = 1.0;
				public:
					rgba_color() noexcept = default;
					rgba_color(const rgba_color& other) noexcept = default;
					rgba_color& operator=(const rgba_color& other) noexcept = default;
					rgba_color(rgba_color&& other) noexcept;
					rgba_color& operator=(rgba_color&& other) noexcept;
					rgba_color(double r, double g, double b, double a = 1.0);
					rgba_color(double r, double g, double b, ::std::error_code& ec) noexcept;
					rgba_color(double r, double g, double b, double a, ::std::error_code& ec) noexcept;
					rgba_color(long long r, long long g, long long b) = delete;
					rgba_color(long long r, long long g, long long b, long long a) = delete;

					void r(double val);
					void r(double val, ::std::error_code& ec) noexcept;

					void g(double val);
					void g(double val, ::std::error_code& ec) noexcept;

					void b(double val);
					void b(double val, ::std::error_code& ec) noexcept;

					void a(double val);
					void a(double val, ::std::error_code& ec) noexcept;

					double r() const noexcept;
					double g() const noexcept;
					double b() const noexcept;
					double a() const noexcept;

					static const rgba_color& alice_blue() noexcept;
					static const rgba_color& antique_white() noexcept;
					static const rgba_color& aqua() noexcept;
					static const rgba_color& aquamarine() noexcept;
					static const rgba_color& azure() noexcept;
					static const rgba_color& beige() noexcept;
					static const rgba_color& bisque() noexcept;
					static const rgba_color& black() noexcept;
					static const rgba_color& blanched_almond() noexcept;
					static const rgba_color& blue() noexcept;
					static const rgba_color& blue_violet() noexcept;
					static const rgba_color& brown() noexcept;
					static const rgba_color& burly_wood() noexcept;
					static const rgba_color& cadet_blue() noexcept;
					static const rgba_color& chartreuse() noexcept;
					static const rgba_color& chocolate() noexcept;
					static const rgba_color& coral() noexcept;
					static const rgba_color& cornflower_blue() noexcept;
					static const rgba_color& cornsilk() noexcept;
					static const rgba_color& crimson() noexcept;
					static const rgba_color& cyan() noexcept;
					static const rgba_color& dark_blue() noexcept;
					static const rgba_color& dark_cyan() noexcept;
					static const rgba_color& dark_goldenrod() noexcept;
					static const rgba_color& dark_gray() noexcept;
					static const rgba_color& dark_green() noexcept;
					static const rgba_color& dark_grey() noexcept;
					static const rgba_color& dark_khaki() noexcept;
					static const rgba_color& dark_magenta() noexcept;
					static const rgba_color& dark_olive_green() noexcept;
					static const rgba_color& dark_orange() noexcept;
					static const rgba_color& dark_orchid() noexcept;
					static const rgba_color& dark_red() noexcept;
					static const rgba_color& dark_salmon() noexcept;
					static const rgba_color& dark_sea_green() noexcept;
					static const rgba_color& dark_slate_blue() noexcept;
					static const rgba_color& dark_slate_gray() noexcept;
					static const rgba_color& dark_slate_grey() noexcept;
					static const rgba_color& dark_turquoise() noexcept;
					static const rgba_color& dark_violet() noexcept;
					static const rgba_color& deep_pink() noexcept;
					static const rgba_color& deep_sky_blue() noexcept;
					static const rgba_color& dim_gray() noexcept;
					static const rgba_color& dim_grey() noexcept;
					static const rgba_color& dodger_blue() noexcept;
					static const rgba_color& firebrick() noexcept;
					static const rgba_color& floral_white() noexcept;
					static const rgba_color& forest_green() noexcept;
					static const rgba_color& fuchsia() noexcept;
					static const rgba_color& gainsboro() noexcept;
					static const rgba_color& ghost_white() noexcept;
					static const rgba_color& gold() noexcept;
					static const rgba_color& goldenrod() noexcept;
					static const rgba_color& gray() noexcept;
					static const rgba_color& green() noexcept;
					static const rgba_color& green_yellow() noexcept;
					static const rgba_color& grey() noexcept;
					static const rgba_color& honeydew() noexcept;
					static const rgba_color& hot_pink() noexcept;
					static const rgba_color& indian_red() noexcept;
					static const rgba_color& indigo() noexcept;
					static const rgba_color& ivory() noexcept;
					static const rgba_color& khaki() noexcept;
					static const rgba_color& lavender() noexcept;
					static const rgba_color& lavender_blush() noexcept;
					static const rgba_color& lawn_green() noexcept;
					static const rgba_color& lemon_chiffon() noexcept;
					static const rgba_color& light_blue() noexcept;
					static const rgba_color& light_coral() noexcept;
					static const rgba_color& light_cyan() noexcept;
					static const rgba_color& light_goldenrod_yellow() noexcept;
					static const rgba_color& light_gray() noexcept;
					static const rgba_color& light_green() noexcept;
					static const rgba_color& light_grey() noexcept;
					static const rgba_color& light_pink() noexcept;
					static const rgba_color& light_salmon() noexcept;
					static const rgba_color& light_sea_green() noexcept;
					static const rgba_color& light_sky_blue() noexcept;
					static const rgba_color& light_slate_gray() noexcept;
					static const rgba_color& light_slate_grey() noexcept;
					static const rgba_color& light_steel_blue() noexcept;
					static const rgba_color& light_yellow() noexcept;
					static const rgba_color& lime() noexcept;
					static const rgba_color& lime_green() noexcept;
					static const rgba_color& linen() noexcept;
					static const rgba_color& magenta() noexcept;
					static const rgba_color& maroon() noexcept;
					static const rgba_color& medium_aquamarine() noexcept;
					static const rgba_color& medium_blue() noexcept;
					static const rgba_color& medium_orchid() noexcept;
					static const rgba_color& medium_purple() noexcept;
					static const rgba_color& medium_sea_green() noexcept;
					static const rgba_color& medium_slate_blue() noexcept;
					static const rgba_color& medium_spring_green() noexcept;
					static const rgba_color& medium_turquoise() noexcept;
					static const rgba_color& medium_violet_red() noexcept;
					static const rgba_color& midnight_blue() noexcept;
					static const rgba_color& mint_cream() noexcept;
					static const rgba_color& misty_rose() noexcept;
					static const rgba_color& moccasin() noexcept;
					static const rgba_color& navajo_white() noexcept;
					static const rgba_color& navy() noexcept;
					static const rgba_color& old_lace() noexcept;
					static const rgba_color& olive() noexcept;
					static const rgba_color& olive_drab() noexcept;
					static const rgba_color& orange() noexcept;
					static const rgba_color& orange_red() noexcept;
					static const rgba_color& orchid() noexcept;
					static const rgba_color& pale_goldenrod() noexcept;
					static const rgba_color& pale_green() noexcept;
					static const rgba_color& pale_turquoise() noexcept;
					static const rgba_color& pale_violet_red() noexcept;
					static const rgba_color& papaya_whip() noexcept;
					static const rgba_color& peach_puff() noexcept;
					static const rgba_color& peru() noexcept;
					static const rgba_color& pink() noexcept;
					static const rgba_color& plum() noexcept;
					static const rgba_color& powder_blue() noexcept;
					static const rgba_color& purple() noexcept;
					static const rgba_color& red() noexcept;
					static const rgba_color& rosy_brown() noexcept;
					static const rgba_color& royal_blue() noexcept;
					static const rgba_color& saddle_brown() noexcept;
					static const rgba_color& salmon() noexcept;
					static const rgba_color& sandy_brown() noexcept;
					static const rgba_color& sea_green() noexcept;
					static const rgba_color& sea_shell() noexcept;
					static const rgba_color& sienna() noexcept;
					static const rgba_color& silver() noexcept;
					static const rgba_color& sky_blue() noexcept;
					static const rgba_color& slate_blue() noexcept;
					static const rgba_color& slate_gray() noexcept;
					static const rgba_color& slate_grey() noexcept;
					static const rgba_color& snow() noexcept;
					static const rgba_color& spring_green() noexcept;
					static const rgba_color& steel_blue() noexcept;
					static const rgba_color& tan() noexcept;
					static const rgba_color& teal() noexcept;
					static const rgba_color& thistle() noexcept;
					static const rgba_color& tomato() noexcept;
					static const rgba_color& transparent_black() noexcept; // Note: Not in CSS3.
					static const rgba_color& turquoise() noexcept;
					static const rgba_color& violet() noexcept;
					static const rgba_color& wheat() noexcept;
					static const rgba_color& white() noexcept;
					static const rgba_color& white_smoke() noexcept;
					static const rgba_color& yellow() noexcept;
					static const rgba_color& yellow_green() noexcept;
				};

				bool operator==(const rgba_color& lhs, const rgba_color& rhs);
				bool operator!=(const rgba_color& lhs, const rgba_color& rhs);

#if _Inline_namespace_conditional_support_test && _User_defined_literal_conditional_support_test
				inline namespace literals {
					// Note: The _ prefix is added because certain compilers reject attempts to add a non-user-defined literal
					inline double operator""_ubyte(unsigned long long value) noexcept {
						return ::std::max(0.0, ::std::min(1.0, static_cast<double>(value) / 255.0));
					}

					// Note: The _ prefix is added because certain compilers reject attempts to add a non-user-defined literal
					inline double operator "" _unorm(long double value) noexcept {
						auto result = ::std::max(0.0, ::std::min(1.0, static_cast<double>(value)));
						result = ::std::nearbyint(result * 255.0); // We need to ensure it is one of the discrete values between 0 and 255.
						return result / 255.0;
					}
				}
#endif

				class matrix_2d {
					double _M00 = 1.0;
					double _M01 = 0.0;
					double _M10 = 0.0;
					double _M11 = 1.0;
					double _M20 = 0.0;
					double _M21 = 0.0;
				public:

					matrix_2d() noexcept = default;
					matrix_2d(const matrix_2d& other) noexcept = default;
					matrix_2d& operator=(const matrix_2d& other) noexcept = default;
					matrix_2d(matrix_2d&& other) noexcept = default;
					matrix_2d& operator=(matrix_2d&& other) noexcept = default;
					matrix_2d(double m00, double m01, double m10, double m11, double m20, double m21) noexcept;

					static matrix_2d init_identity() noexcept;
					static matrix_2d init_translate(const vector_2d& value) noexcept;
					static matrix_2d init_scale(const vector_2d& value) noexcept;
					static matrix_2d init_rotate(double radians) noexcept;
					static matrix_2d init_shear_x(double factor) noexcept;
					static matrix_2d init_shear_y(double factor) noexcept;

					// Modifiers
					void m00(double value) noexcept;
					void m01(double value) noexcept;
					void m10(double value) noexcept;
					void m11(double value) noexcept;
					void m20(double value) noexcept;
					void m21(double value) noexcept;
					matrix_2d& translate(const vector_2d& value) noexcept;
					matrix_2d& scale(const vector_2d& value) noexcept;
					matrix_2d& rotate(double radians) noexcept;
					matrix_2d& shear_x(double factor) noexcept;
					matrix_2d& shear_y(double factor) noexcept;
					matrix_2d& invert();
					matrix_2d& invert(::std::error_code& ec) noexcept;
					void swap(matrix_2d& other);

					// Observers
					double m00() const noexcept;
					double m01() const noexcept;
					double m10() const noexcept;
					double m11() const noexcept;
					double m20() const noexcept;
					double m21() const noexcept;
					bool is_invertible() const noexcept;
					double determinant() const;
					double determinant(::std::error_code& ec) const noexcept;
					vector_2d transform_distance(const vector_2d& dist) const noexcept;
					vector_2d transform_point(const vector_2d& pt) const noexcept;

					matrix_2d& operator*=(const matrix_2d& rhs) noexcept;
				};

				matrix_2d operator*(const matrix_2d& lhs, const matrix_2d& rhs) noexcept;
				bool operator==(const matrix_2d& lhs, const matrix_2d& rhs) noexcept;
				bool operator!=(const matrix_2d& lhs, const matrix_2d& rhs) noexcept;


				namespace path_data {
					class new_path {
					};

					class close_path {
						vector_2d _Data = {};
					public:
						explicit close_path(const vector_2d& to) noexcept;

						vector_2d to() const noexcept;
						void to(const vector_2d& value) noexcept;
					};

					class abs_move {
						vector_2d _Data = {};
					public:
						explicit abs_move(const vector_2d& to) noexcept;

						vector_2d to() const noexcept;
						void to(const vector_2d& value) noexcept;
					};

					class abs_line {
						vector_2d _Data = {};
					public:
						explicit abs_line(const vector_2d& to) noexcept;

						vector_2d to() const noexcept;
						void to(const vector_2d& value) noexcept;
					};

					class rel_move {
						vector_2d _Data = {};
					public:
						explicit rel_move(const vector_2d& to) noexcept;

						vector_2d to() const noexcept;
						void to(const vector_2d& value) noexcept;
					};

					class rel_line {
						vector_2d _Data = {};
					public:
						explicit rel_line(const vector_2d& to) noexcept;

						vector_2d to() const noexcept;
						void to(const vector_2d& value) noexcept;
					};

					class abs_cubic_curve {
						vector_2d _Control_pt1 = {};
						vector_2d _Control_pt2 = {};
						vector_2d _End_pt = {};
					public:
						abs_cubic_curve(const vector_2d& controlPoint1, const vector_2d& controlPoint2, const vector_2d& endPoint) noexcept;

						void control_point_1(const vector_2d& value) noexcept;
						void control_point_2(const vector_2d& value) noexcept;
						void end_point(const vector_2d& value) noexcept;

						vector_2d control_point_1() const noexcept;
						vector_2d control_point_2() const noexcept;
						vector_2d end_point() const noexcept;
					};

					class rel_cubic_curve {
						vector_2d _Control_pt1 = {};
						vector_2d _Control_pt2 = {};
						vector_2d _End_pt = {};
					public:
						rel_cubic_curve(const vector_2d& controlPoint1, const vector_2d& controlPoint2, const vector_2d& endPoint) noexcept;

						void control_point_1(const vector_2d& value) noexcept;
						void control_point_2(const vector_2d& value) noexcept;
						void end_point(const vector_2d& value) noexcept;

						vector_2d control_point_1() const noexcept;
						vector_2d control_point_2() const noexcept;
						vector_2d end_point() const noexcept;
					};

					class abs_quadratic_curve {
						vector_2d _Control_pt = {};
						vector_2d _End_pt = {};
					public:
						abs_quadratic_curve(const vector_2d& cp, const vector_2d& ep) noexcept;

						void control_point(const vector_2d& cp) noexcept;
						void end_point(const vector_2d& ep) noexcept;

						vector_2d control_point() const noexcept;
						vector_2d end_point() const noexcept;
					};

					class rel_quadratic_curve {
						vector_2d _Control_pt = {};
						vector_2d _End_pt = {};
					public:
						rel_quadratic_curve(const vector_2d& cp, const vector_2d& ep) noexcept;

						void control_point(const vector_2d& cp) noexcept;
						void end_point(const vector_2d& ep) noexcept;

						vector_2d control_point() const noexcept;
						vector_2d end_point() const noexcept;
					};

					class arc_clockwise {
						vector_2d _Center = {};
						double _Radius = 0.0;
						double _Angle_1 = 0.0;
						double _Angle_2 = 0.0;
					public:
						arc_clockwise(const vector_2d& center, double radius, double angle1, double angle2) noexcept;

						void center(const vector_2d& value) noexcept;
						void radius(double value) noexcept;
						void angle_1(double radians) noexcept;
						void angle_2(double radians) noexcept;

						vector_2d center() const noexcept;
						double radius() const noexcept;
						double angle_1() const noexcept;
						double angle_2() const noexcept;
					};

					class arc_counterclockwise {
						vector_2d _Center;
						double _Radius;
						double _Angle_1;
						double _Angle_2;
					public:
						arc_counterclockwise(const vector_2d& center, double radius, double angle1, double angle2) noexcept;

						void center(const vector_2d& value) noexcept;
						void radius(double value) noexcept;
						void angle_1(double radians) noexcept;
						void angle_2(double radians) noexcept;

						vector_2d center() const noexcept;
						double radius() const noexcept;
						double angle_1() const noexcept;
						double angle_2() const noexcept;
					};

					class change_matrix {
						matrix_2d _Matrix = {};
					public:
						explicit change_matrix(const matrix_2d& m) noexcept;

						void matrix(const matrix_2d& value) noexcept;
						matrix_2d matrix() const noexcept;
					};

					class change_origin {
						vector_2d _Origin = {};
					public:
						explicit change_origin(const vector_2d& origin) noexcept;

						void origin(const vector_2d& value) noexcept;
						vector_2d origin() const noexcept;
					};

					using path_data_types = typename ::std::variant<abs_move, abs_line, rel_move, rel_line, abs_cubic_curve, rel_cubic_curve, abs_quadratic_curve, rel_quadratic_curve, arc_clockwise, arc_counterclockwise, new_path, close_path, change_matrix, change_origin>;
				}

				// Forward declaration.
				class surface;
				template <class Allocator = allocator<path_data::path_data_types>>
				class path_factory;

				class path_group {
					::std::shared_ptr<cairo_path_t> _Cairo_path;
				public:
					using native_handle_type = cairo_path*;
					// Note: Can default construct. It will just be empty. To be useful it would need to be assigned to.
					path_group() noexcept = default;
					template <class Allocator>
					explicit path_group(const path_factory<Allocator>& p);
					template <class Allocator>
					path_group(const path_factory<Allocator>& p, std::error_code& ec) noexcept;
					path_group(const path_group&) = default;
					path_group& operator=(const path_group&) = default;
					path_group(path_group&&) = default;
					path_group& operator=(path_group&&) = default;

					native_handle_type native_handle() {
						return _Cairo_path.get();
					}
				};

				//void _Free_manual_cairo_path(cairo_path_t* path) noexcept;
				//void _Free_manual_cairo_path(cairo_path_t* path) noexcept {
				//	if (path != nullptr) {
				//		if (path->data != nullptr) {
				//			delete[] path->data;
				//			path->data = nullptr;
				//			path->status = CAIRO_STATUS_NULL_POINTER;
				//		}
				//		delete path;
				//		path = nullptr;
				//	}
				//}

				enum class _Path_data_new_path {};
				constexpr static _Path_data_new_path _Path_data_new_path_val = {};
				enum class _Path_data_close_path {};
				constexpr static _Path_data_close_path _Path_data_close_path_val = {};
				enum class _Path_data_abs_cubic_curve {};
				constexpr static _Path_data_abs_cubic_curve _Path_data_abs_cubic_curve_val = {};
				enum class _Path_data_abs_line {};
				constexpr static _Path_data_abs_line _Path_data_abs_line_val = {};
				enum class _Path_data_abs_move {};
				constexpr static _Path_data_abs_move _Path_data_abs_move_val = {};
				enum class _Path_data_abs_quadratic_curve {};
				constexpr static _Path_data_abs_quadratic_curve _Path_data_abs_quadratic_curve_val = {};
				enum class _Path_data_rel_cubic_curve {};
				constexpr static _Path_data_rel_cubic_curve _Path_data_rel_cubic_curve_val = {};
				enum class _Path_data_rel_line {};
				constexpr static _Path_data_rel_line _Path_data_rel_line_val = {};
				enum class _Path_data_rel_move {};
				constexpr static _Path_data_rel_move _Path_data_rel_move_val = {};
				enum class _Path_data_rel_quadratic_curve {};
				constexpr static _Path_data_rel_quadratic_curve _Path_data_rel_quadratic_curve_val = {};
				enum class _Path_data_arc_clockwise {};
				constexpr static _Path_data_arc_clockwise _Path_data_arc_clockwise_val = {};
				enum class _Path_data_arc_counterclockwise {};
				constexpr static _Path_data_arc_counterclockwise _Path_data_arc_counterclockwise_val = {};
				enum class _Path_data_change_matrix {};
				constexpr static _Path_data_change_matrix _Path_data_change_matrix_val = {};
				enum class _Path_data_change_origin {};
				constexpr static _Path_data_change_origin _Path_data_change_origin_val = {};

				template <class _TItem>
				struct _Path_group_perform_visit {
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_move>, _Path_data_abs_move> = _Path_data_abs_move_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const path_data::abs_move& item) noexcept {
						cairo_path_data_t cpdItem{};
						auto pt = item.to();
						cpdItem.header.type = CAIRO_PATH_MOVE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = {};
						cpdItem.point = { pt.x(), pt.y() };
						vec.push_back(cpdItem);
					}

					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const path_data::abs_line& item) noexcept {
						cairo_path_data_t cpdItem{};
						auto pt = item.to();
						cpdItem.header.type = CAIRO_PATH_LINE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = {};
						cpdItem.point = { pt.x(), pt.y() };
						vec.push_back(cpdItem);
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const path_data::abs_cubic_curve& item) noexcept {
						cairo_path_data_t cpdItem{};
						auto pt1 = item.control_point_1();
						auto pt2 = item.control_point_2();
						auto pt3 = item.end_point();
						cpdItem.header.type = CAIRO_PATH_CURVE_TO;
						cpdItem.header.length = 4;
						vec.push_back(cpdItem);
						cpdItem = {};
						cpdItem.point = { pt1.x(), pt1.y() };
						vec.push_back(cpdItem);
						cpdItem = {};
						cpdItem.point = { pt2.x(), pt2.y() };
						vec.push_back(cpdItem);
						cpdItem = {};
						cpdItem.point = { pt3.x(), pt3.y() };
						vec.push_back(cpdItem);
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::abs_quadratic_curve&) noexcept {
						assert(false && "Quadratic curves should have been transformed into cubic curves already.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::new_path>, _Path_data_new_path> = _Path_data_new_path_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::new_path&) noexcept {
						assert(false && "New path instructions should have been eliminated.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::close_path>, _Path_data_close_path> = _Path_data_close_path_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const path_data::close_path& item) noexcept {
						auto lastMoveToPoint = item.to();
						cairo_path_data_t cpdItem{};
						cpdItem.header.type = CAIRO_PATH_CLOSE_PATH;
						cpdItem.header.length = 1;
						vec.push_back(cpdItem);
						cpdItem.header.type = CAIRO_PATH_MOVE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = {};
						cpdItem.point = { lastMoveToPoint.x(), lastMoveToPoint.y() };
						vec.push_back(cpdItem);
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_move>, _Path_data_rel_move> = _Path_data_rel_move_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::rel_move&) noexcept {
						assert(false && "Rel move should have been transformed into non-relative.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::rel_line&) noexcept {
						assert(false && "Rel line should have been transformed into non-relative.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::rel_cubic_curve&) noexcept {
						assert(false && "Rel curve should have been transformed into non-relative.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::rel_quadratic_curve&) noexcept {
						assert(false && "Quadratic curves should have been transformed into cubic curves.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::arc_clockwise>, _Path_data_arc_clockwise> = _Path_data_arc_clockwise_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::arc_clockwise&) noexcept {
						assert(false && "Quadratic curves should have been transformed into cubic curves.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::arc_counterclockwise>, _Path_data_arc_counterclockwise> = _Path_data_arc_counterclockwise_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::arc_counterclockwise&) {
						assert(false && "Quadratic curves should have been transformed into cubic curves.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::change_matrix>, _Path_data_change_matrix> = _Path_data_change_matrix_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::change_matrix&) noexcept {
						assert(false && "Change matrix should have been eliminated.");
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::change_origin>, _Path_data_change_origin> = _Path_data_change_origin_val>
					constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const path_data::change_origin&) noexcept {
						assert(false && "Change origin should have been eliminated.");
					}
				};
				//void _Free_manual_cairo_path(cairo_path_t* path) noexcept {
				//	if (path != nullptr) {
				//		if (path->data != nullptr) {
				//			delete[] path->data;
				//			path->data = nullptr;
				//			path->status = CAIRO_STATUS_NULL_POINTER;
				//		}
				//		delete path;
				//		path = nullptr;
				//	}
				//}

				template <class Allocator>
				inline path_group::path_group(const path_factory<Allocator>& pf)
					: _Cairo_path(new cairo_path_t, [](cairo_path_t* path) {
					if (path != nullptr) {
						if (path->data != nullptr) {
							delete[] path->data;
							path->data = nullptr;
							path->status = CAIRO_STATUS_NULL_POINTER;
						}
						delete path;
						path = nullptr;
					}
				}) {
					auto processedVec = _Process_path_data<Allocator>(pf);
					::std::vector<cairo_path_data_t> vec;

					for (const auto& val : processedVec) {
						::std::visit([&vec](auto&& item) {
							using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
							_Path_group_perform_visit<T>::template _Perform<T>(vec, item);
						}, val);
					}
					_Cairo_path->num_data = static_cast<int>(vec.size());
					const auto numDataST = vec.size();
					_Cairo_path->data = new cairo_path_data_t[numDataST];
					for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
						_Cairo_path->data[currItemIndex] = vec[currItemIndex];
					}
					_Cairo_path->status = CAIRO_STATUS_SUCCESS;
				}

				template<class Allocator>
				inline path_group::path_group(const path_factory<Allocator>& pf, ::std::error_code& ec) noexcept {
					: _Cairo_path(new cairo_path_t, [](cairo_path_t* path) {
						if (path != nullptr) {
							if (path->data != nullptr) {
								delete[] path->data;
								path->data = nullptr;
								path->status = CAIRO_STATUS_NULL_POINTER;
							}
							delete path;
							path = nullptr;
						}
					}) {
						auto processedVec = _Process_path_data<Allocator>(pf, ec);
						if (static_cast<bool>(ec)) {
							return;
						}

						::std::vector<cairo_path_data_t> vec;

						for (const auto& val : processedVec) {
							::std::visit([&vec](auto&& item) {
								using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
								_Path_group_perform_visit<T>::_Perform<T>(vec, item);
							}, val);
						}
						_Cairo_path->num_data = static_cast<int>(vec.size());
						const auto numDataST = vec.size();
						_Cairo_path->data = new cairo_path_data_t[numDataST];
						for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
							_Cairo_path->data[currItemIndex] = vec[currItemIndex];
						}
						_Cairo_path->status = CAIRO_STATUS_SUCCESS;
					}
					ec.clear();
				}

				//template <class Allocator>
				//inline path_group::path_group(const path_factory<Allocator>& pf)
				//	: _Cairo_path(new cairo_path_t, &_Free_manual_cairo_path) {
				//	auto processedVec = _Process_path_data<Allocator>(pf);
				//	::std::vector<cairo_path_data_t> vec;

				//	for (const auto& val : processedVec) {
				//		::std::visit([&vec](auto&& item) {
				//			using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
				//			cairo_path_data_t cpdItem{};
				//			if (::std::is_same_v<T, path_data::abs_move>) {
				//				auto pt = item.to();
				//				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				//				cpdItem.header.length = 2;
				//				vec.push_back(cpdItem);
				//				cpdItem = {};
				//				cpdItem.point = { pt.x(), pt.y() };
				//				vec.push_back(cpdItem);
				//			}
				//			else if (::std::is_same_v<T, path_data::abs_line>) {
				//				auto pt = item.to();
				//				cpdItem.header.type = CAIRO_PATH_LINE_TO;
				//				cpdItem.header.length = 2;
				//				vec.push_back(cpdItem);
				//				cpdItem = {};
				//				cpdItem.point = { pt.x(), pt.y() };
				//				vec.push_back(cpdItem);
				//			}
				//			else if (::std::is_same_v<T, path_data::abs_cubic_curve>) {
				//				auto pt1 = item.control_point_1();
				//				auto pt2 = item.control_point_2();
				//				auto pt3 = item.end_point();
				//				cpdItem.header.type = CAIRO_PATH_CURVE_TO;
				//				cpdItem.header.length = 4;
				//				vec.push_back(cpdItem);
				//				cpdItem = {};
				//				cpdItem.point = { pt1.x(), pt1.y() };
				//				vec.push_back(cpdItem);
				//				cpdItem = {};
				//				cpdItem.point = { pt2.x(), pt2.y() };
				//				vec.push_back(cpdItem);
				//				cpdItem = {};
				//				cpdItem.point = { pt3.x(), pt3.y() };
				//				vec.push_back(cpdItem);
				//			}
				//			else if (std::is_same_v<T, path_data::abs_quadratic_curve>) {
				//				assert(false && "Quadratic curves should have been transformed into cubic curves already.");
				//			}
				//			else if (std::is_same_v<T, path_data::new_path>) {
				//				// Do nothing.
				//			}
				//			else if (std::is_same_v<T, path_data::close_path>) {
				//				cpdItem.header.type = CAIRO_PATH_CLOSE_PATH;
				//				cpdItem.header.length = 1;
				//				vec.push_back(cpdItem);
				//				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				//				cpdItem.header.length = 2;
				//				vec.push_back(cpdItem);
				//				cpdItem = {};
				//				cpdItem.point = { lastMoveToPoint.x(), lastMoveToPoint.y() };
				//				vec.push_back(cpdItem);
				//			}
				//			else if (std::is_same_v<T, path_data::rel_move>) {
				//				assert(false && "Rel move should have been transformed into non-relative.");
				//			}
				//			else if (std::is_same_v<T, path_data::rel_line>) {
				//				assert(false && "Rel line should have been transformed into non-relative.");
				//			}
				//			else if (std::is_same_v<T, path_data::rel_cubic_curve>) {
				//				assert(false && "Rel curve should have been transformed into non-relative.");
				//			}
				//			else if (std::is_same_v<T, path_data::rel_quadratic_curve>) {
				//				assert(false && "Quadratic curves should have been transformed into cubic curves.");
				//			}
				//			else if (std::is_same_v<T, path_data::arc_clockwise>) {
				//				assert(false && "Quadratic curves should have been transformed into cubic curves.");
				//			}
				//			else if (std::is_same_v<T, path_data::arc_counterclockwise>) {
				//				assert(false && "Quadratic curves should have been transformed into cubic curves.");
				//			}
				//			else if (std::is_same_v<T, path_data::change_matrix>) {
				//				assert(false && "Change matrix should have been eliminated.");
				//			}
				//			else if (std::is_same_v<T, path_data::change_origin>) {
				//				assert(false && "Change origin should have been eliminated.");
				//			}
				//		}, val);
				//	}
				//	_Cairo_path->num_data = static_cast<int>(vec.size());
				//	const auto numDataST = vec.size();
				//	_Cairo_path->data = new cairo_path_data_t[numDataST];
				//	for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
				//		_Cairo_path->data[currItemIndex] = vec[currItemIndex];
				//	}
				//	_Cairo_path->status = CAIRO_STATUS_SUCCESS;
				//}

				//template<class Allocator>
				//inline path_group::path_group(const path_factory<Allocator>& pf, ::std::error_code& ec) noexcept {
				//	: _Cairo_path(new cairo_path_t, &_Free_manual_cairo_path) {
				//		auto processedVec = _Process_path_data<Allocator>(pf, ec);
				//		if (static_cast<bool>(ec)) {
				//			return;
				//		}

				//		::std::vector<cairo_path_data_t> vec;

				//		for (const auto& val : processedVec) {
				//			::std::visit([&vec](auto&& item) {
				//				using T = std::remove_cv_t<std::remove_reference_t<decltype(item)>>;
				//				cairo_path_data_t cpdItem{};
				//				if (std::is_same_v<T, path_data::abs_move>) {
				//					auto pt = item.to();
				//					cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				//					cpdItem.header.length = 2;
				//					vec.push_back(cpdItem);
				//					cpdItem = {};
				//					cpdItem.point = { pt.x(), pt.y() };
				//					vec.push_back(cpdItem);
				//				}
				//				else if (std::is_same_v<T, path_data::abs_line>) {
				//					auto pt = item.to();
				//					cpdItem.header.type = CAIRO_PATH_LINE_TO;
				//					cpdItem.header.length = 2;
				//					vec.push_back(cpdItem);
				//					cpdItem = {};
				//					cpdItem.point = { pt.x(), pt.y() };
				//					vec.push_back(cpdItem);
				//				}
				//				else if (std::is_same_v<T, path_data::abs_cubic_curve>) {
				//					auto pt1 = item.control_point_1();
				//					auto pt2 = item.control_point_2();
				//					auto pt3 = item.end_point();
				//					cpdItem.header.type = CAIRO_PATH_CURVE_TO;
				//					cpdItem.header.length = 4;
				//					vec.push_back(cpdItem);
				//					cpdItem = {};
				//					cpdItem.point = { pt1.x(), pt1.y() };
				//					vec.push_back(cpdItem);
				//					cpdItem = {};
				//					cpdItem.point = { pt2.x(), pt2.y() };
				//					vec.push_back(cpdItem);
				//					cpdItem = {};
				//					cpdItem.point = { pt3.x(), pt3.y() };
				//					vec.push_back(cpdItem);
				//				}
				//				else if (std::is_same_v<T, path_data::abs_quadratic_curve>) {
				//					assert(false && "Quadratic curves should have been transformed into cubic curves already.");
				//				}
				//				else if (std::is_same_v<T, path_data::new_path>) {
				//					// Do nothing.
				//				}
				//				else if (std::is_same_v<T, path_data::close_path>) {
				//					cpdItem.header.type = CAIRO_PATH_CLOSE_PATH;
				//					cpdItem.header.length = 1;
				//					vec.push_back(cpdItem);
				//					cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				//					cpdItem.header.length = 2;
				//					vec.push_back(cpdItem);
				//					cpdItem = {};
				//					cpdItem.point = { lastMoveToPoint.x(), lastMoveToPoint.y() };
				//					vec.push_back(cpdItem);
				//				}
				//				else if (std::is_same_v<T, path_data::rel_move>) {
				//					assert(false && "Rel move should have been transformed into non-relative.");
				//				}
				//				else if (std::is_same_v<T, path_data::rel_line>) {
				//					assert(false && "Rel line should have been transformed into non-relative.");
				//				}
				//				else if (std::is_same_v<T, path_data::rel_cubic_curve>) {
				//					assert(false && "Rel curve should have been transformed into non-relative.");
				//				}
				//				else if (std::is_same_v<T, path_data::rel_quadratic_curve>) {
				//					assert(false && "Quadratic curves should have been transformed into cubic curves.");
				//				}
				//				else if (std::is_same_v<T, path_data::arc_clockwise>) {
				//					assert(false && "Quadratic curves should have been transformed into cubic curves.");
				//				}
				//				else if (std::is_same_v<T, path_data::arc_counterclockwise>) {
				//					assert(false && "Quadratic curves should have been transformed into cubic curves.");
				//				}
				//				else if (std::is_same_v<T, path_data::change_matrix>) {
				//					assert(false && "Change matrix should have been eliminated.");
				//				}
				//				else if (std::is_same_v<T, path_data::change_origin>) {
				//					assert(false && "Change origin should have been eliminated.");
				//				}
				//			}, val);
				//		}
				//		_Cairo_path->num_data = static_cast<int>(vec.size());
				//		const auto numDataST = vec.size();
				//		_Cairo_path->data = new cairo_path_data_t[numDataST];
				//		for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
				//			_Cairo_path->data[currItemIndex] = vec[currItemIndex];
				//		}
				//		_Cairo_path->status = CAIRO_STATUS_SUCCESS;
				//	}
				//	ec.clear();
				//}

				template <class Allocator>
				class path_factory {
					friend path_group;
					::std::vector<path_data::path_data_types, Allocator> _Data;
					optional<vector_2d> _Current_point;
					vector_2d _Last_move_to_point;
					matrix_2d _Transform_matrix;
					vector_2d _Origin;
				public:
					using value_type = path_data::path_data_types;
					using allocator_type = Allocator;
					using reference = value_type&;
					using const_reference = const value_type&;
					using size_type = ::std::vector<path_data::path_data_types>::size_type;
					using difference_type = ::std::vector<path_data::path_data_types>::difference_type;
					using iterator = ::std::vector<path_data::path_data_types>::iterator;
					using const_iterator = ::std::vector<path_data::path_data_types>::const_iterator;
					using reverse_iterator = std::reverse_iterator<iterator>;
					using const_reverse_iterator = std::reverse_iterator<const_iterator>;

					path_factory() noexcept(noexcept(Allocator())) :
						path_factory(Allocator()) { }
					explicit path_factory(const Allocator& a) noexcept;
					explicit path_factory(size_type n, const Allocator& a = Allocator());
					path_factory(size_type n, const value_type& value,
						const Allocator& a = Allocator());
					template <class InputIterator>
					path_factory(InputIterator first, InputIterator last,
						const Allocator& = Allocator());
					path_factory(const path_factory& pf);
					path_factory(path_factory&& pf) noexcept;
					path_factory(const path_factory& pf, const Allocator& a);
					path_factory(path_factory&& pf, const Allocator& a);
					path_factory(initializer_list<value_type> il, const Allocator& a = Allocator());
					~path_factory() { }
					path_factory& operator=(const path_factory& x);
					path_factory& operator=(path_factory&& x)
						noexcept(
							allocator_traits<Allocator>::propagate_on_container_move_assignment::value
							||
							allocator_traits<Allocator>::is_always_equal::value);
					path_factory& operator=(initializer_list<value_type> il);
					template <class InputIterator>
					void assign(InputIterator first, InputIterator last);
					void assign(size_type n, const value_type& u);
					void assign(initializer_list<value_type> il);
					allocator_type get_allocator() const noexcept;

					iterator begin() noexcept;
					const_iterator begin() const noexcept;
					const_iterator cbegin() const noexcept;
					iterator end() noexcept;
					const_iterator end() const noexcept;
					const_iterator cend() const noexcept;
					reverse_iterator rbegin() noexcept;
					const_reverse_iterator rbegin() const noexcept;
					const_reverse_iterator crbegin() const noexcept;
					reverse_iterator rend() noexcept;
					const_reverse_iterator rend() const noexcept;
					const_reverse_iterator crend() const noexcept;

					bool empty() const noexcept;
					size_type size() const noexcept;
					size_type max_size() const noexcept;
					size_type capacity() const noexcept;
					void resize(size_type sz);
					void resize(size_type sz, const value_type& c);
					void reserve(size_type n);
					void shrink_to_fit();

					reference operator[](size_type n);
					const_reference operator[](size_type n) const;
					const_reference at(size_type n) const;
					reference at(size_type n);
					reference front();
					const_reference front() const;
					reference back();
					const_reference back() const;

					// Modifiers
					void new_path() noexcept;
					void close_path() noexcept;
					void arc_clockwise(const vector_2d& center, double radius, double angle1,
						double angle2) noexcept;
					void arc_counterclockwise(const vector_2d& center, double radius,
						double angle1, double angle2) noexcept;
					void cubic_curve_to(const vector_2d& pt0, const vector_2d& pt1,
						const vector_2d& pt2) noexcept;
					void line_to(const vector_2d& pt) noexcept;
					void move_to(const vector_2d& pt) noexcept;
					void quadratic_curve_to(const vector_2d& pt0, const vector_2d& pt1)
						noexcept;
					void rectangle(const experimental::io2d::rectangle& r) noexcept;
					void rel_cubic_curve_to(const vector_2d& dpt0, const vector_2d& dpt1,
						const vector_2d& dpt2) noexcept;
					void rel_line_to(const vector_2d& dpt) noexcept;
					void rel_move_to(const vector_2d& dpt) noexcept;
					void rel_quadratic_curve_to(const vector_2d& dpt0, const vector_2d& dpt1)
						noexcept;
					void transform_matrix(const matrix_2d& m) noexcept;
					void origin(const vector_2d& pt) noexcept;
					template <class... Args>
					reference emplace_back(Args&&... args);
					void push_back(const value_type& x);
					void push_back(value_type&& x);
					void pop_back();

					template <class... Args>
					iterator emplace(const_iterator position, Args&&... args);
					iterator insert(const_iterator position, const value_type& x);
					iterator insert(const_iterator position, value_type&& x);
					iterator insert(const_iterator position, size_type n, const value_type& x);
					template <class InputIterator>
					iterator insert(const_iterator position, InputIterator first,
						InputIterator last);
					iterator insert(const_iterator position,
						initializer_list<value_type> il);
					iterator erase(const_iterator position);
					iterator erase(const_iterator first, const_iterator last);
					void swap(path_factory&)
						noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value
							|| allocator_traits<Allocator>::is_always_equal::value);
					void clear() noexcept;

					// Observers
					::std::experimental::io2d::rectangle path_extents() const;
					::std::experimental::io2d::rectangle path_extents(::std::error_code& ec) const noexcept;
					bool has_current_point() const noexcept;
					vector_2d current_point() const;
					vector_2d current_point(::std::error_code& ec) const noexcept;
					matrix_2d current_matrix() const noexcept;
					vector_2d current_origin() const noexcept;
					//::std::vector<path_data_item> data() const;
					//::std::vector<path_data_item> data(::std::error_code& ec) const noexcept;
					//path_data_item data_item(unsigned int index) const;
					//path_data_item data_item(unsigned int index, ::std::error_code& ec) const noexcept;
					//const ::std::vector<path_data_item>& data_ref() const noexcept;
				};

				template <class Allocator>
				bool operator==(const path_factory<Allocator>& lhs,
					const path_factory<Allocator>& rhs);
				template <class Allocator>
				bool operator!=(const path_factory<Allocator>& lhs,
					const path_factory<Allocator>& rhs);
				// 8.17.8, specialized algorithms:
				template <class Allocator>
				void swap(path_factory<Allocator>& lhs, path_factory<Allocator>& rhs)
					noexcept(noexcept(lhs.swap(rhs)));

				class device {
				public:
					typedef cairo_device_t* native_handle_type;
				private:
					friend surface;
					explicit device(native_handle_type nh);
					device(native_handle_type nh, error_code& ec) noexcept;
				protected:
					::std::shared_ptr<cairo_device_t> _Device;
				public:
					native_handle_type native_handle() const noexcept;

					device() = delete;
					device(const device&) = delete;
					device& operator=(const device&) = delete;
					device(device&& other) noexcept = default;
					device& operator=(device&& other) noexcept = default;

					// Modifiers
					void flush() noexcept;
					void lock();
					void lock(::std::error_code& ec) noexcept;
					void unlock();
					void unlock(::std::error_code& ec) noexcept;
				};

				class color_stop {
				private:
					double _Offset = 0.0;
					rgba_color _Color = rgba_color::black();
				public:
					color_stop(double offset, rgba_color color);

					::std::error_code offset(double value);
					::std::error_code color(rgba_color value);

					double offset() const noexcept;
					rgba_color color() const noexcept;
				};

				template <class Allocator = allocator<color_stop>>
				class color_stop_group {
				public:
					using value_type = color_stop;
					using allocator_type = Allocator;
					using pointer = typename allocator_traits<Allocator>::pointer;
					using const_pointer = typename allocator_traits<Allocator>::const_pointer;
					using reference = value_type&;
					using const_reference = const value_type&;
					using size_type = typename ::std::vector<color_stop, Allocator>::size_type;
					using difference_type = typename ::std::vector<color_stop, Allocator>::difference_type;
					using iterator = typename ::std::vector<color_stop, Allocator>::iterator;
					using const_iterator = typename ::std::vector<color_stop, Allocator>::const_iterator;
					using reverse_iterator = typename ::std::reverse_iterator<iterator>;
					using const_reverse_iterator = typename ::std::reverse_iterator<const_iterator>;

					color_stop_group() noexcept(noexcept(Allocator())) :
						color_stop_group(Allocator()) { }
					explicit color_stop_group(const Allocator&) noexcept;
					explicit color_stop_group(size_type n, const Allocator& = Allocator());
					color_stop_group(size_type n, const value_type& value,
						const Allocator& = Allocator());
					template <class InputIterator>
					color_stop_group(InputIterator first, InputIterator last,
						const Allocator& = Allocator());
					color_stop_group(const color_stop_group& x);
					color_stop_group(color_stop_group&&) noexcept;
					color_stop_group(const color_stop_group&, const Allocator&);
					color_stop_group(color_stop_group&&, const Allocator&);
					color_stop_group(initializer_list<value_type>,
						const Allocator& = Allocator());
					~color_stop_group();
					color_stop_group& operator=(const color_stop_group& x);
					color_stop_group& operator=(color_stop_group&& x)
						noexcept(
							allocator_traits<Allocator>::propagate_on_container_move_assignment::value
							|| allocator_traits<Allocator>::is_always_equal::value);
					color_stop_group& operator=(initializer_list<value_type>);
					template <class InputIterator>
					void assign(InputIterator first, InputIterator last);
					void assign(size_type n, const value_type& u);
					void assign(initializer_list<value_type>);
					allocator_type get_allocator() const noexcept;
					// 9.5.7, iterators:
					iterator begin() noexcept;
					const_iterator begin() const noexcept;
					const_iterator cbegin() const noexcept;
					iterator end() noexcept;
					const_iterator end() const noexcept;
					const_iterator cend() const noexcept;
					reverse_iterator rbegin() noexcept;
					const_reverse_iterator rbegin() const noexcept;
					const_reverse_iterator crbegin() const noexcept;
					reverse_iterator rend() noexcept;
					const_reverse_iterator rend() const noexcept;
					const_reverse_iterator crend() const noexcept;

					bool empty() const noexcept;
					size_type size() const noexcept;
					size_type max_size() const noexcept;
					size_type capacity() const noexcept;
					void resize(size_type sz);
					void resize(size_type sz, const value_type& c);
					void reserve(size_type n);
					void shrink_to_fit();
					// element access:
					reference operator[](size_type n);
					const_reference operator[](size_type n) const;
					const_reference at(size_type n) const;
					reference at(size_type n);
					reference front();
					const_reference front() const;
					reference back();
					const_reference back() const;

					template <class... Args>
					reference emplace_back(Args&&... args);
					void push_back(const value_type& x);
					void push_back(value_type&& x);
					void pop_back();
					template <class... Args>
					iterator emplace(const_iterator position, Args&&... args);
					iterator insert(const_iterator position, const value_type& x);
					iterator insert(const_iterator position, value_type&& x);
					iterator insert(const_iterator position, size_type n, const value_type& x);
					template <class InputIterator>
					iterator insert(const_iterator position, InputIterator first,
						InputIterator last);
					iterator insert(const_iterator position,
						initializer_list<value_type> il);
					iterator erase(const_iterator position);
					iterator erase(const_iterator first, const_iterator last);
					void swap(color_stop_group&)
						noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value
							|| allocator_traits<Allocator>::is_always_equal::value);
					void clear() noexcept;
				};

				template <class Allocator>
				bool operator==(const color_stop_group<Allocator>& lhs,
					const color_stop_group<Allocator>& rhs);
				template <class Allocator>
				bool operator!=(const color_stop_group<Allocator>& lhs,
					const color_stop_group<Allocator>& rhs);
				// 8.17.8, specialized algorithms:
				template <class Allocator>
				void swap(color_stop_group<Allocator>& lhs, color_stop_group<Allocator>& rhs)
					noexcept(noexcept(lhs.swap(rhs)));

				class surface;
				class image_surface;
				class display_surface;

				class brush {
				public:
					typedef cairo_pattern_t* native_handle_type;

				private:
					friend surface;
					friend display_surface;
					// Precondition: nh has already had its reference count incremented (either in creation or with cairo_pattern_reference).
					brush(native_handle_type nh) noexcept;

					::std::shared_ptr<cairo_pattern_t> _Brush;
					::std::shared_ptr<image_surface> _Image_surface;
					brush_type _Brush_type;
					::std::experimental::io2d::tiling _Extend;
					::std::experimental::io2d::filter _Filter;
					matrix_2d _Matrix;

				public:
					native_handle_type native_handle() const noexcept;

					brush() = delete;
					brush(const brush&) noexcept = default;
					brush& operator=(const brush&) noexcept = default;
					brush(brush&& other) noexcept = default;
					brush& operator=(brush&& other) noexcept = default;
					brush(const rgba_color& c);
					brush(const rgba_color& c, error_code& ec) noexcept;
					template <class Allocator = allocator<color_stop>>
					brush(const vector_2d& begin, const vector_2d& end,
						const color_stop_group<Allocator>& csg);
					template <class Allocator = allocator<color_stop>>
					brush(const vector_2d& begin, const vector_2d& end,
						const color_stop_group<Allocator>& csg, error_code& ec) noexcept;
					template <class Allocator = allocator<color_stop>>
					brush(const circle& start, const circle& end,
						const color_stop_group<Allocator>& csg);
					template <class Allocator = allocator<color_stop>>
					brush(const circle& start, const circle& end,
						const color_stop_group<Allocator>& csg, error_code& ec) noexcept;
					brush(image_surface&& img);
					brush(image_surface&& img, error_code& ec) noexcept;

					void tiling(::std::experimental::io2d::tiling e) noexcept;
					void filter(::std::experimental::io2d::filter f) noexcept;
					void matrix(const matrix_2d& m) noexcept;

					::std::experimental::io2d::tiling tiling() const noexcept;
					::std::experimental::io2d::filter filter() const noexcept;
					matrix_2d matrix() const noexcept;
					brush_type type() const noexcept;
					//const image_surface& surface() const;
					//const image_surface& surface(::std::error_code& ec) const noexcept;

				};

				struct _Surface_native_handles {
					::cairo_surface_t* csfce;
					::cairo_t* cctxt;
				};

				class mapped_surface;

				// tuple<dashes, offset>
				typedef ::std::tuple<::std::vector<double>, double> dashes;

				// I don't know why Clang/C2 is complaining about weak vtables here since the at least one virtual function is always anchored but for now silence the warnings. I've never seen this using Clang on OpenSUSE.
#ifdef _WIN32
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
#endif

				class surface {
				public:
					typedef _Surface_native_handles native_handle_type;
				private:
					::std::weak_ptr<::std::experimental::io2d::device> _Device;
				protected:
					::std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> _Surface;
					::std::unique_ptr<cairo_t, decltype(&cairo_destroy)> _Context;
					::std::unique_ptr<cairo_font_options_t, decltype(&cairo_font_options_destroy)> _Native_font_options;

					const double _Line_join_miter_miter_limit = 10000.0;

					// State - unsaved
					typedef rectangle _Dirty_type;
					_Dirty_type _Dirty_rect;
					::std::experimental::io2d::format _Format;
					::std::experimental::io2d::content _Content;

					// State - saved
					::std::experimental::io2d::brush _Brush;
					::std::experimental::io2d::antialias _Antialias;
					::std::experimental::io2d::dashes _Dashes;
					::std::experimental::io2d::fill_rule _Fill_rule;
					::std::experimental::io2d::line_cap _Line_cap;
					::std::experimental::io2d::line_join _Line_join = ::std::experimental::io2d::line_join::miter;
					typedef double _Line_width_type;
					_Line_width_type _Line_width;
					typedef double _Miter_limit_type;
					_Miter_limit_type _Miter_limit = 10.0;
					::std::experimental::io2d::compositing_operator _Compositing_operator;
					::std::shared_ptr<::std::experimental::io2d::path_group> _Current_path;
					::std::experimental::io2d::path_factory<> _Immediate_path;
					typedef matrix_2d _Transform_matrix_type;
					_Transform_matrix_type _Transform_matrix;

					// Relies on C++17 noexcept guarantee for vector default ctor (N4258, adopted 2014-11).
					::std::stack < ::std::tuple<
						::std::experimental::io2d::brush,
						::std::experimental::io2d::antialias,
						::std::experimental::io2d::dashes,
						::std::experimental::io2d::fill_rule,
						::std::experimental::io2d::line_cap,
						::std::experimental::io2d::line_join,
						_Line_width_type,
						_Miter_limit_type,
						::std::experimental::io2d::compositing_operator,
						::std::shared_ptr<::std::experimental::io2d::path_group>,
						::std::experimental::io2d::path_factory<>,
						_Transform_matrix_type
					>, ::std::vector<::std::tuple<
						::std::experimental::io2d::brush,
						::std::experimental::io2d::antialias,
						::std::experimental::io2d::dashes,
						::std::experimental::io2d::fill_rule,
						::std::experimental::io2d::line_cap,
						::std::experimental::io2d::line_join,
						_Line_width_type,
						_Miter_limit_type,
						::std::experimental::io2d::compositing_operator,
						::std::shared_ptr<::std::experimental::io2d::path_group>,
						::std::experimental::io2d::path_factory<>,
						_Transform_matrix_type>> > _Saved_state;

					void _Ensure_state();
					void _Ensure_state(::std::error_code& ec) noexcept;

					surface(::std::experimental::io2d::format fmt, int width, int height);
					surface(::std::experimental::io2d::format fmt, int width, int height, ::std::error_code& ec) noexcept;

					surface(native_handle_type nh, ::std::experimental::io2d::format fmt, ::std::experimental::io2d::content ctnt);
					surface(native_handle_type nh, ::std::experimental::io2d::format fmt, ::std::experimental::io2d::content ctnt, ::std::error_code& ec) noexcept;

					// create_similar
					surface(const surface& other, ::std::experimental::io2d::content ctnt, int width, int height);
					surface(const surface& other, ::std::experimental::io2d::content ctnt, int width, int height, ::std::error_code& ec) noexcept;

					void path_group(const ::std::shared_ptr<::std::experimental::io2d::path_group>& p);
					void path_group(const ::std::shared_ptr<::std::experimental::io2d::path_group>& p, ::std::error_code& ec) noexcept;
				public:
					bool _Has_surface_resource() const noexcept;
					native_handle_type native_handle() const;

					surface() = delete;
					surface(const surface&) = delete;
					surface& operator=(const surface&) = delete;
					surface(surface&& other) /*noexcept*/ = default;
					surface& operator=(surface&& other) /*noexcept*/ = default;

					virtual ~surface();

					// \ref{\iotwod.surface.modifiers.state}, state modifiers:
					virtual void finish() noexcept;
					void flush();
					void flush(::std::error_code& ec) noexcept;
					::std::shared_ptr<::std::experimental::io2d::device> device();
					::std::shared_ptr<::std::experimental::io2d::device> device(::std::error_code& ec) noexcept;
					void mark_dirty();
					void mark_dirty(::std::error_code& ec) noexcept;
					void mark_dirty(const rectangle& rect);
					void mark_dirty(const rectangle& rect, ::std::error_code& ec) noexcept;
					void map(const ::std::function<void(mapped_surface&)>& action);
					void map(const ::std::function<void(mapped_surface&, error_code&)>& action, ::std::error_code& ec);
					void map(const ::std::function<void(mapped_surface&)>& action, const rectangle& extents);
					void map(const ::std::function<void(mapped_surface&, error_code&)>& action, const rectangle& extents, ::std::error_code& ec);
					virtual void save();
					virtual void save(::std::error_code& ec) noexcept;
					virtual void restore();
					virtual void restore(::std::error_code& ec) noexcept;
					void brush(experimental::io2d::nullvalue_t) noexcept;
					void brush(const ::std::experimental::io2d::brush& source);
					void brush(const ::std::experimental::io2d::brush& source, ::std::error_code& ec) noexcept;
					void antialias(::std::experimental::io2d::antialias a) noexcept;
					void dashes(experimental::io2d::nullvalue_t) noexcept;
					void dashes(const ::std::experimental::io2d::dashes& d);
					void dashes(const ::std::experimental::io2d::dashes& d, ::std::error_code& ec) noexcept;
					void fill_rule(::std::experimental::io2d::fill_rule fr) noexcept;
					void line_cap(::std::experimental::io2d::line_cap lc) noexcept;
					void line_join(::std::experimental::io2d::line_join lj) noexcept;
					void line_width(double width) noexcept;
					void miter_limit(double limit) noexcept;
					void compositing_operator(::std::experimental::io2d::compositing_operator co) noexcept;
					//void clip(experimental::nullopt_t) noexcept;
					void clip(const ::std::experimental::io2d::path_group& p);
					void clip(const ::std::experimental::io2d::path_group& p, ::std::error_code& ec) noexcept;
					void clip_immediate();
					void clip_immediate(::std::error_code& ec) noexcept;
					void path_group(experimental::io2d::nullvalue_t) noexcept;
					void path_group(const ::std::experimental::io2d::path_group& p);
					void path_group(const ::std::experimental::io2d::path_group& p, ::std::error_code& ec) noexcept;

					// \ref{\iotwod.surface.modifiers.immediatepath}, immediate path_group modifiers:
					::std::experimental::io2d::path_factory<>& immediate() noexcept;

					// \ref{\iotwod.surface.modifiers.render}, render modifiers:
					void clear();
					void fill();
					void fill(::std::error_code& ec) noexcept;
					void fill(const rgba_color& c);
					void fill(const rgba_color& c, ::std::error_code& ec) noexcept;
					void fill(const ::std::experimental::io2d::brush& b);
					void fill(const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void fill(const surface& s, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good);
					void fill(const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good) noexcept;
					void fill_immediate();
					void fill_immediate(::std::error_code& ec) noexcept;
					void fill_immediate(const rgba_color& c);
					void fill_immediate(const rgba_color& c, ::std::error_code& ec) noexcept;
					void fill_immediate(const ::std::experimental::io2d::brush& b);
					void fill_immediate(const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void fill_immediate(const surface& s, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good);
					void fill_immediate(const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good) noexcept;
					void paint();
					void paint(::std::error_code& ec) noexcept;
					void paint(const rgba_color& c);
					void paint(const rgba_color& c, ::std::error_code& ec) noexcept;
					void paint(const ::std::experimental::io2d::brush& b);
					void paint(const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void paint(const surface& s, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good);
					void paint(const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good) noexcept;
					void paint(double alpha);
					void paint(double alpha, ::std::error_code& ec) noexcept;
					void paint(const rgba_color& c, double alpha);
					void paint(const rgba_color& c, double alpha, ::std::error_code& ec) noexcept;
					void paint(const ::std::experimental::io2d::brush& b, double alpha);
					void paint(const ::std::experimental::io2d::brush& b, double alpha, ::std::error_code& ec) noexcept;
					void paint(const surface& s, double alpha, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good);
					void paint(const surface& s, double alpha, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good) noexcept;
					void stroke();
					void stroke(::std::error_code& ec) noexcept;
					void stroke(const rgba_color& c);
					void stroke(const rgba_color& c, ::std::error_code& ec) noexcept;
					void stroke(const ::std::experimental::io2d::brush& b);
					void stroke(const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void stroke(const surface& s, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good);
					void stroke(const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good) noexcept;
					void stroke_immediate();
					void stroke_immediate(::std::error_code& ec) noexcept;
					void stroke_immediate(const rgba_color& c);
					void stroke_immediate(const rgba_color& c, ::std::error_code& ec) noexcept;
					void stroke_immediate(const ::std::experimental::io2d::brush& b);
					void stroke_immediate(const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void stroke_immediate(const surface& s, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good);
					void stroke_immediate(const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good) noexcept;

					// \ref{\iotwod.surface.modifiers.maskrender}, mask render modifiers:
					void mask(const ::std::experimental::io2d::brush& maskBrush);
					void mask(const ::std::experimental::io2d::brush& maskBrush, ::std::error_code& ec) noexcept;
					void mask(const ::std::experimental::io2d::brush& maskBrush, const rgba_color& c);
					void mask(const ::std::experimental::io2d::brush& maskBrush, const rgba_color& c, ::std::error_code& ec) noexcept;
					void mask(const ::std::experimental::io2d::brush& maskBrush, const ::std::experimental::io2d::brush& b);
					void mask(const ::std::experimental::io2d::brush& maskBrush, const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void mask(const ::std::experimental::io2d::brush& maskBrush, const surface& s, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good);
					void mask(const ::std::experimental::io2d::brush& maskBrush, const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good) noexcept;
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush);
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, ::std::error_code& ec) noexcept;
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const rgba_color& c);
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const rgba_color& c, ::std::error_code& ec) noexcept;
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const ::std::experimental::io2d::brush& b);
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const surface& s, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good);
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), tiling e = tiling::none, filter f = filter::good) noexcept;

					// \ref{\iotwod.surface.modifiers.transform}, transformation modifiers:
					void matrix(const matrix_2d& matrix);
					void matrix(const matrix_2d& matrix, ::std::error_code& ec) noexcept;

					// \ref{\iotwod.surface.observers.state}, state observers:
					bool is_finished() const noexcept;
					::std::experimental::io2d::content content() const noexcept;
					::std::experimental::io2d::brush brush() const noexcept;
					::std::experimental::io2d::antialias antialias() const noexcept;
					::std::experimental::io2d::dashes dashes() const;
					::std::experimental::io2d::dashes dashes(::std::error_code& ec) const noexcept;
					::std::experimental::io2d::fill_rule fill_rule() const noexcept;
					::std::experimental::io2d::line_cap line_cap() const noexcept;
					::std::experimental::io2d::line_join line_join() const noexcept;
					double line_width() const noexcept;
					double miter_limit() const noexcept;
					::std::experimental::io2d::compositing_operator compositing_operator() const noexcept;
					rectangle clip_extents() const noexcept;
					bool in_clip(const vector_2d& pt) const noexcept;
					::std::vector<rectangle> clip_rectangles() const;
					::std::vector<rectangle> clip_rectangles(::std::error_code& ec) const noexcept;

					// \ref{\iotwod.surface.observers.render}, render observers:
					rectangle fill_extents() const noexcept;
					rectangle fill_extents_immediate() const noexcept;
					bool in_fill(const vector_2d& pt) const noexcept;
					bool in_fill_immediate(const vector_2d& pt) const noexcept;
					rectangle stroke_extents() const noexcept;
					rectangle stroke_extents_immediate() const noexcept;
					bool in_stroke(const vector_2d& pt) const noexcept;
					bool in_stroke_immediate(const vector_2d& pt) const noexcept;

					// \ref{\iotwod.surface.observers.transform}, transformation observers:
					matrix_2d matrix() const noexcept;
					vector_2d user_to_surface(const vector_2d& pt) const noexcept;
					vector_2d user_to_surface_distance(const vector_2d& dpt) const noexcept;
					vector_2d surface_to_user(const vector_2d& pt) const;
					vector_2d surface_to_user(const vector_2d& pt, ::std::error_code& ec) const noexcept;
					vector_2d surface_to_user_distance(const vector_2d& dpt) const;
					vector_2d surface_to_user_distance(const vector_2d& dpt, ::std::error_code& ec) const noexcept;
				};

				// I don't know why Clang/C2 is complaining about weak vtables here since the at least one virtual function is always anchored but for now silence the warnings. I've never seen this using Clang on OpenSUSE.
#ifdef _WIN32
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif

				// I don't know why Clang/C2 is complaining about weak vtables here since the at least one virtual function is always anchored but for now silence the warnings. I've never seen this using Clang on OpenSUSE.
#ifdef _WIN32
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
#endif
				class image_surface : public surface {
					friend surface;
				public:
					image_surface() = delete;
					image_surface(const image_surface&) = delete;
					image_surface& operator=(const image_surface&) = delete;
					image_surface(image_surface&& other) /*noexcept*/ = default;
					image_surface& operator=(image_surface&& other) /*noexcept*/ = default;
					image_surface(::std::experimental::io2d::format fmt, int width, int height);
					image_surface(::std::experimental::io2d::format fmt, int width, int height, ::std::error_code& ec) noexcept;
					template <class InputIt>
					image_surface(InputIt first, InputIt last, ::std::experimental::io2d::format fmt, int width, int height);
					template <class InputIt>
					image_surface(InputIt first, InputIt last, ::std::experimental::io2d::format fmt, int width, int height, ::std::error_code& ec) noexcept;
					//// create_similar_image
					//image_surface(const surface& other, ::std::experimental::io2d::format fmt, int width, int height);
					//image_surface(const surface& other, ::std::experimental::io2d::format fmt, int width, int height, ::std::error_code& ec) noexcept;
					//// create_from_png
					//image_surface(const ::std::string& filename);
					virtual ~image_surface() { }

					// Modifiers
					void data(const ::std::vector<unsigned char>& data);
					void data(const ::std::vector<unsigned char>& data, ::std::error_code& ec) noexcept;
					::std::vector<unsigned char> data();
					::std::vector<unsigned char> data(::std::error_code& ec) noexcept;

					// Observers
					::std::experimental::io2d::format format() const noexcept;
					int width() const noexcept;
					int height() const noexcept;
					int stride() const noexcept;
				};

				// I don't know why Clang/C2 is complaining about weak vtables here since the at least one virtual function is always anchored but for now silence the warnings. I've never seen this using Clang on OpenSUSE.
#ifdef _WIN32
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif

				class mapped_surface {
					surface::native_handle_type _Mapped_surface;
					surface::native_handle_type _Map_of;

					friend surface;
					mapped_surface(surface::native_handle_type nh, surface::native_handle_type map_of);
					mapped_surface(surface::native_handle_type nh, surface::native_handle_type map_of, ::std::error_code& ec) noexcept;

				public:
					mapped_surface() = delete;
					mapped_surface(const mapped_surface&) = delete;
					mapped_surface& operator=(const mapped_surface&) = delete;
					mapped_surface(mapped_surface&& other) = delete;
					mapped_surface& operator=(mapped_surface&& other) = delete;
					~mapped_surface();

					// Modifiers
					void commit_changes();
					void commit_changes(::std::error_code& ec) noexcept;
					void commit_changes(const rectangle& area);
					void commit_changes(const rectangle& area, ::std::error_code& ec) noexcept;

					unsigned char* data();
					unsigned char* data(::std::error_code& ec) noexcept;
					//void rgba_data(const ::std::vector<rgba_color>& v);
					//void rgba_data(const ::std::vector<rgba_color>& v, ::std::error_code& ec) noexcept;
					//void rgba_data(const ::std::vector<rgba_color>& v, unsigned int offset);
					//void rgba_data(const ::std::vector<rgba_color>& v, unsigned int offset, ::std::error_code& ec) noexcept;

					// Observers
					const unsigned char* data() const;
					const unsigned char* data(::std::error_code& ec) const noexcept;
					//::std::vector<rgba_color> rgba_data() const;
					//::std::vector<rgba_color> rgba_data(::std::error_code& ec) const noexcept;

					::std::experimental::io2d::format format() const noexcept;
					int width() const noexcept;
					int height() const noexcept;
					int stride() const noexcept;
				};

#ifdef _WIN32_WINNT
				struct _Win32_display_surface_native_handle {
					_Surface_native_handles sfc_nh;
					HWND hwnd;
					_Surface_native_handles win32_sfc_nh;
				};

				const int _Display_surface_ptr_window_data_byte_offset = 0;

				LRESULT CALLBACK _RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
#elif defined(USE_XCB)
				struct _Xcb_display_surface_native_handle {
					_Surface_native_handles sfc_nh;
					_Surface_native_handles display_sfc_nh;
					xcb_connection_t* connection;
					::std::mutex& connection_mutex;
					int& connection_ref_count;
					xcb_screen_t* screen;
					xcb_window_t wndw;
				};
#elif defined(USE_XLIB)
				struct _Xlib_display_surface_native_handle {
					_Surface_native_handles sfc_nh;
					Display* display;
					Window wndw;
					::std::mutex& display_mutex;
					int& display_ref_count;
			};
#endif

				// I don't know why Clang/C2 is complaining about weak vtables here since the at least one virtual function is always anchored but for now silence the warnings. I've never seen this using Clang on OpenSUSE.
#ifdef _WIN32
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
#endif
				class display_surface : public surface {
					friend surface;
					// Unsaved state.
					::std::experimental::io2d::brush _Default_brush;
					typedef int _Display_width_type;
					_Display_width_type _Display_width;
					typedef int _Display_height_type;
					_Display_height_type _Display_height;
					::std::experimental::io2d::scaling _Scaling;
					typedef int _Width_type;
					_Width_type _Width;
					typedef int _Height_type;
					_Height_type _Height;
					::std::function<void(display_surface& sfc)> _Draw_fn;
					::std::function<void(display_surface& sfc)> _Size_change_fn;
					typedef ::std::function<::std::experimental::io2d::rectangle(const display_surface&, bool&)> _User_scaling_fn_type;
					_User_scaling_fn_type _User_scaling_fn;
					::std::experimental::io2d::brush _Letterbox_brush;
					typedef bool _Auto_clear_type;
					_Auto_clear_type _Auto_clear;

					//::std::stack<::std::tuple<
					//	::std::experimental::io2d::scaling,
					//	_Width_type,
					//	_Height_type,
					//	_User_scaling_fn_type,
					//	::std::experimental::io2d::brush
					//>, ::std::vector<::std::tuple<
					//	::std::experimental::io2d::scaling,
					//	_Width_type,
					//	_Height_type,
					//	_User_scaling_fn_type,
					//	::std::experimental::io2d::brush>>> _Display_saved_state;
#ifdef _WIN32_WINNT
					friend LRESULT CALLBACK _RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
					DWORD _Window_style;
					HWND _Hwnd;

					LRESULT _Window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
#elif defined(USE_XCB)
					static ::std::mutex _Connection_mutex;
					static ::std::unique_ptr<xcb_connection_t, decltype(&xcb_disconnect)> _Connection;
					static int _Connection_ref_count;
					xcb_screen_t* _Screen;
					xcb_window_t _Wndw;
					bool _Can_draw = false;
					const uint16_t _Window_border_width = 4;
#elif defined(USE_XLIB)
					static ::std::mutex _Display_mutex;
					static ::std::unique_ptr<Display, ::std::function<void(Display*)>> _Display;
					static int _Display_ref_count;
					::Window _Wndw;
					bool _Can_draw = false;

					static Bool _X11_if_event_pred(Display* display, XEvent* event, XPointer arg);
#endif
					::std::experimental::io2d::refresh_rate _Refresh_rate;
					double _Desired_frame_rate;
					::std::atomic<bool> _Redraw_requested;
					double _Elapsed_draw_time;
					const double _Minimum_frame_rate = 0.01;
					const double _Maximum_frame_rate = 120.0;
					::std::unique_ptr<cairo_surface_t, ::std::function<void(cairo_surface_t*)>> _Native_surface;
					::std::unique_ptr<cairo_t, ::std::function<void(cairo_t*)>> _Native_context;

					void _Make_native_surface_and_context();
					void _Make_native_surface_and_context(::std::error_code& ec) noexcept;
					void _All_dimensions(int w, int h, int dw, int dh);
					void _All_dimensions(int w, int h, int dw, int dh, ::std::error_code& ec) noexcept;
					void _Render_to_native_surface();
					void _Render_to_native_surface(::std::error_code& ec) noexcept;
					void _Resize_window();
					void _Resize_window(::std::error_code& ec) noexcept;
					void _Render_for_scaling_uniform_or_letterbox();
					void _Render_for_scaling_uniform_or_letterbox(::std::error_code& ec) noexcept;

				public:
#ifdef _WIN32_WINNT
					typedef _Win32_display_surface_native_handle native_handle_type;
#elif defined(USE_XCB)
					typedef _Xcb_display_surface_native_handle native_handle_type;
#elif defined(USE_XLIB)
					typedef _Xlib_display_surface_native_handle native_handle_type;
#endif
					native_handle_type native_handle() const;

					display_surface() = delete;
					display_surface(const display_surface&) = delete;
					display_surface& operator=(const display_surface&) = delete;
					display_surface(display_surface&& other) noexcept;
					display_surface& operator=(display_surface&& other) noexcept;

					display_surface(int preferredWidth, int preferredHeight, ::std::experimental::io2d::format preferredFormat,
						::std::experimental::io2d::scaling scl = ::std::experimental::io2d::scaling::letterbox, ::std::experimental::io2d::refresh_rate rr = ::std::experimental::io2d::refresh_rate::as_fast_as_possible, double fps = 30.0);
					display_surface(int preferredWidth, int preferredHeight, ::std::experimental::io2d::format preferredFormat, ::std::error_code& ec,
						::std::experimental::io2d::scaling scl = ::std::experimental::io2d::scaling::letterbox, ::std::experimental::io2d::refresh_rate rr = ::std::experimental::io2d::refresh_rate::as_fast_as_possible, double fps = 30.0) noexcept;

					display_surface(int preferredWidth, int preferredHeight, ::std::experimental::io2d::format preferredFormat,
						int preferredDisplayWidth, int preferredDisplayHeight,
						::std::experimental::io2d::scaling scl = ::std::experimental::io2d::scaling::letterbox, ::std::experimental::io2d::refresh_rate rr = ::std::experimental::io2d::refresh_rate::as_fast_as_possible, double fps = 30.0);
					display_surface(int preferredWidth, int preferredHeight, ::std::experimental::io2d::format preferredFormat,
						int preferredDisplayWidth, int preferredDisplayHeight, ::std::error_code& ec,
						::std::experimental::io2d::scaling scl = ::std::experimental::io2d::scaling::letterbox, ::std::experimental::io2d::refresh_rate rr = ::std::experimental::io2d::refresh_rate::as_fast_as_possible, double fps = 30.0) noexcept;

					virtual ~display_surface();

					virtual void save() override;
					virtual void save(::std::error_code& ec) noexcept override;
					virtual void restore() override;
					virtual void restore(::std::error_code& ec) noexcept override;

					void draw_callback(const ::std::function<void(display_surface& sfc)>& fn);
					void draw_callback(const ::std::function<void(display_surface& sfc)>& fn, ::std::error_code& ec) noexcept;
					void size_change_callback(const ::std::function<void(display_surface& sfc)>& fn);
					void size_change_callback(const ::std::function<void(display_surface& sfc)>& fn, ::std::error_code& ec) noexcept;
					void width(int w);
					void width(int w, ::std::error_code& ec) noexcept;
					void height(int h);
					void height(int h, ::std::error_code& ec) noexcept;
					void display_width(int w);
					void display_width(int w, ::std::error_code& ec) noexcept;
					void display_height(int h);
					void display_height(int h, ::std::error_code& ec) noexcept;
					void dimensions(int w, int h);
					void dimensions(int w, int h, ::std::error_code& ec) noexcept;
					void display_dimensions(int dw, int dh);
					void display_dimensions(int dw, int dh, ::std::error_code& ec) noexcept;
					void scaling(::std::experimental::io2d::scaling scl) noexcept;
					void user_scaling_callback(const ::std::function<::std::experimental::io2d::rectangle(const display_surface&, bool&)>& fn);
					void user_scaling_callback(const ::std::function<::std::experimental::io2d::rectangle(const display_surface&, bool&)>& fn, ::std::error_code& ec) noexcept;
					void letterbox_brush(experimental::io2d::nullvalue_t) noexcept;
					void letterbox_brush(const rgba_color& c);
					void letterbox_brush(const rgba_color& c, ::std::error_code& ec) noexcept;
					void letterbox_brush(const ::std::experimental::io2d::brush& b);
					void letterbox_brush(const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void auto_clear(bool val) noexcept;
					void refresh_rate(::std::experimental::io2d::refresh_rate rr) noexcept;
					bool desired_frame_rate(double fps) noexcept;
					void redraw_required() noexcept;

					int show();
					int show(::std::error_code& ec); // Not noexcept because if the user-provided functions throw they will propagate, but otherwise is non-throwing.
					void exit_show(int ms) noexcept;

					::std::experimental::io2d::format format() const noexcept;
					int width() const noexcept;
					int height() const noexcept;
					int display_width() const noexcept;
					int display_height() const noexcept;
					::std::tuple<int, int> dimensions() const noexcept;
					::std::tuple<int, int> display_dimensions() const noexcept;
					::std::experimental::io2d::scaling scaling() const noexcept;
					::std::function<::std::experimental::io2d::rectangle(const display_surface&, bool&)> user_scaling_callback() const;
					::std::function<::std::experimental::io2d::rectangle(const display_surface&, bool&)> user_scaling_callback(::std::error_code& ec) const noexcept;
					::std::experimental::io2d::brush letterbox_brush() const noexcept;
					bool auto_clear() const noexcept;
					::std::experimental::io2d::refresh_rate refresh_rate() const noexcept;
					double desired_frame_rate() const noexcept;
					double elapsed_draw_time() const noexcept;
				};

				// I don't know why Clang/C2 is complaining about weak vtables here since the at least one virtual function is always anchored but for now silence the warnings. I've never seen this using Clang on OpenSUSE.
#ifdef _WIN32
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif

				int format_stride_for_width(format format, int width) noexcept;
				display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, scaling scl = scaling::letterbox, refresh_rate rr = refresh_rate::as_fast_as_possible, double desiredFramerate = 30.0);
				display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, ::std::error_code& ec, scaling scl = scaling::letterbox, refresh_rate rr = refresh_rate::as_fast_as_possible, double desiredFramerate = 30.0) noexcept;
				display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, scaling scl = scaling::letterbox, refresh_rate rr = refresh_rate::as_fast_as_possible, double desiredFramerate = 30.0);
				display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat,
					int preferredDisplayWidth, int preferredDisplayHeight, ::std::error_code& ec, scaling scl = scaling::letterbox, refresh_rate rr = refresh_rate::as_fast_as_possible, double desiredFramerate = 30.0) noexcept;
				image_surface make_image_surface(format format, int width, int height);
				image_surface make_image_surface(format format, int width, int height, ::std::error_code& ec) noexcept;

				template <class _TItem>
				struct _Path_factory_process_visit {
					constexpr static double twoThirds = 2.0 / 3.0;

					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_move>, _Path_data_abs_move> = _Path_data_abs_move_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint) {
						currentPoint = item.to();
						auto pt = m.transform_point(currentPoint - origin) + origin;
						hasCurrentPoint = true;
						v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
						closePoint = pt;
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint) {
						currentPoint = item.to();
						auto pt = m.transform_point(currentPoint - origin) + origin;
						if (hasCurrentPoint) {
							v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
						}
						else {
							v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
							v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
							hasCurrentPoint = true;
							closePoint = pt;
						}
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint) {
						auto pt1 = m.transform_point(item.control_point_1() - origin) + origin;
						auto pt2 = m.transform_point(item.control_point_2() - origin) + origin;
						auto pt3 = m.transform_point(item.end_point() - origin) + origin;
						if (!hasCurrentPoint) {
							currentPoint = item.control_point_1();
							v.emplace_back(::std::in_place_type<path_data::abs_move>, pt1);
							hasCurrentPoint = true;
							closePoint = pt1;
						}
						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, pt1,
							pt2, pt3);
						currentPoint = item.end_point();
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint) {
						// Turn it into a cubic curve since cairo doesn't have quadratic curves.
						vector_2d beginPt;
						auto controlPt = m.transform_point(item.control_point() - origin) + origin;
						auto endPt = m.transform_point(item.end_point() - origin) + origin;
						if (!hasCurrentPoint) {
							currentPoint = item.control_point();
							v.emplace_back(::std::in_place_type<path_data::abs_move>, controlPt);
							hasCurrentPoint = true;
							closePoint = controlPt;
							beginPt = controlPt;
						}
						else {
							beginPt = m.transform_point(currentPoint - origin) + origin;
						}
						vector_2d cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y() - beginPt.y()) * twoThirds) + beginPt.y() };
						vector_2d cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y() - endPt.y()) * twoThirds) + endPt.y() };
						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1, cpt2, endPt);
						currentPoint = item.end_point();
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::new_path>, _Path_data_new_path> = _Path_data_new_path_val>
					constexpr static void _Perform(const T&, ::std::vector<path_data::path_data_types>&, matrix_2d&, vector_2d&, vector_2d&, bool& hasCurrentPoint, vector_2d&) {
						hasCurrentPoint = false;
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::close_path>, _Path_data_close_path> = _Path_data_close_path_val>
					constexpr static void _Perform(const T&, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint) {
						if (hasCurrentPoint) {
							v.emplace_back(::std::in_place_type<path_data::close_path>, closePoint);
							v.emplace_back(::std::in_place_type<path_data::abs_move>,
								closePoint);
							auto invM = matrix_2d{ m }.invert();
							// Need to assign the untransformed closePoint value to currentPoint.
							currentPoint = invM.transform_point(closePoint - origin) + origin;
						}
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_move>, _Path_data_rel_move> = _Path_data_rel_move_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint) {
						if (!hasCurrentPoint) {
							throw ::std::system_error(::std::make_error_code(io2d_error::invalid_path_data));
						}
						currentPoint = item.to() + currentPoint;
						auto pt = m.transform_point(currentPoint - origin) + origin;
						v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
						hasCurrentPoint = true;
						closePoint = pt;
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d&) {
						if (!hasCurrentPoint) {
							throw ::std::system_error(::std::make_error_code(io2d_error::invalid_path_data));
						}
						currentPoint = item.to() + currentPoint;
						auto pt = m.transform_point(currentPoint - origin) + origin;
						v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d&) {
						if (!hasCurrentPoint) {
							throw ::std::system_error(::std::make_error_code(io2d_error::invalid_path_data));
						}
						auto pt1 = m.transform_point(item.control_point_1() + currentPoint -
							origin) + origin;
						auto pt2 = m.transform_point(item.control_point_2() + currentPoint -
							origin) + origin;
						auto pt3 = m.transform_point(item.end_point() + currentPoint - origin) +
							origin;
						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>,
							pt1, pt2, pt3);
						currentPoint = item.end_point() + currentPoint;
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d&) {
						if (!hasCurrentPoint) {
							throw ::std::system_error(::std::make_error_code(io2d_error::invalid_path_data));
						}
						// Turn it into a cubic curve since cairo doesn't have quadratic curves.
						vector_2d beginPt;
						auto controlPt = m.transform_point(item.control_point() + currentPoint -
							origin) + origin;
						auto endPt = m.transform_point(item.end_point() + currentPoint -
							origin) + origin;
						beginPt = m.transform_point(currentPoint - origin) + origin;
						vector_2d cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y() - beginPt.y()) * twoThirds) + beginPt.y() };
						vector_2d cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y() - endPt.y()) * twoThirds) + endPt.y() };
						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1, cpt2, endPt);
						currentPoint = item.end_point() + currentPoint;
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::arc_clockwise>, _Path_data_arc_clockwise> = _Path_data_arc_clockwise_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint) {
						{
							auto ctr = item.center();
							auto rad = item.radius();
							auto ang1 = item.angle_1();
							auto ang2 = item.angle_2();
							while (ang2 < ang1) {
								ang2 += two_pi<double>;
							}
							vector_2d pt0, pt1, pt2, pt3;
							int bezCount = 1;
							double theta = ang2 - ang1;
							double phi{};
#if _Variable_templates_conditional_support_test
							while (theta >= half_pi<double>) {
#else
							while (theta >= half_pi<double>()) {
#endif
								theta /= 2.0;
								bezCount += bezCount;
							}
							phi = theta / 2.0;
							auto cosPhi = cos(phi);
							auto sinPhi = sin(phi);
							pt0.x(cosPhi);
							pt0.y(-sinPhi);
							pt3.x(pt0.x());
							pt3.y(-pt0.y());
							pt1.x((4.0 - cosPhi) / 3.0);
							pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
							pt2.x(pt1.x());
							pt2.y(-pt1.y());
							phi = -phi;
							auto rotCwFn = [](const vector_2d& pt, double a) -> vector_2d {
								return { pt.x() * cos(a) + pt.y() * sin(a),
									-(pt.x() * -(sin(a)) + pt.y() * cos(a)) };
							};
							pt0 = rotCwFn(pt0, phi);
							pt1 = rotCwFn(pt1, phi);
							pt2 = rotCwFn(pt2, phi);
							pt3 = rotCwFn(pt3, phi);

							auto currTheta = ang1;
							const auto startPt =
								ctr + rotCwFn({ pt0.x() * rad, pt0.y() * rad }, currTheta);
							if (hasCurrentPoint) {
								currentPoint = startPt;
								auto pt = m.transform_point(currentPoint - origin) + origin;
								v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
							}
							else {
								currentPoint = startPt;
								auto pt = m.transform_point(currentPoint - origin) + origin;
								v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
								hasCurrentPoint = true;
								closePoint = pt;
							}
							for (; bezCount > 0; bezCount--) {
								auto cpt1 = ctr + rotCwFn({ pt1.x() * rad, pt1.y() * rad }, currTheta);
								auto cpt2 = ctr + rotCwFn({ pt2.x() * rad, pt2.y() * rad },
									currTheta);
								auto cpt3 = ctr + rotCwFn({ pt3.x() * rad, pt3.y() * rad },
									currTheta);
								currentPoint = cpt3;
								cpt1 = m.transform_point(cpt1 - origin) + origin;
								cpt2 = m.transform_point(cpt2 - origin) + origin;
								cpt3 = m.transform_point(cpt3 - origin) + origin;
								v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1,
									cpt2, cpt3);
								currTheta += theta;
							}
						}
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::arc_counterclockwise>, _Path_data_arc_counterclockwise> = _Path_data_arc_counterclockwise_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint) {
						{
							auto ctr = item.center();
							auto rad = item.radius();
							auto ang1 = item.angle_1();
							auto ang2 = item.angle_2();
							while (ang2 > ang1) {
								ang2 -= two_pi<double>;
							}
							vector_2d pt0, pt1, pt2, pt3;
							int bezCount = 1;
							double theta = ang1 - ang2;
							double phi{};
#if _Variable_templates_conditional_support_test
							while (theta >= half_pi<double>) {
#else
							while (theta >= half_pi<double>()) {
#endif
								theta /= 2.0;
								bezCount += bezCount;
							}
							phi = theta / 2.0;
							auto cosPhi = cos(phi);
							auto sinPhi = sin(phi);
							pt0.x(cosPhi);
							pt0.y(-sinPhi);
							pt3.x(pt0.x());
							pt3.y(-pt0.y());
							pt1.x((4.0 - cosPhi) / 3.0);
							pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
							pt2.x(pt1.x());
							pt2.y(-pt1.y());
							auto rotCwFn = [](const vector_2d& pt, double a) -> vector_2d {
								return { pt.x() * cos(a) + pt.y() * sin(a),
									-(pt.x() * -(sin(a)) + pt.y() * cos(a)) };
							};
							pt0 = rotCwFn(pt0, phi);
							pt1 = rotCwFn(pt1, phi);
							pt2 = rotCwFn(pt2, phi);
							pt3 = rotCwFn(pt3, phi);
							auto shflPt = pt3;
							pt3 = pt0;
							pt0 = shflPt;
							shflPt = pt2;
							pt2 = pt1;
							pt1 = shflPt;
							auto currTheta = ang1;
							const auto startPt =
								ctr + rotCwFn({ pt0.x() * rad, pt0.y() * rad }, currTheta);
							if (hasCurrentPoint) {
								currentPoint = startPt;
								auto pt = m.transform_point(currentPoint - origin) + origin;
								v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
							}
							else {
								currentPoint = startPt;
								auto pt = m.transform_point(currentPoint - origin) + origin;
								v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
								hasCurrentPoint = true;
								closePoint = pt;
							}
							for (; bezCount > 0; bezCount--) {
								auto cpt1 = ctr + rotCwFn({ pt1.x() * rad, pt1.y() * rad },
									currTheta);
								auto cpt2 = ctr + rotCwFn({ pt2.x() * rad, pt2.y() * rad },
									currTheta);
								auto cpt3 = ctr + rotCwFn({ pt3.x() * rad, pt3.y() * rad },
									currTheta);
								currentPoint = cpt3;
								cpt1 = m.transform_point(cpt1 - origin) + origin;
								cpt2 = m.transform_point(cpt2 - origin) + origin;
								cpt3 = m.transform_point(cpt3 - origin) + origin;
								v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1,
									cpt2, cpt3);
								currTheta -= theta;
							}
						}
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::change_matrix>, _Path_data_change_matrix> = _Path_data_change_matrix_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>&, matrix_2d& m, vector_2d&, vector_2d&, bool&, vector_2d&) {
						m = item.matrix();
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::change_origin>, _Path_data_change_origin> = _Path_data_change_origin_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>&, matrix_2d&, vector_2d& origin, vector_2d&, bool&, vector_2d&) {
						origin = item.origin();
					}
				};

				template <class Allocator>
				::std::vector<path_data::path_data_types> _Process_path_data(const path_factory<Allocator>& pf) {
					matrix_2d m;
					vector_2d origin;
					vector_2d currentPoint; // Tracks the untransformed current point.
					bool hasCurrentPoint = false;
					vector_2d closePoint;   // Tracks the transformed close point.
					::std::vector<path_data::path_data_types> v;

					for (const path_data::path_data_types& val : pf) {
						::std::visit([&m, &origin, &currentPoint, &hasCurrentPoint, &closePoint, &v](auto&& item) {
							using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
							_Path_factory_process_visit<T>::template _Perform<T>(item, v, m, origin, currentPoint, hasCurrentPoint, closePoint);
						}, val);
					}
					return v;
				}

				template <class _TItem>
				struct _Path_factory_process_visit_noexcept {
					constexpr static double twoThirds = 2.0 / 3.0;

					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_move>, _Path_data_abs_move> = _Path_data_abs_move_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint, ::std::error_code&) noexcept {
						currentPoint = item.to();
						auto pt = m.transform_point(currentPoint - origin) + origin;
						hasCurrentPoint = true;
						v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
						closePoint = pt;
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint, ::std::error_code&) noexcept {
						currentPoint = item.to();
						auto pt = m.transform_point(currentPoint - origin) + origin;
						if (hasCurrentPoint) {
							v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
						}
						else {
							v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
							v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
							hasCurrentPoint = true;
							closePoint = pt;
						}
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint, ::std::error_code&) noexcept {
						auto pt1 = m.transform_point(item.control_point_1() - origin) + origin;
						auto pt2 = m.transform_point(item.control_point_2() - origin) + origin;
						auto pt3 = m.transform_point(item.end_point() - origin) + origin;
						if (!hasCurrentPoint) {
							currentPoint = item.control_point_1();
							v.emplace_back(::std::in_place_type<path_data::abs_move>, pt1);
							hasCurrentPoint = true;
							closePoint = pt1;
						}
						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, pt1,
							pt2, pt3);
						currentPoint = item.end_point();
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint, ::std::error_code&) noexcept {
						// Turn it into a cubic curve since cairo doesn't have quadratic curves.
						vector_2d beginPt;
						auto controlPt = m.transform_point(item.control_point() - origin) + origin;
						auto endPt = m.transform_point(item.end_point() - origin) + origin;
						if (!hasCurrentPoint) {
							currentPoint = item.control_point();
							v.emplace_back(::std::in_place_type<path_data::abs_move>, controlPt);
							hasCurrentPoint = true;
							closePoint = controlPt;
							beginPt = controlPt;
						}
						else {
							beginPt = m.transform_point(currentPoint - origin) + origin;
						}
						vector_2d cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y - beginPt.y()) * twoThirds) + beginPt.y() };
						vector_2d cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y - endPt.y()) * twoThirds) + endPt.y() };
						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1, cpt2, endPt);
						currentPoint = item.end_point();
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::new_path>, _Path_data_new_path> = _Path_data_new_path_val>
					constexpr static void _Perform(const T&, ::std::vector<path_data::path_data_types>&, matrix_2d&, vector_2d&, vector_2d&, bool& hasCurrentPoint, vector_2d&, ::std::error_code&) noexcept {
						hasCurrentPoint = false;
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::close_path>, _Path_data_close_path> = _Path_data_close_path_val>
					constexpr static void _Perform(const T&, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint, ::std::error_code&) noexcept {
						if (hasCurrentPoint) {
							v.emplace_back(::std::in_place_type<path_data::close_path>, closePoint);
							v.emplace_back(::std::in_place_type<path_data::abs_move>,
								closePoint);
							auto invM = matrix_2d{ m }.invert();
							// Need to assign the untransformed closePoint value to currentPoint.
							currentPoint = invM.transform_point(closePoint - origin) + origin;
						}
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_move>, _Path_data_rel_move> = _Path_data_rel_move_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint, ::std::error_code& ec) noexcept {
						if (!hasCurrentPoint) {
							ec = ::std::make_error_code(io2d_error::invalid_path_data);
							return;
						}
						currentPoint = item.to() + currentPoint;
						auto pt = m.transform_point(currentPoint - origin) + origin;
						v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
						hasCurrentPoint = true;
						closePoint = pt;
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d&, ::std::error_code& ec) noexcept {
						if (!hasCurrentPoint) {
							ec = ::std::make_error_code(io2d_error::invalid_path_data);
							return;
						}
						currentPoint = item.to() + currentPoint;
						auto pt = m.transform_point(currentPoint - origin) + origin;
						v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d&, ::std::error_code& ec) noexcept {
						if (!hasCurrentPoint) {
							ec = ::std::make_error_code(io2d_error::invalid_path_data);
							return;
						}
						auto pt1 = m.transform_point(item.control_point_1() + currentPoint -
							origin) + origin;
						auto pt2 = m.transform_point(item.control_point_2() + currentPoint -
							origin) + origin;
						auto pt3 = m.transform_point(item.end_point() + currentPoint - origin) +
							origin;
						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>,
							pt1, pt2, pt3);
						currentPoint = item.end_point() + currentPoint;
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d&, ::std::error_code& ec) noexcept {
						if (!hasCurrentPoint) {
							ec = ::std::make_error_code(io2d_error::invalid_path_data);
							return;
						}
						// Turn it into a cubic curve since cairo doesn't have quadratic curves.
						vector_2d beginPt;
						auto controlPt = m.transform_point(item.control_point() + currentPoint -
							origin) + origin;
						auto endPt = m.transform_point(item.end_point() + currentPoint -
							origin) + origin;
						beginPt = m.transform_point(currentPoint - origin) + origin;
						vector_2d cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y - beginPt.y()) * twoThirds) + beginPt.y() };
						vector_2d cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y - endPt.y()) * twoThirds) + endPt.y() };
						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1, cpt2, endPt);
						currentPoint = item.end_point() + currentPoint;
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::arc_clockwise>, _Path_data_arc_clockwise> = _Path_data_arc_clockwise_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint, ::std::error_code&) noexcept {
						{
							auto ctr = item.center();
							auto rad = item.radius();
							auto ang1 = item.angle_1();
							auto ang2 = item.angle_2();
							while (ang2 < ang1) {
								ang2 += two_pi<double>;
							}
							vector_2d pt0, pt1, pt2, pt3;
							int bezCount = 1;
							double theta = ang2 - ang1;
							double phi{};
#if _Variable_templates_conditional_support_test
							while (theta >= half_pi<double>) {
#else
							while (theta >= half_pi<double>()) {
#endif
								theta /= 2.0;
								bezCount += bezCount;
							}
							phi = theta / 2.0;
							auto cosPhi = cos(phi);
							auto sinPhi = sin(phi);
							pt0.x(cosPhi);
							pt0.y(-sinPhi);
							pt3.x(pt0.x());
							pt3.y(-pt0.y());
							pt1.x((4.0 - cosPhi) / 3.0);
							pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
							pt2.x(pt1.x());
							pt2.y(-pt1.y());
							phi = -phi;
							auto rotCwFn = [](const vector_2d& pt, double a) -> vector_2d {
								return { pt.x() * cos(a) + pt.y() * sin(a),
									-(pt.x() * -(sin(a)) + pt.y() * cos(a)) };
							};
							pt0 = rotCwFn(pt0, phi);
							pt1 = rotCwFn(pt1, phi);
							pt2 = rotCwFn(pt2, phi);
							pt3 = rotCwFn(pt3, phi);

							auto currTheta = ang1;
							const auto startPt =
								ctr + rotCwFn({ pt0.x() * rad, pt0.y() * rad }, currTheta);
							if (hasCurrentPoint) {
								currentPoint = startPt;
								auto pt = m.transform_point(currentPoint - origin) + origin;
								v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
							}
							else {
								currentPoint = startPt;
								auto pt = m.transform_point(currentPoint - origin) + origin;
								v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
								hasCurrentPoint = true;
								closePoint = pt;
							}
							for (; bezCount > 0; bezCount--) {
								auto cpt1 = ctr + rotCwFn({ pt1.x() * rad, pt1.y() * rad }, currTheta);
								auto cpt2 = ctr + rotCwFn({ pt2.x() * rad, pt2.y() * rad },
									currTheta);
								auto cpt3 = ctr + rotCwFn({ pt3.x() * rad, pt3.y() * rad },
									currTheta);
								currentPoint = cpt3;
								cpt1 = m.transform_point(cpt1 - origin) + origin;
								cpt2 = m.transform_point(cpt2 - origin) + origin;
								cpt3 = m.transform_point(cpt3 - origin) + origin;
								v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1,
									cpt2, cpt3);
								currTheta += theta;
							}
						}
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::arc_counterclockwise>, _Path_data_arc_counterclockwise> = _Path_data_arc_counterclockwise_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>& v, matrix_2d& m, vector_2d& origin, vector_2d& currentPoint, bool& hasCurrentPoint, vector_2d& closePoint, ::std::error_code&) noexcept {
						{
							auto ctr = item.center();
							auto rad = item.radius();
							auto ang1 = item.angle_1();
							auto ang2 = item.angle_2();
							while (ang2 > ang1) {
								ang2 -= two_pi<double>;
							}
							vector_2d pt0, pt1, pt2, pt3;
							int bezCount = 1;
							double theta = ang1 - ang2;
							double phi{};
#if _Variable_templates_conditional_support_test
							while (theta >= half_pi<double>) {
#else
							while (theta >= half_pi<double>()) {
#endif
								theta /= 2.0;
								bezCount += bezCount;
							}
							phi = theta / 2.0;
							auto cosPhi = cos(phi);
							auto sinPhi = sin(phi);
							pt0.x(cosPhi);
							pt0.y(-sinPhi);
							pt3.x(pt0.x());
							pt3.y(-pt0.y());
							pt1.x((4.0 - cosPhi) / 3.0);
							pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
							pt2.x(pt1.x());
							pt2.y(-pt1.y());
							auto rotCwFn = [](const vector_2d& pt, double a) -> vector_2d {
								return { pt.x() * cos(a) + pt.y() * sin(a),
									-(pt.x() * -(sin(a)) + pt.y() * cos(a)) };
							};
							pt0 = rotCwFn(pt0, phi);
							pt1 = rotCwFn(pt1, phi);
							pt2 = rotCwFn(pt2, phi);
							pt3 = rotCwFn(pt3, phi);
							auto shflPt = pt3;
							pt3 = pt0;
							pt0 = shflPt;
							shflPt = pt2;
							pt2 = pt1;
							pt1 = shflPt;
							auto currTheta = ang1;
							const auto startPt =
								ctr + rotCwFn({ pt0.x() * rad, pt0.y() * rad }, currTheta);
							if (hasCurrentPoint) {
								currentPoint = startPt;
								auto pt = m.transform_point(currentPoint - origin) + origin;
								v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
							}
							else {
								currentPoint = startPt;
								auto pt = m.transform_point(currentPoint - origin) + origin;
								v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
								hasCurrentPoint = true;
								closePoint = pt;
							}
							for (; bezCount > 0; bezCount--) {
								auto cpt1 = ctr + rotCwFn({ pt1.x() * rad, pt1.y() * rad },
									currTheta);
								auto cpt2 = ctr + rotCwFn({ pt2.x() * rad, pt2.y() * rad },
									currTheta);
								auto cpt3 = ctr + rotCwFn({ pt3.x() * rad, pt3.y() * rad },
									currTheta);
								currentPoint = cpt3;
								cpt1 = m.transform_point(cpt1 - origin) + origin;
								cpt2 = m.transform_point(cpt2 - origin) + origin;
								cpt3 = m.transform_point(cpt3 - origin) + origin;
								v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1,
									cpt2, cpt3);
								currTheta -= theta;
							}
						}
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::change_matrix>, _Path_data_change_matrix> = _Path_data_change_matrix_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>&, matrix_2d& m, vector_2d&, vector_2d&, bool&, vector_2d&, ::std::error_code&) noexcept {
						m = item.matrix();
					}
					template <class T, ::std::enable_if_t<::std::is_same_v<T, path_data::change_origin>, _Path_data_change_origin> = _Path_data_change_origin_val>
					constexpr static void _Perform(const T& item, ::std::vector<path_data::path_data_types>&, matrix_2d&, vector_2d& origin, vector_2d&, bool&, vector_2d&, ::std::error_code&) noexcept {
						origin = item.origin();
					}
				};

				template <class Allocator>
				::std::vector<path_data::path_data_types> _Process_path_data(const path_factory<Allocator>& pf, ::std::error_code& ec) {
					matrix_2d m;
					vector_2d origin;
					vector_2d currentPoint; // Tracks the untransformed current point.
					bool hasCurrentPoint = false;
					vector_2d closePoint;   // Tracks the transformed close point.
					::std::vector<path_data::path_data_types> v;

					for (const path_data::path_data_types& val : pf) {
						::std::visit([&m, &origin, &currentPoint, &hasCurrentPoint, &closePoint, &v](auto&& item) {
							using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
							_Path_factory_process_visit_noexcept<T>::template _Perform<T>(item, v, m, origin, currentPoint, hasCurrentPoint, closePoint, ec);
						}, val);
						if (static_cast<bool>(ec)) {
							v.clear();
							return v;
						}
					}
					return v;
				}

				//template <class Allocator>
				//::std::vector<path_data::path_data_types> _Process_path_data(const path_factory<Allocator>& pf) {
				//	matrix_2d m;
				//	vector_2d origin;
				//	vector_2d currentPoint; // Tracks the untransformed current point.
				//	bool hasCurrentPoint = false;
				//	vector_2d closePoint;   // Tracks the transformed close point.
				//	::std::vector<path_data::path_data_types> v;
				//	constexpr double twoThirds = 2.0 / 3.0;

				//	for (const path_data::path_data_types& val : pf) {
				//		::std::visit([&m, &origin, &currentPoint, &hasCurrentPoint, &closePoint, &v](auto&& item) {
				//			using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;

				//			if (::std::is_same_v<T, path_data::abs_move>) {
				//				currentPoint = item.to();
				//				auto pt = m.transform_point(currentPoint - origin) + origin;
				//				hasCurrentPoint = true;
				//				v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
				//				closePoint = pt;
				//			}
				//			else if (::std::is_same_v<T, path_data::abs_line>) {
				//				currentPoint = item.to();
				//				auto pt = m.transform_point(currentPoint - origin) + origin;
				//				if (hasCurrentPoint) {
				//					v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
				//				}
				//				else {
				//					v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
				//					v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
				//					hasCurrentPoint = true;
				//					closePoint = pt;
				//				}
				//			}
				//			else if (::std::is_same_v<T, path_data::abs_cubic_curve>) {
				//				auto pt1 = m.transform_point(item.control_point_1() - origin) + origin;
				//				auto pt2 = m.transform_point(item.control_point_2() - origin) + origin;
				//				auto pt3 = m.transform_point(item.end_point() - origin) + origin;
				//				if (!hasCurrentPoint) {
				//					currentPoint = item.control_point_1();
				//					v.emplace_back(::std::in_place_type<path_data::abs_move>, pt1);
				//					hasCurrentPoint = true;
				//					closePoint = pt1;
				//				}
				//				v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, pt1,
				//					pt2, pt3);
				//				currentPoint = item.end_point();
				//			}
				//			else if (::std::is_same_v<T,
				//				path_data::abs_quadratic_curve>) {
				//				// Turn it into a cubic curve since cairo doesn't have quadratic curves.
				//				vector_2d beginPt;
				//				auto controlPt = m.transform_point(item.control_point() - origin) + origin;
				//				auto endPt = m.transform_point(item.end_point() - origin) + origin;
				//				if (!hasCurrentPoint) {
				//					currentPoint = item.control_point();
				//					v.emplace_back(::std::in_place_type<path_data::abs_move>, pt1);
				//					hasCurrentPoint = true;
				//					closePoint = pt1;
				//					beginPt = controlPt;
				//				}
				//				else {
				//					beginPt = m.transform_point(currentPoint - origin) + origin;
				//				}
				//				auto cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y - beginPt.y()) * twoThirds) + beginPt.y() };
				//				auto cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y - endPt.y()) * twoThirds) + endPt.y() };
				//				v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1, cpt2, endPt);
				//				currentPoint = item.end_point();
				//			}
				//			else if (::std::is_same_v<T, path_data::new_path>) {
				//				hasCurrentPoint = false;
				//				//v.emplace_back(::std::in_place_type<path_data::new_path>);
				//			}
				//			else if (::std::is_same_v<T, path_data::close_path>) {
				//				if (hasCurrentPoint) {
				//					v.emplace_back(::std::in_place_type<path_data::close_path>, closePoint);
				//					v.emplace_back(::std::in_place_type<path_data::abs_move>,
				//						closePoint);
				//					auto invM = matrix_2d{ m }.invert();
				//					// Need to assign the untransformed closePoint value to currentPoint.
				//					currentPoint = invM.transform_point(closePoint - origin) + origin;
				//				}
				//			}
				//			else if (::std::is_same_v<T, path_data::rel_move>) {
				//				if (!hasCurrentPoint) {
				//					throw ::std::system_error(::std::make_error_code(io2d_error::invalid_path_data));
				//				}
				//				currentPoint = item.to() + currentPoint;
				//				auto pt = m.transform_point(currentPoint - origin) + origin;
				//				v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
				//				hasCurrentPoint = true;
				//				closePoint = pt;
				//				n.close_point(pt);
				//			}
				//			else if (::std::is_same_v<T, path_data::rel_line>) {
				//				if (!hasCurrentPoint) {
				//					throw ::std::system_error(::std::make_error_code(io2d_error::invalid_path_data));
				//				}
				//				currentPoint = item.to() + currentPoint;
				//				auto pt = m.transform_point(currentPoint - origin) + origin;
				//				v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
				//			}
				//			else if (::std::is_same_v<T, path_data::rel_cubic_curve>) {
				//				if (!hasCurrentPoint) {
				//					throw ::std::system_error(::std::make_error_code(io2d_error::invalid_path_data));
				//				}
				//				auto pt1 = m.transform_point(item.control_point_1() + currentPoint -
				//					origin) + origin;
				//				auto pt2 = m.transform_point(item.control_point_2() + currentPoint -
				//					origin) + origin;
				//				auto pt3 = m.transform_point(item.end_point() + currentPoint - origin) +
				//					origin;
				//				v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>,
				//					pt1, pt2, pt3);
				//				currentPoint = item.end_point() + currentPoint;
				//			}
				//			else if (::std::is_same_v<T,
				//				path_data::rel_quadratic_curve>) {
				//				if (!hasCurrentPoint) {
				//					throw ::std::system_error(::std::make_error_code(io2d_error::invalid_path_data));
				//				}
				//				// Turn it into a cubic curve since cairo doesn't have quadratic curves.
				//				vector_2d beginPt;
				//				auto controlPt = m.transform_point(item.control_point() + currentPoint -
				//					origin) + origin;
				//				auto endPt = m.transform_point(item.end_point() + currentPoint -
				//					origin) + origin;
				//				beginPt = m.transform_point(currentPoint - origin) + origin;
				//				auto cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y - beginPt.y()) * twoThirds) + beginPt.y() };
				//				auto cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y - endPt.y()) * twoThirds) + endPt.y() };
				//				v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1, cpt2, endPt);
				//				currentPoint = item.end_point() + currentPoint;
				//			}
				//			else if (::std::is_same_v<T, path_data::arc_clockwise>) {
				//				{
				//					auto ctr = item.center();
				//					auto rad = item.radius();
				//					auto ang1 = item.angle_1();
				//					auto ang2 = item.angle_2();
				//					while (ang2 < ang1) {
				//						ang2 += two_pi<double>;
				//					}
				//					vector_2d pt0, pt1, pt2, pt3;
				//					int bezCount = 1;
				//					double theta = ang2 - ang1;
				//					double phi;
				//					while (theta >= halfpi) {
				//						theta /= 2.0;
				//						bezCount += bezCount;
				//					}
				//					phi = theta / 2.0;
				//					auto cosPhi = cos(phi);
				//					auto sinPhi = sin(phi);
				//					pt0.x(cosPhi);
				//					pt0.y(-sinPhi);
				//					pt3.x(pt0.x());
				//					pt3.y(-pt0.y());
				//					pt1.x((4.0 - cosPhi) / 3.0);
				//					pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
				//					pt2.x(pt1.x());
				//					pt2.y(-pt1.y());
				//					phi = -phi;
				//					auto rotCwFn = [](const vector_2d& pt, double a) -> vector_2d {
				//						return { pt.x() * cos(a) + pt.y() * sin(a),
				//							-(pt.x() * -(sin(a)) + pt.y() * cos(a)) };
				//					};
				//					pt0 = rotCwFn(pt0, phi);
				//					pt1 = rotCwFn(pt1, phi);
				//					pt2 = rotCwFn(pt2, phi);
				//					pt3 = rotCwFn(pt3, phi);

				//					auto currTheta = ang1;
				//					const auto startPt =
				//						ctr + rotCwFn({ pt0.x() * rad, pt0.y() * rad }, currTheta);
				//					if (hasCurrentPoint) {
				//						currentPoint = startPt;
				//						auto pt = m.transform_point(currentPoint - origin) + origin;
				//						v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
				//					}
				//					else {
				//						currentPoint = startPt;
				//						auto pt = m.transform_point(currentPoint - origin) + origin;
				//						v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
				//						hasCurrentPoint = true;
				//						closePt = pt;
				//					}
				//					for (; bezCount > 0; bezCount--) {
				//						auto cpt1 = ctr + rotCwFn({ pt1.x() * rad, pt1.y() * rad }, currTheta);
				//						auto cpt2 = ctr + rotCwFn({ pt2.x() * rad, pt2.y() * rad },
				//							currTheta);
				//						auto cpt3 = ctr + rotCwFn({ pt3.x() * rad, pt3.y() * rad },
				//							currTheta);
				//						currentPoint = cpt3;
				//						cpt1 = m.transform_point(cpt1 - origin) + origin;
				//						cpt2 = m.transform_point(cpt2 - origin) + origin;
				//						cpt3 = m.transform_point(cpt3 - origin) + origin;
				//						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1,
				//							cpt2, cpt3);
				//						currTheta += theta;
				//					}
				//				}
				//			}
				//			else if (::std::is_same_v<T, path_data::arc_counterclockwise>) {
				//				{
				//					auto ctr = item.center();
				//					auto rad = item.radius();
				//					auto ang1 = item.angle_1();
				//					auto ang2 = item.angle_2();
				//					while (ang2 > ang1) {
				//						ang2 -= two_pi<double>;
				//					}
				//					vector_2d pt0, pt1, pt2, pt3;
				//					int bezCount = 1;
				//					double theta = ang1 - ang2;
				//					double phi;
				//					while (theta >= halfpi) {
				//						theta /= 2.0;
				//						bezCount += bezCount;
				//					}
				//					phi = theta / 2.0;
				//					auto cosPhi = cos(phi);
				//					auto sinPhi = sin(phi);
				//					pt0.x(cosPhi);
				//					pt0.y(-sinPhi);
				//					pt3.x(pt0.x());
				//					pt3.y(-pt0.y());
				//					pt1.x((4.0 - cosPhi) / 3.0);
				//					pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
				//					pt2.x(pt1.x());
				//					pt2.y(-pt1.y());
				//					auto rotCwFn = [](const vector_2d& pt, double a) -> vector_2d {
				//						return { pt.x() * cos(a) + pt.y() * sin(a),
				//							-(pt.x() * -(sin(a)) + pt.y() * cos(a)) };
				//					};
				//					pt0 = rotCwFn(pt0, phi);
				//					pt1 = rotCwFn(pt1, phi);
				//					pt2 = rotCwFn(pt2, phi);
				//					pt3 = rotCwFn(pt3, phi);
				//					auto shflPt = pt3;
				//					pt3 = pt0;
				//					pt0 = shflPt;
				//					shflPt = pt2;
				//					pt2 = pt1;
				//					pt1 = shflPt;
				//					auto currTheta = ang1;
				//					const auto startPt =
				//						ctr + rotCwFn({ pt0.x() * rad, pt0.y() * rad }, currTheta);
				//					if (hasCurrentPoint) {
				//						currentPoint = startPt;
				//						auto pt = m.transform_point(currentPoint - origin) + origin;
				//						v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
				//					}
				//					else {
				//						currentPoint = startPt;
				//						auto pt = m.transform_point(currentPoint - origin) + origin;
				//						v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
				//						hasCurrentPoint = true;
				//						closePt = pt;
				//					}
				//					for (; bezCount > 0; bezCount--) {
				//						auto cpt1 = ctr + rotCwFn({ pt1.x() * rad, pt1.y() * rad },
				//							currTheta);
				//						auto cpt2 = ctr + rotCwFn({ pt2.x() * rad, pt2.y() * rad },
				//							currTheta);
				//						auto cpt3 = ctr + rotCwFn({ pt3.x() * rad, pt3.y() * rad },
				//							currTheta);
				//						currentPoint = cpt3;
				//						cpt1 = m.transform_point(cpt1 - origin) + origin;
				//						cpt2 = m.transform_point(cpt2 - origin) + origin;
				//						cpt3 = m.transform_point(cpt3 - origin) + origin;
				//						v.emplace_back(::std::in_place_type<path_data::cubic_curve_to>, cpt1,
				//							cpt2, cpt3);
				//						currTheta -= theta;
				//					}
				//				}
				//			}
				//			else if (::std::is_same_v<T, path_data::change_matrix>) {
				//				m = item.matrix();
				//			}
				//			else if (::std::is_same_v<T, path_data::change_origin>) {
				//				origin = item.origin();
				//			}
				//		}, val);
				//	}
				//	return v;
				//}

				//template <class Allocator>
				//::std::vector<path_data::path_data_types> _Process_path_data(const path_factory<Allocator>& pf, ::std::error_code& ec) noexcept {
				//	matrix_2d m;
				//	vector_2d origin;
				//	vector_2d currentPoint; // Tracks the untransformed current point.
				//	bool hasCurrentPoint = false;
				//	vector_2d closePoint;   // Tracks the transformed close point.
				//	::std::vector<path_data::path_data_types> v;
				//	constexpr double twoThirds = 2.0 / 3.0;

				//	for (const path_data::path_data_types& val : pf) {
				//		::std::visit([&m, &origin, &currentPoint, &hasCurrentPoint, &closePoint, &v](auto&& item) {
				//			using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;

				//			if (::std::is_same_v<T, path_data::abs_move>) {
				//				currentPoint = item.to();
				//				auto pt = m.transform_point(currentPoint - origin) + origin;
				//				hasCurrentPoint = true;
				//				v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
				//				closePoint = pt;
				//			}
				//			else if (::std::is_same_v<T, path_data::abs_line>) {
				//				currentPoint = item.to();
				//				auto pt = m.transform_point(currentPoint - origin) + origin;
				//				if (hasCurrentPoint) {
				//					v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
				//				}
				//				else {
				//					v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
				//					v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
				//					hasCurrentPoint = true;
				//					closePoint = pt;
				//				}
				//			}
				//			else if (::std::is_same_v<T, path_data::abs_cubic_curve>) {
				//				auto pt1 = m.transform_point(item.control_point_1() - origin) + origin;
				//				auto pt2 = m.transform_point(item.control_point_2() - origin) + origin;
				//				auto pt3 = m.transform_point(item.end_point() - origin) + origin;
				//				if (!hasCurrentPoint) {
				//					currentPoint = item.control_point_1();
				//					v.emplace_back(in_place_type<path_data::abs_move>, pt1);
				//					hasCurrentPoint = true;
				//					closePoint = pt1;
				//				}
				//				v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, pt1,
				//					pt2, pt3);
				//				currentPoint = item.end_point();
				//			}
				//			else if (::std::is_same_v<T,
				//				path_data::abs_quadratic_curve>) {
				//				// Turn it into a cubic curve since cairo doesn't have quadratic curves.
				//				vector_2d beginPt;
				//				auto controlPt = m.transform_point(item.control_point() - origin) + origin;
				//				auto endPt = m.transform_point(item.end_point() - origin) + origin;
				//				if (!hasCurrentPoint) {
				//					currentPoint = item.control_point();
				//					v.emplace_back(::std::in_place_type<path_data::abs_move>, pt1);
				//					hasCurrentPoint = true;
				//					closePoint = pt1;
				//					beginPt = controlPt;
				//				}
				//				else {
				//					beginPt = m.transform_point(currentPoint - origin) + origin;
				//				}
				//				auto cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y - beginPt.y()) * twoThirds) + beginPt.y() };
				//				auto cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y - endPt.y()) * twoThirds) + endPt.y() };
				//				v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1, cpt2, endPt);
				//				currentPoint = item.end_point();
				//			}
				//			else if (::std::is_same_v<T, path_data::new_path>) {
				//				hasCurrentPoint = false;
				//				//v.emplace_back(::std::in_place_type<path_data::new_path>);
				//			}
				//			else if (::std::is_same_v<T, path_data::close_path>) {
				//				if (hasCurrentPoint) {
				//					v.emplace_back(::std::in_place_type<path_data::close_path>, closePoint);
				//					v.emplace_back(::std::in_place_type<path_data::abs_move>,
				//						closePoint);
				//					auto invM = matrix_2d{ m }.invert();
				//					// Need to assign the untransformed closePoint value to currentPoint.
				//					currentPoint = invM.transform_point(closePoint - origin) + origin;
				//				}
				//			}
				//			else if (::std::is_same_v<T, path_data::rel_move>) {
				//				if (!hasCurrentPoint) {
				//					ec = ::std::make_error_code(io2d_error::invalid_path_data);
				//					v.clear();
				//					return v;
				//				}
				//				currentPoint = item.to() + currentPoint;
				//				auto pt = m.transform_point(currentPoint - origin) + origin;
				//				v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
				//				hasCurrentPoint = true;
				//				closePoint = pt;
				//				n.close_point(pt);
				//			}
				//			else if (::std::is_same_v<T, path_data::rel_line>) {
				//				if (!hasCurrentPoint) {
				//					ec = ::std::make_error_code(io2d_error::invalid_path_data);
				//					v.clear();
				//					return v;
				//				}
				//				currentPoint = item.to() + currentPoint;
				//				auto pt = m.transform_point(currentPoint - origin) + origin;
				//				v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
				//			}
				//			else if (::std::is_same_v<T, path_data::rel_cubic_curve>) {
				//				if (!hasCurrentPoint) {
				//					ec = ::std::make_error_code(io2d_error::invalid_path_data);
				//					v.clear();
				//					return v;
				//				}
				//				auto pt1 = m.transform_point(item.control_point_1() + currentPoint -
				//					origin) + origin;
				//				auto pt2 = m.transform_point(item.control_point_2() + currentPoint -
				//					origin) + origin;
				//				auto pt3 = m.transform_point(item.end_point() + currentPoint - origin) +
				//					origin;
				//				v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>,
				//					pt1, pt2, pt3);
				//				currentPoint = item.end_point() + currentPoint;
				//			}
				//			else if (::std::is_same_v<T,
				//				path_data::rel_quadratic_curve>) {
				//				if (!hasCurrentPoint) {
				//					ec = ::std::make_error_code(io2d_error::invalid_path_data);
				//					v.clear();
				//					return v;
				//				}
				//				// Turn it into a cubic curve since cairo doesn't have quadratic curves.
				//				vector_2d beginPt;
				//				auto controlPt = m.transform_point(item.control_point() + currentPoint -
				//					origin) + origin;
				//				auto endPt = m.transform_point(item.end_point() + currentPoint -
				//					origin) + origin;
				//				beginPt = m.transform_point(currentPoint - origin) + origin;
				//				auto cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y - beginPt.y()) * twoThirds) + beginPt.y() };
				//				auto cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y - endPt.y()) * twoThirds) + endPt.y() };
				//				v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1, cpt2, endPt);
				//				currentPoint = item.end_point() + currentPoint;
				//			}
				//			else if (::std::is_same_v<T, path_data::arc_clockwise>) {
				//				{
				//					auto ctr = item.center();
				//					auto rad = item.radius();
				//					auto ang1 = item.angle_1();
				//					auto ang2 = item.angle_2();
				//					while (ang2 < ang1) {
				//						ang2 += two_pi<double>;
				//					}
				//					vector_2d pt0, pt1, pt2, pt3;
				//					int bezCount = 1;
				//					double theta = ang2 - ang1;
				//					double phi;
				//					while (theta >= halfpi) {
				//						theta /= 2.0;
				//						bezCount += bezCount;
				//					}
				//					phi = theta / 2.0;
				//					auto cosPhi = cos(phi);
				//					auto sinPhi = sin(phi);
				//					pt0.x(cosPhi);
				//					pt0.y(-sinPhi);
				//					pt3.x(pt0.x());
				//					pt3.y(-pt0.y());
				//					pt1.x((4.0 - cosPhi) / 3.0);
				//					pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
				//					pt2.x(pt1.x());
				//					pt2.y(-pt1.y());
				//					phi = -phi;
				//					auto rotCwFn = [](const vector_2d& pt, double a) -> vector_2d {
				//						return { pt.x() * cos(a) + pt.y() * sin(a),
				//							-(pt.x() * -(sin(a)) + pt.y() * cos(a)) };
				//					};
				//					pt0 = rotCwFn(pt0, phi);
				//					pt1 = rotCwFn(pt1, phi);
				//					pt2 = rotCwFn(pt2, phi);
				//					pt3 = rotCwFn(pt3, phi);

				//					auto currTheta = ang1;
				//					const auto startPt =
				//						ctr + rotCwFn({ pt0.x() * rad, pt0.y() * rad }, currTheta);
				//					if (hasCurrentPoint) {
				//						currentPoint = startPt;
				//						auto pt = m.transform_point(currentPoint - origin) + origin;
				//						v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
				//					}
				//					else {
				//						currentPoint = startPt;
				//						auto pt = m.transform_point(currentPoint - origin) + origin;
				//						v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
				//						hasCurrentPoint = true;
				//						closePt = pt;
				//					}
				//					for (; bezCount > 0; bezCount--) {
				//						auto cpt1 = ctr + rotCwFn({ pt1.x() * rad, pt1.y() * rad }, currTheta);
				//						auto cpt2 = ctr + rotCwFn({ pt2.x() * rad, pt2.y() * rad },
				//							currTheta);
				//						auto cpt3 = ctr + rotCwFn({ pt3.x() * rad, pt3.y() * rad },
				//							currTheta);
				//						currentPoint = cpt3;
				//						cpt1 = m.transform_point(cpt1 - origin) + origin;
				//						cpt2 = m.transform_point(cpt2 - origin) + origin;
				//						cpt3 = m.transform_point(cpt3 - origin) + origin;
				//						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1,
				//							cpt2, cpt3);
				//						currTheta += theta;
				//					}
				//				}
				//			}
				//			else if (::std::is_same_v<T, path_data::arc_counterclockwise>) {
				//				{
				//					auto ctr = item.center();
				//					auto rad = item.radius();
				//					auto ang1 = item.angle_1();
				//					auto ang2 = item.angle_2();
				//					while (ang2 > ang1) {
				//						ang2 -= two_pi<double>;
				//					}
				//					vector_2d pt0, pt1, pt2, pt3;
				//					int bezCount = 1;
				//					double theta = ang1 - ang2;
				//					double phi;
				//					while (theta >= halfpi) {
				//						theta /= 2.0;
				//						bezCount += bezCount;
				//					}
				//					phi = theta / 2.0;
				//					auto cosPhi = cos(phi);
				//					auto sinPhi = sin(phi);
				//					pt0.x(cosPhi);
				//					pt0.y(-sinPhi);
				//					pt3.x(pt0.x());
				//					pt3.y(-pt0.y());
				//					pt1.x((4.0 - cosPhi) / 3.0);
				//					pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
				//					pt2.x(pt1.x());
				//					pt2.y(-pt1.y());
				//					auto rotCwFn = [](const vector_2d& pt, double a) -> vector_2d {
				//						return { pt.x() * cos(a) + pt.y() * sin(a),
				//							-(pt.x() * -(sin(a)) + pt.y() * cos(a)) };
				//					};
				//					pt0 = rotCwFn(pt0, phi);
				//					pt1 = rotCwFn(pt1, phi);
				//					pt2 = rotCwFn(pt2, phi);
				//					pt3 = rotCwFn(pt3, phi);
				//					auto shflPt = pt3;
				//					pt3 = pt0;
				//					pt0 = shflPt;
				//					shflPt = pt2;
				//					pt2 = pt1;
				//					pt1 = shflPt;
				//					auto currTheta = ang1;
				//					const auto startPt =
				//						ctr + rotCwFn({ pt0.x() * rad, pt0.y() * rad }, currTheta);
				//					if (hasCurrentPoint) {
				//						currentPoint = startPt;
				//						auto pt = m.transform_point(currentPoint - origin) + origin;
				//						v.emplace_back(::std::in_place_type<path_data::abs_line>, pt);
				//					}
				//					else {
				//						currentPoint = startPt;
				//						auto pt = m.transform_point(currentPoint - origin) + origin;
				//						v.emplace_back(::std::in_place_type<path_data::abs_move>, pt);
				//						hasCurrentPoint = true;
				//						closePt = pt;
				//					}
				//					for (; bezCount > 0; bezCount--) {
				//						auto cpt1 = ctr + rotCwFn({ pt1.x() * rad, pt1.y() * rad },
				//							currTheta);
				//						auto cpt2 = ctr + rotCwFn({ pt2.x() * rad, pt2.y() * rad },
				//							currTheta);
				//						auto cpt3 = ctr + rotCwFn({ pt3.x() * rad, pt3.y() * rad },
				//							currTheta);
				//						currentPoint = cpt3;
				//						cpt1 = m.transform_point(cpt1 - origin) + origin;
				//						cpt2 = m.transform_point(cpt2 - origin) + origin;
				//						cpt3 = m.transform_point(cpt3 - origin) + origin;
				//						v.emplace_back(::std::in_place_type<path_data::abs_cubic_curve>, cpt1,
				//							cpt2, cpt3);
				//						currTheta -= theta;
				//					}
				//				}
				//			}
				//			else if (::std::is_same_v<T, path_data::change_matrix>) {
				//				m = item.matrix();
				//			}
				//			else if (::std::is_same_v<T, path_data::change_origin>) {
				//				origin = item.origin();
				//			}
				//		}, val);
				//	}
				//	ec.clear();
				//	return v;
				//}

				template<class Allocator>
				inline path_factory<Allocator>::path_factory(const Allocator &a) noexcept
					: _Data(a)
					, _Current_point()
					, _Last_move_to_point()
					, _Transform_matrix()
					, _Origin() {
				}

				template<class Allocator>
				inline path_factory<Allocator>::path_factory(size_type n, const Allocator & a)
					: _Data(n, a)
					, _Current_point()
					, _Last_move_to_point()
					, _Transform_matrix()
					, _Origin() {
				}

				template<class Allocator>
				inline path_factory<Allocator>::path_factory(size_type n, const value_type & value, const Allocator& a)
					: _Data(n, value, a)
					, _Current_point()
					, _Last_move_to_point()
					, _Transform_matrix()
					, _Origin() {
				}

				template<class Allocator>
				template<class InputIterator>
				inline path_factory<Allocator>::path_factory(InputIterator first, InputIterator last, const Allocator& a)
					: _Data(first, last, a)
					, _Current_point()
					, _Last_move_to_point()
					, _Transform_matrix()
					, _Origin() {
				}

				template<class Allocator>
				template<class InputIterator>
				inline void path_factory<Allocator>::assign(InputIterator first, InputIterator last) {
					_Data.assign(first, last);
				}

				template<class Allocator>
				template<class ...Args>
				inline typename path_factory<Allocator>::reference path_factory<Allocator>::emplace_back(Args && ...args) {
					return _Data.emplace_back(forward<Args&&...>(args...));
				}

				template<class Allocator>
				template<class ...Args>
				inline typename path_factory<Allocator>::iterator path_factory<Allocator>::emplace(const_iterator position, Args&& ...args) {
					return _Data.emplace(position, forward<Args&&...>(args...)).
				}

				template<class Allocator>
				template<class InputIterator>
				inline typename path_factory<Allocator>::iterator path_factory<Allocator>::insert(const_iterator position, InputIterator first, InputIterator last) {
					return _Data.insert<InputIterator>(position, first, last);
				}

				template<class Allocator>
				inline path_factory<Allocator>::path_factory(const path_factory& pf)
					: _Data(pf._Data)
					, _Current_point(pf._Current_point)
					, _Last_move_to_point(pf._Last_move_to_point)
					, _Transform_matrix(pf._Transform_matrix)
					, _Origin(pf._Origin) {
				}

				template<class Allocator>
				inline path_factory<Allocator>::path_factory(path_factory&& pf) noexcept
					: _Data(move(pf._Data))
					, _Current_point(move(pf._Current_point))
					, _Last_move_to_point(move(pf._Last_move_to_point))
					, _Transform_matrix(move(pf._Transform_matrix))
					, _Origin(move(pf._Origin)) {
				}

				template<class Allocator>
				inline path_factory<Allocator>::path_factory(const path_factory& pf, const Allocator & a)
					: _Data(pf._Data, a)
					, _Current_point(pf._Current_point)
					, _Last_move_to_point(pf._Last_move_to_point)
					, _Transform_matrix(pf._Transform_matrix)
					, _Origin(pf._Origin) {
				}

				template<class Allocator>
				inline path_factory<Allocator>::path_factory(path_factory&& pf, const Allocator & a)
					: _Data(move(pf._Data), a)
					, _Current_point(move(pf._Current_point))
					, _Last_move_to_point(move(pf._Last_move_to_point))
					, _Transform_matrix(move(pf._Transform_matrix))
					, _Origin(move(pf._Origin)) {
				}

				template<class Allocator>
				inline path_factory<Allocator>::path_factory(initializer_list<value_type> il, const Allocator & a)
					: _Data(il, a)
					, _Current_point()
					, _Last_move_to_point()
					, _Transform_matrix()
					, _Origin() {
				}

				template <class Allocator>
				inline path_factory<Allocator>& path_factory<Allocator>::operator=(const path_factory& x) {
					_Data = x._Data;
					_Current_point = x._Current_point;
					_Last_move_to_point = x._Last_move_to_point;
					_Origin = x._Origin;
					return *this;
				}
				template<class Allocator>
				inline path_factory<Allocator>& path_factory<Allocator>::operator=(path_factory&& x) noexcept(allocator_traits<Allocator>::propagate_on_container_move_assignment::value || allocator_traits<Allocator>::is_always_equal::value) {
					::std::swap(_Data, x._Data);
					::std::swap(_Current_point, x._Current_point);
					::std::swap(_Last_move_to_point, x._Last_move_to_point);
					::std::swap(_Origin, x._Origin);
					return *this;
				}
				template<class Allocator>
				inline path_factory<Allocator>& path_factory<Allocator>::operator=(initializer_list<value_type> il) {
					_Data.clear();
					for (const auto& item : il) {
						_Data.push_back(item);
					}
					return *this;
				}
				template<class Allocator>
				inline void path_factory<Allocator>::assign(size_type n, const value_type& u) {
					_Data.assign(n, u);
				}
				template<class Allocator>
				inline void path_factory<Allocator>::assign(initializer_list<value_type> il) {
					_Data.assign(il);
				}
				template<class Allocator>
				inline typename path_factory<Allocator>::allocator_type path_factory<Allocator>::get_allocator() const noexcept {
					return _Data.allocator_type();
				}
				template<class Allocator>
				inline typename path_factory<Allocator>::iterator path_factory<Allocator>::begin() noexcept {
					return _Data.begin();
				}
				template<class Allocator>
				inline typename path_factory<Allocator>::const_iterator path_factory<Allocator>::begin() const noexcept {
					return _Data.begin();
				}
				template<class Allocator>
				inline typename path_factory<Allocator>::const_iterator path_factory<Allocator>::cbegin() const noexcept {
					return _Data.cbegin();
				}
				template<class Allocator>
				inline typename path_factory<Allocator>::iterator path_factory<Allocator>::end() noexcept {
					return _Data.end();
				}
				template<class Allocator>
				inline typename path_factory<Allocator>::const_iterator path_factory<Allocator>::end() const noexcept {
					return _Data.end();
				}
				template<class Allocator>
				inline typename path_factory<Allocator>::const_iterator path_factory<Allocator>::cend() const noexcept {
					return _Data.cend();
				}
				template<class Allocator>
				inline typename path_factory<Allocator>::reverse_iterator path_factory<Allocator>::rbegin() noexcept {
					return _Data.rbegin();
				}
				template<class Allocator>
				inline typename path_factory<Allocator>::const_reverse_iterator path_factory<Allocator>::rbegin() const noexcept {
					return _Data.rbegin();
				}
				template<class Allocator>
				inline typename path_factory<Allocator>::const_reverse_iterator path_factory<Allocator>::crbegin() const noexcept {
					return _Data.crbegin();
				}
				template<class Allocator>
				inline typename path_factory<Allocator>::reverse_iterator path_factory<Allocator>::rend() noexcept {
					return _Data.rend();
				}
				template<class Allocator>
				inline typename path_factory<Allocator>::const_reverse_iterator path_factory<Allocator>::rend() const noexcept {
					return _Data.rend();
				}
				template<class Allocator>
				inline typename path_factory<Allocator>::const_reverse_iterator path_factory<Allocator>::crend() const noexcept {
					return _Data.crend();
				}

				template<class Allocator>
				inline bool path_factory<Allocator>::empty() const noexcept {
					return _Data.empty();
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::size_type path_factory<Allocator>::size() const noexcept {
					return _Data.size();
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::size_type path_factory<Allocator>::max_size() const noexcept {
					return _Data.max_size();
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::size_type path_factory<Allocator>::capacity() const noexcept {
					return _Data.capacity();
				}

				template<class Allocator>
				inline void path_factory<Allocator>::resize(size_type sz) {
					_Data.resize(sz);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::resize(size_type sz, const value_type& c) {
					_Data.resize(sz, c);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::reserve(size_type n) {
					_Data.reserve(n)
				}

				template<class Allocator>
				inline void path_factory<Allocator>::shrink_to_fit() {
					_Data.shrink_to_fit();
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::reference path_factory<Allocator>::operator[](size_type n) {
					return _Data[n];
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::const_reference path_factory<Allocator>::operator[](size_type n) const {
					return _Data[n];
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::const_reference path_factory<Allocator>::at(size_type n) const {
					return _Data.at(n);
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::reference path_factory<Allocator>::at(size_type n) {
					return _Data.at(n);
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::reference path_factory<Allocator>::front() {
					return _Data.front();
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::const_reference path_factory<Allocator>::front() const {
					return _Data.front();
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::reference path_factory<Allocator>::back() {
					return _Data.back();
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::const_reference path_factory<Allocator>::back() const {
					return _Data.back();
				}

				template<class Allocator>
				inline void path_factory<Allocator>::new_path() noexcept {
					_Data.emplace_back(in_place_type<path_data::new_path>);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::close_path() noexcept {
					const vector_2d pt{};
					_Data.emplace_back(in_place_type<path_data::close_path>, pt);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::arc_clockwise(const vector_2d& center, double radius, double angle1, double angle2) noexcept {
					_Data.emplace_back(in_place_type<path_data::arc_clockwise>, center, radius, angle1, angle2);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::arc_counterclockwise(const vector_2d& center, double radius, double angle1, double angle2) noexcept {
					_Data.emplace_back(in_place_type<path_data::arc_counterclockwise>, center, radius, angle1, angle2);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::cubic_curve_to(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2) noexcept {
					_Data.emplace_back(in_place_type<path_data::abs_cubic_curve>, pt0, pt1, pt2);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::line_to(const vector_2d& pt) noexcept {
					_Data.emplace_back(in_place_type<path_data::abs_line>, pt);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::move_to(const vector_2d& pt) noexcept {
					_Data.emplace_back(in_place_type<path_data::abs_move>, pt);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::quadratic_curve_to(const vector_2d& pt0, const vector_2d& pt1) noexcept {
					_Data.emplace_back(in_place_type<path_data::abs_quadratic_curve>, pt0, pt1);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::rectangle(const experimental::io2d::rectangle& r) noexcept {
					_Data.emplace_back(in_place_type<path_data::abs_move>, { r.x(), r.y() });
					_Data.emplace_back(in_place_type<path_data::rel_line>, { r.width(), 0.0 });
					_Data.emplace_back(in_place_type<path_data::rel_line>, { 0.0, r.height() });
					_Data.emplace_back(in_place_type<path_data::rel_line>, { -r.width(), 0.0 });
					_Data.emplace_back(in_place_type<path_data::close_path>, { 0.0. 0.0 });
				}

				template<class Allocator>
				inline void path_factory<Allocator>::rel_cubic_curve_to(const vector_2d& dpt0, const vector_2d& dpt1, const vector_2d& dpt2) noexcept {
					_Data.emplace_back(in_place_type<path_data::rel_cubic_curve>, dpt0, dpt1, dpt2);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::rel_line_to(const vector_2d& dpt) noexcept {
					_Data.emplace_back(in_place_type<path_data::rel_line>, dpt);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::rel_move_to(const vector_2d& dpt) noexcept {
					_Data.emplace_back(in_place_type<path_data::rel_move>, dpt);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::rel_quadratic_curve_to(const vector_2d& dpt0, const vector_2d& dpt1) noexcept {
					_Data.emplace_back(in_place_type<path_data::rel_quadratic_curve>, dpt0, dpt1);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::transform_matrix(const matrix_2d& m) noexcept {
					_Data.emplace_back(in_place_type<path_data::change_matrix>, m);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::origin(const vector_2d& pt) noexcept {
					return _Data.emplace_back(in_place_type<path_data::change_origin>, pt);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::push_back(const value_type& x) {
					_Data.push_back(x);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::push_back(value_type&& x) {
					_Data.push_back(move(x));
				}

				template<class Allocator>
				inline void path_factory<Allocator>::pop_back() {
					_Data.pop_back();
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::iterator path_factory<Allocator>::insert(const_iterator position, const value_type& x) {
					return _Data.insert(position, x);
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::iterator path_factory<Allocator>::insert(const_iterator position, value_type&& x) {
					return _Data.insert(position, x);
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::iterator path_factory<Allocator>::insert(const_iterator position, size_type n, const value_type& x) {
					return _Data.insert(position, n, x);
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::iterator path_factory<Allocator>::insert(const_iterator position, initializer_list<value_type> il) {
					return _Data.insert(position, il);
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::iterator path_factory<Allocator>::erase(const_iterator position) {
					return _Data.erase(position);
				}

				template<class Allocator>
				inline typename path_factory<Allocator>::iterator path_factory<Allocator>::erase(const_iterator first, const_iterator last) {
					return _Data.erase(first, last);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::swap(path_factory &pf) noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value || allocator_traits<Allocator>::is_always_equal::value) {
					swap(_data, pf._Data);
					swap(_Current_point, pf._Current_point);
					swap(_Last_move_to_point, pf._Last_move_to_point);
					swap(_Origin, pf._Origin);
					swap(_Transform_matrix, pf._Transform_matrix);
				}

				template<class Allocator>
				inline void path_factory<Allocator>::clear() noexcept {
					_Data.clear();
					_Current_point.reset();
					_Transform_matrix = matrix_2d::init_identity();
					_Origin = {};
				}

#if _Inline_namespace_conditional_support_test
		}
#endif
	}
}
	}

#endif

