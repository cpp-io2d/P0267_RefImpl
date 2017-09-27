#pragma once

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				template <class LinearAlgebra>
				struct basic_linear_algebra {
					class point_2d {
					public:
						using data_type = typename LinearAlgebra::point_2d_data_type;
					private:
						data_type _Data;
					public:
						constexpr const data_type& _Get_data() const noexcept;
						constexpr point_2d(const data_type& val) noexcept;

						// \ref{\iotwod.\pointtwod.cons}, constructors:
						constexpr point_2d() noexcept;
						constexpr point_2d(float xval, float yval) noexcept;

						constexpr void x(float val) noexcept;
						constexpr void y(float val) noexcept;
						constexpr float x() const noexcept;
						constexpr float y() const noexcept;

						// \ref{\iotwod.\pointtwod.observers}, observers:
						constexpr float dot(const point_2d& other) const noexcept;
						float magnitude() const noexcept;
						constexpr float magnitude_squared() const noexcept;
						float angular_direction() const noexcept;
						point_2d to_unit() const noexcept;
						constexpr point_2d zero() noexcept;

						// \ref{\iotwod.\pointtwod.member.ops}, member operators:
						constexpr point_2d& operator+=(const point_2d& rhs) noexcept;
						constexpr point_2d& operator+=(float rhs) noexcept;
						constexpr point_2d& operator-=(const point_2d& rhs) noexcept;
						constexpr point_2d& operator-=(float rhs) noexcept;
						constexpr point_2d& operator*=(const point_2d& rhs) noexcept;
						constexpr point_2d& operator*=(float rhs) noexcept;
						constexpr point_2d& operator/=(const point_2d& rhs) noexcept;
						constexpr point_2d& operator/=(float rhs) noexcept;
					};

					class matrix_2d {
					public:
						using data_type = typename LinearAlgebra::matrix_2d_data_type;
					private:
						data_type _Data;
					public:
						constexpr const data_type& _Get_data() const noexcept;
						constexpr matrix_2d(const data_type& val) noexcept;

						constexpr matrix_2d() noexcept;
						constexpr matrix_2d(float v00, float v01, float v10, float v11, float v20, float v21) noexcept;

						constexpr void m00(float val) noexcept;
						constexpr void m01(float val) noexcept;
						constexpr void m10(float val) noexcept;
						constexpr void m11(float val) noexcept;
						constexpr void m20(float val) noexcept;
						constexpr void m21(float val) noexcept;

						constexpr float m00() const noexcept;
						constexpr float m01() const noexcept;
						constexpr float m10() const noexcept;
						constexpr float m11() const noexcept;
						constexpr float m20() const noexcept;
						constexpr float m21() const noexcept;

						// \ref{\iotwod.\matrixtwod.staticfactories}, static factory functions:
						constexpr static matrix_2d init_translate(const point_2d& val) noexcept;
						constexpr static matrix_2d init_scale(const point_2d& val) noexcept;
						static matrix_2d init_rotate(float radians) noexcept;
						static matrix_2d init_rotate(float radians, const point_2d& origin) noexcept;
						static matrix_2d init_reflect(float radians) noexcept;
						constexpr static matrix_2d init_shear_x(float factor) noexcept;
						constexpr static matrix_2d init_shear_y(float factor) noexcept;

						// \ref{\iotwod.\matrixtwod.modifiers}, modifiers:
						constexpr matrix_2d& translate(const point_2d& v) noexcept;
						constexpr matrix_2d& scale(const point_2d& v) noexcept;
						matrix_2d& rotate(float radians) noexcept;
						matrix_2d& rotate(float radians, const point_2d& origin) noexcept;
						matrix_2d& reflect(float radians) noexcept;
						constexpr matrix_2d& shear_x(float factor) noexcept;
						constexpr matrix_2d& shear_y(float factor) noexcept;

						// \ref{\iotwod.\matrixtwod.observers}, observers:
						constexpr bool is_finite() const noexcept;
						constexpr bool is_invertible() const noexcept;
						constexpr float determinant() const noexcept;
						constexpr matrix_2d inverse() const noexcept;
						constexpr point_2d transform_pt(const point_2d& pt) const noexcept;

						constexpr matrix_2d& operator*=(const matrix_2d& other) noexcept;
					};
				};

				template <class LinearAlgebra>
				constexpr bool operator==(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept;
				template <class LinearAlgebra>
				constexpr bool operator!=(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept;
				template <class LinearAlgebra>
				constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator+(const typename basic_linear_algebra<LinearAlgebra>::point_2d& val) noexcept;
				template <class LinearAlgebra>
				constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator+(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept;
				template <class LinearAlgebra>
				constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator-(const typename basic_linear_algebra<LinearAlgebra>::point_2d& val) noexcept;
				template <class LinearAlgebra>
				constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator-(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept;
				template <class LinearAlgebra>
				constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator*(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, float rhs) noexcept;
				template <class LinearAlgebra>
				constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator*(float lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept;
				template <class LinearAlgebra>
				constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator*(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept;
				template <class LinearAlgebra>
				constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator/(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, float rhs) noexcept;
				template <class LinearAlgebra>
				constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator/(float lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept;
				template <class LinearAlgebra>
				constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator/(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::point_2d& rhs) noexcept;

				//using point_2d = typename basic_linear_algebra<_Point_2d_float_impl, _Matrix_2d_float_impl>::point_2d;

				template <class LinearAlgebra>
				constexpr typename basic_linear_algebra<LinearAlgebra>::matrix_2d operator*(const typename basic_linear_algebra<LinearAlgebra>::matrix_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::matrix_2d& rhs) noexcept;
				template <class LinearAlgebra>
				constexpr typename basic_linear_algebra<LinearAlgebra>::point_2d operator*(const typename basic_linear_algebra<LinearAlgebra>::point_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::matrix_2d& rhs) noexcept;

				template <class LinearAlgebra>
				constexpr bool operator==(const typename basic_linear_algebra<LinearAlgebra>::matrix_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::matrix_2d& rhs) noexcept;
				template <class LinearAlgebra>
				constexpr bool operator!=(const typename basic_linear_algebra<LinearAlgebra>::matrix_2d& lhs, const typename basic_linear_algebra<LinearAlgebra>::matrix_2d& rhs) noexcept;

				//using matrix_2d = typename basic_linear_algebra<_Point_2d_float_impl, _Matrix_2d_float_impl>::matrix_2d;

				struct _Linear_algebra_float_impl {
					struct _Point_2d_data {
						float _X;
						float _Y;
					};

					using point_2d_data_type = _Point_2d_data;

					static point_2d_data_type create() noexcept;
					static point_2d_data_type create(float x, float y) noexcept;

					static void x(point_2d_data_type& val, float xval) noexcept;
					static void y(point_2d_data_type& val, float yval) noexcept;

					static float x(const point_2d_data_type& val) noexcept;
					static float y(const point_2d_data_type& val) noexcept;

					// \ref{\iotwod.\pointtwod.observers}, observers:
					static float dot(const point_2d_data_type& a, const point_2d_data_type& b) noexcept;
					static float magnitude(const point_2d_data_type& val) noexcept;
					static float magnitude_squared(const point_2d_data_type& val) noexcept;
					static float angular_direction(const point_2d_data_type& val) noexcept;
					static point_2d_data_type to_unit(const point_2d_data_type& val) noexcept;

					// \ref{\iotwod.\pointtwod.member.ops}, member operators:
					static point_2d_data_type add(const point_2d_data_type& lhs, const point_2d_data_type& rhs) noexcept;
					static point_2d_data_type add(const point_2d_data_type& lhs, float rhs) noexcept;
					static point_2d_data_type add(float lhs, const point_2d_data_type& rhs) noexcept;

					static point_2d_data_type subtract(const point_2d_data_type& lhs, const point_2d_data_type& rhs) noexcept;
					static point_2d_data_type subtract(const point_2d_data_type& lhs, float rhs) noexcept;
					static point_2d_data_type subtract(float lhs, const point_2d_data_type& rhs) noexcept;

					static point_2d_data_type multiply(const point_2d_data_type& lhs, const point_2d_data_type& rhs) noexcept;
					static point_2d_data_type multiply(const point_2d_data_type& lhs, float rhs) noexcept;
					static point_2d_data_type multiply(float lhs, const point_2d_data_type& rhs) noexcept;

					static point_2d_data_type divide(const point_2d_data_type& lhs, const point_2d_data_type& rhs) noexcept;
					static point_2d_data_type divide(const point_2d_data_type& lhs, float rhs) noexcept;
					static point_2d_data_type divide(float lhs, const point_2d_data_type& rhs) noexcept;

					static bool equal(const point_2d_data_type& lhs, const point_2d_data_type& rhs) noexcept;
					static bool not_equal(const point_2d_data_type& lhs, const point_2d_data_type& rhs) noexcept;
					static point_2d_data_type negate(const point_2d_data_type& val) noexcept;

				private:
					struct _Matrix_2d_data {
						float m00;
						float m01;
						float m02;
						float m10;
						float m11;
						float m12;
						float m20;
						float m21;
						float m22;
					};
				public:
					using matrix_2d_data_type = _Matrix_2d_data;

					constexpr static void m00(matrix_2d_data_type& mtx, float val) noexcept;
					constexpr static void m01(matrix_2d_data_type& mtx, float val) noexcept;
					constexpr static void m10(matrix_2d_data_type& mtx, float val) noexcept;
					constexpr static void m11(matrix_2d_data_type& mtx, float val) noexcept;
					constexpr static void m20(matrix_2d_data_type& mtx, float val) noexcept;
					constexpr static void m21(matrix_2d_data_type& mtx, float val) noexcept;
					constexpr static float m00(const matrix_2d_data_type& mtx) noexcept;
					constexpr static float m01(const matrix_2d_data_type& mtx) noexcept;
					constexpr static float m10(const matrix_2d_data_type& mtx) noexcept;
					constexpr static float m11(const matrix_2d_data_type& mtx) noexcept;
					constexpr static float m20(const matrix_2d_data_type& mtx) noexcept;
					constexpr static float m21(const matrix_2d_data_type& mtx) noexcept;
					constexpr static matrix_2d_data_type init_elements(float v00, float v01, float v10, float v11, float v20, float v21) noexcept;

					// \ref{\iotwod.\matrixtwod.staticfactories}, static factory functions:
					constexpr static matrix_2d_data_type init_identity() noexcept;

					template <class Point2d>
					constexpr static matrix_2d_data_type init_translate(const Point2d& value) noexcept;

					template <class Point2d>
					constexpr static matrix_2d_data_type init_scale(const Point2d& value) noexcept;

					static matrix_2d_data_type init_rotate(float radians) noexcept;

					template <class Point2d>
					static matrix_2d_data_type init_rotate(float radians, const Point2d& origin) noexcept;

					static matrix_2d_data_type init_reflect(float radians) noexcept;

					constexpr static matrix_2d_data_type init_shear_x(float factor) noexcept;

					constexpr static matrix_2d_data_type init_shear_y(float factor) noexcept;

					// \ref{\iotwod.\matrixtwod.modifiers}, modifiers:
					template <class Point2d>
					constexpr static void translate(matrix_2d_data_type& mtx, const Point2d& v) noexcept;
					template <class Point2d>
					constexpr static void scale(matrix_2d_data_type& mtx, const Point2d& v) noexcept;
					static void rotate(matrix_2d_data_type& mtx, float radians) noexcept;
					template <class Point2d>
					static void rotate(matrix_2d_data_type& mtx, float radians, const Point2d& origin) noexcept;
					static void reflect(matrix_2d_data_type& mtx, float radians) noexcept;
					constexpr static void shear_x(matrix_2d_data_type& mtx, float factor) noexcept;
					constexpr static void shear_y(matrix_2d_data_type& mtx, float factor) noexcept;

					// \ref{\iotwod.\matrixtwod.observers}, observers:
					constexpr static bool is_finite(const matrix_2d_data_type& mtx) noexcept;
					constexpr static bool is_invertible(const matrix_2d_data_type& mtx) noexcept;
					constexpr static float determinant(const matrix_2d_data_type& mtx) noexcept;
					constexpr static matrix_2d_data_type inverse(const matrix_2d_data_type& mtx) noexcept;
					template <class Point2d>
					constexpr static Point2d transform_pt(const matrix_2d_data_type& mtx, const Point2d& pt) noexcept;

					constexpr static matrix_2d_data_type multiply(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept;

					constexpr static bool equal(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept;
					constexpr static bool not_equal(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept;
				};
			}
		}
	}
}