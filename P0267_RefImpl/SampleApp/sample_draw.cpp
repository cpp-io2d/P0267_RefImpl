#include "sample_draw.h"
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <chrono>
#include <numeric>
#include <iomanip>

using namespace std;
using namespace std::chrono;
using namespace std::experimental;
using namespace std::experimental::io2d;

//// Declarations
void test_image_load_save(output_surface& ds);
void test_stroke_rules(output_surface& ds);
void test_path_functionality(output_surface& ds);
void draw_radial_circles(output_surface& ds);
//void test_draw_radial_circles(display_surface& ds);
//wostream& operator<<(wostream& os, const point_2d& pt);
//vector<vector<int>> init_sort_steps(int count, unsigned long mtSeed = 1009UL);
//void draw_hello_world(display_surface& ds);
//void draw_test_compositing_operators(display_surface& ds, compositing_op secondRectCompOp, compositing_op firstRectCompOp = compositing_op::over, bool clipToRects = false, bool clipToTriangle = false, bool strokePaths = false, bool mask = false, const rgba_color& backgroundColor = rgba_color::transparent_black(), const rgba_color& firstColor = rgba_color::red() * 0.8F, const rgba_color& secondColor = rgba_color::teal() * 0.4F);
//void draw_sort_visualization_immediate(display_surface& ds, float elapsedTimeInMilliseconds);
//void draw_sort_visualization(display_surface& ds, float elapsedTimeInMilliseconds);
//void test_compositing_operators_different_pixel_formats(display_surface& ds, compositing_op co);
//void test_paint_surface_extend_modes(display_surface& ds, float elapsedTimeInMilliseconds);
//void test_fill_rules(display_surface& ds);
//void test_paint(display_surface& ds);
//void test_mask(display_surface& ds);
//void test_extend_none_on_boundary(display_surface& ds);
//void test_clip_transformation(display_surface& ds);

//
// Drawing entry point.
//
void sample_draw::operator()(output_surface& ds) {
	//test_image_load_save(ds);
	//test_path_functionality(ds);
	draw_radial_circles(ds);
	//ds.paint(rgba_color::cornflower_blue());
	//path_builder pf;
	//pf.new_figure();
	////static auto previousTime = steady_clock::now();
	////auto currentTime = steady_clock::now();
	////auto elapsedTime = currentTime - previousTime;
	////previousTime = currentTime;
	//draw_sort_visualization_immediate(ds, ds.elapsed_draw_time());

	//constexpr auto flColor = rgba_color(1.0F, 0.0F, 1.0F, 1.0F);
	//constexpr auto intColor = rgba_color(255, 0, 255, 255);
	//static_assert(flColor.r() == 1.0F, "Huh floating?");
	//static_assert(intColor.r() == 1.0F, "Huh integral?");

	//path_builder pb;
	//pb.new_figure();
	//pb.bounding_box({ 30.0F, 30.0F, 800.0F, 600.0F });
	//ds.paint(brush{ rgba_color::cornflower_blue() });

	////test_clip_transformation(ds);
	////test_paint(ds);
	//test_stroke_rules(ds);
	//test_path_functionality(ds);
	//draw_radial_circles(ds);
	////test_mask(ds);
	////test_extend_none_on_boundary(ds);

	////test_draw_radial_circles(ds);

	//
	////draw_test_compositing_operators(ds, compositing_op::in, compositing_op::over, true, false, false, true);
	//
	////test_compositing_operators_different_pixel_formats(ds, compositing_op::out);
	//
	////static auto previousTime = steady_clock::now();
	////auto currentTime = steady_clock::now();
	////auto elapsedTime = currentTime - previousTime;
	////previousTime = currentTime;
	////test_paint_surface_extend_modes(ds, duration_cast<microseconds>(elapsedTime).count() / 1000.0F);

	////test_fill_rules(ds);
}

void test_image_load_save(output_surface& ds) {
#ifdef _Filesystem_support_test
//	static auto imgSfc = image_surface(filesystem::path("2017_03_05.jpg"s), image_file_format::jpeg, format::argb32);
	//static auto alphaSfc = image_surface(filesystem::path("alpha8.png"s), format::a8, image_file_format::png, format::a8);
#else
//	static auto imgSfc = image_surface("2017_03_05.jpg"s, format::argb32, image_file_format::jpeg, format::argb32);
	//static auto alphaSfc = image_surface("alpha8.png"s, format::a8, image_file_format::png, format::a8);
#endif
	static bool saveOnce = false;
	if (!saveOnce) {
#ifdef _Filesystem_support_test
		//imgSfc.save(filesystem::path("2017-03-05_testsave.png"s), image_file_format::png);
//		imgSfc.save(filesystem::path("2017-03-05_testsave.jpg"s), image_file_format::jpeg);
		//	alphaSfc.save(filesystem::path("alpha8_testsave.png"s), image_file_format::png);
#else
		//	imgSfc.save("2017-03-05_testsave.png"s, image_file_format::png);
		//	alphaSfc.save("alpha8_testsave.png"s, image_file_format::png);
#endif
		saveOnce = true;
	}

	//brush imgBrush{ ::std::move(image_brush(copy_image_surface(imgSfc))) };
	//brush alphaBrush{ make_image_surface(alphaSfc) };

	ds.paint(brush{ rgba_color::cornflower_blue });
	//ds.paint(imgBrush);
	//ds.mask(imgBrush, alphaBrush, path_builder{});
	ds.flush();
}

