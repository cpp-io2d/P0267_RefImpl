#ifndef _IO2D_CG_DISPLAY_H_
#define _IO2D_CG_DISPLAY_H_

#include "xio2d_cg_main.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {

CGRect _ScaledBackBufferRect(CGSize back_buffer_logic_size, CGSize display_buffer_logic_size, scaling sc);    
void _CheckOnceThatPixelLayoutIsTheSame( CGContextRef view_buffer, CGContextRef draw_buffer );
bool _BitBltIfPossible( CGContextRef view_buffer, CGContextRef draw_buffer, bool flip_vertically = false);    

} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

#endif
