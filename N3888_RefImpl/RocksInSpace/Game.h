#pragma once

#include "io2d.h"
#include "Asteroid.h"
#include "Ship.h"

namespace asteroids
{
	using display_surface = std::experimental::io2d::display_surface;

	class game
	{
	public:
		game();
		void update(display_surface&);

	private:
		void update_asteroids();
		void update_ship();
		void update_missiles();

		void draw_asteroids(display_surface& ds);
		void draw_ship(display_surface& ds);
		void draw_missiles(display_surface& ds);

		void generate_level();

		int										m_level;
		int										m_score;
		ship									m_ship;
		std::vector<asteroid>					m_asteroids;
		int										m_ship_missile_count;
		size_t									m_next_ship_missile;
		std::vector<missile>					m_ship_missiles;
		std::random_device						m_rd;
		std::mt19937							m_gen;
		std::uniform_int_distribution<>			m_0_to_3;
		std::uniform_real_distribution<double>	m_0_to_1;
	};

	int main();
}
