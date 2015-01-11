#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				const ::std::error_category& io2d_category() noexcept{
					static io2d_error_category ec;
					return ec;
				}

				display_surface make_surface(int preferredWidth, int preferredHeight, format preferredFormat) {
					return display_surface(preferredWidth, preferredHeight, preferredFormat);
				}

				surface make_surface(surface::native_handle_type nh, format fmt) {
					return surface(nh, fmt, _Content_for_format(fmt));
				}

				image_surface make_image_surface(format fmt, int width, int height) {
					return image_surface(fmt, width, height);
				}

				int format_stride_for_width(format format, int width) {
					return cairo_format_stride_for_width(_Format_to_cairo_format_t(format), width);
				}
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}

namespace std {
	::std::error_condition make_error_condition(io2d_error err) noexcept{
		return ::std::error_condition(static_cast<int>(err), io2d_category());
	}

		::std::error_code make_error_code(cairo_status_t code) noexcept{
		return ::std::error_code(code, io2d_category());
	}
}
