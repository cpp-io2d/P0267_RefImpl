#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

namespace std {
	namespace experimental {
		namespace drawing {
			int format_stride_for_width(format format, int width) {
				return cairo_format_stride_for_width(_Format_to_cairo_format_t(format), width);
			}

			surface make_surface(surface::native_handle_type nh) {
				return surface(nh);
			}

			surface make_surface(format fmt, int width, int height) {
				return surface(fmt, width, height);
			}
		}
	}
}