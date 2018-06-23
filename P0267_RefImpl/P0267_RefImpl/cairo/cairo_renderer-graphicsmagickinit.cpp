#include "io2d.h"
#include "xcairo.h"
#include <mutex>

#if !defined(__EMSCRIPTEN__)

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

#endif // __EMSCRIPTEN__
