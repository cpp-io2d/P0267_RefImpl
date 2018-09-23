#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

/*
Current state of blend operators compatibility:

Operator        | Testing?| Cairo     | CoreGraphics  |
===================================================================================================
over            |   yes   |   +       |     +         |
clear           |   yes   |   +       |     +         |
source          |   yes   |   +       |     +         |
in              |   yes   |   +       |     +         |
out             |   yes   |   +       |     +         |
atop            |   yes   |   +       |     +         |
dest            |   NO!!! |   +       |    N/A [0]    |
dest_over       |   yes   |   +       |     +         |
dest_in         |   yes   |   +       |     +         |
dest_out        |   yes   |   +       |     +         |
dest_atop       |   yes   |   +       |     +         |
xor_op          |   yes   |   +       |     +         |
add             |   yes   |   +       |     +         |
saturate        |   NO!!! |   +       |    N/A [1]    |
multiply        |   yes   |   +       |     +         |
screen          |   yes   |   +       |     +         |
overlay         |   yes   |   +       |     +         |
darken          |   yes   |   +       |     +         |
lighten         |   yes   |   +       |     +         |
color_dodge     |   NO!!! |   +       | not comp. [2] |
color_burn      |   NO!!! |   +       | not comp. [3] |
hard_light      |   yes   |   +       |     +         |
soft_light      |   NO!!! |   +       | not comp. [4] |
difference      |   yes   |   +       |     +         |
exclusion       |   yes   |   +       |     +         |
hsl_hue         |   yes   |   +       |     +         |
hsl_saturation  |   yes   |   +       |     +         |
hsl_color       |   yes   |   +       |     +         |
hsl_luminosity  |   yes   |   +       |     +         |
===================================================================================================
[0] there's no such operator in CoreGraphics.
[1] there's no such operator in CoreGraphics.
[2] color_dodge in CoreGraphics is kCGBlendModeColorDodge and it apparently follows another formula, which is not specified in Apple's docs. See ColorDodge() for details.
[3] color_burn in CoreGraphics is kCGBlendModeColorBurn and it apparently follows another formula, which is not specified in Apple's docs. See ColorBurn() for details.
[4] soft_light in CoreGraphics is kCGBlendModeSoftLight and it apparently follows another formula, which is not specified in Apple's docs. See SoftLight() for details.
 
*/

