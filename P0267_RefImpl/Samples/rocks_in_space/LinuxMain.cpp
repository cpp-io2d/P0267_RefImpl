#include <io2d.h>
#include "Game.h"
#include <X11/Xlib.h>

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

void rocks_in_space::get_key_states()
{
    static const auto display = XOpenDisplay(nullptr);
    static const auto anti_clockwise_key = XKeysymToKeycode( display, XK_Q );
    static const auto clockwise_key = XKeysymToKeycode( display, XK_W );
    static const auto thrust_key = XKeysymToKeycode( display, XK_U );
    static const auto fire_key = XKeysymToKeycode( display, XK_I );
    static const auto hyperspace_key = XKeysymToKeycode( display, XK_O );

    char keys[32];
    XQueryKeymap( display, keys );
    auto get = [&](uint16_t key) -> bool { return keys[key/8] & (1 << (key%8)); };
    press() = { get(anti_clockwise_key), get(clockwise_key), get(thrust_key), get(fire_key), get(hyperspace_key)};
}

void RunAsteroids()
{
    rocks_in_space::game game;
    output_surface display{ 640, 480, format::argb32, scaling::letterbox, refresh_style::fixed, 60.0f };
    display.draw_callback([&](output_surface& os) { game.update<output_surface>(os); });
    display.begin_show();
}

int main(int /*argc*/, const char** /*argv*/)
{
    RunAsteroids();
    return 0;
}
