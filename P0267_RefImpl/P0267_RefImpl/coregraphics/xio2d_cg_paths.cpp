#include "xio2d_cg_paths.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {
            
[[maybe_unused]] static auto DropTranslation(basic_matrix_2d<GraphicsMath> m) noexcept {
    m.m20(0.0f);
    m.m21(0.0f);
    return m;
}
    
static void Add(_PathInterperationContext &ctx, const basic_figure_items<_GS>::abs_new_figure &figure ) {
    ctx.position = figure.at() * ctx.transform;
    ctx.figure_start = ctx.position;
    CGPathMoveToPoint(ctx.path, nullptr, ctx.position.x(), ctx.position.y());
}
    
static void Add(_PathInterperationContext &ctx, const basic_figure_items<_GS>::rel_new_figure &figure ) {
    ctx.position = ctx.position + figure.at() * DropTranslation(ctx.transform);
    ctx.figure_start = ctx.position;
    CGPathMoveToPoint(ctx.path, nullptr, ctx.position.x(), ctx.position.y());
}
    
static void Add(_PathInterperationContext &ctx, const basic_figure_items<_GS>::close_figure &figure ) {
    ctx.position = ctx.figure_start;
    CGPathCloseSubpath(ctx.path);
}
    
static void Add(_PathInterperationContext &ctx, const basic_figure_items<_GS>::abs_matrix &figure ) {
    ctx.transforms_stack.push( ctx.transform );
    ctx.transform = figure.matrix();
}
    
static void Add(_PathInterperationContext &ctx, const basic_figure_items<_GS>::rel_matrix &figure ) {
    ctx.transforms_stack.push( ctx.transform );
    ctx.transform = figure.matrix() * ctx.transform;
}
    
static void Add(_PathInterperationContext &ctx, const basic_figure_items<_GS>::revert_matrix &figure ) {
    if( ctx.transforms_stack.empty() ) {
        ctx.transform = basic_matrix_2d<GraphicsMath>{};
    }
    else {
        ctx.transform = ctx.transforms_stack.top();
        ctx.transforms_stack.pop();
    }
}
    
static void Add(_PathInterperationContext &ctx, const basic_figure_items<_GS>::abs_line &figure ) {
    ctx.position = figure.to() * ctx.transform;
    CGPathAddLineToPoint(ctx.path, nullptr, ctx.position.x(), ctx.position.y());
}
    
inline void Add(_PathInterperationContext &ctx, const basic_figure_items<_GS>::rel_line &figure ) {
    ctx.position = ctx.position + figure.to() * DropTranslation(ctx.transform);
    CGPathAddLineToPoint(ctx.path, nullptr, ctx.position.x(), ctx.position.y());
}
    
