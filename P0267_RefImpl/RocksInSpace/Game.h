#pragma once


#include "Asteroid.h"
#include "Ship.h"
#include <random>

namespace rocks_in_space
{
	class game
	{
	public:
				game();
		void	update(output_surface&);

	private:
		void	update_asteroids();
		void	update_ship();
		void	update_missiles();

		void	draw_asteroids(output_surface& ds);
		void	draw_ship(output_surface& ds);
		void	draw_missiles(output_surface& ds);

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
