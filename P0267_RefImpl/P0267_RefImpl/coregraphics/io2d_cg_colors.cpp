#include "io2d_cg_colors.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

CGColorSpaceRef _RGBColorSpace() noexcept
{
    static const auto rgb = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
    return rgb;
}

CGColorSpaceRef _GrayColorSpace() noexcept
{
    static const auto gray = CGColorSpaceCreateWithName(kCGColorSpaceGenericGray);
    return gray;
}

CGColorSpaceRef _PatternColorSpace() noexcept
{
    static const auto pattern = CGColorSpaceCreatePattern(nullptr);
    return pattern;
}
    
CGColorRef _ClearColor() noexcept
{
    CGFloat components[] = {0.0, 0.0, 0.0, 1.0};
    static auto color = CGColorCreate(_RGBColorSpace(), components );
    return color;
}
    
CGColorRef _TransparentColor() noexcept
{
    CGFloat components[] = {0.0, 0.0, 0.0, 0.0};    
    static auto color = CGColorCreate(_RGBColorSpace(), components);
    return color;
}
    
} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d
