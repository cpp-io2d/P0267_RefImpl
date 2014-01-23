#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

namespace std {
	namespace experimental {
		namespace drawing {
			path _Make_path(path::native_handle_type nh) {
				path result;
				for (auto i = 0; i < nh->num_data; i += nh->data[i].header.length) {
					auto pathDataType = _Cairo_path_data_type_t_to_path_data_type(nh->data[i].header.type);
					path_data pd;
					pd.header.type = pathDataType;
					auto pdLength = pd.header.length = nh->data[i].header.length;
					result.data.push_back(pd);
					// We already pushed the first element so j starts at 1 not 0.
					for (auto j = 1; j < pdLength; ++j) {
						pd.point.x = nh->data[i + j].point.x;
						pd.point.y = nh->data[i + j].point.y;
						result.data.push_back(pd);
					}
				}
				return result;
			}

			surface make_surface(surface::native_handle_type nh) {
				return surface(nh);
			}

			int format_stride_for_width(format format, int width) {
				return cairo_format_stride_for_width(_Format_to_cairo_format_t(format), width);
			}
		}
	}
}