namespace Blend {
// zero alpha processing does not match the mathetical model in some operators,
// which is coherent between Cairo and CoreGraphics.
    
static rgba_color Clear( const rgba_color& /*a*/, const rgba_color& /*b*/ ) noexcept
{
    return rgba_color::transparent_black;
}

static rgba_color Over( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto inv = 1.f - a.a();
    auto ra = a.a() + b.a() * inv;
    if( ra <= numeric_limits<float>::min() )
        return rgba_color::transparent_black;
    auto rr = (a.r() * a.a() + b.r() * b.a() * inv) / ra;
    auto rg = (a.g() * a.a() + b.g() * b.a() * inv) / ra;
    auto rb = (a.b() * a.a() + b.b() * b.a() * inv) / ra;
    return {rr, rg, rb, ra};
}
    
static rgba_color Source( const rgba_color& a, const rgba_color& /*b*/ ) noexcept
{
    if( a.a() <= numeric_limits<float>::min() )
        return rgba_color::transparent_black;
    return a;
}
    
static rgba_color In( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto ra = a.a() * b.a();
    if( ra <= numeric_limits<float>::min() )
        return rgba_color::transparent_black;
    return {a.r(), a.g(), a.b(), ra};
}

static rgba_color Out( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto ra = a.a() * (1.f - b.a());
    if( ra <= numeric_limits<float>::min() )
        return rgba_color::transparent_black;
    return {a.r(), a.g(), a.b(), ra};
}

static rgba_color Atop( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto ra = b.a();
    if( ra <= numeric_limits<float>::min() )
        return rgba_color::transparent_black;
    auto inv = 1.f - a.a();
    auto rr = a.r() * a.a() + b.r() * inv;
    auto rg = a.g() * a.a() + b.g() * inv;
    auto rb = a.b() * a.a() + b.b() * inv;
    return {rr, rg, rb, ra};
}

static rgba_color DestOver( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto inv = 1.f - b.a();
    auto ra = a.a() * inv + b.a();
    if( ra <= numeric_limits<float>::min() )
        return rgba_color::transparent_black;
    auto rr = (a.r() * a.a() * inv + b.r() * b.a() ) / ra;
    auto rg = (a.g() * a.a() * inv + b.g() * b.a() ) / ra;
    auto rb = (a.b() * a.a() * inv + b.b() * b.a() ) / ra;
    return {rr, rg, rb, ra};
}
    
static rgba_color DestIn( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto ra = a.a() * b.a();
    if( ra <= numeric_limits<float>::min() )
        return rgba_color::transparent_black;
    return {b.r(), b.g(), b.b(), ra};
}

static rgba_color DestOut( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto ra = (1.f - a.a()) * b.a();
    if( ra <= numeric_limits<float>::min() )
        return rgba_color::transparent_black;
    return {b.r(), b.g(), b.b(), ra};
}

static rgba_color DestAtop( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto ra = a.a();
    if( ra <= numeric_limits<float>::min() )
        return rgba_color::transparent_black;
    auto inv = 1.f - b.a();
    auto rr = a.r() * inv + b.r() * b.a();
    auto rg = a.g() * inv + b.g() * b.a();
    auto rb = a.b() * inv + b.b() * b.a();
    return {rr, rg, rb, ra};
}

static rgba_color Xor( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto ra = a.a() + b.a() - 2.f * a.a() * b.a();
    if( ra <= numeric_limits<float>::min() )
        return rgba_color::transparent_black;
    auto rr = (a.r() * a.a() * (1.f - b.a()) + b.r() * b.a() * (1.f - a.a()) ) / ra;
    auto rg = (a.g() * a.a() * (1.f - b.a()) + b.g() * b.a() * (1.f - a.a()) ) / ra;
    auto rb = (a.b() * a.a() * (1.f - b.a()) + b.b() * b.a() * (1.f - a.a()) ) / ra;
    return {rr, rg, rb, ra};
}
    
static rgba_color Add( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto ra = min( 1.f, a.a() + b.a() );
    if( ra <= numeric_limits<float>::min() )
        return rgba_color::transparent_black;
    auto rr = ( a.r() * a.a() + b.r() * b.a() ) / ra;
    auto rg = ( a.g() * a.a() + b.g() * b.a() ) / ra;
    auto rb = ( a.b() * a.a() + b.b() * b.a() ) / ra;
    return {rr, rg, rb, ra};
}

template <class F>
static rgba_color ComplexBlend( const rgba_color& a, const rgba_color& b, F f ) noexcept
{
    auto ra = a.a() + b.a() * (1.f - a.a());
    if( ra <= numeric_limits<float>::min() )
        return rgba_color::transparent_black;
    auto rr = ( a.r() * a.a() * (1.f - b.a()) + b.r() * b.a() * (1.f - a.a()) + a.a() * b.a() * f(a.r(), b.r()) ) / ra;
    auto rg = ( a.g() * a.a() * (1.f - b.a()) + b.g() * b.a() * (1.f - a.a()) + a.a() * b.a() * f(a.g(), b.g()) ) / ra;
    auto rb = ( a.b() * a.a() * (1.f - b.a()) + b.b() * b.a() * (1.f - a.a()) + a.a() * b.a() * f(a.b(), b.b()) ) / ra;
    return {rr, rg, rb, ra};
}

static rgba_color Multiply( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](float a, float b){ return a * b; };
    return ComplexBlend(a, b, f);
}

static rgba_color Screen( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](float a, float b){ return a + b - a * b; };
    return ComplexBlend(a, b, f);
}

static rgba_color Overlay( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](float a, float b){
        if( b <= 0.5f ) return 2.f * a * b;
        else            return 1.f - 2.f * (1.f - a) * (1.f - b);
    };
    return ComplexBlend(a, b, f);
}

static rgba_color Darken( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](float a, float b){ return min(a, b); };
    return ComplexBlend(a, b, f);
}
    
static rgba_color Lighten( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](float a, float b){ return max(a, b); };
    return ComplexBlend(a, b, f);
}

