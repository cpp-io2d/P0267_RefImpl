#pragma once

#include <io2d.h>
#include <string>

std::optional<std::experimental::io2d::image_surface> RenderSVG( const std::string &data, float scale = 1.0f);
