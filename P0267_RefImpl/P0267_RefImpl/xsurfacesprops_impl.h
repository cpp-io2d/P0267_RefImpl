#pragma once

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
#include "xsurfaces.h"

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				template <class GraphicsSurfaces>
				inline const typename basic_render_props<GraphicsSurfaces>::data_type& basic_render_props<GraphicsSurfaces>::data() const noexcept {
					return _Data;
				}

				template<class GraphicsSurfaces>
				inline typename basic_render_props<GraphicsSurfaces>::data_type& basic_render_props<GraphicsSurfaces>::data() noexcept {
					return _Data;
				}

				template <class GraphicsSurfaces>
				inline basic_render_props<GraphicsSurfaces>::basic_render_props() noexcept
					: _Data(GraphicsSurfaces::surface_state_props::create_render_props()) {
				}

				template <class GraphicsSurfaces>
				inline basic_render_props<GraphicsSurfaces>::basic_render_props(io2d::antialias a, const basic_matrix_2d<graphics_math_type>& m,
					compositing_op co) noexcept
					: _Data(GraphicsSurfaces::surface_state_props::create_render_props(a, m, co)) {
				}

				template<class GraphicsSurfaces>
				inline basic_render_props<GraphicsSurfaces>::basic_render_props(const basic_render_props& other)
					: _Data(GraphicsSurfaces::surface_state_props::copy_render_props(other._Data)) {
				}

				template<class GraphicsSurfaces>
				inline basic_render_props<GraphicsSurfaces>& basic_render_props<GraphicsSurfaces>::operator=(const basic_render_props& other) {
					if (this != &other) {
						GraphicsSurfaces::surface_state_props::copy_render_props(other._Data);
					}
					return *this;
				}

				template<class GraphicsSurfaces>
				inline basic_render_props<GraphicsSurfaces>::basic_render_props(basic_render_props&& other) noexcept
					: _Data(GraphicsSurfaces::surface_state_props::move_render_props(move(other._Data))) {
				}

				template<class GraphicsSurfaces>
				inline basic_render_props<GraphicsSurfaces>& basic_render_props<GraphicsSurfaces>::operator=(basic_render_props&& other) noexcept {
					if (this != &other) {
						_Data = GraphicsSurfaces::surface_state_props::move_render_props(move(other._Data));
					}
					return *this;
				}

				template<class GraphicsSurfaces>
				inline basic_render_props<GraphicsSurfaces>::~basic_render_props() noexcept {
					GraphicsSurfaces::surface_state_props::destroy(_Data);
				}

				template <class GraphicsSurfaces>
				inline void basic_render_props<GraphicsSurfaces>::antialiasing(io2d::antialias a) noexcept {
					GraphicsSurfaces::surface_state_props::antialiasing(_Data, a);
				}

				template <class GraphicsSurfaces>
				inline void basic_render_props<GraphicsSurfaces>::compositing(compositing_op co) noexcept {
					GraphicsSurfaces::surface_state_props::compositing(_Data, co);
				}

				template <class GraphicsSurfaces>
				inline void basic_render_props<GraphicsSurfaces>::surface_matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept {
					GraphicsSurfaces::surface_state_props::surface_matrix(_Data, m);
				}

				template <class GraphicsSurfaces>
				inline io2d::antialias basic_render_props<GraphicsSurfaces>::antialiasing() const noexcept {
					return GraphicsSurfaces::surface_state_props::antialiasing(_Data);
				}

				template <class GraphicsSurfaces>
				inline compositing_op basic_render_props<GraphicsSurfaces>::compositing() const noexcept {
					return GraphicsSurfaces::surface_state_props::compositing(_Data);
				}

				template <class GraphicsSurfaces>
				inline basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type> basic_render_props<GraphicsSurfaces>::surface_matrix() const noexcept {
					return GraphicsSurfaces::surface_state_props::surface_matrix(_Data);
				}

				// brush props

				template <class GraphicsSurfaces>
				inline basic_brush_props<GraphicsSurfaces>::basic_brush_props(experimental::io2d::wrap_mode w,
					experimental::io2d::filter fi,
					experimental::io2d::fill_rule fr,
					const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept
					: _Data(GraphicsSurfaces::surface_state_props::create_brush_props(w, fi, fr, m)) {
				}

				template<class GraphicsSurfaces>
				inline basic_brush_props<GraphicsSurfaces>::basic_brush_props(const basic_brush_props& other)
					: _Data(GraphicsSurfaces::surface_state_props::copy_brush_props(other._Data)) {
				}

				template<class GraphicsSurfaces>
				inline basic_brush_props<GraphicsSurfaces>& basic_brush_props<GraphicsSurfaces>::operator=(const basic_brush_props& other) {
					if (this != &other) {
						GraphicsSurfaces::surface_state_props::copy_brush_props(other._Data);
					}
					return *this;
				}

				template<class GraphicsSurfaces>
				inline basic_brush_props<GraphicsSurfaces>::basic_brush_props(basic_brush_props&& other) noexcept
					: _Data(GraphicsSurfaces::surface_state_props::move_brush_props(move(other._Data))) {
				}

				template<class GraphicsSurfaces>
				inline basic_brush_props<GraphicsSurfaces>& basic_brush_props<GraphicsSurfaces>::operator=(basic_brush_props&& other) noexcept {
					if (this != &other) {
						_Data = move(GraphicsSurfaces::surface_state_props::move_brush_props(move(other._Data)));
					}
					return *this;
				}

				template<class GraphicsSurfaces>
				inline basic_brush_props<GraphicsSurfaces>::~basic_brush_props() noexcept {
					GraphicsSurfaces::surface_state_props::destroy(_Data);
				}

				template <class GraphicsSurfaces>
				inline void basic_brush_props<GraphicsSurfaces>::filter(experimental::io2d::filter fi) noexcept {
					GraphicsSurfaces::surface_state_props::filter(_Data, fi);
				}

				template <class GraphicsSurfaces>
				inline void basic_brush_props<GraphicsSurfaces>::wrap_mode(experimental::io2d::wrap_mode w) noexcept {
					GraphicsSurfaces::surface_state_props::wrap_mode(_Data, w);
				}

				template <class GraphicsSurfaces>
				inline void basic_brush_props<GraphicsSurfaces>::fill_rule(experimental::io2d::fill_rule fr) noexcept {
					GraphicsSurfaces::surface_state_props::fill_rule(_Data, fr);
				}

				template <class GraphicsSurfaces>
				inline void basic_brush_props<GraphicsSurfaces>::brush_matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept {
					GraphicsSurfaces::surface_state_props::brush_matrix(_Data, m);
				}

				template <class GraphicsSurfaces>
				inline experimental::io2d::filter basic_brush_props<GraphicsSurfaces>::filter() const noexcept {
					return GraphicsSurfaces::surface_state_props::filter(_Data);
				}

				template <class GraphicsSurfaces>
				inline experimental::io2d::wrap_mode basic_brush_props<GraphicsSurfaces>::wrap_mode() const noexcept {
					return GraphicsSurfaces::surface_state_props::wrap_mode(_Data);
				}

				template <class GraphicsSurfaces>
				inline experimental::io2d::fill_rule basic_brush_props<GraphicsSurfaces>::fill_rule() const noexcept {
					return GraphicsSurfaces::surface_state_props::fill_rule(_Data);
				}

				template <class GraphicsSurfaces>
				inline basic_matrix_2d<typename basic_brush_props<GraphicsSurfaces>::graphics_math_type> basic_brush_props<GraphicsSurfaces>::brush_matrix() const noexcept {
					return GraphicsSurfaces::surface_state_props::brush_matrix(_Data);
				}

				// clip_props
				template <class GraphicsSurfaces>
				inline const typename basic_clip_props<GraphicsSurfaces>::data_type& basic_clip_props<GraphicsSurfaces>::data() const noexcept {
					return _Data;
				}
				template<class GraphicsSurfaces>
				inline typename basic_clip_props<GraphicsSurfaces>::data_type& basic_clip_props<GraphicsSurfaces>::data() noexcept {
					return _Data;
				}
				template <class GraphicsSurfaces>
				inline basic_clip_props<GraphicsSurfaces>::basic_clip_props() noexcept
					: _Data(GraphicsSurfaces::surface_state_props::create_clip_props()) {}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline basic_clip_props<GraphicsSurfaces>::basic_clip_props(const basic_path_builder<GraphicsSurfaces, Allocator> &pb,
					io2d::fill_rule fr)
					: _Data(GraphicsSurfaces::surface_state_props::create_clip_props(pb, fr)) { }

				template <class GraphicsSurfaces>
				inline basic_clip_props<GraphicsSurfaces>::basic_clip_props(const basic_interpreted_path<GraphicsSurfaces>& ip,
					io2d::fill_rule fr) noexcept
					: _Data(GraphicsSurfaces::surface_state_props::create_clip_props(ip, fr)) { }

				template <class GraphicsSurfaces>
				inline basic_clip_props<GraphicsSurfaces>::basic_clip_props(const basic_bounding_box<typename basic_clip_props<GraphicsSurfaces>::graphics_math_type>& bbox,
					experimental::io2d::fill_rule fr)
					: _Data(GraphicsSurfaces::surface_state_props::create_clip_props(bbox, fr)) {
				}

				template<class GraphicsSurfaces>
				inline basic_clip_props<GraphicsSurfaces>::basic_clip_props(const basic_clip_props& other)
					: _Data(GraphicsSurfaces::surface_state_props::copy_clip_props(other._Data)) {
				}

				template<class GraphicsSurfaces>
				inline basic_clip_props<GraphicsSurfaces>& basic_clip_props<GraphicsSurfaces>::operator=(const basic_clip_props& other) {
					if (this != &other) {
						GraphicsSurfaces::surface_state_props::copy_clip_props(other._Data);
					}
					return *this;
				}

				template<class GraphicsSurfaces>
				inline basic_clip_props<GraphicsSurfaces>::basic_clip_props(basic_clip_props&& other) noexcept
					: _Data(GraphicsSurfaces::surface_state_props::move_clip_props(move(other._Data))) {
				}

				template<class GraphicsSurfaces>
				inline basic_clip_props<GraphicsSurfaces>& basic_clip_props<GraphicsSurfaces>::operator=(basic_clip_props&& other) noexcept {
					if (this != &other) {
						_Data = move(GraphicsSurfaces::surface_state_props::move_clip_props(move(other._Data)));
					}
					return *this;
				}

				template<class GraphicsSurfaces>
				inline basic_clip_props<GraphicsSurfaces>::~basic_clip_props() noexcept {
					GraphicsSurfaces::surface_state_props::destroy(_Data);
				}

				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void basic_clip_props<GraphicsSurfaces>::clip(const basic_path_builder<GraphicsSurfaces, Allocator>& pb) {
					GraphicsSurfaces::surface_state_props::clip(_Data, pb);
				}

				template <class GraphicsSurfaces>
				inline void basic_clip_props<GraphicsSurfaces>::clip(const basic_interpreted_path<GraphicsSurfaces>& ip) noexcept {
					GraphicsSurfaces::surface_state_props::clip(_Data, ip);
				}

				template <class GraphicsSurfaces>
				inline void basic_clip_props<GraphicsSurfaces>::fill_rule(experimental::io2d::fill_rule fr) noexcept {
					GraphicsSurfaces::surface_state_props::fill_rule(_Data, fr);
				}

				template <class GraphicsSurfaces>
				inline basic_interpreted_path<GraphicsSurfaces> basic_clip_props<GraphicsSurfaces>::clip() const noexcept {
					return GraphicsSurfaces::surface_state_props::clip(_Data);
				}

				template <class GraphicsSurfaces>
				inline io2d::fill_rule basic_clip_props<GraphicsSurfaces>::fill_rule() const noexcept {
					return GraphicsSurfaces::surface_state_props::fill_rule(_Data);
				}

				// stroke props
				template <class GraphicsSurfaces>
				inline const typename basic_stroke_props<GraphicsSurfaces>::data_type& basic_stroke_props<GraphicsSurfaces>::data() const noexcept {
					return _Data;
				}
				template<class GraphicsSurfaces>
				inline typename basic_stroke_props<GraphicsSurfaces>::data_type& basic_stroke_props<GraphicsSurfaces>::data() noexcept {
					return _Data;
				}
				template <class GraphicsSurfaces>
				inline basic_stroke_props<GraphicsSurfaces>::basic_stroke_props() noexcept
					: _Data(GraphicsSurfaces::surface_state_props::create_stroke_props()) {
				}
				template <class GraphicsSurfaces>
				inline basic_stroke_props<GraphicsSurfaces>::basic_stroke_props(float w,
					io2d::line_cap lc,
					io2d::line_join lj,
					float ml) noexcept
					: _Data(GraphicsSurfaces::surface_state_props::create_stroke_props(w, lc, lj, ml)) {
				}

				template<class GraphicsSurfaces>
				inline basic_stroke_props<GraphicsSurfaces>::basic_stroke_props(const basic_stroke_props& other)
					: _Data(GraphicsSurfaces::surface_state_props::copy_stroke_props(other._Data)) {
				}

				template<class GraphicsSurfaces>
				inline basic_stroke_props<GraphicsSurfaces>& basic_stroke_props<GraphicsSurfaces>::operator=(const basic_stroke_props& other) {
					if (this != &other) {
						_Data = GraphicsSurfaces::surface_state_props::copy_stroke_props(other._Data);
					}
					return *this;
				}

				template<class GraphicsSurfaces>
				inline basic_stroke_props<GraphicsSurfaces>::basic_stroke_props(basic_stroke_props&& other) noexcept
					: _Data(GraphicsSurfaces::surface_state_props::move_stroke_props(move(other._Data))) {
				}

				template<class GraphicsSurfaces>
				inline basic_stroke_props<GraphicsSurfaces>& basic_stroke_props<GraphicsSurfaces>::operator=(basic_stroke_props&& other) noexcept {
					if (this != &other) {
						_Data = move(GraphicsSurfaces::surface_state_props::move_stroke_props(move(other._Data)));
					}
					return *this;
				}

				template<class GraphicsSurfaces>
				inline basic_stroke_props<GraphicsSurfaces>::~basic_stroke_props() noexcept {
					GraphicsSurfaces::surface_state_props::destroy(_Data);
				}

				template <class GraphicsSurfaces>
				inline void basic_stroke_props<GraphicsSurfaces>::line_width(float w) noexcept {
					GraphicsSurfaces::surface_state_props::line_width(_Data, w);
				}
				template <class GraphicsSurfaces>
				inline void basic_stroke_props<GraphicsSurfaces>::line_cap(io2d::line_cap lc) noexcept {
					GraphicsSurfaces::surface_state_props::line_cap(_Data, lc);
				}
				template <class GraphicsSurfaces>
				inline void basic_stroke_props<GraphicsSurfaces>::line_join(experimental::io2d::line_join lj) noexcept {
					GraphicsSurfaces::surface_state_props::line_join(_Data, lj);
				}
				template <class GraphicsSurfaces>
				inline void basic_stroke_props<GraphicsSurfaces>::miter_limit(float ml) noexcept {
					GraphicsSurfaces::surface_state_props::miter_limit(_Data, ml);
				}

				template <class GraphicsSurfaces>
				inline float basic_stroke_props<GraphicsSurfaces>::line_width() const noexcept {
					return GraphicsSurfaces::surface_state_props::line_width(_Data);
				}
				template <class GraphicsSurfaces>
				inline experimental::io2d::line_cap basic_stroke_props<GraphicsSurfaces>::line_cap() const noexcept {
					return GraphicsSurfaces::surface_state_props::line_cap(_Data);
				}
				template <class GraphicsSurfaces>
				inline experimental::io2d::line_join basic_stroke_props<GraphicsSurfaces>::line_join() const noexcept {
					return GraphicsSurfaces::surface_state_props::line_join(_Data);
				}
				template <class GraphicsSurfaces>
				inline float basic_stroke_props<GraphicsSurfaces>::miter_limit() const noexcept {
					return GraphicsSurfaces::surface_state_props::miter_limit(_Data);
				}
				template <class GraphicsSurfaces>
				inline float basic_stroke_props<GraphicsSurfaces>::max_miter_limit() const noexcept {
					return GraphicsSurfaces::surface_state_props::max_miter_limit();
				}

				// Mask props
				template<class GraphicsSurfaces>
				inline const typename basic_mask_props<GraphicsSurfaces>::data_type& basic_mask_props<GraphicsSurfaces>::data() const noexcept {
					return _Data;
				}

				template<class GraphicsSurfaces>
				inline typename basic_mask_props<GraphicsSurfaces>::data_type& basic_mask_props<GraphicsSurfaces>::data() noexcept {
					return _Data;
				}

				template <class GraphicsSurfaces>
				inline basic_mask_props<GraphicsSurfaces>::basic_mask_props(experimental::io2d::wrap_mode w,
					experimental::io2d::filter fi,
					const basic_matrix_2d<graphics_math_type>& m) noexcept
					: _Data(GraphicsSurfaces::surface_state_props::create_mask_props(w, fi, m)) {
				}

				template<class GraphicsSurfaces>
				inline basic_mask_props<GraphicsSurfaces>::basic_mask_props(const basic_mask_props& other) noexcept
					: _Data(GraphicsSurfaces::surface_state_props::copy_mask_props(other._Data)) {
				}

				template<class GraphicsSurfaces>
				inline basic_mask_props<GraphicsSurfaces>& basic_mask_props<GraphicsSurfaces>::operator=(const basic_mask_props & other) noexcept {
					if (this != &other) {
						GraphicsSurfaces::surface_state_props::copy_mask_props(other._Data);
					}
					return *this;
				}

				template<class GraphicsSurfaces>
				inline basic_mask_props<GraphicsSurfaces>::basic_mask_props(basic_mask_props&& other) noexcept
					: _Data(GraphicsSurfaces::surface_state_props::move_mask_props(move(other._Data))) {
				}

				template<class GraphicsSurfaces>
				inline basic_mask_props<GraphicsSurfaces>& basic_mask_props<GraphicsSurfaces>::operator=(basic_mask_props&& other) noexcept {
					if (this != &other) {
						_Data = move(GraphicsSurfaces::surface_state_props::move_mask_props(move(other._Data)));
					}
					return *this;
				}

				template<class GraphicsSurfaces>
				inline basic_mask_props<GraphicsSurfaces>::~basic_mask_props() noexcept {
					GraphicsSurfaces::surface_state_props::destroy(_Data);
				}

				template <class GraphicsSurfaces>
				inline void basic_mask_props<GraphicsSurfaces>::wrap_mode(experimental::io2d::wrap_mode w) noexcept {
					GraphicsSurfaces::surface_state_props::wrap_mode(_Data, w);
				}
				template <class GraphicsSurfaces>
				inline void basic_mask_props<GraphicsSurfaces>::filter(experimental::io2d::filter fi) noexcept {
					GraphicsSurfaces::surface_state_props::filter(_Data, fi);
				}
				template <class GraphicsSurfaces>
				inline void basic_mask_props<GraphicsSurfaces>::mask_matrix(const basic_matrix_2d<graphics_math_type>& m) noexcept {
					GraphicsSurfaces::surface_state_props::mask_matrix(_Data, m);
				}

				template <class GraphicsSurfaces>
				inline experimental::io2d::wrap_mode basic_mask_props<GraphicsSurfaces>::wrap_mode() const noexcept {
					return GraphicsSurfaces::surface_state_props::wrap_mode(_Data);
				}
				template <class GraphicsSurfaces>
				inline experimental::io2d::filter basic_mask_props<GraphicsSurfaces>::filter() const noexcept {
					return GraphicsSurfaces::surface_state_props::filter(_Data);
				}
				template <class GraphicsSurfaces>
				inline basic_matrix_2d<typename basic_mask_props<GraphicsSurfaces>::graphics_math_type> basic_mask_props<GraphicsSurfaces>::mask_matrix() const noexcept {
					return GraphicsSurfaces::surface_state_props::mask_matrix(_Data);
				}

				// dashes
				template<class GraphicsSurfaces>
				inline const typename basic_dashes<GraphicsSurfaces>::data_type& basic_dashes<GraphicsSurfaces>::data() const noexcept {
					return _Data;
				}

				template<class GraphicsSurfaces>
				inline typename basic_dashes<GraphicsSurfaces>::data_type& basic_dashes<GraphicsSurfaces>::data() noexcept {
					return _Data;
				}

				template <class GraphicsSurfaces>
				inline basic_dashes<GraphicsSurfaces>::basic_dashes() noexcept
					: _Data(GraphicsSurfaces::surface_state_props::create_dashes()) {}
				template <class GraphicsSurfaces>
				template <class ForwardIterator>
				inline basic_dashes<GraphicsSurfaces>::basic_dashes(float offset, ForwardIterator first, ForwardIterator last)
					: _Data(GraphicsSurfaces::surface_state_props::create_dashes(offset, first, last)) {}
				template <class GraphicsSurfaces>
				inline basic_dashes<GraphicsSurfaces>::basic_dashes(float offset, ::std::initializer_list<float> il)
					: _Data(GraphicsSurfaces::surface_state_props::create_dashes(offset, il)) {}
				template<class GraphicsSurfaces>
				inline basic_dashes<GraphicsSurfaces>::basic_dashes(const basic_dashes& other)
					: _Data(GraphicsSurfaces::surface_state_props::copy_dashes(other._Data)) {
				}
				template<class GraphicsSurfaces>
				inline basic_dashes<GraphicsSurfaces>& basic_dashes<GraphicsSurfaces>::operator=(const basic_dashes& other) {
					if (this != &other) {
						_Data = GraphicsSurfaces::surface_state_props::copy_dashes(other._Data);
					}
					return *this;
				}
				template<class GraphicsSurfaces>
				inline basic_dashes<GraphicsSurfaces>::basic_dashes(basic_dashes&& other) noexcept
					: _Data(GraphicsSurfaces::surface_state_props::move_dashes(move(other._Data))) {
				}
				template<class GraphicsSurfaces>
				inline basic_dashes<GraphicsSurfaces>& basic_dashes<GraphicsSurfaces>::operator=(basic_dashes&& other) noexcept {
					if (this != &other) {
						_Data = move(GraphicsSurfaces::surface_state_props::move_dashes(move(other._Data)));
					}
					return *this;
				}
				template<class GraphicsSurfaces>
				inline basic_dashes<GraphicsSurfaces>::~basic_dashes() noexcept {
					GraphicsSurfaces::surface_state_props::destroy(_Data);
				}
			}
		}
	}
}
