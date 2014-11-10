#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

scaled_font::native_handle_type scaled_font::native_handle() const {
	return _Scaled_font.get();
}

scaled_font::scaled_font(scaled_font&& other) {
	_Scaled_font = move(other._Scaled_font);
	other._Scaled_font = nullptr;
}

scaled_font& scaled_font::operator=(scaled_font&& other) {
	if (this != &other) {
		_Scaled_font = move(other._Scaled_font);
		other._Scaled_font = nullptr;
	}
	return *this;
}

scaled_font::scaled_font(scaled_font::native_handle_type nh) {
	_Scaled_font = shared_ptr<cairo_scaled_font_t>(nh, &cairo_scaled_font_destroy);
}

scaled_font::scaled_font(const font_face& ff, const matrix_2d& fm, const matrix_2d& ctm, const font_options& fo)
: _Scaled_font(nullptr) {
	cairo_matrix_t c_fm{ fm.m00(), fm.m01(), fm.m10(), fm.m11(), fm.m20(), fm.m21() },
		c_ctm{ ctm.m00(), ctm.m01(), ctm.m10(), ctm.m11(), ctm.m20(), ctm.m21() };
	_Scaled_font = shared_ptr<cairo_scaled_font_t>(cairo_scaled_font_create(ff.native_handle(), &c_fm, &c_ctm, fo.native_handle()), &cairo_scaled_font_destroy);
}

font_extents scaled_font::get_extents() const {
	cairo_font_extents_t c_fe{ };
	cairo_scaled_font_extents(_Scaled_font.get(), &c_fe);
	return{ c_fe.ascent, c_fe.descent, c_fe.height, c_fe.max_x_advance, c_fe.max_y_advance };
}

text_extents scaled_font::get_text_extents(const string& utf8) const {
	cairo_text_extents_t c_te{ };
	cairo_scaled_font_text_extents(_Scaled_font.get(), utf8.c_str(), &c_te);
	return{ c_te.x_bearing, c_te.y_bearing, c_te.width, c_te.height, c_te.x_advance, c_te.y_advance };
}

text_extents scaled_font::get_glyph_extents(const vector<glyph>& glyphs) const {
	cairo_text_extents_t c_te{ };
	vector<cairo_glyph_t> c_vecg;
	c_vecg.reserve(glyphs.size());
	for (const auto& g : glyphs) {
		c_vecg.push_back({ g.index, g.x, g.y });
	}
	cairo_scaled_font_glyph_extents(_Scaled_font.get(), c_vecg.data(), static_cast<int>(c_vecg.size()), &c_te);
	return{ c_te.x_bearing, c_te.y_bearing, c_te.width, c_te.height, c_te.x_advance, c_te.y_advance };
}

vector<glyph> scaled_font::text_to_glyphs(double x, double y, const string& utf8) const {
	vector<glyph> result;
	cairo_glyph_t* c_glyphs = nullptr;
	int num_glyphs;
	try {
		_Throw_if_failed_cairo_status_t(
			cairo_scaled_font_text_to_glyphs(_Scaled_font.get(), x, y, utf8.c_str(), static_cast<int>(utf8.size()), &c_glyphs, &num_glyphs, nullptr, nullptr, nullptr));
		for (int i = 0; i < num_glyphs; i++) {
			result.push_back({ c_glyphs[i].index, c_glyphs[i].x, c_glyphs[i].y });
		}
	}
	catch (...) {
		if (c_glyphs != nullptr) {
			cairo_glyph_free(c_glyphs);
			c_glyphs = nullptr;
		}
		throw;
	}
	if (c_glyphs != nullptr) {
		cairo_glyph_free(c_glyphs);
		c_glyphs = nullptr;
	}
	return result;
}

vector<glyph> scaled_font::text_to_glyphs(double x, double y, const string& utf8, vector<text_cluster>& clusters, bool& clusterToGlyphsMapReverse) const {
	vector<glyph> result;
	cairo_glyph_t* c_glyphs = nullptr;
	int num_glyphs;
	cairo_text_cluster_t* c_clusters = nullptr;
	int num_clusters;
	cairo_text_cluster_flags_t c_clFlags;
	try {
		_Throw_if_failed_cairo_status_t(
			cairo_scaled_font_text_to_glyphs(_Scaled_font.get(), x, y, utf8.c_str(), static_cast<int>(utf8.size()), &c_glyphs, &num_glyphs, &c_clusters, &num_clusters, &c_clFlags));
		for (int i = 0; i < num_glyphs; i++) {
			result.push_back({ c_glyphs[i].index, c_glyphs[i].x, c_glyphs[i].y });
		}
		for (int i = 0; i < num_clusters; i++) {
			clusters.push_back({ c_clusters[i].num_bytes, c_clusters[i].num_glyphs });
		}
		clusterToGlyphsMapReverse = (c_clFlags & CAIRO_TEXT_CLUSTER_FLAG_BACKWARD) != 0;
	}
	catch (...) {
		if (c_glyphs != nullptr) {
			cairo_glyph_free(c_glyphs);
			c_glyphs = nullptr;
		}
		if (c_clusters != nullptr) {
			cairo_text_cluster_free(c_clusters);
			c_clusters = nullptr;
		}
		throw;
	}
	if (c_glyphs != nullptr) {
		cairo_glyph_free(c_glyphs);
		c_glyphs = nullptr;
	}
	if (c_clusters != nullptr) {
		cairo_text_cluster_free(c_clusters);
		c_clusters = nullptr;
	}
	return result;
}
