#pragma once

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				enum class antialias {
					none,
					fast,
					good,
					best
				};

				enum class fill_rule {
					winding,
					even_odd
				};

				enum class line_cap {
					none,
					round,
					square
				};

				enum class line_join {
					miter,
					round,
					bevel
				};

				enum class compositing_op {
					over,
					clear,
					source,
					in,
					out,
					atop,
					dest,
					dest_over,
					dest_in,
					dest_out,
					dest_atop,
					xor_op,
					add,
					saturate,
					multiply,
					screen,
					overlay,
					darken,
					lighten,
					color_dodge,
					color_burn,
					hard_light,
					soft_light,
					difference,
					exclusion,
					hsl_hue,
					hsl_saturation,
					hsl_color,
					hsl_luminosity
				};

				enum class format {
					invalid,
					argb32,
					xrgb32,
					a8,
				};

				enum class scaling {
					letterbox,      // Same as uniform except that the display_surface is cleared using the letterbox brush first
					uniform,        // Maintain aspect ratio and center as needed, ignoring side areas that are not drawn to
					fill_uniform,   // Maintain aspect ratio but fill entire display (some content may not be shown)
					fill_exact,     // Ignore aspect ratio and use (possibly non-uniform) scale to fill exactly
					none            // Do not scale.
				};

				enum class refresh_style {
					as_needed,
					as_fast_as_possible,
					fixed
				};

				enum class image_file_format {
					unknown,
					png,
					jpeg,
					tiff
				};
			}
		}
	}
}
