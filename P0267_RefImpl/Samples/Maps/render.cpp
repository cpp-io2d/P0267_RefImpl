#include "render.h"
#include <iostream>

static bool IsClosed( const Model::Way &way );
static float RoadMetricWidth(Model::Road::Type type);
static io2d::rgba_color RoadColor(Model::Road::Type type);
static io2d::rgba_color RoadContourColor(Model::Road::Type type);
static io2d::dashes RoadDashes(Model::Road::Type type);
static io2d::stroke_props RoadStrokeProps(Model::Road::Type type);

Render::Render( const Model &model ):
    m_Model(model)
{
    BuildRoadReps();
    BuildLanduseBrushes();
}

void Render::Display( io2d::output_surface &surface )
{
    m_Scale = (float)std::min(surface.dimensions().x(), surface.dimensions().y());    
    surface.paint(m_BackgroundFillBrush);        
    DrawWater(surface);
    DrawLanduses(surface);
    DrawLeisure(surface);
    DrawRailways(surface);
    DrawHighways(surface);    
    DrawBuildings(surface);    
}

void Render::DrawBuildings(io2d::output_surface &surface)
{
    for( auto &building: m_Model.Buildings() ) {
        auto path = PathFromMP(surface, building);
        surface.fill(m_BuildingFillBrush, path);        
        surface.stroke(m_BuildingOutlineBrush, path, std::nullopt, m_BuildingOutlineStrokeProps);
    }
}

void Render::DrawLeisure(io2d::output_surface &surface)
{
    for( auto &leisure: m_Model.Leisures()) {
        auto path = PathFromMP(surface, leisure);
        surface.fill(m_LeisureFillBrush, path);        
        surface.stroke(m_LeisureOutlineBrush, path, std::nullopt, m_LeisureOutlineStrokeProps);
    }
}

void Render::DrawWater(io2d::output_surface &surface)
{
    for( auto &water: m_Model.Waters())
        surface.fill(m_WaterFillBrush, PathFromMP(surface, water));
}

void Render::DrawLanduses(io2d::output_surface &surface)
{
    for( auto &landuse: m_Model.Landuses() ) {
        auto br = m_LanduseBrushes.find(landuse.type);
        if( br == m_LanduseBrushes.end() )
            continue;

        auto path = PathFromMP(surface, landuse);        
        surface.fill(br->second, path);
    }
}

void Render::DrawHighways(io2d::output_surface &surface)
{
    auto ways = m_Model.Ways().data();
    for( auto road: m_Model.Roads() ) {
        auto rep_it = m_RoadReps.find(road.type);
        if( rep_it == std::end(m_RoadReps) )
            continue;
        const auto &rep = rep_it->second;
        
        auto &way = ways[road.way];
        auto path = PathFromWay(surface, way);
        auto road_px_width = rep.metric_width > 0.f ?
            (rep.metric_width / m_Model.MetricScale() * m_Scale ) :
            rep.stroke_props.line_width();        
        if( road_px_width < 0.5f )
            continue;
        
        auto sp = rep.stroke_props;
        if( rep.outline_brush ) {
            // poor man's outlining, since we don't have stroke->path in the API.
            sp.line_width(road_px_width + 0.5);
            surface.stroke(*rep.outline_brush, path, rep.brush_props, sp);
        }
        sp.line_width(road_px_width);
        surface.stroke(rep.brush, path, rep.brush_props, sp, rep.dashes);        
    }
}

void Render::DrawRailways(io2d::output_surface &surface)
{
    auto scale = float(m_Scale / m_Model.MetricScale());     
    auto ways = m_Model.Ways().data();
    for( auto &railway: m_Model.Railways() ) {
        auto &way = ways[railway.way];
        auto path = PathFromWay(surface, way);
        surface.stroke(m_RailwayStrokeBrush, path, std::nullopt, io2d::stroke_props{3.f * scale});
        surface.stroke(m_RailwayDashBrush, path, std::nullopt, io2d::stroke_props{2.f * scale}, m_RailwayDashes);
    }
}

io2d::interpreted_path Render::PathFromWay(io2d::output_surface &surface, const Model::Way &way)
{    
    if( way.nodes.empty() )
        return {};
    
    auto m =  io2d::matrix_2d::create_scale({m_Scale, -m_Scale}) *
              io2d::matrix_2d::create_translate({0.f, (float)surface.dimensions().y()});
    auto pb = io2d::path_builder{};
    pb.matrix(m);
    const auto nodes = m_Model.Nodes().data();    
    auto start = nodes[way.nodes.front()];
    pb.new_figure(io2d::point_2d(start.x, start.y));
    for( auto num: way.nodes ) {
        auto p = nodes[num];
        pb.line(io2d::point_2d(p.x, p.y));
    }
    
    if( IsClosed(way) )    
        pb.close_figure();
    
    return io2d::interpreted_path{pb};
}

