#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

radial_pattern::radial_pattern(radial_pattern&& other) : gradient_pattern(move(other)) {
}

radial_pattern& radial_pattern::operator=(radial_pattern&& other) {
	if (this != &other) {
		gradient_pattern::operator=(move(other));
	}
	return *this;
}

radial_pattern::radial_pattern(double cx0, double cy0, double radius0, double cx1, double cy1, double radius1) : gradient_pattern(nullptr) {
	_Pattern = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(cx0, cy0, radius0, cx1, cy1, radius1), &cairo_pattern_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(_Pattern.get())));
}

void radial_pattern::get_radial_circles(double& x0, double& y0, double& radius0, double& x1, double& y1, double& radius1) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_get_radial_circles(_Pattern.get(), &x0, &y0, &radius0, &x1, &y1, &radius1)));
}
