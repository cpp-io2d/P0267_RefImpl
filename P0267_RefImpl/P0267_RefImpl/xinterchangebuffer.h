#ifndef _XINTERCHANGEBUFFER_H_
#define _XINTERCHANGEBUFFER_H_

#include <cstddef>
#include <memory>

namespace std::experimental::io2d { inline namespace v1 {
 
class _Interchange_buffer
{
public:
    enum pixel_layout {
        // 32 bits per pixel
        b8g8r8a8,
        a8r8g8b8,
        r8g8b8a8,
        a8b8g8r8,
        
        // 16 bit per pixel
        r5g6b5,
        b5g6r5,
        r5g5b5a1,
        a1r5g5b5,
        b5g5r5a1,
        a1b5g5r5,
        
        // 8 bits per pixel
        a8
        
        // TODO:
        // 888 - maybe?
    };
    
    enum alpha_mode {
        premultiplied,
        straight,
        ignore
    };    
    
    _Interchange_buffer() noexcept {};
    
    _Interchange_buffer(pixel_layout target_layout,
                        alpha_mode target_alpha_mode,
                        int target_width,
                        int target_height);    
    
    _Interchange_buffer(pixel_layout target_layout,
                        alpha_mode target_alpha_mode,
                        const std::byte *source_data,
                        pixel_layout source_layout,
                        alpha_mode source_alpha_mode,
                        int source_width,
                        int source_height,
                        int source_stride = 0);    

    int width() const noexcept { return m_Width; }
    int height() const noexcept { return m_Height; }
    int stride() const noexcept { return m_Stride; }
    pixel_layout layout() const noexcept { return m_Layout; }
    alpha_mode alpha() const noexcept { return m_Alpha; }
    const std::byte *data() const noexcept { return m_Buffer.get(); }
    std::byte *data() noexcept { return m_Buffer.get(); }
    
private:
    std::unique_ptr<std::byte[]> m_Buffer = nullptr;
    int m_Width = 0;
    int m_Height = 0;
    int m_Stride = 0;
    pixel_layout m_Layout = pixel_layout::b8g8r8a8;
    alpha_mode m_Alpha = alpha_mode::premultiplied;
};
    
bool operator==(const _Interchange_buffer& lhs, const _Interchange_buffer& rhs) noexcept;
bool operator!=(const _Interchange_buffer& lhs, const _Interchange_buffer& rhs) noexcept;

} // inline namespace v1
} // std::experimental::io2d 
#endif
