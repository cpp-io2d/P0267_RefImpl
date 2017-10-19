#pragma once
#ifndef SAMPLE_DRAW_H
#define SAMPLE_DRAW_H
#include "io2d.h"

class sample_draw {
public:
	void operator()(::std::experimental::io2d::output_surface& rs);
};

#endif
