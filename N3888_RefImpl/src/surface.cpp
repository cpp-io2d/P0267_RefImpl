#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

//namespace {
//	const vector_2d _Font_default_size{ 16.0, 16.0 };
//}
//
surface::surface(format fmt, int width, int height)
	: _Device()
	, _Surface(unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), &cairo_surface_destroy))
	, _Context(unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy))
	, _Dirty_rect()
	, _Format(_Cairo_format_t_to_format(cairo_image_surface_get_format(_Surface.get()))) {
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
}

surface::native_handle_type surface::native_handle() const {
	return{ _Surface.get(), _Context.get() };
}

surface::surface(surface::native_handle_type nh, ::std::experimental::io2d::format fmt)
	: _Device()
	, _Surface(unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(nh.csfce, &cairo_surface_destroy))
	, _Context(unique_ptr<cairo_t, decltype(&cairo_destroy)>(((nh.csfce == nullptr) ? nullptr : cairo_create(nh.csfce)), &cairo_destroy))
	, _Dirty_rect()
	, _Format(fmt) {
	if (nh.csfce != nullptr) {
		_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
		_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
	}
}

//surface::surface(const surface& other, int width, int height)
//	: _Device()
//	, _Surface(unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_surface_create_similar(other._Surface.get(), cairo_surface_get_content(other._Surface.get()), width, height), &cairo_surface_destroy))
//	, _Context(unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy))
//	, _Dirty_rect()
//	, _Format(_Cairo_format_t_to_format(cairo_image_surface_get_format(_Surface.get()))) {
//	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
//	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
//}
//
void surface::flush() {
	cairo_surface_flush(_Surface.get());
}

void surface::flush(::std::error_code & ec) noexcept {
	cairo_surface_flush(_Surface.get());
	ec.clear();
}

shared_ptr<device> surface::device() {
	auto dvc = _Device.lock();
	if (dvc.use_count() != 0) {
		return dvc;
	}
	dvc = shared_ptr<::std::experimental::io2d::device>(new ::std::experimental::io2d::device(cairo_surface_get_device(_Surface.get())));
	_Device = weak_ptr<::std::experimental::io2d::device>(dvc);
	return dvc;
}

void surface::mark_dirty() {
	cairo_surface_mark_dirty(_Surface.get());
}

void surface::mark_dirty(const rectangle& rect) {
	_Dirty_rect = rect;
	cairo_surface_mark_dirty_rectangle(_Surface.get(), _Double_to_int(rect.x()), _Double_to_int(rect.y()), _Double_to_int(rect.width()), _Double_to_int(rect.height()));
}

void surface::map(const ::std::function<void(mapped_surface&)>& action) {
	if (action != nullptr) {
		mapped_surface m({ cairo_surface_map_to_image(_Surface.get(), nullptr), nullptr }, { _Surface.get(), nullptr });
		action(m);
		mark_dirty();
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
		mark_dirty();
	}
	ec.clear();
}

void surface::map(const ::std::function<void(mapped_surface&)>& action, const rectangle& extents) {
	if (action != nullptr) {
		cairo_rectangle_int_t cextents{ _Double_to_int(extents.x()), _Double_to_int(extents.y()), _Double_to_int(extents.width()), _Double_to_int(extents.height()) };
		mapped_surface m({ cairo_surface_map_to_image(_Surface.get(), &cextents), nullptr }, { _Surface.get(), nullptr });
		action(m);
	}
	mark_dirty(extents);
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
		mark_dirty(extents);
	}
	ec.clear();
}

