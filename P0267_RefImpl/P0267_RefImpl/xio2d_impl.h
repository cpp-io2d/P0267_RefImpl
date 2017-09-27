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

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
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
				template <class Point2d>
				inline Point2d _Rotate_point_absolute_angle(const Point2d& center, float radius, float angle, bool clockwise = true) {
					if (clockwise) {
						return Point2d((radius * ::std::cos(angle)) + center.x(), (-(radius * -::std::sin(angle))) + center.y());
					}
					else {
						return Point2d((radius * ::std::cos(angle)) + center.x(), (radius * -::std::sin(angle)) + center.y());
					}
				}

				template <class LinearAlgebra>
				inline typename LinearAlgebra::point_2d point_for_angle(float ang, float mgn) noexcept {
					LinearAlgebra::point_2d v{ mgn, 0.0F };
					auto m = LinearAlgebra::matrix_2d::init_rotate(ang);
					auto result = m.transform_pt(v);
					result.x = _Round_floating_point_to_zero(result.x);
					result.y = _Round_floating_point_to_zero(result.y);
					return result;
				}

				template <class LinearAlgebra>
				typename LinearAlgebra::point_2d point_for_angle(float ang, const typename LinearAlgebra::point_2d& rad) noexcept {
					LinearAlgebra::point_2d v{ 1.0F, 0.0F };
					auto m = LinearAlgebra::matrix_2d::init_rotate(ang);
					auto result = m.transform_pt(v);
					result *= rad;
					result.x = _Round_floating_point_to_zero(result.x);
					result.y = _Round_floating_point_to_zero(result.y);
					return result;
				}

				template <class LinearAlgebra>
				float angle_for_point(const typename LinearAlgebra::point_2d& ctr, const typename LinearAlgebra::point_2d& pt) noexcept {
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

				template <class LinearAlgebra>
				inline constexpr const typename LinearAlgebra::point_2d_data_type& basic_linear_algebra<LinearAlgebra>::point_2d::_Get_data() const noexcept {
					return _Data;
				}
				template <class LinearAlgebra>
				inline constexpr basic_linear_algebra<LinearAlgebra>::point_2d::point_2d(const typename LinearAlgebra::point_2d_data_type& val) noexcept
					: _Data(val) {}

				template <class LinearAlgebra>
				inline constexpr basic_linear_algebra<LinearAlgebra>::point_2d::point_2d() noexcept
					: basic_linear_algebra<LinearAlgebra>::point_2d::point_2d(0.0f, 0.0f) {}
				template <class LinearAlgebra>
				inline constexpr basic_linear_algebra<LinearAlgebra>::point_2d::point_2d(float xval, float yval) noexcept
					: _Data(LinearAlgebra::create(xval, yval)) {
				}
				template <class LinearAlgebra>
				inline constexpr void basic_linear_algebra<LinearAlgebra>::point_2d::x(float xval) noexcept {
					LinearAlgebra::x(_Data, xval);
				}
				template <class LinearAlgebra>
				inline constexpr void basic_linear_algebra<LinearAlgebra>::point_2d::y(float yval) noexcept {
					LinearAlgebra::y(_Data, yval);
				}
				template <class LinearAlgebra>
				inline constexpr float basic_linear_algebra<LinearAlgebra>::point_2d::x() const noexcept {
					return LinearAlgebra::y(_Data);
				}
				template <class LinearAlgebra>
				inline constexpr float basic_linear_algebra<LinearAlgebra>::point_2d::y() const noexcept {
					return LinearAlgebra::y(_Data);
				}
				template <class LinearAlgebra>
				inline float basic_linear_algebra<LinearAlgebra>::point_2d::magnitude() const noexcept {
					return LinearAlgebra::magnitude(_Data);
				}
				template <class LinearAlgebra>
				inline constexpr float basic_linear_algebra<LinearAlgebra>::point_2d::magnitude_squared() const noexcept {
					return LinearAlgebra::magniture_square(_Data);
				}
				template <class LinearAlgebra>
				inline constexpr float basic_linear_algebra<LinearAlgebra>::point_2d::dot(const typename basic_linear_algebra<LinearAlgebra>::point_2d& other) const noexcept {
					return LinearAlgebra::dot(_Data, other._Data);
				}
				template <class LinearAlgebra>
				inline float basic_linear_algebra<LinearAlgebra>::point_2d::angular_direction() const noexcept {
					return LinearAlgebra::angular_direction(_Data);
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d basic_linear_algebra<LinearAlgebra>::point_2d::zero() noexcept {
					return point_2d(LinearAlgebra::create());
				}
				template <class LinearAlgebra>
				inline typename basic_linear_algebra<LinearAlgebra>::point_2d basic_linear_algebra<LinearAlgebra>::point_2d::to_unit() const noexcept {
					return point_2d(LinearAlgebra::to_unit(_Data));
				}
				template <class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept {
					return LinearAlgebra::equal(lhs._Get_data(), rhs._Get_data());
				}
				template <class LinearAlgebra>
				inline constexpr bool operator!=(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept {
					return LinearAlgebra::not_equal(lhs._Get_data(), rhs._Get_data());
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator+(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs) noexcept {
					return lhs;
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator+(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept {
					return basic_linear_algebra<LinearAlgebra>::point_2d(LinearAlgebra::add(lhs._Get_data(), rhs._Get_data()));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator+(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, float rhs) noexcept {
					return basic_linear_algebra<LinearAlgebra>::point_2d(LinearAlgebra::add(lhs._Get_data(), rhs));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator+(float lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept {
					return basic_linear_algebra<LinearAlgebra>::point_2d(LinearAlgebra::add(lhs, rhs._Get_data()));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d& basic_linear_algebra<LinearAlgebra>::point_2d::operator+=(const basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept {
					_Data = LinearAlgebra::add(_Data, rhs._Data);
					return *this;
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d& basic_linear_algebra<LinearAlgebra>::point_2d::operator+=(float rhs) noexcept {
					_Data = LinearAlgebra::add(_Data, rhs);
					return *this;
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator-(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs) noexcept {
					return basic_linear_algebra<LinearAlgebra>::point_2d(LinearAlgebra::negate(lhs._Get_data()));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator-(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept {
					return basic_linear_algebra<LinearAlgebra>::point_2d::point_2d(LinearAlgebra::subtract(lhs._Get_data(), rhs._Get_data()));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator-(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, float rhs) noexcept {
					return basic_linear_algebra<LinearAlgebra>::point_2d::point_2d(LinearAlgebra::subtract(lhs._Get_data(), rhs));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator-(float lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept {
					return basic_linear_algebra<LinearAlgebra>::point_2d::point_2d(LinearAlgebra::subtract(lhs, rhs._Get_data()));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d& basic_linear_algebra<LinearAlgebra>::point_2d::operator-=(const basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept {
					_Data = LinearAlgebra::subtract(_Data, rhs._Get_data());
					return *this;
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d& basic_linear_algebra<LinearAlgebra>::point_2d::operator-=(float rhs) noexcept {
					_Data = LinearAlgebra::subtract(_Data, rhs);
					return *this;
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d& basic_linear_algebra<LinearAlgebra>::point_2d::operator*=(float rhs) noexcept {
					_Data = LinearAlgebra::multiply(_Data, rhs);
					return *this;
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d& basic_linear_algebra<LinearAlgebra>::point_2d::operator*=(const basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept {
					_Data = LinearAlgebra::multiply(_Data, rhs._Get_data());
					return *this;
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator*(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, float rhs) noexcept {
					return basic_linear_algebra<LinearAlgebra>::point_2d(LinearAlgebra::multiply(lhs._Get_data(), rhs));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator*(float lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept {
					return basic_linear_algebra<LinearAlgebra>::point_2d(LinearAlgebra::multiply(lhs, rhs._Get_data()));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator*(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept {
					return basic_linear_algebra<LinearAlgebra>::point_2d(LinearAlgebra::multiply(lhs._Get_data(), rhs._Get_data()));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d& basic_linear_algebra<LinearAlgebra>::point_2d::operator/=(float rhs) noexcept {
					_Data = LinearAlgebra::divide(_Data, rhs);
					return *this;
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d& basic_linear_algebra<LinearAlgebra>::point_2d::operator/=(const basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept {
					_Data = LinearAlgebra::divide(_Data, rhs._Get_data());
					return *this;
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator/(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, float rhs) noexcept {
					return basic_linear_algebra<LinearAlgebra>::point_2d(LinearAlgebra::divide(lhs._Get_data(), rhs));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator/(float lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept {
					return basic_linear_algebra<LinearAlgebra>::point_2d(LinearAlgebra::divide(lhs, rhs._Get_data()));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator/(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept {
					return basic_linear_algebra<LinearAlgebra>::point_2d(LinearAlgebra::divide(lhs._Get_data(), rhs._Get_data()));
				}

				//
				// basic_linear_algebra::matrix_2d
				//

				template <class LinearAlgebra>
				inline constexpr const typename LinearAlgebra::matrix_2d_data_type& basic_linear_algebra<LinearAlgebra>::matrix_2d::_Get_data() const noexcept {
					return _Data;
				}
				template <class LinearAlgebra>
				inline constexpr basic_linear_algebra<LinearAlgebra>::matrix_2d::matrix_2d(const data_type& val) noexcept
					: _Data(val) {
				}
				template <class LinearAlgebra>
				inline constexpr basic_linear_algebra<LinearAlgebra>::matrix_2d::matrix_2d() noexcept
					: _Data(LinearAlgebra::init_identity()) {}
				template <class LinearAlgebra>
				inline constexpr basic_linear_algebra<LinearAlgebra>::matrix_2d::matrix_2d(float v00, float v01, float v10, float v11, float v20, float v21) noexcept
					: _Data(LinearAlgebra::init_values(v00, v01, v10, v11, v20, v21)) {
				}
				template <class LinearAlgebra>
				inline constexpr void basic_linear_algebra<LinearAlgebra>::matrix_2d::m00(float val) noexcept {
					LinearAlgebra::m00(val);
				}
				template <class LinearAlgebra>
				inline constexpr void basic_linear_algebra<LinearAlgebra>::matrix_2d::m01(float val) noexcept {
					LinearAlgebra::m01(val);
				}
				template <class LinearAlgebra>
				inline constexpr void basic_linear_algebra<LinearAlgebra>::matrix_2d::m10(float val) noexcept {
					LinearAlgebra::m10(_Data, val);
				}
				template <class LinearAlgebra>
				inline constexpr void basic_linear_algebra<LinearAlgebra>::matrix_2d::m11(float val) noexcept {
					LinearAlgebra::m11(val);
				}
				template <class LinearAlgebra>
				inline constexpr void basic_linear_algebra<LinearAlgebra>::matrix_2d::m20(float val) noexcept {
					LinearAlgebra::m20(val);
				}
				template <class LinearAlgebra>
				inline constexpr void basic_linear_algebra<LinearAlgebra>::matrix_2d::m21(float val) noexcept {
					LinearAlgebra::m21(val);
				}
				template <class LinearAlgebra>
				inline constexpr float basic_linear_algebra<LinearAlgebra>::matrix_2d::m00() const noexcept {
					return LinearAlgebra::m00();
				}
				template <class LinearAlgebra>
				inline constexpr float basic_linear_algebra<LinearAlgebra>::matrix_2d::m01() const noexcept {
					return LinearAlgebra::m01();
				}
				template <class LinearAlgebra>
				inline constexpr float basic_linear_algebra<LinearAlgebra>::matrix_2d::m10() const noexcept {
					return LinearAlgebra::m10();
				}
				template <class LinearAlgebra>
				inline constexpr float basic_linear_algebra<LinearAlgebra>::matrix_2d::m11() const noexcept {
					return LinearAlgebra::m11();
				}
				template <class LinearAlgebra>
				inline constexpr float basic_linear_algebra<LinearAlgebra>::matrix_2d::m20() const noexcept {
					return LinearAlgebra::m20();
				}
				template <class LinearAlgebra>
				inline constexpr float basic_linear_algebra<LinearAlgebra>::matrix_2d::m21() const noexcept {
					return LinearAlgebra::m21();
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::matrix_2d basic_linear_algebra<LinearAlgebra>::matrix_2d::init_translate(const basic_linear_algebra<LinearAlgebra>::point_2d& value) noexcept {
					return basic_linear_algebra<LinearAlgebra>::matrix_2d(LinearAlgebra::init_translate(value));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::matrix_2d basic_linear_algebra<LinearAlgebra>::matrix_2d::init_scale(const basic_linear_algebra<LinearAlgebra>::point_2d& value) noexcept {
					return basic_linear_algebra<LinearAlgebra>::matrix_2d(LinearAlgebra::init_scale(value));
				}
				template <class LinearAlgebra>
				inline typename basic_linear_algebra<LinearAlgebra>::matrix_2d basic_linear_algebra<LinearAlgebra>::matrix_2d::init_rotate(float radians) noexcept {
					return basic_linear_algebra<LinearAlgebra>::matrix_2d(LinearAlgebra::init_rotate(radians));
				}
				template <class LinearAlgebra>
				inline typename basic_linear_algebra<LinearAlgebra>::matrix_2d basic_linear_algebra<LinearAlgebra>::matrix_2d::init_rotate(float radians, const basic_linear_algebra<LinearAlgebra>::point_2d& origin) noexcept {
					return basic_linear_algebra<LinearAlgebra>::matrix_2d(LinearAlgebra::init_rotate(radians, origin));
				}
				template <class LinearAlgebra>
				inline typename basic_linear_algebra<LinearAlgebra>::matrix_2d basic_linear_algebra<LinearAlgebra>::matrix_2d::init_reflect(float radians) noexcept {
					return basic_linear_algebra<LinearAlgebra>::matrix_2d(LinearAlgebra::init_reflect(radians));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::matrix_2d basic_linear_algebra<LinearAlgebra>::matrix_2d::init_shear_x(float factor) noexcept {
					return basic_linear_algebra<LinearAlgebra>::matrix_2d(U::init_shear_x(factor));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::matrix_2d basic_linear_algebra<LinearAlgebra>::matrix_2d::init_shear_y(float factor) noexcept {
					return basic_linear_algebra<LinearAlgebra>::matrix_2d(LinearAlgebra::init_shear_y(factor));
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::matrix_2d& basic_linear_algebra<LinearAlgebra>::matrix_2d::translate(const basic_linear_algebra<LinearAlgebra>::point_2d& val) noexcept {
					LinearAlgebra::translate(_Data, val);
					return *this;
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::matrix_2d& basic_linear_algebra<LinearAlgebra>::matrix_2d::scale(const basic_linear_algebra<LinearAlgebra>::point_2d& val) noexcept {
					LinearAlgebra::scale(_Data, val);
					return *this;
				}
				template <class LinearAlgebra>
				inline typename basic_linear_algebra<LinearAlgebra>::matrix_2d& basic_linear_algebra<LinearAlgebra>::matrix_2d::rotate(float radians) noexcept {
					LinearAlgebra::rotate(_Data, radians);
					return *this;
				}
				template <class LinearAlgebra>
				inline typename basic_linear_algebra<LinearAlgebra>::matrix_2d& basic_linear_algebra<LinearAlgebra>::matrix_2d::rotate(float radians, const basic_linear_algebra<LinearAlgebra>::point_2d& origin) noexcept {
					LinearAlgebra::rotate(_Data, radians, origin);
					return *this;
				}
				template <class LinearAlgebra>
				inline typename basic_linear_algebra<LinearAlgebra>::matrix_2d& basic_linear_algebra<LinearAlgebra>::matrix_2d::reflect(float radians) noexcept {
					LinearAlgebra::reflect(_Data, radians);
					return *this;
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::matrix_2d& basic_linear_algebra<LinearAlgebra>::matrix_2d::shear_x(float factor) noexcept {
					LinearAlgebra::shear_x(_Data, factor);
					return *this;
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::matrix_2d& basic_linear_algebra<LinearAlgebra>::matrix_2d::shear_y(float factor) noexcept {
					LinearAlgebra::shear_y(_Data, factor);
					return *this;
				}
				template <class LinearAlgebra>
				inline constexpr bool basic_linear_algebra<LinearAlgebra>::matrix_2d::is_invertible() const noexcept {
					return LinearAlgebra::is_invertible(_Data);
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::matrix_2d basic_linear_algebra<LinearAlgebra>::matrix_2d::inverse() const noexcept {
					return LinearAlgebra::inverse(_Data);
				}
				template <class LinearAlgebra>
				inline constexpr bool basic_linear_algebra<LinearAlgebra>::matrix_2d::is_finite() const noexcept {
					return LinearAlgebra::is_finite(_Data);
				}
				template <class LinearAlgebra>
				inline constexpr float basic_linear_algebra<LinearAlgebra>::matrix_2d::determinant() const noexcept {
					return LinearAlgebra::determinant(_Data);
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d basic_linear_algebra<LinearAlgebra>::matrix_2d::transform_pt(const basic_linear_algebra<LinearAlgebra>::point_2d& pt) const noexcept {
					return LinearAlgebra::transform_pt(_Data, pt);
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::matrix_2d& basic_linear_algebra<LinearAlgebra>::matrix_2d::operator*=(const basic_linear_algebra<LinearAlgebra>::matrix_2d& rhs) noexcept {
					_Data = LinearAlgebra::multiply(_Data, rhs._Data);
					return *this;
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::matrix_2d operator*(const typename basic_linear_algebra<LinearAlgebra>::matrix_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::matrix_2d& rhs) noexcept {
					return basic_linear_algebra<LinearAlgebra>::matrix_2d(LinearAlgebra::multiply(lhs._Get_data(), rhs._Get_data()));
				}
				template <class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_linear_algebra<LinearAlgebra>::matrix_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::matrix_2d& rhs) noexcept {
					return LinearAlgebra::equal(lhs._Get_data(), rhs._Get_data());
				}
				template <class LinearAlgebra>
				inline constexpr bool operator!=(const typename basic_linear_algebra<LinearAlgebra>::matrix_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::matrix_2d& rhs) noexcept {
					return LinearAlgebra::not_equal(lhs._Get_data(), rhs._Get_data());
				}
				template <class LinearAlgebra>
				inline constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator*(const typename basic_linear_algebra<LinearAlgebra>::point_2d& pt, const typename basic_linear_algebra<LinearAlgebra>::matrix_2d& m) noexcept {
					return LinearAlgebra::transform_pt(m, pt);
				}


				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::create() noexcept {
					return create(0.0f, 0.0f);
				}

				inline typename _Linear_algebra_float_impl::point_2d_data_type _Linear_algebra_float_impl::create(float x, float y) noexcept {
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
					return create(-val._X, -val._Y);
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
				inline constexpr typename matrix_2d_data_type _Linear_algebra_float_impl::init_elements(float v00, float v01, float v10, float v11, float v20, float v21) noexcept {
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

				inline constexpr typename matrix_2d_data_type _Linear_algebra_float_impl::init_identity() noexcept {
					return init_elements(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
				}

				template<class Point2d>
				inline constexpr matrix_2d_data_type std::experimental::io2d::v1::_Linear_algebra_float_impl::init_translate(const Point2d& val) noexcept {
					return init_elements(1.0f, 0.0f, 0.0f, 1.0f, val.x(), val.y());
				}

				template<class Point2d>
				inline constexpr matrix_2d_data_type std::experimental::io2d::v1::_Linear_algebra_float_impl::init_scale(const Point2d& val) noexcept {
					return init_elements(1.0f, 0.0f, 0.0f, 1.0f, val.x(), val.y());
				}

				inline typename matrix_2d_data_type _Linear_algebra_float_impl::init_rotate(float radians) noexcept {
					auto sine = sin(radians);
					auto cosine = cos(radians);
					sine = _Round_floating_point_to_zero(sine);
					cosine = _Round_floating_point_to_zero(cosine);
					return init_elements(cosine, -sine, sine, cosine, 0.0f, 0.0f);
				}

				template <class Point2d>
				inline typename matrix_2d_data_type _Linear_algebra_float_impl::init_rotate(float radians, const Point2d& origin) noexcept {
					return multiply(multiply(init_translate(origin), init_rotate(radians)), init_translate(-origin));
				}

				inline typename matrix_2d_data_type _Linear_algebra_float_impl::init_reflect(float radians) noexcept {
					auto sine = sin(radians * 2.0f);
					auto cosine = cos(radians * 2.0f);
					sine = _Round_floating_point_to_zero(sine);
					cosine = _Round_floating_point_to_zero(cosine);
					return init_elements(cosine, sine, sine, -cosine, 0.0f, 0.0f);
				}

				inline constexpr typename matrix_2d_data_type _Linear_algebra_float_impl::init_shear_x(float factor) noexcept {
					return init_elements(1.0f, 0.0f, factor, 1.0f, 0.0f, 0.0f);
				}

				inline constexpr typename matrix_2d_data_type _Linear_algebra_float_impl::init_shear_y(float factor) noexcept {
					return init_elements(1.0f, factor, 0.0f, 1.0f, 0.0f, 0.0f);
				}

				template <class Point2d>
				inline constexpr void _Linear_algebra_float_impl::translate(matrix_2d_data_type& mtx, const Point2d& v) noexcept {
					mtx = multiply(mtx, init_translate(v));
				}

				template <class Point2d>
				inline constexpr void _Linear_algebra_float_impl::scale(matrix_2d_data_type& mtx, const Point2d& scl) noexcept {
					mtx = multiply(mtx, init_scale(scl));
				}

				inline void _Linear_algebra_float_impl::rotate(matrix_2d_data_type& mtx, float radians) noexcept {
					mtx = multiply(mtx, init_rotate(radians));
				}

				template <class Point2d>
				inline void _Linear_algebra_float_impl::rotate(matrix_2d_data_type& mtx, float radians, const Point2d& origin) noexcept {
					mtx = multiply(mtx, init_rotate(radians, origin));
				}

				inline void _Linear_algebra_float_impl::reflect(typename matrix_2d_data_type& mtx, float radians) noexcept {
					mtx = multiply(mtx, init_reflect(radians));
				}

				inline constexpr void _Linear_algebra_float_impl::shear_x(typename matrix_2d_data_type& mtx, float factor) noexcept {
					mtx = multiply(mtx, init_shear_x(factor));
				}

				inline constexpr void _Linear_algebra_float_impl::shear_y(typename matrix_2d_data_type& mtx, float factor) noexcept {
					mtx = multiply(mtx, init_shear_y(factor));
				}

				constexpr bool _Is_finite_check(float) noexcept;
				inline constexpr bool _Is_finite_check(float val) noexcept {
					const float infinity = ::std::numeric_limits<float>::infinity();
					return val != infinity &&
						val != -infinity &&
						!(val != val);
					// This checks for both types of NaN. Compilers are not supposed to optimize this away but there were some in the past that incorrectly did. The only way to be sure is to check the documentation and any compiler switches you may be using.
				}

				inline constexpr bool _Linear_algebra_float_impl::is_finite(const typename matrix_2d_data_type& mtx) noexcept {
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

				inline constexpr typename matrix_2d_data_type _Linear_algebra_float_impl::inverse(const typename matrix_2d_data_type& mtx) noexcept {
					const auto inverseDeterminant = 1.0F / determinant(mtx);
					return init_elements(
						(mtx.m11 * 1.0F - 0.0F * mtx.m21) * inverseDeterminant,
						-(mtx.m01 * 1.0F - 0.0F * mtx.m21) * inverseDeterminant,
						-(mtx.m10 * 1.0F - 0.0F * mtx.m20) * inverseDeterminant,
						(mtx.m00 * 1.0F - 0.0F * mtx.m20) * inverseDeterminant,
						(mtx.m10 * mtx.m21 - mtx.m11 * mtx.m20) * inverseDeterminant,
						-(mtx.m00 * mtx.m21 - mtx.m01 * mtx.m20) * inverseDeterminant
					);
				}

				template <class Point2d>
				inline constexpr Point2d _Linear_algebra_float_impl::transform_pt(const matrix_2d_data_type& mtx, const Point2d& pt) noexcept {
					const auto x = pt.x();
					const auto y = pt.y();
					Point2d result(_Round_floating_point_to_zero(mtx.m00 * x + mtx.m10 * y + mtx.m20), _Round_floating_point_to_zero(mtx.m01 * x + mtx.m11 * y + mtx.m21));
					return result;
				}

				inline constexpr matrix_2d_data_type _Linear_algebra_float_impl::multiply(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept {
					return init_elements(
						(lhs.m00 * rhs.m00) + (lhs.m01 * rhs.m10),
						(lhs.m00 * rhs.m01) + (lhs.m01 * rhs.m11),
						(lhs.m10 * rhs.m00) + (lhs.m11 * rhs.m10),
						(lhs.m10 * rhs.m01) + (lhs.m11 * rhs.m11),
						(lhs.m20 * rhs.m00) + (lhs.m21 * rhs.m10) + rhs.m20,
						(lhs.m20 * rhs.m01) + (lhs.m21 * rhs.m11) + rhs.m21
					);
				}

				inline constexpr bool _Linear_algebra_float_impl::equal(const typename matrix_2d_data_type& lhs, const typename matrix_2d_data_type& rhs) noexcept {
					return lhs.m00 == rhs.m00 && lhs.m01 == rhs.m01 &&
						lhs.m10 == rhs.m10 && lhs.m11 == rhs.m11 &&
						lhs.m20 == rhs.m20 && lhs.m21 == rhs.m21;
				}

				inline constexpr bool _Linear_algebra_float_impl::not_equal(const typename matrix_2d_data_type& lhs, const typename matrix_2d_data_type& rhs) noexcept {
					return !equal(lhs, rhs);
				}

				template <class LinearAlgebra>
				inline typename LinearAlgebra::point_2d arc_start(const typename LinearAlgebra::point_2d& ctr, float sang, const typename LinearAlgebra::point_2d& rad) noexcept {
					LinearAlgebra::matrix_2d lmtx = LinearAlgebra::matrix_2d();
					lmtx.m20(0.0f); lmtx.m21(0.0f); // Eliminate translation.
					auto pt = point_for_angle<LinearAlgebra>(sang, rad);
					return ctr + pt * lmtx;
				}

				template <class LinearAlgebra>
				inline typename LinearAlgebra::point_2d arc_start(const typename LinearAlgebra::point_2d& ctr, float sang, const typename LinearAlgebra::point_2d& rad, const typename LinearAlgebra::matrix_2d& m) noexcept {
					auto lmtx = m;
					lmtx.m20(0.0f); lmtx.m21(0.0f); // Eliminate translation.
					auto pt = point_for_angle<LinearAlgebra>(sang, rad);
					return ctr + pt * lmtx;
				}

				template <class LinearAlgebra>
				inline typename LinearAlgebra::point_2d arc_center(const typename LinearAlgebra::point_2d& cpt, float sang, const typename LinearAlgebra::point_2d& rad) noexcept {
					LinearAlgebra::matrix_2d lmtx = LinearAlgebra::matrix_2d();
					lmtx.m20(0.0f); lmtx.m21(0.0f); // Eliminate translation.
					auto centerOffset = point_for_angle<LinearAlgebra>(two_pi<float> -sang, rad);
					centerOffset.y(-centerOffset.y());
					return cpt - centerOffset * lmtx;
				}

				template <class LinearAlgebra>
				inline typename LinearAlgebra::point_2d arc_center(const typename LinearAlgebra::point_2d& cpt, float sang, const typename LinearAlgebra::point_2d& rad, const typename LinearAlgebra::matrix_2d& m) noexcept {
					auto lmtx = m;
					lmtx.m20(0.0f); lmtx.m21(0.0f); // Eliminate translation.
					auto centerOffset = point_for_angle<LinearAlgebra>(two_pi<float> -sang, rad);
					centerOffset.y(-centerOffset.y());
					return cpt - centerOffset * lmtx;
				}

				template <class LinearAlgebra>
				inline typename LinearAlgebra::point_2d arc_end(const typename LinearAlgebra::point_2d& cpt, float eang, const typename LinearAlgebra::point_2d& rad) noexcept {
					LinearAlgebra::matrix_2d lmtx = LinearAlgebra::matrix_2d();
					auto tfrm = LinearAlgebra::matrix_2d::init_rotate(eang);
					lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
					auto pt = (rad * tfrm);
					pt.y(-pt.y());
					return cpt + pt * lmtx;
				}

				template <class LinearAlgebra>
				inline typename LinearAlgebra::point_2d arc_end(const typename LinearAlgebra::point_2d& cpt, float eang, const typename LinearAlgebra::point_2d& rad, const typename LinearAlgebra::matrix_2d& m) noexcept {
					auto lmtx = m;
					auto tfrm = LinearAlgebra::matrix_2d::init_rotate(eang);
					lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
					auto pt = (rad * tfrm);
					pt.y(-pt.y);
					return cpt + pt * lmtx;
				}

				// Geometry

				template <class LinearAlgebra>
				inline constexpr bounding_box<LinearAlgebra>::basic_bounding_box() noexcept { }
				template <class LinearAlgebra>
				inline constexpr bounding_box<LinearAlgebra>::basic_bounding_box(float x, float y, float width, float height) noexcept
					: _X(x)
					, _Y(y)
					, _Width(width)
					, _Height(height) {
				}
				template <class LinearAlgebra>
				inline constexpr bounding_box<LinearAlgebra>::bounding_box(const typename LinearAlgebra::point_2d& tl, const typename LinearAlgebra::point_2d& br) noexcept
					: _X(tl.x())
					, _Y(tl.y())
					, _Width(::std::max(0.0F, br.x() - tl.x()))
					, _Height(::std::max(0.0F, br.y() - tl.y())) {
				}

				template <class LinearAlgebra>
				inline constexpr void bounding_box<LinearAlgebra>::x(float value) noexcept {
					_X = value;
				}
				template <class LinearAlgebra>
				inline constexpr void bounding_box<LinearAlgebra>::y(float value) noexcept {
					_Y = value;
				}
				template <class LinearAlgebra>
				inline constexpr void bounding_box<LinearAlgebra>::width(float value) noexcept {
					_Width = value;
				}
				template <class LinearAlgebra>
				inline constexpr void bounding_box<LinearAlgebra>::height(float value) noexcept {
					_Height = value;
				}
				template <class LinearAlgebra>
				inline constexpr void bounding_box<LinearAlgebra>::top_left(const typename LinearAlgebra::point_2d& value) noexcept {
					_X = value.x();
					_Y = value.y();
				}
				template <class LinearAlgebra>
				inline constexpr void bounding_box<LinearAlgebra>::bottom_right(const typename LinearAlgebra::point_2d& value) noexcept {
					_Width = max(0.0F, value.x() - _X);
					_Height = max(0.0F, value.y() - _Y);
				}

				template <class LinearAlgebra>
				inline constexpr float bounding_box<LinearAlgebra>::x() const noexcept {
					return _X;
				}

				template <class LinearAlgebra>
				inline constexpr float bounding_box<LinearAlgebra>::y() const noexcept {
					return _Y;
				}

				template <class LinearAlgebra>
				inline constexpr float bounding_box<LinearAlgebra>::width() const noexcept {
					return _Width;
				}

				template <class LinearAlgebra>
				inline constexpr float bounding_box<LinearAlgebra>::height() const noexcept {
					return _Height;
				}

				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d bounding_box<LinearAlgebra>::top_left() const noexcept {
					return typename LinearAlgebra::point_2d{ _X, _Y };
				}

				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d bounding_box<LinearAlgebra>::bottom_right() const noexcept {
					return typename LinearAlgebra::point_2d{ _X + _Width, _Y + _Height };
				}

				template <class LinearAlgebra>
				inline constexpr bool operator==(const bounding_box<LinearAlgebra>& lhs, const bounding_box<LinearAlgebra>& rhs)
					noexcept {
					return lhs._X == rhs._X && lhs._Y == rhs._Y && lhs._Width == rhs._Width && lhs._Height == rhs._Height;
				}
				template <class LinearAlgebra>
				inline constexpr bool operator!=(const bounding_box<LinearAlgebra>& lhs, const bounding_box<LinearAlgebra>& rhs)
					noexcept {
					return !(lhs == rhs);
				}

				template <class LinearAlgebra>
				inline constexpr basic_circle<LinearAlgebra>::basic_circle() noexcept
					: _X()
					, _Y()
					, _Radius() {}
				template <class LinearAlgebra>
				inline constexpr basic_circle<LinearAlgebra>::basic_circle(const typename LinearAlgebra::point_2d& ctr, float r) noexcept
					: _X(ctr.x())
					, _Y(ctr.y())
					, _Radius(r) {}

				template <class LinearAlgebra>
				inline constexpr void basic_circle<LinearAlgebra>::center(const typename LinearAlgebra::point_2d& ctr) noexcept {
					_X = ctr.x();
					_Y = ctr.y();
				}
				template <class LinearAlgebra>
				inline constexpr void basic_circle<LinearAlgebra>::radius(float r) noexcept {
					_Radius = r;
				}

				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_circle<LinearAlgebra>::center() const noexcept {
					return typename LinearAlgebra::point_2d(_X, _Y);
				}
				template <class LinearAlgebra>
				inline constexpr float basic_circle<LinearAlgebra>::radius() const noexcept {
					return _Radius;
				}

				template <class LinearAlgebra>
				inline constexpr bool operator==(const basic_circle<LinearAlgebra>& lhs, const basic_circle<LinearAlgebra>& rhs) noexcept {
					return lhs._X == rhs._X && lhs._Y == rhs._Y && lhs._Radius == rhs._Radius;
				}
				template <class LinearAlgebra>
				inline constexpr bool operator!=(const basic_circle<LinearAlgebra>& lhs, const basic_circle<LinearAlgebra>& rhs) noexcept {
					return !(lhs == rhs);
				}

				// Paths

				//template <class LinearAlgebra, class T, class U>
				//inline constexpr basic_figure_items<LinearAlgebra<T, U>>::abs_new_figure::abs_new_figure() noexcept {

				//}
				template<class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::abs_new_figure::abs_new_figure() noexcept
					: _Data() { }

				template<class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::abs_new_figure::abs_new_figure(const typename LinearAlgebra::point_2d& pt) noexcept
					: _Data(pt) {
				}
				template<class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::abs_new_figure::at(const typename LinearAlgebra::point_2d& pt) noexcept {
					_Data = pt;
				}
				template<class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::abs_new_figure::at() const noexcept {
					return _Data;
				}
				template<class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_figure_items<LinearAlgebra>::abs_new_figure& lhs, const typename basic_figure_items<LinearAlgebra>::abs_new_figure& rhs) noexcept {
					return lhs._Data == rhs._Data;
				}
				template<class LinearAlgebra>
				inline constexpr bool operator!=(const typename basic_figure_items<LinearAlgebra>::abs_new_figure& lhs, const typename basic_figure_items<LinearAlgebra>::abs_new_figure& rhs) noexcept {
					return !(lhs == rhs);
				}

				template<class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::rel_new_figure::rel_new_figure() noexcept {}

				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::rel_new_figure::rel_new_figure(const typename LinearAlgebra::point_2d& pt) noexcept
					: _Data(pt) {}

				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::rel_new_figure::at(const typename LinearAlgebra::point_2d& pt) noexcept {
					_Data = pt;
				}

				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::rel_new_figure::at() const noexcept {
					return _Data;
				}

				template <class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_figure_items<LinearAlgebra>::rel_new_figure& lhs, const typename basic_figure_items<LinearAlgebra>::rel_new_figure& rhs) noexcept {
					return lhs._Data == rhs._Data;
				}

				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::close_figure::close_figure() noexcept {}

				template <class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_figure_items<LinearAlgebra>::close_figure&, const typename basic_figure_items<LinearAlgebra>::close_figure&) noexcept {
					return true;
				}

				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::abs_matrix::abs_matrix(const typename LinearAlgebra::matrix_2d& m) noexcept
					: _Matrix(m) {
				}
				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::abs_matrix::abs_matrix() noexcept {}

				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::abs_matrix::matrix(const typename LinearAlgebra::matrix_2d& value) noexcept {
					_Matrix = value;
				}
				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::matrix_2d basic_figure_items<LinearAlgebra>::abs_matrix::matrix() const noexcept {
					return _Matrix;
				}

				template <class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_figure_items<LinearAlgebra>::abs_matrix& lhs, const typename basic_figure_items<LinearAlgebra>::abs_matrix& rhs) noexcept {
					return lhs._Matrix == rhs._Matrix;
				}

				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::rel_matrix::rel_matrix(const typename LinearAlgebra::matrix_2d& m) noexcept
					: _Matrix(m) {
				}
				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::rel_matrix::rel_matrix() noexcept {}

				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::rel_matrix::matrix(const typename LinearAlgebra::matrix_2d& value) noexcept {
					_Matrix = value;
				}
				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::matrix_2d basic_figure_items<LinearAlgebra>::rel_matrix::matrix() const noexcept {
					return _Matrix;
				}

				template <class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_figure_items<LinearAlgebra>::rel_matrix& lhs, const typename basic_figure_items<LinearAlgebra>::rel_matrix& rhs) noexcept {
					return lhs._Matrix == rhs._Matrix;
				}

				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::revert_matrix::revert_matrix() noexcept {}

				template <class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_figure_items<LinearAlgebra>::revert_matrix&, const typename basic_figure_items<LinearAlgebra>::revert_matrix&) noexcept {
					return true;
				}

				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::abs_line::abs_line(const typename LinearAlgebra::point_2d& to) noexcept
					: _Data(to) {
				}
				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::abs_line::abs_line() noexcept {}

				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::abs_line::to(const typename LinearAlgebra::point_2d& value) noexcept {
					_Data = value;
				}

				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::abs_line::to() const noexcept {
					return _Data;
				}

				template <class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_figure_items<LinearAlgebra>::abs_line& lhs, const typename basic_figure_items<LinearAlgebra>::abs_line& rhs) noexcept {
					return lhs._Data == rhs._Data;
				}

				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::rel_line::rel_line(const typename LinearAlgebra::point_2d& to) noexcept
					: _Data(to) {
				}
				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::rel_line::rel_line() noexcept {}

				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::rel_line::to(const typename LinearAlgebra::point_2d& value) noexcept {
					_Data = value;
				}

				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::rel_line::to() const noexcept {
					return _Data;
				}

				template <class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_figure_items<LinearAlgebra>::rel_line& lhs, const typename basic_figure_items<LinearAlgebra>::rel_line& rhs) noexcept {
					return lhs._Data == rhs._Data;
				}

				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::abs_quadratic_curve::abs_quadratic_curve(const typename LinearAlgebra::point_2d& cp, const typename LinearAlgebra::point_2d& ep) noexcept
					: _Control_pt(cp)
					, _End_pt(ep) {
				}
				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::abs_quadratic_curve::abs_quadratic_curve() noexcept {}

				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::abs_quadratic_curve::control_pt(const typename LinearAlgebra::point_2d& value) noexcept {
					_Control_pt = value;
				}
				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::abs_quadratic_curve::end_pt(const typename LinearAlgebra::point_2d& value) noexcept {
					_End_pt = value;
				}

				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::abs_quadratic_curve::control_pt() const noexcept {
					return _Control_pt;
				}
				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::abs_quadratic_curve::end_pt() const noexcept {
					return _End_pt;
				}

				template <class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_figure_items<LinearAlgebra>::abs_quadratic_curve& lhs, const typename basic_figure_items<LinearAlgebra>::abs_quadratic_curve& rhs) noexcept {
					return (lhs._Control_pt == rhs._Control_pt) &&
						(lhs._End_pt == rhs._End_pt);
				}

				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::rel_quadratic_curve::rel_quadratic_curve(const typename LinearAlgebra::point_2d& cp, const typename LinearAlgebra::point_2d& ep) noexcept
					: _Control_pt(cp)
					, _End_pt(ep) {
				}
				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::rel_quadratic_curve::rel_quadratic_curve() noexcept {}

				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::rel_quadratic_curve::control_pt(const typename LinearAlgebra::point_2d& value) noexcept {
					_Control_pt = value;
				}
				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::rel_quadratic_curve::end_pt(const typename LinearAlgebra::point_2d& value) noexcept {
					_End_pt = value;
				}

				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::rel_quadratic_curve::control_pt() const noexcept {
					return _Control_pt;
				}
				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::rel_quadratic_curve::end_pt() const noexcept {
					return _End_pt;
				}

				template <class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_figure_items<LinearAlgebra>::rel_quadratic_curve& lhs, const typename basic_figure_items<LinearAlgebra>::rel_quadratic_curve& rhs) noexcept {
					return (lhs._Control_pt == rhs._Control_pt) &&
						(lhs._End_pt == rhs._End_pt);
				}

				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::abs_cubic_curve::abs_cubic_curve(const typename LinearAlgebra::point_2d& controlPoint1, const typename LinearAlgebra::point_2d& controlPoint2, const typename LinearAlgebra::point_2d& endPoint) noexcept
					: _Control_pt1(controlPoint1)
					, _Control_pt2(controlPoint2)
					, _End_pt(endPoint) {
				}
				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::abs_cubic_curve::abs_cubic_curve() noexcept {}

				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::abs_cubic_curve::control_pt1(const typename LinearAlgebra::point_2d& value) noexcept {
					_Control_pt1 = value;
				}
				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::abs_cubic_curve::control_pt2(const typename LinearAlgebra::point_2d& value) noexcept {
					_Control_pt2 = value;
				}
				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::abs_cubic_curve::end_pt(const typename LinearAlgebra::point_2d& value) noexcept {
					_End_pt = value;
				}

				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::abs_cubic_curve::control_pt1() const noexcept {
					return _Control_pt1;
				}
				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::abs_cubic_curve::control_pt2() const noexcept {
					return _Control_pt2;
				}
				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::abs_cubic_curve::end_pt() const noexcept {
					return _End_pt;
				}

				template <class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_figure_items<LinearAlgebra>::abs_cubic_curve& lhs, const typename basic_figure_items<LinearAlgebra>::abs_cubic_curve& rhs) noexcept {
					return (lhs._Control_pt1 == rhs._Control_pt1) &&
						(lhs._Control_pt2 == rhs._Control_pt2) &&
						(lhs._End_pt == rhs._End_pt);
				}

				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::rel_cubic_curve::rel_cubic_curve(const typename LinearAlgebra::point_2d& controlPoint1, const typename LinearAlgebra::point_2d& controlPoint2, const typename LinearAlgebra::point_2d& endPoint) noexcept
					: _Control_pt1(controlPoint1)
					, _Control_pt2(controlPoint2)
					, _End_pt(endPoint) {
				}
				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::rel_cubic_curve::rel_cubic_curve() noexcept {}

				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::rel_cubic_curve::control_pt1(const typename LinearAlgebra::point_2d& value) noexcept {
					_Control_pt1 = value;
				}
				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::rel_cubic_curve::control_pt2(const typename LinearAlgebra::point_2d& value) noexcept {
					_Control_pt2 = value;
				}
				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::rel_cubic_curve::end_pt(const typename LinearAlgebra::point_2d& value) noexcept {
					_End_pt = value;
				}

				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::rel_cubic_curve::control_pt1() const noexcept {
					return _Control_pt1;
				}
				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::rel_cubic_curve::control_pt2() const noexcept {
					return _Control_pt2;
				}
				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::rel_cubic_curve::end_pt() const noexcept {
					return _End_pt;
				}

				template <class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_figure_items<LinearAlgebra>::rel_cubic_curve& lhs, const typename basic_figure_items<LinearAlgebra>::rel_cubic_curve& rhs) noexcept {
					return (lhs._Control_pt1 == rhs._Control_pt1) &&
						(lhs._Control_pt2 == rhs._Control_pt2) &&
						(lhs._End_pt == rhs._End_pt);
				}

				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::arc::arc() noexcept
					: arc(typename LinearAlgebra::point_2d{ 10.0F, 10.0F }, pi<float>, pi<float>) { }
				template <class LinearAlgebra>
				inline constexpr basic_figure_items<LinearAlgebra>::arc::arc(const typename LinearAlgebra::point_2d& rad, float rot, float sang) noexcept
					: _Radius(rad)
					, _Rotation(rot)
					, _Start_angle(sang) {
				}

				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::arc::radius(const typename LinearAlgebra::point_2d& rad) noexcept {
					_Radius = rad;
				}
				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::arc::rotation(float rot) noexcept {
					_Rotation = rot;
				}
				template <class LinearAlgebra>
				inline constexpr void basic_figure_items<LinearAlgebra>::arc::start_angle(float sang) noexcept {
					_Start_angle = sang;
				}

				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::arc::radius() const noexcept {
					return _Radius;
				}
				template <class LinearAlgebra>
				inline constexpr float basic_figure_items<LinearAlgebra>::arc::rotation() const noexcept {
					return _Rotation;
				}
				template <class LinearAlgebra>
				inline constexpr float basic_figure_items<LinearAlgebra>::arc::start_angle() const noexcept {
					return _Start_angle;
				}

				template <class LinearAlgebra>
				inline typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::arc::center(const typename LinearAlgebra::point_2d& cpt, const typename LinearAlgebra::matrix_2d& m) const noexcept {
					auto lmtx = m;
					lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
					auto centerOffset = point_for_angle<LinearAlgebra>(two_pi<float> -_Start_angle, _Radius);
					centerOffset.y(-centerOffset.y);
					return cpt - centerOffset * lmtx;
				}

				template <class LinearAlgebra>
				inline typename LinearAlgebra::point_2d basic_figure_items<LinearAlgebra>::arc::end_pt(const typename LinearAlgebra::point_2d& cpt, const typename LinearAlgebra::matrix_2d& m) const noexcept {
					auto lmtx = m;
					auto tfrm = matrix_2d::init_rotate(_Start_angle + _Rotation);
					lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
					auto pt = (_Radius * tfrm);
					pt.y(-pt.y);
					return cpt + pt * lmtx;
				}

				template <class LinearAlgebra>
				inline constexpr bool operator==(const typename basic_figure_items<LinearAlgebra>::arc& lhs, const typename basic_figure_items<LinearAlgebra>::arc& rhs) noexcept {
					return (lhs._Radius == rhs._Radius) &&
						(lhs._Rotation == rhs._Rotation) &&
						(lhs._Start_angle == rhs._Start_angle);
				}

				template <class LinearAlgebra>
				inline constexpr bool operator!=(const typename basic_figure_items<LinearAlgebra>::arc& lhs, const typename basic_figure_items<LinearAlgebra>::arc& rhs) noexcept {
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

				template <class LinearAlgebra, class Allocator>
				::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item> _Interpret_path_items(const path_builder<LinearAlgebra, Allocator>&);

				template <class T>
				inline constexpr interpreted_path<T>::interpreted_path() noexcept
					: _Path_impl() {}

				template <class T>
				template <class LinearAlgebra, class Allocator>
				inline interpreted_path<T>::interpreted_path(const path_builder<LinearAlgebra, Allocator>& pf)
					: _Path_impl(pf)
				{}

				template <class T>
				template <class ForwardIterator>
				inline interpreted_path<T>::interpreted_path(ForwardIterator first, ForwardIterator last)
					: _Path_impl(first, last)
				{}

				template <class _TItem>
				struct _Path_item_interpret_visitor {
					constexpr static float twoThirds = 2.0F / 3.0F;

					template <class LinearAlgebra, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<LinearAlgebra>::abs_new_figure>, _Path_data_abs_new_figure> = _Path_data_abs_new_figure_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item>& v, typename LinearAlgebra::matrix_2d& m, typename LinearAlgebra::point_2d& currentPoint, typename LinearAlgebra::point_2d& closePoint, stack<typename LinearAlgebra::matrix_2d>&) noexcept {
						const auto pt = m.transform_pt({ 0.0F, 0.0F }) + item.at();
						v.emplace_back(::std::in_place_type<basic_figure_items<LinearAlgebra>::abs_new_figure>, pt);
						currentPoint = pt;
						closePoint = pt;
					}

					template <class LinearAlgebra, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<LinearAlgebra>::rel_new_figure>, _Path_data_rel_new_figure> = _Path_data_rel_new_figure_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item>& v, typename LinearAlgebra::matrix_2d& m, typename LinearAlgebra::point_2d& currentPoint, typename LinearAlgebra::point_2d& closePoint, stack<typename LinearAlgebra::matrix_2d>&) noexcept {
						auto amtx = m;
						amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
						const auto pt = currentPoint + item.at() * amtx;
						v.emplace_back(::std::in_place_type<basic_figure_items<LinearAlgebra>::abs_new_figure>, pt);
						currentPoint = pt;
						closePoint = pt;
					}

					template <class LinearAlgebra, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<LinearAlgebra>::close_figure>, _Path_data_close_path> = _Path_data_close_path_val>
					static void _Interpret(const T&, ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item>& v, typename LinearAlgebra::matrix_2d&, typename LinearAlgebra::point_2d& currentPoint, typename LinearAlgebra::point_2d& closePoint, stack<typename LinearAlgebra::matrix_2d>&) noexcept {
						const auto& item = v.rbegin();
						auto idx = item->index();
						if (idx == 0 || idx == 1) {
							return; // degenerate path
						}
						v.emplace_back(::std::in_place_type<basic_figure_items<LinearAlgebra>::close_figure>);
						v.emplace_back(::std::in_place_type<basic_figure_items<LinearAlgebra>::abs_new_figure>,
							closePoint);
						currentPoint = closePoint;
					}
					template <class LinearAlgebra, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<LinearAlgebra>::abs_matrix>, _Path_data_abs_matrix> = _Path_data_abs_matrix_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item>&, typename LinearAlgebra::matrix_2d& m, typename LinearAlgebra::point_2d&, typename LinearAlgebra::point_2d&, stack<typename LinearAlgebra::matrix_2d>& matrices) noexcept {
						matrices.push(m);
						m = item.matrix();
					}
					template <class LinearAlgebra, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<LinearAlgebra>::rel_matrix>, _Path_data_rel_matrix> = _Path_data_rel_matrix_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item>&, typename LinearAlgebra::matrix_2d& m, typename LinearAlgebra::point_2d&, typename LinearAlgebra::point_2d&, stack<typename LinearAlgebra::matrix_2d>& matrices) noexcept {
						const auto updateM = m * item.matrix();
						matrices.push(m);
						m = updateM;
					}
					template <class LinearAlgebra, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<LinearAlgebra>::revert_matrix>, _Path_data_revert_matrix> = _Path_data_revert_matrix_val>
					static void _Interpret(const T&, ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item>&, typename LinearAlgebra::matrix_2d& m, typename LinearAlgebra::point_2d&, typename LinearAlgebra::point_2d&, stack<typename LinearAlgebra::matrix_2d>& matrices) noexcept {
						if (matrices.empty()) {
							m = matrix_2d{};
						}
						else {
							m = matrices.top();
							matrices.pop();
						}
					}
					template <class LinearAlgebra, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<LinearAlgebra>::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item>& v, typename LinearAlgebra::matrix_2d& m, typename LinearAlgebra::point_2d& currentPoint, typename LinearAlgebra::point_2d&, stack<typename LinearAlgebra::matrix_2d>&) noexcept {
						const auto pt1 = m.transform_pt(item.control_pt1() - currentPoint) + currentPoint;
						const auto pt2 = m.transform_pt(item.control_pt2() - currentPoint) + currentPoint;
						const auto pt3 = m.transform_pt(item.end_pt() - currentPoint) + currentPoint;
						if (currentPoint == pt1 && pt1 == pt2 && pt2 == pt3) {
							return; // degenerate path segment
						}
						v.emplace_back(::std::in_place_type<basic_figure_items<LinearAlgebra>::abs_cubic_curve>, pt1,
							pt2, pt3);
						currentPoint = pt3;
					}
					template <class LinearAlgebra, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<LinearAlgebra>::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item>& v, typename LinearAlgebra::matrix_2d& m, typename LinearAlgebra::point_2d& currentPoint, typename LinearAlgebra::point_2d&, stack<typename LinearAlgebra::matrix_2d>&) noexcept {
						const auto pt = m.transform_pt(item.to() - currentPoint) + currentPoint;
						if (currentPoint == pt) {
							return; // degenerate path segment
						}
						v.emplace_back(::std::in_place_type<basic_figure_items<LinearAlgebra>::abs_line>, pt);
						currentPoint = pt;
					}
					template <class LinearAlgebra, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<LinearAlgebra>::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item>& v, typename LinearAlgebra::matrix_2d& m, typename LinearAlgebra::point_2d& currentPoint, typename LinearAlgebra::point_2d&, stack<typename LinearAlgebra::matrix_2d>&) noexcept {
						// Turn it into a cubic curve since cairo doesn't have quadratic curves.
						const auto controlPt = m.transform_pt(item.control_pt() - currentPoint) + currentPoint;
						const auto endPt = m.transform_pt(item.end_pt() - currentPoint) + currentPoint;
						if (currentPoint == controlPt && controlPt == endPt) {
							return; // degenerate path segment
						}
						const auto beginPt = currentPoint;
						LinearAlgebra::point_2d cpt1 = { ((controlPt.x - beginPt.x) * twoThirds) + beginPt.x, ((controlPt.y - beginPt.y) * twoThirds) + beginPt.y };
						LinearAlgebra::point_2d cpt2 = { ((controlPt.x - endPt.x) * twoThirds) + endPt.x, ((controlPt.y - endPt.y) * twoThirds) + endPt.y };
						v.emplace_back(::std::in_place_type<basic_figure_items<LinearAlgebra>::abs_cubic_curve>, cpt1, cpt2, endPt);
						currentPoint = endPt;
					}

					template <class LinearAlgebra, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<LinearAlgebra>::arc>, _Path_data_arc> = _Path_data_arc_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item>& v, typename LinearAlgebra::matrix_2d& m, typename LinearAlgebra::point_2d& currentPoint, typename LinearAlgebra::point_2d&, stack<typename LinearAlgebra::matrix_2d>&) noexcept {
						const float rot = item.rotation();
						const float oneThousandthOfADegreeInRads = pi<float> / 180'000.0F;
						if (abs(rot) < oneThousandthOfADegreeInRads) {
							// Return if the rotation is less than one thousandth of one degree; it's a degenerate path segment.
							return;
						}
						const auto clockwise = (rot < 0.0F) ? true : false;
						const LinearAlgebra::point_2d rad = item.radius();
						auto startAng = item.start_angle();
						const auto origM = m;
						m = matrix_2d::init_scale(rad);
						auto centerOffset = (point_for_angle(two_pi<float> -startAng) * rad);
						centerOffset.y = -centerOffset.y;
						auto ctr = currentPoint - centerOffset;

						LinearAlgebra::point_2d pt0, pt1, pt2, pt3;
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
						auto rotCntrCwFn = [](const typename LinearAlgebra::point_2d& pt, float a) -> typename LinearAlgebra::point_2d& {
							auto result = point_2d{ pt.x * cos(a) - pt.y * sin(a),
								pt.x * sin(a) + pt.y * cos(a) };
							result.x = _Round_floating_point_to_zero(result.x);
							result.y = _Round_floating_point_to_zero(result.y);
							return result;
						};
						auto rotCwFn = [](const typename LinearAlgebra::point_2d& pt, float a) -> typename LinearAlgebra::point_2d& {
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
						const typename LinearAlgebra::point_2d& tempCurrPt;
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
							v.emplace_back(::std::in_place_type<basic_figure_items<LinearAlgebra>::abs_cubic_curve>, cpt1, cpt2, cpt3);
							currTheta -= theta;
						}
						m = origM;
					}

					template <class LinearAlgebra, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<LinearAlgebra>::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item>& v, typename LinearAlgebra::matrix_2d& m, typename LinearAlgebra::point_2d& currentPoint, typename LinearAlgebra::point_2d&, stack<typename LinearAlgebra::matrix_2d>&) noexcept {
						auto amtx = m;
						amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
						const auto pt1 = item.control_pt1() * amtx;
						const auto pt2 = item.control_pt2() * amtx;
						const auto pt3 = item.end_pt()* amtx;
						if (currentPoint == pt1 && pt1 == pt2 && pt2 == pt3) {
							return; // degenerate path segment
						}
						v.emplace_back(::std::in_place_type<basic_figure_items<LinearAlgebra>::abs_cubic_curve>, currentPoint + pt1, currentPoint + pt1 + pt2, currentPoint + pt1 + pt2 + pt3);
						currentPoint = currentPoint + pt1 + pt2 + pt3;
					}

					template <class LinearAlgebra, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<LinearAlgebra>::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item>& v, typename LinearAlgebra::matrix_2d& m, typename LinearAlgebra::point_2d& currentPoint, typename LinearAlgebra::point_2d&, stack<typename LinearAlgebra::matrix_2d>&) noexcept {
						auto amtx = m;
						amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
						const auto pt = currentPoint + item.to() * amtx;
						if (currentPoint == pt) {
							return; // degenerate path segment
						}
						v.emplace_back(::std::in_place_type<basic_figure_items<LinearAlgebra>::abs_line>, pt);
						currentPoint = pt;
					}

					template <class LinearAlgebra, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<LinearAlgebra>::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
					static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item>& v, typename LinearAlgebra::matrix_2d& m, typename LinearAlgebra::point_2d& currentPoint, typename LinearAlgebra::point_2d&, stack<typename LinearAlgebra::matrix_2d>&) noexcept {
						auto amtx = m;
						amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
						const auto controlPt = currentPoint + item.control_pt() * amtx;
						const auto endPt = currentPoint + item.control_pt() * amtx + item.end_pt() * amtx;
						const auto beginPt = currentPoint;
						if (currentPoint == controlPt && controlPt == endPt) {
							return; // degenerate path segment
						}
						const typename LinearAlgebra::point_2d& cpt1 = { ((controlPt.x - beginPt.x) * twoThirds) + beginPt.x, ((controlPt.y - beginPt.y) * twoThirds) + beginPt.y };
						const typename LinearAlgebra::point_2d& cpt2 = { ((controlPt.x - endPt.x) * twoThirds) + endPt.x, ((controlPt.y - endPt.y) * twoThirds) + endPt.y };
						v.emplace_back(::std::in_place_type<basic_figure_items<LinearAlgebra>::abs_cubic_curve>, cpt1, cpt2, endPt);
						currentPoint = endPt;
					}
				};

				template <class LinearAlgebra, class ForwardIterator>
				inline ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item> _Interpret_path_items(ForwardIterator first, ForwardIterator last);

				template <class LinearAlgebra, class Allocator>
				inline ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item> _Interpret_path_items(const path_builder<LinearAlgebra, Allocator>& pf) {
					return _Interpret_path_items<LinearAlgebra>(begin(pf), end(pf));
				}

				template <class LinearAlgebra, class ForwardIterator>
				inline ::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item> _Interpret_path_items(ForwardIterator first, ForwardIterator last) {
					typename LinearAlgebra::matrix_2d m;
					typename LinearAlgebra::point_2d currentPoint; // Tracks the untransformed current point.
					typename LinearAlgebra::point_2d closePoint;   // Tracks the transformed close point.
					::std::stack<typename LinearAlgebra::matrix_2d> matrices;
					::std::vector<typename basic_figure_items<LinearAlgebra>::figure_item> v;

					for (auto val = first; val != last; val++) {
						::std::visit([&m, &currentPoint, &closePoint, &matrices, &v](auto&& item) {
							using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
							_Path_item_interpret_visitor<T>::template _Interpret<T>(item, v, m, currentPoint, closePoint, matrices);
						}, *val);
					}
					return v;
				}

				template <class LinearAlgebra, class Allocator>
				inline path_builder<LinearAlgebra, Allocator>::path_builder() noexcept(noexcept(Allocator())) :
					path_builder(Allocator()) { }

				template <class LinearAlgebra, class Allocator>
				inline path_builder<LinearAlgebra, Allocator>::path_builder(const Allocator &a) noexcept
					: _Data(a) {
				}

				template <class LinearAlgebra, class Allocator>
				inline path_builder<LinearAlgebra, Allocator>::path_builder(size_type n, const Allocator & a)
					: _Data(n, a) {
				}

				template <class LinearAlgebra, class Allocator>
				inline path_builder<LinearAlgebra, Allocator>::path_builder(size_type n, const value_type & value, const Allocator& a)
					: _Data(n, value, a) {
				}

				template <class LinearAlgebra, class Allocator>
				template<class InputIterator>
				inline path_builder<LinearAlgebra, Allocator>::path_builder(InputIterator first, InputIterator last, const Allocator& a)
					: _Data(first, last, a) {
				}

				template <class LinearAlgebra, class Allocator>
				inline path_builder<LinearAlgebra, Allocator>::~path_builder() { }

				template <class LinearAlgebra, class Allocator>
				template<class InputIterator>
				inline void path_builder<LinearAlgebra, Allocator>::assign(InputIterator first, InputIterator last) {
					_Data.assign(first, last);
				}

				template <class LinearAlgebra, class Allocator>
				template<class ...Args>
				inline typename path_builder<LinearAlgebra, Allocator>::reference path_builder<LinearAlgebra, Allocator>::emplace_back(Args && ...args) {
					return _Data.emplace_back(forward<Args>(args)...);
				}

				template <class LinearAlgebra, class Allocator>
				template<class ...Args>
				inline typename path_builder<LinearAlgebra, Allocator>::iterator path_builder<LinearAlgebra, Allocator>::emplace(const_iterator position, Args&& ...args) {
					return _Data.emplace(position, forward<Args>(args)...);
				}

				template <class LinearAlgebra, class Allocator>
				template<class InputIterator>
				inline typename path_builder<LinearAlgebra, Allocator>::iterator path_builder<LinearAlgebra, Allocator>::insert(const_iterator position, InputIterator first, InputIterator last) {
					return _Data.template insert<InputIterator>(position, first, last);
				}

				template <class LinearAlgebra, class Allocator>
				inline path_builder<LinearAlgebra, Allocator>::path_builder(const path_builder& pf)
					: _Data(pf._Data) {
				}

				template <class LinearAlgebra, class Allocator>
				inline path_builder<LinearAlgebra, Allocator>::path_builder(path_builder&& pf) noexcept
					: _Data(move(pf._Data)) {
				}

				template <class LinearAlgebra, class Allocator>
				inline path_builder<LinearAlgebra, Allocator>::path_builder(const path_builder& pf, const Allocator & a)
					: _Data(pf._Data, a) {
				}

				template <class LinearAlgebra, class Allocator>
				inline path_builder<LinearAlgebra, Allocator>::path_builder(path_builder&& pf, const Allocator & a)
					: _Data(move(pf._Data), a) {
				}

				template <class LinearAlgebra, class Allocator>
				inline path_builder<LinearAlgebra, Allocator>::path_builder(initializer_list<value_type> il, const Allocator & a)
					: _Data(il, a) {
				}

				template <class LinearAlgebra, class Allocator>
				inline path_builder<LinearAlgebra, Allocator>& path_builder<LinearAlgebra, Allocator>::operator=(const path_builder& x) {
					_Data = x._Data;
					return *this;
				}
				template <class LinearAlgebra, class Allocator>
				inline path_builder<LinearAlgebra, Allocator>& path_builder<LinearAlgebra, Allocator>::operator=(path_builder&& x) noexcept(allocator_traits<Allocator>::propagate_on_container_move_assignment::value || allocator_traits<Allocator>::is_always_equal::value) {
					::std::swap(_Data, x._Data);
					return *this;
				}
				template <class LinearAlgebra, class Allocator>
				inline path_builder<LinearAlgebra, Allocator>& path_builder<LinearAlgebra, Allocator>::operator=(initializer_list<value_type> il) {
					_Data.clear();
					for (const auto& item : il) {
						_Data.push_back(item);
					}
					return *this;
				}
				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::assign(size_type n, const value_type& u) {
					_Data.assign(n, u);
				}
				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::assign(initializer_list<value_type> il) {
					_Data.assign(il);
				}
				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::allocator_type path_builder<LinearAlgebra, Allocator>::get_allocator() const noexcept {
					return _Data.allocator_type();
				}
				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::iterator path_builder<LinearAlgebra, Allocator>::begin() noexcept {
					return _Data.begin();
				}
				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::const_iterator path_builder<LinearAlgebra, Allocator>::begin() const noexcept {
					return _Data.begin();
				}
				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::const_iterator path_builder<LinearAlgebra, Allocator>::cbegin() const noexcept {
					return _Data.cbegin();
				}
				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::iterator path_builder<LinearAlgebra, Allocator>::end() noexcept {
					return _Data.end();
				}
				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::const_iterator path_builder<LinearAlgebra, Allocator>::end() const noexcept {
					return _Data.end();
				}
				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::const_iterator path_builder<LinearAlgebra, Allocator>::cend() const noexcept {
					return _Data.cend();
				}
				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::reverse_iterator path_builder<LinearAlgebra, Allocator>::rbegin() noexcept {
					return _Data.rbegin();
				}
				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::const_reverse_iterator path_builder<LinearAlgebra, Allocator>::rbegin() const noexcept {
					return _Data.rbegin();
				}
				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::const_reverse_iterator path_builder<LinearAlgebra, Allocator>::crbegin() const noexcept {
					return _Data.crbegin();
				}
				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::reverse_iterator path_builder<LinearAlgebra, Allocator>::rend() noexcept {
					return _Data.rend();
				}
				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::const_reverse_iterator path_builder<LinearAlgebra, Allocator>::rend() const noexcept {
					return _Data.rend();
				}
				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::const_reverse_iterator path_builder<LinearAlgebra, Allocator>::crend() const noexcept {
					return _Data.crend();
				}

				template <class LinearAlgebra, class Allocator>
				inline bool path_builder<LinearAlgebra, Allocator>::empty() const noexcept {
					return _Data.empty();
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::size_type path_builder<LinearAlgebra, Allocator>::size() const noexcept {
					return _Data.size();
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::size_type path_builder<LinearAlgebra, Allocator>::max_size() const noexcept {
					return _Data.max_size();
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::size_type path_builder<LinearAlgebra, Allocator>::capacity() const noexcept {
					return _Data.capacity();
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::resize(size_type sz) {
					_Data.resize(sz);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::resize(size_type sz, const value_type& c) {
					_Data.resize(sz, c);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::reserve(size_type n) {
					_Data.reserve(n);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::shrink_to_fit() {
					_Data.shrink_to_fit();
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::reference path_builder<LinearAlgebra, Allocator>::operator[](size_type n) {
					return _Data[n];
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::const_reference path_builder<LinearAlgebra, Allocator>::operator[](size_type n) const {
					return _Data[n];
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::const_reference path_builder<LinearAlgebra, Allocator>::at(size_type n) const {
					return _Data.at(n);
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::reference path_builder<LinearAlgebra, Allocator>::at(size_type n) {
					return _Data.at(n);
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::reference path_builder<LinearAlgebra, Allocator>::front() {
					return _Data.front();
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::const_reference path_builder<LinearAlgebra, Allocator>::front() const {
					return _Data.front();
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::reference path_builder<LinearAlgebra, Allocator>::back() {
					return _Data.back();
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::const_reference path_builder<LinearAlgebra, Allocator>::back() const {
					return _Data.back();
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::new_figure(const typename LinearAlgebra::point_2d& v) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<LinearAlgebra>::abs_new_figure>, v);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::rel_new_figure(const typename LinearAlgebra::point_2d& v) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<LinearAlgebra>::rel_new_figure>, v);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::close_figure() noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<LinearAlgebra>::close_figure>);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::matrix(const typename LinearAlgebra::matrix_2d& m) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<LinearAlgebra>::abs_matrix>, m);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::rel_matrix(const typename LinearAlgebra::matrix_2d& m) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<LinearAlgebra>::rel_matrix>, m);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::revert_matrix() noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<LinearAlgebra>::revert_matrix>);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::arc(const typename LinearAlgebra::point_2d& rad, float rot, const float sang) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<LinearAlgebra>::arc>, rad, rot, sang);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::cubic_curve(const typename LinearAlgebra::point_2d& pt0, const typename LinearAlgebra::point_2d& pt1, const typename LinearAlgebra::point_2d& pt2) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<LinearAlgebra>::abs_cubic_curve>, pt0, pt1, pt2);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::line(const typename LinearAlgebra::point_2d& pt) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<LinearAlgebra>::abs_line>, pt);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::quadratic_curve(const typename LinearAlgebra::point_2d& pt0, const typename LinearAlgebra::point_2d& pt1) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<LinearAlgebra>::abs_quadratic_curve>, pt0, pt1);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::rel_cubic_curve(const typename LinearAlgebra::point_2d& dpt0, const typename LinearAlgebra::point_2d& dpt1, const typename LinearAlgebra::point_2d& dpt2) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<LinearAlgebra>::rel_cubic_curve>, dpt0, dpt1, dpt2);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::rel_line(const typename LinearAlgebra::point_2d& dpt) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<LinearAlgebra>::rel_line>, dpt);
				}

				template<class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::rel_quadratic_curve(const typename LinearAlgebra::point_2d& dpt0, const typename LinearAlgebra::point_2d& dpt1) noexcept {
					_Data.emplace_back(in_place_type<basic_figure_items<LinearAlgebra>::rel_quadratic_curve>, dpt0, dpt1);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::push_back(const value_type& x) {
					_Data.push_back(x);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::push_back(value_type&& x) {
					_Data.push_back(move(x));
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::pop_back() {
					_Data.pop_back();
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::iterator path_builder<LinearAlgebra, Allocator>::insert(const_iterator position, const value_type& x) {
					return _Data.insert(position, x);
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::iterator path_builder<LinearAlgebra, Allocator>::insert(const_iterator position, value_type&& x) {
					return _Data.insert(position, x);
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::iterator path_builder<LinearAlgebra, Allocator>::insert(const_iterator position, size_type n, const value_type& x) {
					return _Data.insert(position, n, x);
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::iterator path_builder<LinearAlgebra, Allocator>::insert(const_iterator position, initializer_list<value_type> il) {
					return _Data.insert(position, il);
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::iterator path_builder<LinearAlgebra, Allocator>::erase(const_iterator position) {
					return _Data.erase(position);
				}

				template <class LinearAlgebra, class Allocator>
				inline typename path_builder<LinearAlgebra, Allocator>::iterator path_builder<LinearAlgebra, Allocator>::erase(const_iterator first, const_iterator last) {
					return _Data.erase(first, last);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::swap(path_builder &pf) noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value || allocator_traits<Allocator>::is_always_equal::value) {
					::std::swap(_Data, pf._Data);
				}

				template <class LinearAlgebra, class Allocator>
				inline void path_builder<LinearAlgebra, Allocator>::clear() noexcept {
					_Data.clear();
				}

				/*        template <class LinearAlgebra, class Allocator>
						inline bool path_builder<LinearAlgebra, Allocator>::operator==(const path_builder& rhs) const noexcept {
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

				template <class LinearAlgebra, class T>
				template <class InputIterator>
				inline brush<LinearAlgebra, T>::brush(const circle<LinearAlgebra>& start, const circle<LinearAlgebra>& end, InputIterator first, InputIterator last)
					: _Brush_impl(start, end, first, last)
				{}

				template <class LinearAlgebra, class T>
				inline brush<LinearAlgebra, T>::brush(const rgba_color& color)
					: _Brush_impl(color)
				{}

				template<class LinearAlgebra, class T>
				template<class InputIterator>
				inline brush<LinearAlgebra, T>::brush(const typename LinearAlgebra::point_2d& begin, const typename LinearAlgebra::point_2d& end, InputIterator first, InputIterator last)
					: _Brush_impl(begin, end, first, last) {
				}
				template<class LinearAlgebra, class T>
				inline brush<LinearAlgebra, T>::brush(const typename LinearAlgebra::point_2d& begin, const typename LinearAlgebra::point_2d& end, ::std::initializer_list<gradient_stop> il)
					: _Brush_impl(begin, end, il)
				{}

				template <class LinearAlgebra, class T>
				inline brush<LinearAlgebra, T>::brush(const circle<LinearAlgebra>& start, const circle<LinearAlgebra>& end, ::std::initializer_list<gradient_stop> il)
					: _Brush_impl(start, end, il)
				{}

				template <class LinearAlgebra, class T>
				inline brush_type brush<LinearAlgebra, T>::type() const noexcept {
					return _Brush_impl.type();
				}

				// Surfaces
				template <class LinearAlgebra>
				inline constexpr render_props<LinearAlgebra>::render_props() noexcept {}

				template <class LinearAlgebra>
				inline constexpr render_props<LinearAlgebra>::render_props(antialias a, const typename LinearAlgebra::matrix_2d& m,
					compositing_op co) noexcept
					: _Antialiasing(a)
					, _Matrix(m)
					, _Compositing(co) {}

				template <class LinearAlgebra>
				inline constexpr void render_props<LinearAlgebra>::antialiasing(antialias a) noexcept {
					_Antialiasing = a;
				}

				template <class LinearAlgebra>
				inline constexpr void render_props<LinearAlgebra>::compositing(compositing_op co) noexcept {
					_Compositing = co;
				}

				template <class LinearAlgebra>
				inline constexpr void render_props<LinearAlgebra>::surface_matrix(const typename LinearAlgebra::matrix_2d& m) noexcept {
					_Matrix = m;
				}

				template <class LinearAlgebra>
				inline constexpr antialias render_props<LinearAlgebra>::antialiasing() const noexcept {
					return _Antialiasing;
				}

				template <class LinearAlgebra>
				inline constexpr compositing_op render_props<LinearAlgebra>::compositing() const noexcept {
					return _Compositing;
				}

				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::matrix_2d render_props<LinearAlgebra>::surface_matrix() const noexcept {
					return _Matrix;
				}

				template <class LinearAlgebra>
				constexpr brush_props<LinearAlgebra>::brush_props(experimental::io2d::wrap_mode w,
					experimental::io2d::filter fi,
					experimental::io2d::fill_rule fr,
					const typename LinearAlgebra::matrix_2d& m) noexcept
					: _Wrap_mode(w)
					, _Filter(fi)
					, _Fill_rule(fr)
					, _Matrix(m) {
				}

				template <class LinearAlgebra>
				inline constexpr void brush_props<LinearAlgebra>::filter(experimental::io2d::filter fi) noexcept {
					_Filter = fi;
				}

				template <class LinearAlgebra>
				inline constexpr void brush_props<LinearAlgebra>::wrap_mode(experimental::io2d::wrap_mode w) noexcept {
					_Wrap_mode = w;
				}

				template <class LinearAlgebra>
				inline constexpr void brush_props<LinearAlgebra>::fill_rule(experimental::io2d::fill_rule fr) noexcept {
					_Fill_rule = fr;
				}

				template <class LinearAlgebra>
				inline constexpr void brush_props<LinearAlgebra>::brush_matrix(const typename LinearAlgebra::matrix_2d& m) noexcept {
					_Matrix = m;
				}

				template <class LinearAlgebra>
				inline constexpr experimental::io2d::filter brush_props<LinearAlgebra>::filter() const noexcept {
					return _Filter;
				}

				template <class LinearAlgebra>
				inline constexpr experimental::io2d::wrap_mode brush_props<LinearAlgebra>::wrap_mode() const noexcept {
					return _Wrap_mode;
				}

				template <class LinearAlgebra>
				inline constexpr experimental::io2d::fill_rule brush_props<LinearAlgebra>::fill_rule() const noexcept {
					return _Fill_rule;
				}

				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::matrix_2d brush_props<LinearAlgebra>::brush_matrix() const noexcept {
					return _Matrix;
				}

				template <class T>
				template <class LinearAlgebra, class Allocator>
				inline clip_props<T>::clip_props(const path_builder<LinearAlgebra, Allocator> &pf,
					io2d::fill_rule fr)
					: _Clip(interpreted_path(pf))
					, _Fill_rule(fr) { }

				template <class T>
				inline clip_props<T>::clip_props(const interpreted_path<T>& pg,
					io2d::fill_rule fr) noexcept
					: _Clip(pg)
					, _Fill_rule(fr) { }

				template <class T>
				template <class LinearAlgebra>
				inline clip_props<T>::clip_props(const bounding_box<LinearAlgebra>& r,
					experimental::io2d::fill_rule fr)
					: _Clip()
					, _Fill_rule(fr) {
					path_builder<> clip;
					clip.new_figure(r.top_left());
					clip.rel_line({ r.width(), 0.0F });
					clip.rel_line({ 0.0F, r.height() });
					clip.rel_line({ -r.width(), 0.0F });
					clip.close_figure();
					_Clip = interpreted_path(clip);
				}

				template <class T>
				template <class LinearAlgebra, class Allocator>
				inline void clip_props<T>::clip(const path_builder<LinearAlgebra, Allocator>& pf) {
					_Clip = interpreted_path(pf);
				}

				template <class T>
				inline void clip_props<T>::clip(const interpreted_path<T>& pg) noexcept {
					_Clip = pg;
				}

				template <class T>
				inline void clip_props<T>::fill_rule(experimental::io2d::fill_rule fr) noexcept {
					_Fill_rule = fr;
				}

				template <class T>
				inline interpreted_path<T> clip_props<T>::clip() const noexcept {
					return _Clip;
				}

				template <class T>
				inline experimental::io2d::fill_rule clip_props<T>::fill_rule() const noexcept {
					return _Fill_rule;
				}

				inline constexpr stroke_props::stroke_props() noexcept {}
				inline constexpr stroke_props::stroke_props(float w,
					experimental::io2d::line_cap lc,
					experimental::io2d::line_join lj,
					float ml) noexcept
					: _Line_width(w)
					, _Miter_limit(ml)
					, _Line_cap(lc)
					, _Line_join(lj) {}

				inline constexpr void stroke_props::line_width(float w) noexcept {
					_Line_width = w;
				}
				inline constexpr void stroke_props::line_cap(experimental::io2d::line_cap lc) noexcept {
					_Line_cap = lc;
				}
				inline constexpr void stroke_props::line_join(experimental::io2d::line_join lj) noexcept {
					_Line_join = lj;
				}
				inline constexpr void stroke_props::miter_limit(float ml) noexcept {
					_Miter_limit = ml;
				}

				inline constexpr float stroke_props::line_width() const noexcept {
					return _Line_width;
				}
				inline constexpr experimental::io2d::line_cap stroke_props::line_cap() const noexcept {
					return _Line_cap;
				}
				inline constexpr experimental::io2d::line_join stroke_props::line_join() const noexcept {
					return _Line_join;
				}
				inline constexpr float stroke_props::miter_limit() const noexcept {
					return _Miter_limit;
				}

				template <class LinearAlgebra>
				inline constexpr mask_props<LinearAlgebra>::mask_props(experimental::io2d::wrap_mode w,
					experimental::io2d::filter fi,
					const typename LinearAlgebra::matrix_2d& m) noexcept
					: _Wrap_mode(w)
					, _Filter(fi)
					, _Matrix(m) {
				}

				template <class LinearAlgebra>
				inline constexpr void mask_props<LinearAlgebra>::wrap_mode(experimental::io2d::wrap_mode w) noexcept {
					_Wrap_mode = w;
				}
				template <class LinearAlgebra>
				inline constexpr void mask_props<LinearAlgebra>::filter(experimental::io2d::filter fi) noexcept {
					_Filter = fi;
				}
				template <class LinearAlgebra>
				inline constexpr void mask_props<LinearAlgebra>::mask_matrix(const typename LinearAlgebra::matrix_2d& m) noexcept {
					_Matrix = m;
				}

				template <class LinearAlgebra>
				inline constexpr experimental::io2d::wrap_mode mask_props<LinearAlgebra>::wrap_mode() const noexcept {
					return _Wrap_mode;
				}
				template <class LinearAlgebra>
				inline constexpr experimental::io2d::filter mask_props<LinearAlgebra>::filter() const noexcept {
					return _Filter;
				}
				template <class LinearAlgebra>
				inline constexpr typename LinearAlgebra::matrix_2d mask_props<LinearAlgebra>::mask_matrix() const noexcept {
					return _Matrix;
				}

				// handler

				template <class T>
				template <class LinearAlgebra, class U>
				handler<T>::handler(display_surface<LinearAlgebra, U>& ds, int preferredDisplayWidth, int preferredDisplayHeight, experimental::io2d::refresh_rate rr, float desiredFramerate)
					: _Handler_impl(ds, preferredDisplayWidth, preferredDisplayHeight, rr, desiredFramerate)
				{}

				template <class T>
				int handler<T>::begin_show()
				{
					return _Handler_impl.begin_show();
				}

				template <class T>
				void handler<T>::end_show()
				{
					_Handler_impl.end_show();
				}

				template <class T>
				inline void handler<T>::display_dimensions(display_point dp)
				{
					_Handler_impl.display_dimensions(dp);
				}

				template <class T>
				inline void handler<T>::display_dimensions(display_point dp, error_code& ec) noexcept
				{
					_Handler_impl.display_dimensions(dp, ec);
				}

				template <class T>
				inline void handler<T>::refresh_rate(experimental::io2d::refresh_rate rr) noexcept
				{
					_Handler_impl.refresh_rate(rr);
				}

				template <class T>
				inline bool handler<T>::desired_frame_rate(float fps) noexcept
				{
					return _Handler_impl.desired_frame_rate(fps);
				}

				template <class T>
				inline display_point handler<T>::display_dimensions() const noexcept
				{
					return _Handler_impl.display_dimensions();
				}

				template <class T>
				inline experimental::io2d::refresh_rate handler<T>::refresh_rate() const noexcept
				{
					return _Handler_impl.refresh_rate();
				}

				template <class T>
				inline float handler<T>::desired_frame_rate() const noexcept
				{
					return _Handler_impl.desired_frame_rate();
				}

				template <class T>
				inline float handler<T>::elapsed_draw_time() const noexcept
				{
					return _Handler_impl.elapsed_draw_time();
				}

				// surface

				template <class LinearAlgebra, class T>
				inline surface<LinearAlgebra, T>::surface(::std::experimental::io2d::format fmt, int width, int height)
					: _Surface_impl(make_unique<T::renderer_surface>(fmt, width, height)) {}

				template <class LinearAlgebra, class T>
				inline surface<LinearAlgebra, T>::surface(native_handle_type nh, ::std::experimental::io2d::format fmt)
					: _Surface_impl(make_unique<T::renderer_surface>(nh, fmt)) {}

				template <class LinearAlgebra, class T>
				inline void surface<LinearAlgebra, T>::clear()
				{
					_Surface_impl->clear();
				}

				template <class LinearAlgebra, class T>
				inline void surface<LinearAlgebra, T>::flush()
				{
					_Surface_impl->flush();
				}

				template <class LinearAlgebra, class T>
				inline void surface<LinearAlgebra, T>::flush(error_code& ec) noexcept
				{
					_Surface_impl->flush(ec);
				}

				template <class LinearAlgebra, class T>
				inline void surface<LinearAlgebra, T>::mark_dirty()
				{
					_Surface_impl->mark_dirty();
				}

				template <class LinearAlgebra, class T>
				inline void surface<LinearAlgebra, T>::mark_dirty(error_code& ec) noexcept
				{
					_Surface_impl->mark_dirty(ec);
				}

				template <class LinearAlgebra, class T>
				inline void surface<LinearAlgebra, T>::mark_dirty(const bounding_box<LinearAlgebra>& extents)
				{
					_Surface_impl->mark_dirty(extents);
				}

				template <class LinearAlgebra, class T>
				inline void surface<LinearAlgebra, T>::mark_dirty(const bounding_box<LinearAlgebra>& extents, error_code& ec) noexcept
				{
					_Surface_impl->mark_dirty(extents, ec);
				}

				template <class LinearAlgebra, class T>
				inline void surface<LinearAlgebra, T>::paint(const brush<LinearAlgebra, T>& b, const optional<brush_props<LinearAlgebra>>& bp, const optional<render_props<LinearAlgebra>>& rp, const optional<clip_props<T>>& cl)
				{
					_Surface_impl->paint(b.native_handle(), bp, rp, cl);
				}

				template <class LinearAlgebra, class T>
				template <class Allocator>
				inline void surface<LinearAlgebra, T>::stroke(const brush<LinearAlgebra, T>& b, const path_builder<LinearAlgebra, Allocator>& pb, const optional<brush_props<LinearAlgebra>>& bp, const optional<stroke_props>& sp, const optional<dashes>& d, const optional<render_props<LinearAlgebra>>& rp, const optional<clip_props<T>>& cl)
				{
					_Surface_impl->stroke(b.native_handle(), pb, bp, sp, d, rp, cl);
				}

				template <class LinearAlgebra, class T>
				inline void surface<LinearAlgebra, T>::stroke(const brush<LinearAlgebra, T>& b, const interpreted_path<T>& pg, const optional<brush_props<LinearAlgebra>>& bp, const optional<stroke_props>& sp, const optional<dashes>& d, const optional<render_props<LinearAlgebra>>& rp, const optional<clip_props<T>>& cl)
				{
					_Surface_impl->stroke(b.native_handle(), pg, bp, sp, d, rp, cl);
				}

				template <class LinearAlgebra, class T>
				template <class Allocator>
				inline void surface<LinearAlgebra, T>::fill(const brush<LinearAlgebra, T>& b, const path_builder<LinearAlgebra, Allocator>& pb, const optional<brush_props<LinearAlgebra>>& bp, const optional<render_props<LinearAlgebra>>& rp, const optional<clip_props<T>>& cl)
				{
					_Surface_impl->fill(b.native_handle(), pb, bp, rp, cl);
				}

				template <class LinearAlgebra, class T>
				inline void surface<LinearAlgebra, T>::fill(const brush<LinearAlgebra, T>& b, const interpreted_path<T>& pg, const optional<brush_props<LinearAlgebra>>& bp, const optional<render_props<LinearAlgebra>>& rp, const optional<clip_props<T>>& cl)
				{
					_Surface_impl->fill(b.native_handle(), pg, bp, rp, cl);
				}

				template <class LinearAlgebra, class T>
				inline void surface<LinearAlgebra, T>::mask(const brush<LinearAlgebra, T>& b, const brush<LinearAlgebra, T>& mb, const optional<brush_props<LinearAlgebra>>& bp, const optional<mask_props<LinearAlgebra>>& mp, const optional<render_props<LinearAlgebra>>& rp, const optional<clip_props<T>>& cl)
				{
					_Surface_impl->mask(b.native_handle(), mb.native_handle(), bp, mp, rp, cl);
				}

				// image_surface

				template <class LinearAlgebra, class T>
				inline image_surface<LinearAlgebra, T>::image_surface(io2d::format fmt, int width, int height)
					: surface<T>(fmt, width, height)
					, _Image_surface_impl(surface<LinearAlgebra, T>::_Surface_impl.get())
				{}

#ifdef _Filesystem_support_test
				template <class LinearAlgebra, class T>
				inline image_surface<LinearAlgebra, T>::image_surface(filesystem::path f, image_file_format i, io2d::format fmt)
					: surface<T>({ nullptr, nullptr }, fmt)
					, _Image_surface_impl(surface<LinearAlgebra, T>::_Surface_impl.get(), f, i, fmt)
				{}
#else
				template <class LinearAlgebra, class T>
				inline image_surface<LinearAlgebra, T>::image_surface(::std::string f, experimental::io2d::format fmt, image_file_format idf)
					: surface<T>({ nullptr, nullptr }, fmt)
					, _Image_surface_impl(surface<LinearAlgebra, T>::_Surface_impl.get(), f, i, fmt)
				{}
#endif

#ifdef _Filesystem_support_test
				template <class LinearAlgebra, class T>
				inline void image_surface<LinearAlgebra, T>::save(filesystem::path p, image_file_format i)
				{
					_Image_surface_impl.save(p, i);
				}
#else
				template <class LinearAlgebra, class T>
				inline void image_surface<LinearAlgebra, T>::save(::std::string f, image_file_format i);
				{
					_Image_surface_impl.save(f, i);
				}
#endif

				template <class LinearAlgebra, class T>
				inline void image_surface<LinearAlgebra, T>::map(const function<void(mapped_surface<LinearAlgebra, T>&)>& action)
				{
					_Image_surface_impl.map(action);
				}

				template <class LinearAlgebra, class T>
				inline int image_surface<LinearAlgebra, T>::max_width() noexcept
				{
					return T::renderer_image_surface::max_width();
				}

				template <class LinearAlgebra, class T>
				inline int image_surface<LinearAlgebra, T>::max_height() noexcept
				{
					return T::renderer_image_surface::max_height();
				}

				template <class LinearAlgebra, class T>
				inline io2d::format image_surface<LinearAlgebra, T>::format() const noexcept
				{
					return _Image_surface_impl.format();
				}

				template <class LinearAlgebra, class T>
				inline int image_surface<LinearAlgebra, T>::width() const noexcept
				{
					return _Image_surface_impl.width();
				}

				template <class LinearAlgebra, class T>
				inline int image_surface<LinearAlgebra, T>::height() const noexcept
				{
					return _Image_surface_impl.height();
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

				// display_surface

				template <class LinearAlgebra, class T>
				inline display_surface<LinearAlgebra, T>::display_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, io2d::scaling scl)
					: surface(preferredFormat, preferredWidth, preferredHeight)
					, _Display_surface_impl(_Surface_impl.get(), preferredWidth, preferredHeight, preferredFormat, scl)
				{}

				template <class LinearAlgebra, class T>
				inline display_surface<LinearAlgebra, T>::display_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, error_code& ec, io2d::scaling scl) noexcept
					: surface(preferredFormat, preferredWidth, preferredHeight)
					, _Display_surface_impl(_Surface_impl.get(), preferredWidth, preferredHeight, preferredFormat, ec, scl)
				{}

				template <class LinearAlgebra, class T>
				template <class U>
				inline void display_surface<LinearAlgebra, T>::make_native_surface(U&& context)
				{
					_Display_surface_impl.make_native_surface(context);
				}

				template <class LinearAlgebra, class T>
				inline void display_surface<LinearAlgebra, T>::make_impl_surface()
				{
					_Display_surface_impl.make_impl_surface();
				}

				template <class LinearAlgebra, class T>
				inline void display_surface<LinearAlgebra, T>::draw_callback(const function<void(display_surface<LinearAlgebra, T>& sfc)>& fn)
				{
					_Display_surface_impl.draw_callback(fn);
				}

				template <class LinearAlgebra, class T>
				inline void display_surface<LinearAlgebra, T>::invoke_draw_callback(display_point dp)
				{
					_Display_surface_impl.invoke_draw_callback(dp, *this);
				}

				template <class LinearAlgebra, class T>
				inline void display_surface<LinearAlgebra, T>::size_change_callback(const function<void(display_surface<LinearAlgebra, T>& sfc)>& fn)
				{
					_Display_surface_impl.size_change_callback(fn);
				}

				template <class LinearAlgebra, class T>
				inline void display_surface<LinearAlgebra, T>::invoke_size_change_callback()
				{
					_Display_surface_impl.invoke_size_change_callback(*this);
				}

				template <class LinearAlgebra, class T>
				inline void display_surface<LinearAlgebra, T>::dimensions(display_point dp)
				{
					_Display_surface_impl.dimensions(dp);
				}

				template <class LinearAlgebra, class T>
				inline void display_surface<LinearAlgebra, T>::dimensions(display_point dp, error_code& ec) noexcept
				{
					_Display_surface_impl.dimensions(dp, ec);
				}

				template <class LinearAlgebra, class T>
				inline void display_surface<LinearAlgebra, T>::scaling(experimental::io2d::scaling scl) noexcept
				{
					_Display_surface_impl.scaling(scl);
				}

				template <class LinearAlgebra, class T>
				inline void display_surface<LinearAlgebra, T>::user_scaling_callback(const function<experimental::io2d::bounding_box<LinearAlgebra>(const display_surface&, bool&)>& fn)
				{
					_Display_surface_impl.user_scaling_callback(fn);
				}

				template <class LinearAlgebra, class T>
				inline void display_surface<LinearAlgebra, T>::letterbox_brush(const optional<brush<LinearAlgebra, T>>& b, const optional<brush_props<LinearAlgebra>> bp) noexcept
				{
					_Display_surface_impl.letterbox_brush(b, bp);
				}

				template <class LinearAlgebra, class T>
				inline void display_surface<LinearAlgebra, T>::auto_clear(bool val) noexcept
				{
					_Display_surface_impl.auto_clear(val);
				}

				template <class LinearAlgebra, class T>
				inline void display_surface<LinearAlgebra, T>::redraw_required() noexcept
				{
					_Display_surface_impl.redraw_required();
				}

				template <class LinearAlgebra, class T>
				inline bool display_surface<LinearAlgebra, T>::reset_redraw_request() noexcept
				{
					return _Display_surface_impl.reset_redraw_request();
				}

				template <class LinearAlgebra, class T>
				inline experimental::io2d::format display_surface<LinearAlgebra, T>::format() const noexcept
				{
					return _Display_surface_impl.format();
				}

				template <class LinearAlgebra, class T>
				inline display_point display_surface<LinearAlgebra, T>::dimensions() const noexcept
				{
					return _Display_surface_impl.dimensions();
				}

				template <class LinearAlgebra, class T>
				inline experimental::io2d::scaling display_surface<LinearAlgebra, T>::scaling() const noexcept
				{
					return _Display_surface_impl.scaling();
				}

				template <class LinearAlgebra, class T>
				inline function<experimental::io2d::bounding_box<LinearAlgebra>(const display_surface<LinearAlgebra, T>&, bool&)> display_surface<LinearAlgebra, T>::user_scaling_callback() const
				{
					return _Display_surface_impl.user_scaling_callback();
				}

				template <class LinearAlgebra, class T>
				inline function<experimental::io2d::bounding_box<LinearAlgebra>(const display_surface<LinearAlgebra, T>&, bool&)> display_surface<LinearAlgebra, T>::user_scaling_callback(error_code& ec) const noexcept
				{
					return _Display_surface_impl.user_scaling_callback(ec);
				}

				template <class LinearAlgebra, class T>
				inline optional<brush<LinearAlgebra, T>> display_surface<LinearAlgebra, T>::letterbox_brush() const noexcept
				{
					return _Display_surface_impl.letterbox_brush();
				}

				template <class LinearAlgebra, class T>
				inline optional<brush_props<LinearAlgebra>> display_surface<LinearAlgebra, T>::letterbox_brush_props() const noexcept
				{
					return _Display_surface_impl.letterbox_brush_props();
				}

				template <class LinearAlgebra, class T>
				inline bool display_surface<LinearAlgebra, T>::auto_clear() const noexcept
				{
					return _Display_surface_impl.auto_clear();
				}

				// mapped_surface

				template <class LinearAlgebra, class T>
				inline mapped_surface<LinearAlgebra, T>::mapped_surface(typename surface<LinearAlgebra, T>::native_handle_type nh, typename surface<LinearAlgebra, T>::native_handle_type map_of)
					: _Mapped_surface_impl(nh, map_of)
				{}

				template <class LinearAlgebra, class T>
				inline mapped_surface<LinearAlgebra, T>::mapped_surface(typename surface<LinearAlgebra, T>::native_handle_type nh, typename surface<LinearAlgebra, T>::native_handle_type map_of, error_code& ec) noexcept
					: _Mapped_surface_impl(nh, map_of, ec)
				{}

				template <class LinearAlgebra, class T>
				inline void mapped_surface<LinearAlgebra, T>::commit_changes() {
					_Mapped_surface_impl.commit_changes();
				}

				template <class LinearAlgebra, class T>
				inline void mapped_surface<LinearAlgebra, T>::commit_changes(::std::error_code& ec) noexcept {
					_Mapped_surface_impl.commit_changes(ec);
				}

				template <class LinearAlgebra, class T>
				inline unsigned char* mapped_surface<LinearAlgebra, T>::data() {
					return _Mapped_surface_impl.data();
				}

				template <class LinearAlgebra, class T>
				inline unsigned char* mapped_surface<LinearAlgebra, T>::data(error_code& ec) noexcept {
					return _Mapped_surface_impl.data(ec);
				}

				template <class LinearAlgebra, class T>
				inline const unsigned char* mapped_surface<LinearAlgebra, T>::data() const {
					return _Mapped_surface_impl.data();
				}

				template <class LinearAlgebra, class T>
				inline const unsigned char* mapped_surface<LinearAlgebra, T>::data(error_code& ec) const noexcept {
					return _Mapped_surface_impl.data(ec);
				}

				template <class LinearAlgebra, class T>
				inline ::std::experimental::io2d::format mapped_surface<LinearAlgebra, T>::format() const noexcept {
					return _Mapped_surface_impl.format();
				}

				template <class LinearAlgebra, class T>
				inline int mapped_surface<LinearAlgebra, T>::width() const noexcept {
					return _Mapped_surface_impl.width();
				}

				template <class LinearAlgebra, class T>
				inline int mapped_surface<LinearAlgebra, T>::height() const noexcept {
					return _Mapped_surface_impl.height();
				}

				template <class LinearAlgebra, class T>
				inline int mapped_surface<LinearAlgebra, T>::stride() const noexcept {
					return _Mapped_surface_impl.stride();
				}

				// Standalone functions

				template <class LinearAlgebra, class T>
				inline display_surface<LinearAlgebra, T> make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, scaling scl) {
					return { preferredWidth, preferredHeight, preferredFormat, scl };
				}

				template <class LinearAlgebra, class T, class U>
				inline handler<T> make_handler(display_surface<LinearAlgebra, U>& ds, int preferredDisplayWidth, int preferredDisplayHeight, refresh_rate rr, float desiredFramerate) {
					return { ds, preferredDisplayWidth, preferredDisplayHeight, rr, desiredFramerate };
				}

				template <class LinearAlgebra, class T>
				inline image_surface<LinearAlgebra, T> make_image_surface(format fmt, int width, int height) {
					return image_surface<T>(fmt, width, height);
				}

				template <class LinearAlgebra, class T>
				inline image_surface<LinearAlgebra, T> copy_image_surface(image_surface<LinearAlgebra, T>& sfc) noexcept {
					image_surface<LinearAlgebra, T> retval(sfc.format(), sfc.width(), sfc.height());
					retval.map([&sfc](mapped_surface<LinearAlgebra, T>& rvms) {
						sfc.map([&rvms](mapped_surface<LinearAlgebra, T>& sfcms) {
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