//void test_clip_transformation(display_surface& ds) {
//	ds.save();
//
//	image_surface imgSfc{ format::argb32, 500, 500 };
//	imgSfc.paint(rgba_color::green());
//	imgSfc.immediate().abs_move({ 0.0F, 250.0F });
//	imgSfc.immediate().abs_line({ 250.0F, 0.0F });
//	imgSfc.immediate().abs_line({ 500.0F,250.0F });
//	imgSfc.immediate().abs_line({ 250.0F,500.0F });
//	imgSfc.immediate().close_figure();
//	imgSfc.fill_immediate(rgba_color::white());
//
//	ds.matrix(matrix_2d::create_translate({ 0.0F, 0.0F }));
//	//ds.matrix(matrix_2d::create_translate({ 100.0F, 100.0F }));
//	ds.immediate().clear();
//	ds.immediate().bounding_box({ 0.0F, 0.0F, 500.0F, 500.0F });
//	ds.clip_immediate();
//
//	ds.matrix(matrix_2d::create_translate({ 100.0F, 100.0F }));
//	//ds.matrix(matrix_2d::create_translate({ 0.0F, 0.0F }));
//	//ds.immediate().clear();
//	//ds.immediate().bounding_box({ 0.0F, 0.0F, 500.0F, 500.0F });
//	ds.paint(imgSfc);
//
//	ds.restore();
//}
//
//void test_extend_none_on_boundary(display_surface& ds) {
//	image_surface imgSfc{ format::argb32, 500, 500 };
//	imgSfc.paint(rgba_color::green());
//	imgSfc.immediate().abs_move({ 0.0F, 250.0F });
//	imgSfc.immediate().abs_line({ 250.0F, 0.0F });
//	imgSfc.immediate().abs_line({ 500.0F,250.0F });
//	imgSfc.immediate().abs_line({ 250.0F,500.0F });
//	imgSfc.immediate().close_figure();
//	imgSfc.fill_immediate(rgba_color::white());
//
//	ds.clear();
//	ds.immediate().clear();
//	ds.paint(rgba_color::red());
//	ds.immediate().bounding_box({ 20.0F, 20.0F, static_cast<float>(ds.width()), static_cast<float>(ds.height()) });
//	ds.fill_immediate(imgSfc, matrix_2d::create_translate({ -20.0F, -20.0F }), wrap_mode::none, filter::bilinear);
//}
//
//void test_mask(display_surface& ds) {
//	image_surface imgSfc{ format::argb32, 500, 500 };
//	imgSfc.paint(rgba_color::white(), 0.5F);
//	imgSfc.immediate().abs_move({ 0.0F, 250.0F });
//	imgSfc.immediate().abs_line({ 250.0F, 0.0F });
//	imgSfc.immediate().abs_line({ 500.0F,250.0F });
//	imgSfc.immediate().abs_line({ 250.0F,500.0F });
//	imgSfc.immediate().close_figure();
//	imgSfc.fill_immediate(rgba_color::white());
//	//imgSfc.matrix(matrix_2d::create_translate({ -50.0F, 50.0F }));
//	//imgSfc.matrix(matrix_2d::create_scale({ 0.5F, 1.5F }));
//	//surface_brush_factory sbf(imgSfc);
//	//brush br(sbf);
//	//br.matrix(matrix_2d::create_translate({ -50.0F, -50.0F }).rotate(half_pi<float> * 0.25F));
//	//br.filter(filter::nearest);
//	//br.wrap_mode(wrap_mode::none);
//
//	//radial_brush_factory rbf{ {250.0F, 250.0F}, 0.0F, {250.0F, 250.0F}, 250.0F };
//	//rbf.add_color_stop(0.0F, rgba_color::red());
//	//rbf.add_color_stop(0.5F, rgba_color::lime() * 0.5F);
//	//rbf.add_color_stop(1.0F, rgba_color::blue());
//	//brush br{ rbf };
//	//br.wrap_mode(wrap_mode::repeat);
//	//br.filter(filter::nearest);
//
//	ds.save();
//	ds.clear();
//	ds.immediate().clear();
//	ds.paint(rgba_color::red());
//	ds.immediate().bounding_box({ 0.0F, 0.0F, static_cast<float>(ds.width()), static_cast<float>(ds.height())});
//	//ds.matrix(matrix_2d::create_scale({ 0.5F, 1.5F }));
//	//ds.mask_immediate(br, rgba_color::blue());
//	ds.mask_immediate(imgSfc, rgba_color::blue(), matrix_2d::create_translate({ -50.0F, -50.0F }).rotate(half_pi<float> * 0.25F));
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
//	imgSfc.immediate().abs_move({ 0.0F, 250.0F });
//	imgSfc.immediate().abs_line({ 250.0F, 0.0F });
//	imgSfc.immediate().abs_line({ 500.0F,250.0F });
//	imgSfc.immediate().abs_line({ 250.0F,500.0F });
//	imgSfc.immediate().close_figure();
//	imgSfc.fill_immediate(rgba_color::white());
//	auto m = matrix_2d::create_scale({ 1.5F, 1.0F }).translate({ 20.0F, 20.0F });// .invert().translate({ -10.0F, -10.0F });
//	auto scsm = m;
//	//auto ucsm = matrix_2d::init_identity();
//	auto bcsm = matrix_2d::create_translate({ -10.0F, -10.0F });
//	auto invScsm = scsm;
//	invScsm.invert();
//	auto invBcsm = bcsm;
//	invBcsm.invert();
//
//	////auto pt = m.invert().transform_pt({ 0.0F, 0.0F });
//	////auto pt2 = m.transform_pt({ 10.0F, 10.0F });
//	//auto pt = m.transform_pt({ 0.0F, 0.0F });
//	//auto pt2 = invScsm.transform_pt({ 45.0F, 30.0F });
//	//auto pt3 = point_2d{ -26.6666666666666F, -30.0F };
//	//auto pt4 = point_2d{ -16.6666666666666F, -20.0F };
//	//auto pt5 = point_2d{ 45.0F, 30.0F };
//	ds.matrix(m);
//	ds.paint(imgSfc, matrix_2d::create_translate({ -10.0F, -10.0F })/*init_identity()*//*create_scale({ 1.0F, 1.5F }).translate({ -20.0F, -20.0F })*/, wrap_mode::repeat, filter::nearest);
//	//ds.paint(rgba_color::red());
//	//auto br = brush(solid_color_brush_factory(rgba_color::red()));
//	//br.wrap_mode(wrap_mode::none);
//	//ds.brush(br);
//	ds.paint();
//
//
//	//auto lbf = linear_brush_factory({ 0.0F, 0.0F }, { 50.0F, 50.0F });
//	//lbf.add_color_stop(0.0F, rgba_color::red());
//	//lbf.add_color_stop(0.5F, rgba_color::lime());
//	//lbf.add_color_stop(1.0F, rgba_color::blue());
//	//auto linBrush = brush(lbf);
//	//linBrush.wrap_mode(wrap_mode::repeat);
//	//linBrush.matrix(matrix_2d::create_rotate(half_pi<float> / 2.0F));
//	//ds.immediate().bounding_box({ { 50.0F, 50.0F}, {500.0F, 500.0F} });
//	//ds.clip_immediate();
//	//ds.matrix(matrix_2d::create_rotate(half_pi<float> / 2.0F));
//	//ds.brush(linBrush);
//	//ds.paint();
//
//	ds.restore();
//}
//

