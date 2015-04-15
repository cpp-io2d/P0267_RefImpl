#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

rgba_color::rgba_color(rgba_color&& other) noexcept
	: _R(move(other._R))
	, _G(move(other._G))
	, _B(move(other._B))
	, _A(move(other._A)) {
	other._R = 0.0;
	other._G = 0.0;
	other._B = 0.0;
	other._A = 0.0;
}

rgba_color& rgba_color::operator=(rgba_color&& other) noexcept {
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
	if (red > 1.0 || red < 0.0 || green > 1.0 || green < 0.0 || blue > 1.0 || blue < 0.0 || alpha > 1.0 || alpha < 1.0) {
		throw out_of_range("The arguments must each fall between 0.0 and 1.0, inclusive.");
	}
}

rgba_color::rgba_color(double red, double green, double blue, error_code& ec) noexcept
	: _R(red)
	, _G(green)
	, _B(blue)
	, _A(1.0) {
	if (red > 1.0 || red < 0.0 || green > 1.0 || green < 0.0 || blue > 1.0 || blue < 0.0) {
		// Default to magenta for error visibility in case people don't check the ec.
		_R = 1.0;
		_G = 0.0;
		_B = 1.0;
		_A = 1.0;
		ec = make_error_code(errc::argument_out_of_domain);
	}
	else {
		ec.clear();
	}
}

rgba_color::rgba_color(double red, double green, double blue, double alpha, error_code& ec) noexcept
	: _R(red)
	, _G(green)
	, _B(blue)
	, _A(alpha) {
	if (red > 1.0 || red < 0.0 || green > 1.0 || green < 0.0 || blue > 1.0 || blue < 0.0 || alpha > 1.0 || alpha < 1.0) {
		// Default to magenta for error visibility in case people don't check the ec.
		_R = 1.0;
		_G = 0.0;
		_B = 1.0;
		_A = 1.0;
		ec = make_error_code(errc::argument_out_of_domain);
	}
	else {
		ec.clear();
	}
}

void rgba_color::r(double val) {
	if (val < 0.0 || val > 1.0) {
		throw system_error(make_error_code(errc::argument_out_of_domain));
	}
	_R = val;
}

void rgba_color::r(double val, error_code& ec) noexcept {
	if (val < 0.0 || val > 1.0) {
		ec = make_error_code(errc::argument_out_of_domain);
		return;
	}
	_R = val;
	ec.clear();
}

void rgba_color::g(double val) {
	if (val < 0.0 || val > 1.0) {
		throw system_error(make_error_code(errc::argument_out_of_domain));
	}
	_G = val;
}

void rgba_color::g(double val, error_code& ec) noexcept {
	if (val < 0.0 || val > 1.0) {
		ec = make_error_code(errc::argument_out_of_domain);
		return;
	}
	_G = val;
	ec.clear();
}

void rgba_color::b(double val) {
	if (val < 0.0 || val > 1.0) {
		throw system_error(make_error_code(errc::argument_out_of_domain));
	}
	_B = val;
}

void rgba_color::b(double val, error_code& ec) noexcept {
	if (val < 0.0 || val > 1.0) {
		ec = make_error_code(errc::argument_out_of_domain);
		return;
	}
	_B = val;
	ec.clear();
}

void rgba_color::a(double val) {
	if (val < 0.0 || val > 1.0) {
		throw system_error(make_error_code(errc::argument_out_of_domain));
	}
	_R *= val;
	_G *= val;
	_B *= val;
	_A = val;
}

void rgba_color::a(double val, error_code& ec) noexcept {
	if (val < 0.0 || val > 1.0) {
		ec = make_error_code(errc::argument_out_of_domain);
		return;
	}
	_R *= val;
	_G *= val;
	_B *= val;
	_A = val;
	ec.clear();
}

double rgba_color::r() const noexcept {
	return _R;
}

double rgba_color::g() const noexcept {
	return _G;
}

double rgba_color::b() const noexcept {
	return _B;
}

double rgba_color::a() const noexcept {
	return _A;
}

rgba_color _Rgba_color_from_byte_values(unsigned char r, unsigned char g, unsigned char b, unsigned char a = static_cast<unsigned char>(255)) noexcept;
rgba_color _Rgba_color_from_byte_values(unsigned char r, unsigned char g, unsigned char b, unsigned char a) noexcept {
	return{ static_cast<double>(r) / 255.0, static_cast<double>(g) / 255.0, static_cast<double>(b) / 255.0, static_cast<double>(a) / 255.0 };
}

