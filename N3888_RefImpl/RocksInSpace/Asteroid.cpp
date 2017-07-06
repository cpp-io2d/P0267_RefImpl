#include "Asteroid.h"
#include "Constants.h"

namespace
{
	using rocks_in_space::path_vertices;
	using rocks_in_space::vector_2d;

	path_vertices a1_vb = { vector_2d{ -2, 4 },{ 2, -2 },{ 2, 2 },{ 2, -2 },{ -1, -2 },{ 1, -2 },{ -3, -2 },{ -3, 0 },{ -2, 2 },{ 0, 4 },{ 2, 2 } };
	path_vertices a2_vb = { vector_2d{ -2, 4 },{ 2, -1 },{ 2, 1 },{ 2, -2 },{ -2, -1 },{ 2, -2 },{ -2, -3 },{ -3, 1 },{ -1, -1 },{ -2, 2 },{ 1, 2 },{ -1, 2 },{ 2, 2 } };
	path_vertices a3_vb = { vector_2d{ -2, 4 },{ 3, 0 },{ 3, -2 },{ 0, -1 },{ -3, -1 },{ 3, -2 },{ -2, -2 },{ -4, 0 },{ -2, 3 },{ 0, 3 },{ 3, 0 },{ -1, 2 } };
	path_vertices a4_vb = { vector_2d{ -1, 4 },{ 3, 0 },{ 2, -3 },{ 0, -2 },{ -2, -3 },{ -2, 0 },{ 0, 3 },{ -2, -3 },{ -2, 3 },{ 2, 1 },{ -2, 1 },{ 3, 3 } };
}

const rocks_in_space::path_buffer rocks_in_space::asteroid::a1 = { 11, a1_vb };
const rocks_in_space::path_buffer rocks_in_space::asteroid::a2 = { 13, a2_vb };
const rocks_in_space::path_buffer rocks_in_space::asteroid::a3 = { 12, a3_vb };
const rocks_in_space::path_buffer rocks_in_space::asteroid::a4 = { 12, a4_vb };



void rocks_in_space::asteroid::update()
{
	if (m_active) m_physics.update();
}

rocks_in_space::asteroid_destruction rocks_in_space::asteroid::destroy()
{
	m_active = false;
	if (m_size == big_asteroid_size)	return{ big_asteroid_score, medium_asteroid_size, &m_physics };
	if (m_size == medium_asteroid_size) return{ medium_asteroid_score, small_asteroid_size, &m_physics };
	return{ small_asteroid_score, 0.0, nullptr };
}

void rocks_in_space::asteroid::draw(std::experimental::io2d::display_surface& ds) const
{
	using namespace std::experimental::io2d;

	if (!m_active) return;

	auto path = path_builder<>{};
	path.clear();
	auto v = m_physics.position() + (m_path.m_vertices[0]);
	path.new_path(screen_space(v));
	std::for_each(&m_path.m_vertices[1], &m_path.m_vertices[m_path.m_count], [&](const auto& vert)
	{
		v += vert;
		path.line(screen_space(v));
	});
	path.close_path();

	ds.stroke(brush{ rgba_color::gray }, path);
}

