#include "xio2d.h"

using namespace std;
using namespace std::experimental::io2d;

const rgba_color rgba_color::alice_blue =
	rgba_color{ 240, 248, 255 };

const rgba_color rgba_color::antique_white =
	rgba_color{ 250, 235, 215 };

const rgba_color rgba_color::aqua =
	rgba_color{ 0, 255, 255 };

const rgba_color rgba_color::aquamarine =
	rgba_color{ 127, 255, 212 };

const rgba_color rgba_color::azure =
	rgba_color{ 240, 255, 255 };

const rgba_color rgba_color::beige =
	rgba_color{ 245, 245, 220 };

const rgba_color rgba_color::bisque =
	rgba_color{ 255, 228, 196 };

const rgba_color rgba_color::black =
	rgba_color{ 0, 0, 0 };

const rgba_color rgba_color::blanched_almond =
	rgba_color{ 255, 235, 205 };

const rgba_color rgba_color::blue =
	rgba_color{ 0, 0, 255 };

const rgba_color rgba_color::blue_violet =
	rgba_color{ 138, 43, 226 };

const rgba_color rgba_color::brown =
	rgba_color{ 165, 42, 42 };

const rgba_color rgba_color::burly_wood =
	rgba_color{ 222, 184, 135 };

const rgba_color rgba_color::cadet_blue =
	rgba_color{ 95, 158, 160 };

const rgba_color rgba_color::chartreuse =
	rgba_color{ 127, 255, 0 };

const rgba_color rgba_color::chocolate =
	rgba_color{ 210, 105, 30 };

const rgba_color rgba_color::coral =
	rgba_color{ 255, 127, 80 };

const rgba_color rgba_color::cornflower_blue =
	rgba_color{ 100, 149, 237 };

const rgba_color rgba_color::cornsilk =
	rgba_color{ 255, 248, 220 };

const rgba_color rgba_color::crimson =
	rgba_color{ 220, 20, 60 };

const rgba_color rgba_color::cyan =
	rgba_color{ 0, 255, 255 };

const rgba_color rgba_color::dark_blue =
	rgba_color{ 0, 0, 139 };

const rgba_color rgba_color::dark_cyan =
	rgba_color{ 0, 139, 139 };

const rgba_color rgba_color::dark_goldenrod =
	rgba_color{ 184, 134, 11 };

const rgba_color rgba_color::dark_gray =
	rgba_color{ 169, 169, 169 };

const rgba_color rgba_color::dark_green =
	rgba_color{ 0, 100, 0 };

const rgba_color rgba_color::dark_grey =
	rgba_color{ 169, 169, 169 };

const rgba_color rgba_color::dark_khaki =
	rgba_color{ 189, 183, 107 };

const rgba_color rgba_color::dark_magenta =
	rgba_color{ 139, 0, 139 };

const rgba_color rgba_color::dark_olive_green =
	rgba_color{ 85, 107, 47 };

const rgba_color rgba_color::dark_orange =
	rgba_color{ 255, 140, 0 };

const rgba_color rgba_color::dark_orchid =
	rgba_color{ 153, 50, 204 };

const rgba_color rgba_color::dark_red =
	rgba_color{ 139, 0, 0 };

const rgba_color rgba_color::dark_salmon =
	rgba_color{ 233, 150, 122 };

const rgba_color rgba_color::dark_sea_green =
	rgba_color{ 143, 188, 143 };

const rgba_color rgba_color::dark_slate_blue =
	rgba_color{ 72, 61, 139 };

const rgba_color rgba_color::dark_slate_gray =
	rgba_color{ 47, 79, 79 };

const rgba_color rgba_color::dark_slate_grey =
	rgba_color{ 47, 79, 79 };

const rgba_color rgba_color::dark_turquoise =
	rgba_color{ 0, 206, 209 };

const rgba_color rgba_color::dark_violet =
	rgba_color{ 148, 0, 211 };

const rgba_color rgba_color::deep_pink =
	rgba_color{ 255, 20, 147 };

const rgba_color rgba_color::deep_sky_blue =
	rgba_color{ 0, 191, 255 };

const rgba_color rgba_color::dim_gray =
	rgba_color{ 105, 105, 105 };

const rgba_color rgba_color::dim_grey =
	rgba_color{ 105, 105, 105 };

const rgba_color rgba_color::dodger_blue =
	rgba_color{ 30, 144, 255 };

const rgba_color rgba_color::firebrick =
	rgba_color{ 178, 34, 34 };

const rgba_color rgba_color::floral_white =
	rgba_color{ 255, 250, 240 };

const rgba_color rgba_color::forest_green =
	rgba_color{ 34, 139, 34 };

