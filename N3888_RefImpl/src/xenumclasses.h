#pragma once

namespace std::experimental::io2d {
	inline namespace v1 {

		enum class format {
			invalid,
			argb32,
			xrgb32,
			a8,
			rgb16_565,
			rgb30
		};

		enum class scaling {
			letterbox,      // Same as uniform except that the display_surface is cleared using the letterbox brush first
			uniform,        // Maintain aspect ratio and center as needed, ignoring side areas that are not drawn to
			fill_uniform,   // Maintain aspect ratio but fill entire display (some content may not be shown)
			fill_exact,     // Ignore aspect ratio and use (possibly non-uniform) scale to fill exactly
			none            // Do not scale.
		};

	}
}