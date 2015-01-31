#pragma once

#ifndef _XIO2DHELPERS_
#define _XIO2DHELPERS_

#include "io2d.h"
#include <system_error>
#include <limits>
#include <cmath>

// Throws a system_error with an error_code formed from the 's' argument with a category from io2d_category(). 
inline void _Throw_if_failed_cairo_status_t(::cairo_status_t s) {
	assert(s != CAIRO_STATUS_LAST_STATUS && s != CAIRO_STATUS_INVALID_POP_GROUP);
	if (s != CAIRO_STATUS_SUCCESS) {
		if (s == CAIRO_STATUS_NO_MEMORY) {
			throw ::std::bad_alloc{ };
		}
		else {
			if (s == CAIRO_STATUS_INVALID_FORMAT || s == CAIRO_STATUS_INVALID_CONTENT) {
				if (s == CAIRO_STATUS_INVALID_FORMAT) {
					throw ::std::invalid_argument{ "A format type parameter is invalid." };
				}
				else {
					throw ::std::invalid_argument{ "A content type parameter is invalid." };
				}
			}
			else {
				if (s == CAIRO_STATUS_INVALID_INDEX || s == CAIRO_STATUS_INVALID_SIZE) {
					throw ::std::out_of_range{ "An index or size parameter has an invalid value." };
				}
				else {
					if (s == CAIRO_STATUS_SURFACE_TYPE_MISMATCH
						|| s == CAIRO_STATUS_PATTERN_TYPE_MISMATCH
						|| s == CAIRO_STATUS_FONT_TYPE_MISMATCH
						|| s == CAIRO_STATUS_DEVICE_TYPE_MISMATCH
						|| s == CAIRO_STATUS_DEVICE_FINISHED
						|| s == CAIRO_STATUS_TEMP_FILE_ERROR
						|| s == CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED
						|| s == CAIRO_STATUS_INVALID_VISUAL
						|| s == CAIRO_STATUS_INVALID_DSC_COMMENT
						|| s == CAIRO_STATUS_INVALID_SLANT
						|| s == CAIRO_STATUS_INVALID_WEIGHT) {
						throw ::std::system_error(::std::make_error_code(CAIRO_STATUS_INVALID_STATUS));
					}
					else {
						if (s == CAIRO_STATUS_FILE_NOT_FOUND) {
							throw ::std::system_error(::std::make_error_code(::std::errc::no_such_file_or_directory));
						}
					}
				}
			}
			throw ::std::system_error(::std::make_error_code(s));
		}
	}
}

// Checks for equality between two doubles.
// See: http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
inline bool _Almost_equal_relative(double a, double b, double epsilon = ::std::numeric_limits<double>::epsilon()) {
	auto diff = ::std::abs(a - b);
	a = ::std::abs(a);
	b = ::std::abs(b);
	auto largest = (b > a) ? b : a;
	if (diff <= largest * epsilon) {
		return true;
	}
	return false;
}

inline ::std::experimental::io2d::point _Rotate_point_absolute_angle(const ::std::experimental::io2d::point& center, double radius, double angle, bool clockwise = true) {
	if (clockwise) {
		::std::experimental::io2d::point pt{ radius * ::std::cos(angle), -radius * -::std::sin(angle) };
		pt.x(pt.x() + center.x());
		pt.y(pt.y() + center.y());
		return pt;
	}
	else {
		::std::experimental::io2d::point pt{ radius * ::std::cos(angle), -radius * ::std::sin(angle) };
		pt.x(pt.x() + center.x());
		pt.y(pt.y() + center.y());
		return pt;
	}
}

// Converts 'value' to an int and returns it. If nearestNeighbor is true, the return value is the result of calling 'static_cast<int>(round(value))'; if false, the return value is the result of calling 'static_cast<int>(trunc(value))'. 
inline int _Double_to_int(double value, bool nearestNeighbor = true) {
	if (nearestNeighbor) {
		// Round to the nearest neighbor.
		return static_cast<int>(::std::round(value));
	}
	// Otherwise truncate.
	return static_cast<int>(::std::trunc(value));
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

::std::vector<::std::unique_ptr<::std::experimental::io2d::path_data>> _Get_arc_as_beziers(const ::std::experimental::io2d::point& center, double radius, double angle1, double angle2, bool arcNegative = false, bool hasCurrentPoint = false, const ::std::experimental::io2d::point& currentPoint = { }, const ::std::experimental::io2d::point& origin = { }, const ::std::experimental::io2d::matrix_2d& matrix = ::std::experimental::io2d::matrix_2d::init_identity());

inline double _Clamp_to_normal(double value) {
	return ::std::max(::std::min(value, 1.0), 0.0);
}

// Note: The resulting image_surface does not maintain its own memory store.
inline ::std::experimental::io2d::image_surface _Surface_create_image_surface_copy(::std::experimental::io2d::surface& original) {
	original.flush();
	auto originalImageMap = original.map_to_image();
	auto width = originalImageMap.get_width();
	auto height = originalImageMap.get_height();
	auto format = originalImageMap.get_format();
	auto data = originalImageMap.get_data();
	auto stride = originalImageMap.get_stride();
	original.unmap_image(originalImageMap);
	auto result = ::std::experimental::io2d::image_surface(original, format, width, height);
	assert((width == result.get_width()) && (height == result.get_height()) && (stride == result.get_stride()));
	result.set_data(data);
	return ::std::move(result);
}

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				// Forward declarations.
				class point;
				class rgba_color;

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

				rgba_color operator*(const rgba_color& lhs, double rhs);
				rgba_color operator*(double lhs, const rgba_color& rhs);
				rgba_color& operator*=(rgba_color& lhs, double rhs);
				bool operator==(const rgba_color& lhs, const rgba_color& rhs);
				bool operator!=(const rgba_color& lhs, const rgba_color& rhs);
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}

#endif
