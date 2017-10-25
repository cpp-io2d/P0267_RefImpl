#pragma once

#include "Types.h"
#include "Input.h"
#include "Asteroid.h"
#include "Ship.h"
#include <random>
#include <memory>
#include <vector>
#include <X11/Xlib.h>
#include <X11/keysym.h>

namespace rocks_in_space
{
	using scaling =				::std::experimental::io2d::scaling;
	using format = 				::std::experimental::io2d::format;
	using default_graphics_surfaces =	::std::experimental::io2d::default_graphics_surfaces;
	using display_point =		::std::experimental::io2d::display_point;

	Bool _X11_if_xev_pred(::Display* display, ::XEvent* xev, XPointer arg);
		
	class game
	{
	public:
		game(int w, int h, format fmt, scaling scl);

		template <class OutputType>
		void	update(OutputType&);

		int run_event_loop();

		Window get_window() const noexcept;

	private:
		void	update_asteroids();
		void	update_ship();
		void	update_missiles();

		template <class OutputType>
		void	draw_asteroids(OutputType& ds);
		template <class OutputType>
		void	draw_ship(OutputType& ds);
		template <class OutputType>
		void	draw_missiles(OutputType& ds);

		void	generate_level();


		::std::unique_ptr<Display, decltype(&XCloseDisplay)>
												m_display{ nullptr, &XCloseDisplay };
		int										m_x = 0;
		int										m_y = 0;
		int										m_w = 640;
		int										m_h = 480;
		int										m_borderWidth = 4;
		int										m_screenNumber;
		format									m_fmt;
		scaling									m_scl;
		Window									m_wndw;
		unmanaged_output_surface				m_uosfc;

		int										m_level;
		int										m_score;
		int										m_lives;
		ship									m_ship;
		std::vector<asteroid>					m_asteroids;
		int										m_ship_missile_count;
		size_t									m_next_ship_missile;
		std::vector<missile>					m_ship_missiles;
		std::random_device						m_rd;
		std::mt19937							m_gen;
		std::uniform_int_distribution<>			m_0_to_3;
		std::uniform_real_distribution<float>	m_0_to_1;
	};

	template <class OutputType>
	inline void rocks_in_space::game::update(OutputType& ds)
	{
		using namespace std::experimental::io2d;
	
		get_key_states();
		update_asteroids();
		update_ship();
		update_missiles();
	
		ds.paint(brush{ rgba_color::black });
		draw_asteroids<OutputType>(ds);
		draw_ship<OutputType>(ds);
		draw_missiles<OutputType>(ds);
	}
	
		template <class OutputType>
	inline void rocks_in_space::game::draw_asteroids(OutputType& ds)
	{
		for (auto& a : m_asteroids) { a.draw<OutputType>(ds); }
	}

	template <class OutputType>
	inline void rocks_in_space::game::draw_ship(OutputType& ds)
	{
		m_ship.draw(ds);
	}

	template <class OutputType>
	inline void rocks_in_space::game::draw_missiles(OutputType& ds)
	{
		for (auto& m : m_ship_missiles) { m.draw(ds); }
	}
}
