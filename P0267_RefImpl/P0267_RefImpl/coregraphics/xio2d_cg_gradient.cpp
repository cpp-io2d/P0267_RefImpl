#include "xio2d_cg_gradient.h"
#include "xio2d_cg_colors.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

// see Cairo:cairo-pattern.c for the math model explanation

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

static inline bool Inside( const point_2d &p, const bounding_box &bb )
{
    return p.x() >= bb.top_left().x() &&
           p.x() <= bb.bottom_right().x() &&
           p.y() >= bb.top_left().y() &&
           p.y() <= bb.bottom_right().y();
}

static pair<float, float> ExpandParameters(const circle p1, const circle p2, const bounding_box bb)
{
    const auto dx = p2.center().x() - p1.center().x();
    const auto dy = p2.center().y() - p1.center().y();
    const auto dr = p2.radius() - p1.radius();
    
    const auto bb_tl = bb.top_left();
    const auto bb_br = bb.bottom_right();
    
    float r0 = NAN, r1 = NAN;
    auto expand = [&r0, &r1](float t) {
        if( isnan(r0) )     r0 = r1 = t;
        else if( t < r0 )   r0 = t;
        else if( t > r1 )   r1 = t;
    };
    auto touch_edge_ext = [&](float num, float den, float base, float delta, float min, float max) {
        if( abs(den) >= FLT_EPSILON ) {
            const auto edge_t = num / den;
            const auto edge_v = base + delta * edge_t;
            const auto edge_r = p1.radius() + dr * edge_t;
            if( edge_r >= FLT_EPSILON && edge_v >= min && edge_v <= max )
                expand(edge_t);
        }
    };
    
    if( abs(dr) >= FLT_EPSILON ) { // cone
        const auto focus_t = -1.f * p1.radius() / dr;
        const auto focus_pt = point_2d{ p1.center().x() + dx * focus_t, p1.center().y() + dy * focus_t };
        if( Inside(focus_pt, bb) )
            expand(focus_t);
    }
    
    touch_edge_ext( bb_tl.x() - p1.center().x() - p1.radius(), dx + dr, p1.center().y(), dy, bb_tl.y(), bb_br.y() ); // left
    touch_edge_ext( bb_br.x() - p1.center().x() + p1.radius(), dx - dr, p1.center().y(), dy, bb_tl.y(), bb_br.y() ); // right
    touch_edge_ext( bb_tl.y() - p1.center().y() - p1.radius(), dy + dr, p1.center().x(), dx, bb_tl.x(), bb_br.x() ); // top
    touch_edge_ext( bb_br.y() - p1.center().y() + p1.radius(), dy - dr, p1.center().x(), dx, bb_tl.x(), bb_br.x() ); // bottom

    const auto a = dx*dx + dy*dy - dr*dr;
    if( abs(a) >= FLT_EPSILON*FLT_EPSILON ) { // regular case
        auto touch_corner = [&](float x, float y) {
            x -= p1.center().x();
            y -= p1.center().y();
            const auto b = x*dx + y*dy + p1.radius()*dr;
            const auto c = x*x + y*y - p1.radius()*p1.radius();
            const auto d = b*b - a*c;
            if( d >= 0.f ) {
                const auto corner1_t = (b + sqrt(d)) / a;
                const auto corner1_r = p1.radius() + dr * corner1_t;
                if( corner1_r >= FLT_EPSILON )
                    expand(corner1_t);
                
                const auto corner2_t = (b - sqrt(d)) / a;
                const auto corner2_r = p1.radius() + dr * corner2_t;
                if( corner2_r >= FLT_EPSILON )
                    expand(corner2_t);
            }
        };
        touch_corner( bb_tl.x(), bb_tl.y() );
        touch_corner( bb_br.x(), bb_tl.y() );
        touch_corner( bb_tl.x(), bb_br.y() );
        touch_corner( bb_br.x(), bb_br.y() );
    }
    
    return make_pair(r0, r1);
}
    
static inline point_2d Interpolate(point_2d p1, point_2d p2, const float t)
{
    return { p1.x() + t*(p2.x() - p1.x()), p1.y() + t * (p2.y() - p1.y()) };
}

static inline circle Interpolate(circle c1, circle c2, const float t)
{
    return { Interpolate(c1.center(), c2.center(), t), c1.radius() + t * (c2.radius() - c1.radius()) };
}
    
static inline void InterpolateStopsColor(const vector<gradient_stop> &stops, const float t, double* out)
{
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
        auto &stops = *static_cast<const vector<gradient_stop>*>(info);
        InterpolateStopsColor(stops, param_in, out);
    }
}

