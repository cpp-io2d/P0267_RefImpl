#include "Maths.h"

asteroids::vector_2d asteroids::rotate(const vector_2d& point, double theta, const vector_2d& origin)
{
	const auto translation = point - origin;
	const auto s = sin(theta);
	const auto c = cos(theta);

	return vector_2d{ translation.x() * c - translation.y() * s, translation.x() * s + translation.y() * c } +origin;
}

bool asteroids::intersects(vector_2d a1, vector_2d a2, vector_2d b1, vector_2d b2)
{
	assert(!(a1 == a2 || b1 == b2));

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

