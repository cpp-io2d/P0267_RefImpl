#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

solid_color_pattern::solid_color_pattern(solid_color_pattern&& other) : pattern(move(other)) {
}

solid_color_pattern& solid_color_pattern::operator=(solid_color_pattern&& other) {
	pattern::operator=(move(other));
	return *this;
}

solid_color_pattern::solid_color_pattern(double red, double green, double blue) : pattern(nullptr) {
	_Pattern = shared_ptr<cairo_pattern_t>(cairo_pattern_create_rgb(red, green, blue), &cairo_pattern_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(_Pattern.get())));
}

solid_color_pattern::solid_color_pattern(double red, double green, double blue, double alpha) : pattern(nullptr) {
	_Pattern = shared_ptr<cairo_pattern_t>(cairo_pattern_create_rgba(red, green, blue, alpha), &cairo_pattern_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(_Pattern.get())));
}

void solid_color_pattern::get_rgba(double& red, double& green, double& blue, double& alpha) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_get_rgba(_Pattern.get(), &red, &green, &blue, &alpha)));
}
