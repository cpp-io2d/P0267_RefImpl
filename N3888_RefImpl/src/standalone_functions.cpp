#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

namespace std {
	namespace experimental {
		namespace io2d {
#if (__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190021510)
			inline namespace v1 {
#endif
				const ::std::error_category& io2d_category() {
					static io2d_error_category ec;
					return ec;
				}

				surface make_surface(surface::native_handle_type nh) {
					return surface(nh);
				}

				image_surface make_image_surface(format fmt, int width, int height) {
					return image_surface(fmt, width, height);
				}

				int format_stride_for_width(format format, int width) {
					return cairo_format_stride_for_width(_Format_to_cairo_format_t(format), width);
				}
#if (__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190021510)
			}
#endif
		}
	}
	::std::error_condition make_error_condition(io2d_error err) {
		return ::std::error_condition(static_cast<int>(err), io2d_category());
	}

	::std::error_code make_error_code(cairo_status_t code) {
		return ::std::error_code(code, io2d_category());
	}
}