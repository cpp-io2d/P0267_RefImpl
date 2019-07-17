#pragma once

#ifndef _XQT_SURFACES_IMAGE_IMPL_H_
#define _XQT_SURFACES_IMAGE_IMPL_H_
#include "xqt_surfaces_impl.h"
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
					ec = ::std::make_error_code(errc::not_supported);
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
				//_Init_graphics_magic();
				//if (iff == image_file_format::unknown) {
				//	ec = ::std::make_error_code(errc::not_supported);
				//	return image_surface_data_type{};
				//}
				//ExceptionInfo exInfo;
				//GetExceptionInfo(&exInfo);

				//image_surface_data_type data;

				//unique_ptr<ImageInfo, decltype(&DestroyImageInfo)> imageInfo(CloneImageInfo(nullptr), &DestroyImageInfo);
				//imageInfo->depth = 8;
				//imageInfo->colorspace = TransparentColorspace;
				//auto pathStr = p.string();
				//if (pathStr.length() > MaxTextExtent - 1) {
				//	ec = make_error_code(errc::filename_too_long);
				//	DestroyExceptionInfo(&exInfo);
				//	return image_surface_data_type{};
				//}
				//strncpy(imageInfo->filename, pathStr.c_str(), pathStr.length());
				//PixelPacket mattePixel{};
				//imageInfo->matte_color = mattePixel;
				//unique_ptr<Image, decltype(&DestroyImage)> image(ReadImage(imageInfo.get(), &exInfo), &DestroyImage);
				//if (image == nullptr) {
				//	ec = _Graphics_magic_exception_type_to_error_code(&exInfo);
				//	DestroyExceptionInfo(&exInfo);
				//	return image_surface_data_type{};
				//}
				//auto width = image->columns;
				//auto height = image->rows;
				////auto gamma = image->gamma;

				//data.surface = ::std::move(unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), static_cast<int>(width), static_cast<int>(height)), &cairo_surface_destroy));
				//data.context = ::std::move(unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(data.surface.get()), &cairo_destroy));
				//data.dimensions.x(static_cast<int>(width));
				//data.dimensions.y(static_cast<int>(height));
				//data.format = fmt;

				//// Note: We don't own the pixels pointer.
				//PixelPacket* pixels = GetImagePixelsEx(image.get(), 0, 0, width, height, &exInfo);
				//if (pixels == nullptr) {
				//	ec = _Graphics_magic_exception_type_to_error_code(&exInfo);
				//	DestroyExceptionInfo(&exInfo);
				//	return image_surface_data_type{};
				//}

				//DestroyExceptionInfo(&exInfo);

				//auto map = cairo_surface_map_to_image(data.surface.get(), nullptr);
				//auto mapStride = cairo_image_surface_get_stride(map);
				//auto mapData = cairo_image_surface_get_data(map);
				//const auto channelMaxValue = static_cast<float>(numeric_limits<decltype(mattePixel.red)>::max());
				//if (image->matte != 0) {
				//	for (unsigned long y = 0; y < height; y++) {
				//		for (unsigned long x = 0; x < width; x++) {
				//			const PixelPacket& currPixel = pixels[y * width + x];
				//			auto red = static_cast<unsigned char>(currPixel.red * currPixel.opacity / channelMaxValue * 255);
				//			auto green = static_cast<unsigned char>(currPixel.green * currPixel.opacity / channelMaxValue * 255);
				//			auto blue = static_cast<unsigned char>(currPixel.blue * currPixel.opacity / channelMaxValue * 255);
				//			auto alpha = static_cast<unsigned char>(currPixel.opacity / channelMaxValue * 255);
				//			_Convert_and_set_pixel_to_io2d_format(fmt, mapData, static_cast<int>(y), static_cast<int>(x), mapStride, red, green, blue, alpha);
				//		}
				//	}
				//}
				//else {
				//	for (unsigned long y = 0; y < height; y++) {
				//		for (unsigned long x = 0; x < width; x++) {
				//			const PixelPacket& currPixel = pixels[y * width + x];
				//			auto red = static_cast<unsigned char>(currPixel.red / channelMaxValue * 255);
				//			auto green = static_cast<unsigned char>(currPixel.green / channelMaxValue * 255);
				//			auto blue = static_cast<unsigned char>(currPixel.blue / channelMaxValue * 255);
				//			auto alpha = static_cast<unsigned char>(255);
				//			_Convert_and_set_pixel_to_io2d_format(fmt, mapData, static_cast<int>(y), static_cast<int>(x), mapStride, red, green, blue, alpha);
				//		}
				//	}
				//}
				//cairo_surface_unmap_image(data.surface.get(), map);
				//cairo_surface_mark_dirty(data.surface.get());
				//if (cairo_surface_status(data.surface.get()) != CAIRO_STATUS_SUCCESS) {
				//	ec = ::std::make_error_code(errc::operation_canceled);
				//	return image_surface_data_type{};
				//}
				//ec.clear();
				//return data;
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
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::save(image_surface_data_type& /*data*/, filesystem::path /*p*/, image_file_format /*iff*/) {
				//_Init_graphics_magic();
				::std::error_code ec;
				//save(data, p, iff, ec);
				if (ec) {
					throw ::std::system_error(ec);
				}
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::save(image_surface_data_type& /*data*/, filesystem::path /*p*/, image_file_format /*iff*/, error_code& /*ec*/) noexcept {
				//				_Init_graphics_magic();
				//				if (iff == image_file_format::unknown) {
				//					ec = make_error_code(errc::not_supported);
				//					return;
				//				}
				//				ExceptionInfo exInfo;
				//				GetExceptionInfo(&exInfo);
				//
				//				auto map = cairo_surface_map_to_image(data.surface.get(), nullptr);
				//				auto mapStride = cairo_image_surface_get_stride(map);
				//				auto mapData = cairo_image_surface_get_data(map);
				//				auto width = data.dimensions.x();
				//				auto height = data.dimensions.y();
				//				auto pixelDataUP = _Convert_and_create_pixel_array_from_map_pixels<unsigned char>(data.format, mapData, width, height, mapStride);
				//				::std::unique_ptr<Image, decltype(&DestroyImage)> image(ConstituteImage(static_cast<unsigned long>(width), static_cast<unsigned long>(height), "BGRA", CharPixel, pixelDataUP.get(), &exInfo), &DestroyImage);
				//				if (image == nullptr) {
				//					ec = _Graphics_magic_exception_type_to_error_code(&exInfo);
				//					DestroyExceptionInfo(&exInfo);
				//					return;
				//				}
				//				unique_ptr<ImageInfo, decltype(&DestroyImageInfo)> imageInfo(CloneImageInfo(nullptr), &DestroyImageInfo);
				//				auto pathStr = p.string();
				//				if (pathStr.length() > MaxTextExtent - 1) {
				//					ec = make_error_code(errc::filename_too_long);
				//					DestroyExceptionInfo(&exInfo);
				//					return;
				//				}
				//				strncpy(imageInfo->filename, pathStr.c_str(), pathStr.length());
				//				strncpy(image->filename, pathStr.c_str(), pathStr.length());
				//				switch (iff)
				//				{
				//#ifdef __clang__
				//#pragma clang diagnostic push
				//#pragma clang diagnostic ignored "-Wunreachable-code-break"
				//#endif
				//				case std::experimental::io2d::v1::image_file_format::unknown:
				//				{
				//					//if (p.has_extension()) {
				//
				//					//}
				//					//else {
				//					ec = make_error_code(errc::not_supported);
				//					DestroyExceptionInfo(&exInfo);
				//					//}
				//					return;
				//				} break;
				//#ifdef __clang__
				//#pragma clang diagnostic pop
				//#endif
				//				case std::experimental::io2d::v1::image_file_format::png:
				//				{
				//					const char format[] = "PNG";
				//					const auto formatElemCount = ::std::extent_v<decltype(format)>;
				//					strncpy(imageInfo->magick, format, formatElemCount);
				//					strncpy(image->magick, format, formatElemCount);
				//				} break;
				//				case std::experimental::io2d::v1::image_file_format::jpeg:
				//				{
				//					const char format[] = "JPEG";
				//					const auto formatElemCount = ::std::extent_v<decltype(format)>;
				//					strncpy(imageInfo->magick, format, formatElemCount);
				//					strncpy(image->magick, format, formatElemCount);
				//				} break;
				//				case std::experimental::io2d::v1::image_file_format::tiff:
				//				{
				//					const char format[] = "TIFF";
				//					const auto formatElemCount = ::std::extent_v<decltype(format)>;
				//					strncpy(imageInfo->magick, format, formatElemCount);
				//					strncpy(image->magick, format, formatElemCount);
				//				} break;
				//				default:
				//				{
				//					if (iff == additional_image_file_formats::bmp) {
				//						const char format[] = "BMP";
				//						const auto formatElemCount = ::std::extent_v<decltype(format)>;
				//						strncpy(imageInfo->magick, format, formatElemCount);
				//						strncpy(image->magick, format, formatElemCount);
				//						break;
				//					}
				//					if (iff == additional_image_file_formats::tga) {
				//						const char format[] = "TGA";
				//						const auto formatElemCount = ::std::extent_v<decltype(format)>;
				//						strncpy(imageInfo->magick, format, formatElemCount);
				//						strncpy(image->magick, format, formatElemCount);
				//						break;
				//					}
				//					if (iff == additional_image_file_formats::dib) {
				//						const char format[] = "DIB";
				//						const auto formatElemCount = ::std::extent_v<decltype(format)>;
				//						strncpy(imageInfo->magick, format, formatElemCount);
				//						strncpy(image->magick, format, formatElemCount);
				//						break;
				//					}
				//					if (iff == additional_image_file_formats::gif) {
				//						const char format[] = "GIF";
				//						const auto formatElemCount = ::std::extent_v<decltype(format)>;
				//						strncpy(imageInfo->magick, format, formatElemCount);
				//						strncpy(image->magick, format, formatElemCount);
				//						break;
				//					}
				//					if (iff == additional_image_file_formats::pcx) {
				//						const char format[] = "PCX";
				//						const auto formatElemCount = ::std::extent_v<decltype(format)>;
				//						strncpy(imageInfo->magick, format, formatElemCount);
				//						strncpy(image->magick, format, formatElemCount);
				//						break;
				//					}
				//					if (iff == additional_image_file_formats::pbm) {
				//						const char format[] = "PBM";
				//						const auto formatElemCount = ::std::extent_v<decltype(format)>;
				//						strncpy(imageInfo->magick, format, formatElemCount);
				//						strncpy(image->magick, format, formatElemCount);
				//						break;
				//					}
				//					if (iff == additional_image_file_formats::pgm) {
				//						const char format[] = "PGM";
				//						const auto formatElemCount = ::std::extent_v<decltype(format)>;
				//						strncpy(imageInfo->magick, format, formatElemCount);
				//						strncpy(image->magick, format, formatElemCount);
				//						break;
				//					}
				//					if (iff == additional_image_file_formats::ppm) {
				//						const char format[] = "PPM";
				//						const auto formatElemCount = ::std::extent_v<decltype(format)>;
				//						strncpy(imageInfo->magick, format, formatElemCount);
				//						strncpy(image->magick, format, formatElemCount);
				//						break;
				//					}
				//					if (iff == additional_image_file_formats::psd) {
				//						const char format[] = "PSD";
				//						const auto formatElemCount = ::std::extent_v<decltype(format)>;
				//						strncpy(imageInfo->magick, format, formatElemCount);
				//						strncpy(image->magick, format, formatElemCount);
				//						break;
				//					}
				//					if (iff == additional_image_file_formats::xbm) {
				//						const char format[] = "XBM";
				//						const auto formatElemCount = ::std::extent_v<decltype(format)>;
				//						strncpy(imageInfo->magick, format, formatElemCount);
				//						strncpy(image->magick, format, formatElemCount);
				//						break;
				//					}
				//					if (iff == additional_image_file_formats::xpm) {
				//						const char format[] = "XPM";
				//						const auto formatElemCount = ::std::extent_v<decltype(format)>;
				//						strncpy(imageInfo->magick, format, formatElemCount);
				//						strncpy(image->magick, format, formatElemCount);
				//						break;
				//					}
				//					ec = make_error_code(errc::invalid_argument);
				//					DestroyExceptionInfo(&exInfo);
				//					return;
				//				} break;
				//				}
				//				image->background_color = PixelPacket{};
				//				imageInfo->background_color = PixelPacket{};
				//				image->colorspace = TransparentColorspace;
				//				imageInfo->colorspace = TransparentColorspace;
				//				image->depth = 8;
				//				imageInfo->depth = 8;
				//				image->matte = 1;
				//
				//				image->matte_color = PixelPacket{};
				//				imageInfo->matte_color = PixelPacket{};
				//				image->orientation = TopLeftOrientation;
				//
				//
				//				imageInfo->quality = 90;
				//				image->units = PixelsPerInchResolution;
				//				imageInfo->units = PixelsPerInchResolution;
				//				image->x_resolution = 96.0;
				//
				//				image->y_resolution = 96.0;
				//
				//				if (WriteImage(imageInfo.get(), image.get()) == MagickFail) {
				//					ec = _Graphics_magic_exception_type_to_error_code(&exInfo);
				//					DestroyExceptionInfo(&exInfo);
				//					return;
				//				}
				//				DestroyExceptionInfo(&exInfo);
								//ec.clear();
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
				QBrush& brush = *(b.data().brush);
				_Set_brush_props(brush, bp);
				painter.fillRect(0, 0, data.dimensions.x(), data.dimensions.y(), brush);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::stroke(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_stroke_props<_Graphics_surfaces_type>& sp, const basic_dashes<_Graphics_surfaces_type>& d, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				QPainter painter(&data.surface);
				_Set_render_props(painter, rp);
				_Set_clip_props(painter, cl);
				QBrush& brush = *(b.data().brush);
				_Set_brush_props(brush, bp);
				_Set_stroke_props(painter, b, sp, sp.max_miter_limit(), d);
				ip.data().path->setFillRule(_Fill_rule_to_qt_fillrule(bp.fill_rule()));
				painter.setBrush(brush);
				painter.drawPath(*(ip.data().path));
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::fill(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				QPainter painter(&data.surface);
				_Set_render_props(painter, rp);
				_Set_clip_props(painter, cl);
				QBrush& brush = *(b.data().brush);
				_Set_brush_props(brush, bp);
				ip.data().path->setFillRule(_Fill_rule_to_qt_fillrule(bp.fill_rule()));
				painter.fillPath(*(ip.data().path), brush);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::mask(image_surface_data_type& /*data*/, const basic_brush<_Graphics_surfaces_type>& /*b*/, const basic_brush<_Graphics_surfaces_type>& /*mb*/, const basic_brush_props<_Graphics_surfaces_type>& /*bp*/, const basic_mask_props<_Graphics_surfaces_type>& /*mp*/, const basic_render_props<_Graphics_surfaces_type>& /*rp*/, const basic_clip_props<_Graphics_surfaces_type>& /*cl*/) {
				throw system_error(make_error_code(errc::operation_not_supported), "Not yet implemented.");
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
		}
	}
}


#endif
