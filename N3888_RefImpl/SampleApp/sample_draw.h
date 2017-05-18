#pragma once
#ifndef SAMPLE_DRAW_H
#define SAMPLE_DRAW_H
#include "io2d.h"

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				class display_surface;
			}
		}
	}
}

class sample_draw {
public:
	void operator()(::std::experimental::io2d::display_surface& rs);
};

#endif
