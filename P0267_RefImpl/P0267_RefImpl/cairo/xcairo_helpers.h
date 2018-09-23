#pragma once

#include "xio2d.h"
#include <cairo.h>
#include <cassert>

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Cairo {
			// Throws an exception of type:
			// -  bad_alloc : If the value of s is CAIRO_STATUS_NO_MEMORY.
			// -  runtime_error : If s is any other value, excluding CAIRO_STATUS_SUCCESS.
			inline void _Throw_if_failed_cairo_status_t(::cairo_status_t s) {
				assert(s == CAIRO_STATUS_SUCCESS && "Unexpected cairo_status_t value.");
				if (s != CAIRO_STATUS_SUCCESS) {
					if (s == CAIRO_STATUS_NO_MEMORY) {
						throw ::std::bad_alloc{};
					}
					else {
						throw ::std::runtime_error("Unrecoverable error.");
					}
				}
			}

			inline cairo_antialias_t _Antialias_to_cairo_antialias_t(::std::experimental::io2d::antialias aa) {
				switch (aa) {
				case ::std::experimental::io2d::antialias::none:
					return CAIRO_ANTIALIAS_NONE;
				case ::std::experimental::io2d::antialias::fast:
					return CAIRO_ANTIALIAS_FAST;
				case ::std::experimental::io2d::antialias::good:
					return CAIRO_ANTIALIAS_GOOD;
				case ::std::experimental::io2d::antialias::best:
					return CAIRO_ANTIALIAS_BEST;
				default:
					throw ::std::runtime_error("Unknown antialias value.");
				}
			}

			inline cairo_fill_rule_t _Fill_rule_to_cairo_fill_rule_t(::std::experimental::io2d::fill_rule fr) {
				switch (fr) {
				case ::std::experimental::io2d::fill_rule::winding:
					return CAIRO_FILL_RULE_WINDING;
				case ::std::experimental::io2d::fill_rule::even_odd:
					return CAIRO_FILL_RULE_EVEN_ODD;
				default:
					throw ::std::runtime_error("Unknown fill_rule value.");
				}
			}

			inline ::std::experimental::io2d::fill_rule _Cairo_fill_rule_t_to_fill_rule(cairo_fill_rule_t cfr) {
				switch (cfr) {
				case CAIRO_FILL_RULE_WINDING:
					return ::std::experimental::io2d::fill_rule::winding;
				case CAIRO_FILL_RULE_EVEN_ODD:
					return ::std::experimental::io2d::fill_rule::even_odd;
				default:
					throw ::std::runtime_error("Unknown cairo_fill_rule_t value.");
				}
			}

			inline cairo_line_cap_t _Line_cap_to_cairo_line_cap_t(::std::experimental::io2d::line_cap lc) {
				switch (lc) {
				case ::std::experimental::io2d::line_cap::none:
					return CAIRO_LINE_CAP_BUTT;
				case ::std::experimental::io2d::line_cap::round:
					return CAIRO_LINE_CAP_ROUND;
				case ::std::experimental::io2d::line_cap::square:
					return CAIRO_LINE_CAP_SQUARE;
				default:
					throw ::std::runtime_error("Unknown line_cap value.");
				}
			}

			inline ::std::experimental::io2d::line_cap _Cairo_line_cap_t_to_line_cap(cairo_line_cap_t clc) {
				switch (clc) {
				case CAIRO_LINE_CAP_BUTT:
					return ::std::experimental::io2d::line_cap::none;
				case CAIRO_LINE_CAP_ROUND:
					return ::std::experimental::io2d::line_cap::round;
				case CAIRO_LINE_CAP_SQUARE:
					return ::std::experimental::io2d::line_cap::square;
				default:
					throw ::std::runtime_error("Unknown cairo_line_cap_t value.");
				}
			}

			inline cairo_line_join_t _Line_join_to_cairo_line_join_t(::std::experimental::io2d::line_join lj) {
				switch (lj) {
				case ::std::experimental::io2d::line_join::miter:
					return CAIRO_LINE_JOIN_MITER;
				case ::std::experimental::io2d::line_join::round:
					return CAIRO_LINE_JOIN_ROUND;
				case ::std::experimental::io2d::line_join::bevel:
					return CAIRO_LINE_JOIN_BEVEL;
				default:
					throw ::std::runtime_error("Unknown line_join value.");
				}
			}

			inline ::std::experimental::io2d::line_join _Cairo_line_join_t_to_line_join(cairo_line_join_t clj) {
				switch (clj) {
				case CAIRO_LINE_JOIN_MITER:
					return ::std::experimental::io2d::line_join::miter;
				case CAIRO_LINE_JOIN_ROUND:
					return ::std::experimental::io2d::line_join::round;
				case CAIRO_LINE_JOIN_BEVEL:
					return ::std::experimental::io2d::line_join::bevel;
				default:
					throw ::std::runtime_error("Unknown cairo_line_join_t value.");
				}
			}

			inline cairo_operator_t _Compositing_operator_to_cairo_operator_t(::std::experimental::io2d::compositing_op co) {
				switch (co)
				{
				case ::std::experimental::io2d::compositing_op::clear:
					return CAIRO_OPERATOR_CLEAR;
				case ::std::experimental::io2d::compositing_op::source:
					return CAIRO_OPERATOR_SOURCE;
				case ::std::experimental::io2d::compositing_op::over:
					return CAIRO_OPERATOR_OVER;
				case ::std::experimental::io2d::compositing_op::in:
					return CAIRO_OPERATOR_IN;
				case ::std::experimental::io2d::compositing_op::out:
					return CAIRO_OPERATOR_OUT;
				case ::std::experimental::io2d::compositing_op::atop:
					return CAIRO_OPERATOR_ATOP;
				case ::std::experimental::io2d::compositing_op::dest_over:
					return CAIRO_OPERATOR_DEST_OVER;
				case ::std::experimental::io2d::compositing_op::dest_in:
					return CAIRO_OPERATOR_DEST_IN;
				case ::std::experimental::io2d::compositing_op::dest_out:
					return CAIRO_OPERATOR_DEST_OUT;
				case ::std::experimental::io2d::compositing_op::dest_atop:
					return CAIRO_OPERATOR_DEST_ATOP;
				case ::std::experimental::io2d::compositing_op::xor_op:
					return CAIRO_OPERATOR_XOR;
				case ::std::experimental::io2d::compositing_op::add:
					return CAIRO_OPERATOR_ADD;
				case ::std::experimental::io2d::compositing_op::saturate:
					return CAIRO_OPERATOR_SATURATE;
				case ::std::experimental::io2d::compositing_op::multiply:
					return CAIRO_OPERATOR_MULTIPLY;
				case ::std::experimental::io2d::compositing_op::screen:
					return CAIRO_OPERATOR_SCREEN;
				case ::std::experimental::io2d::compositing_op::overlay:
					return CAIRO_OPERATOR_OVERLAY;
				case ::std::experimental::io2d::compositing_op::darken:
					return CAIRO_OPERATOR_DARKEN;
				case ::std::experimental::io2d::compositing_op::lighten:
					return CAIRO_OPERATOR_LIGHTEN;
				case ::std::experimental::io2d::compositing_op::color_dodge:
					return CAIRO_OPERATOR_COLOR_DODGE;
				case ::std::experimental::io2d::compositing_op::color_burn:
					return CAIRO_OPERATOR_COLOR_BURN;
				case ::std::experimental::io2d::compositing_op::hard_light:
					return CAIRO_OPERATOR_HARD_LIGHT;
				case ::std::experimental::io2d::compositing_op::soft_light:
					return CAIRO_OPERATOR_SOFT_LIGHT;
				case ::std::experimental::io2d::compositing_op::difference:
					return CAIRO_OPERATOR_DIFFERENCE;
				case ::std::experimental::io2d::compositing_op::exclusion:
					return CAIRO_OPERATOR_EXCLUSION;
				case ::std::experimental::io2d::compositing_op::hsl_hue:
					return CAIRO_OPERATOR_HSL_HUE;
				case ::std::experimental::io2d::compositing_op::hsl_saturation:
					return CAIRO_OPERATOR_HSL_SATURATION;
				case ::std::experimental::io2d::compositing_op::hsl_color:
					return CAIRO_OPERATOR_HSL_COLOR;
				case ::std::experimental::io2d::compositing_op::hsl_luminosity:
					return CAIRO_OPERATOR_HSL_LUMINOSITY;
				default:
					throw ::std::runtime_error("Unknown compositing_op value.");
				}
			}

			inline ::std::experimental::io2d::compositing_op _Cairo_operator_t_to_compositing_operator(cairo_operator_t co) {
				switch (co)
				{
				case CAIRO_OPERATOR_CLEAR:
					return ::std::experimental::io2d::compositing_op::clear;
				case CAIRO_OPERATOR_SOURCE:
					return ::std::experimental::io2d::compositing_op::source;
				case CAIRO_OPERATOR_OVER:
					return ::std::experimental::io2d::compositing_op::over;
				case CAIRO_OPERATOR_IN:
					return ::std::experimental::io2d::compositing_op::in;
				case CAIRO_OPERATOR_OUT:
					return ::std::experimental::io2d::compositing_op::out;
				case CAIRO_OPERATOR_ATOP:
					return ::std::experimental::io2d::compositing_op::atop;
				case CAIRO_OPERATOR_DEST:
					throw ::std::runtime_error("CAIRO_OPERATOR_DEST is a no-op and is thus unsupported.");
				case CAIRO_OPERATOR_DEST_OVER:
					return ::std::experimental::io2d::compositing_op::dest_over;
				case CAIRO_OPERATOR_DEST_IN:
					return ::std::experimental::io2d::compositing_op::dest_in;
				case CAIRO_OPERATOR_DEST_OUT:
					return ::std::experimental::io2d::compositing_op::dest_out;
				case CAIRO_OPERATOR_DEST_ATOP:
					return ::std::experimental::io2d::compositing_op::dest_atop;
				case CAIRO_OPERATOR_XOR:
					return ::std::experimental::io2d::compositing_op::xor_op;
				case CAIRO_OPERATOR_ADD:
					return ::std::experimental::io2d::compositing_op::add;
				case CAIRO_OPERATOR_SATURATE:
					return ::std::experimental::io2d::compositing_op::saturate;
				case CAIRO_OPERATOR_MULTIPLY:
					return ::std::experimental::io2d::compositing_op::multiply;
				case CAIRO_OPERATOR_SCREEN:
					return ::std::experimental::io2d::compositing_op::screen;
				case CAIRO_OPERATOR_OVERLAY:
					return ::std::experimental::io2d::compositing_op::overlay;
				case CAIRO_OPERATOR_DARKEN:
					return ::std::experimental::io2d::compositing_op::darken;
				case CAIRO_OPERATOR_LIGHTEN:
					return ::std::experimental::io2d::compositing_op::lighten;
				case CAIRO_OPERATOR_COLOR_DODGE:
					return ::std::experimental::io2d::compositing_op::color_dodge;
				case CAIRO_OPERATOR_COLOR_BURN:
					return ::std::experimental::io2d::compositing_op::color_burn;
				case CAIRO_OPERATOR_HARD_LIGHT:
					return ::std::experimental::io2d::compositing_op::hard_light;
				case CAIRO_OPERATOR_SOFT_LIGHT:
					return ::std::experimental::io2d::compositing_op::soft_light;
				case CAIRO_OPERATOR_DIFFERENCE:
					return ::std::experimental::io2d::compositing_op::difference;
				case CAIRO_OPERATOR_EXCLUSION:
					return ::std::experimental::io2d::compositing_op::exclusion;
				case CAIRO_OPERATOR_HSL_HUE:
					return ::std::experimental::io2d::compositing_op::hsl_hue;
				case CAIRO_OPERATOR_HSL_SATURATION:
					return ::std::experimental::io2d::compositing_op::hsl_saturation;
				case CAIRO_OPERATOR_HSL_COLOR:
					return ::std::experimental::io2d::compositing_op::hsl_color;
				case CAIRO_OPERATOR_HSL_LUMINOSITY:
					return ::std::experimental::io2d::compositing_op::hsl_luminosity;
				default:
					throw ::std::runtime_error("Unknown cairo_operator_t value.");
				}
			}

			inline cairo_format_t _Format_to_cairo_format_t(::std::experimental::io2d::format f) {
				switch (f) {
				case ::std::experimental::io2d::format::invalid:
					return CAIRO_FORMAT_INVALID;
				case ::std::experimental::io2d::format::argb32:
					return CAIRO_FORMAT_ARGB32;
				case ::std::experimental::io2d::format::xrgb32:
					return CAIRO_FORMAT_RGB24;
				case ::std::experimental::io2d::format::a8:
					return CAIRO_FORMAT_A8;
				default:
					throw ::std::runtime_error("Unknown format value.");
				}
			}

			inline ::std::experimental::io2d::format _Cairo_format_t_to_format(cairo_format_t cf) {
				switch (cf) {
				case CAIRO_FORMAT_INVALID:
					return ::std::experimental::io2d::format::invalid;
				case CAIRO_FORMAT_ARGB32:
					return ::std::experimental::io2d::format::argb32;
				case CAIRO_FORMAT_RGB24:
					return ::std::experimental::io2d::format::xrgb32;
				case CAIRO_FORMAT_A8:
					return ::std::experimental::io2d::format::a8;
				case CAIRO_FORMAT_A1:
					// intentional fallthrough
				default:
					throw ::std::runtime_error("Unknown cairo_format_t value.");
				}
			}

			inline cairo_extend_t _Extend_to_cairo_extend_t(::std::experimental::io2d::wrap_mode e) {
				switch (e) {
				case ::std::experimental::io2d::wrap_mode::none:
					return CAIRO_EXTEND_NONE;
				case ::std::experimental::io2d::wrap_mode::repeat:
					return CAIRO_EXTEND_REPEAT;
				case ::std::experimental::io2d::wrap_mode::reflect:
					return CAIRO_EXTEND_REFLECT;
				case ::std::experimental::io2d::wrap_mode::pad:
					return CAIRO_EXTEND_PAD;
				default:
					throw ::std::runtime_error("Unknown wrap_mode value.");
				}
			}

			inline ::std::experimental::io2d::wrap_mode _Cairo_extend_t_to_extend(cairo_extend_t ce) {
				switch (ce) {
				case CAIRO_EXTEND_NONE:
					return ::std::experimental::io2d::wrap_mode::none;
				case CAIRO_EXTEND_REPEAT:
					return ::std::experimental::io2d::wrap_mode::repeat;
				case CAIRO_EXTEND_REFLECT:
					return ::std::experimental::io2d::wrap_mode::reflect;
				case CAIRO_EXTEND_PAD:
					return ::std::experimental::io2d::wrap_mode::pad;
				default:
					throw ::std::runtime_error("Unknown cairo_extend_t value.");
				}
			}

			inline cairo_filter_t _Filter_to_cairo_filter_t(::std::experimental::io2d::filter f) {
				switch (f) {
				case ::std::experimental::io2d::filter::fast:
					return CAIRO_FILTER_FAST;
				case ::std::experimental::io2d::filter::good:
					return CAIRO_FILTER_GOOD;
				case ::std::experimental::io2d::filter::best:
					return CAIRO_FILTER_BEST;
				case ::std::experimental::io2d::filter::nearest:
					return CAIRO_FILTER_NEAREST;
				case ::std::experimental::io2d::filter::bilinear:
					return CAIRO_FILTER_BILINEAR;
				default:
					throw ::std::runtime_error("Unknown filter value.");
				}
			}

			inline ::std::experimental::io2d::filter _Cairo_filter_t_to_filter(cairo_filter_t cf) {
				switch (cf) {
				case CAIRO_FILTER_FAST:
					return ::std::experimental::io2d::filter::fast;
				case CAIRO_FILTER_GOOD:
					return ::std::experimental::io2d::filter::good;
				case CAIRO_FILTER_BEST:
					return ::std::experimental::io2d::filter::best;
				case CAIRO_FILTER_NEAREST:
					return ::std::experimental::io2d::filter::nearest;
				case CAIRO_FILTER_BILINEAR:
					return ::std::experimental::io2d::filter::bilinear;
				case CAIRO_FILTER_GAUSSIAN:
					throw ::std::runtime_error("Unexpected cairo_filter_t value CAIRO_FILTER_GAUSSIAN.");
				default:
					throw ::std::runtime_error("Unknown cairo_filter_t value.");
				}
			}

			inline cairo_pattern_type_t _Brush_type_to_cairo_pattern_type_t(::std::experimental::io2d::brush_type bt) {
				switch (bt) {
				case ::std::experimental::io2d::brush_type::solid_color:
					return CAIRO_PATTERN_TYPE_SOLID;
				case ::std::experimental::io2d::brush_type::surface:
					return CAIRO_PATTERN_TYPE_SURFACE;
				case ::std::experimental::io2d::brush_type::linear:
					return CAIRO_PATTERN_TYPE_LINEAR;
				case ::std::experimental::io2d::brush_type::radial:
					return CAIRO_PATTERN_TYPE_RADIAL;
					//case ::std::experimental::io2d::brush_type::mesh:
					//	return CAIRO_PATTERN_TYPE_MESH;
				default:
					throw ::std::runtime_error("Unknown brush_type value.");
				}
			}

			inline ::std::experimental::io2d::brush_type _Cairo_pattern_type_t_to_brush_type(cairo_pattern_type_t cpt) {
				switch (cpt) {
				case CAIRO_PATTERN_TYPE_SOLID:
					return ::std::experimental::io2d::brush_type::solid_color;
				case CAIRO_PATTERN_TYPE_SURFACE:
					return ::std::experimental::io2d::brush_type::surface;
				case CAIRO_PATTERN_TYPE_LINEAR:
					return ::std::experimental::io2d::brush_type::linear;
				case CAIRO_PATTERN_TYPE_RADIAL:
					return ::std::experimental::io2d::brush_type::radial;
				case CAIRO_PATTERN_TYPE_MESH:
					throw ::std::runtime_error("Unsupported cairo_pattern_type_t value 'CAIRO_PATTERN_TYPE_MESH'.");
					//return ::std::experimental::io2d::brush_type::mesh;
				case CAIRO_PATTERN_TYPE_RASTER_SOURCE:
					throw ::std::runtime_error("Unsupported cairo_pattern_type_t value 'CAIRO_PATTERN_TYPE_RASTER_SOURCE'.");
				default:
					throw ::std::runtime_error("Unknown cairo_pattern_type_t value.");
				}
			}
		}
	}
}
