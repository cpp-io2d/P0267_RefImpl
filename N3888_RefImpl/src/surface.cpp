#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"
#include <algorithm>

using namespace std;
using namespace std::experimental::drawing;

surface::native_handle_type surface::native_handle() const {
	return{ _Surface.get(), _Context.get() };
}

surface::surface(surface::native_handle_type nh)
	: _Lock_for_device()
	, _Device()
	, _Surface(unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(nh.csfce, &cairo_surface_destroy))
	, _Context(unique_ptr<cairo_t, function<void(cairo_t*)>>(((nh.csfce == nullptr) ? nullptr : cairo_create(nh.csfce)), &cairo_destroy)) {
}

surface::surface(surface&& other)
	: _Lock_for_device()
	, _Device(move(other._Device))
	, _Surface(move(other._Surface))
	, _Context(move(other._Context)) {
	other._Surface = nullptr;
	other._Context = nullptr;
}

surface& surface::operator=(surface&& other) {
	if (this != &other) {
		_Device = move(other._Device);
		_Surface = move(other._Surface);
		_Context = move(other._Context);
		other._Surface = nullptr;
		other._Context = nullptr;
	}
	return *this;
}

surface::surface(const surface& other, content content, int width, int height)
	: _Lock_for_device()
	, _Device()
	, _Surface(unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(cairo_surface_create_similar(other._Surface.get(), _Content_to_cairo_content_t(content), width, height), &cairo_surface_destroy))
	, _Context(unique_ptr<cairo_t, function<void(cairo_t*)>>(cairo_create(_Surface.get()), &cairo_destroy)) {
}

surface::surface(const surface& target, const rectangle& rect)
	: _Lock_for_device()
	, _Device()
	, _Surface(unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(cairo_surface_create_for_rectangle(target._Surface.get(), _Double_to_int(rect.x, false), _Double_to_int(rect.y, false), _Double_to_int(rect.width, false), _Double_to_int(rect.height, false)), &cairo_surface_destroy))
	, _Context(unique_ptr<cairo_t, function<void(cairo_t*)>>(cairo_create(_Surface.get()), &cairo_destroy)) {
}

surface::surface(format fmt, int width, int height)
	: _Lock_for_device()
	, _Device()
	, _Surface(unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), &cairo_surface_destroy))
	, _Context(unique_ptr<cairo_t, function<void(cairo_t*)>>(cairo_create(_Surface.get()), &cairo_destroy)) {
}

surface::~surface() {
}

void surface::finish() {
	cairo_surface_finish(_Surface.get());
}

void surface::flush() {
	cairo_surface_flush(_Surface.get());
}

shared_ptr<device> surface::get_device() {
	lock_guard<mutex> lg(_Lock_for_device);
	auto dvc = _Device.lock();
	if (dvc != nullptr) {
		return dvc;
	}
	dvc = shared_ptr<device>(new device(cairo_surface_get_device(_Surface.get())));
	_Device = weak_ptr<device>(dvc);
	return dvc;
}

content surface::get_content() const {
	return _Cairo_content_t_to_content(cairo_surface_get_content(_Surface.get()));
}

void surface::mark_dirty() {
	cairo_surface_mark_dirty(_Surface.get());
}

void surface::mark_dirty_rectangle(const rectangle& rect) {
	cairo_surface_mark_dirty_rectangle(_Surface.get(), static_cast<int>(rect.x), static_cast<int>(rect.y), static_cast<int>(rect.width), static_cast<int>(rect.height));
}

void surface::set_device_offset(const point& offset) {
	cairo_surface_set_device_offset(_Surface.get(), offset.x, offset.y);
}

point surface::get_device_offset() const {
	point result{ };
	cairo_surface_get_device_offset(_Surface.get(), &result.x, &result.y);
	return result;
}

void surface::write_to_png(const string& filename) {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_surface_write_to_png(_Surface.get(), filename.c_str())));
}

image_surface surface::map_to_image(const rectangle& extents) {
	cairo_rectangle_int_t cextents{ _Double_to_int(extents.x), _Double_to_int(extents.y), _Double_to_int(extents.width), _Double_to_int(extents.height) };

	return image_surface({ cairo_surface_map_to_image(_Surface.get(), (extents.x == 0 && extents.y == 0 && extents.width == 0 && extents.height == 0) ? nullptr : &cextents), nullptr }, { _Surface.get(), nullptr });
}

