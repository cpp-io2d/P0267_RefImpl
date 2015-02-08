#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

rgba_color::rgba_color(rgba_color&& other)
	: _R(move(other._R))
	, _G(move(other._G))
	, _B(move(other._B))
	, _A(move(other._A)) {
	other._R = 0.0;
	other._G = 0.0;
	other._B = 0.0;
	other._A = 0.0;
}

rgba_color& rgba_color::operator=(rgba_color&& other) {
	if (this != &other) {
		_R = move(other._R);
		_G = move(other._G);
		_B = move(other._B);
		_A = move(other._A);
		other._R = 0.0;
		other._G = 0.0;
		other._B = 0.0;
		other._A = 0.0;
	}
	return *this;
}

rgba_color::rgba_color(double red, double green, double blue, double alpha)
: _R(red)
, _G(green)
, _B(blue)
, _A(alpha) {
}

rgba_color::rgba_color(int red, int green, int blue, int alpha)
	: _R(red / 255.0)
	, _G(green / 255.0)
	, _B(blue / 255.0)
	, _A(alpha / 255.0) {
}

void rgba_color::r(double value) {
	_R = value;
}

void rgba_color::g(double value) {
	_G = value;
}

void rgba_color::b(double value) {
	_B = value;
}

void rgba_color::a(double value) {
	_A = value;
}

double rgba_color::r() const {
	return _R;
}

double rgba_color::g() const {
	return _G;
}

double rgba_color::b() const {
	return _B;
}

double rgba_color::a() const {
	return _A;
}

rgba_color _Rgba_color_from_byte_values(unsigned char r, unsigned char g, unsigned char b, unsigned char a = static_cast<unsigned char>(255));
rgba_color _Rgba_color_from_byte_values(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	return{ static_cast<double>(r) / 255.0, static_cast<double>(g) / 255.0, static_cast<double>(b) / 255.0, static_cast<double>(a) / 255.0 };
}

const rgba_color& rgba_color::alice_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(240), static_cast<unsigned char>(248), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::antique_white() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(250), static_cast<unsigned char>(235), static_cast<unsigned char>(215));
	return c;
}

const rgba_color& rgba_color::aqua() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(255), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::aquamarine() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(127), static_cast<unsigned char>(255), static_cast<unsigned char>(212));
	return c;
}

const rgba_color& rgba_color::azure() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(240), static_cast<unsigned char>(255), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::beige() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(245), static_cast<unsigned char>(245), static_cast<unsigned char>(220));
	return c;
}

const rgba_color& rgba_color::bisque() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(228), static_cast<unsigned char>(196));
	return c;
}

const rgba_color& rgba_color::black() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::blanched_almond() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(235), static_cast<unsigned char>(205));
	return c;
}

const rgba_color& rgba_color::blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::blue_violet() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(138), static_cast<unsigned char>(43), static_cast<unsigned char>(226));
	return c;
}

const rgba_color& rgba_color::brown() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(165), static_cast<unsigned char>(42), static_cast<unsigned char>(42));
	return c;
}

const rgba_color& rgba_color::burly_wood() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(222), static_cast<unsigned char>(184), static_cast<unsigned char>(135));
	return c;
}

const rgba_color& rgba_color::cadet_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(95), static_cast<unsigned char>(158), static_cast<unsigned char>(160));
	return c;
}

const rgba_color& rgba_color::chartreuse() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(127), static_cast<unsigned char>(255), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::chocolate() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(210), static_cast<unsigned char>(105), static_cast<unsigned char>(30));
	return c;
}

const rgba_color& rgba_color::coral() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(127), static_cast<unsigned char>(80));
	return c;
}

const rgba_color& rgba_color::cornflower_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(100), static_cast<unsigned char>(149), static_cast<unsigned char>(237));
	return c;
}

const rgba_color& rgba_color::cornsilk() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(248), static_cast<unsigned char>(220));
	return c;
}

const rgba_color& rgba_color::crimson() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(220), static_cast<unsigned char>(20), static_cast<unsigned char>(60));
	return c;
}

const rgba_color& rgba_color::cyan() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(255), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::dark_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(139));
	return c;
}

