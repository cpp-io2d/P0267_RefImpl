#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

font_options::native_handle_type font_options::native_handle() const {
	return _Font_options.get();
}

font_options::font_options(font_options&& other) {
	_Font_options = move(other._Font_options);
	other._Font_options = nullptr;
}

font_options& font_options::operator=(font_options&& other) {
	if (this != &other) {
		_Font_options = move(other._Font_options);
		other._Font_options = nullptr;
	}
	return *this;
}

font_options::font_options(antialias a, subpixel_order /*so*/, hint_style hs, hint_metrics /*hm*/)
: _Font_options(shared_ptr<_QFontOptions>(new _QFontOptions)) {
    _Font_options->styleStrategy = _Antialias_to_QFontOptions(a);
    _Font_options->hintingPreference = _Hint_style_to_QFontOptions(hs);
}

font_options::font_options(font_options::native_handle_type nh) {
    _Font_options = shared_ptr<_QFontOptions>(nh);
}

antialias font_options::get_antialias() const {
    return _QFontOptions_to_antialias(_Font_options->styleStrategy);
}

subpixel_order font_options::get_subpixel_order() const {
    return subpixel_order::default_subpixel_order;
}

hint_style font_options::get_hint_style() const {
    return _QFontOptions_to_hint_style(_Font_options->hintingPreference);
}

hint_metrics font_options::get_hint_metrics() const {
    return hint_metrics::default_hint_metrics;
}
