#include <optional>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <io2d.h>
#include "model.h"
#include "render.h"
#include "http.h"

using namespace std::experimental;

static std::optional<std::vector<std::byte>> ReadFile(const std::string &path)
{   
    std::ifstream is{path, std::ios::binary | std::ios::ate};
    if( !is )
        return std::nullopt;
    
    auto size = is.tellg();
    std::vector<std::byte> contents(size);    
    
    is.seekg(0);
    is.read((char*)contents.data(), size);

    if( contents.empty() )
        return std::nullopt;
    return std::move(contents);
}

int main(int argc, const char **argv)
{    
    std::string osm_bounding_box = "";
    std::string osm_data_file = "";
    if( argc > 1 ) {
        for( int i = 1; i < argc; ++i )
            if( std::string_view{argv[i]} == "-b" && ++i < argc )
                osm_bounding_box = argv[i];
            else if( std::string_view{argv[i]} == "-f" && ++i < argc )
                osm_data_file = argv[i];
    }
    else {
        std::cout << "Usage: maps [-b MinLongitude,MinLattitude,MaxLongitude,MaxLattitude] [-f filename.xml]" << std::endl;
        std::cout << "Will use the map of Rapperswil: 8.81598,47.22277,8.83,47.23" << std::endl << std::endl;
        osm_bounding_box = "8.81598,47.22277,8.83,47.23";         
    }
 
    std::vector<std::byte> osm_data;
    
    if( !osm_bounding_box.empty() ) {
        std::cout << "Downloading OpenStreetMap data for the following bounding box: " << osm_bounding_box << std::endl;
        osm_data = FetchOpenStreetMapData( osm_bounding_box );
        if( osm_data.empty() )
            std::cout << "Failed to download." << std::endl;
    }
    
    if( osm_data.empty() && !osm_data_file.empty() ) {
        std::cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << std::endl;
        auto data = ReadFile(osm_data_file);
        if( !data )
            std::cout << "Failed to read." << std::endl;
        else
            osm_data = std::move(*data);
    }
    
    Model model{osm_data};
    Render render{model};
    auto display = io2d::output_surface{400, 400, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
    display.size_change_callback([](io2d::output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);
    });
    display.begin_show();  
}
