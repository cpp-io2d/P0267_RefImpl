#include "io2d.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

//namespace {
//	const point_2d _Font_default_size{ 16.0F, 16.0F };
//}
//
constexpr cairo_matrix_t _Cairo_identity_matrix{ 1.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F };

surface::surface(format fmt, int width, int height)
	: _Surface(unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), &cairo_surface_destroy))
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
	: _Surface(unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(nh.csfce, &cairo_surface_destroy))
	, _Context(unique_ptr<cairo_t, decltype(&cairo_destroy)>(((nh.csfce == nullptr) ? nullptr : cairo_create(nh.csfce)), &cairo_destroy))
	, _Dirty_rect()
	, _Format(fmt) {
	if (nh.csfce != nullptr) {
		_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
		_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
	}
}

void surface::flush() {
	cairo_surface_flush(_Surface.get());
}

void surface::flush(::std::error_code & ec) noexcept {
	cairo_surface_flush(_Surface.get());
	ec.clear();
}

void surface::mark_dirty() {
	cairo_surface_mark_dirty(_Surface.get());
}

void surface::mark_dirty(error_code& ec) noexcept {
	cairo_surface_mark_dirty(_Surface.get());
	ec.clear();
}

void surface::mark_dirty(const bounding_box& extents) {
	_Dirty_rect = extents;
	cairo_surface_mark_dirty_rectangle(_Surface.get(), _Float_to_int(extents.x()), _Float_to_int(extents.y()), _Float_to_int(extents.width()), _Float_to_int(extents.height()));
}

void surface::mark_dirty(const bounding_box& extents, error_code& ec) noexcept {
	_Dirty_rect = extents;
	cairo_surface_mark_dirty_rectangle(_Surface.get(), _Float_to_int(extents.x()), _Float_to_int(extents.y()), _Float_to_int(extents.width()), _Float_to_int(extents.height()));
	ec.clear();
}

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
			cairo_set_antialias(context, _Antialias_to_cairo_antialias_t(antialias::good));
			cairo_identity_matrix(context);
			cairo_set_operator(context, CAIRO_OPERATOR_OVER);
		}
		else {
			const render_props& props = r.value();
			const matrix_2d m = props.surface_matrix();
			cairo_matrix_t cm{ m.m00, m.m01, m.m10, m.m11, m.m20, m.m21 };
			cairo_set_antialias(context, _Antialias_to_cairo_antialias_t(props.antialiasing()));
			cairo_set_matrix(context, &cm);
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
			cairo_append_path(context, props.clip()._Impl_path());
			cairo_clip(context);
			// Restore saved state
			cairo_set_fill_rule(context, fr);
			//cairo_new_path(context);
			//cairo_append_path(context, op.get());
		}
	}

	void _Set_stroke_props(cairo_t* context, const optional<stroke_props>& s, float miterMax, const optional<dashes>& ds) {
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
			cairo_set_miter_limit(context, ::std::min<float>(miterMax, props.miter_limit()));
		}
		if (ds == nullopt) {
			cairo_set_dash(context, nullptr, 0, 0.0);
		}
		else {
			const auto& d = ds.value();
			const auto& dFloatVal = get<0>(d);
			vector<double> dashAsDouble(dFloatVal.size());
			for (const auto& val : dFloatVal) {
				dashAsDouble.push_back(static_cast<double>(val));
			}
			cairo_set_dash(context, dashAsDouble.data(), _Container_size_to_int(dashAsDouble), static_cast<double>(get<1>(d)));
			if (cairo_status(context) == CAIRO_STATUS_INVALID_DASH) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_DASH);
			}
		}
	}

	void _Set_brush_props(cairo_t* context, const optional<brush_props>& bp, const brush& b) {
		if (bp == nullopt) {
			auto p = b._Impl_brush();
			cairo_pattern_set_extend(p, CAIRO_EXTEND_NONE);
			cairo_pattern_set_filter(p, CAIRO_FILTER_BILINEAR);
			cairo_pattern_set_matrix(p, &_Cairo_identity_matrix);
			cairo_set_fill_rule(context, CAIRO_FILL_RULE_WINDING);
		}
		else {
			const auto& props = bp.value();
			auto p = b._Impl_brush();
			cairo_pattern_set_extend(b._Impl_brush(), _Extend_to_cairo_extend_t(props.wrap_mode()));
			cairo_pattern_set_filter(p, _Filter_to_cairo_filter_t(props.filter()));
			const auto& m = props.brush_matrix();
			cairo_matrix_t cm{ m.m00, m.m01, m.m10, m.m11, m.m20, m.m21 };
			cairo_pattern_set_matrix(p, &cm);
			cairo_set_fill_rule(context, _Fill_rule_to_cairo_fill_rule_t(props.fill_rule()));
		}
	}

	void _Set_mask_props(const optional<mask_props>& mp, const brush& b) {
		if (mp == nullopt) {
			auto p = b._Impl_brush();
			cairo_pattern_set_extend(p, CAIRO_EXTEND_NONE);
			cairo_pattern_set_filter(p, CAIRO_FILTER_GOOD);
			cairo_pattern_set_matrix(p, &_Cairo_identity_matrix);
		}
		else {
			const auto& props = mp.value();
			auto p = b._Impl_brush();
			cairo_pattern_set_extend(b._Impl_brush(), _Extend_to_cairo_extend_t(props.wrap_mode()));
			cairo_pattern_set_filter(p, _Filter_to_cairo_filter_t(props.filter()));
			const auto& m = props.mask_matrix();
			cairo_matrix_t cm{ m.m00, m.m01, m.m10, m.m11, m.m20, m.m21 };
			cairo_pattern_set_matrix(p, &cm);
		}
	}
}

