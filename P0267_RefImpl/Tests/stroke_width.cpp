#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

TEST_CASE("IO2D strokes with a proper width")
{
    auto reference = "stroke_widths_300x200.png";
    auto image = image_surface{format::argb32, 300, 200};
    image.paint( brush{rgba_color::red} );
    auto b = brush{rgba_color::blue};

    for( int width = 1; width <= 9; ++width ) {
        auto sp = stroke_props{static_cast<float>(width), line_cap::none};
        auto pb = path_builder{};
        pb.new_figure({20.f, 10.f + 20.f * width + (width % 2 ? 0.5f : 0.f)});
        pb.rel_line({260.f, 0.f});
        image.stroke(b, pb, nullopt, sp);
    }

    CHECK( ComparePNGExact(image, reference) == true );
}
