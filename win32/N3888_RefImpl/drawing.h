#pragma once

#ifndef _DRAWING_
#define _DRAWING_

#include "xdrawing.h"

#include <memory>
#include <functional>
#include <exception>
#include <vector>
#include <string>

#if defined(_MSC_VER) && (_MSC_VER <= 1800)
#define noexcept
#endif

namespace std {
	namespace experimental {
		namespace drawing {

			enum class status {
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
				last_status
			};

			enum class region_overlap {
				in,
				out,
				part
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
				bevel
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
				xor_compositing_operator,
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
				rgb24,
				a8,
				a1,
				rgb16_565,
				rgb30
			};

			enum class path_data_type {
				move_to,
				line_to,
				curve_to,
				close_path
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
				bilinear,
				gaussian
			};

			enum class pattern_type {
				solid,
				surface,
				linear,
				radial,
				mesh,
				raster_source
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
				default_subpixel_order ,
				rgb,
				bgr,
				vrgb,
				vbgr
			};

			enum class hint_style {
				default_hint_style,
				none,
				slight,
				medium,
				full
			};

			enum class hint_metrics {
				default_hint_metrics,
				off,
				on
			};

			namespace text_cluster_flags {
				enum text_cluster_flags : int {
					backward = 0x1
				};
			};

			struct rectangle_int {
				int x;
				int y;
				int width;
				int height;
			};

			struct rectangle {
				double x;
				double y;
				double width;
				double height;
			};

			struct rectangle_list {
				status status;
				::std::vector<rectangle> rectangles;
			};

			union path_data
			{
				struct {
					path_data_type type;
					int length;
				} header;
				struct {
					double x;
					double y;
				} point;
			};

			struct path {
				::std::vector<path_data> data;
				typedef cairo_path_t* native_handle_type;
			};

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

			struct matrix {
				double xx;
				double yx;
				double xy;
				double yy;
				double x0;
				double y0;

				void init(double xx, double yx, double xy, double yy, double x0, double y0);
				void init_identity();
				void init_translate(double tx, double ty);
				void init_scale(double sx, double sy);
				void init_rotate(double radians);

				void translate(double tx, double ty);
				void scale(double sx, double sy);
				void rotate(double radians);
				void invert();
				static matrix multiply(const matrix& a, const matrix& b);
				void transform_distance(double& dx, double& dy);
				void transform_point(double& x, double& y);
			};

			class drawing_exception : public exception {
				status _Status = status::last_status;
			public:
				drawing_exception() noexcept;
				explicit drawing_exception(status s) noexcept;

				virtual ~drawing_exception();

				drawing_exception(const drawing_exception& rhs) noexcept = default;
				drawing_exception& operator=(const drawing_exception& rhs) noexcept = default;

				virtual const char* what() const noexcept;
				status status() const noexcept;
			};

			class region {
				::std::shared_ptr<cairo_region_t> _Region;
			public:
				typedef cairo_region_t* native_handle_type;
				native_handle_type native_handle() const;

				region();
				region(const region& other);
				region& operator=(const region& other);
				region(region&& other);
				region& operator=(region&& other);
				explicit region(native_handle_type nh);
				explicit region(const rectangle_int& rectangle);
				explicit region(const ::std::vector<rectangle_int>& rectangles);
				region copy();

				status status();

				void get_extents(rectangle_int& extents);
				int num_rectangles();
				void get_rectangle(int nth, rectangle_int& rectangle);
				bool is_empty();
				bool contains_point(int x, int y);
				region_overlap contains_rectangle(const rectangle_int& rectangle);

				bool equal(const region& other);
				void translate(int dx, int dy);
				void intersect_region(const region& other);
				void intersect_rectangle(const rectangle_int& rectangle);
				void subtract_region(const region& other);
				void subtract_rectangle(const rectangle_int& rectangle);
				void union_region(const region& other);
				void union_rectangle(const rectangle_int& rectangle);
				void xor_region(const region& other);
				void xor_rectangle(const rectangle_int& rectangle);
			};

