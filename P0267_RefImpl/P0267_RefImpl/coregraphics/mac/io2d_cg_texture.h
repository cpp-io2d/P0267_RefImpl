#ifndef _IO2D_CG_TEXTURE_H_
#define _IO2D_CG_TEXTURE_H_

#include "io2d_cg.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {
  
// relies only on current clipping state of ctx
    
void _DrawTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const basic_brush_props<_GS> &bp);
    
} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

#endif // _IO2D_CG_TEXTURE_H_
