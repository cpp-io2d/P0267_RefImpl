#pragma once

#ifndef _XIO2D_
#define _XIO2D_
//
//#include <map>
//#include <cassert>
//#include <cstdint>
//#include <tuple>
//#include <mutex>
//#include <cmath>
//#include <utility>
//#include <stack>
//#include <array>
//#include <sstream>
//#include <ios>
//#include <type_traits>
//#include <limits>
//
#if ((defined(_MSC_VER) && ((_MSC_VER >= 1910) || (defined(__clang__) && (_MSC_VER >= 1900)))) || defined(HAVE_FILESYSTEM))
#define _Filesystem_support_test
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
