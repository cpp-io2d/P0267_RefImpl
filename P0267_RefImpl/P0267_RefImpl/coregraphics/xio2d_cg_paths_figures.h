#ifndef _IO2D_CG_PATHS_FIGURES_H
#define _IO2D_CG_PATHS_FIGURES_H

#include "xio2d_cg_main.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

// abs_new_figure_data_type

inline _GS::paths::abs_new_figure_data_type
_GS::paths::create_abs_new_figure() noexcept {
    return {};
}
            
inline _GS::paths::abs_new_figure_data_type
_GS::paths::create_abs_new_figure(const basic_point_2d<GraphicsMath>& pt) noexcept {
    abs_new_figure_data_type data;
    data.pt = pt;
    return data;
}

inline _GS::paths::abs_new_figure_data_type
_GS::paths::copy_abs_new_figure(const abs_new_figure_data_type& data) noexcept {
    return data;
}
            
inline _GS::paths::abs_new_figure_data_type
_GS::paths::move_abs_new_figure(abs_new_figure_data_type&& data) noexcept {
    return data;
}
            
inline void
_GS::paths::destroy(abs_new_figure_data_type& /*data*/) noexcept {
    // Do nothing.
}

inline void
_GS::paths::at(abs_new_figure_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.pt = pt;
}

inline basic_point_2d<GraphicsMath>
_GS::paths::at(const abs_new_figure_data_type& data) noexcept {
    return data.pt;
}
    
// rel_new_figure_data_type

inline _GS::paths::rel_new_figure_data_type
_GS::paths::create_rel_new_figure() noexcept {
    return {};
}

inline _GS::paths::rel_new_figure_data_type
_GS::paths::create_rel_new_figure(const basic_point_2d<GraphicsMath>& pt) noexcept {
    rel_new_figure_data_type data;
    data.pt = pt;
    return data;
}
            
inline _GS::paths::rel_new_figure_data_type
_GS::paths::copy_rel_new_figure(const rel_new_figure_data_type& data) noexcept {
    return data;
}
            
inline _GS::paths::rel_new_figure_data_type
_GS::paths::move_rel_new_figure(rel_new_figure_data_type&& data) noexcept {
    return data;
}
            
inline void
_GS::paths::destroy(rel_new_figure_data_type& /*data*/) noexcept {
    // Do nothing.
}

inline void
_GS::paths::at(rel_new_figure_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.pt = pt;
}

inline basic_point_2d<GraphicsMath>
_GS::paths::at(const rel_new_figure_data_type& data) noexcept {
    return data.pt;
}
    
// close_figure_data_type

inline _GS::paths::close_figure_data_type
_GS::paths::create_close_figure() noexcept {
    return {};
}
            
inline _GS::paths::close_figure_data_type
_GS::paths::copy_close_figure(const close_figure_data_type& data) noexcept {
    return data;
}
            
inline _GS::paths::close_figure_data_type
_GS::paths::move_close_figure(close_figure_data_type&& data) noexcept {
    return data;
}
            
inline void
_GS::paths::destroy(close_figure_data_type& /*data*/) noexcept {
    // Do nothing.
}
            
// abs_matrix_data_type

inline _GS::paths::abs_matrix_data_type
_GS::paths::create_abs_matrix() noexcept {
    return {};
}

inline _GS::paths::abs_matrix_data_type
_GS::paths::create_abs_matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept {
    abs_matrix_data_type data;
    data.m = m;
    return data;
}
                        
inline _GS::paths::abs_matrix_data_type
_GS::paths::copy_abs_matrix(const abs_matrix_data_type& data) noexcept {
    return data;
}
            
inline _GS::paths::abs_matrix_data_type
_GS::paths::move_abs_matrix(abs_matrix_data_type&& data) noexcept {
    return data;
}
            
inline void
_GS::paths::destroy(abs_matrix_data_type& /*data*/) noexcept {
    // Do nothing.
}
            
