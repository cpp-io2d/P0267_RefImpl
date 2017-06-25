#pragma once

namespace asteroids
{
	constexpr auto playing_field_width{ 640.0 };
	constexpr auto playing_field_height{ 480.0 };
	constexpr auto max_missiles{ 4 };

	constexpr auto big_asteroid_score{ 10 };
	constexpr auto medium_asteroid_score{ 20 };
	constexpr auto small_asteroid_score{ 40 };

	constexpr auto big_asteroid_size{ 5.0 };
	constexpr auto medium_asteroid_size{ 2.5 };
	constexpr auto small_asteroid_size{ 1.25 };

	constexpr auto initial_speed{ 0.1 };

	constexpr auto spin_left{ 0.01 };
	constexpr auto spin_right{ -0.01 };
	constexpr auto thrust_force{ 0.001 };

	constexpr auto missile_travel_distance_per_tick{ 1.0 };
	constexpr auto max_missile_age{ 30.0 };
}