#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"
#include <algorithm>

using namespace std;
using namespace std::experimental::io2d;

surface::surface(format fmt, int width, int height)
	: _Lock_for_device()
	, _Device()
	, _Surface(unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), &cairo_surface_destroy))
	, _Context(unique_ptr<cairo_t, function<void(cairo_t*)>>(cairo_create(_Surface.get()), &cairo_destroy))
	, _Default_path(get_path(path_factory()))
	, _Current_path(_Default_path)
	, _Immediate_path()
	, _Pattern(cairo_pattern_create_rgba(0.0, 0.0, 0.0, 0.0))
	, _Saved_state() {
}

surface::native_handle_type surface::native_handle() const {
	return{ _Surface.get(), _Context.get() };
}

surface::surface(surface&& other)
	: _Lock_for_device()
	, _Device(move(other._Device))
	, _Surface(move(other._Surface))
	, _Context(move(other._Context))
	, _Default_path(move(other._Default_path))
	, _Current_path(move(other._Current_path))
	, _Immediate_path(move(other._Immediate_path))
	, _Miter_limit(move(other._Miter_limit))
	, _Line_join(move(other._Line_join))
	, _Pattern(move(other._Pattern))
	, _Saved_state(move(other._Saved_state)) {
	other._Surface = nullptr;
	other._Context = nullptr;
}

surface& surface::operator=(surface&& other) {
	if (this != &other) {
		_Device = move(other._Device);
		_Surface = move(other._Surface);
		_Context = move(other._Context);
		_Default_path = move(other._Default_path);
		_Current_path = move(other._Current_path);
		_Immediate_path = move(other._Immediate_path);
		_Miter_limit = move(other._Miter_limit);
		_Line_join = move(other._Line_join);
		_Pattern = move(other._Pattern);
		_Saved_state = move(other._Saved_state);
		other._Surface = nullptr;
		other._Context = nullptr;
	}
	return *this;
}

surface::surface(surface::native_handle_type nh)
	: _Lock_for_device()
	, _Device()
	, _Surface(unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(nh.csfce, &cairo_surface_destroy))
	, _Context(unique_ptr<cairo_t, function<void(cairo_t*)>>(((nh.csfce == nullptr) ? nullptr : cairo_create(nh.csfce)), &cairo_destroy))
	, _Default_path(get_path(path_factory()))
	, _Current_path(_Default_path)
	, _Immediate_path()
	, _Pattern(_Context.get() == nullptr ? cairo_pattern_create_rgba(0.0, 0.0, 0.0, 0.0) : cairo_pattern_reference(cairo_get_source(_Context.get())))
	, _Saved_state() {
	if (_Context.get() != nullptr) {
		cairo_set_miter_limit(_Context.get(), _Line_join_miter_miter_limit);
	}
}

