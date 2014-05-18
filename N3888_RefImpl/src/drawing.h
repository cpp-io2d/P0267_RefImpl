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
                arc,
                arc_negative,
                new_sub_path,
                close_path
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
				solid_color,
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
                    none = 0x0,
					backward = 0x1
				};
			};

			struct rectangle {
				double x;
				double y;
				double width;
				double height;
			};

            struct point {
                double x;
                double y;

                point operator+=(const point& rhs);
                point operator-=(const point& rhs);
                point operator*=(const point& rhs);
                point operator*=(double rhs);
                point operator/=(const point& rhs);
                point operator/=(double rhs);
            };

            point operator+(const point& lhs);
            point operator+(const point& lhs, const point& rhs);
            point operator-(const point& lhs);
            point operator-(const point& lhs, const point& rhs);
            point operator*(const point& lhs, const point& rhs);
            point operator*(const point& lhs, double rhs);
            point operator/(const point& lhs, const point& rhs);
            point operator/(const point& lhs, double rhs);

            struct rectangle_list {
				::std::experimental::drawing::status status;
				::std::vector<rectangle> rectangles;
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

            union path_data
			{
				struct {
					path_data_type type;
					int length;
				} header;
                point point;
                double value;
			};

            // Forward declaration.
            class path_builder;

			class path {
				::std::vector<path_data> _Data;
                bool _Has_current_point;
                point _Current_point;
                point _Extents_pt0;
                point _Extents_pt1;
            public:
                typedef cairo_path_t* native_handle_type;

                path(const path_builder& pb);
                path(const path& other) = default;
                path& operator=(const path& other) = default;
                path(path&& other);
                path& operator=(path&& other);

                ::std::vector<path_data> get_data() const;
                const ::std::vector<path_data>& get_data_ref() const;
                void get_path_extents(point& pt0, point& pt1) const;
			};

            class path_builder {
                friend class path;
                ::std::vector<path_data> _Data;
                bool _Has_current_point;
                point _Current_point;
                point _Extents_pt0;
                point _Extents_pt1;

            public:
                path_builder() = default;
                path_builder(const path_builder& other) = default;
                path_builder& operator=(const path_builder& other) = default;
                path_builder(path_builder&& other);
                path_builder& operator=(path_builder&& other);

                path get_path() const;
                path get_path_flat() const;

                void append_path(const path& p);
                void append_path(const path_builder& p);
                bool has_current_point();
                point get_current_point();
                void new_sub_path();
                void close_path();
                void arc(const point& center, double radius, double angle1, double angle2);
                void arc_negative(const point& center, double radius, double angle1, double angle2);
                void curve_to(const point& pt0, const point& pt1, const point& pt2);
                void line_to(const point& pt);
                void move_to(const point& pt);
                void rectangle(const rectangle& rect);
                void rel_curve_to(const point& dpt0, const point& dpt1, const point& dpt2);
                void rel_line_to(const point& dpt);
                void rel_move_to(const point& dpt);

                ::std::vector<path_data> get_data() const;
                const ::std::vector<path_data>& get_data_ref() const;
                ::std::vector<path_data>& get_data_ref();
                void get_path_extents(point& pt0, point& pt1) const;
            };

            struct matrix {
				double xx;
				double yx;
				double xy;
				double yy;
				double x0;
				double y0;

				static matrix init_identity();
                static matrix init_translate(const point& value);
                static matrix init_scale(const point& value);
                static matrix init_rotate(double radians);

				void translate(const point& value);
				void scale(const point& value);
				void rotate(double radians);
				void invert();
				void transform_distance(point& dist);
				void transform_point(point& pt);

                matrix operator*=(const matrix& rhs);
			};

            matrix operator*(const matrix& lhs, const matrix& rhs);

            class drawing_exception : public exception {
				::std::experimental::drawing::status _Status = ::std::experimental::drawing::status::last_status;
			public:
				drawing_exception() noexcept;
				explicit drawing_exception(::std::experimental::drawing::status s) noexcept;

				virtual ~drawing_exception() noexcept;

				drawing_exception(const drawing_exception& rhs) noexcept = default;
				drawing_exception& operator=(const drawing_exception& rhs) noexcept = default;

				virtual const char* what() const noexcept;
				::std::experimental::drawing::status status() const noexcept;
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
				explicit region(const rectangle& rectangle);
				explicit region(const ::std::vector<rectangle>& rectangles);
				region copy();

				::std::experimental::drawing::status status();

				void get_extents(rectangle& extents);
				int num_rectangles();
				void get_rectangle(int nth, rectangle& rectangle);
				bool is_empty();
				bool contains_point(const point& pt);
				region_overlap contains_rectangle(const rectangle& rectangle);

				bool equal(const region& other);
				void translate(const point& pt);
				void intersect_region(const region& other);
				void intersect_rectangle(const rectangle& rectangle);
				void subtract_region(const region& other);
				void subtract_rectangle(const rectangle& rectangle);
				void union_region(const region& other);
				void union_rectangle(const rectangle& rectangle);
				void xor_region(const region& other);
				void xor_rectangle(const rectangle& rectangle);
			};

			class device {
				device() = delete;
			protected:
				::std::shared_ptr<cairo_device_t> _Device;
			public:
				typedef cairo_device_t* native_handle_type;
				native_handle_type native_handle() const;

				device(const device&) = delete;
				device& operator=(const device&) = delete;
				device(device&& other);
				device& operator=(device&& other);
				explicit device(native_handle_type nh);
				::std::experimental::drawing::status status();
				void finish();
				void flush();
				void acquire();
				void release();
			};

            // Forward declaration.
            class font_options;

			class font_options_builder {
                antialias _Antialias = antialias::default_antialias;
                subpixel_order _Subpixel_order = subpixel_order::default_subpixel_order;
                hint_style _Hint_style = hint_style::default_hint_style;
                hint_metrics _Hint_metrics = hint_metrics::default_hint_metrics;

			public:
                font_options_builder() = default;
                font_options_builder(const font_options_builder&) = default;
                font_options_builder& operator=(const font_options_builder&) = default;
                font_options_builder(font_options_builder&& other);
                font_options_builder& operator=(font_options_builder&& other);

                font_options get_font_options() const;
                void set_antialias(antialias a);
				antialias get_antialias() const;
				void set_subpixel_order(subpixel_order so);
				subpixel_order get_subpixel_order() const;
				void set_hint_style(hint_style hs);
				hint_style get_hint_style() const;
				void set_hint_metrics(hint_metrics hm);
				hint_metrics get_hint_metrics() const;
			};

            class font_options {
                ::std::shared_ptr<cairo_font_options_t> _Font_options;
            public:
                typedef cairo_font_options_t* native_handle_type;
                native_handle_type native_handle() const;

                font_options(const font_options&) = default;
                font_options& operator=(const font_options&) = default;
                font_options(font_options&& other);
                font_options& operator=(font_options&& other);
                font_options(antialias a, subpixel_order so, hint_style hs, hint_metrics hm);
                explicit font_options(native_handle_type nh);

                antialias get_antialias() const;
                subpixel_order get_subpixel_order() const;
                hint_style get_hint_style() const;
                hint_metrics get_hint_metrics() const;
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
                scaled_font(const font_face& ff, const matrix& fm, const matrix& ctm, const font_options& fo);

                font_extents get_extents() const;
                text_extents get_text_extents(const ::std::string& utf8) const;
                text_extents get_glyph_extents(const ::std::vector<glyph>& glyphs) const;
                ::std::vector<glyph> text_to_glyphs(double x, double y, const ::std::string& utf8) const;
                ::std::vector<glyph> text_to_glyphs(double x, double y, const ::std::string& utf8, ::std::vector<text_cluster>& clusters, text_cluster_flags::text_cluster_flags& clFlags) const;
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

            // Forward declaration.
            class linear_pattern_builder;
            class mesh_pattern_builder;
            class radial_pattern_builder;
            class raster_source_pattern_builder;
            class solid_color_pattern_builder;
            class surface_pattern_builder;
            class surface;

            class pattern {
            public:
                typedef cairo_pattern_t* native_handle_type;

            private:
                friend class linear_pattern_builder;
                friend class mesh_pattern_builder;
                friend class radial_pattern_builder;
                friend class raster_source_pattern_builder;
                friend class solid_color_pattern_builder;
                friend class surface_pattern_builder;
                friend class surface;

                pattern() = delete;
                pattern(native_handle_type nh);

                cairo_pattern_t* _Pattern;
                pattern_type _Pattern_type;

            public:
                native_handle_type native_handle() const;

                pattern(const pattern&) = default;
                pattern& operator=(const pattern&) = default;
                pattern(pattern&& other);
                pattern& operator=(pattern&& other);

                ~pattern();

                pattern_type get_type() const;
            };

			class solid_color_pattern_builder {
                pattern_type _Pattern_type;
                extend _Extend;
                filter _Filter;
                matrix _Matrix;
                double _Red;
                double _Green;
                double _Blue;
                double _Alpha;

            public:
				solid_color_pattern_builder(const solid_color_pattern_builder&) = default;
				solid_color_pattern_builder& operator=(const solid_color_pattern_builder&) = default;
				solid_color_pattern_builder(solid_color_pattern_builder&& other);
				solid_color_pattern_builder& operator=(solid_color_pattern_builder&& other);
				solid_color_pattern_builder(double red, double green, double blue);
				solid_color_pattern_builder(double red, double green, double blue, double alpha);

                pattern get_pattern();
                void set_extend(extend e);
                extend get_extend();
                void set_filter(filter f);
                filter get_filter();
                void set_matrix(const matrix& m);
                matrix get_matrix();
                
                void get_rgba(double& red, double& green, double& blue, double& alpha);
			};

			class linear_pattern_builder {
                pattern_type _Pattern_type;
                extend _Extend;
                filter _Filter;
                matrix _Matrix;

                point _Point0;
                point _Point1;
                ::std::vector<::std::tuple<double, double, double, double, double>> _Color_stops;

                linear_pattern_builder() = delete;
			public:
				linear_pattern_builder(const linear_pattern_builder&) = default;
				linear_pattern_builder& operator=(const linear_pattern_builder&) = default;
				linear_pattern_builder(linear_pattern_builder&& other);
				linear_pattern_builder& operator=(linear_pattern_builder&& other);
				linear_pattern_builder(const point& pt0, const point& pt1);

                pattern get_pattern();
                void set_extend(extend extend);
                extend get_extend();
                void set_filter(filter filter);
                filter get_filter();
                void set_matrix(const matrix& matrix);
                matrix get_matrix();
                
                void add_color_stop_rgb(double offset, double red, double green, double blue);
                void add_color_stop_rgba(double offset, double red, double green, double blue, double alpha);
                void get_color_stop_count(int& count);
                void get_color_stop_rgba(int index, double& offset, double& red, double& green, double& blue, double& alpha);

                void get_linear_points(point& pt0, point& pt1);
			};

			class radial_pattern_builder {
                pattern_type _Pattern_type;
                extend _Extend;
                filter _Filter;
                matrix _Matrix;

                point _Center0;
                double _Radius0;
                point _Center1;
                double _Radius1;
                ::std::vector<::std::tuple<double, double, double, double, double>> _Color_stops;

                radial_pattern_builder() = delete;
            public:
				radial_pattern_builder(const radial_pattern_builder&) = default;
				radial_pattern_builder& operator=(const radial_pattern_builder&) = default;
				radial_pattern_builder(radial_pattern_builder&& other);
				radial_pattern_builder& operator=(radial_pattern_builder&& other);
				radial_pattern_builder(const point& center0, double radius0, const point& center1, double radius1);

                pattern get_pattern();
                void set_extend(extend extend);
                extend get_extend();
                void set_filter(filter filter);
                filter get_filter();
                void set_matrix(const matrix& matrix);
                matrix get_matrix();

                void add_color_stop_rgb(double offset, double red, double green, double blue);
                void add_color_stop_rgba(double offset, double red, double green, double blue, double alpha);
                void get_color_stop_count(int& count);
                void get_color_stop_rgba(int index, double& offset, double& red, double& green, double& blue, double& alpha);

                void get_radial_circles(point& center0, double& radius0, point& center1, double& radius1);
			};

			//class surface_pattern_builder {
   //             pattern_type _Pattern_type;
   //             extend _Extend;
   //             filter _Filter;
   //             matrix _Matrix;

   //             surface _Surface;

   //             surface_pattern_builder() = delete;
			//public:
			//	surface_pattern_builder(const surface_pattern_builder&) = delete;
			//	surface_pattern_builder& operator=(const surface_pattern_builder&) = delete;
			//	surface_pattern_builder(surface_pattern_builder&& other);
			//	surface_pattern_builder& operator=(surface_pattern_builder&& other);
			//	explicit surface_pattern_builder(surface&& s);

   //             pattern get_pattern();
   //             void set_extend(extend extend);
   //             extend get_extend();
   //             void set_filter(filter filter);
   //             filter get_filter();
   //             void set_matrix(const matrix& matrix);
   //             matrix get_matrix();

   //             surface& get_surface();
			//};

			class mesh_pattern_builder {
                pattern_type _Pattern_type;
                extend _Extend;
                filter _Filter;
                matrix _Matrix;

                bool _Has_current_patch;
                int _Current_patch_side_count;
                point _Current_patch_initial_point;
                // <Patch data, control points, corner colors>
                typedef ::std::map<unsigned int, point> _Control_points;
                typedef ::std::map<unsigned int, ::std::tuple<double, double, double, double>> _Corner_colors;
                typedef ::std::tuple<path_builder, _Control_points, _Corner_colors> _Patch;
                ::std::vector<_Patch> _Patches;
            public:
				mesh_pattern_builder();
				mesh_pattern_builder(const mesh_pattern_builder&) = default;
				mesh_pattern_builder& operator=(const mesh_pattern_builder&) = default;
				mesh_pattern_builder(mesh_pattern_builder&& other);
				mesh_pattern_builder& operator=(mesh_pattern_builder&& other);

                pattern get_pattern();
                void set_extend(extend extend);
                extend get_extend();
                void set_filter(filter filter);
                filter get_filter();
                void set_matrix(const matrix& matrix);
                matrix get_matrix();

                void begin_patch();
				void end_patch();
				void move_to(const point& pt);
				void line_to(const point& pt);
				void curve_to(const point& pt0, const point& pt1, const point& pt2);
				void set_control_point(unsigned int point_num, const point& pt);
				void set_corner_color_rgb(unsigned int corner_num, double red, double green, double blue);
				void set_corner_color_rgba(unsigned int corner_num, double red, double green, double blue, double alpha);
				void get_patch_count(unsigned int& count);
				path get_path(unsigned int patch_num);
                path_builder get_path_builder(unsigned int patch_num);
				point get_control_point(unsigned int patch_num, unsigned int point_num);
				void get_corner_color_rgba(unsigned int patch_num, unsigned int corner_num, double& red, double& green, double& blue, double& alpha);
			};

			class raster_source_pattern_builder {
                pattern_type _Pattern_type;
                extend _Extend;
                filter _Filter;
                matrix _Matrix;

                void* _User_callback_data;
				int _Width;
				int _Height;
                content _Content;
				::std::shared_ptr<::std::function<surface(void* callback_data, surface& target, const rectangle& extents)>> _Acquire_fn;
				::std::shared_ptr<::std::function<void(void* callback_data, surface& surface)>> _Release_fn;
				
				static cairo_surface_t* _Cairo_acquire(cairo_pattern_t* pattern_builder, void* this_ptr, cairo_surface_t* target, const cairo_rectangle_int_t* extents);
				static void _Cairo_release(cairo_pattern_t* pattern_builder, void* this_ptr, cairo_surface_t* surface);

				raster_source_pattern_builder() = delete;
			public:
				raster_source_pattern_builder(const raster_source_pattern_builder&) = default;
				raster_source_pattern_builder& operator=(const raster_source_pattern_builder&) = default;
				raster_source_pattern_builder(raster_source_pattern_builder&& other);
				raster_source_pattern_builder& operator=(raster_source_pattern_builder&& other);
				raster_source_pattern_builder(void* user_data, content content, int width, int height);

                pattern get_pattern();
                void set_extend(extend extend);
                extend get_extend();
                void set_filter(filter filter);
                filter get_filter();
                void set_matrix(const matrix& matrix);
                matrix get_matrix();
                
                void set_callback_data(void* data);
				void* get_callback_data();
				void set_acquire(
					::std::function<surface(void* callback_data, surface& target, const rectangle& extents)> acquire_fn,
					::std::function<void(void* callback_data, surface& surface)> release_fn
					);
				void get_acquire(
					::std::function<surface(void* callback_data, surface& target, const rectangle& extents)>& acquire_fn,
					::std::function<void(void* callback_data, surface& surface)>& release_fn
					);
			};

			class surface {
            protected:
                ::std::unique_ptr<cairo_surface_t, ::std::function<void(cairo_surface_t*)>> _Surface;
                ::std::unique_ptr<cairo_t, ::std::function<void(cairo_t*)>> _Context;

			public:
                surface() = delete;

                typedef cairo_surface_t* native_handle_type;
                native_handle_type native_handle() const;

                surface(const surface&) = delete;
                surface& operator=(const surface&) = delete;

                surface(surface&& other);
                surface& operator=(surface&& other);

                explicit surface(native_handle_type nh);

                surface(format fmt, double width, double height);
                // create_similar
                surface(const surface& other, content content, double width, double height);
                // create_for_rectangle
                surface(const surface& target, const rectangle& rect);

                virtual ~surface();

                void finish();
                void flush();

                device get_device();

                content get_content();
                void mark_dirty();
                void mark_dirty_rectangle(const rectangle& rect);

                void set_device_offset(const point& offset);
                void get_device_offset(point& offset);
                void write_to_png(const ::std::string& filename);
                image_surface map_to_image(const rectangle& extents);
                void unmap_image(image_surface& image);
                bool has_surface_resource() const;
                
				void save();
				void restore();
				//surface get_target();
				void push_group();
				void push_group_with_content(content c);
				pattern pop_group();
				void pop_group_to_source();
				surface get_group_target();

				void set_pattern(const pattern& source);
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
				void clip_extents(point& pt0, point& pt1);
				bool in_clip(const point& pt);
				void reset_clip();

				rectangle_list copy_clip_rectangle_list();

				void fill();
				void fill_preserve();
				void fill_extents(point& pt0, point& pt1);
				bool in_fill(const point& pt);

				void mask(pattern& pttn);
				void mask_surface(const surface& surface, const point& origin);

				void paint();
                void paint(const surface& s);
				void paint_with_alpha(double alpha);
                void paint_with_alpha(const surface& s, double alpha);

				void stroke();
				void stroke_preserve();
				void stroke_extents(point& pt0, point& pt1);
				bool in_stroke(const point& pt);

				void copy_page();
				void show_page();

                void set_path(const path& p);

				// Transformations
				void translate(const point& value);
				void scale(const point& value);
				void rotate(double angle);
				void transform(const matrix& matrix);
				void set_matrix(const matrix& matrix);
				void get_matrix(matrix& matrix);
				void identity_matrix();
				void user_to_device(point& pt);
				void user_to_device_distance(point& dpt);
				void device_to_user(point& pt);
				void device_to_user_distance(point& dpt);

				// Text
				void select_font_face(const ::std::string& family, font_slant slant, font_weight weight);
				void set_font_size(double size);
				void set_font_matrix(const matrix& matrix);
				void get_font_matrix(matrix& matrix);
				void set_font_options(const font_options& options);
				font_options get_font_options();
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

            class image_surface : public surface {
                friend surface;
                image_surface() = delete;
            protected:
                ::std::shared_ptr<::std::vector<unsigned char>> _Data;
            public:
                image_surface(const image_surface&) = delete;
                image_surface& operator=(const image_surface&) = delete;
                image_surface(image_surface&& other);
                image_surface& operator=(image_surface&& other);
                image_surface(surface::native_handle_type nh, surface::native_handle_type map_of);
                image_surface(format format, int width, int height);
                image_surface(vector<unsigned char>& data, format format, int width, int height, int stride);
                // create_similar_image
                image_surface(surface& other, format format, int width, int height);
                // create_from_png
                image_surface(const ::std::string& filename);

                void set_data(::std::vector<unsigned char>& data);
                ::std::vector<unsigned char> get_data();
                format get_format();
                int get_width();
                int get_height();
                int get_stride();
            };

            int format_stride_for_width(format format, int width);
			surface make_surface(surface::native_handle_type nh);
			surface make_surface(format format, int width, int height);
			path _Make_path_from_native_handle(path::native_handle_type nh);
		}
	}
}

#endif
