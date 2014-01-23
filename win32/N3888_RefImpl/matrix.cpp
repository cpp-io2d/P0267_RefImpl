#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

void matrix::init(double xx, double yx, double xy, double yy, double x0, double y0) {
	*this = { xx, yx, xy, yy, x0, y0 };
}

void matrix::init_identity() {
	cairo_matrix_t cm{ };
	cairo_matrix_init_identity(&cm);
	xx = cm.xx;
	yx = cm.yx;
	xy = cm.xy;
	yy = cm.yy;
	x0 = cm.x0;
	y0 = cm.y0;
}

void matrix::init_translate(double tx, double ty) {
	cairo_matrix_t cm{ };
	cairo_matrix_init_translate(&cm, tx, ty);
	xx = cm.xx;
	yx = cm.yx;
	xy = cm.xy;
	yy = cm.yy;
	x0 = cm.x0;
	y0 = cm.y0;
}

void matrix::init_scale(double sx, double sy) {
	cairo_matrix_t cm{ };
	cairo_matrix_init_scale(&cm, sx, sy);
	xx = cm.xx;
	yx = cm.yx;
	xy = cm.xy;
	yy = cm.yy;
	x0 = cm.x0;
	y0 = cm.y0;
}

void matrix::init_rotate(double radians) {
	cairo_matrix_t cm{ };
	cairo_matrix_init_rotate(&cm, radians);
	xx = cm.xx;
	yx = cm.yx;
	xy = cm.xy;
	yy = cm.yy;
	x0 = cm.x0;
	y0 = cm.y0;
}

void matrix::translate(double tx, double ty) {
	cairo_matrix_t cm{ xx, yx, xy, yy, x0, y0 };
	cairo_matrix_translate(&cm, tx, ty);
	xx = cm.xx;
	yx = cm.yx;
	xy = cm.xy;
	yy = cm.yy;
	x0 = cm.x0;
	y0 = cm.y0;
}

void matrix::scale(double sx, double sy) {
	cairo_matrix_t cm{ xx, yx, xy, yy, x0, y0 };
	cairo_matrix_scale(&cm, sx, sy);
	xx = cm.xx;
	yx = cm.yx;
	xy = cm.xy;
	yy = cm.yy;
	x0 = cm.x0;
	y0 = cm.y0;
}

void matrix::rotate(double radians) {
	cairo_matrix_t cm{ xx, yx, xy, yy, x0, y0 };
	cairo_matrix_rotate(&cm, radians);
	xx = cm.xx;
	yx = cm.yx;
	xy = cm.xy;
	yy = cm.yy;
	x0 = cm.x0;
	y0 = cm.y0;
}

void matrix::invert() {
	cairo_matrix_t cm{ xx, yx, xy, yy, x0, y0 };
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_matrix_invert(&cm)));
	xx = cm.xx;
	yx = cm.yx;
	xy = cm.xy;
	yy = cm.yy;
	x0 = cm.x0;
	y0 = cm.y0;
}

matrix matrix::multiply(const matrix& a, const matrix& b) {
	cairo_matrix_t cr = { },
		ca{ a.xx, a.yx, a.xy, a.yy, a.x0, a.y0 },
		cb{ b.xx, b.yx, b.xy, b.yy, b.x0, b.y0 };
	cairo_matrix_multiply(&cr, &ca, &cb);
	return matrix { cr.xx, cr.yx, cr.xy, cr.yy, cr.x0, cr.y0 };
}

void matrix::transform_distance(double& dx, double& dy) {
	cairo_matrix_t cm{ xx, yx, xy, yy, x0, y0 };
	cairo_matrix_transform_distance(&cm, &dx, &dy);
}

void matrix::transform_point(double& x, double& y) {
	cairo_matrix_t cm{ xx, yx, xy, yy, x0, y0 };
	cairo_matrix_transform_point(&cm, &x, &y);
}
