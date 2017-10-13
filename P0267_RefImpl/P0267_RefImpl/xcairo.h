#pragma once

#ifndef _XCAIRO_
#define _XCAIRO_

#include <cairo.h>

#include "io2d.h"

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				template <class GraphicsMath>
				struct _Cairo_graphics_surfaces {
					using graphics_math_type = GraphicsMath;
					// interpreted_path

					struct _Interpreted_path_data {
						::std::shared_ptr<cairo_path_t> _Cairo_path;
					};
					using interpreted_path_data_type = _Interpreted_path_data;

					constexpr static interpreted_path_data_type create_interpreted_path() noexcept;
					template <class Allocator>
					explicit static interpreted_path_data_type create_interpreted_path(const basic_path_builder<GraphicsMath, Allocator>& p);
					template <class ForwardIterator>
					static interpreted_path_data_type create_interpreted_path(ForwardIterator first, ForwardIterator last);

					// brush

					struct _Brush_data {
						::std::shared_ptr<cairo_pattern_t> _Brush;
						::std::shared_ptr<cairo_image_surface> _Image_surface;
						brush_type _Brush_type;
					};
					using brush_data_type = _Brush_data;

					static brush_data_type create_brush(const rgba_color& c);

					template <class InputIterator>
					static brush_data_type create_brush(const basic_point_2d<GraphicsMath>& begin, const basic_point_2d<GraphicsMath>& end, InputIterator first, InputIterator last);

					static brush_data_type create_brush(const basic_point_2d<GraphicsMath>& begin, const basic_point_2d<GraphicsMath>& end, ::std::initializer_list<gradient_stop> il);

					template <class InputIterator>
					static brush_data_type create_brush(const basic_circle<GraphicsMath>& start, const basic_circle<GraphicsMath>& end, InputIterator first, InputIterator last);

					static create_brush(const basic_circle<GraphicsMath>& start, const basic_circle<GraphicsMath>& end, ::std::initializer_list<gradient_stop> il);

					static brush_type get_brush_type(const brush_data_type& data) noexcept;

					// render_props
					struct _Render_props_data {
						antialias _Antialiasing = antialias::good;
						basic_matrix_2d<GraphicsMath> _Matrix;// = matrix_2d::init_identity(); // Transformation matrix
						compositing_op _Compositing = compositing_op::over;
					};
					
					using render_props_data_type = _Render_props_data;

					constexpr static render_props_data_type create_render_props(antialias aa = antialias::good, basic_matrix_2d<GraphicsMath> m = basic_matrix_2d<GraphicsMath>{}, compositing_op co = compositing_op::over) noexcept;
					constexpr static void antialiasing(render_props_data_type& data, antialias aa) noexcept;
					constexpr static void surface_matrix(render_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept;
					constexpr static void compositing(render_props_data_type& data, io2d::compositing_op co) noexcept;
					constexpr static antialias antialiasing(const render_props_data_type& data) noexcept;
					constexpr static basic_matrix_2d<GraphicsMath> surface_matrix(const render_props_data_type& data) noexcept;
					constexpr static compositing_op compositing(const render_props_data_type& data) noexcept;

					// brush_props

					struct _Brush_props_data {
						experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::none;
						experimental::io2d::filter _Filter = experimental::io2d::filter::good;
						experimental::io2d::fill_rule _Fill_rule = experimental::io2d::fill_rule::winding;
						basic_matrix_2d<GraphicsMath> _Matrix;
					};

					using brush_props_data_type = _Brush_props_data;

					constexpr static brush_props_data_type create_brush_props(wrap_mode wm = wrap_mode::none, filter f = filter::good, fill_rule = fill_rule::winding, const basic_matrix_2d<GraphicsMath>& m = basic_matrix_2d<GraphicsMath>{}) noexcept;
					constexpr static void wrap_mode(brush_props_data_type& data, io2d::wrap_mode wm) noexcept;
					constexpr static void filter(brush_props_data_type& data, io2d::filter f) noexcept;
					constexpr static void fill_rule(brush_props_data_type& data, io2d::fill_rule fr) noexcept;
					constexpr static void brush_matrix(brush_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept;
					constexpr static io2d::wrap_mode wrap_mode(const brush_props_data_type& data) noexcept;
					constexpr static io2d::filter filter(const brush_props_data_type& data) noexcept;
					constexpr static io2d::fill_rule fill_rule(const brush_props_data_type& data) noexcept;
					constexpr static basic_matrix_2d<GraphicsMath> brush_matrix(const brush_props_data_type& data) noexcept;

					// clip_props
					struct _Clip_props_data {
						interpreted_path_data_type clip;
						io2d::fill_rule fr;
					};

					using clip_props_data_type = _Clip_props_data;

					static clip_props_data_type create_clip_props() noexcept;
					static clip_props_data_type create_clip_props(const basic_bounding_box<GraphicsMath>& bbox, io2d::fill_rule fr) noexcept;
					template <class Allocator>
					static clip_props_data_type create_clip_props(const basic_path_builder<GraphicsMath, Allocator>& pb, io2d::fill_rule fr);
					static clip_props_data_type create_clip_props(const basic_interpreted_path_data_type& ip, io2d::fill_rule fr) noexcept;

					static void clip(clip_props_data_type& data, const basic_bounding_box<GraphicsMath>& bbox) noexcept;
					template <class Allocator>
					static void clip(clip_props_data_type& data, const basic_path_builder<GraphicsMath, Allocator>& pb);
					static void clip(clip_props_data_type& data, const basic_interpreted_path<_Cairo_graphics_surfaces>& ip) noexcept;
					static void fill_rule(clip_props_data_type& data, io2d::fill_rule fr) noexcept;
					static interpreted_path_data_type clip(const clip_props_data_type& data) noexcept;
					static io2d::fill_rule fill_rule(const clip_props_data_type& data) noexcept;

					// stroke_props

					struct _Stroke_props_data {
						float _Line_width = 2.0F;
						float _Miter_limit = 10.0F;
						experimental::io2d::line_cap _Line_cap = experimental::io2d::line_cap::none;
						experimental::io2d::line_join _Line_join = experimental::io2d::line_join::miter;
					};

					using stroke_props_data_type = _Stroke_props_data;

					constexpr static stroke_props_data_type create_stroke_props(float lw = 2.0f, io2d::line_cap lc = io2d::line_cap::none, io2d::line_join lj = io2d::line_join::miter, float ml = 10.0f) noexcept;

					constexpr static void line_width(stroke_props_data_type& data, float lw) noexcept;
					constexpr static void line_cap(stroke_props_data_type& data, io2d::line_cap lc) noexcept;
					constexpr static void line_join(stroke_props_data_type& data, io2d::line_join lj) noexcept;
					constexpr static void miter_limit(stroke_props_data_type& data, float ml) noexcept;
					constexpr static float line_width(const stroke_props_data_type& data) noexcept;
					constexpr static io2d::line_cap line_cap(const stroke_props_data_type& data) noexcept;
					constexpr static io2d::line_join line_join(const stroke_props_data_type& data) noexcept;
					constexpr static float miter_limit(const stroke_props_data_type& data) noexcept;
					constexpr static float max_miter_limit(const stroke_props_data_type& data) noexcept;

					// mask_props

					struct _Mask_props_data {
						experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::repeat;
						experimental::io2d::filter _Filter = experimental::io2d::filter::good;
						basic_matrix_2d<GraphicsMath> _Matrix = basic_matrix_2d<GraphicsMath>{};
					};

					using mask_props_data_type = _Mask_props_data;

					constexpr static mask_props_data_type create_brush_props(io2d::wrap_mode wm = io2d::wrap_mode::none, io2d::filter f = io2d::filter::good, const basic_matrix_2d<GraphicsMath>& m = basic_matrix_2d<GraphicsMath>{}) noexcept;
					constexpr static void wrap_mode(mask_props_data_type& data, io2d::wrap_mode wm) noexcept;
					constexpr static void filter(mask_props_data_type& data, io2d::filter f) noexcept;
					constexpr static void mask_matrix(mask_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept;
					constexpr static io2d::wrap_mode wrap_mode(const mask_props_data_type& data, io2d::wrap_mode wm) noexcept;
					constexpr static io2d::filter filter(const mask_props_data_type& data) noexcept;
					constexpr static basic_matrix_2d<GraphicsMath> get_mask_matrix(const mask_props_data_type& data) noexcept;

					// dashes
					struct _Dashes_data {
						float offset;
						::std::vector<float> pattern;
					};

					using dashes_data_type = _Dashes_data;
					static dashes_data_type create_dashes() noexcept;
					template <class ForwardIterator>
					static dashes_data_type create_dashes(float offset, ForwardIterator first, ForwardIterator last);
					static dashes_data_type create_dashes(float offset, ::std::initializer_list<float> il);

					// image_surface
					const float _Line_join_miter_miter_limit = 10000.0F;

					struct _Image_surface_data {
						::std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> _Surface;
						::std::unique_ptr<cairo_t, decltype(&cairo_destroy)> _Context;
						basic_bounding_box<GraphicsMath> _Dirty_rect;
						::std::experimental::io2d::format _Format;
					};

					using image_surface_data_type = _Image_surface_data;
					static void clear(image_surface_data_type& data);

					static image_surface_data_type create_image_surface(::std::experimental::io2d::format fmt, int width, int height);
					//static image_surface_data_type create_image_surface(native_handle_type nh, ::std::experimental::io2d::format fmt);
					static image_surface_data_type create_image_surface(::std::filesystem::path p, image_file_format iff);
					static image_surface_data_type create_image_surface(::std::filesystem::path p, image_file_format iff, ::std::error_code& ec) noexcept;
					static void save(image_surface_data_type& data, ::std::filesystem::path p, image_file_format iff);
					static void save(image_surface_data_type& data, ::std::filesystem::path p, image_file_format iff, error_code& ec) noexcept;
					static void flush(image_surface_data_type& data);
					static void flush(image_surface_data_type& data, error_code& ec) noexcept;
					static void mark_dirty(image_surface_data_type& data);
					static void mark_dirty(image_surface_data_type& data, error_code& ec) noexcept;
					static void mark_dirty(image_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents);
					static void mark_dirty(image_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents, error_code& ec) noexcept;
					static void paint(image_surface_data_type& data, const brush_data_type& b, const brush_props_data_type& bp, const render_props_data_type& rp, const clip_props_data_type& cl);
					static void stroke(image_surface_data_type& data, const basic_brush<_Cairo_graphics_surfaces>& b, const basic_interpreted_path<_Cairo_graphics_surfaces>& ip, const basic_brush<_Cairo_graphics_surfaces>& bp, const basic_stroke_props<_Cairo_graphics_surfaces>& sp, const dashes& d, const basic_render_props<_Cairo_graphics_surfaces>& rp, const basic_clip_props<_Cairo_graphics_surfaces>& cl);
					static void fill(image_surface_data_type& data, const brush_data_type& b, const basic_interpreted_path_data_type& pg, const brush_props_data_type& bp, const render_props_data_type& rp, const clip_props_data_type& cl);
					static void mask(image_surface_data_type& data, const brush_data_type& b, const brush_data_type& mb, const brush_props_data_type& bp, const mask_props_data_type& mp, const render_props_data_type& rp, const clip_props_data_type& cl);

					// display_surface
					// Note: This needs to have impl-def ctor(s) for dealing with different windowing systems, etc. That's how we can get custom event handlers and existing windows passed in. There must also be defined ctors that provide "default" event handling. All of these will create display_surface_data_type objects. Custom handlers (e.g. a WNDPROC) can then use those objects to invoke draw functions (i.e. the invoke functions for the callbacks).
#if defined(WIN32) || defined(WIN64)
					struct _Display_surface_win32_data {
						HWND hwnd;
						HDC hdc;
						//WNDPROC wndproc;

						brush_data_type _Letterbox_brush;
						_Brush_props_data<GraphicsMath> _Letterbox_brush_props;
						
						int display_width;
						int display_height;
						format display_format;
						::std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> display_surface;
						::std::unique_ptr<cairo_t, decltype(&cairo_destroy)> display_context;

						int buffer_width;
						int buffer_height;
						format buffer_format;
						::std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> buffer_surface;
						::std::unique_ptr<cairo_t, decltype(&cairo_destroy)> buffer_context;
						basic_bounding_box<GraphicsMath> dirty_rect;

						::std::function<void(basic_display_surface<_Cairo_graphics_surfaces>&)> display_callback;
						::std::function<void(basic_display_surface<_Cairo_graphics_surfaces>&)> size_change_callback;
						::std::function<basic_bounding_box<GraphicsMath>(const basic_display_surface<_Cairo_graphics_surfaces>&, bool&)> user_scaling_callback;

						bool auto_clear;
					};

					using display_surface_data_type = _Display_surface_win32_data;
#endif

					// Impl-def create function(s)
					static display_surface_data_type create(HWND hwnd, HDC hdc, int preferredWidth, int preferredHeight, format preferredFormat);

					// Specified create functions
					static display_surface_data_type create(int preferredWidth, int preferredHeight, format preferredFormat, scaling scl, refresh_rate rr, float fps);
					static display_surface_data_type create(int preferredWidth, int preferredHeight, format preferredFormat, error_code& ec, scaling scl, refresh_rate rr, float fps) noexcept;
					static display_surface_data_type create(int preferredWidth, int preferredHeight, format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, scaling scl, refresh_rate rr, float fps);
					static display_surface_data_type create(int preferredWidth, int preferredHeight, format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, error_code& ec, scaling scl, refresh_rate rr, float fps) noexcept;
					static void destroy(display_surface_data_type& data) noexcept;

					// rendering functions
					static void paint(display_surface_data_type& data, const brush_data_type& b, const brush_props_data_type& bp, const render_props_data_type& rp, const clip_props_data_type& cl);
					static void stroke(display_surface_data_type& data, const brush_data_type& b, const basic_interpreted_path_data_type& pg, const brush_props_data_type& bp, const stroke_props_data_type& sp, const dashes& d, const render_props_data_type& rp, const clip_props_data_type& cl);
					static void fill(display_surface_data_type& data, const brush_data_type& b, const basic_interpreted_path_data_type& pg, const brush_props_data_type& bp, const render_props_data_type& rp, const clip_props_data_type& cl);
					static void mask(display_surface_data_type& data, const brush_data_type& b, const brush_data_type& mb, const brush_props_data_type& bp, const mask_props_data_type& mp, const render_props_data_type& rp, const clip_props_data_type& cl);

					// display_surface common functions
					static void draw_callback(display_surface_data_type& data, function<void(basic_display_surface<_Cairo_graphics_surfaces>&)>);
					static void size_change_callback(display_surface_data_type& data, function<void(basic_display_surface<_Cairo_graphics_surfaces>&)>);
					static void user_scaling_callback(display_surface_data_type& data, function<basic_bounding_box<GraphicsMath>(const basic_display_surface<_Cairo_graphics_surfaces>&, bool&)>);
					static void width(display_surface_data_type& data, int val);
					static void height(display_surface_data_type& data, int val);
					static void display_width(display_surface_data_type& data, int val);
					static void display_height(display_surface_data_type& data, int val);
					static void dimensions(display_surface_data_type& data, const basic_display_point<GraphicsMath>& val);
					static void display_dimensions(display_surface_data_type& data, const basic_display_point<GraphicsMath>& val);
					static void scaling(display_surface_data_type& data, io2d::scaling val);
					static void letterbox_brush(display_surface_data_type& data, const optional<basic_brush<_Cairo_graphics_surfaces>>& val, const optional<basic_brush_props<_Cairo_graphics_surfaces>& bp) noexcept;
					static void letterbox_brush_props(display_surface_data_type& data, const basic_brush_props<_Cairo_graphics_surfaces>& val);
					static void auto_clear(display_surface_data_type& data, bool val);
					static void refresh_rate(display_surface_data_type& data, io2d::refresh_rate val);
					static void desired_frame_rate(display_surface_data_type& data, float val);
					static void redraw_required(display_surface_data_type& data);

					static function<void(const basic_display_surface<_Cairo_graphics_surfaces>&)> draw_callback(display_surface_data_type& data);
					static function<void(const basic_display_surface<_Cairo_graphics_surfaces>&)> size_change_callback(display_surface_data_type& data);
					static function<basic_bounding_box<GraphicsMath>(const basic_display_surface<_Cairo_graphics_surfaces>&, bool&)> user_scaling_callback(const display_surface_data_type& data);
					static int width(const display_surface_data_type& data);
					static int height(const display_surface_data_type& data);
					static int display_width(const display_surface_data_type& data);
					static int display_height(const display_surface_data_type& data);
					static basic_display_point<GraphicsMath> dimensions(const display_surface_data_type& data);
					static basic_display_point<GraphicsMath> display_dimensions(const display_surface_data_type& data);
					static io2d::scaling scaling(display_surface_data_type& data);
					static optional<brush<_Cairo_graphics_surfaces>> letterbox_brush(const display_surface_data_type& data) noexcept;
					static basic_brush_props<GraphicsMath, _Cairo_graphics_surfaces> letterbox_brush_props(const display_surface_data_type& data);
					static bool auto_clear(display_surface_data_type& data);
					static io2d::refresh_rate refresh_rate(display_surface_data_type& data);
					static float desired_frame_rate(display_surface_data_type& data);

					// display_surface functions that only apply to existing "surfaces"; these are the invokes, etc.
					static void invoke_draw_callback(display_surface_data_type& data, optional<clip_props_data_type>& clip);
					static void invoke_size_change_callback(display_surface_data_type& data);
					static void invoke_user_scaling_callback(display_surface_data_type& data);

					// display_surface functions that only apply to library-created "surfaces"
#if defined(WIN32) || defined(WIN64)
					struct _Show_return_data_win32 {
						WPARAM result;
					};
					using show_return_data_type = _Show_return_data_win32;
#endif
					static show_return_data_type begin_show(display_surface_data_type& data);
					static void end_show(display_surface_data_type& data);
				};

				struct cairo_renderer
				{
					using renderer_interpreted_path = cairo_interpreted_path;
					using renderer_brush = cairo_brush;
					using renderer_surface_native_handles = _Surface_native_handles;
					using renderer_surface = cairo_surface;
					using renderer_display_surface = cairo_display_surface;
					using renderer_image_surface = cairo_image_surface;
					using renderer_mapped_surface = cairo_mapped_surface;
				};

				class cairo_interpreted_path
				{
					::std::shared_ptr<cairo_path_t> _Cairo_path;

				public:
					cairo_path* _Native_handle() const noexcept;

					constexpr cairo_interpreted_path() noexcept;
					template <class GraphicsMath, class Allocator>
					explicit cairo_interpreted_path(const path_builder<GraphicsMath, Allocator>& p);
					template <class ForwardIterator>
					cairo_interpreted_path(ForwardIterator first, ForwardIterator last);
					cairo_interpreted_path(const cairo_interpreted_path& other) noexcept;
					cairo_interpreted_path& operator=(const cairo_interpreted_path& other) noexcept;
					cairo_interpreted_path(cairo_interpreted_path&& other) noexcept;
					cairo_interpreted_path& operator=(cairo_interpreted_path&& other) noexcept;
					~cairo_interpreted_path() noexcept;
				};

				class cairo_brush
				{
					::std::shared_ptr<cairo_pattern_t> _Brush;
					::std::shared_ptr<cairo_image_surface> _Image_surface;
					brush_type _Brush_type;

				public:
					cairo_pattern_t* _Native_handle() const noexcept;

					explicit cairo_brush(const rgba_color& c);

					template <class InputIterator>
					cairo_brush(const point_2d& begin, const point_2d& end, InputIterator first, InputIterator last);

					cairo_brush(const point_2d& begin, const point_2d& end, ::std::initializer_list<gradient_stop> il);

					template <class GraphicsMath, class InputIterator>
					cairo_brush(const circle<GraphicsMath>& start, const circle<GraphicsMath>& end, InputIterator first, InputIterator last);

					template <class GraphicsMath>
					cairo_brush(const circle<GraphicsMath>& start, const circle<GraphicsMath>& end, ::std::initializer_list<gradient_stop> il);

					explicit cairo_brush(cairo_image_surface&& img);	// Fix implementation once cairo_image_surface is done

					brush_type type() const noexcept;
				};

				struct _Surface_native_handles {
					::cairo_surface_t* csfce;
					::cairo_t* cctxt;
				};

				class cairo_surface
				{
					friend class cairo_image_surface;
					friend class cairo_display_surface;

				public:
					using native_handle_type = _Surface_native_handles;

				private:
					const float _Line_join_miter_miter_limit = 10000.0F;

					::std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> _Surface;
					::std::unique_ptr<cairo_t, decltype(&cairo_destroy)> _Context;
					bounding_box<linear_algebra> _Dirty_rect;
					::std::experimental::io2d::format _Format;

				public:
					// surplus to paper
					_IO2D_API _Surface_native_handles _Native_handle() const noexcept;
					_IO2D_API void clear();

					_IO2D_API cairo_surface(::std::experimental::io2d::format fmt, int width, int height);
					_IO2D_API cairo_surface(native_handle_type nh, ::std::experimental::io2d::format fmt);
					_IO2D_API void flush();
					_IO2D_API void flush(error_code& ec) noexcept;
					_IO2D_API void mark_dirty();
					_IO2D_API void mark_dirty(error_code& ec) noexcept;
					_IO2D_API void mark_dirty(const bounding_box<linear_algebra>& extents);
					_IO2D_API void mark_dirty(const bounding_box<linear_algebra>& extents, error_code& ec) noexcept;
					_IO2D_API void paint(const cairo_brush& b, const optional<brush_props<linear_algebra>>& bp = nullopt, const optional<render_props<linear_algebra>>& rp = nullopt, const optional<clip_props<cairo_renderer>>& cl = nullopt);
					template <class Allocator>
					void stroke(const cairo_brush& b, const path_builder<Allocator>& pb, const optional<brush_props<linear_algebra>>& bp = nullopt, const optional<stroke_props>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<render_props<linear_algebra>>& rp = nullopt, const optional<clip_props<cairo_renderer>>& cl = nullopt);
					_IO2D_API void stroke(const cairo_brush& b, const cairo_interpreted_path& pg, const optional<brush_props<linear_algebra>>& bp = nullopt, const optional<stroke_props>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<render_props<linear_algebra>>& rp = nullopt, const optional<clip_props<cairo_renderer>>& cl = nullopt);
					template <class Allocator>
					void fill(const cairo_brush& b, const path_builder<Allocator>& pb, const optional<brush_props<linear_algebra>>& bp = nullopt, const optional<render_props<linear_algebra>>& rp = nullopt, const optional<clip_props<cairo_renderer>>& cl = nullopt);
					_IO2D_API void fill(const cairo_brush& b, const cairo_interpreted_path& pg, const optional<brush_props<linear_algebra>>& bp = nullopt, const optional<render_props<linear_algebra>>& rp = nullopt, const optional<clip_props<cairo_renderer>>& cl = nullopt);
					_IO2D_API void mask(const cairo_brush& b, const cairo_brush& mb, const optional<brush_props<linear_algebra>>& bp = nullopt, const optional<mask_props<linear_algebra>>& mp = nullopt, const optional<render_props<linear_algebra>>& rp = nullopt, const optional<clip_props<cairo_renderer>>& cl = nullopt);
				};

				class cairo_image_surface
				{
					cairo_surface* _Cairo_surface;

				public:
					_IO2D_API cairo_image_surface(cairo_surface* cs);
#ifdef _Filesystem_support_test
					_IO2D_API cairo_image_surface(cairo_surface* cs, filesystem::path f, image_file_format i, io2d::format fmt);
					cairo_image_surface(cairo_surface* cs, filesystem::path f, image_file_format i, io2d::format fmt, error_code& ec) noexcept;
#else
					_IO2D_API cairo_image_surface(::std::string f, experimental::io2d::format fmt, image_file_format idf);
					cairo_image_surface(::std::string f, image_file_format i, io2d::format fmt, error_code& ec) noexcept;
#endif
					cairo_image_surface(cairo_image_surface&&) = default;
					cairo_image_surface& operator=(cairo_image_surface&&) = default;
#ifdef _Filesystem_support_test
					_IO2D_API void save(filesystem::path p, image_file_format i);
					void save(filesystem::path p, image_file_format i, error_code& ec) noexcept;
#else
					_IO2D_API void save(::std::string f, image_file_format i);
					void save(::std::string f, image_file_format i, error_code& ec) noexcept;
#endif
					_IO2D_API void map(const function<void(mapped_surface<linear_algebra, cairo_renderer>&)>& action);
					_IO2D_API void map(const function<void(mapped_surface<linear_algebra, cairo_renderer>&, error_code&)>& action, error_code& ec);
					static int max_width() noexcept;
					static int max_height() noexcept;
					_IO2D_API io2d::format format() const noexcept;
					_IO2D_API int width() const noexcept;
					_IO2D_API int height() const noexcept;
				};

				class cairo_display_surface
				{
					cairo_surface* _Cairo_surface;
					::std::experimental::io2d::scaling _Scaling;
					display_point _Dimensions;
					::std::unique_ptr<::std::function<void(display_surface<linear_algebra, cairo_renderer>& sfc)>> _Draw_fn;
					::std::unique_ptr<::std::function<void(display_surface<linear_algebra, cairo_renderer>& sfc)>> _Size_change_fn;
					::std::unique_ptr<::std::function<::std::experimental::io2d::bounding_box<linear_algebra>(const display_surface<linear_algebra, cairo_renderer>&, bool&)>> _User_scaling_fn;
					optional<brush_props<linear_algebra>> _Letterbox_brush_props;
					typedef bool _Auto_clear_type;
					bool _Auto_clear;
					bool _Redraw_requested;
					::std::unique_ptr<cairo_surface_t, ::std::function<void(cairo_surface_t*)>> _Native_surface;
					::std::unique_ptr<cairo_t, ::std::function<void(cairo_t*)>> _Native_context;
					optional<cairo_brush> _Letterbox_brush;
					cairo_brush _Default_brush;

					void _Render_to_native_surface(display_point dd, display_surface<linear_algebra, cairo_renderer>&);
					void _Render_to_native_surface(display_point dd, display_surface<linear_algebra, cairo_renderer>&, ::std::error_code& ec) noexcept;
					void _Render_for_scaling_uniform_or_letterbox(display_point dd);
					void _Render_for_scaling_uniform_or_letterbox(display_point dd, ::std::error_code& ec) noexcept;

				public:
					const auto _Native_handle() const { return _Cairo_surface->_Native_handle(); }

					cairo_display_surface() = delete;
					cairo_display_surface(const cairo_display_surface&) = delete;
					cairo_display_surface& operator=(const cairo_display_surface&) = delete;
					cairo_display_surface(cairo_display_surface&& other) noexcept = default;
					cairo_display_surface& operator=(cairo_display_surface&& other) noexcept = default;

					// declarations from paper
					_IO2D_API cairo_display_surface(cairo_surface* cs, int preferredWidth, int preferredHeight, io2d::format preferredFormat, io2d::scaling scl = io2d::scaling::letterbox);
					cairo_display_surface(cairo_surface* cs, int preferredWidth, int preferredHeight, io2d::format preferredFormat, error_code& ec, io2d::scaling scl = io2d::scaling::letterbox) noexcept;
					~cairo_display_surface() {}
					template <class T>
					void make_native_surface(T&& context);
					_IO2D_API void make_impl_surface();
					_IO2D_API void draw_callback(const function<void(display_surface<linear_algebra, cairo_renderer>& sfc)>& fn);
					_IO2D_API void invoke_draw_callback(display_point dp, display_surface<linear_algebra, cairo_renderer>& ds);
					_IO2D_API void size_change_callback(const function<void(display_surface<linear_algebra, cairo_renderer>& sfc)>& fn);
					_IO2D_API void invoke_size_change_callback(display_surface<linear_algebra, cairo_renderer>& ds);
					_IO2D_API void dimensions(display_point dp);
					_IO2D_API void dimensions(display_point dp, error_code& ec) noexcept;
					_IO2D_API void scaling(experimental::io2d::scaling scl) noexcept;
					_IO2D_API void user_scaling_callback(const function<experimental::io2d::bounding_box<linear_algebra>(const display_surface<linear_algebra, cairo_renderer>&, bool&)>& fn);
					_IO2D_API void letterbox_brush(const optional<cairo_brush>& b, const optional<brush_props<linear_algebra>> = nullopt) noexcept;
					_IO2D_API void auto_clear(bool val) noexcept;
					_IO2D_API void redraw_required() noexcept;
					_IO2D_API bool reset_redraw_request() noexcept;
					_IO2D_API experimental::io2d::format format() const noexcept;
					_IO2D_API display_point dimensions() const noexcept;
					_IO2D_API experimental::io2d::scaling scaling() const noexcept;
					_IO2D_API function<experimental::io2d::bounding_box<linear_algebra>(const display_surface<linear_algebra, cairo_renderer>&, bool&)> user_scaling_callback() const;
					_IO2D_API function<experimental::io2d::bounding_box<linear_algebra>(const display_surface<linear_algebra, cairo_renderer>&, bool&)> user_scaling_callback(error_code& ec) const noexcept;
					_IO2D_API optional<cairo_brush> letterbox_brush() const noexcept;
					_IO2D_API optional<brush_props<linear_algebra>> letterbox_brush_props() const noexcept;
					_IO2D_API bool auto_clear() const noexcept;
				};

				class cairo_mapped_surface
				{
					friend mapped_surface<linear_algebra, cairo_renderer>;

					_Surface_native_handles _Mapped_surface;
					_Surface_native_handles _Map_of;

					friend cairo_image_surface;
					cairo_mapped_surface(_Surface_native_handles nh, _Surface_native_handles map_of);
					cairo_mapped_surface(_Surface_native_handles nh, _Surface_native_handles map_of, ::std::error_code& ec) noexcept;

				public:
					// surplus to paper
					cairo_mapped_surface(const cairo_mapped_surface&) = delete;
					cairo_mapped_surface& operator=(const cairo_mapped_surface&) = delete;
					cairo_mapped_surface(cairo_mapped_surface&& other) = delete;
					cairo_mapped_surface& operator=(cairo_mapped_surface&& other) = delete;

					cairo_mapped_surface() = delete;
					~cairo_mapped_surface();
					void commit_changes();
					void commit_changes(error_code& ec) noexcept;
					unsigned char* data();
					unsigned char* data(error_code& ec) noexcept;
					const unsigned char* data() const;
					const unsigned char* data(error_code& ec) const noexcept;
					experimental::io2d::format format() const noexcept;
					int width() const noexcept;
					int height() const noexcept;
					int stride() const noexcept;
				};
			}
		}
	}
}

#include "xcairo_impl.h"

#endif