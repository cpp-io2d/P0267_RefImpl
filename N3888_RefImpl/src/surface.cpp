#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

void surface::_Ensure_state() {
	if (_Surface == nullptr || _Context == nullptr) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
	}
	brush(_Brush);
	antialias(_Antialias);
	dashes(_Dashes);
	fill_rule(_Fill_rule);
	line_cap(_Line_cap);
	line_join(_Line_join);
	line_width(_Line_width);
	miter_limit(_Miter_limit);
	compositing_operator(_Compositing_operator);
	if (_Current_path.get() != nullptr) {
		path(*_Current_path);
	}
	else {
		cairo_new_path(_Context.get());
	}
	matrix(_Transform_matrix);
	if (_Font_face.get() != nullptr) {
		font_face(*_Font_face);
	}
	else {
		cairo_set_font_face(_Context.get(), nullptr); // Restore default font.
	}
	font_matrix(_Font_matrix);
	font_options(_Font_options);
}

void surface::_Ensure_state(error_code& ec) noexcept {
	if (_Surface == nullptr || _Context == nullptr) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NULL_POINTER);
		return;
	}
	brush(_Brush, ec);
	if (static_cast<bool>(ec)) {
		return;
	}
	antialias(_Antialias);
	fill_rule(_Fill_rule);
	line_cap(_Line_cap);
	line_join(_Line_join);
	line_width(_Line_width);
	miter_limit(_Miter_limit);
	compositing_operator(_Compositing_operator);
	if (_Current_path.get() != nullptr) {
		path(*_Current_path, ec);
		if (static_cast<bool>(ec)) {
			return;
		}
	}
	else {
		cairo_new_path(_Context.get());
	}
	matrix(_Transform_matrix);
	if (_Font_face.get() != nullptr) {
		font_face(*_Font_face, ec);
		if (static_cast<bool>(ec)) {
			return;
		}
	}
	else {
		cairo_set_font_face(_Context.get(), nullptr); // Restore default font.
	}
	font_matrix(_Font_matrix);
	font_options(_Font_options);
	dashes(_Dashes, ec);
	if (static_cast<bool>(ec)) {
		return;
	}
	ec.clear();
}

surface::surface(format fmt, int width, int height)
	: _Lock_for_device()
	, _Device()
	, _Surface(unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), &cairo_surface_destroy))
	, _Context(unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy))
	, _Native_font_options(unique_ptr<cairo_font_options_t, decltype(&cairo_font_options_destroy)>(cairo_font_options_create(), &cairo_font_options_destroy))
	, _Dirty_rect()
	, _Format(_Cairo_format_t_to_format(cairo_image_surface_get_format(_Surface.get())))
	, _Content(_Cairo_content_t_to_content(cairo_surface_get_content(_Surface.get())))
	, _Brush(cairo_pattern_create_rgba(0.0, 0.0, 0.0, 0.0))
	, _Antialias(experimental::io2d::antialias::default_antialias)
	, _Fill_rule(::std::experimental::io2d::fill_rule::winding)
	, _Line_cap(::std::experimental::io2d::line_cap::butt)
	, _Line_join(::std::experimental::io2d::line_join::miter)
	, _Line_width(2.0)
	, _Miter_limit(10.0)
	, _Compositing_operator(::std::experimental::io2d::compositing_operator::over)
	, _Current_path()
	, _Immediate_path()
	, _Transform_matrix(matrix_2d::init_identity())
	, _Font_face()
	, _Font_matrix(matrix_2d::init_scale({ 10.0, 10.0 }))
	, _Font_options(::std::experimental::io2d::antialias::default_antialias, ::std::experimental::io2d::subpixel_order::default_subpixel_order)
	, _Saved_state() {
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
	_Throw_if_failed_cairo_status_t(cairo_font_options_status(_Native_font_options.get()));
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.native_handle()));
}

surface::native_handle_type surface::native_handle() const {
	return{ _Surface.get(), _Context.get() };
}

surface::surface(surface&& other) noexcept
	: _Lock_for_device()
	, _Device(move(other._Device))
	, _Surface(move(other._Surface))
	, _Context(move(other._Context))
	, _Native_font_options(move(other._Native_font_options))
	, _Format(_Cairo_format_t_to_format(cairo_image_surface_get_format(_Surface.get())))
	, _Content(_Cairo_content_t_to_content(cairo_surface_get_content(_Surface.get())))
	, _Brush(move(other._Brush))
	, _Antialias(move(other._Antialias))
	, _Fill_rule(move(other._Fill_rule))
	, _Line_cap(move(other._Line_cap))
	, _Line_join(move(other._Line_join))
	, _Line_width(move(other._Line_width))
	, _Miter_limit(move(other._Miter_limit))
	, _Compositing_operator(move(other._Compositing_operator))
	, _Current_path(move(other._Current_path))
	, _Immediate_path(move(other._Immediate_path))
	, _Transform_matrix(move(other._Transform_matrix))
	, _Font_face(move(other._Font_face))
	, _Font_matrix(move(other._Font_matrix))
	, _Font_options(move(other._Font_options))
	, _Saved_state(move(other._Saved_state)) {
}

surface& surface::operator=(surface&& other) noexcept {
	if (this != &other) {
		_Device = move(other._Device);
		_Surface = move(other._Surface);
		_Context = move(other._Context);
		_Native_font_options = move(other._Native_font_options);
		_Format = _Cairo_format_t_to_format(cairo_image_surface_get_format(_Surface.get()));
		_Content = _Cairo_content_t_to_content(cairo_surface_get_content(_Surface.get()));
		_Brush = move(other._Brush);
		_Antialias = move(other._Antialias);
		_Fill_rule = move(other._Fill_rule);
		_Line_cap = move(other._Line_cap);
		_Line_join = move(other._Line_join);
		_Line_width = move(other._Line_width);
		_Miter_limit = move(other._Miter_limit);
		_Compositing_operator = move(other._Compositing_operator);
		_Current_path = move(other._Current_path);
		_Immediate_path = move(other._Immediate_path);
		_Transform_matrix = move(other._Transform_matrix);
		_Font_face = move(other._Font_face);
		_Font_matrix = move(other._Font_matrix);
		_Font_options = move(other._Font_options);
		_Saved_state = move(other._Saved_state);
	}
	return *this;
}

