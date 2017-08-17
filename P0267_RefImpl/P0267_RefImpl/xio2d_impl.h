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

namespace std::experimental::io2d {
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

		template <class T, enable_if_t<is_arithmetic_v<T>, _To_radians_sfinae> = _To_radians_sfinae_val>
		constexpr float to_radians(T deg) noexcept {
			auto angle = static_cast<float>(deg) / 360.0F * two_pi<float>;
			float oneThousandthOfADegreeInRads = pi<float> / 180'000.0F;
			if (((angle > 0.0F) && (angle < oneThousandthOfADegreeInRads)) || ((angle < 0.0F) && (-angle < oneThousandthOfADegreeInRads))) {
				return (angle < 0.0F) ? -0.0F : 0.0F;
			}
			return angle;
		}

		template <class T, enable_if_t<is_arithmetic_v<T>, _To_degrees_sfinae> = _To_degrees_sfinae_val>
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
		inline ::std::experimental::io2d::point_2d _Rotate_point_absolute_angle(const ::std::experimental::io2d::point_2d& center, float radius, float angle, bool clockwise = true) {
			if (clockwise) {
				::std::experimental::io2d::point_2d pt{ radius * ::std::cos(angle), -(radius * -::std::sin(angle)) };
				pt.x = pt.x + center.x;
				pt.y = pt.y + center.y;
				return pt;
			}
			else {
				::std::experimental::io2d::point_2d pt{ radius * ::std::cos(angle), radius * -::std::sin(angle) };
				pt.x = pt.x + center.x;
				pt.y = pt.y + center.y;
				return pt;
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

		template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
		inline constexpr void r(T val) noexcept {
			_R = val * _A;
		}

		template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating> = _Color_is_floating_val>
		inline constexpr void r(U val) noexcept {
			_R = val * _A;
		}

		template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
		inline constexpr void g(T val) noexcept {
			_G = val * _A;
		}

		template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating> = _Color_is_floating_val>
		inline constexpr void g(U val) noexcept {
			_G = val * _A;
		}

		template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
		inline constexpr void b(T val) noexcept {
			_B = val * _A;
		}

		template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating> = _Color_is_floating_val>
		inline constexpr void b(U val) noexcept {
			_B = val * _A;
		}

		template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral> = _Color_is_integral_val>
		inline constexpr void a(T val) noexcept {
			_A = val;
		}

		template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating> = _Color_is_floating_val>
		inline constexpr void a(U val) noexcept {
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

		inline constexpr point_2d::point_2d() noexcept
			: point_2d(0.0f, 0.0f) {}
		inline constexpr point_2d::point_2d(float xval, float yval) noexcept
			: x(xval)
			, y(yval) {
		}

		inline float point_2d::magnitude() const noexcept {
			return sqrt(x * x + y * y);
		}
		inline constexpr float point_2d::magnitude_squared() const noexcept {
			return x * x + y * y;
		}
		inline constexpr float point_2d::dot(const point_2d& other) const noexcept {
			return x * other.x + y * other.y;
		}

/*		inline float point_2d::angular_direction() const noexcept {
			auto v = atan2(y, x);
			if (v < 0.0F) {
				v += two_pi<float>;
			}
			return v;
		}*/

        inline constexpr point_2d point_2d::zero() noexcept {
            return { 0.0f, 0.0f };
        }

		inline point_2d point_2d::to_unit() const noexcept {
			auto leng = magnitude();

			return point_2d{ x / leng, y / leng };
		}

		inline constexpr bool operator==(const point_2d& lhs, const point_2d& rhs) noexcept {
			return lhs.x == rhs.x && lhs.y == rhs.y;
		}

		inline constexpr bool operator!=(const point_2d& lhs, const point_2d& rhs) noexcept {
			return !(lhs == rhs);
		}

		inline constexpr point_2d operator+(const point_2d& lhs) noexcept {
			return lhs;
		}

		inline constexpr point_2d operator+(const point_2d& lhs, const point_2d& rhs) noexcept {
			return point_2d{ lhs.x + rhs.x, lhs.y + rhs.y };
		}

		inline constexpr point_2d& point_2d::operator+=(const point_2d& rhs) noexcept {
			x = x + rhs.x;
			y = y + rhs.y;
			return *this;
		}

		inline constexpr point_2d operator-(const point_2d& lhs) noexcept {
			return point_2d{ -lhs.x, -lhs.y };
		}

		inline constexpr point_2d operator-(const point_2d& lhs, const point_2d& rhs) noexcept {
			return point_2d{ lhs.x - rhs.x, lhs.y - rhs.y };
		}

		inline constexpr point_2d& point_2d::operator-=(const point_2d& rhs) noexcept {
			x = x - rhs.x;
			y = y - rhs.y;
			return *this;
		}

		inline constexpr point_2d& point_2d::operator*=(float rhs) noexcept {
			x *= rhs;
			y *= rhs;
			return *this;
		}

		inline constexpr point_2d& point_2d::operator*=(const point_2d& rhs) noexcept {
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}

		inline constexpr point_2d operator*(const point_2d& lhs, float rhs) noexcept {
			return point_2d{ lhs.x * rhs, lhs.y * rhs };
		}

		inline constexpr point_2d operator*(float lhs, const point_2d& rhs) noexcept {
			return point_2d{ lhs * rhs.x, lhs * rhs.y };
		}

		inline constexpr point_2d operator*(const point_2d& lhs, const point_2d& rhs) noexcept {
			return point_2d{ lhs.x * rhs.x, lhs.y * rhs.y };
		}

		inline constexpr point_2d& point_2d::operator/=(float rhs) noexcept {
			x /= rhs;
			y /= rhs;
			return *this;
		}

		inline constexpr point_2d& point_2d::operator/=(const point_2d& rhs) noexcept {
			x /= rhs.x;
			y /= rhs.y;
			return *this;
		}

		inline constexpr point_2d operator/(const point_2d& lhs, float rhs) noexcept {
			return point_2d{ lhs.x / rhs, lhs.y / rhs };
		}

		inline constexpr point_2d operator/(float lhs, const point_2d& rhs) noexcept {
			return point_2d{ lhs / rhs.x, lhs / rhs.y };
		}

		inline constexpr point_2d operator/(const point_2d& lhs, const point_2d& rhs) noexcept {
			return point_2d{ lhs.x / rhs.x, lhs.y / rhs.y };
		}

        inline constexpr matrix_2d::matrix_2d() noexcept
            : matrix_2d(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f) {}
        
        inline constexpr matrix_2d::matrix_2d(float v00, float v01, float v10, float v11, float v20, float v21) noexcept
            : m00(v00)
            , m01(v01)
            , m02(0.0f)
            , m10(v10)
            , m11(v11)
            , m12(0.0f)
            , m20(v20)
            , m21(v21)
            , m22(1.0f) {
        }
        
        inline constexpr matrix_2d matrix_2d::init_translate(point_2d value) noexcept {
            return{ 1.0F, 0.0F, 0.0F, 1.0F, value.x, value.y };
        }
        inline constexpr matrix_2d matrix_2d::init_scale(point_2d value) noexcept {
            return{ value.x, 0.0F, 0.0F, value.y, 0.0F, 0.0F };
        }
        inline matrix_2d matrix_2d::init_rotate(float radians) noexcept {
            auto sine = sin(radians);
            auto cosine = cos(radians);
            sine = _Round_floating_point_to_zero(sine);
            cosine = _Round_floating_point_to_zero(cosine);
            return{ cosine, -sine, sine, cosine, 0.0F, 0.0F };
        }
        inline matrix_2d matrix_2d::init_reflect(float radians) noexcept {
            auto sine = sin(radians * 2.0F);
            auto cosine = cos(radians * 2.0F);
            sine = _Round_floating_point_to_zero(sine);
            cosine = _Round_floating_point_to_zero(cosine);
            return{ cosine, sine, sine, -cosine, 0.0F, 0.0F };
        }
        inline constexpr matrix_2d matrix_2d::init_shear_x(float factor) noexcept {
            return{ 1.0F, 0.0F, factor, 1.0F, 0.0F, 0.0F };
        }
        inline constexpr matrix_2d matrix_2d::init_shear_y(float factor) noexcept {
            return{ 1.0F, factor, 0.0F, 1.0F, 0.0F, 0.0F };
        }

        inline constexpr matrix_2d& matrix_2d::translate(point_2d value) noexcept {
			*this = *this * init_translate(value);
			return *this;
		}
		inline constexpr matrix_2d& matrix_2d::scale(point_2d value) noexcept {
			*this = *this * init_scale(value);
			return *this;
		}
		inline matrix_2d& matrix_2d::rotate(float radians) noexcept {
			*this = *this * init_rotate(radians);
			return *this;
		}
		inline matrix_2d& matrix_2d::reflect(float radians) noexcept {
			*this = *this * init_reflect(radians);
			return *this;
		}
		inline constexpr matrix_2d& matrix_2d::shear_x(float factor) noexcept {
			*this = *this * init_shear_x(factor);
			return *this;
		}
		inline constexpr matrix_2d& matrix_2d::shear_y(float factor) noexcept {
			*this = *this * init_shear_y(factor);
			return *this;
		}

		inline constexpr bool matrix_2d::is_invertible() const noexcept {
			return (m00 * m11 - m01 * m10) != 0.0F;
		}
		inline constexpr matrix_2d matrix_2d::inverse() const noexcept {
			const auto inverseDeterminant = 1.0F / determinant();
			return matrix_2d{
				(m11 * 1.0F - 0.0F * m21) * inverseDeterminant,
				-(m01 * 1.0F - 0.0F * m21) * inverseDeterminant,
				-(m10 * 1.0F - 0.0F * m20) * inverseDeterminant,
				(m00 * 1.0F - 0.0F * m20) * inverseDeterminant,
				(m10 * m21 - m11 * m20) * inverseDeterminant,
				-(m00 * m21 - m01 * m20) * inverseDeterminant
			};
		}
		inline constexpr bool _Is_finite_check(float val) noexcept {
			return val != numeric_limits<float>::infinity() &&
				val != -numeric_limits<float>::infinity() &&
				!(val != val); // This checks for both types of NaN. Compilers should not optimize this away but the only way to be sure is to check the documentation and any compiler switches you may be using.
		}
		inline constexpr bool matrix_2d::is_finite() const noexcept {
			static_assert(numeric_limits<float>::is_iec559 == true, "This implementation relies on IEEE 754 floating point behavior.");
			return numeric_limits<float>::is_iec559 &&
				_Is_finite_check(m00) &&
				_Is_finite_check(m01) &&
				_Is_finite_check(m10) &&
				_Is_finite_check(m11);
		}
		inline constexpr float matrix_2d::determinant() const noexcept {
			return m00 * m11 - m01 * m10;
		}
		inline constexpr point_2d matrix_2d::transform_pt(point_2d pt) const noexcept {
			auto result = point_2d{ m00 * pt.x + m10 * pt.y + m20, m01 * pt.x + m11 * pt.y + m21 };
			result.x = _Round_floating_point_to_zero(result.x);
			result.y = _Round_floating_point_to_zero(result.y);
			return result;
		}

		inline constexpr matrix_2d& matrix_2d::operator*=(const matrix_2d& rhs) noexcept {
			*this = (*this) * rhs;
			return *this;
		}

		inline constexpr matrix_2d operator*(const matrix_2d& lhs, const matrix_2d& rhs) noexcept {
			return matrix_2d{
				(lhs.m00 * rhs.m00) + (lhs.m01 * rhs.m10),
				(lhs.m00 * rhs.m01) + (lhs.m01 * rhs.m11),
				(lhs.m10 * rhs.m00) + (lhs.m11 * rhs.m10),
				(lhs.m10 * rhs.m01) + (lhs.m11 * rhs.m11),
				(lhs.m20 * rhs.m00) + (lhs.m21 * rhs.m10) + rhs.m20,
				(lhs.m20 * rhs.m01) + (lhs.m21 * rhs.m11) + rhs.m21
			};
		}
		inline constexpr bool operator==(const matrix_2d& lhs, const matrix_2d& rhs) noexcept {
			return lhs.m00 == rhs.m00 && lhs.m01 == rhs.m01 &&
				lhs.m10 == rhs.m10 && lhs.m11 == rhs.m11 &&
				lhs.m20 == rhs.m20 && lhs.m21 == rhs.m21;
		}
		inline constexpr bool operator!=(const matrix_2d& lhs, const matrix_2d& rhs) noexcept {
			return !(lhs == rhs);
		}

		inline constexpr point_2d operator*(point_2d pt, const matrix_2d& m) noexcept {
			return m.transform_pt(pt);
		}

		inline point_2d arc_start(point_2d ctr, float sang, point_2d rad, const matrix_2d& m) noexcept {
			auto lmtx = m;
			lmtx.m20 = 0.0F; lmtx.m21 = 0.0F; // Eliminate translation.
			auto pt = point_for_angle(sang, rad);
			return ctr + pt * lmtx;
		}

		inline point_2d arc_center(point_2d cpt, float sang, point_2d rad, const matrix_2d& m) noexcept {
			auto lmtx = m;
			lmtx.m20 = 0.0F; lmtx.m21 = 0.0F; // Eliminate translation.
			auto centerOffset = point_for_angle(two_pi<float> -sang, rad);
			centerOffset.y = -centerOffset.y;
			return cpt - centerOffset * lmtx;
		}

		inline point_2d arc_end(point_2d cpt, float eang, point_2d rad, const matrix_2d& m) noexcept {
			auto lmtx = m;
			auto tfrm = matrix_2d::init_rotate(eang);
			lmtx.m20 = 0.0F; lmtx.m21 = 0.0F; // Eliminate translation.
			auto pt = (rad * tfrm);
			pt.y = -pt.y;
			return cpt + pt * lmtx;
		}

        // Geometry

        inline constexpr bounding_box::bounding_box() noexcept { }
        inline constexpr bounding_box::bounding_box(float x, float y, float width, float height) noexcept
            : _X(x)
            , _Y(y)
            , _Width(width)
            , _Height(height) {
        }
        inline constexpr bounding_box::bounding_box(point_2d tl, point_2d br) noexcept
            : _X(tl.x)
            , _Y(tl.y)
            , _Width(::std::max(0.0F, br.x - tl.x))
            , _Height(::std::max(0.0F, br.y - tl.y)) {
        }

        inline constexpr void bounding_box::x(float value) noexcept {
            _X = value;
        }
        inline constexpr void bounding_box::y(float value) noexcept {
            _Y = value;
        }
        inline constexpr void bounding_box::width(float value) noexcept {
            _Width = value;
        }
        inline constexpr void bounding_box::height(float value) noexcept {
            _Height = value;
        }
        inline constexpr void bounding_box::top_left(point_2d value) noexcept {
            _X = value.x;
            _Y = value.y;
        }
        inline constexpr void bounding_box::bottom_right(point_2d value) noexcept {
            _Width = max(0.0F, value.x - _X);
            _Height = max(0.0F, value.y - _Y);
        }

        inline constexpr float bounding_box::x() const noexcept {
            return _X;
        }

        inline constexpr float bounding_box::y() const noexcept {
            return _Y;
        }

        inline constexpr float bounding_box::width() const noexcept {
            return _Width;
        }

        inline constexpr float bounding_box::height() const noexcept {
            return _Height;
        }

        inline constexpr point_2d bounding_box::top_left() const noexcept {
            return{ _X, _Y };
        }

        inline constexpr point_2d bounding_box::bottom_right() const noexcept {
            return{ _X + _Width, _Y + _Height };
        }

        inline constexpr bool operator==(const bounding_box& lhs, const bounding_box& rhs)
            noexcept {
            return lhs._X == rhs._X && lhs._Y == rhs._Y && lhs._Width == rhs._Width && lhs._Height == rhs._Height;
        }
        inline constexpr bool operator!=(const bounding_box& lhs, const bounding_box& rhs)
            noexcept {
            return !(lhs == rhs);
        }

        inline constexpr circle::circle() noexcept
            : _Center()
            , _Radius() {}
        inline constexpr circle::circle(point_2d ctr, float r) noexcept
            : _Center(ctr)
            , _Radius(r) {}

        inline constexpr void circle::center(point_2d ctr) noexcept {
            _Center = ctr;
        }
        inline constexpr void circle::radius(float r) noexcept {
            _Radius = r;
        }

        inline constexpr point_2d circle::center() const noexcept {
            return _Center;
        }
        inline constexpr float circle::radius() const noexcept {
            return _Radius;
        }

        inline constexpr bool circle::operator==(const circle& rhs) noexcept {
            return _Center == rhs._Center && _Radius == rhs._Radius;
        }
        inline constexpr bool circle::operator!=(const circle& rhs) noexcept {
            return !((*this) == rhs);
        }

        // Paths

        namespace figure_items {
            inline constexpr abs_new_figure::abs_new_figure() noexcept {}

            inline constexpr abs_new_figure::abs_new_figure(point_2d pt) noexcept
                : _Data(pt) {}

            inline constexpr void abs_new_figure::at(point_2d pt) noexcept {
                _Data = pt;
            }

            inline constexpr point_2d abs_new_figure::at() const noexcept {
                return _Data;
            }

            inline constexpr bool operator==(const abs_new_figure& lhs, const abs_new_figure& rhs) noexcept {
                return lhs._Data == rhs._Data;
            }

            inline constexpr rel_new_figure::rel_new_figure() noexcept {}

            inline constexpr rel_new_figure::rel_new_figure(point_2d pt) noexcept
                : _Data(pt) {}

            inline constexpr void rel_new_figure::at(point_2d pt) noexcept {
                _Data = pt;
            }

            inline constexpr point_2d rel_new_figure::at() const noexcept {
                return _Data;
            }

			inline constexpr bool operator==(const rel_new_figure& lhs, const rel_new_figure& rhs) noexcept {
                return lhs._Data == rhs._Data;
            }

            inline constexpr close_figure::close_figure() noexcept {}

            inline constexpr bool operator==(const close_figure&, const close_figure&) noexcept {
                return true;
            }

            inline constexpr abs_matrix::abs_matrix(const matrix_2d& m) noexcept
                : _Matrix(m) {
            }
            inline constexpr abs_matrix::abs_matrix() noexcept {}

            inline constexpr void abs_matrix::matrix(const matrix_2d& value) noexcept {
                _Matrix = value;
            }
            inline constexpr matrix_2d abs_matrix::matrix() const noexcept {
                return _Matrix;
            }

			inline constexpr bool operator==(const abs_matrix& lhs, const abs_matrix& rhs) noexcept {
                return lhs._Matrix == rhs._Matrix;
            }

            inline constexpr rel_matrix::rel_matrix(const matrix_2d& m) noexcept
                : _Matrix(m) {
            }
            inline constexpr rel_matrix::rel_matrix() noexcept {}

            inline constexpr void rel_matrix::matrix(const matrix_2d& value) noexcept {
                _Matrix = value;
            }
            inline constexpr matrix_2d rel_matrix::matrix() const noexcept {
                return _Matrix;
            }

			inline constexpr bool operator==(const rel_matrix& lhs, const rel_matrix& rhs) noexcept {
                return lhs._Matrix == rhs._Matrix;
            }

            inline constexpr revert_matrix::revert_matrix() noexcept {}

			inline constexpr bool operator==(const revert_matrix&, const revert_matrix&) noexcept {
                return true;
            }

            inline constexpr abs_line::abs_line(point_2d to) noexcept
                : _Data(to) {
            }
            inline constexpr abs_line::abs_line() noexcept {}

            inline constexpr void abs_line::to(point_2d value) noexcept {
                _Data = value;
            }

            inline constexpr point_2d abs_line::to() const noexcept {
                return _Data;
            }

			inline constexpr bool operator==(const abs_line& lhs, const abs_line& rhs) noexcept {
                return lhs._Data == rhs._Data;
            }

            inline constexpr rel_line::rel_line(point_2d to) noexcept
                : _Data(to) {
            }
            inline constexpr rel_line::rel_line() noexcept {}

            inline constexpr void rel_line::to(point_2d value) noexcept {
                _Data = value;
            }

            inline constexpr point_2d rel_line::to() const noexcept {
                return _Data;
            }

			inline constexpr bool operator==(const rel_line& lhs, const rel_line& rhs) noexcept {
                return lhs._Data == rhs._Data;
            }

            inline constexpr abs_quadratic_curve::abs_quadratic_curve(point_2d cp, point_2d ep) noexcept
                : _Control_pt(cp)
                , _End_pt(ep) {
            }
            inline constexpr abs_quadratic_curve::abs_quadratic_curve() noexcept {}

            inline constexpr void abs_quadratic_curve::control_pt(point_2d value) noexcept {
                _Control_pt = value;
            }
            inline constexpr void abs_quadratic_curve::end_pt(point_2d value) noexcept {
                _End_pt = value;
            }

            inline constexpr point_2d abs_quadratic_curve::control_pt() const noexcept {
                return _Control_pt;
            }
            inline constexpr point_2d abs_quadratic_curve::end_pt() const noexcept {
                return _End_pt;
            }

			inline constexpr bool operator==(const abs_quadratic_curve& lhs, const abs_quadratic_curve& rhs) noexcept {
                return (lhs._Control_pt == rhs._Control_pt) &&
                    (lhs._End_pt == rhs._End_pt);
            }

            inline constexpr rel_quadratic_curve::rel_quadratic_curve(point_2d cp, point_2d ep) noexcept
                : _Control_pt(cp)
                , _End_pt(ep) {
            }
            inline constexpr rel_quadratic_curve::rel_quadratic_curve() noexcept {}

            inline constexpr void rel_quadratic_curve::control_pt(point_2d value) noexcept {
                _Control_pt = value;
            }
            inline constexpr void rel_quadratic_curve::end_pt(point_2d value) noexcept {
                _End_pt = value;
            }

            inline constexpr point_2d rel_quadratic_curve::control_pt() const noexcept {
                return _Control_pt;
            }
            inline constexpr point_2d rel_quadratic_curve::end_pt() const noexcept {
                return _End_pt;
            }

			inline constexpr bool operator==(const rel_quadratic_curve& lhs, const rel_quadratic_curve& rhs) noexcept {
                return (lhs._Control_pt == rhs._Control_pt) &&
                    (lhs._End_pt == rhs._End_pt);
            }

            inline constexpr abs_cubic_curve::abs_cubic_curve(point_2d controlPoint1, point_2d controlPoint2, point_2d endPoint) noexcept
                : _Control_pt1(controlPoint1)
                , _Control_pt2(controlPoint2)
                , _End_pt(endPoint) {
            }
            inline constexpr abs_cubic_curve::abs_cubic_curve() noexcept {}

            inline constexpr void abs_cubic_curve::control_pt1(point_2d value) noexcept {
                _Control_pt1 = value;
            }
            inline constexpr void abs_cubic_curve::control_pt2(point_2d value) noexcept {
                _Control_pt2 = value;
            }
            inline constexpr void abs_cubic_curve::end_pt(point_2d value) noexcept {
                _End_pt = value;
            }

            inline constexpr point_2d abs_cubic_curve::control_pt1() const noexcept {
                return _Control_pt1;
            }
            inline constexpr point_2d abs_cubic_curve::control_pt2() const noexcept {
                return _Control_pt2;
            }
            inline constexpr point_2d abs_cubic_curve::end_pt() const noexcept {
                return _End_pt;
            }

			inline constexpr bool operator==(const abs_cubic_curve& lhs, const abs_cubic_curve& rhs) noexcept {
                return (lhs._Control_pt1 == rhs._Control_pt1) &&
                    (lhs._Control_pt2 == rhs._Control_pt2) &&
                    (lhs._End_pt == rhs._End_pt);
            }

            inline constexpr rel_cubic_curve::rel_cubic_curve(point_2d controlPoint1, point_2d controlPoint2, point_2d endPoint) noexcept
                : _Control_pt1(controlPoint1)
                , _Control_pt2(controlPoint2)
                , _End_pt(endPoint) {
            }
            inline constexpr rel_cubic_curve::rel_cubic_curve() noexcept {}

            inline constexpr void rel_cubic_curve::control_pt1(point_2d value) noexcept {
                _Control_pt1 = value;
            }
            inline constexpr void rel_cubic_curve::control_pt2(point_2d value) noexcept {
                _Control_pt2 = value;
            }
            inline constexpr void rel_cubic_curve::end_pt(point_2d value) noexcept {
                _End_pt = value;
            }

            inline constexpr point_2d rel_cubic_curve::control_pt1() const noexcept {
                return _Control_pt1;
            }
            inline constexpr point_2d rel_cubic_curve::control_pt2() const noexcept {
                return _Control_pt2;
            }
            inline constexpr point_2d rel_cubic_curve::end_pt() const noexcept {
                return _End_pt;
            }

			inline constexpr bool operator==(const rel_cubic_curve& lhs, const rel_cubic_curve& rhs) noexcept {
                return (lhs._Control_pt1 == rhs._Control_pt1) &&
                    (lhs._Control_pt2 == rhs._Control_pt2) &&
                    (lhs._End_pt == rhs._End_pt);
            }

            inline constexpr arc::arc() noexcept
                : arc(point_2d{ 10.0F, 10.0F }, pi<float>, pi<float>) { }
            inline constexpr arc::arc(point_2d rad, float rot, float sang) noexcept
                : _Radius(rad)
                , _Rotation(rot)
                , _Start_angle(sang) {
            }

            inline constexpr void arc::radius(point_2d rad) noexcept {
                _Radius = rad;
            }
            inline constexpr void arc::rotation(float rot) noexcept {
                _Rotation = rot;
            }
            inline constexpr void arc::start_angle(float sang) noexcept {
                _Start_angle = sang;
            }

            inline constexpr point_2d arc::radius() const noexcept {
                return _Radius;
            }
            inline constexpr float arc::rotation() const noexcept {
                return _Rotation;
            }
            inline constexpr float arc::start_angle() const noexcept {
                return _Start_angle;
            }

            inline point_2d arc::center(point_2d cpt, const matrix_2d& m) const noexcept {
                auto lmtx = m;
                lmtx.m20 = 0.0F; lmtx.m21 = 0.0F; // Eliminate translation.
                auto centerOffset = point_for_angle(two_pi<float> -_Start_angle, _Radius);
                centerOffset.y = -centerOffset.y;
                return cpt - centerOffset * lmtx;
            }

            inline point_2d arc::end_pt(point_2d cpt, const matrix_2d& m) const noexcept {
                auto lmtx = m;
                auto tfrm = matrix_2d::init_rotate(_Start_angle + _Rotation);
                lmtx.m20 = 0.0F; lmtx.m21 = 0.0F; // Eliminate translation.
                auto pt = (_Radius * tfrm);
                pt.y = -pt.y;
                return cpt + pt * lmtx;
            }

			inline constexpr bool operator==(const arc& lhs, const arc& rhs) noexcept {
                return (lhs._Radius == rhs._Radius) &&
                    (lhs._Rotation == rhs._Rotation) &&
                    (lhs._Start_angle == rhs._Start_angle);
            }

			inline constexpr bool operator!=(const arc& lhs, const arc& rhs) noexcept {
				return !(lhs == rhs);
			}
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

		template <class Allocator>
		::std::vector<figure_items::figure_item> _Interpret_path_items(const path_builder<Allocator>&);
		//template <class Allocator>
		//::std::vector<figure_items::path_data_types> _Interpret_path_items(const path_builder<Allocator>&, ::std::error_code&) noexcept;

		inline constexpr interpreted_path::interpreted_path() noexcept
			: _Impl() {}

		template <class Allocator>
		inline interpreted_path::interpreted_path(const path_builder<Allocator>& pf)
			: _Impl(pf)
		{}

		template <class ForwardIterator>
		inline interpreted_path::interpreted_path(ForwardIterator first, ForwardIterator last)
			: _Impl(first, last)
		{}

		template <class ForwardIterator>
		inline ::std::vector<figure_items::figure_item> _Interpret_path_items(ForwardIterator first, ForwardIterator last);

		template <class Allocator>
		inline ::std::vector<figure_items::figure_item> _Interpret_path_items(const path_builder<Allocator>& pf) {
			//matrix_2d m;
			//point_2d currentPoint; // Tracks the untransformed current point.
			//point_2d closePoint;   // Tracks the transformed close point.
			//::std::stack<matrix_2d> matrices;
			//::std::vector<figure_items::figure_item> v;

			//for (const figure_items::figure_item& val : pf) {
			//	::std::visit([&m, &currentPoint, &closePoint, &matrices, &v](auto&& item) {
			//		using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
			//		_Path_item_interpret_visitor<T>::template _Interpret<T>(item, v, m, currentPoint, closePoint, matrices);
			//	}, val);
			//}
			//return v;
			return _Interpret_path_items(begin(pf), end(pf));
		}

		template <class ForwardIterator>
		inline ::std::vector<figure_items::figure_item> _Interpret_path_items(ForwardIterator first, ForwardIterator last) {
			matrix_2d m;
			point_2d currentPoint; // Tracks the untransformed current point.
			point_2d closePoint;   // Tracks the transformed close point.
			::std::stack<matrix_2d> matrices;
			::std::vector<figure_items::figure_item> v;

			for (auto val = first; val != last; val++) {
				::std::visit([&m, &currentPoint, &closePoint, &matrices, &v](auto&& item) {
					using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
					_Path_item_interpret_visitor<T>::template _Interpret<T>(item, v, m, currentPoint, closePoint, matrices);
				}, *val);
			}
			return v;
		}

		template<class Allocator>
        inline path_builder<Allocator>::path_builder() noexcept(noexcept(Allocator())) :
            path_builder(Allocator()) { }
        
        template<class Allocator>
		inline path_builder<Allocator>::path_builder(const Allocator &a) noexcept
			: _Data(a) {
		}

		template<class Allocator>
		inline path_builder<Allocator>::path_builder(size_type n, const Allocator & a)
			: _Data(n, a) {
		}

		template<class Allocator>
		inline path_builder<Allocator>::path_builder(size_type n, const value_type & value, const Allocator& a)
			: _Data(n, value, a) {
		}

		template<class Allocator>
		template<class InputIterator>
		inline path_builder<Allocator>::path_builder(InputIterator first, InputIterator last, const Allocator& a)
			: _Data(first, last, a) {
		}

        template<class Allocator>
        inline path_builder<Allocator>::~path_builder() { }
        
        template<class Allocator>
		template<class InputIterator>
		inline void path_builder<Allocator>::assign(InputIterator first, InputIterator last) {
			_Data.assign(first, last);
		}

		template<class Allocator>
		template<class ...Args>
		inline typename path_builder<Allocator>::reference path_builder<Allocator>::emplace_back(Args && ...args) {
			return _Data.emplace_back(forward<Args>(args)...);
		}

		template<class Allocator>
		template<class ...Args>
		inline typename path_builder<Allocator>::iterator path_builder<Allocator>::emplace(const_iterator position, Args&& ...args) {
			return _Data.emplace(position, forward<Args>(args)...);
		}

		template<class Allocator>
		template<class InputIterator>
		inline typename path_builder<Allocator>::iterator path_builder<Allocator>::insert(const_iterator position, InputIterator first, InputIterator last) {
			return _Data.template insert<InputIterator>(position, first, last);
		}

		template<class Allocator>
		inline path_builder<Allocator>::path_builder(const path_builder& pf)
			: _Data(pf._Data) {
		}

		template<class Allocator>
		inline path_builder<Allocator>::path_builder(path_builder&& pf) noexcept
			: _Data(move(pf._Data)) {
		}

		template<class Allocator>
		inline path_builder<Allocator>::path_builder(const path_builder& pf, const Allocator & a)
			: _Data(pf._Data, a) {
		}

		template<class Allocator>
		inline path_builder<Allocator>::path_builder(path_builder&& pf, const Allocator & a)
			: _Data(move(pf._Data), a) {
		}

		template<class Allocator>
		inline path_builder<Allocator>::path_builder(initializer_list<value_type> il, const Allocator & a)
			: _Data(il, a) {
		}

		template <class Allocator>
		inline path_builder<Allocator>& path_builder<Allocator>::operator=(const path_builder& x) {
			_Data = x._Data;
			return *this;
		}
		template<class Allocator>
		inline path_builder<Allocator>& path_builder<Allocator>::operator=(path_builder&& x) noexcept(allocator_traits<Allocator>::propagate_on_container_move_assignment::value || allocator_traits<Allocator>::is_always_equal::value) {
			::std::swap(_Data, x._Data);
			return *this;
		}
		template<class Allocator>
		inline path_builder<Allocator>& path_builder<Allocator>::operator=(initializer_list<value_type> il) {
			_Data.clear();
			for (const auto& item : il) {
				_Data.push_back(item);
			}
			return *this;
		}
		template<class Allocator>
		inline void path_builder<Allocator>::assign(size_type n, const value_type& u) {
			_Data.assign(n, u);
		}
		template<class Allocator>
		inline void path_builder<Allocator>::assign(initializer_list<value_type> il) {
			_Data.assign(il);
		}
		template<class Allocator>
		inline typename path_builder<Allocator>::allocator_type path_builder<Allocator>::get_allocator() const noexcept {
			return _Data.allocator_type();
		}
		template<class Allocator>
		inline typename path_builder<Allocator>::iterator path_builder<Allocator>::begin() noexcept {
			return _Data.begin();
		}
		template<class Allocator>
		inline typename path_builder<Allocator>::const_iterator path_builder<Allocator>::begin() const noexcept {
			return _Data.begin();
		}
		template<class Allocator>
		inline typename path_builder<Allocator>::const_iterator path_builder<Allocator>::cbegin() const noexcept {
			return _Data.cbegin();
		}
		template<class Allocator>
		inline typename path_builder<Allocator>::iterator path_builder<Allocator>::end() noexcept {
			return _Data.end();
		}
		template<class Allocator>
		inline typename path_builder<Allocator>::const_iterator path_builder<Allocator>::end() const noexcept {
			return _Data.end();
		}
		template<class Allocator>
		inline typename path_builder<Allocator>::const_iterator path_builder<Allocator>::cend() const noexcept {
			return _Data.cend();
		}
		template<class Allocator>
		inline typename path_builder<Allocator>::reverse_iterator path_builder<Allocator>::rbegin() noexcept {
			return _Data.rbegin();
		}
		template<class Allocator>
		inline typename path_builder<Allocator>::const_reverse_iterator path_builder<Allocator>::rbegin() const noexcept {
			return _Data.rbegin();
		}
		template<class Allocator>
		inline typename path_builder<Allocator>::const_reverse_iterator path_builder<Allocator>::crbegin() const noexcept {
			return _Data.crbegin();
		}
		template<class Allocator>
		inline typename path_builder<Allocator>::reverse_iterator path_builder<Allocator>::rend() noexcept {
			return _Data.rend();
		}
		template<class Allocator>
		inline typename path_builder<Allocator>::const_reverse_iterator path_builder<Allocator>::rend() const noexcept {
			return _Data.rend();
		}
		template<class Allocator>
		inline typename path_builder<Allocator>::const_reverse_iterator path_builder<Allocator>::crend() const noexcept {
			return _Data.crend();
		}

		template<class Allocator>
		inline bool path_builder<Allocator>::empty() const noexcept {
			return _Data.empty();
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::size_type path_builder<Allocator>::size() const noexcept {
			return _Data.size();
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::size_type path_builder<Allocator>::max_size() const noexcept {
			return _Data.max_size();
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::size_type path_builder<Allocator>::capacity() const noexcept {
			return _Data.capacity();
		}

		template<class Allocator>
		inline void path_builder<Allocator>::resize(size_type sz) {
			_Data.resize(sz);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::resize(size_type sz, const value_type& c) {
			_Data.resize(sz, c);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::reserve(size_type n) {
			_Data.reserve(n);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::shrink_to_fit() {
			_Data.shrink_to_fit();
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::reference path_builder<Allocator>::operator[](size_type n) {
			return _Data[n];
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::const_reference path_builder<Allocator>::operator[](size_type n) const {
			return _Data[n];
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::const_reference path_builder<Allocator>::at(size_type n) const {
			return _Data.at(n);
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::reference path_builder<Allocator>::at(size_type n) {
			return _Data.at(n);
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::reference path_builder<Allocator>::front() {
			return _Data.front();
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::const_reference path_builder<Allocator>::front() const {
			return _Data.front();
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::reference path_builder<Allocator>::back() {
			return _Data.back();
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::const_reference path_builder<Allocator>::back() const {
			return _Data.back();
		}

		template<class Allocator>
		inline void path_builder<Allocator>::new_figure(point_2d v) noexcept {
			_Data.emplace_back(in_place_type<figure_items::abs_new_figure>, v);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::rel_new_figure(point_2d v) noexcept {
			_Data.emplace_back(in_place_type<figure_items::rel_new_figure>, v);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::close_figure() noexcept {
			_Data.emplace_back(in_place_type<figure_items::close_figure>);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::matrix(const matrix_2d& m) noexcept {
			_Data.emplace_back(in_place_type<figure_items::abs_matrix>, m);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::rel_matrix(const matrix_2d& m) noexcept {
			_Data.emplace_back(in_place_type<figure_items::rel_matrix>, m);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::revert_matrix() noexcept {
			_Data.emplace_back(in_place_type<figure_items::revert_matrix>);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::arc(point_2d rad, float rot, const float sang) noexcept {
			_Data.emplace_back(in_place_type<figure_items::arc>, rad, rot, sang);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::cubic_curve(point_2d pt0, point_2d pt1, point_2d pt2) noexcept {
			_Data.emplace_back(in_place_type<figure_items::abs_cubic_curve>, pt0, pt1, pt2);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::line(point_2d pt) noexcept {
			_Data.emplace_back(in_place_type<figure_items::abs_line>, pt);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::quadratic_curve(point_2d pt0, point_2d pt1) noexcept {
			_Data.emplace_back(in_place_type<figure_items::abs_quadratic_curve>, pt0, pt1);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::rel_cubic_curve(point_2d dpt0, point_2d dpt1, point_2d dpt2) noexcept {
			_Data.emplace_back(in_place_type<figure_items::rel_cubic_curve>, dpt0, dpt1, dpt2);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::rel_line(point_2d dpt) noexcept {
			_Data.emplace_back(in_place_type<figure_items::rel_line>, dpt);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::rel_quadratic_curve(point_2d dpt0, point_2d dpt1) noexcept {
			_Data.emplace_back(in_place_type<figure_items::rel_quadratic_curve>, dpt0, dpt1);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::push_back(const value_type& x) {
			_Data.push_back(x);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::push_back(value_type&& x) {
			_Data.push_back(move(x));
		}

		template<class Allocator>
		inline void path_builder<Allocator>::pop_back() {
			_Data.pop_back();
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::iterator path_builder<Allocator>::insert(const_iterator position, const value_type& x) {
			return _Data.insert(position, x);
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::iterator path_builder<Allocator>::insert(const_iterator position, value_type&& x) {
			return _Data.insert(position, x);
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::iterator path_builder<Allocator>::insert(const_iterator position, size_type n, const value_type& x) {
			return _Data.insert(position, n, x);
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::iterator path_builder<Allocator>::insert(const_iterator position, initializer_list<value_type> il) {
			return _Data.insert(position, il);
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::iterator path_builder<Allocator>::erase(const_iterator position) {
			return _Data.erase(position);
		}

		template<class Allocator>
		inline typename path_builder<Allocator>::iterator path_builder<Allocator>::erase(const_iterator first, const_iterator last) {
			return _Data.erase(first, last);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::swap(path_builder &pf) noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value || allocator_traits<Allocator>::is_always_equal::value) {
			::std::swap(_Data, pf._Data);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::clear() noexcept {
			_Data.clear();
		}

/*        template<class Allocator>
        inline bool path_builder<Allocator>::operator==(const path_builder& rhs) const noexcept {
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

		template <class InputIterator>
		inline brush::brush(const point_2d& begin, const point_2d& end, InputIterator first, InputIterator last)
			: _Impl(begin, end, first, last)
		{}

		template <class InputIterator>
		inline brush::brush(const circle& start, const circle& end, InputIterator first, InputIterator last)
			: _Impl(start, end, first, last)
		{}

		inline brush::brush(const rgba_color& color)
			: _Impl(color)
		{}

		inline brush::brush(const point_2d& begin, const point_2d& end, ::std::initializer_list<gradient_stop> il)
			: _Impl(begin, end, il)
		{}

		inline brush::brush(const circle& start, const circle& end, ::std::initializer_list<gradient_stop> il)
			: _Impl(start, end, il)
		{}

		inline brush::brush(image_surface&& img)
			: _Impl(std::move(img))
		{}

		inline brush_type brush::type() const noexcept {
			return _Impl.type();
		}

		// Surfaces

		inline constexpr render_props::render_props() noexcept {}

		inline constexpr render_props::render_props(antialias a, const matrix_2d& m,
			compositing_op co) noexcept
			: _Antialiasing(a)
			, _Matrix(m)
			, _Compositing(co) {}

		inline constexpr void render_props::antialiasing(antialias a) noexcept {
			_Antialiasing = a;
		}

		inline constexpr void render_props::compositing(compositing_op co) noexcept {
			_Compositing = co;
		}

		inline constexpr void render_props::surface_matrix(const matrix_2d& m) noexcept {
			_Matrix = m;
		}

		inline constexpr antialias render_props::antialiasing() const noexcept {
			return _Antialiasing;
		}

		inline constexpr compositing_op render_props::compositing() const noexcept {
			return _Compositing;
		}

		inline constexpr matrix_2d render_props::surface_matrix() const noexcept {
			return _Matrix;
		}

		constexpr brush_props::brush_props(experimental::io2d::wrap_mode w,
			experimental::io2d::filter fi,
			experimental::io2d::fill_rule fr,
			matrix_2d m) noexcept
			: _Wrap_mode(w)
			, _Filter(fi)
			, _Fill_rule(fr)
			, _Matrix(m) {
		}

		inline constexpr void brush_props::filter(experimental::io2d::filter fi) noexcept {
			_Filter = fi;
		}

		inline constexpr void brush_props::wrap_mode(experimental::io2d::wrap_mode w) noexcept {
			_Wrap_mode = w;
		}

		inline constexpr void brush_props::fill_rule(experimental::io2d::fill_rule fr) noexcept {
			_Fill_rule = fr;
		}

		inline constexpr void brush_props::brush_matrix(const matrix_2d& m) noexcept {
			_Matrix = m;
		}

		inline constexpr experimental::io2d::filter brush_props::filter() const noexcept {
			return _Filter;
		}

		inline constexpr experimental::io2d::wrap_mode brush_props::wrap_mode() const noexcept {
			return _Wrap_mode;
		}

		inline constexpr experimental::io2d::fill_rule brush_props::fill_rule() const noexcept {
			return _Fill_rule;
		}

		inline constexpr matrix_2d brush_props::brush_matrix() const noexcept {
			return _Matrix;
		}

		template <class Allocator>
		inline clip_props::clip_props(const path_builder<Allocator> &pf,
			experimental::io2d::fill_rule fr)
			: _Clip(interpreted_path(pf))
			, _Fill_rule(fr) { }

		inline clip_props::clip_props(const interpreted_path& pg,
			experimental::io2d::fill_rule fr) noexcept
			: _Clip(pg)
			, _Fill_rule(fr) { }

		inline clip_props::clip_props(const bounding_box& r,
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

		template <class Allocator>
		inline void clip_props::clip(const path_builder<Allocator>& pf) {
			_Clip = interpreted_path(pf);
		}

		inline void clip_props::clip(const interpreted_path& pg) noexcept {
			_Clip = pg;
		}

		inline void clip_props::fill_rule(experimental::io2d::fill_rule fr) noexcept{
			_Fill_rule = fr;
		}

		inline interpreted_path clip_props::clip() const noexcept {
			return _Clip;
		}

		inline experimental::io2d::fill_rule clip_props::fill_rule() const noexcept {
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

		inline constexpr mask_props::mask_props(experimental::io2d::wrap_mode w,
			experimental::io2d::filter fi,
			matrix_2d m) noexcept
			: _Wrap_mode(w)
			, _Filter(fi)
			, _Matrix(m) {
		}

		inline constexpr void mask_props::wrap_mode(experimental::io2d::wrap_mode w) noexcept {
			_Wrap_mode = w;
		}
		inline constexpr void mask_props::filter(experimental::io2d::filter fi) noexcept {
			_Filter = fi;
		}
		inline constexpr void mask_props::mask_matrix(const matrix_2d& m) noexcept {
			_Matrix = m;
		}

		inline constexpr experimental::io2d::wrap_mode mask_props::wrap_mode() const noexcept {
			return _Wrap_mode;
		}
		inline constexpr experimental::io2d::filter mask_props::filter() const noexcept {
			return _Filter;
		}
		inline constexpr matrix_2d mask_props::mask_matrix() const noexcept {
			return _Matrix;
		}

		// divergent from paper ?
		template <class Allocator>
		inline void surface::fill(const brush& b, const path_builder<Allocator>& pf, const optional<brush_props>& bp, const optional<render_props>& rp, const optional<clip_props>& cl) {
			interpreted_path pg(pf);
			fill(b, pg, bp, rp, cl);
		}

		template <class Allocator>
		inline void surface::stroke(const brush& b, const path_builder<Allocator>& pf, const optional<brush_props>& bp, const optional<stroke_props>& sp, const optional<dashes>& d, const optional<render_props>& rp, const optional<clip_props>& cl) {
			interpreted_path pg(pf);
			stroke(b, pg, bp, sp, d, rp, cl);
		}
	}
}
