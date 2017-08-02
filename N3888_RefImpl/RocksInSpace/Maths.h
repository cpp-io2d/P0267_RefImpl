#pragma once

#include "io2d.h"

namespace rocks_in_space
{
	using vector_2d = std::experimental::io2d::vector_2d;
	using bounding_box = std::experimental::io2d::bounding_box;

	class polar_2d
	{
	public:
		polar_2d(float r_in, float theta_in);
		float r() const;
		float theta() const;

	private:
		float m_r;
		float m_theta;
	};

	template <class T> constexpr T	tau			= T(std::experimental::io2d::two_pi<T>);
	template <class T> constexpr T	eighth_tau	= T(tau<T> / T(8.0L));

	bool		intersects(vector_2d, vector_2d, vector_2d, vector_2d);
	bool		intersects(const bounding_box&, const bounding_box&);
	bool		contains(const bounding_box&, const vector_2d&);

	vector_2d	pol_to_car(const polar_2d& p);
	polar_2d	car_to_pol(const vector_2d& v);
	float		radius(const bounding_box&);

	vector_2d	rotate(const vector_2d& point, float theta, const vector_2d& origin);
	bounding_box	translate(const bounding_box&, const vector_2d&);
}

inline rocks_in_space::polar_2d::polar_2d(float r_in, float theta_in)
	: m_r(r_in)
	, m_theta(theta_in)
{}

inline float rocks_in_space::polar_2d::r() const
{
	return m_r;
}

inline float rocks_in_space::polar_2d::theta() const
{
	return m_theta;
}

inline rocks_in_space::vector_2d rocks_in_space::pol_to_car(const polar_2d& p)
{
	return{ p.r() * cos(p.theta()), p.r() * sin(p.theta()) };
}

inline rocks_in_space::polar_2d rocks_in_space::car_to_pol(const vector_2d& v)
{
	return{ v.magnitude(), atan2(v.y(), v.x()) };
}
