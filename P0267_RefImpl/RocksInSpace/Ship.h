#pragma once

#include "Types.h"
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
		ship_update		update(float seconds);
		void			destroy();
		template <class OutputType>
		void			draw(OutputType& ds);
		circle			sweep() const;
		bool			active() const;

	private:
		enum class ship_state
		{
			waiting,
			active,
			exploding
		};
		controllable_physics					m_physics;
		path_buffer								m_path;
		ship_state								m_state;
		std::chrono::steady_clock::time_point	m_state_change;
	};

	class missile
	{
	public:
								missile(const point_2d& = { 0.0, 0.0 }, float = 0.0, bool = false);
		bool					update(float seconds);
		void					destroy();
		bool					active() const;
		template <class OutputType>
		void					draw(OutputType& ds);
		std::array<point_2d, 2>	collision_data() const;

	private:
		physics		m_physics;
		float		m_age;
	};

	float ship_radius();

	template <class OutputType>
	inline void rocks_in_space::ship::draw(OutputType& ds)
	{
		using namespace std::experimental::io2d;

		switch (m_state)
		{
		case ship_state::waiting:
		{
			break;
		}
		case ship_state::active:
		{
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
			break;
		}
		case ship_state::exploding:
		{
			break;
		}
		}
	}

	template <class OutputType>
	inline void rocks_in_space::missile::draw(OutputType& ds)
	{
		using namespace std::experimental::io2d;

		if (!active()) return;

		auto path = path_builder{};
		path.new_figure(screen_space(m_physics.position()));
		path.line(screen_space(m_physics.position() - (m_physics.velocity() / missile_speed)));

		ds.stroke(brush{ rgba_color::white }, path);
	}
}

inline std::array<rocks_in_space::point_2d, 2> rocks_in_space::missile::collision_data() const
{
	return{ { m_physics.position(), m_physics.position() - m_physics.velocity() } };
}

inline std::experimental::io2d::circle rocks_in_space::ship::sweep() const
{
	return circle(m_physics.position(), ship_radius());
}

inline bool rocks_in_space::ship::active() const
{
	return m_state == ship_state::active;
}