const rgba_color& rgba_color::alice_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(240), static_cast<unsigned char>(248), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::antique_white() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(250), static_cast<unsigned char>(235), static_cast<unsigned char>(215));
	return c;
}

const rgba_color& rgba_color::aqua() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(255), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::aquamarine() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(127), static_cast<unsigned char>(255), static_cast<unsigned char>(212));
	return c;
}

const rgba_color& rgba_color::azure() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(240), static_cast<unsigned char>(255), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::beige() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(245), static_cast<unsigned char>(245), static_cast<unsigned char>(220));
	return c;
}

const rgba_color& rgba_color::bisque() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(228), static_cast<unsigned char>(196));
	return c;
}

const rgba_color& rgba_color::black() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::blanched_almond() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(235), static_cast<unsigned char>(205));
	return c;
}

const rgba_color& rgba_color::blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::blue_violet() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(138), static_cast<unsigned char>(43), static_cast<unsigned char>(226));
	return c;
}

const rgba_color& rgba_color::brown() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(165), static_cast<unsigned char>(42), static_cast<unsigned char>(42));
	return c;
}

const rgba_color& rgba_color::burly_wood() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(222), static_cast<unsigned char>(184), static_cast<unsigned char>(135));
	return c;
}

const rgba_color& rgba_color::cadet_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(95), static_cast<unsigned char>(158), static_cast<unsigned char>(160));
	return c;
}

const rgba_color& rgba_color::chartreuse() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(127), static_cast<unsigned char>(255), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::chocolate() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(210), static_cast<unsigned char>(105), static_cast<unsigned char>(30));
	return c;
}

const rgba_color& rgba_color::coral() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(127), static_cast<unsigned char>(80));
	return c;
}

const rgba_color& rgba_color::cornflower_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(100), static_cast<unsigned char>(149), static_cast<unsigned char>(237));
	return c;
}

const rgba_color& rgba_color::cornsilk() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(248), static_cast<unsigned char>(220));
	return c;
}

const rgba_color& rgba_color::crimson() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(220), static_cast<unsigned char>(20), static_cast<unsigned char>(60));
	return c;
}

const rgba_color& rgba_color::cyan() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(255), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::dark_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(139));
	return c;
}

const rgba_color& rgba_color::dark_cyan() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(139), static_cast<unsigned char>(139));
	return c;
}

const rgba_color& rgba_color::dark_goldenrod() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(184), static_cast<unsigned char>(134), static_cast<unsigned char>(11));
	return c;
}

const rgba_color& rgba_color::dark_gray() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(169), static_cast<unsigned char>(169), static_cast<unsigned char>(169));
	return c;
}

const rgba_color& rgba_color::dark_green() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(100), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::dark_grey() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(169), static_cast<unsigned char>(169), static_cast<unsigned char>(169));
	return c;
}

const rgba_color& rgba_color::dark_khaki() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(189), static_cast<unsigned char>(183), static_cast<unsigned char>(107));
	return c;
}

const rgba_color& rgba_color::dark_magenta() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(139), static_cast<unsigned char>(0), static_cast<unsigned char>(139));
	return c;
}

const rgba_color& rgba_color::dark_olive_green() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(85), static_cast<unsigned char>(107), static_cast<unsigned char>(47));
	return c;
}

const rgba_color& rgba_color::dark_orange() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(140), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::dark_orchid() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(153), static_cast<unsigned char>(50), static_cast<unsigned char>(204));
	return c;
}

const rgba_color& rgba_color::dark_red() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(139), static_cast<unsigned char>(0), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::dark_salmon() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(233), static_cast<unsigned char>(150), static_cast<unsigned char>(122));
	return c;
}

const rgba_color& rgba_color::dark_sea_green() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(143), static_cast<unsigned char>(188), static_cast<unsigned char>(143));
	return c;
}

const rgba_color& rgba_color::dark_slate_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(72), static_cast<unsigned char>(61), static_cast<unsigned char>(139));
	return c;
}

const rgba_color& rgba_color::dark_slate_gray() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(47), static_cast<unsigned char>(79), static_cast<unsigned char>(79));
	return c;
}

const rgba_color& rgba_color::dark_slate_grey() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(47), static_cast<unsigned char>(79), static_cast<unsigned char>(79));
	return c;
}

const rgba_color& rgba_color::dark_turquoise() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(206), static_cast<unsigned char>(209));
	return c;
}

