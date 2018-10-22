#pragma once
#include "xcairo_surfaces_impl.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Cairo {
			// unmanaged output surface functions

			template<class GraphicsMath>
			struct _Cairo_graphics_surfaces<GraphicsMath>::surfaces::_UnmanagedSurfaceContext {

			};

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::unmanaged_output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_unmanaged_output_surface() {
				return new _Unmanaged_output_surface_data;
			}

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::unmanaged_output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_unmanaged_output_surface(_UnmanagedSurfaceContext &context, int preferredWidth, int preferredHeight, io2d::format preferredFormat, io2d::scaling scl) {
				throw ::std::system_error(::std::make_error_code(::std::errc::not_supported), "io2d/SDL2 port doesn't support unmanaged surfaces, as of yet");
				return create_unmanaged_output_surface();
			}

			template <class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::unmanaged_output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::move_unmanaged_output_surface(unmanaged_output_surface_data_type&& data) noexcept {
				auto result = data;
				data = nullptr;
				return result;
			}
			template <class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::destroy(unmanaged_output_surface_data_type& data) noexcept {
				destroy(data->data.back_buffer);
				delete data;
			}
			template<class GraphicsMath>
			inline bool _Cairo_graphics_surfaces<GraphicsMath>::surfaces::has_draw_callback(const unmanaged_output_surface_data_type& data) noexcept {
				return data->draw_callback != nullptr;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::invoke_draw_callback(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc) {
				data->draw_callback(sfc);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_to_output(unmanaged_output_surface_data_type& uosd, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc) {
				_Render_to_native_surface(uosd, sfc);
			}
			template<class GraphicsMath>
			inline bool _Cairo_graphics_surfaces<GraphicsMath>::surfaces::has_size_change_callback(const unmanaged_output_surface_data_type& data) noexcept {
				return data->size_change_callback != nullptr;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::invoke_size_change_callback(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc) {
				data->size_change_callback(sfc);
			}
			template<class GraphicsMath>
			inline bool _Cairo_graphics_surfaces<GraphicsMath>::surfaces::has_user_scaling_callback(const unmanaged_output_surface_data_type& data) noexcept {
				return data->user_scaling_callback != nullptr;
			}
			template<class GraphicsMath>
			inline basic_bounding_box<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::invoke_user_scaling_callback(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc, bool& useLetterboxBrush) {
				useLetterboxBrush = false;
				return data->user_scaling_callback(sfc, useLetterboxBrush);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::display_dimensions(unmanaged_output_surface_data_type& data, const basic_display_point<GraphicsMath>& val) {
				_Ds_display_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, val);
				_Create_display_surface_and_context<GraphicsMath>(data->data);
				data->data.redraw_required = true;
				// This is unmanaged so we don't deal with resizing the user-visible output (e.g. a window).
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::flush(unmanaged_output_surface_data_type& data) {
				cairo_surface_flush(data->data.back_buffer.surface.get());
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::flush(unmanaged_output_surface_data_type& data, error_code& ec) noexcept {
				cairo_surface_flush(data->data.back_buffer.surface.get());
				ec.clear();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty(unmanaged_output_surface_data_type& data) {
				cairo_surface_mark_dirty(data->data.back_buffer.surface.get());
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty(unmanaged_output_surface_data_type& data, error_code& ec) noexcept {
				cairo_surface_mark_dirty(data->data.back_buffer.surface.get());
				ec.clear();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty(unmanaged_output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents) {
				cairo_surface_mark_dirty_rectangle(data->data.back_buffer.surface.get(), _Float_to_int(extents.x()), _Float_to_int(extents.y()), _Float_to_int(extents.width()), _Float_to_int(extents.height()));
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty(unmanaged_output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents, error_code& ec) noexcept {
				cairo_surface_mark_dirty_rectangle(data->data.back_buffer.surface.get(), _Float_to_int(extents.x()), _Float_to_int(extents.y()), _Float_to_int(extents.width()), _Float_to_int(extents.height()));
				ec.clear();
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clear(unmanaged_output_surface_data_type& data) {
				_Ds_clear<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template <class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::paint(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				_Ds_paint<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, b, bp, rp, cl);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::stroke(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_stroke_props<_Graphics_surfaces_type>& sp, const basic_dashes<_Graphics_surfaces_type>& d, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				_Ds_stroke<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, b, ip, bp, sp, d, rp, cl);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::fill(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				_Ds_fill<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, b, ip, bp, rp, cl);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mask(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush<_Graphics_surfaces_type>& mb, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_mask_props<_Graphics_surfaces_type>& mp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				_Ds_mask<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, b, mb, bp, mp, rp, cl);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_callback(unmanaged_output_surface_data_type& data, function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)> fn) {
				data->draw_callback = fn;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::size_change_callback(unmanaged_output_surface_data_type& data, function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)> fn) {
				data->size_change_callback = fn;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::user_scaling_callback(unmanaged_output_surface_data_type& data, function<basic_bounding_box<GraphicsMath>(const basic_unmanaged_output_surface<_Graphics_surfaces_type>&, bool&)> fn) {
				data->user_scaling_callback = fn;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::dimensions(unmanaged_output_surface_data_type& data, const basic_display_point<GraphicsMath>& val) {
				_Ds_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::scaling(unmanaged_output_surface_data_type& data, io2d::scaling val) {
				_Ds_scaling<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::letterbox_brush(unmanaged_output_surface_data_type& data, const optional<basic_brush<_Graphics_surfaces_type>>& val, const optional<basic_brush_props<_Graphics_surfaces_type>>& bp) noexcept {
				_Ds_letterbox_brush<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, val, bp);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::letterbox_brush_props(unmanaged_output_surface_data_type& data, const basic_brush_props<_Graphics_surfaces_type>& val) {
				_Ds_letterbox_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::auto_clear(unmanaged_output_surface_data_type& data, bool val) {
				_Ds_auto_clear<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::redraw_required(unmanaged_output_surface_data_type& data, bool val) {
				_Ds_redraw_required<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline io2d::format _Cairo_graphics_surfaces<GraphicsMath>::surfaces::format(const unmanaged_output_surface_data_type& data) noexcept {
				return _Ds_format<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline basic_display_point<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::dimensions(const unmanaged_output_surface_data_type& data) noexcept {
				return _Ds_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline basic_display_point<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::display_dimensions(const unmanaged_output_surface_data_type& data) noexcept {
				return _Ds_display_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline io2d::scaling _Cairo_graphics_surfaces<GraphicsMath>::surfaces::scaling(unmanaged_output_surface_data_type& data) noexcept {
				return _Ds_scaling<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline optional<basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::letterbox_brush(const unmanaged_output_surface_data_type& data) noexcept {
				return _Ds_letterbox_brush<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::letterbox_brush_props(const unmanaged_output_surface_data_type& data) noexcept {
				return _Ds_letterbox_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline bool _Cairo_graphics_surfaces<GraphicsMath>::surfaces::auto_clear(const unmanaged_output_surface_data_type& data) noexcept {
				return _Ds_auto_clear<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline bool _Cairo_graphics_surfaces<GraphicsMath>::surfaces::redraw_required(const unmanaged_output_surface_data_type& data) noexcept {
				return _Ds_redraw_required<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
		}
	}
}
