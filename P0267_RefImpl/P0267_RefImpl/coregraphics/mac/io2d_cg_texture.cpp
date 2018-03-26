#include "io2d_cg_texture.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

    
static void DrawSingleTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const basic_brush_props<_GS> &bp);
    
void _DrawTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const basic_brush_props<_GS> &bp)
{
    switch( bp.wrap_mode() ) {
        case wrap_mode::none: DrawSingleTexture(ctx, surface, bp);
        default: break;
    }
}

static void DrawSingleTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const basic_brush_props<_GS> &bp)
{
    CGContextConcatCTM(ctx, _ToCG(bp.brush_matrix().inverse()) );
    CGContextSetInterpolationQuality(ctx, _ToCG(bp.filter()));
    CGContextDrawImage(ctx, CGRectMake(0, 0, surface.width, surface.height), surface.image.get());
}
        
} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d
