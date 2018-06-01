#include "xio2d_cg_display.h"
#include <iostream>

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {
    
CGRect _ScaledBackBufferRect(CGSize back_buffer_size, CGSize display_buffer_size, scaling sc)
{
    assert(back_buffer_size.width >= 1. && back_buffer_size.height >= 1. &&
           display_buffer_size.width >= 1. && display_buffer_size.height >= 1. );
    
    switch (sc) {
        case scaling::none:
            return CGRectMake(0., 0., back_buffer_size.width, back_buffer_size.height);
        case scaling::fill_exact:
            return CGRectMake(0., 0., display_buffer_size.width, display_buffer_size.height);
        case scaling::letterbox:
        case scaling::uniform: {
            auto sx = display_buffer_size.width / back_buffer_size.width;
            auto sy = display_buffer_size.height / back_buffer_size.height;
            if( sx < sy )
                return CGRectMake(0,
                                  (display_buffer_size.height - back_buffer_size.height*sx)/2,
                                  display_buffer_size.width,
                                  back_buffer_size.height*sx);
            else
                return CGRectMake((display_buffer_size.width - back_buffer_size.width*sy)/2,
                                  0,
                                  back_buffer_size.width*sy,
                                  display_buffer_size.height);
        }
        case scaling::fill_uniform: {
            auto sx = display_buffer_size.width / back_buffer_size.width;
            auto sy = display_buffer_size.height / back_buffer_size.height;
            if( sx > sy )
                return CGRectMake(0,
                                  (display_buffer_size.height - back_buffer_size.height*sx)/2,
                                  display_buffer_size.width,
                                  back_buffer_size.height*sx);
            else
                return CGRectMake((display_buffer_size.width - back_buffer_size.width*sy)/2,
                                  0,
                                  back_buffer_size.width*sy,
                                  display_buffer_size.height);
        }
        default:
            assert(0);
    }
}    
    
void _CheckOnceThatPixelLayoutIsTheSame( CGContextRef view, CGContextRef buffer )
{
    static once_flag once;
    call_once(once, [&]{
        auto view_bitmap = CGBitmapContextGetBitmapInfo(view);
        auto buffer_bitmap = CGBitmapContextGetBitmapInfo(buffer); 
        if( view_bitmap != buffer_bitmap )
            std::cerr << "display buffer and back buffer have different pixel layouts: " 
                << view_bitmap << "(display buffer) and "
                << buffer_bitmap << "(back buffer)."
                << std::endl;
    });
}
    
bool _BitBltIfPossible( CGContextRef view, CGContextRef buffer, bool flip )
{
    const auto buffer_width = CGBitmapContextGetWidth(buffer);
    if( buffer_width != CGBitmapContextGetWidth(view) )
        return false;
    
    const auto buffer_height = CGBitmapContextGetHeight(buffer);
    if( buffer_height != CGBitmapContextGetHeight(view) )
        return false;
    
    if( CGBitmapContextGetBitmapInfo(buffer) != CGBitmapContextGetBitmapInfo(view) )
        return false;
    
    const auto bytes_per_row = CGBitmapContextGetBytesPerRow(buffer);
    if( bytes_per_row != CGBitmapContextGetBytesPerRow(view) )
        return false;
    
    if( CGBitmapContextGetBitsPerPixel(buffer) != CGBitmapContextGetBitsPerPixel(view) )
        return false;
    
    if( CGBitmapContextGetBitsPerComponent(buffer) != CGBitmapContextGetBitsPerComponent(view) )
        return false;
    
    auto buffer_data = CGBitmapContextGetData(buffer);
    auto view_data = CGBitmapContextGetData(view);
    
    if( flip ) {
        for( int src_y = 0, dst_y = int(buffer_height) - 1; src_y < buffer_height; ++src_y, --dst_y )
            memcpy((uint8_t*)view_data + bytes_per_row * dst_y,
                   (const uint8_t*)buffer_data + bytes_per_row * src_y,
                   bytes_per_row);
    }
    else {
        memcpy(view_data, buffer_data, bytes_per_row * buffer_height);        
    }
    
    return true;
}   

} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d
