#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

surface_pattern::surface_pattern(surface_pattern&& other) : pattern(move(other)) {
}

surface_pattern& surface_pattern::operator=(surface_pattern&& other) {
	if (this != &other) {
		pattern::operator=(move(other));
	}
	return *this;
}

surface_pattern::surface_pattern(surface& s) : pattern(nullptr) {
	_Pattern = shared_ptr<cairo_pattern_t>(cairo_pattern_create_for_surface(s.native_handle()), &cairo_pattern_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(_Pattern.get())));
}

void surface_pattern::get_surface(surface& s) {
	cairo_surface_t* p_surface = nullptr;
	auto status = _Cairo_status_t_to_status(cairo_pattern_get_surface(_Pattern.get(), &p_surface));

	if (status != status::success) {
		cairo_surface_destroy(p_surface);
		p_surface = nullptr;
		_Throw_if_failed_status(status);
	}

	s = p_surface;
}