void surface::paint(const brush& b, const optional<brush_props>& bp, const optional<render_props>& rp, const optional<clip_props>& cl) {
	auto context = _Context.get();
	_Set_render_props(context, rp);
	_Set_clip_props(context, cl);
	_Set_brush_props(context, bp, b);
	cairo_set_source(context, b._Impl_brush());
	cairo_paint(context);
}

void surface::fill(const brush& b, const interpreted_path& pg, const optional<brush_props>& bp, const optional<render_props>& rp, const optional<clip_props>& cl) {
	auto context = _Context.get();
	_Set_render_props(context, rp);
	_Set_clip_props(context, cl);
	_Set_brush_props(context, bp, b);
	cairo_set_source(context, b._Impl_brush());
	cairo_new_path(context);
	cairo_append_path(context, pg._Impl_path());
	cairo_fill(context);
}

void surface::stroke(const brush& b, const interpreted_path& pg, const optional<brush_props>& bp, const optional<stroke_props>& sp, const optional<dashes>& d, const optional<render_props>& rp, const optional<clip_props>& cl) {
	auto context = _Context.get();
	_Set_render_props(context, rp);
	_Set_clip_props(context, cl);
	_Set_brush_props(context, bp, b);
	_Set_stroke_props(context, sp, _Line_join_miter_miter_limit, d);
	cairo_set_source(context, b._Impl_brush());
	cairo_new_path(context);
	cairo_append_path(context, pg._Impl_path());
	cairo_stroke(context);
}

void surface::mask(const brush& b, const brush& mb, const optional<brush_props>& bp, const optional<mask_props>& mp, const optional<render_props>& rp, const optional<clip_props>& cl) {
	auto context = _Context.get();
	_Set_render_props(context, rp);
	_Set_clip_props(context, cl);
	_Set_brush_props(context, bp, b);
	_Set_mask_props(mp, mb);
	cairo_set_source(context, b._Impl_brush());
	cairo_new_path(context);
	cairo_mask(context, mb._Impl_brush());
}
