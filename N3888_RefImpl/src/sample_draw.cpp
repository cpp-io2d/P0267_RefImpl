#include "sample_draw.h"
#include "xio2dhelpers.h"
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <chrono>
#include <numeric>
#include <iomanip>
#include "test_renderer.h"

using namespace std;
using namespace std::chrono;
using namespace std::experimental;
using namespace std::experimental::io2d;
//using namespace not_proposed::test_renderer;

//// Declarations
void test_stroke_rules(display_surface& ds);
void test_path_functionality(display_surface& ds);
void draw_radial_circles(display_surface& ds);
//void test_draw_radial_circles(display_surface& ds);
//wostream& operator<<(wostream& os, const vector_2d& pt);
//vector<vector<int>> init_sort_steps(int count, unsigned long mtSeed = 1009UL);
//void draw_hello_world(display_surface& ds);
//void draw_test_compositing_operators(display_surface& ds, compositing_operator secondRectCompOp, compositing_operator firstRectCompOp = compositing_operator::over, bool clipToRects = false, bool clipToTriangle = false, bool strokePaths = false, bool mask = false, const rgba_color& backgroundColor = rgba_color::transparent_black(), const rgba_color& firstColor = rgba_color::red() * 0.8, const rgba_color& secondColor = rgba_color::teal() * 0.4);
//void draw_sort_visualization_immediate(display_surface& ds, double elapsedTimeInMilliseconds);
//void draw_sort_visualization(display_surface& ds, double elapsedTimeInMilliseconds);
//void test_compositing_operators_different_pixel_formats(display_surface& ds, compositing_operator co);
//void test_paint_surface_extend_modes(display_surface& ds, double elapsedTimeInMilliseconds);
//void test_fill_rules(display_surface& ds);
//void test_paint(display_surface& ds);
//void test_mask(display_surface& ds);
//void test_extend_none_on_boundary(display_surface& ds);
//void test_clip_transformation(display_surface& ds);

//
// Drawing entry point.
//
void sample_draw::operator()(display_surface& ds) {
	//ds.paint(rgba_color::cornflower_blue());

	//path_factory<> pf;
	//pf.new_path();
	////static auto previousTime = steady_clock::now();
	////auto currentTime = steady_clock::now();
	////auto elapsedTime = currentTime - previousTime;
	////previousTime = currentTime;
	//draw_sort_visualization_immediate(ds, ds.elapsed_draw_time());

	////test_clip_transformation(ds);
	////test_paint(ds);
	//test_stroke_rules(ds);
	test_path_functionality(ds);
	//draw_radial_circles(ds);
	////test_mask(ds);
	////test_extend_none_on_boundary(ds);

	////test_draw_radial_circles(ds);

	//
	////draw_test_compositing_operators(ds, compositing_operator::in, compositing_operator::over, true, false, false, true);
	//
	////test_compositing_operators_different_pixel_formats(ds, compositing_operator::out);
	//
	////static auto previousTime = steady_clock::now();
	////auto currentTime = steady_clock::now();
	////auto elapsedTime = currentTime - previousTime;
	////previousTime = currentTime;
	////test_paint_surface_extend_modes(ds, duration_cast<microseconds>(elapsedTime).count() / 1000.0);

	////test_fill_rules(ds);
}

