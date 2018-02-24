#include "Input.h"

namespace
{
	auto fire_down = false;
	auto hyperspace_down = false;

	bool bounce_check(const bool& key, bool& down)
	{
		if (key && !down)
		{
			down = true;
			return true;
		}
		down = key;
		return false;
	}
}

rocks_in_space::keypress& rocks_in_space::press()
{
	static keypress k;
	return k;
}

bool rocks_in_space::do_anti_clockwise()
{
	return press().anti_clockwise_key_press;
}

bool rocks_in_space::do_clockwise()
{
	return press().clockwise_key_press;
}

bool rocks_in_space::do_thrust()
{
	return press().thrust_key_press;
}

bool rocks_in_space::do_fire()
{
	return bounce_check(press().fire_key_press, fire_down);
}

bool rocks_in_space::do_hyperspace()
{
	return bounce_check(press().hyperspace_key_press, hyperspace_down);
}
