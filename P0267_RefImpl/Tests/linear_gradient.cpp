#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

TEST_CASE("IO2D properly draws a linear gradient")
{
    auto reference = "linear_gradient_aquamarine_dark_magenta_lime_300x200.png";
    auto image = image_surface{format::argb32, 300, 200};

    SECTION("Draw with abs coordinates") {
        auto b = brush{ {0.f, 100.f},
                        {300.f, 100.f},
                        {gradient_stop{0.0f, rgba_color::aquamarine},
                         gradient_stop{0.5f, rgba_color::dark_magenta},
                         gradient_stop{1.0f, rgba_color::lime}}};
        auto pb = path_builder{};
        pb.new_figure({0.f, 0.f});
        pb.rel_line({300.f, 0.f});
        pb.rel_line({0.f, 200.f});
        pb.rel_line({-300.f, 0.f});
        pb.rel_line({0.f, -200.f});
        pb.close_figure();
        image.fill(b, pb);
    }

    CHECK( ComparePNGWithTolerance(image, reference, 0.01f) == true );
}
