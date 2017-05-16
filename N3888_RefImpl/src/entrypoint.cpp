#include "io2d.h"
#include "sample_draw.h"
#include <chrono>
#include <assert.h>
#include <sstream>
#include <ios>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;

//#define DEBUG_ARC_TESTS

//template <class Traits>
//basic_ostream<char, Traits>& operator<<(basic_ostream<char, Traits>& os, const vector_2d& v);
//
//template <class Traits>
//basic_ostream<char, Traits>& operator<<(basic_ostream<char, Traits>& os, const vector_2d& v) {
//	fixed(os);
//	os << "vector_2d { x: " << v.x() << " y: " << v.y() << " }";
//	return os;
//}

vector_2d testArcClockwiseEndAngle(path_builder<>& pb, vector_2d location, bool closePath = false, vector_2d scale = vector_2d{ 1.0, 1.0 }, const vector_2d locadd = vector_2d{ 200.0, 0.0 });
vector_2d testArcClockwiseStartAngle(path_builder<>& pb, vector_2d location, bool closePath = false, vector_2d scale = vector_2d{ 1.0, 1.0 }, const vector_2d locadd = vector_2d{ 200.0, 0.0 });
vector_2d testArcCounterclockwiseEndAngle(path_builder<>& pb, vector_2d location, bool closePath = false, vector_2d scale = vector_2d{ 1.0, 1.0 }, const vector_2d locadd = vector_2d{ 200.0, 0.0 });
vector_2d testArcCounterclockwiseStartAngle(path_builder<>& pb, vector_2d location, bool closePath = false, vector_2d scale = vector_2d{ 1.0, 1.0 }, const vector_2d locadd = vector_2d{ 200.0, 0.0 });

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
	//const auto testRotAng = half_pi<double>;
	//auto testM = matrix_2d::init_rotate(testRotAng);
	//const vector_2d vecRotTestInit{ 60.0, 0.0 };
	//auto vecRotTest = testM.transform_point(vecRotTestInit);
	//OutputDebugStringA(string("Test Rot Angle: ").append(to_string(testRotAng)).append("\nRot Test X:   ").append(to_string(vecRotTestInit.x())).append("\nRot Test Y:   ").append(to_string(vecRotTestInit.y())).append("\ntestM rot X:  ").append(to_string(vecRotTest.x())).append("\ntestM rot Y:  ").append(to_string(vecRotTest.y())).c_str());
	//auto rotCwFn = [](const vector_2d& pt, double a) -> vector_2d {
	//	auto result = vector_2d{ pt.x() * cos(a) + pt.y() * sin(a),
	//		-(pt.x() * -(sin(a)) + pt.y() * cos(a)) };
	//	if (abs(result.x()) < numeric_limits<double>::epsilon() * 100.0) {
	//		result.x(result.x() < 0 ? -0.0 : 0.0);
	//	}
	//	if (abs(result.y()) < numeric_limits<double>::epsilon() * 100.0) {
	//		result.y(result.y() < 0 ? -0.0 : 0.0);
	//	}
	//	return result;
	//};
	//vecRotTest = rotCwFn(vecRotTestInit, half_pi<double>);
	//OutputDebugStringA(string("\nrotCwFn rot X: ").append(to_string(vecRotTest.x())).append("\nrotCwFn rot Y: ").append(to_string(vecRotTest.y())).append("\n\n").c_str());

	auto tempImgSfc = make_image_surface(format::argb32, 2000, 1200);
	const double beginLocX = 100.0;
	double locY = 140.0;
	vector_2d location{ beginLocX, locY };
	//vector_2d relcenter{ 60.0, 0.0 };
	//const vector_2d locadd{ 200.0, 0.0 };
	////double endAngle = 0.0;
	//vector_2d scale{ 1.0, 1.0 };
	//const double quarterPi = half_pi<double> / 2.0;
	//const bool closePath = false;
	//vector_2d ctrVal{};
	////double angleVal{};
	//stringstream outputDebugStr;
	//auto testRot = matrix_2d::init_rotate(to_radians(-45));
	//auto testRotPt = testRot.transform_point({ 60.0, 0.0 });
	pb.clear();
	//pb.transform_matrix(matrix_2d::init_scale({ 0.5, 0.5 }).translate({ 400.0, 400.0 }).rotate(to_radians(-45)));
	pb.transform_matrix(matrix_2d::init_translate({ 400.0, 400.0 }).rotate(to_radians(-45)).scale({ 0.5, 0.5 }));
	//pb.transform_matrix(matrix_2d::init_rotate(half_pi<double> / 4.0));
	//pb.transform_matrix(matrix_2d::init_translate({ 0.0, 100.0 }));
	location = testArcClockwiseEndAngle(pb, location, false, { 60.0, 60.0 });

	//locY += 200;
	//location.x(beginLocX);
	//location.y(locY);
