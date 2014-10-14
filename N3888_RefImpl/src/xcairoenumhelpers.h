#pragma once

#ifndef _XCAIROENUMHELPERS_H_
#define _XCAIROENUMHELPERS_H_

#include "drawing.h"
#include "cairo.h"
#include <stdexcept>

namespace std {
	namespace experimental {
		namespace drawing {
			inline cairo_status_t _Io2d_error_to_cairo_status_t(::std::experimental::drawing::io2d_error s) {
				switch (s) {
				case ::std::experimental::drawing::io2d_error::success:
					return CAIRO_STATUS_SUCCESS;
				case ::std::experimental::drawing::io2d_error::no_memory:
					return CAIRO_STATUS_NO_MEMORY;
				case ::std::experimental::drawing::io2d_error::invalid_restore:
					return CAIRO_STATUS_INVALID_RESTORE;
				case ::std::experimental::drawing::io2d_error::invalid_pop_group:
					return CAIRO_STATUS_INVALID_POP_GROUP;
				case ::std::experimental::drawing::io2d_error::no_current_point:
					return CAIRO_STATUS_NO_CURRENT_POINT;
				case ::std::experimental::drawing::io2d_error::invalid_matrix:
					return CAIRO_STATUS_INVALID_MATRIX;
				case ::std::experimental::drawing::io2d_error::invalid_status:
					return CAIRO_STATUS_INVALID_STATUS;
				case ::std::experimental::drawing::io2d_error::null_pointer:
					return CAIRO_STATUS_NULL_POINTER;
				case ::std::experimental::drawing::io2d_error::invalid_string:
					return CAIRO_STATUS_INVALID_STRING;
				case ::std::experimental::drawing::io2d_error::invalid_path_data:
					return CAIRO_STATUS_INVALID_PATH_DATA;
				case ::std::experimental::drawing::io2d_error::read_error:
					return CAIRO_STATUS_READ_ERROR;
				case ::std::experimental::drawing::io2d_error::write_error:
					return CAIRO_STATUS_WRITE_ERROR;
				case ::std::experimental::drawing::io2d_error::surface_finished:
					return CAIRO_STATUS_SURFACE_FINISHED;
				case ::std::experimental::drawing::io2d_error::surface_type_mismatch:
					return CAIRO_STATUS_SURFACE_TYPE_MISMATCH;
				case ::std::experimental::drawing::io2d_error::pattern_type_mismatch:
					return CAIRO_STATUS_PATTERN_TYPE_MISMATCH;
				case ::std::experimental::drawing::io2d_error::invalid_content:
					return CAIRO_STATUS_INVALID_CONTENT;
				case ::std::experimental::drawing::io2d_error::invalid_format:
					return CAIRO_STATUS_INVALID_FORMAT;
				case ::std::experimental::drawing::io2d_error::invalid_visual:
					return CAIRO_STATUS_INVALID_VISUAL;
				case ::std::experimental::drawing::io2d_error::file_not_found:
					return CAIRO_STATUS_FILE_NOT_FOUND;
				case ::std::experimental::drawing::io2d_error::invalid_dash:
					return CAIRO_STATUS_INVALID_DASH;
				case ::std::experimental::drawing::io2d_error::invalid_dsc_comment:
					return CAIRO_STATUS_INVALID_DSC_COMMENT;
				case ::std::experimental::drawing::io2d_error::invalid_index:
					return CAIRO_STATUS_INVALID_INDEX;
				case ::std::experimental::drawing::io2d_error::clip_not_representable:
					return CAIRO_STATUS_CLIP_NOT_REPRESENTABLE;
				case ::std::experimental::drawing::io2d_error::temp_file_error:
					return CAIRO_STATUS_TEMP_FILE_ERROR;
				case ::std::experimental::drawing::io2d_error::invalid_stride:
					return CAIRO_STATUS_INVALID_STRIDE;
				case ::std::experimental::drawing::io2d_error::font_type_mismatch:
					return CAIRO_STATUS_FONT_TYPE_MISMATCH;
				case ::std::experimental::drawing::io2d_error::user_font_immutable:
					return CAIRO_STATUS_USER_FONT_IMMUTABLE;
				case ::std::experimental::drawing::io2d_error::user_font_error:
					return CAIRO_STATUS_USER_FONT_ERROR;
				case ::std::experimental::drawing::io2d_error::negative_count:
					return CAIRO_STATUS_NEGATIVE_COUNT;
				case ::std::experimental::drawing::io2d_error::invalid_clusters:
					return CAIRO_STATUS_INVALID_CLUSTERS;
				case ::std::experimental::drawing::io2d_error::invalid_slant:
					return CAIRO_STATUS_INVALID_SLANT;
				case ::std::experimental::drawing::io2d_error::invalid_weight:
					return CAIRO_STATUS_INVALID_WEIGHT;
				case ::std::experimental::drawing::io2d_error::invalid_size:
					return CAIRO_STATUS_INVALID_SIZE;
				case ::std::experimental::drawing::io2d_error::user_font_not_implemented:
					return CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED;
				case ::std::experimental::drawing::io2d_error::device_type_mismatch:
					return CAIRO_STATUS_DEVICE_TYPE_MISMATCH;
				case ::std::experimental::drawing::io2d_error::device_error:
					return CAIRO_STATUS_DEVICE_ERROR;
				case ::std::experimental::drawing::io2d_error::invalid_mesh_construction:
					return CAIRO_STATUS_INVALID_MESH_CONSTRUCTION;
				case ::std::experimental::drawing::io2d_error::device_finished:
					return CAIRO_STATUS_DEVICE_FINISHED;
				case ::std::experimental::drawing::io2d_error::last_value:
					throw ::std::runtime_error("Invalid io2d_error value io2d_error::last_value.");
				default:
					throw ::std::runtime_error("Unknown io2d_error value.");
				}
			}

