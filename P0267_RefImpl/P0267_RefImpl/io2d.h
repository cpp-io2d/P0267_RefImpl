#pragma once

#ifndef _IO2D_
#define _IO2D_

#define __cpp_lib_experimental_io2d 201710

#include <memory>
#include <functional>
#include <utility>
#include <exception>
#include <vector>
#include <string>
#include <algorithm>
#include <system_error>
#include <cstdint>
#include <atomic>
#include <variant>
#include <optional>
#include <cmath>
#include <type_traits>
#include <initializer_list>
#include <cmath>
#include <chrono>

#include "xio2d.h"

#if defined(_Filesystem_support_test)
#include <filesystem>
#endif

#include "xcolor.h"
#include "xgraphicsmath.h"
#include "xtext.h"
#include "xpath.h"
#include "xbrushes.h"
#include "xsurfaces.h"
#include "xinput.h"
#include "xgraphicsmathfloat.h"
#include "xcairo.h"

#include "xio2d_impl.h"
#include "xbrushes_impl.h"
#include "xpath_impl.h"
#include "xpathbuilder_impl.h"
#include "xsurfaces_impl.h"
#include "xsurfacesprops_impl.h"
#include "xgraphicsmath_impl.h"
#include "xgraphicsmathfloat_impl.h"
#include "xcairo_impl.h"

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				using bounding_box = basic_bounding_box<_Graphics_math_float_impl>;
				using brush = basic_brush<_Cairo::_Cairo_graphics_surfaces<_Graphics_math_float_impl>>;
				using brush_props = basic_brush_props<_Cairo::_Cairo_graphics_surfaces<_Graphics_math_float_impl>>;
				using circle = basic_circle<_Graphics_math_float_impl>;
				using clip_props = basic_clip_props<_Cairo::_Cairo_graphics_surfaces<_Graphics_math_float_impl>>;
				using dashes = basic_dashes<_Cairo::_Cairo_graphics_surfaces<_Graphics_math_float_impl>>;
				using display_point = basic_display_point<_Graphics_math_float_impl>;
				using figure_items = basic_figure_items<_Graphics_math_float_impl>;
				using image_surface = basic_image_surface<_Cairo::_Cairo_graphics_surfaces<_Graphics_math_float_impl>>;
				using interpreted_path = basic_interpreted_path<_Cairo::_Cairo_graphics_surfaces<_Graphics_math_float_impl>>;
				using mask_props = basic_mask_props<_Cairo::_Cairo_graphics_surfaces<_Graphics_math_float_impl>>;
				using matrix_2d = basic_matrix_2d<_Graphics_math_float_impl>;
				// display_surface type alias for backwards compatibility only. It will be steadily replaced in existing projects.
				using display_surface = basic_output_surface<_Cairo::_Cairo_graphics_surfaces<_Graphics_math_float_impl>>;
				using output_surface = basic_output_surface<_Cairo::_Cairo_graphics_surfaces<_Graphics_math_float_impl>>;
				using path_builder = basic_path_builder<_Graphics_math_float_impl>;
				using point_2d = basic_point_2d<_Graphics_math_float_impl>;
				using render_props = basic_render_props<_Cairo::_Cairo_graphics_surfaces<_Graphics_math_float_impl>>;
				using stroke_props = basic_stroke_props<_Cairo::_Cairo_graphics_surfaces<_Graphics_math_float_impl>>;
				using unmanaged_output_surface = basic_unmanaged_output_surface<_Cairo::_Cairo_graphics_surfaces<_Graphics_math_float_impl>>;
			}
		}
	}
}
#endif
