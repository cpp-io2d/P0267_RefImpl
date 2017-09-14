#include "TestAndTeach.h"

void test_and_teach::tutorial::update(my_display_surface& ds)
{
	using namespace std::experimental::io2d;

	const rgba_color colours[148] =
	{
		rgba_color::alice_blue,				rgba_color::antique_white,			rgba_color::aqua,					rgba_color::aquamarine,				rgba_color::azure,					rgba_color::beige,
		rgba_color::bisque,					rgba_color::black,					rgba_color::blanched_almond,		rgba_color::blue,					rgba_color::blue_violet,			rgba_color::brown,
		rgba_color::burly_wood,				rgba_color::cadet_blue,				rgba_color::chartreuse,				rgba_color::chocolate,				rgba_color::coral,					rgba_color::cornflower_blue,
		rgba_color::cornsilk,				rgba_color::crimson,				rgba_color::cyan,					rgba_color::dark_blue,				rgba_color::dark_cyan,				rgba_color::dark_goldenrod,
		rgba_color::dark_gray,				rgba_color::dark_green,				rgba_color::dark_grey,				rgba_color::dark_khaki,				rgba_color::dark_magenta,			rgba_color::dark_olive_green,
		rgba_color::dark_orange,			rgba_color::dark_orchid,			rgba_color::dark_red,				rgba_color::dark_salmon,			rgba_color::dark_sea_green,			rgba_color::dark_slate_blue,
		rgba_color::dark_slate_gray,		rgba_color::dark_slate_grey,		rgba_color::dark_turquoise,			rgba_color::dark_violet,			rgba_color::deep_pink,				rgba_color::deep_sky_blue,
		rgba_color::dim_gray,				rgba_color::dim_grey,				rgba_color::dodger_blue,			rgba_color::firebrick,				rgba_color::floral_white,			rgba_color::forest_green,
		rgba_color::fuchsia,				rgba_color::gainsboro,				rgba_color::ghost_white,			rgba_color::gold,					rgba_color::goldenrod,				rgba_color::gray,
		rgba_color::green,					rgba_color::green_yellow,			rgba_color::grey,					rgba_color::honeydew,				rgba_color::hot_pink,				rgba_color::indian_red,
		rgba_color::indigo,					rgba_color::ivory,					rgba_color::khaki,					rgba_color::lavender,				rgba_color::lavender_blush,			rgba_color::lawn_green,
		rgba_color::lemon_chiffon,			rgba_color::light_blue,				rgba_color::light_coral,			rgba_color::light_cyan,				rgba_color::light_goldenrod_yellow,	rgba_color::light_gray,
		rgba_color::light_green,			rgba_color::light_grey,				rgba_color::light_pink,				rgba_color::light_salmon,			rgba_color::light_sea_green,		rgba_color::light_sky_blue,
		rgba_color::light_slate_gray,		rgba_color::light_slate_grey,		rgba_color::light_steel_blue,		rgba_color::light_yellow,			rgba_color::lime,					rgba_color::lime_green,
		rgba_color::linen,					rgba_color::magenta,				rgba_color::maroon,					rgba_color::medium_aquamarine,		rgba_color::medium_blue,			rgba_color::medium_orchid,
		rgba_color::medium_purple,			rgba_color::medium_sea_green,		rgba_color::medium_slate_blue,		rgba_color::medium_spring_green,	rgba_color::medium_turquoise,		rgba_color::medium_violet_red,
		rgba_color::midnight_blue,			rgba_color::mint_cream,				rgba_color::misty_rose,				rgba_color::moccasin,				rgba_color::navajo_white,			rgba_color::navy,
		rgba_color::old_lace,				rgba_color::olive,					rgba_color::olive_drab,				rgba_color::orange,					rgba_color::orange_red,				rgba_color::orchid,
		rgba_color::pale_goldenrod,			rgba_color::pale_green,				rgba_color::pale_turquoise,			rgba_color::pale_violet_red,		rgba_color::papaya_whip,			rgba_color::peach_puff,
		rgba_color::peru,					rgba_color::pink,					rgba_color::plum,					rgba_color::powder_blue,			rgba_color::purple,					rgba_color::red,
		rgba_color::rosy_brown,				rgba_color::royal_blue,				rgba_color::saddle_brown,			rgba_color::salmon,					rgba_color::sandy_brown,			rgba_color::sea_green,
		rgba_color::sea_shell,				rgba_color::sienna,					rgba_color::silver,					rgba_color::sky_blue,				rgba_color::slate_blue,				rgba_color::slate_gray,
		rgba_color::slate_grey,				rgba_color::snow,					rgba_color::spring_green,			rgba_color::steel_blue,				rgba_color::tan,					rgba_color::teal,
		rgba_color::thistle,				rgba_color::tomato,					rgba_color::transparent_black,		rgba_color::turquoise,				rgba_color::violet,					rgba_color::wheat,
		rgba_color::white,					rgba_color::white_smoke,			rgba_color::yellow,					rgba_color::yellow_green
	};

	auto pb = path_builder<>{};
	pb.new_figure({ 20.0f, 20.0f });
	pb.rel_line({ 20.0f, 0.0f });
	pb.rel_line({ 0.0f, 20.0f });
	pb.rel_line({ -20.0f, 0.0f });
	pb.close_figure();

	for (auto i = 0; i < 9; ++i)
	{
		for (auto j = 0; j < 16; ++j)
		{
			auto del_x = 20.0f;
			auto del_y = 0.0f;
			if (j == 0)
			{
				if (i > 0)
				{
					del_x = -300.0f;
				}
				del_y = 20.0f;
			}
			pb.insert(pb.begin(), figure_items::rel_matrix(matrix_2d::init_translate({ del_x, del_y })));
			ds.fill(my_brush{ colours[i*16 + j] }, pb);
		}
	}
}