#ifndef _XIO2D_H_
#define _XIO2D_H_

#include <limits>
#include <cmath>
#include <cassert>
#include <type_traits>
#include <memory>
#include <functional>
#include <utility>
#include <exception>
#include <vector>
#include <string>
#include <algorithm>
#include <system_error>
#include <cstdint>
#include <atomic>
#include <variant>
#include <optional>
#include <initializer_list>
#include <cmath>
#include <chrono>

#define __cpp_lib_experimental_io2d 201710

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

#if __has_include(<magick/api.h>)
    #define _IO2D_Has_Magick
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

				template <class T, ::std::enable_if_t<::std::is_floating_point_v<T>, _To_radians_sfinae> = _To_radians_sfinae_val>
				constexpr T degrees_to_radians(T deg) noexcept {
					auto angle = deg / static_cast<T>(360.0L) * two_pi<T>;
					T oneThousandthOfADegreeInRads = pi<T> / static_cast<T>(180'000.0L);
					if (((angle > static_cast<T>(0.0L)) && (angle < oneThousandthOfADegreeInRads)) || ((angle < static_cast<T>(0.0L)) && (-angle < oneThousandthOfADegreeInRads))) {
						return (angle < static_cast<T>(0.0L)) ? static_cast<T>(-0.0L) : static_cast<T>(0.0L);
					}
					return angle;
				}

				template <class T, ::std::enable_if_t<::std::is_floating_point_v<T>, _To_degrees_sfinae> = _To_degrees_sfinae_val>
				constexpr T radians_to_degrees(T rad) noexcept {
					auto angle = static_cast<float>(rad) / two_pi<float> * 360.0F;
					T oneThousandthOfADegree = static_cast<T>(0.001L);
					if (((angle > static_cast<T>(0.0L)) && (angle < oneThousandthOfADegree)) || ((angle < static_cast<T>(0.0L)) && (-angle < oneThousandthOfADegree))) {
						return (angle < static_cast<T>(0.0L)) ? -static_cast<T>(0.0L) : static_cast<T>(0.0L);
					}
					return angle;
				}
			}
		}
	}
}

#include "xbrushes.h"
#include "xcolor.h"
#include "xdiagnostics.h"
#include "xgraphicsmath.h"
#include "xgraphicsmathfloat.h"
#include "xinput.h"
#include "xio2d.h"
#include "xpath.h"
#include "xsurfaces_enums.h"
#include "xsurfaces.h"
#include "xtext.h"
#include "xbrushes_impl.h"
#include "xgraphicsmath_impl.h"
#include "xgraphicsmathfloat_impl.h"
#include "xio2d_impl.h"
#include "xpath_impl.h"
#include "xpathbuilder_impl.h"
#include "xsurfaces_impl.h"
#include "xsurfacesprops_impl.h"
#include "xinterchangebuffer.h"

#endif // _XIO2D_H_