surface::surface(const surface& other, content content, int width, int height)
	: _Lock_for_device()
	, _Device()
	, _Surface(unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(cairo_surface_create_similar(other._Surface.get(), _Content_to_cairo_content_t(content), width, height), &cairo_surface_destroy))
	, _Context(unique_ptr<cairo_t, function<void(cairo_t*)>>(cairo_create(_Surface.get()), &cairo_destroy))
	, _Default_path(get_path(path_factory()))
	, _Current_path(_Default_path)
	, _Immediate_path()
	, _Pattern(cairo_pattern_create_rgba(0.0, 0.0, 0.0, 0.0))
	, _Saved_state() {
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

void surface::mark_dirty() {
	cairo_surface_mark_dirty(_Surface.get());
}

void surface::mark_dirty(const rectangle& rect) {
	cairo_surface_mark_dirty_rectangle(_Surface.get(), _Double_to_int(rect.x(), false), _Double_to_int(rect.y(), false), _Double_to_int(rect.width()), _Double_to_int(rect.height()));
}

void surface::set_device_offset(const point& offset) {
	cairo_surface_set_device_offset(_Surface.get(), offset.x(), offset.y());
}

void surface::write_to_file(const string& filename) {
	_Throw_if_failed_cairo_status_t(cairo_surface_write_to_png(_Surface.get(), filename.c_str()));
}

image_surface surface::map_to_image() {
	return image_surface({ cairo_surface_map_to_image(_Surface.get(), nullptr), nullptr }, { _Surface.get(), _Context.get() });
}

image_surface surface::map_to_image(const rectangle& extents) {
	cairo_rectangle_int_t cextents{ _Double_to_int(extents.x()), _Double_to_int(extents.y()), _Double_to_int(extents.width()), _Double_to_int(extents.height()) };

	return image_surface({ cairo_surface_map_to_image(_Surface.get(), (extents.x() == 0 && extents.y() == 0 && extents.width() == 0 && extents.height() == 0) ? nullptr : &cextents), nullptr }, { _Surface.get(), _Context.get() });
}

void surface::unmap_image(image_surface& image) {
	image._Context = nullptr;
	image._Surface = nullptr;
}

void surface::save() {
	cairo_save(_Context.get());
	_Saved_state.push(make_tuple(_Default_path, _Current_path, _Immediate_path, _Miter_limit, _Line_join, _Pattern));
}

void surface::restore() {
	cairo_restore(_Context.get());
	{
		auto& t = _Saved_state.top();
		_Default_path = get<0>(t);
		_Current_path = get<1>(t);
		_Immediate_path = get<2>(t);
		_Miter_limit = get<3>(t);
		_Line_join = get<4>(t);
		_Pattern = get<5>(t);
	}
	_Saved_state.pop();
}

void surface::set_pattern() {
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
}

void surface::set_pattern(const pattern& source) {
	_Pattern = source;
}

void surface::set_antialias(antialias a) {
	cairo_set_antialias(_Context.get(), _Antialias_to_cairo_antialias_t(a));
}

void surface::set_dashes() {
	cairo_set_dash(_Context.get(), nullptr, 0, 0.0);
}

void surface::set_dashes(const dashes& d) {
	cairo_set_dash(_Context.get(), get<0>(d).data(), _Container_size_to_int(get<0>(d)), get<1>(d));
}

void surface::set_fill_rule(fill_rule fr) {
	cairo_set_fill_rule(_Context.get(), _Fill_rule_to_cairo_fill_rule_t(fr));
}

void surface::set_line_cap(line_cap lc) {
	cairo_set_line_cap(_Context.get(), _Line_cap_to_cairo_line_cap_t(lc));
}

void surface::set_line_join(line_join lj) {
	_Line_join = lj;
	cairo_set_line_join(_Context.get(), _Line_join_to_cairo_line_join_t(lj));
	if (lj == line_join::miter_or_bevel) {
		cairo_set_miter_limit(_Context.get(), _Miter_limit);
	}
	if (lj == line_join::miter) {
		cairo_set_miter_limit(_Context.get(), _Line_join_miter_miter_limit);
	}
}

void surface::set_line_width(double width) {
	cairo_set_line_width(_Context.get(), std::max(width, 0.0));
}

void surface::set_miter_limit(double limit) {
	_Miter_limit = limit;
	if (_Line_join == line_join::miter_or_bevel) {
		cairo_set_miter_limit(_Context.get(), std::min(std::max(limit, 1.0), _Line_join_miter_miter_limit));
	}
}

void surface::set_compositing_operator(compositing_operator co) {
	cairo_set_operator(_Context.get(), _Compositing_operator_to_cairo_operator_t(co));
}

void surface::set_tolerance(double tolerance) {
	cairo_set_tolerance(_Context.get(), tolerance);
}

void surface::clip() {
	cairo_clip(_Context.get());
}

void surface::clip_immediate() {
	auto currPath = _Current_path;
	set_path(get_path(_Immediate_path));
	cairo_clip(_Context.get());
	set_path(currPath);
}

void surface::reset_clip() {
	cairo_reset_clip(_Context.get());
}

void surface::set_path() {
	_Current_path = _Default_path;
	cairo_new_path(_Context.get());
}

void surface::set_path(const path& p) {
	this->_Current_path = p;
	cairo_new_path(_Context.get());
	cairo_append_path(_Context.get(), p.native_handle());
}

path_factory& surface::immediate() {
	return _Immediate_path;
}

void surface::paint() {
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	cairo_paint(_Context.get());
}

void surface::paint(const rgba_color& c) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	paint();
}

void surface::paint(const pattern& pttn) {
	set_pattern(pttn);
	paint();
}

void surface::paint(const surface& s, const point& origin, extend e, filter f) {
	paint(s, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
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
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	cairo_paint_with_alpha(_Context.get(), alpha);
}

void surface::paint(const rgba_color& c, double alpha) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	paint(alpha);
}

void surface::paint(const pattern& pttn, double alpha) {
	set_pattern(pttn);
	paint(alpha);
}

void surface::paint(const surface& s, double alpha, const point& origin, extend e, filter f) {
	paint(s, alpha, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
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
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	cairo_fill_preserve(_Context.get());
}

void surface::fill(const rgba_color& c) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	fill();
}

void surface::fill(const pattern& pttn) {
	set_pattern(pttn);
	fill();
}

void surface::fill(const surface& s, const point& origin, extend e, filter f) {
	fill(s, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
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
	set_path(get_path(_Immediate_path));
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	cairo_fill(_Context.get());
	set_path(currPath);
}

void surface::fill_immediate(const rgba_color& c) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	fill_immediate();
}

void surface::fill_immediate(const pattern& pttn) {
	set_pattern(pttn);
	fill_immediate();
}

