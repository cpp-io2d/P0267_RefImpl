#pragma once

#include "xio2d.h"

#include <memory>
#include <functional>
#include <exception>
#include <vector>
#include <string>
#include <algorithm>
#include <system_error>
#include <cstdint>
#include <atomic>
#include <variant>
#include <optional>
#include <cmath>
#include <type_traits>
#include <initializer_list>
#include <cmath>

#ifdef _Filesystem_support_test
#include <filesystem>
#endif

namespace std::experimental::io2d {
	inline namespace v1 {

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

		// cairo_interpreted_path

		template <class _TItem>
		struct _Path_group_perform_visit {
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_new_figure>, _Path_data_abs_new_figure> = _Path_data_abs_new_figure_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const figure_items::abs_new_figure& item, point_2d& lastMoveToPoint) noexcept {
				cairo_path_data_t cpdItem{};
				auto pt = item.at();
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt.x, pt.y };
				lastMoveToPoint = pt;
				vec.push_back(cpdItem);
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const figure_items::abs_line& item, point_2d&) noexcept {
				cairo_path_data_t cpdItem{};
				auto pt = item.to();
				cpdItem.header.type = CAIRO_PATH_LINE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt.x, pt.y };
				vec.push_back(cpdItem);
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const figure_items::abs_cubic_curve& item, point_2d&) noexcept {
				cairo_path_data_t cpdItem{};
				auto pt1 = item.control_pt1();
				auto pt2 = item.control_pt2();
				auto pt3 = item.end_pt();
				cpdItem.header.type = CAIRO_PATH_CURVE_TO;
				cpdItem.header.length = 4;
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt1.x, pt1.y };
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt2.x, pt2.y };
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt3.x, pt3.y };
				vec.push_back(cpdItem);
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::abs_quadratic_curve&, point_2d&) noexcept {
				assert(false && "Abs quadratic curves should have been transformed into cubic curves already.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_new_figure>, _Path_data_rel_new_figure> = _Path_data_rel_new_figure_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::rel_new_figure&, point_2d&) noexcept {
				assert(false && "Rel new path instructions should have been eliminated.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::close_figure>, _Path_data_close_path> = _Path_data_close_path_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const figure_items::close_figure&, point_2d& lastMoveToPoint) noexcept {
				cairo_path_data_t cpdItem{};
				cpdItem.header.type = CAIRO_PATH_CLOSE_PATH;
				cpdItem.header.length = 1;
				vec.push_back(cpdItem);
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { lastMoveToPoint.x, lastMoveToPoint.y };
				vec.push_back(cpdItem);
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::rel_line&, point_2d&) noexcept {
				assert(false && "Rel line should have been transformed into non-relative.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::rel_cubic_curve&, point_2d&) noexcept {
				assert(false && "Rel curve should have been transformed into non-relative.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::rel_quadratic_curve&, point_2d&) noexcept {
				assert(false && "Rel quadratic curves should have been transformed into cubic curves.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::arc>, _Path_data_arc> = _Path_data_arc_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::arc&, point_2d&) noexcept {
				assert(false && "Arcs should have been transformed into cubic curves.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_matrix>, _Path_data_abs_matrix> = _Path_data_abs_matrix_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::abs_matrix&, point_2d&) noexcept {
				assert(false && "Abs matrix should have been eliminated.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_matrix>, _Path_data_rel_matrix> = _Path_data_rel_matrix_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::rel_matrix&, point_2d&) noexcept {
				assert(false && "Rel matrix should have been eliminated.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::revert_matrix>, _Path_data_revert_matrix> = _Path_data_revert_matrix_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::revert_matrix&, point_2d&) noexcept {
				assert(false && "Revert matrix should have been eliminated.");
			}
		};

		inline cairo_interpreted_path::_Native_handle_type cairo_interpreted_path::_Native_handle() const noexcept {
			return _Cairo_path.get();
		}

		constexpr cairo_interpreted_path::cairo_interpreted_path() noexcept
			: _Cairo_path(nullptr)
		{}

		template <class Allocator>
		inline cairo_interpreted_path::cairo_interpreted_path(const path_builder<Allocator>& pf)
			: _Cairo_path(new cairo_path_t, [](cairo_path_t*) {
			// This deleter intentionally left blank. The dtor will deal with this.
		}) {
			auto processedVec = _Interpret_path_items<Allocator>(pf);
			::std::vector<cairo_path_data_t> vec;
			point_2d lastMoveToPoint;
			for (const auto& val : processedVec) {
				::std::visit([&vec, &lastMoveToPoint](auto&& item) {
					using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
					_Path_group_perform_visit<T>::template _Perform<T>(vec, item, lastMoveToPoint);
				}, val);
			}
			_Cairo_path->num_data = static_cast<int>(vec.size());
			const auto numDataST = vec.size();
			_Cairo_path->data = new cairo_path_data_t[numDataST];
			for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
				_Cairo_path->data[currItemIndex] = vec[currItemIndex];
			}
			_Cairo_path->status = CAIRO_STATUS_SUCCESS;
		}

		template <class ForwardIterator>
		inline cairo_interpreted_path::cairo_interpreted_path(ForwardIterator first, ForwardIterator last)
			: _Cairo_path(new cairo_path_t, [](cairo_path_t*) {
			// This deleter intentionally left blank. The dtor will deal with this.
		}) {
			auto processedVec = _Interpret_path_items<ForwardIterator>(first, last);
			::std::vector<cairo_path_data_t> vec;
			point_2d lastMoveToPoint;
			for (const auto& val : processedVec) {
				::std::visit([&vec, &lastMoveToPoint](auto&& item) {
					using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
					_Path_group_perform_visit<T>::template _Perform<T>(vec, item, lastMoveToPoint);
				}, val);
			}
			_Cairo_path->num_data = static_cast<int>(vec.size());
			const auto numDataST = vec.size();
			_Cairo_path->data = new cairo_path_data_t[numDataST];
			for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
				_Cairo_path->data[currItemIndex] = vec[currItemIndex];
			}
			_Cairo_path->status = CAIRO_STATUS_SUCCESS;
		}

		inline cairo_interpreted_path::cairo_interpreted_path(const cairo_interpreted_path& other) noexcept
			: _Cairo_path(other._Cairo_path) {}

		inline cairo_interpreted_path& cairo_interpreted_path::operator=(const cairo_interpreted_path& other) noexcept {
			_Cairo_path = other._Cairo_path;
			return *this;
		}

		inline cairo_interpreted_path::cairo_interpreted_path(cairo_interpreted_path&& other) noexcept
			: _Cairo_path(move(other._Cairo_path)) {
			other._Cairo_path = nullptr;
		}

		inline cairo_interpreted_path& cairo_interpreted_path::operator=(cairo_interpreted_path&& other) noexcept {
			if (this != &other) {
				_Cairo_path = move(other._Cairo_path);
				other._Cairo_path = nullptr;
			}
			return *this;
		}

		inline cairo_interpreted_path::~cairo_interpreted_path() noexcept {
			auto path = _Cairo_path.get();
			if (path != nullptr) {
				if (path->data != nullptr) {
					delete[] path->data;
					path->data = nullptr;
					path->status = CAIRO_STATUS_NULL_POINTER;
				}
				delete path;
				path = nullptr;
				_Cairo_path = nullptr;
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
			case ::std::experimental::io2d::compositing_op::dest:
				return CAIRO_OPERATOR_DEST;
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
				return ::std::experimental::io2d::compositing_op::dest;
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
			case ::std::experimental::io2d::format::rgb24:
				return CAIRO_FORMAT_RGB24;
			case ::std::experimental::io2d::format::a8:
				return CAIRO_FORMAT_A8;
			case ::std::experimental::io2d::format::rgb16_565:
				return CAIRO_FORMAT_RGB16_565;
			case ::std::experimental::io2d::format::rgb30:
				return CAIRO_FORMAT_RGB30;
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
				return ::std::experimental::io2d::format::rgb24;
			case CAIRO_FORMAT_A8:
				return ::std::experimental::io2d::format::a8;
			case CAIRO_FORMAT_RGB16_565:
				return ::std::experimental::io2d::format::rgb16_565;
			case CAIRO_FORMAT_RGB30:
				return ::std::experimental::io2d::format::rgb30;
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

		template <class _TItem>
		struct _Path_item_interpret_visitor {
			constexpr static float twoThirds = 2.0F / 3.0F;

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_new_figure>, _Path_data_abs_new_figure> = _Path_data_abs_new_figure_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d& closePoint, stack<matrix_2d>&) noexcept {
				const auto pt = m.transform_pt({ 0.0F, 0.0F }) + item.at();
				v.emplace_back(::std::in_place_type<figure_items::abs_new_figure>, pt);
				currentPoint = pt;
				closePoint = pt;
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_new_figure>, _Path_data_rel_new_figure> = _Path_data_rel_new_figure_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d& closePoint, stack<matrix_2d>&) noexcept {
				auto amtx = m;
				amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
				const auto pt = currentPoint + item.at() * amtx;
				v.emplace_back(::std::in_place_type<figure_items::abs_new_figure>, pt);
				currentPoint = pt;
				closePoint = pt;
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::close_figure>, _Path_data_close_path> = _Path_data_close_path_val>
			static void _Interpret(const T&, ::std::vector<figure_items::figure_item>& v, matrix_2d&, point_2d& currentPoint, point_2d& closePoint, stack<matrix_2d>&) noexcept {
				const auto& item = v.rbegin();
				auto idx = item->index();
				if (idx == 0 || idx == 1) {
					return; // degenerate path
				}
				v.emplace_back(::std::in_place_type<figure_items::close_figure>);
				v.emplace_back(::std::in_place_type<figure_items::abs_new_figure>,
					closePoint);
				currentPoint = closePoint;
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_matrix>, _Path_data_abs_matrix> = _Path_data_abs_matrix_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>&, matrix_2d& m, point_2d&, point_2d&, stack<matrix_2d>& matrices) noexcept {
				matrices.push(m);
				m = item.matrix();
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_matrix>, _Path_data_rel_matrix> = _Path_data_rel_matrix_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>&, matrix_2d& m, point_2d&, point_2d&, stack<matrix_2d>& matrices) noexcept {
				const auto updateM = m * item.matrix();
				matrices.push(m);
				m = updateM;
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::revert_matrix>, _Path_data_revert_matrix> = _Path_data_revert_matrix_val>
			static void _Interpret(const T&, ::std::vector<figure_items::figure_item>&, matrix_2d& m, point_2d&, point_2d&, stack<matrix_2d>& matrices) noexcept {
				if (matrices.empty()) {
					m = matrix_2d{};
				}
				else {
					m = matrices.top();
					matrices.pop();
				}
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d&, stack<matrix_2d>&) noexcept {
				const auto pt1 = m.transform_pt(item.control_pt1() - currentPoint) + currentPoint;
				const auto pt2 = m.transform_pt(item.control_pt2() - currentPoint) + currentPoint;
				const auto pt3 = m.transform_pt(item.end_pt() - currentPoint) + currentPoint;
				if (currentPoint == pt1 && pt1 == pt2 && pt2 == pt3) {
					return; // degenerate path segment
				}
				v.emplace_back(::std::in_place_type<figure_items::abs_cubic_curve>, pt1,
					pt2, pt3);
				currentPoint = pt3;
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d&, stack<matrix_2d>&) noexcept {
				const auto pt = m.transform_pt(item.to() - currentPoint) + currentPoint;
				if (currentPoint == pt) {
					return; // degenerate path segment
				}
				v.emplace_back(::std::in_place_type<figure_items::abs_line>, pt);
				currentPoint = pt;
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d&, stack<matrix_2d>&) noexcept {
				// Turn it into a cubic curve since cairo doesn't have quadratic curves.
				//point_2d beginPt;
				const auto controlPt = m.transform_pt(item.control_pt() - currentPoint) + currentPoint;
				const auto endPt = m.transform_pt(item.end_pt() - currentPoint) + currentPoint;
				if (currentPoint == controlPt && controlPt == endPt) {
					return; // degenerate path segment
				}
				const auto beginPt = currentPoint;
				point_2d cpt1 = { ((controlPt.x - beginPt.x) * twoThirds) + beginPt.x, ((controlPt.y - beginPt.y) * twoThirds) + beginPt.y };
				point_2d cpt2 = { ((controlPt.x - endPt.x) * twoThirds) + endPt.x, ((controlPt.y - endPt.y) * twoThirds) + endPt.y };
				v.emplace_back(::std::in_place_type<figure_items::abs_cubic_curve>, cpt1, cpt2, endPt);
				currentPoint = endPt;
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::arc>, _Path_data_arc> = _Path_data_arc_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d&, stack<matrix_2d>&) noexcept {
				const float rot = item.rotation();
				const float oneThousandthOfADegreeInRads = pi<float> / 180'000.0F;
				if (abs(rot) < oneThousandthOfADegreeInRads) {
					// Return if the rotation is less than one thousandth of one degree; it's a degenerate path segment.
					return;
				}
				const auto clockwise = (rot < 0.0F) ? true : false;
				const point_2d rad = item.radius();
				auto startAng = item.start_angle();
				const auto origM = m;
				m = matrix_2d::init_scale(rad);
				auto centerOffset = (point_for_angle(two_pi<float> -startAng) * rad);
				centerOffset.y = -centerOffset.y;
				auto ctr = currentPoint - centerOffset;

				point_2d pt0, pt1, pt2, pt3;
				int bezCount = 1;
				float theta = rot;

				while (abs(theta) > half_pi<float>) {
					theta /= 2.0F;
					bezCount += bezCount;
				}

				float phi = (theta / 2.0F);
				const auto cosPhi = cos(-phi);
				const auto sinPhi = sin(-phi);

				pt0.x = cosPhi;
				pt0.y = -sinPhi;
				pt3.x = pt0.x;
				pt3.y = -pt0.y;
				pt1.x = (4.0F - cosPhi) / 3.0F;
				pt1.y = -(((1.0F - cosPhi) * (3.0F - cosPhi)) / (3.0F * sinPhi));
				pt2.x = pt1.x;
				pt2.y = -pt1.y;
				auto rotCntrCwFn = [](point_2d pt, float a) -> point_2d {
					auto result = point_2d{ pt.x * cos(a) - pt.y * sin(a),
						pt.x * sin(a) + pt.y * cos(a) };
					result.x = _Round_floating_point_to_zero(result.x);
					result.y = _Round_floating_point_to_zero(result.y);
					return result;
				};
				auto rotCwFn = [](point_2d pt, float a) -> point_2d {
					auto result = point_2d{ pt.x * cos(a) - pt.y * sin(a),
						-(pt.x * sin(a) + pt.y * cos(a)) };
					result.x = _Round_floating_point_to_zero(result.x);
					result.y = _Round_floating_point_to_zero(result.y);
					return result;
				};

				startAng = two_pi<float> -startAng;

				if (clockwise) {
					pt0 = rotCwFn(pt0, phi);
					pt1 = rotCwFn(pt1, phi);
					pt2 = rotCwFn(pt2, phi);
					pt3 = rotCwFn(pt3, phi);
					auto shflPt = pt3;
					pt3 = pt0;
					pt0 = shflPt;
					shflPt = pt2;
					pt2 = pt1;
					pt1 = shflPt;
				}
				else {
					pt0 = rotCntrCwFn(pt0, phi);
					pt1 = rotCntrCwFn(pt1, phi);
					pt2 = rotCntrCwFn(pt2, phi);
					pt3 = rotCntrCwFn(pt3, phi);
					pt0.y = -pt0.y;
					pt1.y = -pt1.y;
					pt2.y = -pt2.y;
					pt3.y = -pt3.y;
					auto shflPt = pt3;
					pt3 = pt0;
					pt0 = shflPt;
					shflPt = pt2;
					pt2 = pt1;
					pt1 = shflPt;
				}
				auto currTheta = startAng;
				const auto calcAdjustedCurrPt = ((ctr + (rotCntrCwFn(pt0, currTheta) * m)) * origM);
				auto adjustVal = calcAdjustedCurrPt - currentPoint;
				point_2d tempCurrPt;
				for (; bezCount > 0; bezCount--) {
					const auto rapt0 = m.transform_pt(rotCntrCwFn(pt0, currTheta));
					const auto rapt1 = m.transform_pt(rotCntrCwFn(pt1, currTheta));
					const auto rapt2 = m.transform_pt(rotCntrCwFn(pt2, currTheta));
					const auto rapt3 = m.transform_pt(rotCntrCwFn(pt3, currTheta));
					auto cpt0 = ctr + rapt0;
					auto cpt1 = ctr + rapt1;
					auto cpt2 = ctr + rapt2;
					auto cpt3 = ctr + rapt3;
					cpt0 = origM.transform_pt(cpt0);
					cpt1 = origM.transform_pt(cpt1);
					cpt2 = origM.transform_pt(cpt2);
					cpt3 = origM.transform_pt(cpt3);
					cpt0 -= adjustVal;
					cpt1 -= adjustVal;
					cpt2 -= adjustVal;
					cpt3 -= adjustVal;
					currentPoint = cpt3;
					v.emplace_back(::std::in_place_type<figure_items::abs_cubic_curve>, cpt1, cpt2, cpt3);
					currTheta -= theta;
				}
				m = origM;
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d&, stack<matrix_2d>&) noexcept {
				auto amtx = m;
				amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
				const auto pt1 = item.control_pt1() * amtx;
				const auto pt2 = item.control_pt2() * amtx;
				const auto pt3 = item.end_pt()* amtx;
				if (currentPoint == pt1 && pt1 == pt2 && pt2 == pt3) {
					return; // degenerate path segment
				}
				v.emplace_back(::std::in_place_type<figure_items::abs_cubic_curve>, currentPoint + pt1, currentPoint + pt1 + pt2, currentPoint + pt1 + pt2 + pt3);
				currentPoint = currentPoint + pt1 + pt2 + pt3;
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d&, stack<matrix_2d>&) noexcept {
				auto amtx = m;
				amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
				const auto pt = currentPoint + item.to() * amtx;
				if (currentPoint == pt) {
					return; // degenerate path segment
				}
				v.emplace_back(::std::in_place_type<figure_items::abs_line>, pt);
				currentPoint = pt;
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d&, stack<matrix_2d>&) noexcept {
				auto amtx = m;
				amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
				const auto controlPt = currentPoint + item.control_pt() * amtx;
				const auto endPt = currentPoint + item.control_pt() * amtx + item.end_pt() * amtx;
				const auto beginPt = currentPoint;
				if (currentPoint == controlPt && controlPt == endPt) {
					return; // degenerate path segment
				}
				point_2d cpt1 = { ((controlPt.x - beginPt.x) * twoThirds) + beginPt.x, ((controlPt.y - beginPt.y) * twoThirds) + beginPt.y };
				point_2d cpt2 = { ((controlPt.x - endPt.x) * twoThirds) + endPt.x, ((controlPt.y - endPt.y) * twoThirds) + endPt.y };
				v.emplace_back(::std::in_place_type<figure_items::abs_cubic_curve>, cpt1, cpt2, endPt);
				currentPoint = endPt;
			}
		};

		// cairo_brush

		inline cairo_brush::native_handle_type cairo_brush::native_handle() const noexcept {
			return _Brush.get();
		}

		inline cairo_brush::cairo_brush(const rgba_color& color)
			: _Brush()
			, _Image_surface()
			, _Brush_type(brush_type::solid_color) {
			_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_rgba(color.r(), color.g(), color.b(), color.a()), &cairo_pattern_destroy);
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
		}

		template <class InputIterator>
		inline cairo_brush::cairo_brush(const point_2d& begin, const point_2d& end, InputIterator first, InputIterator last)
			: _Brush()
			, _Image_surface()
			, _Brush_type(brush_type::linear) {
			_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_linear(begin.x, begin.y, end.x, end.y), &cairo_pattern_destroy);
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

			for (auto it = first; it != last; ++it) {
				auto stop = *it;
				cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
			}
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
		}

		inline cairo_brush::cairo_brush(const point_2d& begin, const point_2d& end, ::std::initializer_list<gradient_stop> il)
			: _Brush()
			, _Image_surface()
			, _Brush_type(brush_type::linear) {
			_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_linear(begin.x, begin.y, end.x, end.y), &cairo_pattern_destroy);
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

			for (const gradient_stop& stop : il) {
				cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
			}

			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
		}

		template <class InputIterator>
		inline cairo_brush::cairo_brush(const circle& start, const circle& end, InputIterator first, InputIterator last)
			: _Brush()
			, _Image_surface()
			, _Brush_type(brush_type::radial) {
			_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(start.center().x, start.center().y, start.radius(), end.center().x, end.center().y, end.radius()), &cairo_pattern_destroy);
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
			for (auto it = first; it != last; ++it) {
				auto stop = *it;
				cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
			}
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
		}

		inline cairo_brush::cairo_brush(const circle& start, const circle& end, ::std::initializer_list<gradient_stop> il)
			: _Brush()
			, _Image_surface()
			, _Brush_type(brush_type::radial) {
			_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(start.center().x, start.center().y, start.radius(), end.center().x, end.center().y, end.radius()), &cairo_pattern_destroy);
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

			for (const gradient_stop& stop : il) {
				cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
			}

			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
		}

		inline cairo_brush::cairo_brush(cairo_image_surface&& img)
			: _Brush()
			, _Image_surface(make_shared<cairo_image_surface>(::std::move(img)))
			, _Brush_type(brush_type::surface) {
//			_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_for_surface(_Image_surface.get()->native_handle().csfce), &cairo_pattern_destroy);
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
		}

		inline brush_type cairo_brush::type() const noexcept {
			return _Brush_type;
		}

		// cairo_surface

		template <class Allocator>
		inline void cairo_surface::fill(const brush& b, const path_builder<Allocator>& pf, const optional<brush_props>& bp, const optional<render_props>& rp, const optional<clip_props>& cl) {
			interpreted_path pg(pf);
			fill(b, pg, bp, rp, cl);
		}

		template <class Allocator>
		inline void cairo_surface::stroke(const brush& b, const path_builder<Allocator>& pf, const optional<brush_props>& bp, const optional<stroke_props>& sp, const optional<dashes>& d, const optional<render_props>& rp, const optional<clip_props>& cl) {
			interpreted_path pg(pf);
			stroke(b, pg, bp, sp, d, rp, cl);
		}

		// cairo_mapped_surface

		inline cairo_mapped_surface::cairo_mapped_surface(surface::native_handle_type nh, surface::native_handle_type map_of)
			: _Mapped_surface(nh)
			, _Map_of(map_of) {
			assert(_Mapped_surface.csfce != nullptr && _Map_of.csfce != nullptr);
			auto status = cairo_surface_status(_Mapped_surface.csfce);
			if (status != CAIRO_STATUS_SUCCESS) {
				cairo_surface_unmap_image(_Mapped_surface.csfce, _Map_of.csfce);
				_Mapped_surface = { nullptr, nullptr };
				_Map_of = { nullptr, nullptr };
				_Throw_if_failed_cairo_status_t(status);
			}
			// Reference the surface that is mapped to ensure it isn't accidentally destroyed while the map still exists.
			cairo_surface_reference(_Map_of.csfce);
		}

		inline cairo_mapped_surface::cairo_mapped_surface(surface::native_handle_type nh, surface::native_handle_type map_of, error_code& ec) noexcept
			: _Mapped_surface(nh)
			, _Map_of(map_of) {
			assert(_Mapped_surface.csfce != nullptr && _Map_of.csfce != nullptr);
			auto status = cairo_surface_status(_Mapped_surface.csfce);
			if (status != CAIRO_STATUS_SUCCESS) {
				cairo_surface_unmap_image(_Mapped_surface.csfce, _Map_of.csfce);
				_Mapped_surface = { nullptr, nullptr };
				_Map_of = { nullptr, nullptr };
				ec = make_error_code(errc::not_supported);
				return;
			}
			// Reference the surface that is mapped to ensure it isn't accidentally destroyed while the map still exists.
			cairo_surface_reference(_Map_of.csfce);
			ec.clear();
		}

		inline cairo_mapped_surface::~cairo_mapped_surface() {
			if (_Mapped_surface.csfce != nullptr) {
				cairo_surface_unmap_image(_Map_of.csfce, _Mapped_surface.csfce);
				// Remove the reference we added to the surface that was mapped.
				cairo_surface_destroy(_Map_of.csfce);
				_Mapped_surface.csfce = nullptr;
				_Map_of.csfce = nullptr;
			}
		}

		inline void cairo_mapped_surface::commit_changes() {
			cairo_surface_mark_dirty(_Mapped_surface.csfce);
		}

		inline void cairo_mapped_surface::commit_changes(::std::error_code& ec) noexcept {
			cairo_surface_mark_dirty(_Mapped_surface.csfce);
			ec.clear();
		}

		inline unsigned char* cairo_mapped_surface::data() {
			auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
			if (result == nullptr) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
			}
			return result;
		}

		inline unsigned char* cairo_mapped_surface::data(error_code& ec) noexcept {
			auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
			if (result == nullptr) {
				ec = make_error_code(errc::state_not_recoverable);
				return result;
			}
			ec.clear();
			return result;
		}

		inline const unsigned char* cairo_mapped_surface::data() const {
			auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
			if (result == nullptr) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
			}
			return result;
		}

		inline const unsigned char* cairo_mapped_surface::data(error_code& ec) const noexcept {
			auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
			if (result == nullptr) {
				ec = make_error_code(errc::state_not_recoverable);
				return result;
			}
			ec.clear();
			return result;
		}

		inline ::std::experimental::io2d::format cairo_mapped_surface::format() const noexcept {
			if (cairo_surface_status(_Mapped_surface.csfce) != CAIRO_STATUS_SUCCESS) {
				return experimental::io2d::format::invalid;
			}
			return _Cairo_format_t_to_format(cairo_image_surface_get_format(_Mapped_surface.csfce));
		}

		inline int cairo_mapped_surface::width() const noexcept {
			if (format() == experimental::io2d::format::invalid) {
				return 0;
			}
			return cairo_image_surface_get_width(_Mapped_surface.csfce);
		}

		inline int cairo_mapped_surface::height() const noexcept {
			if (format() == experimental::io2d::format::invalid) {
				return 0;
			}
			return cairo_image_surface_get_height(_Mapped_surface.csfce);
		}

		inline int cairo_mapped_surface::stride() const noexcept {
			if (format() == experimental::io2d::format::invalid) {
				return 0;
			}
			return cairo_image_surface_get_stride(_Mapped_surface.csfce);
		}
	}
}