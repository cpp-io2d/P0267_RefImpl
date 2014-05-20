#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

matrix matrix::init_identity() {
	return { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
}

matrix matrix::init_translate(const point& value) {
	return{ 1.0, 0.0, 0.0, 1.0, value.x, value.y };
}

matrix matrix::init_scale(const point& value) {
	return{ value.x, 0.0, 0.0, value.y, 0.0, 0.0 };
}

matrix matrix::init_rotate(double radians) {
	auto sine = sin(radians);
	auto cosine = cos(radians);
	return{ cosine, sine, -sine, cosine, 0.0, 0.0 };
}

void matrix::translate(const point& value) {
	cairo_matrix_t cm{ xx, yx, xy, yy, x0, y0 };
	cairo_matrix_translate(&cm, value.x, value.y);
	xx = cm.xx;
	yx = cm.yx;
	xy = cm.xy;
	yy = cm.yy;
	x0 = cm.x0;
	y0 = cm.y0;
}

void matrix::scale(const point& value) {
	cairo_matrix_t cm{ xx, yx, xy, yy, x0, y0 };
	cairo_matrix_scale(&cm, value.x, value.y);
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

matrix matrix::operator*=(const matrix& rhs) {
	xx = (xx * rhs.xx) + (yx * rhs.xy);
	yx = (xx * rhs.yx) + (yx * rhs.yy);
	xy = (xy * rhs.xx) + (yy * rhs.xy);
	yy = (xy * rhs.yx) + (yy * rhs.yy);
	x0 = (x0 * rhs.xx) + (y0 * rhs.xy) + x0;
	y0 = (x0 * rhs.yx) + (y0 * rhs.yy) + y0;

	return *this;
}

namespace std {
	namespace experimental {
		namespace drawing {
			matrix operator*(const matrix& lhs, const matrix& rhs) {
				//cairo_matrix_t cr = { },
				//	ca{ a.xx, a.yx, a.xy, a.yy, a.x0, a.y0 },
				//	cb{ b.xx, b.yx, b.xy, b.yy, b.x0, b.y0 };
				//cairo_matrix_multiply(&cr, &ca, &cb);
				//return matrix{ cr.xx, cr.yx, cr.xy, cr.yy, cr.x0, cr.y0 };
				return matrix{
					(lhs.xx * rhs.xx) + (lhs.yx * rhs.xy),
					(lhs.xx * rhs.yx) + (lhs.yx * rhs.yy),
					(lhs.xy * rhs.xx) + (lhs.yy * rhs.xy),
					(lhs.xy * rhs.yx) + (lhs.yy * rhs.yy),
					(lhs.x0 * rhs.xx) + (lhs.y0 * rhs.xy) + lhs.x0,
					(lhs.x0 * rhs.yx) + (lhs.y0 * rhs.yy) + lhs.y0
				};
			}
		}
	}
}

void matrix::transform_distance(point& dist) {
	cairo_matrix_t cm{ xx, yx, xy, yy, x0, y0 };
	cairo_matrix_transform_distance(&cm, &dist.x, &dist.y);
}

void matrix::transform_point(point& pt) {
	cairo_matrix_t cm{ xx, yx, xy, yy, x0, y0 };
	cairo_matrix_transform_point(&cm, &pt.x, &pt.y);
}
