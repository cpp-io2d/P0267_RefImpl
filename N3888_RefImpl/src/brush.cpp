#include "io2d.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

brush::native_handle_type brush::native_handle() const noexcept {
	return _Brush.get();
}

brush::brush(brush::native_handle_type nh) noexcept
	: _Brush(nh, &cairo_pattern_destroy)
	, _Brush_type(_Cairo_pattern_type_t_to_brush_type(cairo_pattern_get_type(nh))) {
}

brush::brush(const bgra_color& color)
: _Brush()
, _Image_surface()
, _Brush_type(brush_type::solid_color) {
	_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_rgba(color.r(), color.g(), color.b(), color.a()), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
}

//brush::brush(const bgra_color& color, error_code& ec) noexcept
//	: _Brush()
//	, _Image_surface()
//	, _Brush_type(brush_type::solid_color) {
//	try {
//		_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_rgba(color.r(), color.g(), color.b(), color.a()), &cairo_pattern_destroy);
//	}
//	catch (const bad_alloc&) {
//		ec = make_error_code(errc::not_enough_memory);
//		return;
//	}
//	catch (const ::std::length_error&) {
//		_Brush.reset();
//		ec = ::std::make_error_code(::std::errc::not_enough_memory);
//		return;
//	}
//
//	auto status = cairo_pattern_status(_Brush.get());
//	if (status != CAIRO_STATUS_SUCCESS) {
//		ec = _Cairo_status_t_to_std_error_code(status);
//		_Brush.reset();
//		return;
//	}
//	ec.clear();
//}

brush::brush(const vector_2d& begin, const vector_2d& end,
	::std::initializer_list<color_stop> il)
	: _Brush()
	, _Image_surface()
	, _Brush_type(brush_type::linear) {
	_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_linear(begin.x(), begin.y(), end.x(), end.y()), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

	for (const color_stop& stop : il) {
		cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
	}

	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
}

brush::brush(const circle& start, const circle& end,
	::std::initializer_list<color_stop> il)
	: _Brush()
	, _Brush_type(brush_type::radial) {
	_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(start.center().x(), start.center().y(), start.radius(), end.center().x(), end.center().y(), end.radius()), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

	for (const color_stop& stop : il) {
		cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
	}

	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
}

//brush::brush(const circle& start, const circle& end, ::std::error_code& ec,
//	::std::initializer_list<color_stop> il) noexcept
//	: _Brush()
//	, _Brush_type(brush_type::radial) {
//	try {
//		_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(start.center().x(), start.center().y(), start.radius(), end.center().x(), end.center().y(), end.radius()), &cairo_pattern_destroy);
//	}
//	catch (const bad_alloc&) {
//		ec = make_error_code(errc::not_enough_memory);
//		_Brush.reset();
//		return;
//	}
//	catch (const ::std::length_error&) {
//		_Brush.reset();
//		ec = ::std::make_error_code(::std::errc::not_enough_memory);
//		return;
//	}
//
//	auto status = cairo_pattern_status(_Brush.get());
//	if (status != CAIRO_STATUS_SUCCESS) {
//		ec = _Cairo_status_t_to_std_error_code(status);
//		_Brush.reset();
//		return;
//	}
//
//	for (const color_stop& stop : il) {
//		cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
//	}
//
//	status = cairo_pattern_status(_Brush.get());
//	if (status != CAIRO_STATUS_SUCCESS) {
//		ec = _Cairo_status_t_to_std_error_code(status);
//		_Brush.reset();
//		return;
//	}
//	ec.clear();
//}

brush::brush(image_surface&& img)
	: _Brush()
	, _Image_surface(make_shared<image_surface>(::std::move(img)))
	, _Brush_type(brush_type::surface) {
	//if (img.is_finished()) {
	//	_Throw_if_failed_cairo_status_t(CAIRO_STATUS_SURFACE_FINISHED);
	//}
	_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_for_surface(_Image_surface.get()->native_handle().csfce), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
}

//brush::brush(image_surface&& img, error_code& ec) noexcept
//	: _Brush()
//	, _Image_surface()
//	, _Brush_type(brush_type::surface) {
//	if (static_cast<bool>(ec)) {
//		_Brush.reset();
//		return;
//	}
//	try {
//		_Image_surface = make_shared<image_surface>(::std::move(img));
//	}
//	catch (const bad_alloc&) {
//		_Brush.reset();
//		ec = ::std::make_error_code(::std::errc::not_enough_memory);
//		return;
//	}
//	catch (const ::std::length_error&) {
//		_Brush.reset();
//		ec = ::std::make_error_code(::std::errc::not_enough_memory);
//		return;
//	}
//
//	try {
//		_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_for_surface(_Image_surface.get()->native_handle().csfce), &cairo_pattern_destroy);
//	}
//	catch (const ::std::bad_alloc&) {
//		_Brush.reset();
//		ec = ::std::make_error_code(::std::errc::not_enough_memory);
//		return;
//	}
//	catch (const ::std::length_error&) {
//		_Brush.reset();
//		ec = ::std::make_error_code(::std::errc::not_enough_memory);
//		return;
//	}
//
//	auto status = cairo_pattern_status(_Brush.get());
//	if (status != CAIRO_STATUS_SUCCESS) {
//		ec = _Cairo_status_t_to_std_error_code(status);
//		_Brush.reset();
//		return;
//	}
//	ec.clear();
//}
//
brush_type brush::type() const noexcept {
	return _Brush_type;
}
