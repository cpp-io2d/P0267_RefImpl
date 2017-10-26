#include "ImplWin.h"
#include <memory>


int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	rocks_in_space::ImplWin w;
	return w.Run();
}

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


rocks_in_space::ImplWin::ImplWin(int w, int h, format fmt, scaling scl)
	: m_game()
	, m_outputSfc(w, h, fmt, scl)
{
}

int rocks_in_space::ImplWin::Run()
{
	m_outputSfc.draw_callback([&](output_surface& os) {m_game.update<output_surface>(os); });
	return m_outputSfc.begin_show();
}