#pragma message ("Needs to be fixed to deal with existing current path and also evaluated to see if each call to it really wanted the existing values or actually wanted surface default state values.")
surface::surface(surface::native_handle_type nh, ::std::experimental::io2d::format fmt, ::std::experimental::io2d::content ctnt)
	: _Lock_for_device()
	, _Device()
	, _Surface(unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(nh.csfce, &cairo_surface_destroy))
	, _Context(unique_ptr<cairo_t, decltype(&cairo_destroy)>(((nh.csfce == nullptr) ? nullptr : cairo_create(nh.csfce)), &cairo_destroy))
	, _Native_font_options(unique_ptr<cairo_font_options_t, decltype(&cairo_font_options_destroy)>(cairo_font_options_create(), &cairo_font_options_destroy))
	, _Format(fmt)
	, _Content(ctnt)
	, _Brush(_Context.get() == nullptr ? cairo_pattern_create_rgba(0.0, 0.0, 0.0, 0.0) : cairo_pattern_reference(cairo_get_source(_Context.get())))
	, _Antialias(_Context.get() == nullptr ? experimental::io2d::antialias::default_antialias : _Cairo_antialias_t_to_antialias(cairo_get_antialias(_Context.get())))
	, _Fill_rule(_Context.get() == nullptr ? ::std::experimental::io2d::fill_rule::winding : _Cairo_fill_rule_t_to_fill_rule(cairo_get_fill_rule(_Context.get())))
	, _Line_cap(_Context.get() == nullptr ? ::std::experimental::io2d::line_cap::butt : _Cairo_line_cap_t_to_line_cap(cairo_get_line_cap(_Context.get())))
	, _Line_join(_Context.get() == nullptr ? ::std::experimental::io2d::line_join::miter : _Cairo_line_join_t_to_line_join(cairo_get_line_join(_Context.get())))
	, _Line_width(_Context.get() == nullptr ? 2.0 : cairo_get_line_width(_Context.get()))
	, _Miter_limit(_Context.get() == nullptr ? 10.0 : cairo_get_miter_limit(_Context.get()))
	, _Compositing_operator(_Context.get() == nullptr ? ::std::experimental::io2d::compositing_operator::over : _Cairo_operator_t_to_compositing_operator(cairo_get_operator(_Context.get())))
	, _Current_path()
	, _Immediate_path()
	, _Transform_matrix()
	, _Font_face()
	, _Font_matrix(matrix_2d::init_scale({ 10.0, 10.0 }))
	, _Font_options(::std::experimental::io2d::antialias::default_antialias, ::std::experimental::io2d::subpixel_order::default_subpixel_order)
	, _Saved_state() {
	if (nh.csfce != nullptr) {
		_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
		_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
	}
	_Throw_if_failed_cairo_status_t(cairo_font_options_status(_Native_font_options.get()));
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.native_handle()));
	if (_Context.get() != nullptr) {
		cairo_set_miter_limit(_Context.get(), _Line_join_miter_miter_limit);
	}
}

surface::surface(surface::native_handle_type nh, ::std::experimental::io2d::format fmt, ::std::experimental::io2d::content ctnt, error_code& ec) noexcept
	: _Lock_for_device()
	, _Device()
	, _Surface(unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(nh.csfce, &cairo_surface_destroy))
	, _Context(unique_ptr<cairo_t, decltype(&cairo_destroy)>(((nh.csfce == nullptr) ? nullptr : cairo_create(nh.csfce)), &cairo_destroy))
	, _Native_font_options(unique_ptr<cairo_font_options_t, decltype(&cairo_font_options_destroy)>(cairo_font_options_create(), &cairo_font_options_destroy))
	, _Format(fmt)
	, _Content(ctnt)
	, _Brush(_Context.get() == nullptr ? cairo_pattern_create_rgba(0.0, 0.0, 0.0, 0.0) : cairo_pattern_reference(cairo_get_source(_Context.get())))
	, _Fill_rule(::std::experimental::io2d::fill_rule::winding)
	, _Line_cap(::std::experimental::io2d::line_cap::butt)
	, _Line_join(::std::experimental::io2d::line_join::miter)
	, _Line_width(2.0)
	, _Miter_limit(10.0)
	, _Compositing_operator(::std::experimental::io2d::compositing_operator::over)
	, _Current_path()
	, _Immediate_path()
	, _Transform_matrix(matrix_2d::init_identity())
	, _Font_face()
	, _Font_matrix(matrix_2d::init_scale({ 10.0, 10.0 }))
	, _Font_options(::std::experimental::io2d::antialias::default_antialias, ::std::experimental::io2d::subpixel_order::default_subpixel_order)
	, _Saved_state() {
	if (nh.csfce != nullptr) {
		if (static_cast<bool>(ec)) {
			_Surface = nullptr;
			_Context = nullptr;
			return;
		}
		ec = _Cairo_status_t_to_std_error_code(cairo_surface_status(_Surface.get()));
		if (static_cast<bool>(ec)) {
			_Surface = nullptr;
			_Context = nullptr;
			return;
		}
		ec = _Cairo_status_t_to_std_error_code(cairo_status(_Context.get()));
		if (static_cast<bool>(ec)) {
			_Surface = nullptr;
			_Context = nullptr;
			return;
		}
	}
	ec = _Cairo_status_t_to_std_error_code(cairo_font_options_status(_Native_font_options.get()));
	if (static_cast<bool>(ec)) {
		_Surface = nullptr;
		_Context = nullptr;
		return;
	}
	ec = _Cairo_status_t_to_std_error_code(cairo_pattern_status(_Brush.native_handle()));
	if (static_cast<bool>(ec)) {
		_Surface = nullptr;
		_Context = nullptr;
		return;
	}
	if (_Context.get() != nullptr) {
		cairo_set_miter_limit(_Context.get(), _Line_join_miter_miter_limit);
	}
	ec.clear();
}

surface::surface(const surface& other, ::std::experimental::io2d::content ctnt, int width, int height)
	: _Lock_for_device()
	, _Device()
	, _Surface(unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_surface_create_similar(other._Surface.get(), _Content_to_cairo_content_t(ctnt), width, height), &cairo_surface_destroy))
	, _Context(unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy))
	, _Native_font_options(unique_ptr<cairo_font_options_t, decltype(&cairo_font_options_destroy)>(cairo_font_options_create(), &cairo_font_options_destroy))
	, _Format(other._Format)
	, _Content(ctnt)
	, _Brush(other._Context.get() == nullptr ? cairo_pattern_create_rgba(0.0, 0.0, 0.0, 0.0) : cairo_pattern_reference(cairo_get_source(other._Context.get())))
	, _Fill_rule(::std::experimental::io2d::fill_rule::winding)
	, _Line_cap(::std::experimental::io2d::line_cap::butt)
	, _Line_join(::std::experimental::io2d::line_join::miter)
	, _Line_width(2.0)
	, _Miter_limit(10.0)
	, _Compositing_operator(::std::experimental::io2d::compositing_operator::over)
	, _Current_path()
	, _Immediate_path()
	, _Transform_matrix(matrix_2d::init_identity())
	, _Font_face()
	, _Font_matrix(matrix_2d::init_scale({ 10.0, 10.0 }))
	, _Font_options(::std::experimental::io2d::antialias::default_antialias, ::std::experimental::io2d::subpixel_order::default_subpixel_order)
	, _Saved_state() {
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
	_Throw_if_failed_cairo_status_t(cairo_font_options_status(_Native_font_options.get()));
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.native_handle()));
}