//	{
//		//{
//		//	matrix_2d m;
//		//	const double quarterpi = half_pi<double> / 2.0;
//		//	const double rot = quarterpi;
//		//	const vector_2d startPt{ 180.0, 140.0 };
//		//	const double startAng = to_radians(180);
//		//	bool clockwise = true;
//		//	vector_2d rad{ 60.0, 60.0 };
//		//	m.scale({ rad.x() / rad.y(), 1.0 });
//		//	auto centerOffset = point_for_angle(two_pi<double> - startAng) * rad;
//		//	m.translate(startPt + centerOffset);
//		//	vector_2d pt0, pt1, pt2, pt3;
//		//	int bezCount = 1;
//		//	double theta = rot;// abs(rot);
//		//					   //while (theta > half_pi<double>) {
//		//	while (abs(theta) > half_pi<double>) {
//		//		//while (theta > quarterpi) {
//		//		theta /= 2.0;
//		//		bezCount += bezCount;
//		//	}
//		//	double phi;
//		//	if (clockwise) {
//		//		phi = (theta / 2.0);
//		//		const auto cosPhi = cos(-phi);
//		//		const auto sinPhi = sin(-phi);
//		//		pt0.x(cosPhi);
//		//		pt0.y(-sinPhi);
//		//		pt3.x(pt0.x());
//		//		pt3.y(-pt0.y());
//		//		pt1.x((4.0 - cosPhi) / 3.0);
//		//		pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
//		//		pt2.x(pt1.x());
//		//		pt2.y(-pt1.y());
//		//	}
//		//	else {
//		//		phi = (theta / 2.0);
//		//		const auto cosPhi = cos(phi);
//		//		const auto sinPhi = sin(phi);
//		//		pt0.x(cosPhi);
//		//		pt0.y(-sinPhi);
//		//		pt3.x(pt0.x());
//		//		pt3.y(-pt0.y());
//		//		pt1.x((4.0 - cosPhi) / 3.0);
//		//		pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
//		//		pt2.x(pt1.x());
//		//		pt2.y(-pt1.y());
//		//	}
//
//		//}
//
//		const auto closePath = false;
//		const double quarterPi = half_pi<double> / 2.0;
//		const double radDefault = 60.0;
//		vector_2d radius{ radDefault, radDefault };
//		double rotation = pi<double>;
//		double startAngle = pi<double>;
//		//double endAngle = 0.0;
//		//vector_2d ctrVal{};
//		//double angleVal{};
//		//const vector_2d relcenter{ 60.0, 0.0 };
//		//vector_2d scale{ 1.0, 1.0 };
//		const vector_2d locadd{ 200.0, 0.0 };
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//		stringstream outputDebugStr;
//#endif
//		pb.new_path(location);
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//		outputDebugStr.str(""s);
//		outputDebugStr << "Center: " << location << "\nCurrent Point: " << location - ctrVal << "\nDiff: " << ctrVal << "\nAngle: " << angleVal << "\n\n";
//		OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//		startAngle = half_pi<double> + quarterPi;
//		rotation = -startAngle;
//		radius = { 60.0, 60.0 };
//		pb.rel_line_to({ 40.0, 0.0 });
//		pb.arc(radius, rotation, startAngle);
//		pb.rel_line_to({ 60.0, 0.0 });
//		if (closePath) {
//			pb.close_path();
//		}
//
//		locY += 200;
//		location.x(beginLocX);
//		location.y(locY);
//		//location += locadd;
//
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//		stringstream outputDebugStr;
//#endif
//		pb.new_path(location);
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//		outputDebugStr.str(""s);
//		outputDebugStr << "Center: " << location << "\nCurrent Point: " << location - ctrVal << "\nDiff: " << ctrVal << "\nAngle: " << angleVal << "\n\n";
//		OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//		startAngle = half_pi<double> +quarterPi;
//		rotation = -startAngle;
//		radius = { 30.0, 60.0 };
//		pb.rel_line_to({ 40.0, 0.0 });
//		pb.arc(radius, rotation, startAngle);
//		pb.rel_line_to({ 60.0, 0.0 });
//		if (closePath) {
//			pb.close_path();
//		}
//
//		locY += 200;
//		location.x(beginLocX);
//		location.y(locY);
//		//location += locadd;
//
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//		stringstream outputDebugStr;
//#endif
//		pb.new_path(location);
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//		outputDebugStr.str(""s);
//		outputDebugStr << "Center: " << location << "\nCurrent Point: " << location - ctrVal << "\nDiff: " << ctrVal << "\nAngle: " << angleVal << "\n\n";
//		OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//		startAngle = half_pi<double> +quarterPi;
//		rotation = -startAngle;
//		radius = { 60.0, 30.0 };
//		pb.rel_line_to({ 40.0, 0.0 });
//		pb.arc(radius, rotation, startAngle);
//		pb.rel_line_to({ 60.0, 0.0 });
//		if (closePath) {
//			pb.close_path();
//		}
//
//		locY += 200;
//		location.x(beginLocX);
//		location.y(locY);
//		//location += locadd;
//	}
	//location = testArcClockwiseStartAngle(pb, location);

	locY += 200;
	location.x(beginLocX);
	location.y(locY);

	location = testArcClockwiseEndAngle(pb, location, false, { 60.0, 30.0 });

	locY += 200;
	location.x(beginLocX);
	location.y(locY);

	location = testArcClockwiseEndAngle(pb, location, false, { 30.0, 60.0 });

	locY += 200;
	location.x(beginLocX);
	location.y(locY);

	//location = testArcClockwiseStartAngle(pb, location, false, { 0.5, 1.0 });
	//
	//locY += 200;
	//location.x(beginLocX);
	//location.y(locY);
	//
	//location = testArcClockwiseStartAngle(pb, location, false, { 1.0, 0.5 });
	//
	//locY += 200;
	//location.x(beginLocX);
	//location.y(locY);

	////// COUNTERCLOCKWISE

	location = testArcCounterclockwiseEndAngle(pb, location, false, { 60.0, 60.0 });

	locY += 200;
	location.x(beginLocX);
	location.y(locY);

	location = testArcCounterclockwiseEndAngle(pb, location, false, { 60.0, 30.0 });

	locY += 200;
	location.x(beginLocX);
	location.y(locY);

	location = testArcCounterclockwiseEndAngle(pb, location, false, { 30.0, 60.0 });

	locY += 200;
	location.x(beginLocX);
	location.y(locY);

	//// Test start angle 90 degree intervals starting at 180
	//locY += 200;
	//location.x(beginLocX);
	//location.y(locY);

	//location = testArcCounterclockwiseStartAngle(pb, location);

