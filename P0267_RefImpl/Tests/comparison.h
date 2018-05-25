#pragma once

#include <string>
#include "io2d.h"

bool CompareImageColor(std::experimental::io2d::image_surface &image,
                       int x,
                       int y,
                       std::experimental::io2d::rgba_color color,
                       float intensity_tolerance = 0.f);

bool CompareWithPNGImage(std::experimental::io2d::image_surface &image,
                         const std::string &path_to_reference_image,
                         float intensity_tolerance = 0.f,
                         int spatial_tolerance = 0);