static rgba_color ColorDodge( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](float a, float b){
        if( b <= numeric_limits<float>::min() )
            return 0.f;
        // Cairo-compatible version:
        return a < 1.f ? min(1.f, b / (1.f - a)) : 1.f;
        // CoreGraphics-compatible version:
        // return a < 1.f ? b / (1.f - a) : numeric_limits<float>::max();        
    };
    return ComplexBlend(a, b, f);
}

static rgba_color ColorBurn( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](float a, float b){
        if( 1.f - b <= numeric_limits<float>::min() )
            return 1.f;        
        // Cairo-compatible version:
        return a > numeric_limits<float>::min() ? 1.f - min(1.f, (1.f - b) / a) : 0.f;
        // CoreGraphics-compatible version:
        // return a > numeric_limits<float>::min() ? 1.f - (1.f - b) / a : numeric_limits<float>::lowest();        
    };
    return ComplexBlend(a, b, f);
}

static rgba_color HardLight( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](float a, float b){
        if( a <= 0.5 )  return 2.f * a * b;
        else            return 1.f - 2.f * (1.f - a) * (1.f - b);
    };
    return ComplexBlend(a, b, f);
}
    
static rgba_color SoftLight( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](float a, float b){
        // Cairo-compatible version:        
        if( a <= 0.5 ) {
            return b - (1.f - 2.f * a) * b * (1.f - b);
        }
        else {
            if( b <= 0.25 )
                return b + (2.f * a - 1.f) * (((16.f * b - 12.f) * b + 4.f) * b - b);
            else
                return b + (2.f * a - 1.f) * (sqrt(b) - b);
        }        
        // CoreGraphics-compatible version:
        // return (1.f - 2.f * a) * b * b + 2.f * a * b;     
    };
    return ComplexBlend(a, b, f);
}
    
static rgba_color Difference( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](float a, float b){
        return abs(a - b);
    };
    return ComplexBlend(a, b, f);
}

static rgba_color Exclusion( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](float a, float b){
        return a + b - 2.f * a * b;
    };
    return ComplexBlend(a, b, f);
}

namespace hsl {

static float sat( tuple<float, float, float> c )
{
    return max({get<0>(c), get<1>(c), get<2>(c)}) - min({get<0>(c), get<1>(c), get<2>(c)});
}

static float lum( tuple<float, float, float> c )
{
    return 0.3f * get<0>(c) + 0.59f * get<1>(c) + 0.11f * get<2>(c);
}

static tuple<float, float, float> clip( tuple<float, float, float> c )
{
    auto& [r, g, b] = c;
    auto L = lum(c);
    auto N = min({r, g, b});
    auto X = max({r, g, b});
    if( N < 0.0f ) {
        r = L + ((r - L) * L) / (L - N);
        g = L + ((g - L) * L) / (L - N);
        b = L + ((b - L) * L) / (L - N);
    }
    if( X > 1.0f ) {
        r = L + ((r - L) * (1.f - L)) / (X - L);
        g = L + ((g - L) * (1.f - L)) / (X - L);
        b = L + ((b - L) * (1.f - L)) / (X - L);
    }
    return c;
}

static tuple<float, float, float> set_lum( tuple<float, float, float> c, float L )
{
    auto D = L - lum(c);
    auto& [r, g, b] = c;
    r = r + D;
    g = g + D;
    b = b + D;
    return clip(c);
}

static tuple<float, float, float> set_sat( tuple<float, float, float> c, float S )
{
    auto& [r, g, b] = c;
    auto &cmax = r > g ? ( r > b ? r : b ) : ( g > b ? g : b );
    auto &cmin = r < g ? ( r < b ? r : b ) : ( g < b ? g : b );
    auto &cmid = r > g ? ( r < b ? r : b ) : ( g < b ? g : b );
    if( cmax > cmin ) {
        cmid = ((cmid - cmin) * S) / (cmax - cmin);
        cmax = S;
    }
    else {
        cmid = cmax = 0.f;
    }
    cmin = 0.f;
    return c;
}

}

