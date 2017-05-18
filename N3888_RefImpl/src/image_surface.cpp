#include "io2d.h"
#include "xcairoenumhelpers.h"
#include <cstring>
#include <fstream>
#include <png.h>
#include <turbojpeg.h>
#include <cstdio>

using namespace std;
using namespace std::experimental::io2d;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
#endif

//namespace {
//	// Apparently, the whole concept of custom character traits is useless if you want to provide a traits type for unsigned char. Thanks for the false hope [char.traits.require]. Should've read and understood the implications of [iostreams.limits.pos] before embarking on this venture;
//	struct unsignedCharTraits {
//		using char_type = unsigned char;
//		using int_type = unsigned short;
//		using off_type = streamoff;
//		using pos_type = streampos;
//		using state_type = mbstate_t;
//		constexpr static bool eq(const char_type c, const char_type d) noexcept {
//			return c == d;
//		}
//		constexpr static bool lt(const char_type c, const char_type d) noexcept {
//			return c < d;
//		}
//		constexpr static int compare(const char_type* p, const char_type* q, const size_t n) noexcept {
//			bool equal = false;
//			bool less = false;
//			for (size_t i = 0; i < n; i++) {
//				if (eq(p[i], q[i])) {
//					if (less) {
//						return -1;
//					}
//					equal = true;
//				}
//				else {
//					if (lt(p[i], q[i])) {
//						if (equal) {
//							return -1;
//						}
//						less = true;
//					}
//					else {
//						return 1;
//					}
//				}
//			}
//			return 0;
//		}
//		constexpr static size_t length(const char_type* p) noexcept {
//			const char_type val = char_type();
//			size_t count{};
//			while (*p != val) {
//				count++;
//				p++;
//			}
//			return count;
//		}
//		constexpr static const char_type* find(const char_type* p, const size_t n, const char_type c) noexcept {
//			for (size_t i = 0; i < n; i++) {
//				if (eq(p[i], c)) {
//					return p;
//				}
//			}
//			return nullptr;
//		}
//		constexpr static void assign(char_type& r, const char_type& d) noexcept {
//			r = d;
//		}
//		static char_type* assign(char_type* s, const size_t n, const char_type c) noexcept {
//			for (size_t i = 0; i < n; i++) {
//				assign(s[i], c);
//			}
//			return s;
//		}
//		static char_type* move(char_type* s, const char_type* p, const size_t n) noexcept {
//			if (p < s) {
//				for (size_t i = n; i > 0; i--) {
//					assign(s[i - 1], p[i - 1]);
//				}
//			}
//			else {
//				for (size_t i = 0; i < n; i++) {
//					assign(s[i], p[i]);
//				}
//			}
//			return s;
//		}
//		static char_type* copy(char_type* s, const char_type* p, const size_t n) noexcept {
//			for (size_t i = 0; i < n; i++) {
//				assign(s[i], p[i]);
//			}
//			return s;
//		}
//		constexpr static int_type eof() {
//			return numeric_limits<int_type>::max();
//		}
//		constexpr static int_type not_eof(const int_type e) {
//			return (e != eof() ? e : !e);
//		}
//		constexpr static char_type to_char_type(const int_type e) {
//			return static_cast<char_type>(e);
//		}
//		constexpr static int_type to_int_type(const char_type c) {
//			return static_cast<int_type>(c);
//		}
//		constexpr static bool eq_int_type(const int_type e, const int_type f) {
//			return e == f;
//		}
//	};
//}

using unsignedCharTraits = ::std::char_traits<char>;

image_surface::image_surface(experimental::io2d::format fmt, int width, int height)
	: surface({ cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), nullptr }, fmt) {
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
}

