#pragma once
#ifndef SAMPLE_DRAW_H
#define SAMPLE_DRAW_H
#include "xio2d.h"

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				class display_surface;
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}

class sample_draw {
public:
	void operator()(::std::experimental::io2d::display_surface& rs);
};

#endif
