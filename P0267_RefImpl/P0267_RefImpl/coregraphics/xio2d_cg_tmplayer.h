#ifndef _IO2D_CG_TMPLAYER_H_
#define _IO2D_CG_TMPLAYER_H_

#include "xio2d_cg_main.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

class _TmpLayer
{
public:
    _TmpLayer(const _TmpLayer&) = delete;
    _TmpLayer(_TmpLayer&&) = default;
    _TmpLayer(CGContextRef target_bitmap, CGRect layer_rc);
    ~_TmpLayer();
    
    CGContextRef GetContext();
    
private:
    void Commit();
    void operator=(const _TmpLayer&) = delete;
    
    const bool      m_UseGCLayer = true;
    CGContextRef    m_TargetBitmap = nullptr;
    CGRect          m_LayerRect;
    
    CGLayerRef      m_CGLayer = nullptr;
    CGContextRef    m_CGLaterContext = nullptr;
    
    CGContextRef    m_BitmapLayerContext = nullptr;
};

} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

#endif