const rgba_color& rgba_color::dark_cyan() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(139), static_cast<unsigned char>(139));
	return c;
}

const rgba_color& rgba_color::dark_goldenrod() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(184), static_cast<unsigned char>(134), static_cast<unsigned char>(11));
	return c;
}

const rgba_color& rgba_color::dark_gray() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(169), static_cast<unsigned char>(169), static_cast<unsigned char>(169));
	return c;
}

const rgba_color& rgba_color::dark_green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(100), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::dark_grey() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(169), static_cast<unsigned char>(169), static_cast<unsigned char>(169));
	return c;
}

const rgba_color& rgba_color::dark_khaki() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(189), static_cast<unsigned char>(183), static_cast<unsigned char>(107));
	return c;
}

const rgba_color& rgba_color::dark_magenta() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(139), static_cast<unsigned char>(0), static_cast<unsigned char>(139));
	return c;
}

const rgba_color& rgba_color::dark_olive_green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(85), static_cast<unsigned char>(107), static_cast<unsigned char>(47));
	return c;
}

const rgba_color& rgba_color::dark_orange() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(140), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::dark_orchid() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(153), static_cast<unsigned char>(50), static_cast<unsigned char>(204));
	return c;
}

const rgba_color& rgba_color::dark_red() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(139), static_cast<unsigned char>(0), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::dark_salmon() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(233), static_cast<unsigned char>(150), static_cast<unsigned char>(122));
	return c;
}

const rgba_color& rgba_color::dark_sea_green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(143), static_cast<unsigned char>(188), static_cast<unsigned char>(143));
	return c;
}

const rgba_color& rgba_color::dark_slate_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(72), static_cast<unsigned char>(61), static_cast<unsigned char>(139));
	return c;
}

const rgba_color& rgba_color::dark_slate_gray() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(47), static_cast<unsigned char>(79), static_cast<unsigned char>(79));
	return c;
}

const rgba_color& rgba_color::dark_slate_grey() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(47), static_cast<unsigned char>(79), static_cast<unsigned char>(79));
	return c;
}

const rgba_color& rgba_color::dark_turquoise() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(206), static_cast<unsigned char>(209));
	return c;
}

const rgba_color& rgba_color::dark_violet() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(148), static_cast<unsigned char>(0), static_cast<unsigned char>(211));
	return c;
}

const rgba_color& rgba_color::deep_pink() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(20), static_cast<unsigned char>(147));
	return c;
}

const rgba_color& rgba_color::deep_sky_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(191), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::dim_gray() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(105), static_cast<unsigned char>(105), static_cast<unsigned char>(105));
	return c;
}

const rgba_color& rgba_color::dim_grey() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(105), static_cast<unsigned char>(105), static_cast<unsigned char>(105));
	return c;
}

const rgba_color& rgba_color::dodger_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(30), static_cast<unsigned char>(144), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::firebrick() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(178), static_cast<unsigned char>(34), static_cast<unsigned char>(34));
	return c;
}

const rgba_color& rgba_color::floral_white() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(250), static_cast<unsigned char>(240));
	return c;
}

const rgba_color& rgba_color::forest_green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(34), static_cast<unsigned char>(139), static_cast<unsigned char>(34));
	return c;
}

const rgba_color& rgba_color::fuchsia() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(0), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::gainsboro() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(220), static_cast<unsigned char>(220), static_cast<unsigned char>(220));
	return c;
}

const rgba_color& rgba_color::ghost_white() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(248), static_cast<unsigned char>(248), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::gold() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(215), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::goldenrod() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(218), static_cast<unsigned char>(165), static_cast<unsigned char>(32));
	return c;
}

const rgba_color& rgba_color::gray() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(128), static_cast<unsigned char>(128), static_cast<unsigned char>(128));
	return c;
}

const rgba_color& rgba_color::green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(128), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::green_yellow() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(173), static_cast<unsigned char>(255), static_cast<unsigned char>(47));
	return c;
}

const rgba_color& rgba_color::grey() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(128), static_cast<unsigned char>(128), static_cast<unsigned char>(128));
	return c;
}

const rgba_color& rgba_color::honeydew() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(240), static_cast<unsigned char>(255), static_cast<unsigned char>(240));
	return c;
}

