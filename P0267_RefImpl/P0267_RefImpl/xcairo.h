#pragma once

#ifndef _XCAIRO_
#define _XCAIRO_

#include <cairo.h>

#include "io2d.h"

namespace std::experimental::io2d {
	inline namespace v1 {

		namespace cairo
		{
			struct _Surface_native_handles;
			class cairo_interpreted_path;
			class cairo_brush;
			class cairo_surface;
			class cairo_display_surface;
			class cairo_image_surface;
			class cairo_mapped_surface;

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
				template <class Allocator>
				explicit cairo_interpreted_path(const path_builder<Allocator>& p);
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

				template <class InputIterator>
				cairo_brush(const circle& start, const circle& end, InputIterator first, InputIterator last);

				cairo_brush(const circle& start, const circle& end, ::std::initializer_list<gradient_stop> il);

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
				bounding_box _Dirty_rect;
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
				_IO2D_API void mark_dirty(const bounding_box& extents);
				_IO2D_API void mark_dirty(const bounding_box& extents, error_code& ec) noexcept;
				_IO2D_API void paint(const cairo_brush& b, const optional<brush_props>& bp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props<cairo_renderer>>& cl = nullopt);
				template <class Allocator>
				void stroke(const cairo_brush& b, const path_builder<Allocator>& pb, const optional<brush_props>& bp = nullopt, const optional<stroke_props>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props<cairo_renderer>>& cl = nullopt);
				_IO2D_API void stroke(const cairo_brush& b, const cairo_interpreted_path& pg, const optional<brush_props>& bp = nullopt, const optional<stroke_props>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props<cairo_renderer>>& cl = nullopt);
				template <class Allocator>
				void fill(const cairo_brush& b, const path_builder<Allocator>& pb, const optional<brush_props>& bp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props<cairo_renderer>>& cl = nullopt);
				_IO2D_API void fill(const cairo_brush& b, const cairo_interpreted_path& pg, const optional<brush_props>& bp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props<cairo_renderer>>& cl = nullopt);
				_IO2D_API void mask(const cairo_brush& b, const cairo_brush& mb, const optional<brush_props>& bp = nullopt, const optional<mask_props>& mp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props<cairo_renderer>>& cl = nullopt);
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
				_IO2D_API void map(const function<void(mapped_surface<cairo_renderer>&)>& action);
				_IO2D_API void map(const function<void(mapped_surface<cairo_renderer>&, error_code&)>& action, error_code& ec);
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
				::std::unique_ptr<::std::function<void(display_surface<cairo_renderer>& sfc)>> _Draw_fn;
				::std::unique_ptr<::std::function<void(display_surface<cairo_renderer>& sfc)>> _Size_change_fn;
				::std::unique_ptr<::std::function<::std::experimental::io2d::bounding_box(const display_surface<cairo_renderer>&, bool&)>> _User_scaling_fn;
				optional<brush_props> _Letterbox_brush_props;
				typedef bool _Auto_clear_type;
				bool _Auto_clear;
				bool _Redraw_requested;
				::std::unique_ptr<cairo_surface_t, ::std::function<void(cairo_surface_t*)>> _Native_surface;
				::std::unique_ptr<cairo_t, ::std::function<void(cairo_t*)>> _Native_context;
				optional<cairo_brush> _Letterbox_brush;
				cairo_brush _Default_brush;

				void _Render_to_native_surface(display_point dd, display_surface<cairo_renderer>&);
				void _Render_to_native_surface(display_point dd, display_surface<cairo_renderer>&, ::std::error_code& ec) noexcept;
				void _Render_for_scaling_uniform_or_letterbox(display_point dd);
				void _Render_for_scaling_uniform_or_letterbox(display_point dd, ::std::error_code& ec) noexcept;

			public:
				const auto& _Native_handle() const { return _Cairo_surface->_Native_handle(); }

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
				_IO2D_API void draw_callback(const function<void(display_surface<cairo_renderer>& sfc)>& fn);
				_IO2D_API void invoke_draw_callback(display_point dp, display_surface<cairo_renderer>& ds);
				_IO2D_API void size_change_callback(const function<void(display_surface<cairo_renderer>& sfc)>& fn);
				_IO2D_API void invoke_size_change_callback(display_surface<cairo_renderer>& ds);
				_IO2D_API void dimensions(display_point dp);
				_IO2D_API void dimensions(display_point dp, error_code& ec) noexcept;
				_IO2D_API void scaling(experimental::io2d::scaling scl) noexcept;
				_IO2D_API void user_scaling_callback(const function<experimental::io2d::bounding_box(const display_surface<cairo_renderer>&, bool&)>& fn);
				_IO2D_API void letterbox_brush(const optional<cairo_brush>& b, const optional<brush_props> = nullopt) noexcept;
				_IO2D_API void auto_clear(bool val) noexcept;
				_IO2D_API void redraw_required() noexcept;
				_IO2D_API bool reset_redraw_request() noexcept;
				_IO2D_API experimental::io2d::format format() const noexcept;
				_IO2D_API display_point dimensions() const noexcept;
				_IO2D_API experimental::io2d::scaling scaling() const noexcept;
				_IO2D_API function<experimental::io2d::bounding_box(const display_surface<cairo_renderer>&, bool&)> user_scaling_callback() const;
				_IO2D_API function<experimental::io2d::bounding_box(const display_surface<cairo_renderer>&, bool&)> user_scaling_callback(error_code& ec) const noexcept;
				_IO2D_API optional<cairo_brush> letterbox_brush() const noexcept;
				_IO2D_API optional<brush_props> letterbox_brush_props() const noexcept;
				_IO2D_API bool auto_clear() const noexcept;
			};

			class cairo_mapped_surface
			{
				friend mapped_surface<cairo_renderer>;

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

#include "xcairo_impl.h"

#endif