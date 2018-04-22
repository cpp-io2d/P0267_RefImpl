#ifndef _IO2D_CG_GRADIENT_H_
#define _IO2D_CG_GRADIENT_H_

#include "io2d_cg_main.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

// relies only on current clipping state of ctx
    
void _DrawLinearGradient(CGContextRef ctx, const _GS::brushes::_Linear &gradient, const matrix_2d &brush_matrix, wrap_mode brush_wrapping_mode);
void _DrawRadialGradient(CGContextRef ctx, const _GS::brushes::_Radial &gradient, const matrix_2d &brush_matrix, wrap_mode brush_wrapping_mode);

} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

#endif // _IO2D_CG_GRADIENT_H_
