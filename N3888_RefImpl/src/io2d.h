#pragma once

#ifndef _IO2D_
#define _IO2D_

#define __cpp_lib_experimental_io2d 201505

#include "xio2d.h"

#include <memory>
#include <functional>
#include <exception>
#include <vector>
#include <string>
#include <algorithm>
#include <system_error>

#ifdef _WIN32_WINNT
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
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
				enum class io2d_error;
				enum class antialias;
				enum class content;
				enum class fill_rule;
				enum class line_cap;
				enum class line_join;
				enum class compositing_operator;
				enum class format;
				enum class extend;
				enum class filter;
				enum class brush_type;
				enum class font_slant;
				enum class font_weight;
				enum class subpixel_order;
				enum class path_data_type;
				enum class scaling;
				class io2d_error_category;
				class rectangle;
				class rgba_color;
				class vector_2d;
				class font_extents;
				class text_extents;
				class matrix_2d;
				class path_data;
				class _Point;
				class move_to;
				class line_to;
				class rel_move_to;
				class rel_line_to;
				class _Curve_to;
				class curve_to;
				class rel_curve_to;
				class _Arc;
				class arc;
				class arc_negative;
				class new_sub_path;
				class close_path;
				class change_matrix;
				class change_origin;
				class path;
				class path_factory;
				class device;
				class font_options;
				class font_fact;
				class simple_font_face;
				class brush;
				class solid_color_brush_factory;
				class linear_brush_factory;
				class radial_brush_factory;
				class mesh_brush_factory;
				struct _Surface_native_handles;
				class surface;
				class image_surface;
				class display_surface;
				class surface_brush_factory;
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}

namespace std {
	namespace experimental {
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
					clear,
					source,
					over,
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
					hsl_luminosity,
					default_op = over
				};

				enum class format {
					invalid,
					argb32,
					rgb24,
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
					radial,
					mesh
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

				class io2d_error_category : public ::std::error_category {
				public:
					// Observers
					virtual const char* name() const noexcept override;
					virtual ::std::string message(int errVal) const override;
					virtual bool equivalent(int code, const ::std::error_condition& condition) const noexcept override;
					virtual bool equivalent(const ::std::error_code& ec, int condition) const noexcept override;
				};

				const ::std::error_category& io2d_category() noexcept;

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

					void x(double value) noexcept;
					void y(double value) noexcept;
					void width(double value) noexcept;
					void height(double value) noexcept;

					double x() const noexcept;
					double y() const noexcept;
					double width() const noexcept;
					double height() const noexcept;
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

					double length() const noexcept;
					double dot(const vector_2d& other) const noexcept;
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
					double determinant() const;
					double determinant(::std::error_code& ec) const noexcept;
					vector_2d transform_distance(const vector_2d& dist) const noexcept;
					vector_2d transform_point(const vector_2d& pt) const noexcept;

					matrix_2d& operator*=(const matrix_2d& rhs) noexcept;
				};

				matrix_2d operator*(const matrix_2d& lhs, const matrix_2d& rhs) noexcept;
				bool operator==(const matrix_2d& lhs, const matrix_2d& rhs) noexcept;
				bool operator!=(const matrix_2d& lhs, const matrix_2d& rhs) noexcept;

				class path_data {
				public:
					path_data() noexcept = default;
					path_data(const path_data& other) noexcept = default;
					path_data& operator=(const path_data& other) noexcept = default;
					path_data(path_data&& other) noexcept;
					path_data& operator=(path_data&& other) noexcept;
					virtual ~path_data() noexcept;

					virtual path_data_type type() const noexcept = 0;
				};

				class _Point : public path_data {
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

				class move_to : public _Point {
				public:
					move_to() noexcept = default;
					move_to(const move_to& other) noexcept = default;
					move_to& operator=(const move_to& other) noexcept = default;
					move_to(move_to&& other) noexcept;
					move_to& operator=(move_to&& other) noexcept;
					move_to(const vector_2d& to) noexcept;
					virtual path_data_type type() const noexcept override;
				};

				class line_to : public _Point {
				public:
					line_to() noexcept = default;
					line_to(const line_to& other) noexcept = default;
					line_to& operator=(const line_to& other) noexcept = default;
					line_to(line_to&& other) noexcept;
					line_to& operator=(line_to&& other) noexcept;
					line_to(const vector_2d& to) noexcept;
					virtual path_data_type type() const noexcept override;
				};

				class rel_move_to : public _Point {
				public:
					rel_move_to() noexcept = default;
					rel_move_to(const rel_move_to& other) noexcept = default;
					rel_move_to& operator=(const rel_move_to& other) noexcept = default;
					rel_move_to(rel_move_to&& other) noexcept;
					rel_move_to& operator=(rel_move_to&& other) noexcept;
					rel_move_to(const vector_2d& to) noexcept;
					virtual path_data_type type() const noexcept override;
				};

				class rel_line_to : public _Point {
				public:
					rel_line_to() noexcept = default;
					rel_line_to(const rel_line_to& other) noexcept = default;
					rel_line_to& operator=(const rel_line_to& other) noexcept = default;
					rel_line_to(rel_line_to&& other) noexcept;
					rel_line_to& operator=(rel_line_to&& other) noexcept;
					rel_line_to(const vector_2d& to) noexcept;
					virtual path_data_type type() const noexcept override;
				};

				class _Curve_to : public path_data {
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

				class curve_to : public _Curve_to {
				public:
					curve_to() noexcept = default;
					curve_to(const curve_to& other) noexcept = default;
					curve_to& operator=(const curve_to& other) noexcept = default;
					curve_to(curve_to&& other) noexcept;
					curve_to& operator=(curve_to&& other) noexcept;
					curve_to(const vector_2d& controlPoint1, const vector_2d& controlPoint2, const vector_2d& endPoint) noexcept;
					virtual path_data_type type() const noexcept override;
				};

				class rel_curve_to : public _Curve_to {
				public:
					rel_curve_to() noexcept = default;
					rel_curve_to(const rel_curve_to& other) noexcept = default;
					rel_curve_to& operator=(const rel_curve_to& other) noexcept = default;
					rel_curve_to(rel_curve_to&& other) noexcept;
					rel_curve_to& operator=(rel_curve_to&& other) noexcept;
					rel_curve_to(const vector_2d& controlPoint1, const vector_2d& controlPoint2, const vector_2d& endPoint) noexcept;
					virtual path_data_type type() const noexcept override;
				};