//void surface::brush(nullvalue_t) noexcept {
//	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
//	_Brush = ::std::experimental::io2d::brush(cairo_pattern_reference(cairo_get_source(_Context.get())));
//}
//
//void surface::brush(const ::std::experimental::io2d::brush& source) {
//	_Brush = source;
//}
//
//void surface::brush(const::std::experimental::io2d::brush & source, ::std::error_code & ec) noexcept {
//	// This overload exists for backends where brushes are device-specific and will require resource allocation, etc., when using them on a different device for the first time.
//	_Brush = source;
//	ec.clear();
//}
//
//void surface::antialias(::std::experimental::io2d::antialias a) noexcept {
//	_Antialias = a;
//	cairo_set_antialias(_Context.get(), _Antialias_to_cairo_antialias_t(a));
//}
//
////void surface::dashes(nullvalue_t) noexcept {
////	_Dashes = ::std::experimental::io2d::dashes(vector<double>(), 0.0);
////	cairo_set_dash(_Context.get(), nullptr, 0, 0.0);
////}
////
//void surface::dashes(const ::std::experimental::io2d::dashes& d) {
//	_Dashes = d;
//	cairo_set_dash(_Context.get(), get<0>(d).data(), _Container_size_to_int(get<0>(d)), get<1>(d));
//	if (cairo_status(_Context.get()) == CAIRO_STATUS_INVALID_DASH) {
//		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_DASH);
//	}
//}
//
//void surface::dashes(const ::std::experimental::io2d::dashes& d, error_code& ec) noexcept {
//	try {
//		_Dashes = d;
//	}
//	catch (const bad_alloc&) {
//		ec = make_error_code(errc::not_enough_memory);
//		return;
//	}
//	cairo_set_dash(_Context.get(), get<0>(d).data(), _Container_size_to_int(get<0>(d)), get<1>(d));
//	if (cairo_status(_Context.get()) == CAIRO_STATUS_INVALID_DASH) {
//		ec = make_error_code(io2d_error::invalid_dash);
//		return;
//	}
//	ec.clear();
//}
//
//void surface::fill_rule(::std::experimental::io2d::fill_rule fr) noexcept {
//	_Fill_rule = fr;
//	cairo_set_fill_rule(_Context.get(), _Fill_rule_to_cairo_fill_rule_t(fr));
//}
//
//void surface::line_cap(::std::experimental::io2d::line_cap lc) noexcept {
//	_Line_cap = lc;
//	cairo_set_line_cap(_Context.get(), _Line_cap_to_cairo_line_cap_t(lc));
//}
//
//void surface::line_join(::std::experimental::io2d::line_join lj) noexcept {
//	_Line_join = lj;
//	cairo_set_line_join(_Context.get(), _Line_join_to_cairo_line_join_t(lj));
//	if (lj == ::std::experimental::io2d::line_join::miter_or_bevel) {
//		cairo_set_miter_limit(_Context.get(), _Miter_limit);
//	}
//	if (lj == ::std::experimental::io2d::line_join::miter) {
//		cairo_set_miter_limit(_Context.get(), _Line_join_miter_miter_limit);
//	}
//}
//
//void surface::line_width(double width) noexcept {
//	_Line_width = max(0.0, width);
//	cairo_set_line_width(_Context.get(), _Line_width);
//}
//
//void surface::miter_limit(double limit) noexcept {
//	_Miter_limit = std::max(limit, 1.0);
//	if (_Line_join == ::std::experimental::io2d::line_join::miter_or_bevel) {
//		cairo_set_miter_limit(_Context.get(), std::min(std::max(limit, 1.0), _Line_join_miter_miter_limit));
//	}
//}
//
//void surface::compositing_op(::std::experimental::io2d::compositing_op co) noexcept {
//	_Compositing_operator = co;
//	cairo_set_operator(_Context.get(), _Compositing_operator_to_cairo_operator_t(co));
//}
//
////void surface::clip(experimental::nullopt_t) noexcept {
////	cairo_reset_clip(_Context.get());
////}
//
//void surface::clip(const experimental::io2d::path_group& p) {
//	auto currPath = _Current_path;
//	path_group(p);
//	cairo_clip(_Context.get());
//	path_group(currPath);
//}
//
//void surface::clip_immediate() {
//	auto currPath = _Current_path;
//	path_group(experimental::io2d::path_group(_Immediate_path));
//	cairo_clip(_Context.get());
//	path_group(currPath);
//}
//
////void surface::path_group(nullvalue_t) noexcept {
////	_Current_path.reset();
////	cairo_new_path(_Context.get());
////}
////
//void surface::path_group(const shared_ptr<experimental::io2d::path_group>& p) {
//	if (p.get() != nullptr) {
//		path_group(*p);
//	}
//	else {
//		cairo_new_path(_Context.get());
//	}
//}
//
//void surface::path_group(const shared_ptr<experimental::io2d::path_group>& p, error_code& ec) noexcept {
//	if (p.get() != nullptr) {
//		path_group(*p, ec);
//		if (static_cast<bool>(ec)) {
//			return;
//		}
//	}
//	else {
//		cairo_new_path(_Context.get());
//	}
//	ec.clear();
//}
//
//void surface::path_group(const ::std::experimental::io2d::path_group& p) {
//	_Current_path = make_shared<experimental::io2d::path_group>(p);
//	cairo_new_path(_Context.get());
//	cairo_append_path(_Context.get(), _Current_path->native_handle());
//}
//
//void surface::path_group(const experimental::io2d::path_group& p, error_code& ec) noexcept {
//	try {
//		_Current_path = make_shared<experimental::io2d::path_group>(p);
//	}
//	catch (const bad_alloc&) {
//		ec = make_error_code(errc::not_enough_memory);
//		return;
//	}
//	cairo_new_path(_Context.get());
//	cairo_append_path(_Context.get(), _Current_path->native_handle());
//	ec.clear();
//}
//
//path_builder<>& surface::immediate() noexcept {
//	return _Immediate_path;
//}
//
void surface::clear() {
	cairo_save(_Context.get());
	cairo_set_operator(_Context.get(), CAIRO_OPERATOR_CLEAR);
	cairo_set_source_rgba(_Context.get(), 1.0, 1.0, 1.0, 1.0);
	cairo_paint(_Context.get());
	cairo_restore(_Context.get());
}

