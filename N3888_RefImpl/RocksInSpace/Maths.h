#pragma once

#include "io2d.h"

namespace asteroids
{
	using vector_2d = std::experimental::io2d::vector_2d;

	class polar_2d
	{
	public:
		polar_2d(float r_in, float theta_in) : m_r(r_in), m_theta(theta_in) {}
		float r() const { return m_r; }
		float theta() const { return m_theta; }

	private:
		float m_r;
		float m_theta;
	};

	template <class T>
	constexpr T tau = T(6.283185307179586476925286766559L);
	template <class T>
	const T eighth_tau = T(tau<T> / T(8.0L));

	vector_2d rotate(const vector_2d& point, float theta, const vector_2d& origin);
	bool intersects(vector_2d, vector_2d, vector_2d, vector_2d);

	inline vector_2d pol_to_car(const polar_2d& p) { return{ p.r() * cos(p.theta()), p.r() * sin(p.theta()) }; }
	inline polar_2d car_to_pol(const vector_2d& v) { return{ v.magnitude(), atan2(v.y(), v.x()) }; }
}
