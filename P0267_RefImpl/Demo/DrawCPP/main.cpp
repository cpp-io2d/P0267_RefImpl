//
//  main.cpp
//  io2dts_cg
//
//  Created by Michael Kazakov on 06/02/2018.
//  Copyright © 2018 Michael Kazakov. All rights reserved.
//

#include <iostream>
#include <io2d.h>

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

void Draw( output_surface &surface )
{
    auto b = brush{ rgba_color(1.0, 0.5, 0.5, 1.0) };
    
    auto path = path_builder{};
    path.clear();
//    path.new_figure({100, 100});
//    path.rel_line({299, 299});
//    path.rel_line({0, -400});
//    path.line({0,400});
    static auto aa = 0.f;
    aa += 0.1;
    path.new_figure({100 + sin(aa)*10, 0 + cos(aa)*10});
    path.rel_line({50, 0});
    path.rel_line({0, 50});
    path.rel_line({-50, 0});
    path.close_figure();
    
    auto ip_path = interpreted_path( begin(path), end(path) );
    
    stroke_props sp{5, line_cap::round, line_join::round};
    
    render_props rp(antialias::best,
                    matrix_2d{0.5, 0, 0, 0.5, 0, 0},
                    compositing_op::over);
    
    dashes d{0., {10.}};
    
    surface.stroke(b, path, nullopt, sp, d, rp);
    
    
//    auto now = std::chrono::steady_clock::now();
//    static auto previous = now;
//    auto interval = std::chrono::duration_cast<std::chrono::milliseconds>(now - previous).count();
//    cout << interval << endl;
//    previous = now;
}

//namespace
//{
//    auto anti_clockwise_key = 'Q';
//    auto clockwise_key = 'W';
//    auto thrust_key = 'U';
//    auto fire_key = 'I';
//    auto hyperspace_key = 'O';
//}

//void rocks_in_space::get_key_states()
//{
//    auto anti_clockwise_key = 12; // Q
//    auto clockwise_key = 13; // W
//    auto thrust_key = 32; // U
//    auto fire_key = 34; // I
//    auto hyperspace_key = 31; // O
//    auto get = [](uint16_t key){ return CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState, key); };
//     press() = { get(anti_clockwise_key), get(clockwise_key), get(thrust_key), get(fire_key), get(hyperspace_key)};
//}
//
//void RunAsteroids()
//{
//    rocks_in_space::game game;
////    output_surface display{ 640, 480, format::argb32 };
//    output_surface display{ 640, 480, format::argb32, scaling::letterbox, refresh_style::fixed, 60.0f };
//    display.draw_callback([&](output_surface& os) { game.update<output_surface>(os); });
//    display.begin_show();
//}

void TestRotate()
{
    auto img = image_surface{ format::argb32, 500, 500 };
    img.clear();
    
    auto path = path_builder{};
    path.rel_matrix(matrix_2d::init_rotate(io2d::pi<float> / 4));
    path.new_figure({ -50, -50 });
    path.line({ 50, -50 });
    path.line({ 50, 50 });
    path.line({ -50, 50 });
    path.line({ -50, -50 });
    path.close_figure();
    
    img.stroke(brush{ rgba_color(1.0, 0.5, 0.5, 1.0) }, path);
    
    img.save("/Users/migun/Desktop/test.png", image_file_format::png);
}

void TestTransform()
{
    auto img = image_surface{format::argb32, 500, 500};
    img.clear();
    
    auto path = path_builder{};
    path.clear();


    // I*Tr*Rot * Pt
    
//                ctx.transform = ctx.transform * figure.matrix();

//    auto pt = matrix_2d::init_rotate(io2d::pi<float>/4, {50, 50}).transform_pt({50, 50});
//    auto pt1 = matrix_2d::init_translate({50, 50}).transform_pt({50, 50});
//    auto pt2 = ( matrix_2d::init_translate({50, 50}) * matrix_2d::init_rotate(io2d::pi<float>/4) ).transform_pt({50, 50});
//    auto pt3 = (
//                ( matrix_2d::init_translate({50, 50}) * matrix_2d::init_rotate(io2d::pi<float>/4) )
//                * matrix_2d::init_translate({-50, -50})
//                ).transform_pt({50, 50});
    
    
    // Pt * I*Rot*Tr
    path.rel_matrix(matrix_2d::init_translate({-50, -50}));
    path.rel_matrix(matrix_2d::init_rotate(io2d::pi<float>/4));
    path.rel_matrix(matrix_2d::init_translate({50, 50}));

//    path.rel_matrix(matrix_2d::init_rotate(io2d::pi<float>/4, {-50, -50}));
    
    path.rel_matrix(matrix_2d::init_translate({200, 200}));
    
//    init_translate
    
//    path.rel_matrix(matrix_2d::init_rotate(io2d::pi<float>/4));
//    path.rel_matrix(matrix_2d::init_translate({-50, -50}));

//    path.rel_matrix(matrix_2d::init_translate({50, 50}));

//            return multiply(multiply(init_translate(origin), init_rotate(radians)), init_translate(negate(origin)));
    
//    path.rel_matrix(matrix_2d::init_rotate(io2d::pi<float>/4, {50, 50}));

//    path.rel_matrix(matrix_2d::init_translate({250, 250}));
    
    path.new_figure({0, 0});
//    path.line({100, 0});
//    path.line({100, 100});
//    path.line({0, 100});
//    path.line({0, 0});

    path.rel_line({100, 0});
    path.rel_line({0, 100});
    path.rel_line({-100, 0});
    path.rel_line({0, -100});

    
//    path.new_figure({-50, -50});
//    path.line({50, -50});
//    path.line({50, 50});
//    path.line({-50, 50});
//    path.line({-50, -50});

    
//    path.close_figure();
 
    img.stroke(brush{ rgba_color(1.0, 0.5, 0.5, 1.0) }, path);
    img.save("/Users/migun/Desktop/test.png", image_file_format::png);

    
}

