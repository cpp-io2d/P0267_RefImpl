#include "io2d.h"
#include "sample_draw.h"
#include <chrono>
#include <assert.h>
#include <sstream>
#include <ios>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;

template <class Traits>
basic_ostream<char, Traits>& operator<<(basic_ostream<char, Traits>& os, const vector_2d& v);

template <class Traits>
basic_ostream<char, Traits>& operator<<(basic_ostream<char, Traits>& os, const vector_2d& v) {
	fixed(os);
	os << "vector_2d { x: " << v.x() << " y: " << v.y() << " }";
	return os;
}

int main() {

	auto imgSfc = make_image_surface(format::argb32, 300, 200);
	auto bkgrndBrush = brush(bgra_color::black());
	auto frgrndBrush = brush(bgra_color::white());
	path_builder<> pb{};

	//{
	//	pb.clear();
	//	double width = 1.0;
	//	vector_2d rowStart{ 1.5, 1.5 };
	//	pb.new_path({ 1.5, 1.5 });
	//	stroke_props sp;
	//	sp.line_width(1.0);
	//}

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
	auto tempImgSfc = make_image_surface(format::argb32, 2000, 800);
	const double beginLocX = 20.0;
	double locY = 100.0;
	vector_2d location{ beginLocX, locY };
	vector_2d relcenter{ 60.0, 0.0 };
	const vector_2d locadd{ 200.0, 0.0 };
	double endAngle = 0.0;
	vector_2d scale{ 1.0, 1.0 };
	const double quarterPi = half_pi<double> / 2.0;
	const bool closePath = false;
	vector_2d ctrVal{};
	double angleVal{};
	stringstream outputDebugStr;

	pb.clear();
	// Test end angle 90 degree increments starting at 180.
	pb.new_path(location);
	scale.y(0.5);
	pb.rel_arc_clockwise(relcenter + vector_2d{ 0.0, 0.0 }, endAngle + two_pi<double>, scale);
	if (closePath) {
		pb.close_path();
	}
	scale.y(1.0);

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.rel_arc_clockwise(relcenter + vector_2d{ 0.0, 0.0 }, endAngle + half_pi<double>, scale);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.rel_arc_clockwise(relcenter + vector_2d{ 0.0, 0.0 }, endAngle + pi<double>, scale);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.rel_arc_clockwise(relcenter + vector_2d{ 0.0, 0.0 }, endAngle + three_pi_over_two<double>, scale);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.rel_arc_clockwise(relcenter + vector_2d{ 0.0, 0.0 }, endAngle + two_pi<double>, scale);
	pb.rel_line_to({ -40.0, 0.0 });
	if (closePath) {
		pb.close_path();
	}

	// Test end angle 90 degree intervals starting at 135
	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.rel_arc_clockwise(relcenter + vector_2d{ 0.0, 0.0 }, endAngle + half_pi<double> +quarterPi, scale);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.rel_arc_clockwise(relcenter + vector_2d{ 0.0, 0.0 }, endAngle + half_pi<double> -quarterPi, scale);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.rel_arc_clockwise(relcenter + vector_2d{ 0.0, 0.0 }, endAngle + three_pi_over_two<double> +quarterPi, scale);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.rel_arc_clockwise(relcenter + vector_2d{ 0.0, 0.0 }, endAngle + three_pi_over_two<double> -quarterPi, scale);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.rel_arc_clockwise(relcenter + vector_2d{ 0.0, 0.0 }, endAngle + two_pi<double> +quarterPi, scale);
	pb.rel_line_to({ -40.0, -40.0 });
	if (closePath) {
		pb.close_path();
	}

	// Test start angle 90 degree intervals starting at 180
	locY += 200;
	location.x(beginLocX);
	location.y(locY);
	//location += locadd;
	ctrVal = point_for_angle({}, pi<double>, relcenter.magnitude());
	location -= ctrVal;
	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
	angleVal = angle_for_point(ctrVal + location, location);
#ifdef _MSC_VER
	outputDebugStr.str(""s);
	outputDebugStr << "Center: " << ctrVal + location << " Current Point: " << location << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
	OutputDebugStringA(outputDebugStr.str().c_str());
#endif
	endAngle = angleVal;
	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
	if (closePath) {
		pb.close_path();
	}

	location.y(locY);
	location += locadd;
	ctrVal = point_for_angle({}, half_pi<double>, relcenter.magnitude());
	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
	angleVal = angle_for_point(ctrVal + location, location);
#ifdef _MSC_VER
	outputDebugStr.str(""s);
	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
	OutputDebugStringA(outputDebugStr.str().c_str());
#endif
	endAngle = angleVal;
	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
	if (closePath) {
		pb.close_path();
	}

	location.y(locY);
	location += locadd;
	ctrVal = point_for_angle({}, 0.0, relcenter.magnitude());
	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
	angleVal = angle_for_point(ctrVal + location, location);
#ifdef _MSC_VER
	outputDebugStr.str(""s);
	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
	OutputDebugStringA(outputDebugStr.str().c_str());
#endif
	endAngle = angleVal;
	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
	if (closePath) {
		pb.close_path();
	}

	location.y(locY);
	location += locadd;
	ctrVal = point_for_angle({}, three_pi_over_two<double>, relcenter.magnitude());
	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
	angleVal = angle_for_point(ctrVal + location, location);
#ifdef _MSC_VER
	outputDebugStr.str(""s);
	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
	OutputDebugStringA(outputDebugStr.str().c_str());
#endif
	endAngle = angleVal;
	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
	if (closePath) {
		pb.close_path();
	}

	// Test start angle 90 degree intervals starting at 135
	location.y(locY);
	location += locadd;
	ctrVal = point_for_angle({}, half_pi<double> -quarterPi, relcenter.magnitude());
	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
	//angleVal = angle_for_point(ctrVal + location, location);
	angleVal = half_pi<double> -quarterPi;
#ifdef _MSC_VER
	outputDebugStr.str(""s);
	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
	OutputDebugStringA(outputDebugStr.str().c_str());
#endif
	endAngle = angleVal;
	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
	if (closePath) {
		pb.close_path();
	}

	location.y(locY);
	location += locadd;
	ctrVal = point_for_angle({}, pi<double> -quarterPi, relcenter.magnitude());
	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
	//angleVal = angle_for_point(ctrVal + location, location);
	angleVal = pi<double> -quarterPi;
#ifdef _MSC_VER
	outputDebugStr.str(""s);
	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
	OutputDebugStringA(outputDebugStr.str().c_str());
#endif
	endAngle = angleVal;
	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
	if (closePath) {
		pb.close_path();
	}

	location.y(locY);
	location += locadd;
	ctrVal = point_for_angle({}, three_pi_over_two<double> -quarterPi, relcenter.magnitude());
	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
	//angleVal = angle_for_point(ctrVal + location, location);
	angleVal = three_pi_over_two<double> -quarterPi;
#ifdef _MSC_VER
	outputDebugStr.str(""s);
	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
	OutputDebugStringA(outputDebugStr.str().c_str());
#endif
	endAngle = angleVal;
	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
	if (closePath) {
		pb.close_path();
	}

	location.y(locY);
	location += locadd;
	ctrVal = point_for_angle({}, two_pi<double> -quarterPi, relcenter.magnitude());
	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
	//angleVal = angle_for_point(ctrVal + location, location);
	angleVal = two_pi<double> -quarterPi;
#ifdef _MSC_VER
	outputDebugStr.str(""s);
	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
	OutputDebugStringA(outputDebugStr.str().c_str());
#endif
	endAngle = angleVal;
	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
	if (closePath) {
		pb.close_path();
	}

	//// Template: copy - don't cut and paste
	//location += locadd;
	//pb.new_path(location + vector_2d{ 0.0, 0.0 });
	//pb.rel_arc_clockwise(relcenter + vector_2d{ 0.0, 0.0 }, endAngle, scale);
	//if (closePath) {
	//	pb.close_path();
	//}

	//pb.new_path({ 120.0, 100.0 });
	//pb.rel_arc_clockwise({ 40.0, 0.0 }, three_pi_over_two<double> + half_pi<double> / 2.0, { 1.0, 2.0 });
	//pb.close_path();

	////pb.rel_line_to({ 0.0, 50.0 });
	////pb.line_to({ 140.0, 120.0 });
	////pb.close_path();

	//pb.new_path({ 40.0, 120.0 });
	//pb.arc_counterclockwise({ 80.0, 120.0 }, 0.0); // half_pi<double> / 2.0);
	//pb.close_path();
	//pb.rel_new_path({ 100.0, 0.0 });
	//pb.rel_arc_counterclockwise({ 40.0, 0.0 }, 0.0);// , { 1.0, 2.0 });
	//pb.close_path();

writefileandexit:
	tempImgSfc.paint(bkgrndBrush);
	tempImgSfc.stroke(frgrndBrush, pb, nullopt, stroke_props{ 10.0 });
#ifdef _Filesystem_support_test
	tempImgSfc.save(experimental::filesystem::path("arctesting01.png"), image_data_format::png);
#else
	tempImgSfc.save("arctesting01.png"s, image_data_format::png);
#endif
	return 0;
	//auto ds = make_display_surface(1280, 720, format::argb32, scaling::letterbox, refresh_rate::as_fast_as_possible, 30.0);
	//sample_draw sd;
	//ds.draw_callback(sd);
	//return ds.begin_show();
}
