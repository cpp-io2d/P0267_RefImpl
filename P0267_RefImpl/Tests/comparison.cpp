#include "comparison.h"
#include <optional>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <png.h>

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

[[maybe_unused]] static const auto g_TMPFN = "tmp.png";

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
    memory_source.position += (int)sz;
}

static bool HasPNGSignature( const vector<uint8_t> &data )
{
    const auto signature_len = 8;
    if( data.size() < signature_len )
        return false;
    
	array<uint8_t, signature_len> sign_buf;
    copy( begin(data), begin(data) + signature_len, begin(sign_buf) );
    if( png_sig_cmp(&sign_buf[0], 0, signature_len) != 0 )
        return false;
 
    return true;
}

static optional<_Interchange_buffer> LoadPNGIntoR8G8B8A8(const vector<uint8_t> &data)
{
    if( !HasPNGSignature(data) )
        return nullopt;
    
    const auto signature_len = 8;
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
    
    if( color_type != PNG_COLOR_TYPE_RGB_ALPHA &&
        color_type != PNG_COLOR_TYPE_RGB )
        return nullopt;
    
    _Interchange_buffer buffer(_Interchange_buffer::pixel_layout::r8g8b8a8,
                               _Interchange_buffer::alpha_mode::straight,
                               width,
                               height);
    
    auto buffer_data = (uint32_t*)buffer.data();
    auto bytesPerRow = png_get_rowbytes(png_ptr, info_ptr);
    auto row = make_unique<uint8_t[]>(bytesPerRow);
    
    if( color_type == PNG_COLOR_TYPE_RGB_ALPHA ) {
        for(int row_index = 0; row_index < (int)height; ++row_index) {
            png_read_row(png_ptr, row.get(), nullptr);
            for(int col_index = 0, byte_index = 0; col_index < (int)width; ++col_index) {
                auto red   = row[byte_index++];
                auto green = row[byte_index++];
                auto blue  = row[byte_index++];
                auto alpha = row[byte_index++];
                buffer_data[ row_index*width + col_index ] = ToRGBA(red, green, blue, alpha);
            }
        }
    }
    else if( color_type == PNG_COLOR_TYPE_RGB ) {
        for(int row_index = 0; row_index < (int)height; ++row_index) {
            png_read_row(png_ptr, row.get(), nullptr);
            for(int col_index = 0, byte_index = 0; col_index < (int)width; ++col_index) {
                auto red   = row[byte_index++];
                auto green = row[byte_index++];
                auto blue  = row[byte_index++];
                buffer_data[ row_index*width + col_index ] = ToRGBA(red, green, blue, uint8_t(255));
            }
        }        
    }
    
    return move(buffer);
}