void TestDrawCPP()
{
    auto img = image_surface{format::argb32, 300, 200};
    img.clear();

    auto surface_brush = brush{ image_surface{"/Library/Desktop Pictures/Abstract Shapes.jpg", image_file_format::jpeg, format::argb32 } };
//    auto shadow_brush = brush{ rgba_color(0.5, 0.5, 0.5, 0.6) };
    auto shadow_brush = brush{ rgba_color::alice_blue };
    auto shadow_offset = figure_items::rel_matrix(matrix_2d::init_translate({ -2.0, -2.0f }));
    auto pb = path_builder{};
    
    // Create the "C".
    auto scl = matrix_2d::init_scale({ 0.9f, 1.1f });
    pb.rel_matrix(scl);
    pb.new_figure( point_2d{ 140.0f, 100.0f } * scl.inverse() + point_for_angle<default_graphics_math>(half_pi<float> / 2.0f, 50.0f) );
    pb.arc({ 50.0f, 50.0f }, three_pi_over_two<float>, half_pi<float> / 2.0f);
    img.stroke(shadow_brush, pb, nullopt, stroke_props{ 10.0f });
    pb.insert(pb.begin(), shadow_offset);
    img.stroke(surface_brush, pb, nullopt, stroke_props{ 10.0f });
    
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
    pb.insert(pb.begin(), shadow_offset);
    img.fill(surface_brush, pb);
    pb.erase(pb.begin());

    // Create the second "+".
    pb.insert(pb.begin(), figure_items::rel_matrix(matrix_2d::init_translate({ 80.0f, 0.0f })));
    img.fill(shadow_brush, pb);
    pb.insert(pb.begin(), shadow_offset);
    img.fill(surface_brush, pb);
    
    img.save("test.png", image_file_format::png);
}

void TestDrawWithRadialBrush()
{
    auto img = image_surface{format::argb32, 500, 500};
    img.clear();
    
    auto path = path_builder{};
    path.clear();
//    path.rel_matrix(matrix_2d::init_translate({200, 200}));
    path.new_figure({0, 0});
    path.rel_line({100, 0});
    path.rel_line({0, 100});
    path.rel_line({-100, 0});
    path.rel_line({0, -100});
    path.close_figure();
    
    
//    CGFloat redBallColors[] = {
//        1.0, 0.9, 0.9, 0.7,
//        1.0, 0.0, 0.0, 0.8
//    };
//    CGFloat glossLocations[] = {0.05, 0.9};
//    CGGradientRef ballGradient = CGGradientCreateWithColorComponents(baseSpace, redBallColors, glossLocations, 2);
//    CGRect circleBounds = CGRectMake(20, 250, 100, 100);
//    startPoint = CGPointMake(50, 270);
//    endPoint = CGPointMake(70, 300);
//    CGContextDrawRadialGradient(context, ballGradient, startPoint, 0, endPoint, 50, 0);
    
//    auto br = brush(circle({20, 20}, 100),
//                    circle({70, 70}, 20),
//                    { gradient_stop(0, rgba_color(1., 0.9, 0.9, 1.)),
//                        gradient_stop(1, rgba_color(1., 0., 0., 1.)) }
//                    );

//    auto br = brush(circle({20, 20}, 0),
//                    circle({80, 80}, 150),
//                    { gradient_stop(0, rgba_color(1., 0.9, 0.9, 1.)),
//                        gradient_stop(1, rgba_color(1., 0., 0., 1.)) }
//                    );

    auto br = brush({20, 20},
                    {80, 80},
                    { gradient_stop(0, rgba_color(1., 0.9, 0.9, 1.)),
                        gradient_stop(1, rgba_color(1., 0., 0., 1.)) }
                    );
    
    auto props = brush_props{};
    props.wrap_mode(wrap_mode::repeat);
//    props.brush_matrix(matrix_2d::init_translate({ -200, -200 }));

//    img.fill(br, path, props);
    img.stroke(br, path, props, stroke_props{20} );
    
    img.save("/Users/migun/Desktop/test.png", image_file_format::png);
}

