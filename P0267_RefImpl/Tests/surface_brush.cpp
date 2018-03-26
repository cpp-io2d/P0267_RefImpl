#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

static image_surface DrawCheckerboard4x4();

TEST_CASE("surface brush")
{
    auto reference = "surface_brush_no_wrapping_20x20.png";
    image_surface img{format::argb32, 20, 20};
    
    auto b = brush{ DrawCheckerboard4x4() };
 
    auto bp = brush_props{};
    bp.filter(filter::nearest);

    auto rp = render_props{};
    rp.antialiasing(antialias::none);

    vector<matrix_2d> mats;
    mats.emplace_back(matrix_2d::init_translate({-2.f, -2.f}) * matrix_2d::init_rotate(pi<float>/2) * matrix_2d::init_translate({2.f, 2.f}) * matrix_2d::init_scale({2.f, 4.f}));
    mats.emplace_back(matrix_2d::init_translate({0.f, 16.f}));
    mats.emplace_back(matrix_2d::init_translate({-2.f, -2.f}) * matrix_2d::init_rotate(pi<float>/2) * matrix_2d::init_translate({2.f, 2.f}) * matrix_2d::init_translate({4.f, 16.f}));
    mats.emplace_back(matrix_2d::init_translate({-2.f, -2.f}) * matrix_2d::init_rotate(pi<float>/2) * matrix_2d::init_translate({2.f, 2.f}) * matrix_2d::init_scale({3.f, 1.f}) * matrix_2d::init_translate({8.f, 16.f}));
    mats.emplace_back(matrix_2d::init_scale({3.f, 1.f}) * matrix_2d::init_translate({8.f, 12.f}));
    mats.emplace_back(matrix_2d::init_scale({3.f, 3.f}) * matrix_2d::init_translate({8.f, 0.f}));

    for( auto &m: mats ) {
        bp.brush_matrix(m.inverse());
        img.paint(b, bp, rp);
    }

    CHECK( ComparePNGExact(img, reference) == true );
}

/**
 * Draws the following pattern:
 * BWBW
 * WBWB
 * BWBW
 * WBWB
 */
static image_surface DrawCheckerboard4x4()
{
    image_surface img{format::argb32, 4, 4};
    
    for( int y = 0; y < 4; y++ )
        for( int x = 0; x < 4; x++ ) {
            auto b = ((y + x) % 2 == 0) ? brush{rgba_color::black} : brush{rgba_color::white};
            auto cl = clip_props{ bounding_box{float(x), float(y), 1., 1.} };
            img.paint(b, nullopt, nullopt, cl);
        }
    
    return img;
}
