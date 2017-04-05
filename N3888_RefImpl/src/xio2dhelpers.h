#pragma once

#ifndef _XIO2DHELPERS_
#define _XIO2DHELPERS_

//#include "io2d.h"
#include <system_error>
#include <limits>
#include <cmath> // Needed for atan2
#include <cstring> // Needed for memcpy
#include <iterator> // Needed for distance
#include <algorithm> // Needed for copy_n

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				//template <typename T>
				//T _Degrees_to_radians(T degrees) {
				//	return degrees * pi<T>() / static_cast<T>(180.0L);
				//}

				//vector_2d _Curve_point_at_t(const vector_2d& startPt, const vector_2d& controlPt1, const vector_2d& controlPt2, const vector_2d& endPt, double t) noexcept;

				//::std::vector<path_data::path_data_types> _Get_arc_as_beziers(const ::std::experimental::io2d::vector_2d& center, double radius, double angle1, double angle2, bool path_arcNegative = false, bool hasCurrentPoint = false, const ::std::experimental::io2d::vector_2d& currentPoint = { }, const ::std::experimental::io2d::vector_2d& origin = { }, const ::std::experimental::io2d::matrix_2d& matrix = ::std::experimental::io2d::matrix_2d::init_identity());

				//::std::vector<path_data::path_data_types> _Get_arc_as_beziers(const ::std::experimental::io2d::vector_2d& center, double radius, double angle1, double angle2, ::std::error_code& ec, bool path_arcNegative = false, bool hasCurrentPoint = false, const ::std::experimental::io2d::vector_2d& currentPoint = { }, const ::std::experimental::io2d::vector_2d& origin = { }, const ::std::experimental::io2d::matrix_2d& matrix = ::std::experimental::io2d::matrix_2d::init_identity()) noexcept;

				//void _Get_arc_extents(const ::std::experimental::io2d::vector_2d& center, double radius, double angle1, double angle2, bool path_arcNegative, bool& hasCurrentPoint, ::std::experimental::io2d::vector_2d& currentPoint, ::std::experimental::io2d::vector_2d& transformedCurrentPoint, ::std::experimental::io2d::vector_2d& lastMoveToPoint, bool& hasExtents, ::std::experimental::io2d::vector_2d& pt0, ::std::experimental::io2d::vector_2d& pt1, ::std::experimental::io2d::vector_2d& origin, ::std::experimental::io2d::matrix_2d& transformMatrix) noexcept;

				//void _Curve_to_extents(const ::std::experimental::io2d::vector_2d& pt0, const ::std::experimental::io2d::vector_2d& pt1, const ::std::experimental::io2d::vector_2d& pt2, const ::std::experimental::io2d::vector_2d& pt3, ::std::experimental::io2d::vector_2d& extents0, ::std::experimental::io2d::vector_2d& extents1) noexcept;

				//inline double _Clamp_to_normal(double value) {
				//	return ::std::max(::std::min(value, 1.0), 0.0);
				//}

				// Forward declarations.
				class bgra_color;

				constexpr bgra_color operator*(const bgra_color& lhs, double rhs);
				constexpr bgra_color operator*(double lhs, const bgra_color& rhs);
				bgra_color& operator*=(bgra_color& lhs, double rhs);

				//inline ::std::vector<path_data::path_data_types> _Cairo_path_data_t_array_to_path_data_item_vector(const cairo_path_t& cpt) {
				//	::std::vector<path_data::path_data_types> vec;
				//	_Throw_if_failed_cairo_status_t(cpt.status);
				//	vector_2d lastMoveToPt{};
				//	for (auto i = 0; i < cpt.num_data; i += cpt.data[i].header.length) {
				//		auto type = cpt.data[i].header.type;
				//		switch (type)
				//		{
				//		case CAIRO_PATH_CLOSE_PATH:
				//		{
				//			vec.emplace_back(path_data::close_path(lastMoveToPt));
				//		} break;
				//		case CAIRO_PATH_CURVE_TO:
				//		{
				//			vec.emplace_back(path_data::abs_cubic_curve({ cpt.data[i + 1].point.x, cpt.data[i + 1].point.y }, { cpt.data[i + 2].point.x, cpt.data[i + 2].point.y }, { cpt.data[i + 3].point.x, cpt.data[i + 3].point.y }));
				//		} break;
				//		case CAIRO_PATH_LINE_TO:
				//		{
				//			vec.emplace_back(path_data::abs_line({ cpt.data[i + 1].point.x, cpt.data[i + 1].point.y }));
				//		} break;
				//		case CAIRO_PATH_MOVE_TO:
				//		{
				//			lastMoveToPt = { cpt.data[i + 1].point.x, cpt.data[i + 1].point.y };
				//			vec.emplace_back(path_data::abs_move({ cpt.data[i + 1].point.x, cpt.data[i + 1].point.y }));
				//		} break;
				//		default:
				//		{
				//			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
				//		} break;
				//		}
				//	}

				//	return vec;
				//}

				//inline ::std::vector<path_data::path_data_types> _Cairo_path_data_t_array_to_path_data_item_vector(const cairo_path_t& cpt, ::std::error_code& ec) noexcept {
				//	::std::vector<path_data::path_data_types> vec;
				//	vector_2d lastMoveToPt{};
				//	ec = _Cairo_status_t_to_std_error_code(cpt.status);
				//	if (static_cast<bool>(ec)) {
				//		return vec;
				//	}
				//	::std::vector<path_data::path_data_types>::size_type reqSize{};
				//	for (auto i = 0; i < cpt.num_data; i += cpt.data[i].header.length) {
				//		reqSize++;
				//	}
				//	try {
				//		vec.reserve(reqSize);
				//	}
				//	catch (const ::std::length_error&) {
				//		ec = ::std::make_error_code(::std::errc::not_enough_memory);
				//		return vec;
				//	}
				//	catch (const ::std::bad_alloc&) {
				//		ec = ::std::make_error_code(::std::errc::not_enough_memory);
				//		return vec;
				//	}

				//	for (auto i = 0; i < cpt.num_data; i += cpt.data[i].header.length) {
				//		auto type = cpt.data[i].header.type;
				//		switch (type)
				//		{
				//		case CAIRO_PATH_CLOSE_PATH:
				//		{
				//			vec.emplace_back(path_data::close_path(lastMoveToPt));
				//		} break;
				//		case CAIRO_PATH_CURVE_TO:
				//		{
				//			vec.emplace_back(path_data::abs_cubic_curve({ cpt.data[i + 1].point.x, cpt.data[i + 1].point.y }, { cpt.data[i + 2].point.x, cpt.data[i + 2].point.y }, { cpt.data[i + 3].point.x, cpt.data[i + 3].point.y }));
				//		} break;
				//		case CAIRO_PATH_LINE_TO:
				//		{
				//			vec.emplace_back(path_data::abs_line({ cpt.data[i + 1].point.x, cpt.data[i + 1].point.y }));
				//		} break;
				//		case CAIRO_PATH_MOVE_TO:
				//		{
				//			lastMoveToPt = { cpt.data[i + 1].point.x, cpt.data[i + 1].point.y };
				//			vec.emplace_back(path_data::abs_move({ cpt.data[i + 1].point.x, cpt.data[i + 1].point.y }));
				//		} break;
				//		default:
				//		{
				//			ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_PATH_DATA);
				//			return vec;
				//		} break;
				//		}
				//	}

				//	ec.clear();
				//	return vec;
				//}
			}
		}
	}
}

#endif
