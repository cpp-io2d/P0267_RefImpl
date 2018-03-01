#ifndef _IO2D_CG_
#define _IO2D_CG_

#include "io2d_x.h"

//#if defined(_Filesystem_support_test)
//#include <filesystem>
//#endif
//#include "P0267_RefImpl/P0267_RefImpl/P0267_RefImpl/xgraphicsmath.h"
//#include "P0267_RefImpl/P0267_RefImpl/P0267_RefImpl/xgraphicsmathfloat.h"
//#include "P0267_RefImpl/P0267_RefImpl/P0267_RefImpl/xgraphicsmath_impl.h"
//#include "P0267_RefImpl/P0267_RefImpl/P0267_RefImpl/xgraphicsmathfloat_impl.h"


#include <CoreGraphics/CoreGraphics.h>

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

using GraphicsMath = _Graphics_math_float_impl;

struct _GS {

using graphics_math_type = GraphicsMath;
            
struct paths {
    struct _AbsNewFigure {
        basic_point_2d<GraphicsMath> pt;
    };
    using abs_new_figure_data_type = _AbsNewFigure;
    static abs_new_figure_data_type create_abs_new_figure() noexcept;
    static abs_new_figure_data_type create_abs_new_figure(const basic_point_2d<GraphicsMath>& pt) noexcept;
    static abs_new_figure_data_type copy_abs_new_figure(const abs_new_figure_data_type& data) noexcept;
    static abs_new_figure_data_type move_abs_new_figure(abs_new_figure_data_type&& data) noexcept;
    static void destroy(abs_new_figure_data_type& data) noexcept;
    static void at(abs_new_figure_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static basic_point_2d<GraphicsMath> at(const abs_new_figure_data_type& data) noexcept;
    
    struct _RelNewFigure {
        basic_point_2d<GraphicsMath> pt;
    };
    using rel_new_figure_data_type = _RelNewFigure;
    static rel_new_figure_data_type create_rel_new_figure() noexcept;
    static rel_new_figure_data_type create_rel_new_figure(const basic_point_2d<GraphicsMath>& pt) noexcept;
    static rel_new_figure_data_type copy_rel_new_figure(const rel_new_figure_data_type& data) noexcept;
    static rel_new_figure_data_type move_rel_new_figure(rel_new_figure_data_type&& data) noexcept;
    static void destroy(rel_new_figure_data_type& data) noexcept;
    static void at(rel_new_figure_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static basic_point_2d<GraphicsMath> at(const rel_new_figure_data_type& data) noexcept;
    
    struct _CloseFigure {
    };
    using close_figure_data_type = _CloseFigure;
    static close_figure_data_type create_close_figure() noexcept;
    static close_figure_data_type copy_close_figure(const close_figure_data_type& data) noexcept;
    static close_figure_data_type move_close_figure(close_figure_data_type&& data) noexcept;
    static void destroy(close_figure_data_type& data) noexcept;
    
    struct _AbsMatrix {
        basic_matrix_2d<GraphicsMath> m;
    };
    using abs_matrix_data_type = _AbsMatrix;
    static abs_matrix_data_type create_abs_matrix() noexcept;
    static abs_matrix_data_type create_abs_matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept;
    static abs_matrix_data_type copy_abs_matrix(const abs_matrix_data_type& data) noexcept;
    static abs_matrix_data_type move_abs_matrix(abs_matrix_data_type&& data) noexcept;
    static void destroy(abs_matrix_data_type& data) noexcept;
    static void matrix(abs_matrix_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept;
    static basic_matrix_2d<GraphicsMath> matrix(const abs_matrix_data_type& data) noexcept;
    
    struct _RelMatrix {
        basic_matrix_2d<GraphicsMath> m;
    };
    using rel_matrix_data_type = _RelMatrix;
    static rel_matrix_data_type create_rel_matrix() noexcept;
    static rel_matrix_data_type create_rel_matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept;
    static rel_matrix_data_type copy_rel_matrix(const rel_matrix_data_type& data) noexcept;
    static rel_matrix_data_type move_rel_matrix(rel_matrix_data_type&& data) noexcept;
    static void destroy(rel_matrix_data_type& data) noexcept;
    static void matrix(rel_matrix_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept;
    static basic_matrix_2d<GraphicsMath> matrix(const rel_matrix_data_type& data) noexcept;
    
    struct _RevertMatrix {
    };
    using revert_matrix_data_type = _RevertMatrix;
    static revert_matrix_data_type create_revert_matrix() noexcept;
    static revert_matrix_data_type copy_revert_matrix(const revert_matrix_data_type& data) noexcept;
    static revert_matrix_data_type move_revert_matrix(revert_matrix_data_type&& data) noexcept;
    static void destroy(revert_matrix_data_type& data) noexcept;
    
    struct _AbsCubicCurve {
        basic_point_2d<GraphicsMath> cpt1;
        basic_point_2d<GraphicsMath> cpt2;
        basic_point_2d<GraphicsMath> ept;
    };
    using abs_cubic_curve_data_type = _AbsCubicCurve;
    static abs_cubic_curve_data_type create_abs_cubic_curve() noexcept;
    static abs_cubic_curve_data_type create_abs_cubic_curve(const basic_point_2d<GraphicsMath>& cpt1, const basic_point_2d<GraphicsMath>& cpt2, const basic_point_2d<GraphicsMath>& ept) noexcept;
    static abs_cubic_curve_data_type copy_abs_cubic_curve(const abs_cubic_curve_data_type& data) noexcept;
    static abs_cubic_curve_data_type move_abs_cubic_curve(abs_cubic_curve_data_type&& data) noexcept;
    static void destroy(abs_cubic_curve_data_type& data) noexcept;
    static void control_pt1(abs_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static void control_pt2(abs_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static void end_pt(abs_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static basic_point_2d<GraphicsMath> control_pt1(const abs_cubic_curve_data_type& data) noexcept;
    static basic_point_2d<GraphicsMath> control_pt2(const abs_cubic_curve_data_type& data) noexcept;
    static basic_point_2d<GraphicsMath> end_pt(const abs_cubic_curve_data_type& data) noexcept;

    struct _AbsLine {
        basic_point_2d<GraphicsMath> pt;
    };
    using abs_line_data_type = _AbsLine;
    static abs_line_data_type create_abs_line() noexcept;
    static abs_line_data_type create_abs_line(const basic_point_2d<GraphicsMath>& pt) noexcept;
    static abs_line_data_type copy_abs_line(const abs_line_data_type& data) noexcept;
    static abs_line_data_type move_abs_line(abs_line_data_type&& data) noexcept;
    static void destroy(abs_line_data_type& data) noexcept;
    static void to(abs_line_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static basic_point_2d<GraphicsMath> to(const abs_line_data_type& data) noexcept;
    
    struct _AbsQuadraticCurve {
        basic_point_2d<GraphicsMath> cpt;
        basic_point_2d<GraphicsMath> ept;
    };
    using abs_quadratic_curve_data_type = _AbsQuadraticCurve;
    static abs_quadratic_curve_data_type create_abs_quadratic_curve() noexcept;
    static abs_quadratic_curve_data_type create_abs_quadratic_curve(const basic_point_2d<GraphicsMath>& cpt, const basic_point_2d<GraphicsMath>& ept) noexcept;
    static abs_quadratic_curve_data_type copy_abs_quadratic_curve(const abs_quadratic_curve_data_type& data) noexcept;
    static abs_quadratic_curve_data_type move_abs_quadratic_curve(abs_quadratic_curve_data_type&& data) noexcept;
    static void destroy(abs_quadratic_curve_data_type& data) noexcept;
    static void control_pt(abs_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static void end_pt(abs_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static basic_point_2d<GraphicsMath> control_pt(const abs_quadratic_curve_data_type& data) noexcept;
    static basic_point_2d<GraphicsMath> end_pt(const abs_quadratic_curve_data_type& data) noexcept;
    
    struct _Arc {
        basic_point_2d<GraphicsMath> radius;
        float rotation = {};
        float startAngle = {};
    };
    using arc_data_type = _Arc;
    static arc_data_type create_arc() noexcept;
    static arc_data_type create_arc(const basic_point_2d<GraphicsMath>& rad, float rot, float sang) noexcept;
    static arc_data_type copy_arc(const arc_data_type& data) noexcept;
    static arc_data_type move_arc(arc_data_type&& data) noexcept;
    static void destroy(arc_data_type& data) noexcept;
    static void radius(arc_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static void rotation(arc_data_type& data, float rot) noexcept;
    static void start_angle(arc_data_type& data, float sang) noexcept;
    static basic_point_2d<GraphicsMath> radius(const arc_data_type& data) noexcept;
    static float rotation(const arc_data_type& data) noexcept;
    static float start_angle(const arc_data_type& data) noexcept;
    static basic_point_2d<GraphicsMath> center(const arc_data_type& data, const basic_point_2d<GraphicsMath>& cpt, const basic_matrix_2d<GraphicsMath>& m) noexcept;
    static basic_point_2d<GraphicsMath> end_pt(const arc_data_type& data, const basic_point_2d<GraphicsMath>& cpt, const basic_matrix_2d<GraphicsMath>& m) noexcept;
    
    struct _RelCubicCurve {
        basic_point_2d<GraphicsMath> cpt1;
        basic_point_2d<GraphicsMath> cpt2;
        basic_point_2d<GraphicsMath> ept;
    };
    using rel_cubic_curve_data_type = _RelCubicCurve;
    static rel_cubic_curve_data_type create_rel_cubic_curve() noexcept;
    static rel_cubic_curve_data_type create_rel_cubic_curve(const basic_point_2d<GraphicsMath>& cpt1, const basic_point_2d<GraphicsMath>& cpt2, const basic_point_2d<GraphicsMath>& ept) noexcept;
    static rel_cubic_curve_data_type copy_rel_cubic_curve(const rel_cubic_curve_data_type& data) noexcept;
    static rel_cubic_curve_data_type move_rel_cubic_curve(rel_cubic_curve_data_type&& data) noexcept;
    static void destroy(rel_cubic_curve_data_type& data) noexcept;
    static void control_pt1(rel_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static void control_pt2(rel_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static void end_pt(rel_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static basic_point_2d<GraphicsMath> control_pt1(const rel_cubic_curve_data_type& data) noexcept;
    static basic_point_2d<GraphicsMath> control_pt2(const rel_cubic_curve_data_type& data) noexcept;
    static basic_point_2d<GraphicsMath> end_pt(const rel_cubic_curve_data_type& data) noexcept;
    
    struct _RelLine {
        basic_point_2d<GraphicsMath> pt;
    };
    using rel_line_data_type = _RelLine;
    static rel_line_data_type create_rel_line() noexcept;
    static rel_line_data_type create_rel_line(const basic_point_2d<GraphicsMath>& pt) noexcept;
    static rel_line_data_type copy_rel_line(const rel_line_data_type& data) noexcept;
    static rel_line_data_type move_rel_line(rel_line_data_type&& data) noexcept;
    static void destroy(rel_line_data_type& data) noexcept;
    static void to(rel_line_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static basic_point_2d<GraphicsMath> to(const rel_line_data_type& data) noexcept;
    
    struct _RelQuadraticCurve {
        basic_point_2d<GraphicsMath> cpt;
        basic_point_2d<GraphicsMath> ept;
    };
    using rel_quadratic_curve_data_type = _RelQuadraticCurve;
    static rel_quadratic_curve_data_type create_rel_quadratic_curve() noexcept;
    static rel_quadratic_curve_data_type create_rel_quadratic_curve(const basic_point_2d<GraphicsMath>& cpt, const basic_point_2d<GraphicsMath>& ept) noexcept;
    static rel_quadratic_curve_data_type copy_rel_quadratic_curve(const rel_quadratic_curve_data_type& data) noexcept;
    static rel_quadratic_curve_data_type move_rel_quadratic_curve(rel_quadratic_curve_data_type&& data) noexcept;
    static void destroy(rel_quadratic_curve_data_type& data) noexcept;
    static void control_pt(rel_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static void end_pt(rel_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt) noexcept;
    static basic_point_2d<GraphicsMath> control_pt(const rel_quadratic_curve_data_type& data) noexcept;
    static basic_point_2d<GraphicsMath> end_pt(const rel_quadratic_curve_data_type& data) noexcept;
    
    struct _InterpretedPath {
        using path_t = remove_pointer_t<CGPathRef>;
        ::std::shared_ptr<path_t> path; // will stay nullptr for empty path
    };
    using interpreted_path_data_type = _InterpretedPath;
    static interpreted_path_data_type create_interpreted_path() noexcept;
    template <class ForwardIterator>
    static interpreted_path_data_type create_interpreted_path(ForwardIterator first, ForwardIterator last);    
    static interpreted_path_data_type copy_interpreted_path(const interpreted_path_data_type&) noexcept;
    static interpreted_path_data_type move_interpreted_path(interpreted_path_data_type&&) noexcept;
    static void destroy(interpreted_path_data_type&) noexcept;
    static bool is_empty(const interpreted_path_data_type&) noexcept;
};
                
struct brushes {
    struct _SolidColor {
        using color_t = remove_pointer_t<CGColorRef>;
        ::std::unique_ptr<color_t, decltype(&CGColorRelease)> color{ nullptr, &CGColorRelease };
    };
    struct _Linear {
        using gradient_t = remove_pointer_t<CGGradientRef>;
        basic_point_2d<GraphicsMath> start;
        basic_point_2d<GraphicsMath> end;
        ::std::unique_ptr<gradient_t, decltype(&CGGradientRelease)> gradient{ nullptr, &CGGradientRelease };
    };
    struct _Radial {
        using gradient_t = remove_pointer_t<CGGradientRef>;
        basic_circle<GraphicsMath> start;
        basic_circle<GraphicsMath> end;
        ::std::unique_ptr<gradient_t, decltype(&CGGradientRelease)> gradient{ nullptr, &CGGradientRelease };
    };
    struct _Surface {
        using bitmap_t = remove_pointer_t<CGContextRef>;
        using image_t = remove_pointer_t<CGImageRef>;
        ::std::unique_ptr<bitmap_t, decltype(&CGContextRelease)> bitmap{ nullptr, &CGContextRelease };
        ::std::unique_ptr<image_t, decltype(&CGImageRelease)> image{ nullptr, &CGImageRelease };
        int width = 0;
        int height = 0;
    };
    struct _Brush {
        using brush_t = ::std::variant<_SolidColor, _Surface, _Radial, _Linear>;
        ::std::shared_ptr<const brush_t> brush;
        brush_type brushType;
    };
    using brush_data_type = _Brush;
    static brush_data_type create_brush(const rgba_color& c);
    template <class InputIterator>
    static brush_data_type create_brush(const basic_point_2d<GraphicsMath>& begin, const basic_point_2d<GraphicsMath>& end, InputIterator first, InputIterator last);
    static brush_data_type create_brush(const basic_point_2d<GraphicsMath>& begin, const basic_point_2d<GraphicsMath>& end, ::std::initializer_list<gradient_stop> il);
    template <class InputIterator>
    static brush_data_type create_brush(const basic_circle<GraphicsMath>& start, const basic_circle<GraphicsMath>& end, InputIterator first, InputIterator last);
    static brush_data_type create_brush(const basic_circle<GraphicsMath>& start, const basic_circle<GraphicsMath>& end, ::std::initializer_list<gradient_stop> il);
    static brush_data_type create_brush(basic_image_surface<_GS>&& img);
    static brush_data_type copy_brush(const brush_data_type& data);
    static brush_data_type move_brush(brush_data_type&& data) noexcept;
    static void destroy(brush_data_type& data) noexcept;
    static brush_type get_brush_type(const brush_data_type& data) noexcept;
};
    
struct surface_state_props {
    struct _Render {
        antialias antialiasing = antialias::good;
        basic_matrix_2d<GraphicsMath> matrix;
        compositing_op compositing = compositing_op::over;
    };
    using render_props_data_type = _Render;
    static render_props_data_type create_render_props(antialias aa = antialias::good, basic_matrix_2d<GraphicsMath> m = basic_matrix_2d<GraphicsMath>{}, compositing_op co = compositing_op::over) noexcept;
    static render_props_data_type copy_render_props(const render_props_data_type& data) noexcept;
    static render_props_data_type move_render_props(render_props_data_type&& data) noexcept;
    static void destroy(render_props_data_type& data) noexcept;
    static void antialiasing(render_props_data_type& data, antialias aa) noexcept;
    static void surface_matrix(render_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept;
    static void compositing(render_props_data_type& data, io2d::compositing_op co) noexcept;
    static antialias antialiasing(const render_props_data_type& data) noexcept;
    static basic_matrix_2d<GraphicsMath> surface_matrix(const render_props_data_type& data) noexcept;
    static compositing_op compositing(const render_props_data_type& data) noexcept;
    
    struct _Brush {
        wrap_mode wrap_mode = wrap_mode::none;
        filter filter = filter::good;
        fill_rule fill_rule = fill_rule::winding;
        basic_matrix_2d<GraphicsMath> matrix;
    };
    using brush_props_data_type = _Brush;
    static brush_props_data_type create_brush_props(io2d::wrap_mode wm = io2d::wrap_mode::none, io2d::filter f = io2d::filter::good, io2d::fill_rule = io2d::fill_rule::winding, const basic_matrix_2d<GraphicsMath>& m = basic_matrix_2d<GraphicsMath>{}) noexcept;
    static brush_props_data_type copy_brush_props(const brush_props_data_type& data) noexcept;
    static brush_props_data_type move_brush_props(brush_props_data_type&& data) noexcept;
    static void destroy(brush_props_data_type& data) noexcept;
    static void wrap_mode(brush_props_data_type& data, io2d::wrap_mode wm) noexcept;
    static void filter(brush_props_data_type& data, io2d::filter f) noexcept;
    static void fill_rule(brush_props_data_type& data, io2d::fill_rule fr) noexcept;
    static void brush_matrix(brush_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept;
    static io2d::wrap_mode wrap_mode(const brush_props_data_type& data) noexcept;
    static io2d::filter filter(const brush_props_data_type& data) noexcept;
    static io2d::fill_rule fill_rule(const brush_props_data_type& data) noexcept;
    static basic_matrix_2d<GraphicsMath> brush_matrix(const brush_props_data_type& data) noexcept;

    struct _Clip {
        basic_interpreted_path<_GS> clip;
        io2d::fill_rule fr = fill_rule::winding;
    };
    using clip_props_data_type = _Clip;
    static clip_props_data_type create_clip_props() noexcept;
    static clip_props_data_type create_clip_props(const basic_bounding_box<GraphicsMath>& bbox, io2d::fill_rule fr);
    template <class Allocator>
    static clip_props_data_type create_clip_props(const basic_path_builder<_GS, Allocator>& pb, io2d::fill_rule fr);
    static clip_props_data_type create_clip_props(const basic_interpreted_path<_GS> &ip, io2d::fill_rule fr) noexcept;
    static clip_props_data_type copy_clip_props(const clip_props_data_type& data) noexcept;
    static clip_props_data_type move_clip_props(clip_props_data_type&& data) noexcept;
    static void destroy(clip_props_data_type& data) noexcept;
    static void fill_rule(clip_props_data_type& data, io2d::fill_rule fr) noexcept;
    template <class Allocator>
    static void clip(clip_props_data_type& data, const basic_path_builder<_GS, Allocator>& pb);
    static void clip(clip_props_data_type& data, const basic_interpreted_path<_GS> &ip) noexcept;
    static io2d::fill_rule fill_rule(const clip_props_data_type& data) noexcept;
    static basic_interpreted_path<_GS> clip(const clip_props_data_type& data) noexcept;
    
    struct _Stroke {
        float width = 2.0F;
        float miter_limit = 10.0F;
        line_cap line_cap = line_cap::none;
        line_join line_join = line_join::miter;
    };
    using stroke_props_data_type = _Stroke;
    static stroke_props_data_type create_stroke_props(float lw = 2.0f, io2d::line_cap lc = io2d::line_cap::none, io2d::line_join lj = io2d::line_join::miter, float ml = 10.0f) noexcept;
    static stroke_props_data_type copy_stroke_props(const stroke_props_data_type& data) noexcept;
    static stroke_props_data_type move_stroke_props(stroke_props_data_type&& data) noexcept;
    static void destroy(stroke_props_data_type& data) noexcept;
    static void line_width(stroke_props_data_type& data, float lw) noexcept;
    static void line_cap(stroke_props_data_type& data, io2d::line_cap lc) noexcept;
    static void line_join(stroke_props_data_type& data, io2d::line_join lj) noexcept;
    static void miter_limit(stroke_props_data_type& data, float ml) noexcept;
    static float line_width(const stroke_props_data_type& data) noexcept;
    static io2d::line_cap line_cap(const stroke_props_data_type& data) noexcept;
    static io2d::line_join line_join(const stroke_props_data_type& data) noexcept;
    static float miter_limit(const stroke_props_data_type& data) noexcept;
    static float max_miter_limit() noexcept;
    //
    //                    // mask_props
    //
    //                    struct _Mask_props_data {
    //                        experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::repeat;
    //                        experimental::io2d::filter _Filter = experimental::io2d::filter::good;
    //                        basic_matrix_2d<GraphicsMath> _Matrix = basic_matrix_2d<GraphicsMath>{};
    //                    };
    //
    //                    using mask_props_data_type = _Mask_props_data;
    //
    //                    static mask_props_data_type create_mask_props(io2d::wrap_mode wm = io2d::wrap_mode::none, io2d::filter f = io2d::filter::good, const basic_matrix_2d<GraphicsMath>& m = basic_matrix_2d<GraphicsMath>{}) noexcept;
    //                    static mask_props_data_type copy_mask_props(const mask_props_data_type& data);
    //                    static mask_props_data_type move_mask_props(mask_props_data_type&& data) noexcept;
    //                    static void destroy(mask_props_data_type& data) noexcept;
    //                    static void wrap_mode(mask_props_data_type& data, io2d::wrap_mode wm) noexcept;
    //                    static void filter(mask_props_data_type& data, io2d::filter f) noexcept;
    //                    static void mask_matrix(mask_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept;
    //                    static io2d::wrap_mode wrap_mode(const mask_props_data_type& data) noexcept;
    //                    static io2d::filter filter(const mask_props_data_type& data) noexcept;
    //                    static basic_matrix_2d<GraphicsMath> mask_matrix(const mask_props_data_type& data) noexcept;
    //
    // dashes
    struct _Dashes_data {
        float offset;
        ::std::vector<double> pattern;
    };
    
    using dashes_data_type = _Dashes_data;
    static dashes_data_type create_dashes() noexcept;
    template <class ForwardIterator>
    static dashes_data_type create_dashes(float offset, ForwardIterator first, ForwardIterator last);
    static dashes_data_type create_dashes(float offset, ::std::initializer_list<float> il);
    static dashes_data_type copy_dashes(const dashes_data_type& data);
    static dashes_data_type move_dashes(dashes_data_type&& data) noexcept;
    static void destroy(dashes_data_type& data) noexcept;
};
                
                struct surfaces {
                    struct _Image_surface_data {
                        using context_t = remove_pointer_t<CGContextRef>;
                        ::std::unique_ptr<context_t, decltype(&CGContextRelease)> context{ nullptr, &CGContextRelease };
                        basic_display_point<GraphicsMath> dimensions;
                        io2d::format format;
                    };
                    using image_surface_data_type = _Image_surface_data;
                
                    // 13.15.3, construct/copy/move/destroy:
                    static image_surface_data_type create_image_surface(io2d::format fmt, int width, int height);
                    static image_surface_data_type create_image_surface(filesystem::path p, image_file_format iff, io2d::format fmt);
                    static image_surface_data_type create_image_surface(filesystem::path p, image_file_format iff, io2d::format fmt, ::std::error_code& ec) noexcept;
                    static image_surface_data_type move_image_surface(image_surface_data_type&& data) noexcept;
                    static void destroy(image_surface_data_type& data) noexcept;
                    
                    // 13.15.4, members:
                    static void save(image_surface_data_type& data, const filesystem::path &p, image_file_format iff);
                    static void save(image_surface_data_type& data, const filesystem::path &p, image_file_format iff, error_code& ec) noexcept;

                    // 13.15.5, static members:
                    static basic_display_point<GraphicsMath> max_dimensions() noexcept;

                    // 13.15.6, observers:
                    static io2d::format format(const image_surface_data_type& data) noexcept;
                    static basic_display_point<GraphicsMath> dimensions(const image_surface_data_type& data) noexcept;
                    
                    // 13.15.7, modifiers:
                    static void clear(image_surface_data_type& data);
                    static void flush(image_surface_data_type& data);
                    static void flush(image_surface_data_type& data, error_code& ec) noexcept;
                    static void mark_dirty(image_surface_data_type& data);
                    static void mark_dirty(image_surface_data_type& data, error_code& ec) noexcept;
                    static void mark_dirty(image_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents);
                    static void mark_dirty(image_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents, error_code& ec) noexcept;
                    static void paint(image_surface_data_type& data, const basic_brush<_GS>& b, const basic_brush_props<_GS>& bp, const basic_render_props<_GS>& rp, const basic_clip_props<_GS>& cl);
                    static void stroke(image_surface_data_type& data, const basic_brush<_GS>& b, const basic_interpreted_path<_GS>& ip, const basic_brush_props<_GS>& bp, const basic_stroke_props<_GS>& sp, const basic_dashes<_GS>& d, const basic_render_props<_GS>& rp, const basic_clip_props<_GS>& cl);
                    static void fill(image_surface_data_type& data, const basic_brush<_GS>& b, const basic_interpreted_path<_GS>& ip, const basic_brush_props<_GS>& bp, const basic_render_props<_GS>& rp, const basic_clip_props<_GS>& cl);
                    static void mask(image_surface_data_type& data, const basic_brush<_GS>& b, const basic_brush<_GS>& mb, const basic_brush_props<_GS>& bp, const basic_mask_props<_GS>& mp, const basic_render_props<_GS>& rp, const basic_clip_props<_GS>& cl);
                    
//                    template <class GraphicsSurfaces>
//                    basic_image_surface<GraphicsSurfaces> copy_image_surface(
//                                                                             basic_image_surface<GraphicsSurfaces>& sfc) noexcept;
                    
                    // display surfaces
/*
#if defined(_WIN32) || defined(_WIN64)
                    struct _Display_surface_win32_data {
                        HINSTANCE hInstance = nullptr;
                        HWND hwnd = nullptr;
                        HDC hdc = nullptr;
                        bool hasOwnDC = true;
                        bool unmanaged = false;
                        bool letterbox_brush_is_default = true;
                        optional<basic_brush<_Graphics_surfaces_type>> _Letterbox_brush;
                        optional<basic_brush_props<_Graphics_surfaces_type>> _Letterbox_brush_props;
                        
                        optional<basic_brush<_Graphics_surfaces_type>> _Default_letterbox_brush;
                        
                        basic_display_point<GraphicsMath> display_dimensions;
                        ::std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> display_surface{ nullptr, &cairo_surface_destroy };
                        ::std::unique_ptr<cairo_t, decltype(&cairo_destroy)> display_context{ nullptr, &cairo_destroy };
                        
                        image_surface_data_type back_buffer;
                        
                        bool auto_clear = false;
                        io2d::scaling scl = io2d::scaling::letterbox;
                        io2d::refresh_style rr = io2d::refresh_style::as_fast_as_possible;
                        float refresh_fps = 30.0f;
                        bool redraw_required = false;
                        float elapsed_draw_time = 0.0f;
                    };
                    
                    using _Display_surface_data_type = _Display_surface_win32_data;
                    struct _Output_surface_win32_data {
                        _Display_surface_data_type data;
                        ::std::function<void(basic_output_surface<_Graphics_surfaces_type>&)> draw_callback;
                        ::std::function<void(basic_output_surface<_Graphics_surfaces_type>&)> size_change_callback;
                        ::std::function<basic_bounding_box<GraphicsMath>(const basic_output_surface<_Graphics_surfaces_type>&, bool&)> user_scaling_callback;
                    };
                    struct _Unmanaged_output_surface_win32_data {
                        _Display_surface_data_type data;
                        ::std::function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)> draw_callback;
                        ::std::function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)> size_change_callback;
                        ::std::function<basic_bounding_box<GraphicsMath>(const basic_unmanaged_output_surface<_Graphics_surfaces_type>&, bool&)> user_scaling_callback;
                    };
 */
                    struct _OutputSurfaceCocoa;
                    using output_surface_data_type = _OutputSurfaceCocoa*;
                    //using output_surface_data_type = _Output_surface_win32_data;
/*                    using unmanaged_output_surface_data_type = _Unmanaged_output_surface_win32_data;
#elif defined(USE_XLIB)
                    struct _Display_surface_xlib_data {
                        unique_ptr<Display, decltype(&XCloseDisplay)> display{ nullptr, &XCloseDisplay };
                        Atom wmDeleteWndw;
                        Window wndw = None;
                        Visual* visual; // Note: This pointer is not a dynamic allocation and thus does not need to be managed.
                        bool unmanaged = false;
                        bool letterbox_brush_is_default = true;
                        optional<basic_brush<_Graphics_surfaces_type>> _Letterbox_brush;
                        optional<basic_brush_props<_Graphics_surfaces_type>> _Letterbox_brush_props;
                        
                        optional<basic_brush<_Graphics_surfaces_type>> _Default_letterbox_brush;
                        
                        basic_display_point<GraphicsMath> display_dimensions;
                        ::std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> display_surface{ nullptr, &cairo_surface_destroy };
                        ::std::unique_ptr<cairo_t, decltype(&cairo_destroy)> display_context{ nullptr, &cairo_destroy };
                        
                        image_surface_data_type back_buffer;
                        
                        bool auto_clear = false;
                        io2d::scaling scl = io2d::scaling::letterbox;
                        io2d::refresh_style rr = io2d::refresh_style::as_fast_as_possible;
                        float refresh_fps = 30.0f;
                        bool redraw_required = false;
                        float elapsed_draw_time = 0.0f;
                        bool can_draw = false;
                    };
                    
                    using _Display_surface_data_type = _Display_surface_xlib_data;
                    struct _Output_surface_xlib_data {
                        _Display_surface_data_type data;
                        ::std::function<void(basic_output_surface<_Graphics_surfaces_type>&)> draw_callback;
                        ::std::function<void(basic_output_surface<_Graphics_surfaces_type>&)> size_change_callback;
                        ::std::function<basic_bounding_box<GraphicsMath>(const basic_output_surface<_Graphics_surfaces_type>&, bool&)> user_scaling_callback;
                    };
                    struct _Unmanaged_output_surface_xlib_data {
                        _Display_surface_data_type data;
                        ::std::function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)> draw_callback;
                        ::std::function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)> size_change_callback;
                        ::std::function<basic_bounding_box<GraphicsMath>(const basic_unmanaged_output_surface<_Graphics_surfaces_type>&, bool&)> user_scaling_callback;
                    };
                    using output_surface_data_type = _Output_surface_xlib_data;
                    using unmanaged_output_surface_data_type = _Unmanaged_output_surface_xlib_data;
                    
#endif

                    template <class OutputDataType, class OutputSurfaceType>
                    static void _Render_to_native_surface(OutputDataType& osd, OutputSurfaceType& sfc);
                    
                    static basic_display_point<GraphicsMath> max_display_dimensions() noexcept;
                    // unmanaged_output_surface functions
                    
                    static unmanaged_output_surface_data_type create_unmanaged_output_surface();
#if defined(_WIN32) || defined(_WIN64)
                    static unmanaged_output_surface_data_type create_unmanaged_output_surface(HINSTANCE hInstance, HWND hwnd, HDC hdc, int preferredWidth, int preferredHeight, io2d::format preferredFormat, io2d::scaling scl);
#elif defined(USE_XLIB)
                    static unmanaged_output_surface_data_type create_unmanaged_output_surface(Display* display, Window wndw, int preferredWidth, int preferredHeight, io2d::format preferredFormat, io2d::scaling scl);
#endif
                    static unmanaged_output_surface_data_type move_unmanaged_output_surface(unmanaged_output_surface_data_type&& data) noexcept;
                    static void destroy(unmanaged_output_surface_data_type& data) noexcept;
                    
                    static bool has_draw_callback(const unmanaged_output_surface_data_type& data) noexcept;
                    static void invoke_draw_callback(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc);
                    static void draw_to_output(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc);
                    static bool has_size_change_callback(const unmanaged_output_surface_data_type& data) noexcept;
                    static void invoke_size_change_callback(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc);
                    static bool has_user_scaling_callback(const unmanaged_output_surface_data_type& data) noexcept;
                    static basic_bounding_box<GraphicsMath> invoke_user_scaling_callback(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc, bool& useLetterboxBrush);
                    static void display_dimensions(unmanaged_output_surface_data_type& data, const basic_display_point<GraphicsMath>& val);
                    
                    static void flush(unmanaged_output_surface_data_type& data);
                    static void flush(unmanaged_output_surface_data_type& data, error_code& ec) noexcept;
                    static void mark_dirty(unmanaged_output_surface_data_type& data);
                    static void mark_dirty(unmanaged_output_surface_data_type& data, error_code& ec) noexcept;
                    static void mark_dirty(unmanaged_output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents);
                    static void mark_dirty(unmanaged_output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents, error_code& ec) noexcept;
                    static void clear(unmanaged_output_surface_data_type& data);
                    static void paint(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
                    static void stroke(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_stroke_props<_Graphics_surfaces_type>& sp, const basic_dashes<_Graphics_surfaces_type>& d, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
                    static void fill(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& pg, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
                    static void mask(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush<_Graphics_surfaces_type>& mb, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_mask_props<_Graphics_surfaces_type>& mp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
                    static void draw_callback(unmanaged_output_surface_data_type& data, function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)>);
                    static void size_change_callback(unmanaged_output_surface_data_type& data, function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)>);
                    static void user_scaling_callback(unmanaged_output_surface_data_type& data, function<basic_bounding_box<GraphicsMath>(const basic_unmanaged_output_surface<_Graphics_surfaces_type>&, bool&)>);
                    static void dimensions(unmanaged_output_surface_data_type& data, const basic_display_point<GraphicsMath>& val);
                    static void scaling(unmanaged_output_surface_data_type& data, io2d::scaling val);
                    static void letterbox_brush(unmanaged_output_surface_data_type& data, const optional<basic_brush<_Graphics_surfaces_type>>& val, const optional<basic_brush_props<_Graphics_surfaces_type>>& bp) noexcept;
                    static void letterbox_brush_props(unmanaged_output_surface_data_type& data, const basic_brush_props<_Graphics_surfaces_type>& val);
                    static void auto_clear(unmanaged_output_surface_data_type& data, bool val);
                    static void redraw_required(unmanaged_output_surface_data_type& data, bool val);
                    
                    static io2d::format format(const unmanaged_output_surface_data_type& data) noexcept;
                    static basic_display_point<GraphicsMath> dimensions(const unmanaged_output_surface_data_type& data) noexcept;
                    static basic_display_point<GraphicsMath> display_dimensions(const unmanaged_output_surface_data_type& data) noexcept;
                    static io2d::scaling scaling(unmanaged_output_surface_data_type& data) noexcept;
                    static optional<basic_brush<_Graphics_surfaces_type>> letterbox_brush(const unmanaged_output_surface_data_type& data) noexcept;
                    static basic_brush_props<_Graphics_surfaces_type> letterbox_brush_props(const unmanaged_output_surface_data_type& data) noexcept;
                    static bool auto_clear(const unmanaged_output_surface_data_type& data) noexcept;
                    static bool redraw_required(const unmanaged_output_surface_data_type& data) noexcept;
 
 */
 
                    // output_surface functions
                    

                    static output_surface_data_type create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, io2d::scaling scl, io2d::refresh_style rr, float fps);
                    static output_surface_data_type create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, error_code& ec, io2d::scaling scl, io2d::refresh_style rr, float fps) noexcept;
                    static output_surface_data_type create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, io2d::scaling scl, io2d::refresh_style rr, float fps);
                    static output_surface_data_type create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, error_code& ec, io2d::scaling scl, io2d::refresh_style rr, float fps) noexcept;
                    
                    static output_surface_data_type move_output_surface(output_surface_data_type&& data) noexcept;
                    static void destroy(output_surface_data_type& data) noexcept;

                    static int begin_show(output_surface_data_type& data, basic_output_surface<_GS>* instance, basic_output_surface<_GS>& sfc);
//                    static void end_show(output_surface_data_type& data);
//                    static void refresh_style(output_surface_data_type& data, io2d::refresh_style val);
//                    static void desired_frame_rate(output_surface_data_type& data, float val);
//                    static void display_dimensions(output_surface_data_type& data, const basic_display_point<GraphicsMath>& val);
//                    static io2d::refresh_style refresh_style(const output_surface_data_type& data) noexcept;
//                    static float desired_frame_rate(const output_surface_data_type& data) noexcept;
//
//                    // rendering functions
//                    static void flush(output_surface_data_type& data);
//                    static void flush(output_surface_data_type& data, error_code& ec) noexcept;
//                    static void mark_dirty(output_surface_data_type& data);
//                    static void mark_dirty(output_surface_data_type& data, error_code& ec) noexcept;
//                    static void mark_dirty(output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents);
//                    static void mark_dirty(output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents, error_code& ec) noexcept;
                    static void clear(output_surface_data_type& data);
                    static void paint(output_surface_data_type& data, const basic_brush<_GS>& b, const basic_brush_props<_GS>& bp, const basic_render_props<_GS>& rp, const basic_clip_props<_GS>& cl);
                    static void stroke(output_surface_data_type& data, const basic_brush<_GS>& b, const basic_interpreted_path<_GS>& ip, const basic_brush_props<_GS>& bp, const basic_stroke_props<_GS>& sp, const basic_dashes<_GS>& d, const basic_render_props<_GS>& rp, const basic_clip_props<_GS>& cl);
                    static void fill(output_surface_data_type& data, const basic_brush<_GS>& b, const basic_interpreted_path<_GS>& ip, const basic_brush_props<_GS>& bp, const basic_render_props<_GS>& rp, const basic_clip_props<_GS>& cl);
//                    static void mask(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush<_Graphics_surfaces_type>& mb, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_mask_props<_Graphics_surfaces_type>& mp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
//
//                    // display_surface common functions
                    static void draw_callback(output_surface_data_type& data, function<void(basic_output_surface<_GS>&)>);
                    static void size_change_callback(output_surface_data_type& data, function<void(basic_output_surface<_GS>&)>);
//                    static void user_scaling_callback(output_surface_data_type& data, function<basic_bounding_box<GraphicsMath>(const basic_output_surface<_Graphics_surfaces_type>&, bool&)>);
//                    static void dimensions(output_surface_data_type& data, const basic_display_point<GraphicsMath>& val);
//                    static void scaling(output_surface_data_type& data, io2d::scaling val);
//                    static void letterbox_brush(output_surface_data_type& data, const optional<basic_brush<_Graphics_surfaces_type>>& val, const optional<basic_brush_props<_Graphics_surfaces_type>>& bp) noexcept;
//                    static void letterbox_brush_props(output_surface_data_type& data, const basic_brush_props<_Graphics_surfaces_type>& val);
                    static void auto_clear(output_surface_data_type& data, bool val) noexcept;
//                    static void redraw_required(output_surface_data_type& data, bool val);
//
//                    static io2d::format format(const output_surface_data_type& data) noexcept;
                    static basic_display_point<GraphicsMath> dimensions(const output_surface_data_type& data) noexcept;
//                    static basic_display_point<GraphicsMath> display_dimensions(const output_surface_data_type& data) noexcept;
//                    static io2d::scaling scaling(output_surface_data_type& data) noexcept;
//                    static optional<basic_brush<_Graphics_surfaces_type>> letterbox_brush(const output_surface_data_type& data) noexcept;
//                    static basic_brush_props<_Graphics_surfaces_type> letterbox_brush_props(const output_surface_data_type& data) noexcept;
                    static bool auto_clear(const output_surface_data_type& data) noexcept;
//                    static bool redraw_required(const output_surface_data_type& data) noexcept;
//
                };

            };
        }
    }
}

#include "io2d_cg_surfaces.h"
#include "io2d_cg_brushes.h"
#include "io2d_cg_paths.h"
#include "io2d_cg_paths_figures.h"
#include "io2d_cg_surface_state_props.h"
#include "io2d_cg_output_surfaces.h"

#endif
