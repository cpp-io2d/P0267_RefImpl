#include "xio2d_cg_texture.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

namespace {
        
struct PatternContext {
    const _GS::brushes::_Surface &brush;
    PatternContext(const _GS::brushes::_Surface &b):brush{b}{}
};

}
    
static void DrawSingleTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, filter fi, const matrix_2d &m);
static void DrawRepeatedTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, filter fi, const matrix_2d &m);
static void DrawReflectedTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, filter fi, const matrix_2d &m);
static void DrawPaddedTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, filter fi, const matrix_2d &m);

void _DrawTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, filter fi, wrap_mode wm, const matrix_2d &m)    
{
    switch( wm ) {
        case wrap_mode::none:
            DrawSingleTexture(ctx, surface, fi, m);
            break;
        case wrap_mode::repeat:
            DrawRepeatedTexture(ctx, surface, fi, m);
            break;
        case wrap_mode::reflect:
            DrawReflectedTexture(ctx, surface, fi, m);
            break;
        case wrap_mode::pad:
            DrawPaddedTexture(ctx, surface, fi, m);
            break;
        default:
            break;
    }
}

static void DrawSingleTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, filter fi, const matrix_2d &m)
{
    {
        _GStateGuard state_guard{ctx};            
        CGContextConcatCTM(ctx, _ToCG(m.inverse()) );
        CGContextConcatCTM(ctx, CGAffineTransform{ 1., 0., 0., -1., 0., double(surface.height) } );
        CGContextSetInterpolationQuality(ctx, _ToCG(fi));
        CGContextDrawImage(ctx, CGRectMake(0, 0, surface.width, surface.height), surface.image.get());
    }    
    _DrawTransparencyOutsideTexture(ctx, surface, m);    
}

static void DrawRepeatedPattern(void * info, CGContextRef ctx)
{
    auto &pattern_context = *(const PatternContext*)info;
    auto rc = CGRectMake(0, 0, pattern_context.brush.width, pattern_context.brush.height);
    CGContextDrawImage(ctx, rc, pattern_context.brush.image.get());
}

static void DrawRepeatedTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, filter fi, const matrix_2d &m)
{
    CGContextConcatCTM(ctx, _ToCG(m.inverse()) );
    CGContextConcatCTM(ctx, CGAffineTransform{ 1., 0., 0., -1., 0., double(surface.height) } );

    CGPatternCallbacks callbacks = {0, &DrawRepeatedPattern, nullptr};
    PatternContext pattern_context{surface};
    
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
    CGContextSetInterpolationQuality(ctx, _ToCG(fi));
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
    
static void DrawReflectedTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, filter fi, const matrix_2d &m)
{
    CGContextConcatCTM(ctx, _ToCG(m.inverse()));
    
    CGPatternCallbacks callbacks = {0, &DrawReflectedPattern, nullptr};
    PatternContext pattern_context{surface};
    
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
    CGContextSetInterpolationQuality(ctx, _ToCG(fi));
    CGContextFillRect(ctx, CGContextGetClipBoundingBox(ctx));
}