const rgba_color& rgba_color::hot_pink() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(105), static_cast<unsigned char>(180));
	return c;
}

const rgba_color& rgba_color::indian_red() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(205), static_cast<unsigned char>(92), static_cast<unsigned char>(92));
	return c;
}

const rgba_color& rgba_color::indigo() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(75), static_cast<unsigned char>(0), static_cast<unsigned char>(130));
	return c;
}

const rgba_color& rgba_color::ivory() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(255), static_cast<unsigned char>(240));
	return c;
}

const rgba_color& rgba_color::khaki() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(240), static_cast<unsigned char>(230), static_cast<unsigned char>(140));
	return c;
}

const rgba_color& rgba_color::lavender() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(230), static_cast<unsigned char>(230), static_cast<unsigned char>(250));
	return c;
}

const rgba_color& rgba_color::lavender_blush() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(240), static_cast<unsigned char>(245));
	return c;
}

const rgba_color& rgba_color::lawn_green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(124), static_cast<unsigned char>(252), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::lemon_chiffon() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(250), static_cast<unsigned char>(205));
	return c;
}

const rgba_color& rgba_color::light_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(173), static_cast<unsigned char>(216), static_cast<unsigned char>(230));
	return c;
}

const rgba_color& rgba_color::light_coral() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(240), static_cast<unsigned char>(128), static_cast<unsigned char>(128));
	return c;
}

const rgba_color& rgba_color::light_cyan() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(224), static_cast<unsigned char>(255), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::light_goldenrod_yellow() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(250), static_cast<unsigned char>(250), static_cast<unsigned char>(210));
	return c;
}

const rgba_color& rgba_color::light_gray() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(211), static_cast<unsigned char>(211), static_cast<unsigned char>(211));
	return c;
}

const rgba_color& rgba_color::light_green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(144), static_cast<unsigned char>(238), static_cast<unsigned char>(144));
	return c;
}

const rgba_color& rgba_color::light_grey() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(211), static_cast<unsigned char>(211), static_cast<unsigned char>(211));
	return c;
}

const rgba_color& rgba_color::light_pink() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(182), static_cast<unsigned char>(193));
	return c;
}

const rgba_color& rgba_color::light_salmon() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(160), static_cast<unsigned char>(122));
	return c;
}

const rgba_color& rgba_color::light_sea_green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(32), static_cast<unsigned char>(178), static_cast<unsigned char>(170));
	return c;
}

const rgba_color& rgba_color::light_sky_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(135), static_cast<unsigned char>(206), static_cast<unsigned char>(250));
	return c;
}

const rgba_color& rgba_color::light_slate_gray() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(119), static_cast<unsigned char>(136), static_cast<unsigned char>(153));
	return c;
}

const rgba_color& rgba_color::light_slate_grey() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(119), static_cast<unsigned char>(136), static_cast<unsigned char>(153));
	return c;
}

const rgba_color& rgba_color::light_steel_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(176), static_cast<unsigned char>(196), static_cast<unsigned char>(222));
	return c;
}

const rgba_color& rgba_color::light_yellow() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(255), static_cast<unsigned char>(224));
	return c;
}

const rgba_color& rgba_color::lime() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(255), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::lime_green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(50), static_cast<unsigned char>(205), static_cast<unsigned char>(50));
	return c;
}

const rgba_color& rgba_color::linen() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(250), static_cast<unsigned char>(240), static_cast<unsigned char>(230));
	return c;
}

const rgba_color& rgba_color::magenta() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(0), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::maroon() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(128), static_cast<unsigned char>(0), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::medium_aquamarine() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(102), static_cast<unsigned char>(205), static_cast<unsigned char>(170));
	return c;
}

const rgba_color& rgba_color::medium_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(205));
	return c;
}

const rgba_color& rgba_color::medium_orchid() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(186), static_cast<unsigned char>(85), static_cast<unsigned char>(211));
	return c;
}

const rgba_color& rgba_color::medium_purple() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(147), static_cast<unsigned char>(112), static_cast<unsigned char>(219));
	return c;
}

const rgba_color& rgba_color::medium_sea_green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(60), static_cast<unsigned char>(179), static_cast<unsigned char>(113));
	return c;
}