//void test_clip_transformation(display_surface& ds) {
//	ds.save();
//
//	image_surface imgSfc{ format::argb32, 500, 500 };
//	imgSfc.paint(rgba_color::green());
//	imgSfc.immediate().abs_move({ 0.0, 250.0 });
//	imgSfc.immediate().abs_line({ 250.0, 0.0 });
//	imgSfc.immediate().abs_line({ 500.0,250.0 });
//	imgSfc.immediate().abs_line({ 250.0,500.0 });
//	imgSfc.immediate().close_path();
//	imgSfc.fill_immediate(rgba_color::white());
//
//	ds.matrix(matrix_2d::init_translate({ 0.0, 0.0 }));
//	//ds.matrix(matrix_2d::init_translate({ 100.0, 100.0 }));
//	ds.immediate().clear();
//	ds.immediate().rectangle({ 0.0, 0.0, 500.0, 500.0 });
//	ds.clip_immediate();
//
//	ds.matrix(matrix_2d::init_translate({ 100.0, 100.0 }));
//	//ds.matrix(matrix_2d::init_translate({ 0.0, 0.0 }));
//	//ds.immediate().clear();
//	//ds.immediate().rectangle({ 0.0, 0.0, 500.0, 500.0 });
//	ds.paint(imgSfc);
//
//	ds.restore();
//}
//
//void test_extend_none_on_boundary(display_surface& ds) {
//	image_surface imgSfc{ format::argb32, 500, 500 };
//	imgSfc.paint(rgba_color::green());
//	imgSfc.immediate().abs_move({ 0.0, 250.0 });
//	imgSfc.immediate().abs_line({ 250.0, 0.0 });
//	imgSfc.immediate().abs_line({ 500.0,250.0 });
//	imgSfc.immediate().abs_line({ 250.0,500.0 });
//	imgSfc.immediate().close_path();
//	imgSfc.fill_immediate(rgba_color::white());
//
//	ds.clear();
//	ds.immediate().clear();
//	ds.paint(rgba_color::red());
//	ds.immediate().rectangle({ 20.0, 20.0, static_cast<double>(ds.width()), static_cast<double>(ds.height()) });
//	ds.fill_immediate(imgSfc, matrix_2d::init_translate({ -20.0, -20.0 }), tiling::none, filter::bilinear);
//}
//
//void test_mask(display_surface& ds) {
//	image_surface imgSfc{ format::argb32, 500, 500 };
//	imgSfc.paint(rgba_color::white(), 0.5);
//	imgSfc.immediate().abs_move({ 0.0, 250.0 });
//	imgSfc.immediate().abs_line({ 250.0, 0.0 });
//	imgSfc.immediate().abs_line({ 500.0,250.0 });
//	imgSfc.immediate().abs_line({ 250.0,500.0 });
//	imgSfc.immediate().close_path();
//	imgSfc.fill_immediate(rgba_color::white());
//	//imgSfc.matrix(matrix_2d::init_translate({ -50.0, 50.0 }));
//	//imgSfc.matrix(matrix_2d::init_scale({ 0.5, 1.5 }));
//	//surface_brush_factory sbf(imgSfc);
//	//brush br(sbf);
//#if _Variable_templates_conditional_support_test
//	//br.matrix(matrix_2d::init_translate({ -50.0, -50.0 }).rotate(half_pi<double> * 0.25));
//#else
//	//br.matrix(matrix_2d::init_translate({ -50.0, -50.0 }).rotate(half_pi<double>() * 0.25));
//#endif
//	//br.filter(filter::nearest);
//	//br.tiling(tiling::none);
//
//	//radial_brush_factory rbf{ {250.0, 250.0}, 0.0, {250.0, 250.0}, 250.0 };
//	//rbf.add_color_stop(0.0, rgba_color::red());
//	//rbf.add_color_stop(0.5, rgba_color::lime() * 0.5);
//	//rbf.add_color_stop(1.0, rgba_color::blue());
//	//brush br{ rbf };
//	//br.tiling(tiling::repeat);
//	//br.filter(filter::nearest);
//
//	ds.save();
//	ds.clear();
//	ds.immediate().clear();
//	ds.paint(rgba_color::red());
//	ds.immediate().rectangle({ 0.0, 0.0, static_cast<double>(ds.width()), static_cast<double>(ds.height())});
//	//ds.matrix(matrix_2d::init_scale({ 0.5, 1.5 }));
//	//ds.mask_immediate(br, rgba_color::blue());
//#if _Variable_templates_conditional_support_test
//	ds.mask_immediate(imgSfc, rgba_color::blue(), matrix_2d::init_translate({ -50.0, -50.0 }).rotate(half_pi<double> * 0.25));
//#else
//	ds.mask_immediate(imgSfc, rgba_color::blue(), matrix_2d::init_translate({ -50.0, -50.0 }).rotate(half_pi<double>() * 0.25));
//#endif
//	//ds.fill_immediate(br);
//	ds.restore();
//}
//
//void test_paint(display_surface& ds) {
//	ds.save();
//	ds.clear();
//
//	image_surface imgSfc{ format::argb32, 500, 500 };
//	imgSfc.paint(rgba_color::green());
//	imgSfc.immediate().abs_move({ 0.0, 250.0 });
//	imgSfc.immediate().abs_line({ 250.0, 0.0 });
//	imgSfc.immediate().abs_line({ 500.0,250.0 });
//	imgSfc.immediate().abs_line({ 250.0,500.0 });
//	imgSfc.immediate().close_path();
//	imgSfc.fill_immediate(rgba_color::white());
//	auto m = matrix_2d::init_scale({ 1.5, 1.0 }).translate({ 20.0, 20.0 });// .invert().translate({ -10.0, -10.0 });
//	auto scsm = m;
//	//auto ucsm = matrix_2d::init_identity();
//	auto bcsm = matrix_2d::init_translate({ -10.0, -10.0 });
//	auto invScsm = scsm;
//	invScsm.invert();
//	auto invBcsm = bcsm;
//	invBcsm.invert();
//
//	////auto pt = m.invert().transform_point({ 0.0, 0.0 });
//	////auto pt2 = m.transform_point({ 10.0, 10.0 });
//	//auto pt = m.transform_point({ 0.0, 0.0 });
//	//auto pt2 = invScsm.transform_point({ 45.0, 30.0 });
//	//auto pt3 = vector_2d{ -26.6666666666666, -30.0 };
//	//auto pt4 = vector_2d{ -16.6666666666666, -20.0 };
//	//auto pt5 = vector_2d{ 45.0, 30.0 };
//	ds.matrix(m);
//	ds.paint(imgSfc, matrix_2d::init_translate({ -10.0, -10.0 })/*init_identity()*//*init_scale({ 1.0, 1.5 }).translate({ -20.0, -20.0 })*/, tiling::repeat, filter::nearest);
//	//ds.paint(rgba_color::red());
//	//auto br = brush(solid_color_brush_factory(rgba_color::red()));
//	//br.tiling(tiling::none);
//	//ds.brush(br);
//	ds.paint();
//
//
//	//auto lbf = linear_brush_factory({ 0.0, 0.0 }, { 50.0, 50.0 });
//	//lbf.add_color_stop(0.0, rgba_color::red());
//	//lbf.add_color_stop(0.5, rgba_color::lime());
//	//lbf.add_color_stop(1.0, rgba_color::blue());
//	//auto linBrush = brush(lbf);
//	//linBrush.tiling(tiling::repeat);
//#if _Variable_templates_conditional_support_test
//	//linBrush.matrix(matrix_2d::init_rotate(half_pi<double> / 2.0));
//#else
//	//linBrush.matrix(matrix_2d::init_rotate(half_pi<double>() / 2.0));
//#endif
//	//ds.immediate().rectangle({ { 50.0, 50.0}, {500.0, 500.0} });
//	//ds.clip_immediate();
//#if _Variable_templates_conditional_support_test
//	//ds.matrix(matrix_2d::init_rotate(half_pi<double> / 2.0));
//#else
//	//ds.matrix(matrix_2d::init_rotate(half_pi<double>() / 2.0));
//#endif
//	//ds.brush(linBrush);
//	//ds.paint();
//
//	ds.restore();
//}
//
void test_stroke_rules(display_surface& ds) {
	ds.save();
	ds.clear();
	color_stop_group<> csg;
	//auto orng = rgba_color::orange();
	csg.emplace_back(0.0, rgba_color::orange());
	csg.emplace_back(0.25, rgba_color::red());
	csg.emplace_back(0.5, rgba_color::lime_green());
	csg.emplace_back(0.75, rgba_color::blue());
	csg.emplace_back(1.0, rgba_color::gray());
	brush linearGrad({ 0.0, 0.0 }, { 0.0, 100.0 }, csg);
	ds.brush(linearGrad);
	linearGrad.tiling(tiling::reflect);
	ds.paint(linearGrad);

	ds.immediate().clear();

	//ds.line_width(40.0);
	//ds.line_cap(line_cap::butt);
	//ds.line_join(line_join::miter_or_bevel);
#if _Variable_templates_conditional_support_test
	//ds.immediate().arc({ ds.width() / 2.0, ds.height() / 2.0 }, 200.0, 0.0, two_pi<double>);
#else
	//ds.immediate().arc({ ds.width() / 2.0, ds.height() / 2.0 }, 200.0, 0.0, two_pi<double>());
#endif
#if _Variable_templates_conditional_support_test
	//ds.matrix(matrix_2d::init_translate({ ds.width() / 2.0, ds.height() / 2.0 }).rotate(half_pi<double> / 2.0).scale({ 0.5, 1.0 }).translate({ -ds.width() / 2.0, -ds.height() / 2.0 }));
#else
	//ds.matrix(matrix_2d::init_translate({ ds.width() / 2.0, ds.height() / 2.0 }).rotate(half_pi<double>() / 2.0).scale({ 0.5, 1.0 }).translate({ -ds.width() / 2.0, -ds.height() / 2.0 }));
#endif
	ds.dashes(nullvalue);
	ds.line_width(12.0);
	ds.immediate().move_to({ 0.0, 199.0 });
	ds.immediate().line_to({ 1280.9, 199.0 });
	ds.stroke_immediate(rgba_color::cornflower_blue());
	ds.immediate().clear();

	ds.line_width(40.0);
	dashes dsh(vector<double>{ 40.0, 50.0, 40.0, 50.0, 40.0, 50.0, 40.0, 50.0, 40.0, 50.0 }, 150.0);
	ds.dashes(dsh);
	ds.line_cap(line_cap::round);
	ds.line_join(line_join::miter_or_bevel);
	ds.immediate().move_to({ 700.0, 200.0 });
	ds.immediate().close_path();

	ds.line_width(40.0);
	ds.line_cap(line_cap::round);
	ds.line_join(line_join::miter_or_bevel);
	ds.immediate().move_to({ 200.0, 200.0 });
	ds.immediate().rel_line_to({ 0.0, 100.0 });
	ds.immediate().move_to({ 200.0, 335.0 });
	ds.immediate().rel_line_to({ 0.0, 200.0 });

#if _Variable_templates_conditional_support_test
	//ds.matrix(matrix_2d::init_scale({ 0.5, 1.0 }).rotate(half_pi<double> / 2.0));
#else
	//ds.matrix(matrix_2d::init_scale({ 0.5, 1.0 }).rotate(half_pi<double>() / 2.0));
#endif
#if _Variable_templates_conditional_support_test
	//ds.matrix(matrix_2d::init_rotate(half_pi<double> / 2.0).scale({ 0.5, 1.0 }));
#else
	//ds.matrix(matrix_2d::init_rotate(half_pi<double>() / 2.0).scale({ 0.5, 1.0 }));
#endif
	//ds.immediate().rel_move({ 20.0, 0.0 });
	//ds.immediate().rel_move({ 0.0, 10.0 });
	//ds.immediate().close_path();
	//ds.immediate().rel_line({ 5.0, 10.0 });
	//ds.immediate().rel_line({ -20.0, 0.0 });
	ds.stroke_immediate(rgba_color::black());

	ds.restore();
}

