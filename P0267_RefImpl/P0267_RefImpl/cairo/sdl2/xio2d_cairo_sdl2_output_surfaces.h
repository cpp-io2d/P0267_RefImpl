#pragma once
#include "xcairo_surfaces_impl.h"
#include <cstdio>
#include <SDL.h>

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Cairo {
			// output surface functions

			template<class GraphicsMath>
			struct _Cairo_graphics_surfaces<GraphicsMath>::surfaces::_Display_surface_data_type {
				// HINSTANCE hInstance = nullptr;
				// HWND hwnd = nullptr;
				// HDC hdc = nullptr;
				// bool hasOwnDC = true;
				SDL_Window * window = nullptr;
				SDL_Renderer * renderer = nullptr;
				SDL_Texture * texture = nullptr;

				bool unmanaged = false;
				bool letterbox_brush_is_default = true;
				optional<basic_brush<_Graphics_surfaces_type>> _Letterbox_brush;
				optional<basic_brush_props<_Graphics_surfaces_type>> _Letterbox_brush_props;

				optional<basic_brush<_Graphics_surfaces_type>> _Default_letterbox_brush;

				basic_display_point<GraphicsMath> display_dimensions;
				::std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> display_surface{ nullptr, &cairo_surface_destroy };
				::std::unique_ptr<cairo_t, decltype(&cairo_destroy)> display_context{ nullptr, &cairo_destroy };

				image_surface_data_type back_buffer;

				bool auto_clear = false;
				io2d::scaling scl = io2d::scaling::letterbox;
				io2d::refresh_style rr = io2d::refresh_style::as_fast_as_possible;
				float refresh_fps = 30.0f;
				bool redraw_required = false;
				float elapsed_draw_time = 0.0f;
				std::chrono::time_point<std::chrono::steady_clock> previous_time;
			};
			
			template<class GraphicsMath>
			struct _Cairo_graphics_surfaces<GraphicsMath>::surfaces::_Output_surface_data {
				_Display_surface_data_type data;
				::std::function<void(basic_output_surface<_Graphics_surfaces_type>&)> draw_callback;
				::std::function<void(basic_output_surface<_Graphics_surfaces_type>&)> size_change_callback;
				::std::function<basic_bounding_box<GraphicsMath>(const basic_output_surface<_Graphics_surfaces_type>&, bool&)> user_scaling_callback;
			};

			template<class GraphicsMath>
			struct _Cairo_graphics_surfaces<GraphicsMath>::surfaces::_Unmanaged_output_surface_data {
				_Display_surface_data_type data;
				::std::function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)> draw_callback;
				::std::function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)> size_change_callback;
				::std::function<basic_bounding_box<GraphicsMath>(const basic_unmanaged_output_surface<_Graphics_surfaces_type>&, bool&)> user_scaling_callback;
			};

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, io2d::scaling scl, io2d::refresh_style rr, float fps) {
				auto result = make_unique<_Output_surface_data>();
				_Display_surface_data_type& data = result->data;
				data.display_dimensions.x(preferredWidth);
				data.display_dimensions.y(preferredHeight);
				data.rr = rr;
				data.refresh_fps = fps;
				data.scl = scl;
				data.back_buffer.format = preferredFormat;
				data.back_buffer.dimensions.x(preferredWidth);
				data.back_buffer.dimensions.y(preferredHeight);
				return result.release();
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, error_code& ec, io2d::scaling scl, io2d::refresh_style rr, float fps) noexcept {
				auto result = make_unique<_Output_surface_data>();
				_Display_surface_data_type& data = result->data;
				data.display_dimensions.x(preferredWidth);
				data.display_dimensions.y(preferredHeight);
				data.rr = rr;
				data.refresh_style = fps;
				data.scl = scl;
				data.back_buffer.format = preferredFormat;
				data.back_buffer.dimensions.x(preferredWidth);
				data.back_buffer.dimensions.y(preferredHeight);
				ec.clear();
				return result.release();
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, io2d::scaling scl, io2d::refresh_style rr, float fps) {
				auto result = make_unique<_Output_surface_data>();
				_Display_surface_data_type& data = result->data;
				data.display_dimensions.x(preferredDisplayWidth);
				data.display_dimensions.y(preferredDisplayHeight);
				data.rr = rr;
				data.refresh_style = fps;
				data.scl = scl;
				data.back_buffer.format = preferredFormat;
				data.back_buffer.dimensions.x(preferredWidth);
				data.back_buffer.dimensions.y(preferredHeight);
				return result.release();
			}
			template <class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, error_code& ec, io2d::scaling scl, io2d::refresh_style rr, float fps) noexcept {
				auto result = make_unique<_Output_surface_data>();
				_Display_surface_data_type& data = result->data;
				data.display_dimensions.x(preferredDisplayWidth);
				data.display_dimensions.y(preferredDisplayHeight);
				data.rr = rr;
				data.refresh_style = fps;
				data.scl = scl;
				data.back_buffer.format = preferredFormat;
				data.back_buffer.dimensions.x(preferredWidth);
				data.back_buffer.dimensions.y(preferredHeight);
				ec.clear();
				return result.release();
			}
			template <class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::move_output_surface(output_surface_data_type&& data) noexcept {
				auto result = data;
				data = nullptr;
				return result;
			}
			template <class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::destroy(output_surface_data_type& data) noexcept {
				destroy(data->data.back_buffer);
				delete data;
			}

			template <class GraphicsMath>
			bool _Is_active(typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::_Display_surface_data_type& data) noexcept;

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::end_show(output_surface_data_type& data) {
				printf("IMPLEMENT ME: %s\n", __PRETTY_FUNCTION__);
				// if (data.renderer) {
				// 	SDL_DestroyRenderer(data.renderer);
				// 	data.renderer = nullptr;
				// }
				// if (data.window) {
				// 	SDL_DestroyWindow(data.window);
				// 	data.window = nullptr;
				// }
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::display_dimensions(output_surface_data_type& datap, const basic_display_point<GraphicsMath>& val) {
				auto &data = *datap;
				data.data.display_dimensions = val;
				printf("IMPLEMENT ME: %s\n", __PRETTY_FUNCTION__);

				// if (data.data.hwnd != 0) {
				// 	// Change window size then call _Ds_display_dimensions, I think.
				// 	RECT clientRect;
				// 	RECT windowRect;
				// 	GetWindowRect(data.data.hwnd, &windowRect);
				// 	GetClientRect(data.data.hwnd, &clientRect);
				// 	auto crWidth = clientRect.right - clientRect.left;
				// 	auto crHeight = clientRect.bottom - clientRect.top;
				// 	auto wrWidth = windowRect.right - windowRect.left;
				// 	auto wrHeight = windowRect.bottom - windowRect.top;
				// 	auto displayWidth = val.x();
				// 	auto displayHeight = val.y();
				// 	if (crWidth != displayWidth || crHeight != displayHeight) {
				// 		auto width = std::max((wrWidth - crWidth) + 1L, (displayWidth - crWidth) + wrWidth);
				// 		auto height = std::max((wrHeight - crHeight) + 1L, (displayHeight - crHeight) + wrHeight);
				// 		// Resize the window.
				// 		if (!SetWindowPos(data.data.hwnd, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS)) {
				// 			_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to SetWindowPos.");
				// 		}

				// 		if (!PostMessageW(data.data.hwnd, WM_PAINT, static_cast<WPARAM>(0), static_cast<LPARAM>(0))) {
				// 			_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to PostMessageW.");
				// 		}
				// 	}
				// }
				// //_Ds_display_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val);
				_Create_display_surface_and_context<GraphicsMath>(data.data);
				data.data.redraw_required = true;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::refresh_style(output_surface_data_type& data, io2d::refresh_style val) {
				data->data.rr = val;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::desired_frame_rate(output_surface_data_type& data, float val) {
				const float oneFramePerHour = 1.0f / (60.0f * 60.0f); // If you need a lower framerate than this, use as_needed and control the refresh by writing a timer that will trigger a refresh at your desired interval.
				const float maxFPS = 120.0f; // It's unlikely to find a display output that operates higher than this.
				data->data.refresh_fps = ::std::min(::std::max(val, oneFramePerHour), maxFPS);
			}
			template<class GraphicsMath>
			inline io2d::refresh_style _Cairo_graphics_surfaces<GraphicsMath>::surfaces::refresh_style(const output_surface_data_type& data) noexcept {
				return data->data.rr;
			}
			template<class GraphicsMath>
			inline float _Cairo_graphics_surfaces<GraphicsMath>::surfaces::desired_frame_rate(const output_surface_data_type& data) noexcept {
				return data->data.refresh_fps;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::flush(output_surface_data_type& data) {
				cairo_surface_flush(data->data.back_buffer.surface.get());
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::flush(output_surface_data_type& data, error_code& ec) noexcept {
				cairo_surface_flush(data->data.back_buffer.surface.get());
				ec.clear();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty(output_surface_data_type& data) {
				cairo_surface_mark_dirty(data->data.back_buffer.surface.get());
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty(output_surface_data_type& data, error_code& ec) noexcept {
				cairo_surface_mark_dirty(data->data.back_buffer.surface.get());
				ec.clear();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty(output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents) {
				cairo_surface_mark_dirty_rectangle(data->data.back_buffer.surface.get(), _Float_to_int(extents.x()), _Float_to_int(extents.y()), _Float_to_int(extents.width()), _Float_to_int(extents.height()));
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty(output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents, error_code& ec) noexcept {
				cairo_surface_mark_dirty_rectangle(data->data.back_buffer.surface.get(), _Float_to_int(extents.x()), _Float_to_int(extents.y()), _Float_to_int(extents.width()), _Float_to_int(extents.height()));
				ec.clear();
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clear(output_surface_data_type& data) {
				_Ds_clear<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template <class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::paint(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				_Ds_paint<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, b, bp, rp, cl);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::stroke(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_stroke_props<_Graphics_surfaces_type>& sp, const basic_dashes<_Graphics_surfaces_type>& d, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				_Ds_stroke<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, b, ip, bp, sp, d, rp, cl);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::fill(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				_Ds_fill<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, b, ip, bp, rp, cl);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mask(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush<_Graphics_surfaces_type>& mb, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_mask_props<_Graphics_surfaces_type>& mp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				_Ds_mask<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, b, mb, bp, mp, rp, cl);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_callback(output_surface_data_type& data, function<void(basic_output_surface<_Graphics_surfaces_type>&)> fn) {
				data->draw_callback = fn;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::size_change_callback(output_surface_data_type& data, function<void(basic_output_surface<_Graphics_surfaces_type>&)> fn) {
				data->size_change_callback = fn;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::user_scaling_callback(output_surface_data_type& data, function<basic_bounding_box<GraphicsMath>(const basic_output_surface<_Graphics_surfaces_type>&, bool&)> fn) {
				data->user_scaling_callback = fn;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::dimensions(output_surface_data_type& data, const basic_display_point<GraphicsMath>& val) {
				_Ds_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::scaling(output_surface_data_type& data, io2d::scaling val) {
				_Ds_scaling<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::letterbox_brush(output_surface_data_type& data, const optional<basic_brush<_Graphics_surfaces_type>>& val, const optional<basic_brush_props<_Graphics_surfaces_type>>& bp) noexcept {
				_Ds_letterbox_brush<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, val, bp);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::letterbox_brush_props(output_surface_data_type& data, const basic_brush_props<_Graphics_surfaces_type>& val) {
				_Ds_letterbox_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::auto_clear(output_surface_data_type& data, bool val) {
				_Ds_auto_clear<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::redraw_required(output_surface_data_type& data, bool val) {
				_Ds_redraw_required<_Cairo_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline io2d::format _Cairo_graphics_surfaces<GraphicsMath>::surfaces::format(const output_surface_data_type& data) noexcept {
				return _Ds_format<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline basic_display_point<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::dimensions(const output_surface_data_type& data) noexcept {
				return _Ds_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline basic_display_point<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::display_dimensions(const output_surface_data_type& data) noexcept {
				return _Ds_display_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline io2d::scaling _Cairo_graphics_surfaces<GraphicsMath>::surfaces::scaling(output_surface_data_type& data) noexcept {
				return _Ds_scaling<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline optional<basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::letterbox_brush(const output_surface_data_type& data) noexcept {
				return _Ds_letterbox_brush<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::letterbox_brush_props(const output_surface_data_type& data) noexcept {
				return _Ds_letterbox_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline bool _Cairo_graphics_surfaces<GraphicsMath>::surfaces::auto_clear(const output_surface_data_type& data) noexcept {
				return _Ds_auto_clear<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline bool _Cairo_graphics_surfaces<GraphicsMath>::surfaces::redraw_required(const output_surface_data_type& data) noexcept {
				return _Ds_redraw_required<_Cairo_graphics_surfaces<GraphicsMath>>(data->data);
			}
		}
	}
}
