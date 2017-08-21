#pragma once

#include "io2d.h"
#include "xcairo.h"

#include "Asteroid.h"
#include "Ship.h"

namespace rocks_in_space
{
	using my_display_surface = std::experimental::io2d::display_surface<std::experimental::io2d::v1::cairo::cairo_renderer>;
	using my_brush = std::experimental::io2d::brush<std::experimental::io2d::v1::cairo::cairo_renderer>;

	class game
	{
	public:
				game();
		void	update(my_display_surface&);

	private:
		void	update_asteroids();
		void	update_ship();
		void	update_missiles();

		void	draw_asteroids(my_display_surface& ds);
		void	draw_ship(my_display_surface& ds);
		void	draw_missiles(my_display_surface& ds);

		void	generate_level();

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

	int main();
}