surface::~surface() {
}

void surface::finish() noexcept {
	cairo_surface_finish(_Surface.get());
}

void surface::flush() {
	cairo_surface_flush(_Surface.get());
}

void surface::flush(::std::error_code & ec) noexcept {
	cairo_surface_flush(_Surface.get());
	ec.clear();
}

shared_ptr<device> surface::device() {
	lock_guard<mutex> lg(_Lock_for_device);
	auto dvc = _Device.lock();
	if (dvc.use_count() != 0) {
		return dvc;
	}
	dvc = shared_ptr<::std::experimental::io2d::device>(new ::std::experimental::io2d::device(cairo_surface_get_device(_Surface.get())));
	_Device = weak_ptr<::std::experimental::io2d::device>(dvc);
	return dvc;
}

shared_ptr<experimental::io2d::device> experimental::io2d::v1::surface::device(error_code & ec) noexcept {
	lock_guard<mutex> lg(_Lock_for_device);
	try {
		auto dvc = _Device.lock();
		if (dvc.use_count() != 0) {
			ec.clear();
			return dvc;
		}
		dvc = shared_ptr<::std::experimental::io2d::device>(new ::std::experimental::io2d::device(cairo_surface_get_device(_Surface.get())));
		_Device = weak_ptr<::std::experimental::io2d::device>(dvc);

		if (dvc.get() == nullptr) {
			_Device.reset();
			ec = ::std::make_error_code(::std::errc::not_enough_memory);
			return nullptr;
		}
		ec.clear();
		return dvc;
	}
	catch (::std::bad_alloc&) {
		_Device.reset();
		ec = ::std::make_error_code(::std::errc::not_enough_memory);
		return nullptr;
	}
}

void surface::mark_dirty() {
	cairo_surface_mark_dirty(_Surface.get());
}

void std::experimental::io2d::v1::surface::mark_dirty(::std::error_code & ec) noexcept {
	cairo_surface_mark_dirty(_Surface.get());
	ec.clear();
}

void surface::mark_dirty(const rectangle& rect) {
	_Dirty_rect = rect;
	cairo_surface_mark_dirty_rectangle(_Surface.get(), _Double_to_int(rect.x()), _Double_to_int(rect.y()), _Double_to_int(rect.width()), _Double_to_int(rect.height()));
}

void std::experimental::io2d::v1::surface::mark_dirty(const rectangle & rect, ::std::error_code & ec) noexcept {
	_Dirty_rect = rect;
	cairo_surface_mark_dirty_rectangle(_Surface.get(), _Double_to_int(rect.x()), _Double_to_int(rect.y()), _Double_to_int(rect.width()), _Double_to_int(rect.height()));
	ec.clear();
}

void surface::map(const ::std::function<void(mapped_surface&)>& action) {
	if (action != nullptr) {
		mapped_surface m({ cairo_surface_map_to_image(_Surface.get(), nullptr), nullptr }, { _Surface.get(), nullptr });
		action(m);
	}
}

void surface::map(const ::std::function<void(mapped_surface&, error_code&)>& action, error_code& ec) {
	if (action != nullptr) {
		mapped_surface m({ cairo_surface_map_to_image(_Surface.get(), nullptr), nullptr }, { _Surface.get(), nullptr }, ec);
		if (static_cast<bool>(ec)) {
			return;
		}
		action(m, ec);
		if (static_cast<bool>(ec)) {
			return;
		}
	}
	ec.clear();
}

void surface::map(const ::std::function<void(mapped_surface&)>& action, const rectangle& extents) {
	if (action != nullptr) {
		cairo_rectangle_int_t cextents{ _Double_to_int(extents.x()), _Double_to_int(extents.y()), _Double_to_int(extents.width()), _Double_to_int(extents.height()) };
		mapped_surface m({ cairo_surface_map_to_image(_Surface.get(), &cextents), nullptr }, { _Surface.get(), nullptr });
		action(m);
	}
}

void surface::map(const ::std::function<void(mapped_surface&, error_code&)>& action, const rectangle& extents, error_code& ec) {
	if (action != nullptr) {
		cairo_rectangle_int_t cextents{ _Double_to_int(extents.x()), _Double_to_int(extents.y()), _Double_to_int(extents.width()), _Double_to_int(extents.height()) };
		mapped_surface m({ cairo_surface_map_to_image(_Surface.get(), &cextents), nullptr }, { _Surface.get(), nullptr }, ec);
		if (static_cast<bool>(ec)) {
			return;
		}
		action(m, ec);
		if (static_cast<bool>(ec)) {
			return;
		}
	}
	ec.clear();
}

void surface::save() {
	cairo_save(_Context.get());
	_Saved_state.push(make_tuple(_Brush, _Antialias, _Dashes, _Fill_rule, _Line_cap, _Line_join, _Line_width, _Miter_limit, _Compositing_operator, _Current_path, _Immediate_path, _Transform_matrix, _Font_face, _Font_matrix, _Font_options));
}

void surface::save(error_code& ec) noexcept {
	cairo_save(_Context.get());
	try {
		_Saved_state.push(make_tuple(_Brush, _Antialias, _Dashes, _Fill_rule, _Line_cap, _Line_join, _Line_width, _Miter_limit, _Compositing_operator, _Current_path, _Immediate_path, _Transform_matrix, _Font_face, _Font_matrix, _Font_options));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
	}
	catch (const length_error&) {
		ec = make_error_code(errc::not_enough_memory);
	}
}

void surface::restore() {
	if (_Saved_state.size() == 0) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_RESTORE);
	}
	cairo_restore(_Context.get());
	{
		auto& t = _Saved_state.top();
		_Brush = get<0>(t);
		_Antialias = get<1>(t);
		_Dashes = move(get<2>(t));
		_Fill_rule = get<3>(t);
		_Line_cap = get<4>(t);
		_Line_join = get<5>(t);
		_Line_width = get<6>(t);
		_Miter_limit = get<7>(t);
		_Compositing_operator = get<8>(t);
		_Current_path = move(get<9>(t));
		_Immediate_path = move(get<10>(t));
		_Transform_matrix = get<11>(t);
		_Font_face = move(get<12>(t));
		_Font_matrix = get<13>(t);
		_Font_options = get<14>(t);
	}
	_Saved_state.pop();

	_Ensure_state();
}

void surface::restore(error_code& ec) noexcept {
	if (_Saved_state.size() == 0) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_RESTORE);
		return;
	}
	cairo_restore(_Context.get());
	{
		auto& t = _Saved_state.top();
		_Brush = get<0>(t);
		_Antialias = get<1>(t);
		_Dashes = move(get<2>(t));
		_Fill_rule = get<3>(t);
		_Line_cap = get<4>(t);
		_Line_join = get<5>(t);
		_Line_width = get<6>(t);
		_Miter_limit = get<7>(t);
		_Compositing_operator = get<8>(t);
		_Current_path = move(get<9>(t));
		_Immediate_path = move(get<10>(t));
		_Transform_matrix = get<11>(t);
		_Font_face = move(get<12>(t));
		_Font_matrix = get<13>(t);
		_Font_options = get<14>(t);
	}
	_Saved_state.pop();

	_Ensure_state(ec);
	if (static_cast<bool>(ec)) {
		return;
	}
	ec.clear();
}

