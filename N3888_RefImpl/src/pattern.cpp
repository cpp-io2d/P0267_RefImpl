#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

pattern::native_handle_type pattern::native_handle() const {
	return _Pattern.get();
}

pattern::pattern(pattern::native_handle_type nh) {
	_Pattern = shared_ptr<cairo_pattern_t>(nh, &cairo_pattern_destroy);
}

pattern::pattern(pattern&& other) {
	_Pattern = move(other._Pattern);
	other._Pattern = nullptr;
}

pattern& pattern::operator=(pattern&& other) {
	if (this != &other) {
		_Pattern = move(other._Pattern);
		other._Pattern = nullptr;
	}
	return *this;
}

pattern::~pattern() {
}

status pattern::status() {
	return _Cairo_status_t_to_status(cairo_pattern_status(_Pattern.get()));
}

void pattern::set_extend(extend e) {
	cairo_pattern_set_extend(_Pattern.get(), _Extend_to_cairo_extend_t(e));
}

extend pattern::get_extend() {
	return _Cairo_extend_t_to_extend(cairo_pattern_get_extend(_Pattern.get()));
}

void pattern::set_filter(filter f) {
	cairo_pattern_set_filter(_Pattern.get(), _Filter_to_cairo_filter_t(f));
}

filter pattern::get_filter() {
	return _Cairo_filter_t_to_filter(cairo_pattern_get_filter(_Pattern.get()));
}

void pattern::set_matrix(const matrix& m) {
	cairo_matrix_t cm{ m.xx, m.yx, m.xy, m.yy, m.x0, m.y0 };
	cairo_pattern_set_matrix(_Pattern.get(), &cm);
}

pattern_type pattern::get_type() {
	return _Cairo_pattern_type_t_to_pattern_type(cairo_pattern_get_type(_Pattern.get()));
}