namespace {
	void _Set_render_props(cairo_t* context, const optional<render_props>& r) {
		if (r == nullopt) {
			cairo_identity_matrix(context);
			cairo_set_antialias(context, CAIRO_ANTIALIAS_GOOD);
			cairo_set_operator(context, CAIRO_OPERATOR_OVER);
		}
		else {
			const render_props& props = r.value();
			const matrix_2d m = props.surface_matrix();
			cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
			cairo_set_matrix(context, &cm);
			cairo_set_antialias(context, _Antialias_to_cairo_antialias_t(props.antialiasing()));
			cairo_set_operator(context, _Compositing_operator_to_cairo_operator_t(props.compositing()));
		}
	}

	void _Set_clip_props(cairo_t* context, const optional<clip_props>& c) {
		cairo_reset_clip(context);
		if (c != nullopt) {
			// Save state
			cairo_fill_rule_t fr = cairo_get_fill_rule(context);
			//unique_ptr<cairo_path_t, decltype(&cairo_path_destroy)> op(cairo_copy_path(context), &cairo_path_destroy);
			// Set clip
			const auto& props = c.value();
			cairo_set_fill_rule(context, _Fill_rule_to_cairo_fill_rule_t(props.fill_rule()));
			cairo_new_path(context);
			cairo_append_path(context, props.clip().native_handle());
			cairo_clip(context);
			// Restore saved state
			cairo_set_fill_rule(context, fr);
			//cairo_new_path(context);
			//cairo_append_path(context, op.get());
		}
	}

