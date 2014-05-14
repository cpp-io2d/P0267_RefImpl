#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

namespace std {
	namespace experimental {
		namespace drawing {
			path _Make_path_from_native_handle(path::native_handle_type nh) {
				path_builder result;
				for (auto i = 0; i < nh->num_data; i += nh->data[i].header.length) {
					auto pathDataType = _Cairo_path_data_type_t_to_path_data_type(nh->data[i].header.type);
                    switch (pathDataType)
                    {
                    case std::experimental::drawing::path_data_type::move_to:
                        result.move_to({ nh->data[i + 1].point.x, nh->data[i + 1].point.y });
                        break;
                    case std::experimental::drawing::path_data_type::line_to:
                        result.line_to({ nh->data[i + 1].point.x, nh->data[i + 1].point.y });
                        break;
                    case std::experimental::drawing::path_data_type::curve_to:
                        result.curve_to(
                        { nh->data[i + 1].point.x, nh->data[i + 1].point.y },
                        { nh->data[i + 2].point.x, nh->data[i + 2].point.y },
                        { nh->data[i + 3].point.x, nh->data[i + 3].point.y }
                        );
                        break;
                    case std::experimental::drawing::path_data_type::close_path:
                        result.close_path();
                        break;
                    default:
                        break;
                    }
				}
				return result.get_path();
			}

			render_surface make_surface(surface::native_handle_type nh) {
				return render_surface(nh);
			}

			render_surface make_surface(format fmt, int width, int height) {
				return render_surface(fmt, width, height);
			}

			int format_stride_for_width(format format, int width) {
				return cairo_format_stride_for_width(_Format_to_cairo_format_t(format), width);
			}
		}
	}
}