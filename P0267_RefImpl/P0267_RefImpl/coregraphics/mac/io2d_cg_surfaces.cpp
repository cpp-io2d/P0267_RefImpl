#include "io2d_cg_surfaces.h"
#include <CoreServices/CoreServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <ImageIO/ImageIO.h>
#include <fstream>
#include "io2d_cg_interop.h"
#include "io2d_cg_gradient.h"
#include "io2d_cg_colors.h"
#include "io2d_cg_texture.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {
    
static void SetStrokeProps( CGContextRef ctx, const basic_stroke_props<_GS>& sp ) noexcept;
static void SetDashProps( CGContextRef ctx, const basic_dashes<_GS>& d ) noexcept;
static void SetRenderProps( CGContextRef ctx, const basic_render_props<_GS>& rp ) noexcept;
static void SetClipProps( CGContextRef ctx, const basic_clip_props<_GS>& cp ) noexcept;
    
CGContextRef _CreateBitmap(io2d::format fmt, int width, int height) noexcept
{
    switch (fmt) {
        case format::argb32:
            return CGBitmapContextCreate(nullptr, width, height, 8, 0, _RGBColorSpace(), kCGImageAlphaPremultipliedFirst);
        case format::rgb24:
            return CGBitmapContextCreate(nullptr, width, height, 8, 0, _RGBColorSpace(), kCGImageAlphaNoneSkipFirst);
        case format::rgb30:
            return CGBitmapContextCreate(nullptr, width, height, 8, 0, _RGBColorSpace(), kCGImageAlphaNoneSkipFirst);
        case format::a8:
            return CGBitmapContextCreate(nullptr, width, height, 8, 0, _GrayColorSpace(), kCGImageAlphaOnly);
        case format::rgb16_565:
            return CGBitmapContextCreate(nullptr, width, height, 5, 0, _RGBColorSpace(), kCGImageAlphaNoneSkipFirst);
        default:
            return nullptr;
    }
}
    
