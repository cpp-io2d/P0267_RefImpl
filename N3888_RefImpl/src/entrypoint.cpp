//#define _HAS_CXX17 1
#include "io2d.h"
#include "sample_draw.h"
#include <chrono>
#include <assert.h>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;

int main() {
    constexpr bool nemc1 = is_nothrow_move_constructible_v<brush>;
    constexpr bool nemc2 = is_nothrow_move_constructible_v<display_surface>;
    constexpr bool nemc3 = is_nothrow_move_constructible_v<surface>;
    constexpr bool nemc4 = is_nothrow_move_constructible_v<rectangle>;
    constexpr bool nemc5 = is_nothrow_move_constructible_v<unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>>;
    constexpr bool nemc6 = is_nothrow_move_constructible_v<weak_ptr<::std::experimental::io2d::device>>;
    constexpr bool nemc7 = is_nothrow_move_constructible_v<device>;
    constexpr bool nemc8 = is_nothrow_move_constructible_v<image_surface>;
    constexpr bool nema8 = is_nothrow_move_assignable_v<image_surface>;
    constexpr bool cc8 = is_copy_constructible_v<image_surface>;
    constexpr bool ca8 = is_copy_assignable_v<image_surface>;
    constexpr bool nemc9 = is_nothrow_move_constructible_v<function<void(display_surface& sfc)>>;
    constexpr bool nemc10 = is_nothrow_move_constructible_v<optional<brush>>;
    constexpr bool necc1 = is_copy_constructible_v<image_surface>;
    //auto ds = make_display_surface(640, 480, format::argb32);

    //auto imgSfc = make_image_surface(format::argb32, 1280, 720);
    auto ds = make_display_surface(1280, 720, format::argb32, scaling::letterbox, refresh_rate::as_fast_as_possible, 30.0);
    //ds.draw_callback([](display_surface& ds) {
	//	ds.paint(bgra_color::firebrick());
	//	//ds.render_text("Hello world!", { 50.0, 50.0 }, bgra_color::aqua());
	//});
	//return ds.show();

	//assert(steady_clock::is_steady);
	//display_surface ds(1280, 720, format::argb32, scaling::letterbox, refresh_rate::fixed, 30.0);
	//auto radialFactory = radial_brush_factory({ 0.0, 0.0 }, 0.0, { 0.0, 0.0 }, 50.0);
	//radialFactory.add_color_stop(0.0, bgra_color::orange());
	//radialFactory.add_color_stop(1.0, bgra_color::aquamarine());
	//auto letterboxBrush = brush(radialFactory);
	//letterboxBrush.wrap_mode(wrap_mode::repeat);
	//ds.letterbox_brush(letterboxBrush);

	sample_draw sd;
	ds.draw_callback(sd);
	return ds.begin_show();
}
