#include "Input.h"
#include "Game.h"

#include <Windows.h>

namespace
{
	constexpr auto anti_clockwise_key = 'Q';
	constexpr auto clockwise_key = 'W';
	constexpr auto thrust_key = 'U';
	constexpr auto fire_key = 'I';
	constexpr auto hyperspace_key = 'O';
}

void rocks_in_space::get_key_states()
{
	press() = { GetKeyState(anti_clockwise_key) < 0, GetKeyState(clockwise_key) < 0, GetKeyState(thrust_key) < 0, GetKeyState(fire_key) < 0, GetKeyState(hyperspace_key) < 0 };
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	rocks_in_space::main();
}