#ifdef _Filesystem_support_test
image_surface::image_surface(experimental::filesystem::path f, experimental::io2d::format fmt, image_data_format idf)
#else
image_surface::image_surface(string f, experimental::io2d::format fmt, image_data_format idf)
#endif
	: surface({ nullptr, nullptr }, fmt) {

	if (fmt == format::a1) {
		throw runtime_error("Not implemented.");
	}
//	basic_ifstream<unsigned char, unsignedCharTraits> fileStream;
//#ifdef _Filesystem_support_test
//	fileStream.open(f.string(), ios_base::in | ios_base::binary | ios_base::ate);
//#else
//	fileStream.open(f, ios_base::in | ios_base::binary | ios_base::ate);
//#endif
//	auto fileStreamSize = static_cast<::std::streamoff>(fileStream.tellg());
//	if (fileStreamSize > numeric_limits<size_t>::max()) {
//		throw ::std::system_error(::std::make_error_code(errc::file_too_large));
//	}
//	auto data = make_unique<unsigned char[]>(static_cast<size_t>(fileStreamSize));
//	fileStream.seekg(0, ios::beg);
//	fileStream.read(data.get(), fileStreamSize);
//	fileStream.close();

	// Great, now to use the old-timey C file i/o because I can't specialize on unsigned char and can't spend the time to determine if using char_traits<char> with ios_base::binary will produce correct, usable data.
	FILE* imgFile = nullptr;
	unique_ptr<unsigned char[]> data{};
	long imgFileSize{};
	try {
		int testFail{};
#ifdef _Filesystem_support_test
#ifdef _MSC_VER
		testFail = fopen_s(&imgFile, f.string().c_str(), "rb");
		if (testFail != 0) {
			throw runtime_error("Failure opening file");
		}
#else
		imgFile = fopen(f.string().c_str(), "rb");
#endif
#else
		imgFile = fopen(f.c_str(), "rb");
#endif
		if (imgFile == nullptr) {
			throw runtime_error("Failure opening file");
		}
		testFail = fseek(imgFile, 0, SEEK_END);
		if (testFail != 0) {
			throw runtime_error("Failure seeking to end of file");
		}
		imgFileSize = ftell(imgFile);
		if (imgFileSize == -1) {
			throw runtime_error("Failure determining size of file");
		}
		testFail = fseek(imgFile, 0, SEEK_SET);
		if (testFail != 0) {
			throw runtime_error("Failure seeking to beginning of file");
		}
		data = make_unique<unsigned char[]>(static_cast<size_t>(imgFileSize));
		static_assert(sizeof(unsigned char) == 1U, "sizeof(unsigned char) != 1U");
		auto testFailFRead = fread(data.get(), sizeof(unsigned char), imgFileSize * sizeof(unsigned char), imgFile);
		if (testFailFRead != static_cast<size_t>(imgFileSize)) {
			throw runtime_error("Reading the file produced unexpected results");
		}
		testFail = fclose(imgFile);
		imgFile = nullptr;
		if (testFail != 0) {
			throw runtime_error("Failure closing file after reading data");
		}
	}
	catch (...) {
		if (imgFile != nullptr) {
			auto result = fclose(imgFile);
			if (result) {
				throw_with_nested(std::runtime_error("Failure closing file"));
			}
		}
		throw;
	}

	if (idf == image_data_format::png) {
#if PNG_LIBPNG_VER < 10600
		throw runtime_error("libpng versions less than 1.6.X are not supported.");
#else
		png_image img{};
		img.version = PNG_IMAGE_VERSION;
		img.opaque = nullptr;
		static_assert(::std::is_same_v<size_t, png_size_t>, "Expected size_t and png_size_t to be the same type.");
		png_image_begin_read_from_memory(&img, static_cast<png_const_voidp>(data.get()), static_cast<png_size_t>(imgFileSize));
		img.format = PNG_FORMAT_BGRA;//PNG_FORMAT_LINEAR_RGB_ALPHA;
		auto dataSize = static_cast<size_t>(PNG_IMAGE_SIZE(img));
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
		switch (fmt) {
		case std::experimental::io2d::v1::format::invalid:
		{
			cairo_surface_unmap_image(_Surface.get(), mapSfc);
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_FORMAT);
		} break;
		case std::experimental::io2d::v1::format::argb32:
		{
			for (int i = 0; i < h; i++) {
				memcpy(mapData + (i * mapStride), pixelData.get() + i * dataStride, mapStride);
			}
		} break;
		case std::experimental::io2d::v1::format::xrgb32:
		{
			for (int i = 0; i < h; i++) {
				memcpy(mapData + (i * mapStride), pixelData.get() + i * dataStride, mapStride);
			}
		} break;
		case std::experimental::io2d::v1::format::a8:
		{
			auto pixelDataPtr = pixelData.get();
			// Just copy the alpha data channel over.
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					mapData[(i * mapStride + j)] = pixelDataPtr[(i * dataStride) + (j * 4) + 3];
				}
			}
		} break;
		case std::experimental::io2d::v1::format::a1:
		{
			cairo_surface_unmap_image(_Surface.get(), mapSfc);
			throw runtime_error("Not supported.");
		} break;
		case std::experimental::io2d::v1::format::rgb16_565:
		{
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					const unsigned char* pixelValue = (pixelData.get() + (i * dataStride) + (j * 4));
					unsigned char blue = static_cast<unsigned char>(pixelValue[0] / 255.0 * 31.0 + 0.5);
					unsigned char green = static_cast<unsigned char>(pixelValue[1] / 255.0 * 63.0 + 0.5);
					unsigned char red = static_cast<unsigned char>(pixelValue[2] / 255.0 * 31.0 + 0.5);
					mapData[(i * mapStride) + (j * 2)] = static_cast<unsigned char>(((blue & 0b00011111)) | ((green & 0b00000111) << 5));
					mapData[(i * mapStride) + (j * 2) + 1] = static_cast<unsigned char>(((green & 0b00111000) >> 3) | ((red & 0b00011111) << 3));
				}
			}
		} break;
		case std::experimental::io2d::v1::format::rgb30:
		{
			for (int i = 0; i < h; i++) {
				memcpy(mapData + (i * mapStride), pixelData.get() + i * dataStride, mapStride);
			}
		} break;
		default:
		{
		} break;
	}
		cairo_surface_unmap_image(_Surface.get(), mapSfc);
		cairo_surface_mark_dirty(_Surface.get());