const rgba_color& rgba_color::dark_violet() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(148), static_cast<unsigned char>(0), static_cast<unsigned char>(211));
	return c;
}

const rgba_color& rgba_color::deep_pink() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(20), static_cast<unsigned char>(147));
	return c;
}

const rgba_color& rgba_color::deep_sky_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(191), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::dim_gray() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(105), static_cast<unsigned char>(105), static_cast<unsigned char>(105));
	return c;
}

const rgba_color& rgba_color::dim_grey() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(105), static_cast<unsigned char>(105), static_cast<unsigned char>(105));
	return c;
}

const rgba_color& rgba_color::dodger_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(30), static_cast<unsigned char>(144), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::firebrick() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(178), static_cast<unsigned char>(34), static_cast<unsigned char>(34));
	return c;
}

const rgba_color& rgba_color::floral_white() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(250), static_cast<unsigned char>(240));
	return c;
}

const rgba_color& rgba_color::forest_green() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(34), static_cast<unsigned char>(139), static_cast<unsigned char>(34));
	return c;
}

const rgba_color& rgba_color::fuchsia() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(0), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::gainsboro() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(220), static_cast<unsigned char>(220), static_cast<unsigned char>(220));
	return c;
}

const rgba_color& rgba_color::ghost_white() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(248), static_cast<unsigned char>(248), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::gold() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(215), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::goldenrod() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(218), static_cast<unsigned char>(165), static_cast<unsigned char>(32));
	return c;
}

const rgba_color& rgba_color::gray() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(128), static_cast<unsigned char>(128), static_cast<unsigned char>(128));
	return c;
}

const rgba_color& rgba_color::green() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(128), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::green_yellow() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(173), static_cast<unsigned char>(255), static_cast<unsigned char>(47));
	return c;
}

const rgba_color& rgba_color::grey() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(128), static_cast<unsigned char>(128), static_cast<unsigned char>(128));
	return c;
}

const rgba_color& rgba_color::honeydew() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(240), static_cast<unsigned char>(255), static_cast<unsigned char>(240));
	return c;
}

const rgba_color& rgba_color::hot_pink() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(105), static_cast<unsigned char>(180));
	return c;
}

const rgba_color& rgba_color::indian_red() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(205), static_cast<unsigned char>(92), static_cast<unsigned char>(92));
	return c;
}

const rgba_color& rgba_color::indigo() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(75), static_cast<unsigned char>(0), static_cast<unsigned char>(130));
	return c;
}

const rgba_color& rgba_color::ivory() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(255), static_cast<unsigned char>(240));
	return c;
}

const rgba_color& rgba_color::khaki() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(240), static_cast<unsigned char>(230), static_cast<unsigned char>(140));
	return c;
}

const rgba_color& rgba_color::lavender() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(230), static_cast<unsigned char>(230), static_cast<unsigned char>(250));
	return c;
}

const rgba_color& rgba_color::lavender_blush() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(240), static_cast<unsigned char>(245));
	return c;
}

const rgba_color& rgba_color::lawn_green() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(124), static_cast<unsigned char>(252), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::lemon_chiffon() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(250), static_cast<unsigned char>(205));
	return c;
}

const rgba_color& rgba_color::light_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(173), static_cast<unsigned char>(216), static_cast<unsigned char>(230));
	return c;
}

const rgba_color& rgba_color::light_coral() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(240), static_cast<unsigned char>(128), static_cast<unsigned char>(128));
	return c;
}

const rgba_color& rgba_color::light_cyan() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(224), static_cast<unsigned char>(255), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::light_goldenrod_yellow() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(250), static_cast<unsigned char>(250), static_cast<unsigned char>(210));
	return c;
}

const rgba_color& rgba_color::light_gray() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(211), static_cast<unsigned char>(211), static_cast<unsigned char>(211));
	return c;
}

const rgba_color& rgba_color::light_green() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(144), static_cast<unsigned char>(238), static_cast<unsigned char>(144));
	return c;
}

const rgba_color& rgba_color::light_grey() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(211), static_cast<unsigned char>(211), static_cast<unsigned char>(211));
	return c;
}

const rgba_color& rgba_color::light_pink() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(182), static_cast<unsigned char>(193));
	return c;
}

const rgba_color& rgba_color::light_salmon() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(160), static_cast<unsigned char>(122));
	return c;
}

const rgba_color& rgba_color::light_sea_green() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(32), static_cast<unsigned char>(178), static_cast<unsigned char>(170));
	return c;
}

const rgba_color& rgba_color::light_sky_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(135), static_cast<unsigned char>(206), static_cast<unsigned char>(250));
	return c;
}

