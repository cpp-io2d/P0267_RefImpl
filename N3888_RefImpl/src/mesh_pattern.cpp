#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

mesh_pattern::mesh_pattern() : pattern(nullptr) {
	_Pattern = shared_ptr<cairo_pattern_t>(cairo_pattern_create_mesh(), &cairo_pattern_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(_Pattern.get())));
}

mesh_pattern::mesh_pattern(mesh_pattern&& other) : pattern(move(other)) {
}

mesh_pattern& mesh_pattern::operator=(mesh_pattern&& other) {
	if (this != &other) {
		pattern::operator=(move(other));
	}
	return *this;
}

void mesh_pattern::begin_patch() {
	cairo_mesh_pattern_begin_patch(_Pattern.get());
}

void mesh_pattern::end_patch() {
	cairo_mesh_pattern_end_patch(_Pattern.get());
}

void mesh_pattern::move_to(double x, double y) {
	cairo_mesh_pattern_move_to(_Pattern.get(), x, y);
}

void mesh_pattern::line_to(double x, double y) {
	cairo_mesh_pattern_line_to(_Pattern.get(), x, y);
}

void mesh_pattern::curve_to(double x1, double y1, double x2, double y2, double x3, double y3) {
	cairo_mesh_pattern_curve_to(_Pattern.get(), x1, y1, x2, y2, x3, y3);
}

void mesh_pattern::set_control_point(unsigned int point_num, double x, double y) {
	cairo_mesh_pattern_set_control_point(_Pattern.get(), point_num, x, y);
}

void mesh_pattern::set_corner_color_rgb(unsigned int corner_num, double red, double green, double blue) {
	cairo_mesh_pattern_set_corner_color_rgb(_Pattern.get(), corner_num, red, green, blue);
}

void mesh_pattern::set_corner_color_rgba(unsigned int corner_num, double red, double green, double blue, double alpha) {
	cairo_mesh_pattern_set_corner_color_rgba(_Pattern.get(), corner_num, red, green, blue, alpha);
}

void mesh_pattern::get_patch_count(unsigned int& count) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_mesh_pattern_get_patch_count(_Pattern.get(), &count)));
}

path mesh_pattern::get_path(unsigned int patch_num) {
	unique_ptr<cairo_path_t, function<void(cairo_path_t*)>> sp_path(cairo_mesh_pattern_get_path(_Pattern.get(), patch_num), &cairo_path_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(sp_path->status));
	return _Make_path(sp_path.get());
}

void mesh_pattern::get_control_point(unsigned int patch_num, unsigned int point_num, double& x, double& y) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_mesh_pattern_get_control_point(_Pattern.get(), patch_num, point_num, &x, &y)));
}

void mesh_pattern::get_corner_color_rgba(unsigned int patch_num, unsigned int corner_num, double& red, double& green, double& blue, double& alpha) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_mesh_pattern_get_corner_color_rgba(_Pattern.get(), patch_num, corner_num, &red, &green, &blue, &alpha)));
}
