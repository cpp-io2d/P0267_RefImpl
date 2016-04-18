#pragma once

#ifndef _IO2D_
#define _IO2D_

#define __cpp_lib_experimental_io2d 201507

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

		//// From C++ Extensions for Library Fundamentals, N4335
		struct nullopt_t {
			constexpr explicit nullopt_t(int) noexcept {
			}
		};
		constexpr nullopt_t nullopt{ 0 };

		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif

				enum class io2d_error {
					success,
					invalid_restore,
					no_current_point,
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

				enum class extend {
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

				enum class path_data_type {
					move_to,
					line_to,
					curve_to,
					new_sub_path,
					close_path,
					rel_move_to,
					rel_line_to,
					rel_curve_to,
					arc,
					arc_negative,
					change_matrix,
					change_origin
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
					double _X = 0.0;
					double _Y = 0.0;
				public:
					vector_2d() noexcept = default;
					vector_2d(const vector_2d& other) noexcept = default;
					vector_2d& operator=(const vector_2d& other) noexcept = default;
					vector_2d(vector_2d&& other) noexcept;
					vector_2d& operator=(vector_2d&& other) noexcept;
					vector_2d(double x, double y) noexcept;

					void x(double value) noexcept;
					void y(double value) noexcept;

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

				class rectangle {
					double _X = 0.0;
					double _Y = 0.0;
					double _Width = 0.0;
					double _Height = 0.0;
				public:
					rectangle() noexcept = default;
					rectangle(const rectangle& other) noexcept = default;
					rectangle& operator=(const rectangle& other) noexcept = default;
					rectangle(rectangle&& other) noexcept ;
					rectangle& operator=(rectangle&& other) noexcept ;
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

				class font_extents {
					cairo_font_extents_t _Font_extents;
				public:
					typedef cairo_font_extents_t* native_handle_type;
					native_handle_type native_handle() noexcept;

					font_extents() noexcept;
					font_extents(const font_extents& other) noexcept = default;
					font_extents& operator=(const font_extents& other) noexcept = default;
					font_extents(font_extents&& other) noexcept;
					font_extents& operator=(font_extents&& other) noexcept;
					font_extents(double ascent, double descent, double height) noexcept;

					void ascent(double value) noexcept;
					void descent(double value) noexcept;
					void height(double value) noexcept;

					double ascent() const noexcept;
					double descent() const noexcept;
					double height() const noexcept;
				};

				class text_extents {
					cairo_text_extents_t _Text_extents;
				public:
					typedef cairo_text_extents_t* native_handle_type;
					native_handle_type native_handle() noexcept;

					text_extents() noexcept;
					text_extents(const text_extents& other) noexcept = default;
					text_extents& operator=(const text_extents& other) noexcept = default;
					text_extents(text_extents&& other) noexcept;
					text_extents& operator=(text_extents&& other) noexcept;
					text_extents(double xBearing, double yBearing, double width, double height, double xAdvance, double yAdvance) noexcept;

					void x_bearing(double value) noexcept;
					void y_bearing(double value) noexcept;
					void width(double value) noexcept;
					void height(double value) noexcept;
					void x_advance(double value) noexcept;
					void y_advance(double value) noexcept;

					double x_bearing() const noexcept;
					double y_bearing() const noexcept;
					double width() const noexcept;
					double height() const noexcept;
					double x_advance() const noexcept;
					double y_advance() const noexcept;
				};

				class matrix_2d {
					double _M00 = 1.0;
					double _M01 = 0.0;
					double _M10 = 0.0;
					double _M11 = 1.0;
					double _M20 = 0.0;
					double _M21 = 0.0;
				public:

					matrix_2d() noexcept;
					matrix_2d(const matrix_2d& other) noexcept = default;
					matrix_2d& operator=(const matrix_2d& other) noexcept = default;
					matrix_2d(matrix_2d&& other) noexcept;
					matrix_2d& operator=(matrix_2d&& other) noexcept;
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

				class path_data_item {
					bool _Has_data = false;
					union {
						struct {
							double centerX;
							double centerY;
							double radius;
							double angle1;
							double angle2;
						} arc;
						struct {
							double m00;
							double m01;
							double m10;
							double m11;
							double m20;
							double m21;
						} matrix;
						struct {
							double cpt1x;
							double cpt1y;
							double cpt2x;
							double cpt2y;
							double eptx;
							double epty;
						} curve;
						struct {
							double x;
							double y;
						} point;
					} _Data;

					path_data_type _Type;

				public:
					class path_data;
					class arc;
					class arc_negative;
					class change_matrix;
					class change_origin;
					class close_path;
					class curve_to;
					class rel_curve_to;
					class new_sub_path;
					class line_to;
					class move_to;
					class rel_line_to;
					class rel_move_to;

					path_data_item() noexcept = default;
					path_data_item(const path_data_item&) noexcept = default;
					path_data_item& operator=(const path_data_item&) noexcept = default;
					path_data_item(path_data_item&& other) noexcept;
					path_data_item& operator=(path_data_item&& other) noexcept;
					path_data_item(const path_data_item::arc& value) noexcept;
					path_data_item(const path_data_item::arc_negative& value) noexcept;
					path_data_item(const path_data_item::change_matrix& value) noexcept;
					path_data_item(const path_data_item::change_origin& value) noexcept;
					path_data_item(const path_data_item::close_path& value) noexcept;
					path_data_item(const path_data_item::curve_to& value) noexcept;
					path_data_item(const path_data_item::rel_curve_to& value) noexcept;
					path_data_item(const path_data_item::new_sub_path& value) noexcept;
					path_data_item(const path_data_item::line_to& value) noexcept;
					path_data_item(const path_data_item::move_to& value) noexcept;
					path_data_item(const path_data_item::rel_line_to& value) noexcept;
					path_data_item(const path_data_item::rel_move_to& value) noexcept;

					void assign(const path_data_item::arc& value) noexcept;
					void assign(const path_data_item::arc_negative& value) noexcept;
					void assign(const path_data_item::change_matrix& value) noexcept;
					void assign(const path_data_item::change_origin& value) noexcept;
					void assign(const path_data_item::close_path& value) noexcept;
					void assign(const path_data_item::curve_to& value) noexcept;
					void assign(const path_data_item::rel_curve_to& value) noexcept;
					void assign(const path_data_item::new_sub_path& value) noexcept;
					void assign(const path_data_item::line_to& value) noexcept;
					void assign(const path_data_item::move_to& value) noexcept;
					void assign(const path_data_item::rel_line_to& value) noexcept;
					void assign(const path_data_item::rel_move_to& value) noexcept;

					bool has_data() const noexcept;
					path_data_type type() const;
					path_data_type type(::std::error_code& ec) const noexcept;

					template <class T>
					T get() const;
					template <class T>
					T get(::std::error_code& ec) const noexcept;
				};
/*
                                template <>
				path_data_item::arc path_data_item::get() const;
				template <>
				path_data_item::arc path_data_item::get(::std::error_code& ec) const noexcept;
				template <>
				path_data_item::arc_negative path_data_item::get() const;
				template <>
				path_data_item::arc_negative path_data_item::get(::std::error_code& ec) const noexcept;
				template <>
				path_data_item::change_matrix path_data_item::get() const;
				template <>
				path_data_item::change_matrix path_data_item::get(::std::error_code& ec) const noexcept;
				template <>
				path_data_item::change_origin path_data_item::get() const;
				template <>
				path_data_item::change_origin path_data_item::get(::std::error_code& ec) const noexcept;
				template <>
				path_data_item::close_path path_data_item::get() const;
				template <>
				path_data_item::close_path path_data_item::get(::std::error_code& ec) const noexcept;
				template <>
				path_data_item::curve_to path_data_item::get() const;
				template <>
				path_data_item::curve_to path_data_item::get(::std::error_code& ec) const noexcept;
				template <>
				path_data_item::rel_curve_to path_data_item::get() const;
				template <>
				path_data_item::rel_curve_to path_data_item::get(::std::error_code& ec) const noexcept;
				template <>
				path_data_item::new_sub_path path_data_item::get() const;
				template <>
				path_data_item::new_sub_path path_data_item::get(::std::error_code& ec) const noexcept;
				template <>
				path_data_item::line_to path_data_item::get() const;
				template <>
				path_data_item::line_to path_data_item::get(::std::error_code& ec) const noexcept;
				template <>
				path_data_item::move_to path_data_item::get() const;
				template <>
				path_data_item::move_to path_data_item::get(::std::error_code& ec) const noexcept;
				template <>
				path_data_item::rel_line_to path_data_item::get() const;
				template <>
				path_data_item::rel_line_to path_data_item::get(::std::error_code& ec) const noexcept;
				template <>
				path_data_item::rel_move_to path_data_item::get() const;
				template <>
				path_data_item::rel_move_to path_data_item::get(::std::error_code& ec) const noexcept;
*/

				// I don't know why Clang/C2 is complaining about weak vtables here since the at least one virtual function is always anchored but for now silence the warnings. I've never seen this using Clang on OpenSUSE.
#ifdef _WIN32
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
#endif
				class path_data_item::path_data {
				public:
					path_data() noexcept = default;
					path_data(const path_data& other) noexcept = default;
					path_data& operator=(const path_data& other) noexcept = default;
					path_data(path_data&& other) noexcept;
					path_data& operator=(path_data&& other) noexcept;
					virtual ~path_data() noexcept;

					virtual path_data_type type() const noexcept = 0;
				};

				class _Point : public path_data_item::path_data {
					vector_2d _Data = { };
				public:
					_Point() noexcept = default;
					_Point(const _Point& other) noexcept = default;
					_Point& operator=(const _Point& other) noexcept = default;
					_Point(_Point&& other) noexcept;
					_Point& operator=(_Point&& other) noexcept;
					_Point(const vector_2d& to) noexcept;
					virtual ~_Point() noexcept;
					virtual path_data_type type() const noexcept override = 0;

					vector_2d to() const noexcept;
					void to(const vector_2d& value) noexcept;
				};

				class path_data_item::move_to : public _Point {
				public:
					move_to() noexcept = default;
					move_to(const move_to& other) noexcept = default;
					move_to& operator=(const move_to& other) noexcept = default;
					move_to(move_to&& other) noexcept;
					move_to& operator=(move_to&& other) noexcept;
					move_to(const vector_2d& to) noexcept;
					virtual path_data_type type() const noexcept override;
				};

				class path_data_item::line_to : public _Point {
				public:
					line_to() noexcept = default;
					line_to(const line_to& other) noexcept = default;
					line_to& operator=(const line_to& other) noexcept = default;
					line_to(line_to&& other) noexcept;
					line_to& operator=(line_to&& other) noexcept;
					line_to(const vector_2d& to) noexcept;
					virtual path_data_type type() const noexcept override;
				};

				class path_data_item::rel_move_to : public _Point {
				public:
					rel_move_to() noexcept = default;
					rel_move_to(const rel_move_to& other) noexcept = default;
					rel_move_to& operator=(const rel_move_to& other) noexcept = default;
					rel_move_to(rel_move_to&& other) noexcept;
					rel_move_to& operator=(rel_move_to&& other) noexcept;
					rel_move_to(const vector_2d& to) noexcept;
					virtual path_data_type type() const noexcept override;
				};

				class path_data_item::rel_line_to : public _Point {
				public:
					rel_line_to() noexcept = default;
					rel_line_to(const rel_line_to& other) noexcept = default;
					rel_line_to& operator=(const rel_line_to& other) noexcept = default;
					rel_line_to(rel_line_to&& other) noexcept;
					rel_line_to& operator=(rel_line_to&& other) noexcept;
					rel_line_to(const vector_2d& to) noexcept;
					virtual path_data_type type() const noexcept override;
				};

				class _Curve_to : public path_data_item::path_data {
					vector_2d _Control_pt1 = { };
					vector_2d _Control_pt2 = { };
					vector_2d _End_pt = { };
				public:
					_Curve_to() noexcept = default;
					_Curve_to(const _Curve_to& other) noexcept = default;
					_Curve_to& operator=(const _Curve_to& other) noexcept = default;
					_Curve_to(_Curve_to&& other) noexcept;
					_Curve_to& operator=(_Curve_to&& other) noexcept;
					_Curve_to(const vector_2d& controlPoint1, const vector_2d& controlPoint2, const vector_2d& endPoint) noexcept;
					virtual ~_Curve_to() noexcept;
					virtual path_data_type type() const noexcept override = 0;

					void control_point_1(const vector_2d& value) noexcept;
					void control_point_2(const vector_2d& value) noexcept;
					void end_point(const vector_2d& value) noexcept;

					vector_2d control_point_1() const noexcept;
					vector_2d control_point_2() const noexcept;
					vector_2d end_point() const noexcept;
				};

				class path_data_item::curve_to : public _Curve_to {
				public:
					curve_to() noexcept = default;
					curve_to(const curve_to& other) noexcept = default;
					curve_to& operator=(const curve_to& other) noexcept = default;
					curve_to(curve_to&& other) noexcept;
					curve_to& operator=(curve_to&& other) noexcept;
					curve_to(const vector_2d& controlPoint1, const vector_2d& controlPoint2, const vector_2d& endPoint) noexcept;
					virtual path_data_type type() const noexcept override;
				};

				class path_data_item::rel_curve_to : public _Curve_to {
				public:
					rel_curve_to() noexcept = default;
					rel_curve_to(const rel_curve_to& other) noexcept = default;
					rel_curve_to& operator=(const rel_curve_to& other) noexcept = default;
					rel_curve_to(rel_curve_to&& other) noexcept;
					rel_curve_to& operator=(rel_curve_to&& other) noexcept;
					rel_curve_to(const vector_2d& controlPoint1, const vector_2d& controlPoint2, const vector_2d& endPoint) noexcept;
					virtual path_data_type type() const noexcept override;
				};

				class _Arc : public path_data_item::path_data {
					vector_2d _Center;
					double _Radius;
					double _Angle_1;
					double _Angle_2;
				public:
					_Arc() noexcept;
					_Arc(const _Arc& other) noexcept = default;
					_Arc& operator=(const _Arc& other) noexcept = default;
					_Arc(_Arc&& other) noexcept;
					_Arc& operator=(_Arc&& other) noexcept;
					_Arc(const vector_2d& center, double radius, double angle1, double angle2) noexcept;
					virtual ~_Arc() noexcept;
					virtual path_data_type type() const noexcept override = 0;

					void center(const vector_2d& value) noexcept;
					void radius(double value) noexcept;
					void angle_1(double radians) noexcept;
					void angle_2(double radians) noexcept;

					vector_2d center() const noexcept;
					double radius() const noexcept;
					double angle_1() const noexcept;
					double angle_2() const noexcept;
				};

				class path_data_item::arc : public _Arc {
				public:
					arc() noexcept = default;
					arc(const arc& other) noexcept = default;
					arc& operator=(const arc& other) noexcept = default;
					arc(arc&& other) noexcept;
					arc& operator=(arc&& other) noexcept;
					arc(const vector_2d& center, double radius, double angle1, double angle2) noexcept;

					virtual path_data_type type() const noexcept override;
				};

				class path_data_item::arc_negative : public _Arc {
				public:
					arc_negative() noexcept = default;
					arc_negative(const arc_negative& other) noexcept = default;
					arc_negative& operator=(const arc_negative& other) noexcept = default;
					arc_negative(arc_negative&& other) noexcept;
					arc_negative& operator=(arc_negative&& other) noexcept;
					arc_negative(const vector_2d& center, double radius, double angle1, double angle2) noexcept;

					virtual path_data_type type() const noexcept override;
				};

				class path_data_item::new_sub_path : public path_data_item::path_data {
				public:
					new_sub_path() noexcept = default;
					new_sub_path(const new_sub_path& other) noexcept = default;
					new_sub_path& operator=(const new_sub_path& other) noexcept = default;
					new_sub_path(new_sub_path&& other) noexcept;
					new_sub_path& operator=(new_sub_path&& other) noexcept;

					virtual path_data_type type() const noexcept override;
				};

				class path_data_item::close_path : public path_data_item::path_data {
				public:
					close_path() noexcept = default;
					close_path(const close_path& other) noexcept = default;
					close_path& operator=(const close_path& other) noexcept = default;
					close_path(close_path&& other) noexcept;
					close_path& operator=(close_path&& other) noexcept;

					virtual path_data_type type() const noexcept override;
				};

				class path_data_item::change_matrix : public path_data_item::path_data {
					matrix_2d _Matrix = { };
				public:
					change_matrix() noexcept = default;
					change_matrix(const change_matrix& other) noexcept = default;
					change_matrix& operator=(const change_matrix& other) noexcept = default;
					change_matrix(change_matrix&& other) noexcept;
					change_matrix& operator=(change_matrix&& other) noexcept;
					change_matrix(const matrix_2d& m) noexcept;

					void matrix(const matrix_2d& value) noexcept;

					matrix_2d matrix() const noexcept;
					virtual path_data_type type() const noexcept override;
				};

				class path_data_item::change_origin : public path_data_item::path_data {
					vector_2d _Origin = { };
				public:
					change_origin() noexcept = default;
					change_origin(const change_origin& other) noexcept = default;
					change_origin& operator=(const change_origin& other) noexcept = default;
					change_origin(change_origin&& other) noexcept;
					change_origin& operator=(change_origin&& other) noexcept;
					change_origin(const vector_2d& origin) noexcept;

					void origin(const vector_2d& value) noexcept;

					vector_2d origin() const noexcept;
					virtual path_data_type type() const noexcept override;
				};

#ifdef _WIN32
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif

				template <>
				inline path_data_item::arc path_data_item::get() const {
					if (!_Has_data) {
						throw ::std::system_error(::std::make_error_code(::std::errc::operation_not_permitted));
					}
					if (_Type != path_data_type::arc) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return path_data_item::arc{ vector_2d{ _Data.arc.centerX, _Data.arc.centerY }, _Data.arc.radius, _Data.arc.angle1, _Data.arc.angle2 };
				}

				template <>
				inline path_data_item::arc path_data_item::get(::std::error_code& ec) const noexcept {
					if (!_Has_data) {
						ec = ::std::make_error_code(::std::errc::operation_not_permitted);
						return path_data_item::arc{ };
					}
					if (_Type != path_data_type::arc) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return path_data_item::arc{ };
					}
					ec.clear();
					return path_data_item::arc{ vector_2d{ _Data.arc.centerX, _Data.arc.centerY }, _Data.arc.radius, _Data.arc.angle1, _Data.arc.angle2 };
				}

				template <>
				inline path_data_item::arc_negative path_data_item::get() const {
					if (!_Has_data) {
						throw ::std::system_error(::std::make_error_code(::std::errc::operation_not_permitted));
					}
					if (_Type != path_data_type::arc_negative) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return path_data_item::arc_negative{ vector_2d{ _Data.arc.centerX, _Data.arc.centerY }, _Data.arc.radius, _Data.arc.angle1, _Data.arc.angle2 };
				}

				template <>
				inline path_data_item::arc_negative path_data_item::get(::std::error_code& ec) const noexcept {
					if (!_Has_data) {
						ec = ::std::make_error_code(::std::errc::operation_not_permitted);
						return path_data_item::arc_negative{ };
					}
					if (_Type != path_data_type::arc_negative) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return path_data_item::arc_negative{ };
					}
					ec.clear();
					return path_data_item::arc_negative{ vector_2d{ _Data.arc.centerX, _Data.arc.centerY }, _Data.arc.radius, _Data.arc.angle1, _Data.arc.angle2 };
				}

				template <>
				inline path_data_item::change_matrix path_data_item::get() const {
					if (!_Has_data) {
						throw ::std::system_error(::std::make_error_code(::std::errc::operation_not_permitted));
					}
					if (_Type != path_data_type::change_matrix) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return path_data_item::change_matrix{ matrix_2d{ _Data.matrix.m00, _Data.matrix.m01, _Data.matrix.m10, _Data.matrix.m11, _Data.matrix.m20, _Data.matrix.m21 } };
				}

				template <>
				inline path_data_item::change_matrix path_data_item::get(::std::error_code& ec) const noexcept {
					if (!_Has_data) {
						ec = ::std::make_error_code(::std::errc::operation_not_permitted);
						return path_data_item::change_matrix{ };
					}
					if (_Type != path_data_type::change_matrix) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return path_data_item::change_matrix{ };
					}
					ec.clear();
					return path_data_item::change_matrix{ matrix_2d{ _Data.matrix.m00, _Data.matrix.m01, _Data.matrix.m10, _Data.matrix.m11, _Data.matrix.m20, _Data.matrix.m21 } };
				}

				template <>
				inline path_data_item::change_origin path_data_item::get() const {
					if (!_Has_data) {
						throw ::std::system_error(::std::make_error_code(::std::errc::operation_not_permitted));
					}
					if (_Type != path_data_type::change_origin) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return path_data_item::change_origin{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				inline path_data_item::change_origin path_data_item::get(::std::error_code& ec) const noexcept {
					if (!_Has_data) {
						ec = ::std::make_error_code(::std::errc::operation_not_permitted);
						return path_data_item::change_origin{ };
					}
					if (_Type != path_data_type::change_origin) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return path_data_item::change_origin{ };
					}
					ec.clear();
					return path_data_item::change_origin{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				inline path_data_item::close_path path_data_item::get() const {
					if (!_Has_data) {
						throw ::std::system_error(::std::make_error_code(::std::errc::operation_not_permitted));
					}
					if (_Type != path_data_type::close_path) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return path_data_item::close_path{ };
				}

				template <>
				inline path_data_item::close_path path_data_item::get(::std::error_code& ec) const noexcept {
					if (!_Has_data) {
						ec = ::std::make_error_code(::std::errc::operation_not_permitted);
						return path_data_item::close_path{ };
					}
					if (_Type != path_data_type::close_path) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return path_data_item::close_path{ };
					}
					ec.clear();
					return path_data_item::close_path{ };
				}

				template <>
				inline path_data_item::curve_to path_data_item::get() const {
					if (!_Has_data) {
						throw ::std::system_error(::std::make_error_code(::std::errc::operation_not_permitted));
					}
					if (_Type != path_data_type::curve_to) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return path_data_item::curve_to{ vector_2d{ _Data.curve.cpt1x, _Data.curve.cpt1y }, vector_2d{ _Data.curve.cpt2x, _Data.curve.cpt2y }, vector_2d{ _Data.curve.eptx, _Data.curve.epty } };
				}

				template <>
				inline path_data_item::curve_to path_data_item::get(::std::error_code& ec) const noexcept {
					if (!_Has_data) {
						ec = ::std::make_error_code(::std::errc::operation_not_permitted);
						return path_data_item::curve_to{ };
					}
					if (_Type != path_data_type::curve_to) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return path_data_item::curve_to{ };
					}
					ec.clear();
					return path_data_item::curve_to{ vector_2d{ _Data.curve.cpt1x, _Data.curve.cpt1y }, vector_2d{ _Data.curve.cpt2x, _Data.curve.cpt2y }, vector_2d{ _Data.curve.eptx, _Data.curve.epty } };
				}

				template <>
				inline path_data_item::rel_curve_to path_data_item::get() const {
					if (!_Has_data) {
						throw ::std::system_error(::std::make_error_code(::std::errc::operation_not_permitted));
					}
					if (_Type != path_data_type::rel_curve_to) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return path_data_item::rel_curve_to{ vector_2d{ _Data.curve.cpt1x, _Data.curve.cpt1y }, vector_2d{ _Data.curve.cpt2x, _Data.curve.cpt2y }, vector_2d{ _Data.curve.eptx, _Data.curve.epty } };
				}

				template <>
				inline path_data_item::rel_curve_to path_data_item::get(::std::error_code& ec) const noexcept {
					if (!_Has_data) {
						ec = ::std::make_error_code(::std::errc::operation_not_permitted);
						return path_data_item::rel_curve_to{ };
					}
					if (_Type != path_data_type::rel_curve_to) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return path_data_item::rel_curve_to{ };
					}
					ec.clear();
					return path_data_item::rel_curve_to{ vector_2d{ _Data.curve.cpt1x, _Data.curve.cpt1y }, vector_2d{ _Data.curve.cpt2x, _Data.curve.cpt2y }, vector_2d{ _Data.curve.eptx, _Data.curve.epty } };
				}

				template <>
				inline path_data_item::new_sub_path path_data_item::get() const {
					if (!_Has_data) {
						throw ::std::system_error(::std::make_error_code(::std::errc::operation_not_permitted));
					}
					if (_Type != path_data_type::new_sub_path) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return path_data_item::new_sub_path{ };
				}

				template <>
				inline path_data_item::new_sub_path path_data_item::get(::std::error_code& ec) const noexcept {
					if (!_Has_data) {
						ec = ::std::make_error_code(::std::errc::operation_not_permitted);
						return path_data_item::new_sub_path{ };
					}
					if (_Type != path_data_type::new_sub_path) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return path_data_item::new_sub_path{ };
					}
					ec.clear();
					return path_data_item::new_sub_path{ };
				}

				template <>
				inline path_data_item::line_to path_data_item::get() const {
					if (!_Has_data) {
						throw ::std::system_error(::std::make_error_code(::std::errc::operation_not_permitted));
					}
					if (_Type != path_data_type::line_to) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return path_data_item::line_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				inline path_data_item::line_to path_data_item::get(::std::error_code& ec) const noexcept {
					if (!_Has_data) {
						ec = ::std::make_error_code(::std::errc::operation_not_permitted);
						return path_data_item::line_to{ };
					}
					if (_Type != path_data_type::line_to) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return path_data_item::line_to{ };
					}
					ec.clear();
					return path_data_item::line_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				inline path_data_item::move_to path_data_item::get() const {
					if (!_Has_data) {
						throw ::std::system_error(::std::make_error_code(::std::errc::operation_not_permitted));
					}
					if (_Type != path_data_type::move_to) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return path_data_item::move_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				inline path_data_item::move_to path_data_item::get(::std::error_code& ec) const noexcept {
					if (!_Has_data) {
						ec = ::std::make_error_code(::std::errc::operation_not_permitted);
						return path_data_item::move_to{ };
					}
					if (_Type != path_data_type::move_to) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return path_data_item::move_to{ };
					}
					ec.clear();
					return path_data_item::move_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				inline path_data_item::rel_line_to path_data_item::get() const {
					if (!_Has_data) {
						throw ::std::system_error(::std::make_error_code(::std::errc::operation_not_permitted));
					}
					if (_Type != path_data_type::rel_line_to) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return path_data_item::rel_line_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				inline path_data_item::rel_line_to path_data_item::get(::std::error_code& ec) const noexcept {
					if (!_Has_data) {
						ec = ::std::make_error_code(::std::errc::operation_not_permitted);
						return path_data_item::rel_line_to{ };
					}
					if (_Type != path_data_type::rel_line_to) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return path_data_item::rel_line_to{ };
					}
					ec.clear();
					return path_data_item::rel_line_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				inline path_data_item::rel_move_to path_data_item::get() const {
					if (!_Has_data) {
						throw ::std::system_error(::std::make_error_code(::std::errc::operation_not_permitted));
					}
					if (_Type != path_data_type::rel_move_to) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return path_data_item::rel_move_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				inline path_data_item::rel_move_to path_data_item::get(::std::error_code& ec) const noexcept {
					if (!_Has_data) {
						ec = ::std::make_error_code(::std::errc::operation_not_permitted);
						return path_data_item::rel_move_to{ };
					}
					if (_Type != path_data_type::rel_move_to) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return path_data_item::rel_move_to{ };
					}
					ec.clear();
					return path_data_item::rel_move_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}


				// Forward declaration.
				class path_factory;
				class surface;

				class path {
					friend path_factory;
					::std::shared_ptr<::std::vector<path_data_item>> _Data;
					::std::shared_ptr<cairo_path_t> _Cairo_path;
				public:
					typedef cairo_path_t* native_handle_type;
					native_handle_type native_handle() const noexcept;

					path() = delete;
					explicit path(const path_factory& pb);
					path(const path_factory& pb, ::std::error_code& ec) noexcept;
					explicit path(const ::std::vector<path_data_item>& p);
					path(const ::std::vector<path_data_item>& p, ::std::error_code& ec) noexcept;
					path(const path& other) noexcept = default;
					path& operator=(const path& other) noexcept = default;
					path(path&& other) noexcept;
					path& operator=(path&& other) noexcept;
				};

				// Forward declaration
				class font_resource;
				class glyph_run;

				class path_factory {
					friend path;
					::std::vector<path_data_item> _Data;
					bool _Has_current_point;
					vector_2d _Current_point;
					vector_2d _Last_move_to_point;
					matrix_2d _Transform_matrix;
					vector_2d _Origin;
				public:
					path_factory() noexcept = default;
					path_factory(const path_factory& other) = default;
					path_factory& operator=(const path_factory& other) = default;
					path_factory(path_factory&& other) noexcept;
					path_factory& operator=(path_factory&& other) noexcept;

					// Modifiers
					void append(const path_factory& p);
					void append(const path_factory& p, ::std::error_code& ec) noexcept;
					void append(const ::std::vector<path_data_item>& p);
					void append(const ::std::vector<path_data_item>& p, ::std::error_code& ec) noexcept;
					void new_sub_path();
					void new_sub_path(::std::error_code& ec) noexcept;
					void close_path();
					void close_path(::std::error_code& ec) noexcept;
					void arc(const vector_2d& center, double radius, double angle1, double angle2);
					void arc(const vector_2d& center, double radius, double angle1, double angle2, ::std::error_code& ec) noexcept;
					void arc_negative(const vector_2d& center, double radius, double angle1, double angle2);
					void arc_negative(const vector_2d& center, double radius, double angle1, double angle2, ::std::error_code& ec) noexcept;
					void curve_to(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2);
					void curve_to(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, ::std::error_code& ec) noexcept;
					void line_to(const vector_2d& pt);
					void line_to(const vector_2d& pt, ::std::error_code& ec) noexcept;
					void move_to(const vector_2d& pt);
					void move_to(const vector_2d& pt, ::std::error_code& ec) noexcept;
					void rectangle(const ::std::experimental::io2d::rectangle& r, bool cw = true);
					void rectangle(const ::std::experimental::io2d::rectangle& r, ::std::error_code& ec, bool cw = true) noexcept;
					void rel_curve_to(const vector_2d& dpt0, const vector_2d& dpt1, const vector_2d& dpt2);
					void rel_curve_to(const vector_2d& dpt0, const vector_2d& dpt1, const vector_2d& dpt2, ::std::error_code& ec) noexcept;
					void rel_line_to(const vector_2d& dpt);
					void rel_line_to(const vector_2d& dpt, ::std::error_code& ec) noexcept;
					void rel_move_to(const vector_2d& dpt);
					void rel_move_to(const vector_2d& dpt, ::std::error_code& ec) noexcept;
					void change_matrix(const matrix_2d& m);
					void change_matrix(const matrix_2d& m, ::std::error_code& ec) noexcept;
					void change_origin(const vector_2d& pt);
					void change_origin(const vector_2d& pt, ::std::error_code& ec) noexcept;
					void clear() noexcept;
					void add_text(const font_resource& fr, const ::std::string& utf8, const vector_2d& pt);
					void add_text(const font_resource& fr, const ::std::string& utf8, const vector_2d& pt, ::std::error_code& ec) noexcept;
					void add_glyph_run(const font_resource& fr, const glyph_run& gr);
					void add_glyph_run(const font_resource& fr, const glyph_run& gr, ::std::error_code& ec) noexcept;

					// Observers
					::std::experimental::io2d::rectangle path_extents() const;
					::std::experimental::io2d::rectangle path_extents(::std::error_code& ec) const noexcept;
					bool has_current_point() const noexcept;
					vector_2d current_point() const;
					vector_2d current_point(::std::error_code& ec) const noexcept;
					matrix_2d current_matrix() const noexcept;
					vector_2d current_origin() const noexcept;
					::std::vector<path_data_item> data() const;
					::std::vector<path_data_item> data(::std::error_code& ec) const noexcept;
					path_data_item data_item(unsigned int index) const;
					path_data_item data_item(unsigned int index, ::std::error_code& ec) const noexcept;
					const ::std::vector<path_data_item>& data_ref() const noexcept;
				};

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
					device(device&& other) noexcept;
					device& operator=(device&& other) noexcept;

					// Modifiers
					void flush() noexcept;
					void lock();
					void lock(::std::error_code& ec) noexcept;
					void unlock();
					void unlock(::std::error_code& ec) noexcept;
				};

				class font_options {
					::std::experimental::io2d::antialias _Antialias = ::std::experimental::io2d::antialias::default_antialias;
					::std::experimental::io2d::subpixel_order _Subpixel_order = ::std::experimental::io2d::subpixel_order::default_subpixel_order;
				public:
					font_options() noexcept = default;
					font_options(const font_options&) noexcept = default;
					font_options& operator=(const font_options&) noexcept = default;
					font_options(font_options&& other) noexcept;
					font_options& operator=(font_options&& other) noexcept;
					font_options(::std::experimental::io2d::antialias a, ::std::experimental::io2d::subpixel_order so) noexcept;

					// Modifiers
					void antialias(::std::experimental::io2d::antialias a) noexcept;
					void subpixel_order(::std::experimental::io2d::subpixel_order so) noexcept;

					// Observers
					::std::experimental::io2d::antialias antialias() const noexcept;
					::std::experimental::io2d::subpixel_order subpixel_order() const noexcept;
				};

				class font_resource_factory {
					::std::string _Family;
					::std::experimental::io2d::font_slant _Font_slant = ::std::experimental::io2d::font_slant::normal;
					::std::experimental::io2d::font_weight _Font_weight = ::std::experimental::io2d::font_weight::normal;
					::std::experimental::io2d::font_options _Font_options;
					matrix_2d _Font_matrix;
					matrix_2d _Surface_matrix;

				public:
					font_resource_factory() = default;
					font_resource_factory(const font_resource_factory&) = default;
					font_resource_factory& operator=(const font_resource_factory&) = default;
					font_resource_factory(font_resource_factory&&) noexcept = default;
					font_resource_factory& operator=(font_resource_factory&&) noexcept;// = default;
					explicit font_resource_factory(const ::std::string& family,
						::std::experimental::io2d::font_slant fs = ::std::experimental::io2d::font_slant::normal,
						::std::experimental::io2d::font_weight fw = ::std::experimental::io2d::font_weight::normal,
						const matrix_2d& fm = matrix_2d::init_scale({ 16.0, 16.0 }),
						const ::std::experimental::io2d::font_options& fo = ::std::experimental::io2d::font_options(),
						const matrix_2d& sm = matrix_2d::init_identity());
					font_resource_factory(const ::std::string& family,
						::std::error_code& ec,
						::std::experimental::io2d::font_slant fs = ::std::experimental::io2d::font_slant::normal,
						::std::experimental::io2d::font_weight fw = ::std::experimental::io2d::font_weight::normal,
						const matrix_2d& fm = matrix_2d::init_scale({ 16.0, 16.0 }),
						const ::std::experimental::io2d::font_options& fo = ::std::experimental::io2d::font_options(),
						const matrix_2d& sm = matrix_2d::init_identity()) noexcept;

					// Modifiers
					void font_family(const ::std::string& f);
					void font_family(const ::std::string& f, ::std::error_code& ec) noexcept;
					void font_slant(const ::std::experimental::io2d::font_slant fs);
					void font_slant(const ::std::experimental::io2d::font_slant fs, ::std::error_code& ec) noexcept;
					void font_weight(::std::experimental::io2d::font_weight fw);
					void font_weight(::std::experimental::io2d::font_weight fw, ::std::error_code& ec) noexcept;
					void font_options(const ::std::experimental::io2d::font_options& fo) noexcept;
					void font_matrix(const matrix_2d& m) noexcept;
					void surface_matrix(const matrix_2d& m) noexcept;

					// Observers
					::std::string font_family() const;
					::std::string font_family(::std::error_code& ec) const noexcept;
					::std::experimental::io2d::font_slant font_slant() const noexcept;
					::std::experimental::io2d::font_weight font_weight() const noexcept;
					::std::experimental::io2d::font_options font_options() const noexcept;
					matrix_2d font_matrix() const noexcept;
					matrix_2d surface_matrix() const noexcept;
				};

				//Forward declaration
				class glyph_run;
				class path_factory;

				class font_resource {
					friend surface;
					friend glyph_run;
					friend path_factory;

					::std::shared_ptr<cairo_scaled_font_t> _Scaled_font;
					::std::shared_ptr<::std::string> _Font_family;
					::std::experimental::io2d::font_slant _Font_slant;
					::std::experimental::io2d::font_weight _Font_weight;
					::std::shared_ptr<cairo_font_options_t> _Font_options;

				public:
					font_resource() = delete;
					font_resource(const font_resource&) noexcept = default;
					font_resource& operator=(const font_resource&) noexcept = default;
					font_resource(font_resource&&) noexcept = default;
					font_resource& operator=(font_resource&&) noexcept = default;
					explicit font_resource(const font_resource_factory& f);
					font_resource(const font_resource_factory& f, ::std::error_code& ec) noexcept;

					// Observers
					::std::string font_family() const;
					::std::string font_family(::std::error_code& ec) const noexcept;
					::std::experimental::io2d::font_slant font_slant() const noexcept;
					::std::experimental::io2d::font_weight font_weight() const noexcept;
					::std::experimental::io2d::font_options font_options() const noexcept;
					matrix_2d font_matrix() const noexcept;
					matrix_2d surface_matrix() const noexcept;
					::std::experimental::io2d::font_extents font_extents() const noexcept;
					::std::experimental::io2d::text_extents text_extents(const ::std::string& utf8) const noexcept;
					glyph_run make_glyph_run(const ::std::string& utf8, const vector_2d& pos) const;
					glyph_run make_glyph_run(const ::std::string& utf8, const vector_2d& pos, ::std::error_code& ec) const noexcept;
				};

				class glyph_run {
					friend ::std::experimental::io2d::font_resource;
					friend surface;
					friend path_factory;

				public:
					class glyph {
						friend glyph_run;
					public:
						typedef unsigned long index_type; // impldef
					private:
						index_type _Index = 0;
						double _X = 0.0;
						double _Y = 0.0;
						cairo_glyph_t* _Native_glyph = nullptr;
					public:
						glyph() noexcept = default;
						glyph(const glyph&) noexcept = default;
						glyph& operator=(const glyph&) noexcept = default;
						glyph(glyph&&) noexcept = default;
						glyph& operator=(glyph&&) noexcept = default;
						glyph(index_type i, double x, double y) noexcept;

						// Modifiers
						void index(index_type i) noexcept;
						void x(double val) noexcept;
						void y(double val) noexcept;

						// Observers
						index_type index() const noexcept;
						double x() const noexcept;
						double y() const noexcept;
					};

					class cluster {
						friend glyph_run;
						// Clusters are useful when dealing with ligatures and ordering in scripts that require complex text layout.
						int _Glyph_count = 0; // Note: It's possible that processing could result in a cluster where one or more characters map to zero glyphs due to the previous or next cluster.
						int _Byte_count = 0; // Note: UTF-8 is variable byte length. A single cluster can map to multiple characters. Lastly, it's possible that processing could result in a cluster with one or more glyphs map to zero characters due to the previous or next cluster.
						cairo_text_cluster_t* _Native_cluster = nullptr;
					public:
						cluster() noexcept = default;
						cluster(const cluster&) noexcept = default;
						cluster& operator=(const cluster&) noexcept = default;
						cluster(cluster&&) noexcept = default;
						cluster& operator=(cluster&&) noexcept = default;
						cluster(int glyphs, int bytes) noexcept;

						// Modifiers
						void glyph_count(int count) noexcept;
						void byte_count(int count) noexcept;

						// Observers
						int glyph_count() const noexcept;
						int byte_count() const noexcept;
					};

				private:
					::std::string _Text_string;
					::std::experimental::io2d::font_resource _Font_resource;
					::std::vector<glyph> _Glyphs;
					::std::vector<cluster> _Clusters;
					::std::shared_ptr<cairo_glyph_t> _Cairo_glyphs;
					::std::shared_ptr<cairo_text_cluster_t> _Cairo_text_clusters;
					vector_2d _Position;
					cairo_text_cluster_flags_t _Text_cluster_flags;

					glyph_run(const ::std::experimental::io2d::font_resource& fr, const ::std::string& utf8, const vector_2d& pos);
					glyph_run(const ::std::experimental::io2d::font_resource& fr, const ::std::string& utf8, const vector_2d& pos, ::std::error_code& ec) noexcept;

				public:
					glyph_run(const glyph_run&) = default;
					glyph_run& operator=(const glyph_run&) = default;
					glyph_run(glyph_run&&) noexcept = default;
					glyph_run& operator=(glyph_run&&) noexcept;

					// Modifiers
					::std::vector<glyph>& glyphs() noexcept;
					::std::vector<cluster>& clusters() noexcept;

					// Observers
					const ::std::string& original_text() const noexcept;
					const ::std::vector<glyph>& glyphs() const noexcept;
					const ::std::vector<cluster>& clusters() const noexcept;
					const ::std::experimental::io2d::font_resource& font_resource() const noexcept;
					bool reversed_clusters() const noexcept;
					vector_2d position() const noexcept;
					text_extents extents() const noexcept;
				};

				// Forward declaration.
				class linear_brush_factory;
				//class mesh_brush_factory;
				class radial_brush_factory;
				class solid_color_brush_factory;
				class surface_brush_factory;
				class surface;
				class image_surface;
				class display_surface;

				class brush {
				public:
					typedef cairo_pattern_t* native_handle_type;

				private:
					friend linear_brush_factory;
					//friend mesh_brush_factory;
					friend radial_brush_factory;
					friend solid_color_brush_factory;
					friend surface_brush_factory;
					friend surface;
					friend display_surface;
					// Precondition: nh has already had its reference count incremented (either in creation or with cairo_pattern_reference).
					brush(native_handle_type nh) noexcept;

					::std::shared_ptr<cairo_pattern_t> _Brush;
					brush_type _Brush_type;
					::std::experimental::io2d::extend _Extend;
					::std::experimental::io2d::filter _Filter;
					matrix_2d _Matrix;

				public:
					native_handle_type native_handle() const noexcept;

					brush() = delete;
					brush(const brush&) noexcept = default;
					brush& operator=(const brush&) noexcept = default;
					brush(brush&& other) noexcept;
					brush& operator=(brush&& other) noexcept;
					brush(const solid_color_brush_factory& f);
					brush(const solid_color_brush_factory& f, ::std::error_code& ec) noexcept;
					brush(const linear_brush_factory& f);
					brush(const linear_brush_factory& f, ::std::error_code& ec) noexcept;
					brush(const radial_brush_factory& f);
					brush(const radial_brush_factory& f, ::std::error_code& ec) noexcept;
					//brush(const mesh_brush_factory& f);
					//brush(const mesh_brush_factory& f, ::std::error_code& ec) noexcept;
					brush(surface_brush_factory& f);
					brush(surface_brush_factory& f, ::std::error_code& ec) noexcept;

					void extend(::std::experimental::io2d::extend e) noexcept;
					void filter(::std::experimental::io2d::filter f) noexcept;
					void matrix(const matrix_2d& m) noexcept;

					::std::experimental::io2d::extend extend() const noexcept;
					::std::experimental::io2d::filter filter() const noexcept;
					matrix_2d matrix() const noexcept;
					brush_type type() const noexcept;
				};

				class solid_color_brush_factory {
					rgba_color _Color;

				public:
					solid_color_brush_factory() noexcept;
					solid_color_brush_factory(const solid_color_brush_factory&) noexcept = default;
					solid_color_brush_factory& operator=(const solid_color_brush_factory&) noexcept = default;
					solid_color_brush_factory(solid_color_brush_factory&& other) noexcept;
					solid_color_brush_factory& operator=(solid_color_brush_factory&& other) noexcept;
					solid_color_brush_factory(const rgba_color& color) noexcept;

					// Modifiers
					void color(const rgba_color& color) noexcept;

					// Observers
					rgba_color color() const noexcept;
				};

				class linear_brush_factory {
					vector_2d _Begin_point;
					vector_2d _End_point;
					typedef ::std::vector<::std::tuple<double, rgba_color>> _Color_stop_collection_type;
					_Color_stop_collection_type _Color_stops;
					typedef _Color_stop_collection_type::difference_type difference_type;

				public:
					typedef _Color_stop_collection_type::size_type size_type;

					linear_brush_factory() noexcept;
					linear_brush_factory(const linear_brush_factory&) = default;
					linear_brush_factory& operator=(const linear_brush_factory&) = default;
					linear_brush_factory(linear_brush_factory&& other) noexcept;
					linear_brush_factory& operator=(linear_brush_factory&& other) noexcept;
					linear_brush_factory(const vector_2d& begin, const vector_2d& end) noexcept;

					// Modifiers
					void add_color_stop(double offset, const rgba_color& color);
					void add_color_stop(double offset, const rgba_color& color, ::std::error_code& ec) noexcept;
					void color_stop(size_type index, double offset, const rgba_color& color);
					void color_stop(size_type index, double offset, const rgba_color& color, ::std::error_code& ec) noexcept;
					void remove_color_stop(size_type index);
					void remove_color_stop(size_type index, ::std::error_code& ec) noexcept;
					void begin_point(const vector_2d& value) noexcept;
					void end_point(const vector_2d& value) noexcept;

					// Observers
					size_type color_stop_count() const noexcept;
					::std::tuple<double, rgba_color> color_stop(size_type index) const;
					::std::tuple<double, rgba_color> color_stop(size_type index, ::std::error_code& ec) const noexcept;
					::std::vector<::std::tuple<double, rgba_color>>& color_stops() noexcept;
					const ::std::vector<::std::tuple<double, rgba_color>>& color_stops() const noexcept;
					vector_2d begin_point() const noexcept;
					vector_2d end_point() const noexcept;
				};

				class radial_brush_factory {
					vector_2d _Center0;
					double _Radius0;
					vector_2d _Center1;
					double _Radius1;
					typedef ::std::vector<::std::tuple<double, rgba_color>> _Color_stop_collection_type;
					_Color_stop_collection_type _Color_stops;
					typedef _Color_stop_collection_type::difference_type difference_type;

				public:
					typedef _Color_stop_collection_type::size_type size_type;

					radial_brush_factory() noexcept;
					radial_brush_factory(const radial_brush_factory&) = default;
					radial_brush_factory& operator=(const radial_brush_factory&) = default;
					radial_brush_factory(radial_brush_factory&& other) noexcept;
					radial_brush_factory& operator=(radial_brush_factory&& other) noexcept;
					radial_brush_factory(const vector_2d& center0, double radius0, const vector_2d& center1, double radius1) noexcept;

					// Modifiers
					void add_color_stop(double offset, const rgba_color& color);
					void add_color_stop(double offset, const rgba_color& color, ::std::error_code& ec) noexcept;
					void color_stop(size_type index, double offset, const rgba_color& color);
					void color_stop(size_type index, double offset, const rgba_color& color, ::std::error_code& ec) noexcept;
					void remove_color_stop(size_type index);
					void remove_color_stop(size_type index, ::std::error_code& ec) noexcept;
					void radial_circles(const vector_2d& center0, double radius0, const vector_2d& center1, double radius1) noexcept;

					// Observers
					size_type color_stop_count() const noexcept;
					::std::tuple<double, rgba_color> color_stop(size_type index) const;
					::std::tuple<double, rgba_color> color_stop(size_type index, ::std::error_code& ec) const noexcept;
					::std::vector<::std::tuple<double, rgba_color>>& color_stops() noexcept;
					const ::std::vector<::std::tuple<double, rgba_color>>& color_stops() const noexcept;
					::std::tuple<vector_2d, double, vector_2d, double> radial_circles() const noexcept;
				};

				//class mesh_brush_factory {
				//	bool _Has_current_patch;
				//	unsigned int _Current_patch_index;
				//	int _Current_patch_side_count;
				//	vector_2d _Current_patch_initial_point;
				//	bool _Has_current_point;
				//	typedef ::std::array<::std::tuple<bool, vector_2d>, 4> _Control_points;
				//	typedef ::std::array<::std::tuple<bool, rgba_color>, 4> _Corner_colors;
				//	// <Patch data, control points, corner colors>
				//	typedef ::std::tuple<::std::experimental::io2d::path_factory, _Control_points, _Corner_colors> _Patch;
				//	::std::vector<_Patch> _Patches;
				//public:
				//	mesh_brush_factory() noexcept;
				//	mesh_brush_factory(const mesh_brush_factory&) = default;
				//	mesh_brush_factory& operator=(const mesh_brush_factory&) = default;
				//	mesh_brush_factory(mesh_brush_factory&& other) noexcept;
				//	mesh_brush_factory& operator=(mesh_brush_factory&& other) noexcept;

				//	// Modifiers
				//	void begin_patch();
				//	void begin_patch(::std::error_code& ec) noexcept;
				//	void begin_replace_patch(unsigned int patch_num);
				//	void begin_replace_patch(unsigned int patch_num, ::std::error_code& ec) noexcept;
				//	void end_patch();
				//	void end_patch(::std::error_code& ec) noexcept;
				//	void move_to(const vector_2d& pt);
				//	void move_to(const vector_2d& pt, ::std::error_code& ec) noexcept;
				//	void line_to(const vector_2d& pt);
				//	void line_to(const vector_2d& pt, ::std::error_code& ec) noexcept;
				//	void curve_to(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2);
				//	void curve_to(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, ::std::error_code& ec) noexcept;
				//	void control_point(unsigned int point_num, const vector_2d& pt);
				//	void control_point(unsigned int point_num, const vector_2d& pt, ::std::error_code& ec) noexcept;
				//	void corner_color(unsigned int corner_num, const rgba_color& color);
				//	void corner_color(unsigned int corner_num, const rgba_color& color, ::std::error_code& ec) noexcept;

				//	// Observers
				//	unsigned int patch_count() const noexcept;
				//	::std::experimental::io2d::path_factory path_factory(unsigned int patch_num) const;
				//	::std::experimental::io2d::path_factory path_factory(unsigned int patch_num, ::std::error_code& ec) const noexcept;
				//	bool control_point(unsigned int patch_num, unsigned int point_num, vector_2d& controlPoint) const;
				//	bool control_point(unsigned int patch_num, unsigned int point_num, vector_2d& controlPoint, ::std::error_code& ec) const noexcept;
				//	bool corner_color(unsigned int patch_num, unsigned int corner_num, rgba_color& color) const;
				//	bool corner_color(unsigned int patch_num, unsigned int corner_num, rgba_color& color, ::std::error_code& ec) const noexcept;
				//};

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
					::std::mutex _Lock_for_device;
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
					::std::shared_ptr<::std::experimental::io2d::path> _Current_path;
					::std::experimental::io2d::path_factory _Immediate_path;
					typedef matrix_2d _Transform_matrix_type;
					_Transform_matrix_type _Transform_matrix;
					::std::experimental::io2d::font_resource _Font_resource;

					// Relies on C++17 noexcept guarantee for vector default ctor (N4258, adopted 2014-11).
					::std::stack<::std::tuple<
						::std::experimental::io2d::brush,
						::std::experimental::io2d::antialias,
						::std::experimental::io2d::dashes,
						::std::experimental::io2d::fill_rule,
						::std::experimental::io2d::line_cap,
						::std::experimental::io2d::line_join,
						_Line_width_type,
						_Miter_limit_type,
						::std::experimental::io2d::compositing_operator,
						::std::shared_ptr<::std::experimental::io2d::path>,
						::std::experimental::io2d::path_factory,
						_Transform_matrix_type,
						::std::experimental::io2d::font_resource
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
						::std::shared_ptr<::std::experimental::io2d::path>,
						::std::experimental::io2d::path_factory,
						_Transform_matrix_type,
						::std::experimental::io2d::font_resource>>> _Saved_state;

					void _Ensure_state();
					void _Ensure_state(::std::error_code& ec) noexcept;

					surface(::std::experimental::io2d::format fmt, int width, int height);
					surface(::std::experimental::io2d::format fmt, int width, int height, ::std::error_code& ec) noexcept;

					surface(native_handle_type nh, ::std::experimental::io2d::format fmt, ::std::experimental::io2d::content ctnt);
					surface(native_handle_type nh, ::std::experimental::io2d::format fmt, ::std::experimental::io2d::content ctnt, ::std::error_code& ec) noexcept;

					// create_similar
					surface(const surface& other, ::std::experimental::io2d::content ctnt, int width, int height);
					surface(const surface& other, ::std::experimental::io2d::content ctnt, int width, int height, ::std::error_code& ec) noexcept;

					void path(const ::std::shared_ptr<::std::experimental::io2d::path>& p);
					void path(const ::std::shared_ptr<::std::experimental::io2d::path>& p, ::std::error_code& ec) noexcept;
				public:
					bool _Has_surface_resource() const noexcept;
					native_handle_type native_handle() const;

					surface() = delete;
					surface(const surface&) = delete;
					surface& operator=(const surface&) = delete;
					surface(surface&& other) noexcept;
					surface& operator=(surface&& other) noexcept;

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
					void brush(experimental::nullopt_t) noexcept;
					void brush(const ::std::experimental::io2d::brush& source);
					void brush(const ::std::experimental::io2d::brush& source, ::std::error_code& ec) noexcept;
					void antialias(::std::experimental::io2d::antialias a) noexcept;
					void dashes(experimental::nullopt_t) noexcept;
					void dashes(const ::std::experimental::io2d::dashes& d);
					void dashes(const ::std::experimental::io2d::dashes& d, ::std::error_code& ec) noexcept;
					void fill_rule(::std::experimental::io2d::fill_rule fr) noexcept;
					void line_cap(::std::experimental::io2d::line_cap lc) noexcept;
					void line_join(::std::experimental::io2d::line_join lj) noexcept;
					void line_width(double width) noexcept;
					void miter_limit(double limit) noexcept;
					void compositing_operator(::std::experimental::io2d::compositing_operator co) noexcept;
					//void clip(experimental::nullopt_t) noexcept;
					void clip(const ::std::experimental::io2d::path& p);
					void clip(const ::std::experimental::io2d::path& p, ::std::error_code& ec) noexcept;
					void clip_immediate();
					void clip_immediate(::std::error_code& ec) noexcept;
					void path(experimental::nullopt_t) noexcept;
					void path(const ::std::experimental::io2d::path& p);
					void path(const ::std::experimental::io2d::path& p, ::std::error_code& ec) noexcept;

					// \ref{\iotwod.surface.modifiers.immediatepath}, immediate path modifiers:
					::std::experimental::io2d::path_factory& immediate() noexcept;

					// \ref{\iotwod.surface.modifiers.render}, render modifiers:
					void clear();
					void fill();
					void fill(::std::error_code& ec) noexcept;
					void fill(const rgba_color& c);
					void fill(const rgba_color& c, ::std::error_code& ec) noexcept;
					void fill(const ::std::experimental::io2d::brush& b);
					void fill(const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void fill(const surface& s, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good);
					void fill(const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good) noexcept;
					void fill_immediate();
					void fill_immediate(::std::error_code& ec) noexcept;
					void fill_immediate(const rgba_color& c);
					void fill_immediate(const rgba_color& c, ::std::error_code& ec) noexcept;
					void fill_immediate(const ::std::experimental::io2d::brush& b);
					void fill_immediate(const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void fill_immediate(const surface& s, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good);
					void fill_immediate(const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good) noexcept;
					void paint();
					void paint(::std::error_code& ec) noexcept;
					void paint(const rgba_color& c);
					void paint(const rgba_color& c, ::std::error_code& ec) noexcept;
					void paint(const ::std::experimental::io2d::brush& b);
					void paint(const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void paint(const surface& s, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good);
					void paint(const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good) noexcept;
					void paint(double alpha);
					void paint(double alpha, ::std::error_code& ec) noexcept;
					void paint(const rgba_color& c, double alpha);
					void paint(const rgba_color& c, double alpha, ::std::error_code& ec) noexcept;
					void paint(const ::std::experimental::io2d::brush& b, double alpha);
					void paint(const ::std::experimental::io2d::brush& b, double alpha, ::std::error_code& ec) noexcept;
					void paint(const surface& s, double alpha, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good);
					void paint(const surface& s, double alpha, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good) noexcept;
					void stroke();
					void stroke(::std::error_code& ec) noexcept;
					void stroke(const rgba_color& c);
					void stroke(const rgba_color& c, ::std::error_code& ec) noexcept;
					void stroke(const ::std::experimental::io2d::brush& b);
					void stroke(const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void stroke(const surface& s, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good);
					void stroke(const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good) noexcept;
					void stroke_immediate();
					void stroke_immediate(::std::error_code& ec) noexcept;
					void stroke_immediate(const rgba_color& c);
					void stroke_immediate(const rgba_color& c, ::std::error_code& ec) noexcept;
					void stroke_immediate(const ::std::experimental::io2d::brush& b);
					void stroke_immediate(const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void stroke_immediate(const surface& s, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good);
					void stroke_immediate(const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good) noexcept;

					// \ref{\iotwod.surface.modifiers.maskrender}, mask render modifiers:
					void mask(const ::std::experimental::io2d::brush& maskBrush);
					void mask(const ::std::experimental::io2d::brush& maskBrush, ::std::error_code& ec) noexcept;
					void mask(const ::std::experimental::io2d::brush& maskBrush, const rgba_color& c);
					void mask(const ::std::experimental::io2d::brush& maskBrush, const rgba_color& c, ::std::error_code& ec) noexcept;
					void mask(const ::std::experimental::io2d::brush& maskBrush, const ::std::experimental::io2d::brush& b);
					void mask(const ::std::experimental::io2d::brush& maskBrush, const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void mask(const ::std::experimental::io2d::brush& maskBrush, const surface& s, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good);
					void mask(const ::std::experimental::io2d::brush& maskBrush, const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good) noexcept;
					void mask(surface& maskSurface, const matrix_2d& maskMatrix = matrix_2d::init_identity(), extend maskExtend = extend::none, filter maskFilter = filter::good);
					void mask(surface& maskSurface, ::std::error_code& ec, const matrix_2d& maskMatrix = matrix_2d::init_identity(), extend maskExtend = extend::none, filter maskFilter = filter::good) noexcept;
					void mask(surface& maskSurface, const rgba_color& c, const matrix_2d& maskMatrix = matrix_2d::init_identity(), extend maskExtend = extend::none, filter maskFilter = filter::good);
					void mask(surface& maskSurface, const rgba_color& c, ::std::error_code& ec, const matrix_2d& maskMatrix = matrix_2d::init_identity(), extend maskExtend = extend::none, filter maskFilter = filter::good) noexcept;
					void mask(surface& maskSurface, const ::std::experimental::io2d::brush& b, const matrix_2d& maskMatrix = matrix_2d::init_identity(), extend maskExtend = extend::none, filter maskFilter = filter::good);
					void mask(surface& maskSurface, const ::std::experimental::io2d::brush& b, ::std::error_code& ec, const matrix_2d& maskMatrix = matrix_2d::init_identity(), extend maskExtend = extend::none, filter maskFilter = filter::good) noexcept;
					void mask(surface& maskSurface, const surface& s, const matrix_2d& maskMatrix = matrix_2d::init_identity(), const matrix_2d& m = matrix_2d::init_identity(), extend maskExtend = extend::none, extend e = extend::none, filter maskFilter = filter::good, filter f = filter::good);
					void mask(surface& maskSurface, const surface& s, ::std::error_code& ec, const matrix_2d& maskMatrix = matrix_2d::init_identity(), const matrix_2d& m = matrix_2d::init_identity(), extend maskExtend = extend::none, extend e = extend::none, filter maskFilter = filter::good, filter f = filter::good) noexcept;
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush);
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, ::std::error_code& ec) noexcept;
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const rgba_color& c);
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const rgba_color& c, ::std::error_code& ec) noexcept;
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const ::std::experimental::io2d::brush& b);
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const surface& s, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good);
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good) noexcept;
					void mask_immediate(surface& maskSurface, const matrix_2d& maskMatrix = matrix_2d::init_identity(), extend maskExtend = extend::none, filter maskFilter = filter::good);
					void mask_immediate(surface& maskSurface, ::std::error_code& ec, const matrix_2d& maskMatrix = matrix_2d::init_identity(), extend maskExtend = extend::none, filter maskFilter = filter::good) noexcept;
					void mask_immediate(surface& maskSurface, const rgba_color& c, const matrix_2d& maskMatrix = matrix_2d::init_identity(), extend maskExtend = extend::none, filter maskFilter = filter::good);
					void mask_immediate(surface& maskSurface, const rgba_color& c, ::std::error_code& ec, const matrix_2d& maskMatrix = matrix_2d::init_identity(), extend maskExtend = extend::none, filter maskFilter = filter::good) noexcept;
					void mask_immediate(surface& maskSurface, const ::std::experimental::io2d::brush& b, const matrix_2d& maskMatrix = matrix_2d::init_identity(), extend maskExtend = extend::none, filter maskFilter = filter::good);
					void mask_immediate(surface& maskSurface, const ::std::experimental::io2d::brush& b, ::std::error_code& ec, const matrix_2d& maskMatrix = matrix_2d::init_identity(), extend maskExtend = extend::none, filter maskFilter = filter::good) noexcept;
					void mask_immediate(surface& maskSurface, const surface& s, const matrix_2d& maskMatrix = matrix_2d::init_identity(), const matrix_2d& m = matrix_2d::init_identity(), extend maskExtend = extend::none, extend e = extend::none, filter maskFilter = filter::good, filter f = filter::good);
					void mask_immediate(surface& maskSurface, const surface& s, ::std::error_code& ec, const matrix_2d& maskMatrix = matrix_2d::init_identity(), const matrix_2d& m = matrix_2d::init_identity(), extend maskExtend = extend::none, extend e = extend::none, filter maskFilter = filter::good, filter f = filter::good) noexcept;

					// \ref{\iotwod.surface.modifiers.textrender}, text render modifiers:
					vector_2d render_text(const ::std::string& utf8, const vector_2d& position);
					vector_2d render_text(const ::std::string& utf8, const vector_2d& position, ::std::error_code& ec) noexcept;
					vector_2d render_text(const ::std::string& utf8, const vector_2d& position, const rgba_color& c);
					vector_2d render_text(const ::std::string& utf8, const vector_2d& position, const rgba_color& c, ::std::error_code& ec) noexcept;
					vector_2d render_text(const ::std::string& utf8, const vector_2d& position, const ::std::experimental::io2d::brush& b);
					vector_2d render_text(const ::std::string& utf8, const vector_2d& position, const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					vector_2d render_text(const ::std::string& utf8, const vector_2d& position, const surface& s, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good);
					vector_2d render_text(const ::std::string& utf8, const vector_2d& position, const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good) noexcept;
					void render_glyph_run(const glyph_run& gr);
					void render_glyph_run(const glyph_run& gr, ::std::error_code& ec) noexcept;
					void render_glyph_run(const glyph_run& gr, const rgba_color& c);
					void render_glyph_run(const glyph_run& gr, const rgba_color& c, ::std::error_code& ec) noexcept;
					void render_glyph_run(const glyph_run& gr, const ::std::experimental::io2d::brush& b);
					void render_glyph_run(const glyph_run& gr, const ::std::experimental::io2d::brush& b, ::std::error_code& ec) noexcept;
					void render_glyph_run(const glyph_run& gr, const surface& s, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good);
					void render_glyph_run(const glyph_run& gr, const surface& s, ::std::error_code& ec, const matrix_2d& m = matrix_2d::init_identity(), extend e = extend::none, filter f = filter::good) noexcept;

					// \ref{\iotwod.surface.modifiers.transform}, transformation modifiers:
					void matrix(const matrix_2d& matrix);
					void matrix(const matrix_2d& matrix, ::std::error_code& ec) noexcept;

					// \ref{\iotwod.surface.modifiers.font}, font modifiers:
					void font_resource(const ::std::experimental::io2d::font_resource& f) noexcept;
					void font_resource(const ::std::string& family, double size, font_slant sl = font_slant::normal, font_weight w = font_weight::normal);
					void font_resource(const ::std::string& family, double size, ::std::error_code& ec, font_slant sl = font_slant::normal, font_weight w = font_weight::normal) noexcept;
					//void font_face(const ::std::experimental::io2d::font_face& f);
					//void font_face(const ::std::experimental::io2d::font_face& f, ::std::error_code& ec) noexcept;
					//void font_size(double s);
					//void font_size(double s, ::std::error_code& ec) noexcept;
					//void font_matrix(const matrix_2d& m);
					//void font_matrix(const matrix_2d& m, ::std::error_code& ec) noexcept;
					//void font_options(const font_options& fo) noexcept;

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
					::std::experimental::io2d::font_extents font_extents() const noexcept;
					::std::experimental::io2d::text_extents text_extents(const ::std::string& utf8) const;
					::std::experimental::io2d::text_extents text_extents(const ::std::string& utf8, ::std::error_code& ec) const noexcept;

					// \ref{\iotwod.surface.observers.transform}, transformation observers:
					matrix_2d matrix() const noexcept;
					vector_2d user_to_surface(const vector_2d& pt) const noexcept;
					vector_2d user_to_surface_distance(const vector_2d& dpt) const noexcept;
					vector_2d surface_to_user(const vector_2d& pt) const;
					vector_2d surface_to_user(const vector_2d& pt, ::std::error_code& ec) const noexcept;
					vector_2d surface_to_user_distance(const vector_2d& dpt) const;
					vector_2d surface_to_user_distance(const vector_2d& dpt, ::std::error_code& ec) const noexcept;

					// \ref{\iotwod.surface.observers.font}, font observers:
					::std::experimental::io2d::font_resource font_resource() const noexcept;

					//matrix_2d font_matrix() const noexcept;
					//::std::experimental::io2d::font_options font_options() const noexcept;
					//::std::experimental::io2d::font_face font_face() const;
					//::std::experimental::io2d::font_face font_face(::std::error_code& ec) const noexcept;
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
					image_surface(image_surface&& other) noexcept;
					image_surface& operator=(image_surface&& other) noexcept;
					image_surface(::std::experimental::io2d::format fmt, int width, int height);
					image_surface(::std::experimental::io2d::format fmt, int width, int height, ::std::error_code& ec) noexcept;
					image_surface(::std::vector<unsigned char>& data, ::std::experimental::io2d::format fmt, int width, int height);
					image_surface(::std::vector<unsigned char>& data, ::std::experimental::io2d::format fmt, int width, int height, ::std::error_code& ec) noexcept;
					//// create_similar_image
					//image_surface(const surface& other, ::std::experimental::io2d::format fmt, int width, int height);
					//image_surface(const surface& other, ::std::experimental::io2d::format fmt, int width, int height, ::std::error_code& ec) noexcept;
					//// create_from_png
					//image_surface(const ::std::string& filename);
					virtual ~image_surface();

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
					void letterbox_brush(experimental::nullopt_t) noexcept;
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

				class surface_brush_factory {
					::std::unique_ptr<image_surface> _Surface;

					friend ::std::experimental::io2d::brush;

				public:
					surface_brush_factory() noexcept;
					surface_brush_factory(const surface_brush_factory&) = delete;
					surface_brush_factory& operator=(const surface_brush_factory&) = delete;
					surface_brush_factory(surface_brush_factory&& other) noexcept;
					surface_brush_factory& operator=(surface_brush_factory&& other) noexcept;
					surface_brush_factory(::std::experimental::io2d::surface& s);
					surface_brush_factory(::std::experimental::io2d::surface& s, ::std::error_code& ec) noexcept;

					// Modifiers
					void surface(::std::experimental::io2d::surface& s);
					void surface(::std::experimental::io2d::surface& s, ::std::error_code& ec) noexcept;

					// Observers
					bool has_surface() const noexcept;
					const image_surface& surface() const;
				};
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
				int format_stride_for_width(format format, int width) noexcept;
				display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, scaling scl = scaling::letterbox, refresh_rate rr = refresh_rate::as_fast_as_possible, double desiredFramerate = 30.0);
				display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, ::std::error_code& ec, scaling scl = scaling::letterbox, refresh_rate rr = refresh_rate::as_fast_as_possible, double desiredFramerate = 30.0) noexcept;
				display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, scaling scl = scaling::letterbox, refresh_rate rr = refresh_rate::as_fast_as_possible, double desiredFramerate = 30.0);
				display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat,
					int preferredDisplayWidth, int preferredDisplayHeight, ::std::error_code& ec, scaling scl = scaling::letterbox, refresh_rate rr = refresh_rate::as_fast_as_possible, double desiredFramerate = 30.0) noexcept;
				image_surface make_image_surface(format format, int width, int height);
				image_surface make_image_surface(format format, int width, int height, ::std::error_code& ec) noexcept;
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}

	template<>
	struct is_error_condition_enum<::std::experimental::io2d::io2d_error>
		: public ::std::true_type{ };

	//template<>
	//struct is_error_code_enum<::cairo_status_t>
	//	: public ::std::true_type{ };

	::std::error_condition make_error_condition(experimental::io2d::io2d_error e) noexcept;

//	::std::error_code make_error_code(cairo_status_t e) noexcept;

	::std::error_code make_error_code(experimental::io2d::io2d_error e) noexcept;
}

#endif
