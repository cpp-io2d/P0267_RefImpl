#pragma once
#include "xcairo_surfaces_impl.h"
#include "xcairo_helpers.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Cairo {
			// image_surface

			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::image_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_image_surface(io2d::format fmt, int width, int height) {
				image_surface_data_type data;
				data.surface = ::std::move(unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), &cairo_surface_destroy));
				data.context = ::std::move(unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(data.surface.get()), &cairo_destroy));
				data.dimensions.x(width);
				data.dimensions.y(height);
				data.format = fmt;
				return data;
			}

#ifdef _IO2D_Has_Magick

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
#endif

			inline ::std::error_code _Graphics_magic_exception_type_to_error_code(ExceptionInfo* exInfo) {
				ExceptionType code = exInfo->severity;
				::std::error_code ec;
				switch (code)
				{
				case UndefinedException:
				{
					ec = ::std::make_error_code(errc::no_message);
				} break;
				case WarningException:
				{
					ec = ::std::make_error_code(errc::operation_canceled);
				} break;
				case ResourceLimitWarning:
				{
					ec = ::std::make_error_code(errc::not_enough_memory);
				} break;
				case TypeWarning:
				{
					ec = ::std::make_error_code(errc::operation_not_supported);
				} break;
				case OptionWarning:
				{
					ec = ::std::make_error_code(errc::invalid_argument);
				} break;
				case DelegateWarning:
				{
					ec = ::std::make_error_code(errc::operation_not_supported);
				} break;
				case MissingDelegateWarning:
				{
					ec = ::std::make_error_code(errc::no_protocol_option);
				} break;
				case CorruptImageWarning:
				{
					ec = ::std::make_error_code(errc::illegal_byte_sequence);
				} break;
				case FileOpenWarning:
				{
					// Note: We're relying on some of the internals of GraphicsMagick here. As such, io_error is a blanket that may cover the more specific cases that are checked for first.
					if (::std::strstr(exInfo->reason, "UnableToCreateTemporaryFile") != nullptr) {
						ec = ::std::make_error_code(errc::no_space_on_device);
					}
					else {
						if (::std::strstr(exInfo->reason, "UnableToOpenFile") != nullptr) {
							ec = ::std::make_error_code(errc::no_such_file_or_directory);
						}
						else {
							ec = ::std::make_error_code(errc::io_error);
						}
					}
				} break;
				case BlobWarning:
				{
					if (::std::strstr(exInfo->reason, "UnableToWriteBlob") != nullptr) {
						ec = ::std::make_error_code(errc::no_space_on_device);
					}
					else {
						ec = ::std::make_error_code(errc::io_error);
					}
				} break;
				case StreamWarning:
				{
					ec = ::std::make_error_code(errc::io_error);
				} break;
				case CacheWarning:
				{
					ec = ::std::make_error_code(errc::not_enough_memory);
				} break;
				case CoderWarning:
				{
					ec = ::std::make_error_code(errc::invalid_argument);
				} break;
				case ModuleWarning:
				{
					ec = ::std::make_error_code(errc::no_protocol_option);
				} break;
				case DrawWarning:
				{
					ec = ::std::make_error_code(errc::no_message);
				} break;
				case ImageWarning:
				{
					ec = ::std::make_error_code(errc::no_message);
				} break;
				case XServerWarning:
				{
					ec = ::std::make_error_code(errc::operation_canceled);
				} break;
				case MonitorWarning:
				{
					ec = ::std::make_error_code(errc::no_message);
				} break;
				case RegistryWarning:
				{
					ec = ::std::make_error_code(errc::operation_not_permitted);
				} break;
				case ConfigureWarning:
				{
					ec = ::std::make_error_code(errc::operation_canceled);
				} break;
				case ErrorException:
				{
					ec = ::std::make_error_code(errc::operation_not_permitted);
				} break;
				case ResourceLimitError:
				{
					ec = ::std::make_error_code(errc::not_enough_memory);
				} break;
				case TypeError:
				{
					ec = ::std::make_error_code(errc::operation_not_supported);
				} break;
				case OptionError:
				{
					ec = ::std::make_error_code(errc::invalid_argument);
				} break;
				case DelegateError:
				{
					ec = ::std::make_error_code(errc::operation_not_supported);
				} break;
				case MissingDelegateError:
				{
					ec = ::std::make_error_code(errc::no_protocol_option);
				} break;
				case CorruptImageError:
				{
					ec = ::std::make_error_code(errc::illegal_byte_sequence);
				} break;
				case FileOpenError:
				{
					// Note: We're relying on some of the internals of GraphicsMagick here. As such, io_error is a blanket that may cover the more specific cases that are checked for first.
					if (::std::strstr(exInfo->reason, "UnableToCreateTemporaryFile") != nullptr) {
						ec = ::std::make_error_code(errc::no_space_on_device);
					}
					else {
						if (::std::strstr(exInfo->reason, "UnableToOpenFile") != nullptr) {
							ec = ::std::make_error_code(errc::no_such_file_or_directory);
						}
						else {
							ec = ::std::make_error_code(errc::io_error);
						}
					}
				} break;
				case BlobError:
				{
					if (::std::strstr(exInfo->reason, "UnableToWriteBlob") != nullptr) {
						ec = ::std::make_error_code(errc::no_space_on_device);
					}
					else {
						ec = ::std::make_error_code(errc::io_error);
					}
				} break;
				case StreamError:
				{
					ec = ::std::make_error_code(errc::io_error);
				} break;
				case CacheError:
				{
					ec = ::std::make_error_code(errc::not_enough_memory);
				} break;
				case CoderError:
				{
					ec = ::std::make_error_code(errc::invalid_argument);
				} break;
				case ModuleError:
				{
					ec = ::std::make_error_code(errc::no_protocol_option);
				} break;
				case DrawError:
				{
					ec = ::std::make_error_code(errc::no_message);
				} break;
				case ImageError:
				{
					ec = ::std::make_error_code(errc::no_message);
				} break;
				case XServerError:
				{
					ec = ::std::make_error_code(errc::operation_canceled);
				} break;
				case MonitorError:
				{
					ec = ::std::make_error_code(errc::no_message);
				} break;
				case RegistryError:
				{
					ec = ::std::make_error_code(errc::operation_not_permitted);
				} break;
				case ConfigureError:
				{
					ec = ::std::make_error_code(errc::operation_canceled);
				} break;
				case FatalErrorException:
				{
					ec = ::std::make_error_code(errc::not_supported);
				} break;
				case ResourceLimitFatalError:
				{
					ec = ::std::make_error_code(errc::not_enough_memory);
				} break;
				case TypeFatalError:
				{
					ec = ::std::make_error_code(errc::operation_not_supported);
				} break;
				case OptionFatalError:
				{
					ec = ::std::make_error_code(errc::invalid_argument);
				} break;
				case DelegateFatalError:
				{
					ec = ::std::make_error_code(errc::operation_not_supported);
				} break;
				case MissingDelegateFatalError:
				{
					ec = ::std::make_error_code(errc::no_protocol_option);
				} break;
				case CorruptImageFatalError:
				{
					ec = ::std::make_error_code(errc::illegal_byte_sequence);
				} break;
				case FileOpenFatalError:
				{
					// Note: We're relying on some of the internals of GraphicsMagick here. As such, io_error is a blanket that may cover the more specific cases that are checked for first.
					if (::std::strstr(exInfo->reason, "UnableToCreateTemporaryFile") != nullptr) {
						ec = ::std::make_error_code(errc::no_space_on_device);
					}
					else {
						if (::std::strstr(exInfo->reason, "UnableToOpenFile") != nullptr) {
							ec = ::std::make_error_code(errc::no_such_file_or_directory);
						}
						else {
							ec = ::std::make_error_code(errc::io_error);
						}
					}
				} break;
				case BlobFatalError:
				{
					if (::std::strstr(exInfo->reason, "UnableToWriteBlob") != nullptr) {
						ec = ::std::make_error_code(errc::no_space_on_device);
					}
					else {
						ec = ::std::make_error_code(errc::io_error);
					}
				} break;
				case StreamFatalError:
				{
					ec = ::std::make_error_code(errc::io_error);
				} break;
				case CacheFatalError:
				{
					ec = ::std::make_error_code(errc::not_enough_memory);
				} break;
				case CoderFatalError:
				{
					ec = ::std::make_error_code(errc::invalid_argument);
				} break;
				case ModuleFatalError:
				{
					ec = ::std::make_error_code(errc::no_protocol_option);
				} break;
				case DrawFatalError:
				{
					ec = ::std::make_error_code(errc::no_message);
				} break;
				case ImageFatalError:
				{
					ec = ::std::make_error_code(errc::no_message);
				} break;
				case XServerFatalError:
				{
					ec = ::std::make_error_code(errc::operation_canceled);
				} break;
				case MonitorFatalError:
				{
					ec = ::std::make_error_code(errc::no_message);
				} break;
				case RegistryFatalError:
				{
					ec = ::std::make_error_code(errc::operation_not_permitted);
				} break;
				case ConfigureFatalError:
				{
					ec = ::std::make_error_code(errc::operation_canceled);
				} break;
				default:
				{
					ec = ::std::make_error_code(errc::bad_message);
				} break;
				}
				return ec;
			}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif	// _IO2D_Has_Magick

			inline void _Convert_and_set_pixel_to_io2d_format(io2d::format fmt, unsigned char* mapData, int i, int j, int mapStride, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
				switch (fmt) {
				case std::experimental::io2d::v1::format::invalid:
				{
					_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_FORMAT);
				} break;
				case std::experimental::io2d::v1::format::argb32:
				{
					const auto index = i * mapStride + j * 4;
					mapData[index + 0] = blue;
					mapData[index + 1] = green;
					mapData[index + 2] = red;
					mapData[index + 3] = alpha;
				} break;
				case std::experimental::io2d::v1::format::xrgb32:
				{
					const auto index = i * mapStride + j * 4;
					mapData[index + 0] = blue;
					mapData[index + 1] = green;
					mapData[index + 2] = red;
					mapData[index + 3] = static_cast<unsigned char>(1);
				} break;
				case std::experimental::io2d::v1::format::a8:
				{
					const auto index = i * mapStride + j;
					mapData[index + 0] = alpha;
				} break;
				default:
				{
				} break;
				}
			}
			template <class result_type = unsigned char>
			inline ::std::unique_ptr<result_type[]> _Convert_and_create_pixel_array_from_map_pixels(io2d::format fmt, unsigned char* mapData, int w, int h, int mapStride) {
				//using result_type = unsigned char;
				size_t pixelsArraySize = static_cast<size_t>(w * h * 4);
				::std::unique_ptr<result_type[]> pixels(new result_type[pixelsArraySize]);
				const float maxChannelSize = static_cast<float>(::std::numeric_limits<result_type>::max());
				const bool keepPremultiplied = false;
				auto pixel = pixels.get();
				switch (fmt)
				{
				case std::experimental::io2d::v1::format::invalid:
				{
					_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_FORMAT);
				} break;
				case std::experimental::io2d::v1::format::argb32:
				{
					for (int i = 0; i < h; i++) {
						for (int j = 0; j < w; j++) {
							const auto ppIndex = i * w * 4 + j * 4;
							const auto mapIndex = i * mapStride + j * 4;
                            const float premul = (keepPremultiplied ?
                                                  1.0f :
                                                  (mapData[mapIndex + 3] != 0 ? 255.0f / float(mapData[mapIndex + 3]) : 0.f )
                                                  );
							pixel[ppIndex + 0] = static_cast<result_type>(mapData[mapIndex + 0] * premul / 255.0f * maxChannelSize);
							pixel[ppIndex + 1] = static_cast<result_type>(mapData[mapIndex + 1] * premul / 255.0f * maxChannelSize);
							pixel[ppIndex + 2] = static_cast<result_type>(mapData[mapIndex + 2] * premul / 255.0f * maxChannelSize);
							pixel[ppIndex + 3] = static_cast<result_type>(mapData[mapIndex + 3] / 255.0f * maxChannelSize);
						}
					}
				} break;
				case std::experimental::io2d::v1::format::xrgb32:
				{
					for (int i = 0; i < h; i++) {
						for (int j = 0; j < w; j++) {
							const auto ppIndex = i * w * 4 + j * 4;
							const auto mapIndex = i * mapStride + j * 4;
							pixel[ppIndex + 0] = static_cast<result_type>(mapData[mapIndex + 0] / 255.0f * maxChannelSize);
							pixel[ppIndex + 1] = static_cast<result_type>(mapData[mapIndex + 1] / 255.0f * maxChannelSize);
							pixel[ppIndex + 2] = static_cast<result_type>(mapData[mapIndex + 2] / 255.0f * maxChannelSize);
							pixel[ppIndex + 3] = static_cast<result_type>(maxChannelSize);
						}
					}
				} break;
				case std::experimental::io2d::v1::format::a8:
				{
					for (int i = 0; i < h; i++) {
						for (int j = 0; j < w; j++) {
							const auto ppIndex = i * w * 4 + j * 4;
							const auto mapIndex = i * mapStride + j;
							//const float premul = (keepPremultiplied ? 1.0f : mapData[mapIndex + 3] / 255.0f);
							const auto pixVal = static_cast<result_type>(mapData[mapIndex] / 255.0f * maxChannelSize);
							pixel[ppIndex + 0] = pixVal;
							pixel[ppIndex + 1] = pixVal;
							pixel[ppIndex + 2] = pixVal;
							pixel[ppIndex + 3] = pixVal;
						}
					}
				} break;
				default:
				{
					_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_FORMAT);
				} break;
				}
				return pixels;
			}

