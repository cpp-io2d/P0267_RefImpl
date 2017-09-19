#pragma once

#include "Renderer.h"
#include "Physics.h"

namespace rocks_in_space
{
	struct ship_update
	{
		bool		m_launch;
		point_2d	m_position;
		float		m_orientation;
		path_buffer	m_path;
	};

	class ship
	{
	public:
						ship(const controllable_physics&);
		ship_update		update();
		void			draw(my_display_surface& ds);

	private:
		controllable_physics	m_physics;
		path_buffer				m_path;
	};

	class missile
	{
	public:
								missile(const point_2d& = { 0.0, 0.0 }, float = 0.0, bool = false);
		bool					update();
		void					destroy();
		bool					active() const;
		void					draw(my_display_surface& ds);
		std::array<point_2d, 2>	collision_data() const;

	private:
		physics		m_physics;
		float		m_age;
	};

	float ship_radius();
}

inline std::array<rocks_in_space::point_2d, 2>	rocks_in_space::missile::collision_data() const
{
	return{ m_physics.position(), m_physics.position() - m_physics.velocity() };
}
