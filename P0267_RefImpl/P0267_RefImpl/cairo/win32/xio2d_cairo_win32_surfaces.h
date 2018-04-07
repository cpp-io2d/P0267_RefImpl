#pragma once

namespace std::experimental::io2d {
    inline namespace v1 {
        namespace _Cairo {

            template <class GraphicsMath>
            void _Create_display_surface_and_context(typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::_Display_surface_data_type& data);
            
            template <class GraphicsSurfaces>
            void _Ds_clear(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data);
            
            template <class GraphicsSurfaces>
            void _Ds_paint(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_brush<GraphicsSurfaces>& b, const basic_brush_props<GraphicsSurfaces>& bp, const basic_render_props<GraphicsSurfaces>& rp, const basic_clip_props<GraphicsSurfaces>& cl);

            template <class GraphicsSurfaces>
            void _Ds_stroke(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const basic_brush_props<GraphicsSurfaces>& bp, const basic_stroke_props<GraphicsSurfaces>& sp, const basic_dashes<GraphicsSurfaces>& d, const basic_render_props<GraphicsSurfaces>& rp, const basic_clip_props<GraphicsSurfaces>& cl);

            template <class GraphicsSurfaces>
            void _Ds_fill(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const basic_brush_props<GraphicsSurfaces>& bp, const basic_render_props<GraphicsSurfaces>& rp, const basic_clip_props<GraphicsSurfaces>& cl);

            template <class GraphicsSurfaces>
            void _Ds_mask(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const basic_brush_props<GraphicsSurfaces>& bp, const basic_mask_props<GraphicsSurfaces>& mp, const basic_render_props<GraphicsSurfaces>& rp, const basic_clip_props<GraphicsSurfaces>& cl);

            template <class GraphicsSurfaces>
            void _Ds_dimensions(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_display_point<typename GraphicsSurfaces::graphics_math_type>& val);

            template <class GraphicsSurfaces>
            void _Ds_display_dimensions(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_display_point<typename GraphicsSurfaces::graphics_math_type>& val);

            template <class GraphicsSurfaces>
            void _Ds_scaling(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, io2d::scaling val);

            template <class GraphicsSurfaces>
            void _Ds_letterbox_brush(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const optional<basic_brush<GraphicsSurfaces>>& val, const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept;

            template <class GraphicsSurfaces>
            void _Ds_letterbox_brush_props(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_brush_props<GraphicsSurfaces>& val);

            template <class GraphicsSurfaces>
            void _Ds_auto_clear(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, bool val);

            template <class GraphicsSurfaces>
            void _Ds_redraw_required(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, bool val);

            template <class GraphicsSurfaces>
            io2d::format _Ds_format(const typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept;

            template <class GraphicsSurfaces>
            basic_display_point<typename GraphicsSurfaces::graphics_math_type> _Ds_dimensions(const typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept;

            template <class GraphicsSurfaces>
            basic_display_point<typename GraphicsSurfaces::graphics_math_type> _Ds_max_dimensions() noexcept;

            template <class GraphicsSurfaces>
            basic_display_point<typename GraphicsSurfaces::graphics_math_type> _Ds_display_dimensions(const typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept;

            template <class GraphicsSurfaces>
            basic_display_point<typename GraphicsSurfaces::graphics_math_type> _Ds_max_display_dimensions() noexcept;

            template <class GraphicsSurfaces>
            io2d::scaling _Ds_scaling(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept;

            template <class GraphicsSurfaces>
            optional<basic_brush<GraphicsSurfaces>> _Ds_letterbox_brush(const typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept;

            template <class GraphicsSurfaces>
            basic_brush_props<GraphicsSurfaces> _Ds_letterbox_brush_props(const typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept;

            template <class GraphicsSurfaces>
            bool _Ds_auto_clear(const typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept;

            template <class GraphicsSurfaces>
            bool _Ds_redraw_required(const typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept;
                        
            template <class OutputDataType>
            void _Render_for_scaling_uniform_or_letterbox(OutputDataType& osd);
        }
    }
}
