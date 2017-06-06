#include "io2d.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

const rgba_color& rgba_color::alice_blue() noexcept {
	static rgba_color c{ 240, 248, 255 };
	return c;
}

const rgba_color& rgba_color::antique_white() noexcept {
	static rgba_color c{ 250, 235, 215 };
	return c;
}

const rgba_color& rgba_color::aqua() noexcept {
	static rgba_color c{ 0, 255, 255 };
	return c;
}

const rgba_color& rgba_color::aquamarine() noexcept {
	static rgba_color c{ 127, 255, 212 };
	return c;
}

const rgba_color& rgba_color::azure() noexcept {
	static rgba_color c{ 240, 255, 255 };
	return c;
}

const rgba_color& rgba_color::beige() noexcept {
	static rgba_color c{ 245, 245, 220 };
	return c;
}

const rgba_color& rgba_color::bisque() noexcept {
	static rgba_color c{ 255, 228, 196 };
	return c;
}

const rgba_color& rgba_color::black() noexcept {
	static rgba_color c{ 0, 0, 0 };
	return c;
}

const rgba_color& rgba_color::blanched_almond() noexcept {
	static rgba_color c{ 255, 235, 205 };
	return c;
}

const rgba_color& rgba_color::blue() noexcept {
	static rgba_color c{ 0, 0, 255 };
	return c;
}

const rgba_color& rgba_color::blue_violet() noexcept {
	static rgba_color c{ 138, 43, 226 };
	return c;
}

const rgba_color& rgba_color::brown() noexcept {
	static rgba_color c{ 165, 42, 42 };
	return c;
}

const rgba_color& rgba_color::burly_wood() noexcept {
	static rgba_color c{ 222, 184, 135 };
	return c;
}

const rgba_color& rgba_color::cadet_blue() noexcept {
	static rgba_color c{ 95, 158, 160 };
	return c;
}

const rgba_color& rgba_color::chartreuse() noexcept {
	static rgba_color c{ 127, 255, 0 };
	return c;
}

const rgba_color& rgba_color::chocolate() noexcept {
	static rgba_color c{ 210, 105, 30 };
	return c;
}

const rgba_color& rgba_color::coral() noexcept {
	static rgba_color c{ 255, 127, 80 };
	return c;
}

const rgba_color& rgba_color::cornflower_blue() noexcept {
	static rgba_color c{ 100, 149, 237 };
	return c;
}

const rgba_color& rgba_color::cornsilk() noexcept {
	static rgba_color c{ 255, 248, 220 };
	return c;
}

const rgba_color& rgba_color::crimson() noexcept {
	static rgba_color c{ 220, 20, 60 };
	return c;
}

const rgba_color& rgba_color::cyan() noexcept {
	static rgba_color c{ 0, 255, 255 };
	return c;
}

const rgba_color& rgba_color::dark_blue() noexcept {
	static rgba_color c{ 0, 0, 139 };
	return c;
}

const rgba_color& rgba_color::dark_cyan() noexcept {
	static rgba_color c{ 0, 139, 139 };
	return c;
}

const rgba_color& rgba_color::dark_goldenrod() noexcept {
	static rgba_color c{ 184, 134, 11 };
	return c;
}

const rgba_color& rgba_color::dark_gray() noexcept {
	static rgba_color c{ 169, 169, 169 };
	return c;
}

const rgba_color& rgba_color::dark_green() noexcept {
	static rgba_color c{ 0, 100, 0 };
	return c;
}

const rgba_color& rgba_color::dark_grey() noexcept {
	static rgba_color c{ 169, 169, 169 };
	return c;
}

const rgba_color& rgba_color::dark_khaki() noexcept {
	static rgba_color c{ 189, 183, 107 };
	return c;
}

const rgba_color& rgba_color::dark_magenta() noexcept {
	static rgba_color c{ 139, 0, 139 };
	return c;
}

