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
				inline basic_text_props<GraphicsSurfaces>::basic_text_props(float scl, float pointsize, bool kern, bool hint, font_antialias aa, font_stretching stretch, bool strike_through, font_extras extras) noexcept : _Data(scl, pointsize, kern, hint, aa, stretch, strike_through, extras) {
				}
				template<class GraphicsSurfaces>
				inline void basic_text_props<GraphicsSurfaces>::kerning(bool k) noexcept {
					GraphicsSurfaces::text::kerning(_Data, k);
				}
				template<class GraphicsSurfaces>
				inline bool basic_text_props<GraphicsSurfaces>::kerning() const noexcept {
					return GraphicsSurfaces::text::kerning(_Data);
				}
				template<class GraphicsSurfaces>
				inline void basic_text_props<GraphicsSurfaces>::hinting(font_hinting fh) noexcept {
					GraphicsSurfaces::text::hinting(_Data, fh);
				}
				template<class GraphicsSurfaces>
				inline font_hinting basic_text_props<GraphicsSurfaces>::hinting() const noexcept {
					return GraphicsSurfaces::text::hinting(_Data);
				}
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
				inline void basic_text_props<GraphicsSurfaces>::extras(font_extras fe) noexcept {
					GraphicsSurfaces::text::extras(_Data, fe);
				}
				template<class GraphicsSurfaces>
				inline font_extras basic_text_props<GraphicsSurfaces>::extras() const noexcept {
					return GraphicsSurfaces::text::extras(_Data);
				}
				template<class GraphicsSurfaces>
				inline void basic_text_props<GraphicsSurfaces>::scale(float s) noexcept {
					if (s > 0.0f) {
						GraphicsSurfaces::text::scale(_Data, s);
					}
				}
				template<class GraphicsSurfaces>
				inline float basic_text_props<GraphicsSurfaces>::scale() const noexcept {
					return GraphicsSurfaces::text::scale(_Data);
				}
				template<class GraphicsSurfaces>
				inline void basic_text_props<GraphicsSurfaces>::point_size(float sz) noexcept {
					GraphicsSurfaces::text::point_size(_Data, sz);
				}
				template<class GraphicsSurfaces>
				inline float basic_text_props<GraphicsSurfaces>::point_size() const noexcept {
					return GraphicsSurfaces::text::point_size(_Data);
				}
				template<class GraphicsSurfaces>
				inline const typename basic_font<GraphicsSurfaces>::data_type& basic_font<GraphicsSurfaces>::data() const noexcept {
					return _Data;
				}
				template<class GraphicsSurfaces>
				inline typename basic_font<GraphicsSurfaces>::data_type& basic_font<GraphicsSurfaces>::data() noexcept {
					return _Data;
				}
				template<class GraphicsSurfaces>
				inline basic_font<GraphicsSurfaces>::basic_font(string name, float pointsize, io2d::font_weight fw, font_style fs) : _Data(name, pointsize, fw, fs) {
				}
				template<class GraphicsSurfaces>
				inline basic_font<GraphicsSurfaces>::basic_font(::std::filesystem::path file, float pointsize, io2d::font_weight fw, font_style fs) : _Data(file, pointsize, fw, fs) {
				}
				template<class GraphicsSurfaces>
				inline void basic_font<GraphicsSurfaces>::point_size(float size) noexcept {
					GraphicsSurfaces::text::point_size(_Data, size);
				}
				template<class GraphicsSurfaces>
				inline float basic_font<GraphicsSurfaces>::point_size() const noexcept {
					return GraphicsSurfaces::text::point_size(_Data);
				}
				template<class GraphicsSurfaces>
				inline void basic_font<GraphicsSurfaces>::weight(io2d::font_weight fw) noexcept {
					GraphicsSurfaces::text::weight(_Data, fw);
				}
				template<class GraphicsSurfaces>
				inline font_weight basic_font<GraphicsSurfaces>::weight() const noexcept {
					return GraphicsSurfaces::text::weight(_Data);
				}
				template<class GraphicsSurfaces>
				inline void basic_font<GraphicsSurfaces>::style(font_style fs) noexcept {
					GraphicsSurfaces::text::style(_Data, fs);
				}
				template<class GraphicsSurfaces>
				inline font_style basic_font<GraphicsSurfaces>::style() const noexcept {
					return GraphicsSurfaces::text::style(_Data);
				}
			}
		}
	}
}