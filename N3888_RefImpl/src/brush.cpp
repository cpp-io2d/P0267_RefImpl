#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

brush::native_handle_type brush::native_handle() const noexcept {
	return _Brush.get();
}

brush::brush(brush::native_handle_type nh) noexcept
	: _Brush(nh, &cairo_pattern_destroy)
	, _Brush_type(_Cairo_pattern_type_t_to_brush_type(cairo_pattern_get_type(nh)))
	, _Extend(::std::experimental::io2d::tiling::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
}

brush::brush(const rgba_color& color)
: _Brush()
, _Image_surface()
, _Brush_type(brush_type::solid_color)
, _Extend(::std::experimental::io2d::tiling::none)
, _Filter(::std::experimental::io2d::filter::good)
, _Matrix(matrix_2d::init_identity()) {
	_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_rgba(color.r(), color.g(), color.b(), color.a()), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
}

brush::brush(const rgba_color& color, error_code& ec) noexcept
	: _Brush()
	, _Image_surface()
	, _Brush_type(brush_type::solid_color)
	, _Extend(::std::experimental::io2d::tiling::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
	try {
		_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_rgba(color.r(), color.g(), color.b(), color.a()), &cairo_pattern_destroy);
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (const ::std::length_error&) {
		_Brush.reset();
		ec = ::std::make_error_code(::std::errc::not_enough_memory);
		return;
	}

	auto status = cairo_pattern_status(_Brush.get());
	if (status != CAIRO_STATUS_SUCCESS) {
		ec = _Cairo_status_t_to_std_error_code(status);
		_Brush.reset();
		return;
	}
	ec.clear();
}

template <class Allocator>
brush::brush(const vector_2d& begin, const vector_2d& end,
	const color_stop_group<Allocator>& csg)
	: _Brush()
	, _Image_surface()
	, _Brush_type(brush_type::linear)
	, _Extend(::std::experimental::io2d::tiling::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
	vector_2d lpt0 = f.begin_point();
	vector_2d lpt1 = f.end_point();
	_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_linear(lpt0.x(), lpt0.y(), lpt1.x(), lpt1.y()), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

	//auto count = f.color_stop_count();
	//for (unsigned int i = 0; i < count; i++) {
	for (const color_stop& stop : csg) {
		//double& offset = get<0>(stop);
		//rgba_color& color = get<1>(stop);
		cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color.r(), stop.color.g(), stop.color.b(), stop.color.a());
	}
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
}

template <class Allocator>
brush::brush(const vector_2d& begin, const vector_2d& end,
	const color_stop_group<Allocator>& csg, error_code& ec) noexcept
	: _Brush()
	, _Image_surface()
	, _Brush_type(brush_type::linear)
	, _Extend(::std::experimental::io2d::tiling::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
	vector_2d lpt0 = f.begin_point();
	vector_2d lpt1 = f.end_point();
	try {
		_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_linear(lpt0.x(), lpt0.y(), lpt1.x(), lpt1.y()), &cairo_pattern_destroy);
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		_Brush.reset();
		return;
	}
	catch (const ::std::length_error&) {
		_Brush.reset();
		ec = ::std::make_error_code(::std::errc::not_enough_memory);
		return;
	}

	auto status = cairo_pattern_status(_Brush.get());
	if (status != CAIRO_STATUS_SUCCESS) {
		ec = _Cairo_status_t_to_std_error_code(status);
		_Brush.reset();
		return;
	}

	//auto count = f.color_stop_count();
	//for (unsigned int i = 0; i < count; i++) {
	//	auto stop = f.color_stop(i);
	//	double& offset = get<0>(stop);
	//	rgba_color& color = get<1>(stop);
	for (const color_stop& stop : csg) {
		cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color.r(), stop.color.g(), stop.color.b(), stop.color.a());
	}
	status = cairo_pattern_status(_Brush.get());
	if (status != CAIRO_STATUS_SUCCESS) {
		ec = _Cairo_status_t_to_std_error_code(status);
		_Brush.reset();
		return;
	}
	ec.clear();
}

template <class Allocator>
brush::brush(const circle& start, const circle& end,
	const color_stop_group<Allocator>& csg)
	: _Brush()
	, _Brush_type(brush_type::radial)
	, _Extend(::std::experimental::io2d::tiling::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
	//auto points = f.radial_circles();
	//vector_2d& center0 = get<0>(points);
	//double& radius0 = get<1>(points);
	//vector_2d& center1 = get<2>(points);
	//double& radius1 = get<3>(points);
	//_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(center0.x(), center0.y(), radius0, center1.x(), center1.y(), radius1), &cairo_pattern_destroy);
	_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(start.center().x(), start.center.y(), start.radius(), end.center.x(), end.center.y(), end.radius()), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

	//auto count = f.color_stop_count();
	//for (unsigned int i = 0; i < count; i++) {
	//	auto stop = f.color_stop(i);
	//	double& offset = get<0>(stop);
	//	rgba_color& color = get<1>(stop);
	//	cairo_pattern_add_color_stop_rgba(_Brush.get(), offset, color.r(), color.g(), color.b(), color.a());
	//}
	for (const color_stop& stop : csg) {
		cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color.r(), stop.color.g(), stop.color.b(), stop.color.a());
	}
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
}