void surface::brush(nullopt_t) noexcept {
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
	_Brush = ::std::experimental::io2d::brush(cairo_pattern_reference(cairo_get_source(_Context.get())));
}

void surface::brush(const ::std::experimental::io2d::brush& source) {
	_Brush = source;
}

void surface::brush(const::std::experimental::io2d::brush & source, ::std::error_code & ec) noexcept {
	// This overload exists for backends where brushes are device-specific and will require resource allocation, etc., when using them on a different device for the first time.
	_Brush = source;
	ec.clear();
}

void surface::antialias(::std::experimental::io2d::antialias a) noexcept {
	_Antialias = a;
	cairo_set_antialias(_Context.get(), _Antialias_to_cairo_antialias_t(a));
}

void surface::dashes(nullopt_t) noexcept {
	_Dashes = ::std::experimental::io2d::dashes(vector<double>(), 0.0);
	cairo_set_dash(_Context.get(), nullptr, 0, 0.0);
}

void surface::dashes(const ::std::experimental::io2d::dashes& d) {
	_Dashes = d;
	cairo_set_dash(_Context.get(), get<0>(d).data(), _Container_size_to_int(get<0>(d)), get<1>(d));
	if (cairo_status(_Context.get()) == CAIRO_STATUS_INVALID_DASH) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_DASH);
	}
}

void surface::dashes(const ::std::experimental::io2d::dashes& d, error_code& ec) noexcept {
	try {
		_Dashes = d;
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	cairo_set_dash(_Context.get(), get<0>(d).data(), _Container_size_to_int(get<0>(d)), get<1>(d));
	if (cairo_status(_Context.get()) == CAIRO_STATUS_INVALID_DASH) {
		ec = make_error_code(io2d_error::invalid_dash);
		return;
	}
	ec.clear();
}

void surface::fill_rule(::std::experimental::io2d::fill_rule fr) noexcept {
	_Fill_rule = fr;
	cairo_set_fill_rule(_Context.get(), _Fill_rule_to_cairo_fill_rule_t(fr));
}

void surface::line_cap(::std::experimental::io2d::line_cap lc) noexcept {
	_Line_cap = lc;
	cairo_set_line_cap(_Context.get(), _Line_cap_to_cairo_line_cap_t(lc));
}

void surface::line_join(::std::experimental::io2d::line_join lj) noexcept {
	_Line_join = lj;
	cairo_set_line_join(_Context.get(), _Line_join_to_cairo_line_join_t(lj));
	if (lj == ::std::experimental::io2d::line_join::miter_or_bevel) {
		cairo_set_miter_limit(_Context.get(), _Miter_limit);
	}
	if (lj == ::std::experimental::io2d::line_join::miter) {
		cairo_set_miter_limit(_Context.get(), _Line_join_miter_miter_limit);
	}
}

void surface::line_width(double width) noexcept {
	_Line_width = max(0.0, width);
	cairo_set_line_width(_Context.get(), _Line_width);
}

void surface::miter_limit(double limit) noexcept {
	_Miter_limit = std::max(limit, 1.0);
	if (_Line_join == ::std::experimental::io2d::line_join::miter_or_bevel) {
		cairo_set_miter_limit(_Context.get(), std::min(std::max(limit, 1.0), _Line_join_miter_miter_limit));
	}
}

void surface::compositing_operator(::std::experimental::io2d::compositing_operator co) noexcept {
	_Compositing_operator = co;
	cairo_set_operator(_Context.get(), _Compositing_operator_to_cairo_operator_t(co));
}

//void surface::clip(experimental::nullopt_t) noexcept {
//	cairo_reset_clip(_Context.get());
//}

void surface::clip(const experimental::io2d::path& p) {
	auto currPath = _Current_path;
	path(p);
	cairo_clip(_Context.get());
	path(currPath);
}

void surface::clip_immediate() {
	auto currPath = _Current_path;
	path(experimental::io2d::path(_Immediate_path));
	cairo_clip(_Context.get());
	path(currPath);
}

void surface::path(nullopt_t) noexcept {
	_Current_path.reset();
	cairo_new_path(_Context.get());
}

void surface::path(const shared_ptr<experimental::io2d::path>& p) {
	if (p.get() != nullptr) {
		path(*p);
	}
	else {
		cairo_new_path(_Context.get());
	}
}

void surface::path(const shared_ptr<experimental::io2d::path>& p, error_code& ec) noexcept {
	if (p.get() != nullptr) {
		path(*p, ec);
		if (static_cast<bool>(ec)) {
			return;
		}
	}
	else {
		cairo_new_path(_Context.get());
	}
	ec.clear();
}

void surface::path(const ::std::experimental::io2d::path& p) {
	_Current_path = make_shared<experimental::io2d::path>(p);
	cairo_new_path(_Context.get());
	cairo_append_path(_Context.get(), _Current_path->native_handle());
}

void surface::path(const experimental::io2d::path& p, error_code& ec) noexcept {
	try {
		_Current_path = make_shared<experimental::io2d::path>(p);
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	cairo_new_path(_Context.get());
	cairo_append_path(_Context.get(), _Current_path->native_handle());
	ec.clear();
}

path_factory& surface::immediate() noexcept {
	return _Immediate_path;
}

void surface::clear() {
	cairo_save(_Context.get());
	cairo_set_operator(_Context.get(), CAIRO_OPERATOR_CLEAR);
	cairo_set_source_rgba(_Context.get(), 1.0, 1.0, 1.0, 1.0);
	cairo_paint(_Context.get());
	cairo_restore(_Context.get());
}

void surface::paint() {
	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.extend()));
	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Brush.native_handle());
	cairo_paint(_Context.get());
}

void surface::paint(const rgba_color& c) {
	solid_color_brush_factory factory(c);
	brush(experimental::io2d::brush(factory));
	paint();
}

void surface::paint(const ::std::experimental::io2d::brush& b) {
	brush(b);
	paint();
}

void surface::paint(const surface& s, const matrix_2d& m, extend e, filter f) {
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_paint(_Context.get());
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
}

void surface::paint(double alpha) {
	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.extend()));
	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Brush.native_handle());
	cairo_paint_with_alpha(_Context.get(), alpha);
}

void surface::paint(const rgba_color& c, double alpha) {
	solid_color_brush_factory factory(c);
	brush(experimental::io2d::brush(factory));
	paint(alpha);
}

void surface::paint(const ::std::experimental::io2d::brush& b, double alpha) {
	brush(b);
	paint(alpha);
}

