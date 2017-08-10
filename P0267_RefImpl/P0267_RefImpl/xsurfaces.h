#pragma once

#if defined(USE_XCB)
#include <xcb/xcb.h>
#elif defined(USE_XLIB)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#elif defined(_WIN32) || defined(_WIN64)
#include "xinclwindows_h.h"
#endif

namespace std::experimental::io2d {
	inline namespace v1 {

		enum class antialias {
			none,
			fast,
			good,
			best
		};

		enum class fill_rule {
			winding,
			even_odd
		};

		enum class line_cap {
			none,
			round,
			square
		};

		enum class line_join {
			miter,
			round,
			bevel
		};

		enum class compositing_op {
			over,
			clear,
			source,
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
			hsl_luminosity
		};

		enum class format {
			invalid,
			argb32,
			rgb24,
			a8,
			rgb16_565,
			rgb30
		};

		enum class scaling {
			letterbox,      // Same as uniform except that the display_surface is cleared using the letterbox brush first
			uniform,        // Maintain aspect ratio and center as needed, ignoring side areas that are not drawn to
			fill_uniform,   // Maintain aspect ratio but fill entire display (some content may not be shown)
			fill_exact,     // Ignore aspect ratio and use (possibly non-uniform) scale to fill exactly
			none            // Do not scale.
		};

		enum class refresh_rate {
			as_needed,
			as_fast_as_possible,
			fixed
		};

		enum class image_file_format {
			unknown,
			png,
			jpeg,
			tiff
		};

		class render_props {
			antialias _Antialiasing = antialias::good;
			matrix_2d _Matrix;// = matrix_2d::init_identity(); // Transformation matrix
			compositing_op _Compositing = compositing_op::over;
		public:
			constexpr render_props() noexcept;
			constexpr explicit render_props(antialias a, const matrix_2d& m = matrix_2d{}, compositing_op co = compositing_op::over) noexcept;
			constexpr void antialiasing(antialias a) noexcept;
			constexpr void compositing(compositing_op co) noexcept;
			constexpr void surface_matrix(const matrix_2d& m) noexcept;
			constexpr antialias antialiasing() const noexcept;
			constexpr compositing_op compositing() const noexcept;
			constexpr matrix_2d surface_matrix() const noexcept;
		};

		class brush_props {
			experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::none;
			experimental::io2d::filter _Filter = experimental::io2d::filter::bilinear;
			experimental::io2d::fill_rule _Fill_rule = experimental::io2d::fill_rule::winding;
			matrix_2d _Matrix;

		public:
			// suprlus to paper
			constexpr brush_props() noexcept;

			constexpr brush_props(io2d::wrap_mode w = io2d::wrap_mode::none, io2d::filter fi = io2d::filter::good, io2d::fill_rule fr = io2d::fill_rule::winding, matrix_2d m = matrix_2d{}) noexcept;
			constexpr void filter(io2d::filter fi) noexcept;
			constexpr void wrap_mode(io2d::wrap_mode w) noexcept;
			constexpr void fill_rule(io2d::fill_rule fr) noexcept;
			constexpr void brush_matrix(const matrix_2d& m) noexcept;
			constexpr io2d::filter filter() const noexcept;
			constexpr io2d::wrap_mode wrap_mode() const noexcept;
			constexpr io2d::fill_rule fill_rule() const noexcept;
			constexpr matrix_2d brush_matrix() const noexcept;
		};

		class clip_props {
			interpreted_path _Clip;
			experimental::io2d::fill_rule _Fill_rule = experimental::io2d::fill_rule::winding;
		public:
			// suprlus to paper
			explicit clip_props(const bounding_box& r, experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding);

			clip_props() noexcept = default;
			template <class Allocator>
			explicit clip_props(const path_builder<Allocator>& pb, experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding);
			explicit clip_props(const interpreted_path& pg, experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding) noexcept;
			template <class Allocator>
			void clip(const path_builder<Allocator>& pb);
			void clip(const interpreted_path& pg) noexcept;
			void fill_rule(experimental::io2d::fill_rule fr) noexcept;
			interpreted_path clip() const noexcept;
			experimental::io2d::fill_rule fill_rule() const noexcept;
		};

		class stroke_props {
			float _Line_width = 2.0F;
			float _Miter_limit = 10.0F;
			experimental::io2d::line_cap _Line_cap = experimental::io2d::line_cap::none;
			experimental::io2d::line_join _Line_join = experimental::io2d::line_join::miter;
			//optional<dashes> _Dashes;
		public:
			constexpr stroke_props() noexcept;
			constexpr explicit stroke_props(float w, io2d::line_cap lc = io2d::line_cap::none, io2d::line_join lj = io2d::line_join::miter, float ml = 10.0f) noexcept;
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

		class mask_props {
			experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::repeat;
			experimental::io2d::filter _Filter = experimental::io2d::filter::good;
			matrix_2d _Matrix = matrix_2d{};

		public:
			// suprlus to paper
			constexpr mask_props(const mask_props&) noexcept = default;
			constexpr mask_props& operator=(const mask_props&) noexcept = default;
			mask_props(mask_props&&) noexcept = default;
			mask_props& operator=(mask_props&&) noexcept = default;

			constexpr mask_props(experimental::io2d::wrap_mode w = experimental::io2d::wrap_mode::repeat, experimental::io2d::filter fi = experimental::io2d::filter::good, matrix_2d m = matrix_2d{}) noexcept;
			constexpr void wrap_mode(experimental::io2d::wrap_mode w) noexcept;
			constexpr void filter(experimental::io2d::filter fi) noexcept;
			constexpr void mask_matrix(const matrix_2d& m) noexcept;
			constexpr experimental::io2d::wrap_mode wrap_mode() const noexcept;
			constexpr experimental::io2d::filter filter() const noexcept;
			constexpr matrix_2d mask_matrix() const noexcept;
		};

		struct _Surface_native_handles {
			::cairo_surface_t* csfce;
			::cairo_t* cctxt;
		};

		class mapped_surface;

		//tuple<dashes, offset>
		typedef ::std::tuple<::std::vector<float>, float> dashes;

		class surface {
		public:
			typedef _Surface_native_handles native_handle_type;
		protected:
			::std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> _Surface;
			::std::unique_ptr<cairo_t, decltype(&cairo_destroy)> _Context;

			const float _Line_join_miter_miter_limit = 10000.0F;

			bounding_box _Dirty_rect;
			::std::experimental::io2d::format _Format;

			_IO2D_API surface(::std::experimental::io2d::format fmt, int width, int height);

			_IO2D_API surface(native_handle_type nh, ::std::experimental::io2d::format fmt);
		protected:
			surface(surface&& other) noexcept = default;
			surface& operator=(surface&& other) noexcept = default;

		public:
			// surplus to paper
			_IO2D_API native_handle_type native_handle() const;
			_IO2D_API void clear();

			surface() = delete;
			_IO2D_API void flush();
			_IO2D_API void flush(error_code& ec) noexcept;
			_IO2D_API void mark_dirty();
			void mark_dirty(error_code& ec) noexcept;
			_IO2D_API void mark_dirty(const bounding_box& extents);
			void mark_dirty(const bounding_box& extents, error_code& ec) noexcept;
			_IO2D_API void paint(const brush& b, const optional<brush_props>& bp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props>& cl = nullopt);
			template <class Allocator>
			void stroke(const brush& b, const path_builder<Allocator>& pb, const optional<brush_props>& bp = nullopt, const optional<stroke_props>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props>& cl = nullopt);
			_IO2D_API void stroke(const brush& b, const interpreted_path& pg, const optional<brush_props>& bp = nullopt, const optional<stroke_props>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props>& cl = nullopt);
			template <class Allocator>
			void fill(const brush& b, const path_builder<Allocator>& pb, const optional<brush_props>& bp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props>& cl = nullopt);
			_IO2D_API void fill(const brush& b, const interpreted_path& pg, const optional<brush_props>& bp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props>& cl = nullopt);

			// Broken R6 - removed unused path from mask but forgot to eliminate this overload:
			//template <class Allocator>
			//void mask(const brush& b, const brush& mb, const optional<brush_props>& bp = nullopt, const optional<mask_props>& mp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props>& cl = nullopt);

			_IO2D_API void mask(const brush& b, const brush& mb, const optional<brush_props>& bp = nullopt, const optional<mask_props>& mp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props>& cl = nullopt);
		};

		class image_surface : public surface {
			friend surface;
		public:
			// surplus to paper
			_IO2D_API int stride() const noexcept;

			_IO2D_API image_surface(io2d::format fmt, int width, int height);
#ifdef _Filesystem_support_test
			_IO2D_API image_surface(filesystem::path f, image_file_format i, io2d::format fmt);
			_IO2D_API image_surface(filesystem::path f, image_file_format i, io2d::format fmt, error_code& ec) noexcept;
#else
			image_surface(::std::string f, experimental::io2d::format fmt, image_file_format idf);
			image_surface(::std::string f, image_file_format i, io2d::format fmt, error_code& ec) noexcept;
#endif
			image_surface(image_surface&&) = default;
			image_surface& operator=(image_surface&&) = default;
#ifdef _Filesystem_support_test
			void save(filesystem::path p, image_file_format i);
			void save(filesystem::path p, image_file_format i, error_code& ec) noexcept;
#else
			void save(::std::string f, image_file_format i);
			void save(::std::string f, image_file_format i, error_code& ec) noexcept;
#endif
			void map(const function<void(mapped_surface&)>& action);
			void map(const function<void(mapped_surface&, error_code&)>& action, error_code& ec);
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
		struct _Win32_display_surface_native_handle {
			_Surface_native_handles sfc_nh;
			HWND hwnd;
			_Surface_native_handles win32_sfc_nh;
		};

		const int _Display_surface_ptr_window_data_byte_offset = 0;

		_IO2D_API LRESULT CALLBACK _RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
#endif

		class display_surface : public surface {
			friend surface;

			int _Display_width;
			int _Display_height;
			::std::experimental::io2d::scaling _Scaling;
			int _Width;
			int _Height;
			::std::unique_ptr<::std::function<void(display_surface& sfc)>> _Draw_fn;
			::std::unique_ptr<::std::function<void(display_surface& sfc)>> _Size_change_fn;
			::std::unique_ptr<::std::function<::std::experimental::io2d::bounding_box(const display_surface&, bool&)>> _User_scaling_fn;
			optional<brush_props> _Letterbox_brush_props;
			typedef bool _Auto_clear_type;
			bool _Auto_clear;

#if defined(USE_XCB)
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
			friend _IO2D_API LRESULT CALLBACK _RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
			DWORD _Window_style;
			HWND _Hwnd;

			LRESULT _Window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
#endif
			::std::experimental::io2d::refresh_rate _Refresh_rate;
			float _Desired_frame_rate;
			bool _Redraw_requested;
			float _Elapsed_draw_time;
			const float _Minimum_frame_rate = 0.01F;
			const float _Maximum_frame_rate = 120.0F;
			::std::unique_ptr<cairo_surface_t, ::std::function<void(cairo_surface_t*)>> _Native_surface;
			::std::unique_ptr<cairo_t, ::std::function<void(cairo_t*)>> _Native_context;
			optional<experimental::io2d::brush> _Letterbox_brush;
			::std::experimental::io2d::brush _Default_brush;

			void _Make_native_surface_and_context();
			void _Make_native_surface_and_context(::std::error_code& ec) noexcept;
			void _All_dimensions(int w, int h, int dw, int dh);
			void _All_dimensions(int w, int h, int dw, int dh, ::std::error_code& ec) noexcept;
			void _Render_to_native_surface();
			void _Render_to_native_surface(::std::error_code& ec) noexcept;
			void _Resize_window();
			void _Resize_window(::std::error_code& ec) noexcept;
			void _Render_for_scaling_uniform_or_letterbox();
			void _Render_for_scaling_uniform_or_letterbox(::std::error_code& ec) noexcept;

		public:
			// surplus to paper
#ifdef _WIN32_WINNT
			typedef _Win32_display_surface_native_handle native_handle_type;
#elif defined(USE_XCB)
			typedef _Xcb_display_surface_native_handle native_handle_type;
#elif defined(USE_XLIB)
			typedef _Xlib_display_surface_native_handle native_handle_type;
#endif
			_IO2D_API native_handle_type native_handle() const;

			display_surface() = delete;
			display_surface(const display_surface&) = delete;
			display_surface& operator=(const display_surface&) = delete;
			
			// declarations from paper
			display_surface(display_surface&& other) noexcept = default;
			display_surface& operator=(display_surface&& other) noexcept = default;
			_IO2D_API display_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, io2d::scaling scl = io2d::scaling::letterbox, io2d::refresh_rate rr = io2d::refresh_rate::as_fast_as_possible, float fps = 30.0f);
			display_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, error_code& ec, io2d::scaling scl = io2d::scaling::letterbox, io2d::refresh_rate rr = io2d::refresh_rate::as_fast_as_possible, float fps = 30.0f) noexcept;
			_IO2D_API display_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, io2d::scaling scl = io2d::scaling::letterbox, io2d::refresh_rate rr = io2d::refresh_rate::as_fast_as_possible, float fps = 30.0f);
			display_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, error_code& ec, io2d::scaling scl = io2d::scaling::letterbox, io2d::refresh_rate rr = io2d::refresh_rate::as_fast_as_possible, float fps = 30.0f) noexcept;
			_IO2D_API ~display_surface();
			_IO2D_API void draw_callback(const function<void(display_surface& sfc)>& fn);
			_IO2D_API void size_change_callback(const function<void(display_surface& sfc)>& fn);
			_IO2D_API void width(int w);
			_IO2D_API void width(int w, error_code& ec) noexcept;
			_IO2D_API void height(int h);
			_IO2D_API void height(int h, error_code& ec) noexcept;
			_IO2D_API void display_width(int w);
			_IO2D_API void display_width(int w, error_code& ec) noexcept;
			_IO2D_API void display_height(int h);
			_IO2D_API void display_height(int h, error_code& ec) noexcept;
			_IO2D_API void dimensions(int w, int h);
			_IO2D_API void dimensions(int w, int h, error_code& ec) noexcept;
			_IO2D_API void display_dimensions(int dw, int dh);
			_IO2D_API void display_dimensions(int dw, int dh, error_code& ec) noexcept;
			_IO2D_API void scaling(experimental::io2d::scaling scl) noexcept;
			_IO2D_API void user_scaling_callback(const function<experimental::io2d::bounding_box(const display_surface&, bool&)>& fn);
			_IO2D_API void letterbox_brush(const optional<brush>& b, const optional<brush_props> = nullopt) noexcept;
			_IO2D_API void auto_clear(bool val) noexcept;
			_IO2D_API void refresh_rate(experimental::io2d::refresh_rate rr) noexcept;
			_IO2D_API bool desired_frame_rate(float fps) noexcept;
			_IO2D_API void redraw_required() noexcept;
			_IO2D_API int begin_show();
			void end_show();
			_IO2D_API experimental::io2d::format format() const noexcept;
			_IO2D_API int width() const noexcept;
			_IO2D_API int height() const noexcept;
			_IO2D_API int display_width() const noexcept;
			_IO2D_API int display_height() const noexcept;
			_IO2D_API point_2d dimensions() const noexcept;
			_IO2D_API point_2d display_dimensions() const noexcept;
			_IO2D_API experimental::io2d::scaling scaling() const noexcept;
			_IO2D_API function<experimental::io2d::bounding_box(const display_surface&, bool&)> user_scaling_callback() const;
			_IO2D_API function<experimental::io2d::bounding_box(const display_surface&, bool&)> user_scaling_callback(error_code& ec) const noexcept;
			_IO2D_API optional<brush> letterbox_brush() const noexcept;
			_IO2D_API optional<brush_props> letterbox_brush_props() const noexcept;
			_IO2D_API bool auto_clear() const noexcept;
			_IO2D_API experimental::io2d::refresh_rate refresh_rate() const noexcept;
			_IO2D_API float desired_frame_rate() const noexcept;
			_IO2D_API float elapsed_draw_time() const noexcept;
		};

		class mapped_surface {
			surface::native_handle_type _Mapped_surface;
			surface::native_handle_type _Map_of;

			friend image_surface;
			mapped_surface(surface::native_handle_type nh, surface::native_handle_type map_of);
			mapped_surface(surface::native_handle_type nh, surface::native_handle_type map_of, ::std::error_code& ec) noexcept;

		public:
			// surplus to paper
			mapped_surface(const mapped_surface&) = delete;
			mapped_surface& operator=(const mapped_surface&) = delete;
			mapped_surface(mapped_surface&& other) = delete;
			mapped_surface& operator=(mapped_surface&& other) = delete;
			
			mapped_surface() = delete;
			~mapped_surface();
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