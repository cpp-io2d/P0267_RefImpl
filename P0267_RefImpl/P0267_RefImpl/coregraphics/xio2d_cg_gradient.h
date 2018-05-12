#ifndef _IO2D_CG_GRADIENT_H_
#define _IO2D_CG_GRADIENT_H_

#include "xio2d_cg_main.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

// relies only on current clipping state of ctx
    
void _DrawLinearGradient(CGContextRef ctx, const _GS::brushes::_Linear &gradient, wrap_mode brush_wrapping_mode, const matrix_2d &brush_matrix);
void _DrawRadialGradient(CGContextRef ctx, const _GS::brushes::_Radial &gradient, wrap_mode brush_wrapping_mode, const matrix_2d &brush_matrix);

} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

#endif // _IO2D_CG_GRADIENT_H_