//void test_fill_rules(display_surface& ds) {
//	ds.clear();
//	auto prevFr = ds.fill_rule();
//
//	bool clockwise = true;
//
//	auto rect = rectangle{ 10.0, 10.0, 120.0, 90.0 };
//
//	ds.fill_rule(fill_rule::winding);
//	clockwise = true;
//	ds.immediate().clear();
//	rect.top_left({ 10.0, 10.0 });
//	ds.immediate().rectangle(rect, clockwise);
//	rect.top_left({ 50.0, 40.0 });
//	ds.immediate().rectangle(rect, clockwise);
//	ds.fill_immediate(rgba_color::red() * 0.5);
//
//	ds.immediate().clear();
//	rect.top_left({ 10.0, 150.0 });
//	ds.immediate().rectangle(rect, clockwise);
//	rect.top_left({ 50.0, 190.0 });
//	clockwise = false;
//	ds.immediate().rectangle(rect, clockwise);
//	ds.fill_immediate(rgba_color::red() * 0.5);
//
//	ds.fill_rule(fill_rule::even_odd);
//	clockwise = true;
//	ds.immediate().clear();
//	rect.top_left({ 190.0, 10.0 });
//	ds.immediate().rectangle(rect, clockwise);
//	rect.top_left({ 240.0, 40.0 });
//	ds.immediate().rectangle(rect, clockwise);
//	ds.fill_immediate(rgba_color::red() * 0.5);
//
//	ds.immediate().clear();
//	rect.top_left({ 190.0, 150.0 });
//	ds.immediate().rectangle(rect, clockwise);
//	rect.top_left({ 240.0, 190.0 });
//	clockwise = false;
//	ds.immediate().rectangle(rect, clockwise);
//	ds.fill_immediate(rgba_color::red() * 0.5);
//
//	ds.fill_rule(prevFr);
//}
//
//void test_paint_surface_extend_modes(display_surface& ds, double elapsedTimeInMilliseconds) {
//	static image_surface imgSfc{ format::argb32, 120, 90 };
//	static bool imgSfcInitialized = false;
//	if (!imgSfcInitialized) {
//		imgSfc.paint(rgba_color::red());
//		
//		imgSfc.immediate().abs_move({ 60.0, 0.0 });
//		imgSfc.immediate().abs_line({ 120.0, 0.0 });
//		imgSfc.immediate().abs_line({ 120.0, 90.0 });
//		imgSfc.immediate().abs_line({ 0.0, 90.0 });
//		imgSfc.immediate().abs_line({ 0.0, 45.0 });
//		imgSfc.immediate().abs_line({ 60.0, 45.0 });
//		imgSfc.immediate().close_path();
//		imgSfc.clip_immediate();
//		imgSfc.paint(rgba_color::yellow());
//		
//		imgSfc.immediate().clear();
//		imgSfc.immediate().abs_move({ 0.0, 45.0 });
//		imgSfc.immediate().abs_line({ 120.0, 45.0 });
//		imgSfc.immediate().abs_line({ 120.0, 90.0 });
//		imgSfc.immediate().abs_line({ 0.0, 90.0 });
//		imgSfc.immediate().close_path();
//		imgSfc.clip_immediate();
//		imgSfc.paint(rgba_color::green());
//
//		imgSfc.immediate().clear();
//		imgSfc.immediate().abs_move({ 60.0, 45.0 });
//		imgSfc.immediate().abs_line({ 120.0, 45.0 });
//		imgSfc.immediate().abs_line({ 120.0, 90.0 });
//		imgSfc.immediate().abs_line({ 60.0, 90.0 });
//		imgSfc.immediate().close_path();
//		imgSfc.clip_immediate();
//		imgSfc.paint(rgba_color::blue());
//		imgSfcInitialized = true;
//	}
//	static double totalElapsedTime = 0.0;
//	ds.compositing_operator(compositing_operator::source);
//	ds.immediate().rectangle({ 400.0, 0.0, 100.0, 100.0 });
//	ds.fill_immediate(rgba_color::orange());
//	ds.immediate().clear();
//	if (totalElapsedTime < 1000.0) {
//		// Do nothing.
//	}
//	else {
//		if (totalElapsedTime < 3000.0) {
//			ds.paint(imgSfc);
//		}
//		else {
//			ds.paint(imgSfc, matrix_2d::init_identity(), tiling::repeat);
//		}
//	}
//	totalElapsedTime += elapsedTimeInMilliseconds;
//}
//
//void test_compositing_operators_different_pixel_formats(display_surface& ds, compositing_operator co) {
//	image_surface srcSfc{ format::a8, 120, 90 };
//	image_surface dstSfc{ format::argb32, 120, 90 };
//	srcSfc.clear();
//	srcSfc.paint(rgba_color::blue(), 0.6);
//	dstSfc.clear();
//	dstSfc.paint(rgba_color::lime(), 0.4);
//	ds.clear();
//	
//	//auto data = srcSfc.data();
//	//ds.paint(rgba_color::white());
//	ds.compositing_operator(compositing_operator::over);
//	ds.immediate().rectangle({ 10.0, 10.0, 120.0, 90.0 });
//	ds.fill_immediate(srcSfc, matrix_2d::init_translate({ -10.0, -10.0 }));
//	ds.compositing_operator(co);
//	ds.immediate().clear();
//	ds.immediate().rectangle({ 50.0, 40.0, 120.0, 90.0 });
//	ds.fill_immediate(dstSfc, matrix_2d::init_translate({ -50.0, -40.0 }));
//}
//
//void test_draw_radial_circles(display_surface& ds) {
//	ds.paint(rgba_color::cornflower_blue());
//	ds.fill_rule(fill_rule::winding);
//	ds.matrix(matrix_2d::init_identity());
//	auto radialFactory = radial_brush_factory();
//	radialFactory.add_color_stop(0.0, rgba_color::white());
//	radialFactory.add_color_stop(0.25, rgba_color::red());
//	radialFactory.add_color_stop(0.5, rgba_color::green());
//	radialFactory.add_color_stop(0.75, rgba_color::blue());
//	//radialFactory.add_color_stop(1.0, rgba_color::black());
//	radialFactory.add_color_stop(1.0, rgba_color::black());
//	//radialFactory.radial_circles({ 400.0, 200.0 }, 100.0, { 600.0, 200.0 }, 50.0);
//	vector_2d center0 = { 150.0, 150.0 }/*{ 200.5, 300.0 }*/;
//	double radius0 = 10.0;
//	vector_2d center1 = { 300.0, 300.0 };
//	double radius1 = 100.0;
//	radialFactory.radial_circles(center0, radius0, center1, radius1);
//	auto extendMode = tiling::reflect;
//	auto radialBrush = brush(radialFactory);
//	radialBrush.tiling(extendMode);
//	path_factory<> pf;
//	rectangle drawArea = { { 100.0, 100.0 }, { 500.0, 500.0 } };
//	pf.rectangle(drawArea);
//	path_group p(pf);
//	ds.path_group(p);
//	ds.brush(radialBrush);
//	ds.fill();
//
//	auto dx = 500.0;
//	auto dy = 0.0;
//	vector_2d delta{ dx, dy };
//	center0 += delta;
//	center1 += delta;
//	radialFactory.radial_circles(center0, radius0, center1, radius1);
//	drawArea.x(drawArea.x() + dx);
//	drawArea.y(drawArea.y() + dy);
//	render_fill_rect_radial_gradient(ds, drawArea, radialFactory, extendMode);
//}
#include "test_process.h"

void test_path_functionality(display_surface& ds) {
	// Clear to background color.
	ds.paint(rgba_color::cornflower_blue());
	ds.brush(brush{ rgba_color::red() });
	//ds.fill_rule(fill_rule::even_odd);
	path_factory<> pf{};
	//void move_to(const vector_2d& pt) noexcept;
	vector_2d v, cpt1, cpt2, ept;
	v = { 10.0, 10.0 };
	pf.move_to(v);
	//void rel_move_to(const vector_2d& dpt) noexcept;
	v = { 30.0, 0.0 };
	pf.rel_move_to(v);
	//void line_to(const vector_2d& pt) noexcept;
	v = { 80.0, 10.0 };
	pf.line_to(v);
	//void rel_line_to(const vector_2d& dpt) noexcept;
	v = { 0.0, 40.0 };
	pf.rel_line_to(v);
	//void close_path() noexcept;
	pf.close_path();

	//void new_path() noexcept;
	pf.new_path();
	v = { 200.0, 20.0 };
	//pf.move_to(v);
	pf.line_to(v); // Should behave as a move_to.
	cpt1 = { 300.0, 60.0 };
	cpt2 = { 100.0, 100.0 };
	ept = { 200.0, 140.0 };
	pf.cubic_curve_to(cpt1, cpt2, ept);
	pf.new_path();

	v = { 30.0, 300.0 };
	pf.move_to(v);
	vector_2d qcpt = { 100.0, 230.0 };
	ept = { 170.0, 300.0 };
	pf.quadratic_curve_to(qcpt, ept);

	pf.new_path();
	pf.arc_clockwise(circle{ { 600.0, 100.0 }, 50.0 }, 0.0, half_pi<double>);
	pf.new_path();
	pf.arc_counterclockwise(circle{ { 600.0, 300.0 }, 50.0 }, 0.0, half_pi<double>);
	pf.new_path();
	pf.arc_clockwise(circle{ { 300.0, 300.0 }, 50.0 }, 0.0, two_pi<double>);

	pf.new_path();
	pf.transform_matrix(matrix_2d::init_rotate(half_pi<double> / 2.0));
	pf.rectangle(rectangle{ 500.0, 300.0, 200.0, 100.0 });

	ds.path_group(path_group(pf));
	ds.stroke();

	pf.clear();

	pf.new_path();
	pf.transform_matrix(matrix_2d::init_rotate(half_pi<double> / 2.0));
	pf.ellipse({ 200.0, 200.0 }, 80.0, 40.0);
	pf.transform_matrix(matrix_2d{});
	pf.move_to({ 200.0, 0.0 });
	pf.line_to({ 200.0, 800.0 });

	auto vecprocessed = test_process::process_path_data(pf);
	ds.path_group(path_group{ pf });
	ds.brush(rgba_color::lime());
	ds.stroke();

	//constexpr auto dClr = rgba_color(1.0, 1.0, 1.0);
	//constexpr auto fClr = rgba_color(0.5f, 1.0f, 0.0f, 0.25f);
	//constexpr circle circ{ {20.0, 20.0}, 10.0 };
	//constexpr ellipse ell{ circ };
	//constexpr double ellx = ell.x_axis();
	////constexpr ellipse ell2 = circ; // Implicit conversion barred, so this is invalid.

	//void arc_clockwise(const vector_2d& center, double radius, double angle1,
	//	double angle2) noexcept;
	//void arc_counterclockwise(const vector_2d& center, double radius,
	//	double angle1, double angle2) noexcept;
	//void cubic_curve_to(const vector_2d& pt0, const vector_2d& pt1,
	//	const vector_2d& pt2) noexcept;
	//void quadratic_curve_to(const vector_2d& pt0, const vector_2d& pt1)
	//	noexcept;
	//void rectangle(const experimental::io2d::rectangle& r) noexcept;
	//void rel_cubic_curve_to(const vector_2d& dpt0, const vector_2d& dpt1,
	//	const vector_2d& dpt2) noexcept;
	//void rel_quadratic_curve_to(const vector_2d& dpt0, const vector_2d& dpt1)
	//	noexcept;
	//void transform_matrix(const matrix_2d& m) noexcept;
	//void origin(const vector_2d& pt) noexcept;


}

