#pragma once

#ifndef _XCAIRO_
#define _XCAIRO_

#include <cairo.h>

#if defined(USE_XCB)
#include <xcb/xcb.h>
#elif defined(USE_XLIB)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#elif defined(_WIN32) || defined(_WIN64)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

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

#if defined(USE_XCB)
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
#elif defined(_WIN32) || defined(_WIN64)
			struct windows_handler
			{
				struct _Display_surface_native_handle {
					_Surface_native_handles sfc_nh;
					HWND hwnd;
					_Surface_native_handles win32_sfc_nh;
				};

				struct context
				{
					context(HWND _Hwnd) : _Hdc(GetDC(_Hwnd)) {}
					~context() { ReleaseDC(_Hwnd, _Hdc); }
					operator HDC() { return _Hdc; }
					HWND _Hwnd;
					HDC _Hdc;
				};

				_IO2D_API static LRESULT CALLBACK _RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

				windows_handler(experimental::io2d::refresh_rate rr = io2d::refresh_rate::as_fast_as_possible, float fps = 30.0f);
				~windows_handler();
				LRESULT _Window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
				void resize_window(LONG width, LONG height) const;
				int begin_show(display_surface<cairo_renderer>&);
				void end_show();
				context make_context() const;
				_IO2D_API float elapsed_draw_time() const noexcept;
				_IO2D_API void refresh_rate(experimental::io2d::refresh_rate rr) noexcept;
				_IO2D_API experimental::io2d::refresh_rate refresh_rate() const noexcept;
				_IO2D_API bool desired_frame_rate(float fps) noexcept;
				_IO2D_API float desired_frame_rate() const noexcept;

				static const int _Display_surface_ptr_window_data_byte_offset = 0;

				cairo_display_surface* _Surface;
				display_surface<cairo_renderer>* _Display_surface;
				::std::experimental::io2d::refresh_rate _Refresh_rate;
				float _Elapsed_draw_time;
				const float _Minimum_frame_rate = 0.01F;
				const float _Maximum_frame_rate = 120.0F;
				float _Desired_frame_rate;
				DWORD _Window_style;
				HWND _Hwnd;
			};
#endif

			class cairo_display_surface
			{
				friend windows_handler;
				cairo_surface* _Cairo_surface;
				int _Display_width;
				int _Display_height;
				::std::experimental::io2d::scaling _Scaling;
				int _Width;
				int _Height;
				::std::unique_ptr<::std::function<void(display_surface<cairo_renderer>& sfc)>> _Draw_fn;
				::std::unique_ptr<::std::function<void(display_surface<cairo_renderer>& sfc)>> _Size_change_fn;
				::std::unique_ptr<::std::function<::std::experimental::io2d::bounding_box(const display_surface<cairo_renderer>&, bool&)>> _User_scaling_fn;
				optional<brush_props> _Letterbox_brush_props;
				typedef bool _Auto_clear_type;
				bool _Auto_clear;

/*#if defined(USE_XCB)
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
#elif  defined(_WIN32) || (_WIN64)
				friend _IO2D_API LRESULT CALLBACK windows_handler::_RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
				windows_handler _Handler_impl;
#endif*/
				bool _Redraw_requested;
				::std::unique_ptr<cairo_surface_t, ::std::function<void(cairo_surface_t*)>> _Native_surface;
				::std::unique_ptr<cairo_t, ::std::function<void(cairo_t*)>> _Native_context;
				optional<cairo_brush> _Letterbox_brush;
				cairo_brush _Default_brush;

				template <class T>
				void _Make_native_surface_and_context(T&&);
				template <class T>
				void _Make_native_surface_and_context(T&&, ::std::error_code& ec) noexcept;
				void _Make_impl_surface_and_context();
				void _Render_to_native_surface(display_surface<cairo_renderer>&);
				void _Render_to_native_surface(display_surface<cairo_renderer>&, ::std::error_code& ec) noexcept;
				void _Render_for_scaling_uniform_or_letterbox();
				void _Render_for_scaling_uniform_or_letterbox(::std::error_code& ec) noexcept;

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
				_IO2D_API cairo_display_surface(cairo_surface* cs, int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, io2d::scaling scl = io2d::scaling::letterbox);
				cairo_display_surface(cairo_surface* cs, int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, error_code& ec, io2d::scaling scl = io2d::scaling::letterbox) noexcept;
				~cairo_display_surface() {}
				_IO2D_API void draw_callback(const function<void(display_surface<cairo_renderer>& sfc)>& fn);
				_IO2D_API void size_change_callback(const function<void(display_surface<cairo_renderer>& sfc)>& fn);
				_IO2D_API void width(int w);
				_IO2D_API void width(int w, error_code& ec) noexcept;
				_IO2D_API void height(int h);
				_IO2D_API void height(int h, error_code& ec) noexcept;
				template <class T>
				void display_width(const T& handler, int w);
				template <class T>
				void display_width(const T& handler, int w, error_code& ec) noexcept;
				template <class T>
				void display_height(const T& handler, int h);
				template <class T>
				void display_height(const T& handler, int h, error_code& ec) noexcept;
				_IO2D_API void dimensions(int w, int h);
				_IO2D_API void dimensions(int w, int h, error_code& ec) noexcept;
				template <class T>
				void display_dimensions(const T& handler, int dw, int dh);
				template <class T>
				void display_dimensions(const T& handler, int dw, int dh, error_code& ec) noexcept;
				_IO2D_API void scaling(experimental::io2d::scaling scl) noexcept;
				_IO2D_API void user_scaling_callback(const function<experimental::io2d::bounding_box(const display_surface<cairo_renderer>&, bool&)>& fn);
				_IO2D_API void letterbox_brush(const optional<cairo_brush>& b, const optional<brush_props> = nullopt) noexcept;
				_IO2D_API void auto_clear(bool val) noexcept;
				_IO2D_API void redraw_required() noexcept;
				template <class T>
				int begin_show(const T&);
				template <class T>
				void end_show(const T&);
				_IO2D_API experimental::io2d::format format() const noexcept;
				_IO2D_API int width() const noexcept;
				_IO2D_API int height() const noexcept;
				_IO2D_API int display_width() const noexcept;
				_IO2D_API int display_height() const noexcept;
				_IO2D_API point_2d dimensions() const noexcept;
				_IO2D_API point_2d display_dimensions() const noexcept;
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