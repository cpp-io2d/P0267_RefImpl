#include <filesystem>
#include <iostream>
#include <io2d.h>

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

std::filesystem::path input_data_dir;   // Where to load input files/data from; set on app launch

template <typename Surface>
void DrawCPP(Surface & img)
{
    img.clear();

    auto surface_brush = brush{ image_surface{(input_data_dir / "texture.jpg").string().c_str(), image_file_format::jpeg, format::argb32 } };
    auto shadow_brush = brush{ rgba_color(0.5, 0.5, 0.5, 0.6) };
    auto shadow_render = render_props{};
    shadow_render.surface_matrix(matrix_2d::create_translate({ -2.0, -2.0f }));
    
    auto pb = path_builder{};
    
    // Create the "C".
    auto scl = matrix_2d::create_scale({ 0.9f, 1.1f });
    pb.rel_matrix(scl);
    pb.new_figure( point_2d{ 140.0f, 100.0f } * scl.inverse() + point_for_angle<default_graphics_math>(half_pi<float> / 2.0f, 50.0f) );
    pb.arc({ 50.0f, 50.0f }, three_pi_over_two<float>, half_pi<float> / 2.0f);
    img.stroke(shadow_brush, pb, nullopt, stroke_props{ 10.0f });
    img.stroke(surface_brush, pb, nullopt, stroke_props{ 10.0f }, nullopt, shadow_render);
    
    // Create the first "+".
    pb.clear();
    pb.new_figure({ 130.0f, 105.0f });
    point_2d lines[] = { { 0.0f, -10.0f }, { 25.0f,  0.0f }, { 0.0f, -25.0f }, {  10.0f, 0.0f },
                         { 0.0f,  25.0f }, { 25.0f,  0.0f }, { 0.0f,  10.0f }, { -25.0f, 0.0f },
                         { 0.0f,  25.0f }, { -10.0f, 0.0f }, { 0.0f, -25.0f }  };
    for( auto l: lines )
        pb.rel_line(l);
    pb.close_figure();
    img.fill(shadow_brush, pb);
    img.fill(surface_brush, pb, nullopt, shadow_render);

    // Create the second "+".
    pb.insert(pb.begin(), figure_items::rel_matrix(matrix_2d::create_translate({ 80.0f, 0.0f })));
    img.fill(shadow_brush, pb);
    img.fill(surface_brush, pb, nullopt, shadow_render);
}

int main(int argc, const char** argv) {
    if (argc >= 1) {
        input_data_dir = std::filesystem::path(argv[0]).remove_filename();
    }
    std::filesystem::path output_file;
    if (argc >= 2) {
        if (argv[1][0] == '-') {
            std::cerr
                << "Usage: " << std::filesystem::path(argv[0]).filename().u8string() << " [output png file]\n"
                << "\n"
                << "  If the 'output png file' is left unspecified, then the output will be\n"
                << "  displayed in a window.\n"
                << "\n";
            return 1;
        } else {
            output_file = argv[1];
        }
    }

    if (!output_file.empty()) {
        auto img = image_surface{format::argb32, 300, 200};
        DrawCPP(img);
        img.save(output_file.u8string(), image_file_format::png);
    } else {
        auto img = output_surface{300, 200, format::argb32, scaling::none, refresh_style::as_needed, 30.f};
        img.size_change_callback([&](output_surface &surface) {
            surface.dimensions(surface.display_dimensions());
        });
        img.draw_callback([&](auto &surface) {
            DrawCPP(surface);
        });
        img.begin_show();
    }

    return 0;
}
