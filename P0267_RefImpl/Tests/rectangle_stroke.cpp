#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

TEST_CASE("IO2D properly strokes a rectangle")
{
    auto reference = "stroked_rectangle_300x200.png";
    auto image = image_surface{format::argb32, 300, 200};
    image.paint( brush{rgba_color::red} );

    SECTION("Draw using relative coordinates") {
        auto pb = path_builder{};
        pb.new_figure({50.f, 50.f});
        pb.rel_line({200.f, 0.f});
        pb.rel_line({0.f, 100.f});
        pb.rel_line({-200.f, 0.f});
        pb.rel_line({0.f, -100.f});
        pb.close_figure();
        image.stroke(brush{rgba_color::blue}, pb);
        CHECK( ComparePNGExact(image, reference) == true );
    }
}
