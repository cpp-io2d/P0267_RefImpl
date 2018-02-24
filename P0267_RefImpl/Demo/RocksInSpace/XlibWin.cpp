#include "XlibWin.h"
#include <iostream>

namespace rocks_in_space
{
	inline XlibWin::XlibWin(int w, int h, format fmt, scaling scl)
		: m_display(::std::move(::std::unique_ptr<Display, decltype(&XCloseDisplay)>(XOpenDisplay(nullptr),
			&XCloseDisplay)))
		, m_canDraw(false)
		, m_x(0)
		, m_y(0)
		, m_w(w)
		, m_h(h)
		, m_borderWidth(4)
		, m_screenNumber(DefaultScreen(m_display.get()))
		, m_fmt(fmt)
		, m_scl(scl)
		, m_game()
		, m_wndw()
		, m_uosfc(::std::move(default_graphics_surfaces::surfaces::create_unmanaged_output_surface()))
	{
	}

	int XlibWin::Run()
	{
		Display* display = m_display.get();
		Atom wmDeleteWndw = XInternAtom(display, "WM_DELETE_WINDOW", False);
		XSetWindowAttributes xswa{};
		m_wndw = XCreateWindow(display, RootWindow(display, m_screenNumber), m_x, m_y, m_w, m_h, m_borderWidth, CopyFromParent, InputOutput, CopyFromParent, 0, &xswa);
		XSelectInput(display, m_wndw, ExposureMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask);
		XSetWMProtocols(display, m_wndw, &wmDeleteWndw, 1);
		XMapWindow(display, m_wndw);

		bool exit = false;
		XEvent xev{};

		while (!exit) {
			while (XCheckIfEvent(display, &xev, &_X11_if_xev_pred, reinterpret_cast<XPointer>(this))) {
				switch (xev.type) {

					// ExposureMask events:
				case Expose:
				{
					m_canDraw = false;
					assert(m_wndw != None && "m_wndw == None?");
					m_uosfc = ::std::move(unmanaged_output_surface(::std::move(default_graphics_surfaces::surfaces::create_unmanaged_output_surface(display, m_wndw, m_w, m_h, m_fmt, m_scl))));
					m_canDraw = true;
					m_uosfc.draw_callback([&](unmanaged_output_surface& uos) { m_game.update<unmanaged_output_surface>(uos); });
					m_uosfc.clear();
					m_uosfc.invoke_draw_callback();
					m_uosfc.draw_to_output();
				} break;

				// StructureNotifyMask events:
				case CirculateNotify:
				{
				} break;
				case ConfigureNotify:
				{
					m_w = xev.xconfigure.width;
					m_h = xev.xconfigure.height;
					if (m_canDraw) {
						m_uosfc.display_dimensions(display_point{ m_w, m_h });
					}
				} break;
				case DestroyNotify:
				{
					exit = true;
				} break;
				case GravityNotify:
				{
				} break;
				case MapNotify:
				{
					// After the window is mapped, and Expose event will be generated once the window is ACTUALLY ready to be drawn to. As such we do nothing here.
				} break;
				case ReparentNotify:
				{
				} break;
				case UnmapNotify:
				{
					// The window still exists, it has just been unmapped.
					m_canDraw = false;
				} break;
				// Might get them even though they are unrequested events (see http://www.x.org/releases/X11R7.7/doc/libX11/libX11/libX11.html#Event_Masks ):
				case GraphicsExpose:
				{
					if (m_canDraw) {
						m_uosfc.clear();
						m_uosfc.invoke_draw_callback();
						m_uosfc.draw_to_output();
					}
				} break;
				case NoExpose:
				{
				} break;

				// KeyPressed event KeyReleased event
				case KeyPress:
				{
					// namespace
					// {
					// 	auto anti_clockwise_key = 'Q';
					// 	auto clockwise_key = 'W';
					// 	auto thrust_key = 'U';
					// 	auto fire_key = 'I';
					// 	auto hyperspace_key = 'O';
					// }
					auto keySym = XKeycodeToKeysym(display, xev.xkey.keycode, 0);
					const bool pressedState = true;
					switch (keySym)
					{
					case XK_q:
					{
						press().anti_clockwise_key_press = pressedState;
					} break;
					case XK_w:
					{
						press().clockwise_key_press = pressedState;
					} break;
					case XK_u:
					{
						press().thrust_key_press = pressedState;
					} break;
					case XK_i:
					{
						press().fire_key_press = pressedState;
					} break;
					case XK_o:
					{
						press().hyperspace_key_press = pressedState;
					} break;
					default:
					{
						// Do nothing.
					} break;
					}
				} break;
				case KeyRelease:
				{
					// namespace
					// {
					// 	auto anti_clockwise_key = 'Q';
					// 	auto clockwise_key = 'W';
					// 	auto thrust_key = 'U';
					// 	auto fire_key = 'I';
					// 	auto hyperspace_key = 'O';
					// }
					auto keySym = XKeycodeToKeysym(display, xev.xkey.keycode, 0);
					const bool pressedState = false;
					switch (keySym)
					{
					case XK_q:
					{
						press().anti_clockwise_key_press = pressedState;
					} break;
					case XK_w:
					{
						press().clockwise_key_press = pressedState;
					} break;
					case XK_u:
					{
						press().thrust_key_press = pressedState;
					} break;
					case XK_i:
					{
						press().fire_key_press = pressedState;
					} break;
					case XK_o:
					{
						press().hyperspace_key_press = pressedState;
					} break;
					default:
					{
						// Do nothing.
					} break;
					}
				} break;

				// Unmasked events
				case ClientMessage:
				{
					if (xev.xclient.format == 32 && static_cast<Atom>(xev.xclient.data.l[0]) == wmDeleteWndw) {
						m_canDraw = false;
						XDestroyWindow(display, m_wndw);
						m_wndw = None;
						exit = true;
					}
				} break;
				case MappingNotify:
				{
				} break;
				case SelectionClear:
				{
				} break;
				case SelectionNotify:
				{
				} break;
				case SelectionRequest:
				{
				} break;
				default:
				{
					// stringstream errorString;
					// errorString << "Unexpected xev.type. Value is '" << xev.type << "'.";
					// cerr << errorString.str().c_str();
					// assert(xev.type >= 64 && xev.type <= 127);
				} break;
				}
				continue;
			}
			if (m_canDraw) {
				m_uosfc.clear();
				m_uosfc.invoke_draw_callback();
				m_uosfc.draw_to_output();
			}
		}
		return 0;
	}

