#pragma once

#include "Constants.h"
#include "Maths.h"

#include <random>

namespace rocks_in_space
{
	using pos = vector_2d;
	using vel = vector_2d;
	using acc = vector_2d;

	using path_vertices = std::array<vector_2d, 13>;

	struct path_buffer
	{
		int				m_count;
		path_vertices	m_vertices;
	};

	struct collision
	{
		const pos&		m_position;
		float			m_radius;
		path_buffer&	m_path;
	};

	struct rotating_collision
	{
		pos&			m_position;
		float			m_radius;
		path_buffer		m_path;
	};

	class physics
	{
	public:
								physics(const pos& position, const vel& velocity);
		void					update();
		void					update(const acc&);

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
					controllable_physics(const physics& phy, const acc& acc, float ori);
		void		update();
		void		thrust(float t);
		void		spin(float spin);

		const pos&	position() const;
		const vel&	velocity() const;
		const acc&	acceleration() const;
		float		orientation() const;

	private:
		physics		m_physics;
		acc			m_acceleration;
		float		m_orientation;
	};

	std::pair<path_buffer, float>	path_from_prototype(const path_buffer& path, float s);
	void							constrain_pos(pos&);
	void							constrain_vel(vel&);
	void							constrain_ori(double&);
	vector_2d						screen_space(const vector_2d& v);
	bool							collides(const collision& a, const std::array<vector_2d, 2>& missile_path);
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

inline rocks_in_space::controllable_physics::controllable_physics(const physics& phy, const acc& acc, float ori)
	: m_physics(phy)
	, m_acceleration(acc)
	, m_orientation(ori)
{}

inline void	rocks_in_space::controllable_physics::thrust(float t)
{
	m_acceleration = pol_to_car(polar_2d{ t, m_orientation });
}

inline void	rocks_in_space::controllable_physics::spin(float spin)
{
	m_orientation += spin;
}

inline const rocks_in_space::pos& rocks_in_space::controllable_physics::position() const
{
	return m_physics.position();
}

inline const rocks_in_space::vel& rocks_in_space::controllable_physics::velocity() const
{
	return m_physics.velocity();
}

inline const rocks_in_space::acc& rocks_in_space::controllable_physics::acceleration() const
{
	return m_acceleration;
}

inline float rocks_in_space::controllable_physics::orientation() const
{
	return m_orientation;
}

inline rocks_in_space::vector_2d rocks_in_space::screen_space(const vector_2d& v)
{
	return{ v.x(), playing_field_height - v.y() };
}