//	//// Template: copy - don't cut and paste
//	//location += locadd;
//	//pb.new_path(location + vector_2d{ 0.0, 0.0 });
//	//pb.rel_arc_clockwise(relcenter + vector_2d{ 0.0, 0.0 }, endAngle, scale);
//	//if (closePath) {
//	//	pb.close_path();
//	//}
//
//	//pb.new_path({ 120.0, 100.0 });
//	//pb.rel_arc_clockwise({ 40.0, 0.0 }, three_pi_over_two<double> + half_pi<double> / 2.0, { 1.0, 2.0 });
//	//pb.close_path();
//
//	////pb.rel_line_to({ 0.0, 50.0 });
//	////pb.line_to({ 140.0, 120.0 });
//	////pb.close_path();
//
//	//pb.new_path({ 40.0, 120.0 });
//	//pb.arc_counterclockwise({ 80.0, 120.0 }, 0.0); // half_pi<double> / 2.0);
//	//pb.close_path();
//	//pb.rel_new_path({ 100.0, 0.0 });
//	//pb.rel_arc_counterclockwise({ 40.0, 0.0 }, 0.0);// , { 1.0, 2.0 });
//	//pb.close_path();

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
	pb.arc(rad, -pi<double>, pi<double> - quarterPi);
	//pb.rel_arc_clockwise(relcenter + vector_2d{ 0.0, 0.0 }, endAngle + half_pi<double> +quarterPi, scale);
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
	pb.arc(rad, -pi<double>, pi<double> + quarterPi);
	if (closePath) {
		pb.close_path();
	}

	location += locadd;
	pb.new_path(location + vector_2d{ 0.0, 0.0 });
	pb.arc(rad, -two_pi<double>, three_pi_over_two<double> + quarterPi);
	pb.rel_line_to({ 40.0, 40.0 });// *scale);
	if (closePath) {
		pb.close_path();
	}

	return location + locadd;
}

