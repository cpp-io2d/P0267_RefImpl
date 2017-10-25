#pragma once

#include "GameXlib.h"
#include "Input.h"
#include "Constants.h"
#include <iostream>

namespace
{
	static const rocks_in_space::path_buffer* asteroid_vbs[] = { &rocks_in_space::asteroid::a1, &rocks_in_space::asteroid::a2, &rocks_in_space::asteroid::a3, &rocks_in_space::asteroid::a4 };
}

namespace rocks_in_space
{
	inline game::game(int w, int h, format fmt, scaling scl)
		: m_display(::std::move(::std::unique_ptr<Display, decltype(&XCloseDisplay)>(XOpenDisplay(nullptr),
			&XCloseDisplay)))
		, m_x(0)
		, m_y(0)
		, m_w(w)
		, m_h(h)
		, m_borderWidth(4)
		, m_screenNumber(DefaultScreen(m_display.get()))
		, m_fmt(fmt)
		, m_scl(scl)
		, m_wndw()
		, m_uosfc(::std::move(default_graphics_surfaces::create_unmanaged_output_surface()))
		, m_level(1)
		, m_score(0)
		, m_lives()
		, m_ship(controllable_physics(
			physics(point_2d(playing_field_width / 2, playing_field_height / 2 ), (point_2d( 0, 0))),
			point_2d(0, 0), 0.0 ))
		, m_asteroids()
	    , m_ship_missile_count(0)
        , m_next_ship_missile(0)
        , m_ship_missiles(max_missiles)
        , m_rd()
        , m_gen(m_rd())
        , m_0_to_3(0, 3)
        , m_0_to_1(0, 1)
 
	{
		if (m_display == nullptr) {
			throw ::std::system_error(::std::make_error_code(::std::errc::io_error));
		}
		generate_level();
	}