				class _Arc : public path_data {
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
					_Arc(vector_2d center, double radius, double angle1, double angle2) noexcept;
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

				class arc : public _Arc {
				public:
					arc() noexcept = default;
					arc(const arc& other) noexcept = default;
					arc& operator=(const arc& other) noexcept = default;
					arc(arc&& other) noexcept;
					arc& operator=(arc&& other) noexcept;
					arc(vector_2d center, double radius, double angle1, double angle2) noexcept;

					virtual path_data_type type() const noexcept override;
				};

				class arc_negative : public _Arc {
				public:
					arc_negative() noexcept = default;
					arc_negative(const arc_negative& other) noexcept = default;
					arc_negative& operator=(const arc_negative& other) noexcept = default;
					arc_negative(arc_negative&& other) noexcept;
					arc_negative& operator=(arc_negative&& other) noexcept;
					arc_negative(vector_2d center, double radius, double angle1, double angle2) noexcept;

					virtual path_data_type type() const noexcept override;
				};

				class new_sub_path : public path_data {
				public:
					new_sub_path() noexcept = default;
					new_sub_path(const new_sub_path& other) noexcept = default;
					new_sub_path& operator=(const new_sub_path& other) noexcept = default;
					new_sub_path(new_sub_path&& other) noexcept;
					new_sub_path& operator=(new_sub_path&& other) noexcept;

					virtual path_data_type type() const noexcept override;
				};

				class close_path : public path_data {
				public:
					close_path() noexcept = default;
					close_path(const close_path& other) noexcept = default;
					close_path& operator=(const close_path& other) noexcept = default;
					close_path(close_path&& other) noexcept;
					close_path& operator=(close_path&& other) noexcept;

					virtual path_data_type type() const noexcept override;
				};

				class change_matrix : public path_data {
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

				class change_origin : public path_data {
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
					path_data_item() noexcept = default;
					path_data_item(const path_data_item&) noexcept = default;
					path_data_item& operator=(const path_data_item&) noexcept = default;
					path_data_item(path_data_item&& other) noexcept;
					path_data_item& operator=(path_data_item&& other) noexcept;
					path_data_item(const arc& value) noexcept;
					path_data_item(const arc_negative& value) noexcept;
					path_data_item(const change_matrix& value) noexcept;
					path_data_item(const change_origin& value) noexcept;
					path_data_item(const close_path& value) noexcept;
					path_data_item(const curve_to& value) noexcept;
					path_data_item(const rel_curve_to& value) noexcept;
					path_data_item(const new_sub_path& value) noexcept;
					path_data_item(const line_to& value) noexcept;
					path_data_item(const move_to& value) noexcept;
					path_data_item(const rel_line_to& value) noexcept;
					path_data_item(const rel_move_to& value) noexcept;

					void assign(const arc& value) noexcept;
					void assign(const arc_negative& value) noexcept;
					void assign(const change_matrix& value) noexcept;
					void assign(const change_origin& value) noexcept;
					void assign(const close_path& value) noexcept;
					void assign(const curve_to& value) noexcept;
					void assign(const rel_curve_to& value) noexcept;
					void assign(const new_sub_path& value) noexcept;
					void assign(const line_to& value) noexcept;
					void assign(const move_to& value) noexcept;
					void assign(const rel_line_to& value) noexcept;
					void assign(const rel_move_to& value) noexcept;

					bool has_data() const noexcept;
					path_data_type type() const;
					path_data_type type(::std::error_code& ec) const noexcept;

					::std::unique_ptr<path_data> get() const;
					::std::unique_ptr<path_data> get(::std::error_code& ec) const noexcept;

					template <class T>
					T get() const;
					template <class T>
					T get(::std::error_code& ec) const noexcept;

					template <>
					arc get() const;
					template <>
					arc get(::std::error_code& ec) const noexcept;
					template <>
					arc_negative get() const;
					template <>
					arc_negative get(::std::error_code& ec) const noexcept;
					template <>
					change_matrix get() const;
					template <>
					change_matrix get(::std::error_code& ec) const noexcept;
					template <>
					change_origin get() const;
					template <>
					change_origin get(::std::error_code& ec) const noexcept;
					template <>
					close_path get() const;
					template <>
					close_path get(::std::error_code& ec) const noexcept;
					template <>
					curve_to get() const;
					template <>
					curve_to get(::std::error_code& ec) const noexcept;
					template <>
					rel_curve_to get() const;
					template <>
					rel_curve_to get(::std::error_code& ec) const noexcept;
					template <>
					new_sub_path get() const;
					template <>
					new_sub_path get(::std::error_code& ec) const noexcept;
					template <>
					line_to get() const;
					template <>
					line_to get(::std::error_code& ec) const noexcept;
					template <>
					move_to get() const;
					template <>
					move_to get(::std::error_code& ec) const noexcept;
					template <>
					rel_line_to get() const;
					template <>
					rel_line_to get(::std::error_code& ec) const noexcept;
					template <>
					rel_move_to get() const;
					template <>
					rel_move_to get(::std::error_code& ec) const noexcept;
				};

				template <>
				arc path_data_item::get() const {
					if (_Type != path_data_type::arc) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return arc{ vector_2d{ _Data.arc.centerX, _Data.arc.centerY }, _Data.arc.radius, _Data.arc.angle1, _Data.arc.angle2 };
				}

				template <>
				arc path_data_item::get(::std::error_code& ec) const noexcept {
					if (_Type != path_data_type::arc) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return arc{ };
					}
					ec.clear();
					return arc{ vector_2d{ _Data.arc.centerX, _Data.arc.centerY }, _Data.arc.radius, _Data.arc.angle1, _Data.arc.angle2 };
				}

				template <>
				arc_negative path_data_item::get() const {
					if (_Type != path_data_type::arc_negative) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return arc_negative{ vector_2d{ _Data.arc.centerX, _Data.arc.centerY }, _Data.arc.radius, _Data.arc.angle1, _Data.arc.angle2 };
				}