const rgba_color& rgba_color::medium_slate_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(123), static_cast<unsigned char>(104), static_cast<unsigned char>(238));
	return c;
}

const rgba_color& rgba_color::medium_spring_green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(250), static_cast<unsigned char>(154));
	return c;
}

const rgba_color& rgba_color::medium_turquoise() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(72), static_cast<unsigned char>(209), static_cast<unsigned char>(204));
	return c;
}

const rgba_color& rgba_color::medium_violet_red() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(199), static_cast<unsigned char>(21), static_cast<unsigned char>(133));
	return c;
}

const rgba_color& rgba_color::midnight_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(25), static_cast<unsigned char>(25), static_cast<unsigned char>(112));
	return c;
}

const rgba_color& rgba_color::mint_cream() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(245), static_cast<unsigned char>(255), static_cast<unsigned char>(250));
	return c;
}

const rgba_color& rgba_color::misty_rose() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(228), static_cast<unsigned char>(225));
	return c;
}

const rgba_color& rgba_color::moccasin() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(228), static_cast<unsigned char>(181));
	return c;
}

const rgba_color& rgba_color::navajo_white() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(222), static_cast<unsigned char>(173));
	return c;
}

const rgba_color& rgba_color::navy() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(128));
	return c;
}

const rgba_color& rgba_color::old_lace() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(253), static_cast<unsigned char>(245), static_cast<unsigned char>(230));
	return c;
}

const rgba_color& rgba_color::olive() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(128), static_cast<unsigned char>(128), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::olive_drab() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(107), static_cast<unsigned char>(142), static_cast<unsigned char>(35));
	return c;
}

const rgba_color& rgba_color::orange() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(165), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::orange_red() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(69), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::orchid() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(218), static_cast<unsigned char>(112), static_cast<unsigned char>(214));
	return c;
}

const rgba_color& rgba_color::pale_goldenrod() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(238), static_cast<unsigned char>(232), static_cast<unsigned char>(170));
	return c;
}

const rgba_color& rgba_color::pale_green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(152), static_cast<unsigned char>(251), static_cast<unsigned char>(152));
	return c;
}

const rgba_color& rgba_color::pale_turquoise() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(175), static_cast<unsigned char>(238), static_cast<unsigned char>(238));
	return c;
}

const rgba_color& rgba_color::pale_violet_red() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(219), static_cast<unsigned char>(112), static_cast<unsigned char>(147));
	return c;
}

const rgba_color& rgba_color::papaya_whip() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(239), static_cast<unsigned char>(213));
	return c;
}

const rgba_color& rgba_color::peach_puff() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(218), static_cast<unsigned char>(185));
	return c;
}

const rgba_color& rgba_color::peru() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(205), static_cast<unsigned char>(133), static_cast<unsigned char>(63));
	return c;
}

const rgba_color& rgba_color::pink() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(192), static_cast<unsigned char>(203));
	return c;
}

const rgba_color& rgba_color::plum() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(221), static_cast<unsigned char>(160), static_cast<unsigned char>(221));
	return c;
}

const rgba_color& rgba_color::powder_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(176), static_cast<unsigned char>(224), static_cast<unsigned char>(230));
	return c;
}

const rgba_color& rgba_color::purple() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(128), static_cast<unsigned char>(0), static_cast<unsigned char>(128));
	return c;
}

const rgba_color& rgba_color::red() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(0), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::rosy_brown() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(188), static_cast<unsigned char>(143), static_cast<unsigned char>(143));
	return c;
}

const rgba_color& rgba_color::royal_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(65), static_cast<unsigned char>(105), static_cast<unsigned char>(225));
	return c;
}

const rgba_color& rgba_color::saddle_brown() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(139), static_cast<unsigned char>(69), static_cast<unsigned char>(19));
	return c;
}

const rgba_color& rgba_color::salmon() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(250), static_cast<unsigned char>(128), static_cast<unsigned char>(114));
	return c;
}

const rgba_color& rgba_color::sandy_brown() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(244), static_cast<unsigned char>(164), static_cast<unsigned char>(96));
	return c;
}

