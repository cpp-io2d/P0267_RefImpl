#include "ImplWin.h"
#include "Win32Win.h"

namespace
{
	auto anti_clockwise_key = 'Q';
	auto clockwise_key = 'W';
	auto thrust_key = 'U';
	auto fire_key = 'I';
	auto hyperspace_key = 'O';
}

void rocks_in_space::get_key_states()
{
	press() = { GetKeyState(anti_clockwise_key) < 0, GetKeyState(clockwise_key) < 0, GetKeyState(thrust_key) < 0, GetKeyState(fire_key) < 0, GetKeyState(hyperspace_key) < 0 };
}

#define USER_WINDOW

#if defined(USER_WINDOW)

int CALLBACK WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int)
{
	rocks_in_space::Win32Win w(hInst);
	return w.Run();
}

#else


int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	rocks_in_space::ImplWin w;
	return w.Run();
}
#endif
