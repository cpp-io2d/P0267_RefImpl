#pragma once

#ifndef _XIO2DHELPERS_
#define _XIO2DHELPERS_

#include "io2d.h"
#include <system_error>
#include <limits>
#include <cmath> // Needed for atan2

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				// Creates the appropriate error_code for a given cairo_status_t value.
				// cairo_status_t values which are implementation detail errors are all mapped to make_error_code(io2d_error::invalid_status).
				inline ::std::error_code _Cairo_status_t_to_std_error_code(cairo_status_t cs) noexcept {
					switch (cs) {
#if CAIRO_VERSION >= CAIRO_VERSION_ENCODE(1, 14, 0)
					case CAIRO_STATUS_JBIG2_GLOBAL_MISSING:
						assert(false && "Unexpected post cairo 1.12.16 value CAIRO_STATUS_JBIG2_GLOBAL_MISSING, though this should not occur due to cairo's compatibility guarantee.");
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
						assert(false && "CAIRO_STATUS_NEGATIVE_COUNT should not occur because the library API should prevent the existence of negative count values.");
						return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
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
						assert(false && "Unexpected value CAIRO_STATUS_LAST_STATUS. The runtime version of cairo is likely newer than the version of cairo this implementation was compiled against.");
						return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
					default:
						assert(false && "Unknown cairo_status_t value caught by default case. The runtime version of cairo is likely newer than the version of cairo this implementation was compiled against, though this still should not occur due to cairo's compatibility guarantee.");
						return ::std::make_error_code(::std::experimental::io2d::io2d_error::invalid_status);
					}
				}

				// Throws an exception of type:
				// -  bad_alloc : If the value of s is CAIRO_STATUS_NO_MEMORY.
				// -  invalid_argument: If the value of s is CAIRO_STATUS_INVALID_FORMAT, CAIRO_STATUS_INVALID_CONTENT, or CAIRO_STATUS_INVALID_SIZE.
				// -  out_of_range : If the value of s is CAIRO_STATUS_INVALID_INDEX.
				// -  system_error : For all other s values, with its error_code being the return value of _Cairo_status_t_to_std_error_code(s).
				// If the value of s is CAIRO_STATUS_LAST_STATUS, CAIRO_STATUS_INVALID_POP_GROUP, CAIRO_STATUS_NEGATIVE_COUNT, CAIRO_STATUS_PATTERN_TYPE_MISMATCH,
				// CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED, or an unknown value, it triggers an assertion failure. If assertion checks are disabled, an exception
				// of type system_error with an error code of make_error_code(io2d_error::invalid_status) will be thrown.
				inline void _Throw_if_failed_cairo_status_t(::cairo_status_t s) {
					assert(s != CAIRO_STATUS_LAST_STATUS && s != CAIRO_STATUS_INVALID_POP_GROUP && s != CAIRO_STATUS_NEGATIVE_COUNT);
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
				inline bool _Almost_equal_relative(T a, T b, T epsilon = ::std::numeric_limits<T>::epsilon()) noexcept{
					auto diff = ::std::abs(a - b);
					a = ::std::abs(a);
					b = ::std::abs(b);
					auto largest = (b > a) ? b : a;
					if (diff <= largest * epsilon) {
						return true;
					}
					return false;
				}

				// Returns the result of adding 'center' to the result of rotating the point { 'radius', 0.0 } 'angle' radians around { 0.0, 0.0 } in a clockwise ('clockwise' == true) or
				// counterclockwise ('clockwise' == false) direction.
				inline ::std::experimental::io2d::vector_2d _Rotate_point_absolute_angle(const ::std::experimental::io2d::vector_2d& center, double radius, double angle, bool clockwise = true) {
					if (clockwise) {
						::std::experimental::io2d::vector_2d pt{ radius * ::std::cos(angle), -(radius * -::std::sin(angle)) };
						pt.x(pt.x() + center.x());
						pt.y(pt.y() + center.y());
						return pt;
					}
					else {
						::std::experimental::io2d::vector_2d pt{ radius * ::std::cos(angle), radius * -::std::sin(angle) };
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
				inline int _Container_size_to_int(const T& container) noexcept{
					assert(container.size() <= static_cast<unsigned int>(::std::numeric_limits<int>::max()));
					return static_cast<int>(container.size());
				}

				template <typename T>
				T _Degrees_to_radians(T degrees) {
					return degrees * pi<T>() / static_cast<T>(180.0L);
				}

				vector_2d _Curve_point_at_t(const vector_2d& startPt, const vector_2d& controlPt1, const vector_2d& controlPt2, const vector_2d& endPt, double t) noexcept;

				::std::vector<::std::experimental::io2d::path_data_item> _Get_arc_as_beziers(const ::std::experimental::io2d::vector_2d& center, double radius, double angle1, double angle2, bool arcNegative = false, bool hasCurrentPoint = false, const ::std::experimental::io2d::vector_2d& currentPoint = { }, const ::std::experimental::io2d::vector_2d& origin = { }, const ::std::experimental::io2d::matrix_2d& matrix = ::std::experimental::io2d::matrix_2d::init_identity());

				::std::vector<::std::experimental::io2d::path_data_item> _Get_arc_as_beziers(const ::std::experimental::io2d::vector_2d& center, double radius, double angle1, double angle2, ::std::error_code& ec, bool arcNegative = false, bool hasCurrentPoint = false, const ::std::experimental::io2d::vector_2d& currentPoint = { }, const ::std::experimental::io2d::vector_2d& origin = { }, const ::std::experimental::io2d::matrix_2d& matrix = ::std::experimental::io2d::matrix_2d::init_identity()) noexcept;

				void _Get_arc_extents(const ::std::experimental::io2d::vector_2d& center, double radius, double angle1, double angle2, bool arcNegative, bool& hasCurrentPoint, ::std::experimental::io2d::vector_2d& currentPoint, ::std::experimental::io2d::vector_2d& transformedCurrentPoint, ::std::experimental::io2d::vector_2d& lastMoveToPoint, bool& hasExtents, ::std::experimental::io2d::vector_2d& pt0, ::std::experimental::io2d::vector_2d& pt1, ::std::experimental::io2d::vector_2d& origin, ::std::experimental::io2d::matrix_2d& transformMatrix) noexcept;

				void _Curve_to_extents(const ::std::experimental::io2d::vector_2d& pt0, const ::std::experimental::io2d::vector_2d& pt1, const ::std::experimental::io2d::vector_2d& pt2, const ::std::experimental::io2d::vector_2d& pt3, ::std::experimental::io2d::vector_2d& extents0, ::std::experimental::io2d::vector_2d& extents1) noexcept;

				inline double _Clamp_to_normal(double value) {
					return ::std::max(::std::min(value, 1.0), 0.0);
				}

				// Note: The resulting image_surface does not maintain its own memory store.
				inline ::std::experimental::io2d::image_surface _Surface_create_image_surface_copy(::std::experimental::io2d::surface& original) {
					if (!original.has_surface_resource()) {
						throw invalid_argument("Surface to be copied has no surface resource.");
					}
					if (original.is_finished()) {
						_Throw_if_failed_cairo_status_t(CAIRO_STATUS_SURFACE_FINISHED);
					}

					original.flush();
					::std::vector<unsigned char> data;
					int width = 0;
					int height = 0;
					::std::experimental::io2d::format fmt = ::std::experimental::io2d::format::invalid;
					int stride = 0;
					original.map([&data, &width, &height, &fmt, &stride](::std::experimental::io2d::mapped_surface& ms) -> void {
						width = ms.width();
						height = ms.height();
						stride = ms.stride();
						fmt = ms.format();
						auto size = static_cast<vector<unsigned char>::size_type>(height * stride);
						data.resize(size);
						switch (fmt)
						{
						case std::experimental::io2d::format::invalid:
							throw invalid_argument("Unexpected surface format 'format::invalid'.");
						case std::experimental::io2d::format::argb32:
							::std::memcpy(data.data(), ms.data(), size);
							break;
						case std::experimental::io2d::format::xrgb32:
							::std::memcpy(data.data(), ms.data(), size);
							break;
						case std::experimental::io2d::format::a8:
							::std::memcpy(data.data(), ms.data(), size);
							break;
						case std::experimental::io2d::format::a1:
							::std::memcpy(data.data(), ms.data(), size);
							break;
						case std::experimental::io2d::format::rgb16_565:
							::std::memcpy(data.data(), ms.data(), size);
							break;
						case std::experimental::io2d::format::rgb30:
							::std::memcpy(data.data(), ms.data(), size);
							break;
						default:
							assert(false && "Unknown format enumerator.");
							throw logic_error("Unknown format type.");
						}
					});
					auto result = ::std::experimental::io2d::image_surface(original, fmt, width, height);
					assert((width == result.width()) && (height == result.height()) && (stride == result.stride()));
					result.data(data);
					return ::std::move(result);
				}

				// Error codes:
				// errc::not_enough_memory
				// 
				inline void _Surface_create_image_surface_copy(::std::experimental::io2d::surface& original, ::std::experimental::io2d::image_surface& result, ::std::error_code& ec) noexcept {
					if (!original.has_surface_resource()) {
						ec = make_error_code(errc::invalid_argument);
						return;
					}
					if (original.is_finished()) {
						ec = make_error_code(io2d_error::surface_finished);
						return;
					}

					original.flush(ec);
					if (static_cast<bool>(ec)) {
						return;
					}

					::std::vector<unsigned char> data;
					int width = 0;
					int height = 0;
					::std::experimental::io2d::format fmt = ::std::experimental::io2d::format::invalid;
					int stride = 0;
					original.map([&data, &width, &height, &fmt, &stride](::std::experimental::io2d::mapped_surface& ms, ::std::error_code& ec) -> void {
						width = ms.width();
						height = ms.height();
						stride = ms.stride();
						fmt = ms.format();
						auto size = static_cast<vector<unsigned char>::size_type>(height * stride);
						if (size > data.max_size()) {
							ec = ::std::make_error_code(::std::errc::not_enough_memory);
							return;
						}
						try {
							data.resize(size);
						}
						catch (const ::std::bad_alloc&) {
							ec = ::std::make_error_code(::std::errc::not_enough_memory);
							return;
						}
						
						switch (fmt)
						{
						case std::experimental::io2d::format::invalid:
							ec = ::std::make_error_code(::std::errc::invalid_argument);
							break;
						case std::experimental::io2d::format::argb32:
							::std::memcpy(data.data(), ms.data(ec), size);
							break;
						case std::experimental::io2d::format::xrgb32:
							::std::memcpy(data.data(), ms.data(ec), size);
							break;
						case std::experimental::io2d::format::a8:
							::std::memcpy(data.data(), ms.data(ec), size);
							break;
						case std::experimental::io2d::format::a1:
							::std::memcpy(data.data(), ms.data(ec), size);
							break;
						case std::experimental::io2d::format::rgb16_565:
							::std::memcpy(data.data(), ms.data(ec), size);
							break;
						case std::experimental::io2d::format::rgb30:
							::std::memcpy(data.data(), ms.data(ec), size);
							break;
						default:
							assert(false && "Unknown format enumerator.");
							ec = ::std::make_error_code(::std::errc::invalid_argument);
							break;
						}
						if (static_cast<bool>(ec)) {
							return;
						}
						ec.clear();
					}, ec);
					if (static_cast<bool>(ec)) {
						return;
					}

					result = ::std::experimental::io2d::image_surface(original, fmt, width, height, ec);
					if (static_cast<bool>(ec)) {
						return;
					}

					assert((width == result.width()) && (height == result.height()) && (stride == result.stride()));

					result.data(data, ec);
					if (static_cast<bool>(ec)) {
						return;
					}
					ec.clear();
				}

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
