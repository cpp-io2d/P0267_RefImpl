#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

static image_surface DrawCheckerboard4x4();

TEST_CASE("Properly draws with a non-wrapped surface brush")
{
    auto reference = "surface_brush_no_wrapping_20x20.png";
    image_surface img{format::argb32, 20, 20};
    
    auto b = brush{ DrawCheckerboard4x4() };
 
    auto bp = brush_props{};
    bp.filter(filter::nearest);

    auto rp = render_props{};
    rp.antialiasing(antialias::none);

    vector<matrix_2d> mats;
    mats.emplace_back(matrix_2d::create_translate({-2.f, -2.f}) * matrix_2d::create_rotate(pi<float>/2) * matrix_2d::create_translate({2.f, 2.f}) * matrix_2d::create_scale({2.f, 4.f}));
    mats.emplace_back(matrix_2d::create_translate({0.f, 16.f}));
    mats.emplace_back(matrix_2d::create_translate({-2.f, -2.f}) * matrix_2d::create_rotate(pi<float>/2) * matrix_2d::create_translate({2.f, 2.f}) * matrix_2d::create_translate({4.f, 16.f}));
    mats.emplace_back(matrix_2d::create_translate({-2.f, -2.f}) * matrix_2d::create_rotate(pi<float>/2) * matrix_2d::create_translate({2.f, 2.f}) * matrix_2d::create_scale({3.f, 1.f}) * matrix_2d::create_translate({8.f, 16.f}));
    mats.emplace_back(matrix_2d::create_scale({3.f, 1.f}) * matrix_2d::create_translate({8.f, 12.f}));
    mats.emplace_back(matrix_2d::create_scale({3.f, 3.f}) * matrix_2d::create_translate({8.f, 0.f}));

    for( auto &m: mats ) {
        bp.brush_matrix(m.inverse());
        img.paint(b, bp, rp);
    }

    CHECK( CompareWithPNGImage(img, reference) == true );
}

TEST_CASE("Properly draws with a repeateded surface brush")
{
    auto reference = "surface_brush_repeat_no_transform_20x20.png";
    image_surface img{format::argb32, 20, 20};
    auto b = brush{ DrawCheckerboard4x4() };
    
    auto bp = brush_props{};
    bp.wrap_mode(wrap_mode::repeat);
    bp.filter(filter::nearest);
    auto rp = render_props{};
    rp.antialiasing(antialias::none);
    
    SECTION("No transforms") {
        img.paint(b, bp, rp);
    }
    SECTION("Translate") {
        bp.brush_matrix( matrix_2d::create_translate({-16.f, -16.f}) );
        img.paint(b, bp, rp);
    }
    SECTION("Translate by 2 px") {
        bp.brush_matrix( matrix_2d::create_translate({-2.f, -2.f}) );
        img.paint(b, bp, rp);
    }
    SECTION("Rotated 180 degrees") {
        auto m = matrix_2d::create_translate({-2.f, -2.f}) * matrix_2d::create_rotate(pi<float>) * matrix_2d::create_translate({2.f, 2.f});
        bp.brush_matrix(m.inverse());
        img.paint(b, bp, rp);
    }

    CHECK( CompareWithPNGImage(img, reference) == true );
}

TEST_CASE("Properly draws with a repeateded scaled surface brush")
{
    auto reference = "surface_brush_repeat_2x_scale_20x20.png";
    image_surface img{format::argb32, 20, 20};
    auto b = brush{ DrawCheckerboard4x4() };
    
    auto bp = brush_props{};
    bp.wrap_mode(wrap_mode::repeat);
    bp.filter(filter::nearest);
    auto rp = render_props{};
    rp.antialiasing(antialias::none);
    
    SECTION("Just scale") {
        bp.brush_matrix( matrix_2d::create_scale({2.f, 2.f}).inverse() );
    }
    SECTION("Scale and translate") {
        auto m = matrix_2d::create_scale({2.f, 2.f}) * matrix_2d::create_translate({8.f, 8.f});
        bp.brush_matrix( m.inverse() );
    }
    SECTION("Scale, translate and 180 degree rotate") {
        auto m = matrix_2d::create_scale({2.f, 2.f}) * matrix_2d::create_translate({8.f, 8.f}) * matrix_2d::create_rotate(pi<float>);
        bp.brush_matrix( m.inverse() );
    }
    img.paint(b, bp, rp);

    CHECK( CompareWithPNGImage(img, reference) == true );
}

