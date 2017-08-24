#pragma once

#if !defined _XINCLWINDOWS_H_H_
#define _XINCLWINDOWS_H_H_

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

#include "xcairo.h"

namespace std::experimental::io2d {
	inline namespace v1 {

		namespace windows
		{
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
				struct context
				{
					context(HWND hwnd) : _Hwnd(hwnd), _Hdc(GetDC(hwnd)) {}
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
				int begin_show(display_surface<cairo::cairo_renderer>&);
				void end_show();
				context make_context() const;
				_IO2D_API float elapsed_draw_time() const noexcept;
				_IO2D_API void refresh_rate(experimental::io2d::refresh_rate rr) noexcept;
				_IO2D_API experimental::io2d::refresh_rate refresh_rate() const noexcept;
				_IO2D_API bool desired_frame_rate(float fps) noexcept;
				_IO2D_API float desired_frame_rate() const noexcept;

				static const int _Display_surface_ptr_window_data_byte_offset = 0;

				cairo::cairo_display_surface* _Surface;
				display_surface<cairo::cairo_renderer>* _Display_surface;
				::std::experimental::io2d::refresh_rate _Refresh_rate;
				float _Elapsed_draw_time;
				const float _Minimum_frame_rate = 0.01F;
				const float _Maximum_frame_rate = 120.0F;
				float _Desired_frame_rate;
				DWORD _Window_style;
				HWND _Hwnd;
			};
#endif

			/* Prior implementation from display_surface
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
			friend _IO2D_API LRESULT CALLBACK windows_handler::_RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
			windows_handler _Handler_impl;
			#endif
			*/

		}
	}
}

#endif