#include <io2d.h>
#include <random>
#include <iostream>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;

struct Cat
{
    point_2d scale = {1.f, 1.f};
    float rotation = 0.f;
    float alpha = 1.f;
    float shear_x = 0.f;
    float shear_y = 0.f;
    point_2d position = {0.f, 0.f};
    point_2d speed = {0.f, 0.f};
    point_2d spawn_position = {0.f, 0.f};
    high_resolution_clock::time_point spawn_time;
    int animator = 0;
};

matrix_2d Transformation(const Cat &cat, display_point image_dimenstions)
{
    return matrix_2d::create_translate({-image_dimenstions.x()/2.f, -image_dimenstions.y()/2.f}) *
           matrix_2d::create_scale(cat.scale) *
           matrix_2d::create_shear_x(cat.shear_x) *
           matrix_2d::create_shear_y(cat.shear_y) *
           matrix_2d::create_rotate(cat.rotation) *    
           matrix_2d::create_translate(cat.position);        
}

bool IsVisible(const Cat &cat, display_point image_dimenstions, display_point output_dimensions)
{
    const bounding_box bb{0.f, 0.f, (float)output_dimensions.x(), (float)output_dimensions.y()};
    const auto inside = [&](point_2d p) {
        return p.x() >= bb.top_left().x() && p.x() <= bb.bottom_right().x() &&
               p.y() >= bb.top_left().y() && p.y() <= bb.bottom_right().y();
    };
    const auto mat = Transformation(cat, image_dimenstions);
    return inside(point_2d{0.f, 0.f} * mat) ||
           inside(point_2d{0.f, (float)image_dimenstions.y()} * mat) ||
           inside(point_2d{(float)image_dimenstions.x(), 0.f} * mat) ||
           inside(point_2d{(float)image_dimenstions.x(), (float)image_dimenstions.y()} * mat);
}

path_builder ImagePath( display_point image_dimenstions, matrix_2d /*mat*/ )
{
    auto pb = path_builder{};
    pb.new_figure({0.f, 0.f});
    pb.rel_line({float(image_dimenstions.x()), 0.f});
    pb.rel_line({0.f, float(image_dimenstions.y())});
    pb.rel_line({-float(image_dimenstions.x()), 0.f});
    pb.rel_line({0.f, -float(image_dimenstions.y())});
    pb.close_figure();
    return pb;
}

void Draw(const Cat &cat, const brush &image, display_point image_dimenstions, output_surface& surface)
{
	const auto min_scale = 0.01f;
	if ( abs(cat.scale.x()) < min_scale || abs(cat.scale.y()) < min_scale )
		return;

    auto mat = Transformation(cat, image_dimenstions);
    
    auto rp = render_props{};
    rp.surface_matrix(mat);
    
    auto bp = brush_props{};
    bp.filter(filter::fast);

    auto cp = clip_props{ImagePath(image_dimenstions, mat)};
    
    if( cat.alpha == 1.f ) {
        rp.compositing(compositing_op::source);
        surface.paint(image, bp, rp, cp);
    }        
    else {
        surface.mask(image, brush{rgba_color{1.f, 1.f, 1.f, cat.alpha}}, bp, nullopt, rp, cp);
    }
}

void Resize(Cat &cat, milliseconds now)
{
    const auto scale = 0.5f + (1.f + cosf(float(now.count()) / 500.f)) / 2.f;
    cat.scale = {scale, scale};
}

void Mirror(Cat &cat, milliseconds now)
{
    cat.scale = {cosf(float(now.count()) / 600.f), sinf(float(now.count()) / 600.f)};    
}

void HorizontalMirror(Cat &cat, milliseconds now)
{  
    cat.scale = {cosf(float(now.count()) / 400.f), 1.f};
}

void VerticalMirror(Cat &cat, milliseconds now)
{
    cat.scale = {1.f, cosf(float(now.count()) / 400.f)}; 
}

void Rotate(Cat &cat, milliseconds now)
{
    cat.rotation = float(now.count()) / 1000.f;
}

void Shear(Cat &cat, milliseconds now)
{
    cat.shear_x = (cosf(float(now.count()) / 700.f)) / 2.f;
    cat.shear_y = (sin(float(now.count()) / 700.f)) / 2.f;
}

void Alpha(Cat &cat, milliseconds now)
{
    cat.alpha = (1.f + cosf(float(now.count()) / 400.f)) / 2.f;        
}

void Move(Cat &cat, milliseconds now)
{
    auto dts = float(now.count()) / float(duration_cast<milliseconds>(1s).count()); 
    cat.position = cat.spawn_position + cat.speed * dts; 
}

static const vector<function<void(Cat&, milliseconds)>> g_Animators =
    {Resize, Rotate, Alpha, Shear, Mirror, HorizontalMirror, VerticalMirror};

void Animate(Cat &cat, milliseconds time)
{
    g_Animators[cat.animator](cat, time);
    Move(cat, time);
}

Cat SpawnCat( display_point output_size )
{
    static auto random_engine = default_random_engine{random_device{}()};
    auto animators_distribution = uniform_int_distribution<int>(0, int(g_Animators.size()) - 1);
    auto vertical_distribution = uniform_int_distribution<int>(0, output_size.y() - 1);
    auto ver_speed_distribution = uniform_int_distribution<int>(-30, 30);
    auto hor_speed_distribution = uniform_int_distribution<int>(20, 80);
    
    Cat cat;
    cat.spawn_time = high_resolution_clock::now();
    cat.animator = animators_distribution(random_engine);
    cat.spawn_position.y( float(vertical_distribution(random_engine)) );
    cat.speed.x( float(hor_speed_distribution(random_engine)) );
    cat.speed.y( float(ver_speed_distribution(random_engine)) );    
    return cat;
}

int main(int /*argc*/, char *argv[]) {    
    auto image = [&]{
        try {
            return image_surface{"cat.jpg", image_file_format::jpeg, format::argb32};            
        }
        catch(...) {
            // We're on some weird system like iOS. To avoid bringing Cocoa stuff here, lets instead use a small hack:              
            auto path = string{argv[0]};
            path = path.substr(0, path.length() - "sprites"s.length()) + "cat.jpg"; 
            return image_surface{path, image_file_format::jpeg, format::argb32};
        }
    }();
    const auto image_size = image.dimensions();
    const auto cat_brush = brush{move(image)};
    auto display = output_surface{500, 500, format::argb32, scaling::none};    
    
    vector<Cat> cats;
    const auto cats_target = 15;

    auto draw_frame = [&](output_surface &surface){
        auto should_remove = [&](const Cat &cat){ return !IsVisible(cat, image_size, surface.dimensions()); };
        cats.erase(remove_if(begin(cats), end(cats), should_remove), end(cats));
        while( cats.size() < cats_target )
            cats.insert(begin(cats), SpawnCat(surface.dimensions()));
        
        surface.paint(brush{rgba_color::dark_gray});
        const auto now = high_resolution_clock::now();
        for( auto &c: cats ) {
            Animate(c, duration_cast<milliseconds>(now - c.spawn_time));
            Draw(c, cat_brush, image_size, surface);
        }
    };
    display.draw_callback(draw_frame);    
    display.size_change_callback([&](output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });    
    display.begin_show();    
}
