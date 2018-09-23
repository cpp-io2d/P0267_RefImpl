#pragma once

#include "Game.h"

namespace rocks_in_space
{
	using scaling =				::std::experimental::io2d::scaling;
	using format = 				::std::experimental::io2d::format;
	using default_graphics_surfaces =	::std::experimental::io2d::default_graphics_surfaces;
	using display_point =		::std::experimental::io2d::display_point;

	Bool _X11_if_xev_pred(::Display* display, ::XEvent* xev, XPointer arg);
		
	class XlibWin
	{
	public:
		XlibWin(int w, int h, format fmt, scaling scl);

		int Run();

		Window get_window() const noexcept;
	private:
		::std::unique_ptr<Display, decltype(&XCloseDisplay)> m_display{ nullptr, &XCloseDisplay };

		bool									m_canDraw = false;
		int										m_x = 0;
		int										m_y = 0;
		int										m_w = 640;
		int										m_h = 480;
		int										m_borderWidth = 4;
		int										m_screenNumber;
		format									m_fmt;
		scaling									m_scl;

		game									m_game;
		Window									m_wndw;
		unmanaged_output_surface				m_uosfc;
	};
}
