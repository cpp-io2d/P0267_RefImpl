#pragma once

#include "Types.h"
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
		
		template <class OutputType>
		void						draw(OutputType& ds) const;
		bool						active() const;
		const collision&			collision_data() const;
		stadium						sweep(float duration) const;

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

inline rocks_in_space::stadium rocks_in_space::asteroid::sweep(float duration) const
{
	return { m_physics.position(), m_physics.position() + m_physics.velocity() * duration, m_collision.m_radius };
}

template <class OutputType>
inline void rocks_in_space::asteroid::draw(OutputType& ds) const
{
	using namespace std::experimental::io2d;

	if (!m_active) return;

	auto path = path_builder{};
	path.clear();
	auto v = m_physics.position() + (m_path.m_vertices[0]);
	path.new_figure(screen_space(v));
	std::for_each(&m_path.m_vertices[1], &m_path.m_vertices[m_path.m_count], [&](const auto& vert)
	{
		v += vert;
		path.line(screen_space(v));
	});
	path.close_figure();

	ds.stroke(brush{ rgba_color::gray }, path);
}

