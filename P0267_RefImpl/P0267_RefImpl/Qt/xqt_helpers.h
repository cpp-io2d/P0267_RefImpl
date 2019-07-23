#pragma once

#include "xio2d.h"
#include "xqt_headers.h"
#include <cassert>

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Qt_io2d {
			inline QFont::Weight _Font_weight_to_qfont_weight(::std::experimental::io2d::font_weight fw) {
				switch (fw)
				{
				case std::experimental::io2d::v1::font_weight::thin:
					return QFont::Thin;
				case std::experimental::io2d::v1::font_weight::extra_light:
					return QFont::ExtraLight;
				case std::experimental::io2d::v1::font_weight::light:
					return QFont::Light;
				case std::experimental::io2d::v1::font_weight::normal:
					return QFont::Normal;
				case std::experimental::io2d::v1::font_weight::medium:
					return QFont::Medium;
				case std::experimental::io2d::v1::font_weight::semi_bold:
					return QFont::DemiBold;
				case std::experimental::io2d::v1::font_weight::bold:
					return QFont::Bold;
				case std::experimental::io2d::v1::font_weight::extra_bold:
					return QFont::ExtraBold;
				case std::experimental::io2d::v1::font_weight::black:
					return QFont::Black;
				default:
					throw ::std::runtime_error("Unknown font_weight value");
				}
			}

			inline QFont::Style _Font_style_to_qfont_style(::std::experimental::io2d::font_style fs) {
				switch (fs)
				{
				case std::experimental::io2d::v1::font_style::normal:
					return QFont::StyleNormal;
				case std::experimental::io2d::v1::font_style::italic:
					return QFont::StyleItalic;
				case std::experimental::io2d::v1::font_style::oblique:
					return QFont::StyleOblique;
				default:
					throw ::std::runtime_error("Unknown font_style value");
				}
			}

			inline QFont::StyleHint _Generic_font_names_to_qfont_stylehint(::std::experimental::io2d::generic_font_names gfn) {
				switch (gfn)
				{
				case std::experimental::io2d::v1::generic_font_names::serif:
					return QFont::Serif;
				case std::experimental::io2d::v1::generic_font_names::sans_serif:
					return QFont::SansSerif;
				case std::experimental::io2d::v1::generic_font_names::cursive:
					return QFont::Cursive;
				case std::experimental::io2d::v1::generic_font_names::fantasy:
					return QFont::Fantasy;
				case std::experimental::io2d::v1::generic_font_names::monospace:
					return QFont::Monospace;
				default:
					throw ::std::runtime_error("Unknown generic_font_names value");
				}
			}

			inline QFont::Stretch _Font_stretching_to_qfont_stretch(::std::experimental::io2d::font_stretching fs) {
				switch (fs)
				{
				case std::experimental::io2d::v1::font_stretching::ultra_condensed:
					return QFont::UltraCondensed;
				case std::experimental::io2d::v1::font_stretching::extra_condensed:
					return QFont::ExtraCondensed;
				case std::experimental::io2d::v1::font_stretching::condensed:
					return QFont::Condensed;
				case std::experimental::io2d::v1::font_stretching::semi_condensed:
					return QFont::SemiCondensed;
				//case std::experimental::io2d::v1::font_stretching::medium: // Note: Same as normal
				case std::experimental::io2d::v1::font_stretching::normal:
					return QFont::Unstretched;
				case std::experimental::io2d::v1::font_stretching::semi_expanded:
					return QFont::SemiExpanded;
				case std::experimental::io2d::v1::font_stretching::expanded:
					return QFont::Expanded;
				case std::experimental::io2d::v1::font_stretching::extra_expanded:
					return QFont::ExtraExpanded;
				case std::experimental::io2d::v1::font_stretching::ultra_expanded:
					return QFont::UltraExpanded;
				default:
					throw ::std::runtime_error("Unknown font_stretching value");
				}
			}

			inline QPainter::RenderHints _Antialias_to_qpainter_renderhints(::std::experimental::io2d::antialias aa) {
				switch (aa) {
				case ::std::experimental::io2d::antialias::none:
					return QFlags<QPainter::RenderHint>();
				case ::std::experimental::io2d::antialias::fast:
					return QPainter::RenderHints(QPainter::Antialiasing);
				case ::std::experimental::io2d::antialias::good:
					return QPainter::RenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
				case ::std::experimental::io2d::antialias::best:
					return QPainter::RenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
				default:
					throw ::std::runtime_error("Unknown antialias value.");
				}
			}

			inline Qt::FillRule _Fill_rule_to_qt_fillrule(::std::experimental::io2d::fill_rule fr) {
				switch (fr) {
				case ::std::experimental::io2d::fill_rule::winding:
					return Qt::WindingFill;
				case ::std::experimental::io2d::fill_rule::even_odd:
					return Qt::OddEvenFill;
				default:
					throw ::std::runtime_error("Unknown fill_rule value.");
				}
			}

			inline Qt::PenCapStyle _Line_cap_to_qt_pencapstyle(::std::experimental::io2d::line_cap lc) {
				switch (lc) {
				case ::std::experimental::io2d::line_cap::none:
					return Qt::FlatCap;
				case ::std::experimental::io2d::line_cap::round:
					return Qt::RoundCap;
				case ::std::experimental::io2d::line_cap::square:
					return Qt::SquareCap;
				default:
					throw ::std::runtime_error("Unknown line_cap value.");
				}
			}

			inline Qt::PenJoinStyle _Line_join_to_qt_penjoinstyle(::std::experimental::io2d::line_join lj) {
				switch (lj) {
				case ::std::experimental::io2d::line_join::miter:
					return Qt::MiterJoin;
				case ::std::experimental::io2d::line_join::round:
					return Qt::RoundJoin;
				case ::std::experimental::io2d::line_join::bevel:
					return Qt::BevelJoin;
				default:
					throw ::std::runtime_error("Unknown line_join value.");
				}
			}

			inline QPainter::CompositionMode _Compositing_operator_to_qpainter_compositionmode(::std::experimental::io2d::compositing_op co) {
				switch (co)
				{
				case ::std::experimental::io2d::compositing_op::clear:
					return QPainter::CompositionMode_Clear;
				case ::std::experimental::io2d::compositing_op::source:
					return QPainter::CompositionMode_Source;
				case ::std::experimental::io2d::compositing_op::over:
					return QPainter::CompositionMode_SourceOver;
				case ::std::experimental::io2d::compositing_op::in:
					return QPainter::CompositionMode_SourceIn;
				case ::std::experimental::io2d::compositing_op::out:
					return QPainter::CompositionMode_SourceOut;
				case ::std::experimental::io2d::compositing_op::atop:
					return QPainter::CompositionMode_SourceAtop;
				case ::std::experimental::io2d::compositing_op::dest_over:
					return QPainter::CompositionMode_DestinationOver;
				case ::std::experimental::io2d::compositing_op::dest_in:
					return QPainter::CompositionMode_DestinationIn;
				case ::std::experimental::io2d::compositing_op::dest_out:
					return QPainter::CompositionMode_DestinationOut;
				case ::std::experimental::io2d::compositing_op::dest_atop:
					return QPainter::CompositionMode_DestinationAtop;
				case ::std::experimental::io2d::compositing_op::xor_op:
					return QPainter::CompositionMode_Xor;
				case ::std::experimental::io2d::compositing_op::add:
					return QPainter::CompositionMode_Plus;
				case ::std::experimental::io2d::compositing_op::saturate:
					throw ::std::runtime_error("Unsupported compositing_op value saturate.");
				case ::std::experimental::io2d::compositing_op::multiply:
					return QPainter::CompositionMode_Multiply;
				case ::std::experimental::io2d::compositing_op::screen:
					return QPainter::CompositionMode_Screen;
				case ::std::experimental::io2d::compositing_op::overlay:
					return QPainter::CompositionMode_Overlay;
				case ::std::experimental::io2d::compositing_op::darken:
					return QPainter::CompositionMode_Darken;
				case ::std::experimental::io2d::compositing_op::lighten:
					return QPainter::CompositionMode_Lighten;
				case ::std::experimental::io2d::compositing_op::color_dodge:
					return QPainter::CompositionMode_ColorDodge;
				case ::std::experimental::io2d::compositing_op::color_burn:
					return QPainter::CompositionMode_ColorBurn;
				case ::std::experimental::io2d::compositing_op::hard_light:
					return QPainter::CompositionMode_HardLight;
				case ::std::experimental::io2d::compositing_op::soft_light:
					return QPainter::CompositionMode_SoftLight;
				case ::std::experimental::io2d::compositing_op::difference:
					return QPainter::CompositionMode_Difference;
				case ::std::experimental::io2d::compositing_op::exclusion:
					return QPainter::CompositionMode_Exclusion;
				case ::std::experimental::io2d::compositing_op::hsl_hue:
					throw ::std::runtime_error("Unsupported compositing_op value hsl_hue.");
				case ::std::experimental::io2d::compositing_op::hsl_saturation:
					throw ::std::runtime_error("Unsupported compositing_op value hsl_saturation.");
				case ::std::experimental::io2d::compositing_op::hsl_color:
					throw ::std::runtime_error("Unsupported compositing_op value hsl_color.");
				case ::std::experimental::io2d::compositing_op::hsl_luminosity:
					throw ::std::runtime_error("Unsupported compositing_op value hsl_luminosity.");
				default:
					throw ::std::runtime_error("Unknown compositing_op value.");
				}
			}

			inline QImage::Format _Format_to_qimage_format(::std::experimental::io2d::format f) {
				switch (f) {
				case ::std::experimental::io2d::format::invalid:
					return QImage::Format_Invalid;
				case ::std::experimental::io2d::format::argb32:
					return QImage::Format_ARGB32_Premultiplied;
				case ::std::experimental::io2d::format::xrgb32:
					return QImage::Format_RGB32;
				case ::std::experimental::io2d::format::a8:
					return QImage::Format_Alpha8;
				default:
					throw ::std::runtime_error("Unknown format value.");
				}
			}

			//inline format _QImage_format_to_format(QImage::Format f) {
			//	switch (f)
			//	{
			//	case QImage::Format_Invalid:
			//		return format::invalid;
			//	case QImage::Format_Mono:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_MonoLSB:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_Indexed8:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_RGB32:
			//		return format::xrgb32;
			//	case QImage::Format_ARGB32:
			//		return format::argb32; // This is probably correct?
			//	case QImage::Format_ARGB32_Premultiplied:
			//		return format::argb32;
			//	case QImage::Format_RGB16:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_ARGB8565_Premultiplied:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_RGB666:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_ARGB6666_Premultiplied:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_RGB555:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_ARGB8555_Premultiplied:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_RGB888:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_RGB444:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_ARGB4444_Premultiplied:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_RGBX8888:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_RGBA8888:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_RGBA8888_Premultiplied:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_BGR30:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_A2BGR30_Premultiplied:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_RGB30:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_A2RGB30_Premultiplied:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_Alpha8:
			//		return format::a8;
			//	case QImage::Format_Grayscale8:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_RGBX64:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_RGBA64:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::Format_RGBA64_Premultiplied:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	case QImage::NImageFormats:
			//		throw ::std::runtime_error("Unexpected format value.");
			//	default:
			//		throw ::std::runtime_error("Unknown format value.");
			//	}
			//}

			inline QGradient::Spread _Wrap_mode_to_qgradient_spread(::std::experimental::io2d::wrap_mode wm) {
				switch (wm)
				{
				case std::experimental::io2d::v1::wrap_mode::none:
					return QGradient::PadSpread;
				case std::experimental::io2d::v1::wrap_mode::repeat:
					return QGradient::RepeatSpread;
				case std::experimental::io2d::v1::wrap_mode::reflect:
					return QGradient::ReflectSpread;
				case std::experimental::io2d::v1::wrap_mode::pad:
					return QGradient::PadSpread;
				default:
					throw ::std::runtime_error("Unknown wrap_mode value");
				}
			}
			// Qt doesn't support anything like extend so it'll need to be done manually.
			//inline cairo_extend_t _Extend_to_cairo_extend_t(::std::experimental::io2d::wrap_mode e) {
			//	switch (e) {
			//	case ::std::experimental::io2d::wrap_mode::none:
			//		return CAIRO_EXTEND_NONE;
			//	case ::std::experimental::io2d::wrap_mode::repeat:
			//		return CAIRO_EXTEND_REPEAT;
			//	case ::std::experimental::io2d::wrap_mode::reflect:
			//		return CAIRO_EXTEND_REFLECT;
			//	case ::std::experimental::io2d::wrap_mode::pad:
			//		return CAIRO_EXTEND_PAD;
			//	default:
			//		throw ::std::runtime_error("Unknown wrap_mode value.");
			//	}
			//}

			inline Qt::TransformationMode _Filter_to_qt_transformationmode(::std::experimental::io2d::filter f) {
				switch (f) {
				case ::std::experimental::io2d::filter::fast:
					return Qt::FastTransformation;
				case ::std::experimental::io2d::filter::good:
					return Qt::SmoothTransformation;
				case ::std::experimental::io2d::filter::best:
					return Qt::SmoothTransformation;
				case ::std::experimental::io2d::filter::nearest:
					return Qt::FastTransformation;
				case ::std::experimental::io2d::filter::bilinear:
					return Qt::SmoothTransformation;
				default:
					throw ::std::runtime_error("Unknown filter value.");
				}
			}

			inline Qt::BrushStyle _Brush_type_to_qt_brushstyle(::std::experimental::io2d::brush_type bt) {
				switch (bt) {
				case ::std::experimental::io2d::brush_type::solid_color:
					return Qt::SolidPattern;
				case ::std::experimental::io2d::brush_type::surface:
					return Qt::TexturePattern;
				case ::std::experimental::io2d::brush_type::linear:
					return Qt::LinearGradientPattern;
				case ::std::experimental::io2d::brush_type::radial:
					return Qt::RadialGradientPattern;
					//case ::std::experimental::io2d::brush_type::mesh:
					//	return CAIRO_PATTERN_TYPE_MESH;
				default:
					throw ::std::runtime_error("Unknown brush_type value.");
				}
			}
		}
	}
}
