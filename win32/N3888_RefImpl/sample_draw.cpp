#include "sample_draw.h"
#include <cmath>

using namespace std;
using namespace std::experimental::drawing;

void sample_draw::operator()(::std::experimental::drawing::context& ctxt, double elapsedTimeInMilliseconds) {
	// The is a demonstration of how a raster_source_pattern works. We create one that is 100px x 100px
	//auto pattern = raster_source_pattern(nullptr, content::color_alpha, 100, 100);
	//pattern.set_acquire(
	//	[pattern](void*, experimental::drawing::surface& target, const rectangle_int& extents) -> experimental::drawing::surface
	//{
	//	auto result = experimental::drawing::image_surface(target, format::rgb24, extents.width - extents.x, extents.height - extents.y);
	//	vector<unsigned char> data;
	//	const auto dataSize = result.get_stride() * result.get_height();
	//	data.resize(dataSize);
	//	for (auto i = 0; i < dataSize; i += 4) {
	//		data[i + 0] = 255ui8;
	//		data[i + 1] = 0ui8;
	//		data[i + 2] = 0ui8;
	//		data[i + 3] = 0ui8;
	//	}
	//	result.set_data(data);
	//	return result;
	//},
	//	nullptr
	//	);
	//pattern.set_extend(extend::repeat);
	//context.set_source(pattern);
	//context.paint();

	static double timer = 0.0;
	timer += elapsedTimeInMilliseconds;

	ctxt.save();
	auto scp = solid_color_pattern(0.0, 0.0, 1.0);
	ctxt.set_source(scp);
	ctxt.paint();
	ctxt.restore();

	ctxt.save();
	const int width = 100;
	const int height = 100;
	const format fmt = format::rgb24;
	const int stride = format_stride_for_width(fmt, width);
	vector<unsigned char> data;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < stride; x++) {
			auto byte = x % 4;
			switch (byte)
			{
			case 0:
				data.push_back(0x7Fui8);
				break;
			case 1:
				data.push_back(0xFFui8);
				break;
			case 2:
				data.push_back(0ui8);
				break;
			case 3:
				data.push_back(0ui8);
				break;
			default:
				throw logic_error("We're MODing by 4, how do we have a value outside of [0,3]?");
			}
		}
	}
	auto imageSurfaceFromData = image_surface(data, fmt, width, height, stride);
	ctxt.set_source_surface(imageSurfaceFromData, 400.0, 400.0);
	ctxt.move_to(400.0, 400.0);
	ctxt.rel_line_to(100.0, 0.0);
	ctxt.rel_line_to(0.0, 100.0);
	ctxt.rel_line_to(-100.0, 0.0);
	ctxt.close_path();
	ctxt.fill();
	imageSurfaceFromData.finish();
	ctxt.restore();

	ctxt.save();
	auto translucentSurface = image_surface(format::argb32, 100, 100);
	auto ctxtForTranslucentSurface = context(translucentSurface);
	ctxtForTranslucentSurface.set_source_rgba(0.5, 0.5, 0.5, 0.5);
	ctxtForTranslucentSurface.set_compositing_operator(compositing_operator::clear);
	ctxtForTranslucentSurface.paint_with_alpha(0.0);
	ctxtForTranslucentSurface.set_source_rgba(0.5, 0.5, 0.5, 0.5);
	ctxtForTranslucentSurface.set_compositing_operator(compositing_operator::add);
	ctxtForTranslucentSurface.paint();
	translucentSurface.flush();
	ctxt.set_source_surface(translucentSurface, 600.0, 400.0);
	ctxt.move_to(600.0, 400.0);
	ctxt.rel_line_to(100.0, 0.0);
	ctxt.rel_line_to(0.0, 100.0);
	ctxt.rel_line_to(-100.0, 0.0);
	ctxt.close_path();
	ctxt.fill();
	ctxt.set_source_surface(translucentSurface, 650.0, 400.0);
	ctxt.move_to(650.0, 400.0);
	ctxt.rel_line_to(100.0, 0.0);
	ctxt.rel_line_to(0.0, 100.0);
	ctxt.rel_line_to(-100.0, 0.0);
	ctxt.close_path();
	ctxt.fill();
	ctxt.restore();

	ctxt.save();
	auto ctxtTarget = ctxt.get_target();
	auto subsurface = surface(ctxtTarget, 10.5, 11.0, 50.0, 50.0);
	auto subcontext = context(subsurface);
	subcontext.set_source_rgb(0.0, 0.0, 0.0);
	subcontext.move_to(2.0, 2.0);
	subcontext.rel_line_to(48.0, 0.0);
	subcontext.set_line_width(3.0);
	subcontext.set_line_cap(line_cap::butt);
	subcontext.stroke();
	ctxt.restore();

	ctxt.save();
	matrix m;
	m.init_translate(300.0, 400.0);
	const double two_pi = 3.1415926535897932 * 2.0;
	m.rotate(two_pi * (fmod(timer, 4000.0) / 4000.0));
	ctxt.set_matrix(m);
	ctxt.new_path();
	ctxt.move_to(-100.0, 0.0);
	ctxt.line_to(100.0, 0.0);
	ctxt.line_to(0.0, 200.0);
	ctxt.close_path();
	ctxt.set_line_width(3.0);
	ctxt.set_dash({ 0.0, 10.0 }, 0.0);
	ctxt.set_line_cap(line_cap::round);

	ctxt.set_source_rgb(1.0, 0.0, 0.0);
	ctxt.fill_preserve();
	ctxt.set_source_rgb(0.0, 0.0, 0.0);
	ctxt.stroke();
	ctxt.restore();

	ctxt.set_source_rgb(1.0, 1.0, 1.0);
	ctxt.move_to(100.0, 100.0);
	ctxt.select_font_face("Segoe UI", font_slant::normal, font_weight::normal);
	ctxt.set_font_size(30.0);
	ctxt.show_text("Hello C++!");
}
