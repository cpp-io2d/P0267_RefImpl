#include "xinterchangebuffer.h"
#include <array>
#include <cmath>
#include <assert.h>

namespace std::experimental::io2d { inline namespace v1 {

static int BytesPerPixel(_Interchange_buffer::pixel_layout layout)
{
    switch( layout ) {
        case _Interchange_buffer::pixel_layout::b8g8r8a8:
        case _Interchange_buffer::pixel_layout::a8r8g8b8:
        case _Interchange_buffer::pixel_layout::r8g8b8a8:
        case _Interchange_buffer::pixel_layout::a8b8g8r8:            
            return 4;
        case _Interchange_buffer::pixel_layout::r5g6b5:
        case _Interchange_buffer::pixel_layout::b5g6r5:
        case _Interchange_buffer::pixel_layout::r5g5b5a1:
        case _Interchange_buffer::pixel_layout::a1r5g5b5:
        case _Interchange_buffer::pixel_layout::b5g5r5a1:
        case _Interchange_buffer::pixel_layout::a1b5g5r5:
            return 2;
        case _Interchange_buffer::pixel_layout::a8:
            return 1;
        default:
            assert(0);
    }
    return 0;            
}    
    
static int DefaultStride(int width, _Interchange_buffer::pixel_layout layout)
{
    assert( width >= 0 );
    return BytesPerPixel(layout) * width;
}

static void Copy( std::byte *target, int target_stride, const std::byte *source, int /*width*/, int height, int source_stride )
{
    if( target_stride == source_stride )
        std::copy( source, source + source_stride * height, target );
    else for( int row = 0; row < height; ++row, source += source_stride, target += target_stride )
        std::copy( source, source + source_stride, target );
}
    
static std::array<float, 4> ExtractFloatRGBA(const std::byte *source,
                                             _Interchange_buffer::pixel_layout layout,
                                             _Interchange_buffer::alpha_mode alpha_mode) noexcept
{
    // following calculations assume little-endian architecture.
    
    float r = 1.f, g = 1.f, b = 1.f, a = 1.f;
    
    switch (layout) {
        case _Interchange_buffer::pixel_layout::b8g8r8a8: {
            auto p = (const uint8_t *)source;  
            r = float(p[2])/255.f;
            g = float(p[1])/255.f;
            b = float(p[0])/255.f;
            a = float(p[3])/255.f;
            break;
        }   
        case _Interchange_buffer::pixel_layout::a8r8g8b8: {
            auto p = (const uint8_t *)source;  
            r = float(p[1])/255.f;
            g = float(p[2])/255.f;
            b = float(p[3])/255.f;
            a = float(p[0])/255.f;
            break;
        }
        case _Interchange_buffer::pixel_layout::r8g8b8a8: {
            auto p = (const uint8_t *)source;  
            r = float(p[0])/255.f;
            g = float(p[1])/255.f;
            b = float(p[2])/255.f;
            a = float(p[3])/255.f;
            break;
        }
        case _Interchange_buffer::pixel_layout::a8b8g8r8: {
            auto p = (const uint8_t *)source;  
            r = float(p[3])/255.f;
            g = float(p[2])/255.f;
            b = float(p[1])/255.f;
            a = float(p[0])/255.f;
            break;
        }
        case _Interchange_buffer::pixel_layout::r5g6b5: {
            auto p = *(const uint16_t *)source;
            const auto red_mask = uint16_t(31 << 0);
            const auto green_mask = uint16_t(63 << 5);
            const auto blue_mask = uint16_t(31 << 11);
            r = float((p & red_mask) >> 0)/31.f;
            g = float((p & green_mask) >> 5)/63.f;
            b = float((p & blue_mask) >> 11)/31.f;
            a = 1.f;
            break;
        }
        case _Interchange_buffer::pixel_layout::b5g6r5: {
            auto p = *(const uint16_t *)source;
            const auto red_mask = uint16_t(31 << 11);
            const auto green_mask = uint16_t(63 << 5);
            const auto blue_mask = uint16_t(31 << 0);
            r = float((p & red_mask) >> 11)/31.f;
            g = float((p & green_mask) >> 5)/63.f;
            b = float((p & blue_mask) >> 0)/31.f;
            a = 1.f;
            break;
        }
        case _Interchange_buffer::pixel_layout::r5g5b5a1: {
            auto p = *(const uint16_t *)source;
            const auto red_mask = uint16_t(31 << 0);
            const auto green_mask = uint16_t(31 << 5);
            const auto blue_mask = uint16_t(31 << 10);
            const auto alpha_mask = uint16_t(1 << 15);
            r = float((p & red_mask) >> 0)/31.f;
            g = float((p & green_mask) >> 5)/31.f;
            b = float((p & blue_mask) >> 10)/31.f;
            a = (p & alpha_mask) != 0 ? 1.f : 0.f;
            break;
        }
        case _Interchange_buffer::pixel_layout::b5g5r5a1: {
            auto p = *(const uint16_t *)source;
            const auto red_mask = uint16_t(31 << 10);
            const auto green_mask = uint16_t(31 << 5);
            const auto blue_mask = uint16_t(31 << 0);
            const auto alpha_mask = uint16_t(1 << 15);
            r = float((p & red_mask) >> 10)/31.f;
            g = float((p & green_mask) >> 5)/31.f;
            b = float((p & blue_mask) >> 0)/31.f;
            a = (p & alpha_mask) != 0 ? 1.f : 0.f;
            break;
        }
        case _Interchange_buffer::pixel_layout::a1r5g5b5: {
            auto p = *(const uint16_t *)source;
            const auto red_mask = uint16_t(31 << 1);
            const auto green_mask = uint16_t(31 << 6);
            const auto blue_mask = uint16_t(31 << 11);
            const auto alpha_mask = uint16_t(1 << 0);
            r = float((p & red_mask) >> 1)/31.f;
            g = float((p & green_mask) >> 6)/31.f;
            b = float((p & blue_mask) >> 11)/31.f;
            a = (p & alpha_mask) != 0 ? 1.f : 0.f;
            break;
        }
        case _Interchange_buffer::pixel_layout::a1b5g5r5: {
            auto p = *(const uint16_t *)source;
            const auto red_mask = uint16_t(31 << 11);
            const auto green_mask = uint16_t(31 << 6);
            const auto blue_mask = uint16_t(31 << 1);
            const auto alpha_mask = uint16_t(1 << 0);
            r = float((p & red_mask) >> 11)/31.f;
            g = float((p & green_mask) >> 6)/31.f;
            b = float((p & blue_mask) >> 1)/31.f;
            a = (p & alpha_mask) != 0 ? 1.f : 0.f;
            break;
        }
        case _Interchange_buffer::pixel_layout::a8: {
            auto p = *(const uint8_t *)source;
            r = 0.f;
            g = 0.f;
            b = 0.f;
            a = float(p)/255.f;
            break;
        }    
        default: assert(0);
    }
    
    switch (alpha_mode) {
        case _Interchange_buffer::alpha_mode::ignore:
            a = 1.f;
            break;
        case _Interchange_buffer::alpha_mode::straight:
            break;
        case _Interchange_buffer::alpha_mode::premultiplied:
            if( a > numeric_limits<float>::min() && 1.f - a > numeric_limits<double>::min() ) {
                r = min( 1.f, r / a );
                g = min( 1.f, g / a );
                b = min( 1.f, b / a );
            }
            break;
    }
    
    return {{r, g, b, a}};
}
    
static void WriteFloatRGBA(std::array<float, 4> rgba,
                           std::byte *target,
                           _Interchange_buffer::pixel_layout layout,
                           _Interchange_buffer::alpha_mode alpha_mode)
{
    // following calculations assume little-endian architecture.
    
    switch (alpha_mode) {
        case _Interchange_buffer::alpha_mode::ignore:
            rgba[3] = 1.f;
            break;
        case _Interchange_buffer::alpha_mode::straight:
            break;
        case _Interchange_buffer::alpha_mode::premultiplied:
            if( 1.f - rgba[3] > numeric_limits<float>::min() ) {
                rgba[0] = rgba[0] * rgba[3];
                rgba[1] = rgba[1] * rgba[3];
                rgba[2] = rgba[2] * rgba[3];
            }
            break;
    }
        
    switch (layout) {
        case _Interchange_buffer::pixel_layout::b8g8r8a8: {
            auto p = (uint8_t *)target;
            p[2] = uint8_t(rgba[0] * 255.f + 0.5f);
            p[1] = uint8_t(rgba[1] * 255.f + 0.5f);
            p[0] = uint8_t(rgba[2] * 255.f + 0.5f);
            p[3] = uint8_t(rgba[3] * 255.f + 0.5f);
            break;
        }   
        case _Interchange_buffer::pixel_layout::a8r8g8b8: {
            auto p = (uint8_t *)target;
            p[1] = uint8_t(rgba[0] * 255.f + 0.5f);
            p[2] = uint8_t(rgba[1] * 255.f + 0.5f);
            p[3] = uint8_t(rgba[2] * 255.f + 0.5f);
            p[0] = uint8_t(rgba[3] * 255.f + 0.5f);
            break;            
        }
        case _Interchange_buffer::pixel_layout::r8g8b8a8: {
            auto p = (uint8_t *)target;
            p[0] = uint8_t(rgba[0] * 255.f + 0.5f);
            p[1] = uint8_t(rgba[1] * 255.f + 0.5f);
            p[2] = uint8_t(rgba[2] * 255.f + 0.5f);
            p[3] = uint8_t(rgba[3] * 255.f + 0.5f);
            break;              
        }
        case _Interchange_buffer::pixel_layout::a8b8g8r8: {
            auto p = (uint8_t *)target;
            p[3] = uint8_t(rgba[0] * 255.f + 0.5f);
            p[2] = uint8_t(rgba[1] * 255.f + 0.5f);
            p[1] = uint8_t(rgba[2] * 255.f + 0.5f);
            p[0] = uint8_t(rgba[3] * 255.f + 0.5f);
            break;                
        }
        case _Interchange_buffer::pixel_layout::r5g6b5: {
            auto &p = *(uint16_t *)target;
            p = (uint16_t(rgba[0] * 31.f + 0.5f) << 0) |
                (uint16_t(rgba[1] * 63.f + 0.5f) << 5) |
                (uint16_t(rgba[2] * 31.f + 0.5f) << 11);
            break;
        }
        case _Interchange_buffer::pixel_layout::b5g6r5: {
            auto &p = *(uint16_t *)target;            
            p = (uint16_t(rgba[0] * 31.f + 0.5f) << 11)|
                (uint16_t(rgba[1] * 63.f + 0.5f) << 5) |
                (uint16_t(rgba[2] * 31.f + 0.5f) << 0) ;
            break;            
        }
        case _Interchange_buffer::pixel_layout::r5g5b5a1: {
            auto &p = *(uint16_t *)target;            
            p = (uint16_t(rgba[0] * 31.f + 0.5f) << 0) |
                (uint16_t(rgba[1] * 31.f + 0.5f) << 5) |
                (uint16_t(rgba[2] * 31.f + 0.5f) << 10)|
                (uint16_t(rgba[3]        + 0.5f) << 15);            
            break;
        }
        case _Interchange_buffer::pixel_layout::b5g5r5a1: {
            auto &p = *(uint16_t *)target;
            p = (uint16_t(rgba[0] * 31.f + 0.5f) << 10)|
                (uint16_t(rgba[1] * 31.f + 0.5f) << 5) |
                (uint16_t(rgba[2] * 31.f + 0.5f) << 0) |
                (uint16_t(rgba[3]        + 0.5f) << 15);
            break;
        }        
        case _Interchange_buffer::pixel_layout::a1r5g5b5: {
            auto &p = *(uint16_t *)target;            
            p = (uint16_t(rgba[0] * 31.f + 0.5f) << 1) |
                (uint16_t(rgba[1] * 31.f + 0.5f) << 6) |
                (uint16_t(rgba[2] * 31.f + 0.5f) << 11)|
                (uint16_t(rgba[3]        + 0.5f) << 0) ;            
            break;
        }
        case _Interchange_buffer::pixel_layout::a1b5g5r5: {
            auto &p = *(uint16_t *)target;
            p = (uint16_t(rgba[0] * 31.f + 0.5f) << 11)|
                (uint16_t(rgba[1] * 31.f + 0.5f) << 6) |
                (uint16_t(rgba[2] * 31.f + 0.5f) << 1) |
                (uint16_t(rgba[3]        + 0.5f) << 0) ;
            break;
        }
        case _Interchange_buffer::pixel_layout::a8: {
            auto &p = *(uint8_t *)target;
            p = uint8_t(rgba[3] * 255.f + 0.5f);
            break;
        }            
        default: assert(0);
    }        
}
    
static void Cast(std::byte *target,
                 _Interchange_buffer::pixel_layout target_layout,
                 _Interchange_buffer::alpha_mode target_alpha_mode,
                 const std::byte *source,
                 _Interchange_buffer::pixel_layout source_layout,
                 _Interchange_buffer::alpha_mode source_alpha_mode) noexcept
{
    const auto rgba = ExtractFloatRGBA(source, source_layout, source_alpha_mode);
    WriteFloatRGBA(rgba, target, target_layout, target_alpha_mode);
}
                 
static void Interpret(std::byte *target_data,
                      enum _Interchange_buffer::pixel_layout target_layout,
                      enum _Interchange_buffer::alpha_mode target_alpha_mode,
                      int target_stride, 
                      const std::byte *source_data,
                      enum _Interchange_buffer::pixel_layout source_layout,
                      enum _Interchange_buffer::alpha_mode source_alpha_mode,
                      int source_width,
                      int source_height,
                      int source_stride) noexcept
{
    const auto dst_bpp = BytesPerPixel(target_layout);
    const auto src_bpp = BytesPerPixel(source_layout);   
    for( int row = 0; row < source_height; ++row ) {
        for( int column = 0; column < source_width; ++column ) {
            auto src = source_data + row * source_stride + column * src_bpp;
            auto dst = target_data + row * target_stride + column * dst_bpp;
            Cast(dst, target_layout, target_alpha_mode, src, source_layout, source_alpha_mode);
        }
    }
}

_Interchange_buffer::_Interchange_buffer(pixel_layout target_layout,
                                         alpha_mode target_alpha_mode,
                                         int target_width,
                                         int target_height)
{
    assert( target_width >= 0 );
    assert( target_height >= 0 );

    m_Layout = target_layout;
    m_Alpha = target_alpha_mode;
    m_Width = target_width;
    m_Height = target_height;
    m_Stride = DefaultStride(m_Width, m_Layout);
    
    if( target_width == 0 || target_height == 0 )
        return;
    
    m_Buffer = std::make_unique<byte[]>(m_Stride * m_Height);
    fill( m_Buffer.get(), m_Buffer.get() + m_Stride * m_Height, std::byte{0});
}    

_Interchange_buffer::_Interchange_buffer(pixel_layout target_layout,
                                         alpha_mode target_alpha_mode,
                                         const std::byte *source_data,
                                         pixel_layout source_layout,
                                         alpha_mode source_alpha_mode,
                                         int source_width,
                                         int source_height,
                                         int source_stride)
{
    assert( source_data != 0 );
    assert( source_width >= 0 );
    assert( source_height >= 0 );
    assert( source_stride >= 0 );

    m_Layout = target_layout;
    m_Alpha = target_alpha_mode;
    m_Width = source_width;
    m_Height = source_height;
    m_Stride = DefaultStride(m_Width, m_Layout);
        
    if( source_width == 0 || source_height == 0 )
        return;
    
    if( source_stride == 0 )
        source_stride = DefaultStride(source_width, source_layout);

    m_Buffer = std::make_unique<byte[]>(m_Stride * m_Height);
    
    if( target_layout == source_layout && target_alpha_mode == source_alpha_mode )
        Copy( m_Buffer.get(), m_Stride, source_data, source_width, source_height, source_stride );
    else
        Interpret(m_Buffer.get(), m_Layout, m_Alpha, m_Stride, source_data, source_layout, source_alpha_mode, source_width, source_height, source_stride);        
}
    
bool operator==(const _Interchange_buffer& lhs, const _Interchange_buffer& rhs) noexcept
{
    return lhs.layout() == rhs.layout() &&
           lhs.alpha() == rhs.alpha() &&
           lhs.width() == rhs.width() &&
           lhs.height() == rhs.height() &&
           equal(lhs.data(), lhs.data() + lhs.height()*lhs.stride(), rhs.data());
}

bool operator!=(const _Interchange_buffer& lhs, const _Interchange_buffer& rhs) noexcept
{
    return !(lhs == rhs);
}

} // inline namespace v1
} // std::experimental::io2d 
