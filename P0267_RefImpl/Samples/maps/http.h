#pragma once

#include <vector>
#include <cstddef>
#include <string>

// params like "8.81598,47.22277,8.83,47.23"
std::vector<std::byte> FetchOpenStreetMapData( const std::string &bounding_box );

