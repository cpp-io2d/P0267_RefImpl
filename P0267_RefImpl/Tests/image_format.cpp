#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

static rgba_color ConvertToAlphaless(rgba_color c)
{
    return { c.r() * c.a(), c.g() * c.a(), c.b() * c.a(), 1.f };
}

static rgba_color ConvertToAlphaonly(rgba_color c)
{
    return { 0.f, 0.f, 0.f, c.a() };
}

TEST_CASE("IO2D backend can create an image_surface with ARGB32 format")
{
    auto img = image_surface{format::argb32, 1, 1};
    CHECK( img.format() == format::argb32 );
}

TEST_CASE("IO2D backend can create an image_surface with XRGB32 format")
{
    auto img = image_surface{format::xrgb32, 1, 1};
    CHECK( img.format() == format::xrgb32 );
}

TEST_CASE("IO2D backend can create an image_surface with A8 format")
{
    auto img = image_surface{format::a8, 1, 1};
    CHECK( img.format() == format::a8 );
}

TEST_CASE("ARGB32 image_surface preserves all ARGB color information")
{
    auto img = image_surface{format::argb32, 1, 1};
    
    auto color = rgba_color{75, 150, 225, 42};
    
    render_props rp;    
    rp.compositing(compositing_op::source);
    img.paint(brush{color}, nullopt, rp);
    
    CHECK( CompareImageColor(img, 0, 0, color, 0.03f) == true );
}

TEST_CASE("XRGB32 image_surface handles colors with transparency as premultiplied with dropped alpha")
{
    auto img = image_surface{format::xrgb32, 1, 1};
    
    auto color = rgba_color{75, 150, 225, 42};
  
    render_props rp;    
    rp.compositing(compositing_op::source);
    
    SECTION("Painting via solid color") {
        img.paint(brush{color}, nullopt, rp);
    }
    SECTION("Painting via linear gradient") {
        auto b = brush{ point_2d{0.f, 0.f}, point_2d{1.f, 0.f}, { {0.f, color}, {1.f, color}  } };        
        img.paint(b, nullopt, rp);
    }    
    SECTION("Painting via brush surface") {
        auto brush_img = image_surface{format::argb32, 1, 1};
        brush_img.paint(brush{color}, nullopt, rp);    
        img.paint(brush{move(brush_img)}, nullopt, rp);
    }
    
    CHECK( CompareImageColor(img, 0, 0, ConvertToAlphaless(color), 0.03f) == true );
}

TEST_CASE("XRGB32 image_surfaces are handled as their alpha values are 1.0f")
{
    auto img_brush = image_surface{format::xrgb32, 1, 1};
    auto color = rgba_color{75, 150, 225};
    img_brush.paint(brush{color});
    auto b = brush{move(img_brush)};
    
    auto img = image_surface{format::argb32, 1, 1};
    img.paint(b);    
    
    CHECK( CompareImageColor(img, 0, 0, color, 0.03f) == true );    
}

#define ITERATE_OVER_COLORS\
    SECTION("black color, black alpha") {\
        color = rgba_color{0, 0, 0, 0};\
    }\
    SECTION("grey color, black alpha") {\
        color = rgba_color{128, 128, 128, 0};\
    }\
    SECTION("white color, black alpha") {\
        color = rgba_color{255, 255, 255, 0};\
    }\
    SECTION("black color, grey alpha") {\
        color = rgba_color{0, 0, 0, 128};\
    }\
    SECTION("grey color, grey alpha") {\
        color = rgba_color{128, 128, 128, 128};\
    }\
    SECTION("white color, grey alpha") {\
        color = rgba_color{255, 255, 255, 128};\
    }\
    SECTION("black color, white alpha") {\
        color = rgba_color{0, 0, 0, 255};\
    }\
    SECTION("grey color, white alpha") {\
        color = rgba_color{128, 128, 128, 255};\
    }\
    SECTION("white color, white alpha") {\
        color = rgba_color{255, 255, 255, 255};\
    }

TEST_CASE("A8 image_surfaces use only alpha channel of colors")
{
    auto img = image_surface{format::a8, 1, 1};
    rgba_color color;
    
    SECTION("Painting via solid color") {
        ITERATE_OVER_COLORS;
        img.paint(brush{color});        
    }
    SECTION("Painting via linear gradient") {
        ITERATE_OVER_COLORS;        
        auto b = brush{ point_2d{0.f, 0.f}, point_2d{1.f, 0.f}, { {0.f, color}, {1.f, color} } };        
        img.paint(b);
    }    
    SECTION("Painting via brush surface") {
        ITERATE_OVER_COLORS;
        auto brush_img = image_surface{format::argb32, 1, 1};
        brush_img.paint(brush{color});    
        img.paint(brush{move(brush_img)});
    }    
    
    CHECK( CompareImageColor(img, 0, 0, ConvertToAlphaonly(color), 0.03f) == true );    
}

TEST_CASE("A8 image_surfaces are handled as their color values are 0.0f")
{
    rgba_color color;
    ITERATE_OVER_COLORS;
    
    auto brush_img = image_surface{format::a8, 1, 1};
    brush_img.paint(brush{color});
    
    auto img = image_surface{format::argb32, 1, 1};
    img.paint(brush{move(brush_img)});

    CHECK( CompareImageColor(img, 0, 0, ConvertToAlphaonly(color), 0.03f) == true );    
}
