#pragma once

#include "xtext.h"

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				template<class GraphicsSurfaces>
				inline const typename basic_text_props<GraphicsSurfaces>::data_type& std::experimental::io2d::v1::basic_text_props<GraphicsSurfaces>::data() const noexcept {
					return _Data;
				}
				template<class GraphicsSurfaces>
				inline typename basic_text_props<GraphicsSurfaces>::data_type& basic_text_props<GraphicsSurfaces>::data() noexcept {
					return _Data;
				}
				template<class GraphicsSurfaces>
				inline basic_text_props<GraphicsSurfaces>::basic_text_props(float scl, font_size_units fsu, float fontsize, bool kern, font_antialias aa, font_stretching stretch, bool strike_through, font_line fl) noexcept : _Data(GraphicsSurfaces::text::create_text_props(scl, fsu, fontsize, kern, aa, stretch, strike_through, fl)) {
				}
				template<class GraphicsSurfaces>
				inline void basic_text_props<GraphicsSurfaces>::scale(float s) noexcept {
					GraphicsSurfaces::text::scale(_Data, s);
				}
				template<class GraphicsSurfaces>
				inline float basic_text_props<GraphicsSurfaces>::scale() const noexcept {
					return GraphicsSurfaces::text::scale(_Data);
				}
				template<class GraphicsSurfaces>
				inline void basic_text_props<GraphicsSurfaces>::font_size(font_size_units u, float sz) noexcept {
					GraphicsSurfaces::text::font_size(_Data, u, sz);
				}
				template<class GraphicsSurfaces>
				inline float basic_text_props<GraphicsSurfaces>::font_size() const noexcept {
					return GraphicsSurfaces::text::font_size(_Data);
				}
				template<class GraphicsSurfaces>
				inline font_size_units basic_text_props<GraphicsSurfaces>::size_units() const noexcept {
					return GraphicsSurfaces::text::size_units(_Data);
				}
				template<class GraphicsSurfaces>
				inline void basic_text_props<GraphicsSurfaces>::kerning(bool k) noexcept {
					GraphicsSurfaces::text::kerning(_Data, k);
				}
				template<class GraphicsSurfaces>
				inline bool basic_text_props<GraphicsSurfaces>::kerning() const noexcept {
					return GraphicsSurfaces::text::kerning(_Data);
				}
				//template<class GraphicsSurfaces>
				//inline void basic_text_props<GraphicsSurfaces>::hinting(font_hinting fh) noexcept {
				//	GraphicsSurfaces::text::hinting(_Data, fh);
				//}
				//template<class GraphicsSurfaces>
				//inline font_hinting basic_text_props<GraphicsSurfaces>::hinting() const noexcept {
				//	return GraphicsSurfaces::text::hinting(_Data);
				//}
				template<class GraphicsSurfaces>
				inline void basic_text_props<GraphicsSurfaces>::antialiasing(font_antialias aa) noexcept {
					GraphicsSurfaces::text::antialiasing(_Data, aa);
				}
				template<class GraphicsSurfaces>
				inline font_antialias basic_text_props<GraphicsSurfaces>::antialiasing() const noexcept {
					return GraphicsSurfaces::text::antialiasing(_Data);
				}
				template<class GraphicsSurfaces>
				inline void basic_text_props<GraphicsSurfaces>::stretching(font_stretching fs) noexcept {
					GraphicsSurfaces::text::stretching(_Data, fs);
				}
				template<class GraphicsSurfaces>
				inline font_stretching basic_text_props<GraphicsSurfaces>::stretching() const noexcept {
					return GraphicsSurfaces::text::stretching(_Data);
				}
				template<class GraphicsSurfaces>
				inline void basic_text_props<GraphicsSurfaces>::strike_through(bool st) noexcept {
					GraphicsSurfaces::text::strike_through(_Data, st);
				}
				template<class GraphicsSurfaces>
				inline bool basic_text_props<GraphicsSurfaces>::strike_through() const noexcept {
					return GraphicsSurfaces::text::strike_through(_Data);
				}
				template<class GraphicsSurfaces>
				inline void basic_text_props<GraphicsSurfaces>::line(font_line fa) noexcept {
					GraphicsSurfaces::text::line(_Data, fa);
				}
				template<class GraphicsSurfaces>
				inline font_line basic_text_props<GraphicsSurfaces>::line() const noexcept {
					return GraphicsSurfaces::text::line(_Data);
				}
				//template<class GraphicsSurfaces>
				//inline void basic_text_props<GraphicsSurfaces>::letter_spacing(float s) noexcept {
				//	GraphicsSurfaces::text::letter_spacing(_Data, s);
				//}
				//template<class GraphicsSurfaces>
				//inline float basic_text_props<GraphicsSurfaces>::letter_spacing() const noexcept {
				//	return GraphicsSurfaces::text::letter_spacing();
				//}
				//template<class GraphicsSurfaces>
				//inline void basic_text_props<GraphicsSurfaces>::word_spacing(float s) noexcept {
				//	GraphicsSurfaces::text::word_spacing(_Data, s);
				//}
				//template<class GraphicsSurfaces>
				//inline float basic_text_props<GraphicsSurfaces>::word_spacing() const noexcept {
				//	return GraphicsSurfaces::text::word_spacing(_Data);
				//}

				//
				// basic_font
				//

				template<class GraphicsSurfaces>
				inline const typename basic_font<GraphicsSurfaces>::data_type& basic_font<GraphicsSurfaces>::data() const noexcept {
					return _Data;
				}
				template<class GraphicsSurfaces>
				inline typename basic_font<GraphicsSurfaces>::data_type& basic_font<GraphicsSurfaces>::data() noexcept {
					return _Data;
				}
				template<class GraphicsSurfaces>
				inline basic_font<GraphicsSurfaces>::basic_font(string name, font_size_units fsu, float size, generic_font_names gfn, io2d::font_weight fw, font_style fs, bool merging)
					: _Data(GraphicsSurfaces::text::create_font(name, fsu, size, gfn, fw, fs, merging)) {
				}
				template<class GraphicsSurfaces>
				inline basic_font<GraphicsSurfaces>::basic_font(::std::filesystem::path file, font_size_units fsu, float size, io2d::font_weight fw, font_style fs, bool merging)
					: _Data(GraphicsSurfaces::text::create_font(file, fsu, size, fw, fs, merging)) {
				}
				template<class GraphicsSurfaces>
				inline basic_font<GraphicsSurfaces>::basic_font(generic_font_names gfn, font_size_units fsu, float size, font_weight fw, font_style fs)
					: _Data(GraphicsSurfaces::text::create_font(gfn, fsu, size, fw, fs)) {
				}
				template<class GraphicsSurfaces>
				inline void basic_font<GraphicsSurfaces>::font_size(font_size_units fsu, float size) noexcept {
					GraphicsSurfaces::text::font_size(_Data, fsu, size);
				}
				template<class GraphicsSurfaces>
				inline void basic_font<GraphicsSurfaces>::merging(bool m) noexcept {
					GraphicsSurfaces::text::merging(_Data, m);
				}
				template<class GraphicsSurfaces>
				inline float basic_font<GraphicsSurfaces>::font_size() const noexcept {
					return GraphicsSurfaces::text::font_size(_Data);
				}
				template<class GraphicsSurfaces>
				inline string basic_font<GraphicsSurfaces>::family() const noexcept {
					return GraphicsSurfaces::text::family(_Data);
				}
				template<class GraphicsSurfaces>
				inline font_size_units basic_font<GraphicsSurfaces>::size_units() const noexcept {
					return GraphicsSurfaces::text::size_units(_Data);
				}
				template<class GraphicsSurfaces>
				inline font_weight basic_font<GraphicsSurfaces>::weight() const noexcept {
					return GraphicsSurfaces::text::weight(_Data);
				}
				template<class GraphicsSurfaces>
				inline font_style basic_font<GraphicsSurfaces>::style() const noexcept {
					return GraphicsSurfaces::text::style(_Data);
				}
				template<class GraphicsSurfaces>
				inline bool basic_font<GraphicsSurfaces>::merging() const noexcept {
					return GraphicsSurfaces::text::merging(_Data);
				}

				//
				// basic_font_database
				//

				template<class GraphicsSurfaces>
				inline const typename basic_font_database<GraphicsSurfaces>::data_type& basic_font_database<GraphicsSurfaces>::data() const noexcept {
					return _Data;
				}
				template<class GraphicsSurfaces>
				inline typename basic_font_database<GraphicsSurfaces>::data_type& basic_font_database<GraphicsSurfaces>::data() noexcept {
					return _Data;
				}
				template<class GraphicsSurfaces>
				inline basic_font_database<GraphicsSurfaces>::basic_font_database() noexcept
					: _Data(GraphicsSurfaces::text::create_font_database()) {
				}
				template<class GraphicsSurfaces>
				inline vector<string> basic_font_database<GraphicsSurfaces>::get_families() const noexcept {
					return GraphicsSurfaces::text::get_families(_Data);
				}
			}
		}
	}
}