#endif
	}
	else if (idf == image_data_format::jpg) {
		unique_ptr<remove_pointer_t<tjhandle>, decltype(&tjDestroy)> upDecompHandle{ tjInitDecompress(), &tjDestroy };
		if (upDecompHandle == nullptr) {
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_STATUS);
		}
		auto decompHandle = upDecompHandle.get();
		//int w{};
		//int h{};
		//int jpegSubsamp{};
		//int jpegColorspace{};
		//if (tjDecompressHeader3(decompHandle, data.get(), static_cast<unsigned long>(fileStreamSize),
		//	&w, &h, &jpegSubsamp, &jpegColorspace)) {
		//	_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_STATUS);
		//}
		int w{};
		int h{};
		int jpegSubsamp{};
		if (tjDecompressHeader2(decompHandle, data.get(), static_cast<unsigned long>(imgFileSize),
			&w, &h, &jpegSubsamp)) {
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_STATUS);
		}
		auto pixelFormat = (fmt == format::a8) ? TJPF_GRAY : TJPF_BGRA;
		auto pitch = TJPAD(w * tjPixelSize[pixelFormat]);
		auto pixelData = make_unique<unsigned char[]>(pitch * h);
		if (tjDecompress2(decompHandle, data.get(), static_cast<unsigned long>(imgFileSize), pixelData.get(), w, pitch, h, pixelFormat, TJFLAG_NOREALLOC | TJFLAG_ACCURATEDCT)) {
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_STATUS);
		}
		decompHandle = nullptr;
		upDecompHandle.reset();
		_Surface = unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), w, h), &cairo_surface_destroy);
		_Context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy);
		_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
		_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
		auto mapSfc = cairo_surface_map_to_image(_Surface.get(), nullptr);
		auto mapStride = cairo_image_surface_get_stride(mapSfc);
		auto mapData = cairo_image_surface_get_data(mapSfc);
		switch (fmt) {
		case std::experimental::io2d::v1::format::invalid:
		{
			cairo_surface_unmap_image(_Surface.get(), mapSfc);
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_FORMAT);
		} break;
		case std::experimental::io2d::v1::format::argb32:
		{
			for (int i = 0; i < h; i++) {
				memcpy(mapData + (i * mapStride), pixelData.get() + i * pitch, mapStride);
			}
		} break;
		case std::experimental::io2d::v1::format::xrgb32:
		{
			for (int i = 0; i < h; i++) {
				memcpy(mapData + (i * mapStride), pixelData.get() + i * pitch, mapStride);
			}
		} break;
		case std::experimental::io2d::v1::format::a8:
		{
			cairo_surface_unmap_image(_Surface.get(), mapSfc);
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_FORMAT);
		} break;
		case std::experimental::io2d::v1::format::a1:
		{
			cairo_surface_unmap_image(_Surface.get(), mapSfc);
			throw runtime_error("Not supported.");
		} break;
		case std::experimental::io2d::v1::format::rgb16_565:
		{
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					const unsigned char* pixelValue = (pixelData.get() + (i * pitch) + (j * 4));
					unsigned char blue = static_cast<unsigned char>(pixelValue[0] / 255.0 * 31.0 + 0.5);
					unsigned char green = static_cast<unsigned char>(pixelValue[1] / 255.0 * 63.0 + 0.5);
					unsigned char red = static_cast<unsigned char>(pixelValue[2] / 255.0 * 31.0 + 0.5);
					mapData[(i * mapStride) + (j * 2)] = static_cast<unsigned char>((((blue & 0b0001'1111)) | ((green & 0b0000'0111) << 5)));
					mapData[(i * mapStride) + (j * 2) + 1] = static_cast<unsigned char>((((green & 0b0011'1000) >> 3) | ((red & 0b0001'1111) << 3)));
				}
			}
		} break;
		case std::experimental::io2d::v1::format::rgb30:
		{
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					const unsigned char* pixelValue = (pixelData.get() + (i * pitch) + (j * 4));

					uint16_t blue16 = static_cast<uint16_t>(pixelValue[0] / 255.0 * 1023.0 + 0.5);
					uint16_t green16 = static_cast<uint16_t>(pixelValue[1] / 255.0 * 1023.0 + 0.5);
					uint16_t red16 = static_cast<uint16_t>(pixelValue[2] / 255.0 * 1023.0 + 0.5);
					mapData[(i * mapStride) + (j * 4) + 0] = static_cast<unsigned char>(blue16 & 0b0000'0000'1111'1111);
					mapData[(i * mapStride) + (j * 4) + 1] = static_cast<unsigned char>(((blue16 & 0b0000'0011'0000'0000) >> 8) | ((green16 & 0b0000'0000'0011'1111) << 2));
					mapData[(i * mapStride) + (j * 4) + 2] = static_cast<unsigned char>(((green16 & 0b0000'0011'1100'0000) >> 6) | ((red16 & 0b0000'0000'0000'1111) << 4));
					mapData[(i * mapStride) + (j * 4) + 3] = static_cast<unsigned char>(((red16 & 0b0000'0011'1111'0000) >> 4) | 0b0000'0000'1100'0000);
				}
			}
		} break;
		default:
		{
			cairo_surface_unmap_image(_Surface.get(), mapSfc);
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_FORMAT);
		} break;
		}
		cairo_surface_unmap_image(_Surface.get(), mapSfc);
		cairo_surface_mark_dirty(_Surface.get());
	}
	else {
		throw system_error(make_error_code(errc::operation_not_supported));
	}
}

