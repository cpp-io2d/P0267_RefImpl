#pragma once
#ifndef _XIO2D_QT_WIN32_OUTPUT_SURFACE_H_
#define _XIO2D_QT_WIN32_OUTPUT_SURFACE_H_

#include "xqt_surfaces_impl.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Qt_io2d {
			// output surface functions

			template<class GraphicsMath>
			struct _Qt_graphics_surfaces<GraphicsMath>::surfaces::_Display_surface_data_type {
				bool unmanaged = false;
				bool letterbox_brush_is_default = true;
				optional<basic_brush<_Graphics_surfaces_type>> _Letterbox_brush;
				optional<basic_brush_props<_Graphics_surfaces_type>> _Letterbox_brush_props;

				optional<basic_brush<_Graphics_surfaces_type>> _Default_letterbox_brush;

				basic_display_point<GraphicsMath> display_dimensions;
				::std::unique_ptr<QGuiApplication> gui_app;
				::std::unique_ptr<_Qt_io2d_raster_window> raster_window;

				image_surface_data_type back_buffer;

				bool auto_clear = false;
				io2d::scaling scl = io2d::scaling::letterbox;
				io2d::refresh_style rr = io2d::refresh_style::as_fast_as_possible;
				float refresh_fps = 30.0f;
				bool redraw_required = false;
				float elapsed_draw_time = 0.0f;
			};

			void _Qt_gui_app_init(::std::unique_ptr<QGuiApplication>& gui_app);

			template<class GraphicsMath>
			struct _Qt_graphics_surfaces<GraphicsMath>::surfaces::_Output_surface_data {
				_Display_surface_data_type data;
				::std::vector<typename basic_commands<typename _Qt_graphics_surfaces<GraphicsMath>::graphics_surfaces_type>::command_item> commands;
				::std::vector<typename basic_commands<typename _Qt_graphics_surfaces<GraphicsMath>::graphics_surfaces_type>::command_item> old_commands;
				::std::function<void(basic_output_surface<_Graphics_surfaces_type>&)> draw_callback;
				::std::function<void(basic_output_surface<_Graphics_surfaces_type>&)> size_change_callback;
				::std::function<basic_bounding_box<GraphicsMath>(const basic_output_surface<_Graphics_surfaces_type>&, bool&)> user_scaling_callback;
			};

			template<class GraphicsMath>
			struct _Qt_graphics_surfaces<GraphicsMath>::surfaces::_Unmanaged_output_surface_data {
				_Display_surface_data_type data;
				::std::vector<typename basic_commands<typename _Qt_graphics_surfaces<GraphicsMath>::graphics_surfaces_type>::command_item> commands;
				::std::vector<typename basic_commands<typename _Qt_graphics_surfaces<GraphicsMath>::graphics_surfaces_type>::command_item> old_commands;
				::std::function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)> draw_callback;
				::std::function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)> size_change_callback;
				::std::function<basic_bounding_box<GraphicsMath>(const basic_unmanaged_output_surface<_Graphics_surfaces_type>&, bool&)> user_scaling_callback;
			};

			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::surfaces::output_surface_data_type _Qt_graphics_surfaces<GraphicsMath>::surfaces::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, io2d::scaling scl, io2d::refresh_style rr, float fps) {
				auto result = make_unique<_Output_surface_data>();
				_Display_surface_data_type& data = result->data;
				_Qt_gui_app_init(data.gui_app);
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
			inline typename _Qt_graphics_surfaces<GraphicsMath>::surfaces::output_surface_data_type _Qt_graphics_surfaces<GraphicsMath>::surfaces::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, error_code& ec, io2d::scaling scl, io2d::refresh_style rr, float fps) noexcept {
				auto result = make_unique<_Output_surface_data>();
				_Display_surface_data_type& data = result->data;
				_Qt_gui_app_init(data.gui_app);
				data.display_dimensions.x(preferredWidth);
				data.display_dimensions.y(preferredHeight);
				data.rr = rr;
				data.refresh_style = fps;
				data.scl = scl;
				data.back_buffer = ::std::move(create_image_surface(preferredFormat, preferredWidth, preferredHeight));
				//data.back_buffer.format = preferredFormat;
				//data.back_buffer.dimensions.x(preferredWidth);
				//data.back_buffer.dimensions.y(preferredHeight);
				ec.clear();
				return result.release();
			}
			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::surfaces::output_surface_data_type _Qt_graphics_surfaces<GraphicsMath>::surfaces::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, io2d::scaling scl, io2d::refresh_style rr, float fps) {
				auto result = make_unique<_Output_surface_data>();
				_Display_surface_data_type& data = result->data;
				_Qt_gui_app_init(data.gui_app);
				data.display_dimensions.x(preferredDisplayWidth);
				data.display_dimensions.y(preferredDisplayHeight);
				data.rr = rr;
				data.refresh_style = fps;
				data.scl = scl;
				data.back_buffer = ::std::move(create_image_surface(preferredFormat, preferredWidth, preferredHeight));
				//data.back_buffer.format = preferredFormat;
				//data.back_buffer.dimensions.x(preferredWidth);
				//data.back_buffer.dimensions.y(preferredHeight);
				return result.release();
			}
			template <class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::surfaces::output_surface_data_type _Qt_graphics_surfaces<GraphicsMath>::surfaces::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, error_code& ec, io2d::scaling scl, io2d::refresh_style rr, float fps) noexcept {
				auto result = make_unique<_Output_surface_data>();
				_Display_surface_data_type& data = result->data;
				_Qt_gui_app_init(data.gui_app);
				data.display_dimensions.x(preferredDisplayWidth);
				data.display_dimensions.y(preferredDisplayHeight);
				data.rr = rr;
				data.refresh_style = fps;
				data.scl = scl;
				data.back_buffer = ::std::move(create_image_surface(preferredFormat, preferredWidth, preferredHeight));
				//data.back_buffer.format = preferredFormat;
				//data.back_buffer.dimensions.x(preferredWidth);
				//data.back_buffer.dimensions.y(preferredHeight);
				ec.clear();
				return result.release();
			}
			template <class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::surfaces::output_surface_data_type _Qt_graphics_surfaces<GraphicsMath>::surfaces::move_output_surface(output_surface_data_type&& data) noexcept {
				auto result = data;
				data = nullptr;
				return result;
			}
			template <class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::destroy(output_surface_data_type& data) noexcept {
				destroy(data->data.back_buffer);
				delete data;
			}

			template<class GraphicsMath>
			inline int _Qt_graphics_surfaces<GraphicsMath>::surfaces::begin_show(output_surface_data_type& osd, basic_output_surface<_Qt_graphics_surfaces<GraphicsMath>>* /*instance*/, basic_output_surface<_Qt_graphics_surfaces<GraphicsMath>>& sfc) {
				_Display_surface_data_type& data = osd->data;

				data.raster_window = make_unique<_Qt_io2d_raster_window>(nullptr, osd, sfc);
				//data.raster_window->surface(sfc);

				data._Default_letterbox_brush = basic_brush<_Qt_graphics_surfaces>(rgba_color::black);
				data._Letterbox_brush = data._Default_letterbox_brush;

				data.back_buffer = ::std::move(create_image_surface(data.back_buffer.format, data.back_buffer.dimensions.x(), data.back_buffer.dimensions.y()));

				return data.raster_window->begin_show();
			}


			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::end_show(output_surface_data_type& data) {
				data.raster_window->end_show();
			}

			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::display_dimensions(output_surface_data_type& datap, const basic_display_point<GraphicsMath>& val) {
				//auto& data = *datap;
				datap->data.raster_window->display_dimensions(val);

				//data.data.display_dimensions = val;
				//if (data.data.hwnd != 0) {
				//	// Change window size then call _Ds_display_dimensions, I think.
				//	RECT clientRect;
				//	RECT windowRect;
				//	GetWindowRect(data.data.hwnd, &windowRect);
				//	GetClientRect(data.data.hwnd, &clientRect);
				//	auto crWidth = clientRect.right - clientRect.left;
				//	auto crHeight = clientRect.bottom - clientRect.top;
				//	auto wrWidth = windowRect.right - windowRect.left;
				//	auto wrHeight = windowRect.bottom - windowRect.top;
				//	auto displayWidth = val.x();
				//	auto displayHeight = val.y();
				//	if (crWidth != displayWidth || crHeight != displayHeight) {
				//		auto width = std::max((wrWidth - crWidth) + 1L, (displayWidth - crWidth) + wrWidth);
				//		auto height = std::max((wrHeight - crHeight) + 1L, (displayHeight - crHeight) + wrHeight);
				//		// Resize the window.
				//		if (!SetWindowPos(data.data.hwnd, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS)) {
				//			_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to SetWindowPos.");
				//		}

				//		if (!PostMessageW(data.data.hwnd, WM_PAINT, static_cast<WPARAM>(0), static_cast<LPARAM>(0))) {
				//			_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to PostMessageW.");
				//		}
				//	}
				//}
				////_Ds_display_dimensions<_Qt_graphics_surfaces<GraphicsMath>>(data.data, val);

				data.data.redraw_required = true;
			}

			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::refresh_style(output_surface_data_type& data, io2d::refresh_style val) {
				data->data.rr = val;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::desired_frame_rate(output_surface_data_type& data, float val) {
				const float oneFramePerHour = 1.0f / (60.0f * 60.0f); // If you need a lower framerate than this, use as_needed and control the refresh by writing a timer that will trigger a refresh at your desired interval.
				const float maxFPS = 120.0f; // It's unlikely to find a display output that operates higher than this.
				data->data.refresh_fps = ::std::min(::std::max(val, oneFramePerHour), maxFPS);
			}
			template<class GraphicsMath>
			inline io2d::refresh_style _Qt_graphics_surfaces<GraphicsMath>::surfaces::refresh_style(const output_surface_data_type& data) noexcept {
				return data->data.rr;
			}
			template<class GraphicsMath>
			inline float _Qt_graphics_surfaces<GraphicsMath>::surfaces::desired_frame_rate(const output_surface_data_type& data) noexcept {
				return data->data.refresh_fps;
			}

			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::clear(output_surface_data_type& data) {
				_Ds_clear<_Qt_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template <class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::paint(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				_Ds_paint<_Qt_graphics_surfaces<GraphicsMath>>(data->data, b, bp, rp, cl);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::stroke(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_stroke_props<_Graphics_surfaces_type>& sp, const basic_dashes<_Graphics_surfaces_type>& d, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				_Ds_stroke<_Qt_graphics_surfaces<GraphicsMath>>(data->data, b, ip, bp, sp, d, rp, cl);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::fill(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				_Ds_fill<_Qt_graphics_surfaces<GraphicsMath>>(data->data, b, ip, bp, rp, cl);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::mask(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush<_Graphics_surfaces_type>& mb, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_mask_props<_Graphics_surfaces_type>& mp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				_Ds_mask<_Qt_graphics_surfaces<GraphicsMath>>(data->data, b, mb, bp, mp, rp, cl);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::draw_text(output_surface_data_type& data, const basic_point_2d<GraphicsMath>& pt, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& font, const string& text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) {
				_Ds_draw_text<_Qt_graphics_surfaces<GraphicsMath>>(data->data, pt, b, font, text, tp, bp, sp, d, rp, cl);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::draw_text(output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& bb, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& font, const string& text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) {
				_Ds_draw_text<_Qt_graphics_surfaces<GraphicsMath>>(data->data, bb, b, font, text, tp, bp, sp, d, rp, cl);
			}

			template<class GraphicsMath>
			template<class InputIterator>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::command_list(output_surface_data_type& data, basic_output_surface<graphics_surfaces_type>& sfc, InputIterator first, InputIterator last) {
				// This prevents iterator invalidation such that the command list can be changed within the command list using run_function. It can only be changed once though.
				if (data->old_commands.empty() == false) {
					throw ::std::logic_error("Attempted to change the command list more than once during command list processing.");
				}
				data->old_commands.insert(data->commands.end(), first, last);
				::std::swap(data->commands, data->old_commands);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::draw_callback(output_surface_data_type& data, function<void(basic_output_surface<_Graphics_surfaces_type>&)> fn) {
				data->draw_callback = fn;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::size_change_callback(output_surface_data_type& data, function<void(basic_output_surface<_Graphics_surfaces_type>&)> fn) {
				data->size_change_callback = fn;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::user_scaling_callback(output_surface_data_type& data, function<basic_bounding_box<GraphicsMath>(const basic_output_surface<_Graphics_surfaces_type>&, bool&)> fn) {
				data->user_scaling_callback = fn;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::dimensions(output_surface_data_type& data, const basic_display_point<GraphicsMath>& val) {
				_Ds_dimensions<_Qt_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::scaling(output_surface_data_type& data, io2d::scaling val) {
				_Ds_scaling<_Qt_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::letterbox_brush(output_surface_data_type& data, const optional<basic_brush<_Graphics_surfaces_type>>& val, const optional<basic_brush_props<_Graphics_surfaces_type>>& bp) noexcept {
				_Ds_letterbox_brush<_Qt_graphics_surfaces<GraphicsMath>>(data->data, val, bp);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::letterbox_brush_props(output_surface_data_type& data, const basic_brush_props<_Graphics_surfaces_type>& val) {
				_Ds_letterbox_brush_props<_Qt_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::auto_clear(output_surface_data_type& data, bool val) {
				_Ds_auto_clear<_Qt_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::redraw_required(output_surface_data_type& data, bool val) {
				_Ds_redraw_required<_Qt_graphics_surfaces<GraphicsMath>>(data->data, val);
			}
			template<class GraphicsMath>
			inline io2d::format _Qt_graphics_surfaces<GraphicsMath>::surfaces::format(const output_surface_data_type& data) noexcept {
				return _Ds_format<_Qt_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline basic_display_point<GraphicsMath> _Qt_graphics_surfaces<GraphicsMath>::surfaces::dimensions(const output_surface_data_type& data) noexcept {
				return _Ds_dimensions<_Qt_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline basic_display_point<GraphicsMath> _Qt_graphics_surfaces<GraphicsMath>::surfaces::display_dimensions(const output_surface_data_type& data) noexcept {
				return _Ds_display_dimensions<_Qt_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline io2d::scaling _Qt_graphics_surfaces<GraphicsMath>::surfaces::scaling(output_surface_data_type& data) noexcept {
				return _Ds_scaling<_Qt_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline optional<basic_brush<_Qt_graphics_surfaces<GraphicsMath>>> _Qt_graphics_surfaces<GraphicsMath>::surfaces::letterbox_brush(const output_surface_data_type& data) noexcept {
				return _Ds_letterbox_brush<_Qt_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline basic_brush_props<_Qt_graphics_surfaces<GraphicsMath>> _Qt_graphics_surfaces<GraphicsMath>::surfaces::letterbox_brush_props(const output_surface_data_type& data) noexcept {
				return _Ds_letterbox_brush_props<_Qt_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline bool _Qt_graphics_surfaces<GraphicsMath>::surfaces::auto_clear(const output_surface_data_type& data) noexcept {
				return _Ds_auto_clear<_Qt_graphics_surfaces<GraphicsMath>>(data->data);
			}
			template<class GraphicsMath>
			inline bool _Qt_graphics_surfaces<GraphicsMath>::surfaces::redraw_required(const output_surface_data_type& data) noexcept {
				return _Ds_redraw_required<_Qt_graphics_surfaces<GraphicsMath>>(data->data);
			}
		}
	}
}
#endif