template <class F>
static rgba_color ComplexHSLBlend( const rgba_color& a, const rgba_color& b, F f ) noexcept
{
    auto ra = a.a() + b.a() * (1.f - a.a());
    if( ra <= numeric_limits<float>::min() )
        return rgba_color::transparent_black;
    auto fc = f(a, b);
    auto rr = ( a.r() * a.a() * (1.f - b.a()) + b.r() * b.a() * (1.f - a.a()) + a.a() * b.a() * get<0>(fc) ) / ra;
    auto rg = ( a.g() * a.a() * (1.f - b.a()) + b.g() * b.a() * (1.f - a.a()) + a.a() * b.a() * get<1>(fc) ) / ra;
    auto rb = ( a.b() * a.a() * (1.f - b.a()) + b.b() * b.a() * (1.f - a.a()) + a.a() * b.a() * get<2>(fc) ) / ra;
    return {rr, rg, rb, ra};
}

static rgba_color HSL_Hue( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](const rgba_color& a, const rgba_color& b){
        auto A = make_tuple(a.r(), a.g(), a.b());
        auto B = make_tuple(b.r(), b.g(), b.b());
        return hsl::set_lum( hsl::set_sat(A, hsl::sat(B)), hsl::lum(B) );
    };
    return ComplexHSLBlend(a, b, f);
}

static rgba_color HSL_Saturation( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](const rgba_color& a, const rgba_color& b){
        auto A = make_tuple(a.r(), a.g(), a.b());
        auto B = make_tuple(b.r(), b.g(), b.b());
        return hsl::set_lum( hsl::set_sat(B, hsl::sat(A)), hsl::lum(B) );
    };
    return ComplexHSLBlend(a, b, f);
}

static rgba_color HSL_Color( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](const rgba_color& a, const rgba_color& b){
        auto A = make_tuple(a.r(), a.g(), a.b());
        auto B = make_tuple(b.r(), b.g(), b.b());
        return hsl::set_lum( A, hsl::lum(B) );
    };
    return ComplexHSLBlend(a, b, f);
}

static rgba_color HSL_Luminosity( const rgba_color& a, const rgba_color& b ) noexcept
{
    auto f = [](const rgba_color& a, const rgba_color& b){
        auto A = make_tuple(a.r(), a.g(), a.b());
        auto B = make_tuple(b.r(), b.g(), b.b());
        return hsl::set_lum( B, hsl::lum(A) );
    };
    return ComplexHSLBlend(a, b, f);
}

}

static function<rgba_color(const rgba_color&, const rgba_color&)> BlendFunction( compositing_op op  )
{
    switch (op) {
        case compositing_op::over:          return Blend::Over;
        case compositing_op::clear:         return Blend::Clear;
        case compositing_op::source:        return Blend::Source;
        case compositing_op::in:            return Blend::In;
        case compositing_op::out:           return Blend::Out;
        case compositing_op::atop:          return Blend::Atop;
        case compositing_op::dest_over:     return Blend::DestOver;
        case compositing_op::dest_in:       return Blend::DestIn;
        case compositing_op::dest_out:      return Blend::DestOut;
        case compositing_op::dest_atop:     return Blend::DestAtop;
        case compositing_op::xor_op:        return Blend::Xor;
        case compositing_op::add:           return Blend::Add;
        case compositing_op::multiply:      return Blend::Multiply;
        case compositing_op::screen:        return Blend::Screen;
        case compositing_op::overlay:       return Blend::Overlay;
        case compositing_op::darken:        return Blend::Darken;
        case compositing_op::lighten:       return Blend::Lighten;
        case compositing_op::color_dodge:   return Blend::ColorDodge;
        case compositing_op::color_burn:    return Blend::ColorBurn;
        case compositing_op::hard_light:    return Blend::HardLight;
        case compositing_op::soft_light:    return Blend::SoftLight;
        case compositing_op::difference:    return Blend::Difference;
        case compositing_op::exclusion:     return Blend::Exclusion;
        case compositing_op::hsl_hue:       return Blend::HSL_Hue;
        case compositing_op::hsl_saturation:return Blend::HSL_Saturation;
        case compositing_op::hsl_color:     return Blend::HSL_Color;
        case compositing_op::hsl_luminosity:return Blend::HSL_Luminosity;
        default: return nullptr;
    }
}

using Triplet = tuple<rgba_color, rgba_color, rgba_color>;

