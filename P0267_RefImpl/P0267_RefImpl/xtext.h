#pragma once
#include <string>
#include <filesystem>
#include "xtext_enums.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		template <class GraphicsSurfaces>
		class basic_text_props {
		public:
			using data_type = typename GraphicsSurfaces::text::text_props_data_type;
		private:
			data_type _Data;
		public:
			const data_type& data() const noexcept;
			data_type& data() noexcept;

			basic_text_props(float scl = 1.0f, float pointsize = -1.0f, bool kern = true, bool hint = font_hinting::default_hinting, font_antialias aa = font_antialias::antialias, font_stretching stretch = font_stretching::normal, bool strike_through = false, font_extras extras = font_extras::none) noexcept;

			void kerning(bool k) noexcept;
			bool kerning() const noexcept;

			void hinting(font_hinting fh) noexcept;
			font_hinting hinting() const noexcept;

			void antialiasing(font_antialias aa) noexcept;
			font_antialias antialiasing() const noexcept;

			void stretching(font_stretching fs) noexcept;
			font_stretching stretching() const noexcept;

			void strike_through(bool st) noexcept;
			bool strike_through() const noexcept;

			void extras(font_extras fe) noexcept;
			font_extras extras() const noexcept;

			void scale(float s) noexcept; // 1.0f means no scaling. Default value is 1.0f. Values less than or equal to 0.0f are invalid.
			float scale() const noexcept;

			void point_size(float sz) noexcept; // This will override the font's point size unless it's set of a value less than or equal to 0.0f. Default value is -1.0f.
			float point_size() const noexcept;
		};

		template <class GraphicsSurfaces>
		class basic_font {
		public:
			using data_type = typename GraphicsSurfaces::text::font_data_type;
		private:
			data_type _Data;
		public:
			const data_type& data() const noexcept;
			data_type& data() noexcept;

			basic_font(string name, float pointsize, font_weight fw = font_weight::normal, font_style fs = font_style::normal);
			basic_font(::std::filesystem::path file, float pointsize, font_weight fw = font_weight::normal, font_style fs = font_style::normal);

			void point_size(float size) noexcept;
			float point_size() const noexcept;

			void weight(font_weight fw) noexcept;
			font_weight weight() const noexcept;

			void style(font_style fs) noexcept;
			font_style style() const noexcept;
		};
	}
}