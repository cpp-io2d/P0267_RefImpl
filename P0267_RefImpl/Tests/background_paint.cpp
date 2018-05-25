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
    SECTION("Proper color with paint()") {
        image.paint( brush{rgba_color::red} );
        CHECK( CompareWithPNGImage(image, reference) == true );
    }
    SECTION("Draw via fill()") {
        auto pb = path_builder{};
        pb.new_figure({0.f, 0.f});
        pb.rel_line({300.f, 0.f});
        pb.rel_line({0.f, 200.f});
        pb.rel_line({-300.f, 0.f});
        pb.rel_line({0.f, -200.f});
        pb.close_figure();
        image.fill( brush{rgba_color::red}, pb);
        CHECK( CompareWithPNGImage(image, reference) == true );
    }
    SECTION("Invalid color") {
        image.paint( brush{rgba_color::blue} );
        CHECK( CompareWithPNGImage(image, reference) == false );
    }
}
