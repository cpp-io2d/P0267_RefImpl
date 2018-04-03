#pragma once

#include <string>
#include "io2d.h"

bool ComparePNGExact( const std::string &path1, const std::string &path2 );
bool ComparePNGExact( std::experimental::io2d::image_surface &image, const std::string &path2 );

bool ComparePNGWithTolerance( const std::string &path1, const std::string &path2, float intensity_tolerance = 0.f, int spatial_tolerance = 0 );
bool ComparePNGWithTolerance( std::experimental::io2d::image_surface &image, const std::string &path2, float intensity_tolerance = 0.f, int spatial_tolerance = 0 );

bool CheckPNGColorWithTolerance( const std::string &image_path, int x, int y, std::experimental::io2d::rgba_color color, float intensity_tolerance = 0.f );
bool CheckPNGColorWithTolerance( std::experimental::io2d::image_surface &image, int x, int y, std::experimental::io2d::rgba_color color, float intensity_tolerance = 0.f );