void surface::fill_immediate(const surface& s, const point& origin, extend e, filter f) {
	fill_immediate(s, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
}

void surface::fill_immediate(const surface& s, const matrix_2d& m, extend e, filter f) {
	auto currPath = _Current_path;
	set_path(get_path(_Immediate_path));
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_fill(_Context.get());
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
	set_path(currPath);
}

void surface::stroke() {
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	cairo_stroke_preserve(_Context.get());
}

void surface::stroke(const rgba_color& c) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	stroke();
}

void surface::stroke(const pattern& pttn) {
	set_pattern(pttn);
	stroke();
}

void surface::stroke(const surface& s, const point& origin, extend e, filter f) {
	stroke(s, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
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
	set_path(get_path(_Immediate_path));
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	cairo_stroke(_Context.get());
	set_path(currPath);
}

void surface::stroke_immediate(const rgba_color& c) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	stroke_immediate();
}

void surface::stroke_immediate(const pattern& pttn) {
	set_pattern(pttn);
	stroke_immediate();
}

void surface::stroke_immediate(const surface& s, const point& origin, extend e, filter f) {
	stroke_immediate(s, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
}

void surface::stroke_immediate(const surface& s, const matrix_2d& m, extend e, filter f) {
	auto currPath = _Current_path;
	set_path(get_path(_Immediate_path));
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_stroke(_Context.get());
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
	set_path(currPath);
}

void surface::mask(const pattern& maskPttn) {
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	cairo_mask(_Context.get(), maskPttn.native_handle());
}

void surface::mask(const pattern& maskPttn, const rgba_color& c) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	mask(maskPttn);
}

void surface::mask(const pattern& maskPttn, const pattern& pttn) {
	set_pattern(pttn);
	mask(maskPttn);
}

void surface::mask(const pattern& maskPttn, const surface& s, const point& origin, extend e, filter f) {
	mask(maskPttn, s, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
}

void surface::mask(const pattern& maskPttn, const surface& s, const matrix_2d& m, extend e, filter f) {
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_mask(_Context.get(), maskPttn.native_handle());
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
}

void surface::mask(const surface& maskSurface) {
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	cairo_mask_surface(_Context.get(), maskSurface.native_handle().csfce, 0.0, 0.0);
}

void surface::mask(const surface& maskSurface, const rgba_color& c) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	mask(maskSurface);
}

void surface::mask(const surface& maskSurface, const pattern& pttn) {
	set_pattern(pttn);
	mask(maskSurface);
}

void surface::mask(const surface& maskSurface, const surface& s, const point& origin, extend e, filter f) {
	mask(maskSurface, s, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
}

void surface::mask(const surface& maskSurface, const surface& s, const matrix_2d& m, extend e, filter f) {
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_mask_surface(_Context.get(), maskSurface.native_handle().csfce, 0.0, 0.0);
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
}

void surface::mask(const surface& maskSurface, const point& maskOrigin) {
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	cairo_mask_surface(_Context.get(), maskSurface.native_handle().csfce, maskOrigin.x(), maskOrigin.y());
}

void surface::mask(const surface& maskSurface, const point& maskOrigin, const rgba_color& c) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	mask(maskSurface, maskOrigin);
}

void surface::mask(const surface& maskSurface, const point& maskOrigin, const pattern& pttn) {
	set_pattern(pttn);
	mask(maskSurface, maskOrigin);
}

void surface::mask(const surface& maskSurface, const point& maskOrigin, const surface& s, const point& origin, extend e, filter f) {
	mask(maskSurface, maskOrigin, s, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
}

void surface::mask(const surface& maskSurface, const point& maskOrigin, const surface& s, const matrix_2d& m, extend e, filter f) {
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_mask_surface(_Context.get(), maskSurface.native_handle().csfce, maskOrigin.x(), maskOrigin.y());
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
}

void surface::mask_immediate(const pattern& maskPttn) {
	auto currPath = _Current_path;
	set_path(get_path(_Immediate_path));
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	cairo_mask(_Context.get(), maskPttn.native_handle());
	set_path(currPath);
}

void surface::mask_immediate(const pattern& maskPttn, const rgba_color& c) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	mask(maskPttn);
}

void surface::mask_immediate(const pattern& maskPttn, const pattern& pttn) {
	set_pattern(pttn);
	mask(maskPttn);
}

void surface::mask_immediate(const pattern& maskPttn, const surface& s, const point& origin, extend e, filter f) {
	mask_immediate(maskPttn, s, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
}

void surface::mask_immediate(const pattern& maskPttn, const surface& s, const matrix_2d& m, extend e, filter f) {
	auto currPath = _Current_path;
	set_path(get_path(_Immediate_path));
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_mask(_Context.get(), maskPttn.native_handle());
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
	set_path(currPath);
}

void surface::mask_immediate(const surface& maskSurface) {
	auto currPath = _Current_path;
	set_path(get_path(_Immediate_path));
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	cairo_mask_surface(_Context.get(), maskSurface.native_handle().csfce, 0.0, 0.0);
	set_path(currPath);
}

void surface::mask_immediate(const surface& maskSurface, const rgba_color& c) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	mask_immediate(maskSurface);
}

