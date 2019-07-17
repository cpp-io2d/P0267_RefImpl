#include <io2d.h>

using namespace std::experimental::io2d;

int main(int /*argc*/, char** /*argv*/) {
	auto output = output_surface{ 1600, 1600, format::argb32, scaling::none, refresh_style::fixed, 30.f };
	auto timesFont = font("Times New Roman", font_size_units::points, 64.0f, generic_font_names::serif);
	auto limeBrush = brush(rgba_color::lime_green);
	auto linearBrush = brush(point_2d{ 0.0f , 0.0f }, point_2d{ 100.0f, 0.0f }, { gradient_stop{ 0.0f, rgba_color::red
		}, gradient_stop{ 1.0f, rgba_color::blue } });
	output.draw_callback([&](output_surface& sfc) {
		sfc.clear();
		sfc.draw_text(point_2d{ 50.0f, 350.0f }, limeBrush, timesFont, "Hello modern world!");
		sfc.draw_text(point_2d{ 50.0f, 700.0f }, linearBrush, timesFont, u8"こんにちは新世界！", std::nullopt, brush_props(wrap_mode::reflect));
		sfc.draw_text(point_2d{ 50.0f, 1050.0f }, limeBrush, timesFont, "Hallo moderne Welt!");
		});
	output.begin_show();
}
