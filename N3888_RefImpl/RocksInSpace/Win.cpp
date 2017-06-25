#include "Input.h"
#include "Game.h"

#include <Windows.h>

namespace
{
	auto anti_clockwise_key = 'Q';
	auto clockwise_key = 'W';
	auto thrust_key = 'U';
	auto fire_key = 'I';
	auto hyperspace_key = 'O';
}

void asteroids::get_key_states()
{
	press() = { GetKeyState(anti_clockwise_key) < 0, GetKeyState(clockwise_key) < 0, GetKeyState(thrust_key) < 0, GetKeyState(fire_key) < 0, GetKeyState(hyperspace_key) < 0 };
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	asteroids::main();
}
