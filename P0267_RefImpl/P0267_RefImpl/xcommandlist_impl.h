#pragma once

#include "xsurfaces.h"
#include "xpath.h"
#include "xcommandlist.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		template<class GraphicsSurfaces>
		inline const typename basic_commands<GraphicsSurfaces>::clear::data_type& basic_commands<GraphicsSurfaces>::clear::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_commands<GraphicsSurfaces>::clear::data_type& basic_commands<GraphicsSurfaces>::clear::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::clear::clear() noexcept :
			_Data(GraphicsSurfaces::surfaces::create_clear()) {
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::clear::clear(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc) noexcept :
			_Data(GraphicsSurfaces::surfaces::create_clear(sfc)) {
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::clear::surface(optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept {
			GraphicsSurfaces::surfaces::surface(_Data, sfc);
		}
		template<class GraphicsSurfaces>
		inline optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> basic_commands<GraphicsSurfaces>::clear::surface() const noexcept {
			return GraphicsSurfaces::surfaces::surface(_Data);
		}

		//template<class GraphicsSurfaces>
		//inline const typename basic_commands<GraphicsSurfaces>::flush::data_type& basic_commands<GraphicsSurfaces>::flush::data() const noexcept {
		//	return _Data;
		//}
		//template<class GraphicsSurfaces>
		//inline typename basic_commands<GraphicsSurfaces>::flush::data_type& basic_commands<GraphicsSurfaces>::flush::data() noexcept {
		//	return _Data;
		//}
		//template<class GraphicsSurfaces>
		//inline void basic_commands<GraphicsSurfaces>::flush::surface(optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept {
		//	GraphicsSurfaces::surfaces::surface(_Data, sfc);
		//}
		//template<class GraphicsSurfaces>
		//inline optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> basic_commands<GraphicsSurfaces>::flush::surface() const noexcept {
		//	return GraphicsSurfaces::surfaces::surface(_Data);
		//}
		//template<class GraphicsSurfaces>
		//inline basic_commands<GraphicsSurfaces>::flush::flush() noexcept
		//	: _Data(GraphicsSurfaces::surfaces::create_flush()) {
		//}
		//template<class GraphicsSurfaces>
		//inline basic_commands<GraphicsSurfaces>::flush::flush(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc) noexcept
		//	: _Data(GraphicsSurfaces::surfaces::create_flush(sfc)) {
		//}

		//template<class GraphicsSurfaces>
		//inline const typename basic_commands<GraphicsSurfaces>::mark_dirty::data_type& basic_commands<GraphicsSurfaces>::mark_dirty::data() const noexcept {
		//	return _Data;
		//}
		//template<class GraphicsSurfaces>
		//inline typename basic_commands<GraphicsSurfaces>::mark_dirty::data_type& basic_commands<GraphicsSurfaces>::mark_dirty::data() noexcept {
		//	return _Data;
		//}
		//template<class GraphicsSurfaces>
		//inline void basic_commands<GraphicsSurfaces>::mark_dirty::surface(optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept {
		//	GraphicsSurfaces::surfaces::surface(_Data, sfc);
		//}
		//template<class GraphicsSurfaces>
		//inline optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> basic_commands<GraphicsSurfaces>::mark_dirty::surface() const noexcept {
		//	return GraphicsSurfaces::surfaces::surface(_Data);
		//}
		//template<class GraphicsSurfaces>
		//inline basic_commands<GraphicsSurfaces>::mark_dirty::mark_dirty() noexcept
		//	: _Data(GraphicsSurfaces::surfaces::create_mark_dirty()) {
		//}
		//template<class GraphicsSurfaces>
		//inline basic_commands<GraphicsSurfaces>::mark_dirty::mark_dirty(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc) noexcept
		//	: _Data(GraphicsSurfaces::surfaces::create_mark_dirty(sfc)) {
		//}
		//template<class GraphicsSurfaces>
		//inline basic_commands<GraphicsSurfaces>::mark_dirty::mark_dirty(reference_wrapper<basic_bounding_box<graphics_math_type>> ext) noexcept
		//	: _Data(GraphicsSurfaces::surfaces::create_mark_dirty(ext)) {
		//}
		//template<class GraphicsSurfaces>
		//inline basic_commands<GraphicsSurfaces>::mark_dirty::mark_dirty(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, reference_wrapper<basic_bounding_box<graphics_math_type>> ext) noexcept
		//	: _Data(GraphicsSurfaces::surfaces::create_mark_dirty(sfc, ext)) {
		//}
		//template<class GraphicsSurfaces>
		//inline void basic_commands<GraphicsSurfaces>::mark_dirty::extents(optional<reference_wrapper<basic_bounding_box<graphics_math_type>>> ext) noexcept {
		//	GraphicsSurfaces::surfaces::extents(_Data, ext);
		//}
		//template<class GraphicsSurfaces>
		//inline optional<reference_wrapper<basic_bounding_box<typename GraphicsSurfaces::graphics_math_type>>> basic_commands<GraphicsSurfaces>::mark_dirty::extents() const noexcept {
		//	return GraphicsSurfaces::surfaces::extents(_Data);
		//}

		template<class GraphicsSurfaces>
		inline const typename basic_commands<GraphicsSurfaces>::paint::data_type& basic_commands<GraphicsSurfaces>::paint::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_commands<GraphicsSurfaces>::paint::data_type& basic_commands<GraphicsSurfaces>::paint::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::paint::surface(optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept {
			GraphicsSurfaces::surfaces::surface(_Data, sfc);
		}
		template<class GraphicsSurfaces>
		inline optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> basic_commands<GraphicsSurfaces>::paint::surface() const noexcept {
			return GraphicsSurfaces::surfaces::surface(_Data);
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::paint::paint(reference_wrapper<basic_brush<GraphicsSurfaces>> b, reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp, reference_wrapper<basic_render_props<GraphicsSurfaces>> rp, reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_paint(b, bp, rp, cl)) {
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::paint::paint(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, reference_wrapper<basic_brush<GraphicsSurfaces>> b, reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp, reference_wrapper<basic_render_props<GraphicsSurfaces>> rp, reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_paint(sfc, b, bp, rp, cl)) {
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::paint::brush(reference_wrapper<basic_brush<GraphicsSurfaces>> b) noexcept {
			GraphicsSurfaces::surfaces::brush(_Data, b);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_brush<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::paint::brush() const noexcept {
			return GraphicsSurfaces::surfaces::brush(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::paint::brush_props(reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp) noexcept {
			GraphicsSurfaces::surfaces::brush_props(_Data, bp);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_brush_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::paint::brush_props() const noexcept {
			return GraphicsSurfaces::surfaces::brush_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::paint::render_props(reference_wrapper<basic_render_props<GraphicsSurfaces>> rp) noexcept {
			GraphicsSurfaces::surfaces::render_props(_Data, rp);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_render_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::paint::render_props() const noexcept {
			return GraphicsSurfaces::surfaces::render_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::paint::clip_props(reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept {
			GraphicsSurfaces::surfaces::clip_props(_Data, cl);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_clip_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::paint::clip_props() const noexcept {
			return GraphicsSurfaces::surfaces::clip_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline const typename basic_commands<GraphicsSurfaces>::stroke::data_type& basic_commands<GraphicsSurfaces>::stroke::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_commands<GraphicsSurfaces>::stroke::data_type& basic_commands<GraphicsSurfaces>::stroke::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::stroke::surface(optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept {
			GraphicsSurfaces::surfaces::surface(_Data, sfc);
		}
		template<class GraphicsSurfaces>
		inline optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> basic_commands<GraphicsSurfaces>::stroke::surface() const noexcept {
			return GraphicsSurfaces::surfaces::surface(_Data);
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::stroke::stroke(reference_wrapper<basic_brush<GraphicsSurfaces>> b, reference_wrapper<basic_interpreted_path<GraphicsSurfaces>> ip, reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp, reference_wrapper<basic_stroke_props<GraphicsSurfaces>> sp, reference_wrapper<basic_dashes<GraphicsSurfaces>> d, reference_wrapper<basic_render_props<GraphicsSurfaces>> rp, reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_stroke(b, ip, bp, sp, d, rp, cl)) {
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::stroke::stroke(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, reference_wrapper<basic_brush<GraphicsSurfaces>> b, reference_wrapper<basic_interpreted_path<GraphicsSurfaces>> ip, reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp, reference_wrapper<basic_stroke_props<GraphicsSurfaces>> sp, reference_wrapper<basic_dashes<GraphicsSurfaces>> d, reference_wrapper<basic_render_props<GraphicsSurfaces>> rp, reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_stroke(sfc, b, ip, bp, sp, d, rp, cl)) {
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::stroke::brush(reference_wrapper<basic_brush<GraphicsSurfaces>> b) noexcept {
			GraphicsSurfaces::surfaces::brush(_Data, b);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_brush<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::stroke::brush() const noexcept {
			return GraphicsSurfaces::surfaces::brush(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::stroke::path(reference_wrapper<basic_interpreted_path<GraphicsSurfaces>> p) noexcept {
			GraphicsSurfaces::surfaces::path(_Data, p);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_interpreted_path<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::stroke::path() const noexcept {
			return GraphicsSurfaces::surfaces::path(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::stroke::stroke_props(reference_wrapper<basic_stroke_props<GraphicsSurfaces>> sp) noexcept {
			GraphicsSurfaces::surfaces::stroke_props(_Data, sp);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_stroke_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::stroke::stroke_props() const noexcept {
			return GraphicsSurfaces::surfaces::stroke_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::stroke::dashes(reference_wrapper<basic_dashes<GraphicsSurfaces>> d) noexcept {
			GraphicsSurfaces::surfaces::dashes(_Data, d);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_dashes<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::stroke::dashes() const noexcept {
			return GraphicsSurfaces::surfaces::dashes(_Data); // Note: this should return nullopt if the basic_dashes equals the default. Same is true for all member functions that return an optional
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::stroke::brush_props(reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp) noexcept {
			GraphicsSurfaces::surfaces::brush_props(_Data, bp);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_brush_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::stroke::brush_props() const noexcept {
			return GraphicsSurfaces::surfaces::brush_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::stroke::render_props(reference_wrapper<basic_render_props<GraphicsSurfaces>> rp) noexcept {
			GraphicsSurfaces::surfaces::render_props(_Data, rp);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_render_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::stroke::render_props() const noexcept {
			return GraphicsSurfaces::surfaces::render_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::stroke::clip_props(reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept {
			GraphicsSurfaces::surfaces::clip_props(_Data, cl);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_clip_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::stroke::clip_props() const noexcept {
			return GraphicsSurfaces::surfaces::clip_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline const typename basic_commands<GraphicsSurfaces>::fill::data_type& basic_commands<GraphicsSurfaces>::fill::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_commands<GraphicsSurfaces>::fill::data_type& basic_commands<GraphicsSurfaces>::fill::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::fill::surface(optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept {
			GraphicsSurfaces::surfaces::surface(_Data, sfc);
		}
		template<class GraphicsSurfaces>
		inline optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> basic_commands<GraphicsSurfaces>::fill::surface() const noexcept {
			return GraphicsSurfaces::surfaces::surface(_Data);
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::fill::fill(reference_wrapper<basic_brush<GraphicsSurfaces>> b, reference_wrapper<basic_interpreted_path<GraphicsSurfaces>> ip, reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp, reference_wrapper<basic_render_props<GraphicsSurfaces>> rp, reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_fill(b, ip, bp, rp, cl)) {
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::fill::fill(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, reference_wrapper<basic_brush<GraphicsSurfaces>> b, reference_wrapper<basic_interpreted_path<GraphicsSurfaces>> ip, reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp, reference_wrapper<basic_render_props<GraphicsSurfaces>> rp, reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_fill(sfc, b, ip, bp, rp, cl)) {
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::fill::brush(reference_wrapper<basic_brush<GraphicsSurfaces>> b) noexcept {
			GraphicsSurfaces::surfaces::brush(_Data, b);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_brush<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::fill::brush() const noexcept {
			return GraphicsSurfaces::surfaces::brush(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::fill::path(reference_wrapper<basic_interpreted_path<GraphicsSurfaces>> p) noexcept {
			GraphicsSurfaces::surfaces::path(_Data, p);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_interpreted_path<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::fill::path() const noexcept {
			return GraphicsSurfaces::surfaces::path(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::fill::brush_props(reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp) noexcept {
			GraphicsSurfaces::surfaces::brush_props(_Data, bp);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_brush_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::fill::brush_props() const noexcept {
			return GraphicsSurfaces::surfaces::brush_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::fill::render_props(reference_wrapper<basic_render_props<GraphicsSurfaces>> rp) noexcept {
			GraphicsSurfaces::surfaces::render_props(_Data, rp);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_render_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::fill::render_props() const noexcept {
			return GraphicsSurfaces::surfaces::render_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::fill::clip_props(reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept {
			GraphicsSurfaces::surfaces::clip_props(_Data, cl);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_clip_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::fill::clip_props() const noexcept {
			return GraphicsSurfaces::surfaces::clip_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline const typename basic_commands<GraphicsSurfaces>::mask::data_type& basic_commands<GraphicsSurfaces>::mask::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_commands<GraphicsSurfaces>::mask::data_type& basic_commands<GraphicsSurfaces>::mask::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::mask::surface(optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept {
			GraphicsSurfaces::surfaces::surface(_Data, sfc);
		}
		template<class GraphicsSurfaces>
		inline optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> basic_commands<GraphicsSurfaces>::mask::surface() const noexcept {
			return GraphicsSurfaces::surfaces::surface(_Data);
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::mask::mask(reference_wrapper<basic_brush<GraphicsSurfaces>> b, reference_wrapper<basic_brush<GraphicsSurfaces>> mb, reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp, reference_wrapper<basic_mask_props<GraphicsSurfaces>> mp, reference_wrapper<basic_render_props<GraphicsSurfaces>> rp, reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_mask(b, mb, bp, mp, rp, cl)) {
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::mask::mask(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, reference_wrapper<basic_brush<GraphicsSurfaces>> b, reference_wrapper<basic_brush<GraphicsSurfaces>> mb, reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp, reference_wrapper<basic_mask_props<GraphicsSurfaces>> mp, reference_wrapper<basic_render_props<GraphicsSurfaces>> rp, reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_mask(sfc, b, mb, bp, mp, rp, cl)) {
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::mask::brush(basic_brush<GraphicsSurfaces>& b) noexcept {
			GraphicsSurfaces::surfaces::brush(_Data, b);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_brush<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::mask::brush() const noexcept {
			return GraphicsSurfaces::surfaces::brush(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::mask::mask_brush(basic_brush<GraphicsSurfaces>& mb) noexcept {
			GraphicsSurfaces::surfaces::mask_brush(_Data, mb);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_brush<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::mask::mask_brush() const noexcept {
			return GraphicsSurfaces::surfaces::mask_brush(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::mask::brush_props(reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp) noexcept {
			GraphicsSurfaces::surfaces::brush_props(_Data, bp);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_brush_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::mask::brush_props() const noexcept {
			return GraphicsSurfaces::surfaces::brush_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::mask::mask_props(reference_wrapper<basic_mask_props<GraphicsSurfaces>> mp) noexcept {
			GraphicsSurfaces::surfaces::mask_props(_Data, mp);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_mask_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::mask::mask_props() const noexcept {
			return GraphicsSurfaces::surfaces::mask_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::mask::render_props(reference_wrapper<basic_render_props<GraphicsSurfaces>> rp) noexcept {
			GraphicsSurfaces::surfaces::render_props(_Data, rp);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_render_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::mask::render_props() const noexcept {
			return GraphicsSurfaces::surfaces::render_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::mask::clip_props(reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept {
			GraphicsSurfaces::surfaces::clip_props(_Data, cl);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_clip_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::mask::clip_props() const noexcept {
			return GraphicsSurfaces::surfaces::clip_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline const typename basic_commands<GraphicsSurfaces>::draw_text::data_type& basic_commands<GraphicsSurfaces>::draw_text::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_commands<GraphicsSurfaces>::draw_text::data_type& basic_commands<GraphicsSurfaces>::draw_text::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::draw_text::surface(optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept {
			GraphicsSurfaces::surfaces::surface(_Data, sfc);
		}
		template<class GraphicsSurfaces>
		inline optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> basic_commands<GraphicsSurfaces>::draw_text::surface() const noexcept {
			return GraphicsSurfaces::surfaces::surface(_Data);
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::draw_text::draw_text(reference_wrapper<basic_point_2d<graphics_math_type>> pt, reference_wrapper<basic_brush<GraphicsSurfaces>> b, reference_wrapper<basic_font<GraphicsSurfaces>> font, reference_wrapper<string> text, reference_wrapper<basic_text_props<GraphicsSurfaces>> tp, reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp, reference_wrapper<basic_stroke_props<GraphicsSurfaces>> sp, reference_wrapper<basic_dashes<GraphicsSurfaces>> d, reference_wrapper<basic_render_props<GraphicsSurfaces>> rp, reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_draw_text(pt, b, font, text, tp, bp, sp, d, rp, cl)) {
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::draw_text::draw_text(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, reference_wrapper<basic_point_2d<graphics_math_type>> pt, reference_wrapper<basic_brush<GraphicsSurfaces>> b, reference_wrapper<basic_font<GraphicsSurfaces>> font, reference_wrapper<string> text, reference_wrapper<basic_text_props<GraphicsSurfaces>> tp, reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp, reference_wrapper<basic_stroke_props<GraphicsSurfaces>> sp, reference_wrapper<basic_dashes<GraphicsSurfaces>> d, reference_wrapper<basic_render_props<GraphicsSurfaces>> rp, reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_draw_text(sfc, pt, b, font, text, tp, bp, sp, d, rp, cl)) {
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::draw_text::draw_text(reference_wrapper<basic_bounding_box<graphics_math_type>> bb, reference_wrapper<basic_brush<GraphicsSurfaces>> b, reference_wrapper<basic_font<GraphicsSurfaces>> font, reference_wrapper<string> text, reference_wrapper<basic_text_props<GraphicsSurfaces>> tp, reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp, reference_wrapper<basic_stroke_props<GraphicsSurfaces>> sp, reference_wrapper<basic_dashes<GraphicsSurfaces>> d, reference_wrapper<basic_render_props<GraphicsSurfaces>> rp, reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_draw_text(bb, b, font, text, tp, bp, sp, d, rp, cl)) {
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::draw_text::draw_text(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, reference_wrapper<basic_bounding_box<graphics_math_type>> bb, reference_wrapper<basic_brush<GraphicsSurfaces>> b, reference_wrapper<basic_font<GraphicsSurfaces>> font, reference_wrapper<string> text, reference_wrapper<basic_text_props<GraphicsSurfaces>> tp, reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp, reference_wrapper<basic_stroke_props<GraphicsSurfaces>> sp, reference_wrapper<basic_dashes<GraphicsSurfaces>> d, reference_wrapper<basic_render_props<GraphicsSurfaces>> rp, reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_draw_text(sfc, bb, b, font, text, tp, bp, sp, d, rp, cl)) {
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::draw_text::location(reference_wrapper<basic_point_2d<graphics_math_type>> pt) noexcept {
			GraphicsSurfaces::surfaces::location(_Data, pt);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::draw_text::location(reference_wrapper<basic_bounding_box<graphics_math_type>> bb) noexcept {
			GraphicsSurfaces::surfaces::location(_Data, bb);
		}
		template<class GraphicsSurfaces>
		inline variant<::std::reference_wrapper<basic_point_2d<typename basic_commands<GraphicsSurfaces>::graphics_math_type>>, ::std::reference_wrapper<basic_bounding_box<typename basic_commands<GraphicsSurfaces>::graphics_math_type>>> basic_commands<GraphicsSurfaces>::draw_text::location() const noexcept {
			return GraphicsSurfaces::surfaces::location(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::draw_text::brush(reference_wrapper<basic_brush<GraphicsSurfaces>> b) noexcept {
			GraphicsSurfaces::surfaces::brush(_Data, b);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_brush<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::draw_text::brush() const noexcept {
			return GraphicsSurfaces::surfaces::brush(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::draw_text::font(reference_wrapper<basic_font<GraphicsSurfaces>> f) noexcept {
			GraphicsSurfaces::surfaces::font(_Data, f);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_font<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::draw_text::font() const noexcept {
			return GraphicsSurfaces::surfaces::font(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::draw_text::text(reference_wrapper<string> t) noexcept {
			GraphicsSurfaces::surfaces::text(_Data, t);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<string> basic_commands<GraphicsSurfaces>::draw_text::text() const noexcept {
			return GraphicsSurfaces::surfaces::text(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::draw_text::text_props(reference_wrapper<basic_text_props<GraphicsSurfaces>> tp) noexcept {
			GraphicsSurfaces::surfaces::text_props(_Data, tp);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_text_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::draw_text::text_props() const noexcept {
			return GraphicsSurfaces::surfaces::text_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::draw_text::stroke_props(reference_wrapper<basic_stroke_props<GraphicsSurfaces>> sp) noexcept {
			GraphicsSurfaces::surfaces::stroke_props(_Data, sp);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_stroke_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::draw_text::stroke_props() const noexcept {
			return GraphicsSurfaces::surfaces::stroke_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::draw_text::dashes(reference_wrapper<basic_dashes<GraphicsSurfaces>> d) noexcept {
			GraphicsSurfaces::surfaces::dashes(_Data);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_dashes<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::draw_text::dashes() const noexcept {
			return GraphicsSurfaces::surfaces::dashes(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::draw_text::brush_props(reference_wrapper<basic_brush_props<GraphicsSurfaces>> bp) noexcept {
			GraphicsSurfaces::surfaces::brush_props(_Data, bp);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_brush_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::draw_text::brush_props() const noexcept {
			return GraphicsSurfaces::surfaces::brush_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::draw_text::render_props(reference_wrapper<basic_render_props<GraphicsSurfaces>> rp) noexcept {
			GraphicsSurfaces::surfaces::render_props(_Data, rp);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_render_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::draw_text::render_props() const noexcept {
			return GraphicsSurfaces::surfaces::render_props(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::draw_text::clip_props(reference_wrapper<basic_clip_props<GraphicsSurfaces>> cl) noexcept {
			GraphicsSurfaces::surfaces::clip_props(_Data, cl);
		}
		template<class GraphicsSurfaces>
		inline reference_wrapper<basic_clip_props<GraphicsSurfaces>> basic_commands<GraphicsSurfaces>::draw_text::clip_props() const noexcept {
			return GraphicsSurfaces::surfaces::clip_props(_Data);
		}

		// run_function
		template<class GraphicsSurfaces>
		inline const typename basic_commands<GraphicsSurfaces>::run_function::data_type basic_commands<GraphicsSurfaces>::run_function::data() const noexcept {
			return GraphicsSurfaces::surfaces::surface(_Data);
		}
		template<class GraphicsSurfaces>
		inline typename basic_commands<GraphicsSurfaces>::run_function::data_type& basic_commands<GraphicsSurfaces>::run_function::data() noexcept {
			return _Data;
		}

		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::run_function::run_function(const function<void(basic_image_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>& fn, void* user_data, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_run_function(fn, user_data, sfc)) {
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::run_function::run_function(const function<void(basic_output_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>& fn, void* user_data, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_run_function(fn, user_data, sfc)) {
		}
		template<class GraphicsSurfaces>
		inline basic_commands<GraphicsSurfaces>::run_function::run_function(const function<void(basic_unmanaged_output_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>& fn, void* user_data, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept
			: _Data(GraphicsSurfaces::surfaces::create_run_function(fn, user_data, sfc)) {
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::run_function::surface(optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept {
			GraphicsSurfaces::surfaces::surface(_Data, sfc);
		}
		template<class GraphicsSurfaces>
		inline optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> basic_commands<GraphicsSurfaces>::run_function::surface() const noexcept {
			return GraphicsSurfaces::surfaces::surface(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::run_function::func(const function<void(basic_image_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>& fn) noexcept {
			GraphicsSurfaces::surfaces::func(_Data, fn);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::run_function::func(const function<void(basic_output_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>& fn) noexcept {
			GraphicsSurfaces::surfaces::func(_Data, fn);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::run_function::func(const function<void(basic_unmanaged_output_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>& fn) noexcept {
			GraphicsSurfaces::surfaces::func(_Data, fn);
		}
		template<class GraphicsSurfaces>
		inline const variant<function<void(basic_image_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>, function<void(basic_output_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>, function<void(basic_unmanaged_output_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>>& basic_commands<GraphicsSurfaces>::run_function::func() const noexcept {
			return GraphicsSurfaces::surfaces::func(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_commands<GraphicsSurfaces>::run_function::user_data(void* ud) noexcept {
			GraphicsSurfaces::surfaces::user_data(_Data, ud);
		}
		template<class GraphicsSurfaces>
		inline void* basic_commands<GraphicsSurfaces>::run_function::user_data() const noexcept {
			return GraphicsSurfaces::surfaces::user_data(_Data);
		}
	}
}