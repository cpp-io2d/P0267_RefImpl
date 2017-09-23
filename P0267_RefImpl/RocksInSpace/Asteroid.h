#pragma once

#include "Renderer.h"
#include "Physics.h"

namespace rocks_in_space
{
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
		bool						update(float seconds);
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
