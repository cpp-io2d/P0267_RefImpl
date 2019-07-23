#pragma once

#ifndef _XQT_SURFACES_IMAGE_IMPL_H_
#define _XQT_SURFACES_IMAGE_IMPL_H_
#include "xqt_surfaces_impl.h"
#include "xqt_headers.h"
#include "xqt_helpers.h"
#include "xqt.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Qt_io2d {
			// image_surface

			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::surfaces::image_surface_data_type _Qt_graphics_surfaces<GraphicsMath>::surfaces::create_image_surface(io2d::format fmt, int width, int height) {
				image_surface_data_type data;
				data.surface = QImage(width, height, _Format_to_qimage_format(fmt));
				data.surface.fill(Qt::transparent);
				data.dimensions.x(width);
				data.dimensions.y(height);
				data.format = fmt;
				return data;
			}

			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::surfaces::image_surface_data_type _Qt_graphics_surfaces<GraphicsMath>::surfaces::create_image_surface(filesystem::path p, image_file_format iff, io2d::format fmt) {
				::std::error_code ec;
				auto data = create_image_surface(p, iff, fmt, ec);
				if (ec) {
					throw ::std::system_error(ec);
				}
				return data;
			}
			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::surfaces::image_surface_data_type _Qt_graphics_surfaces<GraphicsMath>::surfaces::create_image_surface(filesystem::path p, image_file_format iff, io2d::format fmt, ::std::error_code& ec) noexcept {
				image_surface_data_type data;
				switch (iff)
				{
				case std::experimental::io2d::v1::image_file_format::unknown:
					data.surface = QImage(QString(p.string().c_str()));
					break;
				case std::experimental::io2d::v1::image_file_format::png:
					data.surface = QImage(QString(p.string().c_str()), "PNG");
					break;
				case std::experimental::io2d::v1::image_file_format::jpeg:
					data.surface = QImage(QString(p.string().c_str()), "JPG");
					break;
				case std::experimental::io2d::v1::image_file_format::tiff:
					data.surface = QImage(QString(p.string().c_str()));
					break;
				default:
					ec = ::std::make_error_code(errc::invalid_argument);
					return image_surface_data_type{};
				}
				if (data.surface.isNull()) {
					ec = ::std::make_error_code(errc::not_supported);
					return image_surface_data_type{};
				}
				data.dimensions.x(data.surface.width());
				data.dimensions.y(data.surface.height());
				data.format = fmt;
				ec.clear();
				return data;
			}
			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::surfaces::image_surface_data_type _Qt_graphics_surfaces<GraphicsMath>::surfaces::move_image_surface(image_surface_data_type&& data) noexcept {
				return move(data);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::destroy(image_surface_data_type& /*data*/) noexcept {
				// Do nothing.
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::save(image_surface_data_type& data, filesystem::path p, image_file_format iff) {
				::std::error_code ec;
				save(data, p, iff, ec);
				if (ec) {
					throw ::std::system_error(ec);
				}
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::save(image_surface_data_type& data, filesystem::path p, image_file_format iff, error_code& ec) noexcept {
				bool success;
				switch (iff)
				{
				case std::experimental::io2d::v1::image_file_format::unknown:
					success = data.surface.save(QString(p.string().c_str()));
					break;
				case std::experimental::io2d::v1::image_file_format::png:
					success = data.surface.save(QString(p.string().c_str()), "PNG");
					break;
				case std::experimental::io2d::v1::image_file_format::jpeg:
					success = data.surface.save(QString(p.string().c_str()), "JPG");
					break;
				case std::experimental::io2d::v1::image_file_format::tiff:
					success = data.surface.save(QString(p.string().c_str()));
					break;
				default:
					ec = ::std::make_error_code(errc::invalid_argument);
					return;
				}
				if (!success) {
					ec = ::std::make_error_code(errc::not_supported);
					return;
				}
				ec.clear();
				return;
			}
			template<class GraphicsMath>
			inline io2d::format _Qt_graphics_surfaces<GraphicsMath>::surfaces::format(const image_surface_data_type& data) noexcept {
				return data.format;
			}
			template<class GraphicsMath>
			inline basic_display_point<GraphicsMath> _Qt_graphics_surfaces<GraphicsMath>::surfaces::dimensions(const image_surface_data_type& data) noexcept {
				return data.dimensions;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::ppi(image_surface_data_type& data, unsigned int val) noexcept {
				data.ppi = val;
			}
			template<class GraphicsMath>
			inline unsigned int _Qt_graphics_surfaces<GraphicsMath>::surfaces::ppi(const image_surface_data_type& data) noexcept {
				return data.ppi;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::clear(image_surface_data_type& data) {
				data.surface.fill(0);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::paint(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				QPainter painter(&data.surface);
				_Set_render_props(painter, rp);
				_Set_clip_props(painter, cl);
				//QBrush& brush = b.data().brush;
				//_Set_brush_props(painter, b, bp);
				painter.setPen(Qt::NoPen);
				_Set_brush_props(painter, b, bp);
				painter.setBrush(b.data().brush);
				QPainterPath qpp;
				qpp.moveTo(0.0f, 0.0f);
				qpp.lineTo(data.dimensions.x(), 0.0f);
				qpp.lineTo(data.dimensions.x(), data.dimensions.y());
				qpp.lineTo(0.0f, data.dimensions.y());
				qpp.closeSubpath();
				painter.drawPath(qpp);
				//painter.drawRect(0, 0, data.dimensions.x(), data.dimensions.y());
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::stroke(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_stroke_props<_Graphics_surfaces_type>& sp, const basic_dashes<_Graphics_surfaces_type>& d, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				QPainter painter(&data.surface);
				_Set_render_props(painter, rp);
				_Set_clip_props(painter, cl);
				auto path = _Set_stroke_props(painter, *(ip.data().path), b, sp, sp.max_miter_limit(), d);
				_Set_brush_props(painter, b, bp);
				painter.setBrush(b.data().brush);
				painter.drawPath(path);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::fill(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				QPainter painter(&data.surface);
				_Set_render_props(painter, rp);
				_Set_clip_props(painter, cl);
				//QBrush& brush = b.data().brush;
				painter.setPen(Qt::NoPen);
				_Set_brush_props(painter, b, bp);
				ip.data().path->setFillRule(_Fill_rule_to_qt_fillrule(bp.fill_rule()));
				if (b.type() == brush_type::radial) {
					//painter.setBrush(*(b.data().brush));
					painter.drawPath(*(ip.data().path));
				}
				else {
					painter.fillPath(*(ip.data().path), b.data().brush);
				}
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::mask(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush<_Graphics_surfaces_type>& mb, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_mask_props<_Graphics_surfaces_type>& mp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				// Seems like QPainter::CompositionMode_SourceIn is the right compositing op for creating the result of the mask, which would then be composed using paint. Question: How to do this correctly where the source is a non-surface brush? A: Create an image of the same dimensions, paint the mask to it using Source then paint the source using SourceIn then paint the source to the surface as-if it was a normal paint operation.
				_Set_mask_props(mp, mb);
				int width = data.surface.width();
				int height = data.surface.height();
				basic_image_surface<_Qt_graphics_surfaces<GraphicsMath>> img(data.format, width, height);
				QPainter painter(&img.data().surface);
				painter.setCompositionMode(QPainter::CompositionMode_Source);
				//painter.setBrush(*(mb.data().brush));
				painter.fillRect(0, 0, width, height, mb.data().brush);

				painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
				//painter.setBrush(b.data.brush);
				painter.fillRect(0, 0, width, height, b.data().brush);
				if (!painter.end()) {
					throw runtime_error("Unable to finish painting with QPainter in mask.");
				}
				basic_brush<_Qt_graphics_surfaces<GraphicsMath>> maskedBrush(::std::move(img));
				paint(data, maskedBrush, bp, rp, cl);
				//auto context = data.context.get();
				//_Set_render_props(context, rp);
				//_Set_clip_props(context, cl);
				//_Set_brush_props(context, bp, b);
				//_Set_mask_props(mp, mb);
				//cairo_set_source(context, b.data().brush.get());
				//cairo_new_path(context);
				//cairo_mask(context, mb.data().brush.get());
			}
			template<class GraphicsMath>
			template<class InputIterator>
			inline ::std::future<void> _Qt_graphics_surfaces<GraphicsMath>::surfaces::command_list(image_surface_data_type& /*data*/, basic_image_surface<graphics_surfaces_type>& sfc, InputIterator first, InputIterator last) {
				return _Process_command_list_image_surface(sfc, first, last);
			}
			template<class GraphicsMath>
			inline _Interchange_buffer _Qt_graphics_surfaces<GraphicsMath>::surfaces::_Copy_to_interchange_buffer(image_surface_data_type& data, _Interchange_buffer::pixel_layout layout, _Interchange_buffer::alpha_mode alpha) {
				auto fmt = data.format;
				const auto pixels = data.surface.constBits();
				auto stride = data.surface.bytesPerLine();
				auto width = data.dimensions.x();
				auto height = data.dimensions.y();
				auto src_layout = _Interchange_buffer::pixel_layout::b8g8r8a8;
				auto src_alpha = _Interchange_buffer::alpha_mode::premultiplied;
				switch (fmt) {
				case format::argb32:
					src_layout = _Interchange_buffer::pixel_layout::b8g8r8a8;
					//src_layout = _Interchange_buffer::pixel_layout::a8b8g8r8;
					//src_layout = _Interchange_buffer::pixel_layout::a8r8g8b8;
					src_alpha = _Interchange_buffer::alpha_mode::premultiplied;
					break;
				case format::xrgb32:
					src_layout = _Interchange_buffer::pixel_layout::b8g8r8a8;
					//src_layout = _Interchange_buffer::pixel_layout::a8b8g8r8;
					//src_layout = _Interchange_buffer::pixel_layout::a8r8g8b8;
					src_alpha = _Interchange_buffer::alpha_mode::ignore;
					break;
				case format::a8:
					src_layout = _Interchange_buffer::pixel_layout::a8;
					src_alpha = _Interchange_buffer::alpha_mode::straight;
					break;
				default:
					throw make_error_code(errc::not_supported);
				};
				return _Interchange_buffer{ layout, alpha, (const byte*)pixels, src_layout, src_alpha, int(width), int(height), int(stride) };
			}
		}
	}
}


#endif