//vector_2d testArcClockwiseStartAngle(path_builder<>& pb, vector_2d location, bool closePath, vector_2d scale, vector_2d relcenter, const vector_2d locadd) {
//	double endAngle = 0.0;
//	const double quarterPi = half_pi<double> / 2.0;
//	vector_2d ctrVal{};
//	double angleVal{};
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//	stringstream outputDebugStr;
//#endif
//	const auto locY = location.y();
//
//	// Test start angle 90 degree intervals starting at 180
//	ctrVal = point_for_angle(half_pi<double>, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	//angleVal = angle_for_point(ctrVal + location, location, scale);
//	angleVal = angle_for_point(location, location - ctrVal, scale);
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << ctrVal + location << " Current Point: " << location << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//
//	location.y(locY);
//	location += locadd;
//	ctrVal = point_for_angle(0.0, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	//angleVal = angle_for_point(ctrVal + location, location, scale);
//	angleVal = angle_for_point(location, location - ctrVal, scale);
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//	constexpr auto twopi = two_pi<double>;
//	location.y(locY);
//	location += locadd;
//	ctrVal = point_for_angle(three_pi_over_two<double>, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	//angleVal = angle_for_point(ctrVal + location, location, scale);
//	angleVal = angle_for_point(location - ctrVal, location, scale);
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//
//	location.y(locY);
//	location += locadd;
//	ctrVal = point_for_angle(two_pi<double>, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	angleVal = two_pi<double>;
//	//angleVal = angle_for_point(ctrVal + location, location, scale);
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//
//	// Test start angle 90 degree intervals starting at 135
//	location.y(locY);
//	location += locadd;
//	ctrVal = point_for_angle(half_pi<double> -quarterPi, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	angleVal = half_pi<double> -quarterPi;
//	//auto angleVal2 = angle_for_point(ctrVal + location, location, scale);
//	//angleVal = angleVal2;
//	angleVal = angle_for_point(location, location - ctrVal, scale);
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//
//	location.y(locY);
//	location += locadd;
//	ctrVal = point_for_angle(pi<double> -quarterPi, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	//angleVal = angle_for_point(ctrVal + location, location);
//	angleVal = pi<double> -quarterPi;
//	angleVal = angle_for_point(location, location - ctrVal, scale);
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//
//	location.y(locY);
//	location += locadd;
//	ctrVal = point_for_angle(three_pi_over_two<double> -quarterPi, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	//angleVal = angle_for_point(ctrVal + location, location, scale);
//	angleVal = angle_for_point(location, location - ctrVal, scale);
//	angleVal = three_pi_over_two<double> -quarterPi;
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//
//	location.y(locY);
//	location += locadd;
//	ctrVal = point_for_angle(two_pi<double> -quarterPi, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	//angleVal = angle_for_point(ctrVal + location, location, scale);
//	angleVal = angle_for_point(location, location - ctrVal, scale);
//	angleVal = two_pi<double> -quarterPi;
//#if defined(DEBUG_ARC_TESTS) && defined(_MSC_VER)
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_clockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//
//	location.y(locY);
//	return location + locadd;
//}

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
	//pb.rel_arc_clockwise(relcenter + vector_2d{ 0.0, 0.0 }, endAngle + half_pi<double> +quarterPi, scale);
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

