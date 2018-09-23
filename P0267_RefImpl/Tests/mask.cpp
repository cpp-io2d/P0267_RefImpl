#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

TEST_CASE("Properly blends a solid brush with a solid mask")
{
    image_surface img{format::argb32, 1, 1};
    img.paint(brush{rgba_color{0, 0, 0, 0}});
    
    SECTION("M=1.0, S=1.0") {
        img.mask(brush{rgba_color{1., 1., 1., 1.}}, brush{rgba_color{0., 0., 0., 1.0}} );
        CHECK( CompareImageColor(img, 0, 0, rgba_color(1., 1., 1., 1.0), 0.01f) == true);
    }
    SECTION("M=1.0, S=0.5") {
        img.mask(brush{rgba_color{1., 1., 1., 0.5}}, brush{rgba_color{0., 0., 0., 1.0}} );
        CHECK( CompareImageColor(img, 0, 0, rgba_color(1., 1., 1., 0.5), 0.01f) == true);
    }    
    SECTION("M=0.9, S=1.0") {
        img.mask(brush{rgba_color{1., 1., 1., 1.}}, brush{rgba_color{0., 0., 0., 0.9}} );
        CHECK( CompareImageColor(img, 0, 0, rgba_color(1., 1., 1., 0.9), 0.01f) == true);
    }
    SECTION("M=0.9, S=0.5") {
        img.mask(brush{rgba_color{1., 1., 1., 0.5}}, brush{rgba_color{0., 0., 0., 0.9}} );
        CHECK( CompareImageColor(img, 0, 0, rgba_color(1., 1., 1., 0.45), 0.01f) == true);        
    }
    SECTION("M=0.5, S=1.0") {
        img.mask(brush{rgba_color{1., 1., 1., 1.0}}, brush{rgba_color{0., 0., 0., 0.5}} );
        CHECK( CompareImageColor(img, 0, 0, rgba_color(1., 1., 1., 0.5), 0.01f) == true);
    }
    SECTION("M=0.5, S=0.5") {
        img.mask(brush{rgba_color{1., 1., 1., 0.7}}, brush{rgba_color{0., 0., 0., 0.5}} );
        CHECK( CompareImageColor(img, 0, 0, rgba_color(1., 1., 1., 0.35), 0.01f) == true);
    }
    SECTION("M=0.1, S=1.0") {
        img.mask(brush{rgba_color{1., 1., 1., 1.}}, brush{rgba_color{0., 0., 0., 0.1}} );
        CHECK( CompareImageColor(img, 0, 0, rgba_color(1., 1., 1., 0.1), 0.01f) == true);
    }    
    SECTION("M=0.1, S=0.5") {
        img.mask(brush{rgba_color{1., 1., 1., 0.5}}, brush{rgba_color{0., 0., 0., 0.1}} );
        CHECK( CompareImageColor(img, 0, 0, rgba_color(1., 1., 1., 0.05), 0.01f) == true);
    }    
    SECTION("M=0.0, S=1.0") {
        img.mask(brush{rgba_color{1., 1., 1., 1.}}, brush{rgba_color{0., 0., 0., 0.0}} );
        CHECK( CompareImageColor(img, 0, 0, rgba_color(0., 0., 0., 0.0), 0.01f) == true);
    }
    SECTION("M=0.0, S=0.5") {
        img.mask(brush{rgba_color{1., 1., 1., 0.5}}, brush{rgba_color{0., 0., 0., 0.0}} );
        CHECK( CompareImageColor(img, 0, 0, rgba_color(0., 0., 0., 0.0), 0.01f) == true);
    }
}

TEST_CASE("Properly blends a solid brush with a linear gradient mask")
{
    auto reference = "mask_green_to_red_blending_50x50.png";    
    image_surface img{format::argb32, 50, 50};
    img.paint(brush{rgba_color{0., 1., 0., 1.}});
    auto b = brush{rgba_color{1., 0., 0., 1.}};
    auto mb = brush{point_2d{0, 0}, point_2d{0, 50}, {{0., rgba_color{0., 0., 0., 0.}}, {1., rgba_color{0., 0., 0., 1.}}}};    
    img.mask(b, mb);    
    CHECK( CompareWithPNGImage(img, reference, 0.02f) == true );
}

