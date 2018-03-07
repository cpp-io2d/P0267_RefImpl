#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

TEST_CASE("IO2D properly paints background")
{
    auto reference = "red_background_300x200.png";
    auto image = image_surface{format::argb32, 300, 200};
    SECTION("Proper color") {
        image.paint( brush{rgba_color::red} );
        CHECK( ComparePNGExact(image, reference) == true );
    }
    SECTION("Invalid color") {
        image.paint( brush{rgba_color::blue} );
        CHECK( ComparePNGExact(image, reference) == false );
    }
}
