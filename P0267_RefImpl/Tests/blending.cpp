#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

static rgba_color BlendOver( const rgba_color& a, const rgba_color& b )
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

static function<rgba_color(const rgba_color&, const rgba_color&)> BlendFunction( compositing_op op  )
{
    switch (op) {
        case compositing_op::over: return BlendOver;
        default: return nullptr;
    }
}

// returns 625 combinations of "A blend B = C", iterating over one color component and over alpha component
static vector< tuple<rgba_color, rgba_color, rgba_color> > BuildRefData( function<rgba_color(const rgba_color&, const rgba_color&)> blend )
{
    assert( blend );
    auto step = 51;
    vector< tuple<rgba_color, rgba_color, rgba_color> > colors;
    for( int a_r = 0; a_r <= 255; a_r += step )
        for( int a_a = 0; a_a <= 255; a_a += step )
            for( int b_r = 0; b_r <= 255; b_r += step )
                for( int b_a = 0; b_a <= 255; b_a += step ) {
                    auto a = rgba_color{ a_r, 0, 0, a_a };
                    auto b = rgba_color{ b_r, 0, 0, b_a };
                    auto c = blend(a, b);
                    colors.emplace_back(a, b, c);
                }
    return colors;
}

TEST_CASE("IO2D properly blends colors using compositing_op::over")
{
    auto rp = render_props{};
    rp.compositing(compositing_op::over);
    auto colors = BuildRefData( BlendFunction(rp.compositing()) );
    for( auto &t: colors ) {
        auto img = image_surface{format::argb32, 1, 1};
        img.paint(brush{get<1>(t)});
        img.paint(brush{get<0>(t)}, nullopt, rp);
        CHECK( CheckPNGColorWithTolerance(img, 0, 0, get<2>(t), 0.05) == true);
    }
}
