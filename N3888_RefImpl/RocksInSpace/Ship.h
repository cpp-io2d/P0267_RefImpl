#pragma once

#include "Physics.h"

namespace asteroids
{
	using display_surface = std::experimental::io2d::display_surface;

	struct ship_update
	{
		bool		m_launch;
		vector_2d	m_direction;
		double		m_orientation;
	};

	class ship
	{
	public:
		ship(const controllable_physics&);
		ship_update					update();
		void						draw(display_surface& ds);

	private:
		controllable_physics		m_physics;
		path_buffer					m_path;
	};

	class missile
	{
	public:
		missile(const vector_2d& = { 0.0, 0.0 }, double = 0.0, bool = false);
		bool						update();
		void						destroy();
		bool						active() const;
		void						draw(display_surface& ds);
		std::array<vector_2d, 2>	collision_data() const { return{ m_physics.position(), m_physics.position() - m_physics.velocity() }; }

	private:
		physics						m_physics;
		double						m_age;
	};
}

