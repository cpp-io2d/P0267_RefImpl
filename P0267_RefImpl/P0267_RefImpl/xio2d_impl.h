#pragma once
#include "xio2d.h"

#include <memory>
#include <functional>
#include <exception>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <system_error>
#include <cstdint>
#include <atomic>
#include <variant>
#include <optional>
#include <cmath>
#include <type_traits>
#include <initializer_list>
#include <cmath>
#include <utility>

#ifdef _Filesystem_support_test
#include <filesystem>
#endif

#include "xsurfaces.h"
#include "xpath.h"

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
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

				// Returns the result of adding 'center' to the result of rotating the point { 'radius', 0.0F } 'angle' radians around { 0.0F, 0.0F } in a clockwise ('clockwise' == true) or
				// counterclockwise ('clockwise' == false) direction.
				template <class GraphicsMath>
				inline basic_point_2d<GraphicsMath> _Rotate_point_absolute_angle(const basic_point_2d<GraphicsMath>& center, float radius, float angle, bool clockwise = true) {
					if (clockwise) {
						return basic_point_2d<GraphicsMath>((radius * ::std::cos(angle)) + center.x(), (-(radius * -::std::sin(angle))) + center.y());
					}
					else {
						return basic_point_2d<GraphicsMath>((radius * ::std::cos(angle)) + center.x(), (radius * -::std::sin(angle)) + center.y());
					}
				}

				// color

				inline constexpr rgba_color::rgba_color() noexcept { }
				template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral>>
				inline constexpr rgba_color::rgba_color(T r, T g, T b, T a) noexcept
					: _R(static_cast<float>(::std::min<float>(::std::max<float>((r / 255.0F), 0.0F), 1.0F)))
					, _G(static_cast<float>(::std::min<float>(::std::max<float>((g / 255.0F), 0.0F), 1.0F)))
					, _B(static_cast<float>(::std::min<float>(::std::max<float>((b / 255.0F), 0.0F), 1.0F)))
					, _A(static_cast<float>(::std::min<float>(::std::max<float>((a / 255.0F), 0.0F), 1.0F))) { }
				template <class T, ::std::enable_if_t<::std::is_floating_point_v<T>, _Color_is_floating>>
				inline constexpr rgba_color::rgba_color(T r, T g, T b, T a) noexcept
					: _R(static_cast<float>(::std::min<T>(::std::max<T>(static_cast<float>(r), 0.0F), 1.0F)))
					, _G(static_cast<float>(::std::min<T>(::std::max<T>(static_cast<float>(g), 0.0F), 1.0F)))
					, _B(static_cast<float>(::std::min<T>(::std::max<T>(static_cast<float>(b), 0.0F), 1.0F)))
					, _A(static_cast<float>(::std::min<T>(::std::max<T>(static_cast<float>(a), 0.0F), 1.0F))) {
				}

				template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral>>
				inline constexpr void rgba_color::r(T val) noexcept {
					_R = val * _A;
				}

				template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating>>
				inline constexpr void rgba_color::r(U val) noexcept {
					_R = val * _A;
				}

				template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral>>
				inline constexpr void rgba_color::g(T val) noexcept {
					_G = val * _A;
				}

				template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating>>
				inline constexpr void rgba_color::g(U val) noexcept {
					_G = val * _A;
				}

				template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral>>
				inline constexpr void rgba_color::b(T val) noexcept {
					_B = val * _A;
				}

				template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating>>
				inline constexpr void rgba_color::b(U val) noexcept {
					_B = val * _A;
				}

				template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral>>
				inline constexpr void rgba_color::a(T val) noexcept {
					_A = val;
				}

				template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating>>
				inline constexpr void rgba_color::a(U val) noexcept {
					_A = val;
				}

				inline constexpr float rgba_color::r() const noexcept {
					return _R;
				}
				inline constexpr float rgba_color::g() const noexcept {
					return _G;
				}
				inline constexpr float rgba_color::b() const noexcept {
					return _B;
				}
				inline constexpr float rgba_color::a() const noexcept {
					return _A;
				}

				template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral>>
				inline constexpr rgba_color& rgba_color::operator*=(T rhs) noexcept {
					r(::std::min(r() * rhs / 255.0F, 1.0F));
					g(::std::min(g() * rhs / 255.0F, 1.0F));
					b(::std::min(b() * rhs / 255.0F, 1.0F));
					a(::std::min(a() * rhs / 255.0F, 1.0F));
					return *this;
				}
				template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating>>
				inline constexpr rgba_color& rgba_color::operator*=(U rhs) noexcept {
					r(::std::min(r() * rhs, 1.0F));
					g(::std::min(g() * rhs, 1.0F));
					b(::std::min(b() * rhs, 1.0F));
					a(::std::min(a() * rhs, 1.0F));
					return *this;
				}

				inline constexpr bool operator==(const rgba_color& lhs, const rgba_color& rhs) noexcept {
					return lhs.r() == rhs.r() && lhs.g() == rhs.g() && lhs.b() == rhs.b() && lhs.a() == rhs.a();
				}
				inline constexpr bool operator!=(const rgba_color& lhs, const rgba_color& rhs) noexcept {
					return !(lhs == rhs);
				}

				template <class T, ::std::enable_if_t<::std::is_floating_point_v<T>, _Color_is_floating>>
				inline constexpr rgba_color operator*(const rgba_color& lhs, T rhs) noexcept {
					rhs = ::std::max(::std::min(rhs, 1.0F), 0.0F);
					return{
						::std::min(lhs.r() * rhs, 1.0F),
						::std::min(lhs.g() * rhs, 1.0F),
						::std::min(lhs.b() * rhs, 1.0F),
						::std::min(lhs.a() * rhs, 1.0F)
					};
				}

				template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral>>
				inline constexpr rgba_color operator*(const rgba_color& lhs, T rhs) noexcept {
					rhs = ::std::max(::std::min(rhs, 1.0F), 0.0F);
					return{
						::std::min(lhs.r() * rhs / 255.0F, 1.0F),
						::std::min(lhs.g() * rhs / 255.0F, 1.0F),
						::std::min(lhs.b() * rhs / 255.0F, 1.0F),
						::std::min(lhs.a() * rhs / 255.0F, 1.0F)
					};
				}

				template <class T, ::std::enable_if_t<::std::is_floating_point_v<T>, _Color_is_floating>>
				inline constexpr rgba_color operator*(T lhs, const rgba_color& rhs) noexcept {
					lhs = ::std::max(::std::min(lhs, 1.0F), 0.0F);
					return{
						::std::min(lhs * rhs.r(), 1.0F),
						::std::min(lhs * rhs.g(), 1.0F),
						::std::min(lhs * rhs.b(), 1.0F),
						::std::min(lhs * rhs.a(), 1.0F)
					};
				}

				template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral>>
				inline constexpr rgba_color operator*(T lhs, const rgba_color& rhs) noexcept {
					lhs = ::std::max(::std::min(lhs, 1.0F), 0.0F);
					return{
						::std::min(lhs / 255.0F * rhs.r(), 1.0F),
						::std::min(lhs / 255.0F * rhs.g(), 1.0F),
						::std::min(lhs / 255.0F * rhs.b(), 1.0F),
						::std::min(lhs / 255.0F * rhs.a(), 1.0F)
					};
				}

				// Paths

						//Brushes

				//// Standalone functions

				//template <class GraphicsMath, class T>
				//inline image_surface<GraphicsMath, T> copy_image_surface(image_surface<GraphicsMath, T>& sfc) noexcept {
				//	image_surface<GraphicsMath, T> retval(sfc.format(), sfc.width(), sfc.height());
				//	retval.map([&sfc](mapped_surface<GraphicsMath, T>& rvms) {
				//		sfc.map([&rvms](mapped_surface<GraphicsMath, T>& sfcms) {
				//			memcpy(rvms.data(), sfcms.data(), static_cast<size_t>(rvms.height() * rvms.stride()));
				//		});
				//	});
				//	retval.mark_dirty();
				//	return retval;
				//}
			}
		}
	}
}