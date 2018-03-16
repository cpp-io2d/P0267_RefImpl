#include "comparison.h"
#include <optional>
#include <fstream>
#include <vector>
#include <png.h>

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

static uint32_t ToRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    uint32_t rgba = 0;
    rgba |= (uint32_t)red;
    rgba |= (uint32_t)green << 8;
    rgba |= (uint32_t)blue << 16;
    rgba |= (uint32_t)alpha << 24;
    return rgba;
}

static uint8_t GetRed(uint32_t rgba) { return (uint8_t)(rgba & 0xFF); }
static uint8_t GetGreen(uint32_t rgba) { return (uint8_t)((rgba >> 8) & 0xFF); }
static uint8_t GetBlue(uint32_t rgba) { return (uint8_t)((rgba >> 16) & 0xFF); }
static uint8_t GetAlpha(uint32_t rgba) { return (uint8_t)((rgba >> 24) & 0xFF); }

struct RawImage
{
    vector<uint32_t> pixmap;
    int width = 0;
    int height = 0;
};

static bool operator==(const RawImage& lhs, const RawImage& rhs)
{
    return  lhs.height == rhs.height &&
            lhs.width == rhs.width &&
            equal(begin(lhs.pixmap), end(lhs.pixmap), begin(rhs.pixmap));
}

struct MemorySource
{
    const vector<uint8_t> *data;
    int position = 0;
};

template <typename T>
auto at_scope_end( T _l )
{
    struct guard
    {
        guard( T &&_lock ): m_l(std::move(_lock)){}
        guard( guard&& ) = default;
        ~guard() noexcept { m_l(); }
        T m_l;
    };
    return guard( std::move(_l) );
}

static void Feed(png_structp png , png_bytep out, png_size_t sz )
{
    png_voidp io_ptr = png_get_io_ptr(png);
    auto &memory_source = *reinterpret_cast<MemorySource*>(io_ptr);
    
    if( memory_source.position + sz > memory_source.data->size()  ) {
        png_error(png, "Broken file");
        return;
    }
    
    memcpy(out, memory_source.data->data() + memory_source.position, sz );
    memory_source.position += sz;
}

static optional<RawImage> Load(const vector<uint8_t> &data)
{
    const auto signature_len = 8;
    if( data.size() < signature_len || !png_check_sig(data.data(), signature_len) )
        return nullopt;
    
    MemorySource memory_source;
    memory_source.data = &data;
    memory_source.position = signature_len;
    png_structp png_ptr = nullptr;
    png_infop info_ptr = nullptr;
    auto cleanup = at_scope_end([&]{ png_destroy_read_struct(&png_ptr, &info_ptr, nullptr); });
    
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if( png_ptr == nullptr )
        return nullopt;

    info_ptr = png_create_info_struct(png_ptr);
    if( info_ptr == nullptr )
        return nullopt;
    
    png_set_read_fn(png_ptr, (void*)&memory_source, &Feed);
    png_set_sig_bytes(png_ptr, signature_len);
    png_read_info(png_ptr, info_ptr);
    
    png_uint_32 width = 0;
    png_uint_32 height = 0;
    int bit_depth = 0;
    int color_type = -1;
    png_uint_32 retval = png_get_IHDR(png_ptr, info_ptr,
                                      &width,
                                      &height,
                                      &bit_depth,
                                      &color_type,
                                      nullptr, nullptr, nullptr);
    if( retval != 1 )
        return nullopt;
    
    if( color_type != PNG_COLOR_TYPE_RGB_ALPHA )
        return nullopt;
    
    RawImage raw_image;
    raw_image.width = width;
    raw_image.height = height;
    raw_image.pixmap.resize(width*height);
    
    auto bytesPerRow = png_get_rowbytes(png_ptr, info_ptr);
    auto row = make_unique<uint8_t[]>(bytesPerRow);
    
    for(int row_index = 0; row_index < height; ++row_index) {
        png_read_row(png_ptr, row.get(), nullptr);
        for(int col_index = 0, byte_index = 0; col_index < width; ++col_index) {
            auto red   = row[byte_index++];
            auto green = row[byte_index++];
            auto blue  = row[byte_index++];
            auto alpha = row[byte_index++];
            raw_image.pixmap[ row_index*width + col_index ] = ToRGBA(red, green, blue, alpha);
        }
    }
    return move(raw_image);
}

static optional<RawImage> ReadFile(const std::string &path)
{
    ifstream ifs(path, ifstream::in | ifstream::binary);
    vector<uint8_t> contents((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
    if( contents.empty() )
        return nullopt;
    
    return Load(contents);
}

bool ComparePNGExact( const string &path1, const string &path2 )
{
    auto img1 = ReadFile(path1);
    auto img2 = ReadFile(path2);
    if( !img1 || !img2 )
        return false;
    
    return *img1 == *img2;
}

bool ComparePNGWithTolerance( const std::string &path1, const std::string &path2, float intensity_tolerance , int spatial_tolerance )
{
    auto img1 = ReadFile(path1);
    auto img2 = ReadFile(path2);
    if( !img1 || !img2 )
        return false;
    if( img1->width != img2->width || img1->height != img2->height )
        return false;
    
    auto abs_intensity_tolerance = static_cast<int>(256.f * intensity_tolerance);
    auto pred = [abs_intensity_tolerance](uint32_t first, uint32_t second) -> bool {
        return abs( int(GetRed(first))   - int(GetRed(second))   )  <= abs_intensity_tolerance &&
               abs( int(GetGreen(first)) - int(GetGreen(second)) )  <= abs_intensity_tolerance &&
               abs( int(GetBlue(first))  - int(GetBlue(second))  )  <= abs_intensity_tolerance &&
               abs( int(GetAlpha(first)) - int(GetAlpha(second)) )  <= abs_intensity_tolerance ;
    };
    return equal( begin(img1->pixmap), end(img1->pixmap), begin(img2->pixmap), end(img2->pixmap), pred );
}

bool ComparePNGWithTolerance( std::experimental::io2d::image_surface &image, const std::string &path2, float intensity_tolerance, int spatial_tolerance )
{
    image.save("tmp.png", image_file_format::png);
    return ComparePNGWithTolerance("tmp.png", path2, intensity_tolerance, spatial_tolerance);
}

bool ComparePNGExact( image_surface &image, const string &path2 )
{
    image.save("tmp.png", image_file_format::png);
    return ComparePNGExact("tmp.png", path2);
}