void surface::mask_immediate(const surface& maskSurface, const pattern& pttn) {
	set_pattern(pttn);
	mask_immediate(maskSurface);
}

void surface::mask_immediate(const surface& maskSurface, const surface& s, const point& origin, extend e, filter f) {
	mask_immediate(maskSurface, s, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
}

void surface::mask_immediate(const surface& maskSurface, const surface& s, const matrix_2d& m, extend e, filter f) {
	auto currPath = _Current_path;
	set_path(get_path(_Immediate_path));
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_mask_surface(_Context.get(), maskSurface.native_handle().csfce, 0.0, 0.0);
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
}

void surface::mask_immediate(const surface& maskSurface, const point& maskOrigin) {
	auto currPath = _Current_path;
	set_path(get_path(_Immediate_path));
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	cairo_mask_surface(_Context.get(), maskSurface.native_handle().csfce, maskOrigin.x(), maskOrigin.y());
	set_path(currPath);
}

void surface::mask_immediate(const surface& maskSurface, const point& maskOrigin, const rgba_color& c) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	mask_immediate(maskSurface, maskOrigin);
}

void surface::mask_immediate(const surface& maskSurface, const point& maskOrigin, const pattern& pttn) {
	set_pattern(pttn);
	mask_immediate(maskSurface, maskOrigin);
}

void surface::mask_immediate(const surface& maskSurface, const point& maskOrigin, const surface& s, const point& origin, extend e, filter f) {
	mask_immediate(maskSurface, maskOrigin, s, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
}

void surface::mask_immediate(const surface& maskSurface, const point& maskOrigin, const surface& s, const matrix_2d& m, extend e, filter f) {
	auto currPath = _Current_path;
	set_path(get_path(_Immediate_path));
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	cairo_mask_surface(_Context.get(), maskSurface.native_handle().csfce, maskOrigin.x(), maskOrigin.y());
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
}

point surface::show_text(const string& utf8, const point& position) {
	cairo_new_path(_Context.get());
	cairo_move_to(_Context.get(), position.x(), position.y());
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	cairo_show_text(_Context.get(), utf8.c_str());
	double x, y;
	cairo_get_current_point(_Context.get(), &x, &y);
	set_path(_Current_path);
	return point{ x, y };
}

point surface::show_text(const string& utf8, const point& position, const rgba_color& c) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	return show_text(utf8, position);
}

point surface::show_text(const string& utf8, const point& position, const pattern& pttn) {
	set_pattern(pttn);
	return show_text(utf8, position);
}

point surface::show_text(const string& utf8, const point& position, const surface& s, const point& origin, extend e, filter f) {
	return show_text(utf8, position, s, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
}

point surface::show_text(const string& utf8, const point& position, const surface& s, const matrix_2d& m, extend e, filter f) {
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	auto result = show_text(utf8, position);
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
	return result;
}

void surface::show_glyphs(const vector<glyph>& glyphs) {
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	vector<cairo_glyph_t> vec;
	for (const auto& glyph : glyphs) {
		vec.push_back({ glyph.index(), glyph.x(), glyph.y() });
	}
	cairo_show_glyphs(_Context.get(), vec.data(), _Container_size_to_int(vec));
}

void surface::show_glyphs(const vector<glyph>& glyphs, const rgba_color& c) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	show_glyphs(glyphs);
}

void surface::show_glyphs(const vector<glyph>& glyphs, const pattern& pttn) {
	set_pattern(pttn);
	show_glyphs(glyphs);
}

