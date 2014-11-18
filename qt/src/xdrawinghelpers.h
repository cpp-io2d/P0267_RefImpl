#pragma once
#include "drawing.h"

#define _PI 3.1415926535897932384626433832795

inline void _Throw_if_failed_status(::std::experimental::drawing::status s) {
	if (s != ::std::experimental::drawing::status::success) {
		throw ::std::experimental::drawing::drawing_exception(s);
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
