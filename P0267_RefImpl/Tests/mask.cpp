#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

TEST_CASE("Properly blends a solid brush with a solid mask")
{
    image_surface img{format::argb32, 1, 1};
    img.paint(brush{rgba_color{0., 0., 0., 0.0}});
    
    SECTION("M=1.0, S=1.0") {
        img.mask(brush{rgba_color{1., 1., 1., 1.}}, brush{rgba_color{0., 0., 0., 1.0}} );
        CHECK( CheckPNGColorWithTolerance(img, 0, 0, rgba_color(1., 1., 1., 1.0), 0.01) == true);
    }
    SECTION("M=1.0, S=0.5") {
        img.mask(brush{rgba_color{1., 1., 1., 0.5}}, brush{rgba_color{0., 0., 0., 1.0}} );
        CHECK( CheckPNGColorWithTolerance(img, 0, 0, rgba_color(1., 1., 1., 0.5), 0.01) == true);
    }    
    SECTION("M=0.9, S=1.0") {
        img.mask(brush{rgba_color{1., 1., 1., 1.}}, brush{rgba_color{0., 0., 0., 0.9}} );
        CHECK( CheckPNGColorWithTolerance(img, 0, 0, rgba_color(1., 1., 1., 0.9), 0.01) == true);
    }
    SECTION("M=0.9, S=0.5") {
        img.mask(brush{rgba_color{1., 1., 1., 0.5}}, brush{rgba_color{0., 0., 0., 0.9}} );
        CHECK( CheckPNGColorWithTolerance(img, 0, 0, rgba_color(1., 1., 1., 0.45), 0.01) == true);        
    }
    SECTION("M=0.5, S=1.0") {
        img.mask(brush{rgba_color{1., 1., 1., 1.0}}, brush{rgba_color{0., 0., 0., 0.5}} );
        CHECK( CheckPNGColorWithTolerance(img, 0, 0, rgba_color(1., 1., 1., 0.5), 0.01) == true);
    }
    SECTION("M=0.5, S=0.5") {
        img.mask(brush{rgba_color{1., 1., 1., 0.7}}, brush{rgba_color{0., 0., 0., 0.5}} );
        CHECK( CheckPNGColorWithTolerance(img, 0, 0, rgba_color(1., 1., 1., 0.35), 0.01) == true);
    }
    SECTION("M=0.1, S=1.0") {
        img.mask(brush{rgba_color{1., 1., 1., 1.}}, brush{rgba_color{0., 0., 0., 0.1}} );
        CHECK( CheckPNGColorWithTolerance(img, 0, 0, rgba_color(1., 1., 1., 0.1), 0.01) == true);
    }    
    SECTION("M=0.1, S=0.5") {
        img.mask(brush{rgba_color{1., 1., 1., 0.5}}, brush{rgba_color{0., 0., 0., 0.1}} );
        CHECK( CheckPNGColorWithTolerance(img, 0, 0, rgba_color(1., 1., 1., 0.05), 0.01) == true);
    }    
    SECTION("M=0.0, S=1.0") {
        img.mask(brush{rgba_color{1., 1., 1., 1.}}, brush{rgba_color{0., 0., 0., 0.0}} );
        CHECK( CheckPNGColorWithTolerance(img, 0, 0, rgba_color(0., 0., 0., 0.0), 0.01) == true);
    }
    SECTION("M=0.0, S=0.5") {
        img.mask(brush{rgba_color{1., 1., 1., 0.5}}, brush{rgba_color{0., 0., 0., 0.0}} );
        CHECK( CheckPNGColorWithTolerance(img, 0, 0, rgba_color(0., 0., 0., 0.0), 0.01) == true);
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
    CHECK( ComparePNGWithTolerance(img, reference, 0.02f) == true );
}