			class user_data_key {
				static ::std::atomic<::std::int_fast64_t> _Cnt;
				::std::int_fast64_t _Val;
			public:
				user_data_key();
				user_data_key(const user_data_key&) = default;
				user_data_key& operator=(const user_data_key&) = default;
				user_data_key(user_data_key&& other);
				user_data_key& operator=(user_data_key&& other);
				::std::int_fast64_t _Get_value() const;

				bool operator<(const user_data_key& other) const { return _Val < other._Val; }
				bool operator>(const user_data_key& other) const { return _Val > other._Val; }
				bool operator==(const user_data_key& other) const { return _Val == other._Val; }
				bool operator!=(const user_data_key& other) const { return _Val != other._Val; }
			};

			class device {
				device() = delete;
			protected:
				::std::shared_ptr<cairo_device_t> _Device;
				::std::shared_ptr<::std::map<user_data_key, ::std::shared_ptr<void>>> _User_data_map;
			public:
				typedef cairo_device_t* native_handle_type;
				native_handle_type native_handle() const;

				device(const device&) = default;
				device& operator=(const device&) = default;
				device(device&& other);
				device& operator=(device&& other);
				explicit device(native_handle_type nh);
				status status();
				void finish();
				void flush();
				void set_user_data(const user_data_key& key, ::std::shared_ptr<void>& value);
				::std::shared_ptr<void>& get_user_data(const user_data_key& key);
				void acquire();
				void release();
			};

			class font_options {
				::std::shared_ptr<cairo_font_options_t> _Font_options;

				font_options() = delete;
			public:
				typedef cairo_font_options_t* native_handle_type;
				native_handle_type native_handle() const;

				font_options(const font_options&) = default;
				font_options& operator=(const font_options&) = default;
				font_options(font_options&& other);
				font_options& operator=(font_options&& other);

				explicit font_options(native_handle_type nh);

				font_options& operator=(native_handle_type nh);

				status status();

				void merge(const font_options& other);
				unsigned long hash();
				bool equal(const font_options& other);
				void set_antialias(antialias antialias);
				antialias get_antialias();
				void set_subpixel_order(subpixel_order subpixel_order);
				subpixel_order get_subpixel_order();
				void set_hint_style(hint_style hint_style);
				hint_style get_hint_style();
				void set_hint_metrics(hint_metrics hint_metrics);
				hint_metrics get_hint_metrics();
			};

			class font_face {
			protected:
				::std::shared_ptr<cairo_font_face_t> _Font_face;
			private:
				font_face() = delete;
			public:
				typedef cairo_font_face_t* native_handle_type;
				native_handle_type native_handle() const;

				font_face(const font_face&) = default;
				font_face& operator=(const font_face&) = default;
				font_face(font_face&& other);
				font_face& operator=(font_face&& other);

				explicit font_face(native_handle_type nh);

				virtual ~font_face();
			};

			class scaled_font {
				::std::shared_ptr<cairo_scaled_font_t> _Scaled_font;

				scaled_font() = delete;
			public:
				typedef cairo_scaled_font_t* native_handle_type;
				native_handle_type native_handle() const;

				scaled_font(const scaled_font&) = default;
				scaled_font& operator=(const scaled_font&) = default;
				scaled_font(scaled_font&& other);
				scaled_font& operator=(scaled_font&& other);

				explicit scaled_font(native_handle_type nh);
			};

			class toy_font_face : public font_face {
				toy_font_face() = delete;
			public:
				toy_font_face(const toy_font_face&) = default;
				toy_font_face& operator=(const toy_font_face&) = default;
				toy_font_face(const ::std::string& family, font_slant slant, font_weight weight);
				toy_font_face(toy_font_face&& other);
				toy_font_face& operator=(toy_font_face&& other);

				::std::string get_family();
				font_slant get_slant();
				font_weight get_weight();
			};

			// Forward declaration.
			class image_surface;

			class surface {
				surface() = delete;

			protected:
				::std::shared_ptr<cairo_surface_t> _Surface;
				::std::shared_ptr<::std::map<user_data_key, ::std::shared_ptr<void>>> _User_data_map;

