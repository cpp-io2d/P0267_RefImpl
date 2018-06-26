#pragma once

#include "Types.h"
#include "Constants.h"
#include "Maths.h"

#include <random>
#include <array>
#include <cstddef>

namespace rocks_in_space
{
	using pos = point_2d;
	using vel = point_2d;
	using acc = point_2d;

	using path_vertices = std::array<point_2d, 14>;

	struct path_buffer
	{
		std::size_t		m_count;
		path_vertices	m_vertices;
	};

	struct collision
	{
		const pos&		m_position;
		float			m_radius;
		path_buffer&	m_path;
	};

	class physics
	{
	public:
								physics(const pos& position, const vel& velocity);
		void					update(float seconds);
		void					update(float seconds, const acc&);

		std::array<physics, 2>	divide(std::mt19937&, std::uniform_real_distribution<float>&) const;
		const pos&				position() const;
		const vel&				velocity() const;

	private:
		pos		m_position;
		vel		m_velocity;
	};

	class controllable_physics
	{
	public:
					controllable_physics(const physics& phy, float ori);
		void		reset(const physics& phy, float ori);
		void		update(float spin, float thrust, float seconds);

		const pos&	position() const;
		const vel&	velocity() const;
		float		orientation() const;

	private:
		physics		m_physics;
		float		m_orientation;
	};

	std::pair<path_buffer, float>	path_from_prototype(const path_buffer& path, float s);
	void							constrain_pos(pos&);
	void							constrain_vel(vel&);
	void							constrain_ori(double&);
	point_2d						screen_space(const point_2d& v);
	bool							collides(const collision& a, const std::array<point_2d, 2>& missile_path);
	bool							collides(const collision& a, const collision& ship);
}

inline rocks_in_space::physics::physics(const pos& position, const vel& velocity)
	: m_position(position)
	, m_velocity(velocity)
{};

inline const rocks_in_space::pos& rocks_in_space::physics::position() const
{
	return m_position;
}

inline const rocks_in_space::vel& rocks_in_space::physics::velocity() const
{
	return m_velocity;
}

inline rocks_in_space::controllable_physics::controllable_physics(const physics& phy, float ori)
	: m_physics(phy)
	, m_orientation(ori)
{}

inline void rocks_in_space::controllable_physics::reset(const physics& phy, float ori)
{
	m_physics = phy;
	m_orientation = ori;
}

inline const rocks_in_space::pos& rocks_in_space::controllable_physics::position() const
{
	return m_physics.position();
}

inline const rocks_in_space::vel& rocks_in_space::controllable_physics::velocity() const
{
	return m_physics.velocity();
}

inline float rocks_in_space::controllable_physics::orientation() const
{
	return m_orientation;
}

inline rocks_in_space::point_2d rocks_in_space::screen_space(const point_2d& v)
{
	return{ v.x(), playing_field_height - v.y() };
}