void surface::unmap_image(image_surface& image) {
	image._Context = nullptr;
	image._Surface = nullptr;
}

bool surface::has_surface_resource() const {
	return _Surface != nullptr;
}

void surface::save() {
	cairo_save(_Context.get());
}

void surface::restore() {
	cairo_restore(_Context.get());
}

void surface::push_group() {
	cairo_push_group(_Context.get());
}

void surface::push_group_with_content(content c) {
	cairo_push_group_with_content(_Context.get(), _Content_to_cairo_content_t(c));
}

surface surface::pop_group() {
	cairo_surface_t* sfce = nullptr;
	unique_ptr<cairo_pattern_t, function<void(cairo_pattern_t*)>> pttn(cairo_pop_group(_Context.get()), &cairo_pattern_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pttn.get())));
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_get_surface(pttn.get(), &sfce)));
	// This next line would not create a resource leak if it threw because until we reference the surface we don't own it.
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_surface_status(sfce)));
	return surface({ cairo_surface_reference(sfce), nullptr });
}

void surface::pop_group_to_source() {
	cairo_pop_group_to_source(_Context.get());
}

void surface::set_pattern() {
	cairo_set_source_rgb(_Context.get(), 0.0, 0.0, 0.0);
}

void surface::set_pattern(const pattern& source) {
	cairo_set_source(_Context.get(), source.native_handle());
}

pattern surface::get_pattern() const {
	return pattern(cairo_pattern_reference(cairo_get_source(_Context.get())));
}

void surface::set_antialias(antialias a) {
	cairo_set_antialias(_Context.get(), _Antialias_to_cairo_antialias_t(a));
}

antialias surface::get_antialias() const {
	return _Cairo_antialias_t_to_antialias(cairo_get_antialias(_Context.get()));
}

void surface::set_dashes() {
	cairo_set_dash(_Context.get(), nullptr, 0, 0.0);
}

void surface::set_dashes(const dashes& d) {
	cairo_set_dash(_Context.get(), get<0>(d).data(), static_cast<int>(get<0>(d).size()), get<1>(d));
}

int surface::get_dashes_count() const {
	return cairo_get_dash_count(_Context.get());
}

surface::dashes surface::get_dashes() const {
	dashes result{ };
	auto& d = get<0>(result);
	auto& o = get<1>(result);
	d.resize(get_dashes_count());
	cairo_get_dash(_Context.get(), &d[0], &o);
	return result;
}

void surface::set_fill_rule(fill_rule fr) {
	cairo_set_fill_rule(_Context.get(), _Fill_rule_to_cairo_fill_rule_t(fr));
}

fill_rule surface::get_fill_rule() const {
	return _Cairo_fill_rule_t_to_fill_rule(cairo_get_fill_rule(_Context.get()));
}

void surface::set_line_cap(line_cap lc) {
	cairo_set_line_cap(_Context.get(), _Line_cap_to_cairo_line_cap_t(lc));
}

line_cap surface::get_line_cap() const {
	return _Cairo_line_cap_t_to_line_cap(cairo_get_line_cap(_Context.get()));
}

void surface::set_line_join(line_join lj) {
	cairo_set_line_join(_Context.get(), _Line_join_to_cairo_line_join_t(lj));
}

line_join surface::get_line_join() const {
	return _Cairo_line_join_t_to_line_join(cairo_get_line_join(_Context.get()));
}

void surface::set_line_width(double width) {
	cairo_set_line_width(_Context.get(), width);
}

double surface::get_line_width() const {
	return cairo_get_line_width(_Context.get());
}

void surface::set_miter_limit(double limit) {
	cairo_set_miter_limit(_Context.get(), limit);
}

double surface::get_miter_limit() const {
	return cairo_get_miter_limit(_Context.get());
}

void surface::set_compositing_operator(compositing_operator co) {
	cairo_set_operator(_Context.get(), _Compositing_operator_to_cairo_operator_t(co));
}

compositing_operator surface::get_compositing_operator() const {
	return _Cairo_operator_t_to_compositing_operator(cairo_get_operator(_Context.get()));
}

void surface::set_tolerance(double tolerance) {
	cairo_set_tolerance(_Context.get(), tolerance);
}

double surface::get_tolerance() const {
	return cairo_get_tolerance(_Context.get());
}

void surface::clip() {
	cairo_clip_preserve(_Context.get());
}