inline void
_GS::paths::matrix(abs_matrix_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept {
    data.m = m;
}
            
inline basic_matrix_2d<GraphicsMath>
_GS::paths::matrix(const abs_matrix_data_type& data) noexcept {
    return data.m;
}
    
// rel_matrix_data_type

inline _GS::paths::rel_matrix_data_type
_GS::paths::create_rel_matrix() noexcept {
    return {};
}
            
inline _GS::paths::rel_matrix_data_type
_GS::paths::create_rel_matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept {
    rel_matrix_data_type data;
    data.m = m;
    return data;
}

inline _GS::paths::rel_matrix_data_type
_GS::paths::copy_rel_matrix(const rel_matrix_data_type& data) noexcept {
    return data;
}
            
inline _GS::paths::rel_matrix_data_type
_GS::paths::move_rel_matrix(rel_matrix_data_type&& data) noexcept {
    return data;
}
            
inline void
_GS::paths::destroy(rel_matrix_data_type& /*data*/) noexcept {
    // Do nothing.
}
            
inline void
_GS::paths::matrix(rel_matrix_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept {
    data.m = m;
}
            
inline basic_matrix_2d<GraphicsMath>
_GS::paths::matrix(const rel_matrix_data_type& data) noexcept {
    return data.m;
}
            
// revert_matrix_data_type
            
inline _GS::paths::revert_matrix_data_type
_GS::paths::create_revert_matrix() noexcept {
    return {};
}

inline _GS::paths::revert_matrix_data_type
_GS::paths::copy_revert_matrix(const revert_matrix_data_type& data) noexcept {
    return data;
}
            
inline _GS::paths::revert_matrix_data_type
_GS::paths::move_revert_matrix(revert_matrix_data_type&& data) noexcept {
    return data;
}
         
inline void
_GS::paths::destroy(revert_matrix_data_type& /*data*/) noexcept {
    // Do nothing.
}
            
// abs_cubic_curve_data_type

inline _GS::paths::abs_cubic_curve_data_type
_GS::paths::create_abs_cubic_curve() noexcept {
    return {};
}
 
inline _GS::paths::abs_cubic_curve_data_type
_GS::paths::create_abs_cubic_curve(const basic_point_2d<GraphicsMath>& cpt1, const basic_point_2d<GraphicsMath>& cpt2, const basic_point_2d<GraphicsMath>& ept) noexcept {
    abs_cubic_curve_data_type data;
    data.cpt1 = cpt1;
    data.cpt2 = cpt2;
    data.ept = ept;
    return data;
}
    
inline _GS::paths::abs_cubic_curve_data_type
_GS::paths::copy_abs_cubic_curve(const abs_cubic_curve_data_type& data) noexcept {
    return data;
}
            
inline _GS::paths::abs_cubic_curve_data_type
_GS::paths::move_abs_cubic_curve(abs_cubic_curve_data_type&& data) noexcept {
    return data;
}
            
inline void
_GS::paths::destroy(abs_cubic_curve_data_type& /*data*/) noexcept {
    // Do nothing.
}
 
inline void
_GS::paths::control_pt1(abs_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.cpt1 = pt;
}

inline void
_GS::paths::control_pt2(abs_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.cpt2 = pt;
}
    
inline void
_GS::paths::end_pt(abs_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.ept = pt;
}
    
inline basic_point_2d<GraphicsMath>
_GS::paths::control_pt1(const abs_cubic_curve_data_type& data) noexcept {
    return data.cpt1;
}
    
inline basic_point_2d<GraphicsMath>
_GS::paths::control_pt2(const abs_cubic_curve_data_type& data) noexcept {
    return data.cpt2;
}
    
inline basic_point_2d<GraphicsMath>
_GS::paths::end_pt(const abs_cubic_curve_data_type& data) noexcept {
    return data.ept;
}

// abs_line_data_type
            
inline _GS::paths::abs_line_data_type
_GS::paths::create_abs_line() noexcept {
    return {};
}
            
inline _GS::paths::abs_line_data_type
_GS::paths::create_abs_line(const basic_point_2d<GraphicsMath>& pt) noexcept {
    abs_line_data_type data;
    data.pt = pt;
    return data;
}
            
inline _GS::paths::abs_line_data_type
_GS::paths::copy_abs_line(const abs_line_data_type& data) noexcept {
    return data;
}
            
inline _GS::paths::abs_line_data_type
_GS::paths::move_abs_line(abs_line_data_type&& data) noexcept {
    return data;
}
            
inline void
_GS::paths::destroy(abs_line_data_type& /*data*/) noexcept {
    // Do nothing.
}

inline void
_GS::paths::to(abs_line_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.pt = pt;
}
            
inline basic_point_2d<GraphicsMath>
_GS::paths::to(const abs_line_data_type& data) noexcept {
    return data.pt;
}
            
// abs_quadratic_curve_data_type

inline _GS::paths::abs_quadratic_curve_data_type
_GS::paths::create_abs_quadratic_curve() noexcept {
    return {};
}
    
inline _GS::paths::abs_quadratic_curve_data_type
_GS::paths::create_abs_quadratic_curve(const basic_point_2d<GraphicsMath>& cpt, const basic_point_2d<GraphicsMath>& ept) noexcept {
    abs_quadratic_curve_data_type data;
    data.cpt = cpt;
    data.ept = ept;
    return data;
}
    
inline _GS::paths::abs_quadratic_curve_data_type
_GS::paths::copy_abs_quadratic_curve(const abs_quadratic_curve_data_type& data) noexcept {
    return data;
}
            
inline _GS::paths::abs_quadratic_curve_data_type
_GS::paths::move_abs_quadratic_curve(abs_quadratic_curve_data_type&& data) noexcept {
    return data;
}
 
inline void
_GS::paths::destroy(abs_quadratic_curve_data_type& /*data*/) noexcept {
    // Do nothing.
}
    
inline void
_GS::paths::control_pt(abs_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.cpt = pt;
}

inline void
_GS::paths::end_pt(abs_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.ept = pt;
}
    
inline basic_point_2d<GraphicsMath>
_GS::paths::control_pt(const abs_quadratic_curve_data_type& data) noexcept {
    return data.cpt;
}
    
inline basic_point_2d<GraphicsMath>
_GS::paths::end_pt(const abs_quadratic_curve_data_type& data) noexcept {
    return data.ept;
}
            
// arc_data_type

inline _GS::paths::arc_data_type
_GS::paths::create_arc() noexcept {
    return {};
}
 
inline _GS::paths::arc_data_type
_GS::paths::create_arc(const basic_point_2d<GraphicsMath>& rad, float rot, float sang) noexcept {
    arc_data_type data;
    data.radius = rad;
    data.rotation = rot;
    data.startAngle = sang;
    return data;
}
            
inline _GS::paths::arc_data_type
_GS::paths::copy_arc(const arc_data_type& data) noexcept {
    return data;
}
            
inline _GS::paths::arc_data_type
_GS::paths::move_arc(arc_data_type&& data) noexcept {
    return data;
}
            
inline void
_GS::paths::destroy(arc_data_type& /*data*/) noexcept {
    // Do nothing.
}
            
inline void
_GS::paths::radius(arc_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.radius = pt;
}
            
inline void
_GS::paths::rotation(arc_data_type& data, float rot) noexcept {
    data.rotation = rot;
}
            
inline void
_GS::paths::start_angle(arc_data_type& data, float sang) noexcept {
    data.startAngle = sang;
}
            
inline basic_point_2d<GraphicsMath>
_GS::paths::radius(const arc_data_type& data) noexcept {
    return data.radius;
}
            
inline float
_GS::paths::rotation(const arc_data_type& data) noexcept {
    return data.rotation;
}
            
inline float
_GS::paths::start_angle(const arc_data_type& data) noexcept {
    return data.startAngle;
}
            
inline basic_point_2d<GraphicsMath>
_GS::paths::center(const arc_data_type& data, const basic_point_2d<GraphicsMath>& cpt, const basic_matrix_2d<GraphicsMath>& m) noexcept {
    auto lmtx = m;
    lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
    auto centerOffset = point_for_angle<GraphicsMath>(two_pi<float> - data.startAngle, data.radius);
    centerOffset.y(-centerOffset.y());
    return cpt - centerOffset * lmtx;
}
            
inline basic_point_2d<GraphicsMath>
_GS::paths::end_pt(const arc_data_type& data, const basic_point_2d<GraphicsMath>& cpt, const basic_matrix_2d<GraphicsMath>& m) noexcept {
    auto lmtx = m;
    auto tfrm = basic_matrix_2d<GraphicsMath>::create_rotate(data.startAngle + data.rotation);
    lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
    auto pt = (data.radius * tfrm);
    pt.y(-pt.y());
    return cpt + pt * lmtx;
}
            
// rel_cubic_curve_data_type

inline _GS::paths::rel_cubic_curve_data_type
_GS::paths::create_rel_cubic_curve() noexcept {
    return {};
}

inline _GS::paths::rel_cubic_curve_data_type
_GS::paths::create_rel_cubic_curve(const basic_point_2d<GraphicsMath>& cpt1, const basic_point_2d<GraphicsMath>& cpt2, const basic_point_2d<GraphicsMath>& ept) noexcept {
    rel_cubic_curve_data_type data;
    data.cpt1 = cpt1;
    data.cpt2 = cpt2;
    data.ept = ept;
    return data;
}

inline _GS::paths::rel_cubic_curve_data_type
_GS::paths::copy_rel_cubic_curve(const rel_cubic_curve_data_type& data) noexcept {
    return data;
}

inline _GS::paths::rel_cubic_curve_data_type
_GS::paths::move_rel_cubic_curve(rel_cubic_curve_data_type&& data) noexcept {
    return data;
}

inline void
_GS::paths::destroy(rel_cubic_curve_data_type& /*data*/) noexcept {
    // Do nothing.
}

inline void
_GS::paths::control_pt1(rel_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.cpt1 = pt;
}

inline void
_GS::paths::control_pt2(rel_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.cpt2 = pt;
}

inline void
_GS::paths::end_pt(rel_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.ept = pt;
}

inline basic_point_2d<GraphicsMath>
_GS::paths::control_pt1(const rel_cubic_curve_data_type& data) noexcept {
    return data.cpt1;
}

inline basic_point_2d<GraphicsMath>
_GS::paths::control_pt2(const rel_cubic_curve_data_type& data) noexcept {
    return data.cpt2;
}

inline basic_point_2d<GraphicsMath>
_GS::paths::end_pt(const rel_cubic_curve_data_type& data) noexcept {
    return data.ept;
}
    
// rel_line_data_type

inline _GS::paths::rel_line_data_type
_GS::paths::create_rel_line() noexcept {
    return {};
}

inline _GS::paths::rel_line_data_type
_GS::paths::create_rel_line(const basic_point_2d<GraphicsMath>& pt) noexcept {
    rel_line_data_type data;
    data.pt = pt;
    return data;
}
            
inline _GS::paths::rel_line_data_type
_GS::paths::copy_rel_line(const rel_line_data_type& data) noexcept {
    return data;
}
            
inline _GS::paths::rel_line_data_type
_GS::paths::move_rel_line(rel_line_data_type&& data) noexcept {
    return data;
}
            
inline void
_GS::paths::destroy(rel_line_data_type& /*data*/) noexcept {
    // Do nothing.
}
            
inline void
_GS::paths::to(rel_line_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.pt = pt;
}
            
inline basic_point_2d<GraphicsMath>
_GS::paths::to(const rel_line_data_type& data) noexcept  {
    return data.pt;
}
            
// rel_quadratic_curve_data_type

inline _GS::paths::rel_quadratic_curve_data_type
_GS::paths::create_rel_quadratic_curve() noexcept {
    return {};
}
    
inline _GS::paths::rel_quadratic_curve_data_type
_GS::paths::create_rel_quadratic_curve(const basic_point_2d<GraphicsMath>& cpt, const basic_point_2d<GraphicsMath>& ept) noexcept {
    rel_quadratic_curve_data_type data;
    data.cpt = cpt;
    data.ept = ept;
    return data;
}

inline _GS::paths::rel_quadratic_curve_data_type
_GS::paths::copy_rel_quadratic_curve(const rel_quadratic_curve_data_type& data) noexcept {
    return data;
}
            
inline _GS::paths::rel_quadratic_curve_data_type
_GS::paths::move_rel_quadratic_curve(rel_quadratic_curve_data_type&& data) noexcept {
    return data;
}
            
inline void
_GS::paths::destroy(rel_quadratic_curve_data_type& /*data*/) noexcept {
    // Do nothing.
}

inline void
_GS::paths::control_pt(rel_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.cpt = pt;
}
    
inline void
_GS::paths::end_pt(rel_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept {
    data.ept = pt;
}
    
inline basic_point_2d<GraphicsMath>
_GS::paths::control_pt(const rel_quadratic_curve_data_type& data) noexcept {
    return data.cpt;
}

inline basic_point_2d<GraphicsMath>
_GS::paths::end_pt(const rel_quadratic_curve_data_type& data) noexcept {
    return data.ept;
}

} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

#endif