			inline ::std::experimental::drawing::io2d_error _Cairo_status_t_to_io2d_error(cairo_status_t cs) {
				switch (cs) {
				case CAIRO_STATUS_SUCCESS:
					return ::std::experimental::drawing::io2d_error::success;
				case CAIRO_STATUS_NO_MEMORY:
					return ::std::experimental::drawing::io2d_error::no_memory;
				case CAIRO_STATUS_INVALID_RESTORE:
					return ::std::experimental::drawing::io2d_error::invalid_restore;
				case CAIRO_STATUS_INVALID_POP_GROUP:
					return ::std::experimental::drawing::io2d_error::invalid_pop_group;
				case CAIRO_STATUS_NO_CURRENT_POINT:
					return ::std::experimental::drawing::io2d_error::no_current_point;
				case CAIRO_STATUS_INVALID_MATRIX:
					return ::std::experimental::drawing::io2d_error::invalid_matrix;
				case CAIRO_STATUS_INVALID_STATUS:
					return ::std::experimental::drawing::io2d_error::invalid_status;
				case CAIRO_STATUS_NULL_POINTER:
					return ::std::experimental::drawing::io2d_error::null_pointer;
				case CAIRO_STATUS_INVALID_STRING:
					return ::std::experimental::drawing::io2d_error::invalid_string;
				case CAIRO_STATUS_INVALID_PATH_DATA:
					return ::std::experimental::drawing::io2d_error::invalid_path_data;
				case CAIRO_STATUS_READ_ERROR:
					return ::std::experimental::drawing::io2d_error::read_error;
				case CAIRO_STATUS_WRITE_ERROR:
					return ::std::experimental::drawing::io2d_error::write_error;
				case CAIRO_STATUS_SURFACE_FINISHED:
					return ::std::experimental::drawing::io2d_error::surface_finished;
				case CAIRO_STATUS_SURFACE_TYPE_MISMATCH:
					return ::std::experimental::drawing::io2d_error::surface_type_mismatch;
				case CAIRO_STATUS_PATTERN_TYPE_MISMATCH:
					return ::std::experimental::drawing::io2d_error::pattern_type_mismatch;
				case CAIRO_STATUS_INVALID_CONTENT:
					return ::std::experimental::drawing::io2d_error::invalid_content;
				case CAIRO_STATUS_INVALID_FORMAT:
					return ::std::experimental::drawing::io2d_error::invalid_format;
				case CAIRO_STATUS_INVALID_VISUAL:
					return ::std::experimental::drawing::io2d_error::invalid_visual;
				case CAIRO_STATUS_FILE_NOT_FOUND:
					return ::std::experimental::drawing::io2d_error::file_not_found;
				case CAIRO_STATUS_INVALID_DASH:
					return ::std::experimental::drawing::io2d_error::invalid_dash;
				case CAIRO_STATUS_INVALID_DSC_COMMENT:
					return ::std::experimental::drawing::io2d_error::invalid_dsc_comment;
				case CAIRO_STATUS_INVALID_INDEX:
					return ::std::experimental::drawing::io2d_error::invalid_index;
				case CAIRO_STATUS_CLIP_NOT_REPRESENTABLE:
					return ::std::experimental::drawing::io2d_error::clip_not_representable;
				case CAIRO_STATUS_TEMP_FILE_ERROR:
					return ::std::experimental::drawing::io2d_error::temp_file_error;
				case CAIRO_STATUS_INVALID_STRIDE:
					return ::std::experimental::drawing::io2d_error::invalid_stride;
				case CAIRO_STATUS_FONT_TYPE_MISMATCH:
					return ::std::experimental::drawing::io2d_error::font_type_mismatch;
				case CAIRO_STATUS_USER_FONT_IMMUTABLE:
					return ::std::experimental::drawing::io2d_error::user_font_immutable;
				case CAIRO_STATUS_USER_FONT_ERROR:
					return ::std::experimental::drawing::io2d_error::user_font_error;
				case CAIRO_STATUS_NEGATIVE_COUNT:
					return ::std::experimental::drawing::io2d_error::negative_count;
				case CAIRO_STATUS_INVALID_CLUSTERS:
					return ::std::experimental::drawing::io2d_error::invalid_clusters;
				case CAIRO_STATUS_INVALID_SLANT:
					return ::std::experimental::drawing::io2d_error::invalid_slant;
				case CAIRO_STATUS_INVALID_WEIGHT:
					return ::std::experimental::drawing::io2d_error::invalid_weight;
				case CAIRO_STATUS_INVALID_SIZE:
					return ::std::experimental::drawing::io2d_error::invalid_size;
				case CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED:
					return ::std::experimental::drawing::io2d_error::user_font_not_implemented;
				case CAIRO_STATUS_DEVICE_TYPE_MISMATCH:
					return ::std::experimental::drawing::io2d_error::device_type_mismatch;
				case CAIRO_STATUS_DEVICE_ERROR:
					return ::std::experimental::drawing::io2d_error::device_error;
				case CAIRO_STATUS_INVALID_MESH_CONSTRUCTION:
					return ::std::experimental::drawing::io2d_error::invalid_mesh_construction;
				case CAIRO_STATUS_DEVICE_FINISHED:
					return ::std::experimental::drawing::io2d_error::device_finished;
				case CAIRO_STATUS_LAST_STATUS:
					throw ::std::runtime_error("Invalid cairo_status_t value CAIRO_STATUS_LAST_STATUS.");
				default:
					throw ::std::runtime_error("Unknown cairo_status_t value.");
				}
			}

