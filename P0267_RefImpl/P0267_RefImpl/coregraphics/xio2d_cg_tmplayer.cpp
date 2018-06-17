#include "xio2d_cg_tmplayer.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

_TmpLayer::_TmpLayer(CGContextRef target_bitmap, CGRect layer_rc):
    m_TargetBitmap(target_bitmap),
    m_LayerRect(layer_rc)
{
    assert(target_bitmap);
    if( m_UseGCLayer ) {
        m_CGLayer = CGLayerCreateWithContext(m_TargetBitmap, m_LayerRect.size, nullptr);
        assert(m_CGLayer);

        m_CGLaterContext = CGLayerGetContext(m_CGLayer);
        assert(m_CGLaterContext);        
    }
    else {
        const auto bpp = CGBitmapContextGetBitsPerComponent(m_TargetBitmap);
        const auto cs = CGBitmapContextGetColorSpace(m_TargetBitmap);
        const auto bi = CGBitmapContextGetBitmapInfo(m_TargetBitmap);
        const auto width = size_t(m_LayerRect.size.width);
        const auto height = size_t(m_LayerRect.size.height);

        m_BitmapLayerContext = CGBitmapContextCreate(nullptr, width, height, bpp, 0,  cs, bi);
        assert(m_BitmapLayerContext);

        const auto rc = CGRectMake(0., 0., double(width), double(height));
        _Clear(m_BitmapLayerContext, _TransparentColor(), rc);
    }
    
    CGContextTranslateCTM(GetContext(), -m_LayerRect.origin.x, -m_LayerRect.origin.y);    
}
 
_TmpLayer::~_TmpLayer()
{
    Commit();
    
    if( m_CGLayer )
        CFRelease(m_CGLayer);
    if( m_BitmapLayerContext )
        CFRelease(m_BitmapLayerContext);
}    
    
void _TmpLayer::Commit()
{
    if( m_UseGCLayer ) {
        CGContextDrawLayerAtPoint(m_TargetBitmap, m_LayerRect.origin, m_CGLayer);
    }
    else {
        auto image = CGBitmapContextCreateImage(m_BitmapLayerContext);
        _AutoRelease release_img{image};
        CGContextDrawImage(m_TargetBitmap, m_LayerRect, image);
    }
}

CGContextRef _TmpLayer::GetContext()
{
    if( m_UseGCLayer )
        return m_CGLaterContext;
    else 
        return m_BitmapLayerContext;
}
    
} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d
