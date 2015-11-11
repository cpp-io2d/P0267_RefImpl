#include "sample_draw.h"
#include "xio2dhelpers.h"
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <chrono>
#include "test_renderer.h"

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;
using namespace not_proposed::test_renderer;

// Declarations
void draw_radial_circles(display_surface& rs);
void test_draw_radial_circles(display_surface& rs);
wostream& operator<<(wostream& os, const vector_2d& pt);
vector<vector<int>> init_sort_steps(int count, unsigned long mtSeed = 1009UL);
void draw_hello_world(surface& rs);
void draw_test_compositing_operators(surface& rs, compositing_operator secondRectCompOp, compositing_operator firstRectCompOp = compositing_operator::over, bool clipToRects = false, bool clipToTriangle = false, bool strokePaths = false, bool mask = false, const rgba_color& backgroundColor = rgba_color::transparent_black(), const rgba_color& firstColor = rgba_color::red() * 0.8, const rgba_color& secondColor = rgba_color::teal() * 0.4);
void draw_sort_visualization_immediate(surface& rs, double elapsedTimeInMilliseconds);
void draw_sort_visualization(surface& rs, double elapsedTimeInMilliseconds);
void test_compositing_operators_different_pixel_formats(surface& rs, compositing_operator co);
void test_paint_surface_extend_modes(surface& rs, double elapsedTimeInMilliseconds);
void test_fill_rules(surface& rs);

//
// Drawing entry point.
//
void sample_draw::operator()(display_surface& rs) {
	//test_draw_radial_circles(rs);

	static auto previousTime = steady_clock::now();
	auto currentTime = steady_clock::now();
	auto elapsedTime = currentTime - previousTime;
	previousTime = currentTime;
	draw_sort_visualization_immediate(rs, duration_cast<microseconds>(elapsedTime).count() / 1000.0);
	
	//draw_test_compositing_operators(rs, compositing_operator::in, compositing_operator::over, true, false, false, true);
	
	//test_compositing_operators_different_pixel_formats(rs, compositing_operator::out);
	
	//static auto previousTime = steady_clock::now();
	//auto currentTime = steady_clock::now();
	//auto elapsedTime = currentTime - previousTime;
	//previousTime = currentTime;
	//test_paint_surface_extend_modes(rs, duration_cast<microseconds>(elapsedTime).count() / 1000.0);

	//test_fill_rules(rs);
}

void test_fill_rules(surface& rs) {
	rs.clear();
	auto prevFr = rs.fill_rule();

	bool clockwise = true;

	auto rect = rectangle{ 10.0, 10.0, 120.0, 90.0 };

	rs.fill_rule(fill_rule::winding);
	clockwise = true;
	rs.immediate().clear();
	rect.top_left({ 10.0, 10.0 });
	rs.immediate().rectangle(rect, clockwise);
	rect.top_left({ 50.0, 40.0 });
	rs.immediate().rectangle(rect, clockwise);
	rs.fill_immediate(rgba_color::red() * 0.5);

	rs.immediate().clear();
	rect.top_left({ 10.0, 150.0 });
	rs.immediate().rectangle(rect, clockwise);
	rect.top_left({ 50.0, 190.0 });
	clockwise = false;
	rs.immediate().rectangle(rect, clockwise);
	rs.fill_immediate(rgba_color::red() * 0.5);

	rs.fill_rule(fill_rule::even_odd);
	clockwise = true;
	rs.immediate().clear();
	rect.top_left({ 190.0, 10.0 });
	rs.immediate().rectangle(rect, clockwise);
	rect.top_left({ 240.0, 40.0 });
	rs.immediate().rectangle(rect, clockwise);
	rs.fill_immediate(rgba_color::red() * 0.5);

	rs.immediate().clear();
	rect.top_left({ 190.0, 150.0 });
	rs.immediate().rectangle(rect, clockwise);
	rect.top_left({ 240.0, 190.0 });
	clockwise = false;
	rs.immediate().rectangle(rect, clockwise);
	rs.fill_immediate(rgba_color::red() * 0.5);

	rs.fill_rule(prevFr);
}

void test_paint_surface_extend_modes(surface& rs, double elapsedTimeInMilliseconds) {
	static image_surface imgSfc{ format::argb32, 120, 90 };
	static bool imgSfcInitialized = false;
	if (!imgSfcInitialized) {
		imgSfc.paint(rgba_color::red());
		
		imgSfc.immediate().move_to({ 60.0, 0.0 });
		imgSfc.immediate().line_to({ 120.0, 0.0 });
		imgSfc.immediate().line_to({ 120.0, 90.0 });
		imgSfc.immediate().line_to({ 0.0, 90.0 });
		imgSfc.immediate().line_to({ 0.0, 45.0 });
		imgSfc.immediate().line_to({ 60.0, 45.0 });
		imgSfc.immediate().close_path();
		imgSfc.clip_immediate();
		imgSfc.paint(rgba_color::yellow());
		
		imgSfc.immediate().clear();
		imgSfc.immediate().move_to({ 0.0, 45.0 });
		imgSfc.immediate().line_to({ 120.0, 45.0 });
		imgSfc.immediate().line_to({ 120.0, 90.0 });
		imgSfc.immediate().line_to({ 0.0, 90.0 });
		imgSfc.immediate().close_path();
		imgSfc.clip_immediate();
		imgSfc.paint(rgba_color::green());

		imgSfc.immediate().clear();
		imgSfc.immediate().move_to({ 60.0, 45.0 });
		imgSfc.immediate().line_to({ 120.0, 45.0 });
		imgSfc.immediate().line_to({ 120.0, 90.0 });
		imgSfc.immediate().line_to({ 60.0, 90.0 });
		imgSfc.immediate().close_path();
		imgSfc.clip_immediate();
		imgSfc.paint(rgba_color::blue());
		imgSfcInitialized = true;
	}
	static double totalElapsedTime = 0.0;
	rs.compositing_operator(compositing_operator::source);
	rs.immediate().rectangle({ 400.0, 0.0, 100.0, 100.0 });
	rs.fill_immediate(rgba_color::orange());
	rs.immediate().clear();
	if (totalElapsedTime < 1000.0) {
		// Do nothing.
	}
	else {
		if (totalElapsedTime < 3000.0) {
			rs.paint(imgSfc, { 0.0, 0.0 }, extend::none);
		}
		else {
			rs.paint(imgSfc, { 0.0, 0.0 }, extend::repeat);
		}
	}
	totalElapsedTime += elapsedTimeInMilliseconds;
}

