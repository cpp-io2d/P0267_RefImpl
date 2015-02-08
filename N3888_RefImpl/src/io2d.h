#pragma once

#ifndef _IO2D_
#define _IO2D_

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
					pad,
					default_extend = none
				};

				enum class filter {
					fast,
					good,
					best,
					nearest,
					bilinear,
					gaussian,
					default_filter = good
				};

				enum class pattern_type {
					unknown,
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
					none, // Do not scale.
					uniform, // Maintain aspect ratio and letterbox if needed
					fill, // Maintain aspect ratio but fill entire display (some content may not be shown)
					exact, // Ignore aspect ratio and use (possibly non-uniform) scale to fill exactly
					lock_to_display, // Resize to match display dimensions
					default_scaling = uniform // uniform
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
					rectangle() = default;
					rectangle(const rectangle& other) = default;
					rectangle& operator=(const rectangle& other) = default;
					rectangle(rectangle&& other);
					rectangle& operator=(rectangle&& other);
					rectangle(double x, double y, double width, double height);

					void x(double value);
					void y(double value);
					void width(double value);
					void height(double value);

					double x() const;
					double y() const;
					double width() const;
					double height() const;
				};

				class rgba_color {
					double _R = 0.0;
					double _G = 0.0;
					double _B = 0.0;
					double _A = 0.0;
				public:
					rgba_color() = default;
					rgba_color(const rgba_color& other) = default;
					rgba_color& operator=(const rgba_color& other) = default;
					rgba_color(rgba_color&& other);
					rgba_color& operator=(rgba_color&& other);
					rgba_color(double red, double green, double blue, double alpha = 1.0);
					rgba_color(int red, int green, int blue, int alpha = 255);

					void r(double value);
					void g(double value);
					void b(double value);
					void a(double value);

					double r() const;
					double g() const;
					double b() const;
					double a() const;

					static const rgba_color& alice_blue();
					static const rgba_color& antique_white();
					static const rgba_color& aqua();
					static const rgba_color& aquamarine();
					static const rgba_color& azure();
					static const rgba_color& beige();
					static const rgba_color& bisque();
					static const rgba_color& black();
					static const rgba_color& blanched_almond();
					static const rgba_color& blue();
					static const rgba_color& blue_violet();
					static const rgba_color& brown();
					static const rgba_color& burly_wood();
					static const rgba_color& cadet_blue();
					static const rgba_color& chartreuse();
					static const rgba_color& chocolate();
					static const rgba_color& coral();
					static const rgba_color& cornflower_blue();
					static const rgba_color& cornsilk();
					static const rgba_color& crimson();
					static const rgba_color& cyan();
					static const rgba_color& dark_blue();
					static const rgba_color& dark_cyan();
					static const rgba_color& dark_goldenrod();
					static const rgba_color& dark_gray();
					static const rgba_color& dark_green();
					static const rgba_color& dark_grey();
					static const rgba_color& dark_khaki();
					static const rgba_color& dark_magenta();
					static const rgba_color& dark_olive_green();
					static const rgba_color& dark_orange();
					static const rgba_color& dark_orchid();
					static const rgba_color& dark_red();
					static const rgba_color& dark_salmon();
					static const rgba_color& dark_sea_green();
					static const rgba_color& dark_slate_blue();
					static const rgba_color& dark_slate_gray();
					static const rgba_color& dark_slate_grey();
					static const rgba_color& dark_turquoise();
					static const rgba_color& dark_violet();
					static const rgba_color& deep_pink();
					static const rgba_color& deep_sky_blue();
					static const rgba_color& dim_gray();
					static const rgba_color& dim_grey();
					static const rgba_color& dodger_blue();
					static const rgba_color& firebrick();
					static const rgba_color& floral_white();
					static const rgba_color& forest_green();
					static const rgba_color& fuchsia();
					static const rgba_color& gainsboro();
					static const rgba_color& ghost_white();
					static const rgba_color& gold();
					static const rgba_color& goldenrod();
					static const rgba_color& gray();
					static const rgba_color& green();
					static const rgba_color& green_yellow();
					static const rgba_color& grey();
					static const rgba_color& honeydew();
					static const rgba_color& hot_pink();
					static const rgba_color& indian_red();
					static const rgba_color& indigo();
					static const rgba_color& ivory();
					static const rgba_color& khaki();
					static const rgba_color& lavender();
					static const rgba_color& lavender_blush();
					static const rgba_color& lawn_green();
					static const rgba_color& lemon_chiffon();
					static const rgba_color& light_blue();
					static const rgba_color& light_coral();
					static const rgba_color& light_cyan();
					static const rgba_color& light_goldenrod_yellow();
					static const rgba_color& light_gray();
					static const rgba_color& light_green();
					static const rgba_color& light_grey();
					static const rgba_color& light_pink();
					static const rgba_color& light_salmon();
					static const rgba_color& light_sea_green();
					static const rgba_color& light_sky_blue();
					static const rgba_color& light_slate_gray();
					static const rgba_color& light_slate_grey();
					static const rgba_color& light_steel_blue();
					static const rgba_color& light_yellow();
					static const rgba_color& lime();
					static const rgba_color& lime_green();
					static const rgba_color& linen();
					static const rgba_color& magenta();
					static const rgba_color& maroon();
					static const rgba_color& medium_aquamarine();
					static const rgba_color& medium_blue();
					static const rgba_color& medium_orchid();
					static const rgba_color& medium_purple();
					static const rgba_color& medium_sea_green();
					static const rgba_color& medium_slate_blue();
					static const rgba_color& medium_spring_green();
					static const rgba_color& medium_turquoise();
					static const rgba_color& medium_violet_red();
					static const rgba_color& midnight_blue();
					static const rgba_color& mint_cream();
					static const rgba_color& misty_rose();
					static const rgba_color& moccasin();
					static const rgba_color& navajo_white();
					static const rgba_color& navy();
					static const rgba_color& old_lace();
					static const rgba_color& olive();
					static const rgba_color& olive_drab();
					static const rgba_color& orange();
					static const rgba_color& orange_red();
					static const rgba_color& orchid();
					static const rgba_color& pale_goldenrod();
					static const rgba_color& pale_green();
					static const rgba_color& pale_turquoise();
					static const rgba_color& pale_violet_red();
					static const rgba_color& papaya_whip();
					static const rgba_color& peach_puff();
					static const rgba_color& peru();
					static const rgba_color& pink();
					static const rgba_color& plum();
					static const rgba_color& powder_blue();
					static const rgba_color& purple();
					static const rgba_color& red();
					static const rgba_color& rosy_brown();
					static const rgba_color& royal_blue();
					static const rgba_color& saddle_brown();
					static const rgba_color& salmon();
					static const rgba_color& sandy_brown();
					static const rgba_color& sea_green();
					static const rgba_color& sea_shell();
					static const rgba_color& sienna();
					static const rgba_color& silver();
					static const rgba_color& sky_blue();
					static const rgba_color& slate_blue();
					static const rgba_color& slate_gray();
					static const rgba_color& slate_grey();
					static const rgba_color& snow();
					static const rgba_color& spring_green();
					static const rgba_color& steel_blue();
					static const rgba_color& tan();
					static const rgba_color& teal();
					static const rgba_color& thistle();
					static const rgba_color& tomato();
					static const rgba_color& transparent_black(); // Note: Not in CSS3.
					static const rgba_color& turquoise();
					static const rgba_color& violet();
					static const rgba_color& wheat();
					static const rgba_color& white();
					static const rgba_color& white_smoke();
					static const rgba_color& yellow();
					static const rgba_color& yellow_green();
				};

