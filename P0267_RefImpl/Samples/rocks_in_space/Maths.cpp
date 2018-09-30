#include "Maths.h"

bool rocks_in_space::stadium::intersects(circle c) const
{
	return minimum_distance_from_line_segment(m_c1, m_c2, c.center()) < (m_radius + c.radius());
}

float rocks_in_space::minimum_distance_from_line_segment(point_2d e1, point_2d e2, point_2d p)
{
	const auto d_sq = (e1 - e2).magnitude_squared();
	if (d_sq == 0.0f)
	{
		return (e1 - p).magnitude();
	}
	const auto t = std::max(0.0f, std::min(1.0f, (p - e1).dot(e2 - e1) / d_sq));
	const auto projection = e1 + t * (e2 - e1);
	return (p - projection).magnitude();
}

rocks_in_space::point_2d rocks_in_space::rotate(const point_2d& point, float theta, const point_2d& origin)
{
	const auto translation = point - origin;
	const auto s = std::sin(theta);
	const auto c = std::cos(theta);

	return point_2d{ translation.x() * c - translation.y() * s, translation.x() * s + translation.y() * c } + origin;
}

bool rocks_in_space::intersects(point_2d a1, point_2d a2, point_2d b1, point_2d b2)
{
	// First test: do they share an end point?
	if ((a1 == b1) ||
		(a2 == b1) ||
		(a1 == b2) ||
		(a2 == b2))
		return false;

	// Translate the system so that point a1 is on the origin.
	a2 -= a1;
	b1 -= a1;
	b2 -= a1;

	// Rotate the system so that point a2 is on the positive x axis.
	auto a2_length = a2.magnitude();
	auto a2_cos = a2.x() / a2_length;
	auto a2_sin = a2.y() / a2_length;
	auto new_x = b1.x() * a2_cos + b1.y() * a2_sin;
	b1.y(b1.y() * a2_cos - b1.x() * a2_sin);
	b1.x(new_x);
	new_x = b2.x() * a2_cos + b2.y() * a2_sin;
	b2.y(b2.y() * a2_cos - b2.x() * a2_sin);
	b2.x(new_x);

	// Second test: do the endpoints of b both lie above or both lie below the x axis?
	if ((b1.y() < 0.0 && b2.y() < 0.0) ||
		(b1.y() >= 0.0 && b2.y() >= 0.0))
		return false;

	// Discover the position of the intersection point along line a.
	auto intersection_point = b2.x() + (b1.x() - b2.x()) * b2.y() / (b2.y() - b1.y());

	// Final test: does segment b crosses line a outside of segment a?
	return !(intersection_point < 0.0 || intersection_point > a2_length);
}

bool rocks_in_space::intersects(const bounding_box& a, const bounding_box& b)
{
	return contains(a, b.top_left()) ||
		contains(a, b.bottom_right()) ||
		contains(a, point_2d(b.y(), b.x() + b.width())) ||
		contains(a, point_2d(b.y() + b.height(), b.x())) ||
		contains(b, a.top_left()) ||
		contains(b, a.bottom_right()) ||
		contains(b, point_2d(a.y(), a.x() + a.width())) ||
		contains(b, point_2d(a.y() + a.height(), a.x()));
}

bool rocks_in_space::contains(const bounding_box& r, const point_2d& p)
{
	return p.x() >= r.x() &&
		p.x() <= r.x() + r.width() &&
		p.y() >= r.y() &&
		p.y() <= r.y() + r.height();
}

float rocks_in_space::radius(const bounding_box& r)
{
	return (r.top_left() - r.bottom_right()).magnitude() / 2.0f;
}

rocks_in_space::bounding_box rocks_in_space::translate(const bounding_box& r, const point_2d& v)
{
	return{ r.x() + v.x(), r.y() + v.y(), r.width(), r.height() };
}
