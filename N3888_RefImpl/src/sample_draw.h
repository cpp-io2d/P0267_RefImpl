#pragma once
#ifndef SAMPLE_DRAW_H
#define SAMPLE_DRAW_H

namespace std {
	namespace experimental {
		namespace io2d {
#if ((__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190021510))
			inline namespace v1 {
#endif
				class display_surface;
#if ((__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190021510))
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