TEST_CASE("Properly blends a solid brush with a linear gradient mask using a clip region")
{
    auto reference = "mask_green_to_red_blending_clipped_with_rect_50x50.png";    
    image_surface img{format::argb32, 50, 50};
    img.paint(brush{rgba_color{0., 1., 0., 1.}});
    auto b = brush{rgba_color{1., 0., 0., 1.}};
    auto mb = brush{point_2d{0, 0}, point_2d{0, 50}, {{0., rgba_color{0., 0., 0., 0.}}, {1., rgba_color{0., 0., 0., 1.}}}};
    auto cl = clip_props{bounding_box{10, 10, 30, 30}};
    img.mask(b, mb, nullopt, nullopt, nullopt, cl);    
    CHECK( CompareWithPNGImage(img, reference, 0.02f) == true );
}

TEST_CASE("Properly blends a solid brush with a linear gradient mask using clip regions and mask transformations")
{
    auto reference = "mask_green_to_red_blending_clipped_with_rects_and_rotated_35x35.png";    
    image_surface img{format::argb32, 35, 35};
    img.paint(brush{rgba_color{0., 1., 0., 1.}});
    auto b = brush{rgba_color{1., 0., 0., 1.}};
    auto mb = brush{point_2d{0, 0}, point_2d{0, 10}, {{0., rgba_color{0., 0., 0., 0.}}, {1., rgba_color{0., 0., 0., 1.}}}};    
    auto mp = mask_props{};
    auto cl = clip_props{};    
    
    cl = clip_props{bounding_box{5, 5, 10, 10}};
    mp.mask_matrix(matrix_2d::create_translate({5, 5}));
    img.mask(b, mb, nullopt, mp, nullopt, cl);    

    cl = clip_props{bounding_box{20, 5, 10, 10}};
    mp.mask_matrix(matrix_2d::create_translate({20, 5}) * matrix_2d::create_rotate(-pi<float>/2));
    img.mask(b, mb, nullopt, mp, nullopt, cl);    
    
    cl = clip_props{bounding_box{5, 20, 10, 10}};
    mp.mask_matrix(matrix_2d::create_translate({5, 20}) * matrix_2d::create_rotate(pi<float>/2));
    img.mask(b, mb, nullopt, mp, nullopt, cl);    
    
    cl = clip_props{bounding_box{20, 20, 10, 10}};
    mp.mask_matrix(matrix_2d::create_translate({20, 20}) * matrix_2d::create_rotate(pi<float>));
    img.mask(b, mb, nullopt, mp, nullopt, cl);    
        
    CHECK( CompareWithPNGImage(img, reference, 0.05f) == true );
}

TEST_CASE("Properly blends a solid brush with a radial gradient mask using a clip region")
{
    auto reference = "mask_green_to_red_radial_blending_clipped_with_triangle_50x50.png";    
    image_surface img{format::argb32, 50, 50};
    img.paint(brush{rgba_color{0., 1., 0., 1.}});
    auto b = brush{rgba_color{1., 0., 0., 1.}};
    auto mb = brush{ circle(point_2d{25, 25}, 30), circle(point_2d{25, 25}, 0), {{0., rgba_color{0., 0., 0., 0.}}, {1., rgba_color{0., 0., 0., 1.}}}};
    auto pb = path_builder{};
    pb.new_figure({25, 10});
    pb.line({40, 40});
    pb.line({10, 40});
    pb.line({25, 10});
    pb.close_figure();
    auto cl = clip_props{pb};    
    img.mask(b, mb, nullopt, nullopt, nullopt, cl);        
    CHECK( CompareWithPNGImage(img, reference, 0.02f) == true );
}

TEST_CASE("Properly blends a radial brush with a linear gradient mask")
{
    auto reference = "mask_radial_gradient_with_linear_gradient_50x50.png";
    image_surface img{format::argb32, 50, 50};
    img.paint(brush{rgba_color{0., 1., 0., 1.}});
    auto b = brush{ circle(point_2d{25, 25}, 24), circle(point_2d{25, 25}, 0), {{0., rgba_color{1., 0., 0., 1.}}, {1., rgba_color{0., 0., 1., 1.}}}};
    auto mb = brush{point_2d{0, 0}, point_2d{0, 50}, {{0., rgba_color{0., 0., 0., 0.}}, {1., rgba_color{0., 0., 0., 1.}}}};    
    img.mask(b, mb);    
    CHECK( CompareWithPNGImage(img, reference, 0.02f, 1) == true );    
}