void test_compositing_operators_different_pixel_formats(surface& rs, compositing_operator co) {
	image_surface srcSfc{ format::a8, 120, 90 };
	image_surface dstSfc{ format::argb32, 120, 90 };
	srcSfc.clear();
	srcSfc.paint(rgba_color::blue(), 0.6);
	dstSfc.clear();
	dstSfc.paint(rgba_color::lime(), 0.4);
	rs.clear();
	
	//auto data = srcSfc.data();
	//rs.paint(rgba_color::white());
	rs.compositing_operator(compositing_operator::over);
	rs.immediate().rectangle({ 10.0, 10.0, 120.0, 90.0 });
	rs.fill_immediate(srcSfc, matrix_2d::init_translate({ -10.0, -10.0 }));
	rs.compositing_operator(co);
	rs.immediate().clear();
	rs.immediate().rectangle({ 50.0, 40.0, 120.0, 90.0 });
	rs.fill_immediate(dstSfc, matrix_2d::init_translate({ -50.0, -40.0 }));
}

void test_draw_radial_circles(display_surface& rs) {
	rs.paint(rgba_color::cornflower_blue());
	rs.fill_rule(fill_rule::winding);
	rs.matrix(matrix_2d::init_identity());
	auto radialFactory = radial_brush_factory();
	radialFactory.add_color_stop(0.0, rgba_color::white());
	radialFactory.add_color_stop(0.25, rgba_color::red());
	radialFactory.add_color_stop(0.5, rgba_color::green());
	radialFactory.add_color_stop(0.75, rgba_color::blue());
	//radialFactory.add_color_stop(1.0, rgba_color::black());
	radialFactory.add_color_stop(1.0, rgba_color::black());
	//radialFactory.radial_circles({ 400.0, 200.0 }, 100.0, { 600.0, 200.0 }, 50.0);
	vector_2d center0 = { 150.0, 150.0 }/*{ 200.5, 300.0 }*/;
	double radius0 = 10.0;
	vector_2d center1 = { 300.0, 300.0 };
	double radius1 = 100.0;
	radialFactory.radial_circles(center0, radius0, center1, radius1);
	auto extendMode = extend::reflect;
	auto radialBrush = brush(radialFactory);
	radialBrush.extend(extendMode);
	path_factory pf;
	rectangle drawArea = { { 100.0, 100.0 }, { 500.0, 500.0 } };
	pf.rectangle(drawArea);
	path p(pf);
	rs.path(p);
	rs.brush(radialBrush);
	rs.fill();

	auto dx = 500.0;
	auto dy = 0.0;
	vector_2d delta{ dx, dy };
	center0 += delta;
	center1 += delta;
	radialFactory.radial_circles(center0, radius0, center1, radius1);
	drawArea.x(drawArea.x() + dx);
	drawArea.y(drawArea.y() + dy);
	render_fill_rect_radial_gradient(rs, drawArea, radialFactory, extendMode);
}