#ifdef _Filesystem_support_test
void image_surface::save(experimental::filesystem::path f, image_data_format idf) {
#else
void image_surface::save(string f, image_data_format idf) {
#endif
	switch (idf) {
	case image_data_format::png:
	{
#if PNG_LIBPNG_VER < 10600
		throw runtime_error("libpng versions less than 1.6.X are not supported.");
#else
		png_image pngImg{};
		pngImg.opaque = nullptr;
		pngImg.version = PNG_IMAGE_VERSION;
		pngImg.width = width();
		pngImg.height = height();
		auto map = cairo_surface_map_to_image(_Surface.get(), nullptr);
		auto mapData = cairo_image_surface_get_data(map);
		const auto w = width();
		const auto h = height();
		const size_t sfcStride = w * 4;
		const size_t mapStride = stride();
		auto sfcData = make_unique<unsigned char[]>(sfcStride * h);
		switch (_Format)
		{
		case std::experimental::io2d::v1::format::invalid:
		{
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_FORMAT);
		} break;
		case std::experimental::io2d::v1::format::argb32:
		{
			pngImg.format = PNG_FORMAT_BGRA;
			for (int i = 0; i < h; i++) {
				memcpy(sfcData.get() + (i * sfcStride), mapData + (i * sfcStride), sfcStride);
			}
		} break;
		case std::experimental::io2d::v1::format::xrgb32:
		{
			pngImg.format = PNG_FORMAT_BGRA; // We'll write the alpha as-is in case someone was storing some data in them.
			for (int i = 0; i < h; i++) {
				memcpy(sfcData.get() + (i * sfcStride), mapData + (i * sfcStride), sfcStride);
			}
		} break;
		case std::experimental::io2d::v1::format::a8:
		{
			pngImg.format = PNG_FORMAT_BGRA;
			auto sfcDataPtr = sfcData.get();
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					sfcDataPtr[(i * sfcStride) + (j * 4) + 0] = 0;
					sfcDataPtr[(i * sfcStride) + (j * 4) + 1] = 0;
					sfcDataPtr[(i * sfcStride) + (j * 4) + 2] = 0;
					sfcDataPtr[(i * sfcStride) + (j * 4) + 3] = mapData[(i * mapStride) + j];
				}
			}
		} break;
		case std::experimental::io2d::v1::format::a1: // This format is going to be obliterated in R5.
		{
			pngImg.format = PNG_FORMAT_BGRA; // The pixels are stored in bits with a 32-bit int, native-endian.
			throw runtime_error("Not supported.");
		} break;
		case std::experimental::io2d::v1::format::rgb16_565:
		{
			pngImg.format = PNG_FORMAT_BGRA; // We need to convert the data ourselves and pad it out to 32 bits.
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					unsigned char blue = static_cast<unsigned char>((mapData[(i * mapStride) + (j * 2)] & 0b0001'1111) / 31.0 * 255.0 + 0.5);
					unsigned char green = static_cast<unsigned char>((((mapData[(i * mapStride) + (j * 2)] & 0b1110'0000) >> 5) | ((mapData[(i * mapStride) + (j * 2) + 1] & 0b0000'0111) << 3)) / 63.0 * 255.0 + 0.5);
					unsigned char red = static_cast<unsigned char>(((mapData[(i * mapStride) + (j * 2) + 1] & 0b1111'1000) >> 3) / 31.0 * 255.0 + 0.5);
					const unsigned char alpha{ 0xFF };
					auto sfcPixel = (sfcData.get() + (i * sfcStride) + (j * 4));
					sfcPixel[0] = blue;
					sfcPixel[1] = green;
					sfcPixel[2] = red;
					sfcPixel[3] = alpha;
				}
			}
		} break;
		case std::experimental::io2d::v1::format::rgb30:
		{
			pngImg.format = PNG_FORMAT_BGRA; // We'll write this out as is; despite its name, it's 32 bits
			for (int i = 0; i < h; i++) {
				memcpy(sfcData.get() + (i * sfcStride), mapData + (i * sfcStride), sfcStride);
			}
		} break;
		default:
		{
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_FORMAT);
		} break;
		}
		pngImg.colormap_entries = 0;
		const int rowStride = width() * PNG_IMAGE_PIXEL_CHANNELS(pngImg.format);
		const int convertTo8Bit = 0;
		const void* colormap = nullptr;
		png_alloc_size_t outputMemBytesExpected{};
		png_image_write_to_memory(&pngImg, nullptr, &outputMemBytesExpected, convertTo8Bit, sfcData.get(), rowStride, colormap);
		auto outputMem = make_unique<unsigned char[]>(outputMemBytesExpected);
		png_alloc_size_t outputMemBytesActual = outputMemBytesExpected;
		png_image_write_to_memory(&pngImg, outputMem.get(), &outputMemBytesActual, convertTo8Bit, sfcData.get(), rowStride, colormap);
		if (outputMemBytesActual > outputMemBytesExpected) {
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_SIZE);
		}
		// Now write the memory out to the file.
		// Great, now to use the old-timey C file i/o because I can't specialize on unsigned char and can't spend the time to determine if using char_traits<char> with ios_base::binary will produce correct, usable data.
		FILE* imgFile = nullptr;
		//long imgFileSize{};
		try {
			int testFail{};
#ifdef _Filesystem_support_test
#ifdef _MSC_VER
			auto fopensErr = fopen_s(&imgFile, f.string().c_str(), "wb");
			if (fopensErr != 0) {
				throw runtime_error("Failure opening file");
			}
#else
			imgFile = fopen(f.string().c_str(), "wb");
#endif
#else
			imgFile = fopen(f.c_str(), "wb");
#endif
			(void)outputMemBytesActual;
			if (imgFile == nullptr) {
				throw runtime_error("Failure opening file");
			}
			static_assert(sizeof(unsigned char) == 1U, "sizeof(unsigned char) != 1U ?");
			const void* outputMemData = static_cast<const void*>(outputMem.get());
			size_t ucharsWritten = fwrite(outputMemData, sizeof(unsigned char), static_cast<size_t>(outputMemBytesExpected), imgFile);
			if (ucharsWritten != static_cast<size_t>(outputMemBytesExpected)) {
				throw runtime_error("Failure writing data to file");
			}
			testFail = fflush(imgFile);
			if (testFail != 0) {
				throw runtime_error("Error flushing data to file");
			}
			testFail = fclose(imgFile);
			imgFile = nullptr;
			if (testFail != 0) {
				throw runtime_error("Failure closing file after reading data");
			}
		}
		catch (...) {
			if (imgFile != nullptr) {
				auto result = fclose(imgFile);
				if (result) {
					throw_with_nested(std::runtime_error("Failure closing file"));
				}
			}
			throw;
		}

		//		basic_ofstream<unsigned char, char_traits<unsigned char>> fileStream;
//#if (_MSC_VER >= 1910 || HAVE_FILESYSTEM)
//		fileStream.open(f.string(), ios_base::out | ios_base::binary | ios_base::trunc);
//#else
//		fileStream.open(f, ios_base::out | ios_base::binary | ios_base::trunc);
//#endif
//		if (fileStream.fail()) {
//			throw runtime_error("Failed to open file for writing.");
//		}
//		fileStream.write(outputMem.get(), outputMemBytesActual);
//		if (fileStream.fail()) {
//			throw runtime_error("Failed to write data to file.");
//		}
//		fileStream.flush();
//		if (fileStream.fail()) {
//			throw runtime_error("Failed to write data to file.");
//		}
//		fileStream.close();
//		if (fileStream.fail()) {
//			throw runtime_error("Failed to write data to file.");
//		}
#endif
	} break;
	case image_data_format::jpg:
	{
		auto map = cairo_surface_map_to_image(_Surface.get(), nullptr);
		auto mapData = cairo_image_surface_get_data(map);
		const auto w = width();
		const auto h = height();
		const size_t sfcStride = (_Format == format::a8 ? w : w * 4);
		const size_t mapStride = stride();
		auto sfcData = make_unique<unsigned char[]>(sfcStride * h);

		switch (_Format)
		{
		case std::experimental::io2d::v1::format::invalid:
		{
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_FORMAT);
		} break;
		case std::experimental::io2d::v1::format::argb32:
		{
			for (int i = 0; i < h; i++) {
				memcpy(sfcData.get() + (i * sfcStride), mapData + (i * sfcStride), sfcStride);
			}
		} break;
		case std::experimental::io2d::v1::format::xrgb32:
		{
			for (int i = 0; i < h; i++) {
				memcpy(sfcData.get() + (i * sfcStride), mapData + (i * sfcStride), sfcStride);
			}
		} break;
		case std::experimental::io2d::v1::format::a8:
		{
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_FORMAT);
		} break;
		case std::experimental::io2d::v1::format::a1:
			throw runtime_error("Not supported.");
			break;
		case std::experimental::io2d::v1::format::rgb16_565:
		{
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					unsigned char blue = static_cast<unsigned char>((mapData[(i * mapStride) + (j * 2)] & 0b0001'1111) / 31.0 * 255.0 + 0.5);
					unsigned char green = static_cast<unsigned char>((((mapData[(i * mapStride) + (j * 2)] & 0b1110'0000) >> 5) | ((mapData[(i * mapStride) + (j * 2) + 1] & 0b0000'0111) << 3)) / 63.0 * 255.0 + 0.5);
					unsigned char red = static_cast<unsigned char>(((mapData[(i * mapStride) + (j * 2) + 1] & 0b1111'1000) >> 3) / 31.0 * 255.0 + 0.5);
					const unsigned char alpha{ 0xFF };
					auto sfcPixel = (sfcData.get() + (i * sfcStride) + (j * 4));
					sfcPixel[0] = blue;
					sfcPixel[1] = green;
					sfcPixel[2] = red;
					sfcPixel[3] = alpha;
				}
			}
		} break;
		case std::experimental::io2d::v1::format::rgb30:
		{
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					auto pixelData = (mapData + (i * mapStride) + (j * 4));
					uint16_t blue10 = static_cast<uint16_t>((pixelData[0] & 0b0000'0000'1111'1111) | ((pixelData[1] & 0b0000'0000'0000'0011) << 8));
					uint16_t green10 = static_cast<uint16_t>(((pixelData[1] & 0b0000'0000'1111'1100) >> 2) | ((pixelData[2] & 0b0000'0000'0000'1111) << 6));
					uint16_t red10 = static_cast<uint16_t>(((pixelData[2] & 0b0000'0000'1111'0000) >> 4) | ((pixelData[3] & 0b0000'0000'0011'1111) << 4));
					const unsigned char alpha{ 0xFF };
					auto sfcPixel = (sfcData.get() + (i * sfcStride) + (j * 4));
					sfcPixel[0] = static_cast<unsigned char>(blue10 / 1023.0 * 255.0 + 0.5);
					sfcPixel[1] = static_cast<unsigned char>(green10 / 1023.0 * 255.0 + 0.5);
					sfcPixel[2] = static_cast<unsigned char>(red10 / 1023.0 * 255.0 + 0.5);
					sfcPixel[3] = alpha;
				}
			}
		} break;
		break;
		default:
		{
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_FORMAT);
		} break;
		}
		unique_ptr<remove_pointer_t<tjhandle>, decltype(&tjDestroy)> compressor(tjInitCompress(), &tjDestroy);
		const auto subsamp = TJSAMP_444;
		//auto dataSize = tjBufSize(w, h, subsamp);
		unsigned char* jpgBuf = nullptr;
		unsigned long jpgBufSize{};
		tjCompress2(compressor.get(), sfcData.get(), w, sfcStride, h, TJPF_BGRA, &jpgBuf, &jpgBufSize, subsamp, 95, 0);
		unique_ptr<unsigned char[], decltype(&tjFree)> jpgBufUniquePtr{ jpgBuf, &tjFree };
		jpgBuf = nullptr;
		// Now write the memory out to the file.
		
		// Great, now to use the old-timey C file i/o because I can't specialize on unsigned char and can't spend the time to determine if using char_traits<char> with ios_base::binary will produce correct, usable data.
		FILE* imgFile = nullptr;
		//long imgFileSize{};
		try {
			int testFail{};
#ifdef _Filesystem_support_test
#ifdef _MSC_VER
			auto fopensTest = fopen_s(&imgFile, f.string().c_str(), "wb");
			if (fopensTest != 0) {
				throw runtime_error("Failure opening file");
			}
#else
			imgFile = fopen(f.string().c_str(), "wb");
#endif
#else
			imgFile = fopen(f.c_str(), "wb");
#endif
			if (imgFile == nullptr) {
				throw runtime_error("Failure opening file");
			}
			static_assert(sizeof(unsigned char) == 1U, "sizeof(unsigned char) != 1U ?");
			size_t ucharsWritten = fwrite(jpgBufUniquePtr.get(), sizeof(unsigned char), static_cast<size_t>(jpgBufSize), imgFile);
			if (ucharsWritten != static_cast<size_t>(jpgBufSize)) {
				throw runtime_error("Failure writing data to file");
			}
			testFail = fflush(imgFile);
			if (testFail != 0) {
				throw runtime_error("Error flushing data to file");
			}
			testFail = fclose(imgFile);
			imgFile = nullptr;
			if (testFail != 0) {
				throw runtime_error("Failure closing file after reading data");
			}
		}
		catch (...) {
			if (imgFile != nullptr) {
				auto result = fclose(imgFile);
				if (result) {
					throw_with_nested(std::runtime_error("Failure closing file"));
				}
			}
			throw;
		}

		//		basic_ofstream<unsigned char, char_traits<unsigned char>> fileStream;
//#ifdef _Filesystem_support_test
//		fileStream.open(f.string(), ios_base::out | ios_base::binary | ios_base::trunc);
//#else
//		fileStream.open(f, ios_base::out | ios_base::binary | ios_base::trunc);
//#endif
//		if (fileStream.fail()) {
//			throw runtime_error("Failed to open file for writing.");
//		}
//		fileStream.write(jpgBufUniquePtr.get(), jpgBufSize);
//		if (fileStream.fail()) {
//			throw runtime_error("Failed to write data to file.");
//		}
//		fileStream.flush();
//		if (fileStream.fail()) {
//			throw runtime_error("Failed to write data to file.");
//		}
//		fileStream.close();
//		if (fileStream.fail()) {
//			throw runtime_error("Failed to write data to file.");
//		}
	} break;
	default:
	{
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_FORMAT);
	} break;
	}
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

#ifdef __clang__
#pragma clang diagnostic pop
#endif