const rgba_color& rgba_color::light_slate_gray() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(119), static_cast<unsigned char>(136), static_cast<unsigned char>(153));
	return c;
}

const rgba_color& rgba_color::light_slate_grey() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(119), static_cast<unsigned char>(136), static_cast<unsigned char>(153));
	return c;
}

const rgba_color& rgba_color::light_steel_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(176), static_cast<unsigned char>(196), static_cast<unsigned char>(222));
	return c;
}

const rgba_color& rgba_color::light_yellow() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(255), static_cast<unsigned char>(224));
	return c;
}

const rgba_color& rgba_color::lime() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(255), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::lime_green() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(50), static_cast<unsigned char>(205), static_cast<unsigned char>(50));
	return c;
}

const rgba_color& rgba_color::linen() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(250), static_cast<unsigned char>(240), static_cast<unsigned char>(230));
	return c;
}

const rgba_color& rgba_color::magenta() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(0), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::maroon() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(128), static_cast<unsigned char>(0), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::medium_aquamarine() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(102), static_cast<unsigned char>(205), static_cast<unsigned char>(170));
	return c;
}

const rgba_color& rgba_color::medium_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(205));
	return c;
}

const rgba_color& rgba_color::medium_orchid() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(186), static_cast<unsigned char>(85), static_cast<unsigned char>(211));
	return c;
}

const rgba_color& rgba_color::medium_purple() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(147), static_cast<unsigned char>(112), static_cast<unsigned char>(219));
	return c;
}

const rgba_color& rgba_color::medium_sea_green() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(60), static_cast<unsigned char>(179), static_cast<unsigned char>(113));
	return c;
}

const rgba_color& rgba_color::medium_slate_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(123), static_cast<unsigned char>(104), static_cast<unsigned char>(238));
	return c;
}

const rgba_color& rgba_color::medium_spring_green() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(250), static_cast<unsigned char>(154));
	return c;
}

const rgba_color& rgba_color::medium_turquoise() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(72), static_cast<unsigned char>(209), static_cast<unsigned char>(204));
	return c;
}

const rgba_color& rgba_color::medium_violet_red() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(199), static_cast<unsigned char>(21), static_cast<unsigned char>(133));
	return c;
}

const rgba_color& rgba_color::midnight_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(25), static_cast<unsigned char>(25), static_cast<unsigned char>(112));
	return c;
}

const rgba_color& rgba_color::mint_cream() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(245), static_cast<unsigned char>(255), static_cast<unsigned char>(250));
	return c;
}

const rgba_color& rgba_color::misty_rose() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(228), static_cast<unsigned char>(225));
	return c;
}

const rgba_color& rgba_color::moccasin() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(228), static_cast<unsigned char>(181));
	return c;
}

const rgba_color& rgba_color::navajo_white() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(222), static_cast<unsigned char>(173));
	return c;
}

const rgba_color& rgba_color::navy() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(128));
	return c;
}

const rgba_color& rgba_color::old_lace() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(253), static_cast<unsigned char>(245), static_cast<unsigned char>(230));
	return c;
}

const rgba_color& rgba_color::olive() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(128), static_cast<unsigned char>(128), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::olive_drab() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(107), static_cast<unsigned char>(142), static_cast<unsigned char>(35));
	return c;
}

const rgba_color& rgba_color::orange() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(165), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::orange_red() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(69), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::orchid() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(218), static_cast<unsigned char>(112), static_cast<unsigned char>(214));
	return c;
}

const rgba_color& rgba_color::pale_goldenrod() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(238), static_cast<unsigned char>(232), static_cast<unsigned char>(170));
	return c;
}

const rgba_color& rgba_color::pale_green() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(152), static_cast<unsigned char>(251), static_cast<unsigned char>(152));
	return c;
}

const rgba_color& rgba_color::pale_turquoise() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(175), static_cast<unsigned char>(238), static_cast<unsigned char>(238));
	return c;
}

const rgba_color& rgba_color::pale_violet_red() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(219), static_cast<unsigned char>(112), static_cast<unsigned char>(147));
	return c;
}

const rgba_color& rgba_color::papaya_whip() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(239), static_cast<unsigned char>(213));
	return c;
}

const rgba_color& rgba_color::peach_puff() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(218), static_cast<unsigned char>(185));
	return c;
}

const rgba_color& rgba_color::peru() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(205), static_cast<unsigned char>(133), static_cast<unsigned char>(63));
	return c;
}

