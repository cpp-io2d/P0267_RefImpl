#include "io2d.h"
#include "sample_draw.h"
#include <chrono>
#include <assert.h>
#include <sstream>
#include <ios>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;

vector_2d testArcClockwiseEndAngle(path_builder<>& pb, vector_2d location, bool closePath = false, vector_2d scale = vector_2d{ 1.0, 1.0 }, const vector_2d locadd = vector_2d{ 200.0, 0.0 });
vector_2d testArcCounterclockwiseEndAngle(path_builder<>& pb, vector_2d location, bool closePath = false, vector_2d scale = vector_2d{ 1.0, 1.0 }, const vector_2d locadd = vector_2d{ 200.0, 0.0 });

int main() {
	auto ds = make_display_surface(1280, 720, format::argb32, scaling::letterbox, refresh_rate::as_fast_as_possible, 30.0);
	sample_draw sd;
	ds.draw_callback(sd);
	ds.begin_show();
	ds.begin_show();
	return 0;
	//	auto imgSfc = make_image_surface(format::argb32, 300, 200);
	//	auto bkgrndBrush = brush(bgra_color::black());
	//	auto frgrndBrush = brush(bgra_color::white());
	//	path_builder<> pb{};
	//
	//	pb.clear();
	//	pb.new_path({ 80.0, 20.0 });
	//	pb.line_to({ 220.0, 20.0 });
	//	pb.rel_line_to({ 60.0, 160.0 });
	//	pb.rel_line_to({ -260.0, 0.0 });
	//	pb.close_path();
	//
	//	imgSfc.paint(bkgrndBrush);
	//	imgSfc.stroke(frgrndBrush, pb);
	//#ifdef _Filesystem_support_test
	//	imgSfc.save(experimental::filesystem::path("pathexample01.png"), image_data_format::png);
	//#else
	//	imgSfc.save("pathexample01.png"s, image_data_format::png);
	//#endif
	//	pb.clear();
	//	pb.new_path({ 20.0, 20.0 });
	//	pb.rel_line_to({ 100.0, 0.0 });
	//	pb.rel_line_to({ 0.0, 160.0 });
	//	pb.rel_line_to({ -100.0, 0.0 });
	//	pb.rel_line_to({ 0.0, -160.0 });
	//
	//	pb.new_path({ 180.0, 20.0 });
	//	pb.rel_line_to({ 100.0, 0.0 });
	//	pb.rel_line_to({ 0.0, 160.0 });
	//	pb.rel_line_to({ -100.0, 0.0 });
	//	pb.close_path();
	//
	//	imgSfc.paint(bkgrndBrush);
	//	imgSfc.stroke(frgrndBrush, pb, nullopt, stroke_props{ 10.0 });
	//#ifdef _Filesystem_support_test
	//	imgSfc.save(experimental::filesystem::path("pathexample02.png"), image_data_format::png);
	//#else
	//	imgSfc.save("pathexample02.png"s, image_data_format::png);
	//#endif


	//
	//	auto tempImgSfc = make_image_surface(format::argb32, 2000, 1200);
	//	const double beginLocX = 100.0;
	//	double locY = 140.0;
	//	vector_2d location{ beginLocX, locY };
	//	pb.clear();
	//	pb.change_matrix(matrix_2d::init_translate({ 400.0, 400.0 }).rotate(to_radians(-45)).scale({ 0.5, 0.5 }));
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
	//	tempImgSfc.save(experimental::filesystem::path("arctesting01.png"), image_data_format::png);
	//#else
	//	tempImgSfc.save("arctesting01.png"s, image_data_format::png);
	//#endif
	//	return 0;
}

vector_2d testArcClockwiseEndAngle(path_builder<>& pb, vector_2d location, bool closePath, vector_2d rad, const vector_2d locadd) {
	const double quarterPi = half_pi<double> / 2.0;

	vector_2d ctrVal{};

	// Test end angle 90 degree increments starting at 180.
	pb.new_path(location);
	const vector_2d initialRelLine{ 40.0, 0.0 };
	pb.rel_line_to(initialRelLine);
	location += initialRelLine;
	pb.arc(rad, -pi<double>, pi<double>);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, -pi<double>, half_pi<double>);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, -pi<double>, 0.0);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, -pi<double>, three_pi_over_two<double>);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, -two_pi<double>, pi<double>);
	pb.rel_line_to({ -40.0, 0.0 });
	if (closePath) {
		pb.close_path();
	}

	// Test end angle 90 degree intervals starting at 135
	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, -pi<double>, pi<double> -quarterPi);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, -pi<double>, quarterPi);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, -pi<double>, -quarterPi);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, -pi<double>, pi<double> +quarterPi);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, -two_pi<double>, three_pi_over_two<double> +quarterPi);
	pb.rel_line_to({ 40.0, 40.0 });
	if (closePath) {
		pb.close_path();
	}

	return location + locadd;
}

vector_2d testArcCounterclockwiseEndAngle(path_builder<>& pb, vector_2d location, bool closePath, vector_2d rad, const vector_2d locadd) {
	const double quarterPi = half_pi<double> / 2.0;

	// Test end angle 90 degree increments starting at 180.
	pb.new_path(location);
	const vector_2d initialRelLine{ 40.0, 0.0 };
	pb.rel_line_to(initialRelLine);
	location += initialRelLine;
	pb.arc(rad, pi<double>, pi<double>);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, pi<double>, half_pi<double>);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, pi<double>, 0.0);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, pi<double>, three_pi_over_two<double>);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, two_pi<double>, pi<double>);
	pb.rel_line_to({ -40.0, 0.0 });
	if (closePath) {
		pb.close_path();
	}

	// Test end angle 90 degree intervals starting at 135
	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, pi<double>, pi<double> -quarterPi);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, pi<double>, quarterPi);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, pi<double>, -quarterPi);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, pi<double>, pi<double> +quarterPi);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, two_pi<double>, three_pi_over_two<double> +quarterPi);
	pb.rel_line_to({ 40.0, 40.0 });// *scale);
	if (closePath) {
		pb.close_path();
	}

	return location + locadd;
}
