#pragma once
#include "xio2d.h"
#include "xsurfaces_enums.h"
#include "xpath.h"
#include "xgraphicsmath.h"

//#if defined(_Filesystem_support_test)
//#include <filesystem>
//#endif
#include <initializer_list>

namespace std::experimental::io2d {
	inline namespace v1 {
		template <class GraphicsSurfaces>
		class basic_render_props {
		public:
			using data_type = typename GraphicsSurfaces::surface_state_props::render_props_data_type;
			using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
		private:
			data_type _Data;
		public:
			const data_type& data() const noexcept;
			data_type& data() noexcept;
			basic_render_props() noexcept;
			explicit basic_render_props(antialias a, const basic_matrix_2d<graphics_math_type>& m = basic_matrix_2d<graphics_math_type>{}, compositing_op co = compositing_op::over) noexcept;
			basic_render_props(const basic_render_props& other);
			basic_render_props& operator=(const basic_render_props& other);
			basic_render_props(basic_render_props&& other) noexcept;
			basic_render_props& operator=(basic_render_props&& other) noexcept;
			~basic_render_props() noexcept;
			void antialiasing(antialias a) noexcept;
			void compositing(compositing_op co) noexcept;
			void surface_matrix(const basic_matrix_2d<graphics_math_type>& m) noexcept;
			antialias antialiasing() const noexcept;
			compositing_op compositing() const noexcept;
			basic_matrix_2d<graphics_math_type> surface_matrix() const noexcept;
		};

		template <class GraphicsSurfaces>
		class basic_brush_props {
		public:
			using data_type = typename GraphicsSurfaces::surface_state_props::brush_props_data_type;
			using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;

		private:
			data_type _Data;

		public:
			basic_brush_props(io2d::wrap_mode w = io2d::wrap_mode::none, io2d::filter fi = io2d::filter::good, io2d::fill_rule fr = io2d::fill_rule::winding, const basic_matrix_2d<graphics_math_type>& m = basic_matrix_2d<graphics_math_type>{}) noexcept;
			basic_brush_props(const basic_brush_props& other);
			basic_brush_props& operator=(const basic_brush_props& other);
			basic_brush_props(basic_brush_props&& other) noexcept;
			basic_brush_props& operator=(basic_brush_props&& other) noexcept;
			~basic_brush_props() noexcept;
			void filter(io2d::filter fi) noexcept;
			void wrap_mode(io2d::wrap_mode w) noexcept;
			void fill_rule(io2d::fill_rule fr) noexcept;
			void brush_matrix(const basic_matrix_2d<graphics_math_type>& m) noexcept;
			io2d::filter filter() const noexcept;
			io2d::wrap_mode wrap_mode() const noexcept;
			io2d::fill_rule fill_rule() const noexcept;
			basic_matrix_2d<graphics_math_type> brush_matrix() const noexcept;
		};

		template <class GraphicsSurfaces>
		class basic_clip_props {
		public:
			using data_type = typename GraphicsSurfaces::surface_state_props::clip_props_data_type;
			using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
		private:
			data_type _Data;
		public:
			const data_type& data() const noexcept;
			data_type& data() noexcept;

			basic_clip_props() noexcept;
			explicit basic_clip_props(const basic_bounding_box<graphics_math_type>& r, experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding);
			template <class Allocator>
			explicit basic_clip_props(const basic_path_builder<GraphicsSurfaces, Allocator>& pb, io2d::fill_rule fr = io2d::fill_rule::winding);
			explicit basic_clip_props(const basic_interpreted_path<GraphicsSurfaces>& ip, io2d::fill_rule fr = io2d::fill_rule::winding) noexcept;
			basic_clip_props(const basic_clip_props& other);
			basic_clip_props& operator=(const basic_clip_props& other);
			basic_clip_props(basic_clip_props&& other) noexcept;
			basic_clip_props& operator=(basic_clip_props&& other) noexcept;
			~basic_clip_props() noexcept;
			template <class Allocator>
			void clip(const basic_path_builder<GraphicsSurfaces, Allocator>& pb);
			void clip(const basic_interpreted_path<GraphicsSurfaces>& ip) noexcept;
			void fill_rule(experimental::io2d::fill_rule fr) noexcept;
			basic_interpreted_path<GraphicsSurfaces> clip() const noexcept;
			io2d::fill_rule fill_rule() const noexcept;
		};

		template <class GraphicsSurfaces>
		class basic_stroke_props {
		public:
			using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
			using data_type = typename GraphicsSurfaces::surface_state_props::stroke_props_data_type;
		private:
			data_type _Data;
		public:
			const data_type& data() const noexcept;
			data_type& data() noexcept;
			basic_stroke_props() noexcept;
			explicit basic_stroke_props(float w, io2d::line_cap lc = io2d::line_cap::none, io2d::line_join lj = io2d::line_join::miter, float ml = 10.0f) noexcept;
			basic_stroke_props(const basic_stroke_props& other);
			basic_stroke_props& operator=(const basic_stroke_props& other);
			basic_stroke_props(basic_stroke_props&& other) noexcept;
			basic_stroke_props& operator=(basic_stroke_props&& other) noexcept;
			~basic_stroke_props() noexcept;
			void line_width(float w) noexcept;
			void line_cap(io2d::line_cap lc) noexcept;
			void line_join(io2d::line_join lj) noexcept;
			void miter_limit(float ml) noexcept;
			float line_width() const noexcept;
			io2d::line_cap line_cap() const noexcept;
			io2d::line_join line_join() const noexcept;
			float miter_limit() const noexcept;
			float max_miter_limit() const noexcept;
		};

		template <class GraphicsSurfaces>
		class basic_mask_props {
		public:
			using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
			using data_type = typename GraphicsSurfaces::surface_state_props::mask_props_data_type;
		private:
			data_type _Data;
		public:
			const data_type& data() const noexcept;
			data_type& data() noexcept;

			basic_mask_props(io2d::wrap_mode w = io2d::wrap_mode::repeat, io2d::filter fi = io2d::filter::good, const basic_matrix_2d<graphics_math_type>& m = basic_matrix_2d<graphics_math_type>{}) noexcept;
			basic_mask_props(const basic_mask_props& other) noexcept;
			basic_mask_props& operator=(const basic_mask_props& other) noexcept;
			basic_mask_props(basic_mask_props&& other) noexcept;
			basic_mask_props& operator=(basic_mask_props&& other) noexcept;
			~basic_mask_props() noexcept;
			void wrap_mode(experimental::io2d::wrap_mode w) noexcept;
			void filter(experimental::io2d::filter fi) noexcept;
			void mask_matrix(const basic_matrix_2d<graphics_math_type>& m) noexcept;
			experimental::io2d::wrap_mode wrap_mode() const noexcept;
			experimental::io2d::filter filter() const noexcept;
			basic_matrix_2d<graphics_math_type> mask_matrix() const noexcept;
		};

		template <class GraphicsSurfaces>
		class basic_dashes {
		public:
			using data_type = typename GraphicsSurfaces::surface_state_props::dashes_data_type;
		private:
			data_type _Data;
		public:
			const data_type& data() const noexcept;
			data_type& data() noexcept;
			basic_dashes() noexcept;
			template <class ForwardIterator>
			basic_dashes(float offset, ForwardIterator first, ForwardIterator last);
			basic_dashes(float offset, ::std::initializer_list<float> il);
			basic_dashes(const basic_dashes& other);
			basic_dashes& operator=(const basic_dashes& other);
			basic_dashes(basic_dashes&& other) noexcept;
			basic_dashes& operator=(basic_dashes&& other) noexcept;
			~basic_dashes() noexcept;
		};

		template <class GraphicsSurfaces>
		class basic_image_surface {
		public:
			using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
			using data_type = typename GraphicsSurfaces::surfaces::image_surface_data_type;

		private:
			data_type _Data;

		public:
			data_type& data() noexcept;
			basic_image_surface(io2d::format fmt, int width, int height);
#ifdef _Filesystem_support_test
			basic_image_surface(filesystem::path f, image_file_format iff, io2d::format fmt);
			basic_image_surface(filesystem::path f, image_file_format iff, io2d::format fmt, error_code& ec) noexcept;
#else
			basic_image_surface(::std::string f, image_file_format iff, format fmt);
			basic_image_surface(::std::string f, image_file_format iff, io2d::format fmt, error_code& ec) noexcept;
#endif
			basic_image_surface(basic_image_surface&&) noexcept;
			basic_image_surface& operator=(basic_image_surface&&) noexcept;
			~basic_image_surface() noexcept;
#ifdef _Filesystem_support_test
			void save(filesystem::path p, image_file_format i);
			void save(filesystem::path p, image_file_format i, error_code& ec) noexcept;
#else
			void save(::std::string f, image_file_format i);
			void save(::std::string f, image_file_format i, error_code& ec) noexcept;
#endif
			static basic_display_point<graphics_math_type> max_dimensions() noexcept;
			io2d::format format() const noexcept;
			basic_display_point<graphics_math_type> dimensions() const noexcept;

			void clear();
			void flush();
			void flush(error_code& ec) noexcept;
			void mark_dirty();
			void mark_dirty(error_code& ec) noexcept;
			void mark_dirty(const basic_bounding_box<graphics_math_type>& extents);
			void mark_dirty(const basic_bounding_box<graphics_math_type>& extents, error_code& ec) noexcept;
			void paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			template <class Allocator>
			void stroke(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			void stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			template <class Allocator>
			void fill(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			void fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			void mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_mask_props<GraphicsSurfaces>>& mp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
		};

		template <class GraphicsSurfaces>
		class basic_output_surface {
		public:
			using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
			using data_type = typename GraphicsSurfaces::surfaces::output_surface_data_type;

		private:
			data_type _Data;

		public:
			data_type& data() noexcept;

			// System manages event loop
			basic_output_surface(int preferredWidth, int preferredHeight,
				io2d::format preferredFormat, io2d::scaling scl = io2d::scaling::letterbox,
				io2d::refresh_style rr = io2d::refresh_style::as_fast_as_possible, float fps = 30.0f);
			basic_output_surface(int preferredWidth, int preferredHeight,
				io2d::format preferredFormat, error_code& ec,
				io2d::scaling scl = io2d::scaling::letterbox,
				io2d::refresh_style rr = io2d::refresh_style::as_fast_as_possible, float fps = 30.0f)
				noexcept;
			basic_output_surface(int preferredWidth, int preferredHeight,
				io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight,
				io2d::scaling scl = io2d::scaling::letterbox,
				io2d::refresh_style rr = io2d::refresh_style::as_fast_as_possible, float fps = 30.0f);
			basic_output_surface(int preferredWidth, int preferredHeight,
				experimental::io2d::format preferredFormat,
				int preferredDisplayWidth, int preferredDisplayHeight, error_code& ec,
				io2d::scaling scl = io2d::scaling::letterbox,
				io2d::refresh_style rr = io2d::refresh_style::as_fast_as_possible, float fps = 30.0f)
				noexcept;

			~basic_output_surface() noexcept;
			basic_output_surface(basic_output_surface&&) noexcept;
			basic_output_surface& operator=(basic_output_surface&&) noexcept;

			void redraw_required() noexcept;
			int begin_show();
			void end_show();

			// rendering functions
			void clear();
			void flush();
			void flush(error_code& ec) noexcept;
			void mark_dirty();
			void mark_dirty(error_code& ec) noexcept;
			void mark_dirty(const basic_bounding_box<graphics_math_type>& extents);
			void mark_dirty(const basic_bounding_box<graphics_math_type>& extents, error_code& ec) noexcept;
			void paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			template <class Allocator>
			void stroke(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			void stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			template <class Allocator>
			void fill(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			void fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			void mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_mask_props<GraphicsSurfaces>>& mp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);

			// display functions
			void draw_callback(const function<void(basic_output_surface& sfc)>& fn);
			void size_change_callback(const function<void(basic_output_surface& sfc)>& fn);
			void dimensions(basic_display_point<graphics_math_type> dp);
			void dimensions(basic_display_point<graphics_math_type> dp, error_code& ec) noexcept;
			void display_dimensions(basic_display_point<graphics_math_type> dp);
			void display_dimensions(basic_display_point<graphics_math_type> dp, error_code& ec) noexcept;
			void scaling(io2d::scaling scl) noexcept;
			void user_scaling_callback(const function<basic_bounding_box<graphics_math_type>(const basic_output_surface&, bool&)>& fn);
			void letterbox_brush(const optional<basic_brush<GraphicsSurfaces>>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt) noexcept;
			void letterbox_brush_props(const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept;
			void auto_clear(bool val) noexcept;
			void redraw_required(bool val = true) noexcept;

			io2d::format format() const noexcept;
			basic_display_point<graphics_math_type> dimensions() const noexcept;
			basic_display_point<graphics_math_type> max_dimensions() const noexcept;
			basic_display_point<graphics_math_type> display_dimensions() const noexcept;
			basic_display_point<graphics_math_type> max_display_dimensions() const noexcept;
			io2d::scaling scaling() const noexcept;
			optional<basic_brush<GraphicsSurfaces>> letterbox_brush() const noexcept;
			optional<basic_brush_props<GraphicsSurfaces>> letterbox_brush_props() const noexcept;
			bool auto_clear() const noexcept;
		};

		template <class GraphicsSurfaces>
		class basic_unmanaged_output_surface {
		public:
			using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
			using data_type = typename GraphicsSurfaces::surfaces::unmanaged_output_surface_data_type;
		private:
			data_type _Data;

		public:
			data_type& data() noexcept;

			// Note: This is the only way to construct this type without bringing implementation details out of the GraphicsSurfaces backend. As such, users of this type need to directly invoke the appropriate GraphicsSurfaces::surfaces::create_unmanaged_output_surface(...) function and pass the result into this ctor.
			basic_unmanaged_output_surface(data_type&& data) noexcept;

			~basic_unmanaged_output_surface() noexcept;
			basic_unmanaged_output_surface(basic_unmanaged_output_surface&&) noexcept;
			basic_unmanaged_output_surface& operator=(basic_unmanaged_output_surface&&) noexcept;

			bool has_draw_callback() const noexcept;
			void invoke_draw_callback();
			bool has_size_change_callback() const noexcept;
			void invoke_size_change_callback();
			bool has_user_scaling_callback() const noexcept;
			basic_bounding_box<graphics_math_type> invoke_user_scaling_callback(bool& useLetterbox);
			void draw_to_output();

			// rendering functions
			void clear();
			void flush();
			void flush(error_code& ec) noexcept;
			void mark_dirty();
			void mark_dirty(error_code& ec) noexcept;
			void mark_dirty(const basic_bounding_box<graphics_math_type>& extents);
			void mark_dirty(const basic_bounding_box<graphics_math_type>& extents, error_code& ec) noexcept;
			void paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			template <class Allocator>
			void stroke(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			void stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			template <class Allocator>
			void fill(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			void fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			void mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_mask_props<GraphicsSurfaces>>& mp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);

			// display functions
			void draw_callback(const function<void(basic_unmanaged_output_surface& sfc)>& fn);
			void size_change_callback(const function<void(basic_unmanaged_output_surface& sfc)>& fn);
			void dimensions(basic_display_point<graphics_math_type> dp);
			void dimensions(basic_display_point<graphics_math_type> dp, error_code& ec) noexcept;
			void display_dimensions(basic_display_point<graphics_math_type> dp);
			void display_dimensions(basic_display_point<graphics_math_type> dp, error_code& ec) noexcept;
			void scaling(io2d::scaling scl) noexcept;
			void user_scaling_callback(const function<basic_bounding_box<graphics_math_type>(const basic_unmanaged_output_surface&, bool&)>& fn);
			void letterbox_brush(const optional<basic_brush<GraphicsSurfaces>>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt) noexcept;
			void letterbox_brush_props(const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept;
			void auto_clear(bool val) noexcept;
			void redraw_required(bool val = true) noexcept;

			io2d::format format() const noexcept;
			basic_display_point<graphics_math_type> dimensions() const noexcept;
			basic_display_point<graphics_math_type> max_dimensions() const noexcept;
			basic_display_point<graphics_math_type> display_dimensions() const noexcept;
			basic_display_point<graphics_math_type> max_display_dimensions() const noexcept;
			io2d::scaling scaling() const noexcept;
			optional<basic_brush<GraphicsSurfaces>> letterbox_brush() const noexcept;
			optional<basic_brush_props<GraphicsSurfaces>> letterbox_brush_props() const noexcept;
			bool auto_clear() const noexcept;
		};

		template <class GraphicsSurfaces>
		basic_image_surface<GraphicsSurfaces> copy_surface(basic_image_surface<GraphicsSurfaces>& sfc) noexcept;

		template <class GraphicsSurfaces>
		basic_image_surface<GraphicsSurfaces> copy_surface(basic_output_surface<GraphicsSurfaces>& sfc) noexcept;

		template <class GraphicsSurfaces>
		basic_image_surface<GraphicsSurfaces> copy_surface(basic_unmanaged_output_surface<GraphicsSurfaces>& sfc) noexcept;

	}
}
