#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"
#include <cstring>
#include <fstream>
#include <libpng16\png.h>
#include <turbojpeg.h>

using namespace std;
using namespace std::experimental::io2d;

//image_surface::image_surface(image_surface&& other) noexcept
//	: surface(forward<image_surface>(other)) {
//}
//
//image_surface& image_surface::operator=(image_surface&& other) noexcept {
//	if (this != &other) {
//		surface::operator=(move(other));
//	}
//	return *this;
//}
//
//
image_surface::image_surface(experimental::io2d::format fmt, int width, int height)
	: surface({ cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), nullptr }, fmt) {
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
}

image_surface::image_surface(experimental::filesystem::path f, experimental::io2d::format fmt, image_data_format idf)
	: surface({ nullptr, nullptr }, fmt) {
	basic_ifstream<unsigned char, char_traits<unsigned char>> fileStream;
	fileStream.open(f.string(), ios_base::in | ios_base::binary | ios_base::ate);
	auto fileStreamSize = static_cast<::std::streamoff>(fileStream.tellg());
	if (fileStreamSize > numeric_limits<size_t>::max()) {
		throw ::std::system_error(::std::make_error_code(errc::file_too_large));
	}
	auto data = make_unique<unsigned char[]>(static_cast<size_t>(fileStreamSize));
	fileStream.seekg(0, ios::beg);
	fileStream.read(data.get(), fileStreamSize);

	if (fmt != format::argb32) {
		throw runtime_error("Not yet implemented");
	}
	if (idf == image_data_format::png) {
		png_image img{};
		img.version = PNG_IMAGE_VERSION;
		img.opaque = nullptr;
		static_assert(::std::is_same_v<size_t, png_size_t>, "Expected size_t and png_size_t to be the same type.");
		png_image_begin_read_from_memory(&img, static_cast<png_const_voidp>(data.get()), static_cast<png_size_t>(fileStreamSize));
		//if (!png_image_begin_read_from_file(&png, f.))
		img.format = PNG_FORMAT_BGRA;//PNG_FORMAT_LINEAR_RGB_ALPHA;
		auto dataSize = static_cast<size_t>(PNG_IMAGE_SIZE(img));
		//auto data = make_unique<unsigned char>(dataSize);
		auto pixelData = make_unique<unsigned char[]>(dataSize);
		const auto dataStride = PNG_IMAGE_ROW_STRIDE(img);
		png_image_finish_read(&img, nullptr, pixelData.get(), dataStride, nullptr);
		int w{}, h{};
		w = static_cast<int>(img.width);
		h = static_cast<int>(img.height);
		png_image_free(&img);
		_Surface = unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), w, h), &cairo_surface_destroy);
		_Context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy);
		_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
		_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
		auto mapSfc = cairo_surface_map_to_image(_Surface.get(), nullptr);
		auto mapStride = cairo_image_surface_get_stride(mapSfc);
		auto mapData = cairo_image_surface_get_data(mapSfc);
		for (int i = 0; i < h; i++) {
			memcpy(mapData + (i * mapStride), pixelData.get() + i * dataStride, mapStride);
		}
		cairo_surface_unmap_image(_Surface.get(), mapSfc);
		cairo_surface_mark_dirty(_Surface.get());
	}
	else if (idf == image_data_format::jpg) {
		auto decompHandle = tjInitDecompress();
		if (decompHandle == nullptr) {
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_STATUS);
		}
		int w{};
		int h{};
		int jpegSubsamp{};
		int jpegColorspace{};
		if (tjDecompressHeader3(decompHandle, data.get(), static_cast<unsigned long>(fileStreamSize),
			&w, &h, &jpegSubsamp, &jpegColorspace)) {
			tjDestroy(decompHandle);
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_STATUS);
		}
		auto pixelFormat = TJPF_BGRA;
		auto pitch = TJPAD(w * tjPixelSize[pixelFormat]);
		auto pixelData = make_unique<unsigned char[]>(pitch * h);
		if (tjDecompress2(decompHandle, data.get(), static_cast<unsigned long>(fileStreamSize), pixelData.get(), w, pitch, h, pixelFormat, TJFLAG_NOREALLOC | TJFLAG_ACCURATEDCT)) {
			tjDestroy(decompHandle);
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_STATUS);
		}
		tjDestroy(decompHandle);
		_Surface = unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), w, h), &cairo_surface_destroy);
		_Context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy);
		_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
		_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
		auto mapSfc = cairo_surface_map_to_image(_Surface.get(), nullptr);
		auto mapStride = cairo_image_surface_get_stride(mapSfc);
		auto mapData = cairo_image_surface_get_data(mapSfc);
		for (int i = 0; i < h; i++) {
			memcpy(mapData + (i * mapStride), pixelData.get() + i * pitch, mapStride);
		}
		cairo_surface_unmap_image(_Surface.get(), mapSfc);
		cairo_surface_mark_dirty(_Surface.get());
	}
	else {
		throw system_error(make_error_code(errc::operation_not_supported));
	}
}

void image_surface::save(experimental::filesystem::path p, image_data_format idf) {
	throw runtime_error("Not yet implemented");
	//switch (idf) {
	//case image_data_format::png:
	//{
	//	png_image pngImg{};
	//	pngImg.opaque = nullptr;
	//	pngImg.version = PNG_IMAGE_VERSION;
	//	pngImg.width = width();
	//	pngImg.height = height();
	//	pngImg.format = PNG_FORMAT_BGRA;
	//	pngImg.colormap_entries = 0;
	//	//pngImg.flags
	//	png_image_write_to_memory(&pngImg, );
	//}
	//case image_data_format::jpg:
	//{

	//}
	//}
}

format image_surface::format() const noexcept {
	return _Cairo_format_t_to_format(cairo_image_surface_get_format(_Surface.get()));
}

int image_surface::width() const noexcept {
	return cairo_image_surface_get_width(_Surface.get());
}

int image_surface::height() const noexcept {
	return cairo_image_surface_get_height(_Surface.get());
}

int image_surface::stride() const noexcept {
	return cairo_image_surface_get_stride(_Surface.get());
}