void draw_radial_circles(display_surface& ds) {
	// Clear to background color.
	ds.paint(rgba_color::cornflower_blue());
	ds.fill_rule(fill_rule::winding);
	ds.matrix(matrix_2d::init_identity());
	brush radialBrush{ {{ 200.5, 300.0 }, 0.0}, {{ 300.0, 300.0 }, 100.0 }, {
		{ 0.0, rgba_color::white() }, { 0.25, rgba_color::red() },
		{ 0.5, rgba_color::green() }, { 0.75, rgba_color::blue() }, { 1.0, rgba_color::black() } } };
	//auto radialFactory = radial_brush_factory();
	//radialFactory.add_color_stop(0.0, rgba_color::white());
	//radialFactory.add_color_stop(0.25, rgba_color::red());
	//radialFactory.add_color_stop(0.5, rgba_color::green());
	//radialFactory.add_color_stop(0.75, rgba_color::blue());
	//radialFactory.add_color_stop(1.0, rgba_color::black());
	//radialFactory.add_color_stop(1.0, rgba_color::black());
	//radialFactory.radial_circles({ 400.0, 200.0 }, 100.0, { 600.0, 200.0 }, 50.0);

	//radialFactory.radial_circles({ 200.5, 300.0 }, 0.0, { 300.0, 300.0 }, 100.0);
	//auto radialBrush = brush(radialFactory);
	radialBrush.tiling(tiling::repeat);
	path_factory<> pf;
	//pf.rectangle({ { 100.0, 100.0 }, { 500.0, 500.0 } });
	pf.move_to({ 100.0, 100.0 });
	pf.line_to({ 500.0, 100.0 });
	pf.transform_matrix(matrix_2d::init_shear_x(0.25));
	pf.line_to({ 500.0, 500.0 });
	pf.close_path();
	pf.transform_matrix(matrix_2d::init_identity());
	pf.line_to({ 50.0, 150.0 });
	pf.move_to({ 520.0, 520.0 });
	pf.line_to({ 600.0, 600.0 });
	pf.transform_matrix(matrix_2d::init_scale({ 2.0, 1.0 }));
#if _Variable_templates_conditional_support_test
	pf.arc_clockwise({ 300.0, 700.0 }, 100.0, three_pi_over_two<double>, two_pi<double>);
#else
	pf.arc_clockwise({ 300.0, 700.0 }, 100.0, three_pi_over_two<double>(), two_pi<double>());
#endif
	pf.transform_matrix(matrix_2d::init_identity());
	pf.move_to({ 520.0, 10.0 });
	pf.cubic_curve_to({ 480.0, 60.0 }, { 560.0, 60.0 }, { 520.0, 10.0 });
	path_group p(pf);
	ds.path_group(p);
	ds.brush(radialBrush);

	//// For debug inspection testing only; uncomment if needed.
	//auto fe = ds.fill_extents();
	//auto se = ds.stroke_extents();
	//vector_2d pt{ 110.0, 300.0 };
	//auto inFill = ds.in_fill(pt);
	//// End for debug inspection testing only.

	ds.fill();
	ds.brush(brush(rgba_color::red()));
	ds.stroke();
	pf.clear();
	pf.new_path();
#if _Variable_templates_conditional_support_test
	pf.arc_clockwise({ 900.0, 200.0 }, 50.0, 0.0, two_pi<double>);
#else
	pf.arc({ 900.0, 200.0 }, 50.0, 0.0, two_pi<double>());
#endif
	pf.new_path();
#if _Variable_templates_conditional_support_test
	pf.arc_counterclockwise({ 900.0, 200.0 }, 75.0, 0.0, two_pi<double>);
#else
	pf.arc_counterclockwise({ 900.0, 200.0 }, 75.0, 0.0, two_pi<double>());
#endif
	pf.new_path();
#if _Variable_templates_conditional_support_test
	pf.arc_clockwise({ 900.0, 200.0 }, 100.0, 0.0, two_pi<double>);
#else
	pf.arc_clockwise({ 900.0, 200.0 }, 100.0, 0.0, two_pi<double>());
#endif
	pf.new_path();
#if _Variable_templates_conditional_support_test
	pf.arc_counterclockwise({ 900.0, 200.0 }, 125.0, 0.0, two_pi<double>);
#else
	pf.arc_counterclockwise({ 900.0, 200.0 }, 125.0, 0.0, two_pi<double>());
#endif
	pf.new_path();
#if _Variable_templates_conditional_support_test
	pf.arc_clockwise({ 900.0, 200.0 }, 150.0, 0.0, two_pi<double>);
#else
	pf.arc_clockwise({ 900.0, 200.0 }, 150.0, 0.0, two_pi<double>());
#endif
	p = path_group(pf);
	ds.path_group(p);
	ds.fill();
	ds.matrix(matrix_2d::init_translate({ 0.0, 310.0 }));
	ds.path_group(p);
	ds.fill_rule(fill_rule::even_odd);
	ds.fill();

	//render_ellipse(ds, { 200.0, 600.0 }, 250.0, 100.0, rgba_color(0.0, 1.0, 1.0, 1.0));

	//radialFactory.radial_circles({ 200.5, 300.0 }, 0.0, { 300.0, 300.0 }, 100.0);
	//auto radialBrush = brush(radialFactory);
	//radialBrush.tiling(tiling::repeat);
	////radialBrush.matrix(matrix_2d::init_scale({ 2.0, 2.0 }));
	//ds.immediate().clear();
	//ds.immediate().rectangle({ { 100.0, 100.0 }, { 500.0, 500.0 } });
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 115.2, 102.4 }, 25.6, { 102.4, 102.4 }, 128.0);
	//radialBrush = brush(radialFactory);
	//radialBrush.tiling(tiling::pad);
	//ds.immediate().clear();
	//ds.immediate().arc({ 128.0, 128.0 }, 76.8, 0.0, 2 * pi);
	////ds.immediate().rectangle({ 0.0, 0.0, 250.0, 250.0 });
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 400.0, 200.0 }, 100.0, { 600.0, 200.0 }, 100.0);
	//auto color = test_draw_circle(ds, { 400.0, 200.0 }, radialFactory);
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
	//	ds.immediate().clear();
	//	ds.immediate().rectangle({ { 200.0, 280.0 }, { 602.0, 520.0 } });
	//	ds.fill_immediate(brush(linearFactory));
	//}
	//
	//radialFactory.radial_circles({ 600.0, 200.0 }, 100.0, { 400.0, 200.0 }, 100.0);
	//ds.immediate().clear();
	//ds.immediate().rectangle({ { 280.0, 80.0 }, { 720.0, 320.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.tiling(tiling::pad);
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 400.0, 450.0 }, 100.0, { 600.0, 450.0 }, 100.0);
	//ds.immediate().clear();
	//ds.immediate().rectangle({ { 280.0, 330.0 }, { 720.0, 570.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.tiling(tiling::none);
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 1000.0, 200.0 }, 100.0, { 1000.0, 200.0 }, 20.0);
	//ds.immediate().clear();
	//ds.immediate().rectangle({ { 880.0, 80.0 }, { 1120.0, 320.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.tiling(tiling::reflect);
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 1000.0, 450.0 }, 20.0, { 1000.0, 450.0 }, 100.0);
	//ds.immediate().clear();
	//ds.immediate().rectangle({ { 880.0, 330.0 }, { 1120.0, 570.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.tiling(tiling::repeat);
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 105.0, 100.0 }, 0.0, { 200.0, 100.0 }, 100.0);
	//ds.immediate().clear();
	//ds.immediate().rectangle({ { 0.0, 0.0 }, { 520.0, 200.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.tiling(tiling::repeat);
	//ds.fill_immediate(radialBrush);
	//
	//
	//radialFactory.radial_circles({ 200.0, 200.0 }, 100.0, { 400.0, 200.0 }, 100.0);
	//ds.immediate().clear();
	//ds.immediate().rectangle({ { 80.0, 80.0 }, { 520.0, 320.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.tiling(tiling::none);
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 200.0, 450.0 }, 100.0, { 400.0, 450.0 }, 100.0);
	//ds.immediate().clear();
	//ds.immediate().rectangle({ { 80.0, 330.0 }, { 520.0, 570.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.tiling(tiling::pad);
	//ds.fill_immediate(radialBrush);
	//
	////radialFactory.radial_circles({ 200.0, 450.0 }, 100.0, { 400.0, 450.0 }, 100.0);
	////ds.immediate().clear();
	////ds.immediate().rectangle({ { 80.0, 330.0 }, { 520.0, 570.0 } });
	////radialBrush = brush(radialFactory);
	////radialBrush.tiling(tiling::pad);
	////ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 700.0, 200.0 }, 100.0, { 900.0, 200.0 }, 100.0);
	//ds.immediate().clear();
	//ds.immediate().rectangle({ { 580.0, 80.0 }, { 1020.0, 320.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.tiling(tiling::reflect);
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 700.0, 450.0 }, 100.0, { 900.0, 450.0 }, 100.0);
	//ds.immediate().clear();
	//ds.immediate().rectangle({ { 580.0, 330.0 }, { 1020.0, 570.0 } });
	//radialBrush = brush(radialFactory);
	//radialBrush.tiling(tiling::repeat);
	//ds.fill_immediate(radialBrush);
}

