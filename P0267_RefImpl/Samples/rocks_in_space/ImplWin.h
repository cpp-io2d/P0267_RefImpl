#pragma once

#include "Game.h"

namespace rocks_in_space {
	class ImplWin
	{
	public:
		ImplWin(int w = 640, int h = 480, format fmt = format::argb32, scaling scl = scaling::letterbox);

		int		Run();


	private:
		game				m_game;
		output_surface		m_outputSfc;
	};
}