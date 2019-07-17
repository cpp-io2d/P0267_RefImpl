#pragma once

#ifndef _XQT_IO2D_RASTER_WINDOW_IMPL_H_
#define _XQT_IO2D_RASTER_WINDOW_IMPL_H_

#include "xqt_headers.h"
#include "xqt.h"
#include "xqt_surfaces_impl.h"
#include "xio2d_qt_win32_output_surface.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Qt_io2d {
			template<class GraphicsMath>
			inline _Qt_graphics_surfaces<GraphicsMath>::_Qt_io2d_raster_window::_Qt_io2d_raster_window(QWindow* parent, typename _Qt_graphics_surfaces<GraphicsMath>::surfaces::output_surface_data_type& osd, basic_output_surface<_Qt_graphics_surfaces<GraphicsMath>>& sfc) :
				QWindow(parent),
				_Backing_store(make_unique<QBackingStore>(this)),
				_Osd(osd),
				_Sfc(sfc),
				_Last_redraw_time() {
				setGeometry(100, 100, _Osd->data.display_dimensions.x(), _Osd->data.display_dimensions.y());
			}

			//template<class GraphicsMath>
			//inline void _Qt_graphics_surfaces<GraphicsMath>::_Qt_io2d_raster_window::surface(basic_output_surface<_Qt_graphics_surfaces<GraphicsMath>>& sfc) {
			//	_Sfc = sfc;
			//}
			template<class GraphicsMath>
			inline int _Qt_graphics_surfaces<GraphicsMath>::_Qt_io2d_raster_window::begin_show() {
				// Qt event loop goes here?
				auto& data = _Osd->data;
				_Last_redraw_time = ::std::chrono::steady_clock::now();
				data.elapsed_draw_time = 0.0f;
				resize(data.display_dimensions.x(), data.display_dimensions.y());
				startTimer(1, Qt::PreciseTimer);
				show();
				return data.gui_app->exec();
			}

			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::_Qt_io2d_raster_window::render() {
				_Last_redraw_time = ::std::chrono::steady_clock::now();
				if (!isExposed()) {
					return;
				}
				if (_Osd->data.auto_clear) {
					_Sfc.get().clear();
				}
				if (_Osd->draw_callback != nullptr) {
					_Osd->draw_callback(_Sfc);
				}
				_Process_command_list_output_surface<GraphicsMath>(_Sfc, begin(_Osd->commands), end(_Osd->commands));
				if (_Osd->old_commands.empty() == false) {
					_Osd->old_commands.clear();
				}
				// Now we need to draw this to the display.
				_Qt_graphics_surfaces<GraphicsMath>::surfaces::_Render_to_native_surface(_Osd, _Sfc.get());
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::_Qt_io2d_raster_window::end_show() {
				killTimer();
				_Osd->data.gui_app->exit(0);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::_Qt_io2d_raster_window::resize_back_buffer(const basic_display_point<GraphicsMath>& val) {
				auto replacementBackBuffer = _Osd->data.back_buffer.surface.scaled(val.x(), val.y());
				_Osd->data.back_buffer.surface = replacementBackBuffer;
				_Osd->data.back_buffer.dimensions = val;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::_Qt_io2d_raster_window::display_dimensions(const basic_display_point<GraphicsMath>& val) {
				_Backing_store->resize(QSize(val.x(), val.y()));
				//resize(val.x(), val.y());
				_Osd->data.redraw_required = true;
			}
			template<class GraphicsMath>
			inline QBackingStore* _Qt_graphics_surfaces<GraphicsMath>::_Qt_io2d_raster_window::backing_store() noexcept {
				return _Backing_store.get();
			}
			template<class GraphicsMath>
			inline bool _Qt_graphics_surfaces<GraphicsMath>::_Qt_io2d_raster_window::event(QEvent* ev) {
				if (ev->type() == QEvent::UpdateRequest) {
					render();
					// per documentation: https://doc.qt.io/qt-5/qwindow.html#requestUpdate
					return QWindow::event(ev);
				}
				return QWindow::event(ev);
			}

			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::_Qt_io2d_raster_window::timerEvent(QTimerEvent* /*ev*/) {
				bool redraw = true;
				auto currentTime = ::std::chrono::steady_clock::now();
				auto elapsedTimeIncrement = static_cast<float>(::std::chrono::duration_cast<::std::chrono::nanoseconds>(currentTime - _Last_redraw_time).count());
				auto& data = _Osd->data;
				data.elapsed_draw_time += elapsedTimeIncrement;
				if (data.rr == io2d::refresh_style::as_needed) {
					redraw = data.redraw_required;
					data.redraw_required = false;
				}
				const auto desiredElapsed = 1'000'000'000.0F / data.refresh_fps;
				if (data.rr == io2d::refresh_style::fixed) {
					// desiredElapsed is the amount of time, in nanoseconds, that must have passed before we should redraw.
					redraw = data.elapsed_draw_time >= desiredElapsed;
				}
				if (redraw) {
					requestUpdate();
					if (data.rr == experimental::io2d::refresh_style::fixed) {
						while (data.elapsed_draw_time >= desiredElapsed) {
							data.elapsed_draw_time -= desiredElapsed;
						}
					}
					else {
						data.elapsed_draw_time = 0.0F;
					}
				}
			}

			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::_Qt_io2d_raster_window::showEvent(QShowEvent* /*ev*/) {
				setWidth(_Osd->data.display_dimensions.x());
				setHeight(_Osd->data.display_dimensions.y());
			}

			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::_Qt_io2d_raster_window::resizeEvent(QResizeEvent* ev) {
				if (_Osd->size_change_callback != nullptr) {
					_Osd->size_change_callback(_Sfc);
				}
				_Backing_store->resize(ev->size());
			}

			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::_Qt_io2d_raster_window::exposeEvent(QExposeEvent* /*ev*/) {
				render();
			}
		}
	}
}

#endif
