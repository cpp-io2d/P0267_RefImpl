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
		// Throws an exception of type:
		// -  bad_alloc : If the value of s is CAIRO_STATUS_NO_MEMORY.
		// -  runtime_error : If s is any other value, excluding CAIRO_STATUS_SUCCESS.
		inline void _Throw_if_failed_cairo_status_t(::cairo_status_t s) {
			assert(s == CAIRO_STATUS_SUCCESS && "Unexpected cairo_status_t value.");
			if (s != CAIRO_STATUS_SUCCESS) {
				if (s == CAIRO_STATUS_NO_MEMORY) {
					throw ::std::bad_alloc{};
				}
				else {
					throw ::std::runtime_error("Unrecoverable error.");
				}
			}
		}

		// Converts 'value' to an int and returns it. If nearestNeighbor is true, the return value is the result of calling 'static_cast<int>(round(value))'; if false, the return value is the result of calling 'static_cast<int>(trunc(value))'.
		inline int _Double_to_int(float value, bool nearestNeighbor = true) {
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
        inline constexpr rgba_color::rgba_color(T r, T g, T b, T a)
            : _R(static_cast<float>(::std::min<float>(::std::max<float>((r / 255.0F), 0.0F), 1.0F)))
            , _G(static_cast<float>(::std::min<float>(::std::max<float>((g / 255.0F), 0.0F), 1.0F)))
            , _B(static_cast<float>(::std::min<float>(::std::max<float>((b / 255.0F), 0.0F), 1.0F)))
            , _A(static_cast<float>(::std::min<float>(::std::max<float>((a / 255.0F), 0.0F), 1.0F))) { }
        template <class T, ::std::enable_if_t<::std::is_floating_point_v<T>, _Color_is_floating>>
        inline constexpr rgba_color::rgba_color(T r, T g, T b, T a)
            : _R(static_cast<float>(::std::min<T>(::std::max<T>(static_cast<float>(r), 0.0F), 1.0F)))
            , _G(static_cast<float>(::std::min<T>(::std::max<T>(static_cast<float>(g), 0.0F), 1.0F)))
            , _B(static_cast<float>(::std::min<T>(::std::max<T>(static_cast<float>(b), 0.0F), 1.0F)))
            , _A(static_cast<float>(::std::min<T>(::std::max<T>(static_cast<float>(a), 0.0F), 1.0F))) {
        }

        inline constexpr void rgba_color::r(float val) noexcept {
            _R = val * _A;
        }
        inline constexpr void rgba_color::g(float val) noexcept {
            _G = val * _A;
        }
        inline constexpr void rgba_color::b(float val) noexcept {
            _B = val * _A;
        }
        inline constexpr void rgba_color::a(float val) noexcept {
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
        inline constexpr rgba_color& rgba_color::operator*=(T rhs) {
            r(::std::min(r() * rhs / 255.0F, 1.0F));
            g(::std::min(g() * rhs / 255.0F, 1.0F));
            b(::std::min(b() * rhs / 255.0F, 1.0F));
            a(::std::min(a() * rhs / 255.0F, 1.0F));
            return *this;
        }
        template <class U, ::std::enable_if_t<::std::is_floating_point_v<U>, _Color_is_floating>>
        inline constexpr rgba_color& rgba_color::operator*=(U rhs) {
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
        inline constexpr rgba_color operator*(const rgba_color& lhs, T rhs) {
            rhs = ::std::max(::std::min(rhs, 1.0F), 0.0F);
            return{
                ::std::min(lhs.r() * rhs, 1.0F),
                ::std::min(lhs.g() * rhs, 1.0F),
                ::std::min(lhs.b() * rhs, 1.0F),
                ::std::min(lhs.a() * rhs, 1.0F)
            };
        }

        template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral>>
        inline constexpr rgba_color operator*(const rgba_color& lhs, T rhs) {
            rhs = ::std::max(::std::min(rhs, 1.0F), 0.0F);
            return{
                ::std::min(lhs.r() * rhs / 255.0F, 1.0F),
                ::std::min(lhs.g() * rhs / 255.0F, 1.0F),
                ::std::min(lhs.b() * rhs / 255.0F, 1.0F),
                ::std::min(lhs.a() * rhs / 255.0F, 1.0F)
            };
        }

        template <class T, ::std::enable_if_t<::std::is_floating_point_v<T>, _Color_is_floating>>
        inline constexpr rgba_color operator*(T lhs, const rgba_color& rhs) {
            lhs = ::std::max(::std::min(lhs, 1.0F), 0.0F);
            return{
                ::std::min(lhs * rhs.r(), 1.0F),
                ::std::min(lhs * rhs.g(), 1.0F),
                ::std::min(lhs * rhs.b(), 1.0F),
                ::std::min(lhs * rhs.a(), 1.0F)
            };
        }

        template <class T, ::std::enable_if_t<::std::is_integral_v<T>, _Color_is_integral>>
        inline constexpr rgba_color operator*(T lhs, const rgba_color& rhs) {
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

		inline float point_2d::angular_direction() const noexcept {
			auto v = atan2(y, x);
			if (v < 0.0F) {
				v += two_pi<float>;
			}
			return v;
		}

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
        
        inline constexpr matrix_2d matrix_2d::init_translate(const point_2d& value) noexcept {
            return{ 1.0F, 0.0F, 0.0F, 1.0F, value.x, value.y };
        }
        inline constexpr matrix_2d matrix_2d::init_scale(const point_2d& value) noexcept {
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
        inline constexpr bounding_box::bounding_box(const point_2d& tl, const point_2d& br) noexcept
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
        inline constexpr void bounding_box::top_left(const point_2d& value) noexcept {
            _X = value.x;
            _Y = value.y;
        }
        inline constexpr void bounding_box::bottom_right(const point_2d& value) noexcept {
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

        inline constexpr float bounding_box::left() const noexcept {
            return _X;
        }

        inline constexpr float bounding_box::right() const noexcept {
            return _X + _Width;
        }

        inline constexpr float bounding_box::top() const noexcept {
            return _Y;
        }

        inline constexpr float bounding_box::bottom() const noexcept {
            return _Y + _Height;
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
        inline constexpr circle::circle(const point_2d& ctr, float r) noexcept
            : _Center(ctr)
            , _Radius(r) {}

        inline constexpr void circle::center(const point_2d& ctr) noexcept {
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

            inline constexpr abs_new_figure::abs_new_figure(const point_2d& pt) noexcept
                : _Data(pt) {}

            inline constexpr void abs_new_figure::at(const point_2d& pt) noexcept {
                _Data = pt;
            }

            inline constexpr point_2d abs_new_figure::at() const noexcept {
                return _Data;
            }

            inline constexpr bool operator==(const abs_new_figure& lhs, const abs_new_figure& rhs) noexcept {
                return lhs._Data == rhs._Data;
            }

            inline constexpr rel_new_figure::rel_new_figure() noexcept {}

            inline constexpr rel_new_figure::rel_new_figure(const point_2d& pt) noexcept
                : _Data(pt) {}

            inline constexpr void rel_new_figure::at(const point_2d& pt) noexcept {
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

            inline constexpr abs_line::abs_line(const point_2d& to) noexcept
                : _Data(to) {
            }
            inline constexpr abs_line::abs_line() noexcept {}

            inline constexpr void abs_line::to(const point_2d& value) noexcept {
                _Data = value;
            }

            inline constexpr point_2d abs_line::to() const noexcept {
                return _Data;
            }

			inline constexpr bool operator==(const abs_line& lhs, const abs_line& rhs) noexcept {
                return lhs._Data == rhs._Data;
            }

            inline constexpr rel_line::rel_line(const point_2d& to) noexcept
                : _Data(to) {
            }
            inline constexpr rel_line::rel_line() noexcept {}

            inline constexpr void rel_line::to(const point_2d& value) noexcept {
                _Data = value;
            }

            inline constexpr point_2d rel_line::to() const noexcept {
                return _Data;
            }

			inline constexpr bool operator==(const rel_line& lhs, const rel_line& rhs) noexcept {
                return lhs._Data == rhs._Data;
            }

            inline constexpr abs_quadratic_curve::abs_quadratic_curve(const point_2d& cp, const point_2d& ep) noexcept
                : _Control_pt(cp)
                , _End_pt(ep) {
            }
            inline constexpr abs_quadratic_curve::abs_quadratic_curve() noexcept {}

            inline constexpr void abs_quadratic_curve::control_point(const point_2d& value) noexcept {
                _Control_pt = value;
            }
            inline constexpr void abs_quadratic_curve::end_point(const point_2d& value) noexcept {
                _End_pt = value;
            }

            inline constexpr point_2d abs_quadratic_curve::control_point() const noexcept {
                return _Control_pt;
            }
            inline constexpr point_2d abs_quadratic_curve::end_point() const noexcept {
                return _End_pt;
            }

			inline constexpr bool operator==(const abs_quadratic_curve& lhs, const abs_quadratic_curve& rhs) noexcept {
                return (lhs._Control_pt == rhs._Control_pt) &&
                    (lhs._End_pt == rhs._End_pt);
            }

            inline constexpr rel_quadratic_curve::rel_quadratic_curve(const point_2d& cp, const point_2d& ep) noexcept
                : _Control_pt(cp)
                , _End_pt(ep) {
            }
            inline constexpr rel_quadratic_curve::rel_quadratic_curve() noexcept {}

            inline constexpr void rel_quadratic_curve::control_point(const point_2d& value) noexcept {
                _Control_pt = value;
            }
            inline constexpr void rel_quadratic_curve::end_point(const point_2d& value) noexcept {
                _End_pt = value;
            }

            inline constexpr point_2d rel_quadratic_curve::control_point() const noexcept {
                return _Control_pt;
            }
            inline constexpr point_2d rel_quadratic_curve::end_point() const noexcept {
                return _End_pt;
            }

			inline constexpr bool operator==(const rel_quadratic_curve& lhs, const rel_quadratic_curve& rhs) noexcept {
                return (lhs._Control_pt == rhs._Control_pt) &&
                    (lhs._End_pt == rhs._End_pt);
            }

            inline constexpr abs_cubic_curve::abs_cubic_curve(const point_2d& controlPoint1, const point_2d& controlPoint2, const point_2d& endPoint) noexcept
                : _Control_pt1(controlPoint1)
                , _Control_pt2(controlPoint2)
                , _End_pt(endPoint) {
            }
            inline constexpr abs_cubic_curve::abs_cubic_curve() noexcept {}

            inline constexpr void abs_cubic_curve::control_point_1(const point_2d& value) noexcept {
                _Control_pt1 = value;
            }
            inline constexpr void abs_cubic_curve::control_point_2(const point_2d& value) noexcept {
                _Control_pt2 = value;
            }
            inline constexpr void abs_cubic_curve::end_point(const point_2d& value) noexcept {
                _End_pt = value;
            }

            inline constexpr point_2d abs_cubic_curve::control_point_1() const noexcept {
                return _Control_pt1;
            }
            inline constexpr point_2d abs_cubic_curve::control_point_2() const noexcept {
                return _Control_pt2;
            }
            inline constexpr point_2d abs_cubic_curve::end_point() const noexcept {
                return _End_pt;
            }

			inline constexpr bool operator==(const abs_cubic_curve& lhs, const abs_cubic_curve& rhs) noexcept {
                return (lhs._Control_pt1 == rhs._Control_pt1) &&
                    (lhs._Control_pt2 == rhs._Control_pt2) &&
                    (lhs._End_pt == rhs._End_pt);
            }

            inline constexpr rel_cubic_curve::rel_cubic_curve(const point_2d& controlPoint1, const point_2d& controlPoint2, const point_2d& endPoint) noexcept
                : _Control_pt1(controlPoint1)
                , _Control_pt2(controlPoint2)
                , _End_pt(endPoint) {
            }
            inline constexpr rel_cubic_curve::rel_cubic_curve() noexcept {}

            inline constexpr void rel_cubic_curve::control_point_1(const point_2d& value) noexcept {
                _Control_pt1 = value;
            }
            inline constexpr void rel_cubic_curve::control_point_2(const point_2d& value) noexcept {
                _Control_pt2 = value;
            }
            inline constexpr void rel_cubic_curve::end_point(const point_2d& value) noexcept {
                _End_pt = value;
            }

            inline constexpr point_2d rel_cubic_curve::control_point_1() const noexcept {
                return _Control_pt1;
            }
            inline constexpr point_2d rel_cubic_curve::control_point_2() const noexcept {
                return _Control_pt2;
            }
            inline constexpr point_2d rel_cubic_curve::end_point() const noexcept {
                return _End_pt;
            }

			inline constexpr bool operator==(const rel_cubic_curve& lhs, const rel_cubic_curve& rhs) noexcept {
                return (lhs._Control_pt1 == rhs._Control_pt1) &&
                    (lhs._Control_pt2 == rhs._Control_pt2) &&
                    (lhs._End_pt == rhs._End_pt);
            }

            inline constexpr arc::arc() noexcept
                : arc(point_2d{ 10.0F, 10.0F }, pi<float>, pi<float>) { }
            inline constexpr arc::arc(const point_2d& rad, float rot, float sang) noexcept
                : _Radius(rad)
                , _Rotation(rot)
                , _Start_angle(sang) {
            }

            inline constexpr void arc::radius(const point_2d& rad) noexcept {
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

		enum class _Path_data_abs_new_path {};
		constexpr static _Path_data_abs_new_path _Path_data_abs_new_path_val = {};
		enum class _Path_data_rel_new_path {};
		constexpr static _Path_data_rel_new_path _Path_data_rel_new_path_val = {};
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

		template <class _TItem>
		struct _Path_group_perform_visit {
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_new_figure>, _Path_data_abs_new_path> = _Path_data_abs_new_path_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const figure_items::abs_new_figure& item, point_2d& lastMoveToPoint) noexcept {
				cairo_path_data_t cpdItem{};
				auto pt = item.at();
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt.x, pt.y };
				lastMoveToPoint = pt;
				vec.push_back(cpdItem);
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const figure_items::abs_line& item, point_2d&) noexcept {
				cairo_path_data_t cpdItem{};
				auto pt = item.to();
				cpdItem.header.type = CAIRO_PATH_LINE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt.x, pt.y };
				vec.push_back(cpdItem);
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const figure_items::abs_cubic_curve& item, point_2d&) noexcept {
				cairo_path_data_t cpdItem{};
				auto pt1 = item.control_point_1();
				auto pt2 = item.control_point_2();
				auto pt3 = item.end_point();
				cpdItem.header.type = CAIRO_PATH_CURVE_TO;
				cpdItem.header.length = 4;
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt1.x, pt1.y };
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt2.x, pt2.y };
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt3.x, pt3.y };
				vec.push_back(cpdItem);
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::abs_quadratic_curve&, point_2d&) noexcept {
				assert(false && "Abs quadratic curves should have been transformed into cubic curves already.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_new_figure>, _Path_data_rel_new_path> = _Path_data_rel_new_path_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::rel_new_figure&, point_2d&) noexcept {
				assert(false && "Rel new path instructions should have been eliminated.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::close_figure>, _Path_data_close_path> = _Path_data_close_path_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>& vec, const figure_items::close_figure&, point_2d& lastMoveToPoint) noexcept {
				cairo_path_data_t cpdItem{};
				cpdItem.header.type = CAIRO_PATH_CLOSE_PATH;
				cpdItem.header.length = 1;
				vec.push_back(cpdItem);
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { lastMoveToPoint.x, lastMoveToPoint.y };
				vec.push_back(cpdItem);
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::rel_line&, point_2d&) noexcept {
				assert(false && "Rel line should have been transformed into non-relative.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::rel_cubic_curve&, point_2d&) noexcept {
				assert(false && "Rel curve should have been transformed into non-relative.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::rel_quadratic_curve&, point_2d&) noexcept {
				assert(false && "Rel quadratic curves should have been transformed into cubic curves.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::arc>, _Path_data_arc> = _Path_data_arc_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::arc&, point_2d&) noexcept {
				assert(false && "Arcs should have been transformed into cubic curves.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_matrix>, _Path_data_abs_matrix> = _Path_data_abs_matrix_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::abs_matrix&, point_2d&) noexcept {
				assert(false && "Abs matrix should have been eliminated.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_matrix>, _Path_data_rel_matrix> = _Path_data_rel_matrix_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::rel_matrix&, point_2d&) noexcept {
				assert(false && "Rel matrix should have been eliminated.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::revert_matrix>, _Path_data_revert_matrix> = _Path_data_revert_matrix_val>
			constexpr static void _Perform(::std::vector<cairo_path_data_t>&, const figure_items::revert_matrix&, point_2d&) noexcept {
				assert(false && "Revert matrix should have been eliminated.");
			}
		};

		template <class Allocator>
		::std::vector<figure_items::figure_item> _Interpret_path_items(const path_builder<Allocator>&);
		//template <class Allocator>
		//::std::vector<figure_items::path_data_types> _Interpret_path_items(const path_builder<Allocator>&, ::std::error_code&) noexcept;

		template <class Allocator>
		inline path_group::path_group(const path_builder<Allocator>& pf)
			: _Cairo_path(new cairo_path_t, [](cairo_path_t* path) {
			if (path != nullptr) {
				if (path->data != nullptr) {
					delete[] path->data;
					path->data = nullptr;
					path->status = CAIRO_STATUS_NULL_POINTER;
				}
				delete path;
				path = nullptr;
			}
		}) {
			auto processedVec = _Interpret_path_items<Allocator>(pf);
			::std::vector<cairo_path_data_t> vec;
			point_2d lastMoveToPoint;
			for (const auto& val : processedVec) {
				::std::visit([&vec, &lastMoveToPoint](auto&& item) {
					using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
					_Path_group_perform_visit<T>::template _Perform<T>(vec, item, lastMoveToPoint);
				}, val);
			}
			_Cairo_path->num_data = static_cast<int>(vec.size());
			const auto numDataST = vec.size();
			_Cairo_path->data = new cairo_path_data_t[numDataST];
			for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
				_Cairo_path->data[currItemIndex] = vec[currItemIndex];
			}
			_Cairo_path->status = CAIRO_STATUS_SUCCESS;
		}

		template<class Allocator>
		inline path_group::path_group(const path_builder<Allocator>& pf, ::std::error_code& ec) noexcept
			: _Cairo_path(new cairo_path_t, [](cairo_path_t* path) {
			if (path != nullptr) {
				if (path->data != nullptr) {
					delete[] path->data;
					path->data = nullptr;
					path->status = CAIRO_STATUS_NULL_POINTER;
				}
				delete path;
				path = nullptr;
			}
		}) {
			auto processedVec = _Interpret_path_items<Allocator>(pf, ec);
			if (static_cast<bool>(ec)) {
				return;
			}

			::std::vector<cairo_path_data_t> vec;

			for (const auto& val : processedVec) {
				::std::visit([&vec](auto&& item) {
					using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
					_Path_group_perform_visit<T>::template _Perform<T>(vec, item);
				}, val);
			}
			_Cairo_path->num_data = static_cast<int>(vec.size());
			const auto numDataST = vec.size();
			_Cairo_path->data = new cairo_path_data_t[numDataST];
			for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
				_Cairo_path->data[currItemIndex] = vec[currItemIndex];
			}
			_Cairo_path->status = CAIRO_STATUS_SUCCESS;
			ec.clear();
		}

		inline cairo_antialias_t _Antialias_to_cairo_antialias_t(::std::experimental::io2d::antialias aa) {
			switch (aa) {
			case ::std::experimental::io2d::antialias::none:
				return CAIRO_ANTIALIAS_NONE;
			case ::std::experimental::io2d::antialias::fast:
				return CAIRO_ANTIALIAS_FAST;
			case ::std::experimental::io2d::antialias::good:
				return CAIRO_ANTIALIAS_GOOD;
			case ::std::experimental::io2d::antialias::best:
				return CAIRO_ANTIALIAS_BEST;
			default:
				throw ::std::runtime_error("Unknown antialias value.");
			}
		}

		inline cairo_fill_rule_t _Fill_rule_to_cairo_fill_rule_t(::std::experimental::io2d::fill_rule fr) {
			switch (fr) {
			case ::std::experimental::io2d::fill_rule::winding:
				return CAIRO_FILL_RULE_WINDING;
			case ::std::experimental::io2d::fill_rule::even_odd:
				return CAIRO_FILL_RULE_EVEN_ODD;
			default:
				throw ::std::runtime_error("Unknown fill_rule value.");
			}
		}

		inline ::std::experimental::io2d::fill_rule _Cairo_fill_rule_t_to_fill_rule(cairo_fill_rule_t cfr) {
			switch (cfr) {
			case CAIRO_FILL_RULE_WINDING:
				return ::std::experimental::io2d::fill_rule::winding;
			case CAIRO_FILL_RULE_EVEN_ODD:
				return ::std::experimental::io2d::fill_rule::even_odd;
			default:
				throw ::std::runtime_error("Unknown cairo_fill_rule_t value.");
			}
		}

		inline cairo_line_cap_t _Line_cap_to_cairo_line_cap_t(::std::experimental::io2d::line_cap lc) {
			switch (lc) {
			case ::std::experimental::io2d::line_cap::none:
				return CAIRO_LINE_CAP_BUTT;
			case ::std::experimental::io2d::line_cap::round:
				return CAIRO_LINE_CAP_ROUND;
			case ::std::experimental::io2d::line_cap::square:
				return CAIRO_LINE_CAP_SQUARE;
			default:
				throw ::std::runtime_error("Unknown line_cap value.");
			}
		}

		inline ::std::experimental::io2d::line_cap _Cairo_line_cap_t_to_line_cap(cairo_line_cap_t clc) {
			switch (clc) {
			case CAIRO_LINE_CAP_BUTT:
				return ::std::experimental::io2d::line_cap::none;
			case CAIRO_LINE_CAP_ROUND:
				return ::std::experimental::io2d::line_cap::round;
			case CAIRO_LINE_CAP_SQUARE:
				return ::std::experimental::io2d::line_cap::square;
			default:
				throw ::std::runtime_error("Unknown cairo_line_cap_t value.");
			}
		}

		inline cairo_line_join_t _Line_join_to_cairo_line_join_t(::std::experimental::io2d::line_join lj) {
			switch (lj) {
			case ::std::experimental::io2d::line_join::miter:
				return CAIRO_LINE_JOIN_MITER;
			case ::std::experimental::io2d::line_join::round:
				return CAIRO_LINE_JOIN_ROUND;
			case ::std::experimental::io2d::line_join::bevel:
				return CAIRO_LINE_JOIN_BEVEL;
			case ::std::experimental::io2d::line_join::miter_or_bevel:
				return CAIRO_LINE_JOIN_MITER;
			default:
				throw ::std::runtime_error("Unknown line_join value.");
			}
		}

		inline ::std::experimental::io2d::line_join _Cairo_line_join_t_to_line_join(cairo_line_join_t clj) {
			switch (clj) {
			case CAIRO_LINE_JOIN_MITER:
				return ::std::experimental::io2d::line_join::miter_or_bevel;
			case CAIRO_LINE_JOIN_ROUND:
				return ::std::experimental::io2d::line_join::round;
			case CAIRO_LINE_JOIN_BEVEL:
				return ::std::experimental::io2d::line_join::bevel;
			default:
				throw ::std::runtime_error("Unknown cairo_line_join_t value.");
			}
		}

		inline cairo_operator_t _Compositing_operator_to_cairo_operator_t(::std::experimental::io2d::compositing_op co) {
			switch (co)
			{
			case ::std::experimental::io2d::compositing_op::clear:
				return CAIRO_OPERATOR_CLEAR;
			case ::std::experimental::io2d::compositing_op::source:
				return CAIRO_OPERATOR_SOURCE;
			case ::std::experimental::io2d::compositing_op::over:
				return CAIRO_OPERATOR_OVER;
			case ::std::experimental::io2d::compositing_op::in:
				return CAIRO_OPERATOR_IN;
			case ::std::experimental::io2d::compositing_op::out:
				return CAIRO_OPERATOR_OUT;
			case ::std::experimental::io2d::compositing_op::atop:
				return CAIRO_OPERATOR_ATOP;
			case ::std::experimental::io2d::compositing_op::dest:
				return CAIRO_OPERATOR_DEST;
			case ::std::experimental::io2d::compositing_op::dest_over:
				return CAIRO_OPERATOR_DEST_OVER;
			case ::std::experimental::io2d::compositing_op::dest_in:
				return CAIRO_OPERATOR_DEST_IN;
			case ::std::experimental::io2d::compositing_op::dest_out:
				return CAIRO_OPERATOR_DEST_OUT;
			case ::std::experimental::io2d::compositing_op::dest_atop:
				return CAIRO_OPERATOR_DEST_ATOP;
			case ::std::experimental::io2d::compositing_op::xor_op:
				return CAIRO_OPERATOR_XOR;
			case ::std::experimental::io2d::compositing_op::add:
				return CAIRO_OPERATOR_ADD;
			case ::std::experimental::io2d::compositing_op::saturate:
				return CAIRO_OPERATOR_SATURATE;
			case ::std::experimental::io2d::compositing_op::multiply:
				return CAIRO_OPERATOR_MULTIPLY;
			case ::std::experimental::io2d::compositing_op::screen:
				return CAIRO_OPERATOR_SCREEN;
			case ::std::experimental::io2d::compositing_op::overlay:
				return CAIRO_OPERATOR_OVERLAY;
			case ::std::experimental::io2d::compositing_op::darken:
				return CAIRO_OPERATOR_DARKEN;
			case ::std::experimental::io2d::compositing_op::lighten:
				return CAIRO_OPERATOR_LIGHTEN;
			case ::std::experimental::io2d::compositing_op::color_dodge:
				return CAIRO_OPERATOR_COLOR_DODGE;
			case ::std::experimental::io2d::compositing_op::color_burn:
				return CAIRO_OPERATOR_COLOR_BURN;
			case ::std::experimental::io2d::compositing_op::hard_light:
				return CAIRO_OPERATOR_HARD_LIGHT;
			case ::std::experimental::io2d::compositing_op::soft_light:
				return CAIRO_OPERATOR_SOFT_LIGHT;
			case ::std::experimental::io2d::compositing_op::difference:
				return CAIRO_OPERATOR_DIFFERENCE;
			case ::std::experimental::io2d::compositing_op::exclusion:
				return CAIRO_OPERATOR_EXCLUSION;
			case ::std::experimental::io2d::compositing_op::hsl_hue:
				return CAIRO_OPERATOR_HSL_HUE;
			case ::std::experimental::io2d::compositing_op::hsl_saturation:
				return CAIRO_OPERATOR_HSL_SATURATION;
			case ::std::experimental::io2d::compositing_op::hsl_color:
				return CAIRO_OPERATOR_HSL_COLOR;
			case ::std::experimental::io2d::compositing_op::hsl_luminosity:
				return CAIRO_OPERATOR_HSL_LUMINOSITY;
			default:
				throw ::std::runtime_error("Unknown compositing_op value.");
			}
		}

		inline ::std::experimental::io2d::compositing_op _Cairo_operator_t_to_compositing_operator(cairo_operator_t co) {
			switch (co)
			{
			case CAIRO_OPERATOR_CLEAR:
				return ::std::experimental::io2d::compositing_op::clear;
			case CAIRO_OPERATOR_SOURCE:
				return ::std::experimental::io2d::compositing_op::source;
			case CAIRO_OPERATOR_OVER:
				return ::std::experimental::io2d::compositing_op::over;
			case CAIRO_OPERATOR_IN:
				return ::std::experimental::io2d::compositing_op::in;
			case CAIRO_OPERATOR_OUT:
				return ::std::experimental::io2d::compositing_op::out;
			case CAIRO_OPERATOR_ATOP:
				return ::std::experimental::io2d::compositing_op::atop;
			case CAIRO_OPERATOR_DEST:
				return ::std::experimental::io2d::compositing_op::dest;
			case CAIRO_OPERATOR_DEST_OVER:
				return ::std::experimental::io2d::compositing_op::dest_over;
			case CAIRO_OPERATOR_DEST_IN:
				return ::std::experimental::io2d::compositing_op::dest_in;
			case CAIRO_OPERATOR_DEST_OUT:
				return ::std::experimental::io2d::compositing_op::dest_out;
			case CAIRO_OPERATOR_DEST_ATOP:
				return ::std::experimental::io2d::compositing_op::dest_atop;
			case CAIRO_OPERATOR_XOR:
				return ::std::experimental::io2d::compositing_op::xor_op;
			case CAIRO_OPERATOR_ADD:
				return ::std::experimental::io2d::compositing_op::add;
			case CAIRO_OPERATOR_SATURATE:
				return ::std::experimental::io2d::compositing_op::saturate;
			case CAIRO_OPERATOR_MULTIPLY:
				return ::std::experimental::io2d::compositing_op::multiply;
			case CAIRO_OPERATOR_SCREEN:
				return ::std::experimental::io2d::compositing_op::screen;
			case CAIRO_OPERATOR_OVERLAY:
				return ::std::experimental::io2d::compositing_op::overlay;
			case CAIRO_OPERATOR_DARKEN:
				return ::std::experimental::io2d::compositing_op::darken;
			case CAIRO_OPERATOR_LIGHTEN:
				return ::std::experimental::io2d::compositing_op::lighten;
			case CAIRO_OPERATOR_COLOR_DODGE:
				return ::std::experimental::io2d::compositing_op::color_dodge;
			case CAIRO_OPERATOR_COLOR_BURN:
				return ::std::experimental::io2d::compositing_op::color_burn;
			case CAIRO_OPERATOR_HARD_LIGHT:
				return ::std::experimental::io2d::compositing_op::hard_light;
			case CAIRO_OPERATOR_SOFT_LIGHT:
				return ::std::experimental::io2d::compositing_op::soft_light;
			case CAIRO_OPERATOR_DIFFERENCE:
				return ::std::experimental::io2d::compositing_op::difference;
			case CAIRO_OPERATOR_EXCLUSION:
				return ::std::experimental::io2d::compositing_op::exclusion;
			case CAIRO_OPERATOR_HSL_HUE:
				return ::std::experimental::io2d::compositing_op::hsl_hue;
			case CAIRO_OPERATOR_HSL_SATURATION:
				return ::std::experimental::io2d::compositing_op::hsl_saturation;
			case CAIRO_OPERATOR_HSL_COLOR:
				return ::std::experimental::io2d::compositing_op::hsl_color;
			case CAIRO_OPERATOR_HSL_LUMINOSITY:
				return ::std::experimental::io2d::compositing_op::hsl_luminosity;
			default:
				throw ::std::runtime_error("Unknown cairo_operator_t value.");
			}
		}

		inline cairo_format_t _Format_to_cairo_format_t(::std::experimental::io2d::format f) {
			switch (f) {
			case ::std::experimental::io2d::format::invalid:
				return CAIRO_FORMAT_INVALID;
			case ::std::experimental::io2d::format::argb32:
				return CAIRO_FORMAT_ARGB32;
			case ::std::experimental::io2d::format::xrgb32:
				return CAIRO_FORMAT_RGB24;
			case ::std::experimental::io2d::format::a8:
				return CAIRO_FORMAT_A8;
			case ::std::experimental::io2d::format::rgb16_565:
				return CAIRO_FORMAT_RGB16_565;
			case ::std::experimental::io2d::format::rgb30:
				return CAIRO_FORMAT_RGB30;
			default:
				throw ::std::runtime_error("Unknown format value.");
			}
		}

		inline ::std::experimental::io2d::format _Cairo_format_t_to_format(cairo_format_t cf) {
			switch (cf) {
			case CAIRO_FORMAT_INVALID:
				return ::std::experimental::io2d::format::invalid;
			case CAIRO_FORMAT_ARGB32:
				return ::std::experimental::io2d::format::argb32;
			case CAIRO_FORMAT_RGB24:
				return ::std::experimental::io2d::format::xrgb32;
			case CAIRO_FORMAT_A8:
				return ::std::experimental::io2d::format::a8;
			case CAIRO_FORMAT_RGB16_565:
				return ::std::experimental::io2d::format::rgb16_565;
			case CAIRO_FORMAT_RGB30:
				return ::std::experimental::io2d::format::rgb30;
			case CAIRO_FORMAT_A1:
				// intentional fallthrough
			default:
				throw ::std::runtime_error("Unknown cairo_format_t value.");
			}
		}

		inline cairo_extend_t _Extend_to_cairo_extend_t(::std::experimental::io2d::wrap_mode e) {
			switch (e) {
			case ::std::experimental::io2d::wrap_mode::none:
				return CAIRO_EXTEND_NONE;
			case ::std::experimental::io2d::wrap_mode::repeat:
				return CAIRO_EXTEND_REPEAT;
			case ::std::experimental::io2d::wrap_mode::reflect:
				return CAIRO_EXTEND_REFLECT;
			case ::std::experimental::io2d::wrap_mode::pad:
				return CAIRO_EXTEND_PAD;
			default:
				throw ::std::runtime_error("Unknown wrap_mode value.");
			}
		}

		inline ::std::experimental::io2d::wrap_mode _Cairo_extend_t_to_extend(cairo_extend_t ce) {
			switch (ce) {
			case CAIRO_EXTEND_NONE:
				return ::std::experimental::io2d::wrap_mode::none;
			case CAIRO_EXTEND_REPEAT:
				return ::std::experimental::io2d::wrap_mode::repeat;
			case CAIRO_EXTEND_REFLECT:
				return ::std::experimental::io2d::wrap_mode::reflect;
			case CAIRO_EXTEND_PAD:
				return ::std::experimental::io2d::wrap_mode::pad;
			default:
				throw ::std::runtime_error("Unknown cairo_extend_t value.");
			}
		}

		inline cairo_filter_t _Filter_to_cairo_filter_t(::std::experimental::io2d::filter f) {
			switch (f) {
			case ::std::experimental::io2d::filter::fast:
				return CAIRO_FILTER_FAST;
			case ::std::experimental::io2d::filter::good:
				return CAIRO_FILTER_GOOD;
			case ::std::experimental::io2d::filter::best:
				return CAIRO_FILTER_BEST;
			case ::std::experimental::io2d::filter::nearest:
				return CAIRO_FILTER_NEAREST;
			case ::std::experimental::io2d::filter::bilinear:
				return CAIRO_FILTER_BILINEAR;
			default:
				throw ::std::runtime_error("Unknown filter value.");
			}
		}

		inline ::std::experimental::io2d::filter _Cairo_filter_t_to_filter(cairo_filter_t cf) {
			switch (cf) {
			case CAIRO_FILTER_FAST:
				return ::std::experimental::io2d::filter::fast;
			case CAIRO_FILTER_GOOD:
				return ::std::experimental::io2d::filter::good;
			case CAIRO_FILTER_BEST:
				return ::std::experimental::io2d::filter::best;
			case CAIRO_FILTER_NEAREST:
				return ::std::experimental::io2d::filter::nearest;
			case CAIRO_FILTER_BILINEAR:
				return ::std::experimental::io2d::filter::bilinear;
			case CAIRO_FILTER_GAUSSIAN:
				throw ::std::runtime_error("Unexpected cairo_filter_t value CAIRO_FILTER_GAUSSIAN.");
			default:
				throw ::std::runtime_error("Unknown cairo_filter_t value.");
			}
		}

		inline cairo_pattern_type_t _Brush_type_to_cairo_pattern_type_t(::std::experimental::io2d::brush_type bt) {
			switch (bt) {
			case ::std::experimental::io2d::brush_type::solid_color:
				return CAIRO_PATTERN_TYPE_SOLID;
			case ::std::experimental::io2d::brush_type::surface:
				return CAIRO_PATTERN_TYPE_SURFACE;
			case ::std::experimental::io2d::brush_type::linear:
				return CAIRO_PATTERN_TYPE_LINEAR;
			case ::std::experimental::io2d::brush_type::radial:
				return CAIRO_PATTERN_TYPE_RADIAL;
				//case ::std::experimental::io2d::brush_type::mesh:
				//	return CAIRO_PATTERN_TYPE_MESH;
			default:
				throw ::std::runtime_error("Unknown brush_type value.");
			}
		}

		inline ::std::experimental::io2d::brush_type _Cairo_pattern_type_t_to_brush_type(cairo_pattern_type_t cpt) {
			switch (cpt) {
			case CAIRO_PATTERN_TYPE_SOLID:
				return ::std::experimental::io2d::brush_type::solid_color;
			case CAIRO_PATTERN_TYPE_SURFACE:
				return ::std::experimental::io2d::brush_type::surface;
			case CAIRO_PATTERN_TYPE_LINEAR:
				return ::std::experimental::io2d::brush_type::linear;
			case CAIRO_PATTERN_TYPE_RADIAL:
				return ::std::experimental::io2d::brush_type::radial;
			case CAIRO_PATTERN_TYPE_MESH:
				throw ::std::runtime_error("Unsupported cairo_pattern_type_t value 'CAIRO_PATTERN_TYPE_MESH'.");
				//return ::std::experimental::io2d::brush_type::mesh;
			case CAIRO_PATTERN_TYPE_RASTER_SOURCE:
				throw ::std::runtime_error("Unsupported cairo_pattern_type_t value 'CAIRO_PATTERN_TYPE_RASTER_SOURCE'.");
			default:
				throw ::std::runtime_error("Unknown cairo_pattern_type_t value.");
			}
		}

		template <class _TItem>
		struct _Path_item_interpret_visitor {
			constexpr static float twoThirds = 2.0F / 3.0F;

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_new_figure>, _Path_data_abs_new_path> = _Path_data_abs_new_path_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d& closePoint, stack<matrix_2d>&) noexcept {
				const auto pt = m.transform_pt({ 0.0F, 0.0F }) + item.at();
				v.emplace_back(::std::in_place_type<figure_items::abs_new_figure>, pt);
				currentPoint = pt;
				closePoint = pt;
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_new_figure>, _Path_data_rel_new_path> = _Path_data_rel_new_path_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d& closePoint, stack<matrix_2d>&) noexcept {
				auto amtx = m;
				amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
				const auto pt = currentPoint + item.at() * amtx;
				v.emplace_back(::std::in_place_type<figure_items::abs_new_figure>, pt);
				currentPoint = pt;
				closePoint = pt;
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::close_figure>, _Path_data_close_path> = _Path_data_close_path_val>
			static void _Interpret(const T&, ::std::vector<figure_items::figure_item>& v, matrix_2d&, point_2d& currentPoint, point_2d& closePoint, stack<matrix_2d>&) noexcept {
				const auto& item = v.rbegin();
				auto idx = item->index();
				if (idx == 0 || idx == 1) {
					return; // degenerate path
				}
				v.emplace_back(::std::in_place_type<figure_items::close_figure>);
				v.emplace_back(::std::in_place_type<figure_items::abs_new_figure>,
					closePoint);
				currentPoint = closePoint;
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_matrix>, _Path_data_abs_matrix> = _Path_data_abs_matrix_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>&, matrix_2d& m, point_2d&, point_2d&, stack<matrix_2d>& matrices) noexcept {
				matrices.push(m);
				m = item.matrix();
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_matrix>, _Path_data_rel_matrix> = _Path_data_rel_matrix_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>&, matrix_2d& m, point_2d&, point_2d&, stack<matrix_2d>& matrices) noexcept {
				const auto updateM = m * item.matrix();
				matrices.push(m);
				m = updateM;
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::revert_matrix>, _Path_data_revert_matrix> = _Path_data_revert_matrix_val>
			static void _Interpret(const T&, ::std::vector<figure_items::figure_item>&, matrix_2d& m, point_2d&, point_2d&, stack<matrix_2d>& matrices) noexcept {
				if (matrices.empty()) {
					m = matrix_2d{};
				}
				else {
					m = matrices.top();
					matrices.pop();
				}
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d&, stack<matrix_2d>&) noexcept {
				const auto pt1 = m.transform_pt(item.control_point_1() - currentPoint) + currentPoint;
				const auto pt2 = m.transform_pt(item.control_point_2() - currentPoint) + currentPoint;
				const auto pt3 = m.transform_pt(item.end_point() - currentPoint) + currentPoint;
				if (currentPoint == pt1 && pt1 == pt2 && pt2 == pt3) {
					return; // degenerate path segment
				}
				v.emplace_back(::std::in_place_type<figure_items::abs_cubic_curve>, pt1,
					pt2, pt3);
				currentPoint = pt3;
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d&, stack<matrix_2d>&) noexcept {
				const auto pt = m.transform_pt(item.to() - currentPoint) + currentPoint;
				if (currentPoint == pt) {
					return; // degenerate path segment
				}
				v.emplace_back(::std::in_place_type<figure_items::abs_line>, pt);
				currentPoint = pt;
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d&, stack<matrix_2d>&) noexcept {
				// Turn it into a cubic curve since cairo doesn't have quadratic curves.
				//point_2d beginPt;
				const auto controlPt = m.transform_pt(item.control_point() - currentPoint) + currentPoint;
				const auto endPt = m.transform_pt(item.end_point() - currentPoint) + currentPoint;
				if (currentPoint == controlPt && controlPt == endPt) {
					return; // degenerate path segment
				}
				const auto beginPt = currentPoint;
				point_2d cpt1 = { ((controlPt.x - beginPt.x) * twoThirds) + beginPt.x, ((controlPt.y - beginPt.y) * twoThirds) + beginPt.y };
				point_2d cpt2 = { ((controlPt.x - endPt.x) * twoThirds) + endPt.x, ((controlPt.y - endPt.y) * twoThirds) + endPt.y };
				v.emplace_back(::std::in_place_type<figure_items::abs_cubic_curve>, cpt1, cpt2, endPt);
				currentPoint = endPt;
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::arc>, _Path_data_arc> = _Path_data_arc_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d&, stack<matrix_2d>&) noexcept {
				const float rot = item.rotation();
				const float oneThousandthOfADegreeInRads = pi<float> / 180'000.0F;
				if (abs(rot) < oneThousandthOfADegreeInRads) {
					// Return if the rotation is less than one thousandth of one degree; it's a degenerate path segment.
					return;
				}
				const auto clockwise = (rot < 0.0F) ? true : false;
				const point_2d rad = item.radius();
				auto startAng = item.start_angle();
				const auto origM = m;
				m = matrix_2d::init_scale(rad);
				auto centerOffset = (point_for_angle(two_pi<float> -startAng) * rad);
				centerOffset.y = -centerOffset.y;
				auto ctr = currentPoint - centerOffset;

				point_2d pt0, pt1, pt2, pt3;
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
				auto rotCntrCwFn = [](const point_2d& pt, float a) -> point_2d {
					auto result = point_2d{ pt.x * cos(a) - pt.y * sin(a),
						pt.x * sin(a) + pt.y * cos(a) };
					result.x = _Round_floating_point_to_zero(result.x);
					result.y = _Round_floating_point_to_zero(result.y);
					return result;
				};
				auto rotCwFn = [](const point_2d& pt, float a) -> point_2d {
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
				point_2d tempCurrPt;
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
					v.emplace_back(::std::in_place_type<figure_items::abs_cubic_curve>, cpt1, cpt2, cpt3);
					currTheta -= theta;
				}
				m = origM;
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d&, stack<matrix_2d>&) noexcept {
				auto amtx = m;
				amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
				const auto pt1 = item.control_point_1() * amtx;
				const auto pt2 = item.control_point_2() * amtx;
				const auto pt3 = item.end_point()* amtx;
				if (currentPoint == pt1 && pt1 == pt2 && pt2 == pt3) {
					return; // degenerate path segment
				}
				v.emplace_back(::std::in_place_type<figure_items::abs_cubic_curve>, currentPoint + pt1, currentPoint + pt1 + pt2, currentPoint + pt1 + pt2 + pt3);
				currentPoint = currentPoint + pt1 + pt2 + pt3;
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d&, stack<matrix_2d>&) noexcept {
				auto amtx = m;
				amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
				const auto pt = currentPoint + item.to() * amtx;
				if (currentPoint == pt) {
					return; // degenerate path segment
				}
				v.emplace_back(::std::in_place_type<figure_items::abs_line>, pt);
				currentPoint = pt;
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, figure_items::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
			static void _Interpret(const T& item, ::std::vector<figure_items::figure_item>& v, matrix_2d& m, point_2d& currentPoint, point_2d&, stack<matrix_2d>&) noexcept {
				auto amtx = m;
				amtx.m20 = 0.0F; amtx.m21 = 0.0F; // obliterate translation since this is relative.
				const auto controlPt = currentPoint + item.control_point() * amtx;
				const auto endPt = currentPoint + item.control_point() * amtx + item.end_point() * amtx;
				const auto beginPt = currentPoint;
				if (currentPoint == controlPt && controlPt == endPt) {
					return; // degenerate path segment
				}
				point_2d cpt1 = { ((controlPt.x - beginPt.x) * twoThirds) + beginPt.x, ((controlPt.y - beginPt.y) * twoThirds) + beginPt.y };
				point_2d cpt2 = { ((controlPt.x - endPt.x) * twoThirds) + endPt.x, ((controlPt.y - endPt.y) * twoThirds) + endPt.y };
				v.emplace_back(::std::in_place_type<figure_items::abs_cubic_curve>, cpt1, cpt2, endPt);
				currentPoint = endPt;
			}
		};

		template <class Allocator>
		inline ::std::vector<figure_items::figure_item> _Interpret_path_items(const path_builder<Allocator>& pf) {
			matrix_2d m;
			point_2d currentPoint; // Tracks the untransformed current point.
			point_2d closePoint;   // Tracks the transformed close point.
			::std::stack<matrix_2d> matrices;
			::std::vector<figure_items::figure_item> v;

			for (const figure_items::figure_item& val : pf) {
				::std::visit([&m, &currentPoint, &closePoint, &matrices, &v](auto&& item) {
					using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
					_Path_item_interpret_visitor<T>::template _Interpret<T>(item, v, m, currentPoint, closePoint, matrices);
				}, val);
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
		inline void path_builder<Allocator>::new_path(const point_2d& v) noexcept {
			_Data.emplace_back(in_place_type<figure_items::abs_new_figure>, v);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::rel_new_figure(const point_2d& v) noexcept {
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
		inline void path_builder<Allocator>::arc(const point_2d& rad, float rot, const float sang) noexcept {
			_Data.emplace_back(in_place_type<figure_items::arc>, rad, rot, sang);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::cubic_curve(const point_2d& pt0, const point_2d& pt1, const point_2d& pt2) noexcept {
			_Data.emplace_back(in_place_type<figure_items::abs_cubic_curve>, pt0, pt1, pt2);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::line(const point_2d& pt) noexcept {
			_Data.emplace_back(in_place_type<figure_items::abs_line>, pt);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::quadratic_curve(const point_2d& pt0, const point_2d& pt1) noexcept {
			_Data.emplace_back(in_place_type<figure_items::abs_quadratic_curve>, pt0, pt1);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::rel_cubic_curve(const point_2d& dpt0, const point_2d& dpt1, const point_2d& dpt2) noexcept {
			_Data.emplace_back(in_place_type<figure_items::rel_cubic_curve>, dpt0, dpt1, dpt2);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::rel_line(const point_2d& dpt) noexcept {
			_Data.emplace_back(in_place_type<figure_items::rel_line>, dpt);
		}

		template<class Allocator>
		inline void path_builder<Allocator>::rel_quadratic_curve(const point_2d& dpt0, const point_2d& dpt1) noexcept {
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

        template<class Allocator>
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
        }

        //Brushes

		template <class InputIterator>
		inline brush::brush(const point_2d& begin, const point_2d& end,
			InputIterator first, InputIterator last)
			: _Brush()
			, _Image_surface()
			, _Brush_type(brush_type::linear) {
			_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_linear(begin.x, begin.y, end.x, end.y), &cairo_pattern_destroy);
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

			for (auto it = first; it != last; ++it) {
				auto stop = *it;
				cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
			}
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
		}

		template <class InputIterator>
		inline brush::brush(const circle& start, const circle& end,
			InputIterator first, InputIterator last)
			: _Brush()
			, _Image_surface()
			, _Brush_type(brush_type::radial) {
			_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(start.center().x, start.center().y, start.radius(), end.center().x, end.center().y, end.radius()), &cairo_pattern_destroy);
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
			for (auto it = first; it != last; ++it) {
				auto stop = *it;
				cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
			}
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
		}

		inline brush::native_handle_type brush::native_handle() const noexcept {
			return _Brush.get();
		}

		inline brush::brush(const rgba_color& color)
			: _Brush()
			, _Image_surface()
			, _Brush_type(brush_type::solid_color) {
			_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_rgba(color.r(), color.g(), color.b(), color.a()), &cairo_pattern_destroy);
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
		}

		inline brush::brush(const point_2d& begin, const point_2d& end,
			::std::initializer_list<gradient_stop> il)
			: _Brush()
			, _Image_surface()
			, _Brush_type(brush_type::linear) {
			_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_linear(begin.x, begin.y, end.x, end.y), &cairo_pattern_destroy);
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

			for (const gradient_stop& stop : il) {
				cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
			}

			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
		}

		inline brush::brush(const circle& start, const circle& end,
			::std::initializer_list<gradient_stop> il)
			: _Brush()
			, _Image_surface()
			, _Brush_type(brush_type::radial) {
			_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(start.center().x, start.center().y, start.radius(), end.center().x, end.center().y, end.radius()), &cairo_pattern_destroy);
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

			for (const gradient_stop& stop : il) {
				cairo_pattern_add_color_stop_rgba(_Brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
			}

			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
		}

		inline brush::brush(image_surface&& img)
			: _Brush()
			, _Image_surface(make_shared<image_surface>(::std::move(img)))
			, _Brush_type(brush_type::surface) {
			//if (img.is_finished()) {
			//	_Throw_if_failed_cairo_status_t(CAIRO_STATUS_SURFACE_FINISHED);
			//}
			_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_for_surface(_Image_surface.get()->native_handle().csfce), &cairo_pattern_destroy);
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
		}

		inline brush_type brush::type() const noexcept {
			return _Brush_type;
		}

		// Surfaces

		inline mapped_surface::mapped_surface(surface::native_handle_type nh, surface::native_handle_type map_of)
			: _Mapped_surface(nh)
			, _Map_of(map_of) {
			assert(_Mapped_surface.csfce != nullptr && _Map_of.csfce != nullptr);
			auto status = cairo_surface_status(_Mapped_surface.csfce);
			if (status != CAIRO_STATUS_SUCCESS) {
				cairo_surface_unmap_image(_Mapped_surface.csfce, _Map_of.csfce);
				_Mapped_surface = { nullptr, nullptr };
				_Map_of = { nullptr, nullptr };
				_Throw_if_failed_cairo_status_t(status);
			}
			// Reference the surface that is mapped to ensure it isn't accidentally destroyed while the map still exists.
			cairo_surface_reference(_Map_of.csfce);
		}

		inline mapped_surface::mapped_surface(surface::native_handle_type nh, surface::native_handle_type map_of, error_code& ec) noexcept
			: _Mapped_surface(nh)
			, _Map_of(map_of) {
			assert(_Mapped_surface.csfce != nullptr && _Map_of.csfce != nullptr);
			auto status = cairo_surface_status(_Mapped_surface.csfce);
			if (status != CAIRO_STATUS_SUCCESS) {
				cairo_surface_unmap_image(_Mapped_surface.csfce, _Map_of.csfce);
				_Mapped_surface = { nullptr, nullptr };
				_Map_of = { nullptr, nullptr };
				ec = make_error_code(errc::not_supported);
				return;
			}
			// Reference the surface that is mapped to ensure it isn't accidentally destroyed while the map still exists.
			cairo_surface_reference(_Map_of.csfce);
			ec.clear();
		}

		inline mapped_surface::~mapped_surface() {
			if (_Mapped_surface.csfce != nullptr) {
				cairo_surface_unmap_image(_Map_of.csfce, _Mapped_surface.csfce);
				// Remove the reference we added to the surface that was mapped.
				cairo_surface_destroy(_Map_of.csfce);
				_Mapped_surface.csfce = nullptr;
				_Map_of.csfce = nullptr;
			}
		}

		inline void mapped_surface::commit_changes() {
			cairo_surface_mark_dirty(_Mapped_surface.csfce);
		}

		inline void mapped_surface::commit_changes(::std::error_code& ec) noexcept {
			cairo_surface_mark_dirty(_Mapped_surface.csfce);
			ec.clear();
		}

		inline void mapped_surface::commit_changes(const bounding_box& area) {
			cairo_surface_mark_dirty_rectangle(_Mapped_surface.csfce, static_cast<int>(area.x()), static_cast<int>(area.y()),
				static_cast<int>(area.width()), static_cast<int>(area.height()));
		}

		inline void mapped_surface::commit_changes(const bounding_box& area, error_code& ec) noexcept {
			cairo_surface_mark_dirty_rectangle(_Mapped_surface.csfce, static_cast<int>(area.x()), static_cast<int>(area.y()),
				static_cast<int>(area.width()), static_cast<int>(area.height()));
			ec.clear();
		}

		inline unsigned char* mapped_surface::data() {
			auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
			if (result == nullptr) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
			}
			return result;
		}

		inline unsigned char* mapped_surface::data(error_code& ec) noexcept {
			auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
			if (result == nullptr) {
				ec = make_error_code(errc::state_not_recoverable);
				return result;
			}
			ec.clear();
			return result;
		}

		inline const unsigned char* mapped_surface::data() const {
			auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
			if (result == nullptr) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
			}
			return result;
		}

		inline const unsigned char* mapped_surface::data(error_code& ec) const noexcept {
			auto result = cairo_image_surface_get_data(_Mapped_surface.csfce);
			if (result == nullptr) {
				ec = make_error_code(errc::state_not_recoverable);
				return result;
			}
			ec.clear();
			return result;
		}

		inline ::std::experimental::io2d::format mapped_surface::format() const noexcept {
			if (cairo_surface_status(_Mapped_surface.csfce) != CAIRO_STATUS_SUCCESS) {
				return experimental::io2d::format::invalid;
			}
			return _Cairo_format_t_to_format(cairo_image_surface_get_format(_Mapped_surface.csfce));
		}

		inline int mapped_surface::width() const noexcept {
			if (format() == experimental::io2d::format::invalid) {
				return 0;
			}
			return cairo_image_surface_get_width(_Mapped_surface.csfce);
		}

		inline int mapped_surface::height() const noexcept {
			if (format() == experimental::io2d::format::invalid) {
				return 0;
			}
			return cairo_image_surface_get_height(_Mapped_surface.csfce);
		}

		inline int mapped_surface::stride() const noexcept {
			if (format() == experimental::io2d::format::invalid) {
				return 0;
			}
			return cairo_image_surface_get_stride(_Mapped_surface.csfce);
		}
	}
}
