#pragma once
#include "drawing.h"

class sample_draw
{
public:
	void operator()(::std::experimental::drawing::render_surface& rs, double elapsedTimeInMilliseconds);
};