static optional<_Interchange_buffer> ReadFile(const std::string &path)
{
    ifstream ifs(path, ifstream::in | ifstream::binary);
    vector<uint8_t> contents((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
    if( contents.empty() ) {
        return nullopt;
    }
    
    return LoadPNGIntoR8G8B8A8(contents);
}

template <class GS, enable_if_t<is_invocable<decltype(GS::surfaces::_Copy_to_interchange_buffer),
                                             typename GS::surfaces::image_surface_data_type&,
                                             _Interchange_buffer::pixel_layout,
                                             _Interchange_buffer::alpha_mode>::value,
                                             int> = 0>
static optional<_Interchange_buffer> ToInterchangeBufferImpl(basic_image_surface<GS> &image, int)
{
    // fast path - access memory directly
    auto buffer = GS::surfaces::_Copy_to_interchange_buffer(image.data(),
                                                            _Interchange_buffer::pixel_layout::r8g8b8a8,
                                                            _Interchange_buffer::alpha_mode::straight); 
    return move(buffer);
}

template <class GS>
static optional<_Interchange_buffer> ToInterchangeBufferImpl(basic_image_surface<GS> &image, long)
{
    // long path - store as PNG and load it afterwards    
    [[maybe_unused]] static auto warn = []{
        cerr << "Slow path is being used for accessing image_surface data. "
            "Consider providing a _Copy_to_interchange_buffer() function." << endl;
        return true;
    }(); 
    image.save(g_TMPFN, image_file_format::png);
    return ReadFile(g_TMPFN);
}

static optional<_Interchange_buffer> ToInterchangeBuffer(image_surface &image)
{
    return ToInterchangeBufferImpl(image, 0);
}

static bool CompareWithIntensityTolerance(const _Interchange_buffer& first,
                                          const _Interchange_buffer& second,
                                          float intensity_tolerance)
{
    assert( first.layout() == _Interchange_buffer::pixel_layout::r8g8b8a8 &&
            first.layout() == second.layout() &&
            first.alpha() == _Interchange_buffer::alpha_mode::straight &&
            first.alpha() == second.alpha() );
    
    if( first.width() != second.width() || first.height() != second.height()  )
        return false;
    
    auto abs_intensity_tolerance = static_cast<int>(256.f * intensity_tolerance);
    auto pred = [abs_intensity_tolerance](uint32_t first, uint32_t second) -> bool {
        return abs( int(GetRed(first))   - int(GetRed(second))   )  <= abs_intensity_tolerance &&
               abs( int(GetGreen(first)) - int(GetGreen(second)) )  <= abs_intensity_tolerance &&
               abs( int(GetBlue(first))  - int(GetBlue(second))  )  <= abs_intensity_tolerance &&
               abs( int(GetAlpha(first)) - int(GetAlpha(second)) )  <= abs_intensity_tolerance ;
    };
    return equal((const uint32_t*)first.data(),
                 (const uint32_t*)first.data() + first.width() * first.height(),
                 (const uint32_t*)second.data(),
                 (const uint32_t*)second.data() + second.width() * second.height(),
                 pred );
}

static bool CompareWithIntensityAndSpatialTolerance(const _Interchange_buffer& first,
                                                    const _Interchange_buffer& second,
                                                    float intensity_tolerance,
                                                    int spatial_tolerance )
{    
    assert( first.layout() == _Interchange_buffer::pixel_layout::r8g8b8a8 &&
           first.layout() == second.layout() &&
           first.alpha() == _Interchange_buffer::alpha_mode::straight &&
           first.alpha() == second.alpha() );
    
    if( first.width() != second.width() || first.height() != second.height()  )
        return false;
    
    auto abs_intensity_tolerance = static_cast<int>(256.f * intensity_tolerance);
    auto cmp = [abs_intensity_tolerance](uint32_t first, uint32_t second) -> bool {
        return abs( int(GetRed(first))   - int(GetRed(second))   )  <= abs_intensity_tolerance &&
        abs( int(GetGreen(first)) - int(GetGreen(second)) )  <= abs_intensity_tolerance &&
        abs( int(GetBlue(first))  - int(GetBlue(second))  )  <= abs_intensity_tolerance &&
        abs( int(GetAlpha(first)) - int(GetAlpha(second)) )  <= abs_intensity_tolerance ;
    };
    auto pred = [cmp, spatial_tolerance, &first, &second](int x, int y) -> bool {
        auto v = ((const uint32_t*)first.data())[x + y * first.width()];        
        const auto top = max(y - spatial_tolerance, 0);
        const auto bottom = min(second.height()-1, y + spatial_tolerance);
        const auto left = max(x - spatial_tolerance, 0);
        const auto right = min(second.width()-1, x + spatial_tolerance);
        for( int iy = top; iy <= bottom; ++iy )
            for( int ix = left; ix <= right; ++ix )
                if( cmp(v, ((const uint32_t*)second.data())[ix + iy * second.width()]) )                
                    return true;
        return false;
    };
    for( auto y = 0; y < first.height(); ++y )
        for( auto x = 0; x < first.width(); ++x )
            if( !pred(x, y) )
                return false;    
    
    return true;
}

static bool CompareExact( const _Interchange_buffer &buff1, const _Interchange_buffer &buff2 )
{
    return buff1 == buff2;
}

static bool Compare(const _Interchange_buffer& first,
                    const _Interchange_buffer& second,
                    float intensity_tolerance,
                    int spatial_tolerance)
{
    if( intensity_tolerance == 0.f && spatial_tolerance == 0 )
        return CompareExact(first, second);
    else if( spatial_tolerance == 0 )
        return CompareWithIntensityTolerance(first, second, intensity_tolerance);        
    else 
        return CompareWithIntensityAndSpatialTolerance(first, second, intensity_tolerance, spatial_tolerance);    
}

bool CompareWithPNGImage(image_surface &image,
                         const std::string &path_to_reference_image,
                         float intensity_tolerance,
                         int spatial_tolerance)
{
    assert( intensity_tolerance >= 0. && intensity_tolerance <= 1.f );
    assert( spatial_tolerance >= 0 && spatial_tolerance <= 10 );
        
    auto img1 = ToInterchangeBuffer(image);
    if( !img1 ) {
        cerr << "Failed to read image_surface data." << endl;
        return false;
    }
    
    auto img2 = ReadFile(path_to_reference_image);
    if( !img2 ) {
        cerr << "Failed to load an image at " << path_to_reference_image << "." << endl;
        return false;
    }
    
    return Compare(*img1, *img2, intensity_tolerance, spatial_tolerance);
}

bool CompareImages(std::experimental::io2d::image_surface &first,
                   std::experimental::io2d::image_surface &second,
                   float intensity_tolerance,
                   int spatial_tolerance)
{
    assert( intensity_tolerance >= 0. && intensity_tolerance <= 1.f );
    assert( spatial_tolerance >= 0 && spatial_tolerance <= 10 );
    
    auto img1 = ToInterchangeBuffer(first);
    if( !img1 ) {
        cerr << "Failed to read image_surface data." << endl;
        return false;
    }
    
    auto img2 = ToInterchangeBuffer(second);
    if( !img2 ) {
        cerr << "Failed to read image_surface data." << endl;
        return false;
    }
    
    return Compare(*img1, *img2, intensity_tolerance, spatial_tolerance);
}

bool CompareImageColor(std::experimental::io2d::image_surface &image,
                       int x,
                       int y,
                       std::experimental::io2d::rgba_color color,
                       float intensity_tolerance)
{
    auto buff_opt = ToInterchangeBuffer(image);
    if( !buff_opt )
        return false;
    auto &buff = *buff_opt;
    
    if( x < 0 || x >= buff.width() || y < 0 || y >= buff.height() )
        return false;
    
    auto at = [&](int px, int py) -> uint32_t {
        return *((uint32_t*)buff.data() + buff.width() * py + px);
    };
    auto to_float = [](uint8_t c){
        return static_cast<float>(c) / 255.f;
    };    
    
    auto value = at(x, y);
    auto r = to_float(GetRed(value));
    auto g = to_float(GetGreen(value));
    auto b = to_float(GetBlue(value));
    auto a = to_float(GetAlpha(value));
    
    auto valid = abs( r - color.r() ) <= intensity_tolerance &&
                 abs( g - color.g() ) <= intensity_tolerance &&
                 abs( b - color.b() ) <= intensity_tolerance &&
                 abs( a - color.a() ) <= intensity_tolerance;
    return valid;
}