static _GS::brushes::_Surface::_Pad BuildPad(CGImageRef image, CGContextRef orig_ctx)
{
    _GS::brushes::_Surface::_Pad pad;
 
    auto image_info = CGBitmapContextGetBitmapInfo(orig_ctx);
    auto image_width = CGBitmapContextGetWidth(orig_ctx);
    auto image_height = CGBitmapContextGetHeight(orig_ctx);
    auto image_rc = CGRectMake(0, 0, image_width, image_height);
    auto image_bpc = CGBitmapContextGetBitsPerComponent(orig_ctx);
    auto image_cs = CGBitmapContextGetColorSpace(orig_ctx);
    
    { // bottom
        auto ctx = CGBitmapContextCreate(nullptr, image_width, 1, image_bpc, 0, image_cs, image_info);
        _AutoRelease release_ctx{ctx};
        CGContextSetInterpolationQuality(ctx, kCGInterpolationNone);
        CGContextDrawImage(ctx, image_rc, image);
        pad.bottom.reset( CGBitmapContextCreateImage(ctx) );
    }
    
    { // top
        auto ctx = CGBitmapContextCreate(nullptr, image_width, 1, image_bpc, 0, image_cs, image_info);
        _AutoRelease release_ctx{ctx};
        CGContextSetInterpolationQuality(ctx, kCGInterpolationNone);
        CGContextConcatCTM(ctx, { 1., 0., 0., 1., 0., -double(image_height-1) } );
        CGContextDrawImage(ctx, image_rc, image);
        pad.top.reset( CGBitmapContextCreateImage(ctx) );
    }
    
    { // right
        auto ctx = CGBitmapContextCreate(nullptr, 1, image_height, image_bpc, 0, image_cs, image_info);
        _AutoRelease release_ctx{ctx};
        CGContextSetInterpolationQuality(ctx, kCGInterpolationNone);
        CGContextConcatCTM(ctx, { 1., 0., 0., 1., -double(image_width-1), 0. } );
        CGContextDrawImage(ctx, image_rc, image);
        pad.right.reset( CGBitmapContextCreateImage(ctx) );
    }
    
    { // left
        auto ctx = CGBitmapContextCreate(nullptr, 1, image_height, image_bpc, 0, image_cs, image_info);
        _AutoRelease release_ctx{ctx};
        CGContextSetInterpolationQuality(ctx, kCGInterpolationNone);
        CGContextDrawImage(ctx, image_rc, image);
        pad.left.reset( CGBitmapContextCreateImage(ctx) );
    }
    
    pad.top_left.reset( _CreateColorFromBitmapLocation(orig_ctx, 0, 0) );
    pad.top_right.reset( _CreateColorFromBitmapLocation(orig_ctx, image_width-1, 0) );
    pad.bottom_left.reset( _CreateColorFromBitmapLocation(orig_ctx, 0, image_height-1) );
    pad.bottom_right.reset( _CreateColorFromBitmapLocation(orig_ctx, image_width-1, image_height-1) );
    
    return pad;
}

static void DrawPaddedTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, filter fi, const matrix_2d &m)
{
    // TODO: need to calculate real extends instead of using this fake "far" approach. For some reason, it fails for small images.
//    const auto distant_far = 12000.;
    const auto distant_far = 2000.;
    const auto eps = 0.7;

    if( surface.pad == nullptr )
        surface.pad = make_unique<_GS::brushes::_Surface::_Pad>(BuildPad(surface.image.get(), surface.bitmap.get()));

    CGContextSetInterpolationQuality(ctx, _ToCG(fi));
    CGContextConcatCTM(ctx, _ToCG(m.inverse()) );

    CGContextSaveGState(ctx);
    CGContextConcatCTM(ctx, { 1., 0., 0., -1., 0., double(surface.height) } );
    CGContextDrawImage(ctx, CGRectMake(0, 0, surface.width, surface.height), surface.image.get());
    CGContextDrawImage(ctx, CGRectMake(surface.width - eps, 0, distant_far, surface.height), surface.pad->right.get());
    CGContextDrawImage(ctx, CGRectMake(-distant_far, 0, distant_far + eps, surface.height), surface.pad->left.get());
    CGContextRestoreGState(ctx);

    CGContextDrawImage(ctx, CGRectMake(0, -distant_far, surface.width, distant_far + eps), surface.pad->top.get());
    CGContextDrawImage(ctx, CGRectMake(0, surface.height - eps, surface.width, distant_far), surface.pad->bottom.get());
    
    CGContextSetFillColorWithColor(ctx, surface.pad->top_right.get());
    CGContextFillRect(ctx, CGRectMake(surface.width - eps, -distant_far, distant_far, distant_far + eps));

    CGContextSetFillColorWithColor(ctx, surface.pad->top_left.get());
    CGContextFillRect(ctx, CGRectMake(-distant_far, -distant_far, distant_far + eps, distant_far + eps));

    CGContextSetFillColorWithColor(ctx, surface.pad->bottom_left.get());
    CGContextFillRect(ctx, CGRectMake(-distant_far, surface.height - eps, distant_far + eps, distant_far));

    CGContextSetFillColorWithColor(ctx, surface.pad->bottom_right.get());
    CGContextFillRect(ctx, CGRectMake(surface.width - eps, surface.height - eps, distant_far, distant_far));
}

void _DrawTransparencyOutsideTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const matrix_2d &m)
{    
    CGContextConcatCTM(ctx, _ToCG(m.inverse()));
    CGContextAddRect(ctx, CGContextGetClipBoundingBox(ctx));    
    CGContextAddRect(ctx, CGRectMake(0., 0., surface.width, surface.height));
    CGContextEOClip(ctx);
        
    CGContextSetFillColorWithColor(ctx, _TransparentColor());
    CGContextFillRect(ctx, CGContextGetClipBoundingBox(ctx));
}
    
} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d
