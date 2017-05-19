#include "path_examples.h"

using namespace std;
using namespace std::experimental::io2d;

//void path_test() {
//	auto imgSfc = make_image_surface(format::argb32, 300, 200);
//	brush backBrush{ bgra_color::black() };
//	brush foreBrush{ bgra_color::white() };
//	path_builder<> pb{};
//	imgSfc.paint(backBrush);
//	// Example code goes here.
//
//	// Example code ends.
//#ifdef _Filesystem_support_test
//	imgSfc.save(experimental::filesystem::path("pathexample01.png"), image_data_format::png);
//#else
//	imgSfc.save("pathexample01.png"s, image_data_format::png);
//#endif
//}

namespace path_test {
	void path_test_1() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ bgra_color::black() };
		brush foreBrush{ bgra_color::white() };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		pb.new_path({ 80.0, 20.0 });
		pb.line_to({ 220.0, 20.0 });
		pb.rel_line_to({ 60.0, 160.0 });
		pb.rel_line_to({ -260.0, 0.0 });
		pb.close_path();
		imgSfc.stroke(foreBrush, pb);

		// Example code ends.
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path("pathexample01.png"), image_data_format::png);
#else
		imgSfc.save("pathexample01.png"s, image_data_format::png);
#endif
	}

	void path_test_2() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ bgra_color::black() };
		brush foreBrush{ bgra_color::white() };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
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

		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 10.0 });

		// Example code ends.
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path("pathexample02.png"), image_data_format::png);
#else
		imgSfc.save("pathexample02.png"s, image_data_format::png);
#endif
	}

	void path_test_3() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ bgra_color::black() };
		brush foreBrush{ bgra_color::white() };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		pb.new_path({ 80.0, 20.0 });
		pb.line_to({ 220.0, 20.0 });
		pb.rel_line_to({ 60.0, 160.0 });
		pb.rel_line_to({ -260.0, 0.0 });
		pb.close_path();
		imgSfc.stroke(foreBrush, pb);

		// Example code ends.
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path("pathexample03.png"), image_data_format::png);
#else
		imgSfc.save("pathexample03.png"s, image_data_format::png);
#endif
	}

	void path_test_4() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ bgra_color::black() };
		brush foreBrush{ bgra_color::white() };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		pb.new_path({ 80.0, 20.0 });
		pb.line_to({ 220.0, 20.0 });
		pb.rel_line_to({ 60.0, 160.0 });
		pb.rel_line_to({ -260.0, 0.0 });
		pb.close_path();
		imgSfc.stroke(foreBrush, pb);

		// Example code ends.
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path("pathexample04.png"), image_data_format::png);
#else
		imgSfc.save("pathexample04.png"s, image_data_format::png);
#endif
	}

	void path_test_5() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ bgra_color::black() };
		brush foreBrush{ bgra_color::white() };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		pb.new_path({ 80.0, 20.0 });
		pb.line_to({ 220.0, 20.0 });
		pb.rel_line_to({ 60.0, 160.0 });
		pb.rel_line_to({ -260.0, 0.0 });
		pb.close_path();
		imgSfc.stroke(foreBrush, pb);

		// Example code ends.
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path("pathexample05.png"), image_data_format::png);
#else
		imgSfc.save("pathexample05.png"s, image_data_format::png);
#endif
	}
}
