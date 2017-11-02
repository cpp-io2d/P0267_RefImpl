#include "ImplWin.h"
#include <memory>

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
