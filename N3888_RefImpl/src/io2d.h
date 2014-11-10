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
					no_memory,
					invalid_restore,
					invalid_pop_group,
					no_current_point,
					invalid_matrix,
					invalid_status,
					null_pointer,
					invalid_string,
					invalid_path_data,
					read_error,
					write_error,
					surface_finished,
					surface_type_mismatch,
					pattern_type_mismatch,
					invalid_content,
					invalid_format,
					invalid_visual,
					file_not_found,
					invalid_dash,
					invalid_dsc_comment,
					invalid_index,
					clip_not_representable,
					temp_file_error,
					invalid_stride,
					font_type_mismatch,
					user_font_immutable,
					user_font_error,
					negative_count,
					invalid_clusters,
					invalid_slant,
					invalid_weight,
					invalid_size,
					user_font_not_implemented,
					device_type_mismatch,
					device_error,
					invalid_mesh_construction,
					device_finished,
					last_value
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

				struct rectangle {
					double x;
					double y;
					double width;
					double height;
				};

				struct rgba_color {
					double r;
					double g;
					double b;
					double a;

					const static rgba_color alice_blue;
					const static rgba_color antique_white;
					const static rgba_color aqua;
					const static rgba_color aquamarine;
					const static rgba_color azure;
					const static rgba_color beige;
					const static rgba_color bisque;
					const static rgba_color black;
					const static rgba_color blanched_almond;
					const static rgba_color blue;
					const static rgba_color blue_violet;
					const static rgba_color brown;
					const static rgba_color burly_wood;
					const static rgba_color cadet_blue;
					const static rgba_color chartreuse;
					const static rgba_color chocolate;
					const static rgba_color coral;
					const static rgba_color cornflower_blue;
					const static rgba_color cornsilk;
					const static rgba_color crimson;
					const static rgba_color cyan;
					const static rgba_color dark_blue;
					const static rgba_color dark_cyan;
					const static rgba_color dark_goldenrod;
					const static rgba_color dark_gray;
					const static rgba_color dark_green;
					const static rgba_color dark_grey;
					const static rgba_color dark_khaki;
					const static rgba_color dark_magenta;
					const static rgba_color dark_olive_green;
					const static rgba_color dark_orange;
					const static rgba_color dark_orchid;
					const static rgba_color dark_red;
					const static rgba_color dark_salmon;
					const static rgba_color dark_sea_green;
					const static rgba_color dark_slate_blue;
					const static rgba_color dark_slate_gray;
					const static rgba_color dark_slate_grey;
					const static rgba_color dark_turquoise;
					const static rgba_color dark_violet;
					const static rgba_color deep_pink;
					const static rgba_color deep_sky_blue;
					const static rgba_color dim_gray;
					const static rgba_color dim_grey;
					const static rgba_color dodger_blue;
					const static rgba_color firebrick;
					const static rgba_color floral_white;
					const static rgba_color forest_green;
					const static rgba_color fuchsia;
					const static rgba_color gainsboro;
					const static rgba_color ghost_white;
					const static rgba_color gold;
					const static rgba_color goldenrod;
					const static rgba_color gray;
					const static rgba_color green;
					const static rgba_color green_yellow;
					const static rgba_color grey;
					const static rgba_color honeydew;
					const static rgba_color hot_pink;
					const static rgba_color indian_red;
					const static rgba_color indigo;
					const static rgba_color ivory;
					const static rgba_color khaki;
					const static rgba_color lavender;
					const static rgba_color lavender_blush;
					const static rgba_color lawn_green;
					const static rgba_color lemon_chiffon;
					const static rgba_color light_blue;
					const static rgba_color light_coral;
					const static rgba_color light_cyan;
					const static rgba_color light_goldenrod_yellow;
					const static rgba_color light_gray;
					const static rgba_color light_green;
					const static rgba_color light_grey;
					const static rgba_color light_pink;
					const static rgba_color light_salmon;
					const static rgba_color light_sea_green;
					const static rgba_color light_sky_blue;
					const static rgba_color light_slate_gray;
					const static rgba_color light_slate_grey;
					const static rgba_color light_steel_blue;
					const static rgba_color light_yellow;
					const static rgba_color lime;
					const static rgba_color lime_green;
					const static rgba_color linen;
					const static rgba_color magenta;
					const static rgba_color maroon;
					const static rgba_color medium_aquamarine;
					const static rgba_color medium_blue;
					const static rgba_color medium_orchid;
					const static rgba_color medium_purple;
					const static rgba_color medium_sea_green;
					const static rgba_color medium_slate_blue;
					const static rgba_color medium_spring_green;
					const static rgba_color medium_turquoise;
					const static rgba_color medium_violet_red;
					const static rgba_color midnight_blue;
					const static rgba_color mint_cream;
					const static rgba_color misty_rose;
					const static rgba_color moccasin;
					const static rgba_color navajo_white;
					const static rgba_color navy;
					const static rgba_color old_lace;
					const static rgba_color olive;
					const static rgba_color olive_drab;
					const static rgba_color orange;
					const static rgba_color orange_red;
					const static rgba_color orchid;
					const static rgba_color pale_goldenrod;
					const static rgba_color pale_green;
					const static rgba_color pale_turquoise;
					const static rgba_color pale_violet_red;
					const static rgba_color papaya_whip;
					const static rgba_color peach_puff;
					const static rgba_color peru;
					const static rgba_color pink;
					const static rgba_color plum;
					const static rgba_color powder_blue;
					const static rgba_color purple;
					const static rgba_color red;
					const static rgba_color rosy_brown;
					const static rgba_color royal_blue;
					const static rgba_color saddle_brown;
					const static rgba_color salmon;
					const static rgba_color sandy_brown;
					const static rgba_color sea_green;
					const static rgba_color sea_shell;
					const static rgba_color sienna;
					const static rgba_color silver;
					const static rgba_color sky_blue;
					const static rgba_color slate_blue;
					const static rgba_color slate_gray;
					const static rgba_color slate_grey;
					const static rgba_color snow;
					const static rgba_color spring_green;
					const static rgba_color steel_blue;
					const static rgba_color tan;
					const static rgba_color teal;
					const static rgba_color thistle;
					const static rgba_color tomato;
					const static rgba_color transparent_black; // Note: Not in CSS3.
					const static rgba_color turquoise;
					const static rgba_color violet;
					const static rgba_color wheat;
					const static rgba_color white;
					const static rgba_color white_smoke;
					const static rgba_color yellow;
					const static rgba_color yellow_green;
				};

				rgba_color operator*(const rgba_color& lhs, double rhs);
				rgba_color& operator*=(rgba_color& lhs, double rhs);
				bool operator==(const rgba_color& lhs, const rgba_color& rhs);
				bool operator!=(const rgba_color& lhs, const rgba_color& rhs);

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

				struct point {
					double x;
					double y;
				};

				point operator+(const point& lhs);
				point operator+(const point& lhs, const point& rhs);
				point operator+(const point& lhs, double rhs);
				point& operator+=(point& lhs, const point& rhs);
				point& operator+=(point& lhs, double rhs);
				point operator-(const point& lhs);
				point operator-(const point& lhs, const point& rhs);
				point operator-(const point& lhs, double rhs);
				point& operator-=(point& lhs, const point& rhs);
				point& operator-=(point& lhs, double rhs);
				point operator*(const point& lhs, const point& rhs);
				point operator*(const point& lhs, double rhs);
				point& operator*=(point& lhs, const point& rhs);
				point& operator*=(point& lhs, double rhs);
				point operator/(const point& lhs, const point& rhs);
				point operator/(const point& lhs, double rhs);
				point& operator/=(point& lhs, const point& rhs);
				point& operator/=(point& lhs, double rhs);
				bool operator==(const point& lhs, const point& rhs);
				bool operator!=(const point& lhs, const point& rhs);

				struct glyph {
					unsigned long index;
					double x;
					double y;
				};

				struct text_cluster {
					int num_bytes;
					int num_glyphs;
				};

				struct font_extents {
					double ascent;
					double descent;
					double height;
					double max_x_advance;
					double max_y_advance;
				};

				struct text_extents {
					double x_bearing;
					double y_bearing;
					double width;
					double height;
					double x_advance;
					double y_advance;
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
					virtual ~path_data();

					virtual path_data_type type() const = 0;
				};

				class _Point_path_data : public path_data {
					point _Data = { };
				public:
					_Point_path_data() = default;
					_Point_path_data(const _Point_path_data& other) = default;
					_Point_path_data& operator=(const _Point_path_data& other) = default;
					_Point_path_data(const point& to);
					virtual path_data_type type() const override = 0;

					point to() const;
					void to(const point& value);
				};

				class move_to_path_data : public _Point_path_data {
				public:
					move_to_path_data() = default;
					move_to_path_data(const move_to_path_data& other) = default;
					move_to_path_data& operator=(const move_to_path_data& other) = default;
					move_to_path_data(const point& to);
					virtual path_data_type type() const override;
				};

				class line_to_path_data : public _Point_path_data {
				public:
					line_to_path_data() = default;
					line_to_path_data(const line_to_path_data& other) = default;
					line_to_path_data& operator=(const line_to_path_data& other) = default;
					line_to_path_data(const point& to);
					virtual path_data_type type() const override;
				};

				class rel_move_to_path_data : public _Point_path_data {
				public:
					rel_move_to_path_data() = default;
					rel_move_to_path_data(const rel_move_to_path_data& other) = default;
					rel_move_to_path_data& operator=(const rel_move_to_path_data& other) = default;
					rel_move_to_path_data(const point& to);
					virtual path_data_type type() const override;
				};

				class rel_line_to_path_data : public _Point_path_data {
				public:
					rel_line_to_path_data() = default;
					rel_line_to_path_data(const rel_line_to_path_data& other) = default;
					rel_line_to_path_data& operator=(const rel_line_to_path_data& other) = default;
					rel_line_to_path_data(const point& to);
					virtual path_data_type type() const override;
				};

				class _Curve_to_path_data : public path_data {
					point _Control_pt1 = { };
					point _Control_pt2 = { };
					point _End_pt = { };
				public:
					_Curve_to_path_data() = default;
					_Curve_to_path_data(const _Curve_to_path_data& other) = default;
					_Curve_to_path_data& operator=(const _Curve_to_path_data& other) = default;
					_Curve_to_path_data(const point& controlPoint1, const point& controlPoint2, const point& endPoint);
					virtual path_data_type type() const override = 0;

					void control_point_1(const point& value);
					void control_point_2(const point& value);
					void end_point(const point& value);

					point control_point_1() const;
					point control_point_2() const;
					point end_point() const;
				};

				class curve_to_path_data : public _Curve_to_path_data {
				public:
					curve_to_path_data() = default;
					curve_to_path_data(const curve_to_path_data& other) = default;
					curve_to_path_data& operator=(const curve_to_path_data& other) = default;
					curve_to_path_data(const point& controlPoint1, const point& controlPoint2, const point& endPoint);
					virtual path_data_type type() const override;
				};

				class rel_curve_to_path_data : public _Curve_to_path_data {
				public:
					rel_curve_to_path_data() = default;
					rel_curve_to_path_data(const rel_curve_to_path_data& other) = default;
					rel_curve_to_path_data& operator=(const rel_curve_to_path_data& other) = default;
					rel_curve_to_path_data(const point& controlPoint1, const point& controlPoint2, const point& endPoint);
					virtual path_data_type type() const override;
				};

				class _Arc_path_data : public path_data {
					point _Center;
					double _Radius;
					double _Angle_1;
					double _Angle_2;
				public:
					_Arc_path_data();
					_Arc_path_data(const _Arc_path_data& other) = default;
					_Arc_path_data& operator=(const _Arc_path_data& other) = default;
					_Arc_path_data(point center, double radius, double angle1, double angle2);
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

				class arc_path_data : public _Arc_path_data {
				public:
					arc_path_data() = default;
					arc_path_data(const arc_path_data& other) = default;
					arc_path_data& operator=(const arc_path_data& other) = default;
					arc_path_data(point center, double radius, double angle1, double angle2);
					virtual path_data_type type() const override;
				};

				class arc_negative_path_data : public _Arc_path_data {
				public:
					arc_negative_path_data() = default;
					arc_negative_path_data(const arc_negative_path_data& other) = default;
					arc_negative_path_data& operator=(const arc_negative_path_data& other) = default;
					arc_negative_path_data(point center, double radius, double angle1, double angle2);
					virtual path_data_type type() const override;
				};

				class new_sub_path_path_data : public path_data {
				public:
					virtual path_data_type type() const override;
				};

				class close_path_path_data : public path_data {
				public:
					virtual path_data_type type() const override;
				};

				class change_matrix_path_data : public path_data {
					matrix_2d _Matrix = { };
				public:
					change_matrix_path_data() = default;
					change_matrix_path_data(const change_matrix_path_data& other) = default;
					change_matrix_path_data& operator=(const change_matrix_path_data& other) = default;
					change_matrix_path_data(const matrix_2d& m);

					void matrix(const matrix_2d& value);

					matrix_2d matrix() const;
					virtual path_data_type type() const override;
				};

				class change_origin_path_data : public path_data {
					point _Origin = { };
				public:
					change_origin_path_data() = default;
					change_origin_path_data(const change_origin_path_data& other) = default;
					change_origin_path_data& operator=(const change_origin_path_data& other) = default;
					change_origin_path_data(const point& origin);

					void origin(const point& value);

					point origin() const;
					virtual path_data_type type() const override;
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

				// Forward declaration.
				class path_factory;

				class path {
					friend class path_factory;
					::std::shared_ptr<::std::vector<::std::unique_ptr<path_data>>> _Data;
					bool _Has_current_point;
					point _Current_point;
					point _Last_move_to_point;
					rectangle _Extents;
				public:
					typedef cairo_path_t* native_handle_type;

					path() = delete;
					path(const path_factory& pb);
					path(const path& other) = default;
					path& operator=(const path& other) = default;
					path(path&& other);
					path& operator=(path&& other);

					// Observers
					::std::vector<::std::unique_ptr<path_data>> get_data() const;
					const ::std::vector<::std::unique_ptr<path_data>>& get_data_ref() const;
					rectangle get_path_extents() const;
				};

				class path_factory {
					friend class path;
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
					path get_path() const;
					rectangle get_path_extents() const;
					bool has_current_point() const;
					point current_point() const;
					matrix_2d transform_matrix() const;
					point origin() const;
					::std::vector<::std::unique_ptr<path_data>> get_data() const;
					::std::unique_ptr<path_data> get_data(unsigned int index) const;
					const ::std::vector<::std::unique_ptr<path_data>>& get_data_ref() const;
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

				// Forward declaration.
				class font_options;

				class font_options_factory {
					mutable ::std::recursive_mutex _Lock;
					antialias _Antialias = antialias::default_antialias;
					subpixel_order _Subpixel_order = subpixel_order::default_subpixel_order;

				public:
					font_options_factory();
					font_options_factory(const font_options_factory&);
					font_options_factory& operator=(const font_options_factory&);
					font_options_factory(font_options_factory&& other);
					font_options_factory& operator=(font_options_factory&& other);

					// Modifiers
					void set_antialias(antialias a);
					void set_subpixel_order(subpixel_order so);

					// Observers
					font_options get_font_options() const;
					antialias get_antialias() const;
					subpixel_order get_subpixel_order() const;
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
					font_options(antialias a, subpixel_order so);
					explicit font_options(native_handle_type nh);

					// Observers
					antialias get_antialias() const;
					subpixel_order get_subpixel_order() const;
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
					font_extents get_extents() const;
					text_extents get_text_extents(const ::std::string& utf8) const;
					text_extents get_glyph_extents(const ::std::vector<glyph>& glyphs) const;
					::std::vector<glyph> text_to_glyphs(double x, double y, const ::std::string& utf8) const;
					::std::vector<glyph> text_to_glyphs(double x, double y, const ::std::string& utf8, ::std::vector<text_cluster>& clusters, bool& clustersToGlyphsReverseMap) const;
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
					::std::string get_family() const;
					font_slant get_slant() const;
					font_weight get_weight() const;
				};

				// Forward declaration.
				class image_surface;

				// Forward declaration.
				class linear_pattern_factory;
				class mesh_pattern_factory;
				class radial_pattern_factory;
				class raster_source_pattern_factory;
				class solid_color_pattern_factory;
				class surface;

				class pattern {
				public:
					typedef cairo_pattern_t* native_handle_type;

				private:
					friend class linear_pattern_factory;
					friend class mesh_pattern_factory;
					friend class radial_pattern_factory;
					friend class raster_source_pattern_factory;
					friend class solid_color_pattern_factory;
					friend class surface;

					pattern(native_handle_type nh);

					cairo_pattern_t* _Pattern;
					pattern_type _Pattern_type;

				public:
					native_handle_type native_handle() const;

					pattern() = delete;
					pattern(const pattern&) = default;
					pattern& operator=(const pattern&) = default;
					pattern(pattern&& other);
					pattern& operator=(pattern&& other);

					~pattern();

					pattern_type get_type() const;
				};

				class solid_color_pattern_factory {
					mutable ::std::recursive_mutex _Lock;
					pattern_type _Pattern_type;
					extend _Extend;
					filter _Filter;
					matrix_2d _Matrix;
					rgba_color _Color;

				public:
					solid_color_pattern_factory();
					solid_color_pattern_factory(const solid_color_pattern_factory&);
					solid_color_pattern_factory& operator=(const solid_color_pattern_factory&);
					solid_color_pattern_factory(solid_color_pattern_factory&& other);
					solid_color_pattern_factory& operator=(solid_color_pattern_factory&& other);
					solid_color_pattern_factory(const rgba_color& color);

					// Modifiers
					void set_extend(extend e);
					void set_filter(filter f);
					void set_matrix(const matrix_2d& m);
					void set_rgba(const rgba_color& color);
					void set_red(double red);
					void set_green(double green);
					void set_blue(double blue);
					void set_alpha(double alpha);

					// Observers
					pattern get_pattern() const;
					extend get_extend() const;
					filter get_filter() const;
					matrix_2d get_matrix() const;
					rgba_color get_rgba() const;
					double get_red() const;
					double get_green() const;
					double get_blue() const;
					double get_alpha() const;
				};

				class linear_pattern_factory {
					mutable ::std::recursive_mutex _Lock;
					pattern_type _Pattern_type;
					extend _Extend;
					filter _Filter;
					matrix_2d _Matrix;

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
					void set_extend(extend extend);
					void set_filter(filter filter);
					void set_matrix(const matrix_2d& matrix);
					void add_color_stop_rgba(double offset, const rgba_color& color);
					void set_color_stop_rgba(unsigned int index, double offset, const rgba_color& color);
					void set_linear_points(const point& pt0, const point& pt1);

					// Observers
					pattern get_pattern() const;
					extend get_extend() const;
					filter get_filter() const;
					matrix_2d get_matrix() const;
					int get_color_stop_count() const;
					void get_color_stop_rgba(unsigned int index, double& offset, rgba_color& color) const;
					void get_linear_points(point& pt0, point& pt1) const;
				};

				class radial_pattern_factory {
					mutable ::std::recursive_mutex _Lock;
					pattern_type _Pattern_type;
					extend _Extend;
					filter _Filter;
					matrix_2d _Matrix;

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
					void set_extend(extend extend);
					void set_filter(filter filter);
					void set_matrix(const matrix_2d& matrix);
					void add_color_stop_rgba(double offset, const rgba_color& color);
					void set_color_stop_rgba(unsigned int index, double offset, const rgba_color& color);
					void set_radial_circles(const point& center0, double radius0, const point& center1, double radius1);

					// Observers
					pattern get_pattern() const;
					extend get_extend() const;
					filter get_filter() const;
					matrix_2d get_matrix() const;
					int get_color_stop_count() const;
					void get_color_stop_rgba(unsigned int index, double& offset, rgba_color& color) const;
					void get_radial_circles(point& center0, double& radius0, point& center1, double& radius1) const;
				};

				class mesh_pattern_factory {
					mutable ::std::recursive_mutex _Lock;
					pattern_type _Pattern_type;
					extend _Extend;
					filter _Filter;
					matrix_2d _Matrix;

					bool _Has_current_patch;
					unsigned int _Current_patch_index;
					int _Current_patch_side_count;
					point _Current_patch_initial_point;
					typedef ::std::map<unsigned int, point> _Control_points;
					typedef ::std::map<unsigned int, rgba_color> _Corner_colors;
					// <Patch data, control points, corner colors>
					typedef ::std::tuple<path_factory, _Control_points, _Corner_colors> _Patch;
					::std::vector<_Patch> _Patches;
				public:
					mesh_pattern_factory();
					mesh_pattern_factory(const mesh_pattern_factory&);
					mesh_pattern_factory& operator=(const mesh_pattern_factory&);
					mesh_pattern_factory(mesh_pattern_factory&& other);
					mesh_pattern_factory& operator=(mesh_pattern_factory&& other);

					// Modifiers
					void set_extend(extend extend);
					void set_filter(filter filter);
					void set_matrix(const matrix_2d& matrix);
					void begin_patch();
					void begin_edit_patch(unsigned int patch_num);
					void end_patch();
					void move_to(const point& pt);
					void line_to(const point& pt);
					void curve_to(const point& pt0, const point& pt1, const point& pt2);
					void set_control_point(unsigned int point_num, const point& pt);
					void set_corner_color_rgba(unsigned int corner_num, const rgba_color& color);

					// Observers
					pattern get_pattern() const;
					extend get_extend() const;
					filter get_filter() const;
					matrix_2d get_matrix() const;
					unsigned int get_patch_count() const;
					path get_path(unsigned int patch_num) const;
					path_factory get_path_factory(unsigned int patch_num) const;
					point get_control_point(unsigned int patch_num, unsigned int point_num) const;
					rgba_color get_corner_color_rgba(unsigned int patch_num, unsigned int corner_num) const;
				};

				struct _Surface_native_handles {
					::cairo_surface_t* csfce;
					::cairo_t* cctxt;
				};

				class surface {
					::std::mutex _Lock_for_device;
					::std::weak_ptr<device> _Device;
				protected:
					::std::unique_ptr<cairo_surface_t, ::std::function<void(cairo_surface_t*)>> _Surface;
					::std::unique_ptr<cairo_t, ::std::function<void(cairo_t*)>> _Context;
					double _Miter_limit = 10.0;
					const double _Line_join_miter_miter_limit = 10000.0;
					line_join _Line_join = line_join::miter;

					surface(format fmt, int width, int height);
				public:
					typedef _Surface_native_handles native_handle_type;
					native_handle_type native_handle() const;

					// tuple<dashes, offset>
					typedef ::std::tuple<::std::vector<double>, double> dashes;

					surface() = delete;
					surface(const surface&) = delete;
					surface& operator=(const surface&) = delete;
					surface(surface&& other);
					surface& operator=(surface&& other);

					explicit surface(native_handle_type nh);

					// create_similar
					surface(const surface& other, content content, int width, int height);
					virtual ~surface();

					// \ref{\iotwod.surface.modifiers.state}, state modifiers:
					virtual void finish();
					void flush();
					::std::shared_ptr<device> get_device();
					void mark_dirty();
					void mark_dirty(const rectangle& rect);
					void set_device_offset(const point& offset);
					void write_to_file(const ::std::string& filename);
					image_surface map_to_image();
					image_surface map_to_image(const rectangle& extents);
					void unmap_image(image_surface& image);
					void save();
					void restore();
					void set_pattern();
					void set_pattern(const pattern& source);
					void set_antialias(antialias a);
					void set_dashes();
					void set_dashes(const dashes& d);
					void set_fill_rule(fill_rule fr);
					void set_line_cap(line_cap lc);
					void set_line_join(line_join lj);
					void set_line_width(double width);
					void set_miter_limit(double limit);
					void set_compositing_operator(compositing_operator co);
					void set_tolerance(double tolerance);
					void clip();
					void reset_clip();
					void set_path();
					void set_path(const path& p);

					// \ref{\iotwod.surface.modifiers.render}, render modifiers:
					void fill();
					void fill(const surface& s);
					void mask(const pattern& pttn);
					void mask(const surface& surface);
					void mask(const surface& surface, const point& origin);
					void paint();
					void paint(const surface& s);
					void paint(double alpha);
					void paint(const surface& s, double alpha);
					void stroke();
					void stroke(const surface& s);
					void show_text(const ::std::string& utf8);
					void show_glyphs(const ::std::vector<glyph>& glyphs);
					void show_text_glyphs(const ::std::string& utf8,
						const ::std::vector<glyph>& glyphs,
						const ::std::vector<text_cluster>& clusters,
						bool clusterToGlyphsMapReverse = false);

					// \ref{\iotwod.surface.modifiers.transform}, transformation modifiers:
					void set_matrix(const matrix_2d& matrix);

					// \ref{\iotwod.surface.modifiers.font}, font modifiers:
					void select_font_face(const ::std::string& family, font_slant slant,
						font_weight weight);
					void set_font_size(double size);
					void set_font_matrix(const matrix_2d& matrix);
					void set_font_options(const font_options& options);
					void set_font_face(const font_face& font_face);
					void set_scaled_font(const scaled_font& scaled_font);

					// \ref{\iotwod.surface.observers.state}, state observers:
					content get_content() const;
					point get_device_offset() const;
					bool has_surface_resource() const;
					pattern get_pattern() const;
					antialias get_antialias() const;
					int get_dashes_count() const;
					dashes get_dashes() const;
					fill_rule get_fill_rule() const;
					line_cap get_line_cap() const;
					line_join get_line_join() const;
					double get_line_width() const;
					double get_miter_limit() const;
					compositing_operator get_compositing_operator() const;
					double get_tolerance() const;
					rectangle get_clip_extents() const;
					bool in_clip(const point& pt) const;
					::std::vector<rectangle> get_clip_rectangles() const;

					// \ref{\iotwod.surface.observers.render}, render observers:
					rectangle get_fill_extents() const;
					bool in_fill(const point& pt) const;
					rectangle get_stroke_extents() const;
					bool in_stroke(const point& pt) const;
					font_extents get_font_extents() const;
					text_extents get_text_extents(const ::std::string& utf8) const;
					text_extents get_glyph_extents(const ::std::vector<glyph>& glyphs) const;

					// \ref{\iotwod.surface.observers.transform}, transformation observers:
					matrix_2d get_matrix() const;
					point user_to_device() const;
					point user_to_device_distance() const;
					point device_to_user() const;
					point device_to_user_distance() const;

					// \ref{\iotwod.surface.observers.font}, font observers:
					matrix_2d get_font_matrix() const;
					font_options get_font_options() const;
					font_face get_font_face() const;
					scaled_font get_scaled_font() const;
				};

				class image_surface : public surface {
					friend surface;
				protected:
					::std::shared_ptr<::std::vector<unsigned char>> _Data;

					image_surface(surface::native_handle_type nh, surface::native_handle_type map_of);
				public:
					image_surface() = delete;
					image_surface(const image_surface&) = delete;
					image_surface& operator=(const image_surface&) = delete;
					image_surface(image_surface&& other);
					image_surface& operator=(image_surface&& other);
					image_surface(format format, int width, int height);
					image_surface(vector<unsigned char>& data, format format, int width, int height, int stride);
					// create_similar_image
					image_surface(const surface& other, format format, int width, int height);
					// create_from_png
					image_surface(const ::std::string& filename);

					// Modifiers
					void set_data(::std::vector<unsigned char>& data);

					// Observers
					::std::vector<unsigned char> get_data() const;
					format get_format() const;
					int get_width() const;
					int get_height() const;
					int get_stride() const;
				};

				int format_stride_for_width(format format, int width);
				surface make_surface(surface::native_handle_type nh); // parameters are exposition only.
				image_surface make_image_surface(format format, int width, int height); // parameters are exposition only.
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
