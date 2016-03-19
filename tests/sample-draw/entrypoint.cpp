#include "io2d.h"
#include "sample_draw.h"
#include <chrono>
#include <assert.h>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;

int main() {
	//auto ds = make_display_surface(640, 480, format::argb32);
	//ds.draw_callback([](display_surface& ds) {
	//	ds.paint(rgba_color::cornflower_blue());
	//	ds.render_text("Hello world!", { 50.0, 50.0 }, rgba_color::black());
	//});
	//return ds.show();

	assert(steady_clock::is_steady);
	auto ds = make_display_surface(1280, 720, format::argb32, scaling::letterbox, refresh_rate::fixed, 30.0);
	auto radialFactory = radial_brush_factory({ 0.0, 0.0 }, 0.0, { 0.0, 0.0 }, 50.0);
	radialFactory.add_color_stop(0.0, rgba_color::orange());
	radialFactory.add_color_stop(1.0, rgba_color::aquamarine());
	auto letterboxBrush = brush(radialFactory);
	letterboxBrush.extend(extend::repeat);
	ds.letterbox_brush(letterboxBrush);
	sample_draw sd;
	ds.draw_callback(sd);
	return ds.show();
}