	void _Set_stroke_props(cairo_t* context, const optional<stroke_props>& s, double miterMax, const optional<dashes>& ds) {
		if (s == nullopt) {
			cairo_set_line_width(context, 2.0);
			cairo_set_line_cap(context, CAIRO_LINE_CAP_BUTT);
			cairo_set_line_join(context, CAIRO_LINE_JOIN_MITER);
			cairo_set_miter_limit(context, 10.0);
		}
		else {
			const auto& props = s.value();
			cairo_set_line_width(context, props.line_width());
			cairo_set_line_cap(context, _Line_cap_to_cairo_line_cap_t(props.line_cap()));
			cairo_set_line_join(context, _Line_join_to_cairo_line_join_t(props.line_join()));
			cairo_set_miter_limit(context, ::std::min<double>(miterMax, props.miter_limit()));
		}
		if (ds == nullopt) {
			cairo_set_dash(context, nullptr, 0, 0.0);
		}
		else {
			const auto& d = ds.value();
			cairo_set_dash(context, get<0>(d).data(), _Container_size_to_int(get<0>(d)), get<1>(d));
			if (cairo_status(context) == CAIRO_STATUS_INVALID_DASH) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_DASH);
			}
		}
	}

	void _Set_brush_props(cairo_t* context, const optional<brush_props>& bp, const brush& b) {
		if (bp == nullopt) {
			auto p = b.native_handle();
			cairo_pattern_set_extend(p, CAIRO_EXTEND_NONE);
			cairo_pattern_set_filter(p, CAIRO_FILTER_GOOD);
			cairo_pattern_set_matrix(p, &_Cairo_identity_matrix);
			cairo_set_fill_rule(context, CAIRO_FILL_RULE_WINDING);
		}
		else {
			const auto& props = bp.value();
			auto p = b.native_handle();
			cairo_pattern_set_extend(b.native_handle(), _Extend_to_cairo_extend_t(props.wrap_mode()));
			cairo_pattern_set_filter(p, _Filter_to_cairo_filter_t(props.filter()));
			const auto& m = props.matrix();
			cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
			cairo_pattern_set_matrix(p, &cm);
			cairo_set_fill_rule(context, _Fill_rule_to_cairo_fill_rule_t(props.fill_rule()));
		}
	}

	void _Set_mask_props(const optional<mask_props>& mp, const brush& b) {
		if (mp == nullopt) {
			auto p = b.native_handle();
			cairo_pattern_set_extend(p, CAIRO_EXTEND_NONE);
			cairo_pattern_set_filter(p, CAIRO_FILTER_GOOD);
			cairo_pattern_set_matrix(p, &_Cairo_identity_matrix);
		}
		else {
			const auto& props = mp.value();
			auto p = b.native_handle();
			cairo_pattern_set_extend(b.native_handle(), _Extend_to_cairo_extend_t(props.wrap_mode()));
			cairo_pattern_set_filter(p, _Filter_to_cairo_filter_t(props.filter()));
			const auto& m = props.matrix();
			cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
			cairo_pattern_set_matrix(p, &cm);
		}
	}
}

void surface::paint(const brush& b, const optional<brush_props>& bp, const optional<render_props>& rp, const optional<clip_props>& cl) {
	auto context = _Context.get();
	_Set_render_props(context, rp);
	_Set_clip_props(context, cl);
	_Set_brush_props(context, bp, b);
	cairo_set_source(context, b.native_handle());
	cairo_paint(context);
}

//template <class Allocator>
//void surface::fill(const brush& b, const path_builder<Allocator>& pf, const optional<brush_props>& bp, const optional<render_props>& rp, const optional<clip_props>& cl) {
//	path_group pg(pf);
//	fill(b, pg, bp, rp, cl);
//}
void surface::fill(const brush& b, const path_group& pg, const optional<brush_props>& bp, const optional<render_props>& rp, const optional<clip_props>& cl) {
	auto context = _Context.get();
	_Set_render_props(context, rp);
	_Set_clip_props(context, cl);
	_Set_brush_props(context, bp, b);
	cairo_set_source(context, b.native_handle());
	cairo_new_path(context);
	cairo_append_path(context, pg.native_handle());
	cairo_fill(context);
}

//template <class Allocator>
//void surface::stroke(const brush& b, const path_builder<Allocator>& pf, const optional<brush_props>& bp, const optional<stroke_props>& sp, const optional<dashes>& d, const optional<render_props>& rp, const optional<clip_props>& cl) {
//	path_group pg(pf);
//	stroke(b, pg, bp, sp, d, rp, cl);
//}
void surface::stroke(const brush& b, const path_group& pg, const optional<brush_props>& bp, const optional<stroke_props>& sp, const optional<dashes>& d, const optional<render_props>& rp, const optional<clip_props>& cl) {
	auto context = _Context.get();
	_Set_render_props(context, rp);
	_Set_clip_props(context, cl);
	_Set_brush_props(context, bp, b);
	_Set_stroke_props(context, sp, _Line_join_miter_miter_limit, d);
	cairo_set_source(context, b.native_handle());
	cairo_new_path(context);
	cairo_append_path(context, pg.native_handle());
	cairo_stroke(context);
}

