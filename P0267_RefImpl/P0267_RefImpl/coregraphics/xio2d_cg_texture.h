#ifndef _IO2D_CG_TEXTURE_H_
#define _IO2D_CG_TEXTURE_H_

#include "xio2d_cg_main.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {
  
// relies only on current clipping state of ctx
    
void _DrawTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, filter fi, wrap_mode wm, const matrix_2d &m);
void _DrawTransparencyOutsideTexture(CGContextRef ctx, const _GS::brushes::_Surface &surface, const matrix_2d &m);
    
} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

#endif // _IO2D_CG_TEXTURE_H_
