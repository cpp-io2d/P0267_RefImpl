#pragma once
#include "xio2d.h"
#include "xgraphicsmathfloat.h"
#include <limits>

namespace std::experimental::io2d {
	inline namespace v1 {
		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::create_point_2d() noexcept {
			return create_point_2d(0.0f, 0.0f);
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::create_point_2d(float x, float y) noexcept {
			auto result = _Graphics_math_float_impl::point_2d_data_type();
			result._X = x;
			result._Y = y;
			return result;
		}

		inline void _Graphics_math_float_impl::x(typename _Graphics_math_float_impl::point_2d_data_type& val, float x) noexcept {
			val._X = x;
		}

		inline void _Graphics_math_float_impl::y(typename _Graphics_math_float_impl::point_2d_data_type& val, float y) noexcept {
			val._Y = y;
		}

		inline float _Graphics_math_float_impl::x(const typename _Graphics_math_float_impl::point_2d_data_type& val) noexcept {
			return val._X;
		}

		inline float _Graphics_math_float_impl::y(const typename _Graphics_math_float_impl::point_2d_data_type& val) noexcept {
			return val._Y;
		}

		inline float _Graphics_math_float_impl::dot(const typename _Graphics_math_float_impl::point_2d_data_type& a, const typename _Graphics_math_float_impl::point_2d_data_type& b) noexcept {
			return a._X * b._X + a._Y * b._Y;
		}

		inline float _Graphics_math_float_impl::magnitude(const typename _Graphics_math_float_impl::point_2d_data_type& val) noexcept {
			return ::std::sqrt(val._X * val._X + val._Y * val._Y);
		}

		inline float _Graphics_math_float_impl::magnitude_squared(const typename _Graphics_math_float_impl::point_2d_data_type& val) noexcept {
			return val._X * val._X + val._Y * val._Y;
		}

		inline float _Graphics_math_float_impl::angular_direction(const typename _Graphics_math_float_impl::point_2d_data_type& val) noexcept {
			auto v = ::std::atan2(val._Y, val._X);
			if (v < 0.0F) {
				v += two_pi<float>;
			}
			return v;
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::to_unit(const typename _Graphics_math_float_impl::point_2d_data_type& val) noexcept {
			auto leng = magnitude(val);
			auto result = val;
			result._X = val._X / leng;
			result._Y = val._Y / leng;
			return result;
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::add(const typename _Graphics_math_float_impl::point_2d_data_type& lhs, const typename _Graphics_math_float_impl::point_2d_data_type& rhs) noexcept {
			_Graphics_math_float_impl::point_2d_data_type result;
			result._X = lhs._X + rhs._X;
			result._Y = lhs._Y + rhs._Y;
			return result;
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::add(const typename _Graphics_math_float_impl::point_2d_data_type& lhs, float rhs) noexcept {
			_Graphics_math_float_impl::point_2d_data_type result;
			result._X = lhs._X + rhs;
			result._Y = lhs._Y + rhs;
			return result;
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::add(float lhs, const typename _Graphics_math_float_impl::point_2d_data_type& rhs) noexcept {
			_Graphics_math_float_impl::point_2d_data_type result;
			result._X = lhs + rhs._X;
			result._Y = lhs + rhs._Y;
			return result;
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::subtract(const typename _Graphics_math_float_impl::point_2d_data_type& lhs, const typename _Graphics_math_float_impl::point_2d_data_type& rhs) noexcept {
			_Graphics_math_float_impl::point_2d_data_type result;
			result._X = lhs._X - rhs._X;
			result._Y = lhs._Y - rhs._Y;
			return result;
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::subtract(const typename _Graphics_math_float_impl::point_2d_data_type& lhs, float rhs) noexcept {
			_Graphics_math_float_impl::point_2d_data_type result;
			result._X = lhs._X - rhs;
			result._Y = lhs._Y - rhs;
			return result;
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::subtract(float lhs, const typename _Graphics_math_float_impl::point_2d_data_type& rhs) noexcept {
			_Graphics_math_float_impl::point_2d_data_type result;
			result._X = lhs - rhs._X;
			result._Y = lhs - rhs._Y;
			return result;
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::multiply(const typename _Graphics_math_float_impl::point_2d_data_type& lhs, const typename _Graphics_math_float_impl::point_2d_data_type& rhs) noexcept {
			_Graphics_math_float_impl::point_2d_data_type result;
			result._X = lhs._X * rhs._X;
			result._Y = lhs._Y * rhs._Y;
			return result;
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::multiply(const typename _Graphics_math_float_impl::point_2d_data_type& lhs, float rhs) noexcept {
			_Graphics_math_float_impl::point_2d_data_type result;
			result._X = lhs._X * rhs;
			result._Y = lhs._Y * rhs;
			return result;
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::multiply(float lhs, const typename _Graphics_math_float_impl::point_2d_data_type& rhs) noexcept {
			_Graphics_math_float_impl::point_2d_data_type result;
			result._X = lhs * rhs._X;
			result._Y = lhs * rhs._Y;
			return result;
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::divide(const typename _Graphics_math_float_impl::point_2d_data_type& lhs, const typename _Graphics_math_float_impl::point_2d_data_type& rhs) noexcept {
			_Graphics_math_float_impl::point_2d_data_type result;
			result._X = lhs._X / rhs._X;
			result._Y = lhs._Y / rhs._Y;
			return result;
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::divide(const typename _Graphics_math_float_impl::point_2d_data_type& lhs, float rhs) noexcept {
			_Graphics_math_float_impl::point_2d_data_type result;
			result._X = lhs._X / rhs;
			result._Y = lhs._Y / rhs;
			return result;
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::divide(float lhs, const typename _Graphics_math_float_impl::point_2d_data_type& rhs) noexcept {
			_Graphics_math_float_impl::point_2d_data_type result;
			result._X = lhs / rhs._X;
			result._Y = lhs / rhs._Y;
			return result;
		}

		inline bool _Graphics_math_float_impl::equal(const typename _Graphics_math_float_impl::point_2d_data_type& lhs, const typename _Graphics_math_float_impl::point_2d_data_type& rhs) noexcept {
			return lhs._X == rhs._X&& lhs._Y == rhs._Y;
		}

		inline bool _Graphics_math_float_impl::not_equal(const typename _Graphics_math_float_impl::point_2d_data_type& lhs, const typename _Graphics_math_float_impl::point_2d_data_type& rhs) noexcept {
			return !equal(lhs, rhs);
		}

		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::negate(const typename _Graphics_math_float_impl::point_2d_data_type& val) noexcept {
			return create_point_2d(-val._X, -val._Y);
		}

		inline typename _Graphics_math_float_impl::matrix_2d_data_type _Graphics_math_float_impl::create_matrix_2d() noexcept {
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
		inline typename _Graphics_math_float_impl::matrix_2d_data_type _Graphics_math_float_impl::create_matrix_2d(float v00, float v01, float v10, float v11, float v20, float v21) noexcept {
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
		inline void _Graphics_math_float_impl::m00(matrix_2d_data_type& mtx, float val) noexcept {
			mtx.m00 = val;
		}
		inline void _Graphics_math_float_impl::m01(matrix_2d_data_type& mtx, float val) noexcept {
			mtx.m01 = val;
		}
		inline void _Graphics_math_float_impl::m10(matrix_2d_data_type& mtx, float val) noexcept {
			mtx.m10 = val;
		}
		inline void _Graphics_math_float_impl::m11(matrix_2d_data_type& mtx, float val) noexcept {
			mtx.m11 = val;
		}
		inline void _Graphics_math_float_impl::m20(matrix_2d_data_type& mtx, float val) noexcept {
			mtx.m20 = val;
		}
		inline void _Graphics_math_float_impl::m21(matrix_2d_data_type& mtx, float val) noexcept {
			mtx.m21 = val;
		}
		inline float _Graphics_math_float_impl::m00(const matrix_2d_data_type& mtx) noexcept {
			return mtx.m00;
		}
		inline float _Graphics_math_float_impl::m01(const matrix_2d_data_type& mtx) noexcept {
			return mtx.m01;
		}
		inline float _Graphics_math_float_impl::m10(const matrix_2d_data_type& mtx) noexcept {
			return mtx.m10;
		}
		inline float _Graphics_math_float_impl::m11(const matrix_2d_data_type& mtx) noexcept {
			return mtx.m11;
		}
		inline float _Graphics_math_float_impl::m20(const matrix_2d_data_type& mtx) noexcept {
			return mtx.m20;
		}
		inline float _Graphics_math_float_impl::m21(const matrix_2d_data_type& mtx) noexcept {
			return mtx.m21;
		}
		inline typename _Graphics_math_float_impl::matrix_2d_data_type _Graphics_math_float_impl::create_translate(const typename _Graphics_math_float_impl::point_2d_data_type& val) noexcept {
			return create_matrix_2d(1.0f, 0.0f, 0.0f, 1.0f, val._X, val._Y);
		}
		inline typename _Graphics_math_float_impl::matrix_2d_data_type _Graphics_math_float_impl::create_scale(const typename _Graphics_math_float_impl::point_2d_data_type& val) noexcept {
			return create_matrix_2d(val._X, 0.0f, 0.0f, val._Y, 0.0f, 0.0f);
		}
		inline typename _Graphics_math_float_impl::matrix_2d_data_type _Graphics_math_float_impl::create_rotate(float radians) noexcept {
			float sine = sin(radians);
			float cosine = cos(radians);
			sine = _Round_floating_point_to_zero(sine);
			cosine = _Round_floating_point_to_zero(cosine);
			return create_matrix_2d(cosine, -sine, sine, cosine, 0.0f, 0.0f);
		}
		inline typename _Graphics_math_float_impl::matrix_2d_data_type _Graphics_math_float_impl::create_rotate(float radians, const typename _Graphics_math_float_impl::point_2d_data_type& origin) noexcept {
            return multiply(multiply(create_translate(negate(origin)), create_rotate(radians)), create_translate(origin));
		}
		inline typename _Graphics_math_float_impl::matrix_2d_data_type _Graphics_math_float_impl::create_reflect(float radians) noexcept {
			auto sine = sin(radians * 2.0f);
			auto cosine = cos(radians * 2.0f);
			sine = _Round_floating_point_to_zero(sine);
			cosine = _Round_floating_point_to_zero(cosine);
			return create_matrix_2d(cosine, sine, sine, -cosine, 0.0f, 0.0f);
		}
		inline typename _Graphics_math_float_impl::matrix_2d_data_type _Graphics_math_float_impl::create_shear_x(float factor) noexcept {
			return create_matrix_2d(1.0f, 0.0f, factor, 1.0f, 0.0f, 0.0f);
		}
		inline typename _Graphics_math_float_impl::matrix_2d_data_type _Graphics_math_float_impl::create_shear_y(float factor) noexcept {
			return create_matrix_2d(1.0f, factor, 0.0f, 1.0f, 0.0f, 0.0f);
		}
		inline void _Graphics_math_float_impl::translate(matrix_2d_data_type& mtx, const _Graphics_math_float_impl::point_2d_data_type& v) noexcept {
			mtx = multiply(mtx, create_translate(v));
		}
		inline void _Graphics_math_float_impl::scale(matrix_2d_data_type& mtx, const point_2d_data_type& scl) noexcept {
			mtx = multiply(mtx, create_scale(scl));
		}
		inline void _Graphics_math_float_impl::rotate(matrix_2d_data_type& mtx, float radians) noexcept {
			mtx = multiply(mtx, create_rotate(radians));
		}
		inline void _Graphics_math_float_impl::rotate(matrix_2d_data_type& mtx, float radians, const point_2d_data_type& origin) noexcept {
			mtx = multiply(mtx, create_rotate(radians, origin));
		}
		inline void _Graphics_math_float_impl::reflect(matrix_2d_data_type& mtx, float radians) noexcept {
			mtx = multiply(mtx, create_reflect(radians));
		}
		inline void _Graphics_math_float_impl::shear_x(matrix_2d_data_type& mtx, float factor) noexcept {
			mtx = multiply(mtx, create_shear_x(factor));
		}
		inline void _Graphics_math_float_impl::shear_y(matrix_2d_data_type& mtx, float factor) noexcept {
			mtx = multiply(mtx, create_shear_y(factor));
		}
		inline bool _Is_finite_check(float val) noexcept {
			float infinity = ::std::numeric_limits<float>::infinity();
			return val != infinity &&
				val != -infinity &&
				!(val != val);
			// This checks for both types of NaN. Compilers are not supposed to optimize this away but there were some in the past that incorrectly did. The only way to be sure is to check the documentation and any compiler switches you may be using.
		}
		inline bool _Graphics_math_float_impl::is_finite(const matrix_2d_data_type& mtx) noexcept {
			static_assert(::std::numeric_limits<float>::is_iec559 == true, "This implementation relies on IEEE 754 floating point behavior.");
			return ::std::numeric_limits<float>::is_iec559 &&
				_Is_finite_check(mtx.m00) &&
				_Is_finite_check(mtx.m01) &&
				_Is_finite_check(mtx.m10) &&
				_Is_finite_check(mtx.m11) &&
				_Is_finite_check(mtx.m20) &&
				_Is_finite_check(mtx.m21);
		}

		inline bool _Graphics_math_float_impl::is_invertible(const matrix_2d_data_type& mtx) noexcept {
			return (mtx.m00 * mtx.m11 - mtx.m01 * mtx.m10) != 0.0f;
		}

		inline float _Graphics_math_float_impl::determinant(const matrix_2d_data_type& mtx) noexcept {
			return mtx.m00 * mtx.m11 - mtx.m01 * mtx.m10;
		}

		inline _Graphics_math_float_impl::matrix_2d_data_type _Graphics_math_float_impl::inverse(const matrix_2d_data_type& mtx) noexcept {
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

		inline _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::transform_pt(const matrix_2d_data_type& mtx, const _Graphics_math_float_impl::point_2d_data_type& pt) noexcept {
			auto x = _Round_floating_point_to_zero(mtx.m00 * pt._X + mtx.m10 * pt._Y + mtx.m20);
			auto y = _Round_floating_point_to_zero(mtx.m01 * pt._X + mtx.m11 * pt._Y + mtx.m21);
			return create_point_2d(x, y);
		}

		inline _Graphics_math_float_impl::matrix_2d_data_type _Graphics_math_float_impl::multiply(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept {
			return create_matrix_2d(
				(lhs.m00 * rhs.m00) + (lhs.m01 * rhs.m10),
				(lhs.m00 * rhs.m01) + (lhs.m01 * rhs.m11),
				(lhs.m10 * rhs.m00) + (lhs.m11 * rhs.m10),
				(lhs.m10 * rhs.m01) + (lhs.m11 * rhs.m11),
				(lhs.m20 * rhs.m00) + (lhs.m21 * rhs.m10) + rhs.m20,
				(lhs.m20 * rhs.m01) + (lhs.m21 * rhs.m11) + rhs.m21
			);
		}

		inline bool _Graphics_math_float_impl::equal(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept {
			return lhs.m00 == rhs.m00 && lhs.m01 == rhs.m01 &&
				lhs.m10 == rhs.m10 && lhs.m11 == rhs.m11 &&
				lhs.m20 == rhs.m20 && lhs.m21 == rhs.m21;
		}

		inline bool _Graphics_math_float_impl::not_equal(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept {
			return !equal(lhs, rhs);
		}

		inline typename _Graphics_math_float_impl::display_point_data_type _Graphics_math_float_impl::create_display_point() noexcept {
			return display_point_data_type{ 0, 0 };
		}
		inline typename _Graphics_math_float_impl::display_point_data_type _Graphics_math_float_impl::create_display_point(int x, int y) noexcept {
			return display_point_data_type{ x, y };
		}
		inline void _Graphics_math_float_impl::x(typename _Graphics_math_float_impl::display_point_data_type& data, int x) noexcept {
			data.x = x;
		}
		inline void _Graphics_math_float_impl::y(typename _Graphics_math_float_impl::display_point_data_type& data, int y) noexcept {
			data.y = y;
		}
		inline int _Graphics_math_float_impl::x(const typename _Graphics_math_float_impl::display_point_data_type& data) noexcept {
			return data.x;
		}
		inline int _Graphics_math_float_impl::y(const typename _Graphics_math_float_impl::display_point_data_type& data) noexcept {
			return data.y;
		}
		inline bool _Graphics_math_float_impl::equal(const typename _Graphics_math_float_impl::display_point_data_type& lhs, const typename _Graphics_math_float_impl::display_point_data_type& rhs) noexcept {
			return lhs.x == rhs.x && lhs.y == rhs.y;
		}
		inline bool _Graphics_math_float_impl::not_equal(const typename _Graphics_math_float_impl::display_point_data_type& lhs, const typename _Graphics_math_float_impl::display_point_data_type& rhs) noexcept {
			return !(equal(lhs, rhs));
		}

		inline typename _Graphics_math_float_impl::bounding_box_data_type _Graphics_math_float_impl::create_bounding_box() noexcept {
			return bounding_box_data_type{ 0.0f, 0.0f, 0.0f, 0.0f };
		}
		inline typename _Graphics_math_float_impl::bounding_box_data_type _Graphics_math_float_impl::create_bounding_box(float x, float y, float width, float height) noexcept {
			return bounding_box_data_type{ x, y, width, height };
		}
		inline void _Graphics_math_float_impl::x(typename _Graphics_math_float_impl::bounding_box_data_type& bbox, float val) noexcept {
			bbox.x = val;
		}
		inline void _Graphics_math_float_impl::y(typename _Graphics_math_float_impl::bounding_box_data_type& bbox, float val) noexcept {
			bbox.y = val;
		}
		inline void _Graphics_math_float_impl::width(typename _Graphics_math_float_impl::bounding_box_data_type& bbox, float val) noexcept {
			bbox.width = val;
		}
		inline void _Graphics_math_float_impl::height(typename _Graphics_math_float_impl::bounding_box_data_type& bbox, float val) noexcept {
			bbox.height = val;
		}
		inline void _Graphics_math_float_impl::top_left(typename _Graphics_math_float_impl::bounding_box_data_type& bbox, const typename _Graphics_math_float_impl::point_2d_data_type& val) noexcept {
			bbox.x = val._X;
			bbox.y = val._Y;
		}
		inline void _Graphics_math_float_impl::bottom_right(typename _Graphics_math_float_impl::bounding_box_data_type& bbox, const typename _Graphics_math_float_impl::point_2d_data_type& val) noexcept {
			bbox.width = ::std::max(val._X - bbox.x, 0.0f);
			bbox.height = ::std::max(val._Y - bbox.y, 0.0f);
		}
		inline float _Graphics_math_float_impl::x(const typename _Graphics_math_float_impl::bounding_box_data_type& bbox) noexcept {
			return bbox.x;
		}
		inline float _Graphics_math_float_impl::y(const typename _Graphics_math_float_impl::bounding_box_data_type& bbox) noexcept {
			return bbox.y;
		}
		inline float _Graphics_math_float_impl::width(const typename _Graphics_math_float_impl::bounding_box_data_type& bbox) noexcept {
			return bbox.width;
		}
		inline float _Graphics_math_float_impl::height(const typename _Graphics_math_float_impl::bounding_box_data_type& bbox) noexcept {
			return bbox.height;
		}
		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::top_left(const typename _Graphics_math_float_impl::bounding_box_data_type& bbox) noexcept {
			return create_point_2d(bbox.x, bbox.y);
		}
		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::bottom_right(const typename _Graphics_math_float_impl::bounding_box_data_type& bbox) noexcept {
			return create_point_2d(bbox.x + bbox.width, bbox.y + bbox.height);
		}

		inline bool _Graphics_math_float_impl::equal(const typename _Graphics_math_float_impl::bounding_box_data_type& lhs, const typename _Graphics_math_float_impl::bounding_box_data_type& rhs) noexcept {
			return lhs.x == rhs.x && lhs.y == rhs.y && lhs.width == rhs.width && lhs.height == rhs.height;
		}
		inline bool _Graphics_math_float_impl::not_equal(const typename _Graphics_math_float_impl::bounding_box_data_type& lhs, const typename _Graphics_math_float_impl::bounding_box_data_type& rhs) noexcept {
			return !(equal(lhs, rhs));
		}

		inline typename _Graphics_math_float_impl::circle_data_type _Graphics_math_float_impl::create_circle() noexcept {
			return circle_data_type{ 0.0f, 0.0f, 0.0f };
		}
		inline typename _Graphics_math_float_impl::circle_data_type _Graphics_math_float_impl::create_circle(const typename _Graphics_math_float_impl::point_2d_data_type& ctr, float rad) noexcept {
			return circle_data_type{ ctr._X, ctr._Y, rad };
		}
		inline void _Graphics_math_float_impl::center(typename _Graphics_math_float_impl::circle_data_type& data, const point_2d_data_type& ctr) noexcept {
			data.x = ctr._X;
			data.y = ctr._Y;
		}
		inline void _Graphics_math_float_impl::radius(typename _Graphics_math_float_impl::circle_data_type& data, float r) noexcept {
			data.radius = r;
		}
		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::center(const typename _Graphics_math_float_impl::circle_data_type& data) noexcept {
			return point_2d_data_type{ data.x, data.y };
		}
		inline float _Graphics_math_float_impl::radius(const typename _Graphics_math_float_impl::circle_data_type& data) noexcept {
			return data.radius;
		}
		inline bool _Graphics_math_float_impl::equal(const typename _Graphics_math_float_impl::circle_data_type& lhs, const typename _Graphics_math_float_impl::circle_data_type& rhs) noexcept {
			return lhs.radius == rhs.radius && lhs.x == rhs.x && lhs.y == rhs.y;
		}
		inline bool _Graphics_math_float_impl::not_equal(const typename _Graphics_math_float_impl::circle_data_type& lhs, const typename _Graphics_math_float_impl::circle_data_type& rhs) noexcept {
			return !(equal(lhs, rhs));
		}
		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::point_for_angle(float ang, float mgn) noexcept {
			auto v = create_point_2d(mgn, 0.0f);
			auto m = create_rotate(ang);
			auto result = transform_pt(m, v);
			result._X = _Round_floating_point_to_zero(result._Y);
			result._Y = _Round_floating_point_to_zero(result._Y);
			return result;
		}
		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::point_for_angle(float ang, const point_2d_data_type& rad) noexcept {
			auto v = create_point_2d(1.0f, 0.0f);
			auto m = create_rotate(ang);
			auto result = transform_pt(m, v);
			result = multiply(result, rad);
			result._X = _Round_floating_point_to_zero(result._X);
			result._X = _Round_floating_point_to_zero(result._Y);
			return result;
		}
		inline float _Graphics_math_float_impl::angle_for_point(const point_2d_data_type& ctr, const point_2d_data_type& pt) noexcept {
			auto xDiff = pt._X - ctr._X;
			auto yDiff = -(pt._Y - ctr._Y);
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
		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::arc_start(const point_2d_data_type& ctr, float sang, const point_2d_data_type& rad, const matrix_2d_data_type& m) noexcept {
			auto lmtx = m;
			lmtx.m20 = 0.0f; lmtx.m21 = 0.0f; // Eliminate translation.
			auto pt = point_for_angle(sang, rad);
			//return ctr + pt * lmtx;
			return add(ctr, transform_pt(lmtx, pt));
		}
		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::arc_center(const point_2d_data_type& cpt, float sang, const point_2d_data_type& rad, const matrix_2d_data_type& m) noexcept {
			auto lmtx = m;
			lmtx.m20 = 0.0f; lmtx.m21 = 0.0f; // Eliminate translation.
			auto centerOffset = point_for_angle(two_pi<float> -sang, rad);
			centerOffset._Y = -centerOffset._Y;
			return subtract(cpt, transform_pt(lmtx, centerOffset));
		}
		inline typename _Graphics_math_float_impl::point_2d_data_type _Graphics_math_float_impl::arc_end(const point_2d_data_type& cpt, float eang, const point_2d_data_type& rad, const matrix_2d_data_type& m) noexcept {
			auto lmtx = m;
			auto tfrm = create_rotate(eang);
			lmtx.m20 = 0.0f; lmtx.m21 = 0.0f; // Eliminate translation.
			auto pt = transform_pt(tfrm, rad);
			pt._Y = -pt._Y;
			return add(cpt, transform_pt(lmtx, pt));
		}
	}
}