void TestCubicCurve()
{
    auto img = image_surface{ format::argb32, 500, 500 };
    img.clear();
    
    auto path = path_builder{};
    path.clear();
    
    path.new_figure({ 100, 100 });
    
//    path.cubic_curve({ 150, 150 }, { 200, 150 }, { 250, 100 });
//    path.rel_cubic_curve({ 50, 50 }, { 50, 0}, { 50, -50 });
//    path.quadratic_curve({ 100, 200 }, { 200, 200 });
    
    path.rel_quadratic_curve({ 0, 200 }, { 200, -200 });
    
    img.stroke(brush{ rgba_color(1.0, 0.5, 0.5, 1.0) }, path);
    img.save("/Users/migun/Desktop/test.png", image_file_format::png);
}


void TestClipping()
{
    auto img = image_surface{ format::argb32, 500, 500 };
    img.clear();
    
    auto path = path_builder{};
    path.clear();
    
    path.new_figure({ 100, 100 });
    
    //path.cubic_curve({ 150, 150 }, { 200, 150 }, { 250, 100 });
    
    //    path.rel_cubic_curve({ 50, 50 }, { 50, 0}, { 50, -50 });
    
    //    path.quadratic_curve({ 100, 200 }, { 200, 200 });
    
    path.rel_quadratic_curve({ 0, 200 }, { 200, -200 });
    
    
    auto cl_path = path_builder{};
    cl_path.clear();
    cl_path.new_figure({ 0, 150 });
    cl_path.rel_line({ 200, 0 });
    cl_path.rel_line({ 0, 50 });
    cl_path.rel_line({ -200, 0 });
    cl_path.rel_line({ 0, -50 });
    cl_path.close_figure();
    
    
    
    
    img.stroke(brush{ rgba_color(1.0, 0.5, 0.5, 1.0) }, path, nullopt, nullopt, nullopt, nullopt, clip_props(cl_path));
    //    img.stroke(brush{ rgba_color(1.0, 0.5, 0.5, 1.0) }, path, nullopt, nullopt, nullopt, nullopt, nullopt);
    
    
    
    
    path.clear();
    path.new_figure({50, 50});
    path.rel_line({50, 0});
    path.rel_line({0, 300});
    path.rel_line({-50, 0});
    path.rel_line({0, -300});
    path.close_figure();
    
    img.fill(brush{ rgba_color(1.0, 1.0, 0.5, 1.0) }, path, nullopt, nullopt, clip_props(cl_path) );
//    img.fill(brush{ rgba_color(1.0, 1.0, 0.5, 1.0) }, path, nullopt, nullopt, nullopt );
//inline void basic_image_surface<GraphicsSurfaces>::fill(, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
    
    
    img.stroke(brush{ rgba_color(1.0, 0.5, 0.5, 1.0) }, cl_path, nullopt, nullopt, nullopt, nullopt, nullopt);
    
    img.save("/Users/migun/Desktop/test.png", image_file_format::png);
}

