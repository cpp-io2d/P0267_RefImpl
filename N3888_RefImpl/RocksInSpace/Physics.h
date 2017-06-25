#pragma once

#include "Maths.h"
#include <random>

namespace asteroids
{
	using pos = vector_2d;
	using vel = vector_2d;
	using acc = vector_2d;

	class physics
	{
	public:
		physics(const pos& position, const vel& velocity) : m_position(position), m_velocity(velocity) {};
		void update();
		void update(const acc&);
		std::array<physics, 2>	divide(std::mt19937&, std::uniform_real_distribution<double>&) const;
		const pos& position() const { return m_position; }
		const vel& velocity() const { return m_velocity; }

	private:
		pos m_position;
		vel m_velocity;
	};

	class controllable_physics
	{
	public:
		controllable_physics(const physics& phy, const acc& acc, double ori) : m_physics(phy), m_acceleration(acc), m_orientation(ori) {}
		void		update();
		void		thrust(double t) { m_acceleration = pol_to_car(polar_2d{ t, m_orientation }); }
		void		spin(double spin) { m_orientation += spin; }
		const pos&	position() const { return m_physics.position(); }
		const vel&	velocity() const { return m_physics.velocity(); }
		const acc&	acceleration() const { return m_acceleration; }
		double		orientation() const { return m_orientation; }

	private:
		physics		m_physics;
		acc			m_acceleration;
		double		m_orientation;
	};

	using path_vertices = std::array<vector_2d, 14>;

	struct path_buffer
	{
		int m_count;
		path_vertices m_vertices;
	};

	struct collision
	{
		const pos&			m_position;
		const path_buffer&	m_path;
		const double		m_radius;
	};

	std::pair<path_buffer, double> path_from_prototype(const path_buffer& path, double s);
	void constrain_pos(pos&);
	void constrain_vel(vel&);
	inline vector_2d screen_space(const vector_2d& v) { return{ v.x(), 480 - v.y() }; }
	bool collides(const collision& a, const std::array<vector_2d, 2>& missile_path);
}
