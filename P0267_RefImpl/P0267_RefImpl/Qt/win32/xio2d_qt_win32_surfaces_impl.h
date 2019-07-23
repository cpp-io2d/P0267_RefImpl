#pragma once

#ifndef _XIO2D_QT_WIN32_SURFACES_IMPL_H_
#define _XIO2D_QT_WIN32_SURFACES_IMPL_H_

#include "xqt_headers.h"
#include "xio2d_qt_win32_surfaces.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Qt_io2d {
			template <class GraphicsSurfaces>
			inline void _Ds_clear(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) {
				GraphicsSurfaces::surfaces::clear(data.back_buffer);
			}
			template <class GraphicsSurfaces>
			inline void _Ds_paint(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_brush<GraphicsSurfaces>& b, const basic_brush_props<GraphicsSurfaces>& bp, const basic_render_props<GraphicsSurfaces>& rp, const basic_clip_props<GraphicsSurfaces>& cl) {
				GraphicsSurfaces::surfaces::paint(data.back_buffer, b, bp, rp, cl);
			}
			template <class GraphicsSurfaces>
			inline void _Ds_stroke(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const basic_brush_props<GraphicsSurfaces>& bp, const basic_stroke_props<GraphicsSurfaces>& sp, const basic_dashes<GraphicsSurfaces>& d, const basic_render_props<GraphicsSurfaces>& rp, const basic_clip_props<GraphicsSurfaces>& cl) {
				GraphicsSurfaces::surfaces::stroke(data.back_buffer, b, ip, bp, sp, d, rp, cl);
			}
			template <class GraphicsSurfaces>
			inline void _Ds_fill(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const basic_brush_props<GraphicsSurfaces>& bp, const basic_render_props<GraphicsSurfaces>& rp, const basic_clip_props<GraphicsSurfaces>& cl) {
				GraphicsSurfaces::surfaces::fill(data.back_buffer, b, ip, bp, rp, cl);
			}
			template <class GraphicsSurfaces>
			inline void _Ds_mask(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const basic_brush_props<GraphicsSurfaces>& bp, const basic_mask_props<GraphicsSurfaces>& mp, const basic_render_props<GraphicsSurfaces>& rp, const basic_clip_props<GraphicsSurfaces>& cl) {
				GraphicsSurfaces::surfaces::mask(data.back_buffer, b, mb, bp, mp, rp, cl);
			}
			template<class GraphicsSurfaces>
			void _Ds_draw_text(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const basic_text_props<GraphicsSurfaces>& tp, const basic_brush_props<GraphicsSurfaces>& bp, const basic_stroke_props<GraphicsSurfaces>& sp, const basic_dashes<GraphicsSurfaces>& d, const basic_render_props<GraphicsSurfaces>& rp, const basic_clip_props<GraphicsSurfaces>& cl) {
				GraphicsSurfaces::surfaces::draw_text(data.back_buffer, pt, b, font, text, tp, bp, sp, d, rp, cl);
			}
			template<class GraphicsSurfaces>
			void _Ds_draw_text(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_bounding_box<typename GraphicsSurfaces::graphics_math_type>& bb, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const basic_text_props<GraphicsSurfaces>& tp, const basic_brush_props<GraphicsSurfaces>& bp, const basic_stroke_props<GraphicsSurfaces>& sp, const basic_dashes<GraphicsSurfaces>& d, const basic_render_props<GraphicsSurfaces>& rp, const basic_clip_props<GraphicsSurfaces>& cl) {
				GraphicsSurfaces::surfaces::draw_text(data.back_buffer, bb, b, font, text, tp, bp, sp, d, rp, cl);
			}
			template <class GraphicsSurfaces>
			inline void _Ds_dimensions(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_display_point<typename GraphicsSurfaces::graphics_math_type>& val) {
				if (val != data.back_buffer.dimensions) {
					// Recreate the render target that is drawn to the displayed surface
					data.back_buffer = ::std::move(GraphicsSurfaces::surfaces::create_image_surface(data.back_buffer.format, val.x(), val.y()));
				}
			}
			template <class GraphicsSurfaces>
			inline void _Ds_display_dimensions(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_display_point<typename GraphicsSurfaces::graphics_math_type>& val) {
				data.display_dimensions = val;
			}
			template <class GraphicsSurfaces>
			inline void _Ds_scaling(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, io2d::scaling val) {
				data.scl = val;
			}
			template <class GraphicsSurfaces>
			inline void _Ds_letterbox_brush(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const optional<basic_brush<GraphicsSurfaces>>& val, const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept {
				data.letterbox_brush_is_default = !val.has_value();
				data._Letterbox_brush = (val.has_value() ? val.value() : data._Default_letterbox_brush);
				data._Letterbox_brush_props = (bp.has_value() ? bp.value() : basic_brush_props<GraphicsSurfaces>());

			}
			template <class GraphicsSurfaces>
			inline void _Ds_letterbox_brush_props(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, const basic_brush_props<GraphicsSurfaces>& val) {
				data._Letterbox_brush_props = val;
			}
			template <class GraphicsSurfaces>
			inline void _Ds_auto_clear(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, bool val) {
				data.auto_clear = val;
			}
			template <class GraphicsSurfaces>
			inline void _Ds_redraw_required(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data, bool val) {
				data.redraw_required = val;
			}
			template <class GraphicsSurfaces>
			inline io2d::format _Ds_format(const typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept {
				return data.back_buffer.format;
			}
			template <class GraphicsSurfaces>
			inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> _Ds_dimensions(const typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept {
				return data.back_buffer.dimensions;
			}
			template <class GraphicsSurfaces>
			inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> _Ds_max_dimensions() noexcept {
				return GraphicsSurfaces::surfaces::max_dimensions();
			}
			template <class GraphicsSurfaces>
			inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> _Ds_display_dimensions(const typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept {
				return data.display_dimensions;
			}
			template <class GraphicsSurfaces>
			inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> _Ds_max_display_dimensions() noexcept {
				return GraphicsSurfaces::max_display_dimensions();
			}
			template <class GraphicsSurfaces>
			inline io2d::scaling _Ds_scaling(typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept {
				return data.scl;
			}
			template <class GraphicsSurfaces>
			inline optional<basic_brush<GraphicsSurfaces>> _Ds_letterbox_brush(const typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept {
				return (data.letterbox_brush_is_default ? optional<basic_brush<GraphicsSurfaces>>() : optional<basic_brush<GraphicsSurfaces>>(data._Letterbox_brush));
			}
			template <class GraphicsSurfaces>
			inline basic_brush_props<GraphicsSurfaces> _Ds_letterbox_brush_props(const typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept {
				return data._Letterbox_brush_props;
			}
			template <class GraphicsSurfaces>
			inline bool _Ds_auto_clear(const typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept {
				return data.auto_clear;
			}
			template <class GraphicsSurfaces>
			inline bool _Ds_redraw_required(const typename GraphicsSurfaces::surfaces::_Display_surface_data_type& data) noexcept {
				return data.redraw_required;
			}

			template <class GraphicsMath>
			inline basic_display_point<GraphicsMath> _Qt_graphics_surfaces<GraphicsMath>::surfaces::max_display_dimensions() noexcept {
				return basic_display_point<GraphicsMath>(16384, 16384); // This takes up 1 GB of RAM, you probably don't want to do this. 2048x2048 is the max size for hardware that meets 9_1 specs (i.e. quite low powered or really old). Probably much more reasonable.
			}

			template <class GraphicsMath, class OutputDataType>
			inline void _Render_for_scaling_uniform_or_letterbox(OutputDataType& osd, QPainter& painter) {
				//const cairo_filter_t cairoFilter = CAIRO_FILTER_GOOD;

				auto& data = osd->data;
				//QPainter painter(data.raster_window.get());
				int displayWidth = data.display_dimensions.x();
				int displayHeight = data.display_dimensions.y();
				int backBufferWidth = data.back_buffer.dimensions.x();
				int backBufferHeight = data.back_buffer.dimensions.y();
				auto backBufferSfc = data.back_buffer.surface;

				const auto whRatio = backBufferWidth / backBufferHeight;
				const auto displayWHRatio = displayWidth / displayHeight;
				double rectX, rectY, rectWidth, rectHeight;
				if (backBufferWidth == displayWidth && backBufferHeight == displayHeight) {
					//cairo_set_source_surface(displayContext, backBufferSfc, 0.0, 0.0);
					//cairo_paint(displayContext);
					painter.drawImage(QPointF(), backBufferSfc);
				}
				else {
					if (data.scl == io2d::scaling::letterbox) {
						if (data._Letterbox_brush == nullopt) {
							painter.fillRect(0, 0, displayWidth, displayHeight, Qt::black);
						}
						else {
							auto& pttn = data._Letterbox_brush.value().data().brush;
							if (data._Letterbox_brush_props == nullopt) {
								painter.fillRect(0, 0, displayWidth, displayHeight, pttn);
							}
							else {
								const basic_brush_props<_Qt_graphics_surfaces<GraphicsMath>>& props = data._Letterbox_brush_props.value();
								//cairo_pattern_set_extend(pttn, _Extend_to_cairo_extend_t(props.wrap_mode()));
								//cairo_pattern_set_filter(pttn, _Filter_to_cairo_filter_t(props.filter()));
								//cairo_matrix_t cPttnMatrix;
								const auto& m = props.brush_matrix();
								pttn.setMatrix(QMatrix(m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21()));
								painter.fillRect(0, 0, displayWidth, displayHeight, pttn);
							}
						}
					}
				}
				if (whRatio < displayWHRatio) {
					rectWidth = trunc(displayHeight * whRatio);
					rectHeight = displayHeight;
					rectX = trunc(abs(rectWidth - displayWidth) / 2.0f);
					rectY = 0.0f;
					QRectF destRect(rectX, rectY, rectWidth, rectHeight);
					auto scaledBackBuffer = backBufferSfc.scaledToHeight(displayHeight, Qt::SmoothTransformation);
					painter.drawImage(destRect, scaledBackBuffer);
				}
				else {
					rectWidth = displayWidth;
					rectHeight = trunc(displayWidth / whRatio);
					rectX = 0.0;
					rectY = trunc(abs(rectHeight - displayHeight) / 2.0);
					QRectF destRect(rectX, rectY, rectWidth, rectHeight);
					auto scaledBackBuffer = backBufferSfc.scaledToWidth(displayWidth, Qt::SmoothTransformation);
					painter.drawImage(destRect, scaledBackBuffer);
				}
			}
			template <class GraphicsMath>
			template <class OutputDataType, class OutputSurfaceType>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::_Render_to_native_surface(OutputDataType& osdp, OutputSurfaceType& sfc) {
				auto& osd = *osdp;
				auto& data = osd.data;
				int displayWidth = data.display_dimensions.x();
				int displayHeight = data.display_dimensions.y();
				int backBufferWidth = data.back_buffer.dimensions.x();
				int backBufferHeight = data.back_buffer.dimensions.y();
				auto backBufferSfc = data.back_buffer.surface;
				auto displaySfc = data.raster_window.get()->backing_store();
				//cairo_surface_flush(backBufferSfc);
				//cairo_set_operator(displayContext, CAIRO_OPERATOR_SOURCE);
				QRect displayRect(0, 0, displayWidth, displayHeight);
				displaySfc->beginPaint(displayRect);
				QPaintDevice* paintDevice = displaySfc->paintDevice();
				QPainter painter(paintDevice);
				if (osd.user_scaling_callback != nullptr) {
					bool letterbox = false;
					auto userRect = osd.user_scaling_callback(sfc, letterbox);
					if (letterbox) {
						if (data._Letterbox_brush == nullopt) {
							painter.fillRect(0, 0, displayWidth, displayHeight, Qt::black);
							//cairo_set_source_rgb(displayContext, 0.0, 0.0, 0.0);
							//cairo_paint(displayContext);
						}
						else {
							auto& pttn = data._Letterbox_brush.value().data().brush;
							if (data._Letterbox_brush_props == nullopt) {
								painter.fillRect(0, 0, displayWidth, displayHeight, pttn);
								//cairo_pattern_set_extend(pttn, CAIRO_EXTEND_NONE);
								//cairo_pattern_set_filter(pttn, CAIRO_FILTER_GOOD);
								//cairo_matrix_t cPttnMatrix;
								//cairo_matrix_init_identity(&cPttnMatrix);
								//cairo_pattern_set_matrix(pttn, &cPttnMatrix);
								//cairo_set_source(displayContext, pttn);
								//cairo_paint(displayContext);
							}
							else {
								const basic_brush_props<_Qt_graphics_surfaces<GraphicsMath>>& props = data._Letterbox_brush_props.value();
								//cairo_pattern_set_extend(pttn, _Extend_to_cairo_extend_t(props.wrap_mode()));
								//cairo_pattern_set_filter(pttn, _Filter_to_cairo_filter_t(props.filter()));
								//cairo_matrix_t cPttnMatrix;
								const auto& m = props.brush_matrix();
								pttn.setMatrix(QMatrix(m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21()));
								painter.fillRect(0, 0, displayWidth, displayHeight, pttn);
							}
						}
					}
					QRectF targetRect(userRect.x(), userRect.y(), userRect.width(), userRect.height());
					painter.drawImage(targetRect, backBufferSfc);
					//cairo_matrix_t ctm;
					//cairo_matrix_init_scale(&ctm, 1.0 / displayWidth / static_cast<double>(userRect.width()), 1.0 / displayHeight / static_cast<double>(userRect.height()));
					//cairo_matrix_translate(&ctm, -static_cast<double>(userRect.x()), -static_cast<double>(userRect.y()));
					//unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(backBufferSfc), &cairo_pattern_destroy);
					//auto patPtr = pat.get();
					//cairo_pattern_set_matrix(patPtr, &ctm);
					//cairo_pattern_set_extend(patPtr, CAIRO_EXTEND_NONE);
					//cairo_pattern_set_filter(patPtr, cairoFilter);
					//cairo_set_source(displayContext, patPtr);
					//cairo_paint(displayContext);
				}
				else {

					// Calculate the destRect values.
					switch (data.scl) {
					case std::experimental::io2d::scaling::letterbox:
					{
						_Render_for_scaling_uniform_or_letterbox<GraphicsMath, OutputDataType>(osdp, painter);
					} break;
					case std::experimental::io2d::scaling::uniform:
					{
						_Render_for_scaling_uniform_or_letterbox<GraphicsMath, OutputDataType>(osdp, painter);
					} break;

					case std::experimental::io2d::scaling::fill_uniform:
					{
						// Maintain aspect ratio and center, but overflow if needed rather than letterboxing.
						if (backBufferWidth == displayWidth && backBufferHeight == displayHeight) {
							painter.drawImage(QPointF(), backBufferSfc);
							//cairo_set_source_surface(displayContext, backBufferSfc, 0.0, 0.0);
							//cairo_paint(displayContext);
						}
						else {
							auto widthRatio = displayWidth / backBufferWidth;
							auto heightRatio = displayHeight / backBufferHeight;
							if (widthRatio < heightRatio) {
								// scale so that width overflows.
								auto scaledBackBuffer = backBufferSfc.scaledToHeight(displayHeight, Qt::SmoothTransformation);
								auto diff = trunc(abs(displayWidth - (backBufferWidth * heightRatio)));
								QRectF sourceRect(diff / 2.0f, 0.0f, displayWidth - diff, displayHeight);
								painter.drawImage(QPointF(), scaledBackBuffer, sourceRect);

								//cairo_set_source_rgb(displayContext, 0.0, 0.0, 0.0);
								//cairo_paint(displayContext);
								//cairo_matrix_t ctm;
								//cairo_matrix_init_scale(&ctm, 1.0 / heightRatio, 1.0 / heightRatio);
								//cairo_matrix_translate(&ctm, trunc(abs((displayWidth - (backBufferWidth * heightRatio)) / 2.0)), 0.0);
								//unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(backBufferSfc), &cairo_pattern_destroy);
								//auto patPtr = pat.get();
								//cairo_pattern_set_matrix(patPtr, &ctm);
								//cairo_pattern_set_extend(patPtr, CAIRO_EXTEND_NONE);
								//cairo_pattern_set_filter(patPtr, cairoFilter);
								//cairo_set_source(displayContext, patPtr);
								//cairo_paint(displayContext);
							}
							else {
								// scale so that height overflows.
								auto scaledBackBuffer = backBufferSfc.scaledToWidth(displayWidth, Qt::SmoothTransformation);
								auto diff = trunc(abs(displayHeight - (backBufferHeight * widthRatio)));
								QRectF sourceRect(0.0f, diff / 2.0f, displayWidth, displayHeight - diff);
								painter.drawImage(QPointF(), scaledBackBuffer, sourceRect);
								//cairo_set_source_rgb(displayContext, 0.0, 0.0, 0.0);
								//cairo_paint(displayContext);
								//cairo_matrix_t ctm;
								//cairo_matrix_init_scale(&ctm, 1.0 / widthRatio, 1.0 / widthRatio);
								//cairo_matrix_translate(&ctm, 0.0, trunc(abs((displayHeight - (backBufferHeight * widthRatio)) / 2.0)));
								//unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(backBufferSfc), &cairo_pattern_destroy);
								//auto patPtr = pat.get();
								//cairo_pattern_set_matrix(patPtr, &ctm);
								//cairo_pattern_set_extend(patPtr, CAIRO_EXTEND_NONE);
								//cairo_pattern_set_filter(patPtr, cairoFilter);
								//cairo_set_source(displayContext, patPtr);
								//cairo_paint(displayContext);
							}
						}
					} break;
					case std::experimental::io2d::scaling::fill_exact:
					{
						// Maintain aspect ratio and center, but overflow if needed rather than letterboxing.
						if (backBufferWidth == displayWidth && backBufferHeight == displayHeight) {
							//cairo_set_source_surface(displayContext, backBufferSfc, 0.0, 0.0);
							//cairo_paint(displayContext);
							painter.drawImage(QPointF(), backBufferSfc);
						}
						else {
							painter.drawImage(QRectF(0.0f, 0.0f, displayWidth, displayHeight), backBufferSfc);
							//auto widthRatio = displayWidth / backBufferWidth;
							//auto heightRatio = displayHeight / backBufferHeight;
							//cairo_matrix_t ctm;
							//cairo_matrix_init_scale(&ctm, 1.0 / widthRatio, 1.0 / heightRatio);
							//unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(backBufferSfc), &cairo_pattern_destroy);
							//auto patPtr = pat.get();
							//cairo_pattern_set_matrix(patPtr, &ctm);
							//cairo_pattern_set_extend(patPtr, CAIRO_EXTEND_NONE);
							//cairo_pattern_set_filter(patPtr, cairoFilter);
							//cairo_set_source(displayContext, patPtr);
							//cairo_paint(displayContext);
						}
					} break;
					case std::experimental::io2d::scaling::none:
					{
						painter.drawImage(QPointF(), backBufferSfc);
						//cairo_set_source_surface(displayContext, backBufferSfc, 0.0, 0.0);
						//cairo_paint(displayContext);
					} break;
					default:
					{
						assert("Unexpected _Scaling value." && false);
					} break;
					}
				}
				painter.end();
				displaySfc->endPaint();
				displaySfc->flush(displayRect);
			}
		}
	}
}

#endif
