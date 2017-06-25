#pragma once

#include "io2d.h"

namespace asteroids
{
	using vector_2d = std::experimental::io2d::vector_2d;

	class polar_2d
	{
	public:
		polar_2d(double r_in, double theta_in) : m_r(r_in), m_theta(theta_in) {}
		double r() const { return m_r; }
		double theta() const { return m_theta; }

	private:
		double m_r;
		double m_theta;
	};

	const auto tau = 6.283185307179586476925286766559;
	const auto eighth_tau = tau / 8.0;

	vector_2d rotate(const vector_2d& point, double theta, const vector_2d& origin);
	bool intersects(vector_2d, vector_2d, vector_2d, vector_2d);

	inline vector_2d pol_to_car(const polar_2d& p) { return{ p.r() * cos(p.theta()), p.r() * sin(p.theta()) }; }
	inline polar_2d car_to_pol(const vector_2d& v) { return{ v.magnitude(), atan2(v.y(), v.x()) }; }
}
