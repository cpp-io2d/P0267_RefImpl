#pragma once

#ifndef _XIO2DHELPERS_
#define _XIO2DHELPERS_

#include "io2d.h"

inline void _Throw_if_failed_cairo_status_t(::cairo_status_t s) {
	if (s != CAIRO_STATUS_SUCCESS) {
		throw ::std::system_error(::std::error_code(s, ::std::experimental::io2d::io2d_category()));
	}
}

// Converts 'value' to an int and returns it. If nearestNeighbor is true, the return value is the result of calling 'static_cast<int>(round(value))'; if false, the return value is the result of calling 'static_cast<int>(trunc(value))'. 
inline int _Double_to_int(double value, bool nearestNeighbor = true) {
	if (nearestNeighbor) {
		// Round to the nearest neighbor.
		return static_cast<int>(round(value));
	}
	// Otherwise truncate.
	return static_cast<int>(trunc(value));
}

template <typename T>
inline int _Container_size_to_int(const T& container) {
	assert(container.size() <= static_cast<unsigned int>(::std::numeric_limits<int>::max()));
	return static_cast<int>(container.size());
}

template <typename T>
T _Degrees_to_radians(T degrees) {
	return degrees * static_cast<T>(3.1415926535897932384626433832795L) / static_cast<T>(180.0L);
}

inline ::std::vector<::std::unique_ptr<::std::experimental::io2d::path_data>> _Get_arc_as_beziers(const ::std::experimental::io2d::point& center, double radius, double angle1, double angle2, bool arcNegative = false, bool hasCurrentPoint = false, const ::std::experimental::io2d::point& currentPoint = { }, const ::std::experimental::io2d::point& origin = { }, const ::std::experimental::io2d::matrix_2d& matrix = ::std::experimental::io2d::matrix_2d::init_identity());

inline double _Clamp_to_normal(double value) {
	return ::std::max(::std::min(value, 1.0), 0.0);
}

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				point operator+(const point& lhs);
				point operator+(const point& lhs, const point& rhs);
				point operator+(const point& lhs, double rhs);
				point operator+(double lhs, const point& rhs);
				point& operator+=(point& lhs, const point& rhs);
				point& operator+=(point& lhs, double rhs);
				point operator-(const point& lhs);
				point operator-(const point& lhs, const point& rhs);
				point operator-(const point& lhs, double rhs);
				point operator-(double lhs, const point& rhs);
				point& operator-=(point& lhs, const point& rhs);
				point& operator-=(point& lhs, double rhs);
				point operator*(const point& lhs, const point& rhs);
				point operator*(const point& lhs, double rhs);
				point operator*(double lhs, const point& rhs);
				point& operator*=(point& lhs, const point& rhs);
				point& operator*=(point& lhs, double rhs);
				point operator/(const point& lhs, const point& rhs);
				point operator/(const point& lhs, double rhs);
				point operator/(double lhs, const point& rhs);
				point& operator/=(point& lhs, const point& rhs);
				point& operator/=(point& lhs, double rhs);
				bool operator==(const point& lhs, const point& rhs);
				bool operator!=(const point& lhs, const point& rhs);
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}

#endif