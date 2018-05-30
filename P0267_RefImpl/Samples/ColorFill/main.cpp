#include <io2d.h>
#include <mutex>

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

static output_surface & display() {
    static auto surface = output_surface{500, 500, format::argb32, scaling::none, refresh_style::fixed, 30.f};
    return surface;
}

int main(int argc, const char * argv[]) {
    display().size_change_callback([&](output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display().draw_callback([&](auto& surface) {
        brush greenBrush{rgba_color::green};
        surface.paint(greenBrush);
    });
    display().begin_show();
    return 0;
}
