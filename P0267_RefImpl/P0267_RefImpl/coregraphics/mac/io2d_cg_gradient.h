#ifndef _IO2D_CG_GRADIENT_H_
#define _IO2D_CG_GRADIENT_H_

#include "io2d_cg.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

void _DrawLinearGradient(CGContextRef ctx, const _GS::brushes::_Linear &gradient, const basic_brush_props<_GS> &bp);
void _DrawRadialGradient(CGContextRef ctx, const _GS::brushes::_Radial &gradient, const basic_brush_props<_GS> &bp);

} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

#endif // GRADIENT_H_