void surface::mask(const brush& b, const brush& mb, const path_group& pg, const optional<brush_props>& bp, const optional<mask_props>& mp, const optional<render_props>& rp, const optional<clip_props>& cl) {
	auto context = _Context.get();
	_Set_render_props(context, rp);
	_Set_clip_props(context, cl);
	_Set_brush_props(context, bp, b);
	_Set_mask_props(mp, mb);
	cairo_set_source(context, b.native_handle());
	cairo_new_path(context);
	cairo_append_path(context, pg.native_handle());
	cairo_mask(context, mb.native_handle());
}

//void surface::paint() {
//	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.wrap_mode()));
//	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
//	cairo_matrix_t cPttnMatrix;
//	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
//	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
//	cairo_set_source(_Context.get(), _Brush.native_handle());
//	cairo_paint(_Context.get());
//}
//
//void surface::paint(const rgba_color& c) {
//	brush(experimental::io2d::brush{ c });
//	paint();
//}
//
//void surface::paint(const ::std::experimental::io2d::brush& b) {
//	brush(b);
//	paint();
//}
//
//void surface::paint(const surface& s, const matrix_2d& m, wrap_mode e, filter f) {
//	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
//	auto pat = cairo_get_source(_Context.get());
//	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
//	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
//	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
//	cairo_pattern_set_matrix(pat, &cmat);
//	cairo_paint(_Context.get());
//	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
//}
//
//void surface::paint(double alpha) {
//	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.wrap_mode()));
//	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
//	cairo_matrix_t cPttnMatrix;
//	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
//	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
//	cairo_set_source(_Context.get(), _Brush.native_handle());
//	cairo_paint_with_alpha(_Context.get(), alpha);
//}
//
//void surface::paint(const rgba_color& c, double alpha) {
//	brush(experimental::io2d::brush{ c });
//	paint(alpha);
//}
//
//void surface::paint(const ::std::experimental::io2d::brush& b, double alpha) {
//	brush(b);
//	paint(alpha);
//}
//
//void surface::paint(const surface& s, double alpha, const matrix_2d& m, wrap_mode e, filter f) {
//	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
//	auto pat = cairo_get_source(_Context.get());
//	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
//	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
//	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
//	cairo_pattern_set_matrix(pat, &cmat);
//	cairo_paint_with_alpha(_Context.get(), alpha);
//	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
//}
//
//void surface::fill() {
//	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.wrap_mode()));
//	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
//	cairo_matrix_t cPttnMatrix;
//	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
//	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
//	cairo_set_source(_Context.get(), _Brush.native_handle());
//	cairo_fill_preserve(_Context.get());
//}
//
//void surface::fill(const rgba_color& c) {
//	brush(experimental::io2d::brush{ c });
//	fill();
//}
//
//void surface::fill(const ::std::experimental::io2d::brush& b) {
//	brush(b);
//	fill();
//}
//
//void surface::fill(const surface& s, const matrix_2d& m, wrap_mode e, filter f) {
//	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
//	auto pat = cairo_get_source(_Context.get());
//	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
//	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
//	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
//	cairo_pattern_set_matrix(pat, &cmat);
//	cairo_fill_preserve(_Context.get());
//	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
//}
//
//void surface::fill_immediate() {
//	auto currPath = _Current_path;
//	path_group(experimental::io2d::path_group(_Immediate_path));
//	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.wrap_mode()));
//	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
//	cairo_matrix_t cPttnMatrix;
//	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
//	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
//	cairo_set_source(_Context.get(), _Brush.native_handle());
//	cairo_fill(_Context.get());
//	path_group(currPath);
//}
//
//void surface::fill_immediate(const rgba_color& c) {
//	brush(experimental::io2d::brush{ c });
//	fill_immediate();
//}
//
//void surface::fill_immediate(const ::std::experimental::io2d::brush& b) {
//	brush(b);
//	fill_immediate();
//}
//
//void surface::fill_immediate(const surface& s, const matrix_2d& m, wrap_mode e, filter f) {
//	auto currPath = _Current_path;
//	path_group(experimental::io2d::path_group(_Immediate_path));
//	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
//	auto pat = cairo_get_source(_Context.get());
//	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
//	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
//	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
//	cairo_pattern_set_matrix(pat, &cmat);
//	cairo_fill(_Context.get());
//	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
//	path_group(currPath);
//}
//
//void surface::stroke() {
//	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.wrap_mode()));
//	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
//	cairo_matrix_t cPttnMatrix;
//	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
//	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
//	cairo_set_source(_Context.get(), _Brush.native_handle());
//	cairo_stroke_preserve(_Context.get());
//}
//
//void surface::stroke(const rgba_color& c) {
//	brush(experimental::io2d::brush{ c });
//	stroke();
//}
//
//void surface::stroke(const ::std::experimental::io2d::brush& b) {
//	brush(b);
//	stroke();
//}
//
//void surface::stroke(const surface& s, const matrix_2d& m, wrap_mode e, filter f) {
//	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
//	auto pat = cairo_get_source(_Context.get());
//	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
//	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
//	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
//	cairo_pattern_set_matrix(pat, &cmat);
//	cairo_stroke_preserve(_Context.get());
//	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
//}
//
//void surface::stroke_immediate() {
//	auto currPath = _Current_path;
//	path_group(experimental::io2d::path_group(_Immediate_path));
//	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.wrap_mode()));
//	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
//	cairo_matrix_t cPttnMatrix;
//	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
//	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
//	cairo_set_source(_Context.get(), _Brush.native_handle());
//	cairo_stroke(_Context.get());
//	path_group(currPath);
//}
//
//void surface::stroke_immediate(const rgba_color& c) {
//	brush(experimental::io2d::brush{ c });
//	stroke_immediate();
//}
//
//void surface::stroke_immediate(const ::std::experimental::io2d::brush& b) {
//	brush(b);
//	stroke_immediate();
//}
//
//void surface::stroke_immediate(const surface& s, const matrix_2d& m, wrap_mode e, filter f) {
//	auto currPath = _Current_path;
//	path_group(experimental::io2d::path_group(_Immediate_path));
//	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
//	auto pat = cairo_get_source(_Context.get());
//	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
//	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
//	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
//	cairo_pattern_set_matrix(pat, &cmat);
//	cairo_stroke(_Context.get());
//	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
//	path_group(currPath);
//}
//
//void surface::mask(const ::std::experimental::io2d::brush& maskBrush) {
//	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.wrap_mode()));
//	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
//	cairo_matrix_t cPttnMatrix;
//	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
//	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
//	cairo_set_source(_Context.get(), _Brush.native_handle());
//	cairo_mask(_Context.get(), maskBrush.native_handle());
//}
//
//void surface::mask(const ::std::experimental::io2d::brush& maskBrush, const rgba_color& c) {
//	brush(experimental::io2d::brush{ c });
//	mask(maskBrush);
//}
//
//void surface::mask(const ::std::experimental::io2d::brush& maskBrush, const ::std::experimental::io2d::brush& b) {
//	brush(b);
//	mask(maskBrush);
//}
//
//void surface::mask(const ::std::experimental::io2d::brush& maskBrush, const surface& s, const matrix_2d& m, wrap_mode e, filter f) {
//	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
//	auto pat = cairo_get_source(_Context.get());
//	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
//	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
//	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
//	cairo_pattern_set_matrix(pat, &cmat);
//	cairo_mask(_Context.get(), maskBrush.native_handle());
//	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
//}
//
//void surface::mask_immediate(const ::std::experimental::io2d::brush& maskBrush) {
//	auto currPath = _Current_path;
//	path_group(experimental::io2d::path_group(_Immediate_path));
//	cairo_pattern_set_extend(_Brush.native_handle(), _Extend_to_cairo_extend_t(_Brush.wrap_mode()));
//	cairo_pattern_set_filter(_Brush.native_handle(), _Filter_to_cairo_filter_t(_Brush.filter()));
//	cairo_matrix_t cPttnMatrix;
//	cairo_matrix_init(&cPttnMatrix, _Brush.matrix().m00(), _Brush.matrix().m01(), _Brush.matrix().m10(), _Brush.matrix().m11(), _Brush.matrix().m20(), _Brush.matrix().m21());
//	cairo_pattern_set_matrix(_Brush.native_handle(), &cPttnMatrix);
//
//	cairo_pattern_set_extend(maskBrush.native_handle(), _Extend_to_cairo_extend_t(maskBrush.wrap_mode()));
//	cairo_pattern_set_filter(maskBrush.native_handle(), _Filter_to_cairo_filter_t(maskBrush.filter()));
//	cairo_matrix_init(&cPttnMatrix, maskBrush.matrix().m00(), maskBrush.matrix().m01(), maskBrush.matrix().m10(), maskBrush.matrix().m11(), maskBrush.matrix().m20(), maskBrush.matrix().m21());
//	cairo_pattern_set_matrix(maskBrush.native_handle(), &cPttnMatrix);
//
//	cairo_set_source(_Context.get(), _Brush.native_handle());
//	cairo_mask(_Context.get(), maskBrush.native_handle());
//	path_group(currPath);
//}
//
//void surface::mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const rgba_color& c) {
//	brush(experimental::io2d::brush{ c });
//	mask_immediate(maskBrush);
//}
//
//void surface::mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const ::std::experimental::io2d::brush& b) {
//	brush(b);
//	mask_immediate(maskBrush);
//}
//
//void surface::mask_immediate(const ::std::experimental::io2d::brush& maskBrush, const surface& s, const matrix_2d& m, wrap_mode e, filter f) {
//	auto currPath = _Current_path;
//	path_group(experimental::io2d::path_group(_Immediate_path));
//	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
//	auto pat = cairo_get_source(_Context.get());
//	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
//	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
//	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
//	cairo_pattern_set_matrix(pat, &cmat);
//
//	cairo_pattern_set_extend(maskBrush.native_handle(), _Extend_to_cairo_extend_t(maskBrush.wrap_mode()));
//	cairo_pattern_set_filter(maskBrush.native_handle(), _Filter_to_cairo_filter_t(maskBrush.filter()));
//	cairo_matrix_init(&cmat, maskBrush.matrix().m00(), maskBrush.matrix().m01(), maskBrush.matrix().m10(), maskBrush.matrix().m11(), maskBrush.matrix().m20(), maskBrush.matrix().m21());
//	cairo_pattern_set_matrix(maskBrush.native_handle(), &cmat);
//
//	cairo_mask(_Context.get(), maskBrush.native_handle());
//	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
//	path_group(currPath);
//}
//
//void surface::matrix(const matrix_2d& m) {
//	auto det = m.determinant();
//	if (det == 0.0) {
//		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MATRIX);
//		return;
//	}
//	_Transform_matrix = m;
//	cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
//	cairo_set_matrix(_Context.get(), &cm);
//}
//
//void surface::matrix(const matrix_2d& m, error_code& ec) noexcept {
//	auto det = m.determinant();
//	if (det == 0.0) {
//		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MATRIX);
//		return;
//	}
//	_Transform_matrix = m;
//	cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
//	cairo_set_matrix(_Context.get(), &cm);
//	ec.clear();
//}
//
//brush surface::brush() const noexcept {
//	return _Brush;
//}
//
//bool surface::is_finished() const noexcept {
//	assert(_Surface != nullptr);
//	return cairo_surface_status(_Surface.get()) == CAIRO_STATUS_SURFACE_FINISHED;
//}