TEST_CASE("Properly draws with a repeateded non-uniformely scaled surface brush")
{
    auto reference = "surface_brush_repeat_non_uniform_scale_20x20.png";
    image_surface img{format::argb32, 20, 20};
    auto b = brush{ DrawCheckerboard4x4() };
    
    auto bp = brush_props{};
    bp.wrap_mode(wrap_mode::repeat);
    bp.filter(filter::nearest);
    auto rp = render_props{};
    rp.antialiasing(antialias::none);
    
    SECTION("Just scale") {
        bp.brush_matrix( matrix_2d::create_scale({3.f, 2.f}).inverse() );
    }
    SECTION("Scale and translate") {
        auto m = matrix_2d::create_scale({3.f, 2.f}) * matrix_2d::create_translate({12.f, 8.f});
        bp.brush_matrix( m.inverse() );
    }
    SECTION("Scale, translate and 180 degree rotate") {
        auto m = matrix_2d::create_scale({3.f, 2.f}) * matrix_2d::create_translate({12.f, 8.f}) * matrix_2d::create_rotate(pi<float>);
        bp.brush_matrix( m.inverse() );
    }
    img.paint(b, bp, rp);
    
    CHECK( CompareWithPNGImage(img, reference) == true );
}

// Not actually sure how eligible this test is.
// Rasterized might have a freedom to interpret this differently on per-pixel level.
TEST_CASE("Properly draws with a repeateded sheared surface brush")
{
    auto reference = "surface_brush_repeat_x_shear_20x20.png";
    image_surface img{format::argb32, 20, 20};
    auto b = brush{ DrawCheckerboard4x4() };
    
    auto bp = brush_props{};
    bp.wrap_mode(wrap_mode::repeat);
    bp.filter(filter::nearest);
    auto rp = render_props{};
    rp.antialiasing(antialias::none);

    SECTION("Shear right") {
        bp.brush_matrix( matrix_2d::create_shear_x(1.f).inverse() );
    }
    SECTION("Shear left") {
        bp.brush_matrix( (matrix_2d::create_shear_x(-1.f) * matrix_2d::create_translate({-1.f, 0.f}) ).inverse() );
    }
    img.paint(b, bp, rp);
    
    CHECK( CompareWithPNGImage(img, reference, 0.0f, 1) == true );
}

TEST_CASE("Properly draws with a reflected surface brush")
{
    auto reference = "surface_brush_reflect_no_transform_20x20.png";
    image_surface img{format::argb32, 20, 20};
    auto b = brush{ DrawCheckerboard4x4() };
    
    auto bp = brush_props{};
    bp.wrap_mode(wrap_mode::reflect);
    bp.filter(filter::nearest);
    auto rp = render_props{};
    rp.antialiasing(antialias::none);
    
    SECTION("No transforms") {
    }
    SECTION("Translate") {
        bp.brush_matrix( matrix_2d::create_translate({-16.f, -16.f}) );
    }
    SECTION("Rotated 180 degrees") {
        auto m = matrix_2d::create_translate({-2.f, -2.f}) * matrix_2d::create_rotate(pi<float>) * matrix_2d::create_translate({2.f, 2.f});
        bp.brush_matrix(m.inverse());
    }
    img.paint(b, bp, rp);
    
    CHECK( CompareWithPNGImage(img, reference) == true );
}

