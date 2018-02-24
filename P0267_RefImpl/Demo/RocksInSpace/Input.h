#pragma once

namespace rocks_in_space
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
	bool do_anti_clockwise();
	bool do_clockwise();
	bool do_thrust();
	bool do_fire();
	bool do_hyperspace();

	keypress& press();
}
