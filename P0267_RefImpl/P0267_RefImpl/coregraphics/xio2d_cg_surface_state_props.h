#ifndef _IO2D_CG_SURFACE_STATE_PROPS_H_
#define _IO2D_CG_SURFACE_STATE_PROPS_H_

#include "xio2d_cg_main.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

// render_props_data_type
            
inline _GS::surface_state_props::render_props_data_type
_GS::surface_state_props::create_render_props(antialias aa, basic_matrix_2d<GraphicsMath> m, compositing_op co) noexcept {
    render_props_data_type data;
    data.antialiasing = aa;
    data.matrix = m;
    data.compositing = co;
    return data;
}

inline _GS::surface_state_props::render_props_data_type
_GS::surface_state_props::move_render_props(render_props_data_type&& data) noexcept {
    return data;
}
            
inline _GS::surface_state_props::render_props_data_type
_GS::surface_state_props::copy_render_props(const render_props_data_type& data) noexcept {
    return data;
}

inline void
_GS::surface_state_props::destroy(render_props_data_type& /*data*/) noexcept {
}
            
inline void
_GS::surface_state_props::antialiasing(render_props_data_type& data, antialias aa) noexcept {
    data.antialiasing = aa;
}
            
inline void
_GS::surface_state_props::surface_matrix(render_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept {
    data.matrix = m;
}
            
inline void
_GS::surface_state_props::compositing(render_props_data_type& data, io2d::compositing_op co) noexcept {
    data.compositing = co;
}
            
inline antialias
_GS::surface_state_props::antialiasing(const render_props_data_type& data) noexcept {
    return data.antialiasing;
}
            
inline basic_matrix_2d<GraphicsMath>
_GS::surface_state_props::surface_matrix(const render_props_data_type& data) noexcept {
    return data.matrix;
}
            
inline compositing_op
_GS::surface_state_props::compositing(const render_props_data_type& data) noexcept {
    return data.compositing;
}
            
// brush_props_data_type
            
inline _GS::surface_state_props::brush_props_data_type
_GS::surface_state_props::create_brush_props(io2d::wrap_mode wm, io2d::filter f, io2d::fill_rule r, const basic_matrix_2d<GraphicsMath>& m) noexcept {
    brush_props_data_type data;
    data.wrap_mode = wm;
    data.filter = f;
    data.fill_rule = r;
    data.matrix = m;
    return data;
}
            
inline _GS::surface_state_props::brush_props_data_type
_GS::surface_state_props::copy_brush_props(const brush_props_data_type& data) noexcept {
    return data;
}
            
inline _GS::surface_state_props::brush_props_data_type
_GS::surface_state_props::move_brush_props(brush_props_data_type&& data) noexcept {
    return data;
}
            
inline void
_GS::surface_state_props::destroy(brush_props_data_type& /*data*/) noexcept {
    // Do nothing.
}
            
inline void
_GS::surface_state_props::wrap_mode(brush_props_data_type& data, io2d::wrap_mode wm) noexcept {
    data.wrap_mode = wm;
}
            
inline void
_GS::surface_state_props::filter(brush_props_data_type& data, io2d::filter f) noexcept {
    data.filter = f;
}
            
inline void
_GS::surface_state_props::brush_matrix(brush_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept {
    data.matrix = m;
}
            
inline void
_GS::surface_state_props::fill_rule(brush_props_data_type& data, io2d::fill_rule fr) noexcept {
    data.fill_rule = fr;
}
            
inline wrap_mode
_GS::surface_state_props::wrap_mode(const brush_props_data_type& data) noexcept {
    return data.wrap_mode;
}
            
inline io2d::filter
_GS::surface_state_props::filter(const brush_props_data_type& data) noexcept {
    return data.filter;
}
            
inline io2d::fill_rule
_GS::surface_state_props::fill_rule(const brush_props_data_type& data) noexcept {
    return data.fill_rule;
}
            
inline basic_matrix_2d<GraphicsMath>
_GS::surface_state_props::brush_matrix(const brush_props_data_type& data) noexcept {
    return data.matrix;
}
    
// stroke_props_data_type
            
inline _GS::surface_state_props::stroke_props_data_type
_GS::surface_state_props::create_stroke_props(float lw, io2d::line_cap lc, io2d::line_join lj, float ml) noexcept {
    stroke_props_data_type data;
    data.width = lw;
    data.line_cap = lc;
    data.line_join = lj;
    data.miter_limit = ml;
    return data;
}

inline _GS::surface_state_props::stroke_props_data_type
_GS::surface_state_props::copy_stroke_props(const stroke_props_data_type& data) noexcept {
    return data;
}
            
inline _GS::surface_state_props::stroke_props_data_type
_GS::surface_state_props::move_stroke_props(stroke_props_data_type&& data) noexcept {
    return ::std::move(data);
}
            
inline void
_GS::surface_state_props::destroy(stroke_props_data_type& data) noexcept {
    // Do nothing.
}
            
inline void
_GS::surface_state_props::line_width(stroke_props_data_type& data, float lw) noexcept {
    data.width = lw;
}

inline void
_GS::surface_state_props::line_cap(stroke_props_data_type& data, io2d::line_cap lc) noexcept {
    data.line_cap = lc;
}

inline void
_GS::surface_state_props::line_join(stroke_props_data_type& data, io2d::line_join lj) noexcept {
    data.line_join = lj;
}
    
inline void
_GS::surface_state_props::miter_limit(stroke_props_data_type& data, float ml) noexcept {
    data.miter_limit = ml;
}
    
inline float
_GS::surface_state_props::line_width(const stroke_props_data_type& data) noexcept {
    return data.width;
}
    
inline io2d::line_cap
_GS::surface_state_props::line_cap(const stroke_props_data_type& data) noexcept {
    return data.line_cap;
}
    
inline io2d::line_join
_GS::surface_state_props::line_join(const stroke_props_data_type& data) noexcept {
    return data.line_join;
}
    
inline float
_GS::surface_state_props::miter_limit(const stroke_props_data_type& data) noexcept {
    return data.miter_limit;
}
    
inline float
_GS::surface_state_props::max_miter_limit() noexcept {
    return 1000.f; // this is an arbitrary number, since I can't find any official info on limits
}
    
// dashes_data_type
            
inline _GS::surface_state_props::dashes_data_type
_GS::surface_state_props::create_dashes() noexcept {
    dashes_data_type data;
    data.offset = 0.;
    return data;
}
    
template <class ForwardIterator>
inline _GS::surface_state_props::dashes_data_type
_GS::surface_state_props::create_dashes(float offset, ForwardIterator first, ForwardIterator last) {
    dashes_data_type data;
    data.offset = offset;
    data.pattern.assign( first, last );
    return data;
}
            
inline _GS::surface_state_props::dashes_data_type
_GS::surface_state_props::create_dashes(float offset, ::std::initializer_list<float> il) {
    return create_dashes(offset, ::std::begin(il), ::std::end(il));
}
            
inline _GS::surface_state_props::dashes_data_type
_GS::surface_state_props::copy_dashes(const dashes_data_type& data) {
    return data;
}
            
inline _GS::surface_state_props::dashes_data_type
_GS::surface_state_props::move_dashes(dashes_data_type&& data) noexcept {
    return ::std::move(data);
}
            
inline void
_GS::surface_state_props::destroy(dashes_data_type& data) noexcept {
    // Do nothing.
}
            
// clip_props_data_type
    
inline _GS::surface_state_props::clip_props_data_type
_GS::surface_state_props::create_clip_props() noexcept {
    return {};
}
    
inline _GS::surface_state_props::clip_props_data_type
_GS::surface_state_props::create_clip_props(const basic_bounding_box<GraphicsMath>& bbox, io2d::fill_rule fr) {
    basic_path_builder<_GS> pb;
    pb.new_figure(bbox.top_left());
    pb.rel_line({bbox.width(), 0});
    pb.rel_line({0, bbox.height()});
    pb.rel_line({-bbox.width(), 0});
    pb.rel_line({0, -bbox.height()});
    pb.close_figure();

    clip_props_data_type data;
    data.clip = basic_interpreted_path<_GS>{pb};
    data.fr = fr;
    return data;
}

template <class Allocator>
inline _GS::surface_state_props::clip_props_data_type
_GS::surface_state_props::create_clip_props(const basic_path_builder<_GS, Allocator>& pb, io2d::fill_rule fr) {
    clip_props_data_type data;
    data.clip = basic_interpreted_path<_GS>{pb};
    data.fr = fr;
    return data;
}

inline _GS::surface_state_props::clip_props_data_type
_GS::surface_state_props::create_clip_props(const basic_interpreted_path<_GS> &ip, io2d::fill_rule fr) noexcept {
    clip_props_data_type data;
    data.clip = ip;
    data.fr = fr;
    return data;
}

inline _GS::surface_state_props::clip_props_data_type
_GS::surface_state_props::copy_clip_props(const clip_props_data_type& data) noexcept {
    return data;
}
    
inline _GS::surface_state_props::clip_props_data_type
_GS::surface_state_props::move_clip_props(clip_props_data_type&& data) noexcept {
    return data;
}
    
inline void
_GS::surface_state_props::destroy(clip_props_data_type& data) noexcept {
    // Do nothing.
}
    
inline void
_GS::surface_state_props::fill_rule(clip_props_data_type& data, io2d::fill_rule fr) noexcept {
    data.fr = fr;
}

template <class Allocator>
inline void
_GS::surface_state_props::clip(clip_props_data_type& data, const basic_path_builder<_GS, Allocator>& pb) {
    data.clip = basic_interpreted_path<_GS>{pb};
}

inline void
_GS::surface_state_props::clip(clip_props_data_type& data, const basic_interpreted_path<_GS> &ip) noexcept {
    data.clip = ip;
}
    
inline io2d::fill_rule
_GS::surface_state_props::fill_rule(const clip_props_data_type& data) noexcept {
    return data.fr;
}
    
inline basic_interpreted_path<_GS>
_GS::surface_state_props::clip(const clip_props_data_type& data) noexcept {
    return data.clip;
}

// mask_props_data_type

inline _GS::surface_state_props::mask_props_data_type
_GS::surface_state_props::create_mask_props(io2d::wrap_mode wm, io2d::filter f, const basic_matrix_2d<GraphicsMath>& m) noexcept {
    mask_props_data_type data;
    data.filter = f;
    data.wrap_mode = wm;
    data.matrix = m;
    return data;
}

inline _GS::surface_state_props::mask_props_data_type
_GS::surface_state_props::copy_mask_props(const mask_props_data_type& data) noexcept {
    return data;
}
    
inline _GS::surface_state_props::mask_props_data_type 
_GS::surface_state_props::move_mask_props(mask_props_data_type&& data) noexcept {
    return data;
}
    
inline void
_GS::surface_state_props::destroy(mask_props_data_type& data) noexcept {
    // do nothing
}
    
inline void
_GS::surface_state_props::wrap_mode(mask_props_data_type& data, io2d::wrap_mode wm) noexcept {
    data.wrap_mode = wm;
}
    
inline void
_GS::surface_state_props::filter(mask_props_data_type& data, io2d::filter f) noexcept {
    data.filter = f;
}
    
inline void
_GS::surface_state_props::mask_matrix(mask_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept {
    data.matrix = m;
        
}
    
inline wrap_mode
_GS::surface_state_props::wrap_mode(const mask_props_data_type& data) noexcept {
    return data.wrap_mode;
}
    
inline filter
_GS::surface_state_props::filter(const mask_props_data_type& data) noexcept {
    return data.filter;
}
    
inline basic_matrix_2d<GraphicsMath>
_GS::surface_state_props::mask_matrix(const mask_props_data_type& data) noexcept {
    return data.matrix;
}

} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

#endif
