#include "Game.h"
#include "Input.h"
#include "Constants.h"

namespace
{
	const rocks_in_space::path_buffer* asteroid_vbs[] = { &rocks_in_space::asteroid::a1, &rocks_in_space::asteroid::a2, &rocks_in_space::asteroid::a3, &rocks_in_space::asteroid::a4 };
}

rocks_in_space::game::game()
	: m_level{ 0 }
	, m_score{ 0 }
	//, m_lives{ 0 }
	, m_ship(controllable_physics{
	physics{ point_2d{ playing_field_width / 2, playing_field_height / 2 },{ point_2d{ 0, 0 } } },
	0.0f })
	//, m_ship_missile_count{ 0 }
	, m_next_ship_missile(0)
	, m_ship_missiles(max_missiles)
	, m_rd()
	, m_gen(m_rd())
	, m_0_to_3(0, 3)
	, m_0_to_1(0, 1)
	, m_state(game_state::new_level)
	, m_state_change(std::chrono::steady_clock::now())
{
}

void rocks_in_space::game::generate_level()
{
	auto count = m_level * 2 + 2;
	std::uniform_int_distribution<> edge(1, 4);
	std::uniform_real_distribution<float> x(0.0F, playing_field_width);
	std::uniform_real_distribution<float> y(0.0F, playing_field_height);
	std::uniform_real_distribution<float> theta(0.0F, std::experimental::io2d::tau<float>);

	m_asteroids.clear();
	m_asteroids.reserve(static_cast<::std::size_t>(count * 7));

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

void rocks_in_space::game::update_ship(float seconds, std::vector<asteroid_destruction>& ad)
{
	auto ship_update = m_ship.update(seconds);
	if (ship_update.m_launch && std::count_if(std::begin(m_ship_missiles), std::end(m_ship_missiles), [](const auto& m) { return m.active(); }) < max_missiles)
	{
		m_ship_missiles[m_next_ship_missile] = { ship_update.m_position, ship_update.m_orientation, true };
		m_next_ship_missile = ++m_next_ship_missile % max_missiles;
	}
	if (m_ship.active())
	{
		for (auto& a : m_asteroids)
		{
			if (a.active() && collides(a.collision_data(), { ship_update.m_position, ship_radius(), ship_update.m_path }))
			{
				m_ship.destroy();
				ad.push_back(a.destroy());
			}
		}
	}
}

void rocks_in_space::game::update_missiles(float seconds, std::vector<asteroid_destruction>& ad)
{
	for (auto& m : m_ship_missiles)
	{
		if (!m.active()) continue;
		if (!m.update(seconds))
		{
			m.destroy();
		}
		for (auto& a : m_asteroids)
		{
			if (a.active() && collides(a.collision_data(), m.collision_data()))
			{
				ad.push_back(a.destroy());
				m.destroy();
			}
		}
	}
}

bool rocks_in_space::game::update_asteroids(float seconds, std::vector<asteroid_destruction>& ad)
{
	if (m_state == game_state::new_level)
	{
		return true;
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
	return std::count_if(std::begin(m_asteroids), std::end(m_asteroids), [=](auto& a) { return a.update(seconds); }) > 0;
}


//std::once_flag rocks_in_space::my_handler::_Window_class_registered_flag;
//const wchar_t* rocks_in_space::my_handler::_Refimpl_window_class_name = L"_RefImplWndwCls";