rectangle surface::get_clip_extents() const {
	point pt0{ };
	point pt1{ };
	cairo_clip_extents(_Context.get(), &pt0.x, &pt0.y, &pt1.x, &pt1.y);
	return{ min(pt0.x, pt1.x), min(pt0.y, pt1.y), max(pt0.x, pt1.x) - min(pt0.x, pt1.x), max(pt0.y, pt1.y) - min(pt0.y, pt1.y) };
}

bool surface::in_clip(const point& pt) const {
	return cairo_in_clip(_Context.get(), pt.x, pt.y) != 0;
}

void surface::reset_clip() {
	cairo_reset_clip(_Context.get());
}

vector<rectangle> surface::copy_clip_rectangle_list() const {
	vector<rectangle> results;
	std::unique_ptr<cairo_rectangle_list_t, function<void(cairo_rectangle_list_t*)>> sp_rects(cairo_copy_clip_rectangle_list(_Context.get()), &cairo_rectangle_list_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(sp_rects->status));
	for (auto i = 0; i < sp_rects->num_rectangles; ++i) {
		results.push_back({ sp_rects->rectangles[i].x, sp_rects->rectangles[i].y, sp_rects->rectangles[i].width, sp_rects->rectangles[i].height });
	}

	return results;
}

void surface::fill() {
	cairo_fill_preserve(_Context.get());
}

void surface::fill(const surface& s) {
	unique_ptr<cairo_pattern_t, function<void(cairo_pattern_t*)>> pat(cairo_pattern_reference(cairo_get_source(_Context.get())), &cairo_pattern_destroy);
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	cairo_fill_preserve(_Context.get());
	cairo_surface_flush(_Surface.get());
	cairo_set_source(_Context.get(), pat.get());
}

rectangle surface::get_fill_extents() const {
	point pt0{ };
	point pt1{ };
	cairo_fill_extents(_Context.get(), &pt0.x, &pt0.y, &pt1.x, &pt1.y);
	return{ min(pt0.x, pt1.x), min(pt0.y, pt1.y), max(pt0.x, pt1.x) - min(pt0.x, pt1.x), max(pt0.y, pt1.y) - min(pt0.y, pt1.y) };
}

bool surface::in_fill(const point& pt) const {
	return cairo_in_fill(_Context.get(), pt.x, pt.y) != 0;
}

void surface::mask(const pattern& pttn) {
	cairo_mask(_Context.get(), pttn.native_handle());
}

void surface::mask(const surface& surface) {
	cairo_mask_surface(_Context.get(), surface.native_handle().csfce, 0.0, 0.0);
}

void surface::mask(const surface& surface, const point& origin) {
	cairo_mask_surface(_Context.get(), surface.native_handle().csfce, origin.x, origin.y);
}

void surface::paint() {
	cairo_paint(_Context.get());
}

void surface::paint(const surface& s) {
	unique_ptr<cairo_pattern_t, function<void(cairo_pattern_t*)>> pat(cairo_pattern_reference(cairo_get_source(_Context.get())), &cairo_pattern_destroy);
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	cairo_paint(_Context.get());
	cairo_surface_flush(_Surface.get());
	cairo_set_source(_Context.get(), pat.get());
}

void surface::paint_with_alpha(double alpha) {
	cairo_paint_with_alpha(_Context.get(), alpha);
}

void surface::paint_with_alpha(const surface& s, double alpha) {
	auto pat = cairo_get_source(_Context.get());
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	cairo_paint_with_alpha(_Context.get(), alpha);
	cairo_surface_flush(_Surface.get());
	cairo_set_source(_Context.get(), pat);
}

void surface::stroke() {
	cairo_stroke_preserve(_Context.get());
}

void surface::stroke(const surface& s) {
	unique_ptr<cairo_pattern_t, function<void(cairo_pattern_t*)>> pat(cairo_pattern_reference(cairo_get_source(_Context.get())), &cairo_pattern_destroy);
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	cairo_stroke_preserve(_Context.get());
	cairo_surface_flush(_Surface.get());
	cairo_set_source(_Context.get(), pat.get());
}

rectangle surface::get_stroke_extents() const {
	point pt0{ };
	point pt1{ };
	cairo_stroke_extents(_Context.get(), &pt0.x, &pt0.y, &pt1.x, &pt1.y);
	return{ min(pt0.x, pt1.x), min(pt0.y, pt1.y), max(pt0.x, pt1.x) - min(pt0.x, pt1.x), max(pt0.y, pt1.y) - min(pt0.y, pt1.y) };
}