void draw_radial_circles(display_surface& rs) {
	// Clear to background color.
	rs.paint(rgba_color::cornflower_blue());
	rs.fill_rule(fill_rule::winding);
	rs.matrix(matrix_2d::init_identity());
	auto radialFactory = radial_brush_factory();
	radialFactory.add_color_stop(0.0, rgba_color::white());
	//radialFactory.add_color_stop(0.25, rgba_color::red());
	//radialFactory.add_color_stop(0.5, rgba_color::green());
	//radialFactory.add_color_stop(0.75, rgba_color::blue());
	//radialFactory.add_color_stop(1.0, rgba_color::black());
	radialFactory.add_color_stop(1.0, rgba_color::black());
	//radialFactory.radial_circles({ 400.0, 200.0 }, 100.0, { 600.0, 200.0 }, 50.0);

	radialFactory.radial_circles({ 200.5, 300.0 }, 0.0, { 300.0, 300.0 }, 100.0);
	auto radialBrush = brush(radialFactory);
	radialBrush.extend(extend::repeat);
	path_factory pf;
	//pf.rectangle({ { 100.0, 100.0 }, { 500.0, 500.0 } });
	pf.move_to({ 100.0, 100.0 });
	pf.line_to({ 500.0, 100.0 });
	pf.change_matrix(matrix_2d::init_shear_x(0.25));
	pf.line_to({ 500.0, 500.0 });
	pf.close_path();
	pf.change_matrix(matrix_2d::init_identity());
	pf.line_to({ 50.0, 150.0 });
	pf.move_to({ 520.0, 520.0 });
	pf.line_to({ 600.0, 600.0 });
	pf.change_matrix(matrix_2d::init_scale({ 2.0, 1.0 }));
	pf.arc({ 300.0, 700.0 }, 100.0, three_pi_over_two<double>(), two_pi<double>());
	pf.change_matrix(matrix_2d::init_identity());
	pf.move_to({ 520.0, 10.0 });
	pf.curve_to({ 480.0, 60.0 }, { 560.0, 60.0 }, { 520.0, 10.0 });
	path p(pf);
	rs.path(p);
	rs.brush(radialBrush);
	auto fe = rs.fill_extents();
	auto se = rs.stroke_extents();
	vector_2d pt{ 110.0, 300.0 };
	auto inFill = rs.in_fill(pt);
	rs.fill();
	rs.brush(brush(solid_color_brush_factory(rgba_color::red())));
	rs.stroke();
	pf.clear();
	pf.new_sub_path();
	pf.arc({ 900.0, 200.0 }, 50.0, 0.0, two_pi<double>());
	pf.new_sub_path();
	pf.arc_negative({ 900.0, 200.0 }, 75.0, 0.0, two_pi<double>());
	pf.new_sub_path();
	pf.arc({ 900.0, 200.0 }, 100.0, 0.0, two_pi<double>());
	pf.new_sub_path();
	pf.arc_negative({ 900.0, 200.0 }, 125.0, 0.0, two_pi<double>());
	pf.new_sub_path();
	pf.arc({ 900.0, 200.0 }, 150.0, 0.0, two_pi<double>());
	p = path(pf);
	rs.path(p);
	rs.fill();
	rs.matrix(matrix_2d::init_translate({ 0.0, 310.0 }));
	rs.path(p);
	rs.fill_rule(fill_rule::even_odd);
	rs.fill();

	//render_ellipse(rs, { 200.0, 600.0 }, 250.0, 100.0, rgba_color(0.0, 1.0, 1.0, 1.0));

	//radialFactory.radial_circles({ 200.5, 300.0 }, 0.0, { 300.0, 300.0 }, 100.0);
	//auto radialBrush = brush(radialFactory);
	//radialBrush.extend(extend::repeat);
	////radialBrush.matrix(matrix_2d::init_scale({ 2.0, 2.0 }));
	//rs.immediate().clear();
	//rs.immediate().rectangle({ { 100.0, 100.0 }, { 500.0, 500.0 } });
	//rs.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 115.2, 102.4 }, 25.6, { 102.4, 102.4 }, 128.0);
	//radialBrush = brush(radialFactory);
	//radialBrush.extend(extend::pad);
	//rs.immediate().clear();
	//rs.immediate().arc({ 128.0, 128.0 }, 76.8, 0.0, 2 * pi);
	////rs.immediate().rectangle({ 0.0, 0.0, 250.0, 250.0 });
	//rs.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 400.0, 200.0 }, 100.0, { 600.0, 200.0 }, 100.0);
	//auto color = test_draw_circle(rs, { 400.0, 200.0 }, radialFactory);
	//
	//{
	//	auto linearFactory = linear_brush_factory();
	//	linearFactory.begin_point({ 200.0, 0.0 });
	//	linearFactory.end_point({ 601.0, 0.0 });
	//	linearFactory.add_color_stop(0.0, rgba_color::white());
	//	linearFactory.add_color_stop(0.25, rgba_color::red());
	//	linearFactory.add_color_stop(0.5, rgba_color::lime());
	//	linearFactory.add_color_stop(0.6, rgba_color::red());
	//	linearFactory.add_color_stop(0.5, rgba_color::blue());
	//	linearFactory.add_color_stop(1.0, rgba_color::white());
	//
	//	rs.immediate().clear();
	//	rs.immediate().rectangle({ { 200.0, 280.0 }, { 602.0, 520.0 } });
	//	rs.fill_immediate(brush(linearFactory));
	//}
	//
	//radialFactory.radial_circles({ 600.0, 200.0 }, 100.0, { 400.0, 200.0 }, 100.0);
	//rs.immediate().clear();
	//rs.immediate().rectangle({ { 280.0, 80.0 }, { 720.0, 320.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.extend(extend::pad);
	//rs.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 400.0, 450.0 }, 100.0, { 600.0, 450.0 }, 100.0);
	//rs.immediate().clear();
	//rs.immediate().rectangle({ { 280.0, 330.0 }, { 720.0, 570.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.extend(extend::none);
	//rs.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 1000.0, 200.0 }, 100.0, { 1000.0, 200.0 }, 20.0);
	//rs.immediate().clear();
	//rs.immediate().rectangle({ { 880.0, 80.0 }, { 1120.0, 320.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.extend(extend::reflect);
	//rs.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 1000.0, 450.0 }, 20.0, { 1000.0, 450.0 }, 100.0);
	//rs.immediate().clear();
	//rs.immediate().rectangle({ { 880.0, 330.0 }, { 1120.0, 570.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.extend(extend::repeat);
	//rs.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 105.0, 100.0 }, 0.0, { 200.0, 100.0 }, 100.0);
	//rs.immediate().clear();
	//rs.immediate().rectangle({ { 0.0, 0.0 }, { 520.0, 200.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.extend(extend::repeat);
	//rs.fill_immediate(radialBrush);
	//
	//
	//radialFactory.radial_circles({ 200.0, 200.0 }, 100.0, { 400.0, 200.0 }, 100.0);
	//rs.immediate().clear();
	//rs.immediate().rectangle({ { 80.0, 80.0 }, { 520.0, 320.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.extend(extend::none);
	//rs.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 200.0, 450.0 }, 100.0, { 400.0, 450.0 }, 100.0);
	//rs.immediate().clear();
	//rs.immediate().rectangle({ { 80.0, 330.0 }, { 520.0, 570.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.extend(extend::pad);
	//rs.fill_immediate(radialBrush);
	//
	////radialFactory.radial_circles({ 200.0, 450.0 }, 100.0, { 400.0, 450.0 }, 100.0);
	////rs.immediate().clear();
	////rs.immediate().rectangle({ { 80.0, 330.0 }, { 520.0, 570.0 } });
	////radialBrush = brush(radialFactory);
	////radialBrush.extend(extend::pad);
	////rs.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 700.0, 200.0 }, 100.0, { 900.0, 200.0 }, 100.0);
	//rs.immediate().clear();
	//rs.immediate().rectangle({ { 580.0, 80.0 }, { 1020.0, 320.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.extend(extend::reflect);
	//rs.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 700.0, 450.0 }, 100.0, { 900.0, 450.0 }, 100.0);
	//rs.immediate().clear();
	//rs.immediate().rectangle({ { 580.0, 330.0 }, { 1020.0, 570.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.extend(extend::repeat);
	//rs.fill_immediate(radialBrush);
}