void surface::paint(const surface& s, double alpha, const matrix_2d& m, extend e, filter f) {
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_paint_with_alpha(_Context.get(), alpha);
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
}

void surface::fill() {
	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.extend()));
	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Brush.native_handle());
	cairo_fill_preserve(_Context.get());
}

void surface::fill(const rgba_color& c) {
	solid_color_brush_factory factory(c);
	brush(experimental::io2d::brush(factory));
	fill();
}

void surface::fill(const ::std::experimental::io2d::brush& b) {
	brush(b);
	fill();
}

void surface::fill(const surface& s, const matrix_2d& m, extend e, filter f) {
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_fill_preserve(_Context.get());
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
}

void surface::fill_immediate() {
	auto currPath = _Current_path;
	path(experimental::io2d::path(_Immediate_path));
	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.extend()));
	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Brush.native_handle());
	cairo_fill(_Context.get());
	path(currPath);
}

void surface::fill_immediate(const rgba_color& c) {
	solid_color_brush_factory factory(c);
	brush(experimental::io2d::brush(factory));
	fill_immediate();
}

void surface::fill_immediate(const ::std::experimental::io2d::brush& b) {
	brush(b);
	fill_immediate();
}

void surface::fill_immediate(const surface& s, const matrix_2d& m, extend e, filter f) {
	auto currPath = _Current_path;
	path(experimental::io2d::path(_Immediate_path));
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_fill(_Context.get());
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
	path(currPath);
}

void surface::stroke() {
	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.extend()));
	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Brush.native_handle());
	cairo_stroke_preserve(_Context.get());
}

void surface::stroke(const rgba_color& c) {
	solid_color_brush_factory factory(c);
	brush(experimental::io2d::brush(factory));
	stroke();
}

void surface::stroke(const ::std::experimental::io2d::brush& b) {
	brush(b);
	stroke();
}

void surface::stroke(const surface& s, const matrix_2d& m, extend e, filter f) {
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_stroke_preserve(_Context.get());
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
}

void surface::stroke_immediate() {
	auto currPath = _Current_path;
	path(experimental::io2d::path(_Immediate_path));
	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.extend()));
	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Brush.native_handle());
	cairo_stroke(_Context.get());
	path(currPath);
}

void surface::stroke_immediate(const rgba_color& c) {
	solid_color_brush_factory factory(c);
	brush(experimental::io2d::brush(factory));
	stroke_immediate();
}

void surface::stroke_immediate(const ::std::experimental::io2d::brush& b) {
	brush(b);
	stroke_immediate();
}

void surface::stroke_immediate(const surface& s, const matrix_2d& m, extend e, filter f) {
	auto currPath = _Current_path;
	path(experimental::io2d::path(_Immediate_path));
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_stroke(_Context.get());
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
	path(currPath);
}

void surface::mask(const ::std::experimental::io2d::brush& maskBrush) {
	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.extend()));
	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Brush.native_handle());
	cairo_mask(_Context.get(), maskBrush.native_handle());
}

void surface::mask(const ::std::experimental::io2d::brush& maskBrush, const rgba_color& c) {
	solid_color_brush_factory factory(c);
	brush(experimental::io2d::brush(factory));
	mask(maskBrush);
}

void surface::mask(const ::std::experimental::io2d::brush& maskBrush, const ::std::experimental::io2d::brush& b) {
	brush(b);
	mask(maskBrush);
}

void surface::mask(const ::std::experimental::io2d::brush& maskBrush, const surface& s, const matrix_2d& m, extend e, filter f) {
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_mask(_Context.get(), maskBrush.native_handle());
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
}

void surface::mask(surface& maskSurface, const matrix_2d& maskMatrix, extend maskExtend, filter maskFilter) {
	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.extend()));
	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Brush.native_handle());

	surface_brush_factory sbf(maskSurface);
	experimental::io2d::brush maskBrush(sbf);
	maskBrush.matrix(maskMatrix);
	maskBrush.extend(maskExtend);
	maskBrush.filter(maskFilter);

	mask(maskBrush);
}

void surface::mask(surface& maskSurface, const rgba_color& c, const matrix_2d& maskMatrix, extend maskExtend, filter maskFilter) {
	surface_brush_factory sbf(maskSurface);
	experimental::io2d::brush maskBrush(sbf);
	maskBrush.matrix(maskMatrix);
	maskBrush.extend(maskExtend);
	maskBrush.filter(maskFilter);

	mask(maskBrush);
	mask(maskBrush, c);
}

void surface::mask(surface& maskSurface, const ::std::experimental::io2d::brush& b, const matrix_2d& maskMatrix, extend maskExtend, filter maskFilter) {
	surface_brush_factory sbf(maskSurface);
	experimental::io2d::brush maskBrush(sbf);
	maskBrush.matrix(maskMatrix);
	maskBrush.extend(maskExtend);
	maskBrush.filter(maskFilter);

	mask(maskBrush, b);
}

void surface::mask(surface& maskSurface, const surface& s, const matrix_2d& maskMatrix, const matrix_2d& m, extend maskExtend, extend e, filter maskFilter, filter f) {
	//cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	//auto pat = cairo_get_source(_Context.get());
	//cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	//cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	//cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	//cairo_pattern_set_matrix(pat, &cmat);
	//cairo_mask_surface(_Context.get(), maskSurface.native_handle().csfce, 0.0, 0.0);
	//cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
	surface_brush_factory sbf(maskSurface);
	experimental::io2d::brush maskBrush(sbf);
	maskBrush.matrix(maskMatrix);
	maskBrush.extend(maskExtend);
	maskBrush.filter(maskFilter);

	mask(maskBrush, s, m, e, f);
}

void surface::mask_immediate(const ::std::experimental::io2d::brush& maskBrush) {
	auto currPath = _Current_path;
	path(experimental::io2d::path(_Immediate_path));
	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.extend()));
	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);

	cairo_pattern_set_extend(maskBrush.native_handle(), _Extend_to_cairo_extend_t(maskBrush.extend()));
	cairo_pattern_set_filter(maskBrush.native_handle(), _Filter_to_cairo_filter_t(maskBrush.filter()));
	cairo_matrix_init(&cPttnMatrix, maskBrush.matrix().m00(), maskBrush.matrix().m01(), maskBrush.matrix().m10(), maskBrush.matrix().m11(), maskBrush.matrix().m20(), maskBrush.matrix().m21());
	cairo_pattern_set_matrix(maskBrush.native_handle(), &cPttnMatrix);

	cairo_set_source(_Context.get(), _Brush.native_handle());
	cairo_mask(_Context.get(), maskBrush.native_handle());
	path(currPath);
}

void surface::mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const rgba_color& c) {
	solid_color_brush_factory factory(c);
	brush(experimental::io2d::brush(factory));
	mask_immediate(maskBrush);
}

void surface::mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const ::std::experimental::io2d::brush& b) {
	brush(b);
	mask_immediate(maskBrush);
}