			inline cairo_antialias_t _Antialias_to_cairo_antialias_t(::std::experimental::drawing::antialias aa) {
				switch (aa) {
				case ::std::experimental::drawing::antialias::default_antialias:
					return CAIRO_ANTIALIAS_DEFAULT;
				case ::std::experimental::drawing::antialias::none:
					return CAIRO_ANTIALIAS_NONE;
				case ::std::experimental::drawing::antialias::gray:
					return CAIRO_ANTIALIAS_GRAY;
				case ::std::experimental::drawing::antialias::subpixel:
					return CAIRO_ANTIALIAS_SUBPIXEL;
				case ::std::experimental::drawing::antialias::fast:
					return CAIRO_ANTIALIAS_FAST;
				case ::std::experimental::drawing::antialias::good:
					return CAIRO_ANTIALIAS_GOOD;
				case ::std::experimental::drawing::antialias::best:
					return CAIRO_ANTIALIAS_BEST;
				default:
					throw ::std::runtime_error("Unknown antialias value.");
				}
			}

			inline ::std::experimental::drawing::antialias _Cairo_antialias_t_to_antialias(cairo_antialias_t caa) {
				switch (caa) {
				case CAIRO_ANTIALIAS_DEFAULT:
					return ::std::experimental::drawing::antialias::default_antialias;
				case CAIRO_ANTIALIAS_NONE:
					return ::std::experimental::drawing::antialias::none;
				case CAIRO_ANTIALIAS_GRAY:
					return ::std::experimental::drawing::antialias::gray;
				case CAIRO_ANTIALIAS_SUBPIXEL:
					return ::std::experimental::drawing::antialias::subpixel;
				case CAIRO_ANTIALIAS_FAST:
					return ::std::experimental::drawing::antialias::fast;
				case CAIRO_ANTIALIAS_GOOD:
					return ::std::experimental::drawing::antialias::good;
				case CAIRO_ANTIALIAS_BEST:
					return ::std::experimental::drawing::antialias::best;
				default:
					throw ::std::runtime_error("Unknown cairo_antialias_t value.");
				}
			}

			inline cairo_content_t _Content_to_cairo_content_t(::std::experimental::drawing::content c) {
				switch (c) {
				case ::std::experimental::drawing::content::color:
					return CAIRO_CONTENT_COLOR;
				case ::std::experimental::drawing::content::alpha:
					return CAIRO_CONTENT_ALPHA;
				case ::std::experimental::drawing::content::color_alpha:
					return CAIRO_CONTENT_COLOR_ALPHA;
				default:
					throw ::std::runtime_error("Unknown content value.");
				}
			}

			inline ::std::experimental::drawing::content _Cairo_content_t_to_content(cairo_content_t cc) {
				switch (cc) {
				case CAIRO_CONTENT_COLOR:
					return ::std::experimental::drawing::content::color;
				case CAIRO_CONTENT_ALPHA:
					return ::std::experimental::drawing::content::alpha;
				case CAIRO_CONTENT_COLOR_ALPHA:
					return ::std::experimental::drawing::content::color_alpha;
				default:
					throw ::std::runtime_error("Unknown cairo_content_t value.");
				}
			}

			inline cairo_fill_rule_t _Fill_rule_to_cairo_fill_rule_t(::std::experimental::drawing::fill_rule fr) {
				switch (fr) {
				case ::std::experimental::drawing::fill_rule::winding:
					return CAIRO_FILL_RULE_WINDING;
				case ::std::experimental::drawing::fill_rule::even_odd:
					return CAIRO_FILL_RULE_EVEN_ODD;
				default:
					throw ::std::runtime_error("Unknown fill_rule value.");
				}
			}

			inline ::std::experimental::drawing::fill_rule _Cairo_fill_rule_t_to_fill_rule(cairo_fill_rule_t cfr) {
				switch (cfr) {
				case CAIRO_FILL_RULE_WINDING:
					return ::std::experimental::drawing::fill_rule::winding;
				case CAIRO_FILL_RULE_EVEN_ODD:
					return ::std::experimental::drawing::fill_rule::even_odd;
				default:
					throw ::std::runtime_error("Unknown cairo_fill_rule_t value.");
				}
			}

