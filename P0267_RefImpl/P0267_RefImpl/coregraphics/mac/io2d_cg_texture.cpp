#include "io2d_cg_texture.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

namespace {
        
struct PatternContext {
    const _GS::brushes::_Surface &brush;
    const basic_brush_props<_GS> &props;
    PatternContext(const _GS::brushes::_Surface &b, const basic_brush_props<_GS> &bp):
    brush{b}, props{bp}
    {}
};
        
}
    
static void DrawSingleTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const basic_brush_props<_GS> &bp);
static void DrawRepeatedTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const basic_brush_props<_GS> &bp);
    
void _DrawTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const basic_brush_props<_GS> &bp)
{
    switch( bp.wrap_mode() ) {
        case wrap_mode::none: DrawSingleTexture(ctx, surface, bp); break;
        case wrap_mode::repeat: DrawRepeatedTexture(ctx, surface, bp); break;
        default: break;
    }
}

static void DrawSingleTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const basic_brush_props<_GS> &bp)
{
    CGContextConcatCTM(ctx, _ToCG(bp.brush_matrix().inverse()) );
    CGContextConcatCTM(ctx, CGAffineTransform{ 1., 0., 0., -1., 0., double(surface.height) } );
    CGContextSetInterpolationQuality(ctx, _ToCG(bp.filter()));
    CGContextDrawImage(ctx, CGRectMake(0, 0, surface.width, surface.height), surface.image.get());
}

static void RepeatedPatternDraw(void * info, CGContextRef ctx)
{
    auto &pattern_context = *(const PatternContext*)info;
    auto rc = CGRectMake(0, 0, pattern_context.brush.width, pattern_context.brush.height);
    CGContextDrawImage(ctx, rc, pattern_context.brush.image.get());
}
    
static void DrawRepeatedTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const basic_brush_props<_GS> &bp)
{
    CGPatternCallbacks callbacks = {0, &RepeatedPatternDraw, nullptr};
    PatternContext pattern_context{surface, bp};
    
    auto pattern = CGPatternCreate((void*)&pattern_context,
                                   CGRectMake(0, 0, surface.width, surface.height),
                                   _ToCG(bp.brush_matrix().inverse()),
                                   surface.width,
                                   surface.height,
                                   kCGPatternTilingConstantSpacing,
                                   true,
                                   &callbacks);
    _AutoRelease release_pattern{pattern};
    
    constexpr double components[4] = {1., 1., 1., 1.};
    CGContextSetFillColorSpace(ctx, _PatternColorSpace());
    CGContextSetFillPattern(ctx, pattern, components);
    CGContextSetInterpolationQuality(ctx, _ToCG(bp.filter()));
    CGContextFillRect(ctx, CGContextGetClipBoundingBox(ctx));
}
        
} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d