void test_stroke_rules(output_surface& ds) {
	ds.clear();
	vector<gradient_stop> csg;
	csg.emplace_back(0.0F, rgba_color::orange);
	csg.emplace_back(0.25F, rgba_color::red);
	csg.emplace_back(0.5F, rgba_color::lime_green);
	csg.emplace_back(0.75F, rgba_color::blue);
	csg.emplace_back(1.0F, rgba_color::gray);
	brush linearGrad({ 0.0F, 0.0F }, { 0.0F, 100.0F }, begin(csg), end(csg));
	//linearGrad.wrap_mode(wrap_mode::reflect);
	ds.paint(linearGrad);

	path_builder pb;
	//ds.line_width(40.0F);
	//ds.line_cap(line_cap::none);
	//ds.line_join(line_join::miter_or_bevel);
	//ds.immediate().arc({ ds.width() / 2.0F, ds.height() / 2.0F }, 200.0F, 0.0F, two_pi<float>);
	//ds.matrix(matrix_2d::create_translate({ ds.width() / 2.0F, ds.height() / 2.0F }).rotate(half_pi<float> / 2.0F).scale({ 0.5F, 1.0F }).translate({ -ds.width() / 2.0F, -ds.height() / 2.0F }));
	//ds.dashes(nullvalue);

	//ds.line_width(12.0F);
	//ds.immediate().move_to({ 0.0F, 199.0F });
	//ds.immediate().line({ 1280.9F, 199.0F });
	//ds.stroke_immediate(rgba_color::cornflower_blue());
	//ds.immediate().clear();

	//ds.line_width(40.0F);
	//dashes dsh(vector<float>{ 40.0F, 50.0F, 40.0F, 50.0F, 40.0F, 50.0F, 40.0F, 50.0F, 40.0F, 50.0F }, 150.0F);
	//ds.dashes(dsh);
	//ds.line_cap(line_cap::round);
	//ds.line_join(line_join::miter_or_bevel);
	//ds.immediate().move_to({ 700.0F, 200.0F });
	//ds.immediate().close_figure();

	//ds.line_width(40.0F);
	//ds.line_cap(line_cap::round);
	//ds.line_join(line_join::miter_or_bevel);
	//ds.immediate().move_to({ 200.0F, 200.0F });
	//ds.immediate().rel_line({ 0.0F, 100.0F });
	//ds.immediate().move_to({ 200.0F, 335.0F });
	//ds.immediate().rel_line({ 0.0F, 200.0F });

	//ds.matrix(matrix_2d::create_scale({ 0.5F, 1.0F }).rotate(half_pi<float> / 2.0F));
	//ds.matrix(matrix_2d::create_rotate(half_pi<float> / 2.0F).scale({ 0.5F, 1.0F }));
	//ds.immediate().rel_move({ 20.0F, 0.0F });
	//ds.immediate().rel_move({ 0.0F, 10.0F });
	//ds.immediate().close_figure();
	//ds.immediate().rel_line({ 5.0F, 10.0F });
	//ds.immediate().rel_line({ -20.0F, 0.0F });
	//ds.stroke_immediate(rgba_color::black());

	//ds.restore();
}

void test_path_functionality(output_surface& ds) {
	// Clear to background color.
	ds.paint(brush{ rgba_color::cornflower_blue });
	path_builder pf{};
	//void new_figure(const point_2d& pt) noexcept;
	point_2d v, cpt1, cpt2, ept;
	v = { 10.0F, 10.0F };
	pf.new_figure(v);
	//void rel_new_figure(const point_2d& dpt) noexcept;
	v = { 30.0F, 0.0F };
	pf.rel_new_figure(v);
	//void line(const point_2d& pt) noexcept;
	v = { 80.0F, 10.0F };
	pf.line(v);
	//void rel_line(const point_2d& dpt) noexcept;
	v = { 0.0F, 40.0F };
	pf.rel_line(v);
	//void close_figure() noexcept;
	pf.close_figure();

	pf.new_figure({ 50.0F, 50.0F });
	pf.line({ 1240.0F, 50.0F });
	pf.new_figure({ 50.0F, 80.0F });
	pf.line({ 900.0F, 80.0F });
	//void new_figure() noexcept;
	v = { 200.0F, 20.0F };
	pf.new_figure(v);
	////pf.move_to(v);
	//pf.line(v); // Should behave as a move_to.
	cpt1 = { 300.0F, 60.0F };
	cpt2 = { 100.0F, 100.0F };
	ept = { 200.0F, 140.0F };
	pf.cubic_curve(cpt1, cpt2, ept);

	v = { 30.0F, 300.0F };
	pf.new_figure(v);
	point_2d qcpt = { 100.0F, 230.0F };
	ept = { 170.0F, 300.0F };
	pf.quadratic_curve(qcpt, ept);

	//pf.new_figure({ 600.0F, 100.0F });
	//pf.arc_clockwise(circle{ { 600.0F, 100.0F }, 50.0F }, 0.0F, half_pi<float>);
	//pf.new_figure({ 600.0F, 100.0F });
	//pf.arc_clockwise(circle{ { 600.0F, 100.0F }, 50.0F }, 0.0F, half_pi<float>);
	//pf.new_figure({ 600.0F, 300.0F });
	//pf.arc_counterclockwise(circle{ { 600.0F, 300.0F }, 50.0F }, 0.0F, half_pi<float>);
	//pf.new_figure({ 300.0F, 300.0F });
	//pf.arc_clockwise(circle{ { 300.0F, 300.0F }, 50.0F }, 0.0F, two_pi<float>);

	//pf.new_figure({ 500.0F, 300.0F });
	//pf.transform_matrix(matrix_2d::create_rotate(half_pi<float> / 2.0F));
	//pf.rel_line({ 200.0F, 0.0F });
	//pf.rel_line({ 0.0F, 100.0F });
	//pf.rel_line({ -200.0F, 0.0F });
	//pf.close_figure();

	auto pg = interpreted_path(pf);
	ds.stroke(brush{ rgba_color::red }, pg, nullopt, nullopt, nullopt, nullopt, clip_props{ bounding_box(40.0F, 40.0F, 1240.0F, 680.0F) });

	pf.clear();

	//pf.new_figure({ 200.0F, 200.0F });
	////pf.transform_matrix(matrix_2d::create_rotate(half_pi<float> / 2.0F));
	//pf.ellipse({ { 200.0F, 200.0F },{ 80.0F, 40.0F } });
	//pf.new_figure({ 400.0F, 200.0F });
	//pf.rel_ellipse({ { 200.0F, 0.0F },{ 80.0F, 40.0F } });
	//pf.transform_matrix(matrix_2d{});
	//pf.new_figure({ 200.0F, 0.0F });
	//pf.line({ 200.0F, 800.0F });
}

