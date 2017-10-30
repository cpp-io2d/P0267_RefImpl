#pragma once

#include "Types.h"
#include "Asteroid.h"
#include "Input.h"
#include "Maths.h"
#include "Physics.h"
#include "Ship.h"
#include <random>

namespace
{
	constexpr auto level_transition_period = 1;
	constexpr auto new_ship_transition_period = 2;
}

namespace rocks_in_space
{
	class game
	{
	public:
		game();

		template <class OutputType>
		void	update(OutputType&);

	private:
		enum class game_state
		{
			new_level,
			new_ship,
			active,
		};
		bool	update_asteroids(float seconds, std::vector<asteroid_destruction>&);
		void	update_ship(float seconds, std::vector<asteroid_destruction>&);
		void	update_missiles(float seconds, std::vector<asteroid_destruction>&);

		template <class OutputType>
		void	draw_asteroids(OutputType& ds);
		template <class OutputType>
		void	draw_ship(OutputType& ds);
		template <class OutputType>
		void	draw_missiles(OutputType& ds);

		void	generate_level();

		int										m_level;
		int										m_score;
		//int										m_lives;
		ship									m_ship;
		std::vector<asteroid>					m_asteroids;
		//int										m_ship_missile_count;
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

	template <class OutputType>
	void rocks_in_space::game::update(OutputType& ds)
	{
		using namespace std::experimental::io2d;

		static auto last_update = std::chrono::steady_clock::now();
		auto now = std::chrono::steady_clock::now();

		if (m_state == game_state::new_level)
		{
			if (std::chrono::duration_cast<std::chrono::seconds>(now - m_state_change).count() > level_transition_period)
			{
				++m_level;
				generate_level();
				m_state = game_state::active;
				m_state_change = now;
			}
		}

		if (m_state == game_state::new_ship)
		{
			if (std::chrono::duration_cast<std::chrono::seconds>(now - m_state_change).count() > new_ship_transition_period &&
				std::find_if(std::begin(m_asteroids), std::end(m_asteroids), [&](const auto& a)
			{
				// Will the asteroid collide with the ship in the next two seconds?
				// Does the stadium described by the path of the asteroid's bounding circle
				// over the next two seconds intersect the ship's bounding circle?
				return a.sweep(asteroid_sweep_lookahead).intersects(m_ship.sweep());
			}) == std::end(m_asteroids))
			{
				m_state = game_state::active;
				m_state_change = now;
			}
		}

		get_key_states();

		auto ad = std::vector<asteroid_destruction>{};
		ad.reserve(max_missiles);

		auto interval = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_update).count() / 1000.0f;
		if (interval > 0)
		{
			update_ship(interval, ad);
			update_missiles(interval, ad);
			if (!update_asteroids(interval, ad))
			{
				m_state = game_state::new_level;
				m_state_change = now;
			}
			last_update = now;
		}

		ds.paint(brush{ rgba_color::black });
		draw_asteroids(ds);
		draw_ship(ds);
		draw_missiles(ds);
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