CGContextRef _LoadBitmap(const string &p, image_file_format iff, io2d::format fmt, ::std::error_code& ec)
{
 //             TODO: error codes
    std::ifstream ifs(p, std::ifstream::in | std::ifstream::binary);
    std::vector<uint8_t> contents((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    if( contents.empty() )
        return nullptr;
    
    auto data = CFDataCreateWithBytesNoCopy(nullptr, contents.data(), contents.size(), kCFAllocatorNull);
    _AutoRelease data_release{data};
    if( !data )
        return nullptr;

    const void *keys [] = { (const void*)kCGImageSourceTypeIdentifierHint };
    const void *values[] = { (const void*)_ToCG(iff) };
    
    auto dict = CFDictionaryCreate(nullptr, keys, values, 1, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
    _AutoRelease dict_release{dict};
    
    auto source = CGImageSourceCreateWithData(data, dict);
    _AutoRelease source_release{source};
    if( !source )
        return nullptr;
    
    auto image = CGImageSourceCreateImageAtIndex(source, 0, nullptr);
    _AutoRelease image_release{image};
    
    if( !image )
        return nullptr;
    
    auto width = (int)CGImageGetWidth(image);
    auto height = (int)CGImageGetHeight(image);
    
    auto bitmap = _CreateBitmap(fmt, width, height);
    if( !bitmap )
        return nullptr;

    CGContextDrawImage(bitmap, CGRectMake(0, 0, width, height), image);
    
    return bitmap;
}
            
void _WriteBitmap(CGContextRef ctx, const string &p, image_file_format iff, ::std::error_code &ec)
{
    if (iff == image_file_format::unknown) {
        ec = make_error_code(errc::not_supported);
        return;
    }
    
    //             TODO: error codes
    auto type = _ToCG(iff);
    
    auto data = CFDataCreateMutable(nullptr, 0 );
    
    auto destination = CGImageDestinationCreateWithData(data, type, 1, nullptr);
    
    auto image = CGBitmapContextCreateImage(ctx);
    CGImageDestinationAddImage(destination, image, nullptr);
    
    CGImageDestinationFinalize(destination);
    CGImageRelease(image);
    
    
    std::ofstream ofs(p, std::ofstream::binary);
    auto bytes = reinterpret_cast<const char*>(CFDataGetBytePtr(data));
    auto size = static_cast<streamsize>(CFDataGetLength(data));
    ofs.write(bytes, size);
    
    CFRelease(data);
}

void _Clear(CGContextRef ctx, CGColorRef with_color, CGRect in_rect)
{
    CGContextSaveGState(ctx);
    CGContextSetFillColorWithColor(ctx, with_color);
    CGContextFillRect(ctx, in_rect);
    CGContextRestoreGState(ctx);
}

static void PatternDraw(void * info, CGContextRef context)
{
    auto &surface_brush = *(const _GS::brushes::_Surface*)info;
    
    CGContextDrawImage(context,
                       CGRectMake(0, 0, surface_brush.width, surface_brush.height),
                       surface_brush.image.get());
}
    
void _Stroke(CGContextRef ctx,
             const basic_brush<_GS>& b,
             const basic_interpreted_path<_GS>& ip,
             const basic_brush_props<_GS>& bp,
             const basic_stroke_props<_GS>& sp,
             const basic_dashes<_GS>& d,
             const basic_render_props<_GS>& rp,
             const basic_clip_props<_GS>& cl)
{
    if( _GS::paths::is_empty(ip._Get_data()) )
        return;
    _GStateGuard state_guard{ctx};
    SetRenderProps(ctx, rp);
    SetStrokeProps(ctx, sp);
    SetDashProps(ctx, d);
    SetClipProps(ctx, cl);
    
    if( b.type() == brush_type::solid_color ) {
        auto &solid_color_brush = std::get<_GS::brushes::_SolidColor>(*b._Get_data().brush);
        CGContextSetStrokeColorWithColor(ctx, solid_color_brush.color.get());
        CGContextAddPath(ctx, ip._Get_data().path.get());
        CGContextStrokePath(ctx);
    }
    else if( b.type() == brush_type::linear ) {
        const auto &linear_brush = std::get<_GS::brushes::_Linear>(*b._Get_data().brush);
        CGContextAddPath(ctx, ip._Get_data().path.get());
        CGContextReplacePathWithStrokedPath(ctx);
        CGContextClip(ctx);
        _DrawLinearGradient(ctx, linear_brush, bp);
    }
    else if( b.type() == brush_type::radial ) {
        const auto &radial_brush = std::get<_GS::brushes::_Radial>(*b._Get_data().brush);
        CGContextAddPath(ctx, ip._Get_data().path.get());
        CGContextReplacePathWithStrokedPath(ctx);
        CGContextClip(ctx);
        _DrawRadialGradient(ctx, radial_brush, bp);
    }
    else if( b.type() == brush_type::surface ) {
        const auto &surface_brush = std::get<_GS::brushes::_Surface>(*b._Get_data().brush);
        
        auto transform = CGAffineTransformMake(1, 0, 0, 1, 0, 0);
        
        CGPatternCallbacks callbacks = {0, &PatternDraw, nullptr};
        
        auto pattern = CGPatternCreate((void*)&surface_brush,
                                       CGRectMake (0, 0, surface_brush.width, surface_brush.height),
                                       transform,
                                       surface_brush.width,
                                       surface_brush.height,
                                       kCGPatternTilingConstantSpacing,
                                       true,
                                       &callbacks);
        _AutoRelease pattern_release{pattern};
        
        CGContextSetFillColorSpace(ctx, _PatternColorSpace());
        constexpr double components[4] = {1., 1., 1., 1.};
        CGContextSetFillPattern(ctx, pattern, components);
        CGContextAddPath(ctx, ip._Get_data().path.get());
        CGContextReplacePathWithStrokedPath(ctx);
        CGContextFillPath(ctx);
    }
}
    
void _Paint(CGContextRef ctx,
            const basic_brush<_GS>& b,
            const basic_brush_props<_GS>& bp,
            const basic_render_props<_GS>& rp,
            const basic_clip_props<_GS>& cl)
{
    _GStateGuard state_guard{ctx};
    SetRenderProps(ctx, rp);
    SetClipProps(ctx, cl);
    
    if( b.type() == brush_type::solid_color ) {
        const auto &solid_color_brush = std::get<_GS::brushes::_SolidColor>(*b._Get_data().brush);
        CGContextSetFillColorWithColor(ctx, solid_color_brush.color.get());
        CGContextFillRect(ctx, CGContextGetClipBoundingBox(ctx));
    }
    else if( b.type() == brush_type::linear ) {
        const auto &linear_brush = std::get<_GS::brushes::_Linear>(*b._Get_data().brush);
        _DrawLinearGradient(ctx, linear_brush, bp);
    }
    else if( b.type() == brush_type::radial ) {
        const auto &radial_brush = std::get<_GS::brushes::_Radial>(*b._Get_data().brush);
        _DrawRadialGradient(ctx, radial_brush, bp);
    }
    else if( b.type() == brush_type::surface ) {
        const auto &surface_brush = std::get<_GS::brushes::_Surface>(*b._Get_data().brush);
        _DrawTexture(ctx, surface_brush, bp);
    }
}

void _Fill(CGContextRef ctx,
           const basic_brush<_GS>& b,
           const basic_interpreted_path<_GS>& ip,
           const basic_brush_props<_GS>& bp,
           const basic_render_props<_GS>& rp,
           const basic_clip_props<_GS>& cl)
{
    if( _GS::paths::is_empty(ip._Get_data()) )
        return;
    _GStateGuard state_guard{ctx};
    SetRenderProps(ctx, rp);
    SetClipProps(ctx, cl);
    
    if( b.type() == brush_type::solid_color ) {
        const auto &solid_color_brush = std::get<_GS::brushes::_SolidColor>(*b._Get_data().brush);
        CGContextSetFillColorWithColor(ctx, solid_color_brush.color.get());
        CGContextAddPath(ctx, ip._Get_data().path.get());
        CGContextFillPath(ctx);
    }
    else if( b.type() == brush_type::linear ) {
        const auto &linear_brush = std::get<_GS::brushes::_Linear>(*b._Get_data().brush);
        CGContextAddPath(ctx, ip._Get_data().path.get());
        CGContextClip(ctx);
        _DrawLinearGradient(ctx, linear_brush, bp);
    }
    else if( b.type() == brush_type::radial ) {
        const auto &radial_brush = std::get<_GS::brushes::_Radial>(*b._Get_data().brush);
        CGContextAddPath(ctx, ip._Get_data().path.get());
        CGContextClip(ctx);
        _DrawRadialGradient(ctx, radial_brush, bp);
    }
    else if( b.type() == brush_type::surface ) {
        const auto &surface_brush = std::get<_GS::brushes::_Surface>(*b._Get_data().brush);
        
        auto transform = CGAffineTransformMake(1, 0, 0, 1, 0, 0);
        
        CGPatternCallbacks callbacks = {0, &PatternDraw, nullptr};
        
        auto pattern = CGPatternCreate((void*)&surface_brush,
                                       CGRectMake (0, 0, surface_brush.width, surface_brush.height),
                                       transform,
                                       surface_brush.width,
                                       surface_brush.height,
                                       kCGPatternTilingConstantSpacing,
                                       true,
                                       &callbacks);
        _AutoRelease pattern_release{pattern};
        
        CGContextSetFillColorSpace(ctx, _PatternColorSpace());
        constexpr double components[4] = {1., 1., 1., 1.};
        CGContextSetFillPattern(ctx, pattern, components);
        CGContextAddPath(ctx, ip._Get_data().path.get());
        CGContextFillPath(ctx);
    }
}

static void SetClipProps( CGContextRef ctx, const basic_clip_props<_GS>& cp ) noexcept {
    auto path = cp.clip();
    if( _GS::paths::is_empty(path._Get_data()) )
        return;
    CGContextAddPath(ctx, path._Get_data().path.get());
    if( cp.fill_rule() == fill_rule::winding )
        CGContextClip(ctx);
    else
        CGContextEOClip(ctx);
}

static void SetStrokeProps( CGContextRef ctx, const basic_stroke_props<_GS>& sp ) noexcept
{
    CGContextSetLineCap(ctx, _ToCG(sp.line_cap()));
    CGContextSetLineWidth(ctx, sp.line_width());
    CGContextSetMiterLimit(ctx, sp.miter_limit());
    CGContextSetLineJoin(ctx, _ToCG(sp.line_join()));
}
    
static void SetRenderProps( CGContextRef ctx, const basic_render_props<_GS>& rp ) noexcept
{
    CGContextSetShouldAntialias(ctx, rp.antialiasing() != antialias::none);
    CGContextSetBlendMode(ctx, _ToCG(rp.compositing()));
    
    auto height = CGBitmapContextGetHeight(ctx);
    CGContextConcatCTM(ctx, CGAffineTransform{ 1., 0., 0., -1., 0., double(height) } );
    CGContextConcatCTM(ctx, _ToCG(rp.surface_matrix()));
}
    
static void SetDashProps( CGContextRef ctx, const basic_dashes<_GS>& d ) noexcept
{
    auto &data = d._Get_data();
    auto sz = data.pattern.size();
    if( sz == 1 ) {
        double lens[2] = { data.pattern[0], data.pattern[0] };
        CGContextSetLineDash(ctx, data.offset, lens, 2);
    }
    else if( sz >= 2 ) {
        CGContextSetLineDash(ctx, data.offset, data.pattern.data(), sz);
    }
}

} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d
