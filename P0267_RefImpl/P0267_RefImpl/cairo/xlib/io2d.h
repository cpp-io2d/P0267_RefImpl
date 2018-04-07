#pragma once

#ifndef _IO2D_H_
#define _IO2D_H_

//#include "io2d_cairo_xlib_frontend.h"
//#include "xcairo.h"
//#include "io2d_cairo_xlib_surfaces.h"
//#include "io2d_cairo_xlib_output_surfaces.h"
//#include "io2d_cairo_xlib_unmanaged_output_surfaces.h"
//#include "io2d_cairo_xlib_surfaces_impl.h"

#include "io2d_cairo_xlib.h"

namespace std::experimental::io2d {
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
        using output_surface = basic_output_surface<default_graphics_surfaces>;
        using path_builder = basic_path_builder<default_graphics_surfaces>;
        using point_2d = basic_point_2d<default_graphics_math>;
        using render_props = basic_render_props<default_graphics_surfaces>;
        using stroke_props = basic_stroke_props<default_graphics_surfaces>;
        using unmanaged_output_surface = basic_unmanaged_output_surface<default_graphics_surfaces>;
    }
}
#endif
