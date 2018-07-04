#include "window.h"
#include <iostream>
#include <fstream>
#include <io2d.h>
#include "svg.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

static string Load( const string &path ) {
    ifstream file(path);
    if( !file.is_open() )
        return {};
    return string{ istreambuf_iterator<char>(file), istreambuf_iterator<char>() };
}

static optional<image_surface> Render( const string& svg, float scale = 1.f ) {
    try {
        return RenderSVG(svg, scale);
    }
    catch (const exception& /*e*/) {
        return nullopt;
    }
}

void RunWindowed( const string &path_in ) {
    auto data = Load(path_in);
    auto canonical = Render(data);
    if( !canonical )
        return;
    auto canonical_dims = canonical->dimensions();
    
    auto scale = 1.f;
    auto dims = display_point{};
    auto img_brush = optional<io2d::brush>{};
    auto build = [&](int target_width, int target_heigt) {
        scale = min(float(target_width) / float(canonical_dims.x()), float(target_heigt) / float(canonical_dims.y()));
        auto new_img = Render(data, scale);
        dims = new_img->dimensions();
        img_brush = io2d::brush{ move(*new_img)};
    };
    build(640, 480);
    
    output_surface display{ 640, 480, format::argb32, scaling::letterbox, refresh_style::fixed, 30.0f };
    display.size_change_callback([&](output_surface& os) {
        display.dimensions(display.display_dimensions());        
        build(os.dimensions().x(), os.dimensions().y());
    });
    display.draw_callback([&](output_surface& os) {
        os.paint(brush{rgba_color::white});
        path_builder pb;
        pb.new_figure({0.0f, 0.0f});
        pb.rel_line(point_2d(static_cast<float>(dims.x()), 0.0f));
        pb.rel_line(point_2d(0.0f, static_cast<float>(dims.y())));
        pb.rel_line(point_2d(static_cast<float>(-dims.x()), 0.0f));
        pb.rel_line(point_2d(0.0f, static_cast<float>(-dims.y())));
        pb.close_figure();
        os.fill(*img_brush, pb);
    });
    display.begin_show();
}
