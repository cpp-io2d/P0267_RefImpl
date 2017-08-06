#pragma once

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

	constexpr auto initial_speed{ 0.1F };

	constexpr auto spin_left{ 0.01F };
	constexpr auto spin_right{ -0.01F };
	constexpr auto thrust_force{ 0.001F };
	constexpr auto max_ship_speed{ 0.9F };

	constexpr auto missile_travel_distance_per_tick{ 1.0F };
	constexpr auto max_missile_age{ 30.0F };
}