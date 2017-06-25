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

asteroids::keypress& asteroids::press()
{
	static keypress k;
	return k;
}

bool asteroids::anti_clockwise()
{
	return press().anti_clockwise_key_press;
}

bool asteroids::clockwise()
{
	return press().clockwise_key_press;
}

bool asteroids::thrust()
{
	return press().thrust_key_press;
}

bool asteroids::fire()
{
	return bounce_check(press().fire_key_press, fire_down);
}

bool asteroids::hyperspace()
{
	return bounce_check(press().hyperspace_key_press, hyperspace_down);
}