wostream& operator<<(wostream& os, const vector_2d& pt) {
	os << L"(" << pt.x() << L"," << pt.y() << L")";
	return os;
}

vector<vector<int>> init_sort_steps(int count, unsigned long mtSeed) {
	vector<vector<int>> result;
	result.push_back([count, mtSeed]() {
		vector<int> init;
		for (int i = 0; i < count; ++i) {
			init.push_back(i);
		}
		mt19937 rng(mtSeed);
		shuffle(begin(init), end(init), rng);
		return init;
	}());
	bool notSorted = true;
	while (notSorted) {
		vector<int> curr(result.back());
		const auto size = curr.size();
		notSorted = false;
		for (auto i = 0U; i < size - 1; ++i) {
			if (curr[i] > curr[i + 1]) {
				notSorted = true;
				auto temp = curr[i + 1];
				curr[i + 1] = curr[i];
				curr[i] = temp;
			}
		}
		if (notSorted) {
			result.push_back(curr);
		}
	}
	return result;
}

void init_mask_surface(image_surface& imsfc) {
	// { 30.0, 25.0, 70.0, 70.0 } - clip
	imsfc.immediate().move_to({ 40.0, 0.0 });
	imsfc.immediate().rel_curve_to({ -35.0, 70.0 }, { -35.0, 70.0 }, { 0.0, 140.0 });
	imsfc.immediate().rel_curve_to({ 35.0, -70.0 }, { 35.0, -70.0 }, { 0.0, -140.0 });
	imsfc.brush({ rgba_color::white() });
	imsfc.fill_immediate();
}

void draw_hello_world(surface& rs) {
	rs.show_text("Hello world", { 100.0, 100.0 }, brush(solid_color_brush_factory(rgba_color::white())));
}

// For testing purposes only.
void draw_test_compositing_operators(surface& rs, compositing_operator secondRectCompOp, compositing_operator firstRectCompOp, bool clipToRects, bool clipToTriangle, bool strokePaths, bool mask, const rgba_color& backgroundColor, const rgba_color& firstColor, const rgba_color& secondColor) {
	// Parameter validation.
	if (clipToRects && clipToTriangle) {
		throw invalid_argument("clipToRects and clipToTriangle cannot both be set to true.");
	}
	rs.save();

	auto backgroundBrush = brush(solid_color_brush_factory(backgroundColor));
	auto firstBrush = brush(solid_color_brush_factory(firstColor));
	auto secondBrush = brush(solid_color_brush_factory(secondColor));

	auto pb = path_factory();

	pb.rectangle({ 10.0, 10.0, 120.0, 90.0 });
	auto firstRectPath = path(pb);

	pb.clear();
	pb.rectangle({ 50.0, 40.0, 120.0, 90.0 });
	auto secondRectPath = path(pb);

	pb.clear();
	pb.rectangle({ 30.0, 25.0, 70.0, 70.0 });
	auto bothRectsClipPath = path(pb);

	pb.clear();
	pb.move_to({ 85.0, 25.0 });
	pb.line_to({ 150.0, 115.0 });
	pb.line_to({ 30.0, 115.0 });
	pb.close_path();
	auto triangleClipPath = path(pb);

	rs.brush(backgroundBrush);
	rs.compositing_operator(compositing_operator::clear);
	rs.paint();

	rs.brush(firstBrush);
	rs.compositing_operator(firstRectCompOp);
	rs.path(firstRectPath);
	rs.fill();

	rs.save(); // Preserve old clip.
	if (clipToRects) {
		rs.clip(bothRectsClipPath);
	}

	if (clipToTriangle) {
		rs.clip(triangleClipPath);
	}

	rs.path(secondRectPath);
	rs.compositing_operator(secondRectCompOp);
	rs.brush(secondBrush);
	if (mask) {
		static image_surface maskSurface(format::a8, 200, 200);
		static once_flag drawMaskOnceFlag;
		static bool maskSurfaceInitialized = false;
		if (!maskSurfaceInitialized) {
			init_mask_surface(maskSurface);
			maskSurfaceInitialized = true;
		}
		//function<void(bool&)> fn([](bool & msinit) { msinit = true; });
		//call_once(drawMaskOnceFlag,
		//	fn,
		//	maskSurfaceInitialized);
		//	//init_mask_surface,
		////	[](image_surface&& imsfc) -> image_surface&& {
		////	// { 30.0, 25.0, 70.0, 70.0 } - clip
		////	imsfc.immediate().move_to({ 40.0, 0.0 });
		////	imsfc.immediate().rel_curve_to({ -35.0, 70.0 }, { -35.0, 70.0 }, { 0.0, 140.0 });
		////	imsfc.immediate().rel_curve_to({ 35.0, -70.0 }, { 35.0, -70.0 }, { 0.0, -140.0 });
		////	imsfc.brush({ rgba_color::white() });
		////	imsfc.fill_immediate();
		////	return move(imsfc);
		////}, 
		//	//move(maskSurface));
		rs.mask(maskSurface);
	}
	else {
		rs.fill();
	}

	rs.restore(); // Restore old clip

	if (strokePaths) {
		rs.compositing_operator(compositing_operator::source);
		rs.line_width(2.0);

		rs.path(firstRectPath);
		rs.brush(brush(solid_color_brush_factory(rgba_color::teal())));
		rs.stroke();

		rs.path(secondRectPath);
		rs.brush(brush(solid_color_brush_factory(rgba_color::red())));
		rs.stroke();

		if (clipToTriangle) {
			rs.path(triangleClipPath);
			rs.brush(brush(solid_color_brush_factory(rgba_color::yellow())));
			rs.stroke();
		}
	}

	rs.restore();
}

