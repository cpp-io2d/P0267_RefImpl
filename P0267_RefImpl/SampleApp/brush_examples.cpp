#include "brush_examples.h"

#include "xcairo.h"

using namespace std;
using namespace std::experimental::io2d;
using namespace std::experimental::io2d::v1::cairo;

namespace brush_test {
	void solid_color_test_01() {
		auto imgSfc = make_image_surface<cairo_renderer>(format::argb32, 300, 200);
		brush<cairo_renderer> backBrush{ rgba_color::black };
		brush<cairo_renderer> foreBrush{ rgba_color::white };
		path_builder<> pb{};
		imgSfc.paint(backBrush);
		pb.new_figure({ 80.0, 20.0 });
		pb.line({ 220.0, 20.0 });
		pb.rel_line({ 60.0, 160.0 });
		pb.rel_line({ -260.0, 0.0 });
		pb.close_figure();

		// Example code goes here.
		brush<cairo_renderer> fillBrush{ rgba_color::orange };
		imgSfc.stroke(foreBrush, pb);
		imgSfc.fill(fillBrush, pb);

		// Example code ends.
		std::string filename = "brushexample01.png";
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path(filename), image_file_format::png);
#else
		imgSfc.save(filename, image_file_format::png);
#endif

	}
	void linear_gradient_test_01() {

	}
	void radial_gradient_test_01() {

	}
	void surface_test_01() {

	}
}