			inline cairo_line_cap_t _Line_cap_to_cairo_line_cap_t(::std::experimental::drawing::line_cap lc) {
				switch (lc) {
				case ::std::experimental::drawing::line_cap::butt:
					return CAIRO_LINE_CAP_BUTT;
				case ::std::experimental::drawing::line_cap::round:
					return CAIRO_LINE_CAP_ROUND;
				case ::std::experimental::drawing::line_cap::square:
					return CAIRO_LINE_CAP_SQUARE;
				default:
					throw ::std::runtime_error("Unknown line_cap value.");
				}
			}

			inline ::std::experimental::drawing::line_cap _Cairo_line_cap_t_to_line_cap(cairo_line_cap_t clc) {
				switch (clc) {
				case CAIRO_LINE_CAP_BUTT:
					return ::std::experimental::drawing::line_cap::butt;
				case CAIRO_LINE_CAP_ROUND:
					return ::std::experimental::drawing::line_cap::round;
				case CAIRO_LINE_CAP_SQUARE:
					return ::std::experimental::drawing::line_cap::square;
				default:
					throw ::std::runtime_error("Unknown cairo_line_cap_t value.");
				}
			}

			inline cairo_line_join_t _Line_join_to_cairo_line_join_t(::std::experimental::drawing::line_join lj) {
				switch (lj) {
				case ::std::experimental::drawing::line_join::miter:
					return CAIRO_LINE_JOIN_MITER;
				case ::std::experimental::drawing::line_join::round:
					return CAIRO_LINE_JOIN_ROUND;
				case ::std::experimental::drawing::line_join::bevel:
					return CAIRO_LINE_JOIN_BEVEL;
				default:
					throw ::std::runtime_error("Unknown line_join value.");
				}
			}

			inline ::std::experimental::drawing::line_join _Cairo_line_join_t_to_line_join(cairo_line_join_t clj) {
				switch (clj) {
				case CAIRO_LINE_JOIN_MITER:
					return ::std::experimental::drawing::line_join::miter;
				case CAIRO_LINE_JOIN_ROUND:
					return ::std::experimental::drawing::line_join::round;
				case CAIRO_LINE_JOIN_BEVEL:
					return ::std::experimental::drawing::line_join::bevel;
				default:
					throw ::std::runtime_error("Unknown cairo_line_join_t value.");
				}
			}

			inline cairo_operator_t _Compositing_operator_to_cairo_operator_t(::std::experimental::drawing::compositing_operator co) {
				switch (co)
				{
				case ::std::experimental::drawing::compositing_operator::clear:
					return CAIRO_OPERATOR_CLEAR;
				case ::std::experimental::drawing::compositing_operator::source:
					return CAIRO_OPERATOR_SOURCE;
				case ::std::experimental::drawing::compositing_operator::over:
					return CAIRO_OPERATOR_OVER;
				case ::std::experimental::drawing::compositing_operator::in:
					return CAIRO_OPERATOR_IN;
				case ::std::experimental::drawing::compositing_operator::out:
					return CAIRO_OPERATOR_OUT;
				case ::std::experimental::drawing::compositing_operator::atop:
					return CAIRO_OPERATOR_ATOP;
				case ::std::experimental::drawing::compositing_operator::dest:
					return CAIRO_OPERATOR_DEST;
				case ::std::experimental::drawing::compositing_operator::dest_over:
					return CAIRO_OPERATOR_DEST_OVER;
				case ::std::experimental::drawing::compositing_operator::dest_in:
					return CAIRO_OPERATOR_DEST_IN;
				case ::std::experimental::drawing::compositing_operator::dest_out:
					return CAIRO_OPERATOR_DEST_OUT;
				case ::std::experimental::drawing::compositing_operator::dest_atop:
					return CAIRO_OPERATOR_DEST_ATOP;
				case ::std::experimental::drawing::compositing_operator::xor_op:
					return CAIRO_OPERATOR_XOR;
				case ::std::experimental::drawing::compositing_operator::add:
					return CAIRO_OPERATOR_ADD;
				case ::std::experimental::drawing::compositing_operator::saturate:
					return CAIRO_OPERATOR_SATURATE;
				case ::std::experimental::drawing::compositing_operator::multiply:
					return CAIRO_OPERATOR_MULTIPLY;
				case ::std::experimental::drawing::compositing_operator::screen:
					return CAIRO_OPERATOR_SCREEN;
				case ::std::experimental::drawing::compositing_operator::overlay:
					return CAIRO_OPERATOR_OVERLAY;
				case ::std::experimental::drawing::compositing_operator::darken:
					return CAIRO_OPERATOR_DARKEN;
				case ::std::experimental::drawing::compositing_operator::lighten:
					return CAIRO_OPERATOR_LIGHTEN;
				case ::std::experimental::drawing::compositing_operator::color_dodge:
					return CAIRO_OPERATOR_COLOR_DODGE;
				case ::std::experimental::drawing::compositing_operator::color_burn:
					return CAIRO_OPERATOR_COLOR_BURN;
				case ::std::experimental::drawing::compositing_operator::hard_light:
					return CAIRO_OPERATOR_HARD_LIGHT;
				case ::std::experimental::drawing::compositing_operator::soft_light:
					return CAIRO_OPERATOR_SOFT_LIGHT;
				case ::std::experimental::drawing::compositing_operator::difference:
					return CAIRO_OPERATOR_DIFFERENCE;
				case ::std::experimental::drawing::compositing_operator::exclusion:
					return CAIRO_OPERATOR_EXCLUSION;
				case ::std::experimental::drawing::compositing_operator::hsl_hue:
					return CAIRO_OPERATOR_HSL_HUE;
				case ::std::experimental::drawing::compositing_operator::hsl_saturation:
					return CAIRO_OPERATOR_HSL_SATURATION;
				case ::std::experimental::drawing::compositing_operator::hsl_color:
					return CAIRO_OPERATOR_HSL_COLOR;
				case ::std::experimental::drawing::compositing_operator::hsl_luminosity:
					return CAIRO_OPERATOR_HSL_LUMINOSITY;
				default:
					throw ::std::runtime_error("Unknown compositing_operator value.");
				}
			}