TEST_CASE("Properly intersects a radial brush with a radial gradient mask")
{
    auto reference = "mask_circles_intersection_50x50.png";
    image_surface img{format::argb32, 50, 50};
    img.paint(brush{rgba_color{0., 0., 0., 1.}});
    auto b = brush{ circle(point_2d{20, 25}, 18), circle(point_2d{20, 25}, 0), {{0., rgba_color{1., 0., 0., 1.}}, {1., rgba_color{1., 0., 0., 1.}}}};
    auto mb = brush{ circle(point_2d{32, 25}, 18), circle(point_2d{32, 25}, 0), {{0., rgba_color{1., 1., 1., 1.}}, {1., rgba_color{1., 1., 1., 1.}}}};
    auto mbp = mask_props{};
    mbp.wrap_mode(wrap_mode::none);
    img.mask(b, mb, nullopt, mbp);
    CHECK( CompareWithPNGImage(img, reference, 0.02f, 1) == true );    
}

TEST_CASE("Properly intersects a radial brush with a radial gradient mask, clipped with a bounding box")
{
    auto reference = "mask_circles_intersection_clipped_with_bb_50x50.png";
    image_surface img{format::argb32, 50, 50};
    img.paint(brush{rgba_color{0., 0., 0., 1.}});
    auto b = brush{ circle(point_2d{20, 25}, 18), circle(point_2d{20, 25}, 0), {{0., rgba_color{1., 0., 0., 1.}}, {1., rgba_color{1., 0., 0., 1.}}}};
    auto mb = brush{ circle(point_2d{32, 25}, 18), circle(point_2d{32, 25}, 0), {{0., rgba_color{1., 1., 1., 1.}}, {1., rgba_color{1., 1., 1., 1.}}}};
    auto mbp = mask_props{};
    mbp.wrap_mode(wrap_mode::none);
    auto cl = clip_props{ bounding_box(10., 10., 30., 20.) };    
    img.mask(b, mb, nullopt, mbp, nullopt, cl);
    CHECK( CompareWithPNGImage(img, reference, 0.02f, 1) == true );    
}

TEST_CASE("Properly intersects a radial brush with a radial gradient mask, clipped with a non-convex figure")
{
    auto reference = "mask_circles_intersection_clipped_with_nc_figure_50x50.png";
    image_surface img{format::argb32, 50, 50};
    img.paint(brush{rgba_color{0., 0., 0., 1.}});
    auto b = brush{ circle(point_2d{20, 25}, 18), circle(point_2d{20, 25}, 0), {{0., rgba_color{1., 0., 0., 1.}}, {1., rgba_color{1., 0., 0., 1.}}}};
    auto mb = brush{ circle(point_2d{32, 25}, 18), circle(point_2d{32, 25}, 0), {{0., rgba_color{1., 1., 1., 1.}}, {1., rgba_color{1., 1., 1., 1.}}}};
    auto mbp = mask_props{};
    mbp.wrap_mode(wrap_mode::none);
    
    auto pb = path_builder{};
    pb.new_figure({10., 12.});
    pb.line({10., 40.});
    pb.line({26., 20.});
    pb.line({40., 40.});
    pb.line({40., 12.});
    pb.line({10., 12.});
    pb.close_figure();
    auto cl = clip_props{ pb };    
    
    img.mask(b, mb, nullopt, mbp, nullopt, cl);
    CHECK( CompareWithPNGImage(img, reference, 0.03f, 1) == true );    
}

static image_surface MakeCheckerboardMask(int width, int height, format fmt = format::argb32)
{
    image_surface s{fmt, width, height};
    s.paint(brush{rgba_color::transparent_black});
    auto b = brush{rgba_color::white};
    for( auto y = 0; y < height; ++y )
        for( auto x = 0; x < width; ++x )
            if( (x + y) % 2 == 0 )
                s.paint(b, nullopt, nullopt, clip_props{ bounding_box(static_cast<float>(x), static_cast<float>(y), 1.0f, 1.0f) });
    return s; 
}

