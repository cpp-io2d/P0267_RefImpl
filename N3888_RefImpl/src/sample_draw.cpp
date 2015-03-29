#include "sample_draw.h"
#include "xio2dhelpers.h"
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;

vector<vector<int>> init_sort_steps(int count, unsigned long mtSeed = 1009UL);

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

wostream& operator<<(wostream& os, const point& pt);
wostream& operator<<(wostream& os, const point& pt) {
	os << L"(" << pt.x() << L"," << pt.y() << L")";
	return os;
}

// Declaration
void draw_hello_world(surface& rs);

// Declaration
void draw_test_compositing_operators(surface& rs, double elapsedTimeInMilliseconds, compositing_operator secondRectCompOp, compositing_operator firstRectCompOp = compositing_operator::over, bool strokePaths = false, const rgba_color& backgroundColor = rgba_color::transparent_black(), const rgba_color& firstColor = rgba_color::red() * 0.8, const rgba_color& secondColor = rgba_color::teal() * 0.4, bool clipToRects = false, bool clipToTriangle = false);

// Declaration
void draw_sort_visualization_immediate(surface& rs, double elapsedTimeInMilliseconds);

// Declaration
void draw_sort_visualization(surface& rs, double elapsedTimeInMilliseconds);

// Drawing entry point.
void sample_draw::operator()(display_surface& rs) {
	static auto previousTime = steady_clock::now();
	auto currentTime = steady_clock::now();
	auto elapsedTime = currentTime - previousTime;
	previousTime = currentTime;
	draw_sort_visualization_immediate(rs, duration_cast<microseconds>(elapsedTime).count() / 1000.0);
	//draw_test_compositing_operators(rs, elapsedTimeInMilliseconds, compositing_operator::over);
}

void draw_hello_world(surface& rs) {
	rs.show_text("Hello world", { 100.0, 100.0 }, rs.create_pattern(solid_color_pattern_factory(rgba_color::white())));
}