	int game::run_event_loop()
	{
		Display* display = m_display.get();
		Atom wmDeleteWndw = XInternAtom(display, "WM_DELETE_WINDOW", False);
		// m_wndw = XCreateSimpleWindow(display, RootWindow(display,
		// 	m_screenNumber), m_x, m_y, m_w, m_h, m_borderWidth, WhitePixel(display, 
		// 	m_screenNumber), BlackPixel(display, m_screenNumber));
		XSetWindowAttributes xswa{};
		m_wndw = XCreateWindow(display, RootWindow(display, m_screenNumber), m_x, m_y, m_w, m_h, m_borderWidth, CopyFromParent, InputOutput, CopyFromParent, 0, &xswa);
		XSelectInput(display, m_wndw, ExposureMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask);
		XSetWMProtocols(display, m_wndw, &wmDeleteWndw, 1);
		XMapWindow(display, m_wndw);
// 		m_uosfc = ::std::move(unmanaged_output_surface(
// 			::std::move(default_graphics_surfaces::create_unmanaged_output_surface(display, 
// 			m_wndw, m_w, m_h, m_fmt, m_scl))));
// //		auto& uosd = m_uosfc._Get_data();
// //		auto& data = uosd.data;
	
// 		m_uosfc.draw_callback([&](unmanaged_output_surface& uos) {
// 			update<unmanaged_output_surface>(uos);
// 		});

		bool exit = false;
		bool canDraw = false;
		XEvent xev{};

		while (!exit) {
			while (XCheckIfEvent(display, &xev, &_X11_if_xev_pred, reinterpret_cast<XPointer>(this))) {
				switch (xev.type) {

					// ExposureMask events:
				case Expose:
				{
					canDraw = false;
					assert(m_wndw != None && "m_wndw == None?");
					m_uosfc = ::std::move(unmanaged_output_surface(::std::move(default_graphics_surfaces::create_unmanaged_output_surface(display, m_wndw, m_w, m_h, m_fmt, m_scl))));
					canDraw = true;
					m_uosfc.draw_callback([&](unmanaged_output_surface& uos) { update<unmanaged_output_surface>(uos); });
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
					if (canDraw) {
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
					canDraw = false;
				} break;
				// Might get them even though they are unrequested events (see http://www.x.org/releases/X11R7.7/doc/libX11/libX11/libX11.html#Event_Masks ):
				case GraphicsExpose:
				{
					if (canDraw) {
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
						canDraw = false;
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
			if (canDraw) {
				m_uosfc.clear();
				m_uosfc.invoke_draw_callback();
				m_uosfc.draw_to_output();
			}
		}
		return 0;
	}

	Window game::get_window() const noexcept {
		return m_wndw;
	}

	Bool _X11_if_xev_pred(::Display* display, ::XEvent* xev, XPointer arg) {
		assert(display != nullptr && xev != nullptr && arg != nullptr);
		auto sfc = reinterpret_cast<game*>(arg);

		// If the display_surface window is invalid, we will never get a match so return False.
		if (sfc->get_window() == None) {
			return False;
		}
		// Need to check for ExposureMask xevs, StructureNotifyMask xevs, and unmaskable xevs.
		switch (xev->type) {
			// ExposureMask xevs:
		case Expose:
		{
			if (xev->xexpose.window == sfc->get_window()) {
				return True;
			}
		} break;
		// StructureNotifyMask xevs:
		case CirculateNotify:
		{
			if (xev->xcirculate.window == sfc->get_window()) {
				return True;
			}
		} break;
		case ConfigureNotify:
		{
			if (xev->xconfigure.window == sfc->get_window()) {
				return True;
			}
		} break;
		case DestroyNotify:
		{
			if (xev->xdestroywindow.window == sfc->get_window()) {
				return True;
			}
		} break;
		case GravityNotify:
		{
			if (xev->xgravity.window == sfc->get_window()) {
				return True;
			}
		} break;
		case MapNotify:
		{
			if (xev->xmap.window == sfc->get_window()) {
				return True;
			}
		} break;
		case ReparentNotify:
		{
			if (xev->xreparent.window == sfc->get_window()) {
				return True;
			}
		} break;
		case UnmapNotify:
		{
			if (xev->xunmap.window == sfc->get_window()) {
				return True;
			}
		} break;
		// Might get them even though unrequested xevs (see http://www.x.org/releases/X11R7.7/doc/libX11/libX11/libX11.html#Event_Masks ):
		case GraphicsExpose:
		{
			if (xev->xgraphicsexpose.drawable == static_cast<Drawable>(sfc->get_window())) {
				return True;
			}
		} break;
		case NoExpose:
		{
			if (xev->xnoexpose.drawable == static_cast<Drawable>(sfc->get_window())) {
				return True;
			}
		} break;
		// Key events
		case KeyPress:
		{
			if (xev->xkey.window == static_cast<Drawable>(sfc->get_window())) {
				return True;
			}
		} break;
		case KeyRelease:
		{
			if (xev->xkey.window == static_cast<Drawable>(sfc->get_window())) {
				return True;
			}
		} break;
		// Unmasked xevs
		case ClientMessage:
		{
			if (xev->xclient.window == sfc->get_window()) {
				return True;
			}
		} break;
		case MappingNotify:
		{
			if (xev->xmapping.window == sfc->get_window()) {
				return True;
			}
		} break;
		case SelectionClear:
		{
			if (xev->xselectionclear.window == sfc->get_window()) {
				return True;
			}
		} break;
		case SelectionNotify:
		{
			if (xev->xselection.requestor == sfc->get_window()) {
				return True;
			}
		} break;
		case SelectionRequest:
		{
			if (xev->xselectionrequest.owner == sfc->get_window()) {
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

	void game::generate_level()
	{
		auto count = m_level * 2 + 2;
		std::uniform_int_distribution<> edge(1, 4);
		std::uniform_real_distribution<float> x(0.0F, playing_field_width);
		std::uniform_real_distribution<float> y(0.0F, playing_field_height);
		std::uniform_real_distribution<float> theta(0.0F, tau<float>);

		m_asteroids.clear();
		m_asteroids.reserve(count * 7);

		while (count-- != 0)
		{
			switch (edge(m_gen))
			{
			case 1:	m_asteroids.emplace_back(physics{ point_2d{ 0.0F, y(m_gen) },					pol_to_car(polar_2d{ initial_speed, theta(m_gen) }) }, path_from_prototype(*asteroid_vbs[m_0_to_3(m_gen)], big_asteroid_size), big_asteroid_size); break;
			case 2:	m_asteroids.emplace_back(physics{ point_2d{ playing_field_width, y(m_gen) },	pol_to_car(polar_2d{ initial_speed, theta(m_gen) }) }, path_from_prototype(*asteroid_vbs[m_0_to_3(m_gen)], big_asteroid_size), big_asteroid_size); break;
			case 3:	m_asteroids.emplace_back(physics{ point_2d{ x(m_gen), 0.0F },					pol_to_car(polar_2d{ initial_speed, theta(m_gen) }) }, path_from_prototype(*asteroid_vbs[m_0_to_3(m_gen)], big_asteroid_size), big_asteroid_size); break;
			case 4:	m_asteroids.emplace_back(physics{ point_2d{ x(m_gen), playing_field_height },	pol_to_car(polar_2d{ initial_speed, theta(m_gen) }) }, path_from_prototype(*asteroid_vbs[m_0_to_3(m_gen)], big_asteroid_size), big_asteroid_size); break;
			}
		}
	}

	void game::update_asteroids()
	{
		for (auto& a : m_asteroids) { a.update(); }
	}

	void game::update_ship()
	{
		auto missile = m_ship.update();
		if (missile.m_launch && m_ship_missile_count < max_missiles)
		{
			// launch a missile
			m_ship_missiles[m_next_ship_missile] = { missile.m_direction, missile.m_orientation, true };
			if (++m_next_ship_missile == max_missiles)
			{
				m_next_ship_missile = 0;
			}
			++m_ship_missile_count;
		}
	}

	void game::update_missiles()
	{
		auto ad = std::vector<asteroid_destruction>{};
		ad.reserve(max_missiles);
		for (auto& m : m_ship_missiles)
		{
			if (!m.active()) continue;
			if (!m.update())
			{
				m.destroy();
				--m_ship_missile_count;
			}
			for (auto& a : m_asteroids)
			{
				if (a.active() && collides(a.collision_data(), m.collision_data()))
				{
					ad.push_back(a.destroy());
					m.destroy();
					--m_ship_missile_count;
				}
			}
		}

		for (auto& next_asteroids : ad)
		{
			m_score += next_asteroids.m_score;
			if (!next_asteroids.m_physics) continue;

			auto new_physics = next_asteroids.m_physics->divide(m_gen, m_0_to_1);
			auto path1 = path_from_prototype(*asteroid_vbs[m_0_to_3(m_gen)], next_asteroids.m_size);
		m_asteroids.emplace_back(std::move(new_physics[0]), path1, next_asteroids.m_size);
			auto path2 = path_from_prototype(*asteroid_vbs[m_0_to_3(m_gen)], next_asteroids.m_size);
			m_asteroids.emplace_back(std::move(new_physics[1]), path2, next_asteroids.m_size);
		}
	}
	inline void get_key_states() {
	}
}

int x_error_handler(Display* dpy, XErrorEvent* evt)
{
	const int buffLength = 1024;
	char errorText[buffLength] = {};
	XGetErrorText(evt->display, evt->error_code, errorText, buffLength);
	::std::cerr << "Error encountered with serial number '" << evt->serial << "', opcode '"
		<< evt->request_code << "', and minor opcode '" << evt->minor_code << "'."
		<< ::std::endl << "Error text is: " << errorText << ::std::endl;
	return static_cast<int>(evt->error_code);
}

int main()
{
	XSetErrorHandler(&x_error_handler);
	rocks_in_space::game g(640, 480, rocks_in_space::format::argb32, rocks_in_space::scaling::letterbox);
	return g.run_event_loop();
}
