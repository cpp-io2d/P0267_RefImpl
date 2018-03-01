#pragma once

#ifndef _XIO2D_
#define _XIO2D_

#include <limits>
#include <cmath>
#include <cassert>
#include <type_traits>

#define __cpp_lib_experimental_io2d 201710

////
//#if ((defined(_MSC_VER) && ((_MSC_VER >= 1910) || (defined(__clang__) && (_MSC_VER >= 1900)))) || defined(HAVE_FILESYSTEM))
//#define _Filesystem_support_test
//#endif

//#define HAVE_FILESYSTEM
//#include <experimental/filesystem>
//namespace std::filesystem {
//    using path = ::std::experimental::filesystem::path;
//}

#if __has_include(<filesystem>)
    #define _IO2D_Has_Filesystem
    #include <filesystem>
#elif __has_include(<experimental/filesystem>)
    #define _IO2D_Has_Filesystem
    #include <experimental/filesystem>
    namespace std::filesystem {
        using path = ::std::experimental::filesystem::path;
    }
#endif

#if defined BUILD_IO2D_API_DLL 
#define _IO2D_API __declspec(dllexport)
#elif defined USE_IO2D_API_DLL
#define _IO2D_API __declspec(dllimport)
#else
#define _IO2D_API
#endif

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				template <class T>
				constexpr T pi = T(3.14159265358979323846264338327950288L);

				template <class T>
				constexpr T two_pi = T(6.28318530717958647692528676655900577L);

				template <class T>
				constexpr T half_pi = T(1.57079632679489661923132169163975144L);

				template <class T>
				constexpr T three_pi_over_two = T(4.71238898038468985769396507491925432L);

				template <class T>
				constexpr T tau = T(6.28318530717958647692528676655900577L);

				template <class T>
				constexpr T three_quarters_tau = T(4.71238898038468985769396507491925432L);

				template <class T>
				constexpr T half_tau = T(3.14159265358979323846264338327950288L);

				template <class T>
				constexpr T quarter_tau = T(1.57079632679489661923132169163975144L);

				constexpr float _Round_floating_point_to_zero(float v) noexcept {
					if ((v > 0.0f && v < ::std::numeric_limits<float>::epsilon() * 1000.0F) ||
						(v < 0.0f && -v < ::std::numeric_limits<float>::epsilon() * 1000.0F)) {
						return (v > 0.0f) ? 0.0f : -0.0f;
					}
					return v;
				}

				// Converts 'value' to an int and returns it. If nearestNeighbor is true, the return value is the result of calling 'static_cast<int>(round(value))'; if false, the return value is the result of calling 'static_cast<int>(trunc(value))'.
				inline int _Float_to_int(float value, bool nearestNeighbor = true) {
					if (nearestNeighbor) {
						// Round to the nearest neighbor.
						return static_cast<int>(::std::round(value));
					}
					// Otherwise truncate.
					return static_cast<int>(::std::trunc(value));
				}

				template <typename T>
				inline int _Container_size_to_int(const T& container) noexcept {
					assert(container.size() <= static_cast<unsigned int>(::std::numeric_limits<int>::max()));
					return static_cast<int>(container.size());
				}

				enum class _To_radians_sfinae {};
				constexpr static _To_radians_sfinae _To_radians_sfinae_val = {};
				enum class _To_degrees_sfinae {};
				constexpr static _To_degrees_sfinae _To_degrees_sfinae_val = {};

				template <class T, ::std::enable_if_t<::std::is_arithmetic_v<T>, _To_radians_sfinae> = _To_radians_sfinae_val>
				constexpr float to_radians(T deg) noexcept {
					auto angle = static_cast<float>(deg) / 360.0F * two_pi<float>;
					float oneThousandthOfADegreeInRads = pi<float> / 180'000.0F;
					if (((angle > 0.0F) && (angle < oneThousandthOfADegreeInRads)) || ((angle < 0.0F) && (-angle < oneThousandthOfADegreeInRads))) {
						return (angle < 0.0F) ? -0.0F : 0.0F;
					}
					return angle;
				}

				template <class T, ::std::enable_if_t<::std::is_arithmetic_v<T>, _To_degrees_sfinae> = _To_degrees_sfinae_val>
				constexpr float to_degrees(T rad) noexcept {
					auto angle = static_cast<float>(rad) / two_pi<float> * 360.0F;
					float oneThousandthOfADegree = 0.001F;
					if (((angle > 0.0F) && (angle < oneThousandthOfADegree)) || ((angle < 0.0F) && (-angle < oneThousandthOfADegree))) {
						return (angle < 0.0F) ? -0.0F : 0.0F;
					}
					return angle;
				}
			}
		}
	}
}

//// Designed to be used to conditionally define compiler support for inline namespaces using a #if
////define _Inline_namespace_conditional_support_test ((__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190022609))
//
//// Designed to be used to conditionally define compiler support for UDLs using a #if
////define _User_defined_literal_conditional_support_test ((__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190022203))
//
//// Designed to be used to conditionally define compiler support for noexcept using a #if
////define _Noexcept_conditional_support_test ((__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190022203))
//
//// Designed to be used to conditionally define compiler support for constexpr using a #if
////define _Constexpr_conditional_support_test ((__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190022203))
//
////define _Variable_templates_conditional_support_test ((__cplusplus >= 201402L) || _MSC_FULL_VER >= 190023918)
//#endif
//namespace std {
//	namespace experimental {
//		namespace io2d {
//			inline namespace v1 {
//				enum class _Round_floating_point_to_zero_sfinae {};
//				constexpr _Round_floating_point_to_zero_sfinae _Round_floating_point_to_zero_sfinae_val{};
//
//				template <class T, enable_if_t<::std::is_floating_point_v<T>, _Round_floating_point_to_zero_sfinae> = _Round_floating_point_to_zero_sfinae_val>
//				constexpr T _Round_floating_point_to_zero(T v) noexcept {
//					if ((v > static_cast<T>(0.0F) && v < ::std::numeric_limits<T>::epsilon() * 1000.0F) ||
//						(v < static_cast<T>(0.0F) && -v < ::std::numeric_limits<T>::epsilon() * 1000.0F)) {
//						return (v > static_cast<T>(0.0F)) ? static_cast<T>(0.0F) : static_cast<T>(-0.0F);
//					}
//					return v;
//				}
//			}
//		}
//	}
//}
#endif
