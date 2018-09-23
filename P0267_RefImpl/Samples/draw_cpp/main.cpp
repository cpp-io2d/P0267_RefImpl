#include <iostream>
#include <io2d.h>

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

void DrawCPP()
{
    auto img = image_surface{format::argb32, 300, 200};
    img.clear();

    auto surface_brush = brush{ image_surface{"texture.jpg", image_file_format::jpeg, format::argb32 } };
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
    
    img.save("cpp.png", image_file_format::png);
}

int main(int /*argc*/, const char** /*argv*/) {
	DrawCPP();
    return 0;
}