#if defined(_Filesystem_support_test)
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::image_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_image_surface(filesystem::path p, image_file_format iff, io2d::format fmt) {
				::std::error_code ec;
				auto data = create_image_surface(p, iff, fmt, ec);
				if (ec) {
					throw ::std::system_error(ec);
				}
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::image_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_image_surface(filesystem::path p, image_file_format iff, io2d::format fmt, ::std::error_code& ec) noexcept {
				_Init_graphics_magic();
				if (iff == image_file_format::unknown) {
					ec = ::std::make_error_code(errc::not_supported);
					return image_surface_data_type{};
				}
				ExceptionInfo exInfo;
				GetExceptionInfo(&exInfo);

				image_surface_data_type data;

				unique_ptr<ImageInfo, decltype(&DestroyImageInfo)> imageInfo(CloneImageInfo(nullptr), &DestroyImageInfo);
				imageInfo->depth = 8;
				imageInfo->colorspace = TransparentColorspace;
				auto pathStr = p.string();
				if (pathStr.length() > MaxTextExtent - 1) {
					ec = make_error_code(errc::filename_too_long);
					DestroyExceptionInfo(&exInfo);
					return image_surface_data_type{};
				}
				strncpy(imageInfo->filename, pathStr.c_str(), pathStr.length());
				PixelPacket mattePixel{};
				imageInfo->matte_color = mattePixel;
				unique_ptr<Image, decltype(&DestroyImage)> image(ReadImage(imageInfo.get(), &exInfo), &DestroyImage);
				if (image == nullptr) {
					ec = _Graphics_magic_exception_type_to_error_code(&exInfo);
					DestroyExceptionInfo(&exInfo);
					return image_surface_data_type{};
				}
				auto width = image->columns;
				auto height = image->rows;
				//auto gamma = image->gamma;

				data.surface = ::std::move(unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), static_cast<int>(width), static_cast<int>(height)), &cairo_surface_destroy));
				data.context = ::std::move(unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(data.surface.get()), &cairo_destroy));
				data.dimensions.x(static_cast<int>(width));
				data.dimensions.y(static_cast<int>(height));
				data.format = fmt;

				// Note: We don't own the pixels pointer.
				PixelPacket* pixels = GetImagePixelsEx(image.get(), 0, 0, width, height, &exInfo);
				if (pixels == nullptr) {
					ec = _Graphics_magic_exception_type_to_error_code(&exInfo);
					DestroyExceptionInfo(&exInfo);
					return image_surface_data_type{};
				}

				DestroyExceptionInfo(&exInfo);

				auto map = cairo_surface_map_to_image(data.surface.get(), nullptr);
				auto mapStride = cairo_image_surface_get_stride(map);
				auto mapData = cairo_image_surface_get_data(map);
				const auto channelMaxValue = static_cast<float>(numeric_limits<decltype(mattePixel.red)>::max());
				if (image->matte != 0) {
					for (unsigned long y = 0; y < height; y++) {
						for (unsigned long x = 0; x < width; x++) {
							const PixelPacket& currPixel = pixels[y * width + x];
							auto red = static_cast<unsigned char>(currPixel.red * currPixel.opacity / channelMaxValue * 255);
							auto green = static_cast<unsigned char>(currPixel.green * currPixel.opacity / channelMaxValue * 255);
							auto blue = static_cast<unsigned char>(currPixel.blue * currPixel.opacity / channelMaxValue * 255);
							auto alpha = static_cast<unsigned char>(currPixel.opacity / channelMaxValue * 255);
							_Convert_and_set_pixel_to_io2d_format(fmt, mapData, static_cast<int>(y), static_cast<int>(x), mapStride, red, green, blue, alpha);
						}
					}
				}
				else {
					for (unsigned long y = 0; y < height; y++) {
						for (unsigned long x = 0; x < width; x++) {
							const PixelPacket& currPixel = pixels[y * width + x];
							auto red = static_cast<unsigned char>(currPixel.red / channelMaxValue * 255);
							auto green = static_cast<unsigned char>(currPixel.green / channelMaxValue * 255);
							auto blue = static_cast<unsigned char>(currPixel.blue / channelMaxValue * 255);
							auto alpha = static_cast<unsigned char>(255);
							_Convert_and_set_pixel_to_io2d_format(fmt, mapData, static_cast<int>(y), static_cast<int>(x), mapStride, red, green, blue, alpha);
						}
					}
				}
				cairo_surface_unmap_image(data.surface.get(), map);
				cairo_surface_mark_dirty(data.surface.get());
				if (cairo_surface_status(data.surface.get()) != CAIRO_STATUS_SUCCESS) {
					ec = ::std::make_error_code(errc::operation_canceled);
					return image_surface_data_type{};
				}
				ec.clear();
				return data;
			}
