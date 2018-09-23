#pragma once

#include <io2d.h>

namespace rocks_in_space
{
	constexpr auto playing_field_width{ 640.0F };
	constexpr auto playing_field_height{ 480.0F };
	constexpr auto max_missiles{ 4 };

	constexpr auto big_asteroid_score{ 10 };
	constexpr auto medium_asteroid_score{ 20 };
	constexpr auto small_asteroid_score{ 40 };

	constexpr auto big_asteroid_size{ 5.0F };
	constexpr auto medium_asteroid_size{ 2.5F };
	constexpr auto small_asteroid_size{ 1.25F };

	constexpr auto initial_speed{ 25.0F };

	constexpr auto spin_left{ std::experimental::io2d::tau<float> };
	constexpr auto spin_right{ -std::experimental::io2d::tau<float> };
	constexpr auto thrust{ 150.0F };
	constexpr auto max_ship_speed{ 300.0F };

	constexpr auto missile_speed{ 250.0F };
	constexpr auto missile_lifespan{ 1.5F };

	constexpr auto asteroid_sweep_lookahead{ 2.0f };
}
