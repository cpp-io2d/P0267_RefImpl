#ifndef _IO2D_CG_COLORS_H_
#define _IO2D_CG_COLORS_H_

#include <CoreGraphics/CoreGraphics.h>

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {
    
CGColorSpaceRef _RGBColorSpace() noexcept;
CGColorSpaceRef _GrayColorSpace() noexcept;
CGColorSpaceRef _PatternColorSpace() noexcept;

CGColorRef _ClearColor() noexcept;       // 0.0, 0.0, 0.0, 1.0
CGColorRef _TransparentColor() noexcept; // 0.0, 0.0, 0.0, 0.0
    
} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

#endif // _IO2D_CG_COLORS_H_