			inline ::std::experimental::drawing::compositing_operator _Cairo_operator_t_to_compositing_operator(cairo_operator_t co) {
				switch (co)
				{
				case CAIRO_OPERATOR_CLEAR:
					return ::std::experimental::drawing::compositing_operator::clear;
				case CAIRO_OPERATOR_SOURCE:
					return ::std::experimental::drawing::compositing_operator::source;
				case CAIRO_OPERATOR_OVER:
					return ::std::experimental::drawing::compositing_operator::over;
				case CAIRO_OPERATOR_IN:
					return ::std::experimental::drawing::compositing_operator::in;
				case CAIRO_OPERATOR_OUT:
					return ::std::experimental::drawing::compositing_operator::out;
				case CAIRO_OPERATOR_ATOP:
					return ::std::experimental::drawing::compositing_operator::atop;
				case CAIRO_OPERATOR_DEST:
					return ::std::experimental::drawing::compositing_operator::dest;
				case CAIRO_OPERATOR_DEST_OVER:
					return ::std::experimental::drawing::compositing_operator::dest_over;
				case CAIRO_OPERATOR_DEST_IN:
					return ::std::experimental::drawing::compositing_operator::dest_in;
				case CAIRO_OPERATOR_DEST_OUT:
					return ::std::experimental::drawing::compositing_operator::dest_out;
				case CAIRO_OPERATOR_DEST_ATOP:
					return ::std::experimental::drawing::compositing_operator::dest_atop;
				case CAIRO_OPERATOR_XOR:
					return ::std::experimental::drawing::compositing_operator::xor_op;
				case CAIRO_OPERATOR_ADD:
					return ::std::experimental::drawing::compositing_operator::add;
				case CAIRO_OPERATOR_SATURATE:
					return ::std::experimental::drawing::compositing_operator::saturate;
				case CAIRO_OPERATOR_MULTIPLY:
					return ::std::experimental::drawing::compositing_operator::multiply;
				case CAIRO_OPERATOR_SCREEN:
					return ::std::experimental::drawing::compositing_operator::screen;
				case CAIRO_OPERATOR_OVERLAY:
					return ::std::experimental::drawing::compositing_operator::overlay;
				case CAIRO_OPERATOR_DARKEN:
					return ::std::experimental::drawing::compositing_operator::darken;
				case CAIRO_OPERATOR_LIGHTEN:
					return ::std::experimental::drawing::compositing_operator::lighten;
				case CAIRO_OPERATOR_COLOR_DODGE:
					return ::std::experimental::drawing::compositing_operator::color_dodge;
				case CAIRO_OPERATOR_COLOR_BURN:
					return ::std::experimental::drawing::compositing_operator::color_burn;
				case CAIRO_OPERATOR_HARD_LIGHT:
					return ::std::experimental::drawing::compositing_operator::hard_light;
				case CAIRO_OPERATOR_SOFT_LIGHT:
					return ::std::experimental::drawing::compositing_operator::soft_light;
				case CAIRO_OPERATOR_DIFFERENCE:
					return ::std::experimental::drawing::compositing_operator::difference;
				case CAIRO_OPERATOR_EXCLUSION:
					return ::std::experimental::drawing::compositing_operator::exclusion;
				case CAIRO_OPERATOR_HSL_HUE:
					return ::std::experimental::drawing::compositing_operator::hsl_hue;
				case CAIRO_OPERATOR_HSL_SATURATION:
					return ::std::experimental::drawing::compositing_operator::hsl_saturation;
				case CAIRO_OPERATOR_HSL_COLOR:
					return ::std::experimental::drawing::compositing_operator::hsl_color;
				case CAIRO_OPERATOR_HSL_LUMINOSITY:
					return ::std::experimental::drawing::compositing_operator::hsl_luminosity;
				default:
					throw ::std::runtime_error("Unknown cairo_operator_t value.");
				}
			}

			inline cairo_format_t _Format_to_cairo_format_t(::std::experimental::drawing::format f) {
				switch (f) {
				case ::std::experimental::drawing::format::invalid:
					return CAIRO_FORMAT_INVALID;
				case ::std::experimental::drawing::format::argb32:
					return CAIRO_FORMAT_ARGB32;
				case ::std::experimental::drawing::format::rgb24:
					return CAIRO_FORMAT_RGB24;
				case ::std::experimental::drawing::format::a8:
					return CAIRO_FORMAT_A8;
				case ::std::experimental::drawing::format::a1:
					return CAIRO_FORMAT_A1;
				case ::std::experimental::drawing::format::rgb16_565:
					return CAIRO_FORMAT_RGB16_565;
				case ::std::experimental::drawing::format::rgb30:
					return CAIRO_FORMAT_RGB30;
				default:
					throw ::std::runtime_error("Unknown format value.");
				}
			}