				template <>
				arc_negative path_data_item::get(::std::error_code& ec) const noexcept {
					if (_Type != path_data_type::arc_negative) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return arc_negative{ };
					}
					ec.clear();
					return arc_negative{ vector_2d{ _Data.arc.centerX, _Data.arc.centerY }, _Data.arc.radius, _Data.arc.angle1, _Data.arc.angle2 };
				}

				template <>
				change_matrix path_data_item::get() const {
					if (_Type != path_data_type::change_matrix) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return change_matrix{ matrix_2d{ _Data.matrix.m00, _Data.matrix.m01, _Data.matrix.m10, _Data.matrix.m11, _Data.matrix.m20, _Data.matrix.m21 } };
				}

				template <>
				change_matrix path_data_item::get(::std::error_code& ec) const noexcept {
					if (_Type != path_data_type::change_matrix) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return change_matrix{ };
					}
					ec.clear();
					return change_matrix{ matrix_2d{ _Data.matrix.m00, _Data.matrix.m01, _Data.matrix.m10, _Data.matrix.m11, _Data.matrix.m20, _Data.matrix.m21 } };
				}

				template <>
				change_origin path_data_item::get() const {
					if (_Type != path_data_type::change_origin) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return change_origin{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				change_origin path_data_item::get(::std::error_code& ec) const noexcept{
					if (_Type != path_data_type::change_origin) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return change_origin{ };
					}
					ec.clear();
					return change_origin{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				close_path path_data_item::get() const {
					if (_Type != path_data_type::close_path) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return close_path{ };
				}

				template <>
				close_path path_data_item::get(::std::error_code& ec) const noexcept{
					if (_Type != path_data_type::close_path) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return close_path{ };
					}
					ec.clear();
					return close_path{ };
				}

				template <>
				curve_to path_data_item::get() const {
					if (_Type != path_data_type::curve_to) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return curve_to{ vector_2d{ _Data.curve.cpt1x, _Data.curve.cpt1y }, vector_2d{ _Data.curve.cpt2x, _Data.curve.cpt2y }, vector_2d{ _Data.curve.eptx, _Data.curve.epty } };
				}

				template <>
				curve_to path_data_item::get(::std::error_code& ec) const noexcept{
					if (_Type != path_data_type::curve_to) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return curve_to{ };
					}
					ec.clear();
					return curve_to{ vector_2d{ _Data.curve.cpt1x, _Data.curve.cpt1y }, vector_2d{ _Data.curve.cpt2x, _Data.curve.cpt2y }, vector_2d{ _Data.curve.eptx, _Data.curve.epty } };
				}

				template <>
				rel_curve_to path_data_item::get() const {
					if (_Type != path_data_type::rel_curve_to) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return rel_curve_to{ vector_2d{ _Data.curve.cpt1x, _Data.curve.cpt1y }, vector_2d{ _Data.curve.cpt2x, _Data.curve.cpt2y }, vector_2d{ _Data.curve.eptx, _Data.curve.epty } };
				}

				template <>
				rel_curve_to path_data_item::get(::std::error_code& ec) const noexcept{
					if (_Type != path_data_type::rel_curve_to) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return rel_curve_to{ };
					}
					ec.clear();
					return rel_curve_to{ vector_2d{ _Data.curve.cpt1x, _Data.curve.cpt1y }, vector_2d{ _Data.curve.cpt2x, _Data.curve.cpt2y }, vector_2d{ _Data.curve.eptx, _Data.curve.epty } };
				}

				template <>
				new_sub_path path_data_item::get() const {
					if (_Type != path_data_type::new_sub_path) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return new_sub_path{ };
				}

				template <>
				new_sub_path path_data_item::get(::std::error_code& ec) const noexcept{
					if (_Type != path_data_type::new_sub_path) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return new_sub_path{ };
					}
					ec.clear();
					return new_sub_path{ };
				}