				::std::shared_ptr<::std::function<void(void* closure, const ::std::vector<unsigned char>& data)>> _Write_to_png_fn;
				void* _Write_to_png_closure;
				::std::shared_ptr<::std::map<::std::string, ::std::function<void(void* data)>>> _Mime_data_destroy_fn_map;
				::std::shared_ptr<::std::map<::std::string, void*>> _Mime_data_destroy_closure_map;
			public:
				typedef cairo_surface_t* native_handle_type;
				native_handle_type native_handle() const;

				surface(const surface&) = default;
				surface& operator=(const surface&) = default;

				explicit surface(native_handle_type nh);
				surface& operator=(native_handle_type nh);
				surface(surface&& other);
				surface& operator=(surface&& other);

				// create_similar
				surface(surface& other, content content, int width, int height);
				// create_for_rectangle
				surface(surface& target, double x, double y, double width, double height);
				virtual ~surface();

				status status();
				void finish();
				void flush();

				device get_device();
				void get_font_options(font_options& options);

				content get_content();
				void mark_dirty();
				void mark_dirty_rectangle(int x, int y, int width, int height);

				void set_device_offset(double x_offset, double y_offset);
				void get_device_offset(double& x_offset, double& y_offset);
				void set_fallback_resolution(double x_pixels_per_inch, double y_pixels_per_inch);
				void get_fallback_resolution(double& x_pixels_per_inch, double& y_pixels_per_inch);
				void write_to_png(const ::std::string& filename);
				void write_to_png_stream(::std::function<void(void* closure, const ::std::vector<unsigned char>& data)> write_fn, void* closure);
				void set_user_data(const user_data_key& key, ::std::shared_ptr<void>& value);
				::std::shared_ptr<void>& get_user_data(const user_data_key& key);
				void copy_page();
				void show_page();
				bool has_show_text_glyphs();
				void set_mime_data(const ::std::string& mime_type, const ::std::vector<unsigned char>& data, ::std::function<void(void* data)> destroy, void* closure);
				void get_mime_data(const ::std::string& mime_type, ::std::vector<unsigned char>& data);
				bool supports_mime_type(const ::std::string& mime_type);
				image_surface map_to_image(const rectangle_int& extents);
				void unmap_image(image_surface& image);
			protected:
				static cairo_status_t _Cairo_write_to_png_stream(void* this_ptr, const unsigned char* data, unsigned int length);
			};

			class image_surface : public surface {
				friend surface;
				image_surface() = delete;
			protected:
				::std::shared_ptr<::std::function<void(void* closure, ::std::vector<unsigned char>& data)>> _Create_from_png_fn;
				void* _Create_from_png_closure;
				::std::shared_ptr<::std::vector<unsigned char>> _Data;
			public:
				image_surface(const image_surface&) = default;
				image_surface& operator=(const image_surface&) = default;
				image_surface(image_surface&& other);
				image_surface& operator=(image_surface&& other);
				image_surface(surface::native_handle_type nh, surface::native_handle_type map_of);
				image_surface(format format, int width, int height);
				image_surface(vector<unsigned char>& data, format format, int width, int height, int stride);
				// create_similar_image
				image_surface(surface& other, format format, int width, int height);
				// create_from_png
				image_surface(const ::std::string& filename);
				// create_from_png_stream
				image_surface(::std::function<void(void* closure, ::std::vector<unsigned char>& data)> read_fn, void* closure);

				void set_data(::std::vector<unsigned char>& data);
				::std::vector<unsigned char> get_data();
				format get_format();
				int get_width();
				int get_height();
				int get_stride();
			protected:
				static cairo_status_t _Cairo_create_from_png_stream(void* this_ptr, unsigned char* data, unsigned int length);
			};

			class pattern {
				pattern() = delete;
			protected:
				::std::shared_ptr<cairo_pattern_t> _Pattern;
				::std::shared_ptr<::std::map<user_data_key, ::std::shared_ptr<void>>> _User_data_map;
			public:
				typedef cairo_pattern_t* native_handle_type;
				native_handle_type native_handle() const;

				explicit pattern(native_handle_type nh);

