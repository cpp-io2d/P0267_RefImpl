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
			struct windows_handler_impl
			{
				struct context
				{
					context(HWND hwnd) : _Hwnd(hwnd), _Hdc(GetDC(hwnd)) {}
					~context() { ReleaseDC(_Hwnd, _Hdc); }
					operator HDC() { return _Hdc; }
					HWND _Hwnd;
					HDC _Hdc;
				};

				windows_handler_impl(experimental::io2d::refresh_rate rr = io2d::refresh_rate::as_fast_as_possible, float fps = 30.0f);
				~windows_handler_impl();
				void resize_window(LONG width, LONG height) const;
				context make_context() const;
				float elapsed_draw_time() const noexcept;
				void refresh_rate(experimental::io2d::refresh_rate rr) noexcept;
				experimental::io2d::refresh_rate refresh_rate() const noexcept;
				bool desired_frame_rate(float fps) noexcept;
				float desired_frame_rate() const noexcept;

				static const int _Display_surface_ptr_window_data_byte_offset = 0;

				::std::experimental::io2d::refresh_rate _Refresh_rate;
				float _Elapsed_draw_time;
				const float _Minimum_frame_rate = 0.01F;
				const float _Maximum_frame_rate = 120.0F;
				float _Desired_frame_rate;
				DWORD _Window_style;
				HWND _Hwnd;
			};

			template <class T>
			class windows_handler
			{
				static once_flag _Window_class_registered_flag;
				static const wchar_t* _Refimpl_window_class_name;

				LRESULT _Window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

				display_surface<T>& _Display_surface;
				windows_handler_impl _Impl;
			public:
				static LRESULT CALLBACK _RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

				windows_handler(display_surface<T>& ds, experimental::io2d::refresh_rate rr = io2d::refresh_rate::as_fast_as_possible, float fps = 30.0f);
				void resize_window(LONG width, LONG height) const;
				windows_handler_impl::context make_context() const;
				int begin_show();
				void end_show();
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
			friend _IO2D_API LRESULT CALLBACK windows_handler_impl::_RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
			windows_handler_impl _Handler_impl;
			#endif
			*/

		}
	}
}

#include "xwindows_handler_impl.h"

#endif