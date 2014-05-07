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

radial_pattern::radial_pattern(const point& center0, double radius0, const point& center1, double radius1) : gradient_pattern(nullptr) {
	_Pattern = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(center0.x, center0.y, radius0, center1.x, center1.y, radius1), &cairo_pattern_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(_Pattern.get())));
}

void radial_pattern::get_radial_circles(point& center0, double& radius0, point& center1, double& radius1) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_get_radial_circles(_Pattern.get(), &center0.x, &center0.y, &radius0, &center1.x, &center1.y, &radius1)));
}
