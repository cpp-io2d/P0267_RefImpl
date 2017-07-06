#include "Ship.h"
#include "Input.h"
#include "Constants.h"

#include <algorithm>

namespace
{
	using rocks_in_space::path_vertices;
	using rocks_in_space::path_buffer;
	using rocks_in_space::vector_2d;

	path_vertices ship_vb{ vector_2d{ 8, 0 },{ -15, -5 },{ 2, 3 },{ 0, 5 },{ -2, 3 },{ 15, -5 } };
	const rocks_in_space::path_buffer ship_shape{ 6, ship_vb };
}

rocks_in_space::ship::ship(const controllable_physics& cp)
	: m_physics(cp)
	, m_path(ship_shape)
{}

rocks_in_space::ship_update rocks_in_space::ship::update()
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
	return{ fire(), m_physics.position(), m_physics.orientation() };
}

void rocks_in_space::ship::draw(display_surface& ds)
{
	using namespace std::experimental::io2d;

	auto path = path_builder<>{};
	path.clear();
	auto v = m_physics.position() + (m_path.m_vertices[0]);
	path.new_path(screen_space(v));
	std::for_each(&m_path.m_vertices[1], &m_path.m_vertices[m_path.m_count], [&](const auto& vert)
	{
		v += vert;
		path.line(screen_space(v));
	});

	ds.stroke(brush{ rgba_color::white }, path);
}

rocks_in_space::missile::missile(const vector_2d& position, float orientation, bool active)
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

void rocks_in_space::missile::draw(display_surface& ds)
{
	using namespace std::experimental::io2d;

	if (!active()) return;

	auto path = path_builder<>{};
	path.new_path(screen_space(m_physics.position()));
	path.line(screen_space(m_physics.position() - m_physics.velocity()));

	ds.stroke(brush{ rgba_color::white }, path);
}