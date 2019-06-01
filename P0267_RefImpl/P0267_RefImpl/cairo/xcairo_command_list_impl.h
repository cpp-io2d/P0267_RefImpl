#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#include "xcairo.h"
#pragma once

#include "xcairo_helpers.h"
#include "xsystemheaders.h"
#include <cassert>
#if defined(_WIN32) || defined(_WIN64)
#include <cairo-win32.h>
#endif

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Cairo {
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clear_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_clear() noexcept {
				return clear_data_type{};
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clear_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_clear(::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>> sfc) noexcept {
				clear_data_type result;
				result.sfc = sfc;
				return result;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(clear_data_type& data, const ::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>>& sfc) noexcept {
				data.sfc = sfc;
			}
			template<class GraphicsMath>
			inline ::std::optional<::std::reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(const clear_data_type& data) noexcept {
				return data.sfc;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::flush_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_flush() noexcept {
				return flush_data_type{};
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::flush_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_flush(::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>> sfc) noexcept {
				flush_data_type result;
				result.sfc = sfc;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(flush_data_type& data, const::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>>& sfc) noexcept {
				data.sfc = sfc;
			}
			template<class GraphicsMath>
			inline ::std::optional<::std::reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(const flush_data_type& data) noexcept {
				return data.sfc;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_mark_dirty() noexcept {
				return mark_dirty_data_type{};
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_mark_dirty(::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>> sfc) noexcept {
				mark_dirty_data_type result;
				result.sfc = sfc;
				return result;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_mark_dirty(const basic_bounding_box<graphics_math_type>& ext) noexcept {
				mark_dirty_data_type result;
				result.ext = ext;
				return result;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_mark_dirty(::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>> sfc, const basic_bounding_box<graphics_math_type>& ext) noexcept
			{
				mark_dirty_data_type result;
				result.sfc = sfc;
				result.ext = ext;
				return result;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(mark_dirty_data_type& data, const::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>>& sfc) noexcept {
				data.sfc = sfc;
			}
			template<class GraphicsMath>
			inline ::std::optional<::std::reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(const mark_dirty_data_type& data) noexcept {
				return data.sfc;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::extents(mark_dirty_data_type& data, const::std::optional<basic_bounding_box<GraphicsMath>>& ext) noexcept {
				data.ext = ext;
			}
			template<class GraphicsMath>
			inline ::std::optional<basic_bounding_box<GraphicsMath>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::extents(const mark_dirty_data_type& data) noexcept {
				return data.ext;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::paint_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_paint(const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b, const ::std::optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp, const ::std::optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp, const ::std::optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				paint_data_type result;
				result.b = b;
				result.bp = bp;
				result.rp = rp;
				result.cl = cl;
				return result;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::paint_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_paint(::std::reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>> sfc, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b, const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				paint_data_type result;
				result.sfc = sfc;
				result.b = b;
				result.bp = bp;
				result.rp = rp;
				result.cl = cl;
				return result;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(paint_data_type& data, const::std::optional<::std::reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>>& sfc) noexcept {
				data.sfc = sfc;
			}
			template<class GraphicsMath>
			inline ::std::optional<::std::reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(const paint_data_type& data) noexcept {
				return data.sfc;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush(paint_data_type& data, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b) noexcept {
				data.b = b;
			}
			template<class GraphicsMath>
			inline const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush(const paint_data_type& data) noexcept {
				return data.b;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush_props(paint_data_type& data, const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp) noexcept {
				data.bp = bp;
			}
			template<class GraphicsMath>
			inline const::std::optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush_props(const paint_data_type& data) noexcept {
				return data.bp;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::render_props(paint_data_type& data, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp) noexcept {
				data.rp = rp;
			}
			template<class GraphicsMath>
			inline const::std::optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::render_props(const paint_data_type& data) noexcept {
				return data.rp;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clip_props(paint_data_type& data, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				data.cl = cl;
			}
			template<class GraphicsMath>
			inline const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clip_props(const paint_data_type& data) noexcept {
				return data.cl;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::stroke_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_stroke(const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b, const basic_interpreted_path<_Cairo_graphics_surfaces<GraphicsMath>>& ip, const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp, const optional<basic_stroke_props<_Cairo_graphics_surfaces<GraphicsMath>>>& sp, const optional<basic_dashes<_Cairo_graphics_surfaces<GraphicsMath>>>& d, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				return stroke_data_type{ nullopt, b, ip, bp, sp, d, rp, cl };
				//result.b = b;
				//result.ip = ip;
				//result.bp = bp;
				//result.sp = sp;
				//result.d = d;
				//result.rp = rp;
				//result.cl = cl;
				//return result;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::stroke_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_stroke(reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>> sfc, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b, const basic_interpreted_path<_Cairo_graphics_surfaces<GraphicsMath>>& ip, const optional<basic_brush_props<graphics_surfaces_type>>& bp, const optional<basic_stroke_props<_Cairo_graphics_surfaces<GraphicsMath>>>& sp, const optional<basic_dashes<_Cairo_graphics_surfaces<GraphicsMath>>>& d, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				return stroke_data_type(sfc, b, ip, bp, sp, d, rp, cl);
				//stroke_data_type result;
				//result.sfc = sfc;
				//result.b = b;
				//result.ip = ip;
				//result.bp = bp;
				//result.sp = sp;
				//result.d = d;
				//result.rp = rp;
				//result.cl = cl;
				//return result;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(stroke_data_type& data, const optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>>& sfc) noexcept {
				data.sfc = sfc;
			}
			template<class GraphicsMath>
			inline optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(const stroke_data_type& data) noexcept {
				return data.sfc;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush(stroke_data_type& data, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b) noexcept {
				data.b = b;
			}
			template<class GraphicsMath>
			inline const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush(const stroke_data_type& data) noexcept {
				return data.b.value();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::path(stroke_data_type& data, const basic_interpreted_path<_Cairo_graphics_surfaces<GraphicsMath>>& ip) noexcept {
				data.ip = ip;
			}
			template<class GraphicsMath>
			inline const basic_interpreted_path<_Cairo_graphics_surfaces<GraphicsMath>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::path(const stroke_data_type& data) noexcept {
				return data.ip.value();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::stroke_props(stroke_data_type& data, const basic_stroke_props<_Cairo_graphics_surfaces<GraphicsMath>>& sp) noexcept {
				data.sp = sp;
			}
			template<class GraphicsMath>
			inline optional<basic_stroke_props<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::stroke_props(const stroke_data_type& data) noexcept {
				return data.sp;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::dashes(stroke_data_type& data, const optional<basic_dashes<_Cairo_graphics_surfaces<GraphicsMath>>>& d) noexcept {
				data.d = d;
			}
			template<class GraphicsMath>
			inline optional<basic_dashes<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::dashes(const stroke_data_type& data) noexcept {
				return data.d;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush_props(stroke_data_type& data, const optional<basic_brush_props<graphics_surfaces_type>>& bp) noexcept {
				data.bp = bp;
			}
			template<class GraphicsMath>
			inline optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush_props(const stroke_data_type& data) noexcept {
				return data.bp;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::render_props(stroke_data_type& data, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp) noexcept {
				data.rp = rp;
			}
			template<class GraphicsMath>
			inline optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::render_props(const stroke_data_type& data) noexcept {
				return data.rp;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clip_props(stroke_data_type& data, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				data.cl = cl;
			}
			template<class GraphicsMath>
			inline optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clip_props(const stroke_data_type& data) noexcept {
				return data.cl;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::fill_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_fill(const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b, const basic_interpreted_path<_Cairo_graphics_surfaces<GraphicsMath>>& ip, const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				fill_data_type result;
				result.b = b;
				result.ip = ip;
				result.bp = bp;
				result.rp = rp;
				result.cl = cl;
				return result;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::fill_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_fill(reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>> sfc, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b, const basic_interpreted_path<_Cairo_graphics_surfaces<GraphicsMath>>& ip, const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				fill_data_type result;
				result.sfc = sfc;
				result.b = b;
				result.ip = ip;
				result.bp = bp;
				result.rp = rp;
				result.cl = cl;
				return result;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(fill_data_type& data, const optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>>& sfc) noexcept {
				data.sfc = sfc;
			}
			template<class GraphicsMath>
			inline optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(const fill_data_type& data) noexcept {
				return data.sfc;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush(fill_data_type& data, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b) noexcept {
				data.b = b;
			}
			template<class GraphicsMath>
			inline const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush(const fill_data_type& data) noexcept {
				return data.b.value();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::path(fill_data_type& data, const basic_interpreted_path<_Cairo_graphics_surfaces<GraphicsMath>>& ip) noexcept {
				data.ip = ip;
			}
			template<class GraphicsMath>
			inline const basic_interpreted_path<_Cairo_graphics_surfaces<GraphicsMath>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::path(const fill_data_type& data) noexcept {
				return data.ip.value();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush_props(fill_data_type& data, const optional<basic_brush_props<graphics_surfaces_type>>& bp) noexcept {
				data.bp = bp;
			}
			template<class GraphicsMath>
			inline optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush_props(const fill_data_type& data) noexcept {
				return data.bp;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::render_props(fill_data_type& data, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp) noexcept {
				data.rp = rp;
			}
			template<class GraphicsMath>
			inline optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::render_props(const fill_data_type& data) noexcept {
				return data.rp;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clip_props(fill_data_type& data, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				data.cl = cl;
			}
			template<class GraphicsMath>
			inline optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clip_props(const fill_data_type& data) noexcept {
				return data.cl;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mask_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_mask(const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& mb, const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp, const optional<basic_mask_props<_Cairo_graphics_surfaces<GraphicsMath>>>& mp, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				mask_data_type result;
				result.b = b;
				result.mb = mb;
				result.bp = bp;
				result.mp = mp;
				result.rp = rp;
				result.cl = cl;
				return result;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mask_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_mask(reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>> sfc, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& mb, const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp, const optional<basic_mask_props<_Cairo_graphics_surfaces<GraphicsMath>>>& mp, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				mask_data_type result;
				result.sfc = sfc;
				result.b = b;
				result.mb = mb;
				result.bp = bp;
				result.mp = mp;
				result.rp = rp;
				result.cl = cl;
				return result;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(mask_data_type& data, const optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>>& sfc) noexcept {
				data.sfc = sfc;
			}
			template<class GraphicsMath>
			inline optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(const mask_data_type& data) noexcept {
				return data.sfc;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush(mask_data_type& data, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b) noexcept {
				data.b = b;
			}
			template<class GraphicsMath>
			inline const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush(const mask_data_type& data) noexcept {
				return data.b.value();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mask_brush(mask_data_type& data, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& mb) noexcept {
				data.mb = mb;
			}
			template<class GraphicsMath>
			inline const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mask_brush(const mask_data_type& data) noexcept {
				return data.mb.value();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush_props(mask_data_type& data, const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp) noexcept {
				data.bp = bp;
			}
			template<class GraphicsMath>
			inline optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush_props(const mask_data_type& data) noexcept {
				return data.bp;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mask_props(mask_data_type& data, const optional<basic_mask_props<_Cairo_graphics_surfaces<GraphicsMath>>>& mp) noexcept {
				data.mp = mp;
			}
			template<class GraphicsMath>
			inline optional<basic_mask_props<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mask_props(const mask_data_type& data) noexcept {
				return data.mp;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::render_props(mask_data_type& data, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp) noexcept {
				data.rp = rp;
			}
			template<class GraphicsMath>
			inline optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::render_props(const mask_data_type& data) noexcept {
				return data.rp;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clip_props(mask_data_type& data, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				data.cl = cl;
			}
			template<class GraphicsMath>
			inline optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clip_props(const mask_data_type& data) noexcept {
				return data.cl;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_text_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_draw_text(const basic_point_2d<GraphicsMath>& pt, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b, const basic_font<_Cairo_graphics_surfaces<GraphicsMath>>& f, const string& text, const optional<basic_text_props<_Cairo_graphics_surfaces<GraphicsMath>>>& tp, const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp, const optional<basic_stroke_props<_Cairo_graphics_surfaces<GraphicsMath>>>& sp, const optional<basic_dashes<_Cairo_graphics_surfaces<GraphicsMath>>>& d, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				draw_text_data_type result;
				result.loc = pt;
				result.b = b;
				result.f = f;
				result.text = text;
				result.tp = tp;
				result.bp = bp;
				result.sp = sp;
				result.d = d;
				result.rp = rp;
				result.cl = cl;
				return result;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_text_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_draw_text(reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>> sfc, const basic_point_2d<GraphicsMath>& pt, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b, const basic_font<_Cairo_graphics_surfaces<GraphicsMath>>& f, const string& text, const optional<basic_text_props<_Cairo_graphics_surfaces<GraphicsMath>>>& tp, const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp, const optional<basic_stroke_props<_Cairo_graphics_surfaces<GraphicsMath>>>& sp, const optional<basic_dashes<_Cairo_graphics_surfaces<GraphicsMath>>>& d, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				draw_text_data_type result;
				result.sfc = sfc;
				result.loc = pt;
				result.b = b;
				result.f = f;
				result.text = text;
				result.tp = tp;
				result.bp = bp;
				result.sp = sp;
				result.d = d;
				result.rp = rp;
				result.cl = cl;
				return result;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_text_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_draw_text(const basic_bounding_box<GraphicsMath>& bb, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b, const basic_font<_Cairo_graphics_surfaces<GraphicsMath>>& f, const string& text, const optional<basic_text_props<_Cairo_graphics_surfaces<GraphicsMath>>>& tp, const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp, const optional<basic_stroke_props<_Cairo_graphics_surfaces<GraphicsMath>>>& sp, const optional<basic_dashes<_Cairo_graphics_surfaces<GraphicsMath>>>& d, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				draw_text_data_type result;
				result.loc = bb;
				result.b = b;
				result.f = f;
				result.text = text;
				result.tp = tp;
				result.bp = bp;
				result.sp = sp;
				result.d = d;
				result.rp = rp;
				result.cl = cl;
				return result;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_text_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_draw_text(reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>> sfc, const basic_bounding_box<GraphicsMath>& bb, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b, const basic_font<_Cairo_graphics_surfaces<GraphicsMath>>& f, const string& text, const optional<basic_text_props<_Cairo_graphics_surfaces<GraphicsMath>>>& tp, const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp, const optional<basic_stroke_props<_Cairo_graphics_surfaces<GraphicsMath>>>& sp, const optional<basic_dashes<_Cairo_graphics_surfaces<GraphicsMath>>>& d, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				draw_text_data_type result;
				result.sfc = sfc;
				result.loc = bb;
				result.b = b;
				result.f = f;
				result.text = text;
				result.tp = tp;
				result.bp = bp;
				result.sp = sp;
				result.d = d;
				result.rp = rp;
				result.cl = cl;
				return result;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(draw_text_data_type& data, const optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>>& sfc) noexcept {
				data.sfc = sfc;
			}
			template<class GraphicsMath>
			inline optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(const draw_text_data_type& data) noexcept {
				return data.sfc;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::location(draw_text_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
				data.loc = pt;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::location(draw_text_data_type& data, const basic_bounding_box<GraphicsMath>& bb) noexcept {
				data.loc = bb;
			}
			template<class GraphicsMath>
			inline ::std::variant<basic_point_2d<GraphicsMath>, basic_bounding_box<GraphicsMath>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::location(const draw_text_data_type& data) noexcept {
				return data.loc;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush(draw_text_data_type& data, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b) noexcept {
				data.b = b;
			}
			template<class GraphicsMath>
			inline const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush(const draw_text_data_type& data) noexcept {
				return data.b.value();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::font(draw_text_data_type& data, const basic_font<_Cairo_graphics_surfaces<GraphicsMath>>& f) noexcept {
				data.f = f;
			}
			template<class GraphicsMath>
			inline const basic_font<_Cairo_graphics_surfaces<GraphicsMath>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::font(const draw_text_data_type& data) noexcept {
				return data.f.value();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::text(draw_text_data_type& data, const string& t) noexcept {
				data.text = t;
			}
			template<class GraphicsMath>
			inline const string& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::text(const draw_text_data_type& data) noexcept {
				return data.text;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::text_props(draw_text_data_type& data, const optional<basic_text_props<_Cairo_graphics_surfaces<GraphicsMath>>>& tp) noexcept {
				data.tp = tp;
			}
			template<class GraphicsMath>
			inline const optional<basic_text_props<_Cairo_graphics_surfaces<GraphicsMath>>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::text_props(const draw_text_data_type& data) noexcept {
				return data.tp;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush_props(draw_text_data_type& data, const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp) noexcept {
				data.bp = bp;
			}
			template<class GraphicsMath>
			inline const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::brush_props(const draw_text_data_type& data) noexcept {
				return data.bp;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::stroke_props(draw_text_data_type& data, const optional<basic_stroke_props<_Cairo_graphics_surfaces<GraphicsMath>>>& sp) noexcept {
				data.sp = sp;
			}
			template<class GraphicsMath>
			inline const optional<basic_stroke_props<_Cairo_graphics_surfaces<GraphicsMath>>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::stroke_props(const draw_text_data_type& data) noexcept {
				return data.sp;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::dashes(draw_text_data_type& data, const optional<basic_dashes<_Cairo_graphics_surfaces<GraphicsMath>>>& d) noexcept {
				data.d = d;
			}
			template<class GraphicsMath>
			inline const optional<basic_dashes<_Cairo_graphics_surfaces<GraphicsMath>>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::dashes(const draw_text_data_type& data) noexcept {
				return data.d;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::render_props(draw_text_data_type& data, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& rp) noexcept {
				data.rp = rp;
			}
			template<class GraphicsMath>
			inline const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::render_props(const draw_text_data_type& data) noexcept {
				return data.rp;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clip_props(draw_text_data_type& data, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& cl) noexcept {
				data.cl = cl;
			}
			template<class GraphicsMath>
			inline const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clip_props(const draw_text_data_type& data) noexcept {
				return data.cl;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::run_function_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_run_function(const::std::function<void(basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>&, optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>>, void*)>& fn, void* user_data, optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>> sfc) noexcept {
				run_function_data_type result;
				result.func = fn;
				result.user_data = user_data;
				result.sfc = sfc;
				return result;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::run_function_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_run_function(const::std::function<void(basic_output_surface<_Cairo_graphics_surfaces<GraphicsMath>>&, optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>>, void*)>& fn, void* user_data, optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>> sfc) noexcept {
				run_function_data_type result;
				result.func = fn;
				result.user_data = user_data;
				result.sfc = sfc;
				return result;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::run_function_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_run_function(const::std::function<void(basic_unmanaged_output_surface<_Cairo_graphics_surfaces<GraphicsMath>>&, optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>>, void*)>& fn, void* user_data, optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>> sfc) noexcept {
				run_function_data_type result;
				result.func = fn;
				result.user_data = user_data;
				result.sfc = sfc;
				return result;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(run_function_data_type& data, const optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>>& sfc) noexcept {
				data.sfc = sfc;
			}
			template<class GraphicsMath>
			inline optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::surface(const run_function_data_type& data) noexcept {
				return data.sfc;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::func(run_function_data_type& data, const::std::function<void(basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>&, optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>>, void*)>& fn) noexcept {
				data.func = fn;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::func(run_function_data_type& data, const::std::function<void(basic_output_surface<_Cairo_graphics_surfaces<GraphicsMath>>&, optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>>, void*)>& fn) noexcept {
				data.func = fn;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::func(run_function_data_type& data, const::std::function<void(basic_unmanaged_output_surface<_Cairo_graphics_surfaces<GraphicsMath>>&, optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>>, void*)>& fn) noexcept {
				data.func = fn;
			}
			template<class GraphicsMath>
			inline const variant<::std::function<void(basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>&, optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>>, void*)>, function<void(basic_output_surface<_Cairo_graphics_surfaces<GraphicsMath>>&, optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>>, void*)>, function<void(basic_unmanaged_output_surface<_Cairo_graphics_surfaces<GraphicsMath>>&, optional<reference_wrapper<basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>>>, void*)>>& _Cairo_graphics_surfaces<GraphicsMath>::surfaces::func(const run_function_data_type& data) noexcept {
				return data.func;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::user_data(run_function_data_type& data, void* user_data) {
				data.user_data = user_data;
			}
			template<class GraphicsMath>
			inline void* _Cairo_graphics_surfaces<GraphicsMath>::surfaces::user_data(const run_function_data_type& data) {
				return data.user_data;
			}
		}
	}
}