				template <>
				line_to path_data_item::get() const {
					if (_Type != path_data_type::line_to) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return line_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				line_to path_data_item::get(::std::error_code& ec) const noexcept{
					if (_Type != path_data_type::line_to) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return line_to{ };
					}
					ec.clear();
					return line_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				move_to path_data_item::get() const {
					if (_Type != path_data_type::move_to) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return move_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				move_to path_data_item::get(::std::error_code& ec) const noexcept{
					if (_Type != path_data_type::move_to) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return move_to{ };
					}
					ec.clear();
					return move_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				rel_line_to path_data_item::get() const {
					if (_Type != path_data_type::rel_line_to) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return rel_line_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				rel_line_to path_data_item::get(::std::error_code& ec) const noexcept{
					if (_Type != path_data_type::rel_line_to) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return rel_line_to{ };
					}
					ec.clear();
					return rel_line_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				rel_move_to path_data_item::get() const {
					if (_Type != path_data_type::rel_move_to) {
						throw ::std::invalid_argument{ "Incorrect type parameter." };
					}
					return rel_move_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}

				template <>
				rel_move_to path_data_item::get(::std::error_code& ec) const noexcept{
					if (_Type != path_data_type::rel_move_to) {
						ec = ::std::make_error_code(::std::errc::invalid_argument);
						return rel_move_to{ };
					}
					ec.clear();
					return rel_move_to{ vector_2d{ _Data.point.x, _Data.point.y } };
				}


				// Forward declaration.
				class path_factory;
				class surface;

				class path {
					friend path_factory;
					::std::shared_ptr<::std::vector<path_data_item>> _Data;
					::std::shared_ptr<cairo_path_t> _Cairo_path;
					bool _Has_current_point;
					vector_2d _Current_point;
					vector_2d _Last_move_to_point;
					rectangle _Extents;
				public:
					typedef cairo_path_t* native_handle_type;
					native_handle_type native_handle() const noexcept;

					path() = delete;
					path(const path_factory& pb, const surface& sf);
					path(const path_factory& pb, const surface& sf, ::std::error_code& ec) noexcept;
					path(const path& other) noexcept = default;
					path& operator=(const path& other) noexcept = default;
					path(path&& other) noexcept;
					path& operator=(path&& other) noexcept;

					// Observers
					::std::vector<path_data_item> data() const;
					::std::vector<path_data_item> data(::std::error_code& ec) const noexcept;
					const ::std::vector<path_data_item>& data_ref() const noexcept;
					rectangle path_extents() const noexcept;
				};

				class path_factory {
					friend path;
					::std::vector<path_data_item> _Data;
					bool _Has_current_point;
					vector_2d _Current_point;
					vector_2d _Last_move_to_point;
					vector_2d _Extents_pt0;
					vector_2d _Extents_pt1;
					matrix_2d _Transform_matrix;
					vector_2d _Origin;

					void _Set_current_point_and_last_move_to_point_for_arc(const ::std::vector<path_data_item>& data) noexcept;
				public:
					path_factory() noexcept = default;
					path_factory(const path_factory& other) = default;
					path_factory& operator=(const path_factory& other) = default;
					path_factory(path_factory&& other) noexcept;
					path_factory& operator=(path_factory&& other) noexcept;

					// Modifiers
					void append(const path& p);
					void append(const path& p, ::std::error_code& ec) noexcept;
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
					void rect(const rectangle& r);
					void rect(const rectangle& r, ::std::error_code& ec) noexcept;
					void rel_curve_to(const vector_2d& dpt0, const vector_2d& dpt1, const vector_2d& dpt2);
					void rel_curve_to(const vector_2d& dpt0, const vector_2d& dpt1, const vector_2d& dpt2, ::std::error_code& ec) noexcept;
					void rel_line_to(const vector_2d& dpt);
					void rel_line_to(const vector_2d& dpt, ::std::error_code& ec) noexcept;
					void rel_move_to(const vector_2d& dpt);
					void rel_move_to(const vector_2d& dpt, ::std::error_code& ec) noexcept;
					void transform_matrix(const matrix_2d& m);
					void transform_matrix(const matrix_2d& m, ::std::error_code& ec) noexcept;
					void origin(const vector_2d& pt);
					void origin(const vector_2d& pt, ::std::error_code& ec) noexcept;
					void clear() noexcept;

					// Observers
					rectangle path_extents() const noexcept;
					bool has_current_point() const noexcept;
					vector_2d current_point() const;
					vector_2d current_point(::std::error_code& ec) const noexcept;
					matrix_2d transform_matrix() const noexcept;
					vector_2d origin() const noexcept;
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

				class font_face {
				protected:
					::std::shared_ptr<cairo_font_face_t> _Font_face;
				public:
					typedef cairo_font_face_t* native_handle_type;
					native_handle_type native_handle() const noexcept;

					font_face() = delete;
					font_face(const font_face&) noexcept = default;
					font_face& operator=(const font_face&) noexcept = default;
					font_face(font_face&& other) noexcept;
					font_face& operator=(font_face&& other) noexcept;
					explicit font_face(native_handle_type nh) noexcept;
					virtual ~font_face();
				};

				class simple_font_face : public font_face {
				public:
					simple_font_face() = delete;
					simple_font_face(const simple_font_face&) noexcept = default;
					simple_font_face& operator=(const simple_font_face&) noexcept = default;
					simple_font_face(const ::std::string& family, ::std::experimental::io2d::font_slant fs, ::std::experimental::io2d::font_weight fw) noexcept;
					simple_font_face(simple_font_face&& other) noexcept;
					simple_font_face& operator=(simple_font_face&& other) noexcept;
					virtual ~simple_font_face();

					// Observers
					::std::string font_family() const;
					void font_family(::std::string& str, ::std::error_code& ec) const noexcept;
					::std::experimental::io2d::font_slant font_slant() const noexcept;
					::std::experimental::io2d::font_weight font_weight() const noexcept;
				};

				// Forward declaration.
				class linear_brush_factory;
				class mesh_brush_factory;
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
					friend mesh_brush_factory;
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
					brush(const mesh_brush_factory& f);
					brush(const mesh_brush_factory& f, ::std::error_code& ec) noexcept;
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
					::std::vector<::std::tuple<double, rgba_color>> _Color_stops;

				public:
					linear_brush_factory() noexcept;
					linear_brush_factory(const linear_brush_factory&) = default;
					linear_brush_factory& operator=(const linear_brush_factory&) = default;
					linear_brush_factory(linear_brush_factory&& other) noexcept;
					linear_brush_factory& operator=(linear_brush_factory&& other) noexcept;
					linear_brush_factory(const vector_2d& begin, const vector_2d& end) noexcept;

					// Modifiers
					void add_color_stop(double offset, const rgba_color& color);
					void add_color_stop(double offset, const rgba_color& color, ::std::error_code& ec) noexcept;
					void color_stop(unsigned int index, double offset, const rgba_color& color);
					void color_stop(unsigned int index, double offset, const rgba_color& color, ::std::error_code& ec) noexcept;
					void begin_point(const vector_2d& value) noexcept;
					void end_point(const vector_2d& value) noexcept;

					// Observers
					unsigned int color_stop_count() const noexcept;
					::std::tuple<double, rgba_color> color_stop(unsigned int index) const;
					::std::tuple<double, rgba_color> color_stop(unsigned int index, ::std::error_code& ec) const noexcept;
					vector_2d begin_point() const noexcept;
					vector_2d end_point() const noexcept;
				};

				class radial_brush_factory {
					vector_2d _Center0;
					double _Radius0;
					vector_2d _Center1;
					double _Radius1;
					::std::vector<::std::tuple<double, rgba_color>> _Color_stops;

				public:
					radial_brush_factory() noexcept;
					radial_brush_factory(const radial_brush_factory&) = default;
					radial_brush_factory& operator=(const radial_brush_factory&) = default;
					radial_brush_factory(radial_brush_factory&& other) noexcept;
					radial_brush_factory& operator=(radial_brush_factory&& other) noexcept;
					radial_brush_factory(const vector_2d& center0, double radius0, const vector_2d& center1, double radius1) noexcept;

					// Modifiers
					void add_color_stop(double offset, const rgba_color& color);
					void add_color_stop(double offset, const rgba_color& color, ::std::error_code& ec) noexcept;
					void color_stop(unsigned int index, double offset, const rgba_color& color);
					void color_stop(unsigned int index, double offset, const rgba_color& color, ::std::error_code& ec) noexcept;
					void radial_circles(const vector_2d& center0, double radius0, const vector_2d& center1, double radius1) noexcept;

					// Observers
					unsigned int color_stop_count() const noexcept;
					::std::tuple<double, rgba_color> color_stop(unsigned int index) const;
					::std::tuple<double, rgba_color> color_stop(unsigned int index, ::std::error_code& ec) const noexcept;
					::std::tuple<vector_2d, double, vector_2d, double> radial_circles() const noexcept;
				};

				class mesh_brush_factory {
					bool _Has_current_patch;
					unsigned int _Current_patch_index;
					int _Current_patch_side_count;
					vector_2d _Current_patch_initial_point;
					bool _Has_current_point;
					typedef ::std::array<::std::tuple<bool, vector_2d>, 4> _Control_points;
					typedef ::std::array<::std::tuple<bool, rgba_color>, 4> _Corner_colors;
					// <Patch data, control points, corner colors>
					typedef ::std::tuple<::std::experimental::io2d::path_factory, _Control_points, _Corner_colors> _Patch;
					::std::vector<_Patch> _Patches;
				public:
					mesh_brush_factory() noexcept;
					mesh_brush_factory(const mesh_brush_factory&) = default;
					mesh_brush_factory& operator=(const mesh_brush_factory&) = default;
					mesh_brush_factory(mesh_brush_factory&& other) noexcept;
					mesh_brush_factory& operator=(mesh_brush_factory&& other) noexcept;

					// Modifiers
					void begin_patch();
					void begin_patch(::std::error_code& ec) noexcept;
					void begin_replace_patch(unsigned int patch_num);
					void begin_replace_patch(unsigned int patch_num, ::std::error_code& ec) noexcept;
					void end_patch();
					void end_patch(::std::error_code& ec) noexcept;
					void move_to(const vector_2d& pt);
					void move_to(const vector_2d& pt, ::std::error_code& ec) noexcept;
					void line_to(const vector_2d& pt);
					void line_to(const vector_2d& pt, ::std::error_code& ec) noexcept;
					void curve_to(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2);
					void curve_to(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, ::std::error_code& ec) noexcept;
					void control_point(unsigned int point_num, const vector_2d& pt);
					void control_point(unsigned int point_num, const vector_2d& pt, ::std::error_code& ec) noexcept;
					void corner_color(unsigned int corner_num, const rgba_color& color);
					void corner_color(unsigned int corner_num, const rgba_color& color, ::std::error_code& ec) noexcept;

					// Observers
					unsigned int patch_count() const noexcept;
					::std::experimental::io2d::path_factory path_factory(unsigned int patch_num) const;
					::std::experimental::io2d::path_factory path_factory(unsigned int patch_num, ::std::error_code& ec) const noexcept;
					bool control_point(unsigned int patch_num, unsigned int point_num, vector_2d& controlPoint) const;
					bool control_point(unsigned int patch_num, unsigned int point_num, vector_2d& controlPoint, ::std::error_code& ec) const noexcept;
					bool corner_color(unsigned int patch_num, unsigned int corner_num, rgba_color& color) const;
					bool corner_color(unsigned int patch_num, unsigned int corner_num, rgba_color& color, ::std::error_code& ec) const noexcept;
				};

				struct _Surface_native_handles {
					::cairo_surface_t* csfce;
					::cairo_t* cctxt;
				};

				typedef ::std::tuple<::std::vector<double>, double> dashes;

				class surface {
				public:
					// tuple<dashes, offset>
				private:
					::std::mutex _Lock_for_device;
					::std::weak_ptr<::std::experimental::io2d::device> _Device;
				protected:
					::std::unique_ptr<cairo_surface_t, ::std::function<void(cairo_surface_t*)>> _Surface;
					::std::unique_ptr<cairo_t, ::std::function<void(cairo_t*)>> _Context;
					::std::unique_ptr<cairo_font_options_t, decltype(&cairo_font_options_destroy)> _Native_font_options;

					const double _Line_join_miter_miter_limit = 10000.0;

					// State - unsaved
					typedef rectangle _Dirty_type;
					_Dirty_type _Dirty_rect;
					::std::experimental::io2d::format _Format;
					::std::experimental::io2d::content _Content;

					// State - saved
					typedef vector_2d _Device_offtype;
					_Device_offtype _Device_offset = { 0.0, 0.0 };
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
					typedef double _Tolerance_type;
					_Tolerance_type _Tolerance = 0.1;
					::std::experimental::io2d::path _Default_path;
					::std::experimental::io2d::path _Current_path;
					::std::experimental::io2d::path_factory _Immediate_path;
					typedef matrix_2d _Transform_matrix_type;
					_Transform_matrix_type _Transform_matrix;
					::std::experimental::io2d::font_face _Font_face; // Altered by select_font_face and font_face
					typedef matrix_2d _Font_matrix_type;
					_Font_matrix_type _Font_matrix; // Covers both size and full matrix - size is just a uniform scale matrix.
					::std::experimental::io2d::font_options _Font_options;
					// The current scaled_font is created on demand from parameters that are already saved.

					// We use vector here because of its C++17 default ctor noexcept guarantee.
					::std::stack<::std::tuple<_Device_offtype, ::std::experimental::io2d::brush, ::std::experimental::io2d::antialias, ::std::experimental::io2d::dashes, ::std::experimental::io2d::fill_rule, ::std::experimental::io2d::line_cap, ::std::experimental::io2d::line_join, _Line_width_type, _Miter_limit_type, ::std::experimental::io2d::compositing_operator, _Tolerance_type, ::std::experimental::io2d::path, ::std::experimental::io2d::path, ::std::experimental::io2d::path_factory, _Transform_matrix_type, ::std::experimental::io2d::font_face, _Font_matrix_type, ::std::experimental::io2d::font_options>, ::std::vector<::std::tuple<_Device_offtype, ::std::experimental::io2d::brush, ::std::experimental::io2d::antialias, ::std::experimental::io2d::dashes, ::std::experimental::io2d::fill_rule, ::std::experimental::io2d::line_cap, ::std::experimental::io2d::line_join, _Line_width_type, _Miter_limit_type, ::std::experimental::io2d::compositing_operator, _Tolerance_type, ::std::experimental::io2d::path, ::std::experimental::io2d::path, ::std::experimental::io2d::path_factory, _Transform_matrix_type, ::std::experimental::io2d::font_face, _Font_matrix_type, ::std::experimental::io2d::font_options>>> _Saved_state;

					void _Ensure_state();
					void _Ensure_state(::std::error_code& ec) noexcept;

					surface(::std::experimental::io2d::format fmt, int width, int height);
				public:

					typedef _Surface_native_handles native_handle_type;
					native_handle_type native_handle() const;

					surface() = delete;
					surface(const surface&) = delete;
					surface& operator=(const surface&) = delete;
					surface(surface&& other) noexcept;
					surface& operator=(surface&& other) noexcept;

					surface(native_handle_type nh, ::std::experimental::io2d::format fmt, ::std::experimental::io2d::content ctnt);

					// create_similar
					surface(const surface& other, ::std::experimental::io2d::content ctnt, int width, int height);
					virtual ~surface();

					// \ref{\iotwod.surface.modifiers.state}, state modifiers:
					virtual void finish();
					void flush();
					::std::shared_ptr<::std::experimental::io2d::device> device();
					void mark_dirty();
					void mark_dirty(const rectangle& rect);
					void device_offset(const vector_2d& offset);
					void write_to_file(const ::std::string& filename);
					image_surface map_to_image();
					image_surface map_to_image(const rectangle& extents);
					void unmap_image(image_surface& image);
					virtual void save();
					virtual void save(::std::error_code& ec) noexcept;
					virtual void restore();
					virtual void restore(::std::error_code& ec) noexcept;
					void reset_brush() noexcept;
					void brush(const ::std::experimental::io2d::brush& source) noexcept;
					void antialias(::std::experimental::io2d::antialias a) noexcept;
					void reset_dashes() noexcept;
					void dashes(const ::std::experimental::io2d::dashes& d);
					void dashes(const ::std::experimental::io2d::dashes& d, ::std::error_code& ec) noexcept;
					void fill_rule(::std::experimental::io2d::fill_rule fr) noexcept;
					void line_cap(::std::experimental::io2d::line_cap lc) noexcept;
					void line_join(::std::experimental::io2d::line_join lj) noexcept;
					void line_width(double width) noexcept;
					void miter_limit(double limit) noexcept;
					void compositing_operator(::std::experimental::io2d::compositing_operator co) noexcept;
					void tolerance(double t) noexcept;
					void clip(const ::std::experimental::io2d::path& p);
					void clip_immediate();
					void reset_clip();
					void reset_path() noexcept;
					void path(const ::std::experimental::io2d::path& p) noexcept;

					// \ref{\iotwod.surface.modifiers.immediatepath}, immediate path modifiers:
					::std::experimental::io2d::path_factory& immediate();

					// \ref{\iotwod.surface.modifiers.render}, render modifiers:
					void paint();
					void paint(const rgba_color& c);
					void paint(const ::std::experimental::io2d::brush& b);
					void paint(const surface& s, const vector_2d& origin = vector_2d{ 0.0, 0.0 }, extend e = extend::none, filter f = filter::good);
					void paint(const surface& s, const matrix_2d& m, extend e = extend::none, filter f = filter::good);
					void paint(double alpha);
					void paint(const rgba_color& c, double alpha);
					void paint(const ::std::experimental::io2d::brush& b, double alpha);
					void paint(const surface& s, double alpha, const vector_2d& origin = vector_2d{ 0.0, 0.0 }, extend e = extend::none, filter f = filter::good);
					void paint(const surface& s, double alpha, const matrix_2d& m, extend e = extend::none, filter f = filter::good);
					void fill();
					void fill(const rgba_color& c);
					void fill(const ::std::experimental::io2d::brush& b);
					void fill(const surface& s, const vector_2d& origin = vector_2d{ 0.0, 0.0 }, extend e = extend::none, filter f = filter::good);
					void fill(const surface& s, const matrix_2d& m, extend e = extend::none, filter f = filter::good);
					void fill_immediate();
					void fill_immediate(const rgba_color& c);
					void fill_immediate(const ::std::experimental::io2d::brush& b);
					void fill_immediate(const surface& s, const vector_2d& origin = vector_2d{ 0.0, 0.0 }, extend e = extend::none, filter f = filter::good);
					void fill_immediate(const surface& s, const matrix_2d& m, extend e = extend::none, filter f = filter::good);
					void stroke();
					void stroke(const rgba_color& c);
					void stroke(const ::std::experimental::io2d::brush& b);
					void stroke(const surface& s, const vector_2d& origin = vector_2d{ 0.0, 0.0 }, extend e = extend::none, filter f = filter::good);
					void stroke(const surface& s, const matrix_2d& m, extend e = extend::none, filter f = filter::good);
					void stroke_immediate();
					void stroke_immediate(const rgba_color& c);
					void stroke_immediate(const ::std::experimental::io2d::brush& b);
					void stroke_immediate(const surface& s, const vector_2d& origin = vector_2d{ 0.0, 0.0 }, extend e = extend::none, filter f = filter::good);
					void stroke_immediate(const surface& s, const matrix_2d& m, extend e = extend::none, filter f = filter::good);

					// \ref{\iotwod.surface.modifiers.maskrender}, mask render modifiers:
					void mask(const ::std::experimental::io2d::brush& maskBrush);
					void mask(const ::std::experimental::io2d::brush& maskBrush, const rgba_color& c);
					void mask(const ::std::experimental::io2d::brush& maskBrush, const ::std::experimental::io2d::brush& b);
					void mask(const ::std::experimental::io2d::brush& maskBrush, const surface& s, const vector_2d& origin = vector_2d{ 0.0, 0.0 }, extend e = extend::none, filter f = filter::good);
					void mask(const ::std::experimental::io2d::brush& maskBrush, const surface& s, const matrix_2d& m, extend e = extend::none, filter f = filter::good);
					void mask(const surface& maskSurface);
					void mask(const surface& maskSurface, const rgba_color& c);
					void mask(const surface& maskSurface, const ::std::experimental::io2d::brush& b);
					void mask(const surface& maskSurface, const surface& s, const vector_2d& origin = vector_2d{ 0.0, 0.0 }, extend e = extend::none, filter f = filter::good);
					void mask(const surface& maskSurface, const surface& s, const matrix_2d& m, extend e = extend::none, filter f = filter::good);
					void mask(const surface& maskSurface, const vector_2d& maskOrigin);
					void mask(const surface& maskSurface, const vector_2d& maskOrigin, const rgba_color& c);
					void mask(const surface& maskSurface, const vector_2d& maskOrigin, const ::std::experimental::io2d::brush& b);
					void mask(const surface& maskSurface, const vector_2d& maskOrigin, const surface& s, const vector_2d& origin = vector_2d{ 0.0, 0.0 }, extend e = extend::none, filter f = filter::good);
					void mask(const surface& maskSurface, const vector_2d& maskOrigin, const surface& s, const matrix_2d& m, extend e = extend::none, filter f = filter::good);
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush);
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const rgba_color& c);
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const ::std::experimental::io2d::brush& b);
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const surface& s, const vector_2d& origin = vector_2d{ 0.0, 0.0 }, extend e = extend::none, filter f = filter::good);
					void mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const surface& s, const matrix_2d& m, extend e = extend::none, filter f = filter::good);
					void mask_immediate(const surface& maskSurface);
					void mask_immediate(const surface& maskSurface, const rgba_color& c);
					void mask_immediate(const surface& maskSurface, const ::std::experimental::io2d::brush& b);
					void mask_immediate(const surface& maskSurface, const surface& s, const vector_2d& origin = vector_2d{ 0.0, 0.0 }, extend e = extend::none, filter f = filter::good);
					void mask_immediate(const surface& maskSurface, const surface& s, const matrix_2d& m, extend e = extend::none, filter f = filter::good);
					void mask_immediate(const surface& maskSurface, const vector_2d& maskOrigin);
					void mask_immediate(const surface& maskSurface, const vector_2d& maskOrigin, const rgba_color& c);
					void mask_immediate(const surface& maskSurface, const vector_2d& maskOrigin, const ::std::experimental::io2d::brush& b);
					void mask_immediate(const surface& maskSurface, const vector_2d& maskOrigin, const surface& s, const vector_2d& origin = vector_2d{ 0.0, 0.0 }, extend e = extend::none, filter f = filter::good);
					void mask_immediate(const surface& maskSurface, const vector_2d& maskOrigin, const surface& s, const matrix_2d& m, extend e = extend::none, filter f = filter::good);

					// \ref{\iotwod.surface.modifiers.textrender}, text render modifiers:
					vector_2d show_text(const ::std::string& utf8, const vector_2d& position);
					vector_2d show_text(const ::std::string& utf8, const vector_2d& position, const rgba_color& c);
					vector_2d show_text(const ::std::string& utf8, const vector_2d& position, const ::std::experimental::io2d::brush& b);
					vector_2d show_text(const ::std::string& utf8, const vector_2d& position, const surface& s, const vector_2d& origin = vector_2d{ 0.0, 0.0 }, extend e = extend::none, filter f = filter::good);
					vector_2d show_text(const ::std::string& utf8, const vector_2d& position, const surface& s, const matrix_2d& m, extend e = extend::none, filter f = filter::good);
					// \ref{\iotwod.surface.modifiers.transform}, transformation modifiers:
					void matrix(const matrix_2d& matrix);

					// \ref{\iotwod.surface.modifiers.font}, font modifiers:
					void font_face(const ::std::string& family, font_slant sl, font_weight w);
					void font_face(const ::std::experimental::io2d::font_face& f);
					void font_size(double s);
					void font_matrix(const matrix_2d& m);
					void font_options(const font_options& fo);

					// \ref{\iotwod.surface.observers.stateobjects}, state object observers:
					::std::experimental::io2d::path path(const path_factory& pf) const;

					// \ref{\iotwod.surface.observers.state}, state observers:
					::std::experimental::io2d::content content() const ;
					vector_2d device_offset() const;
					bool has_surface_resource() const;
					::std::experimental::io2d::brush brush() const;
					::std::experimental::io2d::antialias antialias() const;
					int dashes_count() const;
					::std::experimental::io2d::dashes dashes() const;
					::std::experimental::io2d::fill_rule fill_rule() const;
					::std::experimental::io2d::line_cap line_cap() const;
					::std::experimental::io2d::line_join line_join() const;
					double line_width() const;
					double miter_limit() const;
					::std::experimental::io2d::compositing_operator compositing_operator() const;
					double tolerance() const;
					rectangle clip_extents() const;
					bool in_clip(const vector_2d& pt) const;
					::std::vector<rectangle> clip_rectangles() const;
					::std::vector<rectangle> clip_rectangles(::std::error_code& ec) const noexcept;

					// \ref{\iotwod.surface.observers.render}, render observers:
					rectangle fill_extents() const;
					rectangle fill_extents_immediate() const;
					bool in_fill(const vector_2d& pt) const;
					bool in_fill_immediate(const vector_2d& pt) const;
					rectangle stroke_extents() const;
					rectangle stroke_extents_immediate() const;
					bool in_stroke(const vector_2d& pt) const;
					bool in_stroke_immediate(const vector_2d& pt) const;
					::std::experimental::io2d::font_extents font_extents() const;
					::std::experimental::io2d::text_extents text_extents(const ::std::string& utf8) const;

					// \ref{\iotwod.surface.observers.transform}, transformation observers:
					matrix_2d matrix() const;
					vector_2d user_to_surface(const vector_2d& pt) const;
					vector_2d user_to_surface_distance(const vector_2d& dpt) const;
					vector_2d surface_to_user(const vector_2d& pt) const;
					vector_2d surface_to_user_distance(const vector_2d& dpt) const;

					// \ref{\iotwod.surface.observers.font}, font observers:
					matrix_2d font_matrix() const;
					::std::experimental::io2d::font_options font_options() const;
					::std::experimental::io2d::font_face font_face() const;
				};

				class image_surface : public surface {
					friend surface;
				protected:
					image_surface(surface::native_handle_type nh, surface::native_handle_type map_of);
				public:
					image_surface() = delete;
					image_surface(const image_surface&) = delete;
					image_surface& operator=(const image_surface&) = delete;
					image_surface(image_surface&& other);
					image_surface& operator=(image_surface&& other);
					image_surface(::std::experimental::io2d::format fmt, int width, int height);
					image_surface(vector<unsigned char>& data, ::std::experimental::io2d::format fmt, int width, int height);
					// create_similar_image
					image_surface(const surface& other, ::std::experimental::io2d::format fmt, int width, int height);
					// create_from_png
					image_surface(const ::std::string& filename);
					virtual ~image_surface();

					// Modifiers
					void data(const ::std::vector<unsigned char>& data);
					::std::vector<unsigned char> data();

					// Observers
					::std::experimental::io2d::format format() const;
					int width() const;
					int height() const;
					int stride() const;
				};

