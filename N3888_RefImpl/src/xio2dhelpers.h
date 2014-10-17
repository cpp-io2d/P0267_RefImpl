#pragma once

#ifndef _XIO2DHELPERS_
#define _XIO2DHELPERS_

#include "io2d.h"

#define _PI 3.1415926535897932384626433832795

inline void _Throw_if_failed_cairo_status_t(::cairo_status_t s) {
	if (s != CAIRO_STATUS_SUCCESS) {
		throw ::std::system_error(s);
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
T _Degrees_to_radians(T degrees) {
	return degrees * static_cast<T>(3.1415926535897932384626433832795L) / static_cast<T>(180.0L);
}

::std::vector<::std::experimental::io2d::path_data> _Get_arc_as_beziers(const ::std::experimental::io2d::point& center, double radius, double angle1, double angle2, bool arcNegative = false, bool hasCurrentPoint = false, const ::std::experimental::io2d::point& currentPoint = { }, const ::std::experimental::io2d::point& origin = { }, const ::std::experimental::io2d::matrix_2d& matrix = ::std::experimental::io2d::matrix_2d::init_identity());

#endif