void draw_sort_visualization_immediate(surface& rs, double elapsedTimeInMilliseconds) {
	static double timer = 0.0;
	const double power = 3.0;
	const double lerpTime = 1250.0;
	const double phaseTime = lerpTime + 500.0;
	const double normalizedTime = min(fmod(timer, phaseTime) / lerpTime, 1.0);
	const double adjustment = (normalizedTime < 0.5) ? pow(normalizedTime * 2.0, power) / 2.0 :
		((1.0 - pow(1.0 - ((normalizedTime - 0.5) * 2.0), power)) * 0.5) + 0.5;
	const int elementCount = 12;
	const static auto vec = init_sort_steps(elementCount);
	const auto phaseCount = vec.size();
	const size_t x = ::std::min(static_cast<size_t>(timer / phaseTime), ::std::max(static_cast<size_t>(phaseCount - 1U), static_cast<size_t>(0U)));
	rs.paint(rgba_color::cornflower_blue()); // Paint background.

	rs.immediate().clear();
	rs.immediate().arc({ 100.0, 100.0 }, 50.0, 0.0, half_pi<double>());
	auto initLineWidth = rs.line_width();
	rs.line_width(8.0);
	rs.stroke_immediate(rgba_color::black());
	rs.immediate().clear();
	rs.immediate().arc_negative({ 300.0, 100.0 }, 50.0, 0.0, half_pi<double>());
	rs.stroke_immediate(rgba_color::brown());
	rs.immediate().clear();
	rs.line_width(initLineWidth);

	auto clextents = rs.clip_extents();
	const double radius = trunc(min(clextents.width() * 0.8 / elementCount, clextents.height() + 120.0) / 2.0);
	const double beginX = trunc(clextents.width() * 0.1);
	const double y = trunc(clextents.height() * 0.5);

	auto linearTest1 = linear_brush_factory({ 400.0, 400.0 }, { 400.0, 500.0 });
	linearTest1.add_color_stop(0.0, rgba_color::black());
	linearTest1.add_color_stop(0.3, rgba_color::yellow());
	linearTest1.add_color_stop(0.5, rgba_color::blue());
	linearTest1.add_color_stop(0.3, rgba_color::lime());
	linearTest1.add_color_stop(0.5, rgba_color::black());
	linearTest1.add_color_stop(0.7, rgba_color::purple());
	linearTest1.add_color_stop(0.5, rgba_color::red());
	//	linearTest1.add_color_stop(1.0, rgba_color::black());
	linearTest1.add_color_stop(0.7, rgba_color::orange());
	linearTest1.add_color_stop(0.8, rgba_color::green());
	linearTest1.add_color_stop(0.8, rgba_color::yellow());
	linearTest1.add_color_stop(1.0, rgba_color::white());
	rs.immediate().rectangle({ 400.0, 400.0, 200.0, 200.0 });
	rs.fill_immediate(brush(linearTest1));

	rs.font_face("Segoe UI", font_slant::normal, font_weight::normal);
	rs.font_size(40.0);
	auto str = string("Phase ").append(to_string(x + 1));
	rs.show_text(str, { beginX, 50.0 }, rgba_color::white());

	for (size_t i = 0; i < elementCount; ++i) {
		rs.immediate().clear();
		const auto currVal = vec[x][i];
		if (x < phaseCount - 1) {
			const auto i2 = find(begin(vec[x + 1]), end(vec[x + 1]), currVal) - begin(vec[x + 1]);
			const auto x1r = radius * i * 2.0 + radius + beginX, x2r = radius * i2 * 2.0 + radius + beginX;
			const auto yr = y - ((i2 == static_cast<int>(i) ? 0.0 : (radius * 4.0 * (normalizedTime < 0.5 ? normalizedTime : 1.0 - normalizedTime)))
				* (i % 2 == 1 ? 1.0 : -1.0));
			const auto center = vector_2d{ trunc((x2r - x1r) * adjustment + x1r), trunc(yr) };
			rs.immediate().change_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi<double>() / 4.0) * matrix_2d::init_translate({ 0.0, 50.0 }));
			rs.immediate().change_origin(center);
			rs.immediate().arc_negative(center, radius - 3.0, half_pi<double>(), -half_pi<double>());
		}
		else {
			const vector_2d center{ radius * i * 2.0 + radius + beginX, y };
			rs.immediate().change_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi<double>() / 4.0));
			rs.immediate().change_origin(center);
			rs.immediate().arc_negative(center, radius - 3.0, half_pi<double>(), -half_pi<double>());
		}
		double greyColor = 1.0 - (currVal / (elementCount - 1.0));
		rs.fill_immediate({ greyColor, greyColor, greyColor, 1.0 });
	}

	rs.immediate().clear();
	rs.immediate().change_origin({ 250.0, 450.0 });
	rs.immediate().change_matrix(matrix_2d::init_shear_x(0.5).scale({ 2.0, 2.5 }));
	rs.immediate().rectangle({ 200.0, 400.0, 100.0, 100.0 });
	rs.line_width(3.0);
	rs.stroke_immediate(rgba_color::red());
	//auto radialFactory = radial_brush_factory({ 250.0, 450.0 }, 0.0, { 250.0, 450.0 }, 80.0);
	//radialFactory.add_color_stop(0.0, rgba_color::black());
	//radialFactory.add_color_stop(0.25, rgba_color::red());
	//radialFactory.add_color_stop(0.5, rgba_color::green());
	//radialFactory.add_color_stop(0.75, rgba_color::blue());
	//radialFactory.add_color_stop(1.0, rgba_color::white());
	//auto radialBrush = rs.create_brush(radialFactory);
	//radialBrush.extend(extend::reflect);
	//rs.fill_immediate(radialBrush);

	//auto meshFactory = mesh_brush_factory();
	//meshFactory.begin_patch();
	//meshFactory.move_to({ 0.0, 0.0 });
	//meshFactory.curve_to({ 30.0, -30.0 }, { 60.0, 30.0 }, { 100.0, 0.0 });
	//meshFactory.curve_to({ 60.0, 30.0 }, { 130.0, 60.0 }, { 100.0, 100.0 });
	//meshFactory.curve_to({ 60.0, 70.0 }, { 30.0, 130.0 }, { 0.0, 100.0 });
	//meshFactory.curve_to({ 30.0, 70.0 }, { -30.0, 30.0 }, { 0.0, 0.0 });
	//meshFactory.corner_color(0, rgba_color::red());
	//meshFactory.corner_color(1, rgba_color::lime());
	//meshFactory.corner_color(2, rgba_color::blue());
	//meshFactory.corner_color(3, rgba_color::yellow());
	//meshFactory.end_patch();
	//meshFactory.begin_patch();
	//meshFactory.move_to({ 100.0, 100.0 });
	//meshFactory.line_to({ 130.0, 130.0 });
	//meshFactory.line_to({ 130.0, 70.0 });
	//meshFactory.corner_color(0, rgba_color::red());
	//meshFactory.corner_color(1, rgba_color::lime());
	//meshFactory.corner_color(2, rgba_color::blue());
	//meshFactory.end_patch();
	//auto meshBrush = brush(meshFactory);
	//meshBrush.matrix(matrix_2d::init_translate({ -200.0, -400.0 }));
	//rs.fill_immediate(meshBrush);

	auto imgSfc = image_surface(format::argb32, 40, 40);
	imgSfc.immediate().move_to({ 0.0, 0.0 });
	imgSfc.immediate().line_to({ 40.0, 40.0 });
	imgSfc.immediate().line_to({ 0.0, 40.0 });
	imgSfc.immediate().close_path();
	imgSfc.paint(rgba_color::green());
	imgSfc.fill_immediate(rgba_color::yellow());

	auto sfcFactory = surface_brush_factory(imgSfc);
	auto sfcBrush = brush(sfcFactory);
	sfcBrush.extend(extend::repeat);
	rs.immediate().clear();
	rs.immediate().rectangle({ 500.0, 450.0, 100.0, 100.0 });
	rs.immediate().rectangle({ 525.0, 425.0, 50.0, 150.0 });
	rs.line_join(line_join::miter_or_bevel);
	rs.miter_limit(1.0);
	rs.line_width(10.0);
	rs.stroke_immediate(rgba_color::red());
	rs.fill_immediate(sfcBrush);

	auto linearFactory = linear_brush_factory({ 510.0, 460.0 }, { 530.0, 480.0 });
	linearFactory.add_color_stop(0.0, rgba_color::chartreuse());
	linearFactory.add_color_stop(1.0, rgba_color::salmon());
	auto linearBrush = brush(linearFactory);
	linearBrush.extend(extend::repeat);
	rs.immediate().clear();
	rs.immediate().move_to({ 650.0, 400.0 });
	rs.immediate().rel_line_to({ 0.0, 100.0 });
	rs.immediate().rel_line_to({ 10.0, -100.0 });
	rs.line_join(line_join::miter);
	rs.stroke_immediate(rgba_color::red());
	rs.fill_immediate(linearBrush);

	rs.immediate().clear();
	rs.immediate().move_to({ 430.0, 60.0 });
	rs.immediate().arc({ 500.0, 60.0 }, 30.0, pi<double>(), two_pi<double>());
	rs.immediate().line_to({ 570.0, 60.0 });
	//	rs.immediate().new_sub_path();
	rs.immediate().arc({ 500.0, 130.0 }, 30.0, two_pi<double>(), pi<double>() * 3.0 / 4.0);
	rs.immediate().new_sub_path();
	rs.dashes(dashes{ { 0.0, 10.0 }, 0.0 });
	rs.line_width(5.0);
	rs.line_cap(line_cap::round);
	rs.fill_immediate(rgba_color::blue());
	rs.stroke_immediate(rgba_color::orange());
	// Reset dashes to be a solid line.
	rs.reset_dashes();
	rs.line_cap(line_cap::butt);

	rs.immediate().clear();
	rs.immediate().curve_to({ 610.0, 400.0 }, { 660.0, 300.0 }, { 710.0, 400.0 });
	rs.immediate().close_path();
	rs.stroke_immediate(rgba_color::yellow_green());

	//auto radialFactory = radial_brush_factory({ 115.2, 102.4 }, 25.6, { 102.4, 102.4 }, 128.0);
	//radialFactory.add_color_stop(0.0, rgba_color::white());
	////radialFactory.add_color_stop(0.25, rgba_color::red());
	////radialFactory.add_color_stop(0.5, rgba_color::green());
	////radialFactory.add_color_stop(0.75, rgba_color::blue());
	//radialFactory.add_color_stop(1.0, rgba_color::black());
	//auto radialBrush = brush(radialFactory);
	//radialBrush.extend(extend::pad);
	//rs.immediate().clear();
	////rs.immediate().arc({ 128.0, 128.0 }, 76.8, 0.0, 2 * pi);
	//rs.immediate().rectangle({ 0.0, 0.0, 250.0, 250.0 });
	//rs.fill_immediate(radialBrush);

	timer = (timer > phaseTime * (phaseCount + 2)) ? 0.0 : timer + elapsedTimeInMilliseconds;
}

