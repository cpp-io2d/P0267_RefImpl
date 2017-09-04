#pragma once

#include "xcairo.h"
#include "xinclwindows_h.h"

namespace rocks_in_space
{
	using namespace std::experimental::io2d;
	using my_renderer = cairo::cairo_renderer;
	using my_handler = windows::windows_handler<my_renderer>;	// Here is the problem: how do we make this a friend of display_surface<my_renderer>?
	using my_display_surface = display_surface<my_renderer>;
	using my_brush = brush<my_renderer>;
}
