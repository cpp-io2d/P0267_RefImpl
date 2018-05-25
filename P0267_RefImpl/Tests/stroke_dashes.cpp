#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

TEST_CASE("IO2D strokes with proper dashes")
{
    auto reference = "dash_pattern_two_one_300x200.png";
    auto image = image_surface{format::argb32, 300, 200};
    image.paint( brush{rgba_color::red} );
    auto b = brush{rgba_color::blue};
    
    SECTION("Draw left to right") {
        for( auto row = 0; row < 19; ++row ) {
            auto len = static_cast<float>(row + 1);
            auto d = dashes{0.f, {len * 2.f, len}};
            auto pb = path_builder{};
            pb.new_figure({10.f, 10.f + 10.f * row});
            pb.rel_line({280.f, 0.f});
            image.stroke(b, pb, nullopt, nullopt, d);
        }
    }
    
    SECTION("Draw right to left") {
        auto cp = clip_props{bounding_box{{10.f, 9.f}, {290.f, 191.f}}};
        for( auto row = 0; row < 19; ++row ) {
            auto len = static_cast<float>(row + 1);
            auto lenx3 = 3 * (row+1);
            auto d = dashes{0.f, {len * 2.f, len}};
            auto n = (280 / lenx3) + 1;
            auto pb = path_builder{};
            pb.new_figure({ 10.f + n*lenx3 - len, 10.f + 10.f * row});
            pb.rel_line({ static_cast<float>(-(n*lenx3 -len) ), 0.f});
            image.stroke(b, pb, nullopt, nullopt, d, nullopt, cp);
        }
    }
    
    CHECK( CompareWithPNGImage(image, reference) == true );
}