#else
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::image_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_image_surface(::std::string p, image_file_format iff, io2d::format fmt) {
				::std::error_code ec;
				ec.clear();
				auto data = move(create_image_surface(p, iff, fmt, ec));
				if (ec) {
					throw ::std::system_error(ec);
				}
				return data;
			}

#ifdef _IO2D_Has_Magick
			template <class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::image_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::create_image_surface(::std::string p, image_file_format iff, io2d::format fmt, ::std::error_code& ec) noexcept {
				_Init_graphics_magic();
				if (iff == image_file_format::unknown) {
					ec = ::std::make_error_code(errc::not_supported);
					return image_surface_data_type{};
				}
				ExceptionInfo exInfo;
				GetExceptionInfo(&exInfo);

				image_surface_data_type data;

				unique_ptr<ImageInfo, decltype(&DestroyImageInfo)> imageInfo(CloneImageInfo(nullptr), &DestroyImageInfo);
				imageInfo->depth = 8;
				imageInfo->colorspace = TransparentColorspace;
				auto& pathStr = p;
				if (pathStr.length() > MaxTextExtent - 1) {
					ec = make_error_code(errc::filename_too_long);
					DestroyExceptionInfo(&exInfo);
					return image_surface_data_type{};
				}
				strncpy(imageInfo->filename, pathStr.c_str(), pathStr.length());
				PixelPacket mattePixel{};
				imageInfo->matte_color = mattePixel;
				unique_ptr<Image, decltype(&DestroyImage)> image(ReadImage(imageInfo.get(), &exInfo), &DestroyImage);
				if (image == nullptr) {
					ec = _Graphics_magic_exception_type_to_error_code(&exInfo);
					DestroyExceptionInfo(&exInfo);
					return image_surface_data_type{};
				}
				auto width = image->columns;
				auto height = image->rows;

				data.surface = ::std::move(unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), &cairo_surface_destroy));
				data.context = ::std::move(unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(data.surface.get()), &cairo_destroy));
				data.dimensions.x(width);
				data.dimensions.y(height);
				data.format = fmt;

				// Note: We don't own the pixels pointer.
				PixelPacket* pixels = GetImagePixelsEx(image.get(), 0, 0, width, height, &exInfo);
				if (pixels == nullptr) {
					ec = _Graphics_magic_exception_type_to_error_code(&exInfo);
					DestroyExceptionInfo(&exInfo);
					return image_surface_data_type{};
				}

				DestroyExceptionInfo(&exInfo);

				auto map = cairo_surface_map_to_image(data.surface.get(), nullptr);
				auto mapStride = cairo_image_surface_get_stride(map);
				auto mapData = cairo_image_surface_get_data(map);
				const auto channelMaxValue = static_cast<float>(numeric_limits<decltype(mattePixel.red)>::max());
				if (image->matte != 0) {
					for (unsigned long y = 0; y < height; y++) {
						for (unsigned long x = 0; x < width; x++) {
							const PixelPacket& currPixel = pixels[y * width + x];
							auto red = static_cast<unsigned char>(currPixel.red * currPixel.opacity / channelMaxValue * 255);
							auto green = static_cast<unsigned char>(currPixel.green * currPixel.opacity / channelMaxValue * 255);
							auto blue = static_cast<unsigned char>(currPixel.blue * currPixel.opacity / channelMaxValue * 255);
							auto alpha = static_cast<unsigned char>(currPixel.opacity / channelMaxValue * 255);
							_Convert_and_set_pixel_to_io2d_format(fmt, mapData, y, x, mapStride, red, green, blue, alpha);
						}
					}
				}
				else {
					for (unsigned long y = 0; y < height; y++) {
						for (unsigned long x = 0; x < width; x++) {
							const PixelPacket& currPixel = pixels[y * width + x];
							auto red = static_cast<unsigned char>(currPixel.red / channelMaxValue * 255);
							auto green = static_cast<unsigned char>(currPixel.green / channelMaxValue * 255);
							auto blue = static_cast<unsigned char>(currPixel.blue / channelMaxValue * 255);
							auto alpha = static_cast<unsigned char>(255);
							_Convert_and_set_pixel_to_io2d_format(fmt, mapData, y, x, mapStride, red, green, blue, alpha);
						}
					}
				}
				cairo_surface_unmap_image(data.surface.get(), map);
				cairo_surface_mark_dirty(data.surface.get());
				if (cairo_surface_status(data.surface.get()) != CAIRO_STATUS_SUCCESS) {
					ec = ::std::make_error_code(errc::operation_canceled);
					return image_surface_data_type{};
				}
				ec.clear();
				return data;
			}
