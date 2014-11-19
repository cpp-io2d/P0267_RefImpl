#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"
#include <cmath>


using namespace std;
using namespace std::experimental::drawing;

namespace {

inline
double
det2x2(double a1, double a2, double b1, double b2) {
    return a1 * b2 - a2 * b1;
}

} // anon

matrix matrix::init_identity() {
    return{ 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
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

matrix matrix::init_shear_x(double factor) {
    return{ 1.0, 0.0, factor, 1.0, 0.0, 0.0 };
}

matrix matrix::init_shear_y(double factor) {
    return{ 1.0, factor, 0.0, 1.0, 0.0, 0.0 };
}

matrix& matrix::translate(const point& value) {
    *this = init_translate(value) * (*this);
    return *this;
}

matrix& matrix::scale(const point& value) {
    *this *= init_scale(value);
    return *this;
}

matrix& matrix::rotate(double radians) {
    *this *= init_rotate(radians);
    return *this;
}

matrix& matrix::shear_x(double factor) {
    *this *= init_shear_x(factor);
    return *this;
}

matrix& matrix::shear_y(double factor) {
    *this *= init_shear_y(factor);
    return *this;
}

double matrix::determinant() {
    if (isnan(x0) || isnan(y0)) {
        throw drawing_exception(status::invalid_matrix);
    }
    return xx * yy - yx * xy;
}

void matrix::invert() {
    // Yep, peeked at the cairo sources
    /* Simple scaling|translation matrices are quite common... */
    if (xy == 0. && yx == 0.) {
        x0 = -x0;
        y0 = -y0;

        if (xx != 1.) {
            if (xx == 0.)
            throw drawing_exception(status::invalid_matrix);

            xx = 1. / xx;
            x0 *= xx;
        }

        if (yy != 1.) {
            if (yy == 0.)
            throw drawing_exception(status::invalid_matrix);

            yy = 1. / yy;
            y0 *= yy;
        }
    } else {

        /* inv (A) = 1/det (A) * adj (A) */
        const double det = det2x2 (xx, yx, xy, yy);

        if (! isfinite (det))
            throw drawing_exception(status::invalid_matrix);

        if (det == 0)
            throw drawing_exception(status::invalid_matrix);

        const double a = xx, b = yx, c = xy, d = yy, tx = x0, ty = y0;
        const double onOverDet = 1 / det;

        xx = d * onOverDet;
        yx = -b * onOverDet;
        xy = -c * onOverDet;
        yy = a * onOverDet;
        x0 = (c * ty - d * tx) * onOverDet;
        y0 = (b * tx - a * ty) * onOverDet;
    }
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

point matrix::transform_distance(const point& dist) const {
    return{ xx * dist.x + xy * dist.y, yx * dist.x + yy * dist.y };
}

point matrix::transform_point(const point& pt) const {
    return transform_distance(pt) + point{ x0, y0 };
}
