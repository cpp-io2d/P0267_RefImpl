#include "xcairo.h"
#include <mutex>

#ifdef _IO2D_Has_Magick

#include <magick/api.h>

static ::std::once_flag _Init_graphics_magick_once_flag;

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Cairo {

			void _Init_graphics_magic() {
				::std::call_once(_Init_graphics_magick_once_flag, []() {
					InitializeMagick(nullptr);
				});
			}
		}
	}
}

#endif // _IO2D_Has_Magick