#endif	// _IO2D_Has_Magick
#endif
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::image_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::surfaces::move_image_surface(image_surface_data_type&& data) noexcept {
				return move(data);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::destroy(image_surface_data_type& /*data*/) noexcept {
				// Do nothing.
			}
#if defined(_Filesystem_support_test)
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::save(image_surface_data_type& data, filesystem::path p, image_file_format iff) {
				_Init_graphics_magic();
				::std::error_code ec;
				save(data, p, iff, ec);
				if (ec) {
					throw ::std::system_error(ec);
				}
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::save(image_surface_data_type& data, filesystem::path p, image_file_format iff, error_code& ec) noexcept {
				_Init_graphics_magic();
				if (iff == image_file_format::unknown) {
					ec = make_error_code(errc::not_supported);
					return;
				}
				ExceptionInfo exInfo;
				GetExceptionInfo(&exInfo);

				auto map = cairo_surface_map_to_image(data.surface.get(), nullptr);
				auto mapStride = cairo_image_surface_get_stride(map);
				auto mapData = cairo_image_surface_get_data(map);
				auto width = data.dimensions.x();
				auto height = data.dimensions.y();
				auto pixelDataUP = _Convert_and_create_pixel_array_from_map_pixels<unsigned char>(data.format, mapData, width, height, mapStride);
				::std::unique_ptr<Image, decltype(&DestroyImage)> image(ConstituteImage(static_cast<unsigned long>(width), static_cast<unsigned long>(height), "BGRA", CharPixel, pixelDataUP.get(), &exInfo), &DestroyImage);
				if (image == nullptr) {
					ec = _Graphics_magic_exception_type_to_error_code(&exInfo);
					DestroyExceptionInfo(&exInfo);
					return;
				}
				unique_ptr<ImageInfo, decltype(&DestroyImageInfo)> imageInfo(CloneImageInfo(nullptr), &DestroyImageInfo);
				auto pathStr = p.string();
				if (pathStr.length() > MaxTextExtent - 1) {
					ec = make_error_code(errc::filename_too_long);
					DestroyExceptionInfo(&exInfo);
					return;
				}
				strncpy(imageInfo->filename, pathStr.c_str(), pathStr.length());
				strncpy(image->filename, pathStr.c_str(), pathStr.length());
				switch (iff)
				{
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunreachable-code-break"
#endif
				case std::experimental::io2d::v1::image_file_format::unknown:
				{
					//if (p.has_extension()) {

					//}
					//else {
					ec = make_error_code(errc::not_supported);
					DestroyExceptionInfo(&exInfo);
					//}
					return;
				} break;
#ifdef __clang__
#pragma clang diagnostic pop
#endif
				case std::experimental::io2d::v1::image_file_format::png:
				{
					const char format[] = "PNG";
					const auto formatElemCount = ::std::extent_v<decltype(format)>;
					strncpy(imageInfo->magick, format, formatElemCount);
					strncpy(image->magick, format, formatElemCount);
				} break;
				case std::experimental::io2d::v1::image_file_format::jpeg:
				{
					const char format[] = "JPEG";
					const auto formatElemCount = ::std::extent_v<decltype(format)>;
					strncpy(imageInfo->magick, format, formatElemCount);
					strncpy(image->magick, format, formatElemCount);
				} break;
				case std::experimental::io2d::v1::image_file_format::tiff:
				{
					const char format[] = "TIFF";
					const auto formatElemCount = ::std::extent_v<decltype(format)>;
					strncpy(imageInfo->magick, format, formatElemCount);
					strncpy(image->magick, format, formatElemCount);
				} break;
				default:
				{
					if (iff == additional_image_file_formats::bmp) {
						const char format[] = "BMP";
						const auto formatElemCount = ::std::extent_v<decltype(format)>;
						strncpy(imageInfo->magick, format, formatElemCount);
						strncpy(image->magick, format, formatElemCount);
						break;
					}
					if (iff == additional_image_file_formats::tga) {
						const char format[] = "TGA";
						const auto formatElemCount = ::std::extent_v<decltype(format)>;
						strncpy(imageInfo->magick, format, formatElemCount);
						strncpy(image->magick, format, formatElemCount);
						break;
					}
					if (iff == additional_image_file_formats::dib) {
						const char format[] = "DIB";
						const auto formatElemCount = ::std::extent_v<decltype(format)>;
						strncpy(imageInfo->magick, format, formatElemCount);
						strncpy(image->magick, format, formatElemCount);
						break;
					}
					if (iff == additional_image_file_formats::gif) {
						const char format[] = "GIF";
						const auto formatElemCount = ::std::extent_v<decltype(format)>;
						strncpy(imageInfo->magick, format, formatElemCount);
						strncpy(image->magick, format, formatElemCount);
						break;
					}
					if (iff == additional_image_file_formats::pcx) {
						const char format[] = "PCX";
						const auto formatElemCount = ::std::extent_v<decltype(format)>;
						strncpy(imageInfo->magick, format, formatElemCount);
						strncpy(image->magick, format, formatElemCount);
						break;
					}
					if (iff == additional_image_file_formats::pbm) {
						const char format[] = "PBM";
						const auto formatElemCount = ::std::extent_v<decltype(format)>;
						strncpy(imageInfo->magick, format, formatElemCount);
						strncpy(image->magick, format, formatElemCount);
						break;
					}
					if (iff == additional_image_file_formats::pgm) {
						const char format[] = "PGM";
						const auto formatElemCount = ::std::extent_v<decltype(format)>;
						strncpy(imageInfo->magick, format, formatElemCount);
						strncpy(image->magick, format, formatElemCount);
						break;
					}
					if (iff == additional_image_file_formats::ppm) {
						const char format[] = "PPM";
						const auto formatElemCount = ::std::extent_v<decltype(format)>;
						strncpy(imageInfo->magick, format, formatElemCount);
						strncpy(image->magick, format, formatElemCount);
						break;
					}
					if (iff == additional_image_file_formats::psd) {
						const char format[] = "PSD";
						const auto formatElemCount = ::std::extent_v<decltype(format)>;
						strncpy(imageInfo->magick, format, formatElemCount);
						strncpy(image->magick, format, formatElemCount);
						break;
					}
					if (iff == additional_image_file_formats::xbm) {
						const char format[] = "XBM";
						const auto formatElemCount = ::std::extent_v<decltype(format)>;
						strncpy(imageInfo->magick, format, formatElemCount);
						strncpy(image->magick, format, formatElemCount);
						break;
					}
					if (iff == additional_image_file_formats::xpm) {
						const char format[] = "XPM";
						const auto formatElemCount = ::std::extent_v<decltype(format)>;
						strncpy(imageInfo->magick, format, formatElemCount);
						strncpy(image->magick, format, formatElemCount);
						break;
					}
					ec = make_error_code(errc::invalid_argument);
					DestroyExceptionInfo(&exInfo);
					return;
				} break;
				}
				image->background_color = PixelPacket{};
				imageInfo->background_color = PixelPacket{};
				image->colorspace = TransparentColorspace;
				imageInfo->colorspace = TransparentColorspace;
				image->depth = 8;
				imageInfo->depth = 8;
				image->matte = 1;

				image->matte_color = PixelPacket{};
				imageInfo->matte_color = PixelPacket{};
				image->orientation = TopLeftOrientation;


				imageInfo->quality = 90;
				image->units = PixelsPerInchResolution;
				imageInfo->units = PixelsPerInchResolution;
				image->x_resolution = 96.0;

				image->y_resolution = 96.0;

				if (WriteImage(imageInfo.get(), image.get()) == MagickFail) {
					ec = _Graphics_magic_exception_type_to_error_code(&exInfo);
					DestroyExceptionInfo(&exInfo);
					return;
				}
				DestroyExceptionInfo(&exInfo);
				ec.clear();
				return;
			}
#else
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::save(image_surface_data_type& data, ::std::string p, image_file_format iff) {
				_Init_graphics_magic();
				::std::error_code ec;
				save(data, p, iff, ec);
				if (ec) {
					throw ::std::system_error(ec);
				}
			}

#ifdef _IO2D_Has_Magick
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::save(image_surface_data_type& data, ::std::string p, image_file_format iff, error_code& ec) noexcept {
				_Init_graphics_magic();
				if (iff == image_file_format::unknown) {
					ec = make_error_code(errc::not_supported);
					return;
				}
				ExceptionInfo exInfo;
				GetExceptionInfo(&exInfo);

				auto map = cairo_surface_map_to_image(data.surface.get(), nullptr);
				auto mapStride = cairo_image_surface_get_stride(map);
				auto mapData = cairo_image_surface_get_data(map);
				auto width = data.dimensions.x();
				auto height = data.dimensions.y();
				auto pixelDataUP = _Convert_and_create_pixel_array_from_map_pixels<unsigned char>(data.format, mapData, width, height, mapStride);
				::std::unique_ptr<Image, decltype(&DestroyImage)> image(ConstituteImage(static_cast<unsigned long>(width), static_cast<unsigned long>(height), "BGRA", CharPixel, pixelDataUP.get(), &exInfo), &DestroyImage);
				if (image == nullptr) {
					ec = _Graphics_magic_exception_type_to_error_code(&exInfo);
					DestroyExceptionInfo(&exInfo);
					return;
				}
				unique_ptr<ImageInfo, decltype(&DestroyImageInfo)> imageInfo(CloneImageInfo(nullptr), &DestroyImageInfo);
				auto& pathStr = p;
				if (pathStr.length() > MaxTextExtent - 1) {
					ec = make_error_code(errc::filename_too_long);
					DestroyExceptionInfo(&exInfo);
					return;
				}
				strncpy(imageInfo->filename, pathStr.c_str(), pathStr.length());
				strncpy(image->filename, pathStr.c_str(), pathStr.length());
				switch (iff)
				{
				case std::experimental::io2d::v1::image_file_format::unknown:
				{
					//if (p.has_extension()) {

					//}
					//else {
					ec = make_error_code(errc::not_supported);
					DestroyExceptionInfo(&exInfo);
					//}
					return;
				} break;
				case std::experimental::io2d::v1::image_file_format::png:
				{
					const char format[] = "PNG";
					strncpy(imageInfo->magick, format, MaxTextExtent);
					strncpy(image->magick, format, MaxTextExtent);
				} break;
				case std::experimental::io2d::v1::image_file_format::jpeg:
				{
					const char format[] = "JPEG";
					strncpy(imageInfo->magick, format, MaxTextExtent);
					strncpy(image->magick, format, MaxTextExtent);
				} break;
				case std::experimental::io2d::v1::image_file_format::tiff:
				{
					const char format[] = "TIFF";
					strncpy(imageInfo->magick, format, MaxTextExtent);
					strncpy(image->magick, format, MaxTextExtent);
				}break;
				default:
					if (iff == additional_image_file_formats::bmp) {
						const char format[] = "BMP";
						const auto formatElemCount = ::std::extent_v<decltype(format)>;
						strncpy(imageInfo->magick, format, formatElemCount);
						strncpy(image->magick, format, formatElemCount);
						break;
					}
					ec = make_error_code(errc::invalid_argument);
					DestroyExceptionInfo(&exInfo);
					return;
				}
				image->background_color = PixelPacket{};
				imageInfo->background_color = PixelPacket{};
				image->colorspace = TransparentColorspace;
				imageInfo->colorspace = TransparentColorspace;
				image->depth = 8;
				imageInfo->depth = 8;
				image->matte = 1;

				image->matte_color = PixelPacket{};
				imageInfo->matte_color = PixelPacket{};
				image->orientation = TopLeftOrientation;


				imageInfo->quality = 90;
				image->units = PixelsPerInchResolution;
				imageInfo->units = PixelsPerInchResolution;
				image->x_resolution = 96.0;

				image->y_resolution = 96.0;

				if (WriteImage(imageInfo.get(), image.get()) == MagickFail) {
					ec = _Graphics_magic_exception_type_to_error_code(&exInfo);
					DestroyExceptionInfo(&exInfo);
					return;
				}
				DestroyExceptionInfo(&exInfo);
				ec.clear();
				return;
			}
#endif	// _IO2D_Has_Magick
#endif
			template<class GraphicsMath>
			inline io2d::format _Cairo_graphics_surfaces<GraphicsMath>::surfaces::format(const image_surface_data_type& data) noexcept {
				return data.format;
			}
			template<class GraphicsMath>
			inline basic_display_point<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::dimensions(const image_surface_data_type& data) noexcept {
				return data.dimensions;
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::clear(image_surface_data_type& data) {
				auto ctx = data.context.get();
				cairo_save(ctx);
				cairo_set_operator(ctx, CAIRO_OPERATOR_CLEAR);
				cairo_set_source_rgba(ctx, 1.0, 1.0, 1.0, 1.0);
				cairo_paint(ctx);
				cairo_restore(ctx);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::flush(image_surface_data_type& data) {
				cairo_surface_flush(data.surface.get());
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::flush(image_surface_data_type& data, error_code& ec) noexcept {
				cairo_surface_flush(data.surface.get());
				ec.clear();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty(image_surface_data_type& data) {
				cairo_surface_mark_dirty(data.surface.get());
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty(image_surface_data_type& data, error_code& ec) noexcept {
				cairo_surface_mark_dirty(data.surface.get());
				ec.clear();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty(image_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents) {
				cairo_surface_mark_dirty_rectangle(data.surface.get(), _Float_to_int(extents.x()), _Float_to_int(extents.y()), _Float_to_int(extents.width()), _Float_to_int(extents.height()));
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mark_dirty(image_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents, error_code& ec) noexcept {
				cairo_surface_mark_dirty_rectangle(data.surface.get(), _Float_to_int(extents.x()), _Float_to_int(extents.y()), _Float_to_int(extents.width()), _Float_to_int(extents.height()));
				ec.clear();
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::paint(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				auto context = data.context.get();
				_Set_render_props(context, rp);
				_Set_clip_props(context, cl);
				_Set_brush_props(context, bp, b);
				cairo_set_source(context, b.data().brush.get());
				cairo_paint(context);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::stroke(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_stroke_props<_Graphics_surfaces_type>& sp, const basic_dashes<_Graphics_surfaces_type>& d, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				auto context = data.context.get();
				_Set_render_props(context, rp);
				_Set_clip_props(context, cl);
				_Set_brush_props(context, bp, b);
				_Set_stroke_props(context, sp, sp.max_miter_limit(), d);
				cairo_set_source(context, b.data().brush.get());
				cairo_new_path(context);
				cairo_append_path(context, ip.data().path.get());
				cairo_stroke(context);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::fill(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				auto context = data.context.get();
				_Set_render_props(context, rp);
				_Set_clip_props(context, cl);
				_Set_brush_props(context, bp, b);
				cairo_set_source(context, b.data().brush.get());
				cairo_new_path(context);
				cairo_append_path(context, ip.data().path.get());
				cairo_fill(context);
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::mask(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush<_Graphics_surfaces_type>& mb, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_mask_props<_Graphics_surfaces_type>& mp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
				auto context = data.context.get();
				_Set_render_props(context, rp);
				_Set_clip_props(context, cl);
				_Set_brush_props(context, bp, b);
				_Set_mask_props(mp, mb);
				cairo_set_source(context, b.data().brush.get());
				cairo_new_path(context);
				cairo_mask(context, mb.data().brush.get());
			}
            template<class GraphicsMath>
            inline _Interchange_buffer _Cairo_graphics_surfaces<GraphicsMath>::surfaces::_Copy_to_interchange_buffer(image_surface_data_type& data, _Interchange_buffer::pixel_layout layout, _Interchange_buffer::alpha_mode alpha) {
                auto fmt = data.format;
                auto map = cairo_surface_map_to_image(data.surface.get(), nullptr);
                auto stride = cairo_image_surface_get_stride(map);
                auto pixels = cairo_image_surface_get_data(map);
                auto width = data.dimensions.x();
                auto height = data.dimensions.y();
                auto src_layout = _Interchange_buffer::pixel_layout::r8g8b8a8;
                auto src_alpha = _Interchange_buffer::alpha_mode::ignore;
                switch( fmt ) {
                    case format::argb32:
                        src_layout = _Interchange_buffer::pixel_layout::b8g8r8a8;
                        src_alpha = _Interchange_buffer::alpha_mode::premultiplied;
                        break;
                    case format::xrgb32:
                        src_layout = _Interchange_buffer::pixel_layout::b8g8r8a8;
                        src_alpha = _Interchange_buffer::alpha_mode::ignore;
                        break;
                    case format::a8:
                        src_layout = _Interchange_buffer::pixel_layout::a8;
                        src_alpha = _Interchange_buffer::alpha_mode::straight;
                        break;
                    default:
                        throw make_error_code(errc::not_supported);
                };                
                return _Interchange_buffer{layout, alpha, (const byte*)pixels, src_layout, src_alpha, int(width), int(height), int(stride) };    
            }
		}
	}
}