			inline ::std::experimental::drawing::format _Cairo_format_t_to_format(cairo_format_t cf) {
				switch (cf) {
				case CAIRO_FORMAT_INVALID:
					return ::std::experimental::drawing::format::invalid;
				case CAIRO_FORMAT_ARGB32:
					return ::std::experimental::drawing::format::argb32;
				case CAIRO_FORMAT_RGB24:
					return ::std::experimental::drawing::format::rgb24;
				case CAIRO_FORMAT_A8:
					return ::std::experimental::drawing::format::a8;
				case CAIRO_FORMAT_A1:
					return ::std::experimental::drawing::format::a1;
				case CAIRO_FORMAT_RGB16_565:
					return ::std::experimental::drawing::format::rgb16_565;
				case CAIRO_FORMAT_RGB30:
					return ::std::experimental::drawing::format::rgb30;
				default:
					throw ::std::runtime_error("Unknown cairo_format_t value.");
				}
			}

			inline ::std::experimental::drawing::path_data_type _Cairo_path_data_type_t_to_path_data_type(cairo_path_data_type_t cpdt) {
				switch (cpdt) {
				case CAIRO_PATH_MOVE_TO:
					return ::std::experimental::drawing::path_data_type::move_to;
				case CAIRO_PATH_LINE_TO:
					return ::std::experimental::drawing::path_data_type::line_to;
				case CAIRO_PATH_CURVE_TO:
					return ::std::experimental::drawing::path_data_type::curve_to;
				case CAIRO_PATH_CLOSE_PATH:
					return ::std::experimental::drawing::path_data_type::close_path;
				default:
					throw ::std::runtime_error("Unknown cairo_path_data_type_t value.");
				}
			}

			inline cairo_extend_t _Extend_to_cairo_extend_t(::std::experimental::drawing::extend e) {
				switch (e) {
				case ::std::experimental::drawing::extend::none:
					return CAIRO_EXTEND_NONE;
				case ::std::experimental::drawing::extend::repeat:
					return CAIRO_EXTEND_REPEAT;
				case ::std::experimental::drawing::extend::reflect:
					return CAIRO_EXTEND_REFLECT;
				case ::std::experimental::drawing::extend::pad:
					return CAIRO_EXTEND_PAD;
				default:
					throw ::std::runtime_error("Unknown extend value.");
				}
			}

			inline ::std::experimental::drawing::extend _Cairo_extend_t_to_extend(cairo_extend_t ce) {
				switch (ce) {
				case CAIRO_EXTEND_NONE:
					return ::std::experimental::drawing::extend::none;
				case CAIRO_EXTEND_REPEAT:
					return ::std::experimental::drawing::extend::repeat;
				case CAIRO_EXTEND_REFLECT:
					return ::std::experimental::drawing::extend::reflect;
				case CAIRO_EXTEND_PAD:
					return ::std::experimental::drawing::extend::pad;
				default:
					throw ::std::runtime_error("Unknown cairo_extend_t value.");
				}
			}

			inline cairo_filter_t _Filter_to_cairo_filter_t(::std::experimental::drawing::filter f) {
				switch (f) {
				case ::std::experimental::drawing::filter::fast:
					return CAIRO_FILTER_FAST;
				case ::std::experimental::drawing::filter::good:
					return CAIRO_FILTER_GOOD;
				case ::std::experimental::drawing::filter::best:
					return CAIRO_FILTER_BEST;
				case ::std::experimental::drawing::filter::nearest:
					return CAIRO_FILTER_NEAREST;
				case ::std::experimental::drawing::filter::bilinear:
					return CAIRO_FILTER_BILINEAR;
				case ::std::experimental::drawing::filter::gaussian:
					return CAIRO_FILTER_GAUSSIAN;
				default:
					throw ::std::runtime_error("Unknown filter value.");
				}
			}

			inline ::std::experimental::drawing::filter _Cairo_filter_t_to_filter(cairo_filter_t cf) {
				switch (cf) {
				case CAIRO_FILTER_FAST:
					return ::std::experimental::drawing::filter::fast;
				case CAIRO_FILTER_GOOD:
					return ::std::experimental::drawing::filter::good;
				case CAIRO_FILTER_BEST:
					return ::std::experimental::drawing::filter::best;
				case CAIRO_FILTER_NEAREST:
					return ::std::experimental::drawing::filter::nearest;
				case CAIRO_FILTER_BILINEAR:
					return ::std::experimental::drawing::filter::bilinear;
				case CAIRO_FILTER_GAUSSIAN:
					return ::std::experimental::drawing::filter::gaussian;
				default:
					throw ::std::runtime_error("Unknown cairo_filter_t value.");
				}
			}