				pattern(const pattern&) = default;
				pattern& operator=(const pattern&) = default;
				pattern(pattern&& other);
				pattern& operator=(pattern&& other);

				virtual ~pattern();

				status status();
				void set_extend(extend extend);
				extend get_extend();
				void set_filter(filter filter);
				filter get_filter();
				void set_matrix(const matrix& matrix);
				void get_matrix(matrix& matrix);

				pattern_type get_type();

				void set_user_data(const user_data_key& key, ::std::shared_ptr<void>& value);
				::std::shared_ptr<void>& get_user_data(const user_data_key& key);
			};

			class solid_color_pattern : public pattern {
			public:
				solid_color_pattern(const solid_color_pattern&) = default;
				solid_color_pattern& operator=(const solid_color_pattern&) = default;
				solid_color_pattern(solid_color_pattern&& other);
				solid_color_pattern& operator=(solid_color_pattern&& other);
				solid_color_pattern(double red, double green, double blue);
				solid_color_pattern(double red, double green, double blue, double alpha);

				void get_rgba(double& red, double& green, double& blue, double& alpha);
			};

			class gradient_pattern : public pattern {
				gradient_pattern() = delete;
			protected:
				gradient_pattern(native_handle_type nh);
			public:
				gradient_pattern(const gradient_pattern&) = default;
				gradient_pattern& operator=(const gradient_pattern&) = default;
				gradient_pattern(gradient_pattern&& other);
				gradient_pattern& operator=(gradient_pattern&& other);
				virtual ~gradient_pattern();

				void add_color_stop_rgb(double offset, double red, double green, double blue);
				void add_color_stop_rgba(double offset, double red, double green, double blue, double alpha);
				void get_color_stop_count(int& count);
				void get_color_stop_rgba(int index, double& offset, double& red, double& green, double& blue, double& alpha);
			};

			class linear_pattern : public gradient_pattern {
				linear_pattern() = delete;
			public:
				linear_pattern(const linear_pattern&) = default;
				linear_pattern& operator=(const linear_pattern&) = default;
				linear_pattern(linear_pattern&& other);
				linear_pattern& operator=(linear_pattern&& other);
				linear_pattern(double x0, double y0, double x1, double y1);
				void get_linear_points(double& x0, double& y0, double& x1, double& y1);
			};

			class radial_pattern : public gradient_pattern {
			public:
				radial_pattern(const radial_pattern&) = default;
				radial_pattern& operator=(const radial_pattern&) = default;
				radial_pattern(radial_pattern&& other);
				radial_pattern& operator=(radial_pattern&& other);
				radial_pattern(double cx0, double cy0, double radius0, double cx1, double cy1, double radius1);
				void get_radial_circles(double& x0, double& y0, double& radius0, double& x1, double& y1, double& radius1);
			};

			class surface_pattern : public pattern {
				surface_pattern() = delete;
			public:
				surface_pattern(const surface_pattern&) = default;
				surface_pattern& operator=(const surface_pattern&) = default;
				surface_pattern(surface_pattern&& other);
				surface_pattern& operator=(surface_pattern&& other);
				explicit surface_pattern(surface& surface);
				void get_surface(surface& s);
			};

			class mesh_pattern : public pattern {
			public:
				mesh_pattern();
				mesh_pattern(const mesh_pattern&) = default;
				mesh_pattern& operator=(const mesh_pattern&) = default;
				mesh_pattern(mesh_pattern&& other);
				mesh_pattern& operator=(mesh_pattern&& other);
				void begin_patch();
				void end_patch();
				void move_to(double x, double y);
				void line_to(double x, double y);
				void curve_to(double x1, double y1, double x2, double y2, double x3, double y3);
				void set_control_point(unsigned int point_num, double x, double y);
				void set_corner_color_rgb(unsigned int corner_num, double red, double green, double blue);
				void set_corner_color_rgba(unsigned int corner_num, double red, double green, double blue, double alpha);
				void get_patch_count(unsigned int& count);
				path get_path(unsigned int patch_num);
				void get_control_point(unsigned int patch_num, unsigned int point_num, double& x, double& y);
				void get_corner_color_rgba(unsigned int patch_num, unsigned int corner_num, double& red, double& green, double& blue, double& alpha);
			};