//wostream& operator<<(wostream& os, const vector_2d& pt) {
//	os << L"(" << pt.x() << L"," << pt.y() << L")";
//	return os;
//}
//
//vector<vector<int>> init_sort_steps(int count, unsigned long mtSeed) {
//	vector<vector<int>> result;
//	result.push_back([count, mtSeed]() {
//		vector<int> init;
//		for (int i = 0; i < count; ++i) {
//			init.push_back(i);
//		}
//		mt19937 rng(mtSeed);
//		shuffle(begin(init), end(init), rng);
//		return init;
//	}());
//	bool notSorted = true;
//	while (notSorted) {
//		vector<int> curr(result.back());
//		const auto size = curr.size();
//		notSorted = false;
//		for (auto i = 0U; i < size - 1; ++i) {
//			if (curr[i] > curr[i + 1]) {
//				notSorted = true;
//				auto temp = curr[i + 1];
//				curr[i + 1] = curr[i];
//				curr[i] = temp;
//			}
//		}
//		if (notSorted) {
//			result.push_back(curr);
//		}
//	}
//	return result;
//}
//
//void init_mask_surface(image_surface&);
//void init_mask_surface(image_surface& imsfc) {
//	// { 30.0, 25.0, 70.0, 70.0 } - clip
//	imsfc.immediate().abs_move({ 40.0, 0.0 });
//	imsfc.immediate().rel_cubic_curve({ -35.0, 70.0 }, { -35.0, 70.0 }, { 0.0, 140.0 });
//	imsfc.immediate().rel_cubic_curve({ 35.0, -70.0 }, { 35.0, -70.0 }, { 0.0, -140.0 });
//	imsfc.brush({ rgba_color::white() });
//	imsfc.fill_immediate();
//}
//
//void draw_hello_world(display_surface& ds) {
//	//ds.render_text("Hello world", { 100.0, 100.0 }, brush(rgba_color::white()));
//}
//
//// For testing purposes only.
//void draw_test_compositing_operators(display_surface& ds, compositing_operator secondRectCompOp, compositing_operator firstRectCompOp, bool clipToRects, bool clipToTriangle, bool strokePaths, bool mask, const rgba_color& backgroundColor, const rgba_color& firstColor, const rgba_color& secondColor) {
//	// Parameter validation.
//	if (clipToRects && clipToTriangle) {
//		throw invalid_argument("clipToRects and clipToTriangle cannot both be set to true.");
//	}
//	ds.save();
//
//	auto backgroundBrush = brush(backgroundColor);
//	auto firstBrush = brush(firstColor);
//	auto secondBrush = brush(secondColor);
//
//	auto pb = path_factory<>();
//
//	pb.rectangle({ 10.0, 10.0, 120.0, 90.0 });
//	auto firstRectPath = path_group(pb);
//
//	pb.clear();
//	pb.rectangle({ 50.0, 40.0, 120.0, 90.0 });
//	auto secondRectPath = path_group(pb);
//
//	pb.clear();
//	pb.rectangle({ 30.0, 25.0, 70.0, 70.0 });
//	auto bothRectsClipPath = path_group(pb);
//
//	pb.clear();
//	pb.abs_move({ 85.0, 25.0 });
//	pb.abs_line({ 150.0, 115.0 });
//	pb.abs_line({ 30.0, 115.0 });
//	pb.close_path();
//	auto triangleClipPath = path_group(pb);
//
//	ds.brush(backgroundBrush);
//	ds.compositing_operator(compositing_operator::clear);
//	ds.paint();
//
//	ds.brush(firstBrush);
//	ds.compositing_operator(firstRectCompOp);
//	ds.path_group(firstRectPath);
//	ds.fill();
//
//	ds.save(); // Preserve old clip.
//	if (clipToRects) {
//		ds.clip(bothRectsClipPath);
//	}
//
//	if (clipToTriangle) {
//		ds.clip(triangleClipPath);
//	}
//
//	ds.path_group(secondRectPath);
//	ds.compositing_operator(secondRectCompOp);
//	ds.brush(secondBrush);
//	if (mask) {
//		static image_surface maskSurface(format::a8, 200, 200);
//		static once_flag drawMaskOnceFlag;
//		static bool maskSurfaceInitialized = false;
//		if (!maskSurfaceInitialized) {
//			init_mask_surface(maskSurface);
//			maskSurfaceInitialized = true;
//		}
//		//function<void(bool&)> fn([](bool & msinit) { msinit = true; });
//		//call_once(drawMaskOnceFlag,
//		//	fn,
//		//	maskSurfaceInitialized);
//		//	//init_mask_surface,
//		////	[](image_surface&& imsfc) -> image_surface&& {
//		////	// { 30.0, 25.0, 70.0, 70.0 } - clip
//		////	imsfc.immediate().abs_move({ 40.0, 0.0 });
//		////	imsfc.immediate().rel_cubic_curve({ -35.0, 70.0 }, { -35.0, 70.0 }, { 0.0, 140.0 });
//		////	imsfc.immediate().rel_cubic_curve({ 35.0, -70.0 }, { 35.0, -70.0 }, { 0.0, -140.0 });
//		////	imsfc.brush({ rgba_color::white() });
//		////	imsfc.fill_immediate();
//		////	return move(imsfc);
//		////}, 
//		//	//move(maskSurface));
//		ds.mask(maskSurface);
//	}
//	else {
//		ds.fill();
//	}
//
//	ds.restore(); // Restore old clip
//
//	if (strokePaths) {
//		ds.compositing_operator(compositing_operator::source);
//		ds.line_width(2.0);
//
//		ds.path_group(firstRectPath);
//		ds.brush(brush(solid_color_brush_factory(rgba_color::teal())));
//		ds.stroke();
//
//		ds.path_group(secondRectPath);
//		ds.brush(brush(solid_color_brush_factory(rgba_color::red())));
//		ds.stroke();
//
//		if (clipToTriangle) {
//			ds.path_group(triangleClipPath);
//			ds.brush(brush(solid_color_brush_factory(rgba_color::yellow())));
//			ds.stroke();
//		}
//	}
//
//	ds.restore();
//}
//
//void draw_sort_visualization_immediate(display_surface& ds, double elapsedTimeInMilliseconds) {
//	static double timer = 0.0;
//	const double power = 3.0;
//	const double lerpTime = 1250.0;
//	const double phaseTime = lerpTime + 500.0;
//	const double normalizedTime = min(fmod(timer, phaseTime) / lerpTime, 1.0);
//	const double adjustment = (normalizedTime < 0.5) ? pow(normalizedTime * 2.0, power) / 2.0 :
//		((1.0 - pow(1.0 - ((normalizedTime - 0.5) * 2.0), power)) * 0.5) + 0.5;
//	const int elementCount = 12;
//	const static auto vec = init_sort_steps(elementCount);
//	const auto phaseCount = vec.size();
//	const size_t x = ::std::min(static_cast<size_t>(timer / phaseTime), ::std::max(static_cast<size_t>(phaseCount - 1U), static_cast<size_t>(0U)));
//
//	static deque<double> elapsedTimes(static_cast<size_t>(30), 1000.0 / ds.desired_frame_rate());
//	elapsedTimes.pop_front();
//	elapsedTimes.push_back(elapsedTimeInMilliseconds);
//
//	ds.paint(rgba_color::cornflower_blue()); // Paint background.
//
//	ds.immediate().clear();
//#if _Variable_templates_conditional_support_test
//	ds.immediate().arc({ 100.0, 100.0 }, 50.0, 0.0, half_pi<double>);
//#else
//	ds.immediate().arc({ 100.0, 100.0 }, 50.0, 0.0, half_pi<double>());
//#endif
//	auto initLineWidth = ds.line_width();
//	ds.line_width(8.0);
//	ds.stroke_immediate(rgba_color::black());
//	ds.immediate().clear();
//#if _Variable_templates_conditional_support_test
//	ds.immediate().arc_negative({ 300.0, 100.0 }, 50.0, 0.0, half_pi<double>);
//#else
//	ds.immediate().arc_negative({ 300.0, 100.0 }, 50.0, 0.0, half_pi<double>());
//#endif
//	ds.stroke_immediate(rgba_color::brown());
//	ds.immediate().clear();
//	ds.line_width(initLineWidth);
//
//	auto clextents = ds.clip_extents();
//	const double radius = trunc(min(clextents.width() * 0.8 / elementCount, clextents.height() + 120.0) / 2.0);
//	const double beginX = trunc(clextents.width() * 0.1);
//	const double y = trunc(clextents.height() * 0.5);
//
//	auto linearTest1 = linear_brush_factory({ 400.0, 400.0 }, { 400.0, 500.0 });
//	linearTest1.add_color_stop(0.0, rgba_color::black());
//	linearTest1.add_color_stop(0.3, rgba_color::yellow());
//	linearTest1.add_color_stop(0.5, rgba_color::blue());
//	linearTest1.add_color_stop(0.3, rgba_color::lime());
//	linearTest1.add_color_stop(0.5, rgba_color::black());
//	linearTest1.add_color_stop(0.7, rgba_color::purple());
//	linearTest1.add_color_stop(0.5, rgba_color::red());
//	//	linearTest1.add_color_stop(1.0, rgba_color::black());
//	linearTest1.add_color_stop(0.7, rgba_color::orange());
//	linearTest1.add_color_stop(0.8, rgba_color::green());
//	linearTest1.add_color_stop(0.8, rgba_color::yellow());
//	linearTest1.add_color_stop(1.0, rgba_color::white());
//	ds.immediate().rectangle({ 400.0, 400.0, 200.0, 200.0 });
//	ds.fill_immediate(brush(linearTest1));
//
//	ds.font_resource("Segoe UI", 40.0);
//	auto str = string("Phase ").append(to_string(x + 1));
//	ds.render_text(str, { beginX, 50.0 }, rgba_color::white());
//
//	for (size_t i = 0; i < elementCount; ++i) {
//		ds.immediate().clear();
//		const auto currVal = vec[x][i];
//		if (x < phaseCount - 1) {
//			const auto i2 = find(begin(vec[x + 1]), end(vec[x + 1]), currVal) - begin(vec[x + 1]);
//			const auto x1r = radius * i * 2.0 + radius + beginX, x2r = radius * i2 * 2.0 + radius + beginX;
//			const auto yr = y - ((i2 == static_cast<int>(i) ? 0.0 : (radius * 4.0 * (normalizedTime < 0.5 ? normalizedTime : 1.0 - normalizedTime)))
//				* (i % 2 == 1 ? 1.0 : -1.0));
//			const auto center = vector_2d{ trunc((x2r - x1r) * adjustment + x1r), trunc(yr) };
//#if _Variable_templates_conditional_support_test
//			ds.immediate().change_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi<double> / 4.0) * matrix_2d::init_translate({ 0.0, 50.0 }));
//#else
//			ds.immediate().change_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi<double>() / 4.0) * matrix_2d::init_translate({ 0.0, 50.0 }));
//#endif
//			ds.immediate().change_origin(center);
//#if _Variable_templates_conditional_support_test
//			ds.immediate().arc_negative(center, radius - 3.0, half_pi<double>, -half_pi<double>);
//#else
//			ds.immediate().arc_negative(center, radius - 3.0, half_pi<double>(), -half_pi<double>());
//#endif
//		}
//		else {
//			const vector_2d center{ radius * i * 2.0 + radius + beginX, y };
//#if _Variable_templates_conditional_support_test
//			ds.immediate().change_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi<double> / 4.0) * matrix_2d::init_translate({ 0.0, 50.0 }));
//#else
//			ds.immediate().change_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi<double>() / 4.0) * matrix_2d::init_translate({ 0.0, 50.0 }));
//#endif
//			ds.immediate().change_origin(center);
//#if _Variable_templates_conditional_support_test
//			ds.immediate().arc_negative(center, radius - 3.0, half_pi<double>, -half_pi<double>);
//#else
//			ds.immediate().arc_negative(center, radius - 3.0, half_pi<double>(), -half_pi<double>());
//#endif
//		}
//		double greyColor = 1.0 - (currVal / (elementCount - 1.0));
//		ds.fill_immediate({ greyColor, greyColor, greyColor, 1.0 });
//	}
//
//	ds.immediate().clear();
//	ds.immediate().change_origin({ 250.0, 450.0 });
//	ds.immediate().change_matrix(matrix_2d::init_shear_x(0.5).scale({ 2.0, 2.5 }));
//	ds.immediate().rectangle({ 200.0, 400.0, 100.0, 100.0 });
//	ds.line_width(3.0);
//	ds.stroke_immediate(rgba_color::red());
//	//auto radialFactory = radial_brush_factory({ 250.0, 450.0 }, 0.0, { 250.0, 450.0 }, 80.0);
//	//radialFactory.add_color_stop(0.0, rgba_color::black());
//	//radialFactory.add_color_stop(0.25, rgba_color::red());
//	//radialFactory.add_color_stop(0.5, rgba_color::green());
//	//radialFactory.add_color_stop(0.75, rgba_color::blue());
//	//radialFactory.add_color_stop(1.0, rgba_color::white());
//	//auto radialBrush = ds.create_brush(radialFactory);
//	//radialBrush.tiling(tiling::reflect);
//	//ds.fill_immediate(radialBrush);
//
//	//auto meshFactory = mesh_brush_factory();
//	//meshFactory.begin_patch();
//	//meshFactory.abs_move({ 0.0, 0.0 });
//	//meshFactory.curve({ 30.0, -30.0 }, { 60.0, 30.0 }, { 100.0, 0.0 });
//	//meshFactory.curve({ 60.0, 30.0 }, { 130.0, 60.0 }, { 100.0, 100.0 });
//	//meshFactory.curve({ 60.0, 70.0 }, { 30.0, 130.0 }, { 0.0, 100.0 });
//	//meshFactory.curve({ 30.0, 70.0 }, { -30.0, 30.0 }, { 0.0, 0.0 });
//	//meshFactory.corner_color(0, rgba_color::red());
//	//meshFactory.corner_color(1, rgba_color::lime());
//	//meshFactory.corner_color(2, rgba_color::blue());
//	//meshFactory.corner_color(3, rgba_color::yellow());
//	//meshFactory.end_patch();
//	//meshFactory.begin_patch();
//	//meshFactory.abs_move({ 100.0, 100.0 });
//	//meshFactory.abs_line({ 130.0, 130.0 });
//	//meshFactory.abs_line({ 130.0, 70.0 });
//	//meshFactory.corner_color(0, rgba_color::red());
//	//meshFactory.corner_color(1, rgba_color::lime());
//	//meshFactory.corner_color(2, rgba_color::blue());
//	//meshFactory.end_patch();
//	//auto meshBrush = brush(meshFactory);
//	//meshBrush.matrix(matrix_2d::init_translate({ -200.0, -400.0 }));
//	//ds.fill_immediate(meshBrush);
//
//	auto imgSfc = image_surface(format::argb32, 40, 40);
//	imgSfc.immediate().abs_move({ 0.0, 0.0 });
//	imgSfc.immediate().abs_line({ 40.0, 40.0 });
//	imgSfc.immediate().abs_line({ 0.0, 40.0 });
//	imgSfc.immediate().close_path();
//	imgSfc.paint(rgba_color::green());
//	imgSfc.fill_immediate(rgba_color::yellow());
//
//	auto sfcFactory = surface_brush_factory(imgSfc);
//	auto sfcBrush = brush(sfcFactory);
//	sfcBrush.tiling(tiling::repeat);
//	ds.immediate().clear();
//	ds.immediate().rectangle({ 500.0, 450.0, 100.0, 100.0 });
//	ds.immediate().rectangle({ 525.0, 425.0, 50.0, 150.0 });
//	ds.line_join(line_join::miter_or_bevel);
//	ds.miter_limit(1.0);
//	ds.line_width(10.0);
//	ds.stroke_immediate(rgba_color::red());
//	ds.fill_immediate(sfcBrush);
//
//	auto linearFactory = linear_brush_factory({ 510.0, 460.0 }, { 530.0, 480.0 });
//	linearFactory.add_color_stop(0.0, rgba_color::chartreuse());
//	linearFactory.add_color_stop(1.0, rgba_color::salmon());
//	auto linearBrush = brush(linearFactory);
//	linearBrush.tiling(tiling::repeat);
//	ds.immediate().clear();
//	ds.immediate().abs_move({ 650.0, 400.0 });
//	ds.immediate().rel_line({ 0.0, 100.0 });
//	ds.immediate().rel_line({ 10.0, -100.0 });
//	ds.line_join(line_join::miter);
//	ds.stroke_immediate(rgba_color::red());
//	ds.fill_immediate(linearBrush);
//
//	ds.immediate().clear();
//	ds.immediate().abs_move({ 430.0, 60.0 });
//#if _Variable_templates_conditional_support_test
//	ds.immediate().arc({ 500.0, 60.0 }, 30.0, pi<double>, two_pi<double>);
//#else
//	ds.immediate().arc({ 500.0, 60.0 }, 30.0, pi<double>(), two_pi<double>());
//#endif
//	ds.immediate().abs_line({ 570.0, 60.0 });
//	//	ds.immediate().new_sub_path();
//#if _Variable_templates_conditional_support_test
//	ds.immediate().arc({ 500.0, 130.0 }, 30.0, two_pi<double>, pi<double> * 3.0 / 4.0);
//#else
//	ds.immediate().arc({ 500.0, 130.0 }, 30.0, two_pi<double>(), pi<double>() * 3.0 / 4.0);
//#endif
//	ds.immediate().new_sub_path();
//	ds.dashes(dashes{ { 0.0, 10.0 }, 0.0 });
//	ds.line_width(5.0);
//	ds.line_cap(line_cap::round);
//	ds.fill_immediate(rgba_color::blue());
//	ds.stroke_immediate(rgba_color::orange());
//	// Reset dashes to be a solid line.
//	ds.dashes(nullopt);
//	ds.line_cap(line_cap::butt);
//
//	ds.immediate().clear();
//	ds.immediate().curve({ 610.0, 400.0 }, { 660.0, 300.0 }, { 710.0, 400.0 });
//	ds.immediate().close_path();
//	ds.stroke_immediate(rgba_color::yellow_green());
//	auto sumOfElapsedTimes = accumulate(begin(elapsedTimes), end(elapsedTimes), 0.0);
//	auto countOfElapsedTimes = static_cast<double>(elapsedTimes.size());
//	auto fps = 1000.0 / (sumOfElapsedTimes / countOfElapsedTimes);
//	stringstream fpsStr;
//	fpsStr << "FPS: " << setprecision(3) << fps;
//	
//	auto origM = ds.matrix();
//	
//	//ds.matrix(matrix_2d::init_scale({ 1.0, 0.5 }));
//	font_resource_factory frf{ "Segoe UI", font_slant::normal, font_weight::normal, matrix_2d::init_scale({40.0, 40.0}) };//, font_options{}, matrix_2d::init_scale({ 1.0, 1.5 }) };
//	ds.font_resource(experimental::io2d::font_resource{ frf });
//	auto gr = ds.font_resource().make_glyph_run(fpsStr.str(), { static_cast<double>(ds.width()) - 400.0, 50.0 });
//	//vector<glyph_run::glyph>::size_type idx = 0;
//	//gr.glyphs()[idx].x(gr.glyphs()[idx].x() - 20.0);
//	//gr.glyphs()[idx + 1].x(gr.glyphs()[idx + 1].x() - 10.0);
//	ds.immediate().clear();
//	//ds.immediate().add_text(ds.font_resource(), fpsStr.str(), { static_cast<double>(ds.width()) - 400.0, 50.0 });
//	//ds.immediate().add_glyph_run(ds.font_resource(), gr);
//	//ds.fill_immediate(rgba_color::dark_red());
//	ds.render_glyph_run(gr, rgba_color::dark_red());
//	
//	////ds.render_text(fpsStr.str(), { static_cast<double>(ds.width()) - 400.0, 50.0 }, rgba_color::dark_red());
//	////fpsStr = stringstream();
//	////fpsStr << static_cast<int>(timer) << " " << elapsedTimeInMilliseconds;
//	////ds.render_text(fpsStr.str(), { static_cast<double>(ds.width()) - 400.0, 150.0 }, rgba_color::dark_red());
//	
//	ds.matrix(origM);
//
//	//auto radialFactory = radial_brush_factory({ 115.2, 102.4 }, 25.6, { 102.4, 102.4 }, 128.0);
//	//radialFactory.add_color_stop(0.0, rgba_color::white());
//	////radialFactory.add_color_stop(0.25, rgba_color::red());
//	////radialFactory.add_color_stop(0.5, rgba_color::green());
//	////radialFactory.add_color_stop(0.75, rgba_color::blue());
//	//radialFactory.add_color_stop(1.0, rgba_color::black());
//	//auto radialBrush = brush(radialFactory);
//	//radialBrush.tiling(tiling::pad);
//	//ds.immediate().clear();
//	////ds.immediate().arc({ 128.0, 128.0 }, 76.8, 0.0, 2 * pi);
//	//ds.immediate().rectangle({ 0.0, 0.0, 250.0, 250.0 });
//	//ds.fill_immediate(radialBrush);
//
//	timer = (timer > phaseTime * (phaseCount + 2)) ? 0.0 : timer + elapsedTimeInMilliseconds;
//}
//
//void draw_sort_visualization(display_surface& ds, double elapsedTimeInMilliseconds) {
//	static double timer = 0.0;
//	const double power = 3.0;
//	const double lerpTime = 1250.0;
//	const double phaseTime = lerpTime + 500.0;
//	const double normalizedTime = min(fmod(timer, phaseTime) / lerpTime, 1.0);
//	const double adjustment = (normalizedTime < 0.5) ? pow(normalizedTime * 2.0, power) / 2.0 :
//		((1.0 - pow(1.0 - ((normalizedTime - 0.5) * 2.0), power)) * 0.5) + 0.5;
//	const int elementCount = 12;
//	const static auto vec = init_sort_steps(elementCount);
//	const auto phaseCount = vec.size();
//	assert(phaseCount > 0);
//	const size_t x = min(static_cast<size_t>(timer / phaseTime), max(static_cast<size_t>(phaseCount - 1U), static_cast<size_t>(0U)));
//	auto cornflowerBlueBrush = brush(solid_color_brush_factory(rgba_color::cornflower_blue()));
//	ds.brush(cornflowerBlueBrush);
//	ds.paint(); // Paint background.
//
//	auto clextents = ds.clip_extents();
//	const double radius = trunc(min(clextents.width() * 0.8 / elementCount, clextents.height() + 120.0) / 2.0);
//	const double beginX = trunc(clextents.width() * 0.1);
//	const double y = trunc(clextents.height() * 0.5);
//
//	auto whiteBrush = brush(rgba_color::white());
//	ds.brush(whiteBrush);
//	//ds.font_resource("Segoe UI", 40.0);
//	//ds.render_text(string("Phase ").append(to_string(x + 1)).c_str(), { beginX, 50.0 });
//
//	path_factory<> pf;
//
//	for (size_t i = 0; i < elementCount; ++i) {
//		pf.clear();
//		const auto currVal = vec[x][i];
//		if (x < phaseCount - 1) {
//			const auto i2 = find(begin(vec[x + 1]), end(vec[x + 1]), currVal) - begin(vec[x + 1]);
//			const auto x1r = radius * i * 2.0 + radius + beginX, x2r = radius * i2 * 2.0 + radius + beginX;
//			const auto yr = y - ((i2 == static_cast<int>(i) ? 0.0 : (radius * 4.0 * (normalizedTime < 0.5 ? normalizedTime : 1.0 - normalizedTime)))
//				* (i % 2 == 1 ? 1.0 : -1.0));
//			const auto center = vector_2d{ trunc((x2r - x1r) * adjustment + x1r), trunc(yr) };
//#if _Variable_templates_conditional_support_test
//			pf.change_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi<double> / 4.0) * matrix_2d::init_translate({ 0.0, 50.0 }));
//#else
//			pf.change_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi<double>() / 4.0) * matrix_2d::init_translate({ 0.0, 50.0 }));
//#endif
//			pf.change_origin(center);
//#if _Variable_templates_conditional_support_test
//			pf.arc_negative(center, radius - 3.0, half_pi<double>, -half_pi<double>);
//#else
//			pf.arc_negative(center, radius - 3.0, half_pi<double>(), -half_pi<double>());
//#endif
//		}
//		else {
//			const vector_2d center{ radius * i * 2.0 + radius + beginX, y };
//#if _Variable_templates_conditional_support_test
//			pf.change_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi<double> / 4.0));
//#else
//			pf.change_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi<double>() / 4.0));
//#endif
//			pf.change_origin(center);
//#if _Variable_templates_conditional_support_test
//			pf.arc_negative(center, radius - 3.0, half_pi<double>, -half_pi<double>);
//#else
//			pf.arc_negative(center, radius - 3.0, half_pi<double>(), -half_pi<double>());
//#endif
//		}
//		ds.path_group(path_group(pf));
//		double greyColor = 1.0 - (currVal / (elementCount - 1.0));
//		auto greyBrush = brush(solid_color_brush_factory({ greyColor, greyColor, greyColor, 1.0 }));
//		ds.brush(greyBrush);
//		ds.fill();
//	}
//
//	pf.clear();
//	pf.change_origin({ 250.0, 450.0 });
//	pf.change_matrix(matrix_2d::init_shear_x(0.5).scale({ 2.0, 1.0 }));
//	pf.rectangle({ 200.0, 400.0, 100.0, 100.0 });
//	ds.path_group(path_group(pf));
//	auto redBrush = brush(solid_color_brush_factory(rgba_color::red()));
//	ds.brush(redBrush);
//	ds.line_width(3.0);
//	ds.stroke();
//	auto radialFactory = radial_brush_factory({ 250.0, 450.0 }, 0.0, { 250.0, 450.0 }, 80.0);
//	radialFactory.add_color_stop(0.0, rgba_color::black());
//	radialFactory.add_color_stop(0.25, rgba_color::red());
//	radialFactory.add_color_stop(0.5, rgba_color::green());
//	radialFactory.add_color_stop(0.75, rgba_color::blue());
//	radialFactory.add_color_stop(1.0, rgba_color::white());
//	auto radialBrush = brush(radialFactory);
//	radialBrush.tiling(tiling::reflect);
//	ds.brush(radialBrush);
//	ds.fill();
//
//	auto linearFactory = linear_brush_factory({ 510.0, 460.0 }, { 530.0, 480.0 });
//	linearFactory.add_color_stop(0.0, rgba_color::chartreuse());
//	linearFactory.add_color_stop(1.0, rgba_color::salmon());
//	auto linearBrush = brush(linearFactory);
//	linearBrush.tiling(tiling::repeat);
//	pf.clear();
//	pf.rectangle({ 500.0, 450.0, 100.0, 100.0 });
//	pf.rectangle({ 525.0, 425.0, 50.0, 150.0 });
//	ds.line_join(line_join::miter_or_bevel);
//	ds.miter_limit(1.0);
//	ds.line_width(10.0);
//	ds.path_group(path_group(pf));
//	ds.brush(redBrush);
//	ds.stroke();
//	ds.brush(linearBrush);
//	ds.fill();
//
//	pf.clear();
//	pf.abs_move({ 650.0, 400.0 });
//	pf.rel_line({ 0.0, 100.0 });
//	pf.rel_line({ 10.0, -100.0 });
//	ds.line_join(line_join::miter);
//	ds.path_group(path_group(pf));
//	ds.brush(redBrush);
//	ds.stroke();
//	ds.brush(linearBrush);
//	ds.fill();
//
//	pf.clear();
//	pf.abs_move({ 430.0, 60.0 });
//#if _Variable_templates_conditional_support_test
//	pf.arc({ 500.0, 60.0 }, 30.0, pi<double>, two_pi<double>);
//#else
//	pf.arc({ 500.0, 60.0 }, 30.0, pi<double>(), two_pi<double>());
//#endif
//	pf.abs_line({ 570.0, 60.0 });
//	pf.new_sub_path();
//#if _Variable_templates_conditional_support_test
//	pf.arc_negative({ 500.0, 130.0 }, 30.0, 0.0, pi<double> * 3.0 / 4.0);
//#else
//	pf.arc_negative({ 500.0, 130.0 }, 30.0, 0.0, pi<double>() * 3.0 / 4.0);
//#endif
//	pf.new_sub_path();
//	ds.path_group(path_group(pf));
//	ds.line_width(2.0);
//	ds.brush(redBrush);
//	ds.stroke();
//
//	timer = (timer > phaseTime * (phaseCount + 2)) ? 0.0 : timer + elapsedTimeInMilliseconds;
//}
//
//namespace {
//
//	//vector<vector_2d> curve_intersects_line_segment(const vector_2d& firstStart, const vector_2d& firstControl1, const vector_2d& firstControl2, const vector_2d& firstEnd,
//	//	const vector_2d& secondStart, const vector_2d& secondEnd) {
//
//	//}
//
//	//vector<vector_2d> curve_intersects_curve(const vector_2d& firstStart, const vector_2d& firstControl1, const vector_2d& firstControl2, const vector_2d& firstEnd,
//	//	const vector_2d& secondStart, const vector_2d& secondControl1, const vector_2d& secondControl2, const vector_2d& secondEnd) {
//
//	//}
//
//	//vector<vector<vector_2d>> path_curve_non_intersecting_sub_paths(const vector_2d& startPt, const vector_2d& controlPt1, const vector_2d& controlPt2, const vector_2d& endPt) noexcept;
//	//vector<vector<vector_2d>> path_curve_non_intersecting_sub_paths(const vector_2d& startPt, const vector_2d& controlPt1, const vector_2d& controlPt2, const vector_2d& endPt) noexcept {
//
//	//}
//
//	//bool sub_paths_intersect(const vector<path_data_item>& lhs, const vector<path_data_item>& rhs) {
//
//	//}
//
//	//vector<vector<path_data_item>> sub_path_to_non_intersecting_sub_paths(const vector<path_data_item>& subPath) {
//	//}
//
//	// This function takes two paths and does the following:
//	// 0. In the steps that follow, any time a sub path is broken up, the curves and lines of the resulting sub paths shall retain their original direction for proper fill_rule::winding fills.
//	// 1. It creates 'vector<vector<path_data_item>> processedLhs'.
//	// 2. It examines lhs and If lhs contains areas formed by intersections Then it breaks up lhs into non-intersecting sub paths and adds them to processedLhs, Else it adds lhs to processedLhs.
//	// 3. It creates 'vector<vector<path_data_item>> processedRhs'.
//	// 4. It examines rhs and If rhs contains areas formed by intersections Then it breaks up rhs into non-intersecting sub paths and adds them to processedRhs, Else it adds rhs to processedRhs.
//	// 5. If lhs and rhs do not intersect Then it returns the concatenation of processedLhs and processedRhs.
//	// 6. It creates 'vector<vector<path_data_item>> result'.
//	// 7. For each sub path 'item' in processedLhs, If 'item' does not intersect with rhs Then 'item' is move appended to 'result'.
//	// 8. Empty sub paths in processedLhs are erase-removed.
//	// 9. For each sub path 'item' in processedRhs, If 'item' does not intersect with lhs Then 'item' is move appended to 'result'.
//	// 10. Empty sub paths in processedRhs are erase-removed.
//	// 11. Each sub path in processedLhs is checked against each sub path in processedRhs for intersection.
//	// 12. If the sub paths intersect, then the sub path created by the intersection is appended to processedLhs and the sub paths that intersect are modified to exclude the intersecting area.
//	// 13. When the sub path from processedLhs has been checked against all sub paths from processedRhs, add it (as modified) to result.
//	// 14. When all sub paths in processedLhs (including any that are added along the way) are checked, return result.
//	//vector<vector<path_data_item>> transformed_fill_only_sub_paths_to_non_intersecting_sub_paths(const vector<path_data_item>& lhs, const vector<path_data_item>& rhs) {
//
//	//}
//
//	//vector<tuple<bool, bool, vector<path_data_item>>> transformed_fill_only_sub_paths_to_winding_bool_even_odd_bool_transformed_non_intersecting_filled_sub_paths(const vector<vector<path_data_item>>& pathData) {
//	//	// Need to 
//	//}
//}
//
//void test_draw_circle(display_surface&, const vector_2d&, const radial_brush_factory&);
//void test_draw_circle(display_surface& /*ds*/, const vector_2d& coords, const radial_brush_factory& f) {
//	// Can get t for s_fn via a simple magnitude. Determine the rotation angle of coords around center0, determine the point on circle 0 with that angle then the point on cirle 1 with that angle then get the distances from circle 0 pt to coords and from circle 0 pt to circle 1 pt and t = (dist(circ0, coords) / dist(circ0, circ1).
//	auto circles = f.radial_circles();
//	auto center0 = get<0>(circles);
//	auto radius0 = get<1>(circles);
//	auto center1 = get<2>(circles);
//	auto radius1 = get<3>(circles);
//	auto coordsAtZeroOrigin = coords - center0;
//	double angle = 0.0;
//	if (coordsAtZeroOrigin.x() != 0.0 || coordsAtZeroOrigin.y() != 0.0) {
//		angle = atan2(coordsAtZeroOrigin.y(), coordsAtZeroOrigin.x());
//	}
//	auto circ0 = _Rotate_point_absolute_angle(center0, radius0, angle);
//	auto circ1 = _Rotate_point_absolute_angle(center1, radius1, angle);
//	auto dist_fn = [](const vector_2d& from, const vector_2d& to) -> double { return to.magnitude() > from.magnitude() ? (to - from).magnitude() : -(to - from).magnitude(); };
//	if (_Almost_equal_relative(dist_fn(circ0, circ1), 0.0)) {
//		return;
//	}
//	auto t = dist_fn(circ0, coords) / dist_fn(circ0, circ1);
//	auto s_fn = [](double tForSFn) -> double { return (tForSFn - 0.0) / (1.0 - 0.0); };
//	auto x_fn = [&circles](double s) -> double { auto x0 = get<0>(circles).x(); return x0 + s * (get<2>(circles).x() - x0); };
//	auto y_fn = [&circles](double s) -> double { auto y0 = get<0>(circles).y(); return y0 + s * (get<2>(circles).y() - y0); };
//	auto r_fn = [&circles](double s) -> double { auto r0 = get<1>(circles); return r0 + s * (get<3>(circles) -r0); };
//	auto s = s_fn(t);
//	auto x = x_fn(s); // center x of circle for s
//	auto y = y_fn(s); // center y of circle for s
//	auto r = r_fn(s); // radius of circle for s
//	(void)x;
//	(void)y;
//	(void)r;
//	auto cs0 = get<1>(f.color_stop(0));
//	auto length = (circ1 - circ0).magnitude();
//	rgba_color result{ 1.0 - ((r / length) * cs0.r()), 1.0 - ((r / length) * cs0.g()), 1.0 - ((r / length) * cs0.b()) };
//}
