#pragma once
#include "xio2d.h"
#include "xsurfaces_enums.h"
#include "xpath.h"
#include "xlinear_algebra.h"

#if defined(_Filesystem_support_test)
#include <filesystem>
#endif
#include <initializer_list>

namespace std {
	namespace experimental {
		namespace io2d {
			namespace v1 {
				template <class GraphicsSurfaces>
				class basic_render_props {
				public:
					using _Data_type = typename GraphicsSurfaces::render_props_data_type;
					using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
				private:
					_Data_type _Data;
				public:
					constexpr const _Data_type _Get_data() const noexcept;
					constexpr basic_render_props() noexcept;
					constexpr explicit basic_render_props(antialias a, const basic_matrix_2d<graphics_math_type>& m = basic_matrix_2d<graphics_math_type>{}, compositing_op co = compositing_op::over) noexcept;
					constexpr void antialiasing(antialias a) noexcept;
					constexpr void compositing(compositing_op co) noexcept;
					constexpr void surface_matrix(const basic_matrix_2d<graphics_math_type>& m) noexcept;
					constexpr antialias antialiasing() const noexcept;
					constexpr compositing_op compositing() const noexcept;
					constexpr basic_matrix_2d<graphics_math_type> surface_matrix() const noexcept;
				};

				template <class GraphicsSurfaces>
				class basic_brush_props {
				public:
					using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
					using _Data_type = typename GraphicsSurfaces::brush_props_data_type;

				private:
					_Data_type _Data;

				public:
					constexpr basic_brush_props(io2d::wrap_mode w = io2d::wrap_mode::none, io2d::filter fi = io2d::filter::good, io2d::fill_rule fr = io2d::fill_rule::winding, const basic_matrix_2d<graphics_math_type>& m = basic_matrix_2d<graphics_math_type>{}) noexcept;
					constexpr void filter(io2d::filter fi) noexcept;
					constexpr void wrap_mode(io2d::wrap_mode w) noexcept;
					constexpr void fill_rule(io2d::fill_rule fr) noexcept;
					constexpr void brush_matrix(const basic_matrix_2d<graphics_math_type>& m) noexcept;
					constexpr io2d::filter filter() const noexcept;
					constexpr io2d::wrap_mode wrap_mode() const noexcept;
					constexpr io2d::fill_rule fill_rule() const noexcept;
					constexpr basic_matrix_2d<graphics_math_type> brush_matrix() const noexcept;
				};

				template <class GraphicsSurfaces>
				class basic_clip_props {
				public:
					using graphics_math_type = typename GraphicsSurfaces::graphics_math_types;
					using _Data_type = typename GraphicsSurfaces::clip_props_data_type;
				private:
					_Data_type _Data;
				public:
					// surplus to paper
					explicit basic_clip_props(const basic_bounding_box<graphics_math_type>& r, experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding);

					basic_clip_props() noexcept = default;
					template <class Allocator>
					explicit basic_clip_props(const basic_path_builder<graphics_math_type, Allocator>& pb, io2d::fill_rule fr = io2d::fill_rule::winding);
					explicit basic_clip_props(const basic_interpreted_path<GraphicsSurfaces>& ip, io2d::fill_rule fr = io2d::fill_rule::winding) noexcept;
					template <class Allocator>
					void clip(const basic_path_builder<graphics_math_type, Allocator>& pb);
					void clip(const basic_interpreted_path<GraphicsSurfaces>& ip) noexcept;
					void fill_rule(experimental::io2d::fill_rule fr) noexcept;
					basic_interpreted_path<GraphicsSurfaces> clip() const noexcept;
					io2d::fill_rule fill_rule() const noexcept;
				};

				template <class GraphicsSurfaces>
				class basic_stroke_props {
				public:
					using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
					using _Data_type = typename GraphicsSurfaces::stroke_props_data_type;
				private:
					_Data_type _Data;
				public:
					constexpr basic_stroke_props() noexcept;
					constexpr explicit basic_stroke_props(float w, io2d::line_cap lc = io2d::line_cap::none, io2d::line_join lj = io2d::line_join::miter, float ml = 10.0f) noexcept;
					constexpr void line_width(float w) noexcept;
					constexpr void line_cap(experimental::io2d::line_cap lc) noexcept;
					constexpr void line_join(experimental::io2d::line_join lj) noexcept;
					constexpr void miter_limit(float ml) noexcept;
					constexpr float line_width() const noexcept;
					constexpr experimental::io2d::line_cap line_cap() const noexcept;
					constexpr experimental::io2d::line_join line_join() const noexcept;
					constexpr float miter_limit() const noexcept;
					constexpr float max_miter_limit() const noexcept;
				};

