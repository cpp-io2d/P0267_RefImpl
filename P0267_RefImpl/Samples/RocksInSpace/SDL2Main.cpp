#include <io2d.h>
#include "Game.h"
#include <SDL.h>

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

void rocks_in_space::get_key_states()
{
    static const auto anti_clockwise_key = SDL_GetScancodeFromKey(SDLK_q);
    static const auto clockwise_key = SDL_GetScancodeFromKey(SDLK_w);
    static const auto thrust_key = SDL_GetScancodeFromKey(SDLK_u);
    static const auto fire_key = SDL_GetScancodeFromKey(SDLK_i);
    static const auto hyperspace_key = SDL_GetScancodeFromKey(SDLK_o);

    int num_keys = 0;
    const auto *key_states = SDL_GetKeyboardState(&num_keys);
    auto get = [&](SDL_Keycode key) {
        if (key >= 0 && key < num_keys) {
            return (key_states[key] != 0);
        }
        return false;
    };
    press() = { get(anti_clockwise_key), get(clockwise_key), get(thrust_key), get(fire_key), get(hyperspace_key)};
}

static auto & display() {
    static output_surface display{ 640, 480, format::argb32, scaling::letterbox, refresh_style::fixed, 60.0f };
    return display;
}

static rocks_in_space::game game;

int main(int argc, const char * argv[])
{
    display().draw_callback([&](output_surface& os) { game.update<output_surface>(os); });
    display().begin_show();
    return 0;
}