void draw_sort_visualization(surface& rs, double elapsedTimeInMilliseconds) {
	static double timer = 0.0;
	const double power = 3.0;
	const double lerpTime = 1250.0;
	const double phaseTime = lerpTime + 500.0;
	const double normalizedTime = min(fmod(timer, phaseTime) / lerpTime, 1.0);
	const double adjustment = (normalizedTime < 0.5) ? pow(normalizedTime * 2.0, power) / 2.0 :
		((1.0 - pow(1.0 - ((normalizedTime - 0.5) * 2.0), power)) * 0.5) + 0.5;
	const int elementCount = 12;
	const static auto vec = init_sort_steps(elementCount);
	const auto phaseCount = vec.size();
	assert(phaseCount > 0);
	const size_t x = min(static_cast<size_t>(timer / phaseTime), max(static_cast<size_t>(phaseCount - 1U), static_cast<size_t>(0U)));
	auto cornflowerBlueBrush = brush(solid_color_brush_factory(rgba_color::cornflower_blue()));
	rs.brush(cornflowerBlueBrush);
	rs.paint(); // Paint background.

	auto clextents = rs.clip_extents();
	const double radius = trunc(min(clextents.width() * 0.8 / elementCount, clextents.height() + 120.0) / 2.0);
	const double beginX = trunc(clextents.width() * 0.1);
	const double y = trunc(clextents.height() * 0.5);

	auto whiteBrush = brush(solid_color_brush_factory(rgba_color::white()));
	rs.brush(whiteBrush);
	rs.font_face("Segoe UI", font_slant::normal, font_weight::normal);
	rs.font_size(40.0);
	rs.show_text(string("Phase ").append(to_string(x + 1)).c_str(), { beginX, 50.0 });

	path_factory pf;

	for (size_t i = 0; i < elementCount; ++i) {
		pf.clear();
		const auto currVal = vec[x][i];
		if (x < phaseCount - 1) {
			const auto i2 = find(begin(vec[x + 1]), end(vec[x + 1]), currVal) - begin(vec[x + 1]);
			const auto x1r = radius * i * 2.0 + radius + beginX, x2r = radius * i2 * 2.0 + radius + beginX;
			const auto yr = y - ((i2 == static_cast<int>(i) ? 0.0 : (radius * 4.0 * (normalizedTime < 0.5 ? normalizedTime : 1.0 - normalizedTime)))
				* (i % 2 == 1 ? 1.0 : -1.0));
			const auto center = vector_2d{ trunc((x2r - x1r) * adjustment + x1r), trunc(yr) };
			pf.change_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi<double>() / 4.0) * matrix_2d::init_translate({ 0.0, 50.0 }));
			pf.change_origin(center);
			pf.arc_negative(center, radius - 3.0, half_pi<double>(), -half_pi<double>());
		}
		else {
			const vector_2d center{ radius * i * 2.0 + radius + beginX, y };
			pf.change_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi<double>() / 4.0));
			pf.change_origin(center);
			pf.arc_negative(center, radius - 3.0, half_pi<double>(), -half_pi<double>());
		}
		rs.path(path(pf));
		double greyColor = 1.0 - (currVal / (elementCount - 1.0));
		auto greyBrush = brush(solid_color_brush_factory({ greyColor, greyColor, greyColor, 1.0 }));
		rs.brush(greyBrush);
		rs.fill();
	}

	pf.clear();
	pf.change_origin({ 250.0, 450.0 });
	pf.change_matrix(matrix_2d::init_shear_x(0.5).scale({ 2.0, 1.0 }));
	pf.rectangle({ 200.0, 400.0, 100.0, 100.0 });
	rs.path(path(pf));
	auto redBrush = brush(solid_color_brush_factory(rgba_color::red()));
	rs.brush(redBrush);
	rs.line_width(3.0);
	rs.stroke();
	auto radialFactory = radial_brush_factory({ 250.0, 450.0 }, 0.0, { 250.0, 450.0 }, 80.0);
	radialFactory.add_color_stop(0.0, rgba_color::black());
	radialFactory.add_color_stop(0.25, rgba_color::red());
	radialFactory.add_color_stop(0.5, rgba_color::green());
	radialFactory.add_color_stop(0.75, rgba_color::blue());
	radialFactory.add_color_stop(1.0, rgba_color::white());
	auto radialBrush = brush(radialFactory);
	radialBrush.extend(extend::reflect);
	rs.brush(radialBrush);
	rs.fill();

	auto linearFactory = linear_brush_factory({ 510.0, 460.0 }, { 530.0, 480.0 });
	linearFactory.add_color_stop(0.0, rgba_color::chartreuse());
	linearFactory.add_color_stop(1.0, rgba_color::salmon());
	auto linearBrush = brush(linearFactory);
	linearBrush.extend(extend::repeat);
	pf.clear();
	pf.rectangle({ 500.0, 450.0, 100.0, 100.0 });
	pf.rectangle({ 525.0, 425.0, 50.0, 150.0 });
	rs.line_join(line_join::miter_or_bevel);
	rs.miter_limit(1.0);
	rs.line_width(10.0);
	rs.path(path(pf));
	rs.brush(redBrush);
	rs.stroke();
	rs.brush(linearBrush);
	rs.fill();

	pf.clear();
	pf.move_to({ 650.0, 400.0 });
	pf.rel_line_to({ 0.0, 100.0 });
	pf.rel_line_to({ 10.0, -100.0 });
	rs.line_join(line_join::miter);
	rs.path(path(pf));
	rs.brush(redBrush);
	rs.stroke();
	rs.brush(linearBrush);
	rs.fill();

	pf.clear();
	pf.move_to({ 430.0, 60.0 });
	pf.arc({ 500.0, 60.0 }, 30.0, pi<double>(), two_pi<double>());
	pf.line_to({ 570.0, 60.0 });
	pf.new_sub_path();
	pf.arc_negative({ 500.0, 130.0 }, 30.0, 0.0, pi<double>() * 3.0 / 4.0);
	pf.new_sub_path();
	rs.path(path(pf));
	rs.line_width(2.0);
	rs.brush(redBrush);
	rs.stroke();

	timer = (timer > phaseTime * (phaseCount + 2)) ? 0.0 : timer + elapsedTimeInMilliseconds;
}

