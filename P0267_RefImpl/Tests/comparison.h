#pragma once

#include <ostream>
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

bool CompareImages(std::experimental::io2d::image_surface &first,
                   std::experimental::io2d::image_surface &second,
                   float intensity_tolerance = 0.f,
                   int spatial_tolerance = 0);

// TODO: move it into IO2D itself?
namespace std::experimental::io2d {
inline std::ostream& operator<<(std::ostream& stream, const rgba_color& color) {
    stream << "{";
    stream << to_string(static_cast<int>(color.r() * 255.f)) << ",";
    stream << to_string(static_cast<int>(color.g() * 255.f)) << ",";
    stream << to_string(static_cast<int>(color.b() * 255.f)) << ",";
    stream << to_string(static_cast<int>(color.a() * 255.f)) << "}";
    return stream;
}
}