// For testing purposes only.
void draw_test_compositing_operators(surface& rs, double /*elapsedTimeInMilliseconds*/, compositing_operator secondRectCompOp, compositing_operator firstRectCompOp, bool strokePaths, const rgba_color& backgroundColor, const rgba_color& firstColor, const rgba_color& secondColor, bool clipToRects, bool clipToTriangle) {
	// Parameter validation.
	if (clipToRects && clipToTriangle) {
		throw invalid_argument("clipToRects and clipToTriangle cannot both be set to true.");
	}
	rs.save();

	auto backgroundPattern = rs.create_pattern(solid_color_pattern_factory(backgroundColor));
	auto firstPattern = rs.create_pattern(solid_color_pattern_factory(firstColor));
	auto secondPattern = rs.create_pattern(solid_color_pattern_factory(secondColor));

	auto pb = path_factory();

	pb.rect({ 10.0, 10.0, 120.0, 90.0 });
	auto firstRectPath = rs.path(pb);

	pb.reset();
	pb.rect({ 50.0, 40.0, 120.0, 90.0 });
	auto secondRectPath = rs.path(pb);

	pb.reset();
	pb.append(firstRectPath);
	pb.append(secondRectPath);
	auto bothRectsClipPath = rs.path(pb);

	pb.reset();
	pb.move_to({ 85.0, 25.0 });
	pb.line_to({ 150.0, 115.0 });
	pb.line_to({ 30.0, 115.0 });
	pb.close_path();
	auto triangleClipPath = rs.path(pb);

	rs.pattern(backgroundPattern);
	rs.compositing_operator(compositing_operator::source);
	rs.paint();

	rs.pattern(firstPattern);
	rs.compositing_operator(firstRectCompOp);
	rs.path(firstRectPath);
	rs.fill();


	if (clipToRects) {
		rs.path(bothRectsClipPath);
		rs.clip();
	}

	if (clipToTriangle) {
		rs.path(triangleClipPath);
		rs.clip();
	}

	rs.path(secondRectPath);
	rs.compositing_operator(secondRectCompOp);
	rs.pattern(secondPattern);
	rs.fill();

	rs.reclip();

	if (strokePaths) {
		rs.compositing_operator(compositing_operator::source);
		rs.line_width(2.0);

		rs.path(firstRectPath);
		rs.pattern(rs.create_pattern(solid_color_pattern_factory(rgba_color::teal())));
		rs.stroke();

		rs.path(secondRectPath);
		rs.pattern(rs.create_pattern(solid_color_pattern_factory(rgba_color::red())));
		rs.stroke();

		if (clipToTriangle) {
			rs.path(triangleClipPath);
			rs.pattern(rs.create_pattern(solid_color_pattern_factory(rgba_color::yellow())));
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
	const double pi = 3.1415926535897932;
	const double normalizedTime = min(fmod(timer, phaseTime) / lerpTime, 1.0);
	const double adjustment = (normalizedTime < 0.5) ? pow(normalizedTime * 2.0, power) / 2.0 :
		((1.0 - pow(1.0 - ((normalizedTime - 0.5) * 2.0), power)) * 0.5) + 0.5;
	const int elementCount = 12;
	const static auto vec = init_sort_steps(elementCount);
	const auto phaseCount = vec.size();
	const size_t x = min(static_cast<size_t>(timer / phaseTime), max(phaseCount - 1U, 0U));
	rs.paint(rgba_color::cornflower_blue()); // Paint background.

	auto clextents = rs.clip_extents();
	const double radius = trunc(min(clextents.width() * 0.8 / elementCount, clextents.height() + 120.0) / 2.0);
	const double beginX = trunc(clextents.width() * 0.1);
	const double y = trunc(clextents.height() * 0.5);

	rs.font_face("Segoe UI", font_slant::normal, font_weight::normal);
	rs.font_size(40.0);
	auto str = string("Phase ").append(to_string(x + 1));
	rs.show_text(str, { beginX, 50.0 }, rgba_color::white());

	for (size_t i = 0; i < elementCount; ++i) {
		rs.immediate().reset();
		const auto currVal = vec[x][i];
		if (x < phaseCount - 1) {
			const auto i2 = find(begin(vec[x + 1]), end(vec[x + 1]), currVal) - begin(vec[x + 1]);
			const auto x1r = radius * i * 2.0 + radius + beginX, x2r = radius * i2 * 2.0 + radius + beginX;
			const auto yr = y - ((i2 == static_cast<int>(i) ? 0.0 : (radius * 4.0 * (normalizedTime < 0.5 ? normalizedTime : 1.0 - normalizedTime)))
				* (i % 2 == 1 ? 1.0 : -1.0));
			const auto center = point{ trunc((x2r - x1r) * adjustment + x1r), trunc(yr) };
			rs.immediate().transform_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi / 4.0) * matrix_2d::init_translate({ 0.0, 50.0 }));
			rs.immediate().origin(center);
			rs.immediate().arc_negative(center, radius - 3.0, pi / 2.0, -pi / 2.0);
		}
		else {
			const point center{ radius * i * 2.0 + radius + beginX, y };
			rs.immediate().transform_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi / 4.0));
			rs.immediate().origin(center);
			rs.immediate().arc_negative(center, radius - 3.0, pi / 2.0, -pi / 2.0);
		}
		double greyColor = 1.0 - (currVal / (elementCount - 1.0));
		rs.fill_immediate({ greyColor, greyColor, greyColor, 1.0 });
	}

	rs.immediate().reset();
	rs.immediate().origin({ 250.0, 450.0 });
	rs.immediate().transform_matrix(matrix_2d::init_shear_x(0.5).scale({ 2.0, 2.5 }));
	rs.immediate().rect({ 200.0, 400.0, 100.0, 100.0 });
	rs.line_width(3.0);
	rs.stroke_immediate(rgba_color::red());
	//auto radialFactory = radial_pattern_factory({ 250.0, 450.0 }, 0.0, { 250.0, 450.0 }, 80.0);
	//radialFactory.add_color_stop_rgba(0.0, rgba_color::black());
	//radialFactory.add_color_stop_rgba(0.25, rgba_color::red());
	//radialFactory.add_color_stop_rgba(0.5, rgba_color::green());
	//radialFactory.add_color_stop_rgba(0.75, rgba_color::blue());
	//radialFactory.add_color_stop_rgba(1.0, rgba_color::white());
	//auto radialPattern = rs.create_pattern(radialFactory);
	//radialPattern.extend(extend::reflect);
	//rs.fill_immediate(radialPattern);
	auto meshFactory = mesh_pattern_factory();
	meshFactory.begin_patch();
	meshFactory.move_to({ 0.0, 0.0 });
	meshFactory.curve_to({ 30.0, -30.0 }, { 60.0, 30.0 }, { 100.0, 0.0 });
	meshFactory.curve_to({ 60.0, 30.0 }, { 130.0, 60.0 }, { 100.0, 100.0 });
	meshFactory.curve_to({ 60.0, 70.0 }, { 30.0, 130.0 }, { 0.0, 100.0 });
	meshFactory.curve_to({ 30.0, 70.0 }, { -30.0, 30.0 }, { 0.0, 0.0 });
	meshFactory.corner_color_rgba(0, rgba_color::red());
	meshFactory.corner_color_rgba(1, rgba_color::lime());
	meshFactory.corner_color_rgba(2, rgba_color::blue());
	meshFactory.corner_color_rgba(3, rgba_color::yellow());
	meshFactory.end_patch();
	meshFactory.begin_patch();
	meshFactory.move_to({ 100.0, 100.0 });
	meshFactory.line_to({ 130.0, 130.0 });
	meshFactory.line_to({ 130.0, 70.0 });
	meshFactory.corner_color_rgba(0, rgba_color::red());
	meshFactory.corner_color_rgba(1, rgba_color::lime());
	meshFactory.corner_color_rgba(2, rgba_color::blue());
	meshFactory.end_patch();
	auto meshPattern = rs.create_pattern(meshFactory);
	meshPattern.matrix(matrix_2d::init_translate({ -200.0, -400.0 }));
	rs.fill_immediate(meshPattern);

	auto imgSfc = image_surface(format::argb32, 40, 40);
	imgSfc.immediate().move_to({ 0.0, 0.0 });
	imgSfc.immediate().line_to({ 40.0, 40.0 });
	imgSfc.immediate().line_to({ 0.0, 40.0 });
	imgSfc.immediate().close_path();
	imgSfc.paint(rgba_color::green());
	imgSfc.fill_immediate(rgba_color::yellow());

	auto sfcFactory = surface_pattern_factory(imgSfc);
	auto sfcPattern = rs.create_pattern(sfcFactory);
	sfcPattern.extend(extend::repeat);
	rs.immediate().reset();
	rs.immediate().rect({ 500.0, 450.0, 100.0, 100.0 });
	rs.immediate().rect({ 525.0, 425.0, 50.0, 150.0 });
	rs.line_join(line_join::miter_or_bevel);
	rs.miter_limit(1.0);
	rs.line_width(10.0);
	rs.stroke_immediate(rgba_color::red());
	rs.fill_immediate(sfcPattern);

	auto linearFactory = linear_pattern_factory({ 510.0, 460.0 }, { 530.0, 480.0 });
	linearFactory.add_color_stop_rgba(0.0, rgba_color::chartreuse());
	linearFactory.add_color_stop_rgba(1.0, rgba_color::salmon());
	auto linearPattern = rs.create_pattern(linearFactory);
	linearPattern.extend(extend::repeat);
	rs.immediate().reset();
	rs.immediate().move_to({ 650.0, 400.0 });
	rs.immediate().rel_line_to({ 0.0, 100.0 });
	rs.immediate().rel_line_to({ 10.0, -100.0 });
	rs.line_join(line_join::miter);
	rs.stroke_immediate(rgba_color::red());
	rs.fill_immediate(linearPattern);

	rs.immediate().reset();
	rs.immediate().move_to({ 430.0, 60.0 });
	rs.immediate().arc({ 500.0, 60.0 }, 30.0, pi, pi * 2.0);
	rs.immediate().line_to({ 570.0, 60.0 });
	rs.immediate().new_sub_path();
	rs.immediate().arc_negative({ 500.0, 130.0 }, 30.0, 0.0, pi * 3.0 / 4.0);
	rs.immediate().new_sub_path();
	rs.dashes(dashes{ { 1.0, 0.0, 2.0, 0.0 } , 0.0 });
	rs.line_width(2.0);
	rs.stroke_immediate(rgba_color::red());
	// Reset dashes to be a solid line.
	rs.dashes();

	timer = (timer > phaseTime * (phaseCount + 2)) ? 0.0 : timer + elapsedTimeInMilliseconds;
}

