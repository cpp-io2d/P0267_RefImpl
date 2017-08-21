#pragma once

#include "io2d.h"
#include "xcairo.h"

#include "Physics.h"

namespace rocks_in_space
{
	using my_display_surface = std::experimental::io2d::display_surface<std::experimental::io2d::v1::cairo::cairo_renderer>;
	using my_brush = std::experimental::io2d::brush<std::experimental::io2d::v1::cairo::cairo_renderer>;

	struct asteroid_destruction
	{
		int				m_score;
		float			m_size;
		const physics*	m_physics;
	};

	class asteroid
	{
	public:
									asteroid(physics&& phys, std::pair<const path_buffer&, float> path, float s);
		void						update();
		asteroid_destruction		destroy();

		void						draw(my_display_surface& ds) const;
		bool						active() const;
		const collision&			collision_data() const;

		static const path_buffer	a1;
		static const path_buffer	a2;
		static const path_buffer	a3;
		static const path_buffer	a4;

	private:
		physics			m_physics;
		path_buffer		m_path;
		float			m_size;
		collision		m_collision;
		bool			m_active;
	};
}

inline rocks_in_space::asteroid::asteroid(physics&& phys, std::pair<const path_buffer&, float> path, float s)
	: m_physics(phys)
	, m_path(path.first)
	, m_size(s)
	, m_collision{ m_physics.position(), path.second, m_path }
	, m_active(true)
{};

inline bool rocks_in_space::asteroid::active() const
{
	return m_active;
}

inline const rocks_in_space::collision&	rocks_in_space::asteroid::collision_data() const
{
	return m_collision;
}