namespace {

	//vector<vector_2d> curve_intersects_line_segment(const vector_2d& firstStart, const vector_2d& firstControl1, const vector_2d& firstControl2, const vector_2d& firstEnd,
	//	const vector_2d& secondStart, const vector_2d& secondEnd) {

	//}

	//vector<vector_2d> curve_intersects_curve(const vector_2d& firstStart, const vector_2d& firstControl1, const vector_2d& firstControl2, const vector_2d& firstEnd,
	//	const vector_2d& secondStart, const vector_2d& secondControl1, const vector_2d& secondControl2, const vector_2d& secondEnd) {

	//}

	//vector<vector<vector_2d>> curve_to_non_intersecting_sub_paths(const vector_2d& startPt, const vector_2d& controlPt1, const vector_2d& controlPt2, const vector_2d& endPt) noexcept;
	//vector<vector<vector_2d>> curve_to_non_intersecting_sub_paths(const vector_2d& startPt, const vector_2d& controlPt1, const vector_2d& controlPt2, const vector_2d& endPt) noexcept {

	//}

	//bool sub_paths_intersect(const vector<path_data_item>& lhs, const vector<path_data_item>& rhs) {

	//}

	//vector<vector<path_data_item>> sub_path_to_non_intersecting_sub_paths(const vector<path_data_item>& subPath) {
	//}

