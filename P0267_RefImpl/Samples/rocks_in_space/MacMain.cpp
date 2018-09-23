#include <io2d.h>
#include <CoreGraphics/CoreGraphics.h>
#include "Game.h"
using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

void rocks_in_space::get_key_states()
{
    auto anti_clockwise_key = 12; // Q
    auto clockwise_key = 13; // W
    auto thrust_key = 32; // U
    auto fire_key = 34; // I
    auto hyperspace_key = 31; // O
    auto get = [](uint16_t key){ return CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState, key); };
    press() = { get(anti_clockwise_key), get(clockwise_key), get(thrust_key), get(fire_key), get(hyperspace_key)};
}

void RunAsteroids()
{
    rocks_in_space::game game;
    output_surface display{ 640, 480, format::argb32, scaling::letterbox, refresh_style::fixed, 60.0f };
    display.draw_callback([&](output_surface& os) { game.update<output_surface>(os); });
    display.begin_show();
}

int main(int argc, const char * argv[])
{
    RunAsteroids();
    return 0;
}
