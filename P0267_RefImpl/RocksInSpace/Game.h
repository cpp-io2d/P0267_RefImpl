#pragma once

#include "Renderer.h"
#include "Asteroid.h"
#include "Ship.h"

namespace rocks_in_space
{
	class game
	{
	public:
				game();
		void	update(my_display_surface&);

	private:
		enum class game_state
		{
			active,
			new_level
		};
		void	update_ship(float seconds, std::vector<asteroid_destruction>&);
		void	update_missiles(float seconds, std::vector<asteroid_destruction>&);
		bool	update_asteroids(float seconds, std::vector<asteroid_destruction>&);

		void	draw_asteroids(my_display_surface& ds);
		void	draw_ship(my_display_surface& ds);
		void	draw_missiles(my_display_surface& ds);

		void	generate_level();

		int										m_level;
		int										m_score;
		int										m_lives;
		ship									m_ship;
		std::vector<asteroid>					m_asteroids;
		size_t									m_next_ship_missile;
		std::vector<missile>					m_ship_missiles;
		std::random_device						m_rd;
		std::mt19937							m_gen;
		std::uniform_int_distribution<>			m_0_to_3;
		std::uniform_real_distribution<float>	m_0_to_1;
		game_state								m_state;
		std::chrono::steady_clock::time_point	m_state_change;
	};

	int main();
}