void draw_radial_circles(output_surface& ds) {
	// Clear to background color.
	ds.paint(brush{ rgba_color::magenta });
	ds.paint(brush{ rgba_color::cornflower_blue }, nullopt, nullopt, clip_props{ bounding_box(40.0F, 40.0F, 1200.0F, 640.0F) });
	//auto sfc = ds._Get_data().data.back_buffer.surface.get();
	//auto data = cairo_image_surface_get_data(sfc);

	vector<gradient_stop> csv;
	csv.emplace_back(0.0F, rgba_color::white);
	brush radialBrush{ {{ 200.5F, 300.0F }, 0.0F}, {{ 300.0F, 300.0F }, 100.0F }, {
		{ 0.0F, rgba_color::white }, { 0.25F, rgba_color::red },
		{ 0.5F, rgba_color::green }, { 0.75F, rgba_color::blue }, { 1.0F, rgba_color::black } } };

	path_builder pf;
	//pf.bounding_box({ { 100.0F, 100.0F }, { 500.0F, 500.0F } });
	pf.new_figure({ 100.0F, 100.0F });
	pf.line({ 500.0F, 100.0F });
	pf.matrix(matrix_2d::create_shear_x(0.25F));
	pf.line({ 500.0F, 500.0F });
	pf.close_figure();
	pf.matrix(matrix_2d());
	pf.line({ 50.0F, 150.0F });
	pf.new_figure({ 520.0F, 520.0F });
	pf.line({ 600.0F, 600.0F });
	pf.matrix(matrix_2d::create_scale({ 2.0F, 1.0F }));
	//pf.arc_clockwise({ 300.0F, 700.0F }, 100.0F, three_pi_over_two<float>, two_pi<float>);
	pf.matrix(matrix_2d());
	pf.new_figure({ 520.0F, 10.0F });
	pf.cubic_curve({ 480.0F, 60.0F }, { 560.0F, 60.0F }, { 520.0F, 10.0F });
	interpreted_path p(pf);

	//// For debug inspection testing only; uncomment if needed.
	//auto fe = ds.fill_extents();
	//auto se = ds.stroke_extents();
	//point_2d pt{ 110.0F, 300.0F };
	//auto inFill = ds.in_fill(pt);
	//// End for debug inspection testing only.

	//optional<brush_props> bp{};
	//bp.emplace(wrap_mode::repeat);
	//ds.fill(radialBrush, p, bp);
	ds.fill(radialBrush, p, brush_props{ wrap_mode::repeat, filter::nearest });
	//ds.brush(brush(rgba_color::red()));
	ds.stroke(brush{ rgba_color::red }, p);
	pf.clear();
	//pf.new_figure({ 900.0F, 200.0F });
	//pf.arc_clockwise({ 900.0F, 200.0F }, 50.0F, 0.0F, two_pi<float>);
	//pf.new_figure({ 900.0F, 200.0F });
	//pf.arc_counterclockwise({ 900.0F, 200.0F }, 75.0F, 0.0F, two_pi<float>);
	//pf.new_figure({ 900.0F, 200.0F });
	//pf.arc_clockwise({ 900.0F, 200.0F }, 100.0F, 0.0F, two_pi<float>);
	//pf.new_figure({ 900.0F, 200.0F });
	//pf.arc_counterclockwise({ 900.0F, 200.0F }, 125.0F, 0.0F, two_pi<float>);
	//pf.new_figure({ 900.0F, 200.0F });
	//pf.arc_clockwise({ 900.0F, 200.0F }, 150.0F, 0.0F, two_pi<float>);
	p = interpreted_path(pf);
	//ds.path_group(p);
	ds.stroke(radialBrush, p);
	//ds.matrix(matrix_2d::create_translate({ 0.0F, 310.0F }));
	//ds.path_group(p);
	//ds.fill_rule(fill_rule::even_odd);
	ds.stroke(radialBrush, p, brush_props{ wrap_mode::repeat, filter::nearest, fill_rule::even_odd }, stroke_props{ 10.0F }, nullopt, render_props{ antialias::good, matrix_2d::create_translate({0.0F, 310.0F}) });

	//render_ellipse(ds, { 200.0F, 600.0F }, 250.0F, 100.0F, rgba_color(0.0F, 1.0F, 1.0F, 1.0F));

	//radialFactory.radial_circles({ 200.5F, 300.0F }, 0.0F, { 300.0F, 300.0F }, 100.0F);
	//auto radialBrush = brush(radialFactory);
	//radialBrush.wrap_mode(wrap_mode::repeat);
	////radialBrush.matrix(matrix_2d::create_scale({ 2.0F, 2.0F }));
	//ds.immediate().clear();
	//ds.immediate().bounding_box({ { 100.0F, 100.0F }, { 500.0F, 500.0F } });
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 115.2F, 102.4F }, 25.6F, { 102.4F, 102.4F }, 128.0F);
	//radialBrush = brush(radialFactory);
	//radialBrush.wrap_mode(wrap_mode::pad);
	//ds.immediate().clear();
	//ds.immediate().arc({ 128.0F, 128.0F }, 76.8F, 0.0F, 2 * pi);
	////ds.immediate().bounding_box({ 0.0F, 0.0F, 250.0F, 250.0F });
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 400.0F, 200.0F }, 100.0F, { 600.0F, 200.0F }, 100.0F);
	//auto color = test_draw_circle(ds, { 400.0F, 200.0F }, radialFactory);
	//
	//{
	//	auto linearFactory = linear_brush_factory();
	//	linearFactory.begin_point({ 200.0F, 0.0F });
	//	linearFactory.end_point({ 601.0F, 0.0F });
	//	linearFactory.add_color_stop(0.0F, rgba_color::white());
	//	linearFactory.add_color_stop(0.25F, rgba_color::red());
	//	linearFactory.add_color_stop(0.5F, rgba_color::lime());
	//	linearFactory.add_color_stop(0.6F, rgba_color::red());
	//	linearFactory.add_color_stop(0.5F, rgba_color::blue());
	//	linearFactory.add_color_stop(1.0F, rgba_color::white());
	//
	//	ds.immediate().clear();
	//	ds.immediate().bounding_box({ { 200.0F, 280.0F }, { 602.0F, 520.0F } });
	//	ds.fill_immediate(brush(linearFactory));
	//}
	//
	//radialFactory.radial_circles({ 600.0F, 200.0F }, 100.0F, { 400.0F, 200.0F }, 100.0F);
	//ds.immediate().clear();
	//ds.immediate().bounding_box({ { 280.0F, 80.0F }, { 720.0F, 320.0F } });
	//radialBrush = brush(radialFactory);
	//radialBrush.wrap_mode(wrap_mode::pad);
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 400.0F, 450.0F }, 100.0F, { 600.0F, 450.0F }, 100.0F);
	//ds.immediate().clear();
	//ds.immediate().bounding_box({ { 280.0F, 330.0F }, { 720.0F, 570.0F } });
	//radialBrush = brush(radialFactory);
	//radialBrush.wrap_mode(wrap_mode::none);
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 1000.0F, 200.0F }, 100.0F, { 1000.0F, 200.0F }, 20.0F);
	//ds.immediate().clear();
	//ds.immediate().bounding_box({ { 880.0F, 80.0F }, { 1120.0F, 320.0F } });
	//radialBrush = brush(radialFactory);
	//radialBrush.wrap_mode(wrap_mode::reflect);
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 1000.0F, 450.0F }, 20.0F, { 1000.0F, 450.0F }, 100.0F);
	//ds.immediate().clear();
	//ds.immediate().bounding_box({ { 880.0F, 330.0F }, { 1120.0F, 570.0F } });
	//radialBrush = brush(radialFactory);
	//radialBrush.wrap_mode(wrap_mode::repeat);
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 105.0F, 100.0F }, 0.0F, { 200.0F, 100.0F }, 100.0F);
	//ds.immediate().clear();
	//ds.immediate().bounding_box({ { 0.0F, 0.0F }, { 520.0F, 200.0F } });
	//radialBrush = brush(radialFactory);
	//radialBrush.wrap_mode(wrap_mode::repeat);
	//ds.fill_immediate(radialBrush);
	//
	//
	//radialFactory.radial_circles({ 200.0F, 200.0F }, 100.0F, { 400.0F, 200.0F }, 100.0F);
	//ds.immediate().clear();
	//ds.immediate().bounding_box({ { 80.0F, 80.0F }, { 520.0F, 320.0F } });
	//radialBrush = brush(radialFactory);
	//radialBrush.wrap_mode(wrap_mode::none);
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 200.0F, 450.0F }, 100.0F, { 400.0F, 450.0F }, 100.0F);
	//ds.immediate().clear();
	//ds.immediate().bounding_box({ { 80.0F, 330.0F }, { 520.0F, 570.0F } });
	//radialBrush = brush(radialFactory);
	//radialBrush.wrap_mode(wrap_mode::pad);
	//ds.fill_immediate(radialBrush);
	//
	////radialFactory.radial_circles({ 200.0F, 450.0F }, 100.0F, { 400.0F, 450.0F }, 100.0F);
	////ds.immediate().clear();
	////ds.immediate().bounding_box({ { 80.0F, 330.0F }, { 520.0F, 570.0F } });
	////radialBrush = brush(radialFactory);
	////radialBrush.wrap_mode(wrap_mode::pad);
	////ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 700.0F, 200.0F }, 100.0F, { 900.0F, 200.0F }, 100.0F);
	//ds.immediate().clear();
	//ds.immediate().bounding_box({ { 580.0F, 80.0F }, { 1020.0F, 320.0F } });
	//radialBrush = brush(radialFactory);
	//radialBrush.wrap_mode(wrap_mode::reflect);
	//ds.fill_immediate(radialBrush);
	//
	//radialFactory.radial_circles({ 700.0F, 450.0F }, 100.0F, { 900.0F, 450.0F }, 100.0F);
	//ds.immediate().clear();
	//ds.immediate().bounding_box({ { 580.0F, 330.0F }, { 1020.0F, 570.0F } });
	//radialBrush = brush(radialFactory);
	//radialBrush.wrap_mode(wrap_mode::repeat);
	//ds.fill_immediate(radialBrush);
}

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
//	// { 30.0F, 25.0F, 70.0F, 70.0F } - clip
//	imsfc.immediate().abs_move({ 40.0F, 0.0F });
//	imsfc.immediate().rel_cubic_curve({ -35.0F, 70.0F }, { -35.0F, 70.0F }, { 0.0F, 140.0F });
//	imsfc.immediate().rel_cubic_curve({ 35.0F, -70.0F }, { 35.0F, -70.0F }, { 0.0F, -140.0F });
//	imsfc.brush({ rgba_color::white() });
//	imsfc.fill_immediate();
//}
//
//void draw_hello_world(display_surface& ds) {
//	//ds.render_text("Hello world", { 100.0F, 100.0F }, brush(rgba_color::white()));
//}
//
//// For testing purposes only.
//void draw_test_compositing_operators(display_surface& ds, compositing_op secondRectCompOp, compositing_op firstRectCompOp, bool clipToRects, bool clipToTriangle, bool strokePaths, bool mask, const rgba_color& backgroundColor, const rgba_color& firstColor, const rgba_color& secondColor) {
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
//	auto pb = path_builder();
//
//	pb.bounding_box({ 10.0F, 10.0F, 120.0F, 90.0F });
//	auto firstRectPath = path_group(pb);
//
//	pb.clear();
//	pb.bounding_box({ 50.0F, 40.0F, 120.0F, 90.0F });
//	auto secondRectPath = path_group(pb);
//
//	pb.clear();
//	pb.bounding_box({ 30.0F, 25.0F, 70.0F, 70.0F });
//	auto bothRectsClipPath = path_group(pb);
//
//	pb.clear();
//	pb.abs_move({ 85.0F, 25.0F });
//	pb.abs_line({ 150.0F, 115.0F });
//	pb.abs_line({ 30.0F, 115.0F });
//	pb.close_figure();
//	auto triangleClipPath = path_group(pb);
//
//	ds.brush(backgroundBrush);
//	ds.compositing_op(compositing_op::clear);
//	ds.paint();
//
//	ds.brush(firstBrush);
//	ds.compositing_op(firstRectCompOp);
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
//	ds.compositing_op(secondRectCompOp);
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
//		////	// { 30.0F, 25.0F, 70.0F, 70.0F } - clip
//		////	imsfc.immediate().abs_move({ 40.0F, 0.0F });
//		////	imsfc.immediate().rel_cubic_curve({ -35.0F, 70.0F }, { -35.0F, 70.0F }, { 0.0F, 140.0F });
//		////	imsfc.immediate().rel_cubic_curve({ 35.0F, -70.0F }, { 35.0F, -70.0F }, { 0.0F, -140.0F });
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
//		ds.compositing_op(compositing_op::source);
//		ds.line_width(2.0F);
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
//void draw_sort_visualization_immediate(display_surface& ds, float elapsedTimeInMilliseconds) {
//	static float timer = 0.0F;
//	const float power = 3.0F;
//	const float lerpTime = 1250.0F;
//	const float phaseTime = lerpTime + 500.0F;
//	const float normalizedTime = min(fmod(timer, phaseTime) / lerpTime, 1.0F);
//	const float adjustment = (normalizedTime < 0.5F) ? pow(normalizedTime * 2.0F, power) / 2.0F :
//		((1.0F - pow(1.0F - ((normalizedTime - 0.5F) * 2.0F), power)) * 0.5F) + 0.5F;
//	const int elementCount = 12;
//	const static auto vec = init_sort_steps(elementCount);
//	const auto phaseCount = vec.size();
//	const size_t x = ::std::min(static_cast<size_t>(timer / phaseTime), ::std::max(static_cast<size_t>(phaseCount - 1U), static_cast<size_t>(0U)));
//
//	static deque<float> elapsedTimes(static_cast<size_t>(30), 1000.0F / ds.desired_frame_rate());
//	elapsedTimes.pop_front();
//	elapsedTimes.push_back(elapsedTimeInMilliseconds);
//
//	ds.paint(rgba_color::cornflower_blue()); // Paint background.
//
//	ds.immediate().clear();
//	ds.immediate().arc({ 100.0F, 100.0F }, 50.0F, 0.0F, half_pi<float>);
//	auto initLineWidth = ds.line_width();
//	ds.line_width(8.0F);
//	ds.stroke_immediate(rgba_color::black());
//	ds.immediate().clear();
//	ds.immediate().arc_negative({ 300.0F, 100.0F }, 50.0F, 0.0F, half_pi<float>);
//	ds.stroke_immediate(rgba_color::brown());
//	ds.immediate().clear();
//	ds.line_width(initLineWidth);
//
//	auto clextents = ds.clip_extents();
//	const float radius = trunc(min(clextents.width() * 0.8F / elementCount, clextents.height() + 120.0F) / 2.0F);
//	const float beginX = trunc(clextents.width() * 0.1F);
//	const float y = trunc(clextents.height() * 0.5F);
//
//	auto linearTest1 = linear_brush_factory({ 400.0F, 400.0F }, { 400.0F, 500.0F });
//	linearTest1.add_color_stop(0.0F, rgba_color::black());
//	linearTest1.add_color_stop(0.3F, rgba_color::yellow());
//	linearTest1.add_color_stop(0.5F, rgba_color::blue());
//	linearTest1.add_color_stop(0.3F, rgba_color::lime());
//	linearTest1.add_color_stop(0.5F, rgba_color::black());
//	linearTest1.add_color_stop(0.7F, rgba_color::purple());
//	linearTest1.add_color_stop(0.5F, rgba_color::red());
//	//	linearTest1.add_color_stop(1.0F, rgba_color::black());
//	linearTest1.add_color_stop(0.7F, rgba_color::orange());
//	linearTest1.add_color_stop(0.8F, rgba_color::green());
//	linearTest1.add_color_stop(0.8F, rgba_color::yellow());
//	linearTest1.add_color_stop(1.0F, rgba_color::white());
//	ds.immediate().bounding_box({ 400.0F, 400.0F, 200.0F, 200.0F });
//	ds.fill_immediate(brush(linearTest1));
//
//	ds.font_resource("Segoe UI", 40.0F);
//	auto str = string("Phase ").append(to_string(x + 1));
//	ds.render_text(str, { beginX, 50.0F }, rgba_color::white());
//
//	for (size_t i = 0; i < elementCount; ++i) {
//		ds.immediate().clear();
//		const auto currVal = vec[x][i];
//		if (x < phaseCount - 1) {
//			const auto i2 = find(begin(vec[x + 1]), end(vec[x + 1]), currVal) - begin(vec[x + 1]);
//			const auto x1r = radius * i * 2.0F + radius + beginX, x2r = radius * i2 * 2.0F + radius + beginX;
//			const auto yr = y - ((i2 == static_cast<int>(i) ? 0.0F : (radius * 4.0F * (normalizedTime < 0.5F ? normalizedTime : 1.0F - normalizedTime)))
//				* (i % 2 == 1 ? 1.0F : -1.0F));
//			const auto center = point_2d{ trunc((x2r - x1r) * adjustment + x1r), trunc(yr) };
//			ds.immediate().abs_matrix(matrix_2d::create_scale({ 1.0F, 1.5F }) * matrix_2d::create_rotate(pi<float> / 4.0F) * matrix_2d::create_translate({ 0.0F, 50.0F }));
//			ds.immediate().set_origin(center);
//			ds.immediate().arc_negative(center, radius - 3.0F, half_pi<float>, -half_pi<float>);
//		}
//		else {
//			const point_2d center{ radius * i * 2.0F + radius + beginX, y };
//			ds.immediate().abs_matrix(matrix_2d::create_scale({ 1.0F, 1.5F }) * matrix_2d::create_rotate(pi<float> / 4.0F) * matrix_2d::create_translate({ 0.0F, 50.0F }));
//			ds.immediate().set_origin(center);
//			ds.immediate().arc_negative(center, radius - 3.0F, half_pi<float>, -half_pi<float>);
//		}
//		float greyColor = 1.0F - (currVal / (elementCount - 1.0F));
//		ds.fill_immediate({ greyColor, greyColor, greyColor, 1.0F });
//	}
//
//	ds.immediate().clear();
//	ds.immediate().set_origin({ 250.0F, 450.0F });
//	ds.immediate().abs_matrix(matrix_2d::create_shear_x(0.5F).scale({ 2.0F, 2.5F }));
//	ds.immediate().bounding_box({ 200.0F, 400.0F, 100.0F, 100.0F });
//	ds.line_width(3.0F);
//	ds.stroke_immediate(rgba_color::red());
//	//auto radialFactory = radial_brush_factory({ 250.0F, 450.0F }, 0.0F, { 250.0F, 450.0F }, 80.0F);
//	//radialFactory.add_color_stop(0.0F, rgba_color::black());
//	//radialFactory.add_color_stop(0.25F, rgba_color::red());
//	//radialFactory.add_color_stop(0.5F, rgba_color::green());
//	//radialFactory.add_color_stop(0.75F, rgba_color::blue());
//	//radialFactory.add_color_stop(1.0F, rgba_color::white());
//	//auto radialBrush = ds.create_brush(radialFactory);
//	//radialBrush.wrap_mode(wrap_mode::reflect);
//	//ds.fill_immediate(radialBrush);
//
//	//auto meshFactory = mesh_brush_factory();
//	//meshFactory.begin_patch();
//	//meshFactory.abs_move({ 0.0F, 0.0F });
//	//meshFactory.curve({ 30.0F, -30.0F }, { 60.0F, 30.0F }, { 100.0F, 0.0F });
//	//meshFactory.curve({ 60.0F, 30.0F }, { 130.0F, 60.0F }, { 100.0F, 100.0F });
//	//meshFactory.curve({ 60.0F, 70.0F }, { 30.0F, 130.0F }, { 0.0F, 100.0F });
//	//meshFactory.curve({ 30.0F, 70.0F }, { -30.0F, 30.0F }, { 0.0F, 0.0F });
//	//meshFactory.corner_color(0, rgba_color::red());
//	//meshFactory.corner_color(1, rgba_color::lime());
//	//meshFactory.corner_color(2, rgba_color::blue());
//	//meshFactory.corner_color(3, rgba_color::yellow());
//	//meshFactory.end_patch();
//	//meshFactory.begin_patch();
//	//meshFactory.abs_move({ 100.0F, 100.0F });
//	//meshFactory.abs_line({ 130.0F, 130.0F });
//	//meshFactory.abs_line({ 130.0F, 70.0F });
//	//meshFactory.corner_color(0, rgba_color::red());
//	//meshFactory.corner_color(1, rgba_color::lime());
//	//meshFactory.corner_color(2, rgba_color::blue());
//	//meshFactory.end_patch();
//	//auto meshBrush = brush(meshFactory);
//	//meshBrush.matrix(matrix_2d::create_translate({ -200.0F, -400.0F }));
//	//ds.fill_immediate(meshBrush);
//
//	auto imgSfc = image_surface(format::argb32, 40, 40);
//	imgSfc.immediate().abs_move({ 0.0F, 0.0F });
//	imgSfc.immediate().abs_line({ 40.0F, 40.0F });
//	imgSfc.immediate().abs_line({ 0.0F, 40.0F });
//	imgSfc.immediate().close_figure();
//	imgSfc.paint(rgba_color::green());
//	imgSfc.fill_immediate(rgba_color::yellow());
//
//	auto sfcFactory = surface_brush_factory(imgSfc);
//	auto sfcBrush = brush(sfcFactory);
//	sfcBrush.wrap_mode(wrap_mode::repeat);
//	ds.immediate().clear();
//	ds.immediate().bounding_box({ 500.0F, 450.0F, 100.0F, 100.0F });
//	ds.immediate().bounding_box({ 525.0F, 425.0F, 50.0F, 150.0F });
//	ds.line_join(line_join::miter_or_bevel);
//	ds.miter_limit(1.0F);
//	ds.line_width(10.0F);
//	ds.stroke_immediate(rgba_color::red());
//	ds.fill_immediate(sfcBrush);
//
//	auto linearFactory = linear_brush_factory({ 510.0F, 460.0F }, { 530.0F, 480.0F });
//	linearFactory.add_color_stop(0.0F, rgba_color::chartreuse());
//	linearFactory.add_color_stop(1.0F, rgba_color::salmon());
//	auto linearBrush = brush(linearFactory);
//	linearBrush.wrap_mode(wrap_mode::repeat);
//	ds.immediate().clear();
//	ds.immediate().abs_move({ 650.0F, 400.0F });
//	ds.immediate().rel_line({ 0.0F, 100.0F });
//	ds.immediate().rel_line({ 10.0F, -100.0F });
//	ds.line_join(line_join::miter);
//	ds.stroke_immediate(rgba_color::red());
//	ds.fill_immediate(linearBrush);
//
//	ds.immediate().clear();
//	ds.immediate().abs_move({ 430.0F, 60.0F });
//	ds.immediate().arc({ 500.0F, 60.0F }, 30.0F, pi<float>, two_pi<float>);
//	ds.immediate().abs_line({ 570.0F, 60.0F });
//	//	ds.immediate().new_sub_path();
//	ds.immediate().arc({ 500.0F, 130.0F }, 30.0F, two_pi<float>, pi<float> * 3.0F / 4.0F);
//	ds.immediate().new_sub_path();
//	ds.dashes(dashes{ { 0.0F, 10.0F }, 0.0F });
//	ds.line_width(5.0F);
//	ds.line_cap(line_cap::round);
//	ds.fill_immediate(rgba_color::blue());
//	ds.stroke_immediate(rgba_color::orange());
//	// Reset dashes to be a solid line.
//	ds.dashes(nullopt);
//	ds.line_cap(line_cap::none);
//
//	ds.immediate().clear();
//	ds.immediate().curve({ 610.0F, 400.0F }, { 660.0F, 300.0F }, { 710.0F, 400.0F });
//	ds.immediate().close_figure();
//	ds.stroke_immediate(rgba_color::yellow_green());
//	auto sumOfElapsedTimes = accumulate(begin(elapsedTimes), end(elapsedTimes), 0.0F);
//	auto countOfElapsedTimes = static_cast<float>(elapsedTimes.size());
//	auto fps = 1000.0F / (sumOfElapsedTimes / countOfElapsedTimes);
//	stringstream fpsStr;
//	fpsStr << "FPS: " << setprecision(3) << fps;
//	
//	auto origM = ds.matrix();
//	
//	//ds.matrix(matrix_2d::create_scale({ 1.0F, 0.5F }));
//	font_resource_factory frf{ "Segoe UI", font_slant::normal, font_weight::normal, matrix_2d::create_scale({40.0F, 40.0F}) };//, font_options{}, matrix_2d::create_scale({ 1.0F, 1.5F }) };
//	ds.font_resource(experimental::io2d::font_resource{ frf });
//	auto gr = ds.font_resource().make_glyph_run(fpsStr.str(), { static_cast<float>(ds.width()) - 400.0F, 50.0F });
//	//vector<glyph_run::glyph>::size_type idx = 0;
//	//gr.glyphs()[idx].x(gr.glyphs()[idx].x() - 20.0F);
//	//gr.glyphs()[idx + 1].x(gr.glyphs()[idx + 1].x() - 10.0F);
//	ds.immediate().clear();
//	//ds.immediate().add_text(ds.font_resource(), fpsStr.str(), { static_cast<float>(ds.width()) - 400.0F, 50.0F });
//	//ds.immediate().add_glyph_run(ds.font_resource(), gr);
//	//ds.fill_immediate(rgba_color::dark_red());
//	ds.render_glyph_run(gr, rgba_color::dark_red());
//	
//	////ds.render_text(fpsStr.str(), { static_cast<float>(ds.width()) - 400.0F, 50.0F }, rgba_color::dark_red());
//	////fpsStr = stringstream();
//	////fpsStr << static_cast<int>(timer) << " " << elapsedTimeInMilliseconds;
//	////ds.render_text(fpsStr.str(), { static_cast<float>(ds.width()) - 400.0F, 150.0F }, rgba_color::dark_red());
//	
//	ds.matrix(origM);
//
//	//auto radialFactory = radial_brush_factory({ 115.2F, 102.4F }, 25.6F, { 102.4F, 102.4F }, 128.0F);
//	//radialFactory.add_color_stop(0.0F, rgba_color::white());
//	////radialFactory.add_color_stop(0.25F, rgba_color::red());
//	////radialFactory.add_color_stop(0.5F, rgba_color::green());
//	////radialFactory.add_color_stop(0.75F, rgba_color::blue());
//	//radialFactory.add_color_stop(1.0F, rgba_color::black());
//	//auto radialBrush = brush(radialFactory);
//	//radialBrush.wrap_mode(wrap_mode::pad);
//	//ds.immediate().clear();
//	////ds.immediate().arc({ 128.0F, 128.0F }, 76.8F, 0.0F, 2 * pi);
//	//ds.immediate().bounding_box({ 0.0F, 0.0F, 250.0F, 250.0F });
//	//ds.fill_immediate(radialBrush);
//
//	timer = (timer > phaseTime * (phaseCount + 2)) ? 0.0F : timer + elapsedTimeInMilliseconds;
//}
//
//void draw_sort_visualization(display_surface& ds, float elapsedTimeInMilliseconds) {
//	static float timer = 0.0F;
//	const float power = 3.0F;
//	const float lerpTime = 1250.0F;
//	const float phaseTime = lerpTime + 500.0F;
//	const float normalizedTime = min(fmod(timer, phaseTime) / lerpTime, 1.0F);
//	const float adjustment = (normalizedTime < 0.5F) ? pow(normalizedTime * 2.0F, power) / 2.0F :
//		((1.0F - pow(1.0F - ((normalizedTime - 0.5F) * 2.0F), power)) * 0.5F) + 0.5F;
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
//	const float radius = trunc(min(clextents.width() * 0.8F / elementCount, clextents.height() + 120.0F) / 2.0F);
//	const float beginX = trunc(clextents.width() * 0.1F);
//	const float y = trunc(clextents.height() * 0.5F);
//
//	auto whiteBrush = brush(rgba_color::white());
//	ds.brush(whiteBrush);
//	//ds.font_resource("Segoe UI", 40.0F);
//	//ds.render_text(string("Phase ").append(to_string(x + 1)).c_str(), { beginX, 50.0F });
//
//	path_builder pf;
//
//	for (size_t i = 0; i < elementCount; ++i) {
//		pf.clear();
//		const auto currVal = vec[x][i];
//		if (x < phaseCount - 1) {
//			const auto i2 = find(begin(vec[x + 1]), end(vec[x + 1]), currVal) - begin(vec[x + 1]);
//			const auto x1r = radius * i * 2.0F + radius + beginX, x2r = radius * i2 * 2.0F + radius + beginX;
//			const auto yr = y - ((i2 == static_cast<int>(i) ? 0.0F : (radius * 4.0F * (normalizedTime < 0.5F ? normalizedTime : 1.0F - normalizedTime)))
//				* (i % 2 == 1 ? 1.0F : -1.0F));
//			const auto center = point_2d{ trunc((x2r - x1r) * adjustment + x1r), trunc(yr) };
//			pf.abs_matrix(matrix_2d::create_scale({ 1.0F, 1.5F }) * matrix_2d::create_rotate(pi<float> / 4.0F) * matrix_2d::create_translate({ 0.0F, 50.0F }));
//			pf.set_origin(center);
//			pf.arc_negative(center, radius - 3.0F, half_pi<float>, -half_pi<float>);
//		}
//		else {
//			const point_2d center{ radius * i * 2.0F + radius + beginX, y };
//			pf.abs_matrix(matrix_2d::create_scale({ 1.0F, 1.5F }) * matrix_2d::create_rotate(pi<float> / 4.0F));
//			pf.set_origin(center);
//			pf.arc_negative(center, radius - 3.0F, half_pi<float>, -half_pi<float>);
//		}
//		ds.path_group(path_group(pf));
//		float greyColor = 1.0F - (currVal / (elementCount - 1.0F));
//		auto greyBrush = brush(solid_color_brush_factory({ greyColor, greyColor, greyColor, 1.0F }));
//		ds.brush(greyBrush);
//		ds.fill();
//	}
//
//	pf.clear();
//	pf.set_origin({ 250.0F, 450.0F });
//	pf.abs_matrix(matrix_2d::create_shear_x(0.5F).scale({ 2.0F, 1.0F }));
//	pf.bounding_box({ 200.0F, 400.0F, 100.0F, 100.0F });
//	ds.path_group(path_group(pf));
//	auto redBrush = brush(solid_color_brush_factory(rgba_color::red()));
//	ds.brush(redBrush);
//	ds.line_width(3.0F);
//	ds.stroke();
//	auto radialFactory = radial_brush_factory({ 250.0F, 450.0F }, 0.0F, { 250.0F, 450.0F }, 80.0F);
//	radialFactory.add_color_stop(0.0F, rgba_color::black());
//	radialFactory.add_color_stop(0.25F, rgba_color::red());
//	radialFactory.add_color_stop(0.5F, rgba_color::green());
//	radialFactory.add_color_stop(0.75F, rgba_color::blue());
//	radialFactory.add_color_stop(1.0F, rgba_color::white());
//	auto radialBrush = brush(radialFactory);
//	radialBrush.wrap_mode(wrap_mode::reflect);
//	ds.brush(radialBrush);
//	ds.fill();
//
//	auto linearFactory = linear_brush_factory({ 510.0F, 460.0F }, { 530.0F, 480.0F });
//	linearFactory.add_color_stop(0.0F, rgba_color::chartreuse());
//	linearFactory.add_color_stop(1.0F, rgba_color::salmon());
//	auto linearBrush = brush(linearFactory);
//	linearBrush.wrap_mode(wrap_mode::repeat);
//	pf.clear();
//	pf.bounding_box({ 500.0F, 450.0F, 100.0F, 100.0F });
//	pf.bounding_box({ 525.0F, 425.0F, 50.0F, 150.0F });
//	ds.line_join(line_join::miter_or_bevel);
//	ds.miter_limit(1.0F);
//	ds.line_width(10.0F);
//	ds.path_group(path_group(pf));
//	ds.brush(redBrush);
//	ds.stroke();
//	ds.brush(linearBrush);
//	ds.fill();
//
//	pf.clear();
//	pf.abs_move({ 650.0F, 400.0F });
//	pf.rel_line({ 0.0F, 100.0F });
//	pf.rel_line({ 10.0F, -100.0F });
//	ds.line_join(line_join::miter);
//	ds.path_group(path_group(pf));
//	ds.brush(redBrush);
//	ds.stroke();
//	ds.brush(linearBrush);
//	ds.fill();
//
//	pf.clear();
//	pf.abs_move({ 430.0F, 60.0F });
//	pf.arc({ 500.0F, 60.0F }, 30.0F, pi<float>, two_pi<float>);
//	pf.abs_line({ 570.0F, 60.0F });
//	pf.new_sub_path();
//	pf.arc_negative({ 500.0F, 130.0F }, 30.0F, 0.0F, pi<float> * 3.0F / 4.0F);
//	pf.new_sub_path();
//	ds.path_group(path_group(pf));
//	ds.line_width(2.0F);
//	ds.brush(redBrush);
//	ds.stroke();
//
//	timer = (timer > phaseTime * (phaseCount + 2)) ? 0.0F : timer + elapsedTimeInMilliseconds;
//}
//
//namespace {
//
//	//vector<point_2d> curve_intersects_line_segment(const point_2d& firstStart, const point_2d& firstControl1, const point_2d& firstControl2, const point_2d& firstEnd,
//	//	const point_2d& secondStart, const point_2d& secondEnd) {
//
//	//}
//
//	//vector<point_2d> curve_intersects_curve(const point_2d& firstStart, const point_2d& firstControl1, const point_2d& firstControl2, const point_2d& firstEnd,
//	//	const point_2d& secondStart, const point_2d& secondControl1, const point_2d& secondControl2, const point_2d& secondEnd) {
//
//	//}
//
//	//vector<vector<point_2d>> path_curve_non_intersecting_sub_paths(const point_2d& startPt, const point_2d& controlPt1, const point_2d& controlPt2, const point_2d& endPt) noexcept;
//	//vector<vector<point_2d>> path_curve_non_intersecting_sub_paths(const point_2d& startPt, const point_2d& controlPt1, const point_2d& controlPt2, const point_2d& endPt) noexcept {
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
//void test_draw_circle(display_surface&, const point_2d&, const radial_brush_factory&);
//void test_draw_circle(display_surface& /*ds*/, const point_2d& coords, const radial_brush_factory& f) {
//	// Can get t for s_fn via a simple magnitude. Determine the rotation angle of coords around center0, determine the point on circle 0 with that angle then the point on cirle 1 with that angle then get the distances from circle 0 pt to coords and from circle 0 pt to circle 1 pt and t = (dist(circ0, coords) / dist(circ0, circ1).
//	auto circles = f.radial_circles();
//	auto center0 = get<0>(circles);
//	auto radius0 = get<1>(circles);
//	auto center1 = get<2>(circles);
//	auto radius1 = get<3>(circles);
//	auto coordsAtZeroOrigin = coords - center0;
//	float angle = 0.0F;
//	if (coordsAtZeroOrigin.x() != 0.0F || coordsAtZeroOrigin.y() != 0.0F) {
//		angle = atan2(coordsAtZeroOrigin.y(), coordsAtZeroOrigin.x());
//	}
//	auto circ0 = _Rotate_point_absolute_angle(center0, radius0, angle);
//	auto circ1 = _Rotate_point_absolute_angle(center1, radius1, angle);
//	auto dist_fn = [](const point_2d& from, const point_2d& to) -> float { return to.magnitude() > from.magnitude() ? (to - from).magnitude() : -(to - from).magnitude(); };
//	if (_Almost_equal_relative(dist_fn(circ0, circ1), 0.0F)) {
//		return;
//	}
//	auto t = dist_fn(circ0, coords) / dist_fn(circ0, circ1);
//	auto s_fn = [](float tForSFn) -> float { return (tForSFn - 0.0F) / (1.0F - 0.0F); };
//	auto x_fn = [&circles](float s) -> float { auto x0 = get<0>(circles).x(); return x0 + s * (get<2>(circles).x() - x0); };
//	auto y_fn = [&circles](float s) -> float { auto y0 = get<0>(circles).y(); return y0 + s * (get<2>(circles).y() - y0); };
//	auto r_fn = [&circles](float s) -> float { auto r0 = get<1>(circles); return r0 + s * (get<3>(circles) -r0); };
//	auto s = s_fn(t);
//	auto x = x_fn(s); // center x of circle for s
//	auto y = y_fn(s); // center y of circle for s
//	auto r = r_fn(s); // radius of circle for s
//	(void)x;
//	(void)y;
//	(void)r;
//	auto cs0 = get<1>(f.gradient_stop(0));
//	auto length = (circ1 - circ0).magnitude();
//	rgba_color result{ 1.0F - ((r / length) * cs0.r()), 1.0F - ((r / length) * cs0.g()), 1.0F - ((r / length) * cs0.b()) };
//}
