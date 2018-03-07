#pragma once

#include <string>
#include "io2d.h"

bool ComparePNGExact( const std::string &path1, const std::string &path2 );
bool ComparePNGExact( std::experimental::io2d::image_surface &image, const std::string &path2 );