bool surface::in_stroke(const point& pt) const {
	return cairo_in_stroke(_Context.get(), pt.x, pt.y) != 0;
}

void surface::set_path() {
	cairo_new_path(_Context.get());
}

void surface::set_path(const path& p) {
	auto ctx = _Context.get();
	cairo_new_path(ctx);
	const auto& pathData = p.get_data_ref();
	for (unsigned int i = 0; i < pathData.size(); i += pathData[i].header.length) {
		auto pdt = pathData[i].header.type;
		switch (pdt) {
		case ::std::experimental::drawing::path_data_type::move_to:
			cairo_move_to(ctx, pathData[i + 1].pt.x, pathData[i + 1].pt.y);
			break;
		case ::std::experimental::drawing::path_data_type::line_to:
			cairo_line_to(ctx, pathData[i + 1].pt.x, pathData[i + 1].pt.y);
			break;
		case ::std::experimental::drawing::path_data_type::curve_to:
			cairo_curve_to(ctx, pathData[i + 1].pt.x, pathData[i + 1].pt.y, pathData[i + 2].pt.x, pathData[i + 2].pt.y, pathData[i + 3].pt.x, pathData[i + 3].pt.y);
			break;
		case ::std::experimental::drawing::path_data_type::new_sub_path:
			cairo_new_sub_path(ctx);
			break;
		case std::experimental::drawing::path_data_type::close_path:
			cairo_close_path(ctx);
			break;
		default:
			throw drawing_exception(status::invalid_path_data);
		}
	}
}

void surface::set_matrix(const matrix_2d& m) {
	cairo_matrix_t cm{ m.xx, m.yx, m.xy, m.yy, m.x0, m.y0 };
	cairo_set_matrix(_Context.get(), &cm);
}

matrix_2d surface::get_matrix() const {
	cairo_matrix_t cm{ };
	cairo_get_matrix(_Context.get(), &cm);
	return{ cm.xx, cm.yx, cm.xy, cm.yy, cm.x0, cm.y0 };
}

point surface::user_to_device() const {
	point result{ };
	cairo_user_to_device(_Context.get(), &result.x, &result.y);
	return result;
}

point surface::user_to_device_distance() const {
	point result{ };
	cairo_user_to_device_distance(_Context.get(), &result.x, &result.y);
	return result;
}

point surface::device_to_user() const {
	point result{ };
	cairo_device_to_user(_Context.get(), &result.x, &result.y);
	return result;
}

point surface::device_to_user_distance() const {
	point result{ };
	cairo_device_to_user_distance(_Context.get(), &result.x, &result.y);
	return result;
}

void surface::select_font_face(const string& family, font_slant slant, font_weight weight) {
	cairo_select_font_face(_Context.get(), family.c_str(), _Font_slant_to_cairo_font_slant_t(slant), _Font_weight_to_cairo_font_weight_t(weight));
}

void surface::set_font_size(double size) {
	cairo_set_font_size(_Context.get(), size);
}

void surface::set_font_matrix(const matrix_2d& m) {
	cairo_matrix_t cm{ m.xx, m.yx, m.xy, m.yy, m.x0, m.y0 };
	cairo_set_font_matrix(_Context.get(), &cm);
}

matrix_2d surface::get_font_matrix() const {
	cairo_matrix_t cm{ };
	cairo_get_font_matrix(_Context.get(), &cm);
	return{ cm.xx, cm.yx, cm.xy, cm.yy, cm.x0, cm.y0 };
}

void surface::set_font_options(const font_options& options) {
	cairo_set_font_options(_Context.get(), options.native_handle());
}

// Note: This deviates from cairo in that we return the values that will actually wind up being used.
font_options surface::get_font_options() const {
	font_options fo(antialias::default_antialias, subpixel_order::default_subpixel_order, hint_style::default_hint_style, hint_metrics::default_hint_metrics);
	cairo_get_font_options(_Context.get(), fo.native_handle());
	auto ca = fo.get_antialias();
	auto cso = fo.get_subpixel_order();
	auto chs = fo.get_hint_style();
	auto chm = fo.get_hint_metrics();
	cairo_surface_get_font_options(_Surface.get(), fo.native_handle());

	return font_options(
		(ca == antialias::default_antialias) ? fo.get_antialias() : ca,
		(cso == subpixel_order::default_subpixel_order) ? fo.get_subpixel_order() : cso,
		(chs == hint_style::default_hint_style) ? fo.get_hint_style() : chs,
		(chm == hint_metrics::default_hint_metrics) ? fo.get_hint_metrics() : chm
		);
}