			inline cairo_pattern_type_t _Pattern_type_to_cairo_pattern_type_t(::std::experimental::drawing::pattern_type pt) {
				switch (pt) {
				case ::std::experimental::drawing::pattern_type::solid_color:
					return CAIRO_PATTERN_TYPE_SOLID;
				case ::std::experimental::drawing::pattern_type::surface:
					return CAIRO_PATTERN_TYPE_SURFACE;
				case ::std::experimental::drawing::pattern_type::linear:
					return CAIRO_PATTERN_TYPE_LINEAR;
				case ::std::experimental::drawing::pattern_type::radial:
					return CAIRO_PATTERN_TYPE_RADIAL;
				case ::std::experimental::drawing::pattern_type::mesh:
					return CAIRO_PATTERN_TYPE_MESH;
				case ::std::experimental::drawing::pattern_type::raster_source:
					return CAIRO_PATTERN_TYPE_RASTER_SOURCE;
				default:
					throw ::std::runtime_error("Unknown pattern_type value.");
				}
			}

			inline ::std::experimental::drawing::pattern_type _Cairo_pattern_type_t_to_pattern_type(cairo_pattern_type_t cpt) {
				switch (cpt) {
				case CAIRO_PATTERN_TYPE_SOLID:
					return ::std::experimental::drawing::pattern_type::solid_color;
				case CAIRO_PATTERN_TYPE_SURFACE:
					return ::std::experimental::drawing::pattern_type::surface;
				case CAIRO_PATTERN_TYPE_LINEAR:
					return ::std::experimental::drawing::pattern_type::linear;
				case CAIRO_PATTERN_TYPE_RADIAL:
					return ::std::experimental::drawing::pattern_type::radial;
				case CAIRO_PATTERN_TYPE_MESH:
					return ::std::experimental::drawing::pattern_type::mesh;
				case CAIRO_PATTERN_TYPE_RASTER_SOURCE:
					return ::std::experimental::drawing::pattern_type::raster_source;
				default:
					throw ::std::runtime_error("Unknown cairo_pattern_type_t value.");
				}
			}

			inline cairo_font_slant_t _Font_slant_to_cairo_font_slant_t(::std::experimental::drawing::font_slant fs) {
				switch (fs) {
				case ::std::experimental::drawing::font_slant::normal:
					return CAIRO_FONT_SLANT_NORMAL;
				case ::std::experimental::drawing::font_slant::italic:
					return CAIRO_FONT_SLANT_ITALIC;
				case ::std::experimental::drawing::font_slant::oblique:
					return CAIRO_FONT_SLANT_OBLIQUE;
				default:
					throw ::std::runtime_error("Unknown font_slant value.");
				}
			}

			inline ::std::experimental::drawing::font_slant _Cairo_font_slant_t_to_font_slant(cairo_font_slant_t cfs) {
				switch (cfs) {
				case CAIRO_FONT_SLANT_NORMAL:
					return ::std::experimental::drawing::font_slant::normal;
				case CAIRO_FONT_SLANT_ITALIC:
					return ::std::experimental::drawing::font_slant::italic;
				case CAIRO_FONT_SLANT_OBLIQUE:
					return ::std::experimental::drawing::font_slant::oblique;
				default:
					throw ::std::runtime_error("Unknown cairo_font_slant_t value.");
				}
			}

			inline cairo_font_weight_t _Font_weight_to_cairo_font_weight_t(::std::experimental::drawing::font_weight fw) {
				switch (fw) {
				case ::std::experimental::drawing::font_weight::normal:
					return CAIRO_FONT_WEIGHT_NORMAL;
				case ::std::experimental::drawing::font_weight::bold:
					return CAIRO_FONT_WEIGHT_BOLD;
				default:
					throw ::std::runtime_error("Unknown font_weight value.");
				}
			}

			inline ::std::experimental::drawing::font_weight _Cairo_font_weight_t_to_font_weight(cairo_font_weight_t cfw) {
				switch (cfw) {
				case CAIRO_FONT_WEIGHT_NORMAL:
					return ::std::experimental::drawing::font_weight::normal;
				case CAIRO_FONT_WEIGHT_BOLD:
					return ::std::experimental::drawing::font_weight::bold;
				default:
					throw ::std::runtime_error("Unknown cairo_font_weight_t value.");
				}
			}

			inline cairo_text_cluster_flags_t _Text_cluster_flags_to_cairo_text_cluster_flags_t(const ::std::experimental::drawing::text_cluster_flags::text_cluster_flags& tcf) {
				cairo_text_cluster_flags_t result{ };
				if (tcf == 0) {
					return static_cast<cairo_text_cluster_flags_t>(0);
				}
				if ((tcf & ::std::experimental::drawing::text_cluster_flags::backward) != 0) {
					result = static_cast<cairo_text_cluster_flags_t>(result | CAIRO_TEXT_CLUSTER_FLAG_BACKWARD);
				}
				return result;
			}

			inline ::std::experimental::drawing::text_cluster_flags::text_cluster_flags _Cairo_text_cluster_flags_t_to_text_cluster_flags(cairo_text_cluster_flags_t ctcf) {
				::std::experimental::drawing::text_cluster_flags::text_cluster_flags result{ };
				if (ctcf == 0) {
					return result;
				}

				if ((ctcf & CAIRO_TEXT_CLUSTER_FLAG_BACKWARD) != 0) {
					result = static_cast<::std::experimental::drawing::text_cluster_flags::text_cluster_flags>(result | ::std::experimental::drawing::text_cluster_flags::backward);
				}

				return result;
			}

