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
		brush backBrush{ rgba_color::black };
		brush foreBrush{ rgba_color::white };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		pb.new_path({ 80.0F, 20.0F });
		pb.line({ 220.0F, 20.0F });
		pb.rel_line({ 60.0F, 160.0F });
		pb.rel_line({ -260.0F, 0.0F });
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
		brush backBrush{ rgba_color::black };
		brush foreBrush{ rgba_color::white };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		pb.new_path({ 20.0F, 20.0F });
		pb.rel_line({ 100.0F, 0.0F });
		pb.rel_line({ 0.0F, 160.0F });
		pb.rel_line({ -100.0F, 0.0F });
		pb.rel_line({ 0.0F, -160.0F });

		pb.new_path({ 180.0F, 20.0F });
		pb.rel_line({ 100.0F, 0.0F });
		pb.rel_line({ 0.0F, 160.0F });
		pb.rel_line({ -100.0F, 0.0F });
		pb.close_path();

		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 10.0F }, nullopt, aliased);

		// Example code ends.
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path("pathexample02.png"), image_data_format::png);
#else
		imgSfc.save("pathexample02.png"s, image_data_format::png);
#endif
	}

	void path_test_3() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ rgba_color::black };
		brush foreBrush{ rgba_color::white };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		pb.new_path({ 20.0F, 20.0F });
		pb.rel_quadratic_curve({ 60.0F, 120.0F }, { 60.0F, -120.0F });
		pb.rel_new_path({ 20.0F, 0.0F });
		pb.rel_quadratic_curve({ 60.0F, 120.0F }, { 60.0F, -120.0F });
		pb.close_path();
		pb.new_path({ 20.0F, 150.0F });
		pb.rel_cubic_curve({ 40.0F, -120.0F }, { 40.0F, 120.0F * 2.0F }, { 40.0F, -120.0F });
		pb.rel_new_path({ 20.0F, 0.0F });
		pb.rel_cubic_curve({ 40.0F, -120.0F }, { 40.0F, 120.0F * 2.0F }, { 40.0F, -120.0F });
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
		brush backBrush{ rgba_color::black };
		brush foreBrush{ rgba_color::white };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		const matrix_2d sclMtx = matrix_2d::init_scale({ 0.9F, 1.1F });// .rotate(half_pi<float>);// * matrix_2d::init_rotate(half_pi<float>);
		const point_2d rad{ 50.0F, 50.0F };
		//auto pt = sclMtx.inverse().transform_pt({ 85.0F, 100.0F }) +
		//	point_for_angle(half_pi<float> / 2.0F, rad);
		//auto pt = sclMtx.inverse().transform_pt({ 85.0F, 100.0F }) +
		//	point_for_angle(half_pi<float> / 2.0F, 50.0F);
		//auto pt = point_2d{ 85.0F, 100.0F } + 
		//	point_for_angle(half_pi<float> / 2.0F, rad);
		auto pt = arc_start({ 85.0F, 100.0F }, half_pi<float> / 2.0F, { 50.0F, 50.0F }, sclMtx);
		pb.matrix(sclMtx);
		pb.new_path(pt);
		//pb.matrix(sclMtx);
		pb.arc({ 50.0F, 50.0F }, three_pi_over_two<float>, half_pi<float> / 2.0F);
		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 10.0F });// , nullopt, aliased);
		pb.clear();
		pb.new_path({ 130.0F, 105.0F });
		pb.rel_line({ 0.0F, -10.0F });
		pb.rel_line({ 25.0F, 0.0F });
		pb.rel_line({ 0.0F, -25.0F });
		pb.rel_line({ 10.0F, 0.0F });
		pb.rel_line({ 0.0F, 25.0F });
		pb.rel_line({ 25.0F, 0.0F });
		pb.rel_line({ 0.0F, 10.0F });
		pb.rel_line({ -25.0F, 0.0F });
		pb.rel_line({ 0.0F, 25.0F });
		pb.rel_line({ -10.0F, 0.0F });
		pb.rel_line({ 0.0F, -25.0F });
		pb.close_path();
		imgSfc.fill(foreBrush, pb);
		pb.insert(pb.begin(), path_data::abs_matrix(matrix_2d::init_translate({ 80.0F, 0.0F })));
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
		brush backBrush{ rgba_color::black };
		brush foreBrush{ rgba_color::white };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		auto scl = matrix_2d::init_scale({ 0.5F, 1.0F });
		auto rot = matrix_2d::init_rotate(half_pi<float>);
		auto trn = matrix_2d::init_translate({ 20.0F, 20.0F });
		pb.new_path({ 10.0F, 150.0F });
		pb.quadratic_curve({ 30.0F, 120.0F }, { 50.0F, 150.0F });

		//pb.new_path({ 110.0F, 150.0F });
		//pb.matrix(rot);
		//pb.quadratic_curve({ 130.0F, 120.0F }, { 150.0F, 150.0F });
		//pb.revert_matrix();

		pb.new_path({ 110.0F, 150.0F });
		pb.matrix(rot);
		pb.quadratic_curve({ 130.0F, 120.0F }, { 150.0F, 150.0F });
		pb.revert_matrix();

		pb.new_path({ 170.0F, 150.0F });
		pb.matrix(rot * scl);
		pb.rel_quadratic_curve({ 20.0F, -30.0F }, { 20.0F, 30.0F });
		pb.revert_matrix();

		pb.new_path({ 230.0F, 150.0F });
		pb.matrix(scl * rot);
		pb.rel_quadratic_curve({ 20.0F, -30.0F }, { 20.0F, 30.0F });
		pb.revert_matrix();

		pb.new_path({ 290.0F, 150.0F });
		pb.matrix(rot * trn);
		pb.rel_quadratic_curve({ 20.0F, -30.0F }, { 20.0F, 30.0F });
		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 2.0F }, nullopt, aliased);

		// Example code ends.
		string fileName = "pathexample05.png";
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path(fileName), image_data_format::png);
#else
		imgSfc.save(fileName, image_data_format::png);