const rgba_color& rgba_color::dark_olive_green() noexcept {
	static rgba_color c{ 85, 107, 47 };
	return c;
}

const rgba_color& rgba_color::dark_orange() noexcept {
	static rgba_color c{ 255, 140, 0 };
	return c;
}

const rgba_color& rgba_color::dark_orchid() noexcept {
	static rgba_color c{ 153, 50, 204 };
	return c;
}

const rgba_color& rgba_color::dark_red() noexcept {
	static rgba_color c{ 139, 0, 0 };
	return c;
}

const rgba_color& rgba_color::dark_salmon() noexcept {
	static rgba_color c{ 233, 150, 122 };
	return c;
}

const rgba_color& rgba_color::dark_sea_green() noexcept {
	static rgba_color c{ 143, 188, 143 };
	return c;
}

const rgba_color& rgba_color::dark_slate_blue() noexcept {
	static rgba_color c{ 72, 61, 139 };
	return c;
}

const rgba_color& rgba_color::dark_slate_gray() noexcept {
	static rgba_color c{ 47, 79, 79 };
	return c;
}

const rgba_color& rgba_color::dark_slate_grey() noexcept {
	static rgba_color c{ 47, 79, 79 };
	return c;
}

const rgba_color& rgba_color::dark_turquoise() noexcept {
	static rgba_color c{ 0, 206, 209 };
	return c;
}

const rgba_color& rgba_color::dark_violet() noexcept {
	static rgba_color c{ 148, 0, 211 };
	return c;
}

const rgba_color& rgba_color::deep_pink() noexcept {
	static rgba_color c{ 255, 20, 147 };
	return c;
}

const rgba_color& rgba_color::deep_sky_blue() noexcept {
	static rgba_color c{ 0, 191, 255 };
	return c;
}

const rgba_color& rgba_color::dim_gray() noexcept {
	static rgba_color c{ 105, 105, 105 };
	return c;
}

const rgba_color& rgba_color::dim_grey() noexcept {
	static rgba_color c{ 105, 105, 105 };
	return c;
}

const rgba_color& rgba_color::dodger_blue() noexcept {
	static rgba_color c{ 30, 144, 255 };
	return c;
}

const rgba_color& rgba_color::firebrick() noexcept {
	static rgba_color c{ 178, 34, 34 };
	return c;
}

const rgba_color& rgba_color::floral_white() noexcept {
	static rgba_color c{ 255, 250, 240 };
	return c;
}

const rgba_color& rgba_color::forest_green() noexcept {
	static rgba_color c{ 34, 139, 34 };
	return c;
}

const rgba_color& rgba_color::fuchsia() noexcept {
	static rgba_color c{ 255, 0, 255 };
	return c;
}

const rgba_color& rgba_color::gainsboro() noexcept {
	static rgba_color c{ 220, 220, 220 };
	return c;
}

const rgba_color& rgba_color::ghost_white() noexcept {
	static rgba_color c{ 248, 248, 255 };
	return c;
}

const rgba_color& rgba_color::gold() noexcept {
	static rgba_color c{ 255, 215, 0 };
	return c;
}

const rgba_color& rgba_color::goldenrod() noexcept {
	static rgba_color c{ 218, 165, 32 };
	return c;
}

const rgba_color& rgba_color::gray() noexcept {
	static rgba_color c{ 128, 128, 128 };
	return c;
}

const rgba_color& rgba_color::green() noexcept {
	static rgba_color c{ 0, 128, 0 };
	return c;
}

const rgba_color& rgba_color::green_yellow() noexcept {
	static rgba_color c{ 173, 255, 47 };
	return c;
}

const rgba_color& rgba_color::grey() noexcept {
	static rgba_color c{ 128, 128, 128 };
	return c;
}

const rgba_color& rgba_color::honeydew() noexcept {
	static rgba_color c{ 240, 255, 240 };
	return c;
}

const rgba_color& rgba_color::hot_pink() noexcept {
	static rgba_color c{ 255, 105, 180 };
	return c;
}