			class raster_source_pattern : public pattern {
				void* _User_callback_data;
				int _Width;
				int _Height;
				::std::shared_ptr<::std::function<surface(void* callback_data, surface& target, const rectangle_int& extents)>> _Acquire_fn;
				::std::shared_ptr<::std::function<void(void* callback_data, surface& surface)>> _Release_fn;
				::std::shared_ptr<::std::function<experimental::drawing::status(void* callback_data)>> _Snapshot_fn;
				::std::shared_ptr<::std::function<experimental::drawing::status(void* callback_data, const pattern& other)>> _Copy_fn;
				::std::shared_ptr<::std::function<void(void* callback_data)>> _Finish_fn;
				
				static cairo_surface_t* _Cairo_acquire(cairo_pattern_t* pattern, void* this_ptr, cairo_surface_t* target, const cairo_rectangle_int_t* extents);
				static void _Cairo_release(cairo_pattern_t* pattern, void* this_ptr, cairo_surface_t* surface);
				static cairo_status_t _Cairo_snapshot(cairo_pattern_t* pattern, void* this_ptr);
				static cairo_status_t _Cairo_copy(cairo_pattern_t* pattern, void* this_ptr, const cairo_pattern_t* other);
				static void _Cairo_finish(cairo_pattern_t* pattern, void* this_ptr);

				raster_source_pattern() = delete;
			public:
				raster_source_pattern(const raster_source_pattern&) = default;
				raster_source_pattern& operator=(const raster_source_pattern&) = default;
				raster_source_pattern(raster_source_pattern&& other);
				raster_source_pattern& operator=(raster_source_pattern&& other);
				raster_source_pattern(void* user_data, content content, int width, int height);
				void set_callback_data(void* data);
				void* get_callback_data();
				void set_acquire(
					::std::function<surface(void* callback_data, surface& target, const rectangle_int& extents)> acquire_fn,
					::std::function<void(void* callback_data, surface& surface)> release_fn
					);
				void get_acquire(
					::std::function<surface(void* callback_data, surface& target, const rectangle_int& extents)>& acquire_fn,
					::std::function<void(void* callback_data, surface& surface)>& release_fn
					);
				void set_snapshot(
					::std::function<experimental::drawing::status(void* callback_data)> snapshot_fn
					);
				void get_snapshot(
					::std::function<experimental::drawing::status(void* callback_data)>& snapshot_fn
					);
				void set_copy(
					::std::function<experimental::drawing::status(void* callback_data, const pattern& other)> copy_fn
					);
				void get_copy(
					::std::function<experimental::drawing::status(void* callback_data, const pattern& other)>& copy_fn
					);
				void set_finish(::std::function<void(void* callback_data)> finish_fn);
				void get_finish(::std::function<void(void* callback_data)>& finish_fn);
			};

			class context {
				::std::shared_ptr<surface> _Surface;
				::std::shared_ptr<cairo_t> _Context;
				::std::shared_ptr<::std::map<user_data_key, ::std::shared_ptr<void>>> _User_data_map;

				context() = delete;
			public:
				typedef cairo_t* native_handle_type;
				native_handle_type native_handle() const;

				context(const context&) = default;
				context& operator=(const context&) = default;
				context(context&& other);
				context& operator=(context&& other);
				explicit context(surface& s);

				status status();
				void save();
				void restore();
				surface get_target();
				void push_group();
				void push_group_with_content(content c);
				pattern pop_group();
				void pop_group_to_source();
				surface get_group_target();

				void set_source_rgb(double red, double green, double blue);
				void set_source_rgba(double red, double green, double blue, double alpha);
				void set_source(const pattern& source);
				void set_source_surface(const surface& s, double x, double y);
				pattern get_source();

				void set_antialias(antialias a);
				antialias get_antialias();

				void set_dash(const ::std::vector<double>& dashes, double offset);
				int get_dash_count();
				void get_dash(::std::vector<double>& dashes, double& offset);

