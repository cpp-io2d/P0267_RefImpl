#include "path_examples.h"

using namespace std;
using namespace std::experimental::io2d;

//void path_test() {
//	auto imgSfc = make_image_surface(format::argb32, 300, 200);
//	brush backBrush{ rgba_color::black() };
//	brush foreBrush{ rgba_color::white() };
//	render_props aliased{ antialias::none };
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
		pb.line({ 220.0, 20.0 });
		pb.rel_line({ 60.0, 160.0 });
		pb.rel_line({ -260.0, 0.0 });
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
		pb.rel_line({ 100.0, 0.0 });
		pb.rel_line({ 0.0, 160.0 });
		pb.rel_line({ -100.0, 0.0 });
		pb.rel_line({ 0.0, -160.0 });

		pb.new_path({ 180.0, 20.0 });
		pb.rel_line({ 100.0, 0.0 });
		pb.rel_line({ 0.0, 160.0 });
		pb.rel_line({ -100.0, 0.0 });
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
		pb.rel_quadratic_curve({ 60.0, 120.0 }, { 60.0, -120.0 });
		pb.rel_new_path({ 20.0, 0.0 });
		pb.rel_quadratic_curve({ 60.0, 120.0 }, { 60.0, -120.0 });
		pb.close_path();
		pb.new_path({ 20.0, 150.0 });
		pb.rel_cubic_curve({ 40.0, -120.0 }, { 40.0, 120.0 * 2.0 }, { 40.0, -120.0 });
		pb.rel_new_path({ 20.0, 0.0 });
		pb.rel_cubic_curve({ 40.0, -120.0 }, { 40.0, 120.0 * 2.0 }, { 40.0, -120.0 });
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
		const vector_2d rad{ 50.0, 50.0 };
		//auto pt = sclMtx.inverse().transform_pt({ 85.0, 100.0 }) +
		//	point_for_angle(half_pi<double> / 2.0, rad);
		//auto pt = sclMtx.inverse().transform_pt({ 85.0, 100.0 }) +
		//	point_for_angle(half_pi<double> / 2.0, 50.0);
		//auto pt = vector_2d{ 85.0, 100.0 } + 
		//	point_for_angle(half_pi<double> / 2.0, rad);
		auto pt = arc_start({ 85.0, 100.0 }, half_pi<double> / 2.0, { 50.0, 50.0 }, sclMtx);
		pb.matrix(sclMtx);
		pb.new_path(pt);
		//pb.matrix(sclMtx);
		pb.arc({ 50.0, 50.0 }, three_pi_over_two<double>, half_pi<double> / 2.0);
		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 10.0 });// , nullopt, aliased);
		pb.clear();
		pb.new_path({ 130.0, 105.0 });
		pb.rel_line({ 0.0, -10.0 });
		pb.rel_line({ 25.0, 0.0 });
		pb.rel_line({ 0.0, -25.0 });
		pb.rel_line({ 10.0, 0.0 });
		pb.rel_line({ 0.0, 25.0 });
		pb.rel_line({ 25.0, 0.0 });
		pb.rel_line({ 0.0, 10.0 });
		pb.rel_line({ -25.0, 0.0 });
		pb.rel_line({ 0.0, 25.0 });
		pb.rel_line({ -10.0, 0.0 });
		pb.rel_line({ 0.0, -25.0 });
		pb.close_path();
		imgSfc.fill(foreBrush, pb);
		pb.insert(pb.begin(), path_data::abs_matrix(matrix_2d::init_translate({ 80.0, 0.0 })));
		//pb.insert(pb.begin() + 2, path_data::revert_matrix());
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
		pb.rel_line({ 105.0, 0.0 });
		pb.rel_line({ 0.0, 140.0 });
		pb.rel_line({ -105.0, 0.0 });
		pb.close_path();
		imgSfc.stroke(foreBrush, pb, nullopt, ten);
		imgSfc.fill(blueBrush, pb);
		pb.insert(pb.begin(), path_data::abs_matrix(matrix_2d::init_translate({ 135.0, 0.0 })));
		//pb.insert(pb.begin() + 2, path_data::revert_matrix());
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
		auto pt = vector_2d{ 80.0, 100.0 };
		pb.new_path(pt);
		pb.arc({ 30.0, 30.0 }, half_pi<double>, half_pi<double>);

		auto rot = matrix_2d::init_rotate(half_pi<double> / 2.0);
		pt.x(pt.x() + 50.0);
		pb.new_path(pt);
		pb.matrix(rot);
		pb.arc({ 30.0, 30.0 }, half_pi<double>, half_pi<double>);

		pb.revert_matrix();
		rot = matrix_2d::init_rotate(half_pi<double>);
		pt.x(pt.x() + 50.0);
		pb.new_path(pt);
		pb.matrix(rot.translate({ 20.0, 10.0 }));
		pb.arc({ 30.0, 30.0 }, half_pi<double>, half_pi<double>);

		imgSfc.stroke(foreBrush, pb, nullopt, nullopt, nullopt, aliased);
		// Example code ends.
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path("pathexample06.png"), image_data_format::png);
#else
		imgSfc.save("pathexample06.png"s, image_data_format::png);