const rgba_color& rgba_color::indian_red() noexcept {
	static rgba_color c{ 205, 92, 92 };
	return c;
}

const rgba_color& rgba_color::indigo() noexcept {
	static rgba_color c{ 75, 0, 130 };
	return c;
}

const rgba_color& rgba_color::ivory() noexcept {
	static rgba_color c{ 255, 255, 240 };
	return c;
}

const rgba_color& rgba_color::khaki() noexcept {
	static rgba_color c{ 240, 230, 140 };
	return c;
}

const rgba_color& rgba_color::lavender() noexcept {
	static rgba_color c{ 230, 230, 250 };
	return c;
}

const rgba_color& rgba_color::lavender_blush() noexcept {
	static rgba_color c{ 255, 240, 245 };
	return c;
}

const rgba_color& rgba_color::lawn_green() noexcept {
	static rgba_color c{ 124, 252, 0 };
	return c;
}

const rgba_color& rgba_color::lemon_chiffon() noexcept {
	static rgba_color c{ 255, 250, 205 };
	return c;
}

const rgba_color& rgba_color::light_blue() noexcept {
	static rgba_color c{ 173, 216, 230 };
	return c;
}

const rgba_color& rgba_color::light_coral() noexcept {
	static rgba_color c{ 240, 128, 128 };
	return c;
}

const rgba_color& rgba_color::light_cyan() noexcept {
	static rgba_color c{ 224, 255, 255 };
	return c;
}

const rgba_color& rgba_color::light_goldenrod_yellow() noexcept {
	static rgba_color c{ 250, 250, 210 };
	return c;
}

const rgba_color& rgba_color::light_gray() noexcept {
	static rgba_color c{ 211, 211, 211 };
	return c;
}

const rgba_color& rgba_color::light_green() noexcept {
	static rgba_color c{ 144, 238, 144 };
	return c;
}

const rgba_color& rgba_color::light_grey() noexcept {
	static rgba_color c{ 211, 211, 211 };
	return c;
}

const rgba_color& rgba_color::light_pink() noexcept {
	static rgba_color c{ 255, 182, 193 };
	return c;
}

const rgba_color& rgba_color::light_salmon() noexcept {
	static rgba_color c{ 255, 160, 122 };
	return c;
}

const rgba_color& rgba_color::light_sea_green() noexcept {
	static rgba_color c{ 32, 178, 170 };
	return c;
}

const rgba_color& rgba_color::light_sky_blue() noexcept {
	static rgba_color c{ 135, 206, 250 };
	return c;
}

const rgba_color& rgba_color::light_slate_gray() noexcept {
	static rgba_color c{ 119, 136, 153 };
	return c;
}

const rgba_color& rgba_color::light_slate_grey() noexcept {
	static rgba_color c{ 119, 136, 153 };
	return c;
}

const rgba_color& rgba_color::light_steel_blue() noexcept {
	static rgba_color c{ 176, 196, 222 };
	return c;
}

const rgba_color& rgba_color::light_yellow() noexcept {
	static rgba_color c{ 255, 255, 224 };
	return c;
}

const rgba_color& rgba_color::lime() noexcept {
	static rgba_color c{ 0, 255, 0 };
	return c;
}

const rgba_color& rgba_color::lime_green() noexcept {
	static rgba_color c{ 50, 205, 50 };
	return c;
}

const rgba_color& rgba_color::linen() noexcept {
	static rgba_color c{ 250, 240, 230 };
	return c;
}

const rgba_color& rgba_color::magenta() noexcept {
	static rgba_color c{ 255, 0, 255 };
	return c;
}

const rgba_color& rgba_color::maroon() noexcept {
	static rgba_color c{ 128, 0, 0 };
	return c;
}

const rgba_color& rgba_color::medium_aquamarine() noexcept {
	static rgba_color c{ 102, 205, 170 };
	return c;
}

