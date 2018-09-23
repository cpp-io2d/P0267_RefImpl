#include "Physics.h"
#include "Constants.h"

#include <algorithm>

void rocks_in_space::physics::update(float seconds)
{
	m_position += m_velocity * seconds;
	constrain_pos(m_position);
}

void rocks_in_space::physics::update(float seconds, const acc& a)
{
	m_velocity += a * seconds;
	constrain_vel(m_velocity);
	update(seconds);
}

std::array<rocks_in_space::physics, 2> rocks_in_space::physics::divide(std::mt19937& gen, std::uniform_real_distribution<float>& zero_to_one) const
{
	auto polar = car_to_pol(m_velocity);
	auto r = polar.r();
	auto r1 = r * (1.2F + zero_to_one(gen));
	auto r2 = r * (1.2F + zero_to_one(gen));
	auto theta1 = polar.theta() + (zero_to_one(gen) - eighth_tau<float>);
	auto theta2 = polar.theta() + (zero_to_one(gen) - eighth_tau<float>);
	return{ { physics(m_position, pol_to_car({r1, theta1})), physics(m_position, pol_to_car({r2, theta2})) } };
}

void rocks_in_space::controllable_physics::update(float spin, float thrust_val, float seconds)
{
    m_orientation += spin * seconds;
    auto acceleration = pol_to_car(polar_2d{ thrust_val, m_orientation });
	m_physics.update(seconds, acceleration);
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

bool rocks_in_space::collides(const collision& col, const std::array<point_2d, 2>& line)
{
	auto delta = col.m_position - line[0];
	if (delta.magnitude() > col.m_radius)
	{
		return false;
	}

	auto segment_start = col.m_path.m_vertices[col.m_path.m_count - 1];
	return &col.m_path.m_vertices[col.m_path.m_count] != std::find_if(&col.m_path.m_vertices[0], &col.m_path.m_vertices[col.m_path.m_count], [&](const auto& v)
	{
		if (intersects(segment_start + col.m_position, v + col.m_position, line[0], line[1]))
		{
			return true;
		}
		segment_start = v;
		return false;
	});
}

bool rocks_in_space::collides(const collision& col_a, const collision& col_b)
{
	auto delta = col_a.m_position - col_b.m_position;
	if (delta.magnitude() > (col_a.m_radius + col_b.m_radius))
	{
		return false;
	}

	auto segment_start = col_a.m_path.m_vertices[col_a.m_path.m_count - 1];
	return &col_a.m_path.m_vertices[col_a.m_path.m_count] != std::find_if(&col_a.m_path.m_vertices[0], &col_a.m_path.m_vertices[col_a.m_path.m_count], [&](const auto& v)
	{
		if (collides(col_b, { { segment_start + col_a.m_position, v + col_a.m_position } }))
		{
			return true;
		}
		segment_start += v;
		return false;
	});
}
