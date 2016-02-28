#include <io2d.h>

#include <fstream>
#include "tga_header.h"

namespace io2d = std::experimental::io2d;

void save_surface_to_tga_file(io2d::image_surface& surface,
                              std::string const& fileName)
{
    tga::header tga_header;
    tga_header.image_type = tga::image_type::true_color;
    tga_header.image_spec.width = surface.width();
    tga_header.image_spec.height = surface.height();
    tga_header.image_spec.depth = 32;
    tga_header.image_spec.descriptor.top = 1;

    std::ofstream ofs(fileName, std::ofstream::binary);
    ofs.write(reinterpret_cast<const char*>(&tga_header),
              sizeof(tga_header));

    auto bytes = surface.data();
    ofs.write(reinterpret_cast<const char*>(&bytes[0]),
            bytes.size());
}

int main ()
{
    io2d::image_surface image(io2d::format::argb32, 240, 80);

    io2d::simple_font_face consolas("Consolas", io2d::font_slant::normal,
                                    io2d::font_weight::bold);
    image.font_face(consolas);
    image.font_size(32.0);

    io2d::brush cyan(io2d::rgba_color::cyan());
    image.brush(cyan);

    image.render_text("Hello World", {20.0, 50.0});

    save_surface_to_tga_file(image, "hello.tga");
}