//vector_2d testArcCounterclockwiseStartAngle(path_builder<>& pb, vector_2d location, bool closePath, vector_2d scale, vector_2d relcenter, const vector_2d locadd) {
//	double endAngle = 0.0;
//	const double quarterPi = half_pi<double> / 2.0;
//	vector_2d ctrVal{};
//	double angleVal{};
//	stringstream outputDebugStr;
//	const auto locY = location.y();
//
//	ctrVal = point_for_angle(pi<double>, relcenter.magnitude());
//	location -= ctrVal;
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	angleVal = angle_for_point(ctrVal + location, location);
//#ifdef _MSC_VER
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << ctrVal + location << " Current Point: " << location << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_counterclockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//
//	location.y(locY);
//	location += locadd;
//	ctrVal = point_for_angle(half_pi<double>, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	angleVal = angle_for_point(ctrVal + location, location);
//#ifdef _MSC_VER
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_counterclockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//
//	location.y(locY);
//	location += locadd;
//	ctrVal = point_for_angle(0.0, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	angleVal = angle_for_point(ctrVal + location, location);
//#ifdef _MSC_VER
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_counterclockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//
//	location.y(locY);
//	location += locadd;
//	ctrVal = point_for_angle(three_pi_over_two<double>, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	angleVal = angle_for_point(ctrVal + location, location);
//#ifdef _MSC_VER
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_counterclockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//
//	// Test start angle 90 degree intervals starting at 135
//	location.y(locY);
//	location += locadd;
//	ctrVal = point_for_angle(half_pi<double> -quarterPi, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	//angleVal = angle_for_point(ctrVal + location, location);
//	angleVal = half_pi<double> -quarterPi;
//#ifdef _MSC_VER
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_counterclockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//
//	location.y(locY);
//	location += locadd;
//	ctrVal = point_for_angle(pi<double> -quarterPi, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	angleVal = pi<double> -quarterPi;
//#ifdef _MSC_VER
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_counterclockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//
//	location.y(locY);
//	location += locadd;
//	ctrVal = point_for_angle(three_pi_over_two<double> -quarterPi, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	angleVal = three_pi_over_two<double> -quarterPi;
//#ifdef _MSC_VER
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	//scale.y(0.5);
//	pb.rel_arc_counterclockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//	//scale.y(1.0);
//
//	location.y(locY);
//	location += locadd;
//	ctrVal = point_for_angle(two_pi<double> -quarterPi, relcenter.magnitude());
//	pb.new_path(location + vector_2d{ 0.0, 0.0 } -ctrVal);
//	angleVal = two_pi<double> -quarterPi;
//#ifdef _MSC_VER
//	outputDebugStr.str(""s);
//	outputDebugStr << "Center: " << location << " Current Point: " << location - ctrVal << " Diff: " << ctrVal << " Angle: " << angleVal << "\n";
//	OutputDebugStringA(outputDebugStr.str().c_str());
//#endif
//	endAngle = angleVal;
//	pb.rel_arc_counterclockwise(ctrVal, endAngle, scale);
//	if (closePath) {
//		pb.close_path();
//	}
//
//	location.y(locY);
//	return location + locadd;
//}