	// This function takes two paths and does the following:
	// 0. In the steps that follow, any time a sub path is broken up, the curves and lines of the resulting sub paths shall retain their original direction for proper fill_rule::winding fills.
	// 1. It creates 'vector<vector<path_data_item>> processedLhs'.
	// 2. It examines lhs and If lhs contains areas formed by intersections Then it breaks up lhs into non-intersecting sub paths and adds them to processedLhs, Else it adds lhs to processedLhs.
	// 3. It creates 'vector<vector<path_data_item>> processedRhs'.
	// 4. It examines rhs and If rhs contains areas formed by intersections Then it breaks up rhs into non-intersecting sub paths and adds them to processedRhs, Else it adds rhs to processedRhs.
	// 5. If lhs and rhs do not intersect Then it returns the concatenation of processedLhs and processedRhs.
	// 6. It creates 'vector<vector<path_data_item>> result'.
	// 7. For each sub path 'item' in processedLhs, If 'item' does not intersect with rhs Then 'item' is move appended to 'result'.
	// 8. Empty sub paths in processedLhs are erase-removed.
	// 9. For each sub path 'item' in processedRhs, If 'item' does not intersect with lhs Then 'item' is move appended to 'result'.
	// 10. Empty sub paths in processedRhs are erase-removed.
	// 11. Each sub path in processedLhs is checked against each sub path in processedRhs for intersection.
	// 12. If the sub paths intersect, then the sub path created by the intersection is appended to processedLhs and the sub paths that intersect are modified to exclude the intersecting area.
	// 13. When the sub path from processedLhs has been checked against all sub paths from processedRhs, add it (as modified) to result.
	// 14. When all sub paths in processedLhs (including any that are added along the way) are checked, return result.
	//vector<vector<path_data_item>> transformed_fill_only_sub_paths_to_non_intersecting_sub_paths(const vector<path_data_item>& lhs, const vector<path_data_item>& rhs) {

	//}

	//vector<tuple<bool, bool, vector<path_data_item>>> transformed_fill_only_sub_paths_to_winding_bool_even_odd_bool_transformed_non_intersecting_filled_sub_paths(const vector<vector<path_data_item>>& pathData) {
	//	// Need to 
	//}
}

void test_draw_circle(display_surface& ds, const vector_2d& coords, const radial_brush_factory& f) {
	// Can get t for s_fn via a simple magnitude. Determine the rotation angle of coords around center0, determine the point on circle 0 with that angle then the point on cirle 1 with that angle then get the distances from circle 0 pt to coords and from circle 0 pt to circle 1 pt and t = (dist(circ0, coords) / dist(circ0, circ1).
	auto circles = f.radial_circles();
	auto center0 = get<0>(circles);
	auto radius0 = get<1>(circles);
	auto center1 = get<2>(circles);
	auto radius1 = get<3>(circles);
	auto coordsAtZeroOrigin = coords - center0;
	double angle = 0.0;
	if (coordsAtZeroOrigin.x() != 0.0 || coordsAtZeroOrigin.y() != 0.0) {
		angle = atan2(coordsAtZeroOrigin.y(), coordsAtZeroOrigin.x());
	}
	auto circ0 = _Rotate_point_absolute_angle(center0, radius0, angle);
	auto circ1 = _Rotate_point_absolute_angle(center1, radius1, angle);
	auto dist_fn = [](const vector_2d& from, const vector_2d& to) -> double { return to.magnitude() > from.magnitude() ? (to - from).magnitude() : -(to - from).magnitude(); };
	if (_Almost_equal_relative(dist_fn(circ0, circ1), 0.0)) {
		return;
	}
	auto t = dist_fn(circ0, coords) / dist_fn(circ0, circ1);
	auto s_fn = [](double t) -> double { return (t - 0.0) / (1.0 - 0.0); };
	auto x_fn = [&circles](double s) -> double { auto x0 = get<0>(circles).x(); return x0 + s * (get<2>(circles).x() - x0); };
	auto y_fn = [&circles](double s) -> double { auto y0 = get<0>(circles).y(); return y0 + s * (get<2>(circles).y() - y0); };
	auto r_fn = [&circles](double s) -> double { auto r0 = get<1>(circles); return r0 + s * (get<3>(circles) -r0); };
	auto s = s_fn(t);
	auto x = x_fn(s); // center x of circle for s
	auto y = y_fn(s); // center y of circle for s
	auto r = r_fn(s); // radius of circle for s
	(void)x;
	(void)y;
	(void)r;
	auto cs0 = get<1>(f.color_stop(0));
	auto length = (circ1 - circ0).magnitude();
	rgba_color result{ 1.0 - ((r / length) * cs0.r()), 1.0 - ((r / length) * cs0.g()), 1.0 - ((r / length) * cs0.b()) };
}
