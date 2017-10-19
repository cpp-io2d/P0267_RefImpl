#pragma once
#include "io2d.h"

#include <memory>
#include <functional>
#include <exception>
#include <vector>
#include <string>
#include <algorithm>
#include <system_error>
#include <cstdint>
#include <atomic>
#include <variant>
#include <optional>
#include <cmath>
#include <type_traits>
#include <initializer_list>
#include <cmath>

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				template <class GraphicsSurfaces>
				inline const typename basic_render_props<GraphicsSurfaces>::_Data_type& basic_render_props<GraphicsSurfaces>::_Get_data() const noexcept {
					return _Data;
				}

				template <class GraphicsSurfaces>
				inline basic_render_props<GraphicsSurfaces>::basic_render_props() noexcept
					: _Data(GraphicsSurfaces::create_render_props()) {
				}

				template <class GraphicsSurfaces>
				inline basic_render_props<GraphicsSurfaces>::basic_render_props(io2d::antialias a, const basic_matrix_2d<graphics_math_type>& m,
					compositing_op co) noexcept
					: _Data(GraphicsSurfaces::create_render_props(a, m, co)) {
				}

				template <class GraphicsSurfaces>
				inline void basic_render_props<GraphicsSurfaces>::antialiasing(io2d::antialias a) noexcept {
					GraphicsSurfaces::antialiasing(_Data, a);
				}

				template <class GraphicsSurfaces>
				inline void basic_render_props<GraphicsSurfaces>::compositing(compositing_op co) noexcept {
					GraphicsSurfaces::compositing(_Data, co);
				}

				template <class GraphicsSurfaces>
				inline void basic_render_props<GraphicsSurfaces>::surface_matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept {
					GraphicsSurfaces::surface_matrix(_Data, m);
				}

				template <class GraphicsSurfaces>
				inline io2d::antialias basic_render_props<GraphicsSurfaces>::antialiasing() const noexcept {
					return GraphicsSurfaces::antialiasing(_Data);
				}

				template <class GraphicsSurfaces>
				inline compositing_op basic_render_props<GraphicsSurfaces>::compositing() const noexcept {
					return GraphicsSurfaces::compositing(_Data);
				}

				template <class GraphicsSurfaces>
				inline basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type> basic_render_props<GraphicsSurfaces>::surface_matrix() const noexcept {
					return GraphicsSurfaces::surface_matrix(_Data);
				}

				// brush props

				template <class GraphicsSurfaces>
				inline basic_brush_props<GraphicsSurfaces>::basic_brush_props(experimental::io2d::wrap_mode w,
					experimental::io2d::filter fi,
					experimental::io2d::fill_rule fr,
					const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept
					: _Data(GraphicsSurfaces::create_brush_props(w, fi, fr, m)) {
				}

				template <class GraphicsSurfaces>
				inline void basic_brush_props<GraphicsSurfaces>::filter(experimental::io2d::filter fi) noexcept {
					GraphicsSurfaces::filter(_Data, fi);
				}

				template <class GraphicsSurfaces>
				inline void basic_brush_props<GraphicsSurfaces>::wrap_mode(experimental::io2d::wrap_mode w) noexcept {
					GraphicsSurfaces::wrap_mode(_Data, w);
				}

				template <class GraphicsSurfaces>
				inline void basic_brush_props<GraphicsSurfaces>::fill_rule(experimental::io2d::fill_rule fr) noexcept {
					GraphicsSurfaces::fill_rule(_Data, fr);
				}

				template <class GraphicsSurfaces>
				inline void basic_brush_props<GraphicsSurfaces>::brush_matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept {
					GraphicsSurfaces::brush_matrix(_Data, m);
				}

				template <class GraphicsSurfaces>
				inline experimental::io2d::filter basic_brush_props<GraphicsSurfaces>::filter() const noexcept {
					return GraphicsSurfaces::filter(_Data);
				}

				template <class GraphicsSurfaces>
				inline experimental::io2d::wrap_mode basic_brush_props<GraphicsSurfaces>::wrap_mode() const noexcept {
					return GraphicsSurfaces::wrap_mode(_Data);
				}

				template <class GraphicsSurfaces>
				inline experimental::io2d::fill_rule basic_brush_props<GraphicsSurfaces>::fill_rule() const noexcept {
					return GraphicsSurfaces::fill_rule(_Data);
				}

				template <class GraphicsSurfaces>
				inline basic_matrix_2d<typename basic_brush_props<GraphicsSurfaces>::graphics_math_type> basic_brush_props<GraphicsSurfaces>::brush_matrix() const noexcept {
					return GraphicsSurfaces::brush_matrix(_Data);
				}

				// clip_props
				template <class GraphicsSurfaces>
				inline const typename basic_clip_props<GraphicsSurfaces>::_Data_type& basic_clip_props<GraphicsSurfaces>::_Get_data() const noexcept {
					return _Data;
				}
				template <class GraphicsSurfaces>
				inline basic_clip_props<GraphicsSurfaces>::basic_clip_props() noexcept
					: _Data(GraphicsSurfaces::create_clip_props()) {}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline basic_clip_props<GraphicsSurfaces>::basic_clip_props(const basic_path_builder<graphics_math_type, Allocator> &pb,
					io2d::fill_rule fr)
					: _Data(GraphicsSurfaces::create_clip_props(pb, fr)) { }

				template <class GraphicsSurfaces>
				inline basic_clip_props<GraphicsSurfaces>::basic_clip_props(const basic_interpreted_path<GraphicsSurfaces>& ip,
					io2d::fill_rule fr) noexcept
					: _Data(GraphicsSurfaces::create_clip_props(ip, fr)) { }

				template <class GraphicsSurfaces>
				inline basic_clip_props<GraphicsSurfaces>::basic_clip_props(const basic_bounding_box<typename basic_clip_props<GraphicsSurfaces>::graphics_math_type>& bbox,
					experimental::io2d::fill_rule fr)
					: _Data(GraphicsSurfaces::create_clip_props(bbox, fr)) {
					//path_builder<> clip;
					//clip.new_figure(r.top_left());
					//clip.rel_line({ r.width(), 0.0F });
					//clip.rel_line({ 0.0F, r.height() });
					//clip.rel_line({ -r.width(), 0.0F });
					//clip.close_figure();
					//_Clip = interpreted_path(clip);
				}

				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void basic_clip_props<GraphicsSurfaces>::clip(const basic_path_builder<graphics_math_type, Allocator>& pb) {
					GraphicsSurfaces::clip(_Data, pb);
				}

				template <class GraphicsSurfaces>
				inline void basic_clip_props<GraphicsSurfaces>::clip(const basic_interpreted_path<GraphicsSurfaces>& ip) noexcept {
					GraphicsSurfaces::clip(_Data, ip);
				}

				template <class GraphicsSurfaces>
				inline void basic_clip_props<GraphicsSurfaces>::fill_rule(experimental::io2d::fill_rule fr) noexcept {
					GraphicsSurfaces::fill_rule(_Data, fr);
				}

				template <class GraphicsSurfaces>
				inline basic_interpreted_path<GraphicsSurfaces> basic_clip_props<GraphicsSurfaces>::clip() const noexcept {
					return GraphicsSurfaces::clip(_Data);
				}

				template <class GraphicsSurfaces>
				inline io2d::fill_rule basic_clip_props<GraphicsSurfaces>::fill_rule() const noexcept {
					return GraphicsSurfaces::fill_rule(_Data);
				}

				// stroke props
				template <class GraphicsSurfaces>
				inline const typename basic_stroke_props<GraphicsSurfaces>::_Data_type& basic_stroke_props<GraphicsSurfaces>::_Get_data() const noexcept {
					return _Data;
				}
				template <class GraphicsSurfaces>
				inline basic_stroke_props<GraphicsSurfaces>::basic_stroke_props() noexcept
					: _Data(GraphicsSurfaces::create_stroke_props()) {
				}
				template <class GraphicsSurfaces>
				inline basic_stroke_props<GraphicsSurfaces>::basic_stroke_props(float w,
					io2d::line_cap lc,
					io2d::line_join lj,
					float ml) noexcept
					: _Data(GraphicsSurfaces::create_stroke_props(w, lc, lj, ml)) {
				}

				template <class GraphicsSurfaces>
				inline void basic_stroke_props<GraphicsSurfaces>::line_width(float w) noexcept {
					GraphicsSurfaces::line_width(_Data, w);
				}
				template <class GraphicsSurfaces>
				inline void basic_stroke_props<GraphicsSurfaces>::line_cap(io2d::line_cap lc) noexcept {
					GraphicsSurfaces::line_cap(_Data, lc);
				}
				template <class GraphicsSurfaces>
				inline void basic_stroke_props<GraphicsSurfaces>::line_join(experimental::io2d::line_join lj) noexcept {
					GraphicsSurfaces::line_join(_Data, lj);
				}
				template <class GraphicsSurfaces>
				inline void basic_stroke_props<GraphicsSurfaces>::miter_limit(float ml) noexcept {
					GraphicsSurfaces::miter_limit(_Data, ml);
				}

				template <class GraphicsSurfaces>
				inline float basic_stroke_props<GraphicsSurfaces>::line_width() const noexcept {
					return GraphicsSurfaces::line_width(_Data);
				}
				template <class GraphicsSurfaces>
				inline experimental::io2d::line_cap basic_stroke_props<GraphicsSurfaces>::line_cap() const noexcept {
					return GraphicsSurfaces::line_cap(_Data);
				}
				template <class GraphicsSurfaces>
				inline experimental::io2d::line_join basic_stroke_props<GraphicsSurfaces>::line_join() const noexcept {
					return GraphicsSurfaces::line_join(_Data);
				}
				template <class GraphicsSurfaces>
				inline float basic_stroke_props<GraphicsSurfaces>::miter_limit() const noexcept {
					return GraphicsSurfaces::miter_limit(_Data);
				}
				template <class GraphicsSurfaces>
				inline float basic_stroke_props<GraphicsSurfaces>::max_miter_limit() const noexcept {
					return GraphicsSurfaces::max_miter_limit();
				}

				// mask props
				template <class GraphicsSurfaces>
				inline basic_mask_props<GraphicsSurfaces>::basic_mask_props(experimental::io2d::wrap_mode w,
					experimental::io2d::filter fi,
					const basic_matrix_2d<graphics_math_type>& m) noexcept
					: _Data(GraphicsSurfaces::create_mask_props(w, fi, m)) {
				}

				template <class GraphicsSurfaces>
				inline void basic_mask_props<GraphicsSurfaces>::wrap_mode(experimental::io2d::wrap_mode w) noexcept {
					GraphicsSurfaces::wrap_mode(_Data, w);
				}
				template <class GraphicsSurfaces>
				inline void basic_mask_props<GraphicsSurfaces>::filter(experimental::io2d::filter fi) noexcept {
					GraphicsSurfaces::filter(_Data, fi);
				}
				template <class GraphicsSurfaces>
				inline void basic_mask_props<GraphicsSurfaces>::mask_matrix(const basic_matrix_2d<graphics_math_type>& m) noexcept {
					GraphicsSurfaces::mask_matrix(_Data, m);
				}

				template <class GraphicsSurfaces>
				inline experimental::io2d::wrap_mode basic_mask_props<GraphicsSurfaces>::wrap_mode() const noexcept {
					return GraphicsSurfaces::wrap_mode(_Data);
				}
				template <class GraphicsSurfaces>
				inline experimental::io2d::filter basic_mask_props<GraphicsSurfaces>::filter() const noexcept {
					return GraphicsSurfaces::filter(_Data);
				}
				template <class GraphicsSurfaces>
				inline basic_matrix_2d<typename basic_mask_props<GraphicsSurfaces>::graphics_math_type> basic_mask_props<GraphicsSurfaces>::mask_matrix() const noexcept {
					return GraphicsSurfaces::mask_matrix(_Data);
				}
			}
		}
	}
}
