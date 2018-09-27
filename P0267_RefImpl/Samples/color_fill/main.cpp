
#include <io2d.h>

using namespace std::experimental::io2d;

int main(int argc, const char *argv[]) {
    auto display = output_surface {512, 512, format::argb32, scaling::none, refresh_style::fixed, 30.f};
    display.size_change_callback([&](output_surface &surface) {
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](auto &surface) {
        brush mainColor {rgba_color::green};
        surface.paint(mainColor);
    });
    display.begin_show();
    return 0;
}
