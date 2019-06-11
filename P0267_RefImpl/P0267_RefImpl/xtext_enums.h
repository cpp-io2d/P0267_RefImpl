#pragma once

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				enum class font_size_units {
					points,
					pixels
				};
				enum class font_weight {
					thin,
					extra_light,
					light,
					normal,
					medium,
					semi_bold,
					bold,
					extra_bold,
					black
				};

				enum class font_capitalization {
					mixed_case,
					default_capitalization = mixed_case,
					upper,
					lower,
					small_caps,
					first_character
				};

				enum class font_hinting {
					default_hinting,
					none,
					vertical,
					full
				};

				enum class font_stretching {
					ultra_condensed,
					extra_condensed,
					condensed,
					semi_condensed,
					normal,
					semi_expanded,
					expanded,
					extra_expanded,
					ultra_expanded,
					initial
				};

				enum class font_style {
					normal,
					italic,
					oblique,
					initial
				};

				enum class font_line {
					none,
					underline,
					overline
				};

				enum class font_antialias {
					none,
					antialias, // prefer antialiasing, leaving it up to the implementation to decide on gray vs. subpixel
					gray, // use gray antialiasing if available, otherwise none
					subpixel, // use subpixel antialiasing if available, otherwise none
					prefer_gray, // prefer gray antialiasing if available, otherwise use subpixel if available, none if neither are available
					prefer_subpixel // prefer subpixel antialiasing if available, otherwise use gray if available, none if neither are available
				};
			}
		}
	}
}