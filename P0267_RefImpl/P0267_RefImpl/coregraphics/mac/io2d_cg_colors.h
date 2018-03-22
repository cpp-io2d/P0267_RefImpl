#ifndef _IO2D_CG_COLORS_H_
#define _IO2D_CG_COLORS_H_

#include "io2d_cg.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {
    
CGColorSpaceRef _RGBColorSpace() noexcept;
CGColorSpaceRef _GrayColorSpace() noexcept;
CGColorSpaceRef _PatternColorSpace() noexcept;
    
} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

#endif // _IO2D_CG_COLORS_H_
