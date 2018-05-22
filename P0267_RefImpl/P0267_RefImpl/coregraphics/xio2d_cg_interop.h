#ifndef _IO2D_CG_INTEROP_
#define _IO2D_CG_INTEROP_

#include "xio2d_cg_main.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

class _GStateGuard
{
public:
    _GStateGuard( CGContextRef _ctx ) noexcept: ctx(_ctx) { CGContextSaveGState (ctx); }
    ~_GStateGuard() noexcept { CGContextRestoreGState(ctx); }
private:
    _GStateGuard( _GStateGuard& ) = delete;
    const CGContextRef ctx;
};
    
class _AutoRelease
{
public:
    _AutoRelease( CFTypeRef _obj ) noexcept: obj(_obj) {}
    ~_AutoRelease() noexcept { if(obj) CFRelease(obj); }
private:
    _AutoRelease( _AutoRelease& ) = delete;
    const CFTypeRef obj;
};

inline constexpr CGPoint _ToCG( const basic_point_2d<GraphicsMath> &p ) noexcept
{
    return CGPoint{ p.x(), p.y() };
}
    
inline constexpr CGAffineTransform _ToCG( const basic_matrix_2d<GraphicsMath> &m ) noexcept
{
    return CGAffineTransform{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
}

inline constexpr CGLineCap _ToCG(line_cap lc) noexcept
{
    switch (lc) {
        case line_cap::none:    return kCGLineCapButt;
        case line_cap::round:   return kCGLineCapRound;
        case line_cap::square:  return kCGLineCapSquare;
        default:                return kCGLineCapButt;
    }
}

inline constexpr CGLineJoin _ToCG(line_join lj) noexcept
{
    switch (lj) {
        case line_join::miter: return kCGLineJoinMiter;
        case line_join::bevel: return kCGLineJoinBevel;
        case line_join::round: return kCGLineJoinRound;
        default:               return kCGLineJoinMiter;
    }
}

inline constexpr CGBlendMode _ToCG(compositing_op op) noexcept
{
    switch (op) {
        case compositing_op::over:              return kCGBlendModeNormal;
        case compositing_op::clear:             return kCGBlendModeClear;
        case compositing_op::source:            return kCGBlendModeCopy;
        case compositing_op::in:                return kCGBlendModeSourceIn;
        case compositing_op::out:               return kCGBlendModeSourceOut;
        case compositing_op::atop:              return kCGBlendModeSourceAtop;
        case compositing_op::dest_over:         return kCGBlendModeDestinationOver;
        case compositing_op::dest_in:           return kCGBlendModeDestinationIn;
        case compositing_op::dest_out:          return kCGBlendModeDestinationOut;
        case compositing_op::dest_atop:         return kCGBlendModeDestinationAtop;
        case compositing_op::xor_op:            return kCGBlendModeXOR;
        case compositing_op::add:               return kCGBlendModePlusLighter;
        case compositing_op::saturate:          return kCGBlendModePlusLighter; // looks like CoreGraphics doesn't have an exact blend mode for IO2DTS' saturate
        case compositing_op::multiply:          return kCGBlendModeMultiply;
        case compositing_op::screen:            return kCGBlendModeScreen;
        case compositing_op::overlay:           return kCGBlendModeOverlay;
        case compositing_op::darken:            return kCGBlendModeDarken;
        case compositing_op::lighten:           return kCGBlendModeLighten;
        case compositing_op::color_dodge:       return kCGBlendModeColorDodge;
        case compositing_op::color_burn:        return kCGBlendModeColorBurn;
        case compositing_op::hard_light:        return kCGBlendModeHardLight;
        case compositing_op::soft_light:        return kCGBlendModeSoftLight;
        case compositing_op::difference:        return kCGBlendModeDifference;
        case compositing_op::exclusion:         return kCGBlendModeExclusion;
        case compositing_op::hsl_hue:           return kCGBlendModeHue;
        case compositing_op::hsl_saturation:    return kCGBlendModeSaturation;
        case compositing_op::hsl_color:         return kCGBlendModeColor;
        case compositing_op::hsl_luminosity:    return kCGBlendModeLuminosity;
        default:                                return kCGBlendModeNormal;
    }
}

inline constexpr CFStringRef _ToCG(image_file_format iff) noexcept
{
    switch (iff) {
        case image_file_format::jpeg:   return CFSTR("public.jpeg");
        case image_file_format::png:    return CFSTR("public.png");
        case image_file_format::tiff:   return CFSTR("public.tiff");
        default:                        return CFSTR("");
    }
}
    
inline constexpr CGInterpolationQuality _ToCG(filter f) noexcept
{
    switch (f) {
        case filter::fast:      return kCGInterpolationNone;
        case filter::good:      return kCGInterpolationMedium;
        case filter::best:      return kCGInterpolationHigh;
        case filter::nearest:   return kCGInterpolationNone;
        case filter::bilinear:  return kCGInterpolationHigh;
        default:                return kCGInterpolationDefault;
    }
}
    
inline basic_bounding_box<GraphicsMath> _FromCG(const CGRect& rc)
{
    return basic_bounding_box<GraphicsMath>( rc.origin.x, rc.origin.y, rc.size.width, rc.size.height );
}

} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

#endif