const rgba_color& rgba_color::sea_green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(46), static_cast<unsigned char>(139), static_cast<unsigned char>(87));
	return c;
}

const rgba_color& rgba_color::sea_shell() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(245), static_cast<unsigned char>(238));
	return c;
}

const rgba_color& rgba_color::sienna() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(160), static_cast<unsigned char>(82), static_cast<unsigned char>(45));
	return c;
}

const rgba_color& rgba_color::silver() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(192), static_cast<unsigned char>(192), static_cast<unsigned char>(192));
	return c;
}

const rgba_color& rgba_color::sky_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(135), static_cast<unsigned char>(206), static_cast<unsigned char>(235));
	return c;
}

const rgba_color& rgba_color::slate_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(106), static_cast<unsigned char>(90), static_cast<unsigned char>(205));
	return c;
}

const rgba_color& rgba_color::slate_gray() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(112), static_cast<unsigned char>(128), static_cast<unsigned char>(144));
	return c;
}

const rgba_color& rgba_color::slate_grey() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(112), static_cast<unsigned char>(128), static_cast<unsigned char>(144));
	return c;
}

const rgba_color& rgba_color::snow() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(250), static_cast<unsigned char>(250));
	return c;
}

const rgba_color& rgba_color::spring_green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(255), static_cast<unsigned char>(127));
	return c;
}

const rgba_color& rgba_color::steel_blue() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(70), static_cast<unsigned char>(130), static_cast<unsigned char>(180));
	return c;
}

const rgba_color& rgba_color::tan() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(210), static_cast<unsigned char>(180), static_cast<unsigned char>(140));
	return c;
}

const rgba_color& rgba_color::teal() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(128), static_cast<unsigned char>(128));
	return c;
}

const rgba_color& rgba_color::thistle() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(216), static_cast<unsigned char>(191), static_cast<unsigned char>(216));
	return c;
}

const rgba_color& rgba_color::tomato() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(99), static_cast<unsigned char>(71));
	return c;
}

const rgba_color& rgba_color::transparent_black() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::turquoise() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(64), static_cast<unsigned char>(244), static_cast<unsigned char>(208));
	return c;
}

const rgba_color& rgba_color::violet() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(238), static_cast<unsigned char>(130), static_cast<unsigned char>(238));
	return c;
}

const rgba_color& rgba_color::wheat() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(245), static_cast<unsigned char>(222), static_cast<unsigned char>(179));
	return c;
}

const rgba_color& rgba_color::white() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(255), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::white_smoke() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(245), static_cast<unsigned char>(245), static_cast<unsigned char>(245));
	return c;
}

const rgba_color& rgba_color::yellow() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(255), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::yellow_green() {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(154), static_cast<unsigned char>(205), static_cast<unsigned char>(50));
	return c;
}


namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				rgba_color operator*(const rgba_color& lhs, double rhs) {
					rhs = ::std::max(rhs, 0.0);
					return{
						::std::min(lhs.r() * rhs, 1.0),
						::std::min(lhs.g() * rhs, 1.0),
						::std::min(lhs.b() * rhs, 1.0),
						::std::min(lhs.a() * rhs, 1.0)
					};
				}

				rgba_color operator*(double lhs, const rgba_color& rhs) {
					lhs = _Clamp_to_normal(lhs);
					return{
						::std::min(lhs * rhs.r(), 1.0),
						::std::min(lhs * rhs.g(), 1.0),
						::std::min(lhs * rhs.b(), 1.0),
						::std::min(lhs * rhs.a(), 1.0)
					};
				}

				rgba_color& operator*=(rgba_color& lhs, double rhs) {
					lhs = lhs * rhs;
					return lhs;
				}

				bool operator==(const rgba_color& lhs, const rgba_color& rhs) {
					return
						_Almost_equal_relative(lhs.r(), rhs.r()) &&
						_Almost_equal_relative(lhs.g(), rhs.g()) &&
						_Almost_equal_relative(lhs.b(), rhs.b()) &&
						_Almost_equal_relative(lhs.a(), rhs.a());
				}

				bool operator!=(const rgba_color& lhs, const rgba_color& rhs) {
					return !(lhs == rhs);
				}
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}
