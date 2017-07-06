#include "physics.h"
#include "Constants.h"
#include <algorithm>

void rocks_in_space::physics::update()
{
	m_position += m_velocity;
	constrain_pos(m_position);
}

void rocks_in_space::physics::update(const acc& a)
{
	m_velocity += a;
	constrain_vel(m_velocity);
	update();
}

std::array<rocks_in_space::physics, 2> rocks_in_space::physics::divide(std::mt19937& gen, std::uniform_real_distribution<float>& zero_to_one) const
{
	auto polar = car_to_pol(m_velocity);
	auto r = polar.r();
	auto r1 = r * (1.2F + zero_to_one(gen));
	auto r2 = r * (1.2F + zero_to_one(gen));
	auto theta1 = polar.theta() + (zero_to_one(gen) - eighth_tau<float>);
	auto theta2 = polar.theta() + (zero_to_one(gen) - eighth_tau<float>);
	return{ physics(m_position, pol_to_car({r1, theta1})), physics(m_position, pol_to_car({r2, theta2})) };
}

void rocks_in_space::controllable_physics::update()
{
	m_physics.update(m_acceleration);
	m_acceleration = { 0,0 };
}

std::pair<rocks_in_space::path_buffer, float> rocks_in_space::path_from_prototype(const path_buffer& path, float s)
{
	auto pv = rocks_in_space::path_vertices{ path.m_vertices };
	auto radius = 0.0F;
	std::for_each(&pv[0], &pv[path.m_count], [&](auto& v) {v *= s; radius = std::max(radius, v.magnitude()); });
	return std::make_pair(path_buffer{ path.m_count, pv }, radius);
}

void rocks_in_space::constrain_pos(pos& p)
{
	while (p.x() >= playing_field_width) p.x(p.x() - playing_field_width);
	while (p.y() >= playing_field_height) p.y(p.y() - playing_field_height);
	while (p.x() < 0.0f) p.x(p.x() + playing_field_width);
	while (p.y() < 0.0f) p.y(p.y() + playing_field_height);
}

void rocks_in_space::constrain_vel(vel& v)
{
	auto polar = car_to_pol(v);
	if (polar.r() > max_ship_speed)
	{
		v = pol_to_car({ max_ship_speed, polar.theta() });
	}
}

bool rocks_in_space::collides(const collision& a, const std::array<vector_2d, 2>& missile_path)
{
	auto delta = a.m_position - missile_path[0];
	if (delta.magnitude() > a.m_radius)
	{
		return false;
	}

	auto segment_start = a.m_path.m_vertices[a.m_path.m_count - 1];
	return &a.m_path.m_vertices[a.m_path.m_count] != std::find_if(&a.m_path.m_vertices[0], &a.m_path.m_vertices[a.m_path.m_count], [&](const auto& v)
	{
		if (intersects(segment_start + a.m_position, v + a.m_position, missile_path[0], missile_path[1]))
		{
			return true;
		}
		segment_start = v;
		return false;
	});
}