#ifdef _WIN32_WINNT
				struct _Win32_display_surface_native_handle {
					_Surface_native_handles sfc_nh;
					HWND hwnd;
					_Surface_native_handles win32_sfc_nh;
				};

				const int _Display_surface_ptr_window_data_byte_offset = 0;

				LRESULT CALLBACK _RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
#else
				struct _Xlib_display_surface_native_handle {
					_Surface_native_handles sfc_nh;
					Display* display;
					Window wndw;
					::std::mutex& display_mutex;
					int& display_ref_count;
				};
#endif
				class display_surface : public surface {
					friend surface;
					::std::experimental::io2d::scaling _Scaling;
					typedef int _Width_type;
					_Width_type _Width;
					typedef int _Height_type;
					_Height_type _Height;
					typedef int _Display_width_type;
					_Display_width_type _Display_width;
					typedef int _Display_height_type;
					_Display_height_type _Display_height;
					::std::function<void(display_surface& sfc)> _Draw_fn;
					::std::function<void(display_surface& sfc)> _Size_change_fn;
					typedef ::std::function<::std::experimental::io2d::rectangle(const display_surface&, bool&)> _User_scaling_fn_type;
					 _User_scaling_fn_type _User_scaling_fn = nullptr;
					 ::std::experimental::io2d::brush _Letterbox_brush;

					void _Make_native_surface_and_context();
					void _All_dimensions(int w, int h, int dw, int dh);
					void _Render_to_native_surface();
					void _Resize_window();
					void _Render_for_scaling_uniform_or_letterbox();

					::std::stack<::std::tuple<
						::std::experimental::io2d::scaling,
						_Width_type,
						_Height_type,
						_Display_width_type,
						_Display_height_type,
						_User_scaling_fn_type,
						::std::experimental::io2d::brush>> _Display_saved_state;
#ifdef _WIN32_WINNT
					friend LRESULT CALLBACK _RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
					DWORD _Window_style;
					HWND _Hwnd;

					LRESULT _Window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
#else
					static ::std::mutex _Display_mutex;
					static ::std::unique_ptr<Display, ::std::function<void(Display*)>> _Display;
					static int _Display_ref_count;
					::Window _Wndw;
					bool _Can_draw = false;

					static Bool _X11_if_event_pred(Display* display, XEvent* event, XPointer arg);
#endif
					::std::unique_ptr<cairo_surface_t, ::std::function<void(cairo_surface_t*)>> _Native_surface;
					::std::unique_ptr<cairo_t, ::std::function<void(cairo_t*)>> _Native_context;

				public:
#ifdef _WIN32_WINNT
					typedef _Win32_display_surface_native_handle native_handle_type;
#else
					typedef _Xlib_display_surface_native_handle native_handle_type;
#endif
					native_handle_type native_handle() const;

					display_surface() = delete;
					display_surface(const display_surface&) = delete;
					display_surface& operator=(const display_surface&) = delete;
					display_surface(display_surface&& other);
					display_surface& operator=(display_surface&& other);
					display_surface(int preferredWidth, int preferredHeight, ::std::experimental::io2d::format preferredFormat, ::std::experimental::io2d::scaling scl = ::std::experimental::io2d::scaling::letterbox);
					display_surface(int preferredWidth, int preferredHeight, ::std::experimental::io2d::format preferredFormat,
						int preferredDisplayWidth, int preferredDisplayHeight,
						::std::experimental::io2d::scaling scl = ::std::experimental::io2d::scaling::letterbox);

					virtual ~display_surface();

					virtual void save() override;
					virtual void restore() override;

					void draw_fn(const ::std::function<void(display_surface& sfc)>& fn);
					void size_change_fn(const ::std::function<void(display_surface& sfc)>& fn);
					void width(int w);
					void height(int h);
					void display_width(int w);
					void display_height(int h);
					void dimensions(int w, int h);
					void display_dimensions(int dw, int dh);
					void scaling(::std::experimental::io2d::scaling scl);
					void user_scaling_fn(const ::std::function<::std::experimental::io2d::rectangle(const display_surface&, bool&)>& fn);
					void clear_letterbox_brush();
					void letterbox_brush(const rgba_color& c);
					void letterbox_brush(const ::std::experimental::io2d::brush& b);
					int join();

					::std::experimental::io2d::format format() const;
					int width() const;
					int height() const;
					int display_width() const;
					int display_height() const;
					::std::tuple<int, int> dimensions() const;
					::std::tuple<int, int> display_dimensions() const;
					::std::experimental::io2d::scaling scaling() const;
					const ::std::function<::std::experimental::io2d::rectangle(const display_surface&, bool&)>& user_scaling_fn() const;
					::std::experimental::io2d::brush letterbox_brush() const;
				};

				class surface_brush_factory {
					image_surface _Surface;

					friend ::std::experimental::io2d::brush;

				public:
					surface_brush_factory();
					surface_brush_factory(const surface_brush_factory&) = delete;
					surface_brush_factory& operator=(const surface_brush_factory&) = delete;
					surface_brush_factory(surface_brush_factory&& other);
					surface_brush_factory& operator=(surface_brush_factory&& other);
					surface_brush_factory(::std::experimental::io2d::surface& s);

					// Modifiers
					image_surface surface(::std::experimental::io2d::surface& s);

					// Observers
					const image_surface& surface() const;
				};

				int format_stride_for_width(format format, int width);
				display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, scaling scl = scaling::letterbox);
				surface make_surface(surface::native_handle_type nh, format fmt); // parameters are exposition only.
				image_surface make_image_surface(format format, int width, int height);
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