void surface::show_glyphs(const vector<glyph>& glyphs, const surface& s, const point& origin, extend e, filter f) {
	show_glyphs(glyphs, s, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
}

void surface::show_glyphs(const vector<glyph>& glyphs, const surface& s, const matrix_2d& m, extend e, filter f) {
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	vector<cairo_glyph_t> vec;
	for (const auto& glyph : glyphs) {
		vec.push_back({ glyph.index(), glyph.x(), glyph.y() });
	}
	cairo_show_glyphs(_Context.get(), vec.data(), _Container_size_to_int(vec));
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
}

void surface::show_text_glyphs(const string& utf8, const vector<glyph>& glyphs, const vector<text_cluster>& clusters, bool clusterToGlyphsMapReverse) {
	cairo_pattern_set_extend(_Pattern.native_handle(), _Extend_to_cairo_extend_t(_Pattern.get_extend()));
	cairo_pattern_set_filter(_Pattern.native_handle(), _Filter_to_cairo_filter_t(_Pattern.get_filter()));
	cairo_matrix_t cPttnMatrix;
	cairo_matrix_init(&cPttnMatrix, _Pattern.get_matrix().m00(), _Pattern.get_matrix().m01(), _Pattern.get_matrix().m10(), _Pattern.get_matrix().m11(), _Pattern.get_matrix().m20(), _Pattern.get_matrix().m21());
	cairo_pattern_set_matrix(_Pattern.native_handle(), &cPttnMatrix);
	cairo_set_source(_Context.get(), _Pattern.native_handle());
	vector<cairo_glyph_t> vec;
	for (const auto& glyph : glyphs) {
		vec.push_back({ glyph.index(), glyph.x(), glyph.y() });
	}
	const auto tcSize = _Container_size_to_int(clusters);
	unique_ptr<cairo_text_cluster_t, function<void(cairo_text_cluster_t*)>> sp_tc(cairo_text_cluster_allocate(tcSize), &cairo_text_cluster_free);
	auto tc_ptr = sp_tc.get();
	for (auto i = 0; i < tcSize; ++i) {
		tc_ptr[i].num_bytes = clusters[i].num_bytes();
		tc_ptr[i].num_glyphs = clusters[i].num_glyphs();
	}
	auto ctcf = static_cast<cairo_text_cluster_flags_t>(clusterToGlyphsMapReverse ? CAIRO_TEXT_CLUSTER_FLAG_BACKWARD : 0);
	cairo_show_text_glyphs(_Context.get(), utf8.data(), _Container_size_to_int(utf8), vec.data(), _Container_size_to_int(vec), sp_tc.get(), tcSize, ctcf);
}

void surface::show_text_glyphs(const string& utf8, const vector<glyph>& glyphs, const vector<text_cluster>& clusters, bool clusterToGlyphsMapReverse, const rgba_color& c) {
	solid_color_pattern_factory factory(c);
	set_pattern(get_pattern(factory));
	show_text_glyphs(utf8, glyphs, clusters, clusterToGlyphsMapReverse);
}

void surface::show_text_glyphs(const string& utf8, const vector<glyph>& glyphs, const vector<text_cluster>& clusters, bool clusterToGlyphsMapReverse, const pattern& pttn) {
	set_pattern(pttn);
	show_text_glyphs(utf8, glyphs, clusters, clusterToGlyphsMapReverse);
}

void surface::show_text_glyphs(const string& utf8, const vector<glyph>& glyphs, const vector<text_cluster>& clusters, bool clusterToGlyphsMapReverse, const surface& s, const point& origin, extend e, filter f) {
	show_text_glyphs(utf8, glyphs, clusters, clusterToGlyphsMapReverse, s, matrix_2d{ 1.0, 0.0, 0.0, 1.0, origin.x(), origin.y() }, e, f);
}

void surface::show_text_glyphs(const string& utf8, const vector<glyph>& glyphs, const vector<text_cluster>& clusters, bool clusterToGlyphsMapReverse, const surface& s, const matrix_2d& m, extend e, filter f) {
	cairo_set_source_surface(_Context.get(), s.native_handle().csfce, 0.0, 0.0);
	auto pat = cairo_get_source(_Context.get());
	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(e));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(f));
	cairo_matrix_t cmat{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_pattern_set_matrix(pat, &cmat);
	vector<cairo_glyph_t> vec;
	for (const auto& glyph : glyphs) {
		vec.push_back({ glyph.index(), glyph.x(), glyph.y() });
	}
	const auto tcSize = _Container_size_to_int(clusters);
	unique_ptr<cairo_text_cluster_t, function<void(cairo_text_cluster_t*)>> sp_tc(cairo_text_cluster_allocate(tcSize), &cairo_text_cluster_free);
	auto tc_ptr = sp_tc.get();
	for (auto i = 0; i < tcSize; ++i) {
		tc_ptr[i].num_bytes = clusters[i].num_bytes();
		tc_ptr[i].num_glyphs = clusters[i].num_glyphs();
	}
	auto ctcf = static_cast<cairo_text_cluster_flags_t>(clusterToGlyphsMapReverse ? CAIRO_TEXT_CLUSTER_FLAG_BACKWARD : 0);
	cairo_show_text_glyphs(_Context.get(), utf8.data(), _Container_size_to_int(utf8), vec.data(), _Container_size_to_int(vec), sp_tc.get(), tcSize, ctcf);
	cairo_set_source_rgba(_Context.get(), 0.0, 0.0, 0.0, 0.0);
}

void surface::set_matrix(const matrix_2d& m) {
	cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_set_matrix(_Context.get(), &cm);
}

void surface::select_font_face(const string& family, font_slant slant, font_weight weight) {
	cairo_select_font_face(_Context.get(), family.c_str(), _Font_slant_to_cairo_font_slant_t(slant), _Font_weight_to_cairo_font_weight_t(weight));
}

void surface::set_font_size(double size) {
	cairo_set_font_size(_Context.get(), size);
}

