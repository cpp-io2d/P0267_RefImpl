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

bool rocks_in_space::anti_clockwise()
{
	return press().anti_clockwise_key_press;
}

bool rocks_in_space::clockwise()
{
	return press().clockwise_key_press;
}

bool rocks_in_space::thrust()
{
	return press().thrust_key_press;
}

bool rocks_in_space::fire()
{
	return bounce_check(press().fire_key_press, fire_down);
}

bool rocks_in_space::hyperspace()
{
	return bounce_check(press().hyperspace_key_press, hyperspace_down);
}
