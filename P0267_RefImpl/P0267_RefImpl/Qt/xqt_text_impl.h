#pragma once

#ifndef _XQT_TEXT_IMPL_H_
#define _XQT_TEXT_IMPL_H_

#include "xqt_headers.h"
#include <cassert>
#include "xpath.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <system_error>
#include <cstring>
#include <chrono>

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Qt_io2d {
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::draw_text(image_surface_data_type& data, const basic_point_2d<GraphicsMath>& pt, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& font, const string& text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) {
				QPainter painter(&data.surface);
				_Set_render_props(painter, rp);
				_Set_clip_props(painter, cl);
				//QBrush& brush = *(b.data().brush);
				//_Set_brush_props(brush, bp);
				_Set_brush_props(painter, b, bp);
				_Set_draw_text_stroke_props(painter, b, sp, sp.max_miter_limit(), d);
				painter.setBrush(b.data().brush);
				QPen pen(b.data().brush, static_cast<qreal>(sp.line_width()));
				painter.setPen(pen);
				//_Set_text_props(painter, font, tp);
				QFont qtFont = font.data().font;
				auto oldStyleStrategy = qtFont.styleStrategy();
				if (tp.antialiasing() == font_antialias::none) {
					qtFont.setStyleStrategy(static_cast<QFont::StyleStrategy>(oldStyleStrategy | QFont::NoAntialias));
				}
				else {
					qtFont.setStyleStrategy(static_cast<QFont::StyleStrategy>(oldStyleStrategy & (~(QFont::NoAntialias))));
				}
				if (tp.font_size() > 0) {
					switch (tp.size_units())
					{
					case font_size_units::pixels:
					{
						qtFont.setPixelSize(static_cast<int>(tp.font_size() + 0.5f));
					} break;
					case font_size_units::points:
					{
						qtFont.setPointSizeF(tp.font_size());
					} break;
					default:
						throw runtime_error("Unexpected font_size_units value.");
					}
				}
				else {
					switch (font.size_units())
					{
					case font_size_units::pixels:
					{
						qtFont.setPixelSize(static_cast<int>(font.font_size() + 0.5f));
					} break;
					case font_size_units::points:
					{
						qtFont.setPointSizeF(font.font_size());
					} break;
					default:
						throw runtime_error("Unexpected font_size_units value.");
					}
				}

				qtFont.setKerning(tp.kerning());
				qtFont.setStrikeOut(tp.strike_through());
				font_line fl = tp.line();
				switch (fl)
				{
				case std::experimental::io2d::v1::font_line::none:
				{
					qtFont.setUnderline(false);
				} break;
				case std::experimental::io2d::v1::font_line::underline:
				{
					qtFont.setUnderline(true);
				} break;
				default:
					throw runtime_error("Unexpected font_size_units value.");
				}
				qtFont.setStretch(_Font_stretching_to_qfont_stretch(tp.stretching()));
				painter.setFont(font.data().font);
				auto qstringText = QString(text.c_str());
				painter.drawText(QPoint(static_cast<int>(pt.x()), static_cast<int>(pt.y())), qstringText);
				qtFont.setStyleStrategy(oldStyleStrategy);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::draw_text(image_surface_data_type& data, const basic_bounding_box<GraphicsMath>& bb, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& font, const string& text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) {
				QPainter painter(&data.surface);
				_Set_render_props(painter, rp);
				_Set_clip_props(painter, cl);
				//QBrush& brush = *(b.data().brush);
				//_Set_brush_props(brush, bp);
				_Set_brush_props(painter, b, bp);
				_Set_draw_text_stroke_props(painter, b, sp, sp.max_miter_limit(), d);
				painter.setBrush(b.data().brush);
				QPen pen(b.data().brush, static_cast<qreal>(sp.line_width()));
				painter.setPen(pen);
				//_Set_text_props(painter, font, tp);
				QFont qtFont = font.data().font;
				auto oldStyleStrategy = qtFont.styleStrategy();
				auto oldRenderHints = painter.renderHints();
				if (tp.antialiasing() == font_antialias::none) {
					painter.setRenderHints(static_cast<QPainter::RenderHints>(oldRenderHints & (~(QPainter::TextAntialiasing))));
					qtFont.setStyleStrategy(static_cast<QFont::StyleStrategy>(oldStyleStrategy | QFont::NoAntialias));
				}
				else {
					painter.setRenderHints(static_cast<QPainter::RenderHints>(oldRenderHints | QPainter::TextAntialiasing));
					qtFont.setStyleStrategy(static_cast<QFont::StyleStrategy>(oldStyleStrategy & (~(QFont::NoAntialias))));
				}
				if (tp.font_size() > 0) {
					switch (tp.size_units())
					{
					case font_size_units::pixels:
					{
						qtFont.setPixelSize(static_cast<int>(tp.font_size() + 0.5f));
					} break;
					case font_size_units::points:
					{
						qtFont.setPointSizeF(tp.font_size());
					} break;
					default:
						throw runtime_error("Unexpected font_size_units value.");
					}
				}
				else {
					switch (font.size_units())
					{
					case font_size_units::pixels:
					{
						qtFont.setPixelSize(static_cast<int>(font.font_size() + 0.5f));
					} break;
					case font_size_units::points:
					{
						qtFont.setPointSizeF(font.font_size());
					} break;
					default:
						throw runtime_error("Unexpected font_size_units value.");
					}
				}

				qtFont.setKerning(tp.kerning());
				qtFont.setStrikeOut(tp.strike_through());
				font_line fl = tp.line();
				switch (fl)
				{
				case std::experimental::io2d::v1::font_line::none:
				{
					qtFont.setUnderline(false);
				} break;
				case std::experimental::io2d::v1::font_line::underline:
				{
					qtFont.setUnderline(true);
				} break;
				default:
					throw runtime_error("Unexpected font_size_units value.");
				}
				qtFont.setStretch(_Font_stretching_to_qfont_stretch(tp.stretching()));
				painter.setFont(font.data().font);
				auto qstringText = QString(text.c_str());
				painter.drawText(QRectF(bb.x(), bb.y(), bb.width(), bb.height()), qstringText);
				qtFont.setStyleStrategy(oldStyleStrategy);
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::draw_text(unmanaged_output_surface_data_type& /*data*/, const basic_point_2d<GraphicsMath>& /*pt*/, const basic_brush<graphics_surfaces_type>& /*b*/, const basic_font<graphics_surfaces_type>& /*font*/, const string& /*text*/, const basic_text_props<graphics_surfaces_type>& /*tp*/, const basic_brush_props<graphics_surfaces_type>& /*bp*/, const basic_stroke_props<graphics_surfaces_type>& /*sp*/, const basic_dashes<graphics_surfaces_type>& /*d*/, const basic_render_props<graphics_surfaces_type>& /*rp*/, const basic_clip_props<graphics_surfaces_type>& /*cl*/) {
				throw ::std::system_error(make_error_code(errc::not_supported), "draw_text is not yet implemented.");
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::surfaces::draw_text(unmanaged_output_surface_data_type& /*data*/, const basic_bounding_box<GraphicsMath>& /*bb*/, const basic_brush<graphics_surfaces_type>& /*b*/, const basic_font<graphics_surfaces_type>& /*font*/, const string& /*text*/, const basic_text_props<graphics_surfaces_type>& /*tp*/, const basic_brush_props<graphics_surfaces_type>& /*bp*/, const basic_stroke_props<graphics_surfaces_type>& /*sp*/, const basic_dashes<graphics_surfaces_type>& /*d*/, const basic_render_props<graphics_surfaces_type>& /*rp*/, const basic_clip_props<graphics_surfaces_type>& /*cl*/) {
				throw ::std::system_error(make_error_code(errc::not_supported), "draw_text is not yet implemented.");
			}

			// font

			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::text::font_data_type _Qt_graphics_surfaces<GraphicsMath>::text::create_font(string name, font_size_units fsu, float size, generic_font_names gfn, io2d::font_weight fw, font_style fs, bool merging) {
				font_data_type result;
				result.fsu = fsu;
				result.fontsize = size;
				result.fw = fw;
				result.fs = fs;
				result.merging = merging;
				QString qtFamilyName(name.c_str());
				result.font = QFont(qtFamilyName, size, _Font_weight_to_qfont_weight(fw), (fs == font_style::normal ? false : true));
				result.font.setStyle(_Font_style_to_qfont_style(fs));
				if (!merging) {
					result.font.setStyleStrategy(QFont::NoFontMerging);
				}
				result.font.setStyleHint(_Generic_font_names_to_qfont_stylehint(gfn));
				QFontInfo fontInfo(result.font);
				result.family = fontInfo.family().toStdString();
				return result;
			}
			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::text::font_data_type _Qt_graphics_surfaces<GraphicsMath>::text::create_font(::std::filesystem::path file, font_size_units fsu, float size, io2d::font_weight fw, font_style fs, bool merging) {
				font_data_type result;
				result.fsu = fsu;
				result.fontsize = size;
				result.fw = fw;
				result.fs = fs;
				result.merging = merging;
				int fontId = QFontDatabase::addApplicationFont(file.u8string().c_str());
				// Pull in the first family in the font; TODO: change the API so that it also take a family name since font files can contain multiple families; if null then it'd just use the first familyname.
				auto qtFamilyName = QFontDatabase::applicationFontFamilies(fontId).at(0);
				result.font = QFont(qtFamilyName, size, _Font_weight_to_qfont_weight(fw), (fs == font_style::normal ? false : true));
				result.font.setStyle(_Font_style_to_qfont_style(fs));
				if (!merging) {
					result.font.setStyleStrategy(QFont::NoFontMerging);
				}
				QFontInfo fontInfo(result.font);
				result.family = fontInfo.family().toStdString();
				return result;
			}
			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::text::font_data_type _Qt_graphics_surfaces<GraphicsMath>::text::create_font(generic_font_names gfn, font_size_units fsu, float size, font_weight fw, font_style fs) {
				font_data_type result;
				result.fsu = fsu;
				result.fontsize = size;
				result.fw = fw;
				result.fs = fs;
				result.merging = true;
				result.font = QFont();// qtFamilyName, size, _Font_weight_to_qfont_weight(fw), (fs == font_style::normal ? false : true));
				result.font.setWeight(_Font_weight_to_qfont_weight(fw));
				result.font.setStyle(_Font_style_to_qfont_style(fs));
				result.font.setStyleHint(_Generic_font_names_to_qfont_stylehint(gfn));
				QFontInfo fontInfo(result.font);
				result.family = fontInfo.family().toStdString();
				return result;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::text::font_size(font_data_type& data, font_size_units fsu, float size) {
				data.fsu = fsu;
				data.fontsize = size;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::text::merging(font_data_type& data, bool m) {
				data.merging = m;
				auto styleStrategy = data.font.styleStrategy();
				if (!m) {
					data.font.setStyleStrategy(styleStrategy | QFont::NoFontMerging);
				}
				else {
					styleStrategy = styleStrategy & (~(QFont::NoFontMerging));
					data.font.setStyleStrategy(styleStrategy);
				}
			}
			template<class GraphicsMath>
			inline float _Qt_graphics_surfaces<GraphicsMath>::text::font_size(const font_data_type& data) {
				return data.fontsize;
			}
			template<class GraphicsMath>
			inline ::std::string _Qt_graphics_surfaces<GraphicsMath>::text::family(const font_data_type& data) {
				return data.family;
			}
			template<class GraphicsMath>
			inline font_size_units _Qt_graphics_surfaces<GraphicsMath>::text::size_units(const font_data_type& data) {
				return data.fsu;
			}
			template<class GraphicsMath>
			inline font_weight _Qt_graphics_surfaces<GraphicsMath>::text::weight(const font_data_type& data) {
				return data.fw;
			}
			template<class GraphicsMath>
			inline font_style _Qt_graphics_surfaces<GraphicsMath>::text::style(const font_data_type& data) {
				return data.fs;
			}
			template<class GraphicsMath>
			inline bool _Qt_graphics_surfaces<GraphicsMath>::text::merging(const font_data_type& data) {
				return data.merging;
			}

			// text_props
			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::text::text_props_data_type _Qt_graphics_surfaces<GraphicsMath>::text::create_text_props(float scl, font_size_units fsu, float fontsize, bool kern, font_antialias aa, font_stretching stretch, bool strike_through, font_line fl) noexcept {
				text_props_data_type result;
				result.scale = scl;
				result.fsu = fsu;
				result.fontsize = fontsize;
				result.kern = kern;
				result.aa = aa;
				result.stretch = stretch;
				result.strike_through = strike_through;
				result.fl = fl;
				return result;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::text::scale(text_props_data_type& data, float scl) noexcept {
				data.scale = scl;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::text::font_size(text_props_data_type& data, font_size_units fsu, float sz) noexcept {
				data.fsu = fsu;
				data.fontsize = sz;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::text::kerning(text_props_data_type& data, bool k) noexcept {
				data.kern = k;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::text::antialiasing(text_props_data_type& data, font_antialias aa) noexcept {
				data.aa = aa;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::text::stretching(text_props_data_type& data, font_stretching fs) noexcept {
				data.stretch = fs;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::text::strike_through(text_props_data_type& data, bool st) noexcept {
				data.strike_through = st;
			}
			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::text::line(text_props_data_type& data, font_line fl) noexcept {
				data.fl = fl;
			}
			template<class GraphicsMath>
			inline float _Qt_graphics_surfaces<GraphicsMath>::text::scale(const text_props_data_type& data) noexcept {
				return data.scale;
			}
			template<class GraphicsMath>
			inline float _Qt_graphics_surfaces<GraphicsMath>::text::font_size(const text_props_data_type& data) noexcept {
				return data.fontsize;
			}
			template<class GraphicsMath>
			inline font_size_units _Qt_graphics_surfaces<GraphicsMath>::text::size_units(const text_props_data_type& data) noexcept {
				return data.fsu;
			}
			template<class GraphicsMath>
			inline bool _Qt_graphics_surfaces<GraphicsMath>::text::kerning(const text_props_data_type& data) noexcept {
				return data.kern;
			}
			template<class GraphicsMath>
			inline font_antialias _Qt_graphics_surfaces<GraphicsMath>::text::antialiasing(const text_props_data_type& data) noexcept {
				return data.aa;
			}
			template<class GraphicsMath>
			inline font_stretching _Qt_graphics_surfaces<GraphicsMath>::text::stretching(const text_props_data_type& data) noexcept {
				return data.stretch;
			}
			template<class GraphicsMath>
			inline bool _Qt_graphics_surfaces<GraphicsMath>::text::strike_through(const text_props_data_type& data) noexcept {
				return data.strike_through;
			}
			template<class GraphicsMath>
			inline font_line _Qt_graphics_surfaces<GraphicsMath>::text::line(const text_props_data_type& data) noexcept {
				return data.fl;
			}
		}
	}
}

#endif