				void set_fill_rule(fill_rule fr);
				fill_rule get_fill_rule();

				void set_line_cap(line_cap lc);
				line_cap get_line_cap();

				void set_line_join(line_join lj);
				line_join get_line_join();

				void set_line_width(double width);
				double get_line_width();

				void set_miter_limit(double limit);
				double get_miter_limit();

				void set_compositing_operator(compositing_operator co);
				compositing_operator get_compositing_operator();

				void set_tolerance(double tolerance);
				double get_tolerance();

				void clip();
				void clip_preserve();
				void clip_extents(double& x1, double& y1, double& x2, double& y2);
				bool in_clip(double x, double y);
				void reset_clip();

				rectangle_list copy_clip_rectangle_list();

				void fill();
				void fill_preserve();
				void fill_extents(double& x1, double& y1, double& x2, double& y2);
				bool in_fill(double x, double y);

				void mask(pattern& pattern);
				void mask_surface(surface& surface, double surface_x, double surface_y);

				void paint();
				void paint_with_alpha(double alpha);

				void stroke();
				void stroke_preserve();
				void stroke_extents(double& x1, double& y1, double& x2, double& y2);
				bool in_stroke(double x, double y);

				void copy_page();
				void show_page();

				void set_user_data(const user_data_key& key, ::std::shared_ptr<void>& value);
				::std::shared_ptr<void>& get_user_data(const user_data_key& key);

				// Paths
				path copy_path();
				path copy_path_flat();
				void append_path(const path& p);
				bool has_current_point();
				void get_current_point(double& x, double& y);
				void new_path();
				void new_sub_path();
				void close_path();
				void arc(double xc, double yc, double radius, double angle1, double angle2);
				void arc_negative(double xc, double yc, double radius, double angle1, double angle2);
				void curve_to(double x1, double y1, double x2, double y2, double x3, double y3);
				void line_to(double x, double y);
				void move_to(double x, double y);
				void rectangle(double x, double y, double width, double height);
				void glyph_path(const ::std::vector<glyph>& glyphs);
				void text_path(const ::std::string& utf8);
				void rel_curve_to(double dx1, double dy1, double dx2, double dy2, double dx3, double dy3);
				void rel_line_to(double dx, double dy);
				void rel_move_to(double dx, double dy);
				void path_extents(double& x1, double& y1, double& x2, double& y2);

				// Transformations
				void translate(double tx, double ty);
				void scale(double sx, double sy);
				void rotate(double angle);
				void transform(const matrix& matrix);
				void set_matrix(const matrix& matrix);
				void get_matrix(matrix& matrix);
				void identity_matrix();
				void user_to_device(double& x, double& y);
				void user_to_device_distance(double& dx, double& dy);
				void device_to_user(double& x, double& y);
				void device_to_user_distance(double& dx, double& dy);

				// Text
				void select_font_face(const ::std::string& family, font_slant slant, font_weight weight);
				void set_font_size(double size);
				void set_font_matrix(const matrix& matrix);
				void get_font_matrix(matrix& matrix);
				void set_font_options(const font_options& options);
				void get_font_options(font_options& options);
				void set_font_face(font_face& font_face);
				font_face get_font_face();
				void set_scaled_font(const scaled_font& scaled_font);
				scaled_font get_scaled_font();
				void show_text(const ::std::string& utf8);
				void show_glyphs(const ::std::vector<glyph>& glyphs);
				void show_text_glyphs(const ::std::string& utf8, const ::std::vector<glyph>& glyphs, const ::std::vector<text_cluster>& clusters, text_cluster_flags::text_cluster_flags cluster_flags);
				void font_extents(font_extents& extents);
				void text_extents(const ::std::string& utf8, text_extents& extents);
				void glyph_extents(const ::std::vector<glyph>& glyphs, ::std::experimental::drawing::text_extents& extents);
			};

			int format_stride_for_width(format format, int width);
			surface make_surface(surface::native_handle_type nh);
			surface make_surface(format format, int width, int height);
			path _Make_path(path::native_handle_type nh);
		}
	}
}

#endif
