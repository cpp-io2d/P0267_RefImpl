#include "catch.hpp"
#include <io2d.h>
#include "comparison.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

TEST_CASE("IO2D properly draws a radial gradient")
{
    auto reference = "radial_gradient_aquamarine_dark_magenta_lime_300x200.png";
    auto image = image_surface{format::argb32, 300, 200};
    
    SECTION("Draw with an identity brush matrix") {
        auto b = brush{ circle{{100.f, 100.f}, 90},
                        circle{{150.f, 150.f}, 0},
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
        image.fill(b, pb, brush_props{wrap_mode::none});
    }
    SECTION("Draw with a translation brush matrix") {
        auto b = brush{ circle{{50.f, 0.f}, 90},
                        circle{{100.f, 50.f}, 0},
                        {gradient_stop{0.0f, rgba_color::aquamarine},
                         gradient_stop{0.5f, rgba_color::dark_magenta},
                         gradient_stop{1.0f, rgba_color::lime}}};
        auto m = matrix_2d::init_translate({-50.f, -100.f});
        auto pb = path_builder{};
        pb.new_figure({0.f, 0.f});
        pb.rel_line({300.f, 0.f});
        pb.rel_line({0.f, 200.f});
        pb.rel_line({-300.f, 0.f});
        pb.rel_line({0.f, -200.f});
        pb.close_figure();
        image.fill(b, pb, brush_props{wrap_mode::none, filter::good, fill_rule::winding, m});
    }
    
    CHECK( ComparePNGWithTolerance(image, reference, 0.02f, 2) == true );
}

TEST_CASE("IO2D properly draws a radial gradient with a reflected pattern")
{
    auto reference = "radial_gradient_aquamarine_dark_magenta_lime_reflect_300x200.png";
    auto image = image_surface{format::argb32, 300, 200};
    auto b = brush{ circle{{100.f, 100.f}, 90},
        circle{{150.f, 150.f}, 0},
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
    image.fill(b, pb, brush_props{wrap_mode::reflect});
    
    CHECK( ComparePNGWithTolerance(image, reference, 0.02f, 2) == true );
}
