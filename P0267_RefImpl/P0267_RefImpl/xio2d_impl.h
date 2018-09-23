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

//#ifdef _Filesystem_support_test
//#include <filesystem>
//#endif

#include "xsurfaces.h"
#include "xpath.h"

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				//// Checks for equality between two floating point numbers using an epsilon value to specify the equality tolerance limit.
				//// See: http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
				//template <typename T>
				//inline bool _Almost_equal_relative(T a, T b, T epsilon = ::std::numeric_limits<T>::epsilon()) noexcept {
				//	auto diff = ::std::abs(a - b);
				//	a = ::std::abs(a);
				//	b = ::std::abs(b);
				//	auto largest = (b > a) ? b : a;
				//	if (diff <= largest * epsilon) {
				//		return true;
				//	}
				//	return false;
				//}


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
                    return *this = (*this * rhs);
                }
                
				template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating>>
				inline constexpr rgba_color& rgba_color::operator*=(U rhs) noexcept {
                    return *this = (*this * rhs); 
				}

				inline constexpr bool operator==(const rgba_color& lhs, const rgba_color& rhs) noexcept {
					return lhs.r() == rhs.r() && lhs.g() == rhs.g() && lhs.b() == rhs.b() && lhs.a() == rhs.a();
				}
				inline constexpr bool operator!=(const rgba_color& lhs, const rgba_color& rhs) noexcept {
					return !(lhs == rhs);
				}

				template <class T, ::std::enable_if_t<::std::is_floating_point_v<T>, _Color_is_floating>>
				inline constexpr rgba_color operator*(const rgba_color& lhs, T rhs) noexcept {
                    auto m = ::std::max(::std::min(static_cast<float>(rhs), 1.0F), 0.0F);
					return{
                        ::std::min(lhs.r() * m, 1.0F),
                        ::std::min(lhs.g() * m, 1.0F),
                        ::std::min(lhs.b() * m, 1.0F),
                        ::std::min(lhs.a() * m, 1.0F)
					};
				}

				template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral>>
				inline constexpr rgba_color operator*(const rgba_color& lhs, T rhs) noexcept {
                    return lhs * (rhs / 255.0F);
				}

				template <class T, ::std::enable_if_t<::std::is_floating_point_v<T>, _Color_is_floating>>
				inline constexpr rgba_color operator*(T lhs, const rgba_color& rhs) noexcept {
                    return rhs * lhs;
				}

				template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral>>
				inline constexpr rgba_color operator*(T lhs, const rgba_color& rhs) noexcept {
                    return rhs * lhs;
				}

				inline rgba_color rgba_from_HSL(float hue, float saturation, float luminescence) noexcept
				{
					auto chroma = 1.0f - fabs(2.0f * luminescence - 1.0f) * saturation;
					auto hue_segment = hue / 60.0f;
					auto int_part = floorf(hue_segment);
					auto rem_part = hue_segment - int_part;
					auto x = chroma * (1.0f - fabs(rem_part - 1.0f + float(int(int_part) % 2)));
					auto m = luminescence - chroma / 2.0f;
					if (hue_segment <= 1.0f) return rgba_color{ chroma + m, x + m, m, 1.0f };
					if (hue_segment <= 2.0f) return rgba_color{ x + m, chroma + m, m, 1.0f };
					if (hue_segment <= 3.0f) return rgba_color{ m, chroma + m, x + m, 1.0f };
					if (hue_segment <= 4.0f) return rgba_color{ m, x + m, chroma + m, 1.0f };
					if (hue_segment <= 5.0f) return rgba_color{ x + m, m, chroma + m, 1.0f };
					if (hue_segment <= 6.0f) return rgba_color{ chroma + m, m, x + m, 1.0f };
                    return {};
				}

				inline rgba_color rgba_from_HSV(float hue, float saturation, float value) noexcept
				{
					auto chroma = value * saturation;
					auto hue_segment = hue / 60.0f;
					auto int_part = floorf(hue_segment);
					auto rem_part = hue_segment - int_part;
					auto x = chroma * (1.0f - fabs(rem_part - 1.0f + float(int(int_part) % 2)));
					auto m = value - chroma;
					if (hue_segment <= 1.0f) return rgba_color{ chroma + m, x + m, m, 1.0f };
					if (hue_segment <= 2.0f) return rgba_color{ x + m, chroma + m, m, 1.0f };
					if (hue_segment <= 3.0f) return rgba_color{ m, chroma + m, x + m, 1.0f };
					if (hue_segment <= 4.0f) return rgba_color{ m, x + m, chroma + m, 1.0f };
					if (hue_segment <= 5.0f) return rgba_color{ x + m, m, chroma + m, 1.0f };
					if (hue_segment <= 6.0f) return rgba_color{ chroma + m, m, x + m, 1.0f };
                    return {};
				}
			}
		}
	}
}