TEST_CASE("Properly draws with a reflected scaled surface brush")
{
    auto reference = "surface_brush_reflect_2x_scale_20x20.png";
    
    image_surface img{format::argb32, 20, 20};
    auto b = brush{ DrawCheckerboard4x4() };
    
    auto bp = brush_props{};
    bp.wrap_mode(wrap_mode::reflect);
    bp.filter(filter::nearest);
    auto rp = render_props{};
    rp.antialiasing(antialias::none);

    SECTION("Just scale") {
        bp.brush_matrix( matrix_2d::create_scale({2.f, 2.f}).inverse() );
    }
    SECTION("Scale and translate") {
        auto m = matrix_2d::create_scale({2.f, 2.f}) * matrix_2d::create_translate({8.f, 8.f});
        bp.brush_matrix(m.inverse());
    }
    SECTION("Scale, translate and rotated 180 degrees") {
        auto m = matrix_2d::create_translate({-2.f, -2.f}) *
                 matrix_2d::create_rotate(pi<float>) *
                 matrix_2d::create_translate({2.f, 2.f}) *
                 matrix_2d::create_scale({2.f, 2.f}) *
                 matrix_2d::create_translate({8.f, 8.f});
        bp.brush_matrix(m.inverse());
    }
    
    img.paint(b, bp, rp);
    
    CHECK( CompareWithPNGImage(img, reference) == true );
}

TEST_CASE("Properly draws with a reflected non-uniformely scaled surface brush")
{
    auto reference = "surface_brush_reflect_non_uniform_scale_20x20.png";

    image_surface img{format::argb32, 20, 20};
    auto b = brush{ DrawCheckerboard4x4() };
    
    auto bp = brush_props{};
    bp.wrap_mode(wrap_mode::reflect);
    bp.filter(filter::nearest);
    auto rp = render_props{};
    rp.antialiasing(antialias::none);
    
    SECTION("Just scale") {
        bp.brush_matrix( matrix_2d::create_scale({3.f, 2.f}).inverse() );
    }
    SECTION("Scale and translate") {
        auto m = matrix_2d::create_scale({3.f, 2.f}) * matrix_2d::create_translate({12.f, 8.f});
        bp.brush_matrix(m.inverse());
    }
    SECTION("Scale, translate and rotated 180 degrees") {
        auto m = matrix_2d::create_translate({-2.f, -2.f}) *
                 matrix_2d::create_rotate(pi<float>) *
                 matrix_2d::create_translate({2.f, 2.f}) *
                 matrix_2d::create_scale({3.f, 2.f}) *
                 matrix_2d::create_translate({12.f, 8.f});
        bp.brush_matrix(m.inverse());
    }

    img.paint(b, bp, rp);
    
    CHECK( CompareWithPNGImage(img, reference) == true );
}

TEST_CASE("Properly draws with a padded surface brush")
{
    auto reference = "surface_brush_pad_translate_20x20.png";
    
    image_surface img{format::argb32, 20, 20};
    auto b = brush{ DrawCheckerboard4x4() };
    
    auto bp = brush_props{};
    bp.wrap_mode(wrap_mode::pad);
    bp.filter(filter::nearest);
    auto rp = render_props{};
    rp.antialiasing(antialias::none);
    
    SECTION("Just translate") {
        bp.brush_matrix( matrix_2d::create_translate({-8.f, -8.f}) );
    }
    SECTION("Rotate 180 degrees and translate") {
        auto m = matrix_2d::create_translate({-2.f, -2.f}) *
                 matrix_2d::create_rotate(pi<float>) *
                 matrix_2d::create_translate({2.f, 2.f}) *
                 matrix_2d::create_translate({8.f, 8.f});
        bp.brush_matrix( m.inverse() );
    }

    img.paint(b, bp, rp);
    
    CHECK( CompareWithPNGImage(img, reference) == true );
}

TEST_CASE("IO2D extends a non-papped surface brush with transparent_black")
{
    auto reference = "surface_brush_samples_outside_non_padded_10x10.png";    
    
    image_surface img{format::argb32, 10, 10};
    auto b = brush{ DrawCheckerboard4x4() };
    img.paint(brush{rgba_color::red});
    
    auto bp = brush_props{};
    bp.wrap_mode(wrap_mode::none);
    bp.filter(filter::nearest);
    bp.brush_matrix(matrix_2d::create_translate({3, 3}).inverse());
    
    auto rp = render_props{};
    rp.antialiasing(antialias::none);
    rp.compositing(compositing_op::source);
    
    img.paint(b, bp, rp);
    
    CHECK( CompareWithPNGImage(img, reference) == true );
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