#endif
	}

	void path_test_6() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ rgba_color::black };
		brush foreBrush{ rgba_color::white };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);
		// Example code goes here.
		auto pt = point_2d{ 80.0F, 100.0F };
		pb.new_path(pt);
		pb.arc({ 30.0F, 30.0F }, half_pi<float>, half_pi<float>);

		auto rot = matrix_2d::init_rotate(half_pi<float> / 2.0F);
		pt.x(pt.x() + 50.0F);
		pb.new_path(pt);
		pb.matrix(rot);
		pb.arc({ 30.0F, 30.0F }, half_pi<float>, half_pi<float>);

		pb.revert_matrix();
		rot = matrix_2d::init_rotate(half_pi<float>);
		pt.x(pt.x() + 50.0F);
		pb.new_path(pt);
		pb.matrix(rot.translate({ 20.0F, 10.0F }));
		pb.arc({ 30.0F, 30.0F }, half_pi<float>, half_pi<float>);

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
		brush backBrush{ rgba_color::black };
		brush foreBrush{ rgba_color::white };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		brush blueBrush{ rgba_color::blue };
		stroke_props ten{ 10.0F };
		pb.new_path({ 30.0F, 30.0F });
		pb.rel_line({ 105.0F, 0.0F });
		pb.rel_line({ 0.0F, 140.0F });
		pb.rel_line({ -105.0F, 0.0F });
		pb.close_path();
		imgSfc.stroke(foreBrush, pb, nullopt, ten);
		imgSfc.fill(blueBrush, pb);
		pb.insert(pb.begin(), path_data::abs_matrix(matrix_2d::init_translate({ 135.0F, 0.0F })));
		//pb.insert(pb.begin() + 2, path_data::revert_matrix());
		imgSfc.fill(blueBrush, pb);
		imgSfc.stroke(foreBrush, pb, nullopt, ten);
		// Example code ends.