TEST_CASE("Properly intersects a solid brush with a surface mask")
{
    auto reference = "mask_red_green_checkerboard_50x50.png";
    image_surface img{format::argb32, 50, 50};
    img.paint(brush{rgba_color::green});
    auto b = brush{rgba_color{}};
    SECTION("ARGB32 mask") {
        b = brush{MakeCheckerboardMask(50, 50)};
    }
    SECTION("A8 mask") {
        b = brush{MakeCheckerboardMask(50, 50, format::a8)};
    }
    img.mask(brush{rgba_color::red}, b);
    CHECK( CompareWithPNGImage(img, reference) == true );    
}

TEST_CASE("Properly intersects a solid brush with a repeated surface mask")
{
    auto reference = "mask_red_green_checkerboard_50x50.png";
    image_surface img{format::argb32, 50, 50};
    img.paint(brush{rgba_color::green});
    auto b = brush{rgba_color{}};
    SECTION("ARGB32 mask") {
        b = brush{MakeCheckerboardMask(10, 10)};
    }
    SECTION("A8 mask") {
        b = brush{MakeCheckerboardMask(10, 10, format::a8)};
    }
    img.mask(brush{rgba_color::red}, b);
    CHECK( CompareWithPNGImage(img, reference) == true );    
}

TEST_CASE("Properly intersects a solid brush with a reflected surface mask")
{
    auto reference = "mask_red_green_checkerboard_reflect_50x50.png";
    image_surface img{format::argb32, 50, 50};
    img.paint(brush{rgba_color::green});    
    auto mp = mask_props{};
    mp.wrap_mode(wrap_mode::reflect);
    auto b = brush{rgba_color{}};
    SECTION("ARGB32 mask") {
        b = brush{MakeCheckerboardMask(10, 10)};
    }
    SECTION("A8 mask") {
        b = brush{MakeCheckerboardMask(10, 10, format::a8)};
    }    
    img.mask(brush{rgba_color::red}, b, nullopt, mp);
    CHECK( CompareWithPNGImage(img, reference) == true );    
}

/**
 * Two tests below are marked as [!mayfail] due to some weird behavior of CoreGraphics:
 * it looks like it can't perform DrawImage() with A8 image and DestIn compositing mode.
 * It's not clear at the moment what to do with this issue: is this a bug in the IO2D backend or in
 * CoreGraphics itself. 
 */

TEST_CASE("Properly intersects a solid brush with a padded surface mask", "[!mayfail]")
{
    auto reference = "mask_red_green_checkerboard_pad_50x50.png";
    image_surface img{format::argb32, 50, 50};
    img.paint(brush{rgba_color::green});    
    auto mp = mask_props{};
    mp.wrap_mode(wrap_mode::pad);
    auto b = brush{rgba_color{}};
    SECTION("ARGB32 mask") {
        b = brush{MakeCheckerboardMask(10, 10)};
    }
    SECTION("A8 mask") {
        b = brush{MakeCheckerboardMask(10, 10, format::a8)};
    }
    img.mask(brush{rgba_color::red}, b, nullopt, mp);
    CHECK( CompareWithPNGImage(img, reference) == true );    
}

TEST_CASE("Properly intersects a solid brush with a non-wrapped surface mask", "[!mayfail]")
{
    auto reference = "mask_red_green_checkerboard_none_50x50.png";
    image_surface img{format::argb32, 50, 50};
    img.paint(brush{rgba_color::green});    
    auto mp = mask_props{};
    mp.wrap_mode(wrap_mode::none);
    auto b = brush{rgba_color{}};
    SECTION("ARGB32 mask") {
        b = brush{MakeCheckerboardMask(10, 10)};
    }
    SECTION("A8 mask") {
        b = brush{MakeCheckerboardMask(10, 10, format::a8)};
    }
    img.mask(brush{rgba_color::red}, b, nullopt, mp);
    CHECK( CompareWithPNGImage(img, reference) == true );    
}
