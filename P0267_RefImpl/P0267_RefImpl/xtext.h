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

			basic_text_props(float scl = 1.0f, font_size_units fsu = font_size_units::points, float fontsize = -1.0f, bool kern = true, font_antialias aa = font_antialias::antialias, font_stretching stretch = font_stretching::normal, bool strike_through = false, font_line fl = font_line::none) noexcept;

			void scale(float s) noexcept; // 1.0f means no scaling. Default value is 1.0f. Values less than or equal to 0.0f are invalid.
			void font_size(font_size_units u, float sz) noexcept; // This will override the font's point size unless it's set of a value less than or equal to 0.0f. Default value is -1.0f.
			void kerning(bool k) noexcept;
			void antialiasing(font_antialias aa) noexcept;
			void stretching(font_stretching fs) noexcept;
			void strike_through(bool st) noexcept;
			void line(font_line fa) noexcept;
			//void letter_spacing(float s) noexcept;
			//void word_spacing(float s) noexcept;

			float scale() const noexcept;
			float font_size() const noexcept;
			font_size_units size_units() const noexcept;
			bool kerning() const noexcept;
			font_antialias antialiasing() const noexcept;
			font_stretching stretching() const noexcept;
			bool strike_through() const noexcept;
			font_line line() const noexcept;
			//float letter_spacing() const noexcept;
			//float word_spacing() const noexcept;
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

			basic_font(string family, font_size_units fsu, float size, generic_font_names gfn, font_weight fw = font_weight::normal, font_style fs = font_style::normal, bool merging = true);
			basic_font(::std::filesystem::path file, font_size_units fsu, float size, font_weight fw = font_weight::normal, font_style fs = font_style::normal, bool merging = true);
			basic_font(generic_font_names gfn, font_size_units fsu, float size, font_weight fw = font_weight::normal, font_style fs = font_style::normal);

			void font_size(font_size_units fsu, float size) noexcept;
			void merging(bool m) noexcept;

			float font_size() const noexcept;
			string family() const noexcept;
			font_size_units size_units() const noexcept;
			font_weight weight() const noexcept;
			font_style style() const noexcept;
			bool merging() const noexcept;
		};

		template <class GraphicsSurfaces>
		class basic_font_database {
		public:
			using data_type = typename GraphicsSurfaces::text::font_database_data_type;
		private:
			data_type _Data;
		public:
			const data_type& data() const noexcept;
			data_type& data() noexcept;

			basic_font_database() noexcept;
			vector<string> get_families() const noexcept;
		};
	}
}