const rgba_color& rgba_color::medium_blue() noexcept {
	static rgba_color c{ 0, 0, 205 };
	return c;
}

const rgba_color& rgba_color::medium_orchid() noexcept {
	static rgba_color c{ 186, 85, 211 };
	return c;
}

const rgba_color& rgba_color::medium_purple() noexcept {
	static rgba_color c{ 147, 112, 219 };
	return c;
}

const rgba_color& rgba_color::medium_sea_green() noexcept {
	static rgba_color c{ 60, 179, 113 };
	return c;
}

const rgba_color& rgba_color::medium_slate_blue() noexcept {
	static rgba_color c{ 123, 104, 238 };
	return c;
}

const rgba_color& rgba_color::medium_spring_green() noexcept {
	static rgba_color c{ 0, 250, 154 };
	return c;
}

const rgba_color& rgba_color::medium_turquoise() noexcept {
	static rgba_color c{ 72, 209, 204 };
	return c;
}

const rgba_color& rgba_color::medium_violet_red() noexcept {
	static rgba_color c{ 199, 21, 133 };
	return c;
}

const rgba_color& rgba_color::midnight_blue() noexcept {
	static rgba_color c{ 25, 25, 112 };
	return c;
}

const rgba_color& rgba_color::mint_cream() noexcept {
	static rgba_color c{ 245, 255, 250 };
	return c;
}

const rgba_color& rgba_color::misty_rose() noexcept {
	static rgba_color c{ 255, 228, 225 };
	return c;
}

const rgba_color& rgba_color::moccasin() noexcept {
	static rgba_color c{ 255, 228, 181 };
	return c;
}

const rgba_color& rgba_color::navajo_white() noexcept {
	static rgba_color c{ 255, 222, 173 };
	return c;
}

const rgba_color& rgba_color::navy() noexcept {
	static rgba_color c{ 0, 0, 128 };
	return c;
}

const rgba_color& rgba_color::old_lace() noexcept {
	static rgba_color c{ 253, 245, 230 };
	return c;
}

const rgba_color& rgba_color::olive() noexcept {
	static rgba_color c{ 128, 128, 0 };
	return c;
}

const rgba_color& rgba_color::olive_drab() noexcept {
	static rgba_color c{ 107, 142, 35 };
	return c;
}

const rgba_color& rgba_color::orange() noexcept {
	static rgba_color c{ 255, 165, 0 };
	return c;
}

const rgba_color& rgba_color::orange_red() noexcept {
	static rgba_color c{ 255, 69, 0 };
	return c;
}

const rgba_color& rgba_color::orchid() noexcept {
	static rgba_color c{ 218, 112, 214 };
	return c;
}

const rgba_color& rgba_color::pale_goldenrod() noexcept {
	static rgba_color c{ 238, 232, 170 };
	return c;
}

const rgba_color& rgba_color::pale_green() noexcept {
	static rgba_color c{ 152, 251, 152 };
	return c;
}

const rgba_color& rgba_color::pale_turquoise() noexcept {
	static rgba_color c{ 175, 238, 238 };
	return c;
}

const rgba_color& rgba_color::pale_violet_red() noexcept {
	static rgba_color c{ 219, 112, 147 };
	return c;
}

const rgba_color& rgba_color::papaya_whip() noexcept {
	static rgba_color c{ 255, 239, 213 };
	return c;
}

const rgba_color& rgba_color::peach_puff() noexcept {
	static rgba_color c{ 255, 218, 185 };
	return c;
}

const rgba_color& rgba_color::peru() noexcept {
	static rgba_color c{ 205, 133, 63 };
	return c;
}

const rgba_color& rgba_color::pink() noexcept {
	static rgba_color c{ 255, 192, 203 };
	return c;
}

const rgba_color& rgba_color::plum() noexcept {
	static rgba_color c{ 221, 160, 221 };
	return c;
}

const rgba_color& rgba_color::powder_blue() noexcept {
	static rgba_color c{ 176, 224, 230 };
	return c;
}

