#pragma once

// http://stackoverflow.com/questions/14025735/problems-displaying-targa-tga
namespace tga
{
    enum class color_map_type : uint8_t
    {
        absent  = 0,
        present = 1,
    };

    enum class image_type : uint8_t
    {
        none             = 0,
        color_mapped     = 1,
        true_color       = 2,
        black_white      = 3,
        rle_color_mapped = 9,
        rle_true_color   = 10,
        rle_black_white  = 11,
    };

    #pragma pack(1)
    struct color_map_spec
    {
        uint16_t first_entry_index {0};
        uint16_t length {0};
        uint8_t  entry_size {0};
    };
    static_assert(sizeof(color_map_spec) == 5, "bad size");

    struct image_descriptor
    {
        uint8_t alpha    : 4;
        uint8_t right    : 1;
        uint8_t top      : 1;
        uint8_t reserved : 2;
    };
    static_assert(sizeof(image_descriptor) == 1, "bad size");

    struct image_spec
    {
        uint16_t         x_origin {0};
        uint16_t         y_origin {0};
        uint16_t         width {0};
        uint16_t         height {0};
        uint8_t          depth {0};
        image_descriptor descriptor {0};
    };
    static_assert(sizeof(image_spec) == 10, "bad size");

    struct header
    {
        uint8_t        id_length {0};
        color_map_type color_map_type {color_map_type::absent };
        image_type     image_type;
        color_map_spec color_map_spec;
        image_spec     image_spec;
    };
    static_assert(sizeof(header) == 18, "bad size");
}