//content surface::content() const noexcept {
//	return _Cairo_content_t_to_content(cairo_surface_get_content(_Surface.get()));
//}
//
//bool surface::_Has_surface_resource() const noexcept {
//	return _Surface != nullptr;
//}
//
//antialias surface::antialias() const noexcept {
//	return _Antialias;
//}
//
//::std::experimental::io2d::dashes surface::dashes() const {
//	::std::experimental::io2d::dashes result{};
//	auto& d = get<0>(result);
//	auto& o = get<1>(result);
//	d.resize(static_cast<vector<double>::size_type>(cairo_get_dash_count(_Context.get())));
//	cairo_get_dash(_Context.get(), d.data(), &o);
//	return result;
//}
//
//experimental::io2d::dashes surface::dashes(error_code& ec) const noexcept {
//	::std::experimental::io2d::dashes result{};
//	auto& d = get<0>(result);
//	auto& o = get<1>(result);
//	try {
//		d.resize(static_cast<vector<double>::size_type>(cairo_get_dash_count(_Context.get())));
//	}
//	catch (const ::std::length_error&) {
//		ec = ::std::make_error_code(::std::errc::not_enough_memory);
//		return result;
//	}
//	catch (const ::std::bad_alloc&) {
//		ec = ::std::make_error_code(::std::errc::not_enough_memory);
//		return result;
//	}
//	cairo_get_dash(_Context.get(), d.data(), &o);
//	ec.clear();
//	return result;
//}
//
//fill_rule surface::fill_rule() const noexcept {
//	return _Cairo_fill_rule_t_to_fill_rule(cairo_get_fill_rule(_Context.get()));
//}
//
//line_cap surface::line_cap() const noexcept {
//	return _Cairo_line_cap_t_to_line_cap(cairo_get_line_cap(_Context.get()));
//}
//
//line_join surface::line_join() const noexcept {
//	return _Line_join;
//}
//
//double surface::line_width() const noexcept {
//	return cairo_get_line_width(_Context.get());
//}
//
//double surface::miter_limit() const noexcept {
//	return _Miter_limit;
//}
//
//compositing_op surface::compositing_op() const noexcept {
//	return _Cairo_operator_t_to_compositing_operator(cairo_get_operator(_Context.get()));
//}
//
//rectangle surface::clip_extents() const noexcept {
//	double pt0x, pt0y, pt1x, pt1y;
//	cairo_clip_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
//	return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
//}
//
//bool surface::in_clip(const vector_2d& pt) const noexcept {
//	return cairo_in_clip(_Context.get(), pt.x(), pt.y()) != 0;
//}
//
//vector<rectangle> surface::clip_rectangles() const {
//	vector<rectangle> results;
//	unique_ptr<cairo_rectangle_list_t, function<void(cairo_rectangle_list_t*)>> sp_rects(cairo_copy_clip_rectangle_list(_Context.get()), &cairo_rectangle_list_destroy);
//	_Throw_if_failed_cairo_status_t(sp_rects->status);
//	for (auto i = 0; i < sp_rects->num_rectangles; ++i) {
//		results.push_back({ sp_rects->rectangles[i].x, sp_rects->rectangles[i].y, sp_rects->rectangles[i].width, sp_rects->rectangles[i].height });
//	}
//
//	return results;
//}
//
//rectangle surface::fill_extents() const noexcept {
//	double pt0x, pt0y, pt1x, pt1y;
//	cairo_fill_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
//	return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
//}
//
//rectangle surface::fill_extents_immediate() const noexcept {
//	// fill_extents doesn't care whether something is ACTUALLY inked; just whether or not the current fill_rule combined with the path_group means the area could be filled (even if the brush won't actually change it).
//	throw runtime_error("Not implemented.");
//	//double pt0x, pt0y, pt1x, pt1y;
//	//cairo_fill_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
//	//return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
//}
//
//bool surface::in_fill(const vector_2d& pt) const noexcept {
//	return cairo_in_fill(_Context.get(), pt.x(), pt.y()) != 0;
//}
//
//bool surface::in_fill_immediate(const vector_2d& pt) const noexcept {
//	throw runtime_error("Not implemented.");
//	//return cairo_in_fill(_Context.get(), pt.x(), pt.y()) != 0;
//}
//
//rectangle surface::stroke_extents() const noexcept {
//	double pt0x, pt0y, pt1x, pt1y;
//	cairo_stroke_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
//	return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
//}
//
//rectangle surface::stroke_extents_immediate() const noexcept {
//	throw runtime_error("Not implemented.");
//	//auto currPath = _Current_path;
//	//path_group(path_group(_Immediate_path));
//	//double pt0x, pt0y, pt1x, pt1y;
//	//cairo_stroke_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
//	//path_group(currPath);
//	//return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
//}
//
//bool surface::in_stroke(const vector_2d& pt) const noexcept {
//	return cairo_in_stroke(_Context.get(), pt.x(), pt.y()) != 0;
//}
//
//bool surface::in_stroke_immediate(const vector_2d& pt) const noexcept {
//	throw runtime_error("Not implemented.");
//}
//
//matrix_2d surface::matrix() const noexcept {
//	return _Transform_matrix;
//}
//
//vector_2d surface::user_to_surface(const vector_2d& pt) const noexcept {
//	return _Transform_matrix.transform_point(pt);
//}
//
//vector_2d surface::surface_to_user(const vector_2d& pt) const noexcept {
//	auto im = _Transform_matrix;
//	im.invert();
//	return im.transform_point(pt);
//}
