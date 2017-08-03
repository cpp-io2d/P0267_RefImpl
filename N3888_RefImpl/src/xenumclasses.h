#pragma once

namespace std::experimental::io2d {
	inline namespace v1 {
		enum class wrap_mode;
		enum class filter;
		enum class brush_type;
		enum class antialias;
		enum class fill_rule;
		enum class line_cap;
		enum class line_join;
		enum class compositing_op;
		enum class format;
		enum class scaling;
		enum class refresh_rate;
		enum class image_file_format;

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
			bevel,
			miter_or_bevel
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
			rgb16_565,
			rgb30
		};

		enum class wrap_mode {
			none,
			repeat,
			reflect,
			pad
		};

		enum class filter {
			fast,
			good,
			best,
			nearest,
			bilinear
		};

		enum class brush_type {
			solid_color,
			surface,
			linear,
			radial
		};

		enum class scaling {
			letterbox, // Same as uniform except that the display_surface is cleared using the letterbox brush first
			uniform, // Maintain aspect ratio and center as needed, ignoring side areas that are not drawn to
			fill_uniform, // Maintain aspect ratio but fill entire display (some content may not be shown)
			fill_exact, // Ignore aspect ratio and use (possibly non-uniform) scale to fill exactly
			none // Do not scale.
		};

		enum class refresh_rate {
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