void surface::set_font_matrix(const matrix_2d& m) {
	cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
	cairo_set_font_matrix(_Context.get(), &cm);
}

void surface::set_font_options(const font_options& options) {
	cairo_set_font_options(_Context.get(), options.native_handle());
}

void surface::set_font_face(const font_face& font_face) {
	cairo_set_font_face(_Context.get(), font_face.native_handle());
}

void surface::set_scaled_font(const scaled_font& scaled_font) {
	cairo_set_scaled_font(_Context.get(), scaled_font.native_handle());
}

path surface::get_path(const path_factory& pf) const {
	return path(pf, *this);
}

font_options surface::get_font_options(const font_options_factory& fo) const {
	return font_options(fo.get_antialias(), fo.get_subpixel_order());
}

pattern surface::get_pattern(const solid_color_pattern_factory& f) const {
	unique_ptr<cairo_pattern_t, function<void(cairo_pattern_t*)>> pat(cairo_pattern_create_rgba(f.get_red(), f.get_green(), f.get_blue(), f.get_alpha()), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));

	auto pttn = pattern(pat.get());
	pat.release();
	return pttn;
}

pattern surface::get_pattern(const linear_pattern_factory& f) const {
	point lpt0;
	point lpt1;
	f.get_linear_points(lpt0, lpt1);
	unique_ptr<cairo_pattern_t, function<void(cairo_pattern_t*)>> pat(cairo_pattern_create_linear(lpt0.x(), lpt0.y(), lpt1.x(), lpt1.y()), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));

	auto count = static_cast<unsigned int>(f.get_color_stop_count());
	for (unsigned int i = 0; i < count; i++) {
		double offset;
		rgba_color color;
		f.get_color_stop_rgba(i, offset, color);
		cairo_pattern_add_color_stop_rgba(pat.get(), offset, color.r(), color.g(), color.b(), color.a());
	}
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));

	auto pttn = pattern(pat.get());
	pat.release();
	return pttn;
}

pattern surface::get_pattern(const radial_pattern_factory& f) const {
	point center0, center1;
	double radius0, radius1;
	f.get_radial_circles(center0, radius0, center1, radius1);
	unique_ptr<cairo_pattern_t, function<void(cairo_pattern_t*)>> pat(cairo_pattern_create_radial(center0.x(), center0.y(), radius0, center1.x(), center1.y(), radius1), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));

	auto count = static_cast<unsigned int>(f.get_color_stop_count());
	for (unsigned int i = 0; i < count; i++) {
		double offset;
		rgba_color color;
		f.get_color_stop_rgba(i, offset, color);
		cairo_pattern_add_color_stop_rgba(pat.get(), offset, color.r(), color.g(), color.b(), color.a());
	}
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));

	auto pttn = pattern(pat.get());
	pat.release();
	return pttn;
}

pattern surface::get_pattern(const mesh_pattern_factory& f) const {
	unique_ptr<cairo_pattern_t, function<void(cairo_pattern_t*)>> upPat(cairo_pattern_create_mesh(), &cairo_pattern_destroy);
	auto pat = upPat.get();
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat));

	auto count = f.get_patch_count();
	for (auto patchNum = 0U; patchNum < count; patchNum++) {
		cairo_mesh_pattern_begin_patch(pat);
		auto pathFactory = f.get_path_factory(patchNum);
		const auto& pathData = pathFactory.get_data_ref();
		auto pdSize = pathData.size();
		for (unsigned int pdIndex = 0; pdIndex < pdSize; pdIndex++) {
			const auto& item = pathData[pdIndex];
			auto type = item->type();
			switch (type) {
			case std::experimental::io2d::path_data_type::move_to:
			{
				auto pt = dynamic_cast<move_to_path_data*>(item.get())->to();
				cairo_mesh_pattern_move_to(pat, pt.x(), pt.y());
			} break;
			case std::experimental::io2d::path_data_type::line_to:
			{
				auto pt = dynamic_cast<line_to_path_data*>(item.get())->to();
				cairo_mesh_pattern_line_to(pat, pt.x(), pt.y());
			} break;
			case std::experimental::io2d::path_data_type::curve_to:
			{
				auto dataItem = dynamic_cast<curve_to_path_data*>(item.get());
				cairo_mesh_pattern_curve_to(pat, dataItem->control_point_1().x(), dataItem->control_point_1().y(), dataItem->control_point_2().x(), dataItem->control_point_2().y(), dataItem->end_point().x(), dataItem->end_point().y());
			} break;
			case std::experimental::io2d::path_data_type::new_sub_path:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			} break;
			case std::experimental::io2d::path_data_type::close_path:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			} break;
			case std::experimental::io2d::path_data_type::rel_move_to:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			} break;
			case std::experimental::io2d::path_data_type::rel_line_to:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			} break;
			case std::experimental::io2d::path_data_type::rel_curve_to:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			} break;
			case std::experimental::io2d::path_data_type::arc:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			} break;
			case std::experimental::io2d::path_data_type::arc_negative:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			} break;
			case std::experimental::io2d::path_data_type::change_matrix:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			} break;
			case std::experimental::io2d::path_data_type::change_origin:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			} break;
			default:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			} break;
			}
		}

		for (auto pointNum = 0U; pointNum < 4U; pointNum++) {
			point pt;
			if (f.get_control_point(patchNum, pointNum, pt)) {
				cairo_mesh_pattern_set_control_point(pat, pointNum, pt.x(), pt.y());
			}
		}
		for (auto cornerNum = 0U; cornerNum < 4U; cornerNum++) {
			rgba_color color;
			if (f.get_corner_color_rgba(patchNum, cornerNum, color)) {
				cairo_mesh_pattern_set_corner_color_rgba(pat, cornerNum, color.r(), color.g(), color.b(), color.a());
			}
		}
		cairo_mesh_pattern_end_patch(pat);
	}
	auto pttn = pattern(pat);
	upPat.release(); // Release the pattern only after it has been safely transferred to pttn.
	return pttn;
}

