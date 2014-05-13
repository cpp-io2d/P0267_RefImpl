#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

pattern::native_handle_type pattern::native_handle() const {
    return _Pattern;
}

pattern::pattern(pattern::native_handle_type nh)
: _Pattern(nh)
, _Pattern_type(_Cairo_pattern_type_t_to_pattern_type(cairo_pattern_get_type(nh))) {
}

pattern::~pattern() {
    if (_Pattern != nullptr) {
        cairo_pattern_destroy(_Pattern);
        _Pattern = nullptr;
    }
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
