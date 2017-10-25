#pragma once

#include "Types.h"
#include "Physics.h"

namespace rocks_in_space
{
	struct ship_update
	{
		bool		m_launch;
		point_2d	m_direction;
		float		m_orientation;
	};

	class ship
	{
	public:
						ship(const controllable_physics&);
		ship_update		update();
		template <class OutputType>
		void			draw(OutputType& ds);

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
		template <class OutputType>
		void					draw(OutputType& ds);
		std::array<point_2d, 2>	collision_data() const;

	private:
		physics		m_physics;
		float		m_age;
	};

	template <class OutputType>
	inline void rocks_in_space::ship::draw(OutputType& ds)
	{
		using namespace std::experimental::io2d;

		auto path = path_builder{};
		path.clear();
		auto v = m_physics.position() + (m_path.m_vertices[0]);
		path.new_figure(screen_space(v));
		std::for_each(&m_path.m_vertices[1], &m_path.m_vertices[m_path.m_count], [&](const auto& vert)
		{
			v += vert;
			path.line(screen_space(v));
		});

		ds.stroke(brush{ rgba_color::white }, path);
	}

	template <class OutputType>
	inline void rocks_in_space::missile::draw(OutputType& ds)
	{
		using namespace std::experimental::io2d;

		if (!active()) return;

		auto path = path_builder{};
		path.new_figure(screen_space(m_physics.position()));
		path.line(screen_space(m_physics.position() - m_physics.velocity()));

		ds.stroke(brush{ rgba_color::white }, path);
	}
}

inline std::array<rocks_in_space::point_2d, 2>	rocks_in_space::missile::collision_data() const
{
	return{ { m_physics.position(), m_physics.position() - m_physics.velocity() } };
}
