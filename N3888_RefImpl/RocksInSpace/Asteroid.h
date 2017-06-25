#pragma once

#include "Physics.h"

namespace asteroids
{
	using display_surface = std::experimental::io2d::display_surface;

	struct asteroid_destruction
	{
		int				m_score;
		double			m_size;
		const physics*	m_physics;
	};

	class asteroid
	{
	public:
		asteroid(physics&& phys, std::pair<const path_buffer&, double> path, double s) : m_physics(phys), m_path(path.first), m_size(s), m_collision{ m_physics.position(), m_path, path.second }, m_active(true) {};
		void		update();
		asteroid_destruction	destroy();
		void		draw(display_surface& ds) const;
		bool		active() const { return m_active; }
		const collision&	collision_data() const { return m_collision; }

		static const path_buffer	a1;
		static const path_buffer	a2;
		static const path_buffer	a3;
		static const path_buffer	a4;

	private:
		physics		m_physics;
		path_buffer	m_path;
		double		m_size;
		collision	m_collision;
		bool		m_active;
	};
}