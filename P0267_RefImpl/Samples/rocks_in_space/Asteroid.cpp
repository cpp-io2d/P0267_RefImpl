#include "Asteroid.h"
#include "Constants.h"

namespace
{
	using rocks_in_space::path_vertices;
	using rocks_in_space::point_2d;

	const path_vertices a1_vb = { { point_2d{ -2, 4 },{ 2, -2 },{ 2, 2 },{ 2, -2 },{ -1, -2 },{ 1, -2 },{ -3, -2 },{ -3, 0 },{ -2, 2 },{ 0, 4 },{ 2, 2 } } };
	const path_vertices a2_vb = { { point_2d{ -2, 4 },{ 2, -1 },{ 2, 1 },{ 2, -2 },{ -2, -1 },{ 2, -2 },{ -2, -3 },{ -3, 1 },{ -1, -1 },{ -2, 2 },{ 1, 2 },{ -1, 2 },{ 2, 2 } } };
	const path_vertices a3_vb = { { point_2d{ -2, 4 },{ 3, 0 },{ 3, -2 },{ 0, -1 },{ -3, -1 },{ 3, -2 },{ -2, -2 },{ -4, 0 },{ -2, 3 },{ 0, 3 },{ 3, 0 },{ -1, 2 } } };
	const path_vertices a4_vb = { { point_2d{ -1, 4 },{ 3, 0 },{ 2, -3 },{ 0, -2 },{ -2, -3 },{ -2, 0 },{ 0, 3 },{ -2, -3 },{ -2, 3 },{ 2, 1 },{ -2, 1 },{ 3, 3 } }  };
}

const rocks_in_space::path_buffer rocks_in_space::asteroid::a1 = { 11, a1_vb };
const rocks_in_space::path_buffer rocks_in_space::asteroid::a2 = { 13, a2_vb };
const rocks_in_space::path_buffer rocks_in_space::asteroid::a3 = { 12, a3_vb };
const rocks_in_space::path_buffer rocks_in_space::asteroid::a4 = { 12, a4_vb };

bool rocks_in_space::asteroid::update(float seconds)
{
	if (!m_active)
	{
		return false;
	}
	m_physics.update(seconds);
	return true;
}

rocks_in_space::asteroid_destruction rocks_in_space::asteroid::destroy()
{
	m_active = false;
	if (m_size == big_asteroid_size)	return{ big_asteroid_score, medium_asteroid_size, &m_physics };
	if (m_size == medium_asteroid_size) return{ medium_asteroid_score, small_asteroid_size, &m_physics };
	return{ small_asteroid_score, 0.0, nullptr };
}

