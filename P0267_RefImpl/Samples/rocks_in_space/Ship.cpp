#include "Ship.h"
#include "Input.h"
#include "Constants.h"

#include <algorithm>

namespace
{
	using rocks_in_space::path_vertices;
	using rocks_in_space::path_buffer;
	using rocks_in_space::point_2d;

	const path_vertices ship_vb{ { point_2d{ 8, 0 },{ -15, -5 },{ 2, 3 },{ 0, 5 },{ -2, 3 },{ 15, -5 } } };
	const auto ship_path_radius{ 9.7f };
	const auto ship_shape = path_buffer{ 6, ship_vb };
	const auto wait_period{ 1 };
	const auto destruct_period{ 1 };
}

rocks_in_space::ship::ship(const controllable_physics& cp)
	: m_physics(cp)
	, m_path(ship_shape)
	, m_state(ship_state::waiting)
	, m_state_change(std::chrono::steady_clock::now())
{}

rocks_in_space::ship_update rocks_in_space::ship::update(float seconds)
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
        auto spin_val = do_anti_clockwise() ? spin_left
                      : (do_clockwise() ? spin_right : 0.0f);
        auto thrust_val = do_thrust() ? thrust : 0.0f;
		m_physics.update(spin_val, thrust_val, seconds);

		std::transform( std::begin(ship_vb), std::next(std::begin(ship_vb), ship_shape.m_count), std::begin(m_path.m_vertices), [&](const auto & v_in)
		{
			return rotate(v_in, m_physics.orientation(), { 0.0f, 0.0f });
		});
		return{ do_fire(), m_physics.position(), m_physics.orientation(), m_path };
	}
	case ship_state::exploding:
	{
		auto now = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(now - m_state_change).count() > destruct_period)
		{
			m_physics.reset(physics{ point_2d{ playing_field_width / 2, playing_field_height / 2 },{ point_2d{ 0, 0 } } }, 0.0f);
			m_state = ship_state::waiting;
			m_state_change = now;
		}
		return{ false, m_physics.position(), m_physics.orientation(), m_path };
	}
	default:
	{
		throw ::std::system_error(::std::make_error_code(::std::errc::invalid_argument));
	} break;
	}
}

void rocks_in_space::ship::destroy()
{
	m_state = ship_state::exploding;
}

rocks_in_space::missile::missile(const point_2d& position, float orientation, bool active)
	: m_physics(position, pol_to_car({ missile_speed, orientation }))
	, m_age(active ? 0.0F : missile_lifespan)
{}

bool rocks_in_space::missile::update(float seconds)
{
	if (!active()) return true;

	m_physics.update(seconds);
	m_age += seconds;
	return active();
}

void rocks_in_space::missile::destroy()
{
	m_age = missile_lifespan;
}

bool rocks_in_space::missile::active() const
{
	return (m_age < missile_lifespan);
}

float rocks_in_space::ship_radius()
{
	return ship_path_radius;
}
