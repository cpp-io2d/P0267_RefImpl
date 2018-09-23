#ifndef _IO2D_CG_PATHS_H
#define _IO2D_CG_PATHS_H

#include "xio2d_cg_main.h"
#include "xio2d_cg_interop.h"

namespace std::experimental::io2d { inline namespace v1 { namespace _CoreGraphics {
    
struct _PathInterperationContext {
    CGMutablePathRef path = nullptr;
    basic_point_2d<GraphicsMath> position;      // user coordinate space
    basic_point_2d<GraphicsMath> figure_start;  // user coordinate space
    basic_matrix_2d<GraphicsMath> transform;    // user space -> device space transformation
    std::stack<basic_matrix_2d<GraphicsMath>> transforms_stack;
    void Insert( const basic_figure_items<_GS>::figure_item &figure );
};

inline _GS::paths::interpreted_path_data_type
_GS::paths::create_interpreted_path() noexcept {
    return {};
}

template <class ForwardIterator>
inline _GS::paths::interpreted_path_data_type
_GS::paths::create_interpreted_path(ForwardIterator first, ForwardIterator last) {
    _PathInterperationContext context;
    for(; first != last; ++first )
        context.Insert( *first );    
    interpreted_path_data_type data;
    data.path = shared_ptr<typename interpreted_path_data_type::path_t>(context.path, CGPathRelease);
    return data;
}
    
inline _GS::paths::interpreted_path_data_type
_GS::paths::create_interpreted_path(const bounding_box& bb) {
    using bf = basic_figure_items<graphics_surfaces_type>;
    using fi = typename bf::figure_item;
    initializer_list<fi> il = {
        fi(bf::abs_new_figure(bb.top_left())),
        fi(bf::rel_line({bb.width(), 0})),
        fi(bf::rel_line({0, bb.height()})),
        fi(bf::rel_line({-bb.width(), 0})),
        fi(bf::rel_line({0, -bb.height()})),
        fi(bf::close_figure{})
    };
    return create_interpreted_path(il);
}

inline _GS::paths::interpreted_path_data_type
_GS::paths::create_interpreted_path(initializer_list<typename basic_figure_items<graphics_surfaces_type>::figure_item> il)
{
    return create_interpreted_path(begin(il), end(il));
}    
    
inline _GS::paths::interpreted_path_data_type
_GS::paths::copy_interpreted_path(const interpreted_path_data_type& data) noexcept {
    return data;
}

inline _GS::paths::interpreted_path_data_type
_GS::paths::move_interpreted_path(interpreted_path_data_type&& data) noexcept {
    return data;
}

inline void
_GS::paths::destroy(interpreted_path_data_type&) noexcept {
    // Do nothing.
}

inline bool
_GS::paths::is_empty(const interpreted_path_data_type& data) noexcept {
    return data.path == nullptr || CGPathIsEmpty(data.path.get());
}
    
} // namespace _CoreGraphics
} // inline namespace v1
} // namespace std::experimental::io2d

#endif