#ifdef _Filesystem_support_test
		imgSfc.save(experimental::filesystem::path("pathexample07.png"), image_data_format::png);
#else
		imgSfc.save("pathexample07.png"s, image_data_format::png);
#endif
	}

	void path_test_8() {
		auto imgSfc = make_image_surface(format::argb32, 300, 200);
		brush backBrush{ rgba_color::black };
		brush foreBrush{ rgba_color::white };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		auto scl = matrix_2d::init_scale({ 0.5F, 1.0F });
		auto rot = matrix_2d::init_rotate(half_pi<float> / 2.0F);
		auto trn = matrix_2d::init_translate({ 20.0F, 20.0F });
		pb.matrix(scl);
		pb.new_path({ 40.0F, 50.0F });
		pb.line({ 80.0F, 50.0F });
		pb.new_path({ 40.0F, 150.0F });
		pb.rel_line({ 40.0F, 0.0F });
		pb.revert_matrix();
		pb.new_path({ 60.0F, 150.0F });
		//pb.origin({ 60.0F, 150.0F });
		pb.matrix(rot);
		pb.line({ 80.0F, 150.0F });
		pb.rel_line({ 0.0F, -20.0F });
		pb.revert_matrix();
		//pb.revert_origin();
		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 2.0F }, nullopt, aliased);
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
		brush backBrush{ rgba_color::black };
		brush foreBrush{ rgba_color::white };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		auto scl = matrix_2d::init_scale({ 0.5F, 1.0F });
		auto rot = matrix_2d::init_rotate(half_pi<float> / 2.0F);
		auto trn = matrix_2d::init_translate({ 20.0F, 20.0F });
		pb.matrix(scl);
		pb.new_path({ 40.0F, 50.0F });
		pb.line({ 80.0F, 50.0F });
		pb.new_path({ 40.0F, 150.0F });
		pb.rel_line({ 40.0F, 0.0F });
		pb.revert_matrix();
		pb.new_path({ 60.0F, 150.0F });
		//pb.origin({ 60.0F, 150.0F });
		pb.matrix(rot);
		pb.line({ 80.0F, 150.0F });
		pb.rel_line({ 0.0F, -20.0F });
		pb.revert_matrix();
		//pb.revert_origin();
		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 2.0F }, nullopt, aliased);
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
		brush backBrush{ rgba_color::black };
		brush foreBrush{ rgba_color::white };
		render_props aliased{ antialias::none };
		path_builder<> pb{};
		imgSfc.paint(backBrush);

		// Example code goes here.
		auto scl = matrix_2d::init_scale({ 0.5F, 1.0F });
		auto rot = matrix_2d::init_rotate(half_pi<float> / 2.0F);
		auto trn = matrix_2d::init_translate({ 20.0F, 20.0F });
		pb.matrix(scl);
		pb.new_path({ 40.0F, 50.0F });
		pb.line({ 80.0F, 50.0F });
		pb.new_path({ 40.0F, 150.0F });
		pb.rel_line({ 40.0F, 0.0F });
		pb.revert_matrix();
		pb.new_path({ 60.0F, 150.0F });
		//pb.origin({ 60.0F, 150.0F });
		pb.matrix(rot);
		pb.line({ 80.0F, 150.0F });
		pb.rel_line({ 0.0F, -20.0F });
		pb.revert_matrix();
		//pb.revert_origin();
		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 2.0F }, nullopt, aliased);
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
//		brush backBrush{ rgba_color::black };
//		brush foreBrush{ rgba_color::white };
//		render_props aliased{ antialias::none };
//		path_builder<> pb{};
//		imgSfc.paint(backBrush);
//
//		// Example code goes here.
//
//		imgSfc.stroke(foreBrush, pb, nullopt, stroke_props{ 2.0F }, nullopt, aliased);
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