inline void Add(_PathInterperationContext &ctx, const basic_figure_items<_GS>::arc &figure ) {
    // this implementation was shamelessly copied from RefImpl
    const float rot = figure.rotation();
    const float oneThousandthOfADegreeInRads = pi<float> / 180'000.0F;
    if (abs(rot) < oneThousandthOfADegreeInRads) {
        // Return if the rotation is less than one thousandth of one degree; it's a degenerate path segment.
        return;
    }
    const auto clockwise = (rot < 0.0F) ? true : false;
    const auto rad = figure.radius();
    auto startAng = figure.start_angle();
    const auto m = basic_matrix_2d<GraphicsMath>::create_scale(rad);
    
    auto centerOffset = (point_for_angle<GraphicsMath>(two_pi<float> -startAng) * rad);
    centerOffset.y(-centerOffset.y());
    auto ctr = ctx.position - centerOffset;
    
    basic_point_2d<GraphicsMath> pt0, pt1, pt2, pt3;
    int bezCount = 1;
    float theta = rot;
    
    while (abs(theta) > half_pi<float>) {
        theta /= 2.0F;
        bezCount += bezCount;
    }
    
    float phi = (theta / 2.0F);
    const auto cosPhi = cos(-phi);
    const auto sinPhi = sin(-phi);
    
    pt0.x(cosPhi);
    pt0.y(-sinPhi);
    pt3.x(pt0.x());
    pt3.y(-pt0.y());
    pt1.x((4.0F - cosPhi) / 3.0F);
    pt1.y(-(((1.0F - cosPhi) * (3.0F - cosPhi)) / (3.0F * sinPhi)));
    pt2.x(pt1.x());
    pt2.y(-pt1.y());
    auto rotCntrCwFn = [](const basic_point_2d<GraphicsMath>& pt, float a) -> basic_point_2d<GraphicsMath> {
        auto result = basic_point_2d<GraphicsMath>{ pt.x() * cos(a) - pt.y() * sin(a),
            pt.x() * sin(a) + pt.y() * cos(a) };
        result.x(_Round_floating_point_to_zero(result.x()));
        result.y(_Round_floating_point_to_zero(result.y()));
        return result;
    };
    auto rotCwFn = [](const basic_point_2d<GraphicsMath>& pt, float a) -> basic_point_2d<GraphicsMath> {
        auto result = basic_point_2d<GraphicsMath>{ pt.x() * cos(a) - pt.y() * sin(a),
            -(pt.x() * sin(a) + pt.y() * cos(a)) };
        result.x(_Round_floating_point_to_zero(result.x()));
        result.y(_Round_floating_point_to_zero(result.y()));
        return result;
    };
    
    startAng = two_pi<float> -startAng;
    
    if (clockwise) {
        pt0 = rotCwFn(pt0, phi);
        pt1 = rotCwFn(pt1, phi);
        pt2 = rotCwFn(pt2, phi);
        pt3 = rotCwFn(pt3, phi);
        auto shflPt = pt3;
        pt3 = pt0;
        pt0 = shflPt;
        shflPt = pt2;
        pt2 = pt1;
        pt1 = shflPt;
    }
    else {
        pt0 = rotCntrCwFn(pt0, phi);
        pt1 = rotCntrCwFn(pt1, phi);
        pt2 = rotCntrCwFn(pt2, phi);
        pt3 = rotCntrCwFn(pt3, phi);
        pt0.y(-pt0.y());
        pt1.y(-pt1.y());
        pt2.y(-pt2.y());
        pt3.y(-pt3.y());
        auto shflPt = pt3;
        pt3 = pt0;
        pt0 = shflPt;
        shflPt = pt2;
        pt2 = pt1;
        pt1 = shflPt;
    }
    auto currTheta = startAng;
    const auto calcAdjustedCurrPt = ((ctr + (rotCntrCwFn(pt0, currTheta) * m)) * ctx.transform);
    auto adjustVal = calcAdjustedCurrPt - ctx.transform.transform_pt(ctx.position);
    basic_point_2d<GraphicsMath> tempCurrPt;
    for (; bezCount > 0; bezCount--) {
        const auto rapt0 = m.transform_pt(rotCntrCwFn(pt0, currTheta));
        const auto rapt1 = m.transform_pt(rotCntrCwFn(pt1, currTheta));
        const auto rapt2 = m.transform_pt(rotCntrCwFn(pt2, currTheta));
        const auto rapt3 = m.transform_pt(rotCntrCwFn(pt3, currTheta));
        auto cpt0 = ctr + rapt0;
        auto cpt1 = ctr + rapt1;
        auto cpt2 = ctr + rapt2;
        auto cpt3 = ctr + rapt3;
        cpt0 = ctx.transform.transform_pt(cpt0);
        cpt1 = ctx.transform.transform_pt(cpt1);
        cpt2 = ctx.transform.transform_pt(cpt2);
        cpt3 = ctx.transform.transform_pt(cpt3);
        cpt0 -= adjustVal;
        cpt1 -= adjustVal;
        cpt2 -= adjustVal;
        cpt3 -= adjustVal;
        
        CGPathMoveToPoint(ctx.path, nullptr, cpt0.x(), cpt0.y());
        CGPathAddCurveToPoint(ctx.path, nullptr, cpt1.x(), cpt1.y(), cpt2.x(), cpt2.y(), cpt3.x(), cpt3.y());
        ctx.position = ctx.transform.inverse().transform_pt(cpt3);
        
        currTheta -= theta;
    }
}
    
static void Add(_PathInterperationContext &ctx, const basic_figure_items<_GS>::abs_cubic_curve &figure ) {
    auto cpt1 = figure.control_pt1() * ctx.transform;
    auto cpt2 = figure.control_pt2() * ctx.transform;
    auto ept  = figure.end_pt() * ctx.transform;
    CGPathAddCurveToPoint(ctx.path, nullptr, cpt1.x(), cpt1.y(), cpt2.x(), cpt2.y(), ept.x(), ept.y());
    ctx.position = figure.end_pt();
}
    
static void Add(_PathInterperationContext &ctx, const basic_figure_items<_GS>::rel_cubic_curve &figure ) {
    auto mm = DropTranslation(ctx.transform);
    auto cpt1 = ctx.position + figure.control_pt1() * mm;
    auto cpt2 = ctx.position + figure.control_pt1() * mm + figure.control_pt2() * mm;
    auto ept =  ctx.position + figure.control_pt1() * mm + figure.control_pt2() * mm + figure.end_pt() * mm;
    CGPathAddCurveToPoint(ctx.path, nullptr, cpt1.x(), cpt1.y(), cpt2.x(), cpt2.y(), ept.x(), ept.y());
    ctx.position = ctx.position + figure.control_pt1() + figure.control_pt2() + figure.end_pt();
}
    
static void Add(_PathInterperationContext &ctx, const basic_figure_items<_GS>::abs_quadratic_curve &figure ) {
    auto cpt = figure.control_pt() * ctx.transform;
    auto ept = figure.end_pt() * ctx.transform;
    CGPathAddQuadCurveToPoint(ctx.path, nullptr, cpt.x(), cpt.y(), ept.x(), ept.y());
    ctx.position = figure.end_pt();
}
    
static void Add(_PathInterperationContext &ctx, const basic_figure_items<_GS>::rel_quadratic_curve &figure ) {
    auto mm = DropTranslation(ctx.transform);
    auto cpt = ctx.position + figure.control_pt() * mm;
    auto ept =  ctx.position + figure.control_pt() * mm + figure.end_pt() * mm;
    CGPathAddQuadCurveToPoint(ctx.path, nullptr, cpt.x(), cpt.y(), ept.x(), ept.y());
    ctx.position = ept;
}

void _PathInterperationContext::Insert( const basic_figure_items<_GS>::figure_item &figure )
{
    if( path == nullptr )
        path = CGPathCreateMutable();

    visit([&](auto&& arg) { Add(*this, arg); }, figure);
}

} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d
