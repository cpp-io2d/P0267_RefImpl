#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

TEST_CASE("IO2D properly encodes and decodes colors")
{
    auto background = brush{rgba_color::transparent_black};
    auto step = 51;
    for( int red = 0; red <= 255; red += step )
        for( int green = 0; green <= 255; green += step )
            for( int blue = 0; blue <= 255; blue += step )
                for( int alpha = step; alpha <= 255; alpha += step ) {
                    auto img = image_surface{format::argb32, 1, 1};
                    img.paint(background);
                    
                    auto color = rgba_color{ red, green, blue, alpha };
                    img.paint(brush{color});
                    
                    CHECK( CompareImageColor(img, 0, 0, color, 0.05f) == true);
                }
}

TEST_CASE("rgba_color is correclty multiplied by float numbers")
{
    const rgba_color c1{1.0f, 0.8f, 0.6f, 0.4f};
    const float m = 0.5f;
    rgba_color c2{0.0f, 0.0f, 0.0f, 0.0f};
    SECTION("right hand side multiplication") {
        c2 = c1 * m;
    }
    SECTION("left hand side multiplication") {
        c2 = m * c1;
    }
    SECTION("multiply-assign multiplication") {
        c2 = c1; 
        c2 *= m;
    }
    const float eps = std::numeric_limits<float>::epsilon(); 
    CHECK( fabs(c2.r() - 0.5f) < eps );
    CHECK( fabs(c2.g() - 0.4f) < eps );
    CHECK( fabs(c2.b() - 0.3f) < eps );
    CHECK( fabs(c2.a() - 0.2f) < eps );     
}

TEST_CASE("rgba_color is correclty multiplied by double numbers")
{
    const rgba_color c1{1.0f, 0.8f, 0.6f, 0.4f};
    const double m = 0.5f;
    rgba_color c2{0.0f, 0.0f, 0.0f, 0.0f};
    SECTION("right hand side multiplication") {
        c2 = c1 * m;
    }
    SECTION("left hand side multiplication") {
        c2 = m * c1;
    }
    SECTION("multiply-assign multiplication") {
        c2 = c1; 
        c2 *= m;
    }
    const float eps = std::numeric_limits<float>::epsilon(); 
    CHECK( fabs(c2.r() - 0.5f) < eps );
    CHECK( fabs(c2.g() - 0.4f) < eps );
    CHECK( fabs(c2.b() - 0.3f) < eps );
    CHECK( fabs(c2.a() - 0.2f) < eps );     
}

TEST_CASE("rgba_color is correclty multiplied by integral numbers")
{
    const rgba_color c1{1.0f, 0.8f, 0.6f, 0.4f};
    const int m = 127;
    rgba_color c2{0.0f, 0.0f, 0.0f, 0.0f};
    SECTION("right hand side multiplication") {
        c2 = c1 * m;
    }
    SECTION("left hand side multiplication") {
        c2 = m * c1;
    }
    SECTION("multiply-assign multiplication") {
        c2 = c1; 
        c2 *= m;
    }
    const float eps = 0.005f; 
    CHECK( fabs(c2.r() - 0.5f) < eps );
    CHECK( fabs(c2.g() - 0.4f) < eps );
    CHECK( fabs(c2.b() - 0.3f) < eps );
    CHECK( fabs(c2.a() - 0.2f) < eps );     
}