template <class Allocator>
brush::brush(const circle& start, const circle& end,
	const color_stop_group<Allocator>& csg, error_code& ec) noexcept
	: _Brush()
	, _Image_surface()
	, _Brush_type(brush_type::radial)
	, _Extend(::std::experimental::io2d::tiling::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
	//auto points = f.radial_circles();
	//vector_2d& center0 = get<0>(points);
	//double& radius0 = get<1>(points);
	//vector_2d& center1 = get<2>(points);
	//double& radius1 = get<3>(points);
	try {
		_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(start.center().x(), start.center.y(), start.radius(), end.center.x(), end.center.y(), end.radius()), &cairo_pattern_destroy);
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		_Brush.reset();
		return;
	}
	catch (const ::std::length_error&) {
		_Brush.reset();
		ec = ::std::make_error_code(::std::errc::not_enough_memory);
		return;
	}

	auto status = cairo_pattern_status(_Brush.get());
	if (status != CAIRO_STATUS_SUCCESS) {
		ec = _Cairo_status_t_to_std_error_code(status);
		_Brush.reset();
		return;
	}

	//auto count = f.color_stop_count();
	//for (unsigned int i = 0; i < count; i++) {
	//	auto stop = f.color_stop(i);
	//	double& offset = get<0>(stop);
	//	rgba_color& color = get<1>(stop);
	//	cairo_pattern_add_color_stop_rgba(_Brush.get(), offset, color.r(), color.g(), color.b(), color.a());
	//}
	for (const color_stop& stop : csg) {
		cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color.r(), stop.color.g(), stop.color.b(), stop.color.a());
	}
	status = cairo_pattern_status(_Brush.get());
	if (status != CAIRO_STATUS_SUCCESS) {
		ec = _Cairo_status_t_to_std_error_code(status);
		_Brush.reset();
		return;
	}
	ec.clear();
}

brush::brush(image_surface&& img)
	: _Brush()
	, _Image_surface(make_shared<image_surface>(::std::move(img)))
	, _Brush_type(brush_type::surface)
	, _Extend(::std::experimental::io2d::tiling::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
	if (img.is_finished()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_SURFACE_FINISHED);
	}
	_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_for_surface(_Image_surface.get()->native_handle().csfce), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
}

brush::brush(image_surface&& img, error_code& ec) noexcept
	: _Brush()
	, _Image_surface()
	, _Brush_type(brush_type::surface)
	, _Extend(::std::experimental::io2d::tiling::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
	if (static_cast<bool>(ec)) {
		_Brush.reset();
		return;
	}
	try {
		_Image_surface = make_shared<image_surface>(::std::move(img));
	}
	catch (const bad_alloc&) {
		_Brush.reset();
		ec = ::std::make_error_code(::std::errc::not_enough_memory);
		return;
	}
	catch (const ::std::length_error&) {
		_Brush.reset();
		ec = ::std::make_error_code(::std::errc::not_enough_memory);
		return;
	}

	try {
		_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_for_surface(_Image_surface.get()->native_handle().csfce), &cairo_pattern_destroy);
	}
	catch (const ::std::bad_alloc&) {
		_Brush.reset();
		ec = ::std::make_error_code(::std::errc::not_enough_memory);
		return;
	}
	catch (const ::std::length_error&) {
		_Brush.reset();
		ec = ::std::make_error_code(::std::errc::not_enough_memory);
		return;
	}

	auto status = cairo_pattern_status(_Brush.get());
	if (status != CAIRO_STATUS_SUCCESS) {
		ec = _Cairo_status_t_to_std_error_code(status);
		_Brush.reset();
		return;
	}
	ec.clear();
}

void brush::tiling(::std::experimental::io2d::tiling e) noexcept {
	_Extend = e;
}

void brush::filter(::std::experimental::io2d::filter f) noexcept {
	_Filter = f;
}

void brush::matrix(const matrix_2d& m) noexcept {
	_Matrix = m;
}

::std::experimental::io2d::tiling brush::tiling() const noexcept {
	return _Extend;
}

::std::experimental::io2d::filter brush::filter() const noexcept {
	return _Filter;
}

matrix_2d brush::matrix() const noexcept {
	return _Matrix;
}

brush_type brush::type() const noexcept {
	return _Brush_type;
}