// returns 2025 combinations of "A blend B = C", iterating over one color component and over alpha component
static vector<Triplet> BuildRefData(function<rgba_color(const rgba_color&, const rgba_color&)> blend)
{
    assert( blend );    
    auto color_step = 17;
    auto alpha_step = 51;    
    vector<Triplet> colors;
    for( int a_r = 0; a_r <= 255; a_r += color_step )
        for( int a_a = 153; a_a <= 255; a_a += alpha_step )
            for( int b_r = 0; b_r <= 255; b_r += color_step )
                for( int b_a = 153; b_a <= 255; b_a += alpha_step ) {    
                    auto a = rgba_color{ a_r, 0, 0, a_a };
                    auto b = rgba_color{ b_r, 0, 0, b_a };
                    auto c = blend(a, b);
                    colors.emplace_back(a, b, c);
                }
    return colors;
}

static void clear(image_surface &s)
{
    static const auto b = brush{rgba_color::transparent_black};    
    auto rp = render_props{};
    rp.compositing(compositing_op::source);
    s.paint(b, nullopt, rp);
}

[[maybe_unused]] static image_surface build_blend_map_256x256(compositing_op op)
{
    image_surface img{format::argb32, 256, 256};
    for( int x = 0; x < 256; ++x )
        for( int y = 0; y < 256; ++y ) {
            auto background = brush{rgba_color(x, x, x)};            
            auto foreground = brush{rgba_color(y, y, y)};
            auto cl = clip_props( bounding_box(float(x), float(255-y), 1.f, 1.f) );
            
            render_props rp;
            
            rp.compositing(compositing_op::source);
            img.paint(background, nullopt, rp, cl);
            
            rp.compositing(op);            
            img.paint(foreground, nullopt, rp, cl);            
        }
    
    return img;
}

TEST_CASE("IO2D properly blends colors using compositing_op::over")
{
    auto op = compositing_op::over;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};    
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::clear")
{
    auto op = compositing_op::clear;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};    
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );  
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::source")
{
    auto op = compositing_op::source;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};    
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::in")
{
    auto op = compositing_op::in;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};    
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::out")
{
    auto op = compositing_op::out;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::atop")
{
    auto op = compositing_op::atop;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::dest_over")
{
    auto op = compositing_op::dest_over;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::dest_in")
{
    auto op = compositing_op::dest_in;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::dest_out")
{
    auto op = compositing_op::dest_out;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::dest_atop")
{
    auto op = compositing_op::dest_atop;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::xor_op")
{
    auto op = compositing_op::xor_op;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::add")
{
    auto op = compositing_op::add;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::multiply")
{
    auto op = compositing_op::multiply;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::screen")
{
    auto op = compositing_op::screen;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::overlay")
{
    auto op = compositing_op::overlay;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::darken")
{
    auto op = compositing_op::darken;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::lighten")
{
    auto op = compositing_op::lighten;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::hard_light")
{
    auto op = compositing_op::hard_light;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::difference")
{
    auto op = compositing_op::difference;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::exclusion")
{
    auto op = compositing_op::exclusion;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};    
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::hsl_hue")
{
    auto op = compositing_op::hsl_hue;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::hsl_saturation")
{
    auto op = compositing_op::hsl_saturation;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};    
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::hsl_color")
{
    auto op = compositing_op::hsl_color;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::hsl_luminosity")
{
    auto op = compositing_op::hsl_luminosity;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};    
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);
    }
}

// These 3 test cases are hid out due to differences in color blending in different backends. 
TEST_CASE("IO2D properly blends colors using compositing_op::color_dodge", "[!hide][!mayfail]")
{
    auto op = compositing_op::color_dodge;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};    
    for( auto &t: colors ) {
        clear(img);        
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);            
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::color_burn", "[!hide][!mayfail]")
{
    auto op = compositing_op::color_burn;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};    
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);            
    }
}

TEST_CASE("IO2D properly blends colors using compositing_op::soft_light", "[!hide][!mayfail]")
{
    auto op = compositing_op::soft_light;
    auto rp = render_props{};
    rp.compositing(op);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    auto img = image_surface{format::argb32, 1, 1};    
    for( auto &t: colors ) {
        clear(img);
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        INFO("A: " << get<0>(t) << ", B: " << get<1>(t) << ", C: " << get<2>(t) );
        CHECK( CompareImageColor(img, 0, 0, get<2>(t), 0.05f) == true);            
    }
}
