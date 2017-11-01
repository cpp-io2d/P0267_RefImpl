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
	auto x = m_outputSfc.display_dimensions().x();
	if (x > 10000) {
		return 0;
	}
	return m_outputSfc.begin_show();
}
