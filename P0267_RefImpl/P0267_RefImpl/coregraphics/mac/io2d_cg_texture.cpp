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
static void DrawReflectedTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const basic_brush_props<_GS> &bp);
    
void _DrawTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const basic_brush_props<_GS> &bp)
{
    switch( bp.wrap_mode() ) {
        case wrap_mode::none:
            DrawSingleTexture(ctx, surface, bp);
            break;
        case wrap_mode::repeat:
            DrawRepeatedTexture(ctx, surface, bp);
            break;
        case wrap_mode::reflect:
            DrawReflectedTexture(ctx, surface, bp);
            break;
        default:
            break;
    }
}

static void DrawSingleTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const basic_brush_props<_GS> &bp)
{
    CGContextConcatCTM(ctx, _ToCG(bp.brush_matrix().inverse()) );
    CGContextConcatCTM(ctx, CGAffineTransform{ 1., 0., 0., -1., 0., double(surface.height) } );
    CGContextSetInterpolationQuality(ctx, _ToCG(bp.filter()));
    CGContextDrawImage(ctx, CGRectMake(0, 0, surface.width, surface.height), surface.image.get());
}

static void DrawRepeatedPattern(void * info, CGContextRef ctx)
{
    auto &pattern_context = *(const PatternContext*)info;
    auto rc = CGRectMake(0, 0, pattern_context.brush.width, pattern_context.brush.height);
    CGContextDrawImage(ctx, rc, pattern_context.brush.image.get());
}
    
static void DrawRepeatedTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const basic_brush_props<_GS> &bp)
{
    CGContextConcatCTM(ctx, _ToCG(bp.brush_matrix().inverse()) );
    CGContextConcatCTM(ctx, CGAffineTransform{ 1., 0., 0., -1., 0., double(surface.height) } );

    CGPatternCallbacks callbacks = {0, &DrawRepeatedPattern, nullptr};
    PatternContext pattern_context{surface, bp};
    
    auto pattern = CGPatternCreate((void*)&pattern_context,
                                   CGRectMake(0, 0, surface.width, surface.height),
                                   CGContextGetCTM(ctx),
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
    
static void DrawReflectedPattern(void * info, CGContextRef ctx)
{
    auto &pattern_context = *(const PatternContext*)info;
    auto img = pattern_context.brush.image.get();
    auto width = double(pattern_context.brush.width);
    auto height = double(pattern_context.brush.height);
    auto rc = CGRectMake(0, 0, width, height);
    
    CGContextConcatCTM(ctx, { 1., 0., 0., -1., 0., height});
    CGContextDrawImage(ctx, rc, img);

    CGContextConcatCTM(ctx, {1., 0., 0., -1., 0., 0.});
    CGContextDrawImage(ctx, rc, img);
    
    CGContextConcatCTM(ctx, {-1., 0., 0., 1., 2.*width, 0.});
    CGContextDrawImage(ctx, rc, img);
    
    CGContextConcatCTM(ctx, {1., 0., 0., -1., 0., 0.});
    CGContextDrawImage(ctx, rc, img);
}
    
static void DrawReflectedTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const basic_brush_props<_GS> &bp)
{
    CGContextConcatCTM(ctx, _ToCG(bp.brush_matrix().inverse()));
    
    CGPatternCallbacks callbacks = {0, &DrawReflectedPattern, nullptr};
    PatternContext pattern_context{surface, bp};
    
    auto pattern = CGPatternCreate((void*)&pattern_context,
                                   CGRectMake(0, 0, surface.width * 2., surface.height * 2.),
                                   CGContextGetCTM(ctx),
                                   surface.width * 2.,
                                   surface.height * 2.,
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