#endif
	}

	void path_test_7() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ rgba_color::black() };
		brush foreBrush{ rgba_color::white() };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		auto scl = matrix_2d::init_scale({ 0.5, 1.0 });
		auto rot = matrix_2d::init_rotate(half_pi<double>);
		auto trn = matrix_2d::init_translate({ 20.0, 20.0 });
		pb.new_path({ 10.0, 150.0 });
		pb.quadratic_curve({ 30.0, 120.0 }, { 50.0, 150.0 });

		//pb.new_path({ 110.0, 150.0 });
		//pb.matrix(rot);
		//pb.quadratic_curve({ 130.0, 120.0 }, { 150.0, 150.0 });
		//pb.revert_matrix();

		pb.new_path({ 110.0, 150.0 });
		pb.matrix(rot);
		pb.quadratic_curve({ 130.0, 120.0 }, { 150.0, 150.0 });
		pb.revert_matrix();

		pb.new_path({ 170.0, 150.0 });
		pb.matrix(rot * scl);
		pb.rel_quadratic_curve({ 20.0, -30.0 }, { 20.0, 30.0 });
		pb.revert_matrix();

		pb.new_path({ 230.0, 150.0 });
		pb.matrix(scl * rot);
		pb.rel_quadratic_curve({ 20.0, -30.0 }, { 20.0, 30.0 });
		pb.revert_matrix();

		pb.new_path({ 290.0, 150.0 });
		pb.matrix(rot * trn);
		pb.rel_quadratic_curve({ 20.0, -30.0 }, { 20.0, 30.0 });
		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 2.0 }, nullopt, aliased);

		// Example code ends.
		string fileName = "pathexample07.png";
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path(fileName), image_data_format::png);
#else
		imgSfc.save(fileName, image_data_format::png);
#endif
	}

	void path_test_8() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ rgba_color::black() };
		brush foreBrush{ rgba_color::white() };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		auto scl = matrix_2d::init_scale({ 0.5, 1.0 });
		auto rot = matrix_2d::init_rotate(half_pi<double> / 2.0);
		auto trn = matrix_2d::init_translate({ 20.0, 20.0 });
		pb.matrix(scl);
		pb.new_path({ 40.0, 50.0 });
		pb.line({ 80.0, 50.0 });
		pb.new_path({ 40.0, 150.0 });
		pb.rel_line({ 40.0, 0.0 });
		pb.revert_matrix();
		pb.new_path({ 60.0, 150.0 });
		//pb.origin({ 60.0, 150.0 });
		pb.matrix(rot);
		pb.line({ 80.0, 150.0 });
		pb.rel_line({ 0.0, -20.0 });
		pb.revert_matrix();
		//pb.revert_origin();
		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 2.0 }, nullopt, aliased);
		// Example code ends.
		string fileName = "pathexample08.png";
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path(fileName), image_data_format::png);
#else
		imgSfc.save(fileName, image_data_format::png);
#endif
	}

	void path_test_9() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ rgba_color::black() };
		brush foreBrush{ rgba_color::white() };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		auto scl = matrix_2d::init_scale({ 0.5, 1.0 });
		auto rot = matrix_2d::init_rotate(half_pi<double> / 2.0);
		auto trn = matrix_2d::init_translate({ 20.0, 20.0 });
		pb.matrix(scl);
		pb.new_path({ 40.0, 50.0 });
		pb.line({ 80.0, 50.0 });
		pb.new_path({ 40.0, 150.0 });
		pb.rel_line({ 40.0, 0.0 });
		pb.revert_matrix();
		pb.new_path({ 60.0, 150.0 });
		//pb.origin({ 60.0, 150.0 });
		pb.matrix(rot);
		pb.line({ 80.0, 150.0 });
		pb.rel_line({ 0.0, -20.0 });
		pb.revert_matrix();
		//pb.revert_origin();
		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 2.0 }, nullopt, aliased);
		// Example code ends.
		string fileName = "pathexample09.png";
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path(fileName), image_data_format::png);
#else
		imgSfc.save(fileName, image_data_format::png);
#endif
	}

	void path_test_10() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ rgba_color::black() };
		brush foreBrush{ rgba_color::white() };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		auto scl = matrix_2d::init_scale({ 0.5, 1.0 });
		auto rot = matrix_2d::init_rotate(half_pi<double> / 2.0);
		auto trn = matrix_2d::init_translate({ 20.0, 20.0 });
		pb.matrix(scl);
		pb.new_path({ 40.0, 50.0 });
		pb.line({ 80.0, 50.0 });
		pb.new_path({ 40.0, 150.0 });
		pb.rel_line({ 40.0, 0.0 });
		pb.revert_matrix();
		pb.new_path({ 60.0, 150.0 });
		//pb.origin({ 60.0, 150.0 });
		pb.matrix(rot);
		pb.line({ 80.0, 150.0 });
		pb.rel_line({ 0.0, -20.0 });
		pb.revert_matrix();
		//pb.revert_origin();
		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 2.0 }, nullopt, aliased);
		// Example code ends.
		string fileName = "pathexample10.png";
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path(fileName), image_data_format::png);
#else
		imgSfc.save(fileName, image_data_format::png);
#endif
	}
//
//	void path_test_1X() {
//		auto imgSfc = make_image_surface(format::argb32, 300, 200);
//		brush backBrush{ rgba_color::black() };
//		brush foreBrush{ rgba_color::white() };
//		render_props aliased{ antialias::none };
//		path_builder<> pb{};
//		imgSfc.paint(backBrush);
//
//		// Example code goes here.
//
//		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 2.0 }, nullopt, aliased);
//
//		// Example code ends.
//		string fileName = "pathexample.png";
//#ifdef _Filesystem_support_test
//		imgSfc.save(experimental::filesystem::path(fileName), image_data_format::png);
//#else
//		imgSfc.save(fileName, image_data_format::png);
//#endif
//	}
}
