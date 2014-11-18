#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

//surface_pattern_builder::surface_pattern_builder(surface_pattern_builder&& other)
//: _Pattern_type(move(other._Pattern_type))
//, _Extend(move(other._Extend))
//, _Filter(move(other._Filter))
//, _Matrix(move(other._Matrix))
//, _Surface(move(other._Surface)) {
//}
//
//surface_pattern_builder& surface_pattern_builder::operator=(surface_pattern_builder&& other) {
//    if (this != &other) {
//        _Pattern_type = move(other._Pattern_type);
//        _Extend = move(other._Extend);
//        _Filter = move(other._Filter);
//        _Matrix = move(other._Matrix);
//        _Surface = move(other._Surface);
//    }
//    return *this;
//}
//
//surface_pattern_builder::surface_pattern_builder(surface&& s)
//: _Pattern_type(pattern_type::surface)
//, _Extend(extend::default_extend)
//, _Filter(filter::default_filter)
//, _Matrix(matrix::init_identity())
//, _Surface(move(s)) {
//}
//
//pattern surface_pattern_builder::get_pattern() {
//    if (!_Surface.has_surface_resource()) {
//        _Throw_if_failed_status(status::null_pointer);
//    }
//    auto pat = cairo_pattern_create_for_surface(_Surface.native_handle());
//    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));
//
//    cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(_Extend));
//    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));
//    cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(_Filter));
//    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));
//    cairo_matrix_t mtrx{ _Matrix.xx, _Matrix.yx, _Matrix.xy, _Matrix.yy, _Matrix.x0, _Matrix.y0 };
//    cairo_pattern_set_matrix(pat, &mtrx);
//    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));
//
//    return pattern(pat);
//}
//
//void surface_pattern_builder::set_extend(extend e) {
//    _Extend = e;
//}
//
//extend surface_pattern_builder::get_extend() {
//    return _Extend;
//}
//
//void surface_pattern_builder::set_filter(filter f) {
//    _Filter = f;
//}
//
//filter surface_pattern_builder::get_filter() {
//    return _Filter;
//}
//
//void surface_pattern_builder::set_matrix(const matrix& m) {
//    _Matrix = m;
//}
//
//matrix surface_pattern_builder::get_matrix() {
//    return _Matrix;
//}
//
//surface& surface_pattern_builder::get_surface() {
//    return _Surface;
//}
