#ifndef _IO2D_CG_BRUSHES_
#define _IO2D_CG_BRUSHES_

#include "xio2d_cg_main.h"
#include "xio2d_cg_interop.h"
#include "xio2d_cg_colors.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {
            
inline _GS::brushes::brush_data_type
_GS::brushes::create_brush(const rgba_color& c) {    
    CGFloat components[] = {c.r(), c.g(), c.b(), c.a()};
    auto color = CGColorCreate(_RGBColorSpace(), components);
    
    if( color == nullptr )
        throw ::std::runtime_error("error");
    
    _SolidColor solid_data;
    solid_data.color.reset(color);
    solid_data.source = c;
    
    brush_data_type data;
    data.brush = std::make_shared<typename brush_data_type::brush_t>( ::std::move(solid_data) );
    data.brushType = brush_type::solid_color;
    return data;
}
            
inline _GS::brushes::brush_data_type
_GS::brushes::create_brush(basic_image_surface<_GS>&& img) {
    auto &source_data = img.data();
    
    _Surface surface_data;
    surface_data.bitmap = ::std::move(source_data.context);
    surface_data.image.reset( CGBitmapContextCreateImage(surface_data.bitmap.get()) );
    surface_data.width = (int)CGImageGetWidth(surface_data.image.get());
    surface_data.height = (int)CGImageGetHeight(surface_data.image.get());
    
    brush_data_type data;
    data.brush = std::make_shared<typename brush_data_type::brush_t>( ::std::move(surface_data) );
    data.brushType = brush_type::surface;
    return data;
}

template <class InputIterator>
inline _GS::brushes::brush_data_type
_GS::brushes::create_brush(const basic_point_2d<GraphicsMath>& begin, const basic_point_2d<GraphicsMath>& end, InputIterator first, InputIterator last) {
    _Linear linear_data;
    linear_data.start = begin;
    linear_data.end = end;
    linear_data.stops.assign(first, last);
    
    brush_data_type data;
    data.brush = std::make_shared<typename brush_data_type::brush_t>( ::std::move(linear_data) );
    data.brushType = brush_type::linear;
    return data;
}
    
inline _GS::brushes::brush_data_type
_GS::brushes::create_brush(const basic_point_2d<GraphicsMath>& begin, const basic_point_2d<GraphicsMath>& end, ::std::initializer_list<gradient_stop> il) {
    return create_brush(begin, end, il.begin(), il.end());
}
    
template <class InputIterator>
inline _GS::brushes::brush_data_type
_GS::brushes::create_brush(const basic_circle<GraphicsMath>& start, const basic_circle<GraphicsMath>& end, InputIterator first, InputIterator last) {
    _Radial radial_data;
    radial_data.start = start;
    radial_data.end = end;
    radial_data.stops.assign(first, last);
    
    brush_data_type data;
    data.brush = std::make_shared<typename brush_data_type::brush_t>( ::std::move(radial_data) );
    data.brushType = brush_type::radial;
    return data;
}
    
inline _GS::brushes::brush_data_type
_GS::brushes::create_brush(const basic_circle<GraphicsMath>& start, const basic_circle<GraphicsMath>& end, ::std::initializer_list<gradient_stop> il) {
    return create_brush(start, end, il.begin(), il.end());
}
    
inline _GS::brushes::brush_data_type
_GS::brushes::copy_brush(const brush_data_type& data) {
    return data;
}

inline _GS::brushes::brush_data_type
_GS::brushes::move_brush(brush_data_type&& data) noexcept {
    return ::std::move(data);
}

inline void
_GS::brushes::destroy(brush_data_type&/*data*/) noexcept {
    // Do nothing.
}

inline brush_type
_GS::brushes::get_brush_type(const brush_data_type& data) noexcept {
    return data.brushType;
}

} // namespace _CoreGraphics
} // inline namespace v1
} // std::experimental::io2d

#endif