	Window XlibWin::get_window() const noexcept {
		return m_wndw;
	}

	Bool _X11_if_xev_pred(::Display* display, ::XEvent* xev, XPointer arg) {
		assert(display != nullptr && xev != nullptr && arg != nullptr);
		auto win = reinterpret_cast<XlibWin*>(arg);

		// If the display_surface window is invalid, we will never get a match so return False.
		if (win->get_window() == None) {
			return False;
		}
		// Need to check for ExposureMask xevs, StructureNotifyMask xevs, and unmaskable xevs.
		switch (xev->type) {
			// ExposureMask xevs:
		case Expose:
		{
			if (xev->xexpose.window == win->get_window()) {
				return True;
			}
		} break;
		// StructureNotifyMask xevs:
		case CirculateNotify:
		{
			if (xev->xcirculate.window == win->get_window()) {
				return True;
			}
		} break;
		case ConfigureNotify:
		{
			if (xev->xconfigure.window == win->get_window()) {
				return True;
			}
		} break;
		case DestroyNotify:
		{
			if (xev->xdestroywindow.window == win->get_window()) {
				return True;
			}
		} break;
		case GravityNotify:
		{
			if (xev->xgravity.window == win->get_window()) {
				return True;
			}
		} break;
		case MapNotify:
		{
			if (xev->xmap.window == win->get_window()) {
				return True;
			}
		} break;
		case ReparentNotify:
		{
			if (xev->xreparent.window == win->get_window()) {
				return True;
			}
		} break;
		case UnmapNotify:
		{
			if (xev->xunmap.window == win->get_window()) {
				return True;
			}
		} break;
		// Might get them even though unrequested xevs (see http://www.x.org/releases/X11R7.7/doc/libX11/libX11/libX11.html#Event_Masks ):
		case GraphicsExpose:
		{
			if (xev->xgraphicsexpose.drawable == static_cast<Drawable>(win->get_window())) {
				return True;
			}
		} break;
		case NoExpose:
		{
			if (xev->xnoexpose.drawable == static_cast<Drawable>(win->get_window())) {
				return True;
			}
		} break;
		// Key events
		case KeyPress:
		{
			if (xev->xkey.window == static_cast<Drawable>(win->get_window())) {
				return True;
			}
		} break;
		case KeyRelease:
		{
			if (xev->xkey.window == static_cast<Drawable>(win->get_window())) {
				return True;
			}
		} break;
		// Unmasked xevs
		case ClientMessage:
		{
			if (xev->xclient.window == win->get_window()) {
				return True;
			}
		} break;
		case MappingNotify:
		{
			if (xev->xmapping.window == win->get_window()) {
				return True;
			}
		} break;
		case SelectionClear:
		{
			if (xev->xselectionclear.window == win->get_window()) {
				return True;
			}
		} break;
		case SelectionNotify:
		{
			if (xev->xselection.requestor == win->get_window()) {
				return True;
			}
		} break;
		case SelectionRequest:
		{
			if (xev->xselectionrequest.owner == win->get_window()) {
				return True;
			}
		} break;
		default:
		{
			// Per the X protocol, types 64 through 127 are reserved for extensions.
			// We only care about non-extension xevs since we likely should be aware of those and should handle them.
			// So we only return True if it is not an extension xev.
			if (xev->type < 64 || xev->type > 127) {
				// Return True so we can inspect it in the xev loop for diagnostic purposes.
				return True;
			}
			::std::cerr << "Ignored event of type '" << xev->type << "'." << ::std::endl;
			return false;
		} break;
		}
		return False;
	}

	inline void get_key_states() {
	}
}

int x_error_handler(Display* dpy, XErrorEvent* evt)
{
	const int buffLength = 1024;
	char errorText[buffLength] = {};
	XGetErrorText(evt->display, evt->error_code, errorText, buffLength);
	::std::cerr << "Error encountered with error_code'" << static_cast<int>(evt->error_code) << "', serial number '" << static_cast<int>(evt->serial) << "', opcode '"
		<< static_cast<int>(evt->request_code) << "', and minor opcode '" << static_cast<int>(evt->minor_code) << "'."
		<< ::std::endl << "Error text is: '" << errorText << "'." << ::std::endl;
	return static_cast<int>(evt->error_code);
}

int main()
{
	//XSetErrorHandler(&x_error_handler);
	rocks_in_space::XlibWin win(640, 480, rocks_in_space::format::argb32, rocks_in_space::scaling::letterbox);
	return win.Run();
}
