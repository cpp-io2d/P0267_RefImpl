#pragma once

namespace asteroids
{
	struct keypress
	{
		bool anti_clockwise_key_press = false;
		bool clockwise_key_press = false;
		bool thrust_key_press = false;
		bool fire_key_press = false;
		bool hyperspace_key_press = false;
	};

	void get_key_states();
	bool anti_clockwise();
	bool clockwise();
	bool thrust();
	bool fire();
	bool hyperspace();

	keypress& press();
}