const rgba_color rgba_color::fuchsia =
	rgba_color{ 255, 0, 255 };

const rgba_color rgba_color::gainsboro =
	rgba_color{ 220, 220, 220 };

const rgba_color rgba_color::ghost_white =
	rgba_color{ 248, 248, 255 };

const rgba_color rgba_color::gold =
	rgba_color{ 255, 215, 0 };

const rgba_color rgba_color::goldenrod =
	rgba_color{ 218, 165, 32 };

const rgba_color rgba_color::gray =
	rgba_color{ 128, 128, 128 };

const rgba_color rgba_color::green =
	rgba_color{ 0, 128, 0 };

const rgba_color rgba_color::green_yellow =
	rgba_color{ 173, 255, 47 };

const rgba_color rgba_color::grey =
	rgba_color{ 128, 128, 128 };

const rgba_color rgba_color::honeydew =
	rgba_color{ 240, 255, 240 };

const rgba_color rgba_color::hot_pink =
	rgba_color{ 255, 105, 180 };

const rgba_color rgba_color::indian_red =
	rgba_color{ 205, 92, 92 };

const rgba_color rgba_color::indigo =
	rgba_color{ 75, 0, 130 };

const rgba_color rgba_color::ivory =
	rgba_color{ 255, 255, 240 };

const rgba_color rgba_color::khaki =
	rgba_color{ 240, 230, 140 };

const rgba_color rgba_color::lavender =
	rgba_color{ 230, 230, 250 };

const rgba_color rgba_color::lavender_blush =
	rgba_color{ 255, 240, 245 };

const rgba_color rgba_color::lawn_green =
	rgba_color{ 124, 252, 0 };

const rgba_color rgba_color::lemon_chiffon =
	rgba_color{ 255, 250, 205 };

const rgba_color rgba_color::light_blue =
	rgba_color{ 173, 216, 230 };

const rgba_color rgba_color::light_coral =
	rgba_color{ 240, 128, 128 };

const rgba_color rgba_color::light_cyan =
	rgba_color{ 224, 255, 255 };

const rgba_color rgba_color::light_goldenrod_yellow =
	rgba_color{ 250, 250, 210 };

const rgba_color rgba_color::light_gray =
	rgba_color{ 211, 211, 211 };

const rgba_color rgba_color::light_green =
	rgba_color{ 144, 238, 144 };

const rgba_color rgba_color::light_grey =
	rgba_color{ 211, 211, 211 };

const rgba_color rgba_color::light_pink =
	rgba_color{ 255, 182, 193 };

const rgba_color rgba_color::light_salmon =
	rgba_color{ 255, 160, 122 };

const rgba_color rgba_color::light_sea_green =
	rgba_color{ 32, 178, 170 };

const rgba_color rgba_color::light_sky_blue =
	rgba_color{ 135, 206, 250 };

const rgba_color rgba_color::light_slate_gray =
	rgba_color{ 119, 136, 153 };

const rgba_color rgba_color::light_slate_grey =
	rgba_color{ 119, 136, 153 };

const rgba_color rgba_color::light_steel_blue =
	rgba_color{ 176, 196, 222 };

const rgba_color rgba_color::light_yellow =
	rgba_color{ 255, 255, 224 };

const rgba_color rgba_color::lime =
	rgba_color{ 0, 255, 0 };

const rgba_color rgba_color::lime_green =
	rgba_color{ 50, 205, 50 };

const rgba_color rgba_color::linen =
	rgba_color{ 250, 240, 230 };

const rgba_color rgba_color::magenta =
	rgba_color{ 255, 0, 255 };

const rgba_color rgba_color::maroon =
	rgba_color{ 128, 0, 0 };

const rgba_color rgba_color::medium_aquamarine =
	rgba_color{ 102, 205, 170 };

const rgba_color rgba_color::medium_blue =
	rgba_color{ 0, 0, 205 };

const rgba_color rgba_color::medium_orchid =
	rgba_color{ 186, 85, 211 };

const rgba_color rgba_color::medium_purple =
	rgba_color{ 147, 112, 219 };

const rgba_color rgba_color::medium_sea_green =
	rgba_color{ 60, 179, 113 };

const rgba_color rgba_color::medium_slate_blue =
	rgba_color{ 123, 104, 238 };

const rgba_color rgba_color::medium_spring_green =
	rgba_color{ 0, 250, 154 };

const rgba_color rgba_color::medium_turquoise =
	rgba_color{ 72, 209, 204 };

const rgba_color rgba_color::medium_violet_red =
	rgba_color{ 199, 21, 133 };

const rgba_color rgba_color::midnight_blue =
	rgba_color{ 25, 25, 112 };

const rgba_color rgba_color::mint_cream =
	rgba_color{ 245, 255, 250 };

