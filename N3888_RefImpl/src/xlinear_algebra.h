#pragma once

namespace std::experimental::io2d {
	inline namespace v1 {

		class point_2d {
			float _X = 0.0f;
			float _Y = 0.0f;
		public:
			// \ref{\iotwod.\pointtwod.cons}, constructors:
			constexpr point_2d() noexcept;
			constexpr point_2d(float x, float y) noexcept;

			constexpr void x(float value) noexcept;
			constexpr void y(float value) noexcept;

			constexpr float x() const noexcept;
			constexpr float y() const noexcept;

			// \ref{\iotwod.\pointtwod.observers}, observers:
			constexpr float dot(const point_2d& other) const noexcept;
			float magnitude() const noexcept;
			constexpr float magnitude_squared() const noexcept;
			float angular_direction() const noexcept;
			point_2d to_unit() const noexcept;
			constexpr point_2d zero() const noexcept;

			// \ref{\iotwod.\pointtwod.member.ops}, member operators:
			constexpr point_2d& operator+=(const point_2d& rhs) noexcept;
			constexpr point_2d& operator-=(const point_2d& rhs) noexcept;
			constexpr point_2d& operator*=(float rhs) noexcept;
			constexpr point_2d& operator*=(const point_2d& rhs) noexcept;
			constexpr point_2d& operator/=(float rhs) noexcept;
			constexpr point_2d& operator/=(const point_2d& rhs) noexcept;
		};
		constexpr bool operator==(const point_2d& lhs, const point_2d& rhs)
			noexcept;
		constexpr bool operator!=(const point_2d& lhs, const point_2d& rhs)
			noexcept;
		constexpr point_2d operator+(const point_2d& lhs) noexcept;
		constexpr point_2d operator+(const point_2d& lhs, const point_2d& rhs)
			noexcept;
		constexpr point_2d operator-(const point_2d& lhs) noexcept;
		constexpr point_2d operator-(const point_2d& lhs, const point_2d& rhs)
			noexcept;
		constexpr point_2d operator*(const point_2d& lhs, float rhs) noexcept;
		constexpr point_2d operator*(float lhs, const point_2d& rhs) noexcept;

		class matrix_2d {
			float _M00 = 1.0F;
			float _M01 = 0.0F;
			float _M10 = 0.0F;
			float _M11 = 1.0F;
			float _M20 = 0.0F;
			float _M21 = 0.0F;

		public:
			constexpr matrix_2d() noexcept
				: matrix_2d(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f) {}
			constexpr matrix_2d(float m00, float m01, float m10, float m11, float m20, float m21) noexcept {
				_M00 = m00;
				_M01 = m01;
				_M10 = m10;
				_M11 = m11;
				_M20 = m20;
				_M21 = m21;
			}

			constexpr void m00(float value) noexcept;
			constexpr void m01(float value) noexcept;
			constexpr void m10(float value) noexcept;
			constexpr void m11(float value) noexcept;
			constexpr void m20(float value) noexcept;
			constexpr void m21(float value) noexcept;

			constexpr float m00() const noexcept;
			constexpr float m01() const noexcept;
			constexpr float m10() const noexcept;
			constexpr float m11() const noexcept;
			constexpr float m20() const noexcept;
			constexpr float m21() const noexcept;

			// \ref{\iotwod.\matrixtwod.staticfactories}, static factory functions:
			constexpr static matrix_2d init_translate(const point_2d& value) noexcept {
				return{ 1.0F, 0.0F, 0.0F, 1.0F, value.x(), value.y() };
			}
			constexpr static matrix_2d init_scale(const point_2d& value) noexcept {
				return{ value.x(), 0.0F, 0.0F, value.y(), 0.0F, 0.0F };
			}
			static matrix_2d init_rotate(float radians) noexcept {
				auto sine = sin(radians);
				auto cosine = cos(radians);
				sine = _Round_floating_point_to_zero(sine);
				cosine = _Round_floating_point_to_zero(cosine);
				return{ cosine, -sine, sine, cosine, 0.0F, 0.0F };
			}
			static matrix_2d init_reflect(float radians) noexcept {
				auto sine = sin(radians * 2.0F);
				auto cosine = cos(radians * 2.0F);
				sine = _Round_floating_point_to_zero(sine);
				cosine = _Round_floating_point_to_zero(cosine);
				return{ cosine, sine, sine, -cosine, 0.0F, 0.0F };
			}
			constexpr static matrix_2d init_shear_x(float factor) noexcept {
				return{ 1.0F, 0.0F, factor, 1.0F, 0.0F, 0.0F };
			}
			constexpr static matrix_2d init_shear_y(float factor) noexcept {
				return{ 1.0F, factor, 0.0F, 1.0F, 0.0F, 0.0F };
			}

			// \ref{\iotwod.\matrixtwod.modifiers}, modifiers:
			constexpr matrix_2d& translate(point_2d v) noexcept;
			constexpr matrix_2d& scale(point_2d v) noexcept;
			matrix_2d& rotate(float radians) noexcept;
			matrix_2d& rotate(float radians, point_2d origin) noexcept;
			matrix_2d& reflect(float radians) noexcept;
			constexpr matrix_2d& shear_x(float factor) noexcept;
			constexpr matrix_2d& shear_y(float factor) noexcept;

			// \ref{\iotwod.\matrixtwod.observers}, observers:
			constexpr bool is_finite() const noexcept;
			constexpr bool is_invertible() const noexcept;
			constexpr float determinant() const noexcept;
			constexpr matrix_2d inverse() const noexcept;
			constexpr point_2d transform_pt(point_2d pt) const noexcept;

			// \ref{\iotwod.\matrixtwod.member.ops}, matrix_2d member operators:
			constexpr matrix_2d& operator*=(const matrix_2d& rhs) noexcept;
		};

		// \ref{\iotwod.\matrixtwod.ops}, matrix_2d non-member operators:
		constexpr matrix_2d operator*(const matrix_2d& lhs, const matrix_2d& rhs)
			noexcept;
		constexpr bool operator==(const matrix_2d& lhs, const matrix_2d& rhs)
			noexcept;
		constexpr bool operator!=(const matrix_2d& lhs, const matrix_2d& rhs)
			noexcept;
		constexpr point_2d operator*(point_2d v, const matrix_2d& m)
			noexcept;
		constexpr matrix_2d operator*(const matrix_2d& lhs, const matrix_2d& rhs)
			noexcept;
		constexpr bool operator==(const matrix_2d& lhs, const matrix_2d& rhs)
			noexcept;
		constexpr bool operator!=(const matrix_2d& lhs, const matrix_2d& rhs)
			noexcept;

	}
}