#if _Inline_namespace_conditional_support_test && _User_defined_literal_conditional_support_test
				inline namespace literals {
					// Note: The _ prefix is added because certain compilers reject attempts to add a non-user-defined literal
					inline double operator""_ubyte(unsigned long long value) {
						return ::std::max(0.0, ::std::min(1.0, static_cast<double>(value) / 255.0));
					}

					// Note: The _ prefix is added because certain compilers reject attempts to add a non-user-defined literal
					inline double operator "" _unorm(long double value) {
						auto result = ::std::max(0.0, ::std::min(1.0, static_cast<double>(value)));
						result = ::std::nearbyint(result * 255.0); // We need to ensure it is one of the discrete values between 0 and 255.
						return result / 255.0;
					}
				}
#endif

				class point {
					double _X = 0.0;
					double _Y = 0.0;
				public:
					point() = default;
					point(const point& other) = default;
					point& operator=(const point& other) = default;
					point(point&& other);
					point& operator=(point&& other);
					point(double x, double y);

					void x(double value);
					void y(double value);

					double x() const;
					double y() const;
				};

				bool operator==(const point& lhs, const point& rhs);
				bool operator!=(const point& lhs, const point& rhs);

				class glyph {
					cairo_glyph_t _Glyph_data;

				public:
					typedef cairo_glyph_t* native_handle_type;
					native_handle_type native_handle();

					glyph();
					glyph(const glyph& other) = default;
					glyph& operator=(const glyph& other) = default;
					glyph(glyph&& other);
					glyph& operator=(glyph&& other);
					glyph(unsigned long index, double x, double y);

					void index(unsigned long index);
					void x(double x);
					void y(double y);

					unsigned long index() const;
					double x() const;
					double y() const;
				};

				class text_cluster {
					cairo_text_cluster_t _Text_cluster;
				public:
					typedef cairo_text_cluster_t* native_handle_type;
					native_handle_type native_handle();

					text_cluster();
					text_cluster(const text_cluster& other) = default;
					text_cluster& operator=(const text_cluster& other) = default;
					text_cluster(text_cluster&& other);
					text_cluster& operator=(text_cluster&& other);
					text_cluster(int numBytes, int numGlyphs);

					void num_bytes(int value);
					void num_glyphs(int value);

					int num_bytes() const;
					int num_glyphs() const;
				};

				class font_extents {
					cairo_font_extents_t _Font_extents;
				public:
					typedef cairo_font_extents_t* native_handle_type;
					native_handle_type native_handle();

					font_extents();
					font_extents(const font_extents& other) = default;
					font_extents& operator=(const font_extents& other) = default;
					font_extents(font_extents&& other);
					font_extents& operator=(font_extents&& other);
					font_extents(double ascent, double descent, double height, double maxXAdvance, double maxYAdvance);

					void ascent(double value);
					void descent(double value);
					void height(double value);
					void max_x_advance(double value);
					void max_y_advance(double value);

					double ascent() const;
					double descent() const;
					double height() const;
					double max_x_advance() const;
					double max_y_advance() const;
				};

				class text_extents {
					cairo_text_extents_t _Text_extents;
				public:
					typedef cairo_text_extents_t* native_handle_type;
					native_handle_type native_handle();

					text_extents();
					text_extents(const text_extents& other) = default;
					text_extents& operator=(const text_extents& other) = default;
					text_extents(text_extents&& other);
					text_extents& operator=(text_extents&& other);
					text_extents(double xBearing, double yBearing, double width, double height, double xAdvance, double yAdvance);

					void x_bearing(double value);
					void y_bearing(double value);
					void width(double value);
					void height(double value);
					void x_advance(double value);
					void y_advance(double value);

					double x_bearing() const;
					double y_bearing() const;
					double width() const;
					double height() const;
					double x_advance() const;
					double y_advance() const;
				};

				class matrix_2d {
					double _M00;
					double _M01;
					double _M10;
					double _M11;
					double _M20;
					double _M21;
				public:

					matrix_2d();
					matrix_2d(const matrix_2d& other) = default;
					matrix_2d& operator=(const matrix_2d& other) = default;
					matrix_2d(matrix_2d&& other);
					matrix_2d& operator=(matrix_2d&& other);
					matrix_2d(double m00, double m01, double m10, double m11, double m20, double m21);

					static matrix_2d init_identity();
					static matrix_2d init_translate(const point& value);
					static matrix_2d init_scale(const point& value);
					static matrix_2d init_rotate(double radians);
					static matrix_2d init_shear_x(double factor);
					static matrix_2d init_shear_y(double factor);

					// Modifiers
					void m00(double value);
					void m01(double value);
					void m10(double value);
					void m11(double value);
					void m20(double value);
					void m21(double value);
					matrix_2d& translate(const point& value);
					matrix_2d& scale(const point& value);
					matrix_2d& rotate(double radians);
					matrix_2d& shear_x(double factor);
					matrix_2d& shear_y(double factor);
					matrix_2d& invert();

					// Observers
					double m00() const;
					double m01() const;
					double m10() const;
					double m11() const;
					double m20() const;
					double m21() const;
					double determinant() const;
					point transform_distance(const point& dist) const;
					point transform_point(const point& pt) const;
				};

				matrix_2d operator*(const matrix_2d& lhs, const matrix_2d& rhs);
				matrix_2d& operator*=(matrix_2d& lhs, const matrix_2d& rhs);
				bool operator==(const matrix_2d& lhs, const matrix_2d& rhs);
				bool operator!=(const matrix_2d& lhs, const matrix_2d& rhs);

				class path_data {
				public:
					path_data() = default;
					path_data(const path_data& other) = default;
					path_data& operator=(const path_data& other) = default;
					path_data(path_data&& other);
					path_data& operator=(path_data&& other);
					virtual ~path_data();

					virtual path_data_type type() const = 0;
				};

				class _Point : public path_data {
					point _Data = { };
				public:
					_Point() = default;
					_Point(const _Point& other) = default;
					_Point& operator=(const _Point& other) = default;
					_Point(_Point&& other);
					_Point& operator=(_Point&& other);
					_Point(const point& to);
					virtual ~_Point();
					virtual path_data_type type() const override = 0;

					point to() const;
					void to(const point& value);
				};

				class move_to : public _Point {
				public:
					move_to() = default;
					move_to(const move_to& other) = default;
					move_to& operator=(const move_to& other) = default;
					move_to(move_to&& other);
					move_to& operator=(move_to&& other);
					move_to(const point& to);
					virtual path_data_type type() const override;
				};

				class line_to : public _Point {
				public:
					line_to() = default;
					line_to(const line_to& other) = default;
					line_to& operator=(const line_to& other) = default;
					line_to(line_to&& other);
					line_to& operator=(line_to&& other);
					line_to(const point& to);
					virtual path_data_type type() const override;
				};

				class rel_move_to : public _Point {
				public:
					rel_move_to() = default;
					rel_move_to(const rel_move_to& other) = default;
					rel_move_to& operator=(const rel_move_to& other) = default;
					rel_move_to(rel_move_to&& other);
					rel_move_to& operator=(rel_move_to&& other);
					rel_move_to(const point& to);
					virtual path_data_type type() const override;
				};

				class rel_line_to : public _Point {
				public:
					rel_line_to() = default;
					rel_line_to(const rel_line_to& other) = default;
					rel_line_to& operator=(const rel_line_to& other) = default;
					rel_line_to(rel_line_to&& other);
					rel_line_to& operator=(rel_line_to&& other);
					rel_line_to(const point& to);
					virtual path_data_type type() const override;
				};

				class _Curve_to : public path_data {
					point _Control_pt1 = { };
					point _Control_pt2 = { };
					point _End_pt = { };
				public:
					_Curve_to() = default;
					_Curve_to(const _Curve_to& other) = default;
					_Curve_to& operator=(const _Curve_to& other) = default;
					_Curve_to(_Curve_to&& other);
					_Curve_to& operator=(_Curve_to&& other);
					_Curve_to(const point& controlPoint1, const point& controlPoint2, const point& endPoint);
					virtual ~_Curve_to();
					virtual path_data_type type() const override = 0;

					void control_point_1(const point& value);
					void control_point_2(const point& value);
					void end_point(const point& value);

					point control_point_1() const;
					point control_point_2() const;
					point end_point() const;
				};

				class curve_to : public _Curve_to {
				public:
					curve_to() = default;
					curve_to(const curve_to& other) = default;
					curve_to& operator=(const curve_to& other) = default;
					curve_to(curve_to&& other);
					curve_to& operator=(curve_to&& other);
					curve_to(const point& controlPoint1, const point& controlPoint2, const point& endPoint);
					virtual path_data_type type() const override;
				};

				class rel_curve_to : public _Curve_to {
				public:
					rel_curve_to() = default;
					rel_curve_to(const rel_curve_to& other) = default;
					rel_curve_to& operator=(const rel_curve_to& other) = default;
					rel_curve_to(rel_curve_to&& other);
					rel_curve_to& operator=(rel_curve_to&& other);
					rel_curve_to(const point& controlPoint1, const point& controlPoint2, const point& endPoint);
					virtual path_data_type type() const override;
				};

				class _Arc : public path_data {
					point _Center;
					double _Radius;
					double _Angle_1;
					double _Angle_2;
				public:
					_Arc();
					_Arc(const _Arc& other) = default;
					_Arc& operator=(const _Arc& other) = default;
					_Arc(_Arc&& other);
					_Arc& operator=(_Arc&& other);
					_Arc(point center, double radius, double angle1, double angle2);
					virtual ~_Arc();
					virtual path_data_type type() const override = 0;

					void center(const point& value);
					void radius(double value);
					void angle_1(double radians);
					void angle_2(double radians);

					point center() const;
					double radius() const;
					double angle_1() const;
					double angle_2() const;
				};

				class arc : public _Arc {
				public:
					arc() = default;
					arc(const arc& other) = default;
					arc& operator=(const arc& other) = default;
					arc(arc&& other);
					arc& operator=(arc&& other);
					arc(point center, double radius, double angle1, double angle2);

					virtual path_data_type type() const override;
				};

				class arc_negative : public _Arc {
				public:
					arc_negative() = default;
					arc_negative(const arc_negative& other) = default;
					arc_negative& operator=(const arc_negative& other) = default;
					arc_negative(arc_negative&& other);
					arc_negative& operator=(arc_negative&& other);
					arc_negative(point center, double radius, double angle1, double angle2);

					virtual path_data_type type() const override;
				};

				class new_sub_path : public path_data {
				public:
					new_sub_path() = default;
					new_sub_path(const new_sub_path& other) = default;
					new_sub_path& operator=(const new_sub_path& other) = default;
					new_sub_path(new_sub_path&& other);
					new_sub_path& operator=(new_sub_path&& other);

					virtual path_data_type type() const override;
				};

				class close_path : public path_data {
				public:
					close_path() = default;
					close_path(const close_path& other) = default;
					close_path& operator=(const close_path& other) = default;
					close_path(close_path&& other);
					close_path& operator=(close_path&& other);

					virtual path_data_type type() const override;
				};

				class change_matrix : public path_data {
					matrix_2d _Matrix = { };
				public:
					change_matrix() = default;
					change_matrix(const change_matrix& other) = default;
					change_matrix& operator=(const change_matrix& other) = default;
					change_matrix(change_matrix&& other);
					change_matrix& operator=(change_matrix&& other);
					change_matrix(const matrix_2d& m);

					void matrix(const matrix_2d& value);

					matrix_2d matrix() const;
					virtual path_data_type type() const override;
				};

				class change_origin : public path_data {
					point _Origin = { };
				public:
					change_origin() = default;
					change_origin(const change_origin& other) = default;
					change_origin& operator=(const change_origin& other) = default;
					change_origin(change_origin&& other);
					change_origin& operator=(change_origin&& other);
					change_origin(const point& origin);

					void origin(const point& value);

					point origin() const;
					virtual path_data_type type() const override;
				};

				// Forward declaration.
				class path_factory;
				class surface;

				class path {
					friend path_factory;
					::std::shared_ptr<::std::vector<::std::unique_ptr<path_data>>> _Data;
					::std::shared_ptr<cairo_path_t> _Cairo_path;
					bool _Has_current_point;
					point _Current_point;
					point _Last_move_to_point;
					rectangle _Extents;
				public:
					typedef cairo_path_t* native_handle_type;
					native_handle_type native_handle() const;

					path() = delete;
					path(const path_factory& pb, const surface& sf);
					path(const path& other) = default;
					path& operator=(const path& other) = default;
					path(path&& other);
					path& operator=(path&& other);

					// Observers
					::std::vector<::std::unique_ptr<path_data>> data() const;
					const ::std::vector<::std::unique_ptr<path_data>>& data_ref() const;
					rectangle path_extents() const;
				};

				class path_factory {
					friend path;
					mutable ::std::recursive_mutex _Lock;
					::std::vector<::std::unique_ptr<path_data>> _Data;
					bool _Has_current_point;
					point _Current_point;
					point _Last_move_to_point;
					point _Extents_pt0;
					point _Extents_pt1;
					matrix_2d _Transform_matrix;
					point _Origin;

					void _Set_current_point_and_last_move_to_point_for_arc(const ::std::vector<::std::unique_ptr<path_data>>& data);
				public:
					path_factory();
					path_factory(const path_factory& other);
					path_factory& operator=(const path_factory& other);
					path_factory(path_factory&& other);
					path_factory& operator=(path_factory&& other);

					// Modifiers
					void append(const path& p);
					void append(const path_factory& p);
					void append(const ::std::vector<::std::unique_ptr<path_data>>& p);
					void new_sub_path();
					void close_path();
					void arc(const point& center, double radius, double angle1, double angle2);
					void arc_negative(const point& center, double radius, double angle1, double angle2);
					void curve_to(const point& pt0, const point& pt1, const point& pt2);
					void line_to(const point& pt);
					void move_to(const point& pt);
					void rect(const rectangle& r);
					void rel_curve_to(const point& dpt0, const point& dpt1, const point& dpt2);
					void rel_line_to(const point& dpt);
					void rel_move_to(const point& dpt);
					void transform_matrix(const matrix_2d& m);
					void origin(const point& pt);
					void reset();

					// Observers
					rectangle path_extents() const;
					bool has_current_point() const;
					point current_point() const;
					matrix_2d transform_matrix() const;
					point origin() const;
					::std::vector<::std::unique_ptr<path_data>> data() const;
					::std::unique_ptr<path_data> data(unsigned int index) const;
					const ::std::vector<::std::unique_ptr<path_data>>& data_ref() const;
				};

				class device {
				protected:
					::std::shared_ptr<cairo_device_t> _Device;
				public:
					typedef cairo_device_t* native_handle_type;
					native_handle_type native_handle() const;

					device() = delete;
					device(const device&) = delete;
					device& operator=(const device&) = delete;
					device(device&& other);
					device& operator=(device&& other);
					explicit device(native_handle_type nh);

					// Modifiers
					void flush();
					void lock();
					void unlock();
				};

				class font_options_factory {
					mutable ::std::recursive_mutex _Lock;
					::std::experimental::io2d::antialias _Antialias = ::std::experimental::io2d::antialias::default_antialias;
					::std::experimental::io2d::subpixel_order _Subpixel_order = ::std::experimental::io2d::subpixel_order::default_subpixel_order;

				public:
					font_options_factory();
					font_options_factory(const font_options_factory&);
					font_options_factory& operator=(const font_options_factory&);
					font_options_factory(font_options_factory&& other);
					font_options_factory& operator=(font_options_factory&& other);

					// Modifiers
					void antialias(::std::experimental::io2d::antialias a);
					void subpixel_order(::std::experimental::io2d::subpixel_order so);

					// Observers
					::std::experimental::io2d::antialias antialias() const;
					::std::experimental::io2d::subpixel_order subpixel_order() const;
				};

				class font_options {
					::std::shared_ptr<cairo_font_options_t> _Font_options;
				public:
					typedef cairo_font_options_t* native_handle_type;
					native_handle_type native_handle() const;

					font_options() = delete;
					font_options(const font_options&) = default;
					font_options& operator=(const font_options&) = default;
					font_options(font_options&& other);
					font_options& operator=(font_options&& other);
					font_options(::std::experimental::io2d::antialias a, ::std::experimental::io2d::subpixel_order so);
					explicit font_options(native_handle_type nh);

					// Observers
					::std::experimental::io2d::antialias antialias() const;
					::std::experimental::io2d::subpixel_order subpixel_order() const;
				};

				class font_face {
				protected:
					::std::shared_ptr<cairo_font_face_t> _Font_face;
				public:
					typedef cairo_font_face_t* native_handle_type;
					native_handle_type native_handle() const;

					font_face() = delete;
					font_face(const font_face&) = default;
					font_face& operator=(const font_face&) = default;
					font_face(font_face&& other);
					font_face& operator=(font_face&& other);
					explicit font_face(native_handle_type nh);
					virtual ~font_face();
				};

				class simple_font_face : public font_face {
				public:
					simple_font_face() = delete;
					simple_font_face(const simple_font_face&) = default;
					simple_font_face& operator=(const simple_font_face&) = default;
					simple_font_face(const ::std::string& family, font_slant slant, font_weight weight);
					simple_font_face(simple_font_face&& other);
					simple_font_face& operator=(simple_font_face&& other);
					virtual ~simple_font_face();

					// Observers
					::std::string family() const;
					font_slant slant() const;
					font_weight weight() const;
				};

				class scaled_font {
					::std::shared_ptr<cairo_scaled_font_t> _Scaled_font;

				public:
					typedef cairo_scaled_font_t* native_handle_type;
					native_handle_type native_handle() const;

					scaled_font() = delete;
					scaled_font(const scaled_font&) = default;
					scaled_font& operator=(const scaled_font&) = default;
					scaled_font(scaled_font&& other);
					scaled_font& operator=(scaled_font&& other);
					explicit scaled_font(native_handle_type nh);
					scaled_font(const font_face& ff, const matrix_2d& fm, const matrix_2d& ctm, const font_options& fo);

					// Observers
					font_extents extents() const;
					::std::experimental::io2d::text_extents text_extents(const ::std::string& utf8) const;
					::std::experimental::io2d::text_extents glyph_extents(const ::std::vector<glyph>& glyphs) const;
					::std::vector<glyph> text_to_glyphs(double x, double y, const ::std::string& utf8) const;
					::std::vector<glyph> text_to_glyphs(double x, double y, const ::std::string& utf8, ::std::vector<text_cluster>& clusters, bool& clustersToGlyphsReverseMap) const;
				};

				// Forward declaration.
				class linear_pattern_factory;
				class mesh_pattern_factory;
				class radial_pattern_factory;
				class solid_color_pattern_factory;
				class surface_pattern_factory;
				class surface;
				class image_surface;

				class pattern {
				public:
					typedef cairo_pattern_t* native_handle_type;

				private:
					friend linear_pattern_factory;
					friend mesh_pattern_factory;
					friend radial_pattern_factory;
					friend solid_color_pattern_factory;
					friend surface_pattern_factory;
					friend surface;

					// Precondition: nh has already had its reference count incremented (either in creation or with cairo_pattern_reference).
					pattern(native_handle_type nh);

					::std::shared_ptr<cairo_pattern_t> _Pattern;
					pattern_type _Pattern_type;
					::std::experimental::io2d::extend _Extend;
					::std::experimental::io2d::filter _Filter;
					matrix_2d _Matrix;

				public:
					native_handle_type native_handle() const;

					pattern() = delete;
					pattern(const pattern&) = default;
					pattern& operator=(const pattern&) = default;
					pattern(pattern&& other);
					pattern& operator=(pattern&& other);

					void extend(::std::experimental::io2d::extend e);
					void filter(::std::experimental::io2d::filter f);
					void matrix(const matrix_2d& m);

					::std::experimental::io2d::extend extend() const;
					::std::experimental::io2d::filter filter() const;
					matrix_2d matrix() const;
					pattern_type type() const;
				};

				class solid_color_pattern_factory {
					mutable ::std::recursive_mutex _Lock;
					pattern_type _Pattern_type;
					rgba_color _Color;

				public:
					solid_color_pattern_factory();
					solid_color_pattern_factory(const solid_color_pattern_factory&);
					solid_color_pattern_factory& operator=(const solid_color_pattern_factory&);
					solid_color_pattern_factory(solid_color_pattern_factory&& other);
					solid_color_pattern_factory& operator=(solid_color_pattern_factory&& other);
					solid_color_pattern_factory(const rgba_color& color);

					// Modifiers
					void rgba(const rgba_color& color);
					void red(double red);
					void green(double green);
					void blue(double blue);
					void alpha(double alpha);

					// Observers
					rgba_color rgba() const;
					double red() const;
					double green() const;
					double blue() const;
					double alpha() const;
				};

				class linear_pattern_factory {
					mutable ::std::recursive_mutex _Lock;
					pattern_type _Pattern_type;

					point _Point0;
					point _Point1;
					::std::vector<::std::tuple<double, rgba_color>> _Color_stops;

				public:
					linear_pattern_factory();
					linear_pattern_factory(const linear_pattern_factory&);
					linear_pattern_factory& operator=(const linear_pattern_factory&);
					linear_pattern_factory(linear_pattern_factory&& other);
					linear_pattern_factory& operator=(linear_pattern_factory&& other);
					linear_pattern_factory(const point& pt0, const point& pt1);

					// Modifiers
					void add_color_stop_rgba(double offset, const rgba_color& color);
					void color_stop_rgba(unsigned int index, double offset, const rgba_color& color);
					void linear_points(const point& pt0, const point& pt1);

					// Observers
					int color_stop_count() const;
					void color_stop_rgba(unsigned int index, double& offset, rgba_color& color) const;
					void linear_points(point& pt0, point& pt1) const;
				};

				class radial_pattern_factory {
					mutable ::std::recursive_mutex _Lock;
					pattern_type _Pattern_type;

					point _Center0;
					double _Radius0;
					point _Center1;
					double _Radius1;
					::std::vector<::std::tuple<double, rgba_color>> _Color_stops;

				public:
					radial_pattern_factory();
					radial_pattern_factory(const radial_pattern_factory&);
					radial_pattern_factory& operator=(const radial_pattern_factory&);
					radial_pattern_factory(radial_pattern_factory&& other);
					radial_pattern_factory& operator=(radial_pattern_factory&& other);
					radial_pattern_factory(const point& center0, double radius0, const point& center1, double radius1);

					// Modifiers
					void add_color_stop_rgba(double offset, const rgba_color& color);
					void color_stop_rgba(unsigned int index, double offset, const rgba_color& color);
					void radial_circles(const point& center0, double radius0, const point& center1, double radius1);

					// Observers
					int color_stop_count() const;
					void color_stop_rgba(unsigned int index, double& offset, rgba_color& color) const;
					void radial_circles(point& center0, double& radius0, point& center1, double& radius1) const;
				};

				class mesh_pattern_factory {
					mutable ::std::recursive_mutex _Lock;
					pattern_type _Pattern_type;

					bool _Has_current_patch;
					unsigned int _Current_patch_index;
					int _Current_patch_side_count;
					point _Current_patch_initial_point;
					typedef ::std::map<unsigned int, point> _Control_points;
					typedef ::std::map<unsigned int, rgba_color> _Corner_colors;
					// <Patch data, control points, corner colors>
					typedef ::std::tuple<::std::experimental::io2d::path_factory, _Control_points, _Corner_colors> _Patch;
					::std::vector<_Patch> _Patches;
				public:
					mesh_pattern_factory();
					mesh_pattern_factory(const mesh_pattern_factory&);
					mesh_pattern_factory& operator=(const mesh_pattern_factory&);
					mesh_pattern_factory(mesh_pattern_factory&& other);
					mesh_pattern_factory& operator=(mesh_pattern_factory&& other);

					// Modifiers
					void begin_patch();
					void begin_edit_patch(unsigned int patch_num);
					void end_patch();
					void move_to(const point& pt);
					void line_to(const point& pt);
					void curve_to(const point& pt0, const point& pt1, const point& pt2);
					void control_point(unsigned int point_num, const point& pt);
					void corner_color_rgba(unsigned int corner_num, const rgba_color& color);

					// Observers
					unsigned int patch_count() const;
					::std::experimental::io2d::path_factory path_factory(unsigned int patch_num) const;
					bool control_point(unsigned int patch_num, unsigned int point_num, point& controlPoint) const;
					bool corner_color_rgba(unsigned int patch_num, unsigned int corner_num, rgba_color& color) const;
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

					const double _Line_join_miter_miter_limit = 10000.0;

					// State - unsaved
					typedef rectangle _Dirty_type;
					_Dirty_type _Dirty_rect;
					::std::experimental::io2d::format _Format;
					::std::experimental::io2d::content _Content;

					// State - saved
					typedef point _Device_offtype;
					_Device_offtype _Device_offset = { 0.0, 0.0 };
					::std::experimental::io2d::pattern _Pattern;
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

					::std::stack<::std::tuple<_Device_offtype, ::std::experimental::io2d::pattern, ::std::experimental::io2d::antialias, ::std::experimental::io2d::dashes, ::std::experimental::io2d::fill_rule, ::std::experimental::io2d::line_cap, ::std::experimental::io2d::line_join, _Line_width_type, _Miter_limit_type, ::std::experimental::io2d::compositing_operator, _Tolerance_type, ::std::experimental::io2d::path, ::std::experimental::io2d::path, ::std::experimental::io2d::path_factory, _Transform_matrix_type, ::std::experimental::io2d::font_face, _Font_matrix_type, ::std::experimental::io2d::font_options>> _Saved_state;

					void _Ensure_state();
					void _Ensure_state(::std::error_code& ec) noexcept;

					surface(::std::experimental::io2d::format fmt, int width, int height);
				public:

					typedef _Surface_native_handles native_handle_type;
					native_handle_type native_handle() const;

					surface() = delete;
					surface(const surface&) = delete;
					surface& operator=(const surface&) = delete;
					surface(surface&& other);
					surface& operator=(surface&& other);

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
					void device_offset(const point& offset);
					void write_to_file(const ::std::string& filename);
					image_surface map_to_image();
					image_surface map_to_image(const rectangle& extents);
					void unmap_image(image_surface& image);
					virtual void save();
					virtual void restore();
					void pattern();
					void pattern(const ::std::experimental::io2d::pattern& source);
					void antialias(::std::experimental::io2d::antialias a);
					void dashes();
					void dashes(const ::std::experimental::io2d::dashes& d);
					void fill_rule(::std::experimental::io2d::fill_rule fr);
					void line_cap(::std::experimental::io2d::line_cap lc);
					void line_join(::std::experimental::io2d::line_join lj);
					void line_width(double width);
					void miter_limit(double limit);
					void compositing_operator(::std::experimental::io2d::compositing_operator co);
					void tolerance(double t);
					void clip();
					void clip_immediate();
					void reclip();
					void path();
					void path(const ::std::experimental::io2d::path& p);

					// \ref{\iotwod.surface.modifiers.immediatepath}, immediate path modifiers:
					::std::experimental::io2d::path_factory& immediate();

					// \ref{\iotwod.surface.modifiers.render}, render modifiers:
					void paint();
					void paint(const rgba_color& c);
					void paint(const ::std::experimental::io2d::pattern& pttn);
					void paint(const surface& s, const point& origin = point{ 0.0, 0.0 }, extend e = extend::default_extend, filter f = filter::default_filter);
					void paint(const surface& s, const matrix_2d& m, extend e = extend::default_extend, filter f = filter::default_filter);
					void paint(double alpha);
					void paint(const rgba_color& c, double alpha);
					void paint(const ::std::experimental::io2d::pattern& pttn, double alpha);
					void paint(const surface& s, double alpha, const point& origin = point{ 0.0, 0.0 }, extend e = extend::default_extend, filter f = filter::default_filter);
					void paint(const surface& s, double alpha, const matrix_2d& m, extend e = extend::default_extend, filter f = filter::default_filter);
					void fill();
					void fill(const rgba_color& c);
					void fill(const ::std::experimental::io2d::pattern& pttn);
					void fill(const surface& s, const point& origin = point{ 0.0, 0.0 }, extend e = extend::default_extend, filter f = filter::default_filter);
					void fill(const surface& s, const matrix_2d& m, extend e = extend::default_extend, filter f = filter::default_filter);
					void fill_immediate();
					void fill_immediate(const rgba_color& c);
					void fill_immediate(const ::std::experimental::io2d::pattern& pttn);
					void fill_immediate(const surface& s, const point& origin = point{ 0.0, 0.0 }, extend e = extend::default_extend, filter f = filter::default_filter);
					void fill_immediate(const surface& s, const matrix_2d& m, extend e = extend::default_extend, filter f = filter::default_filter);
					void stroke();
					void stroke(const rgba_color& c);
					void stroke(const ::std::experimental::io2d::pattern& pttn);
					void stroke(const surface& s, const point& origin = point{ 0.0, 0.0 }, extend e = extend::default_extend, filter f = filter::default_filter);
					void stroke(const surface& s, const matrix_2d& m, extend e = extend::default_extend, filter f = filter::default_filter);
					void stroke_immediate();
					void stroke_immediate(const rgba_color& c);
					void stroke_immediate(const ::std::experimental::io2d::pattern& pttn);
					void stroke_immediate(const surface& s, const point& origin = point{ 0.0, 0.0 }, extend e = extend::default_extend, filter f = filter::default_filter);
					void stroke_immediate(const surface& s, const matrix_2d& m, extend e = extend::default_extend, filter f = filter::default_filter);

					// \ref{\iotwod.surface.modifiers.maskrender}, mask render modifiers:
					void mask(const ::std::experimental::io2d::pattern& maskPttn);
					void mask(const ::std::experimental::io2d::pattern& maskPttn, const rgba_color& c);
					void mask(const ::std::experimental::io2d::pattern& maskPttn, const ::std::experimental::io2d::pattern& pttn);
					void mask(const ::std::experimental::io2d::pattern& maskPttn, const surface& s, const point& origin = point{ 0.0, 0.0 }, extend e = extend::default_extend, filter f = filter::default_filter);
					void mask(const ::std::experimental::io2d::pattern& maskPttn, const surface& s, const matrix_2d& m, extend e = extend::default_extend, filter f = filter::default_filter);
					void mask(const surface& maskSurface);
					void mask(const surface& maskSurface, const rgba_color& c);
					void mask(const surface& maskSurface, const ::std::experimental::io2d::pattern& pttn);
					void mask(const surface& maskSurface, const surface& s, const point& origin = point{ 0.0, 0.0 }, extend e = extend::default_extend, filter f = filter::default_filter);
					void mask(const surface& maskSurface, const surface& s, const matrix_2d& m, extend e = extend::default_extend, filter f = filter::default_filter);
					void mask(const surface& maskSurface, const point& maskOrigin);
					void mask(const surface& maskSurface, const point& maskOrigin, const rgba_color& c);
					void mask(const surface& maskSurface, const point& maskOrigin, const ::std::experimental::io2d::pattern& pttn);
					void mask(const surface& maskSurface, const point& maskOrigin, const surface& s, const point& origin = point{ 0.0, 0.0 }, extend e = extend::default_extend, filter f = filter::default_filter);
					void mask(const surface& maskSurface, const point& maskOrigin, const surface& s, const matrix_2d& m, extend e = extend::default_extend, filter f = filter::default_filter);
					void mask_immediate(const ::std::experimental::io2d::pattern& maskPttn);
					void mask_immediate(const ::std::experimental::io2d::pattern& maskPttn, const rgba_color& c);
					void mask_immediate(const ::std::experimental::io2d::pattern& maskPttn, const ::std::experimental::io2d::pattern& pttn);
					void mask_immediate(const ::std::experimental::io2d::pattern& maskPttn, const surface& s, const point& origin = point{ 0.0, 0.0 }, extend e = extend::default_extend, filter f = filter::default_filter);
					void mask_immediate(const ::std::experimental::io2d::pattern& maskPttn, const surface& s, const matrix_2d& m, extend e = extend::default_extend, filter f = filter::default_filter);
					void mask_immediate(const surface& maskSurface);
					void mask_immediate(const surface& maskSurface, const rgba_color& c);
					void mask_immediate(const surface& maskSurface, const ::std::experimental::io2d::pattern& pttn);
					void mask_immediate(const surface& maskSurface, const surface& s, const point& origin = point{ 0.0, 0.0 }, extend e = extend::default_extend, filter f = filter::default_filter);
					void mask_immediate(const surface& maskSurface, const surface& s, const matrix_2d& m, extend e = extend::default_extend, filter f = filter::default_filter);
					void mask_immediate(const surface& maskSurface, const point& maskOrigin);
					void mask_immediate(const surface& maskSurface, const point& maskOrigin, const rgba_color& c);
					void mask_immediate(const surface& maskSurface, const point& maskOrigin, const ::std::experimental::io2d::pattern& pttn);
					void mask_immediate(const surface& maskSurface, const point& maskOrigin, const surface& s, const point& origin = point{ 0.0, 0.0 }, extend e = extend::default_extend, filter f = filter::default_filter);
					void mask_immediate(const surface& maskSurface, const point& maskOrigin, const surface& s, const matrix_2d& m, extend e = extend::default_extend, filter f = filter::default_filter);

					// \ref{\iotwod.surface.modifiers.textrender}, text render modifiers:
					point show_text(const ::std::string& utf8, const point& position);
					point show_text(const ::std::string& utf8, const point& position, const rgba_color& c);
					point show_text(const ::std::string& utf8, const point& position, const ::std::experimental::io2d::pattern& pttn);
					point show_text(const ::std::string& utf8, const point& position, const surface& s, const point& origin = point{ 0.0, 0.0 }, extend e = extend::default_extend, filter f = filter::default_filter);
					point show_text(const ::std::string& utf8, const point& position, const surface& s, const matrix_2d& m, extend e = extend::default_extend, filter f = filter::default_filter);
					void show_glyphs(const ::std::vector<glyph>& glyphs);
					void show_glyphs(const ::std::vector<glyph>& glyphs, const rgba_color& c);
					void show_glyphs(const ::std::vector<glyph>& glyphs, const ::std::experimental::io2d::pattern& pttn);
					void show_glyphs(const ::std::vector<glyph>& glyphs, const surface& s, const point& origin = point{ 0.0, 0.0 }, extend e = extend::default_extend, filter f = filter::default_filter);
					void show_glyphs(const ::std::vector<glyph>& glyphs, const surface& s, const matrix_2d& m, extend e = extend::default_extend, filter f = filter::default_filter);
					void show_text_glyphs(const ::std::string& utf8,
						const ::std::vector<glyph>& glyphs,
						const ::std::vector<text_cluster>& clusters,
						bool clusterToGlyphsMapReverse);
					void show_text_glyphs(const ::std::string& utf8,
						const ::std::vector<glyph>& glyphs,
						const ::std::vector<text_cluster>& clusters,
						bool clusterToGlyphsMapReverse,
						const rgba_color& c);
					void show_text_glyphs(const ::std::string& utf8,
						const ::std::vector<glyph>& glyphs,
						const ::std::vector<text_cluster>& clusters,
						bool clusterToGlyphsMapReverse,
						const ::std::experimental::io2d::pattern& pttn);
					void show_text_glyphs(const ::std::string& utf8,
						const ::std::vector<glyph>& glyphs,
						const ::std::vector<text_cluster>& clusters,
						bool clusterToGlyphsMapReverse,
						const surface& s,
						const point& origin = point{ 0.0, 0.0 },
						extend e = extend::default_extend,
						filter f = filter::default_filter);
					void show_text_glyphs(const ::std::string& utf8,
						const ::std::vector<glyph>& glyphs,
						const ::std::vector<text_cluster>& clusters,
						bool clusterToGlyphsMapReverse,
						const surface& s,
						const matrix_2d& m,
						extend e = extend::default_extend,
						filter f = filter::default_filter);

					// \ref{\iotwod.surface.modifiers.transform}, transformation modifiers:
					void matrix(const matrix_2d& matrix);

					// \ref{\iotwod.surface.modifiers.font}, font modifiers:
					void select_font_face(const ::std::string& family, font_slant sl,
						font_weight w);
					void font_size(double s);
					void font_matrix(const matrix_2d& m);
					void font_options(const font_options& fo);
					void font_face(const ::std::experimental::io2d::font_face& f);
					void scaled_font(const ::std::experimental::io2d::scaled_font& sf);

					// \ref{\iotwod.surface.observers.stateobjects}, state object observers:
					::std::experimental::io2d::path path(const path_factory& pf) const;
					::std::experimental::io2d::font_options font_options(const font_options_factory& fo) const;
					::std::experimental::io2d::pattern create_pattern(const solid_color_pattern_factory& f) const;
					::std::experimental::io2d::pattern create_pattern(const linear_pattern_factory& f) const;
					::std::experimental::io2d::pattern create_pattern(const radial_pattern_factory& f) const;
					::std::experimental::io2d::pattern create_pattern(const mesh_pattern_factory& f) const;
					::std::experimental::io2d::pattern create_pattern(surface_pattern_factory& f) const;

					// \ref{\iotwod.surface.observers.state}, state observers:
					::std::experimental::io2d::content content() const;
					point device_offset() const;
					bool has_surface_resource() const;
					::std::experimental::io2d::pattern pattern() const;
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
					bool in_clip(const point& pt) const;
					::std::vector<rectangle> clip_rectangles() const;

					// \ref{\iotwod.surface.observers.render}, render observers:
					rectangle fill_extents() const;
					rectangle fill_extents_immediate() const;
					bool in_fill(const point& pt) const;
					bool in_fill_immediate(const point& pt) const;
					rectangle stroke_extents() const;
					rectangle stroke_extents_immediate() const;
					bool in_stroke(const point& pt) const;
					bool in_stroke_immediate(const point& pt) const;
					::std::experimental::io2d::font_extents font_extents() const;
					::std::experimental::io2d::text_extents text_extents(const ::std::string& utf8) const;
					::std::experimental::io2d::text_extents glyph_extents(const ::std::vector<glyph>& glyphs) const;

					// \ref{\iotwod.surface.observers.transform}, transformation observers:
					matrix_2d matrix() const;
					point user_to_device() const;
					point user_to_device_distance() const;
					point device_to_user() const;
					point device_to_user_distance() const;

					// \ref{\iotwod.surface.observers.font}, font observers:
					matrix_2d font_matrix() const;
					::std::experimental::io2d::font_options font_options() const;
					::std::experimental::io2d::font_face font_face() const;
					::std::experimental::io2d::scaled_font scaled_font() const;
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

					void _Make_native_surface_and_context();
					void _All_dimensions(int w, int h, int dw, int dh);
					void _Render_to_native_surface();
					void _Resize_window();
					::std::stack<::std::tuple<::std::experimental::io2d::scaling, _Width_type, _Height_type, _Display_width_type, _Display_height_type>> _Display_saved_state;
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
					display_surface(int preferredWidth, int preferredHeight, ::std::experimental::io2d::format preferredFormat, ::std::experimental::io2d::scaling scl = ::std::experimental::io2d::scaling::default_scaling);

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
					int join();

					::std::experimental::io2d::format format() const;
					int width() const;
					int height() const;
					int display_width() const;
					int display_height() const;
				};

				class surface_pattern_factory {
					mutable ::std::recursive_mutex _Lock;
					pattern_type _Pattern_type;
					image_surface _Surface;

					friend ::std::experimental::io2d::surface;

				public:
					surface_pattern_factory();
					surface_pattern_factory(surface_pattern_factory&);
					surface_pattern_factory& operator=(surface_pattern_factory&);
					surface_pattern_factory(surface_pattern_factory&& other);
					surface_pattern_factory& operator=(surface_pattern_factory&& other);
					surface_pattern_factory(::std::experimental::io2d::surface& s);

					// Modifiers
					image_surface surface(::std::experimental::io2d::surface& s);

					// Observers
					const image_surface& surface() const;
				};

				int format_stride_for_width(format format, int width);
				display_surface make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, scaling scl = scaling::default_scaling);
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

	template<>
	struct is_error_code_enum<::cairo_status_t>
		: public ::std::true_type{ };

	::std::error_condition make_error_condition(experimental::io2d::io2d_error e) noexcept;

	::std::error_code make_error_code(cairo_status_t e) noexcept;
}

#endif