void draw_sort_visualization(surface& rs, double elapsedTimeInMilliseconds) {
	static double timer = 0.0;
	const double power = 3.0;
	const double lerpTime = 1250.0;
	const double phaseTime = lerpTime + 500.0;
	const double pi = 3.1415926535897932;
	const double normalizedTime = min(fmod(timer, phaseTime) / lerpTime, 1.0);
	const double adjustment = (normalizedTime < 0.5) ? pow(normalizedTime * 2.0, power) / 2.0 :
		((1.0 - pow(1.0 - ((normalizedTime - 0.5) * 2.0), power)) * 0.5) + 0.5;
	const int elementCount = 12;
	const static auto vec = init_sort_steps(elementCount);
	const auto phaseCount = vec.size();
	assert(phaseCount > 0);
	const size_t x = min(static_cast<size_t>(timer / phaseTime), max(phaseCount - 1U, 0U));
	auto cornflowerBluePattern = rs.create_pattern(solid_color_pattern_factory(rgba_color::cornflower_blue()));
	rs.pattern(cornflowerBluePattern);
	rs.paint(); // Paint background.

	auto clextents = rs.clip_extents();
	const double radius = trunc(min(clextents.width() * 0.8 / elementCount, clextents.height() + 120.0) / 2.0);
	const double beginX = trunc(clextents.width() * 0.1);
	const double y = trunc(clextents.height() * 0.5);

	auto whitePattern = rs.create_pattern(solid_color_pattern_factory(rgba_color::white()));
	rs.pattern(whitePattern);
	rs.font_face("Segoe UI", font_slant::normal, font_weight::normal);
	rs.font_size(40.0);
	rs.show_text(string("Phase ").append(to_string(x + 1)).c_str(), { beginX, 50.0 });

	path_factory pf;

	for (size_t i = 0; i < elementCount; ++i) {
		pf.reset();
		const auto currVal = vec[x][i];
		if (x < phaseCount - 1) {
			const auto i2 = find(begin(vec[x + 1]), end(vec[x + 1]), currVal) - begin(vec[x + 1]);
			const auto x1r = radius * i * 2.0 + radius + beginX, x2r = radius * i2 * 2.0 + radius + beginX;
			const auto yr = y - ((i2 == static_cast<int>(i) ? 0.0 : (radius * 4.0 * (normalizedTime < 0.5 ? normalizedTime : 1.0 - normalizedTime)))
				* (i % 2 == 1 ? 1.0 : -1.0));
			const auto center = point{ trunc((x2r - x1r) * adjustment + x1r), trunc(yr) };
			pf.transform_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi / 4.0) * matrix_2d::init_translate({ 0.0, 50.0 }));
			pf.origin(center);
			pf.arc_negative(center, radius - 3.0, pi / 2.0, -pi / 2.0);
		}
		else {
			const point center{ radius * i * 2.0 + radius + beginX, y };
			pf.transform_matrix(matrix_2d::init_scale({ 1.0, 1.5 }) * matrix_2d::init_rotate(pi / 4.0));
			pf.origin(center);
			pf.arc_negative(center, radius - 3.0, pi / 2.0, -pi / 2.0);
		}
		rs.path(rs.path(pf));
		double greyColor = 1.0 - (currVal / (elementCount - 1.0));
		auto greyPattern = rs.create_pattern(solid_color_pattern_factory({ greyColor, greyColor, greyColor, 1.0 }));
		rs.pattern(greyPattern);
		rs.fill();
	}

	pf.reset();
	pf.origin({ 250.0, 450.0 });
	pf.transform_matrix(matrix_2d::init_shear_x(0.5).scale({ 2.0, 1.0 }));
	pf.rect({ 200.0, 400.0, 100.0, 100.0 });
	rs.path(rs.path(pf));
	auto redPattern = rs.create_pattern(solid_color_pattern_factory(rgba_color::red()));
	rs.pattern(redPattern);
	rs.line_width(3.0);
	rs.stroke();
	auto radialFactory = radial_pattern_factory({ 250.0, 450.0 }, 0.0, { 250.0, 450.0 }, 80.0);
	radialFactory.add_color_stop_rgba(0.0, rgba_color::black());
	radialFactory.add_color_stop_rgba(0.25, rgba_color::red());
	radialFactory.add_color_stop_rgba(0.5, rgba_color::green());
	radialFactory.add_color_stop_rgba(0.75, rgba_color::blue());
	radialFactory.add_color_stop_rgba(1.0, rgba_color::white());
	auto radialPattern = rs.create_pattern(radialFactory);
	radialPattern.extend(extend::reflect);
	rs.pattern(radialPattern);
	rs.fill();

	auto linearFactory = linear_pattern_factory({ 510.0, 460.0 }, { 530.0, 480.0 });
	linearFactory.add_color_stop_rgba(0.0, rgba_color::chartreuse());
	linearFactory.add_color_stop_rgba(1.0, rgba_color::salmon());
	auto linearPattern = rs.create_pattern(linearFactory);
	linearPattern.extend(extend::repeat);
	pf.reset();
	pf.rect({ 500.0, 450.0, 100.0, 100.0 });
	pf.rect({ 525.0, 425.0, 50.0, 150.0 });
	rs.line_join(line_join::miter_or_bevel);
	rs.miter_limit(1.0);
	rs.line_width(10.0);
	rs.path(rs.path(pf));
	rs.pattern(redPattern);
	rs.stroke();
	rs.pattern(linearPattern);
	rs.fill();

	pf.reset();
	pf.move_to({ 650.0, 400.0 });
	pf.rel_line_to({ 0.0, 100.0 });
	pf.rel_line_to({ 10.0, -100.0 });
	rs.line_join(line_join::miter);
	rs.path(rs.path(pf));
	rs.pattern(redPattern);
	rs.stroke();
	rs.pattern(linearPattern);
	rs.fill();

	pf.reset();
	pf.move_to({ 430.0, 60.0 });
	pf.arc({ 500.0, 60.0 }, 30.0, pi, pi * 2.0);
	pf.line_to({ 570.0, 60.0 });
	pf.new_sub_path();
	pf.arc_negative({ 500.0, 130.0 }, 30.0, 0.0, pi * 3.0 / 4.0);
	pf.new_sub_path();
	rs.path(rs.path(pf));
	rs.line_width(2.0);
	rs.pattern(redPattern);
	rs.stroke();

	timer = (timer > phaseTime * (phaseCount + 2)) ? 0.0 : timer + elapsedTimeInMilliseconds;
}