void surface::mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const surface& s, const matrix_2d& m, extend e, filter f) {
	auto currPath = _Current_path;
	path(experimental::io2d::path(_Immediate_path));
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);

	cairo_pattern_set_extend(maskBrush.native_handle(), _Extend_to_cairo_extend_t(maskBrush.extend()));
	cairo_pattern_set_filter(maskBrush.native_handle(), _Filter_to_cairo_filter_t(maskBrush.filter()));
	cairo_matrix_init(&cmat, maskBrush.matrix().m00(), maskBrush.matrix().m01(), maskBrush.matrix().m10(), maskBrush.matrix().m11(), maskBrush.matrix().m20(), maskBrush.matrix().m21());
	cairo_pattern_set_matrix(maskBrush.native_handle(), &cmat);

	cairo_mask(_Context.get(), maskBrush.native_handle());
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
	path(currPath);
}

void surface::mask_immediate(surface& maskSurface, const matrix_2d& maskMatrix, extend maskExtend, filter maskFilter) {
	//auto currPath = _Current_path;
	//path(experimental::io2d::path(_Immediate_path));
	//cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.extend()));
	//cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
	//cairo_matrix_t cPttnMatrix;
	//cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
	//cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
	//cairo_set_source(_Context.get(), _Brush.native_handle());
	//cairo_mask_surface(_Context.get(), maskSurface.native_handle().csfce, 0.0, 0.0);
	//path(currPath);
	surface_brush_factory sbf(maskSurface);
	experimental::io2d::brush maskBrush(sbf);
	maskBrush.matrix(maskMatrix);
	maskBrush.extend(maskExtend);
	maskBrush.filter(maskFilter);

	mask_immediate(maskBrush);
}

void surface::mask_immediate(surface& maskSurface, const rgba_color& c, const matrix_2d& maskMatrix, extend maskExtend, filter maskFilter) {
	surface_brush_factory sbf(maskSurface);
	experimental::io2d::brush maskBrush(sbf);
	maskBrush.matrix(maskMatrix);
	maskBrush.extend(maskExtend);
	maskBrush.filter(maskFilter);

	mask_immediate(maskBrush, c);
}

void surface::mask_immediate(surface& maskSurface, const ::std::experimental::io2d::brush& b, const matrix_2d& maskMatrix, extend maskExtend, filter maskFilter) {
	surface_brush_factory sbf(maskSurface);
	experimental::io2d::brush maskBrush(sbf);
	maskBrush.matrix(maskMatrix);
	maskBrush.extend(maskExtend);
	maskBrush.filter(maskFilter);

	mask_immediate(maskBrush, b);
}

void surface::mask_immediate(surface& maskSurface, const surface& s, const matrix_2d& maskMatrix, const matrix_2d& m, extend maskExtend, extend e, filter maskFilter, filter f) {
	//auto currPath = _Current_path;
	//path(experimental::io2d::path(_Immediate_path));
	//cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	//auto pat = cairo_get_source(_Context.get());
	//cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	//cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	//cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	//cairo_pattern_set_matrix(pat, &cmat);
	//cairo_mask_surface(_Context.get(), maskSurface.native_handle().csfce, 0.0, 0.0);
	//cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
	surface_brush_factory sbf(maskSurface);
	experimental::io2d::brush maskBrush(sbf);
	maskBrush.matrix(maskMatrix);
	maskBrush.extend(maskExtend);
	maskBrush.filter(maskFilter);

	mask_immediate(maskBrush, s, m, e, f);
}

vector_2d surface::render_text(const string& utf8, const vector_2d& position) {
	cairo_new_path(_Context.get());
	cairo_move_to(_Context.get(), position.x(), position.y());
	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.extend()));
	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Brush.native_handle());
	cairo_show_text(_Context.get(), utf8.c_str());
	double x, y;
	cairo_get_current_point(_Context.get(), &x, &y);
	path(_Current_path);
	return vector_2d{ x, y };
}

vector_2d surface::render_text(const string& utf8, const vector_2d& position, const rgba_color& c) {
	solid_color_brush_factory factory(c);
	brush(experimental::io2d::brush(factory));
	return render_text(utf8, position);
}

vector_2d surface::render_text(const string& utf8, const vector_2d& position, const ::std::experimental::io2d::brush& b) {
	brush(b);
	return render_text(utf8, position);
}

vector_2d surface::render_text(const string& utf8, const vector_2d& position, const surface& s, const matrix_2d& m, extend e, filter f) {
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	auto result = render_text(utf8, position);
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
	return result;
}

void surface::matrix(const matrix_2d& m) {
	auto det = m.determinant();
	if (det == 0.0) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MATRIX);
	}
	_Transform_matrix = m;
	cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_set_matrix(_Context.get(), &cm);
}

void surface::matrix(const matrix_2d& m, error_code& ec) noexcept {
	auto det = m.determinant(ec);
	if (static_cast<bool>(ec)) {
		return;
	}
	if (det == 0.0) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MATRIX);
		return;
	}
	_Transform_matrix = m;
	cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_set_matrix(_Context.get(), &cm);
	ec.clear();
}

void surface::font_face(const string& family, font_slant slant, font_weight weight) {
	cairo_select_font_face(_Context.get(), family.c_str(), _Font_slant_to_cairo_font_slant_t(slant), _Font_weight_to_cairo_font_weight_t(weight));
}

void surface::font_size(double size) {
	if (size <= 0.0) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_SIZE);
	}
	cairo_set_font_size(_Context.get(), size);
}

void surface::font_size(double size, error_code& ec) noexcept {
	if (size <= 0.0) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_SIZE);
		return;
	}
	cairo_set_font_size(_Context.get(), size);
	ec.clear();
}

void surface::font_matrix(const matrix_2d& m) {
	auto det = m.determinant();
	if (det == 0.0) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MATRIX);
	}
	cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_set_font_matrix(_Context.get(), &cm);
}

void surface::font_matrix(const matrix_2d& m, error_code& ec) noexcept {
	auto det = m.determinant(ec);
	if (static_cast<bool>(ec)) {
		return;
	}
	if (det == 0.0) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MATRIX);
		return;
	}
	cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_set_font_matrix(_Context.get(), &cm);
	ec.clear();
}

void surface::font_options(const ::std::experimental::io2d::font_options& options) noexcept {
	cairo_font_options_set_antialias(_Native_font_options.get(), _Antialias_to_cairo_antialias_t(options.antialias()));
	cairo_font_options_set_subpixel_order(_Native_font_options.get(), _Subpixel_order_to_cairo_subpixel_order_t(options.subpixel_order()));
	cairo_set_font_options(_Context.get(), _Native_font_options.get());
}

void surface::font_face(const ::std::experimental::io2d::font_face& font_face) {
	_Font_face = make_shared<experimental::io2d::font_face>(font_face);
	cairo_set_font_face(_Context.get(), font_face.native_handle());
}

