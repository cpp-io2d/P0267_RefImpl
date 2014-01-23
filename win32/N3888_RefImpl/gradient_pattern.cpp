#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

gradient_pattern::gradient_pattern(gradient_pattern::native_handle_type nh) : pattern(nh) {
}

gradient_pattern::gradient_pattern(gradient_pattern&& other) : pattern(move(other)) {
}

gradient_pattern& gradient_pattern::operator=(gradient_pattern&& other) {
	if (this != &other) {
		pattern::operator=(move(other));
	}
	return *this;
}

void gradient_pattern::add_color_stop_rgb(double offset, double red, double green, double blue) {
	cairo_pattern_add_color_stop_rgb(_Pattern.get(), offset, red, green, blue);
}

void gradient_pattern::add_color_stop_rgba(double offset, double red, double green, double blue, double alpha) {
	cairo_pattern_add_color_stop_rgba(_Pattern.get(), offset, red, green, blue, alpha);
}

void gradient_pattern::get_color_stop_count(int& count) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_get_color_stop_count(_Pattern.get(), &count)));
}

void gradient_pattern::get_color_stop_rgba(int index, double& offset, double& red, double& green, double& blue, double& alpha) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_get_color_stop_rgba(_Pattern.get(), index, &offset, &red, &green, &blue, &alpha)));
}
