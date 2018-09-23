#include "model.h"
#include "external/pugixml/src/pugixml.hpp"
#include <iostream>
#include <string_view>
#include <cmath>
#include <algorithm>
#include <assert.h>

static Model::Road::Type String2RoadType(std::string_view type)
{
    if( type == "motorway" )        return Model::Road::Motorway;
    if( type == "trunk" )           return Model::Road::Trunk;
    if( type == "primary" )         return Model::Road::Primary;
    if( type == "secondary" )       return Model::Road::Secondary;    
    if( type == "tertiary" )        return Model::Road::Tertiary;
    if( type == "residential" )     return Model::Road::Residential;
    if( type == "living_street" )   return Model::Road::Residential;    
    if( type == "service" )         return Model::Road::Service;
    if( type == "unclassified" )    return Model::Road::Unclassified;
    if( type == "footway" )         return Model::Road::Footway;
    if( type == "bridleway" )       return Model::Road::Footway;
    if( type == "steps" )           return Model::Road::Footway;
    if( type == "path" )            return Model::Road::Footway;
    if( type == "pedestrian" )      return Model::Road::Footway;    
    return Model::Road::Invalid;    
}

static Model::Landuse::Type String2LanduseType(std::string_view type)
{
    if( type == "commercial" )      return Model::Landuse::Commercial;
    if( type == "construction" )    return Model::Landuse::Construction;
    if( type == "grass" )           return Model::Landuse::Grass;
    if( type == "forest" )          return Model::Landuse::Forest;
    if( type == "industrial" )      return Model::Landuse::Industrial;
    if( type == "railway" )         return Model::Landuse::Railway;
    if( type == "residential" )     return Model::Landuse::Residential;    
    return Model::Landuse::Invalid;
}

Model::Model( const std::vector<std::byte> &xml )
{
    LoadData(xml);

    AdjustCoordinates();

    std::sort(m_Roads.begin(), m_Roads.end(), [](const auto &_1st, const auto &_2nd){
        return (int)_1st.type < (int)_2nd.type; 
    });
}

void Model::LoadData(const std::vector<std::byte> &xml)
{
    using namespace pugi;
    
    xml_document doc;
    if( !doc.load_buffer(xml.data(), xml.size()) )
        throw std::logic_error("failed to parse the xml file");
    
    if( auto bounds = doc.select_nodes("/osm/bounds"); !bounds.empty() ) {
        auto node = bounds.first().node();
        m_MinLat = atof(node.attribute("minlat").as_string());
        m_MaxLat = atof(node.attribute("maxlat").as_string());
        m_MinLon = atof(node.attribute("minlon").as_string());
        m_MaxLon = atof(node.attribute("maxlon").as_string());
    }
    else 
        throw std::logic_error("map's bounds are not defined");

    std::unordered_map<std::string, int> node_id_to_num;
    for( const auto &node: doc.select_nodes("/osm/node") ) {
        node_id_to_num[node.node().attribute("id").as_string()] = (int)m_Nodes.size();
        m_Nodes.emplace_back();        
        m_Nodes.back().y = atof(node.node().attribute("lat").as_string());
        m_Nodes.back().x = atof(node.node().attribute("lon").as_string());
    }

    std::unordered_map<std::string, int> way_id_to_num;    
    for( const auto &way: doc.select_nodes("/osm/way") ) {
        auto node = way.node();
        
        const auto way_num = (int)m_Ways.size();
        way_id_to_num[node.attribute("id").as_string()] = way_num;
        m_Ways.emplace_back();
        auto &new_way = m_Ways.back();
        
        for( auto child: node.children() ) {
            auto name = std::string_view{child.name()}; 
            if( name == "nd" ) {
                auto ref = child.attribute("ref").as_string();
                if( auto it = node_id_to_num.find(ref); it != end(node_id_to_num) )
                    new_way.nodes.emplace_back(it->second);
            }
            else if( name == "tag" ) {
                auto category = std::string_view{child.attribute("k").as_string()};
                auto type = std::string_view{child.attribute("v").as_string()};
                if( category == "highway" ) {
                    if( auto road_type = String2RoadType(type); road_type != Road::Invalid ) {
                        m_Roads.emplace_back();
                        m_Roads.back().way = way_num;
                        m_Roads.back().type = road_type;
                    }
                }
                if( category == "railway" ) {
                    m_Railways.emplace_back();
                    m_Railways.back().way = way_num;
                }                
                else if( category == "building" ) {
                    m_Buildings.emplace_back();
                    m_Buildings.back().outer = {way_num};
                }
                else if( category == "leisure" ||
                        (category == "natural" && (type == "wood"  || type == "tree_row" || type == "scrub" || type == "grassland")) ||
                        (category == "landcover" && type == "grass" ) ) {
                    m_Leisures.emplace_back();
                    m_Leisures.back().outer = {way_num};
                }
                else if( category == "natural" && type == "water" ) {
                    m_Waters.emplace_back();
                    m_Waters.back().outer = {way_num};
                }
                else if( category == "landuse" ) {
                    if( auto landuse_type = String2LanduseType(type); landuse_type != Landuse::Invalid ) {
                        m_Landuses.emplace_back();
                        m_Landuses.back().outer = {way_num};
                        m_Landuses.back().type = landuse_type;
                    }                    
                }
            }
        }
    }
    
    for( const auto &relation: doc.select_nodes("/osm/relation") ) {
        auto node = relation.node();
        auto noode_id = std::string_view{node.attribute("id").as_string()};
        std::vector<int> outer, inner;
        auto commit = [&](Multipolygon &mp) {
            mp.outer = std::move(outer);
            mp.inner = std::move(inner);
        };
        for( auto child: node.children() ) {
            auto name = std::string_view{child.name()}; 
            if( name == "member" ) {
                if( std::string_view{child.attribute("type").as_string()} == "way" ) {
                    if( !way_id_to_num.count(child.attribute("ref").as_string()) )
                        continue;
                    auto way_num = way_id_to_num[child.attribute("ref").as_string()];
                    if( std::string_view{child.attribute("role").as_string()} == "outer" )
                        outer.emplace_back(way_num);
                    else
                        inner.emplace_back(way_num);
                }
            }
            else if( name == "tag" ) { 
                auto category = std::string_view{child.attribute("k").as_string()};
                auto type = std::string_view{child.attribute("v").as_string()};
                if( category == "building" ) {
                    commit( m_Buildings.emplace_back() );
                    break;
                }
                if( category == "natural" && type == "water" ) {
                    commit( m_Waters.emplace_back() );
                    BuildRings(m_Waters.back());
                    break;
                }
                if( category == "landuse" ) {
                    if( auto landuse_type = String2LanduseType(type); landuse_type != Landuse::Invalid ) {
                        commit( m_Landuses.emplace_back() );
                        m_Landuses.back().type = landuse_type;
                        BuildRings(m_Landuses.back());
                    }
                    break;
                }
            }
        }
    }
}