const rgba_color& rgba_color::pink() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(192), static_cast<unsigned char>(203));
	return c;
}

const rgba_color& rgba_color::plum() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(221), static_cast<unsigned char>(160), static_cast<unsigned char>(221));
	return c;
}

const rgba_color& rgba_color::powder_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(176), static_cast<unsigned char>(224), static_cast<unsigned char>(230));
	return c;
}

const rgba_color& rgba_color::purple() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(128), static_cast<unsigned char>(0), static_cast<unsigned char>(128));
	return c;
}

const rgba_color& rgba_color::red() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(0), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::rosy_brown() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(188), static_cast<unsigned char>(143), static_cast<unsigned char>(143));
	return c;
}

const rgba_color& rgba_color::royal_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(65), static_cast<unsigned char>(105), static_cast<unsigned char>(225));
	return c;
}

const rgba_color& rgba_color::saddle_brown() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(139), static_cast<unsigned char>(69), static_cast<unsigned char>(19));
	return c;
}

const rgba_color& rgba_color::salmon() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(250), static_cast<unsigned char>(128), static_cast<unsigned char>(114));
	return c;
}

const rgba_color& rgba_color::sandy_brown() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(244), static_cast<unsigned char>(164), static_cast<unsigned char>(96));
	return c;
}

const rgba_color& rgba_color::sea_green() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(46), static_cast<unsigned char>(139), static_cast<unsigned char>(87));
	return c;
}

const rgba_color& rgba_color::sea_shell() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(245), static_cast<unsigned char>(238));
	return c;
}

const rgba_color& rgba_color::sienna() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(160), static_cast<unsigned char>(82), static_cast<unsigned char>(45));
	return c;
}

const rgba_color& rgba_color::silver() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(192), static_cast<unsigned char>(192), static_cast<unsigned char>(192));
	return c;
}

const rgba_color& rgba_color::sky_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(135), static_cast<unsigned char>(206), static_cast<unsigned char>(235));
	return c;
}

const rgba_color& rgba_color::slate_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(106), static_cast<unsigned char>(90), static_cast<unsigned char>(205));
	return c;
}

const rgba_color& rgba_color::slate_gray() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(112), static_cast<unsigned char>(128), static_cast<unsigned char>(144));
	return c;
}

const rgba_color& rgba_color::slate_grey() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(112), static_cast<unsigned char>(128), static_cast<unsigned char>(144));
	return c;
}

const rgba_color& rgba_color::snow() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(250), static_cast<unsigned char>(250));
	return c;
}

const rgba_color& rgba_color::spring_green() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(255), static_cast<unsigned char>(127));
	return c;
}

const rgba_color& rgba_color::steel_blue() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(70), static_cast<unsigned char>(130), static_cast<unsigned char>(180));
	return c;
}

const rgba_color& rgba_color::tan() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(210), static_cast<unsigned char>(180), static_cast<unsigned char>(140));
	return c;
}

const rgba_color& rgba_color::teal() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(128), static_cast<unsigned char>(128));
	return c;
}

const rgba_color& rgba_color::thistle() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(216), static_cast<unsigned char>(191), static_cast<unsigned char>(216));
	return c;
}

const rgba_color& rgba_color::tomato() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(99), static_cast<unsigned char>(71));
	return c;
}

const rgba_color& rgba_color::transparent_black() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(0), static_cast<unsigned char>(0), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::turquoise() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(64), static_cast<unsigned char>(244), static_cast<unsigned char>(208));
	return c;
}

const rgba_color& rgba_color::violet() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(238), static_cast<unsigned char>(130), static_cast<unsigned char>(238));
	return c;
}

const rgba_color& rgba_color::wheat() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(245), static_cast<unsigned char>(222), static_cast<unsigned char>(179));
	return c;
}

const rgba_color& rgba_color::white() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(255), static_cast<unsigned char>(255));
	return c;
}

const rgba_color& rgba_color::white_smoke() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(245), static_cast<unsigned char>(245), static_cast<unsigned char>(245));
	return c;
}

const rgba_color& rgba_color::yellow() noexcept {
	static auto c = _Rgba_color_from_byte_values(static_cast<unsigned char>(255), static_cast<unsigned char>(255), static_cast<unsigned char>(0));
	return c;
}

const rgba_color& rgba_color::yellow_green() noexcept {
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
					return lhs.r() == rhs.r() && lhs.g() == rhs.g() && lhs.b() == rhs.b() && lhs.a() == rhs.a();
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