static void ShadingWithWrappingRepeat(void* info, const double* in, double* out)
{
    const auto param_in = *in;
    const auto param_effective = param_in - floor(param_in);
    auto &stops = *static_cast<const vector<gradient_stop>*>(info);
    InterpolateStopsColor(stops, param_effective, out);
}

static void ShadingWithWrappingReflect(void* info, const double* in, double* out)
{
    const auto param_in = *in;
    auto param_effective = fmod(abs(param_in), 2.0);
    if( param_effective > 1.0 )
        param_effective = 2.0 - param_effective;
    auto &stops = *static_cast<const vector<gradient_stop>*>(info);
    InterpolateStopsColor(stops, param_effective, out);
}

static void ShadingWithWrappingPad(void* info, const double* in, double* out)
{
    auto &stops = *static_cast<const vector<gradient_stop>*>(info);
    const auto param_in = *in;
    if( param_in < 0. ) {
        out[0] = stops.front().color().r();
        out[1] = stops.front().color().g();
        out[2] = stops.front().color().b();
        out[3] = stops.front().color().a();
    }
    else if(param_in > 1. ) {
        out[0] = stops.back().color().r();
        out[1] = stops.back().color().g();
        out[2] = stops.back().color().b();
        out[3] = stops.back().color().a();
    }
    else {
        InterpolateStopsColor(stops, param_in, out);
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

static auto CallbacksByMode( wrap_mode wm )
{
    CGFunctionCallbacks callbacks;
    callbacks.version = 0;
    callbacks.evaluate = FunctionByMode(wm);
    callbacks.releaseInfo = nullptr;
    return callbacks;
}

static inline bounding_box ClippedBoundingBox(CGContextRef ctx)
{
    return _FromCG(CGContextGetClipBoundingBox(ctx));
}

static inline bool IsEmpty( const bounding_box &bb )
{
    return bb.width() < FLT_MIN || bb.height() < FLT_MIN;
}

void _DrawLinearGradient(CGContextRef ctx, const _GS::brushes::_Linear &gradient, wrap_mode wm, const matrix_2d &m)
{
    if( gradient.stops.empty() )
        return;

    const auto bounding_box = ClippedBoundingBox(ctx);
    if( IsEmpty(bounding_box) )
        return;

    const auto gradient_start = gradient.start * m.inverse();
    const auto gradient_end = gradient.end * m.inverse();
    const auto [t0, t1] = ExpandParameters(gradient_start, gradient_end, bounding_box);
    const auto p0 = Interpolate(gradient_start, gradient_end, t0);
    const auto p1 = Interpolate(gradient_start, gradient_end, t1);
    
    auto callbacks = CallbacksByMode(wm);
    size_t domain_dimension = 1;
    double domain[2] = {t0, t1};
    size_t range_dimension = 4;
    double range[8] = {0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0};
    auto shading_function = CGFunctionCreate((void*)(&gradient.stops), domain_dimension, domain, range_dimension, range, &callbacks);
    _AutoRelease release_shading_function{shading_function};
    
    auto shading = CGShadingCreateAxial(_RGBColorSpace(), _ToCG(p0), _ToCG(p1), shading_function, false, false);
    _AutoRelease release_shading{shading};
    
    CGContextDrawShading(ctx, shading);
}

void _DrawRadialGradient(CGContextRef ctx, const _GS::brushes::_Radial &gradient, wrap_mode wm, const matrix_2d &m)
{
    if( gradient.stops.empty() )
        return;

    const auto bounding_box = ClippedBoundingBox(ctx);
    if( IsEmpty(bounding_box) )
        return;
    
    const auto gradient_start = circle{ gradient.start.center() * m.inverse(), gradient.start.radius() };
    const auto gradient_end = circle{ gradient.end.center() * m.inverse(), gradient.end.radius() };
    const auto [t0, t1] = ExpandParameters(gradient_start, gradient_end, bounding_box);
    if( isnan(t0) || isnan(t1) )
        return;
    const auto c0 = Interpolate(gradient_start, gradient_end, t0);
    const auto c1 = Interpolate(gradient_start, gradient_end, t1);
    
    auto callbacks = CallbacksByMode(wm);
    size_t domain_dimension = 1;
    double domain[2] = {t0, t1};
    size_t range_dimension = 4;
    double range[8] = {0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0};
    auto shading_function = CGFunctionCreate((void*)(&gradient.stops), domain_dimension, domain, range_dimension, range, &callbacks);
    _AutoRelease release_shading_function{shading_function};

    auto shading = CGShadingCreateRadial(_RGBColorSpace(), _ToCG(c0.center()), c0.radius(), _ToCG(c1.center()), c1.radius(), shading_function, false, false);
    _AutoRelease release_shading{shading};
    
    CGContextDrawShading(ctx, shading);
}
    
} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d
