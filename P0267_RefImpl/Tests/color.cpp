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
                    
                    CHECK( CheckPNGColorWithTolerance(img, 0, 0, color, 0.05) == true);
                }
}
