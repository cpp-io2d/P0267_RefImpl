#include <io2d.h>
#include "data_source.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

class CPUMeter
{
public:
    void Run();
    
private:
    void Update();
    void Display(output_surface& surface) const;
    void DrawBackground(output_surface& surface) const;
    void DrawHorizontalGridLines(output_surface& surface) const;
    void DrawVerticalGridLines(output_surface& surface) const;
    void DrawGraphs(output_surface& surface) const;
    
    DataSource m_Source;
    brush m_FillBrush{ {0, 0}, {0, 1}, { {0.f, rgba_color::green}, {0.4f, rgba_color::yellow}, {1.0f, rgba_color::red}}};
    brush m_CountourBrush{ rgba_color{0, 0, 255, 128} };
    stroke_props m_ContourStrokeProps{1.f};
    brush m_BackgroundFill{rgba_color::alice_blue};
    stroke_props m_GridStrokeProps{1.f};
    brush m_VerticalLinesBrush{ rgba_color::cornflower_blue };
    dashes m_VerticalLinesDashes{0.f, {1.f, 3.f}};
    brush m_HorizontalLinesBrush{ rgba_color::blue };
};

void CPUMeter::Run()
{
    auto display = output_surface{400, 400, format::argb32, scaling::none, refresh_style::fixed, 30};
    display.size_change_callback([](output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](output_surface& surface){
        Update();
        Display(surface);
    });
    display.begin_show();    
}

void CPUMeter::Update()
{
    m_Source.Fetch();
}

void CPUMeter::Display(output_surface& surface) const
{
    DrawBackground(surface);
    DrawVerticalGridLines(surface);
    DrawHorizontalGridLines(surface);
    DrawGraphs(surface);
}

void CPUMeter::DrawBackground(output_surface& surface) const
{
    surface.paint(m_BackgroundFill);
}

void CPUMeter::DrawHorizontalGridLines(output_surface& surface) const
{
    auto cpus = m_Source.CoresCount();
    auto dimensions = surface.dimensions();
    auto height_per_cpu = float(dimensions.y()) / cpus;
    
    auto pb = path_builder{};
    pb.new_figure({0.f, 0.f});
    pb.line({float(dimensions.x()), 0.f});
    auto ip = interpreted_path{pb};
        
    for( auto cpu = 0; cpu < cpus; ++cpu ) {
        auto rp = render_props{};
        rp.surface_matrix(matrix_2d::create_translate({0.f, floorf((cpu+1)*height_per_cpu) + 0.5f}));
        surface.stroke(m_HorizontalLinesBrush, ip, nullopt, m_GridStrokeProps, nullopt, rp);
    }
}

void CPUMeter::DrawVerticalGridLines(output_surface& surface) const
{
    auto pb = path_builder{};    
    pb.new_figure({0.f, 0.f});
    pb.line({0.f, float(surface.dimensions().y())});
    auto ip = interpreted_path{pb};
        
    for( auto x = surface.dimensions().x() - 1; x >= 0; x -= 10 ) {
        auto rp = render_props{};
        rp.surface_matrix(matrix_2d::create_translate({x + 0.5f, 0}));
        surface.stroke(m_VerticalLinesBrush, ip, nullopt, m_GridStrokeProps, m_VerticalLinesDashes, rp);
    }    
}

void CPUMeter::DrawGraphs(output_surface& surface) const
{
    auto cpus = m_Source.CoresCount();    
    auto dimensions = surface.dimensions();
    auto height_per_cpu = float(dimensions.y()) / cpus;
    
    for( auto cpu = 0; cpu < cpus; ++cpu ) {
        auto m = matrix_2d{1, 0, 0, -height_per_cpu, 0, (cpu+1) * height_per_cpu};
        
        auto graph = path_builder{};
        graph.matrix(m);
        auto x = float(dimensions.x());        
        graph.new_figure({x, 0.f});            
        for( auto i = m_Source.SamplesCount() - 1; i >= 0 && x >= 0; --i, --x )
            graph.line({x, m_Source.At(cpu, i) });     
        graph.line({x, 0.f});
        auto contour = graph;            
        graph.line({float(dimensions.x()), 0.f});
        graph.close_figure();
        
        auto bp = brush_props{};
        bp.brush_matrix(m.inverse());
        surface.fill(m_FillBrush, graph, bp);
        
        surface.stroke(m_CountourBrush, contour, nullopt, m_ContourStrokeProps);
    }        
}

int main(int /*argc*/, char** /*argv*/)
{
    CPUMeter meter;
    meter.Run();
}