				template <class GraphicsSurfaces>
				class basic_mask_props {
				public:
					using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
					using _Data_type = typename GraphicsSurfaces::mask_props_data_type;
				private:
					_Data_type _Data;
				public:
					//// surplus to paper
					//constexpr basic_mask_props(const basic_mask_props&) noexcept = default;
					//constexpr basic_mask_props& operator=(const basic_mask_props&) noexcept = default;
					//basic_mask_props(basic_mask_props&&) noexcept = default;
					//basic_mask_props& operator=(basic_mask_props&&) noexcept = default;

					constexpr const _Data_type& basic_mask_props::_Get_data() const noexcept;
					constexpr basic_mask_props(experimental::io2d::wrap_mode w = experimental::io2d::wrap_mode::repeat, experimental::io2d::filter fi = experimental::io2d::filter::good, const basic_matrix_2d<graphics_math_type>& m = basic_matrix_2d<graphics_math_type>{}) noexcept;
					constexpr void wrap_mode(experimental::io2d::wrap_mode w) noexcept;
					constexpr void filter(experimental::io2d::filter fi) noexcept;
					constexpr void mask_matrix(const basic_matrix_2d<graphics_math_type>& m) noexcept;
					constexpr experimental::io2d::wrap_mode wrap_mode() const noexcept;
					constexpr experimental::io2d::filter filter() const noexcept;
					constexpr basic_matrix_2d<graphics_math_type> mask_matrix() const noexcept;
				};

				template <class GraphicsSurfaces>
				class base_dashes {
					using _Data_type = typename GraphicsSurfaces::dashes_data_type;
					_Data_type _Data;
				public:
					base_dashes() noexcept;
					template <class ForwardIterator>
					base_dashes(float offset, ForwardIterator first, ForwardIterator last);
					base_dashes(float offset, ::std::initializer_list<float> il);
				};

				template <class GraphicsSurfaces>
				class base_image_surface {
				public:
					using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
					using _Data_type = typename GraphicsSurfaces::image_surface_data_type;

				private:
					_Data_type _Data;

				public:
					const _Data_type& _Get_data() const noexcept;
					base_image_surface(io2d::format fmt, int width, int height);
#ifdef _Filesystem_support_test
					base_image_surface(filesystem::path f, image_file_format iff, io2d::format fmt);
					base_image_surface(filesystem::path f, image_file_format iff, io2d::format fmt, error_code& ec) noexcept;
#else
					base_image_surface(::std::string f, image_file_format iff, format fmt);
					base_image_surface(::std::string f, image_file_format iff, io2d::format fmt, error_code& ec) noexcept;
#endif
					base_image_surface(image_surface&&) = default;
					base_image_surface& operator=(image_surface&&) = default;
#ifdef _Filesystem_support_test
					void save(filesystem::path p, image_file_format i);
					void save(filesystem::path p, image_file_format i, error_code& ec) noexcept;
#else
					void save(::std::string f, image_file_format i);
					void save(::std::string f, image_file_format i, error_code& ec) noexcept;
#endif
					static int max_width() noexcept;
					static int max_height() noexcept;
					io2d::format format() const noexcept;
					int width() const noexcept;
					int height() const noexcept;