int main(int argc, const char * argv[]) {
//    {
//        RunAsteroids();
//        return 0;
//    }
    
    {
        TestDrawCPP();
        return 0;
    }
    
    
    auto img = image_surface{format::argb32, 500, 500};
    
//    auto img = image_surface{format::argb32,
//        image_surface::max_dimensions().x(),
//        image_surface::max_dimensions().y()
//    };
    img.clear();
    
    
    auto b = brush{ rgba_color(1.0, 0.5, 0.5, 1.0) };
    
//    auto path = path_builder{};
//    path.clear();
////    auto v = m_physics.position() + (m_path.m_vertices[0]);
//    path.new_figure({100, 100});
//    path.rel_line({299, 299});
//    path.rel_line({0, -400});
//    path.line({0,400});
////    std::for_each(&m_path.m_vertices[1], &m_path.m_vertices[m_path.m_count], [&](const auto& vert)
////                  {
////                      v += vert;
////                      path.line(screen_space(v));
////                  });
//    path.close_figure();
//
//    auto ip_path = interpreted_path( begin(path), end(path) );
//
//    stroke_props sp{10, line_cap::round, line_join::round};
//
//    render_props rp(antialias::best,
//                    matrix_2d{0.5, 0, 0, 0.5, 200, 200},
//                    compositing_op::over);
//
////explicit basic_stroke_props(float w, io2d::line_cap lc = io2d::line_cap::none, io2d::line_join lj = io2d::line_join::miter, float ml = 10.0f) noexcept;
//
//    dashes d{0., {30.}};
    
//    auto path = path_builder{};
//    path.clear();
//    path.new_figure({0, 100});
//    path.line({500, 100});
//    path.close_figure();
//    stroke_props sp{10, line_cap::none, line_join::round};
//    dashes d{0., {30., 30., 20., 20., 10., 10.}};
//    img.stroke(b, path, nullopt, sp, d);

    
    auto path = path_builder{};
    path.clear();
//    path.new_figure({100, 100});
//    path.line({200, 100});
//    path.line({200, 200});
//    path.line({100, 200});
//    path.line({100, 100});

//        path.new_figure({50, 50});
//        path.line({450, 50});
//        path.line({450, 450});
//        path.line({50, 450});
//        path.line({50, 50});

//    path.rel_matrix(matrix_2d::init_rotate(0.5, {128, 128}));
    
    path.rel_matrix(matrix_2d::init_translate({-50, -50}));
//    path.rel_matrix(matrix_2d::init_rotate(M_PI / 4));

//    path.rel_matrix(matrix_2d::init_rotate(3.14 ));
    
    path.rel_matrix(matrix_2d::init_rotate(3.9 ));

//    auto alpha = 3.9;
//    path.rel_matrix(matrix_2d{ cosf(alpha), -sinf(alpha), sinf(alpha), cosf(alpha), 0.f, 0.f });
    
//    cairo_translate (cr, 128.0, 128.0);
//    cairo_rotate (cr, M_PI / 4);
//    cairo_scale (cr, 1 / sqrt (2), 1 / sqrt (2));
//    cairo_translate (cr, -128.0, -128.0);
    path.rel_matrix(matrix_2d::init_translate({50, 50}));
    
    path.rel_matrix(matrix_2d::init_translate({200, 200}));
    
//    path.new_figure({100, 100});
//    path.new_figure({0, 0});
//    path.line({256, 0});
//    path.line({256, 256});
//    path.line({0, 256});
//    path.line({0, 0});

    
    path.new_figure({0, 0});
    path.line({100, 0});
    path.line({100, 100});
    path.line({0, 100});
    path.line({0, 0});

    
    
//    path.rel_line({256, 0});
//    path.rel_line({0, 256});
//    path.rel_line({-256, 0});
//    path.rel_line({0, -256});
    
    
//    path.rel_line({256, 0});
//    path.rel_line({0, 192});
////    path.rel_line({0, 70});
////    path.rel_line({-256, -70});
//    path.rel_line({-256, 0});
//    path.rel_line({0, -192});

    
    path.close_figure();
    stroke_props sp{30, line_cap::round, line_join::round};
//    dashes d{0., {30., 30., 20., 20., 10., 10.}};
    
//    img.stroke(b, path, nullopt, sp, nullopt);

    img.stroke(b, path);
    
//    img.fill(brush{ rgba_color(1.0, 0.5, 0.5, 1.0) }, path);
//    img.stroke(brush{ rgba_color(0.5, 1.0, 0.5, 0.5) }, path, nullopt, sp, nullopt);
    
    
//    image_surface pict{"/Users/migun/Desktop/pict.jpg", image_file_format::jpeg, format::argb32};
    image_surface pattern{"/Users/migun/Desktop/romedalen.png", image_file_format::png, format::argb32};
//    pattern.save("/Users/migun/Desktop/romedalen1.jpg", image_file_format::jpeg);
    
    
//    brush surface_brush{ move(pattern) };

//    img.fill(surface_brush, path);
//    img.stroke(surface_brush, path, nullopt, sp, nullopt);
    
//    pict.save("/Users/migun/Desktop/pict1.jpg", image_file_format::jpeg);
    
//void stroke(const basic_brush<GraphicsSurfaces>& b,
//    const basic_path_builder<GraphicsSurfaces, Allocator>& pb,
//    const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt,
//    const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt,
//    const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt,
//    const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt,
//    const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
    
    img.flush();
    
    img.save("/Users/migun/Desktop/test.png", image_file_format::png);
   
//    output_surface{}
//    basic_output_surface(int preferredWidth, int preferredHeight,
//                         io2d::format preferredFormat, io2d::scaling scl = io2d::scaling::letterbox,
//                         io2d::refresh_style rr = io2d::refresh_style::as_fast_as_possible, float fps = 30.0f);
    //output_surface display{ 400, 300, format::argb32, scaling::letterbox, refresh_style::fixed, 30.0f };
//    output_surface display{ 400, 300, format::argb32 };
//    display.auto_clear(true);
//    display.draw_callback(Draw);
//    display.begin_show();

    std::cout << "Hello, World!\n";
    return 0;
}
