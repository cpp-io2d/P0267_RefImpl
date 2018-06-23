
#include <io2d.h>

using namespace std::experimental::io2d;

static output_surface & display() {
    static auto surface = output_surface {512, 512, format::argb32, scaling::none, refresh_style::as_needed, 30.f};
    return surface;
}

int main(int argc, const char *argv[]) {
    try {
        auto &d = display();
        d.size_change_callback([&](output_surface &surface) {
            surface.dimensions(surface.display_dimensions());
        });
        d.draw_callback([&](auto &surface) {
            brush mainColor {rgba_color::green};
            surface.paint(mainColor);
        });
        d.begin_show();
    } catch (const std::exception &ex) {
        printf("std::exception caught, what=\"%s\"\n", ex.what());
    } catch (...) {
        printf("unknown exception caught\n");
    }
    return 0;
}