void surface::set_font_face(const font_face& font_face) {
	cairo_set_font_face(_Context.get(), font_face.native_handle());
}

font_face surface::get_font_face() const {
	auto ff = cairo_get_font_face(_Context.get());
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_font_face_status(ff)));
	// Cairo doesn't increase the font face's reference count when you call cairo_get_font_face so we do it manually.
	return font_face(cairo_font_face_reference(ff));
}

void surface::set_scaled_font(const scaled_font& scaled_font) {
	cairo_set_scaled_font(_Context.get(), scaled_font.native_handle());
}

scaled_font surface::get_scaled_font() const {
	auto sf = cairo_get_scaled_font(_Context.get());
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_scaled_font_status(sf)));
	// Cairo doesn't increase the scaled font's reference count when you call cairo_get_scaled_font so we do it manually.
	return scaled_font(cairo_scaled_font_reference(sf));
}

void surface::show_text(const string& utf8) {
	cairo_show_text(_Context.get(), utf8.c_str());
}

void surface::show_glyphs(const vector<glyph>& glyphs) {
	vector<cairo_glyph_t> vec;
	for (const auto& glyph : glyphs) {
		vec.push_back({ glyph.index, glyph.x, glyph.y });
	}
	cairo_show_glyphs(_Context.get(), vec.data(), static_cast<int>(vec.size()));
}

void surface::show_text_glyphs(const string& utf8, const vector<glyph>& glyphs, const vector<text_cluster>& clusters, text_cluster_flags::text_cluster_flags cluster_flags) {
	vector<cairo_glyph_t> vec;
	for (const auto& glyph : glyphs) {
		vec.push_back({ glyph.index, glyph.x, glyph.y });
	}
	const auto tcSize = static_cast<int>(clusters.size());
	unique_ptr<cairo_text_cluster_t, function<void(cairo_text_cluster_t*)>> sp_tc(cairo_text_cluster_allocate(tcSize), &cairo_text_cluster_free);
	auto tc_ptr = sp_tc.get();
	for (auto i = 0; i < tcSize; ++i) {
		tc_ptr[i].num_bytes = clusters[i].num_bytes;
		tc_ptr[i].num_glyphs = clusters[i].num_glyphs;
	}
	auto ctcf = _Text_cluster_flags_to_cairo_text_cluster_flags_t(cluster_flags);
	cairo_show_text_glyphs(_Context.get(), utf8.data(), static_cast<int>(utf8.size()), vec.data(), static_cast<int>(vec.size()), sp_tc.get(), tcSize, ctcf);
}

font_extents surface::get_font_extents() const {
	font_extents result;
	cairo_font_extents_t cfe{ };
	cairo_font_extents(_Context.get(), &cfe);
	result.ascent = cfe.ascent;
	result.descent = cfe.descent;
	result.height = cfe.height;
	result.max_x_advance = cfe.max_x_advance;
	result.max_y_advance = cfe.max_y_advance;
	return result;
}

text_extents surface::get_text_extents(const string& utf8) const {
	text_extents result;
	cairo_text_extents_t cte{ };
	cairo_text_extents(_Context.get(), utf8.c_str(), &cte);
	result.height = cte.height;
	result.width = cte.width;
	result.x_advance = cte.x_advance;
	result.x_bearing = cte.x_bearing;
	result.y_advance = cte.y_advance;
	result.y_bearing = cte.y_bearing;
	return result;
}

text_extents surface::get_glyph_extents(const vector<glyph>& glyphs) const {
	vector<cairo_glyph_t> vec;
	for (const auto& glyph : glyphs) {
		vec.push_back({ glyph.index, glyph.x, glyph.y });
	}
	text_extents result;
	cairo_text_extents_t cfe{ };
	cairo_glyph_extents(_Context.get(), vec.data(), static_cast<int>(vec.size()), &cfe);
	result.height = cfe.height;
	result.width = cfe.width;
	result.x_advance = cfe.x_advance;
	result.x_bearing = cfe.x_bearing;
	result.y_advance = cfe.y_advance;
	result.y_bearing = cfe.y_bearing;
	return result;
}
