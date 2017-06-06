#include "path_examples.h"

using namespace std;
using namespace std::experimental::io2d;

//void path_test() {
//	auto imgSfc = make_image_surface(format::argb32, 300, 200);
//	brush backBrush{ rgba_color::black() };
//	brush foreBrush{ rgba_color::white() };
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
		brush backBrush{ rgba_color::black() };
		brush foreBrush{ rgba_color::white() };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		pb.new_path({ 80.0, 20.0 });
		pb.line_to({ 220.0, 20.0 });
		pb.rel_line_to({ 60.0, 160.0 });
		pb.rel_line_to({ -260.0, 0.0 });
		pb.close_path();
		imgSfc.stroke(foreBrush, pb, nullopt, nullopt, nullopt, aliased);

		// Example code ends.
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path("pathexample01.png"), image_data_format::png);
#else
		imgSfc.save("pathexample01.png"s, image_data_format::png);
#endif
	}

	void path_test_2() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ rgba_color::black() };
		brush foreBrush{ rgba_color::white() };
		render_props aliased{ antialias::none };
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

		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 10.0 }, nullopt, aliased);

		// Example code ends.
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path("pathexample02.png"), image_data_format::png);
#else
		imgSfc.save("pathexample02.png"s, image_data_format::png);
#endif
	}

	void path_test_3() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ rgba_color::black() };
		brush foreBrush{ rgba_color::white() };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		pb.new_path({ 20.0, 20.0 });
		pb.rel_quadratic_curve_to({ 60.0, 120.0 }, { 60.0, -120.0 });
		pb.rel_new_path({ 20.0, 0.0 });
		pb.rel_quadratic_curve_to({ 60.0, 120.0 }, { 60.0, -120.0 });
		pb.close_path();
		pb.new_path({ 20.0, 150.0 });
		pb.rel_cubic_curve_to({ 40.0, -120.0 }, { 40.0, 120.0 * 2.0 }, { 40.0, -120.0 });
		pb.rel_new_path({ 20.0, 0.0 });
		pb.rel_cubic_curve_to({ 40.0, -120.0 }, { 40.0, 120.0 * 2.0 }, { 40.0, -120.0 });
		pb.close_path();
		imgSfc.stroke(foreBrush, pb, nullopt, nullopt, nullopt, aliased);

		// Example code ends.
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path("pathexample03.png"), image_data_format::png);
#else
		imgSfc.save("pathexample03.png"s, image_data_format::png);
#endif
	}

	void path_test_4() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ rgba_color::black() };
		brush foreBrush{ rgba_color::white() };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		const matrix_2d sclMtx = matrix_2d::init_scale({ 0.9, 1.1 });// .rotate(half_pi<double>);// * matrix_2d::init_rotate(half_pi<double>);
		auto pt = sclMtx.inverse().transform_pt({ 85.0, 100.0 }) +
			point_for_angle(half_pi<double> / 2.0, 50.0);
		pb.matrix(sclMtx);
		pb.new_path(pt);
		pb.arc({ 50.0, 50.0 }, three_pi_over_two<double>, half_pi<double> / 2.0);
		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 10.0 });// , nullopt, aliased);
		pb.clear();
		pb.new_path({ 130.0, 105.0 });
		pb.rel_line_to({ 0.0, -10.0 });
		pb.rel_line_to({ 25.0, 0.0 });
		pb.rel_line_to({ 0.0, -25.0 });
		pb.rel_line_to({ 10.0, 0.0 });
		pb.rel_line_to({ 0.0, 25.0 });
		pb.rel_line_to({ 25.0, 0.0 });
		pb.rel_line_to({ 0.0, 10.0 });
		pb.rel_line_to({ -25.0, 0.0 });
		pb.rel_line_to({ 0.0, 25.0 });
		pb.rel_line_to({ -10.0, 0.0 });
		pb.rel_line_to({ 0.0, -25.0 });
		pb.close_path();
		imgSfc.fill(foreBrush, pb);
		pb.insert(pb.begin(), path_data::abs_matrix(matrix_2d::init_translate({ 80.0, 0.0 })));
		imgSfc.fill(foreBrush, pb);
		// Example code ends.
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path("pathexample04.png"), image_data_format::png);
#else
		imgSfc.save("pathexample04.png"s, image_data_format::png);
#endif
	}

	void path_test_5() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ rgba_color::black() };
		brush foreBrush{ rgba_color::white() };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		brush blueBrush{ rgba_color::blue() };
		stroke_props ten{ 10.0 };
		pb.new_path({ 30.0, 30.0 });
		pb.rel_line_to({ 105.0, 0.0 });
		pb.rel_line_to({ 0.0, 140.0 });
		pb.rel_line_to({ -105.0, 0.0 });
		pb.close_path();
		imgSfc.stroke(foreBrush, pb, nullopt, ten);
		imgSfc.fill(blueBrush, pb);
		pb.insert(pb.begin(), path_data::abs_matrix(matrix_2d::init_translate({ 135.0, 0.0 })));
		imgSfc.fill(blueBrush, pb);
		imgSfc.stroke(foreBrush, pb, nullopt, ten);
		// Example code ends.
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path("pathexample05.png"), image_data_format::png);
#else
		imgSfc.save("pathexample05.png"s, image_data_format::png);
#endif
	}

	void path_test_6() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ rgba_color::black() };
		brush foreBrush{ rgba_color::white() };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		pb.new_path({ 90.0, 90.0 });
//		pb.abs_matrix(matrix_2d::init_rotate(half_pi<double> / 2.0));
		//pb.rel_line_to({ 0.0, 30.0 });
		pb.arc({ 20.0, 16.0 }, three_pi_over_two<double>, pi<double> + half_pi<double> / 2.0);

		//pb.abs_matrix(matrix_2d::init_shear_x(tan(half_pi<double> / 2.0)).reflect(half_pi<double>));
		//pb.rel_line_to({ 100.0, 0.0 });
		//pb.rel_line_to({ 0.0, 160.0 });
		//pb.rel_line_to({ -100.0, 0.0 });
		////pb.rel_line_to({ 0.0, -160.0 });
		//pb.close_path();

		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 10.0 }, nullopt, aliased);
		// Example code ends.
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path("pathexample06.png"), image_data_format::png);
#else
		imgSfc.save("pathexample06.png"s, image_data_format::png);
#endif
	}
}
