#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

glyph_run::glyph::glyph(glyph_run::glyph::index_type i, double x, double y) noexcept
	: _Index(i)
	, _X(x)
	, _Y(y)
	, _Native_glyph(nullptr) {
}

void glyph_run::glyph::index(index_type i) noexcept {
	_Index = i;
	if (_Native_glyph != nullptr) {
		(*_Native_glyph).index = i;
	}
}

void glyph_run::glyph::x(double val) noexcept {
	_X = val;
	if (_Native_glyph != nullptr) {
		(*_Native_glyph).x = val;
	}
}

void glyph_run::glyph::y(double val) noexcept {
	_Y = val;
	if (_Native_glyph != nullptr) {
		(*_Native_glyph).y = val;
	}
}

glyph_run::glyph::index_type glyph_run::glyph::index() const noexcept {
	return _Index;
}

double glyph_run::glyph::x() const noexcept {
	return _X;
}

double glyph_run::glyph::y() const noexcept {
	return _Y;
}

glyph_run::cluster::cluster(int glyphs, int bytes) noexcept
	: _Glyph_count(glyphs)
	, _Byte_count(bytes)
	, _Native_cluster(nullptr) {
}

void glyph_run::cluster::glyph_count(int count) noexcept {
	_Glyph_count = count;
	if (_Native_cluster != nullptr) {
		(*_Native_cluster).num_glyphs = count;
	}
}

void glyph_run::cluster::byte_count(int count) noexcept {
	_Byte_count = count;
	if (_Native_cluster != nullptr) {
		(*_Native_cluster).num_bytes = count;
	}
}

int glyph_run::cluster::glyph_count() const noexcept {
	return _Glyph_count;
}

int glyph_run::cluster::byte_count() const noexcept {
	return _Byte_count;
}

glyph_run::glyph_run(const experimental::io2d::font_resource& fr, const ::std::string& utf8, const vector_2d& pos)
	: _Text_string(utf8)
	, _Font_resource(fr)
	, _Glyphs()
	, _Clusters()
	, _Cairo_glyphs()
	, _Cairo_text_clusters()
	, _Position(pos)
	, _Text_cluster_flags() {
	//unique_ptr<cairo_glyph_t, decltype(&cairo_glyph_free)> upcgt(nullptr, &cairo_glyph_free);
	//unique_ptr<cairo_text_cluster_t, decltype(&cairo_text_cluster_free)> upctc(nullptr, &cairo_text_cluster_free);

	cairo_glyph_t* cgt = nullptr;
	int cgtCount = 0;
	cairo_text_cluster_t* ctc = nullptr;
	int ctcCount = 0;
	auto status = cairo_scaled_font_text_to_glyphs(fr._Scaled_font.get(), pos.x(), pos.y(), utf8.c_str(), -1, &cgt, &cgtCount, &ctc, &ctcCount, &_Text_cluster_flags);
	//upcgt.reset(cgt);
	//upctc.reset(ctc);
	try {
		_Cairo_glyphs.reset(cgt, &cairo_glyph_free);
	}
	catch (...) {
		cairo_text_cluster_free(ctc);
		throw;
	}

	_Cairo_text_clusters.reset(ctc, &cairo_text_cluster_free);

	//if (status != CAIRO_STATUS_SUCCESS) {
	//	if (cgt != nullptr) {
	//		cairo_glyph_free(cgt);
	//	}
	//	if (ctc != nullptr) {
	//		cairo_text_cluster_free(ctc);
	//	}
	//	_Throw_if_failed_cairo_status_t(status);
	//}

	_Throw_if_failed_cairo_status_t(status);

	_Glyphs.reserve(static_cast<vector<glyph>::size_type>(cgtCount));

	_Clusters.reserve(static_cast<vector<cluster>::size_type>(ctcCount));

	for (int i = 0; i < cgtCount; ++i) {
		const auto& val = cgt[i];
		_Glyphs.emplace_back(static_cast<glyph::index_type>(val.index), val.x, val.y);
		_Glyphs.rbegin()->_Native_glyph = cgt + i;//&(cgt[i]);
	}

	for (int i = 0; i < ctcCount; ++i) {
		const auto& val = ctc[i];
		_Clusters.emplace_back(val.num_glyphs, val.num_bytes);
		_Clusters.rbegin()->_Native_cluster = ctc + i;
	}
}

vector<glyph_run::glyph>& glyph_run::glyphs() noexcept {
	return _Glyphs;
}

vector<glyph_run::cluster>& glyph_run::clusters() noexcept {
	return _Clusters;
}

const string& glyph_run::original_text() const noexcept {
	return _Text_string;
}

const vector<glyph_run::glyph>& glyph_run::glyphs() const noexcept {
	return _Glyphs;
}

const vector<glyph_run::cluster>& glyph_run::clusters() const noexcept {
	return _Clusters;
}

const experimental::io2d::font_resource& glyph_run::font_resource() const noexcept {
	return _Font_resource;
}

bool glyph_run::reversed_clusters() const noexcept {
	return (_Text_cluster_flags & CAIRO_TEXT_CLUSTER_FLAG_BACKWARD) != 0;
}

vector_2d glyph_run::position() const noexcept {
	return _Position;
}

text_extents glyph_run::extents() const noexcept {
	cairo_text_extents_t cte{};
	cairo_scaled_font_glyph_extents(_Font_resource._Scaled_font.get(), _Cairo_glyphs.get(), static_cast<int>(_Glyphs.size()), &cte);
	return text_extents(cte.x_bearing, cte.y_bearing, cte.width, cte.height, cte.x_advance, cte.y_advance);
}
