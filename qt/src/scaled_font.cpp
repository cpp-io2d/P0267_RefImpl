#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

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
	_Scaled_font = shared_ptr<QFont>(new QFont(*nh));
}

scaled_font::scaled_font(const font_face& ff, const matrix& fm, const matrix& ctm, const font_options& fo)
: _Scaled_font(nullptr) {
//	cairo_matrix_t c_fm{ fm.xx, fm.xy, fm.yx, fm.yy, fm.x0, fm.y0 },
//		c_ctm{ ctm.xx, ctm.xy, ctm.yx, ctm.yy, ctm.x0, ctm.y0 };
//	_Scaled_font = shared_ptr<cairo_scaled_font_t>(cairo_scaled_font_create(ff.native_handle(), &c_fm, &c_ctm, fo.native_handle()), &cairo_scaled_font_destroy);
	_Scaled_font = shared_ptr<QFont>(new QFont(*ff.native_handle()));
	_Scaled_font->setHintingPreference(fo.native_handle()->hintingPreference);
	_Scaled_font->setStyleStrategy(fo.native_handle()->styleStrategy);
}

font_extents scaled_font::get_extents() const {
	// TODO: find values for max_x_advance and max_y_advance
	QFontMetrics metrics(*_Scaled_font);
	return{ metrics.ascent(), metrics.descent(), metrics.height(), 0, 0 };
}

text_extents scaled_font::get_text_extents(const string& utf8) const {
	// TODO: find values for x_bearing, y_bearing, x_advance and y_advance
	QFontMetrics metrics(*_Scaled_font);
	QRect bounding = metrics.boundingRect(QString::fromUtf8(utf8.c_str()));

	return{ 0, 0, bounding.width(), bounding.height(), 0, 0 };
}

text_extents scaled_font::get_glyph_extents(const vector<glyph>& /*glyphs*/) const {
	// TODO: implement this
	return{ 0, 0, 0, 0, 0, 0 };
}

vector<glyph> scaled_font::text_to_glyphs(double /*x*/, double /*y*/, const string& utf8) const {
	QRawFont rawFont = QRawFont::fromFont(*_Scaled_font);
	auto indexVector = rawFont.glyphIndexesForString(QString::fromUtf8(utf8.c_str()));

	vector<glyph> result;
	for (const auto& index : indexVector)
	{
		// TODO: what to put for glyph.x and glyph.y?
		result.push_back({index, 0, 0 });
	}

	return result;
}

vector<glyph> scaled_font::text_to_glyphs(double /*x*/, double /*y*/, const string& /*utf8*/,
										  vector<text_cluster>& /*clusters*/, text_cluster_flags::text_cluster_flags& /*clFlags*/) const {
	// TODO: implement
	vector<glyph> result;
	return result;
}
