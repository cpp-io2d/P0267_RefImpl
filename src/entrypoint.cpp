#include "io2d.h"
#include "sample_draw.h"
#include <chrono>
#include <assert.h>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;

int main() {
	assert(steady_clock::is_steady);
	auto ds = make_display_surface(1280, 720, format::argb32, scaling::letterbox);
	auto radialFactory = radial_brush_factory({ 0.0, 0.0 }, 0.0, { 0.0, 0.0 }, 50.0);
	radialFactory.add_color_stop(0.0, rgba_color::orange());
	radialFactory.add_color_stop(1.0, rgba_color::aquamarine());
	auto letterboxBrush = brush(radialFactory);
	letterboxBrush.extend(extend::repeat);
	ds.letterbox_brush(letterboxBrush);
	sample_draw sd;
	ds.draw_callback(sd);
	//ds.draw_callback([](display_surface& sfc) {
	//	sfc.paint(rgba_color::cornflower_blue);
	//	sfc.font_size(48.0);
	//	sfc.render_text("Hello ISO C++!", { 50.0, 50.0 }, rgba_color::white);
	//});
	return ds.show();
}

