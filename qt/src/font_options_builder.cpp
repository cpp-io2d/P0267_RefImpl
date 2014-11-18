#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

font_options_builder::font_options_builder(font_options_builder&& other)
: _Antialias(move(other._Antialias))
, _Subpixel_order(move(other._Subpixel_order))
, _Hint_style(move(other._Hint_style))
, _Hint_metrics(move(other._Hint_metrics)) {
}

font_options_builder& font_options_builder::operator=(font_options_builder&& other) {
	if (this != &other) {
		_Antialias = move(other._Antialias);
		_Subpixel_order = move(other._Subpixel_order);
		_Hint_style = move(other._Hint_style);
		_Hint_metrics = move(other._Hint_metrics);
	}
	return *this;
}

font_options font_options_builder::get_font_options() const {
	return font_options(_Antialias, _Subpixel_order, _Hint_style, _Hint_metrics);
}

void font_options_builder::set_antialias(antialias a) {
	_Antialias = a;
}

antialias font_options_builder::get_antialias() const {
	return _Antialias;
}

void font_options_builder::set_subpixel_order(subpixel_order so) {
	_Subpixel_order = so;
}

subpixel_order font_options_builder::get_subpixel_order() const {
	return _Subpixel_order;
}

void font_options_builder::set_hint_style(hint_style hs) {
	_Hint_style = hs;
}

hint_style font_options_builder::get_hint_style() const {
	return _Hint_style;
}

void font_options_builder::set_hint_metrics(hint_metrics hm) {
	_Hint_metrics = hm;
}

hint_metrics font_options_builder::get_hint_metrics() const {
	return _Hint_metrics;
}