					void clear();
					void flush();
					void flush(error_code& ec) noexcept;
					void mark_dirty();
					void mark_dirty(error_code& ec) noexcept;
					void mark_dirty(const basic_bounding_box<graphics_math_type>& extents);
					template <class GraphicsMath>
					void mark_dirty(const basic_bounding_box<graphics_math_type>& extents, error_code& ec) noexcept;
					void paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
					template <class Allocator>
					void stroke(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
					void stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
					template <class Allocator>
					void fill(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
					void fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
					void mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_mask_props<GraphicsSurfaces>>& mp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
				};

				template <class GraphicsSurfaces>
				class base_display_surface {
				public:
					using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
					using _Data_type = typename GraphicsSurfaces::display_surface_data_type;

				protected:
					_Data_type _Data;
					
					base_display_surface(_Data_type&& data);
					base_display_surface(base_display_surface&&) noexcept = default;
					base_display_surface& operator=(base_display_surface&&) noexcept = default;

				private:
					~base_display_surface() noexcept;
				public:
					const _Data_type& _Get_data() const noexcept;

					// rendering functions
					void clear();
					void flush();
					void flush(error_code& ec) noexcept;
					void mark_dirty();
					void mark_dirty(error_code& ec) noexcept;
					void mark_dirty(const basic_bounding_box<graphics_math_type>& extents);
					template <class GraphicsMath>
					void mark_dirty(const basic_bounding_box<graphics_math_type>& extents, error_code& ec) noexcept;
					void paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
					template <class Allocator>
					void stroke(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
					void stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
					template <class Allocator>
					void fill(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
					void fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
					void mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_mask_props<GraphicsSurfaces>>& mp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);

					// display functions
					void draw_callback(const function<void(display_surface& sfc)>& fn);
					void size_change_callback(const function<void(display_surface& sfc)>& fn);
					void dimensions(basic_display_point<graphics_math_type> dp);
					void dimensions(basic_display_point<graphics_math_type> dp, error_code& ec) noexcept;
					void scaling(experimental::io2d::scaling scl) noexcept;
					void user_scaling_callback(const function<basic_bounding_box<graphics_math_type>(const display_surface&, bool&)>& fn);
					void letterbox_brush(const optional<basic_brush<GraphicsSurfaces>>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt) noexcept;
					void letterbox_brush_props(const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept;
					void auto_clear(bool val) noexcept;
					experimental::io2d::format format() const noexcept;
					basic_display_point<graphics_math_type> dimensions() const noexcept;
					experimental::io2d::scaling scaling() const noexcept;
					optional<basic_brush<GraphicsSurfaces>> letterbox_brush() const noexcept;
					optional<basic_brush_props<GraphicsSurfaces>> letterbox_brush_props() const noexcept;
					bool auto_clear() const noexcept;
				};

				template <class GraphicsSurfaces>
				class base_output_surface : public base_display_surface<GraphicsSurfaces> {
				public:
					// System manages event loop
					base_output_surface(int preferredWidth, int preferredHeight,
						io2d::format preferredFormat, io2d::scaling scl = io2d::scaling::letterbox,
						io2d::refresh_rate rr = io2d::refresh_rate::as_fast_as_possible, float fps = 30.0f);
					base_output_surface(int preferredWidth, int preferredHeight,
						io2d::format preferredFormat, error_code& ec,
						io2d::scaling scl = io2d::scaling::letterbox,
						io2d::refresh_rate rr = io2d::refresh_rate::as_fast_as_possible, float fps = 30.0f)
						noexcept;
					base_output_surface(int preferredWidth, int preferredHeight,
						io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight,
						io2d::scaling scl = io2d::scaling::letterbox,
						io2d::refresh_rate rr = io2d::refresh_rate::as_fast_as_possible, float fps = 30.0f);
					base_output_surface(int preferredWidth, int preferredHeight,
						experimental::io2d::format preferredFormat,
						int preferredDisplayWidth, int preferredDisplayHeight, error_code& ec,
						io2d::scaling scl = io2d::scaling::letterbox,
						io2d::refresh_rate rr = io2d::refresh_rate::as_fast_as_possible, float fps = 30.0f)
						noexcept;

					~base_output_surface() noexcept;
					base_output_surface(base_output_surface&&) noexcept = default;
					base_output_surface& operator=(base_output_surface&&) noexcept = default;

					void redraw_required() noexcept;
					typename GraphicsSurfaces::show_return_data_type begin_show();
					void end_show();
				};

				template <class GraphicsSurfaces>
				class base_unmanaged_output_surface : public base_display_surface<GraphicsSurfaces> {
				public:
					// User manages event loop
					base_unmanaged_output_surface(HWND hwnd, HDC hdc, int preferredWidth, int preferredHeight, format preferredFormat);
					~base_unmanaged_output_surface() noexcept;
					base_unmanaged_output_surface(base_unmanaged_output_surface&&) noexcept = default;
					base_unmanaged_output_surface& operator=(base_unmanaged_output_surface&&) noexcept = default;

					typename GraphicsSurfaces::display_surface_data_type& get_data() const noexcept;

					void invoke_draw_callback(const optional<basic_clip_props<GraphicsSurfaces>>& clip);
					void invoke_size_change_callback();
					bool reset_redraw_request() noexcept;
				};
			}
		}
	}
}