void surface::font_face(const::std::experimental::io2d::font_face & f, ::std::error_code & ec) noexcept {
	try {
		_Font_face = make_shared<experimental::io2d::font_face>(f);
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	cairo_set_font_face(_Context.get(), f.native_handle());
	ec.clear();
}

brush surface::brush() const noexcept {
	return _Brush;
}

bool surface::is_finished() const noexcept {
	assert(_Surface != nullptr);
	return cairo_surface_status(_Surface.get()) == CAIRO_STATUS_SURFACE_FINISHED;
}

content surface::content() const noexcept {
	return _Cairo_content_t_to_content(cairo_surface_get_content(_Surface.get()));
}

bool surface::_Has_surface_resource() const noexcept {
	return _Surface != nullptr;
}

antialias surface::antialias() const noexcept {
	return _Antialias;
}

::std::experimental::io2d::dashes surface::dashes() const {
	::std::experimental::io2d::dashes result{};
	auto& d = get<0>(result);
	auto& o = get<1>(result);
	d.resize(static_cast<vector<double>::size_type>(cairo_get_dash_count(_Context.get())));
	cairo_get_dash(_Context.get(), d.data(), &o);
	return result;
}

experimental::io2d::dashes surface::dashes(error_code& ec) const noexcept {
	::std::experimental::io2d::dashes result{};
	auto& d = get<0>(result);
	auto& o = get<1>(result);
	try {
		d.resize(static_cast<vector<double>::size_type>(cairo_get_dash_count(_Context.get())));
	}
	catch (const ::std::length_error&) {
		ec = ::std::make_error_code(::std::errc::not_enough_memory);
		return result;
	}
	catch (const ::std::bad_alloc&) {
		ec = ::std::make_error_code(::std::errc::not_enough_memory);
		return result;
	}
	cairo_get_dash(_Context.get(), d.data(), &o);
	ec.clear();
	return result;
}

fill_rule surface::fill_rule() const noexcept {
	return _Cairo_fill_rule_t_to_fill_rule(cairo_get_fill_rule(_Context.get()));
}

line_cap surface::line_cap() const noexcept {
	return _Cairo_line_cap_t_to_line_cap(cairo_get_line_cap(_Context.get()));
}

line_join surface::line_join() const noexcept {
	return _Line_join;
}

double surface::line_width() const noexcept {
	return cairo_get_line_width(_Context.get());
}

double surface::miter_limit() const noexcept {
	return _Miter_limit;
}

compositing_operator surface::compositing_operator() const noexcept {
	return _Cairo_operator_t_to_compositing_operator(cairo_get_operator(_Context.get()));
}

rectangle surface::clip_extents() const noexcept {
	double pt0x, pt0y, pt1x, pt1y;
	cairo_clip_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
	return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
}

bool surface::in_clip(const vector_2d& pt) const noexcept {
	return cairo_in_clip(_Context.get(), pt.x(), pt.y()) != 0;
}

vector<rectangle> surface::clip_rectangles() const {
	vector<rectangle> results;
	unique_ptr<cairo_rectangle_list_t, function<void(cairo_rectangle_list_t*)>> sp_rects(cairo_copy_clip_rectangle_list(_Context.get()), &cairo_rectangle_list_destroy);
	_Throw_if_failed_cairo_status_t(sp_rects->status);
	for (auto i = 0; i < sp_rects->num_rectangles; ++i) {
		results.push_back({ sp_rects->rectangles[i].x, sp_rects->rectangles[i].y, sp_rects->rectangles[i].width, sp_rects->rectangles[i].height });
	}

	return results;
}

rectangle surface::fill_extents() const noexcept {
	double pt0x, pt0y, pt1x, pt1y;
	cairo_fill_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
	return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
}

rectangle surface::fill_extents_immediate() const noexcept {
	// fill_extents doesn't care whether something is ACTUALLY inked; just whether or not the current fill_rule combined with the path means the area could be filled (even if the brush won't actually change it).
	throw runtime_error("Not implemented.");
	//double pt0x, pt0y, pt1x, pt1y;
	//cairo_fill_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
	//return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
}

bool surface::in_fill(const vector_2d& pt) const noexcept {
	return cairo_in_fill(_Context.get(), pt.x(), pt.y()) != 0;
}

bool surface::in_fill_immediate(const vector_2d& pt) const noexcept {
	throw runtime_error("Not implemented.");
	//return cairo_in_fill(_Context.get(), pt.x(), pt.y()) != 0;
}

rectangle surface::stroke_extents() const noexcept {
	double pt0x, pt0y, pt1x, pt1y;
	cairo_stroke_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
	return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
}

rectangle surface::stroke_extents_immediate() const noexcept {
	throw runtime_error("Not implemented.");
	//auto currPath = _Current_path;
	//path(path(_Immediate_path));
	//double pt0x, pt0y, pt1x, pt1y;
	//cairo_stroke_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
	//path(currPath);
	//return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
}

bool surface::in_stroke(const vector_2d& pt) const noexcept {
	return cairo_in_stroke(_Context.get(), pt.x(), pt.y()) != 0;
}

bool surface::in_stroke_immediate(const vector_2d& pt) const noexcept {
	throw runtime_error("Not implemented.");
}

::std::experimental::io2d::font_extents surface::font_extents() const noexcept {
	::std::experimental::io2d::font_extents result;
	cairo_font_extents_t cfe{};
	cairo_font_extents(_Context.get(), &cfe);
	result.ascent(cfe.ascent);
	result.descent(cfe.descent);
	result.height(cfe.height);
	return result;
}

::std::experimental::io2d::text_extents surface::text_extents(const string& utf8) const {
	::std::experimental::io2d::text_extents result;
	if (utf8.size() == 0) {
		return result;
	}

	cairo_text_extents_t cte{};
	cairo_text_extents(_Context.get(), utf8.c_str(), &cte);

	cairo_text_extents_t spaceExtents{};
	cairo_text_extents(_Context.get(), " ", &spaceExtents);

	char str[2] = { '\0', '\0' };
	vector<cairo_text_extents_t> extentsVec;
	for (const auto& iter : utf8) {
		extentsVec.emplace_back(cairo_text_extents_t{});
		str[0] = iter;
		cairo_text_extents(_Context.get(), str, &extentsVec.back());
	}

	auto beginSpaceCount = 0U;
	for (auto iter = utf8.cbegin(); iter != utf8.cend(); iter++) {
		if (*iter == ' ') {
			beginSpaceCount++;
		}
		else {
			break;
		}
	}
	auto endSpaceCount = 0U;
	for (auto iter = utf8.crbegin(); iter != utf8.crend(); iter++) {
		if (*iter == ' ') {
			endSpaceCount++;
		}
		else {
			break;
		}
	}

	if (extentsVec.size() == 1) {
		const auto& item = extentsVec[0];
		result.x_advance(item.x_advance);
		result.y_advance(item.y_advance);
		if (utf8[0] == ' ') {
			// Everything else is already zeroes so we're done.
			return result;
		}
		else {
			result.x_bearing(item.x_bearing);
			result.y_bearing(item.y_bearing);
			result.width(item.width);
			result.height(item.height);

			return result;
		}
	}

	const auto evSize = extentsVec.size();
	const auto extentsVecNoSpaceSize = extentsVec.size() - (beginSpaceCount + endSpaceCount);

	if (extentsVecNoSpaceSize == 0) {
		result.x_advance(spaceExtents.x_advance * evSize);
		result.y_advance(spaceExtents.y_advance * evSize);

		// Everything else is already zeroes so we're done.
		return result;
	}
	if (extentsVecNoSpaceSize == 1) {
		const auto& item = extentsVec[beginSpaceCount];
		result.x_advance(spaceExtents.x_advance * (evSize - 1) + item.x_advance);
		result.y_advance(spaceExtents.y_advance * (evSize - 1) + item.y_advance);
		result.width(item.width);
		result.height(item.height);
		result.x_bearing(item.x_bearing + beginSpaceCount * spaceExtents.x_advance);
		result.y_bearing(item.y_bearing + beginSpaceCount * spaceExtents.y_advance);

		return result;
	}

	assert(extentsVecNoSpaceSize >= 2);


	for (auto i = beginSpaceCount; i < extentsVecNoSpaceSize + beginSpaceCount; ++i) {
		const auto& item = extentsVec[i];
		if (i == beginSpaceCount) {
			result.x_bearing(spaceExtents.x_advance * beginSpaceCount + item.x_bearing);
			result.y_bearing(spaceExtents.y_advance * beginSpaceCount + item.y_bearing);
			result.x_advance(spaceExtents.x_advance * beginSpaceCount + item.x_advance);
			result.y_advance(spaceExtents.y_advance * beginSpaceCount + item.y_advance);
			result.width(item.x_advance == 0.0 ? item.width : item.x_advance - item.x_bearing);
			result.height(item.y_advance == 0.0 ? item.height : item.y_advance - item.y_bearing);
		}
		else {
			if (i + 1U == extentsVecNoSpaceSize + beginSpaceCount) {
				// Handle LTR and RTL scripts.
				result.x_bearing(min(result.x_bearing(), result.x_advance() + item.x_bearing));
				result.y_bearing(min(result.y_bearing(), result.y_advance() + item.y_bearing));
				result.x_advance(result.x_advance() + spaceExtents.x_advance * endSpaceCount + item.x_advance);
				result.y_advance(result.y_advance() + spaceExtents.y_advance * endSpaceCount + item.y_advance);
				if (item.x_advance != 0.0) {
					if (item.x_advance < 0.0) {
						// If RTL then x_bearing is the max extent of the item.
						result.width(abs(result.width() + item.x_bearing));
					}
					else {
						// Otherwise the max extent should be x_bearing + width
						result.width(result.width() + item.x_bearing + item.width);
					}
					result.height(max(result.height(), item.height));
				}
				else {
					if (item.y_advance < 0.0) {
						// I don't know of any bottom to top scripts but we might as well provide for them.
						result.height(abs(result.height() + item.y_bearing));
					}
					else {
						// I believe that this works even if y_bearing is negative since we're advancing baseline to baseline except for first and last items.
						result.height(result.height() + item.y_bearing + item.height);
					}
					result.width(max(result.width(), item.width));
				}
			}
			else {
				result.x_advance(result.x_advance() + item.x_advance);
				result.y_advance(result.y_advance() + item.y_advance);
				if (item.x_advance != 0.0) {
					// If this is a horizontal script, the correct y_bearing is the min of all char/glyph extents from the string.
					result.y_bearing(min(result.y_bearing(), result.y_advance() + item.y_bearing));
					result.width(result.width() + item.x_advance);
					result.height(max(result.height(), item.height));
				}
				else {
					// If this is a vertical script, the correct x_bearing is the min of all char/glyph extents from the string.
					result.x_bearing(min(result.x_bearing(), result.x_advance() + item.x_bearing));
					result.width(max(result.width(), item.width));
					result.height(result.height() + item.y_advance);
				}
			}
		}
	}

	return result;
}

matrix_2d surface::matrix() const noexcept {
	return _Transform_matrix;
}

vector_2d surface::user_to_surface(const vector_2d& pt) const noexcept {
	return _Transform_matrix.transform_point(pt);
}

vector_2d surface::user_to_surface_distance(const vector_2d& dpt) const noexcept {
	return _Transform_matrix.transform_distance(dpt);
}

vector_2d surface::surface_to_user(const vector_2d& pt) const {
	auto im = _Transform_matrix;
	im.invert();
	return im.transform_point(pt);
}

vector_2d surface::surface_to_user_distance(const vector_2d& dpt) const {
	auto im = _Transform_matrix;
	im.invert();
	return im.transform_distance(dpt);
}

matrix_2d surface::font_matrix() const noexcept {
	cairo_matrix_t cm{};
	cairo_get_font_matrix(_Context.get(), &cm);
	return{ cm.xx, cm.yx, cm.xy, cm.yy, cm.x0, cm.y0 };
}

// Note: This deviates from cairo in that we return the values that will actually wind up being used.
::std::experimental::io2d::font_options surface::font_options() const noexcept {
	::std::experimental::io2d::font_options fo(::std::experimental::io2d::antialias::default_antialias, ::std::experimental::io2d::subpixel_order::default_subpixel_order);
	unique_ptr<cairo_font_options_t, decltype(&cairo_font_options_destroy)> up(nullptr, &cairo_font_options_destroy);
	cairo_get_font_options(_Context.get(), up.get());
	_Throw_if_failed_cairo_status_t(cairo_font_options_status(up.get()));
	auto ca = _Cairo_antialias_t_to_antialias(cairo_font_options_get_antialias(up.get()));
	auto cso = _Cairo_subpixel_order_t_to_subpixel_order(cairo_font_options_get_subpixel_order(up.get()));
	cairo_get_font_options(_Context.get(), up.get());
	_Throw_if_failed_cairo_status_t(cairo_font_options_status(up.get()));

	return ::std::experimental::io2d::font_options(
		(ca == ::std::experimental::io2d::antialias::default_antialias) ? _Cairo_antialias_t_to_antialias(cairo_font_options_get_antialias(up.get())) : ca,
		(cso == ::std::experimental::io2d::subpixel_order::default_subpixel_order) ? _Cairo_subpixel_order_t_to_subpixel_order(cairo_font_options_get_subpixel_order(up.get())) : cso
		);
}

::std::experimental::io2d::font_face surface::font_face() const {
	auto ff = cairo_get_font_face(_Context.get());
	_Throw_if_failed_cairo_status_t(cairo_font_face_status(ff));
	// Cairo doesn't increase the font face's reference count when you call cairo_get_font_face so we do it manually.
	return ::std::experimental::io2d::font_face(cairo_font_face_reference(ff));
}
