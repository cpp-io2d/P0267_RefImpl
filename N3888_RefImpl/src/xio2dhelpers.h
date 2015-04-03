#pragma once

#ifndef _XIO2DHELPERS_
#define _XIO2DHELPERS_

#include "io2d.h"
#include <system_error>
#include <limits>
#include <cmath>

// Creates the appropriate error_code for a given cairo_status_t value.
// cairo_status_t values which are implementation detail errors are all mapped to make_error_code(io2d_error::invalid_status).
inline ::std::error_code _Cairo_status_t_to_std_error_code(cairo_status_t cs) noexcept{
	switch (cs) {
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 14, 0)
	case CAIRO_STATUS_JBIG2_GLOBAL_MISSING:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
#endif
	case CAIRO_STATUS_SUCCESS:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::success);
	case CAIRO_STATUS_NO_MEMORY:
		return ::std::make_error_code(::std::errc::not_enough_memory);
	case CAIRO_STATUS_INVALID_RESTORE:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_restore);
	case CAIRO_STATUS_INVALID_POP_GROUP:
		assert(false && "Unexpected value CAIRO_STATUS_INVALID_POP_GROUP.");
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	case CAIRO_STATUS_NO_CURRENT_POINT:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::no_current_point);
	case CAIRO_STATUS_INVALID_MATRIX:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_matrix);
	case CAIRO_STATUS_INVALID_STATUS:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	case CAIRO_STATUS_NULL_POINTER:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::null_pointer);
	case CAIRO_STATUS_INVALID_STRING:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_string);
	case CAIRO_STATUS_INVALID_PATH_DATA:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_path_data);
	case CAIRO_STATUS_READ_ERROR:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::read_error);
	case CAIRO_STATUS_WRITE_ERROR:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::write_error);
	case CAIRO_STATUS_SURFACE_FINISHED:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::surface_finished);
	case CAIRO_STATUS_SURFACE_TYPE_MISMATCH:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	case CAIRO_STATUS_PATTERN_TYPE_MISMATCH:
		assert(false && "Unexpected value CAIRO_STATUS_PATTERN_TYPE_MISMATCH.");
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	case CAIRO_STATUS_INVALID_CONTENT:
		return ::std::make_error_code(::std::errc::invalid_argument);
	case CAIRO_STATUS_INVALID_FORMAT:
		return ::std::make_error_code(::std::errc::invalid_argument);
	case CAIRO_STATUS_INVALID_VISUAL:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	case CAIRO_STATUS_FILE_NOT_FOUND:
		return ::std::make_error_code(::std::errc::no_such_file_or_directory);
	case CAIRO_STATUS_INVALID_DASH:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_dash);
	case CAIRO_STATUS_INVALID_DSC_COMMENT:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	case CAIRO_STATUS_INVALID_INDEX:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_index);
	case CAIRO_STATUS_CLIP_NOT_REPRESENTABLE:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::clip_not_representable);
	case CAIRO_STATUS_TEMP_FILE_ERROR:
		// Even though it's an I/O error, this is an implementation detail error and as such is invalid_status.
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	case CAIRO_STATUS_INVALID_STRIDE:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_stride);
	case CAIRO_STATUS_FONT_TYPE_MISMATCH:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	case CAIRO_STATUS_USER_FONT_IMMUTABLE:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::user_font_immutable);
	case CAIRO_STATUS_USER_FONT_ERROR:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::user_font_error);
	case CAIRO_STATUS_NEGATIVE_COUNT:
		return ::std::make_error_code(::std::errc::invalid_argument);
	case CAIRO_STATUS_INVALID_CLUSTERS:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_clusters);
	case CAIRO_STATUS_INVALID_SLANT:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	case CAIRO_STATUS_INVALID_WEIGHT:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	case CAIRO_STATUS_INVALID_SIZE:
		return ::std::make_error_code(::std::errc::invalid_argument);
	case CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED:
		assert(false && "CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED encountered but the API doesn't expose user fonts so this status should never occur. What happened?");
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	case CAIRO_STATUS_DEVICE_TYPE_MISMATCH:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	case CAIRO_STATUS_DEVICE_ERROR:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::device_error);
	case CAIRO_STATUS_INVALID_MESH_CONSTRUCTION:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_mesh_construction);
	case CAIRO_STATUS_DEVICE_FINISHED:
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	case CAIRO_STATUS_LAST_STATUS:
		assert(false && "Unexpected value CAIRO_STATUS_LAST_STATUS. The runtime version of cairo is likely newer than the version of cairo this library was compiled against.");
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	default:
		assert(false && "Unknown cairo_status_t value caught by default case. The runtime version of cairo is likely newer than the version of cairo this library was compiled against.");
		return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
	}
}