pattern surface::get_pattern(surface_pattern_factory& f) const {
	auto patternSurface = _Surface_create_image_surface_copy(f._Surface);
	unique_ptr<cairo_pattern_t, function<void(cairo_pattern_t*)>> pat(cairo_pattern_create_for_surface(patternSurface.native_handle().csfce), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat.get()));

	auto pttn = pattern(pat.get());
	pat.release();
	return pttn;
}

pattern surface::get_pattern() const {
	return pattern(cairo_pattern_reference(cairo_get_source(_Context.get())));
}

content surface::get_content() const {
	return _Cairo_content_t_to_content(cairo_surface_get_content(_Surface.get()));
}

point surface::get_device_offset() const {
	double x, y;
	cairo_surface_get_device_offset(_Surface.get(), &x, &y);
	return point{ x, y };
}

bool surface::has_surface_resource() const {
	return _Surface != nullptr;
}

antialias surface::get_antialias() const {
	return _Cairo_antialias_t_to_antialias(cairo_get_antialias(_Context.get()));
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

fill_rule surface::get_fill_rule() const {
	return _Cairo_fill_rule_t_to_fill_rule(cairo_get_fill_rule(_Context.get()));
}

line_cap surface::get_line_cap() const {
	return _Cairo_line_cap_t_to_line_cap(cairo_get_line_cap(_Context.get()));
}

line_join surface::get_line_join() const {
	return _Line_join;
}

double surface::get_line_width() const {
	return cairo_get_line_width(_Context.get());
}

double surface::get_miter_limit() const {
	return _Miter_limit;
}

compositing_operator surface::get_compositing_operator() const {
	return _Cairo_operator_t_to_compositing_operator(cairo_get_operator(_Context.get()));
}

double surface::get_tolerance() const {
	return cairo_get_tolerance(_Context.get());
}

rectangle surface::get_clip_extents() const {
	double pt0x, pt0y, pt1x, pt1y;
	cairo_clip_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
	return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
}

bool surface::in_clip(const point& pt) const {
	return cairo_in_clip(_Context.get(), pt.x(), pt.y()) != 0;
}

vector<rectangle> surface::get_clip_rectangles() const {
	vector<rectangle> results;
	unique_ptr<cairo_rectangle_list_t, function<void(cairo_rectangle_list_t*)>> sp_rects(cairo_copy_clip_rectangle_list(_Context.get()), &cairo_rectangle_list_destroy);
	_Throw_if_failed_cairo_status_t(sp_rects->status);
	for (auto i = 0; i < sp_rects->num_rectangles; ++i) {
		results.push_back({ sp_rects->rectangles[i].x, sp_rects->rectangles[i].y, sp_rects->rectangles[i].width, sp_rects->rectangles[i].height });
	}

	return results;
}

rectangle surface::get_fill_extents() const {
	double pt0x, pt0y, pt1x, pt1y;
	cairo_fill_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
	return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
}

rectangle surface::get_fill_extents_immediate() const {
	throw runtime_error("Not implemented.");
	//double pt0x, pt0y, pt1x, pt1y;
	//cairo_fill_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
	//return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
}

bool surface::in_fill(const point& pt) const {
	return cairo_in_fill(_Context.get(), pt.x(), pt.y()) != 0;
}

bool surface::in_fill_immediate(const point& pt) const {
	throw runtime_error("Not implemented.");
	//return cairo_in_fill(_Context.get(), pt.x(), pt.y()) != 0;
}

rectangle surface::get_stroke_extents() const {
	double pt0x, pt0y, pt1x, pt1y;
	cairo_stroke_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
	return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
}

rectangle surface::get_stroke_extents_immediate() const {
	throw runtime_error("Not implemented.");
	//auto currPath = _Current_path;
	//set_path(get_path(_Immediate_path));
	//double pt0x, pt0y, pt1x, pt1y;
	//cairo_stroke_extents(_Context.get(), &pt0x, &pt0y, &pt1x, &pt1y);
	//set_path(currPath);
	//return{ min(pt0x, pt1x), min(pt0y, pt1y), max(pt0x, pt1x) - min(pt0x, pt1x), max(pt0y, pt1y) - min(pt0y, pt1y) };
}

bool surface::in_stroke(const point& pt) const {
	return cairo_in_stroke(_Context.get(), pt.x(), pt.y()) != 0;
}

bool surface::in_stroke_immediate(const point& pt) const {
	throw runtime_error("Not implemented.");
}

font_extents surface::get_font_extents() const {
	font_extents result;
	cairo_font_extents_t cfe{ };
	cairo_font_extents(_Context.get(), &cfe);
	result.ascent(cfe.ascent);
	result.descent(cfe.descent);
	result.height(cfe.height);
	result.max_x_advance(cfe.max_x_advance);
	result.max_y_advance(cfe.max_y_advance);
	return result;
}

text_extents surface::get_text_extents(const string& utf8) const {
	text_extents result;
	cairo_text_extents_t cte{ };
	cairo_text_extents(_Context.get(), utf8.c_str(), &cte);
	result.height(cte.height);
	result.width(cte.width);
	result.x_advance(cte.x_advance);
	result.x_bearing(cte.x_bearing);
	result.y_advance(cte.y_advance);
	result.y_bearing(cte.y_bearing);
	return result;
}

text_extents surface::get_glyph_extents(const vector<glyph>& glyphs) const {
	vector<cairo_glyph_t> vec;
	for (const auto& glyph : glyphs) {
		vec.push_back({ glyph.index(), glyph.x(), glyph.y() });
	}
	text_extents result;
	cairo_text_extents_t cfe{ };
	cairo_glyph_extents(_Context.get(), vec.data(), _Container_size_to_int(vec), &cfe);
	result.height(cfe.height);
	result.width(cfe.width);
	result.x_advance(cfe.x_advance);
	result.x_bearing(cfe.x_bearing);
	result.y_advance(cfe.y_advance);
	result.y_bearing(cfe.y_bearing);
	return result;
}

matrix_2d surface::get_matrix() const {
	cairo_matrix_t cm{ };
	cairo_get_matrix(_Context.get(), &cm);
	return{ cm.xx, cm.yx, cm.xy, cm.yy, cm.x0, cm.y0 };
}

point surface::user_to_device() const {
	double x, y;
	cairo_user_to_device(_Context.get(), &x, &y);
	return point{ x, y };
}

point surface::user_to_device_distance() const {
	double x, y;
	cairo_user_to_device_distance(_Context.get(), &x, &y);
	return point{ x, y };
}

point surface::device_to_user() const {
	double x, y;
	cairo_device_to_user(_Context.get(), &x, &y);
	return point{ x, y };
}

point surface::device_to_user_distance() const {
	double x, y;
	cairo_device_to_user_distance(_Context.get(), &x, &y);
	return point{ x, y };
}

matrix_2d surface::get_font_matrix() const {
	cairo_matrix_t cm{ };
	cairo_get_font_matrix(_Context.get(), &cm);
	return{ cm.xx, cm.yx, cm.xy, cm.yy, cm.x0, cm.y0 };
}

// Note: This deviates from cairo in that we return the values that will actually wind up being used.
font_options surface::get_font_options() const {
	font_options fo(antialias::default_antialias, subpixel_order::default_subpixel_order);
	cairo_get_font_options(_Context.get(), fo.native_handle());
	auto ca = fo.get_antialias();
	auto cso = fo.get_subpixel_order();
	cairo_surface_get_font_options(_Surface.get(), fo.native_handle());

	return font_options(
		(ca == antialias::default_antialias) ? fo.get_antialias() : ca,
		(cso == subpixel_order::default_subpixel_order) ? fo.get_subpixel_order() : cso
		);
}

font_face surface::get_font_face() const {
	auto ff = cairo_get_font_face(_Context.get());
	_Throw_if_failed_cairo_status_t(cairo_font_face_status(ff));
	// Cairo doesn't increase the font face's reference count when you call cairo_get_font_face so we do it manually.
	return font_face(cairo_font_face_reference(ff));
}

scaled_font surface::get_scaled_font() const {
	auto sf = cairo_get_scaled_font(_Context.get());
	_Throw_if_failed_cairo_status_t(cairo_scaled_font_status(sf));
	// Cairo doesn't increase the scaled font's reference count when you call cairo_get_scaled_font so we do it manually.
	return scaled_font(cairo_scaled_font_reference(sf));
}