const rgba_color rgba_color::misty_rose =
	rgba_color{ 255, 228, 225 };

const rgba_color rgba_color::moccasin =
	rgba_color{ 255, 228, 181 };

const rgba_color rgba_color::navajo_white =
	rgba_color{ 255, 222, 173 };

const rgba_color rgba_color::navy =
	rgba_color{ 0, 0, 128 };

const rgba_color rgba_color::old_lace =
	rgba_color{ 253, 245, 230 };

const rgba_color rgba_color::olive =
	rgba_color{ 128, 128, 0 };

const rgba_color rgba_color::olive_drab =
	rgba_color{ 107, 142, 35 };

const rgba_color rgba_color::orange =
	rgba_color{ 255, 165, 0 };

const rgba_color rgba_color::orange_red =
	rgba_color{ 255, 69, 0 };

const rgba_color rgba_color::orchid =
	rgba_color{ 218, 112, 214 };

const rgba_color rgba_color::pale_goldenrod =
	rgba_color{ 238, 232, 170 };

const rgba_color rgba_color::pale_green =
	rgba_color{ 152, 251, 152 };

const rgba_color rgba_color::pale_turquoise =
	rgba_color{ 175, 238, 238 };

const rgba_color rgba_color::pale_violet_red =
	rgba_color{ 219, 112, 147 };

const rgba_color rgba_color::papaya_whip =
	rgba_color{ 255, 239, 213 };

const rgba_color rgba_color::peach_puff =
	rgba_color{ 255, 218, 185 };

const rgba_color rgba_color::peru =
	rgba_color{ 205, 133, 63 };

const rgba_color rgba_color::pink =
	rgba_color{ 255, 192, 203 };

const rgba_color rgba_color::plum =
	rgba_color{ 221, 160, 221 };

const rgba_color rgba_color::powder_blue =
	rgba_color{ 176, 224, 230 };

const rgba_color rgba_color::purple =
	rgba_color{ 128, 0, 128 };

const rgba_color rgba_color::red =
	rgba_color{ 255, 0, 0 };

const rgba_color rgba_color::rosy_brown =
	rgba_color{ 188, 143, 143 };

const rgba_color rgba_color::royal_blue =
	rgba_color{ 65, 105, 225 };

const rgba_color rgba_color::saddle_brown =
	rgba_color{ 139, 69, 19 };

const rgba_color rgba_color::salmon =
	rgba_color{ 250, 128, 114 };

const rgba_color rgba_color::sandy_brown =
	rgba_color{ 244, 164, 96 };

const rgba_color rgba_color::sea_green =
	rgba_color{ 46, 139, 87 };

const rgba_color rgba_color::sea_shell =
	rgba_color{ 255, 245, 238 };

const rgba_color rgba_color::sienna =
	rgba_color{ 160, 82, 45 };

const rgba_color rgba_color::silver =
	rgba_color{ 192, 192, 192 };

const rgba_color rgba_color::sky_blue =
	rgba_color{ 135, 206, 235 };

const rgba_color rgba_color::slate_blue =
	rgba_color{ 106, 90, 205 };

const rgba_color rgba_color::slate_gray =
	rgba_color{ 112, 128, 144 };

const rgba_color rgba_color::slate_grey =
	rgba_color{ 112, 128, 144 };

const rgba_color rgba_color::snow =
	rgba_color{ 255, 250, 250 };

const rgba_color rgba_color::spring_green =
	rgba_color{ 0, 255, 127 };

const rgba_color rgba_color::steel_blue =
	rgba_color{ 70, 130, 180 };

const rgba_color rgba_color::tan =
	rgba_color{ 210, 180, 140 };

const rgba_color rgba_color::teal =
	rgba_color{ 0, 128, 128 };

const rgba_color rgba_color::thistle =
	rgba_color{ 216, 191, 216 };

const rgba_color rgba_color::tomato =
	rgba_color{ 255, 99, 71 };

const rgba_color rgba_color::transparent_black =
	rgba_color{ 0, 0, 0, 0 };

const rgba_color rgba_color::turquoise =
	rgba_color{ 64, 244, 208 };

const rgba_color rgba_color::violet =
	rgba_color{ 238, 130, 238 };

const rgba_color rgba_color::wheat =
	rgba_color{ 245, 222, 179 };

const rgba_color rgba_color::white =
	rgba_color{ 255, 255, 255 };

const rgba_color rgba_color::white_smoke =
	rgba_color{ 245, 245, 245 };

const rgba_color rgba_color::yellow =
	rgba_color{ 255, 255, 0 };

const rgba_color rgba_color::yellow_green =
	rgba_color{ 154, 205, 50};

