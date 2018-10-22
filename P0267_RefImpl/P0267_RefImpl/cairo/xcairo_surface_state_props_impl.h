#pragma once

#include "xcairo_helpers.h"
#include "xsystemheaders.h"
#include <cassert>
#if defined(_WIN32) || defined(_WIN64)
#include <cairo-win32.h>
#endif
#include "xpath.h"
#include <iostream>
#include <sstream>
#include <iomanip>

#ifdef _IO2D_Has_Magick
#include <magick/api.h>
#endif

#include <system_error>
#include <cstring>
#include <chrono>

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Cairo {
			// render props
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::render_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::create_render_props(antialias aa, basic_matrix_2d<GraphicsMath> m, compositing_op co) noexcept {
				render_props_data_type data;
				data._Antialiasing = aa;
				data._Matrix = m;
				data._Compositing = co;
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::render_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::copy_render_props(const render_props_data_type& data) {
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::render_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::move_render_props(render_props_data_type&& data) noexcept {
				return data;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::destroy(render_props_data_type& /*data*/) noexcept {
				// Do nothing.
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::antialiasing(render_props_data_type& data, antialias aa) noexcept {
				data._Antialiasing = aa;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::surface_matrix(render_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept {
				data._Matrix = m;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::compositing(render_props_data_type& data, io2d::compositing_op co) noexcept {
				data._Compositing = co;
			}
			template<class GraphicsMath>
			inline antialias _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::antialiasing(const render_props_data_type& data) noexcept {
				return data._Antialiasing;
			}
			template<class GraphicsMath>
			inline basic_matrix_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::surface_matrix(const render_props_data_type& data) noexcept {
				return data._Matrix;
			}
			template<class GraphicsMath>
			inline  compositing_op _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::compositing(const render_props_data_type& data) noexcept {
				return data._Compositing;
			}
			template<class GraphicsMath>
			inline  typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::brush_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::create_brush_props(io2d::wrap_mode wm, io2d::filter f, io2d::fill_rule fr, const basic_matrix_2d<GraphicsMath>& m) noexcept {
				brush_props_data_type data;
				data._Wrap_mode = wm;
				data._Filter = f;
				data._Fill_rule = fr;
				data._Matrix = m;
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::brush_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::copy_brush_props(const brush_props_data_type& data) {
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::brush_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::move_brush_props(brush_props_data_type&& data) noexcept {
				return data;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::destroy(brush_props_data_type& /*data*/) noexcept {
				// Do nothing.
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::wrap_mode(brush_props_data_type& data, io2d::wrap_mode wm) noexcept {
				data._Wrap_mode = wm;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::filter(brush_props_data_type& data, io2d::filter f) noexcept {
				data._Filter = f;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::fill_rule(brush_props_data_type& data, io2d::fill_rule fr) noexcept {
				data._Fill_rule = fr;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::brush_matrix(brush_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept {
				data._Matrix = m;
			}
			template<class GraphicsMath>
			inline io2d::wrap_mode _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::wrap_mode(const brush_props_data_type& data) noexcept {
				return data._Wrap_mode;
			}
			template<class GraphicsMath>
			inline io2d::filter _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::filter(const brush_props_data_type& data) noexcept {
				return data._Filter;
			}
			template<class GraphicsMath>
			inline io2d::fill_rule _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::fill_rule(const brush_props_data_type& data) noexcept {
				return data._Fill_rule;
			}
			template<class GraphicsMath>
			inline basic_matrix_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::brush_matrix(const brush_props_data_type& data) noexcept {
				return data._Matrix;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::clip_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::create_clip_props() noexcept {
				clip_props_data_type data;
				data.clip = nullopt;
				data.fr = io2d::fill_rule::winding;
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::clip_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::create_clip_props(const basic_bounding_box<GraphicsMath>& bbox, io2d::fill_rule fr) noexcept {
				clip_props_data_type data;
				clip(data, bbox);
				data.fr = fr;
				return data;
			}
			template<class GraphicsMath>
			template<class Allocator>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::clip_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::create_clip_props(const basic_path_builder<_Graphics_surfaces_type, Allocator>& pb, io2d::fill_rule fr) {
				clip_props_data_type data;
				data.clip = basic_interpreted_path<_Graphics_surfaces_type>(pb);
				data.fr = fr;
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::clip_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::create_clip_props(const basic_interpreted_path<_Graphics_surfaces_type> ip, io2d::fill_rule fr) noexcept {
				clip_props_data_type data;
				data.clip = ip;
				data.fr = fr;
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::clip_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::copy_clip_props(const clip_props_data_type& data) {
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::clip_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::move_clip_props(clip_props_data_type&& data) noexcept {
				return data;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::destroy(clip_props_data_type& /*data*/) noexcept {
				// Do nothing.
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::clip(clip_props_data_type& data, const basic_bounding_box<GraphicsMath>& bbox) noexcept {
				basic_path_builder<_Graphics_surfaces_type> pb;
				basic_point_2d<GraphicsMath> point(bbox.x(), bbox.y());
				pb.new_figure(point);
				point.x(bbox.width());
				point.y(0.0f);
				pb.rel_line(point);
				point.x(0.0f);
				point.y(bbox.height());
				pb.rel_line(point);
				point.x(-bbox.width());
				point.y(0.0f);
				pb.rel_line(point);
				pb.close_figure();
				data.clip = basic_interpreted_path<_Graphics_surfaces_type>(pb);
			}
			template<class GraphicsMath>
			template<class Allocator>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::clip(clip_props_data_type& data, const basic_path_builder<_Graphics_surfaces_type, Allocator>& pb) {
				data.clip = basic_interpreted_path<_Graphics_surfaces_type>(pb);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::clip(clip_props_data_type& data, const basic_interpreted_path<_Graphics_surfaces_type>& ip) noexcept {
				data.clip = ip;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::fill_rule(clip_props_data_type& data, io2d::fill_rule fr) noexcept {
				data.fr = fr;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::paths::interpreted_path_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::clip(const clip_props_data_type& data) noexcept {
				return data.clip;
			}
			template<class GraphicsMath>
			inline io2d::fill_rule _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::fill_rule(const clip_props_data_type& data) noexcept {
				return data.fr;
			}

			// stroke props
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::stroke_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::create_stroke_props(float lw, io2d::line_cap lc, io2d::line_join lj, float ml) noexcept {
				stroke_props_data_type data;
				data._Line_width = lw;
				data._Miter_limit = ::std::min(ml, max_miter_limit());
				data._Line_cap = lc;
				data._Line_join = lj;
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::stroke_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::copy_stroke_props(const stroke_props_data_type& data) {
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::stroke_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::move_stroke_props(stroke_props_data_type&& data) noexcept {
				return data;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::destroy(stroke_props_data_type& /*data*/) noexcept {
				// Do nothing.
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::line_width(stroke_props_data_type& data, float lw) noexcept {
				data._Line_width = lw;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::line_cap(stroke_props_data_type& data, io2d::line_cap lc) noexcept {
				data._Line_cap = lc;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::line_join(stroke_props_data_type& data, io2d::line_join lj) noexcept {
				data._Line_join = lj;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::miter_limit(stroke_props_data_type& data, float ml) noexcept {
				data._Miter_limit = ::std::min(ml, max_miter_limit());
			}
			template<class GraphicsMath>
			inline float _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::line_width(const stroke_props_data_type& data) noexcept {
				return data._Line_width;
			}
			template<class GraphicsMath>
			inline io2d::line_cap _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::line_cap(const stroke_props_data_type& data) noexcept {
				return data._Line_cap;
			}
			template<class GraphicsMath>
			inline io2d::line_join _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::line_join(const stroke_props_data_type& data) noexcept {
				return data._Line_join;
			}
			template<class GraphicsMath>
			inline float _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::miter_limit(const stroke_props_data_type& data) noexcept {
				return data._Miter_limit;
			}
			template<class GraphicsMath>
			inline float _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::max_miter_limit() noexcept {
				return 10000.0F;
			}

			// mask props
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::mask_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::create_mask_props(io2d::wrap_mode wm, io2d::filter f, const basic_matrix_2d<GraphicsMath>& m) noexcept {
				mask_props_data_type data;
				data._Wrap_mode = wm;
				data._Filter = f;
				data._Matrix = m;
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::mask_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::copy_mask_props(const mask_props_data_type& data) {
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::mask_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::move_mask_props(mask_props_data_type&& data) noexcept {
				return data;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::destroy(mask_props_data_type& /*data*/) noexcept {
				// Do nothing.
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::wrap_mode(mask_props_data_type& data, io2d::wrap_mode wm) noexcept {
				data._Wrap_mode = wm;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::filter(mask_props_data_type& data, io2d::filter f) noexcept {
				data._Filter = f;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::mask_matrix(mask_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept {
				data._Matrix = m;
			}
			template<class GraphicsMath>
			inline io2d::wrap_mode _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::wrap_mode(const mask_props_data_type& data) noexcept {
				return data._Wrap_mode;
			}
			template<class GraphicsMath>
			inline io2d::filter _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::filter(const mask_props_data_type& data) noexcept {
				return data._Filter;
			}
			template<class GraphicsMath>
			inline basic_matrix_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::mask_matrix(const mask_props_data_type& data) noexcept {
				return data._Matrix;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::dashes_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::create_dashes() noexcept {
				dashes_data_type data;
				data.offset = 0.0f;
				return data;
			}
			template<class GraphicsMath>
			template<class ForwardIterator>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::dashes_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::create_dashes(float offset, ForwardIterator first, ForwardIterator last) {
				dashes_data_type data;
				data.offset = offset;
				data.pattern.insert(data.pattern.end(), first, last);
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::dashes_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::create_dashes(float offset, ::std::initializer_list<float> il) {
				dashes_data_type data;
				data.offset = offset;
				data.pattern.insert(data.pattern.end(), il);
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::dashes_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::copy_dashes(const dashes_data_type& data) {
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::dashes_data_type _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::move_dashes(dashes_data_type&& data) noexcept {
				return data;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_state_props::destroy(dashes_data_type& /*data*/) noexcept {
				// Do nothing.
			}
		}
	}
}
