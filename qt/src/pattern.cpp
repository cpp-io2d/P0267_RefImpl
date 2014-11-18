#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

pattern::native_handle_type pattern::native_handle() const {
	return _Pattern.get();
}

pattern::pattern(pattern::native_handle_type nh)
: _Pattern(nh)
, _Pattern_type(_Qt_brush_style_to_pattern_type(nh->style())) {
}

pattern::~pattern() {
	_Pattern = nullptr;
}

pattern::pattern(pattern&& other)
: _Pattern(move(other._Pattern))
, _Pattern_type(move(other._Pattern_type)) {
	other._Pattern = nullptr;
}

pattern& pattern::operator=(pattern&& other) {
	if (this != &other) {
		_Pattern = move(other._Pattern);
		_Pattern_type = move(other._Pattern_type);
		other._Pattern = nullptr;
	}

	return *this;
}

pattern_type pattern::get_type() const {
	return _Pattern_type;
}