			inline cairo_subpixel_order_t _Subpixel_order_to_cairo_subpixel_order_t(::std::experimental::drawing::subpixel_order so) {
				switch (so) {
				case ::std::experimental::drawing::subpixel_order::default_subpixel_order:
					return CAIRO_SUBPIXEL_ORDER_DEFAULT;
				case ::std::experimental::drawing::subpixel_order::rgb:
					return CAIRO_SUBPIXEL_ORDER_RGB;
				case ::std::experimental::drawing::subpixel_order::bgr:
					return CAIRO_SUBPIXEL_ORDER_BGR;
				case ::std::experimental::drawing::subpixel_order::vrgb:
					return CAIRO_SUBPIXEL_ORDER_VRGB;
				case ::std::experimental::drawing::subpixel_order::vbgr:
					return CAIRO_SUBPIXEL_ORDER_VBGR;
				default:
					throw ::std::runtime_error("Unknown subpixel_order value.");
				}
			}

			inline ::std::experimental::drawing::subpixel_order _Cairo_subpixel_order_t_to_subpixel_order(cairo_subpixel_order_t cso) {
				switch (cso) {
				case CAIRO_SUBPIXEL_ORDER_DEFAULT:
					return ::std::experimental::drawing::subpixel_order::default_subpixel_order;
				case CAIRO_SUBPIXEL_ORDER_RGB:
					return ::std::experimental::drawing::subpixel_order::rgb;
				case CAIRO_SUBPIXEL_ORDER_BGR:
					return ::std::experimental::drawing::subpixel_order::bgr;
				case CAIRO_SUBPIXEL_ORDER_VRGB:
					return ::std::experimental::drawing::subpixel_order::vrgb;
				case CAIRO_SUBPIXEL_ORDER_VBGR:
					return ::std::experimental::drawing::subpixel_order::vbgr;
				default:
					throw ::std::runtime_error("Unknown cairo_subpixel_order value.");
				}
			}

			inline cairo_hint_style_t _Hint_style_to_cairo_hint_style_t(::std::experimental::drawing::hint_style hs) {
				switch (hs) {
				case ::std::experimental::drawing::hint_style::default_hint_style:
					return CAIRO_HINT_STYLE_DEFAULT;
				case ::std::experimental::drawing::hint_style::none:
					return CAIRO_HINT_STYLE_NONE;
				case ::std::experimental::drawing::hint_style::slight:
					return CAIRO_HINT_STYLE_SLIGHT;
				case ::std::experimental::drawing::hint_style::medium:
					return CAIRO_HINT_STYLE_MEDIUM;
				case ::std::experimental::drawing::hint_style::full:
					return CAIRO_HINT_STYLE_FULL;
				default:
					throw ::std::runtime_error("Unknown hint_style value.");
				}
			}

			inline ::std::experimental::drawing::hint_style _Cairo_hint_style_t_to_hint_style(cairo_hint_style_t chs) {
				switch (chs) {
				case CAIRO_HINT_STYLE_DEFAULT:
					return ::std::experimental::drawing::hint_style::default_hint_style;
				case CAIRO_HINT_STYLE_NONE:
					return ::std::experimental::drawing::hint_style::none;
				case CAIRO_HINT_STYLE_SLIGHT:
					return ::std::experimental::drawing::hint_style::slight;
				case CAIRO_HINT_STYLE_MEDIUM:
					return ::std::experimental::drawing::hint_style::medium;
				case CAIRO_HINT_STYLE_FULL:
					return ::std::experimental::drawing::hint_style::full;
				default:
					throw ::std::runtime_error("Unknown cairo_hint_style_t value.");
				}
			}

			inline cairo_hint_metrics_t _Hint_metrics_to_cairo_hint_metrics_t(::std::experimental::drawing::hint_metrics hm) {
				switch (hm) {
				case ::std::experimental::drawing::hint_metrics::default_hint_metrics:
					return CAIRO_HINT_METRICS_DEFAULT;
				case ::std::experimental::drawing::hint_metrics::off:
					return CAIRO_HINT_METRICS_OFF;
				case ::std::experimental::drawing::hint_metrics::on:
					return CAIRO_HINT_METRICS_ON;
				default:
					throw ::std::runtime_error("Unknown hint_metrics value.");
				}
			}

			inline ::std::experimental::drawing::hint_metrics _Cairo_hint_metrics_t_to_hint_metrics(cairo_hint_metrics_t chm) {
				switch (chm) {
				case CAIRO_HINT_METRICS_DEFAULT:
					return ::std::experimental::drawing::hint_metrics::default_hint_metrics;
				case CAIRO_HINT_METRICS_OFF:
					return ::std::experimental::drawing::hint_metrics::off;
				case CAIRO_HINT_METRICS_ON:
					return ::std::experimental::drawing::hint_metrics::on;
				default:
					throw ::std::runtime_error("Unknown cairo_hint_metrics_t value.");
				}
			}

		} // close drawing
	} // close experimental
} // close std

#endif