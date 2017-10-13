#pragma once
#include "xio2d.h"

#include <memory>
#include <functional>
#include <exception>
#include <vector>
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

#ifdef _Filesystem_support_test
#include <filesystem>
#endif

#include "xsurfaces.h"

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				enum class _Round_floating_point_to_zero_sfinae {};
				constexpr _Round_floating_point_to_zero_sfinae _Round_floating_point_to_zero_sfinae_val{};

				template <class T, enable_if_t<::std::is_floating_point_v<T>, _Round_floating_point_to_zero_sfinae> = _Round_floating_point_to_zero_sfinae_val>
				constexpr T _Round_floating_point_to_zero(T v) noexcept {
					if ((v > static_cast<T>(0.0F) && v < ::std::numeric_limits<T>::epsilon() * 1000.0F) ||
						(v < static_cast<T>(0.0F) && -v < ::std::numeric_limits<T>::epsilon() * 1000.0F)) {
						return (v > static_cast<T>(0.0F)) ? static_cast<T>(0.0F) : static_cast<T>(-0.0F);
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

				template <class GraphicsMath>
				inline basic_point_2d<GraphicsMath> point_for_angle(float ang, float mgn) noexcept {
					basic_point_2d<GraphicsMath> v{ mgn, 0.0F };
					auto m = basic_matrix_2d<GraphicsMath>::init_rotate(ang);
					auto result = m.transform_pt(v);
					result.x = _Round_floating_point_to_zero(result.x);
					result.y = _Round_floating_point_to_zero(result.y);
					return result;
				}

				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> point_for_angle(float ang, const basic_point_2d<GraphicsMath>& rad) noexcept {
					basic_point_2d<GraphicsMath> v{ 1.0F, 0.0F };
					auto m = basic_matrix_2d<GraphicsMath>::init_rotate(ang);
					auto result = m.transform_pt(v);
					result *= rad;
					result.x = _Round_floating_point_to_zero(result.x);
					result.y = _Round_floating_point_to_zero(result.y);
					return result;
				}

				template <class GraphicsMath>
				float angle_for_point(const basic_point_2d<GraphicsMath>& ctr, const basic_point_2d<GraphicsMath>& pt) noexcept {
					auto xDiff = pt.x() - ctr.x();
					auto yDiff = -(pt.y() - ctr.y());
					auto angle = atan2(yDiff, xDiff);
					const float oneThousandthOfADegreeInRads = pi<float> / 180'000.0F;
					if ((abs(angle) < oneThousandthOfADegreeInRads) || abs(angle - two_pi<float>) < oneThousandthOfADegreeInRads) {
						return 0.0F;
					}
					if (angle < 0.0F) {
						return angle + two_pi<float>;
					}
					return angle;
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

				// linear algebra

				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath>::basic_point_2d(const _Data_type& val) noexcept
					: _Data(val) {}

				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath>::basic_point_2d() noexcept
					: basic_point_2d<GraphicsMath>::point_2d(0.0f, 0.0f) {}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath>::basic_point_2d(float xval, float yval) noexcept
					: _Data(GraphicsMath::create_point_2d(xval, yval)) {
				}
				template <class GraphicsMath>
				inline constexpr void basic_point_2d<GraphicsMath>::x(float xval) noexcept {
					GraphicsMath::x(_Data, xval);
				}
				template <class GraphicsMath>
				inline constexpr void basic_point_2d<GraphicsMath>::y(float yval) noexcept {
					GraphicsMath::y(_Data, yval);
				}
				template <class GraphicsMath>
				inline constexpr float basic_point_2d<GraphicsMath>::x() const noexcept {
					return GraphicsMath::y(_Data);
				}
				template <class GraphicsMath>
				inline constexpr float basic_point_2d<GraphicsMath>::y() const noexcept {
					return GraphicsMath::y(_Data);
				}
				template <class GraphicsMath>
				inline float basic_point_2d<GraphicsMath>::magnitude() const noexcept {
					return GraphicsMath::magnitude(_Data);
				}
				template <class GraphicsMath>
				inline constexpr float basic_point_2d<GraphicsMath>::magnitude_squared() const noexcept {
					return GraphicsMath::magniture_square(_Data);
				}
				template <class GraphicsMath>
				inline constexpr float basic_point_2d<GraphicsMath>::dot(const basic_point_2d<GraphicsMath>& other) const noexcept {
					return GraphicsMath::dot(_Data, other._Data);
				}
				template <class GraphicsMath>
				inline float basic_point_2d<GraphicsMath>::angular_direction() const noexcept {
					return GraphicsMath::angular_direction(_Data);
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> basic_point_2d<GraphicsMath>::zero() noexcept {
					return point_2d(GraphicsMath::create());
				}
				template <class GraphicsMath>
				inline basic_point_2d<GraphicsMath> basic_point_2d<GraphicsMath>::to_unit() const noexcept {
					return point_2d(GraphicsMath::to_unit(_Data));
				}
				template <class GraphicsMath>
				inline constexpr bool operator==(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
					return GraphicsMath::equal(lhs._Get_data(), rhs._Get_data());
				}
				template <class GraphicsMath>
				inline constexpr bool operator!=(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
					return GraphicsMath::not_equal(lhs._Get_data(), rhs._Get_data());
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> operator+(const basic_point_2d<GraphicsMath>& lhs) noexcept {
					return lhs;
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> operator+(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
					return basic_point_2d<GraphicsMath>(GraphicsMath::add(lhs._Get_data(), rhs._Get_data()));
				}
				template <class GraphicsMath>
				inline constexpr \basic_point_2d<GraphicsMath> operator+(const basic_point_2d<GraphicsMath>& lhs, float rhs) noexcept {
					return basic_point_2d<GraphicsMath>(GraphicsMath::add(lhs._Get_data(), rhs));
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> operator+(float lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
					return basic_point_2d<GraphicsMath>(GraphicsMath::add(lhs, rhs._Get_data()));
				}
				template <class GraphicsMath>
				inline const basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator+=(const basic_point_2d<GraphicsMath>& rhs) noexcept {
					_Data = GraphicsMath::add(_Data, rhs._Data);
					return *this;
				}
				template <class GraphicsMath>
				inline const basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator+=(float rhs) noexcept {
					_Data = GraphicsMath::add(_Data, rhs);
					return *this;
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> operator-(const basic_point_2d<GraphicsMath>& lhs) noexcept {
					return basic_point_2d<GraphicsMath>(GraphicsMath::negate(lhs._Get_data()));
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> operator-(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
					return basic_point_2d<GraphicsMath>(GraphicsMath::subtract(lhs._Get_data(), rhs._Get_data()));
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> operator-(const basic_point_2d<GraphicsMath>& lhs, float rhs) noexcept {
					return basic_point_2d<GraphicsMath>(GraphicsMath::subtract(lhs._Get_data(), rhs));
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> operator-(float lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
					return basic_point_2d<GraphicsMath>(GraphicsMath::subtract(lhs, rhs._Get_data()));
				}
				template <class GraphicsMath>
				inline const basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator-=(const basic_point_2d<GraphicsMath>& rhs) noexcept {
					_Data = GraphicsMath::subtract(_Data, rhs._Get_data());
					return *this;
				}
				template <class GraphicsMath>
				inline const basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator-=(float rhs) noexcept {
					_Data = GraphicsMath::subtract(_Data, rhs);
					return *this;
				}
				template <class GraphicsMath>
				inline const basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator*=(float rhs) noexcept {
					_Data = GraphicsMath::multiply(_Data, rhs);
					return *this;
				}
				template <class GraphicsMath>
				inline const basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator*=(const basic_point_2d<GraphicsMath>& rhs) noexcept {
					_Data = GraphicsMath::multiply(_Data, rhs._Get_data());
					return *this;
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> operator*(const basic_point_2d<GraphicsMath>& lhs, float rhs) noexcept {
					return basic_point_2d<GraphicsMath>(GraphicsMath::multiply(lhs._Get_data(), rhs));
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> operator*(float lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
					return basic_point_2d<GraphicsMath>(GraphicsMath::multiply(lhs, rhs._Get_data()));
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> operator*(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
					return basic_point_2d<GraphicsMath>(GraphicsMath::multiply(lhs._Get_data(), rhs._Get_data()));
				}
				template <class GraphicsMath>
				inline const basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator/=(float rhs) noexcept {
					_Data = GraphicsMath::divide(_Data, rhs);
					return *this;
				}
				template <class GraphicsMath>
				inline const basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator/=(const basic_point_2d<GraphicsMath>& rhs) noexcept {
					_Data = GraphicsMath::divide(_Data, rhs._Get_data());
					return *this;
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> operator/(const basic_point_2d<GraphicsMath>& lhs, float rhs) noexcept {
					return basic_point_2d<GraphicsMath>(GraphicsMath::divide(lhs._Get_data(), rhs));
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> operator/(float lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
					return basic_point_2d<GraphicsMath>(GraphicsMath::divide(lhs, rhs._Get_data()));
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> operator/(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
					return basic_point_2d<GraphicsMath>(GraphicsMath::divide(lhs._Get_data(), rhs._Get_data()));
				}

				//
				// basic_linear_algebra::matrix_2d
				//

				template <class GraphicsMath>
				inline constexpr const typename GraphicsMath::matrix_2d_data_type& basic_matrix_2d<GraphicsMath>::_Get_data() const noexcept {
					return _Data;
				}
				template <class GraphicsMath>
				inline constexpr basic_matrix_2d<GraphicsMath>::basic_matrix_2d(const _Data_type& val) noexcept
					: _Data(val) {
				}
				template <class GraphicsMath>
				inline constexpr basic_matrix_2d<GraphicsMath>::basic_matrix_2d() noexcept
					: _Data(GraphicsMath::init_identity()) {}
				template <class GraphicsMath>
				inline constexpr basic_matrix_2d<GraphicsMath>::basic_matrix_2d(float v00, float v01, float v10, float v11, float v20, float v21) noexcept
					: _Data(GraphicsMath::init_values(v00, v01, v10, v11, v20, v21)) {
				}
				template <class GraphicsMath>
				inline constexpr void basic_matrix_2d<GraphicsMath>::m00(float val) noexcept {
					GraphicsMath::m00(val);
				}
				template <class GraphicsMath>
				inline constexpr void basic_matrix_2d<GraphicsMath>::m01(float val) noexcept {
					GraphicsMath::m01(val);
				}
				template <class GraphicsMath>
				inline constexpr void basic_matrix_2d<GraphicsMath>::m10(float val) noexcept {
					GraphicsMath::m10(_Data, val);
				}
				template <class GraphicsMath>
				inline constexpr void basic_matrix_2d<GraphicsMath>::m11(float val) noexcept {
					GraphicsMath::m11(val);
				}
				template <class GraphicsMath>
				inline constexpr void basic_matrix_2d<GraphicsMath>::m20(float val) noexcept {
					GraphicsMath::m20(val);
				}
				template <class GraphicsMath>
				inline constexpr void basic_matrix_2d<GraphicsMath>::m21(float val) noexcept {
					GraphicsMath::m21(val);
				}
				template <class GraphicsMath>
				inline constexpr float basic_matrix_2d<GraphicsMath>::m00() const noexcept {
					return GraphicsMath::m00();
				}
				template <class GraphicsMath>
				inline constexpr float basic_matrix_2d<GraphicsMath>::m01() const noexcept {
					return GraphicsMath::m01();
				}
				template <class GraphicsMath>
				inline constexpr float basic_matrix_2d<GraphicsMath>::m10() const noexcept {
					return GraphicsMath::m10();
				}
				template <class GraphicsMath>
				inline constexpr float basic_matrix_2d<GraphicsMath>::m11() const noexcept {
					return GraphicsMath::m11();
				}
				template <class GraphicsMath>
				inline constexpr float basic_matrix_2d<GraphicsMath>::m20() const noexcept {
					return GraphicsMath::m20();
				}
				template <class GraphicsMath>
				inline constexpr float basic_matrix_2d<GraphicsMath>::m21() const noexcept {
					return GraphicsMath::m21();
				}
				template <class GraphicsMath>
				inline constexpr typename basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::init_translate(const basic_point_2d<GraphicsMath>& value) noexcept {
					return basic_matrix_2d<GraphicsMath>(GraphicsMath::init_translate(value));
				}
				template <class GraphicsMath>
				inline constexpr typename basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::init_scale(const basic_point_2d<GraphicsMath>& value) noexcept {
					return basic_matrix_2d<GraphicsMath>(GraphicsMath::init_scale(value));
				}
				template <class GraphicsMath>
				inline typename basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::init_rotate(float radians) noexcept {
					return basic_matrix_2d<GraphicsMath>(GraphicsMath::init_rotate(radians));
				}
				template <class GraphicsMath>
				inline typename basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::init_rotate(float radians, const basic_point_2d<GraphicsMath>& origin) noexcept {
					return basic_matrix_2d<GraphicsMath>(GraphicsMath::init_rotate(radians, origin));
				}
				template <class GraphicsMath>
				inline typename basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::init_reflect(float radians) noexcept {
					return basic_matrix_2d<GraphicsMath>(GraphicsMath::init_reflect(radians));
				}
				template <class GraphicsMath>
				inline constexpr typename basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::init_shear_x(float factor) noexcept {
					return basic_matrix_2d<GraphicsMath>(GraphicsMath::init_shear_x(factor));
				}
				template <class GraphicsMath>
				inline constexpr typename basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::init_shear_y(float factor) noexcept {
					return basic_matrix_2d<GraphicsMath>(GraphicsMath::init_shear_y(factor));
				}
				template <class GraphicsMath>
				inline constexpr typename basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::translate(const basic_point_2d<GraphicsMath>& val) noexcept {
					GraphicsMath::translate(_Data, val);
					return *this;
				}
				template <class GraphicsMath>
				inline constexpr typename basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::scale(const basic_point_2d<GraphicsMath>& val) noexcept {
					GraphicsMath::scale(_Data, val);
					return *this;
				}
				template <class GraphicsMath>
				inline typename basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::rotate(float radians) noexcept {
					GraphicsMath::rotate(_Data, radians);
					return *this;
				}
				template <class GraphicsMath>
				inline typename basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::rotate(float radians, const basic_point_2d<GraphicsMath>& origin) noexcept {
					GraphicsMath::rotate(_Data, radians, origin);
					return *this;
				}
				template <class GraphicsMath>
				inline typename basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::reflect(float radians) noexcept {
					GraphicsMath::reflect(_Data, radians);
					return *this;
				}
				template <class GraphicsMath>
				inline constexpr typename basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::shear_x(float factor) noexcept {
					GraphicsMath::shear_x(_Data, factor);
					return *this;
				}
				template <class GraphicsMath>
				inline constexpr typename basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::shear_y(float factor) noexcept {
					GraphicsMath::shear_y(_Data, factor);
					return *this;
				}
				template <class GraphicsMath>
				inline constexpr bool basic_matrix_2d<GraphicsMath>::is_invertible() const noexcept {
					return GraphicsMath::is_invertible(_Data);
				}
				template <class GraphicsMath>
				inline constexpr typename basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::inverse() const noexcept {
					return GraphicsMath::inverse(_Data);
				}
				template <class GraphicsMath>
				inline constexpr bool basic_matrix_2d<GraphicsMath>::is_finite() const noexcept {
					return GraphicsMath::is_finite(_Data);
				}
				template <class GraphicsMath>
				inline constexpr float basic_matrix_2d<GraphicsMath>::determinant() const noexcept {
					return GraphicsMath::determinant(_Data);
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::transform_pt(const basic_point_2d<GraphicsMath>& pt) const noexcept {
					return GraphicsMath::transform_pt(_Data, pt);
				}
				template <class GraphicsMath>
				inline constexpr typename basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::operator*=(const basic_matrix_2d<GraphicsMath>& rhs) noexcept {
					_Data = GraphicsMath::multiply(_Data, rhs._Data);
					return *this;
				}
				template <class GraphicsMath>
				inline constexpr typename basic_matrix_2d<GraphicsMath> operator*(const basic_matrix_2d<GraphicsMath>& lhs, const basic_matrix_2d<GraphicsMath>& rhs) noexcept {
					return basic_matrix_2d<GraphicsMath>(GraphicsMath::multiply(lhs._Get_data(), rhs._Get_data()));
				}
				template <class GraphicsMath>
				inline constexpr bool operator==(const basic_matrix_2d<GraphicsMath>& lhs, const basic_matrix_2d<GraphicsMath>& rhs) noexcept {
					return GraphicsMath::equal(lhs._Get_data(), rhs._Get_data());
				}
				template <class GraphicsMath>
				inline constexpr bool operator!=(const basic_matrix_2d<GraphicsMath>& lhs, const basic_matrix_2d<GraphicsMath>& rhs) noexcept {
					return GraphicsMath::not_equal(lhs._Get_data(), rhs._Get_data());
				}
				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> operator*(const basic_point_2d<GraphicsMath>& pt, const basic_matrix_2d<GraphicsMath>& m) noexcept {
					return GraphicsMath::transform_pt(m, pt);
				}

				// basic_display_point
				template <class GraphicsMath>
				inline constexpr const typename basic_display_point<GraphicsMath>::_Data_type basic_display_point<GraphicsMath>::_Get_data() const noexcept {
					return _Data;
				}
				template <class GraphicsMatch>
				inline constexpr basic_display_point<GraphicsMath>::basic_display_point(const _Data_type& val) noexcept
					: _Data(val) {
				}
				template <class GraphicsMath>
				inline constexpr basic_display_point<GraphicsMath>::basic_display_point() noexcept
					: _Data(0, 0) {
				}
				template <class GraphicsMath>
				inline constexpr basic_display_point<GraphicsMath>::basic_display_point(int x, int y) noexcept
					: _Data(x, y) {
				}
				template <class GraphicsMath>
				inline constexpr void basic_display_point<GraphicsMath>::x(int val) noexcept {
					GraphicsMath::x(_Data, val);
				}
				template <class GraphicsMath>
				inline constexpr void basic_display_point<GraphicsMath>::y(int val) noexcept {
					GraphicsMath::y(_Data, val);
				}
				template <class GraphicsMath>
				inline constexpr int basic_display_point<GraphicsMath>::x() const noexcept {
					return GraphicsMath::x();
				}
				template <class GraphicsMath>
				inline constexpr int basic_display_point<GraphicsMath>::y() const noexcept {
					return GraphicsMath::y();
				}
				template <class GraphicsMath>
				inline constexpr bool operator==(const basic_display_point<GraphicsMath>& lhs, const basic_display_point<GraphicsMath>& rhs) noexcept {
					return GraphicsMath::equal(lhs._Get_data(), rhs._Get_data());
				}
				template <class GraphicsMath>
				inline constexpr bool operator!=(const basic_display_point<GraphicsMath>& lhs, const basic_display_point<GraphicsMath>& rhs) noexcept {
					return GraphicsMath::not_equal(lhs._Get_data(), rhs._Get_data());
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::create_point_2d() noexcept {
					return create_point_2d(0.0f, 0.0f);
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::create_point_2d(float x, float y) noexcept {
					auto result = _Linear_algebra_float_impl::point_2d_data_type();
					result._X = x;
					result._Y = y;
					return result;
				}

				inline void _Linear_algebra_float_impl::x(typename _Linear_algebra_float_impl::point_2d_data_type& val, float x) noexcept {
					val._X = x;
				}

				inline void _Linear_algebra_float_impl::y(typename _Linear_algebra_float_impl::point_2d_data_type& val, float y) noexcept {
					val._Y = y;
				}

				inline float _Linear_algebra_float_impl::x(const typename _Linear_algebra_float_impl::point_2d_data_type& val) noexcept {
					return val._X;
				}

				inline float _Linear_algebra_float_impl::y(const typename _Linear_algebra_float_impl::point_2d_data_type& val) noexcept {
					return val._Y;
				}

				inline float _Linear_algebra_float_impl::dot(const typename _Linear_algebra_float_impl::point_2d_data_type& a, const typename _Linear_algebra_float_impl::point_2d_data_type& b) noexcept {
					return a._X * b._X + a._Y * b._Y;
				}

				inline float _Linear_algebra_float_impl::magnitude(const typename _Linear_algebra_float_impl::point_2d_data_type& val) noexcept {
					return ::std::sqrt(val._X * val._X + val._Y * val._Y);
				}

				inline float _Linear_algebra_float_impl::magnitude_squared(const typename _Linear_algebra_float_impl::point_2d_data_type& val) noexcept {
					return val._X * val._X + val._Y * val._Y;
				}

				inline float _Linear_algebra_float_impl::angular_direction(const typename _Linear_algebra_float_impl::point_2d_data_type& val) noexcept {
					auto v = ::std::atan2(val._Y, val._X);
					if (v < 0.0F) {
						v += two_pi<float>;
					}
					return v;
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::to_unit(const typename _Linear_algebra_float_impl::point_2d_data_type& val) noexcept {
					auto leng = magnitude(val);
					auto result = val;
					result._X = val._X / leng;
					result._Y = val._Y / leng;
					return result;
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::add(const typename _Linear_algebra_float_impl::point_2d_data_type& lhs, const typename _Linear_algebra_float_impl::point_2d_data_type& rhs) noexcept {
					_Linear_algebra_float_impl::point_2d_data_type result;
					result._X = lhs._X + rhs._X;
					result._Y = lhs._Y + rhs._Y;
					return result;
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::add(const typename _Linear_algebra_float_impl::point_2d_data_type& lhs, float rhs) noexcept {
					_Linear_algebra_float_impl::point_2d_data_type result;
					result._X = lhs._X + rhs;
					result._Y = lhs._Y + rhs;
					return result;
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::add(float lhs, const typename _Linear_algebra_float_impl::point_2d_data_type& rhs) noexcept {
					_Linear_algebra_float_impl::point_2d_data_type result;
					result._X = lhs + rhs._X;
					result._Y = lhs + rhs._Y;
					return result;
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::subtract(const typename _Linear_algebra_float_impl::point_2d_data_type& lhs, const typename _Linear_algebra_float_impl::point_2d_data_type& rhs) noexcept {
					_Linear_algebra_float_impl::point_2d_data_type result;
					result._X = lhs._X - rhs._X;
					result._Y = lhs._Y - rhs._Y;
					return result;
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::subtract(const typename _Linear_algebra_float_impl::point_2d_data_type& lhs, float rhs) noexcept {
					_Linear_algebra_float_impl::point_2d_data_type result;
					result._X = lhs._X - rhs;
					result._Y = lhs._Y - rhs;
					return result;
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::subtract(float lhs, const typename _Linear_algebra_float_impl::point_2d_data_type& rhs) noexcept {
					_Linear_algebra_float_impl::point_2d_data_type result;
					result._X = lhs - rhs._X;
					result._Y = lhs - rhs._Y;
					return result;
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::multiply(const typename _Linear_algebra_float_impl::point_2d_data_type& lhs, const typename _Linear_algebra_float_impl::point_2d_data_type& rhs) noexcept {
					_Linear_algebra_float_impl::point_2d_data_type result;
					result._X = lhs._X * rhs._X;
					result._Y = lhs._Y * rhs._Y;
					return result;
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::multiply(const typename _Linear_algebra_float_impl::point_2d_data_type& lhs, float rhs) noexcept {
					_Linear_algebra_float_impl::point_2d_data_type result;
					result._X = lhs._X * rhs;
					result._Y = lhs._Y * rhs;
					return result;
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::multiply(float lhs, const typename _Linear_algebra_float_impl::point_2d_data_type& rhs) noexcept {
					_Linear_algebra_float_impl::point_2d_data_type result;
					result._X = lhs * rhs._X;
					result._Y = lhs * rhs._Y;
					return result;
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::divide(const typename _Linear_algebra_float_impl::point_2d_data_type& lhs, const typename _Linear_algebra_float_impl::point_2d_data_type& rhs) noexcept {
					_Linear_algebra_float_impl::point_2d_data_type result;
					result._X = lhs._X / rhs._X;
					result._Y = lhs._Y / rhs._Y;
					return result;
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::divide(const typename _Linear_algebra_float_impl::point_2d_data_type& lhs, float rhs) noexcept {
					_Linear_algebra_float_impl::point_2d_data_type result;
					result._X = lhs._X / rhs;
					result._Y = lhs._Y / rhs;
					return result;
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::divide(float lhs, const typename _Linear_algebra_float_impl::point_2d_data_type& rhs) noexcept {
					_Linear_algebra_float_impl::point_2d_data_type result;
					result._X = lhs / rhs._X;
					result._Y = lhs / rhs._Y;
					return result;
				}

				inline bool _Linear_algebra_float_impl::equal(const typename _Linear_algebra_float_impl::point_2d_data_type& lhs, const typename _Linear_algebra_float_impl::point_2d_data_type& rhs) noexcept {
					return lhs._X == rhs._X&& lhs._Y == rhs._Y;
				}

				inline bool _Linear_algebra_float_impl::not_equal(const typename _Linear_algebra_float_impl::point_2d_data_type& lhs, const typename _Linear_algebra_float_impl::point_2d_data_type& rhs) noexcept {
					return !equal(lhs, rhs);
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::negate(const typename _Linear_algebra_float_impl::point_2d_data_type& val) noexcept {
					return create_point_2d(-val._X, -val._Y);
				}

				inline constexpr typename _Linear_algebra_float_impl::matrix_2d_data_type _Linear_algebra_float_impl::create_matrix_2d() noexcept {
					auto result = matrix_2d_data_type();
					result.m00 = 1.0f;
					result.m01 = 0.0f;
					result.m02 = 0.0f;
					result.m10 = 0.0f;
					result.m11 = 1.0f;
					result.m12 = 0.0f;
					result.m20 = 0.0f;
					result.m21 = 0.0f;
					result.m22 = 1.0f;
					return result;
				}
				inline constexpr typename _Linear_algebra_float_impl::matrix_2d_data_type _Linear_algebra_float_impl::create_matrix_2d(float v00, float v01, float v10, float v11, float v20, float v21) noexcept {
					auto result = matrix_2d_data_type();
					result.m00 = v00;
					result.m01 = v01;
					result.m02 = 0.0f;
					result.m10 = v10;
					result.m11 = v11;
					result.m12 = 0.0f;
					result.m20 = v20;
					result.m21 = v21;
					result.m22 = 1.0f;
					return result;
				}
				inline constexpr void _Linear_algebra_float_impl::m00(matrix_2d_data_type& mtx, float val) noexcept {
					mtx.m00 = val;
				}
				inline constexpr void _Linear_algebra_float_impl::m01(matrix_2d_data_type& mtx, float val) noexcept {
					mtx.m01 = val;
				}
				inline constexpr void _Linear_algebra_float_impl::m10(matrix_2d_data_type& mtx, float val) noexcept {
					mtx.m10 = val;
				}
				inline constexpr void _Linear_algebra_float_impl::m11(matrix_2d_data_type& mtx, float val) noexcept {
					mtx.m11 = val;
				}
				inline constexpr void _Linear_algebra_float_impl::m20(matrix_2d_data_type& mtx, float val) noexcept {
					mtx.m20 = val;
				}
				inline constexpr void _Linear_algebra_float_impl::m21(matrix_2d_data_type& mtx, float val) noexcept {
					mtx.m21 = val;
				}
				inline constexpr float _Linear_algebra_float_impl::m00(const matrix_2d_data_type& mtx) noexcept {
					return mtx.m00;
				}
				inline constexpr float _Linear_algebra_float_impl::m01(const matrix_2d_data_type& mtx) noexcept {
					return mtx.m01;
				}
				inline constexpr float _Linear_algebra_float_impl::m10(const matrix_2d_data_type& mtx) noexcept {
					return mtx.m10;
				}
				inline constexpr float _Linear_algebra_float_impl::m11(const matrix_2d_data_type& mtx) noexcept {
					return mtx.m11;
				}
				inline constexpr float _Linear_algebra_float_impl::m20(const matrix_2d_data_type& mtx) noexcept {
					return mtx.m20;
				}
				inline constexpr float _Linear_algebra_float_impl::m21(const matrix_2d_data_type& mtx) noexcept {
					return mtx.m21;
				}
				inline constexpr typename _Linear_algebra_float_impl::matrix_2d_data_type _Linear_algebra_float_impl::init_identity() noexcept {
					return create_matrix_2d(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
				}
				inline constexpr typename _Linear_algebra_float_impl::matrix_2d_data_type _Linear_algebra_float_impl::init_translate(const typename _Linear_algebra_float_impl::point_2d_data_type& val) noexcept {
					return create_matrix_2d(1.0f, 0.0f, 0.0f, 1.0f, val._X, val._Y);
				}
				inline constexpr typename _Linear_algebra_float_impl::matrix_2d_data_type _Linear_algebra_float_impl::init_scale(const typename _Linear_algebra_float_impl::point_2d_data_type& val) noexcept {
					return create_matrix_2d(1.0f, 0.0f, 0.0f, 1.0f, val._X, val._Y);
				}
				inline typename _Linear_algebra_float_impl::matrix_2d_data_type _Linear_algebra_float_impl::init_rotate(float radians) noexcept {
					float sine = sin(radians);
					float cosine = cos(radians);
					sine = _Round_floating_point_to_zero(sine);
					cosine = _Round_floating_point_to_zero(cosine);
					return create_matrix_2d(cosine, -sine, sine, cosine, 0.0f, 0.0f);
				}
				inline typename _Linear_algebra_float_impl::matrix_2d_data_type _Linear_algebra_float_impl::init_rotate(float radians, const typename _Linear_algebra_float_impl::point_2d_data_type& origin) noexcept {
					return multiply(multiply(init_translate(origin), init_rotate(radians)), init_translate(-origin));
				}
				inline typename _Linear_algebra_float_impl::matrix_2d_data_type _Linear_algebra_float_impl::init_reflect(float radians) noexcept {
					auto sine = sin(radians * 2.0f);
					auto cosine = cos(radians * 2.0f);
					sine = _Round_floating_point_to_zero(sine);
					cosine = _Round_floating_point_to_zero(cosine);
					return create_matrix_2d(cosine, sine, sine, -cosine, 0.0f, 0.0f);
				}
				inline constexpr typename _Linear_algebra_float_impl::matrix_2d_data_type _Linear_algebra_float_impl::init_shear_x(float factor) noexcept {
					return create_matrix_2d(1.0f, 0.0f, factor, 1.0f, 0.0f, 0.0f);
				}
				inline constexpr typename _Linear_algebra_float_impl::matrix_2d_data_type _Linear_algebra_float_impl::init_shear_y(float factor) noexcept {
					return create_matrix_2d(1.0f, factor, 0.0f, 1.0f, 0.0f, 0.0f);
				}
				inline constexpr void _Linear_algebra_float_impl::translate(matrix_2d_data_type& mtx, const _Linear_algebra_float_impl::point_2d_data_type& v) noexcept {
					mtx = multiply(mtx, init_translate(v));
				}
				inline constexpr void _Linear_algebra_float_impl::scale(matrix_2d_data_type& mtx, const point_2d_data_type& scl) noexcept {
					mtx = multiply(mtx, init_scale(scl));
				}
				inline void _Linear_algebra_float_impl::rotate(matrix_2d_data_type& mtx, float radians) noexcept {
					mtx = multiply(mtx, init_rotate(radians));
				}
				inline void _Linear_algebra_float_impl::rotate(matrix_2d_data_type& mtx, float radians, const point_2d_data_type& origin) noexcept {
					mtx = multiply(mtx, init_rotate(radians, origin));
				}
				inline void _Linear_algebra_float_impl::reflect(matrix_2d_data_type& mtx, float radians) noexcept {
					mtx = multiply(mtx, init_reflect(radians));
				}
				inline constexpr void _Linear_algebra_float_impl::shear_x(matrix_2d_data_type& mtx, float factor) noexcept {
					mtx = multiply(mtx, init_shear_x(factor));
				}
				inline constexpr void _Linear_algebra_float_impl::shear_y(matrix_2d_data_type& mtx, float factor) noexcept {
					mtx = multiply(mtx, init_shear_y(factor));
				}
				constexpr bool _Is_finite_check(float) noexcept;
				inline constexpr bool _Is_finite_check(float val) noexcept {
					float infinity = ::std::numeric_limits<float>::infinity();
					return val != infinity &&
						val != -infinity &&
						!(val != val);
					// This checks for both types of NaN. Compilers are not supposed to optimize this away but there were some in the past that incorrectly did. The only way to be sure is to check the documentation and any compiler switches you may be using.
				}
				inline constexpr bool _Linear_algebra_float_impl::is_finite(const matrix_2d_data_type& mtx) noexcept {
					static_assert(::std::numeric_limits<float>::is_iec559 == true, "This implementation relies on IEEE 754 floating point behavior.");
					return ::std::numeric_limits<float>::is_iec559 &&
						_Is_finite_check(mtx.m00) &&
						_Is_finite_check(mtx.m01) &&
						_Is_finite_check(mtx.m10) &&
						_Is_finite_check(mtx.m11) &&
						_Is_finite_check(mtx.m20) &&
						_Is_finite_check(mtx.m21);
				}

				inline constexpr bool _Linear_algebra_float_impl::is_invertible(const typename matrix_2d_data_type& mtx) noexcept {
					return (mtx.m00 * mtx.m11 - mtx.m01 * mtx.m10) != 0.0f;
				}

				inline constexpr float _Linear_algebra_float_impl::determinant(const typename matrix_2d_data_type& mtx) noexcept {
					return mtx.m00 * mtx.m11 - mtx.m01 * mtx.m10;
				}

				inline constexpr _Linear_algebra_float_impl::matrix_2d_data_type _Linear_algebra_float_impl::inverse(const matrix_2d_data_type& mtx) noexcept {
					auto inverseDeterminant = 1.0F / determinant(mtx);
					return create_matrix_2d(
						(mtx.m11 * 1.0F - 0.0F * mtx.m21) * inverseDeterminant,
						-(mtx.m01 * 1.0F - 0.0F * mtx.m21) * inverseDeterminant,
						-(mtx.m10 * 1.0F - 0.0F * mtx.m20) * inverseDeterminant,
						(mtx.m00 * 1.0F - 0.0F * mtx.m20) * inverseDeterminant,
						(mtx.m10 * mtx.m21 - mtx.m11 * mtx.m20) * inverseDeterminant,
						-(mtx.m00 * mtx.m21 - mtx.m01 * mtx.m20) * inverseDeterminant
					);
				}

				inline constexpr _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::transform_pt(const matrix_2d_data_type& mtx, const _Linear_algebra_float_impl::point_2d_data_type& pt) noexcept {
					return point_2d_data_type(_Round_floating_point_to_zero(mtx.m00 * pt._X + mtx.m10 * pt._Y + mtx.m20), _Round_floating_point_to_zero(mtx.m01 * pt._X + mtx.m11 * pt._Y + mtx.m21));
				}

				inline constexpr _Linear_algebra_float_impl::matrix_2d_data_type _Linear_algebra_float_impl::multiply(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept {
					return create_matrix_2d(
						(lhs.m00 * rhs.m00) + (lhs.m01 * rhs.m10),
						(lhs.m00 * rhs.m01) + (lhs.m01 * rhs.m11),
						(lhs.m10 * rhs.m00) + (lhs.m11 * rhs.m10),
						(lhs.m10 * rhs.m01) + (lhs.m11 * rhs.m11),
						(lhs.m20 * rhs.m00) + (lhs.m21 * rhs.m10) + rhs.m20,
						(lhs.m20 * rhs.m01) + (lhs.m21 * rhs.m11) + rhs.m21
					);
				}

				inline constexpr bool _Linear_algebra_float_impl::equal(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept {
					return lhs.m00 == rhs.m00 && lhs.m01 == rhs.m01 &&
						lhs.m10 == rhs.m10 && lhs.m11 == rhs.m11 &&
						lhs.m20 == rhs.m20 && lhs.m21 == rhs.m21;
				}

				inline constexpr bool _Linear_algebra_float_impl::not_equal(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept {
					return !equal(lhs, rhs);
				}

				inline constexpr typename _Linear_algebra_float_impl::display_point_data_type _Linear_algebra_float_impl::create_display_point() noexcept {
					return display_point_data_type{ 0, 0 };
				}
				inline constexpr typename _Linear_algebra_float_impl::display_point_data_type _Linear_algebra_float_impl::create_display_point(int x, int y) noexcept {
					return display_point_data_type{ x, y };
				}
				inline constexpr void _Linear_algebra_float_impl::x(typename _Linear_algebra_float_impl::display_point_data_type& data, int x) noexcept {
					data.x = x;
				}
				inline constexpr void _Linear_algebra_float_impl::y(typename _Linear_algebra_float_impl::display_point_data_type& data, int y) noexcept {
					data.y = y;
				}
				inline constexpr int _Linear_algebra_float_impl::x(const typename _Linear_algebra_float_impl::display_point_data_type& data) noexcept {
					return data.x;
				}
				inline constexpr int _Linear_algebra_float_impl::y(const typename _Linear_algebra_float_impl::display_point_data_type& data) noexcept {
					return data.y;
				}
				inline constexpr bool _Linear_algebra_float_impl::equal(const typename _Linear_algebra_float_impl::display_point_data_type& lhs, const typename _Linear_algebra_float_impl::display_point_data_type& rhs) noexcept {
					return lhs.x == rhs.x && lhs.y == rhs.y;
				}
				inline constexpr bool _Linear_algebra_float_impl::not_equal(const typename _Linear_algebra_float_impl::display_point_data_type& lhs, const typename _Linear_algebra_float_impl::display_point_data_type& rhs) noexcept {
					return !(equal(lhs, rhs));
				}

				inline constexpr typename _Linear_algebra_float_impl::bounding_box_data_type _Linear_algebra_float_impl::create_bounding_box() noexcept {
					return bounding_box_data_type{ 0.0f, 0.0f, 0.0f, 0.0f };
				}
				inline constexpr typename _Linear_algebra_float_impl::bounding_box_data_type _Linear_algebra_float_impl::create_bounding_box(float x, float y, float width, float height) noexcept {
					return bounding_box_data_type{ x, y, width, height };
				}
				inline constexpr void _Linear_algebra_float_impl::x(typename _Linear_algebra_float_impl::bounding_box_data_type& bbox, float val) noexcept {
					bbox.x = val;
				}
				inline constexpr void _Linear_algebra_float_impl::y(typename _Linear_algebra_float_impl::bounding_box_data_type& bbox, float val) noexcept {
					bbox.y = val;
				}
				inline constexpr void _Linear_algebra_float_impl::width(typename _Linear_algebra_float_impl::bounding_box_data_type& bbox, float val) noexcept {
					bbox.width = val;
				}
				inline constexpr void _Linear_algebra_float_impl::height(typename _Linear_algebra_float_impl::bounding_box_data_type& bbox, float val) noexcept {
					bbox.height = val;
				}
				inline constexpr void _Linear_algebra_float_impl::top_left(typename _Linear_algebra_float_impl::bounding_box_data_type& bbox, const typename _Linear_algebra_float_impl::point_2d_data_type& val) noexcept {
					bbox.x = ::std::min(val._X, bbox.x + bbox.width);
					bbox.y = ::std::min(val._Y, bbox.y + bbox.height);
				}
				inline constexpr void _Linear_algebra_float_impl::bottom_right(typename _Linear_algebra_float_impl::bounding_box_data_type& bbox, const typename _Linear_algebra_float_impl::point_2d_data_type& val) noexcept {
					bbox.width = ::std::min(val._X - bbox.x, 0.0f);
					bbox.height = ::std::min(val._Y - bbox.y, 0.0f);
				}
				inline constexpr float _Linear_algebra_float_impl::x(const typename _Linear_algebra_float_impl::bounding_box_data_type& bbox) noexcept {
					return bbox.x;
				}
				inline constexpr float _Linear_algebra_float_impl::y(const typename _Linear_algebra_float_impl::bounding_box_data_type& bbox) noexcept {
					return bbox.y;
				}
				inline constexpr float _Linear_algebra_float_impl::width(const typename _Linear_algebra_float_impl::bounding_box_data_type& bbox) noexcept {
					return bbox.width;
				}
				inline constexpr float _Linear_algebra_float_impl::height(const typename _Linear_algebra_float_impl::bounding_box_data_type& bbox) noexcept {
					return bbox.height;
				}
				inline constexpr typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::top_left(const typename _Linear_algebra_float_impl::bounding_box_data_type& bbox) noexcept {
					return point_2d_data_type{ bbox.x, bbox.y };
				}
				inline constexpr typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::bottom_right(const typename _Linear_algebra_float_impl::bounding_box_data_type& bbox) noexcept {
					return point_2d_data_type{ bbox.x + bbox.width, bbox.y + bbox.height };
				}

				inline constexpr bool _Linear_algebra_float_impl::equal(const typename _Linear_algebra_float_impl::bounding_box_data_type& lhs, const typename _Linear_algebra_float_impl::bounding_box_data_type& rhs) noexcept {
					return lhs.x == rhs.x && lhs.y == rhs.y && lhs.width == rhs.width && lhs.height == rhs.height;
				}
				inline constexpr bool _Linear_algebra_float_impl::not_equal(const typename _Linear_algebra_float_impl::bounding_box_data_type& lhs, const typename _Linear_algebra_float_impl::bounding_box_data_type& rhs) noexcept {
					return !(equal(lhs, rhs));
				}

				inline constexpr typename _Linear_algebra_float_impl::circle_data_type _Linear_algebra_float_impl::create_circle() noexcept {
					return circle_data_type{ 0.0f, 0.0f, 0.0f };
				}
				inline constexpr typename _Linear_algebra_float_impl::circle_data_type _Linear_algebra_float_impl::create_circle(const typename _Linear_algebra_float_impl::point_2d_data_type& ctr, float rad) noexcept {
					return circle_data_type{ ctr._X, ctr._Y, rad };
				}
				inline constexpr void _Linear_algebra_float_impl::center(typename _Linear_algebra_float_impl::circle_data_type& data, const point_2d_data_type& ctr) noexcept {
					data.x = ctr._X;
					data.y = ctr._Y;
				}
				inline constexpr void _Linear_algebra_float_impl::radius(typename _Linear_algebra_float_impl::circle_data_type& data, float r) noexcept {
					data.radius = r;
				}
				inline constexpr typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::center(const typename _Linear_algebra_float_impl::circle_data_type& data) noexcept {
					return point_2d_data_type{ data.x, data.y };
				}
				inline constexpr float _Linear_algebra_float_impl::radius(const typename _Linear_algebra_float_impl::circle_data_type& data) noexcept {
					return data.radius;
				}
				inline constexpr bool _Linear_algebra_float_impl::equal(const typename _Linear_algebra_float_impl::circle_data_type& lhs, const typename _Linear_algebra_float_impl::circle_data_type& rhs) noexcept {
					return lhs.radius == rhs.radius && lhs.x == rhs.x && lhs.y == rhs.y;
				}
				inline constexpr bool _Linear_algebra_float_impl::not_equal(const typename _Linear_algebra_float_impl::circle_data_type& lhs, const typename _Linear_algebra_float_impl::circle_data_type& rhs) noexcept {
					return !(equal(lhs, rhs));
				}

				template <class GraphicsMath>
				inline typename basic_point_2d<GraphicsMath> arc_start(const basic_point_2d<GraphicsMath>& ctr, float sang, const basic_point_2d<GraphicsMath>& rad) noexcept {
					auto lmtx = basic_matrix_2d<GraphicsMath>();
					lmtx.m20(0.0f); lmtx.m21(0.0f); // Eliminate translation.
					auto pt = point_for_angle<GraphicsMath>(sang, rad);
					return ctr + pt * lmtx;
				}

				template <class GraphicsMath>
				inline basic_point_2d<GraphicsMath> arc_start(const basic_point_2d<GraphicsMath>& ctr, float sang, const basic_point_2d<GraphicsMath>& rad, const basic_matrix_2d<GraphicsMath>& m) noexcept {
					auto lmtx = m;
					lmtx.m20(0.0f); lmtx.m21(0.0f); // Eliminate translation.
					auto pt = point_for_angle<GraphicsMath>(sang, rad);
					return ctr + pt * lmtx;
				}

				template <class GraphicsMath>
				inline basic_point_2d<GraphicsMath> arc_center(const basic_point_2d<GraphicsMath>& cpt, float sang, const basic_point_2d<GraphicsMath>& rad) noexcept {
					auto lmtx = basic_matrix_2d<GraphicsMath>();
					lmtx.m20(0.0f); lmtx.m21(0.0f); // Eliminate translation.
					auto centerOffset = point_for_angle<GraphicsMath>(two_pi<float> -sang, rad);
					centerOffset.y(-centerOffset.y());
					return cpt - centerOffset * lmtx;
				}

				template <class GraphicsMath>
				inline basic_point_2d<GraphicsMath> arc_center(const basic_point_2d<GraphicsMath>& cpt, float sang, const basic_point_2d<GraphicsMath>& rad, const basic_matrix_2d<GraphicsMath>& m) noexcept {
					auto lmtx = m;
					lmtx.m20(0.0f); lmtx.m21(0.0f); // Eliminate translation.
					auto centerOffset = point_for_angle<GraphicsMath>(two_pi<float> -sang, rad);
					centerOffset.y(-centerOffset.y());
					return cpt - centerOffset * lmtx;
				}

				template <class GraphicsMath>
				inline basic_point_2d<GraphicsMath> arc_end(const basic_point_2d<GraphicsMath>& cpt, float eang, const basic_point_2d<GraphicsMath>& rad) noexcept {
					auto lmtx = basic_matrix_2d<GraphicsMath>();
					auto tfrm = basic_matrix_2d<GraphicsMath>::init_rotate(eang);
					lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
					auto pt = (rad * tfrm);
					pt.y(-pt.y());
					return cpt + pt * lmtx;
				}

				template <class GraphicsMath>
				inline typename basic_point_2d<GraphicsMath> arc_end(const basic_point_2d<GraphicsMath>& cpt, float eang, const basic_point_2d<GraphicsMath>& rad, const basic_matrix_2d<GraphicsMath>& m) noexcept {
					auto lmtx = m;
					auto tfrm = basic_matrix_2d<GraphicsMath>::init_rotate(eang);
					lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
					auto pt = (rad * tfrm);
					pt.y(-pt.y);
					return cpt + pt * lmtx;
				}

				// GraphicsMath

				template <class GraphicsMath>
				inline constexpr basic_bounding_box<GraphicsMath>::basic_bounding_box() noexcept { }
				template <class GraphicsMath>
				inline constexpr basic_bounding_box<GraphicsMath>::basic_bounding_box(float x, float y, float width, float height) noexcept
					: _X(x)
					, _Y(y)
					, _Width(width)
					, _Height(height) {
				}
				template <class GraphicsMath>
				inline constexpr basic_bounding_box<GraphicsMath>::basic_bounding_box(const basic_point_2d<GraphicsMath>& tl, const basic_point_2d<GraphicsMath>& br) noexcept
					: _X(tl.x())
					, _Y(tl.y())
					, _Width(::std::max(0.0F, br.x() - tl.x()))
					, _Height(::std::max(0.0F, br.y() - tl.y())) {
				}

				template <class GraphicsMath>
				inline constexpr void basic_bounding_box<GraphicsMath>::x(float value) noexcept {
					_X = value;
				}
				template <class GraphicsMath>
				inline constexpr void basic_bounding_box<GraphicsMath>::y(float value) noexcept {
					_Y = value;
				}
				template <class GraphicsMath>
				inline constexpr void basic_bounding_box<GraphicsMath>::width(float value) noexcept {
					_Width = value;
				}
				template <class GraphicsMath>
				inline constexpr void basic_bounding_box<GraphicsMath>::height(float value) noexcept {
					_Height = value;
				}
				template <class GraphicsMath>
				inline constexpr void basic_bounding_box<GraphicsMath>::top_left(const basic_point_2d<GraphicsMath>& value) noexcept {
					_X = value.x();
					_Y = value.y();
				}
				template <class GraphicsMath>
				inline constexpr void basic_bounding_box<GraphicsMath>::bottom_right(const basic_point_2d<GraphicsMath>& value) noexcept {
					_Width = max(0.0F, value.x() - _X);
					_Height = max(0.0F, value.y() - _Y);
				}

				template <class GraphicsMath>
				inline constexpr float basic_bounding_box<GraphicsMath>::x() const noexcept {
					return _X;
				}

				template <class GraphicsMath>
				inline constexpr float basic_bounding_box<GraphicsMath>::y() const noexcept {
					return _Y;
				}

				template <class GraphicsMath>
				inline constexpr float basic_bounding_box<GraphicsMath>::width() const noexcept {
					return _Width;
				}

				template <class GraphicsMath>
				inline constexpr float basic_bounding_box<GraphicsMath>::height() const noexcept {
					return _Height;
				}

				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> basic_bounding_box<GraphicsMath>::top_left() const noexcept {
					return basic_point_2d<GraphicsMath>{ _X, _Y };
				}

				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> basic_bounding_box<GraphicsMath>::bottom_right() const noexcept {
					return basic_point_2d<GraphicsMath>{ _X + _Width, _Y + _Height };
				}

				template <class GraphicsMath>
				inline constexpr bool operator==(const basic_bounding_box<GraphicsMath>& lhs, const basic_bounding_box<GraphicsMath>& rhs)
					noexcept {
					return lhs._X == rhs._X && lhs._Y == rhs._Y && lhs._Width == rhs._Width && lhs._Height == rhs._Height;
				}
				template <class GraphicsMath>
				inline constexpr bool operator!=(const basic_bounding_box<GraphicsMath>& lhs, const basic_bounding_box<GraphicsMath>& rhs)
					noexcept {
					return !(lhs == rhs);
				}

				template <class GraphicsMath>
				inline constexpr basic_circle<GraphicsMath>::basic_circle() noexcept
					: _X()
					, _Y()
					, _Radius() {}
				template <class GraphicsMath>
				inline constexpr basic_circle<GraphicsMath>::basic_circle(const basic_point_2d<GraphicsMath>& ctr, float r) noexcept
					: _X(ctr.x())
					, _Y(ctr.y())
					, _Radius(r) {}

				template <class GraphicsMath>
				inline constexpr void basic_circle<GraphicsMath>::center(const basic_point_2d<GraphicsMath>& ctr) noexcept {
					_X = ctr.x();
					_Y = ctr.y();
				}
				template <class GraphicsMath>
				inline constexpr void basic_circle<GraphicsMath>::radius(float r) noexcept {
					_Radius = r;
				}

				template <class GraphicsMath>
				inline constexpr basic_point_2d<GraphicsMath> basic_circle<GraphicsMath>::center() const noexcept {
					return basic_point_2d<GraphicsMath>(_X, _Y);
				}
				template <class GraphicsMath>
				inline constexpr float basic_circle<GraphicsMath>::radius() const noexcept {
					return _Radius;
				}

				template <class GraphicsMath>
				inline constexpr bool operator==(const basic_circle<GraphicsMath>& lhs, const basic_circle<GraphicsMath>& rhs) noexcept {
					return lhs._X == rhs._X && lhs._Y == rhs._Y && lhs._Radius == rhs._Radius;
				}
				template <class GraphicsMath>
				inline constexpr bool operator!=(const basic_circle<GraphicsMath>& lhs, const basic_circle<GraphicsMath>& rhs) noexcept {
					return !(lhs == rhs);
				}

				// Paths

				//template <class GraphicsMath, class T, class U>
				//inline constexpr basic_figure_items<GraphicsMath<T, U>>::abs_new_figure::abs_new_figure() noexcept {

				//}
				template<class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::abs_new_figure::abs_new_figure() noexcept
					: _Data() { }

				template<class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::abs_new_figure::abs_new_figure(const typename GraphicsMath::point_2d& pt) noexcept
					: _Data(pt) {
				}
				template<class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::abs_new_figure::at(const typename GraphicsMath::point_2d& pt) noexcept {
					_Data = pt;
				}
				template<class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::abs_new_figure::at() const noexcept {
					return _Data;
				}
				template<class GraphicsMath>
				inline constexpr bool operator==(const typename basic_figure_items<GraphicsMath>::abs_new_figure& lhs, const typename basic_figure_items<GraphicsMath>::abs_new_figure& rhs) noexcept {
					return lhs._Data == rhs._Data;
				}
				template<class GraphicsMath>
				inline constexpr bool operator!=(const typename basic_figure_items<GraphicsMath>::abs_new_figure& lhs, const typename basic_figure_items<GraphicsMath>::abs_new_figure& rhs) noexcept {
					return !(lhs == rhs);
				}

				template<class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::rel_new_figure::rel_new_figure() noexcept {}

				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::rel_new_figure::rel_new_figure(const typename GraphicsMath::point_2d& pt) noexcept
					: _Data(pt) {}

				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::rel_new_figure::at(const typename GraphicsMath::point_2d& pt) noexcept {
					_Data = pt;
				}

				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::rel_new_figure::at() const noexcept {
					return _Data;
				}

				template <class GraphicsMath>
				inline constexpr bool operator==(const typename basic_figure_items<GraphicsMath>::rel_new_figure& lhs, const typename basic_figure_items<GraphicsMath>::rel_new_figure& rhs) noexcept {
					return lhs._Data == rhs._Data;
				}

				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::close_figure::close_figure() noexcept {}

				template <class GraphicsMath>
				inline constexpr bool operator==(const typename basic_figure_items<GraphicsMath>::close_figure&, const typename basic_figure_items<GraphicsMath>::close_figure&) noexcept {
					return true;
				}

				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::abs_matrix::abs_matrix(const typename GraphicsMath::matrix_2d& m) noexcept
					: _Matrix(m) {
				}
				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::abs_matrix::abs_matrix() noexcept {}

				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::abs_matrix::matrix(const typename GraphicsMath::matrix_2d& value) noexcept {
					_Matrix = value;
				}
				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::matrix_2d basic_figure_items<GraphicsMath>::abs_matrix::matrix() const noexcept {
					return _Matrix;
				}

				template <class GraphicsMath>
				inline constexpr bool operator==(const typename basic_figure_items<GraphicsMath>::abs_matrix& lhs, const typename basic_figure_items<GraphicsMath>::abs_matrix& rhs) noexcept {
					return lhs._Matrix == rhs._Matrix;
				}

				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::rel_matrix::rel_matrix(const typename GraphicsMath::matrix_2d& m) noexcept
					: _Matrix(m) {
				}
				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::rel_matrix::rel_matrix() noexcept {}

				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::rel_matrix::matrix(const typename GraphicsMath::matrix_2d& value) noexcept {
					_Matrix = value;
				}
				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::matrix_2d basic_figure_items<GraphicsMath>::rel_matrix::matrix() const noexcept {
					return _Matrix;
				}

				template <class GraphicsMath>
				inline constexpr bool operator==(const typename basic_figure_items<GraphicsMath>::rel_matrix& lhs, const typename basic_figure_items<GraphicsMath>::rel_matrix& rhs) noexcept {
					return lhs._Matrix == rhs._Matrix;
				}

				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::revert_matrix::revert_matrix() noexcept {}

				template <class GraphicsMath>
				inline constexpr bool operator==(const typename basic_figure_items<GraphicsMath>::revert_matrix&, const typename basic_figure_items<GraphicsMath>::revert_matrix&) noexcept {
					return true;
				}

				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::abs_line::abs_line(const typename GraphicsMath::point_2d& to) noexcept
					: _Data(to) {
				}
				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::abs_line::abs_line() noexcept {}

				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::abs_line::to(const typename GraphicsMath::point_2d& value) noexcept {
					_Data = value;
				}

				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::abs_line::to() const noexcept {
					return _Data;
				}

				template <class GraphicsMath>
				inline constexpr bool operator==(const typename basic_figure_items<GraphicsMath>::abs_line& lhs, const typename basic_figure_items<GraphicsMath>::abs_line& rhs) noexcept {
					return lhs._Data == rhs._Data;
				}

				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::rel_line::rel_line(const typename GraphicsMath::point_2d& to) noexcept
					: _Data(to) {
				}
				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::rel_line::rel_line() noexcept {}

				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::rel_line::to(const typename GraphicsMath::point_2d& value) noexcept {
					_Data = value;
				}

				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::rel_line::to() const noexcept {
					return _Data;
				}

				template <class GraphicsMath>
				inline constexpr bool operator==(const typename basic_figure_items<GraphicsMath>::rel_line& lhs, const typename basic_figure_items<GraphicsMath>::rel_line& rhs) noexcept {
					return lhs._Data == rhs._Data;
				}

				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::abs_quadratic_curve::abs_quadratic_curve(const typename GraphicsMath::point_2d& cp, const typename GraphicsMath::point_2d& ep) noexcept
					: _Control_pt(cp)
					, _End_pt(ep) {
				}
				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::abs_quadratic_curve::abs_quadratic_curve() noexcept {}

				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::abs_quadratic_curve::control_pt(const typename GraphicsMath::point_2d& value) noexcept {
					_Control_pt = value;
				}
				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::abs_quadratic_curve::end_pt(const typename GraphicsMath::point_2d& value) noexcept {
					_End_pt = value;
				}

				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::abs_quadratic_curve::control_pt() const noexcept {
					return _Control_pt;
				}
				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::abs_quadratic_curve::end_pt() const noexcept {
					return _End_pt;
				}

				template <class GraphicsMath>
				inline constexpr bool operator==(const typename basic_figure_items<GraphicsMath>::abs_quadratic_curve& lhs, const typename basic_figure_items<GraphicsMath>::abs_quadratic_curve& rhs) noexcept {
					return (lhs._Control_pt == rhs._Control_pt) &&
						(lhs._End_pt == rhs._End_pt);
				}

				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::rel_quadratic_curve::rel_quadratic_curve(const typename GraphicsMath::point_2d& cp, const typename GraphicsMath::point_2d& ep) noexcept
					: _Control_pt(cp)
					, _End_pt(ep) {
				}
				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::rel_quadratic_curve::rel_quadratic_curve() noexcept {}

				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::rel_quadratic_curve::control_pt(const typename GraphicsMath::point_2d& value) noexcept {
					_Control_pt = value;
				}
				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::rel_quadratic_curve::end_pt(const typename GraphicsMath::point_2d& value) noexcept {
					_End_pt = value;
				}

				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::rel_quadratic_curve::control_pt() const noexcept {
					return _Control_pt;
				}
				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::rel_quadratic_curve::end_pt() const noexcept {
					return _End_pt;
				}

				template <class GraphicsMath>
				inline constexpr bool operator==(const typename basic_figure_items<GraphicsMath>::rel_quadratic_curve& lhs, const typename basic_figure_items<GraphicsMath>::rel_quadratic_curve& rhs) noexcept {
					return (lhs._Control_pt == rhs._Control_pt) &&
						(lhs._End_pt == rhs._End_pt);
				}

				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::abs_cubic_curve::abs_cubic_curve(const typename GraphicsMath::point_2d& controlPoint1, const typename GraphicsMath::point_2d& controlPoint2, const typename GraphicsMath::point_2d& endPoint) noexcept
					: _Control_pt1(controlPoint1)
					, _Control_pt2(controlPoint2)
					, _End_pt(endPoint) {
				}
				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::abs_cubic_curve::abs_cubic_curve() noexcept {}

				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::abs_cubic_curve::control_pt1(const typename GraphicsMath::point_2d& value) noexcept {
					_Control_pt1 = value;
				}
				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::abs_cubic_curve::control_pt2(const typename GraphicsMath::point_2d& value) noexcept {
					_Control_pt2 = value;
				}
				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::abs_cubic_curve::end_pt(const typename GraphicsMath::point_2d& value) noexcept {
					_End_pt = value;
				}

				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::abs_cubic_curve::control_pt1() const noexcept {
					return _Control_pt1;
				}
				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::abs_cubic_curve::control_pt2() const noexcept {
					return _Control_pt2;
				}
				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::abs_cubic_curve::end_pt() const noexcept {
					return _End_pt;
				}

				template <class GraphicsMath>
				inline constexpr bool operator==(const typename basic_figure_items<GraphicsMath>::abs_cubic_curve& lhs, const typename basic_figure_items<GraphicsMath>::abs_cubic_curve& rhs) noexcept {
					return (lhs._Control_pt1 == rhs._Control_pt1) &&
						(lhs._Control_pt2 == rhs._Control_pt2) &&
						(lhs._End_pt == rhs._End_pt);
				}

				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::rel_cubic_curve::rel_cubic_curve(const typename GraphicsMath::point_2d& controlPoint1, const typename GraphicsMath::point_2d& controlPoint2, const typename GraphicsMath::point_2d& endPoint) noexcept
					: _Control_pt1(controlPoint1)
					, _Control_pt2(controlPoint2)
					, _End_pt(endPoint) {
				}
				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::rel_cubic_curve::rel_cubic_curve() noexcept {}

				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::rel_cubic_curve::control_pt1(const typename GraphicsMath::point_2d& value) noexcept {
					_Control_pt1 = value;
				}
				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::rel_cubic_curve::control_pt2(const typename GraphicsMath::point_2d& value) noexcept {
					_Control_pt2 = value;
				}
				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::rel_cubic_curve::end_pt(const typename GraphicsMath::point_2d& value) noexcept {
					_End_pt = value;
				}

				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::rel_cubic_curve::control_pt1() const noexcept {
					return _Control_pt1;
				}
				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::rel_cubic_curve::control_pt2() const noexcept {
					return _Control_pt2;
				}
				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::rel_cubic_curve::end_pt() const noexcept {
					return _End_pt;
				}

				template <class GraphicsMath>
				inline constexpr bool operator==(const typename basic_figure_items<GraphicsMath>::rel_cubic_curve& lhs, const typename basic_figure_items<GraphicsMath>::rel_cubic_curve& rhs) noexcept {
					return (lhs._Control_pt1 == rhs._Control_pt1) &&
						(lhs._Control_pt2 == rhs._Control_pt2) &&
						(lhs._End_pt == rhs._End_pt);
				}

				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::arc::arc() noexcept
					: arc(typename GraphicsMath::point_2d{ 10.0F, 10.0F }, pi<float>, pi<float>) { }
				template <class GraphicsMath>
				inline constexpr basic_figure_items<GraphicsMath>::arc::arc(const typename GraphicsMath::point_2d& rad, float rot, float sang) noexcept
					: _Radius(rad)
					, _Rotation(rot)
					, _Start_angle(sang) {
				}

				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::arc::radius(const typename GraphicsMath::point_2d& rad) noexcept {
					_Radius = rad;
				}
				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::arc::rotation(float rot) noexcept {
					_Rotation = rot;
				}
				template <class GraphicsMath>
				inline constexpr void basic_figure_items<GraphicsMath>::arc::start_angle(float sang) noexcept {
					_Start_angle = sang;
				}

				template <class GraphicsMath>
				inline constexpr typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::arc::radius() const noexcept {
					return _Radius;
				}
				template <class GraphicsMath>
				inline constexpr float basic_figure_items<GraphicsMath>::arc::rotation() const noexcept {
					return _Rotation;
				}
				template <class GraphicsMath>
				inline constexpr float basic_figure_items<GraphicsMath>::arc::start_angle() const noexcept {
					return _Start_angle;
				}

				template <class GraphicsMath>
				inline typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::arc::center(const typename GraphicsMath::point_2d& cpt, const typename GraphicsMath::matrix_2d& m) const noexcept {
					auto lmtx = m;
					lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
					auto centerOffset = point_for_angle<GraphicsMath>(two_pi<float> -_Start_angle, _Radius);
					centerOffset.y(-centerOffset.y);
					return cpt - centerOffset * lmtx;
				}

				template <class GraphicsMath>
				inline typename GraphicsMath::point_2d basic_figure_items<GraphicsMath>::arc::end_pt(const typename GraphicsMath::point_2d& cpt, const typename GraphicsMath::matrix_2d& m) const noexcept {
					auto lmtx = m;
					auto tfrm = matrix_2d::init_rotate(_Start_angle + _Rotation);
					lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
					auto pt = (_Radius * tfrm);
					pt.y(-pt.y);
					return cpt + pt * lmtx;
				}

				template <class GraphicsMath>
				inline constexpr bool operator==(const typename basic_figure_items<GraphicsMath>::arc& lhs, const typename basic_figure_items<GraphicsMath>::arc& rhs) noexcept {
					return (lhs._Radius == rhs._Radius) &&
						(lhs._Rotation == rhs._Rotation) &&
						(lhs._Start_angle == rhs._Start_angle);
				}

				template <class GraphicsMath>
				inline constexpr bool operator!=(const typename basic_figure_items<GraphicsMath>::arc& lhs, const typename basic_figure_items<GraphicsMath>::arc& rhs) noexcept {
					return !(lhs == rhs);
				}

				enum class _Path_data_abs_new_figure {};
				constexpr static _Path_data_abs_new_figure _Path_data_abs_new_figure_val = {};
				enum class _Path_data_rel_new_figure {};
				constexpr static _Path_data_rel_new_figure _Path_data_rel_new_figure_val = {};
				enum class _Path_data_close_path {};
				constexpr static _Path_data_close_path _Path_data_close_path_val = {};
				enum class _Path_data_abs_matrix {};
				constexpr static _Path_data_abs_matrix _Path_data_abs_matrix_val = {};
				enum class _Path_data_rel_matrix {};
				constexpr static _Path_data_rel_matrix _Path_data_rel_matrix_val = {};
				enum class _Path_data_revert_matrix {};
				constexpr static _Path_data_revert_matrix _Path_data_revert_matrix_val = {};
				enum class _Path_data_abs_cubic_curve {};
				constexpr static _Path_data_abs_cubic_curve _Path_data_abs_cubic_curve_val = {};
				enum class _Path_data_abs_line {};
				constexpr static _Path_data_abs_line _Path_data_abs_line_val = {};
				enum class _Path_data_abs_quadratic_curve {};
				constexpr static _Path_data_abs_quadratic_curve _Path_data_abs_quadratic_curve_val = {};
				enum class _Path_data_arc {};
				constexpr static _Path_data_arc _Path_data_arc_val = {};
				enum class _Path_data_rel_cubic_curve {};
				constexpr static _Path_data_rel_cubic_curve _Path_data_rel_cubic_curve_val = {};
				enum class _Path_data_rel_line {};
				constexpr static _Path_data_rel_line _Path_data_rel_line_val = {};
				enum class _Path_data_rel_quadratic_curve {};
				constexpr static _Path_data_rel_quadratic_curve _Path_data_rel_quadratic_curve_val = {};

				template <class GraphicsMath, class Allocator>
				::std::vector<typename basic_figure_items<GraphicsMath>::figure_item> _Interpret_path_items(const path_builder<GraphicsMath, Allocator>&);

				template <class GraphicsSurfaces>
				inline constexpr basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path() noexcept
					: _Data(GraphicsSurfaces::create_interpreted_path()) { }

				template <class GraphicsSurfaces>
				template <class GraphicsMath, class Allocator>
				inline basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path(const path_builder<GraphicsMath, Allocator>& pb)
					: _Data(GraphicsSurfaces::create_interpreted_path(pb)) { }

				template <class GraphicsSurfaces>
				template <class ForwardIterator>
				inline interpreted_path<T>::interpreted_path(ForwardIterator first, ForwardIterator last)
					: _Data(GraphicsSurfaces::create_interpreted_path(first, last)) { }

				template <class _TItem>
				struct _Path_item_interpret_visitor {
					constexpr static float twoThirds = 2.0F / 3.0F;

					template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_new_figure>, _Path_data_abs_new_figure> = _Path_data_abs_new_figure_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, typename GraphicsMath::matrix_2d& m, typename GraphicsMath::point_2d& currentPoint, typename GraphicsMath::point_2d& closePoint, stack<typename GraphicsMath::matrix_2d>&) noexcept {
						const auto pt = m.transform_pt({ 0.0F, 0.0F }) + item.at();
						v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_new_figure>, pt);
						currentPoint = pt;
						closePoint = pt;
					}

					template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_new_figure>, _Path_data_rel_new_figure> = _Path_data_rel_new_figure_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, typename GraphicsMath::matrix_2d& m, typename GraphicsMath::point_2d& currentPoint, typename GraphicsMath::point_2d& closePoint, stack<typename GraphicsMath::matrix_2d>&) noexcept {
						auto amtx = m;
						amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
						const auto pt = currentPoint + item.at() * amtx;
						v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_new_figure>, pt);
						currentPoint = pt;
						closePoint = pt;
					}

					template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::close_figure>, _Path_data_close_path> = _Path_data_close_path_val>
					static void _Interpret(const T&, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, typename GraphicsMath::matrix_2d&, typename GraphicsMath::point_2d& currentPoint, typename GraphicsMath::point_2d& closePoint, stack<typename GraphicsMath::matrix_2d>&) noexcept {
						const auto& item = v.rbegin();
						auto idx = item->index();
						if (idx == 0 || idx == 1) {
							return; // degenerate path
						}
						v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::close_figure>);
						v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_new_figure>,
							closePoint);
						currentPoint = closePoint;
					}
					template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_matrix>, _Path_data_abs_matrix> = _Path_data_abs_matrix_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>&, typename GraphicsMath::matrix_2d& m, typename GraphicsMath::point_2d&, typename GraphicsMath::point_2d&, stack<typename GraphicsMath::matrix_2d>& matrices) noexcept {
						matrices.push(m);
						m = item.matrix();
					}
					template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_matrix>, _Path_data_rel_matrix> = _Path_data_rel_matrix_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>&, typename GraphicsMath::matrix_2d& m, typename GraphicsMath::point_2d&, typename GraphicsMath::point_2d&, stack<typename GraphicsMath::matrix_2d>& matrices) noexcept {
						const auto updateM = m * item.matrix();
						matrices.push(m);
						m = updateM;
					}
					template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::revert_matrix>, _Path_data_revert_matrix> = _Path_data_revert_matrix_val>
					static void _Interpret(const T&, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>&, typename GraphicsMath::matrix_2d& m, typename GraphicsMath::point_2d&, typename GraphicsMath::point_2d&, stack<typename GraphicsMath::matrix_2d>& matrices) noexcept {
						if (matrices.empty()) {
							m = matrix_2d{};
						}
						else {
							m = matrices.top();
							matrices.pop();
						}
					}
					template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, typename GraphicsMath::matrix_2d& m, typename GraphicsMath::point_2d& currentPoint, typename GraphicsMath::point_2d&, stack<typename GraphicsMath::matrix_2d>&) noexcept {
						const auto pt1 = m.transform_pt(item.control_pt1() - currentPoint) + currentPoint;
						const auto pt2 = m.transform_pt(item.control_pt2() - currentPoint) + currentPoint;
						const auto pt3 = m.transform_pt(item.end_pt() - currentPoint) + currentPoint;
						if (currentPoint == pt1 && pt1 == pt2 && pt2 == pt3) {
							return; // degenerate path segment
						}
						v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_cubic_curve>, pt1,
							pt2, pt3);
						currentPoint = pt3;
					}
					template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, typename GraphicsMath::matrix_2d& m, typename GraphicsMath::point_2d& currentPoint, typename GraphicsMath::point_2d&, stack<typename GraphicsMath::matrix_2d>&) noexcept {
						const auto pt = m.transform_pt(item.to() - currentPoint) + currentPoint;
						if (currentPoint == pt) {
							return; // degenerate path segment
						}
						v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_line>, pt);
						currentPoint = pt;
					}
					template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, typename GraphicsMath::matrix_2d& m, typename GraphicsMath::point_2d& currentPoint, typename GraphicsMath::point_2d&, stack<typename GraphicsMath::matrix_2d>&) noexcept {
						// Turn it into a cubic curve since cairo doesn't have quadratic curves.
						const auto controlPt = m.transform_pt(item.control_pt() - currentPoint) + currentPoint;
						const auto endPt = m.transform_pt(item.end_pt() - currentPoint) + currentPoint;
						if (currentPoint == controlPt && controlPt == endPt) {
							return; // degenerate path segment
						}
						const auto beginPt = currentPoint;
						GraphicsMath::point_2d cpt1 = { ((controlPt.x - beginPt.x) * twoThirds) + beginPt.x, ((controlPt.y - beginPt.y) * twoThirds) + beginPt.y };
						GraphicsMath::point_2d cpt2 = { ((controlPt.x - endPt.x) * twoThirds) + endPt.x, ((controlPt.y - endPt.y) * twoThirds) + endPt.y };
						v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_cubic_curve>, cpt1, cpt2, endPt);
						currentPoint = endPt;
					}

					template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::arc>, _Path_data_arc> = _Path_data_arc_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, typename GraphicsMath::matrix_2d& m, typename GraphicsMath::point_2d& currentPoint, typename GraphicsMath::point_2d&, stack<typename GraphicsMath::matrix_2d>&) noexcept {
						const float rot = item.rotation();
						const float oneThousandthOfADegreeInRads = pi<float> / 180'000.0F;
						if (abs(rot) < oneThousandthOfADegreeInRads) {
							// Return if the rotation is less than one thousandth of one degree; it's a degenerate path segment.
							return;
						}
						const auto clockwise = (rot < 0.0F) ? true : false;
						const GraphicsMath::point_2d rad = item.radius();
						auto startAng = item.start_angle();
						const auto origM = m;
						m = matrix_2d::init_scale(rad);
						auto centerOffset = (point_for_angle(two_pi<float> -startAng) * rad);
						centerOffset.y = -centerOffset.y;
						auto ctr = currentPoint - centerOffset;

						GraphicsMath::point_2d pt0, pt1, pt2, pt3;
						int bezCount = 1;
						float theta = rot;

						while (abs(theta) > half_pi<float>) {
							theta /= 2.0F;
							bezCount += bezCount;
						}

						float phi = (theta / 2.0F);
						const auto cosPhi = cos(-phi);
						const auto sinPhi = sin(-phi);

						pt0.x = cosPhi;
						pt0.y = -sinPhi;
						pt3.x = pt0.x;
						pt3.y = -pt0.y;
						pt1.x = (4.0F - cosPhi) / 3.0F;
						pt1.y = -(((1.0F - cosPhi) * (3.0F - cosPhi)) / (3.0F * sinPhi));
						pt2.x = pt1.x;
						pt2.y = -pt1.y;
						auto rotCntrCwFn = [](const typename GraphicsMath::point_2d& pt, float a) -> typename GraphicsMath::point_2d& {
							auto result = point_2d{ pt.x * cos(a) - pt.y * sin(a),
								pt.x * sin(a) + pt.y * cos(a) };
							result.x = _Round_floating_point_to_zero(result.x);
							result.y = _Round_floating_point_to_zero(result.y);
							return result;
						};
						auto rotCwFn = [](const typename GraphicsMath::point_2d& pt, float a) -> typename GraphicsMath::point_2d& {
							auto result = point_2d{ pt.x * cos(a) - pt.y * sin(a),
								-(pt.x * sin(a) + pt.y * cos(a)) };
							result.x = _Round_floating_point_to_zero(result.x);
							result.y = _Round_floating_point_to_zero(result.y);
							return result;
						};

						startAng = two_pi<float> -startAng;

						if (clockwise) {
							pt0 = rotCwFn(pt0, phi);
							pt1 = rotCwFn(pt1, phi);
							pt2 = rotCwFn(pt2, phi);
							pt3 = rotCwFn(pt3, phi);
							auto shflPt = pt3;
							pt3 = pt0;
							pt0 = shflPt;
							shflPt = pt2;
							pt2 = pt1;
							pt1 = shflPt;
						}
						else {
							pt0 = rotCntrCwFn(pt0, phi);
							pt1 = rotCntrCwFn(pt1, phi);
							pt2 = rotCntrCwFn(pt2, phi);
							pt3 = rotCntrCwFn(pt3, phi);
							pt0.y = -pt0.y;
							pt1.y = -pt1.y;
							pt2.y = -pt2.y;
							pt3.y = -pt3.y;
							auto shflPt = pt3;
							pt3 = pt0;
							pt0 = shflPt;
							shflPt = pt2;
							pt2 = pt1;
							pt1 = shflPt;
						}
						auto currTheta = startAng;
						const auto calcAdjustedCurrPt = ((ctr + (rotCntrCwFn(pt0, currTheta) * m)) * origM);
						auto adjustVal = calcAdjustedCurrPt - currentPoint;
						const typename GraphicsMath::point_2d& tempCurrPt;
						for (; bezCount > 0; bezCount--) {
							const auto rapt0 = m.transform_pt(rotCntrCwFn(pt0, currTheta));
							const auto rapt1 = m.transform_pt(rotCntrCwFn(pt1, currTheta));
							const auto rapt2 = m.transform_pt(rotCntrCwFn(pt2, currTheta));
							const auto rapt3 = m.transform_pt(rotCntrCwFn(pt3, currTheta));
							auto cpt0 = ctr + rapt0;
							auto cpt1 = ctr + rapt1;
							auto cpt2 = ctr + rapt2;
							auto cpt3 = ctr + rapt3;
							cpt0 = origM.transform_pt(cpt0);
							cpt1 = origM.transform_pt(cpt1);
							cpt2 = origM.transform_pt(cpt2);
							cpt3 = origM.transform_pt(cpt3);
							cpt0 -= adjustVal;
							cpt1 -= adjustVal;
							cpt2 -= adjustVal;
							cpt3 -= adjustVal;
							currentPoint = cpt3;
							v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_cubic_curve>, cpt1, cpt2, cpt3);
							currTheta -= theta;
						}
						m = origM;
					}

					template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, typename GraphicsMath::matrix_2d& m, typename GraphicsMath::point_2d& currentPoint, typename GraphicsMath::point_2d&, stack<typename GraphicsMath::matrix_2d>&) noexcept {
						auto amtx = m;
						amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
						const auto pt1 = item.control_pt1() * amtx;
						const auto pt2 = item.control_pt2() * amtx;
						const auto pt3 = item.end_pt()* amtx;
						if (currentPoint == pt1 && pt1 == pt2 && pt2 == pt3) {
							return; // degenerate path segment
						}
						v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_cubic_curve>, currentPoint + pt1, currentPoint + pt1 + pt2, currentPoint + pt1 + pt2 + pt3);
						currentPoint = currentPoint + pt1 + pt2 + pt3;
					}

					template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, typename GraphicsMath::matrix_2d& m, typename GraphicsMath::point_2d& currentPoint, typename GraphicsMath::point_2d&, stack<typename GraphicsMath::matrix_2d>&) noexcept {
						auto amtx = m;
						amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
						const auto pt = currentPoint + item.to() * amtx;
						if (currentPoint == pt) {
							return; // degenerate path segment
						}
						v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_line>, pt);
						currentPoint = pt;
					}

					template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, typename GraphicsMath::matrix_2d& m, typename GraphicsMath::point_2d& currentPoint, typename GraphicsMath::point_2d&, stack<typename GraphicsMath::matrix_2d>&) noexcept {
						auto amtx = m;
						amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
						const auto controlPt = currentPoint + item.control_pt() * amtx;
						const auto endPt = currentPoint + item.control_pt() * amtx + item.end_pt() * amtx;
						const auto beginPt = currentPoint;
						if (currentPoint == controlPt && controlPt == endPt) {
							return; // degenerate path segment
						}
						const typename GraphicsMath::point_2d& cpt1 = { ((controlPt.x - beginPt.x) * twoThirds) + beginPt.x, ((controlPt.y - beginPt.y) * twoThirds) + beginPt.y };
						const typename GraphicsMath::point_2d& cpt2 = { ((controlPt.x - endPt.x) * twoThirds) + endPt.x, ((controlPt.y - endPt.y) * twoThirds) + endPt.y };
						v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_cubic_curve>, cpt1, cpt2, endPt);
						currentPoint = endPt;
					}
				};

				template <class GraphicsMath, class ForwardIterator>
				inline ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item> _Interpret_path_items(ForwardIterator first, ForwardIterator last);

				template <class GraphicsMath, class Allocator>
				inline ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item> _Interpret_path_items(const path_builder<GraphicsMath, Allocator>& pf) {
					return _Interpret_path_items<GraphicsMath>(begin(pf), end(pf));
				}

				template <class GraphicsMath, class ForwardIterator>
				inline ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item> _Interpret_path_items(ForwardIterator first, ForwardIterator last) {
					typename GraphicsMath::matrix_2d m;
					typename GraphicsMath::point_2d currentPoint; // Tracks the untransformed current point.
					typename GraphicsMath::point_2d closePoint;   // Tracks the transformed close point.
					::std::stack<typename GraphicsMath::matrix_2d> matrices;
					::std::vector<typename basic_figure_items<GraphicsMath>::figure_item> v;

					for (auto val = first; val != last; val++) {
						::std::visit([&m, &currentPoint, &closePoint, &matrices, &v](auto&& item) {
							using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
							_Path_item_interpret_visitor<T>::template _Interpret<T>(item, v, m, currentPoint, closePoint, matrices);
						}, *val);
					}
					return v;
				}

				template <class GraphicsMath, class Allocator>
				inline path_builder<GraphicsMath, Allocator>::path_builder() noexcept(noexcept(Allocator())) :
					path_builder(Allocator()) { }

				template <class GraphicsMath, class Allocator>
				inline path_builder<GraphicsMath, Allocator>::path_builder(const Allocator &a) noexcept
					: _Data(a) {
				}

				template <class GraphicsMath, class Allocator>
				inline path_builder<GraphicsMath, Allocator>::path_builder(size_type n, const Allocator & a)
					: _Data(n, a) {
				}

				template <class GraphicsMath, class Allocator>
				inline path_builder<GraphicsMath, Allocator>::path_builder(size_type n, const value_type & value, const Allocator& a)
					: _Data(n, value, a) {
				}

				template <class GraphicsMath, class Allocator>
				template<class InputIterator>
				inline path_builder<GraphicsMath, Allocator>::path_builder(InputIterator first, InputIterator last, const Allocator& a)
					: _Data(first, last, a) {
				}

				template <class GraphicsMath, class Allocator>
				inline path_builder<GraphicsMath, Allocator>::~path_builder() { }

				template <class GraphicsMath, class Allocator>
				template<class InputIterator>
				inline void path_builder<GraphicsMath, Allocator>::assign(InputIterator first, InputIterator last) {
					_Data.assign(first, last);
				}

				template <class GraphicsMath, class Allocator>
				template<class ...Args>
				inline typename path_builder<GraphicsMath, Allocator>::reference path_builder<GraphicsMath, Allocator>::emplace_back(Args && ...args) {
					return _Data.emplace_back(forward<Args>(args)...);
				}

				template <class GraphicsMath, class Allocator>
				template<class ...Args>
				inline typename path_builder<GraphicsMath, Allocator>::iterator path_builder<GraphicsMath, Allocator>::emplace(const_iterator position, Args&& ...args) {
					return _Data.emplace(position, forward<Args>(args)...);
				}

				template <class GraphicsMath, class Allocator>
				template<class InputIterator>
				inline typename path_builder<GraphicsMath, Allocator>::iterator path_builder<GraphicsMath, Allocator>::insert(const_iterator position, InputIterator first, InputIterator last) {
					return _Data.template insert<InputIterator>(position, first, last);
				}

				template <class GraphicsMath, class Allocator>
				inline path_builder<GraphicsMath, Allocator>::path_builder(const path_builder& pf)
					: _Data(pf._Data) {
				}

				template <class GraphicsMath, class Allocator>
				inline path_builder<GraphicsMath, Allocator>::path_builder(path_builder&& pf) noexcept
					: _Data(move(pf._Data)) {
				}

				template <class GraphicsMath, class Allocator>
				inline path_builder<GraphicsMath, Allocator>::path_builder(const path_builder& pf, const Allocator & a)
					: _Data(pf._Data, a) {
				}

				template <class GraphicsMath, class Allocator>
				inline path_builder<GraphicsMath, Allocator>::path_builder(path_builder&& pf, const Allocator & a)
					: _Data(move(pf._Data), a) {
				}

				template <class GraphicsMath, class Allocator>
				inline path_builder<GraphicsMath, Allocator>::path_builder(initializer_list<value_type> il, const Allocator & a)
					: _Data(il, a) {
				}

				template <class GraphicsMath, class Allocator>
				inline path_builder<GraphicsMath, Allocator>& path_builder<GraphicsMath, Allocator>::operator=(const path_builder& x) {
					_Data = x._Data;
					return *this;
				}
				template <class GraphicsMath, class Allocator>
				inline path_builder<GraphicsMath, Allocator>& path_builder<GraphicsMath, Allocator>::operator=(path_builder&& x) noexcept(allocator_traits<Allocator>::propagate_on_container_move_assignment::value || allocator_traits<Allocator>::is_always_equal::value) {
					::std::swap(_Data, x._Data);
					return *this;
				}
				template <class GraphicsMath, class Allocator>
				inline path_builder<GraphicsMath, Allocator>& path_builder<GraphicsMath, Allocator>::operator=(initializer_list<value_type> il) {
					_Data.clear();
					for (const auto& item : il) {
						_Data.push_back(item);
					}
					return *this;
				}
				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::assign(size_type n, const value_type& u) {
					_Data.assign(n, u);
				}
				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::assign(initializer_list<value_type> il) {
					_Data.assign(il);
				}
				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::allocator_type path_builder<GraphicsMath, Allocator>::get_allocator() const noexcept {
					return _Data.allocator_type();
				}
				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::iterator path_builder<GraphicsMath, Allocator>::begin() noexcept {
					return _Data.begin();
				}
				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::const_iterator path_builder<GraphicsMath, Allocator>::begin() const noexcept {
					return _Data.begin();
				}
				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::const_iterator path_builder<GraphicsMath, Allocator>::cbegin() const noexcept {
					return _Data.cbegin();
				}
				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::iterator path_builder<GraphicsMath, Allocator>::end() noexcept {
					return _Data.end();
				}
				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::const_iterator path_builder<GraphicsMath, Allocator>::end() const noexcept {
					return _Data.end();
				}
				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::const_iterator path_builder<GraphicsMath, Allocator>::cend() const noexcept {
					return _Data.cend();
				}
				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::reverse_iterator path_builder<GraphicsMath, Allocator>::rbegin() noexcept {
					return _Data.rbegin();
				}
				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::const_reverse_iterator path_builder<GraphicsMath, Allocator>::rbegin() const noexcept {
					return _Data.rbegin();
				}
				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::const_reverse_iterator path_builder<GraphicsMath, Allocator>::crbegin() const noexcept {
					return _Data.crbegin();
				}
				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::reverse_iterator path_builder<GraphicsMath, Allocator>::rend() noexcept {
					return _Data.rend();
				}
				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::const_reverse_iterator path_builder<GraphicsMath, Allocator>::rend() const noexcept {
					return _Data.rend();
				}
				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::const_reverse_iterator path_builder<GraphicsMath, Allocator>::crend() const noexcept {
					return _Data.crend();
				}

				template <class GraphicsMath, class Allocator>
				inline bool path_builder<GraphicsMath, Allocator>::empty() const noexcept {
					return _Data.empty();
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::size_type path_builder<GraphicsMath, Allocator>::size() const noexcept {
					return _Data.size();
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::size_type path_builder<GraphicsMath, Allocator>::max_size() const noexcept {
					return _Data.max_size();
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::size_type path_builder<GraphicsMath, Allocator>::capacity() const noexcept {
					return _Data.capacity();
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::resize(size_type sz) {
					_Data.resize(sz);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::resize(size_type sz, const value_type& c) {
					_Data.resize(sz, c);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::reserve(size_type n) {
					_Data.reserve(n);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::shrink_to_fit() {
					_Data.shrink_to_fit();
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::reference path_builder<GraphicsMath, Allocator>::operator[](size_type n) {
					return _Data[n];
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::const_reference path_builder<GraphicsMath, Allocator>::operator[](size_type n) const {
					return _Data[n];
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::const_reference path_builder<GraphicsMath, Allocator>::at(size_type n) const {
					return _Data.at(n);
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::reference path_builder<GraphicsMath, Allocator>::at(size_type n) {
					return _Data.at(n);
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::reference path_builder<GraphicsMath, Allocator>::front() {
					return _Data.front();
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::const_reference path_builder<GraphicsMath, Allocator>::front() const {
					return _Data.front();
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::reference path_builder<GraphicsMath, Allocator>::back() {
					return _Data.back();
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::const_reference path_builder<GraphicsMath, Allocator>::back() const {
					return _Data.back();
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::new_figure(const typename GraphicsMath::point_2d& v) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::abs_new_figure>, v);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::rel_new_figure(const typename GraphicsMath::point_2d& v) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::rel_new_figure>, v);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::close_figure() noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::close_figure>);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::matrix(const typename GraphicsMath::matrix_2d& m) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::abs_matrix>, m);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::rel_matrix(const typename GraphicsMath::matrix_2d& m) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::rel_matrix>, m);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::revert_matrix() noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::revert_matrix>);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::arc(const typename GraphicsMath::point_2d& rad, float rot, const float sang) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::arc>, rad, rot, sang);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::cubic_curve(const typename GraphicsMath::point_2d& pt0, const typename GraphicsMath::point_2d& pt1, const typename GraphicsMath::point_2d& pt2) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::abs_cubic_curve>, pt0, pt1, pt2);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::line(const typename GraphicsMath::point_2d& pt) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::abs_line>, pt);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::quadratic_curve(const typename GraphicsMath::point_2d& pt0, const typename GraphicsMath::point_2d& pt1) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::abs_quadratic_curve>, pt0, pt1);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::rel_cubic_curve(const typename GraphicsMath::point_2d& dpt0, const typename GraphicsMath::point_2d& dpt1, const typename GraphicsMath::point_2d& dpt2) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::rel_cubic_curve>, dpt0, dpt1, dpt2);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::rel_line(const typename GraphicsMath::point_2d& dpt) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::rel_line>, dpt);
				}

				template<class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::rel_quadratic_curve(const typename GraphicsMath::point_2d& dpt0, const typename GraphicsMath::point_2d& dpt1) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::rel_quadratic_curve>, dpt0, dpt1);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::push_back(const value_type& x) {
					_Data.push_back(x);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::push_back(value_type&& x) {
					_Data.push_back(move(x));
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::pop_back() {
					_Data.pop_back();
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::iterator path_builder<GraphicsMath, Allocator>::insert(const_iterator position, const value_type& x) {
					return _Data.insert(position, x);
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::iterator path_builder<GraphicsMath, Allocator>::insert(const_iterator position, value_type&& x) {
					return _Data.insert(position, x);
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::iterator path_builder<GraphicsMath, Allocator>::insert(const_iterator position, size_type n, const value_type& x) {
					return _Data.insert(position, n, x);
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::iterator path_builder<GraphicsMath, Allocator>::insert(const_iterator position, initializer_list<value_type> il) {
					return _Data.insert(position, il);
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::iterator path_builder<GraphicsMath, Allocator>::erase(const_iterator position) {
					return _Data.erase(position);
				}

				template <class GraphicsMath, class Allocator>
				inline typename path_builder<GraphicsMath, Allocator>::iterator path_builder<GraphicsMath, Allocator>::erase(const_iterator first, const_iterator last) {
					return _Data.erase(first, last);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::swap(path_builder &pf) noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value || allocator_traits<Allocator>::is_always_equal::value) {
					::std::swap(_Data, pf._Data);
				}

				template <class GraphicsMath, class Allocator>
				inline void path_builder<GraphicsMath, Allocator>::clear() noexcept {
					_Data.clear();
				}

				/*        template <class GraphicsMath, class Allocator>
						inline bool path_builder<GraphicsMath, Allocator>::operator==(const path_builder& rhs) const noexcept {
							if (size() != rhs.size()) {
								return false;
							}
							//return equal(_Data.cbegin(), _Data.cend(), rhs._Data.cbegin(), rhs._Data.cend());
							auto lhsEnd = _Data.end();
							auto rhsEnd = rhs._Data.end();
							auto lhsIter = _Data.begin();
							auto rhsIter = rhs._Data.begin();
							for (; lhsIter != lhsEnd &&
								rhsIter != rhsEnd; ++lhsIter, ++rhsIter) {
								assert(lhsIter != lhsEnd && "Unexpected path_builder op== size mismatch. rhs greater than lhs.");
								assert(rhsIter != rhsEnd && "Unexpected path_builder op== size mismatch. lhs greater than rhs.");
								if (*lhsIter != *rhsIter) {
									return false;
								}
							}
							//const size_t dataSize = _Data.size();
							//for (size_t i = 0; i < dataSize; i++) {
							//	if (_Data.at(i) != rhs._Data.at(i)) {
							//		return false;
							//	}
							//}
							return true;
						}*/

						//Brushes

				inline constexpr gradient_stop::gradient_stop() noexcept
					: _Offset(0.0F)
					, _Color(rgba_color{}) {}
				inline constexpr gradient_stop::gradient_stop(float offset, const rgba_color& color)
					: _Offset(offset)
					, _Color(color) {}

				inline constexpr void gradient_stop::offset(float value) noexcept {
					_Offset = value;
				}
				inline constexpr void gradient_stop::color(const rgba_color& value) noexcept {
					_Color = value;
				}

				inline constexpr float gradient_stop::offset() const noexcept {
					return _Offset;
				}
				inline constexpr rgba_color gradient_stop::color() const noexcept {
					return _Color;
				}

				inline constexpr bool operator==(const gradient_stop& lhs, const gradient_stop& rhs) noexcept {
					return lhs._Offset == rhs._Offset && lhs._Color == rhs._Color;
				}

				template <class GraphicsMath, class T>
				template <class InputIterator>
				inline brush<GraphicsMath, T>::brush(const circle<GraphicsMath>& start, const circle<GraphicsMath>& end, InputIterator first, InputIterator last)
					: _Brush_impl(start, end, first, last)
				{}

				template <class GraphicsMath, class T>
				inline brush<GraphicsMath, T>::brush(const rgba_color& color)
					: _Brush_impl(color)
				{}

				template<class GraphicsMath, class T>
				template<class InputIterator>
				inline brush<GraphicsMath, T>::brush(const typename GraphicsMath::point_2d& begin, const typename GraphicsMath::point_2d& end, InputIterator first, InputIterator last)
					: _Brush_impl(begin, end, first, last) {
				}
				template<class GraphicsMath, class T>
				inline brush<GraphicsMath, T>::brush(const typename GraphicsMath::point_2d& begin, const typename GraphicsMath::point_2d& end, ::std::initializer_list<gradient_stop> il)
					: _Brush_impl(begin, end, il)
				{}

				template <class GraphicsMath, class T>
				inline brush<GraphicsMath, T>::brush(const circle<GraphicsMath>& start, const circle<GraphicsMath>& end, ::std::initializer_list<gradient_stop> il)
					: _Brush_impl(start, end, il)
				{}

				template <class GraphicsMath, class T>
				inline brush_type brush<GraphicsMath, T>::type() const noexcept {
					return _Brush_impl.type();
				}

				// display_point

				inline constexpr display_point::display_point() noexcept
					: x(0)
					, y(0)
				{}

				inline constexpr display_point::display_point(int _X, int _Y) noexcept
					: x(_X)
					, y(_Y)
				{}

				constexpr inline bool operator==(const display_point& lhs, const display_point& rhs) noexcept
				{
					return (lhs.x == rhs.x) && (lhs.y == rhs.y);
				}

				constexpr inline bool operator!=(const display_point& lhs, const display_point& rhs) noexcept
				{
					return !(lhs == rhs);
				}


				// mapped_surface

				template <class GraphicsMath, class T>
				inline mapped_surface<GraphicsMath, T>::mapped_surface(typename surface<GraphicsMath, T>::native_handle_type nh, typename surface<GraphicsMath, T>::native_handle_type map_of)
					: _Mapped_surface_impl(nh, map_of)
				{}

				template <class GraphicsMath, class T>
				inline mapped_surface<GraphicsMath, T>::mapped_surface(typename surface<GraphicsMath, T>::native_handle_type nh, typename surface<GraphicsMath, T>::native_handle_type map_of, error_code& ec) noexcept
					: _Mapped_surface_impl(nh, map_of, ec)
				{}

				template <class GraphicsMath, class T>
				inline void mapped_surface<GraphicsMath, T>::commit_changes() {
					_Mapped_surface_impl.commit_changes();
				}

				template <class GraphicsMath, class T>
				inline void mapped_surface<GraphicsMath, T>::commit_changes(::std::error_code& ec) noexcept {
					_Mapped_surface_impl.commit_changes(ec);
				}

				template <class GraphicsMath, class T>
				inline unsigned char* mapped_surface<GraphicsMath, T>::data() {
					return _Mapped_surface_impl.data();
				}

				template <class GraphicsMath, class T>
				inline unsigned char* mapped_surface<GraphicsMath, T>::data(error_code& ec) noexcept {
					return _Mapped_surface_impl.data(ec);
				}

				template <class GraphicsMath, class T>
				inline const unsigned char* mapped_surface<GraphicsMath, T>::data() const {
					return _Mapped_surface_impl.data();
				}

				template <class GraphicsMath, class T>
				inline const unsigned char* mapped_surface<GraphicsMath, T>::data(error_code& ec) const noexcept {
					return _Mapped_surface_impl.data(ec);
				}

				template <class GraphicsMath, class T>
				inline ::std::experimental::io2d::format mapped_surface<GraphicsMath, T>::format() const noexcept {
					return _Mapped_surface_impl.format();
				}

				template <class GraphicsMath, class T>
				inline int mapped_surface<GraphicsMath, T>::width() const noexcept {
					return _Mapped_surface_impl.width();
				}

				template <class GraphicsMath, class T>
				inline int mapped_surface<GraphicsMath, T>::height() const noexcept {
					return _Mapped_surface_impl.height();
				}

				template <class GraphicsMath, class T>
				inline int mapped_surface<GraphicsMath, T>::stride() const noexcept {
					return _Mapped_surface_impl.stride();
				}

				// Standalone functions

				template <class GraphicsMath, class T>
				inline display_surface<GraphicsMath, T> make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, scaling scl) {
					return { preferredWidth, preferredHeight, preferredFormat, scl };
				}

				template <class GraphicsMath, class T, class U>
				inline handler<T> make_handler(display_surface<GraphicsMath, U>& ds, int preferredDisplayWidth, int preferredDisplayHeight, refresh_rate rr, float desiredFramerate) {
					return { ds, preferredDisplayWidth, preferredDisplayHeight, rr, desiredFramerate };
				}

				template <class GraphicsMath, class T>
				inline image_surface<GraphicsMath, T> make_image_surface(format fmt, int width, int height) {
					return image_surface<T>(fmt, width, height);
				}

				template <class GraphicsMath, class T>
				inline image_surface<GraphicsMath, T> copy_image_surface(image_surface<GraphicsMath, T>& sfc) noexcept {
					image_surface<GraphicsMath, T> retval(sfc.format(), sfc.width(), sfc.height());
					retval.map([&sfc](mapped_surface<GraphicsMath, T>& rvms) {
						sfc.map([&rvms](mapped_surface<GraphicsMath, T>& sfcms) {
							memcpy(rvms.data(), sfcms.data(), static_cast<size_t>(rvms.height() * rvms.stride()));
						});
					});
					retval.mark_dirty();
					return retval;
				}
			}
		}
	}
}