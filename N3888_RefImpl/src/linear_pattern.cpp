#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

linear_pattern::linear_pattern(linear_pattern&& other) : gradient_pattern(move(other)) {
}

linear_pattern& linear_pattern::operator=(linear_pattern&& other) {
	if (this != &other) {
		gradient_pattern::operator=(move(other));
	}
	return *this;
}

linear_pattern::linear_pattern(const point& pt0, const point& pt1) : gradient_pattern(nullptr) {
	_Pattern = shared_ptr<cairo_pattern_t>(cairo_pattern_create_linear(pt0.x, pt0.y, pt1.x, pt1.y), &cairo_pattern_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(_Pattern.get())));
}

void linear_pattern::get_linear_points(point& pt0, point& pt1) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_get_linear_points(_Pattern.get(), &pt0.x, &pt0.y, &pt1.x, &pt1.y)));
}
