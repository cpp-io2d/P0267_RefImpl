#include "io2d.h"
#include "sample_draw.h"
#include <chrono>
#include <assert.h>
#include <sstream>
#include <ios>
#include <thread>
#include <mutex>
#include "path_examples.h"
#include "brush_examples.h"
#include <experimental/filesystem>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;
using namespace path_test;
using namespace brush_test;

point_2d testArcClockwiseEndAngle(path_builder& pb, point_2d location, bool closePath = false, point_2d scale = point_2d{ 1.0, 1.0 }, const point_2d locadd = point_2d{ 200.0, 0.0 });
point_2d testArcCounterclockwiseEndAngle(path_builder& pb, point_2d location, bool closePath = false, point_2d scale = point_2d{ 1.0, 1.0 }, const point_2d locadd = point_2d{ 200.0, 0.0 });

void make_path_examples();
void make_path_examples() {
	path_test_1();
	path_test_2();
	path_test_3();
	path_test_4();
	path_test_5();
	path_test_6();
	path_test_7();
	path_test_8();
	path_test_9();
	path_test_10();
}

void make_brush_examples();
void make_brush_examples() {
	//solid_color_test_01();
}
int main() {
	//auto pt = point_2d{ 80.0, 100.0 };
	//figure_items::arc testArc{};
	//point_2d ctr, endPt;
	//testArc = figure_items::arc({ 30.0, 30.0 }, half_pi<float>, half_pi<float>);
	//ctr = testArc.center(pt);
	//endPt = testArc.end_pt(pt);
	//auto rot = matrix_2d::create_rotate(half_pi<float> / 2.0);
	//pt.x(pt.x() + 50.0);
	//testArc = figure_items::arc({ 30.0, 30.0 }, half_pi<float>, half_pi<float>);
	//ctr = testArc.center(pt, rot);
	//endPt = testArc.end_pt(pt, rot);

	//rot = matrix_2d::create_rotate(half_pi<float>);
	//pt.x(pt.x() + 50.0);
	//testArc = figure_items::arc({ 30.0, 30.0 }, half_pi<float>, half_pi<float>);
	//ctr = testArc.center(pt, rot);
	//endPt = testArc.end_pt(pt, rot);

	//make_path_examples();
	//make_brush_examples();
	const bool useThreads = true;
	if (useThreads) {
		// Note: We're using a mutex here because you can't rely in thread safety when dealing with the same file. (e.g. In the case of this implementation, GraphicsMagick is NOT thread-safe for JPEG files.)
		::std::mutex jpegMutex;

		::std::thread outputOne([&jpegMutex]() {
			output_surface os(1280, 720, format::argb32, scaling::letterbox, refresh_style::as_fast_as_possible, 30.0);
			image_surface imgSfc = [&jpegMutex]() -> image_surface {
				::std::lock_guard<::std::mutex> lg(jpegMutex);
				return image_surface(std::experimental::filesystem::path("2017_03_05.jpg"s), image_file_format::jpeg, format::rgb30);
			}();

			imgSfc.save(::std::experimental::filesystem::path("2017_03_05_copy_rgb30.jpg"s), image_file_format::jpeg);
			brush imgSfcBrush(move(imgSfc));
			os.draw_callback([&](output_surface& outSfc) {
				outSfc.clear();
				outSfc.paint(imgSfcBrush);
			});
			os.begin_show();
		});

		::std::thread outputTwo([&jpegMutex]() {
			output_surface os(1280, 720, format::argb32, scaling::letterbox, refresh_style::as_fast_as_possible, 30.0);
			image_surface imgSfc = [&jpegMutex]() -> image_surface {
				::std::lock_guard<::std::mutex> lg(jpegMutex);
				return image_surface(std::experimental::filesystem::path("2017_03_05.jpg"s), image_file_format::jpeg, format::rgb16_565);
			}();

			imgSfc.save(::std::experimental::filesystem::path("2017_03_05_copy_rgb16_565.jpg"s), image_file_format::jpeg);
			brush imgSfcBrush(move(imgSfc));
			os.draw_callback([&](output_surface& outSfc) {
				outSfc.clear();
				outSfc.paint(imgSfcBrush);
			});
			os.begin_show();
		});

		::std::thread outputThree([]() {
			output_surface os(1280, 720, format::argb32, scaling::letterbox, refresh_style::as_fast_as_possible, 30.0);
			image_surface imgSfc(std::experimental::filesystem::path("2016_06_22.png"s), image_file_format::png, format::argb32);
			//imgSfc.save(::std::experimental::filesystem::path("2016_06_22_copy_argb32.jpg"s), image_file_format::jpeg);
			imgSfc.save(::std::experimental::filesystem::path("2016_06_22_copy_argb32.bmp"s), default_graphics_surfaces::additional_image_file_formats::bmp);
			brush imgSfcBrush(move(imgSfc));
			os.draw_callback([&](output_surface& outSfc) {
				outSfc.clear();
				outSfc.paint(imgSfcBrush);
			});
			os.begin_show();
		});

		::std::thread outputFour([]() {
			output_surface os(1280, 720, format::argb32, scaling::letterbox, refresh_style::as_fast_as_possible, 30.0);
			image_surface imgSfc(std::experimental::filesystem::path("alpha8.png"s), image_file_format::png, format::a8);
			imgSfc.save(::std::experimental::filesystem::path("alpha8_copy_a8.png"s), image_file_format::png);
			brush imgSfcBrush(move(imgSfc));
			brush redBrush(rgba_color::red);
			os.draw_callback([&](output_surface& outSfc) {
				outSfc.clear();
				outSfc.mask(redBrush, imgSfcBrush);
			});
			os.begin_show();
		});

		::std::thread outputFive([]() {
			output_surface os(1280, 720, format::argb32, scaling::letterbox, refresh_style::as_fast_as_possible, 30.0);
			image_surface imgSfc(std::experimental::filesystem::path("2017_07_12.tiff"s), image_file_format::tiff, format::rgb24);
			imgSfc.save(::std::experimental::filesystem::path("2017_07_12_copy_rgb24.tiff"s), image_file_format::tiff);
			brush imgSfcBrush(move(imgSfc));
			os.draw_callback([&](output_surface& outSfc) {
				outSfc.clear();
				outSfc.paint(imgSfcBrush);
			});
			os.begin_show();
		});

		outputOne.join();
		outputTwo.join();
		outputThree.join();
		outputFour.join();
		outputFive.join();
	}
	else {
		output_surface os(1280, 720, format::argb32, scaling::letterbox, refresh_style::as_fast_as_possible, 30.0);
		image_surface imgSfc(std::experimental::filesystem::path("2016_06_22.png"s), image_file_format::png, format::argb32);
		//imgSfc.save(::std::experimental::filesystem::path("2016_06_22_copy_argb32.jpg"s), image_file_format::jpeg);
		imgSfc.save(::std::experimental::filesystem::path("2016_06_22_copy_argb32.bmp"s), default_graphics_surfaces::additional_image_file_formats::bmp);
		brush imgSfcBrush(move(imgSfc));
		os.draw_callback([&](output_surface& outSfc) {
			outSfc.clear();
			outSfc.paint(imgSfcBrush);
		});
		os.begin_show();
	}
	return 0;
	//	auto imgSfc = make_image_surface(format::argb32, 300, 200);
	//	auto bkgrndBrush = brush(rgba_color::black());
	//	auto frgrndBrush = brush(rgba_color::white());
	//	path_builder pb{};
	//
	//	pb.clear();
	//	pb.new_figure({ 80.0, 20.0 });
	//	pb.line({ 220.0, 20.0 });
	//	pb.rel_line({ 60.0, 160.0 });
	//	pb.rel_line({ -260.0, 0.0 });
	//	pb.close_figure();
	//
	//	imgSfc.paint(bkgrndBrush);
	//	imgSfc.stroke(frgrndBrush, pb);
	//#ifdef _Filesystem_support_test
	//	imgSfc.save(experimental::filesystem::path("pathexample01.png"), image_file_format::png);
	//#else
	//	imgSfc.save("pathexample01.png"s, image_file_format::png);
	//#endif
	//	pb.clear();
	//	pb.new_figure({ 20.0, 20.0 });
	//	pb.rel_line({ 100.0, 0.0 });
	//	pb.rel_line({ 0.0, 160.0 });
	//	pb.rel_line({ -100.0, 0.0 });
	//	pb.rel_line({ 0.0, -160.0 });
	//
	//	pb.new_figure({ 180.0, 20.0 });
	//	pb.rel_line({ 100.0, 0.0 });
	//	pb.rel_line({ 0.0, 160.0 });
	//	pb.rel_line({ -100.0, 0.0 });
	//	pb.close_figure();
	//
	//	imgSfc.paint(bkgrndBrush);
	//	imgSfc.stroke(frgrndBrush, pb, nullopt, stroke_props{ 10.0 });
	//#ifdef _Filesystem_support_test
	//	imgSfc.save(experimental::filesystem::path("pathexample02.png"), image_file_format::png);
	//#else
	//	imgSfc.save("pathexample02.png"s, image_file_format::png);
	//#endif


	//
	//	auto tempImgSfc = make_image_surface(format::argb32, 2000, 1200);
	//	const float beginLocX = 100.0;
	//	float locY = 140.0;
	//	point_2d location{ beginLocX, locY };
	//	pb.clear();
	//	pb.abs_matrix(matrix_2d::create_translate({ 400.0, 400.0 }).rotate(to_radians(-45)).scale({ 0.5, 0.5 }));
	//	location = testArcClockwiseEndAngle(pb, location, false, { 60.0, 60.0 });
	//
	//	locY += 200;
	//	location.x(beginLocX);
	//	location.y(locY);
	//
	//	location = testArcClockwiseEndAngle(pb, location, false, { 60.0, 30.0 });
	//
	//	locY += 200;
	//	location.x(beginLocX);
	//	location.y(locY);
	//
	//	location = testArcClockwiseEndAngle(pb, location, false, { 30.0, 60.0 });
	//
	//	locY += 200;
	//	location.x(beginLocX);
	//	location.y(locY);
	//
	//	////// COUNTERCLOCKWISE
	//
	//	location = testArcCounterclockwiseEndAngle(pb, location, false, { 60.0, 60.0 });
	//
	//	locY += 200;
	//	location.x(beginLocX);
	//	location.y(locY);
	//
	//	location = testArcCounterclockwiseEndAngle(pb, location, false, { 60.0, 30.0 });
	//
	//	locY += 200;
	//	location.x(beginLocX);
	//	location.y(locY);
	//
	//	location = testArcCounterclockwiseEndAngle(pb, location, false, { 30.0, 60.0 });
	//
	//	locY += 200;
	//	location.x(beginLocX);
	//	location.y(locY);
	//
	//	tempImgSfc.paint(bkgrndBrush);
	//	tempImgSfc.stroke(frgrndBrush, pb, nullopt, stroke_props{ 10.0 });
	//#ifdef _Filesystem_support_test
	//	tempImgSfc.save(experimental::filesystem::path("arctesting01.png"), image_file_format::png);
	//#else
	//	tempImgSfc.save("arctesting01.png"s, image_file_format::png);
	//#endif
	//	return 0;
}