const rgba_color& rgba_color::purple() noexcept {
	static rgba_color c{ 128, 0, 128 };
	return c;
}

const rgba_color& rgba_color::red() noexcept {
	static rgba_color c{ 255, 0, 0 };
	return c;
}

const rgba_color& rgba_color::rosy_brown() noexcept {
	static rgba_color c{ 188, 143, 143 };
	return c;
}

const rgba_color& rgba_color::royal_blue() noexcept {
	static rgba_color c{ 65, 105, 225 };
	return c;
}

const rgba_color& rgba_color::saddle_brown() noexcept {
	static rgba_color c{ 139, 69, 19 };
	return c;
}

const rgba_color& rgba_color::salmon() noexcept {
	static rgba_color c{ 250, 128, 114 };
	return c;
}

const rgba_color& rgba_color::sandy_brown() noexcept {
	static rgba_color c{ 244, 164, 96 };
	return c;
}

const rgba_color& rgba_color::sea_green() noexcept {
	static rgba_color c{ 46, 139, 87 };
	return c;
}

const rgba_color& rgba_color::sea_shell() noexcept {
	static rgba_color c{ 255, 245, 238 };
	return c;
}

const rgba_color& rgba_color::sienna() noexcept {
	static rgba_color c{ 160, 82, 45 };
	return c;
}

const rgba_color& rgba_color::silver() noexcept {
	static rgba_color c{ 192, 192, 192 };
	return c;
}

const rgba_color& rgba_color::sky_blue() noexcept {
	static rgba_color c{ 135, 206, 235 };
	return c;
}

const rgba_color& rgba_color::slate_blue() noexcept {
	static rgba_color c{ 106, 90, 205 };
	return c;
}

const rgba_color& rgba_color::slate_gray() noexcept {
	static rgba_color c{ 112, 128, 144 };
	return c;
}

const rgba_color& rgba_color::slate_grey() noexcept {
	static rgba_color c{ 112, 128, 144 };
	return c;
}

const rgba_color& rgba_color::snow() noexcept {
	static rgba_color c{ 255, 250, 250 };
	return c;
}

const rgba_color& rgba_color::spring_green() noexcept {
	static rgba_color c{ 0, 255, 127 };
	return c;
}

const rgba_color& rgba_color::steel_blue() noexcept {
	static rgba_color c{ 70, 130, 180 };
	return c;
}

const rgba_color& rgba_color::tan() noexcept {
	static rgba_color c{ 210, 180, 140 };
	return c;
}

const rgba_color& rgba_color::teal() noexcept {
	static rgba_color c{ 0, 128, 128 };
	return c;
}

const rgba_color& rgba_color::thistle() noexcept {
	static rgba_color c{ 216, 191, 216 };
	return c;
}

const rgba_color& rgba_color::tomato() noexcept {
	static rgba_color c{ 255, 99, 71 };
	return c;
}

const rgba_color& rgba_color::transparent_black() noexcept {
	static rgba_color c{ 0, 0, 0, 0 };
	return c;
}

const rgba_color& rgba_color::turquoise() noexcept {
	static rgba_color c{ 64, 244, 208 };
	return c;
}

const rgba_color& rgba_color::violet() noexcept {
	static rgba_color c{ 238, 130, 238 };
	return c;
}

const rgba_color& rgba_color::wheat() noexcept {
	static rgba_color c{ 245, 222, 179 };
	return c;
}

const rgba_color& rgba_color::white() noexcept {
	static rgba_color c{ 255, 255, 255 };
	return c;
}

const rgba_color& rgba_color::white_smoke() noexcept {
	static rgba_color c{ 245, 245, 245 };
	return c;
}

const rgba_color& rgba_color::yellow() noexcept {
	static rgba_color c{ 255, 255, 0 };
	return c;
}

const rgba_color& rgba_color::yellow_green() noexcept {
	static rgba_color c{ 154, 205, 50};
	return c;
}

