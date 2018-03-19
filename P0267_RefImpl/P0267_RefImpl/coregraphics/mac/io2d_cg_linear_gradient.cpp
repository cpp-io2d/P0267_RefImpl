#include "io2d_cg_linear_gradient.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

static pair<float, float> ExpandParameters(const point_2d p1, const point_2d p2, const bounding_box bb)
{
    const auto unit_dot_raw = (p1.x()-p2.x())*(p1.x()-p2.x()) + (p1.y()-p2.y())*(p1.y()-p2.y());
    const auto unit_dot = max(unit_dot_raw, 1.f); // guard against degenerate cases
    const auto pdx = (p2.x() - p1.x()) / unit_dot;
    const auto pdy = (p2.y() - p1.y()) / unit_dot;
    const auto t0 = (bb.x() - p1.x()) * pdx + (bb.y() - p1.y()) * pdy;
    const auto tdx = bb.width() * pdx;
    const auto tdy = bb.height() * pdy;
    auto r0 = t0;
    auto r1 = t0;
    (tdx < 0. ? r0 : r1) += tdx;
    (tdy < 0. ? r0 : r1) += tdy;
    return make_pair(r0, r1);
}
 
static inline point_2d InterpolatePoint(point_2d p1, point_2d p2, const float t)
{
    return { p1.x() + t*(p2.x() - p1.x()), p1.y() + t * (p2.y() - p1.y()) };
}

static inline void InterpolateStopsColor(const _GS::brushes::_Linear &gradient, const float t, double* out)
{
    auto &stops = gradient.stops;
    auto pred = [](const gradient_stop &g, float v){ return g.offset() < v; };
    auto pos = lower_bound(begin(stops), end(stops), t, pred);
    if( pos == begin(stops) ) {
        out[0] = pos->color().r();
        out[1] = pos->color().g();
        out[2] = pos->color().b();
        out[3] = pos->color().a();
    }
    else if( pos == end(stops) ) {
        --pos;
        out[0] = pos->color().r();
        out[1] = pos->color().g();
        out[2] = pos->color().b();
        out[3] = pos->color().a();
    }
    else {
        const auto prev = pos - 1;
        const auto dist = pos->offset() - prev->offset();
        const auto c2 = (t - prev->offset()) / dist;
        const auto c1 = 1.f - c2;
        out[0] = prev->color().r() * c1 + pos->color().r() * c2;
        out[1] = prev->color().g() * c1 + pos->color().g() * c2;
        out[2] = prev->color().b() * c1 + pos->color().b() * c2;
        out[3] = prev->color().a() * c1 + pos->color().a() * c2;
    }
}

static void ShadingWithWrappingNone(void* info, const double* in, double* out)
{
    const auto param_in = *in;
    if( param_in < 0. || param_in > 1. ) {
        out[0] = 0.;
        out[1] = 0.;
        out[2] = 0.;
        out[3] = 0.;
    }
    else {
        auto &gradient = *static_cast<const _GS::brushes::_Linear*>(info);
        InterpolateStopsColor(gradient, param_in, out);
    }
}

static void ShadingWithWrappingRepeat(void* info, const double* in, double* out)
{
    const auto param_in = *in;
    const auto param_effective = param_in - floor(param_in);
    auto &gradient = *static_cast<const _GS::brushes::_Linear*>(info);
    InterpolateStopsColor(gradient, param_effective, out);
}

static void ShadingWithWrappingReflect(void* info, const double* in, double* out)
{
    const auto param_in = *in;
    auto param_effective = fmod(abs(param_in), 2.0);
    if( param_effective > 1.0 )
        param_effective = 2.0 - param_effective;
    auto &gradient = *static_cast<const _GS::brushes::_Linear*>(info);
    InterpolateStopsColor(gradient, param_effective, out);
}
    
static void ShadingWithWrappingPad(void* info, const double* in, double* out)
{
    auto &gradient = *static_cast<const _GS::brushes::_Linear*>(info);
    const auto param_in = *in;
    if( param_in < 0. ) {
        out[0] = gradient.stops.front().color().r();
        out[1] = gradient.stops.front().color().g();
        out[2] = gradient.stops.front().color().b();
        out[3] = gradient.stops.front().color().a();
    }
    else if(param_in > 1. ) {
        out[0] = gradient.stops.back().color().r();
        out[1] = gradient.stops.back().color().g();
        out[2] = gradient.stops.back().color().b();
        out[3] = gradient.stops.back().color().a();
    }
    else {
        InterpolateStopsColor(gradient, param_in, out);
    }
}

static auto FunctionByMode( wrap_mode wm )
{
    switch( wm ) {
        case wrap_mode::none:       return ShadingWithWrappingNone;
        case wrap_mode::pad:        return ShadingWithWrappingPad;
        case wrap_mode::repeat:     return ShadingWithWrappingRepeat;
        case wrap_mode::reflect:    return ShadingWithWrappingReflect;
        default:                    assert(0);
    }
}

void _DrawLinearGradient(CGContextRef ctx, const _GS::brushes::_Linear &gradient, const basic_brush_props<_GS> &bp)
{
    if( gradient.stops.empty() )
        return;
    
    static const auto rgb = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB); // need some central place to manage color spaces
    
    const auto gradient_start = gradient.start * bp.brush_matrix().inverse();
    const auto gradient_end = gradient.end * bp.brush_matrix().inverse();
    const auto bounding_box = _FromCG(CGContextGetClipBoundingBox(ctx));
    const auto [t0, t1] = ExpandParameters(gradient_start, gradient_end, bounding_box);
    const auto p0 = InterpolatePoint(gradient_start, gradient_end, t0);
    const auto p1 = InterpolatePoint(gradient_start, gradient_end, t1);
    
    CGFunctionCallbacks callbacks;
    callbacks.version = 0;
    callbacks.evaluate = FunctionByMode(bp.wrap_mode());
    callbacks.releaseInfo = nullptr;
    
    size_t domainDimension = 1;
    double domain[2] = {t0, t1};
    size_t rangeDimension = 4;
    double range[8] = {0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0};
    auto shading_function = CGFunctionCreate((void*)(&gradient), domainDimension, domain, rangeDimension, range, &callbacks);
    _AutoRelease release_shading_funciton{shading_function};
    
    auto shading = CGShadingCreateAxial(rgb, _ToCG(p0), _ToCG(p1), shading_function, false, false);
    _AutoRelease release_shading{shading};
    
    CGContextDrawShading(ctx, shading);
}

} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d