io2d::interpreted_path Render::PathFromMP(io2d::output_surface &surface, const Model::Multipolygon &mp)
{
    auto m = io2d::matrix_2d::create_scale({m_Scale, -m_Scale}) * 
             io2d::matrix_2d::create_translate({0.f, (float)surface.dimensions().y()});

    auto pb = io2d::path_builder{};    
    pb.matrix(m);
    const auto nodes = m_Model.Nodes().data();
    const auto ways = m_Model.Ways().data();
    
    auto commit = [&](const Model::Way &way) {
        if( way.nodes.empty() )
            return;
        auto start = nodes[way.nodes.front()];
        pb.new_figure(io2d::point_2d(start.x, start.y));
        for( auto num: way.nodes ) {
            auto p = nodes[num];
            pb.line(io2d::point_2d(p.x, p.y));
        }        
        pb.close_figure();        
    };
    
    for( auto way_num: mp.outer )
        commit( ways[way_num] );
    for( auto way_num: mp.inner )
        commit( ways[way_num] );
    
    return io2d::interpreted_path{pb};
}

void Render::BuildRoadReps()
{
    using R = Model::Road;
    auto types = {R::Motorway, R::Trunk, R::Primary,  R::Secondary, R::Tertiary,
        R::Residential, R::Service, R::Unclassified, R::Footway};
    for( auto type: types ) {
        auto &rep = m_RoadReps[type];
        rep.brush = io2d::brush{ RoadColor(type) };
        rep.metric_width = RoadMetricWidth(type);  
        if( auto c = RoadContourColor(type); c.a() != 0.f )
            rep.outline_brush = io2d::brush{ c }; 
        rep.dashes = RoadDashes(type);
        rep.stroke_props = RoadStrokeProps(type);
    }
}

void Render::BuildLanduseBrushes()
{
    m_LanduseBrushes.insert_or_assign(Model::Landuse::Commercial, io2d::brush{io2d::rgba_color{233, 195, 196}});
    m_LanduseBrushes.insert_or_assign(Model::Landuse::Construction, io2d::brush{io2d::rgba_color{187, 188, 165}});
    m_LanduseBrushes.insert_or_assign(Model::Landuse::Grass, io2d::brush{io2d::rgba_color{197, 236, 148}});
    m_LanduseBrushes.insert_or_assign(Model::Landuse::Industrial, io2d::brush{io2d::rgba_color{223, 197, 220}});
    m_LanduseBrushes.insert_or_assign(Model::Landuse::Railway, io2d::brush{io2d::rgba_color{223, 197, 220}});
    m_LanduseBrushes.insert_or_assign(Model::Landuse::Residential, io2d::brush{io2d::rgba_color{209, 209, 209}});
}

static bool IsClosed( const Model::Way &way )
{
    return way.nodes.size() > 1 && way.nodes.front() == way.nodes.back();  
}

static float RoadMetricWidth(Model::Road::Type type)
{
    if( type == Model::Road::Motorway )        return 6.f;
    if( type == Model::Road::Trunk )           return 6.f;
    if( type == Model::Road::Primary )         return 5.f;
    if( type == Model::Road::Secondary )       return 5.f;    
    if( type == Model::Road::Tertiary )        return 4.f;
    if( type == Model::Road::Residential )     return 2.5f;
    if( type == Model::Road::Service )         return 1.f;
    if( type == Model::Road::Unclassified )    return 2.5f;
    if( type == Model::Road::Footway )         return 0.f;
    return 1.f;
}

static io2d::rgba_color RoadColor(Model::Road::Type type)
{
    if( type == Model::Road::Motorway )        return io2d::rgba_color{226, 122, 143};
    if( type == Model::Road::Trunk )           return io2d::rgba_color{245, 161, 136};
    if( type == Model::Road::Primary )         return io2d::rgba_color{249, 207, 144};
    if( type == Model::Road::Secondary )       return io2d::rgba_color{244, 251, 173};    
    if( type == Model::Road::Tertiary )        return io2d::rgba_color{244, 251, 173};
    if( type == Model::Road::Residential )     return io2d::rgba_color{254, 254, 254};
    if( type == Model::Road::Service )         return io2d::rgba_color{254, 254, 254};
    if( type == Model::Road::Footway )         return io2d::rgba_color{241, 106, 96};    
    if( type == Model::Road::Unclassified )    return io2d::rgba_color{254, 254, 254};
    return io2d::rgba_color::grey;  
}

static io2d::rgba_color RoadContourColor(Model::Road::Type type)
{
    if( type == Model::Road::Motorway )        return io2d::rgba_color{213, 18, 89};
    if( type == Model::Road::Trunk )           return io2d::rgba_color{192, 62, 35};
    if( type == Model::Road::Primary )         return io2d::rgba_color{154, 105, 7};
    if( type == Model::Road::Secondary )       return io2d::rgba_color{105, 121, 1};    
    if( type == Model::Road::Tertiary )        return io2d::rgba_color{157, 157, 157};
    if( type == Model::Road::Residential )     return io2d::rgba_color{189, 184, 184};
    if( type == Model::Road::Service )         return io2d::rgba_color{189, 184, 184};
    if( type == Model::Road::Unclassified )    return io2d::rgba_color{189, 184, 184};    
    
    return io2d::rgba_color::transparent_black;
}

static io2d::dashes RoadDashes(Model::Road::Type type)
{
    if( type == Model::Road::Footway )          return io2d::dashes{0.f, {1.f, 2.f} };    
    return {};
}

static io2d::stroke_props RoadStrokeProps(Model::Road::Type type)
{
    if( type == Model::Road::Footway )          return io2d::stroke_props{1.f, io2d::line_cap::round};
    return {};    
}