void Model::AdjustCoordinates()
{    
    const auto pi = 3.14159265358979323846264338327950288;
    const auto deg_to_rad = 2. * pi / 360.;
    const auto earth_radius = 6378137.;
    const auto lat2ym = [&](double lat) { return log(tan(lat * deg_to_rad / 2 +  pi/4)) / 2 * earth_radius; };
    const auto lon2xm = [&](double lon) { return lon * deg_to_rad / 2 * earth_radius; };     
    const auto dx = lon2xm(m_MaxLon) - lon2xm(m_MinLon);
    const auto dy = lat2ym(m_MaxLat) - lat2ym(m_MinLat);
    const auto min_y = lat2ym(m_MinLat);
    const auto min_x = lon2xm(m_MinLon);
    m_MetricScale = std::min(dx, dy);
    for( auto &node: m_Nodes ) {
        node.x = (lon2xm(node.x) - min_x) / m_MetricScale;
        node.y = (lat2ym(node.y) - min_y) / m_MetricScale;        
    }
}

static bool TrackRec(const std::vector<int> &open_ways,
                     const Model::Way *ways,
                     std::vector<bool> &used,
                     std::vector<int> &nodes) 
{
    if( nodes.empty() ) {
        for( int i = 0; i < open_ways.size(); ++i )
            if( !used[i] ) {
                used[i] = true;
                const auto &way_nodes = ways[open_ways[i]].nodes;
                nodes = way_nodes;
                if( TrackRec(open_ways, ways, used, nodes) )
                    return true;
                nodes.clear();
                used[i] = false;
            }
        return false;
    }
    else {
        const auto head = nodes.front();
        const auto tail = nodes.back();
        if( head == tail && nodes.size() > 1 )
            return true;
        for( int i = 0; i < open_ways.size(); ++i )
            if( !used[i] ) {
                const auto &way_nodes = ways[open_ways[i]].nodes;
                const auto way_head = way_nodes.front();
                const auto way_tail = way_nodes.back();
                if( way_head == tail || way_tail == tail ) {
                    used[i] = true;
                    const auto len = nodes.size();
                    if( way_head == tail ) 
                        nodes.insert(nodes.end(), way_nodes.begin(), way_nodes.end());
                    else
                        nodes.insert(nodes.end(), way_nodes.rbegin(), way_nodes.rend());
                    if( TrackRec(open_ways, ways, used, nodes) )
                        return true;
                    nodes.resize(len);                    
                    used[i] = false;
                }
            }
        return false;
    }
}

static std::vector<int> Track(std::vector<int> &open_ways, const Model::Way *ways)
{
    assert( !open_ways.empty() );
    std::vector<bool> used(open_ways.size(), false);
    std::vector<int> nodes;    
    if( TrackRec(open_ways, ways, used, nodes) )
        for( int i = 0; i < open_ways.size(); ++i )
            if( used[i] )
                open_ways[i] = -1;
    return nodes;
}

void Model::BuildRings( Multipolygon &mp )
{
    auto is_closed = []( const Model::Way &way ) {
        return way.nodes.size() > 1 && way.nodes.front() == way.nodes.back();    
    };

    auto process = [&]( std::vector<int> &ways_nums ) {
        auto ways = m_Ways.data();
        std::vector<int> closed, open;
        
        for( auto &way_num: ways_nums )
            (is_closed(ways[way_num]) ? closed : open).emplace_back(way_num);  
        
        while( !open.empty() ) {            
            auto new_nodes = Track(open, ways);
            if( new_nodes.empty() )
                break;
            open.erase(std::remove_if(open.begin(), open.end(), [](auto v){return v < 0;}), open.end() );
            closed.emplace_back( (int)m_Ways.size() );
            Model::Way new_way;
            new_way.nodes = std::move(new_nodes);
            m_Ways.emplace_back(new_way);
        }        
        std::swap(ways_nums, closed);        
    };

    process(mp.outer);
    process(mp.inner);
}