point_2d testArcClockwiseEndAngle(path_builder& pb, point_2d location, bool closePath, point_2d rad, const point_2d locadd) {
	const float quarterPi = half_pi<float> / 2.0;

	point_2d ctrVal{};

	// Test end angle 90 degree increments starting at 180.
	pb.new_figure(location);
	const point_2d initialRelLine{ 40.0, 0.0 };
	pb.rel_line(initialRelLine);
	location += initialRelLine;
	pb.arc(rad, -pi<float>, pi<float>);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, -pi<float>, half_pi<float>);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, -pi<float>, 0.0);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, -pi<float>, three_pi_over_two<float>);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, -two_pi<float>, pi<float>);
	pb.rel_line({ -40.0, 0.0 });
	if (closePath) {
		pb.close_figure();
	}

	// Test end angle 90 degree intervals starting at 135
	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, -pi<float>, pi<float> -quarterPi);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, -pi<float>, quarterPi);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, -pi<float>, -quarterPi);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, -pi<float>, pi<float> +quarterPi);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, -two_pi<float>, three_pi_over_two<float> +quarterPi);
	pb.rel_line({ 40.0, 40.0 });
	if (closePath) {
		pb.close_figure();
	}

	return location + locadd;
}

point_2d testArcCounterclockwiseEndAngle(path_builder& pb, point_2d location, bool closePath, point_2d rad, const point_2d locadd) {
	const float quarterPi = half_pi<float> / 2.0;

	// Test end angle 90 degree increments starting at 180.
	pb.new_figure(location);
	const point_2d initialRelLine{ 40.0, 0.0 };
	pb.rel_line(initialRelLine);
	location += initialRelLine;
	pb.arc(rad, pi<float>, pi<float>);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, pi<float>, half_pi<float>);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, pi<float>, 0.0);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, pi<float>, three_pi_over_two<float>);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, two_pi<float>, pi<float>);
	pb.rel_line({ -40.0, 0.0 });
	if (closePath) {
		pb.close_figure();
	}

	// Test end angle 90 degree intervals starting at 135
	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, pi<float>, pi<float> -quarterPi);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, pi<float>, quarterPi);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, pi<float>, -quarterPi);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, pi<float>, pi<float> +quarterPi);
	if (closePath) {
		pb.close_figure();
	}

	location += locadd;
	pb.new_figure(location + point_2d{ 0.0, 0.0 });
	pb.arc(rad, two_pi<float>, three_pi_over_two<float> +quarterPi);
	pb.rel_line({ 40.0, 40.0 });// *scale);
	if (closePath) {
		pb.close_figure();
	}

	return location + locadd;
}