// Throws a system_error with an error_code formed from the 's' argument with a category from io2d_category().
inline void _Throw_if_failed_cairo_status_t(::cairo_status_t s) {
	assert(s != CAIRO_STATUS_LAST_STATUS && s != CAIRO_STATUS_INVALID_POP_GROUP);
	if (s != CAIRO_STATUS_SUCCESS) {
		if (s == CAIRO_STATUS_NO_MEMORY) {
			throw ::std::bad_alloc{ };
		}
		else {
			if (s == CAIRO_STATUS_INVALID_FORMAT || s == CAIRO_STATUS_INVALID_CONTENT || s == CAIRO_STATUS_INVALID_SIZE) {
				if (s == CAIRO_STATUS_INVALID_FORMAT) {
					throw ::std::invalid_argument{ "The value of a format type argument is invalid." };
				}
				else {
					if (s == CAIRO_STATUS_INVALID_CONTENT) {
						throw ::std::invalid_argument{ "The value of a content type argument is invalid." };
					}
					else {
						throw ::std::invalid_argument{ "A value of a size parameter is invalid." };
					}
				}
			}
			else {
				if (s == CAIRO_STATUS_INVALID_INDEX) {
					throw ::std::out_of_range{ "An index parameter has an invalid value." };
				}
			}

			throw ::std::system_error(_Cairo_status_t_to_std_error_code(s));
		}
	}
}

// Checks for equality between two floating point numbers using an epsilon value to specify the equality tolerance limit.
// See: http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
template <typename T>
inline bool _Almost_equal_relative(T a, T b, T epsilon = ::std::numeric_limits<T>::epsilon()) noexcept {
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

::std::vector<::std::experimental::io2d::path_data_item> _Get_arc_as_beziers(const ::std::experimental::io2d::point& center, double radius, double angle1, double angle2, bool arcNegative = false, bool hasCurrentPoint = false, const ::std::experimental::io2d::point& currentPoint = { }, const ::std::experimental::io2d::point& origin = { }, const ::std::experimental::io2d::matrix_2d& matrix = ::std::experimental::io2d::matrix_2d::init_identity());

::std::vector<::std::experimental::io2d::path_data_item> _Get_arc_as_beziers(const ::std::experimental::io2d::point& center, double radius, double angle1, double angle2, ::std::error_code& ec, bool arcNegative = false, bool hasCurrentPoint = false, const ::std::experimental::io2d::point& currentPoint = { }, const ::std::experimental::io2d::point& origin = { }, const ::std::experimental::io2d::matrix_2d& matrix = ::std::experimental::io2d::matrix_2d::init_identity()) noexcept;

void _Get_arc_extents(const ::std::experimental::io2d::point& center, double radius, double angle1, double angle2, bool arcNegative, bool& hasCurrentPoint, ::std::experimental::io2d::point& currentPoint, bool& hasExtents, ::std::experimental::io2d::point& pt0, ::std::experimental::io2d::point& pt1, ::std::experimental::io2d::point& origin, ::std::experimental::io2d::matrix_2d& transformMatrix) noexcept;

inline double _Clamp_to_normal(double value) {
	return ::std::max(::std::min(value, 1.0), 0.0);
}

// Note: The resulting image_surface does not maintain its own memory store.
inline ::std::experimental::io2d::image_surface _Surface_create_image_surface_copy(::std::experimental::io2d::surface& original) {
	original.flush();
	auto originalImageMap = original.map_to_image();
	auto width = originalImageMap.width();
	auto height = originalImageMap.height();
	auto format = originalImageMap.format();
	auto data = originalImageMap.data();
	auto stride = originalImageMap.stride();
	original.unmap_image(originalImageMap);
	auto result = ::std::experimental::io2d::image_surface(original, format, width, height);
	assert((width == result.width()) && (height == result.height()) && (stride == result.stride()));
	result.data(data);
	return ::std::move(result);
}

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				// Forward declarations.
				class rgba_color;

				rgba_color operator*(const rgba_color& lhs, double rhs);
				rgba_color operator*(double lhs, const rgba_color& rhs);
				rgba_color& operator*=(rgba_color& lhs, double rhs);
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}

#endif
