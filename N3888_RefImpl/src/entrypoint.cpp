#include "io2d.h"
#include "sample_draw.h"
#include <chrono>
#include <assert.h>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;

int main() {

	auto imgSfc = make_image_surface(format::argb32, 300, 200);
	auto bkgrndBrush = brush(bgra_color::black());
	auto frgrndBrush = brush(bgra_color::white());
	path_builder<> pb{};

	pb.clear();
	pb.new_path({ 80.0, 20.0 });
	pb.line_to({ 220.0, 20.0 });
	pb.rel_line_to({ 60.0, 160.0 });
	pb.rel_line_to({ -260.0, 0.0 });
	pb.close_path();

	imgSfc.paint(bkgrndBrush);
	imgSfc.stroke(frgrndBrush, pb);
#ifdef _Filesystem_support_test
	imgSfc.save(experimental::filesystem::path("pathexample01.png"), image_data_format::png);
#else
	imgSfc.save("pathexample01.png"s, image_data_format::png);
#endif
	pb.clear();
	pb.new_path({ 20.0, 20.0 });
	pb.rel_line_to({ 100.0, 0.0 });
	pb.rel_line_to({ 0.0, 160.0 });
	pb.rel_line_to({ -100.0, 0.0 });
	pb.rel_line_to({ 0.0, -160.0 });

	pb.new_path({ 180.0, 20.0 });
	pb.rel_line_to({ 100.0, 0.0 });
	pb.rel_line_to({ 0.0, 160.0 });
	pb.rel_line_to({ -100.0, 0.0 });
	pb.close_path();

	imgSfc.paint(bkgrndBrush);
	imgSfc.stroke(frgrndBrush, pb, nullopt, stroke_props{ 10.0 });
#ifdef _Filesystem_support_test
	imgSfc.save(experimental::filesystem::path("pathexample02.png"), image_data_format::png);
#else
	imgSfc.save("pathexample02.png"s, image_data_format::png);
#endif
	return 0;
	//auto ds = make_display_surface(1280, 720, format::argb32, scaling::letterbox, refresh_rate::as_fast_as_possible, 30.0);
	//sample_draw sd;
	//ds.draw_callback(sd);
	//return ds.begin_show();
}
