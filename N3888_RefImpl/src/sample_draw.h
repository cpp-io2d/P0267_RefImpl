#pragma once
#include "io2d.h"

class sample_draw
{
public:
	void operator()(::std::experimental::io2d::surface& rs, double elapsedTimeInMilliseconds);
};

