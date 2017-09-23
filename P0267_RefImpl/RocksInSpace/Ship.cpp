#include "Ship.h"
#include "Input.h"
#include "Constants.h"

#include <algorithm>

namespace
{
	using rocks_in_space::path_vertices;
	using rocks_in_space::path_buffer;
	using rocks_in_space::point_2d;

	constexpr path_vertices ship_vb{ point_2d{ 8, 0 },{ -15, -5 },{ 2, 3 },{ 0, 5 },{ -2, 3 },{ 15, -5 } };
	constexpr auto ship_path_radius{ 9.7f };
	constexpr auto ship_shape = path_buffer{ 6, ship_vb };
	constexpr auto wait_period{ 1 };
	constexpr auto destruct_period{ 1 };
}

rocks_in_space::ship::ship(const controllable_physics& cp)
	: m_physics(cp)
	, m_path(ship_shape)
	, m_state(ship_state::waiting)
	, m_state_change(std::chrono::steady_clock::now())
{}

rocks_in_space::ship_update rocks_in_space::ship::update()
{
	switch (m_state)
	{
	case ship_state::waiting:
	{
		auto now = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(now - m_state_change).count() > wait_period)
		{
			m_state = ship_state::active;
			m_state_change = now;
		}
		return{ false, m_physics.position(), m_physics.orientation(), m_path };
	}
	case ship_state::active:
	{
		if (anti_clockwise())
		{
			m_physics.spin(spin_left);
		}
		if (clockwise())
		{
			m_physics.spin(spin_right);
		}
		if (thrust())
		{
			m_physics.thrust(thrust_force);
		}
		m_physics.update();

		std::transform(&ship_vb[0], &ship_vb[ship_shape.m_count], &m_path.m_vertices[0], [&](const auto & v_in)
		{
			return rotate(v_in, m_physics.orientation(), { 0.0, 0.0 });
		});
		return{ fire(), m_physics.position(), m_physics.orientation(), m_path };
	}
	case ship_state::exploding:
	{
		auto now = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(now - m_state_change).count() > destruct_period)
		{
			m_physics.reset(physics{ point_2d{ playing_field_width / 2, playing_field_height / 2 },{ point_2d{ 0, 0 } } }, point_2d{ 0.0f, 0.0f }, 0.0f);
			m_state = ship_state::waiting;
			m_state_change = now;
		}
		return{ false, m_physics.position(), m_physics.orientation(), m_path };
	}
	}
}

void rocks_in_space::ship::destroy()
{
	m_state = ship_state::exploding;
}

void rocks_in_space::ship::draw(my_display_surface& ds)
{
	using namespace std::experimental::io2d;

	switch (m_state)
	{
	case ship_state::waiting:
	{
		break;
	}
	case ship_state::active:
	{
		auto path = path_builder<>{};
		path.clear();
		auto v = m_physics.position() + (m_path.m_vertices[0]);
		path.new_figure(screen_space(v));
		std::for_each(&m_path.m_vertices[1], &m_path.m_vertices[m_path.m_count], [&](const auto& vert)
		{
			v += vert;
			path.line(screen_space(v));
		});

		ds.stroke(my_brush{ rgba_color::white }, path);
		break;
	}
	case ship_state::exploding:
	{
		break;
	}
	}
}

rocks_in_space::missile::missile(const point_2d& position, float orientation, bool active)
	: m_physics(position, pol_to_car({ missile_travel_distance_per_tick, orientation }))
	, m_age(active ? 0.0F : max_missile_age)
{}

bool rocks_in_space::missile::update()
{
	if (!active()) return true;

	m_physics.update();
	m_age += 0.1F;
	return active();
}

void rocks_in_space::missile::destroy()
{
	m_age = max_missile_age;
}

bool rocks_in_space::missile::active() const
{
	return (m_age < max_missile_age);
}

void rocks_in_space::missile::draw(my_display_surface& ds)
{
	using namespace std::experimental::io2d;

	if (!active()) return;

	auto path = path_builder<>{};
	path.new_figure(screen_space(m_physics.position()));
	path.line(screen_space(m_physics.position() - m_physics.velocity()));

	ds.stroke(my_brush{ rgba_color::white }, path);
}

float rocks_in_space::ship_radius()
{
	return ship_path_radius;
}