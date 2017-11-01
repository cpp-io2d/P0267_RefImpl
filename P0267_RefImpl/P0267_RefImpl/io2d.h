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

#include "xbrushes.h"
#include "xcolor.h"
#include "xdiagnostics.h"
#include "xgraphicsmath.h"
#include "xgraphicsmathfloat.h"
#include "xinput.h"
#include "xio2d.h"
#include "xpath.h"
#include "xsurfaces_enums.h"
#include "xsurfaces.h"
#include "xtext.h"

#include "xbrushes_impl.h"
#include "xgraphicsmath_impl.h"
#include "xgraphicsmathfloat_impl.h"
#include "xio2d_impl.h"
#include "xpath_impl.h"
#include "xpathbuilder_impl.h"
#include "xsurfaces_impl.h"
#include "xsurfacesprops_impl.h"

#include "xsystemheaders.h"
#include "xcairo.h"
#include "xcairo_helpers.h"
#include "xcairo_impl.h"

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				using default_graphics_math = _Graphics_math_float_impl;
				using default_graphics_surfaces = _Cairo::_Cairo_graphics_surfaces<default_graphics_math>;
				
				using bounding_box = basic_bounding_box<default_graphics_math>;
				using brush = basic_brush<default_graphics_surfaces>;
				using brush_props = basic_brush_props<default_graphics_surfaces>;
				using circle = basic_circle<default_graphics_math>;
				using clip_props = basic_clip_props<default_graphics_surfaces>;
				using dashes = basic_dashes<default_graphics_surfaces>;
				using display_point = basic_display_point<default_graphics_math>;
				using figure_items = basic_figure_items<default_graphics_surfaces>;
				using image_surface = basic_image_surface<default_graphics_surfaces>;
				using interpreted_path = basic_interpreted_path<default_graphics_surfaces>;
				using mask_props = basic_mask_props<default_graphics_surfaces>;
				using matrix_2d = basic_matrix_2d<default_graphics_math>;
				// display_surface type alias for backwards compatibility only. It will be steadily replaced in existing projects.
				using display_surface = basic_output_surface<default_graphics_surfaces>;
				using output_surface = basic_output_surface<default_graphics_surfaces>;
				using path_builder = basic_path_builder<default_graphics_surfaces>;
				using point_2d = basic_point_2d<default_graphics_math>;
				using render_props = basic_render_props<default_graphics_surfaces>;
				using stroke_props = basic_stroke_props<default_graphics_surfaces>;
				using unmanaged_output_surface = basic_unmanaged_output_surface<default_graphics_surfaces>;
			}
		}
	}
}
#endif
