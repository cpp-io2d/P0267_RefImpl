#pragma once

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				template <class GraphicsMath>
				class basic_point_2d {
				public:
					using _Data_type = typename GraphicsMath::point_2d_data_type;
				private:
					_Data_type _Data;
				public:
					constexpr const _Data_type& _Get_data() const noexcept;
					constexpr basic_point_2d(const _Data_type& val) noexcept;

					// \ref{\iotwod.\pointtwod.cons}, constructors:
					constexpr basic_point_2d() noexcept;
					constexpr basic_point_2d(float xval, float yval) noexcept;

					constexpr void x(float val) noexcept;
					constexpr void y(float val) noexcept;
					constexpr float x() const noexcept;
					constexpr float y() const noexcept;

					// \ref{\iotwod.\pointtwod.observers}, observers:
					constexpr float dot(const basic_point_2d& other) const noexcept;
					float magnitude() const noexcept;
					constexpr float magnitude_squared() const noexcept;
					float angular_direction() const noexcept;
					basic_point_2d to_unit() const noexcept;
					constexpr basic_point_2d zero() noexcept;

					// \ref{\iotwod.\pointtwod.member.ops}, member operators:
					constexpr basic_point_2d& operator+=(const basic_point_2d& rhs) noexcept;
					constexpr basic_point_2d& operator+=(float rhs) noexcept;
					constexpr basic_point_2d& operator-=(const basic_point_2d& rhs) noexcept;
					constexpr basic_point_2d& operator-=(float rhs) noexcept;
					constexpr basic_point_2d& operator*=(const basic_point_2d& rhs) noexcept;
					constexpr basic_point_2d& operator*=(float rhs) noexcept;
					constexpr basic_point_2d& operator/=(const basic_point_2d& rhs) noexcept;
					constexpr basic_point_2d& operator/=(float rhs) noexcept;
				};

				template <class GraphicsMath>
				class basic_matrix_2d {
				public:
					using _Data_type = typename GraphicsMath::matrix_2d_data_type;
				private:
					_Data_type _Data;
				public:
					constexpr const _Data_type& _Get_data() const noexcept;
					constexpr basic_matrix_2d(const _Data_type& val) noexcept;

					constexpr basic_matrix_2d() noexcept;
					constexpr basic_matrix_2d(float v00, float v01, float v10, float v11, float v20, float v21) noexcept;

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
					constexpr static basic_matrix_2d init_translate(const basic_point_2d<GraphicsMath>& val) noexcept;
					constexpr static basic_matrix_2d init_scale(const basic_point_2d<GraphicsMath>& val) noexcept;
					static basic_matrix_2d init_rotate(float radians) noexcept;
					static basic_matrix_2d init_rotate(float radians, const basic_point_2d<GraphicsMath>& origin) noexcept;
					static basic_matrix_2d init_reflect(float radians) noexcept;
					constexpr static basic_matrix_2d init_shear_x(float factor) noexcept;
					constexpr static basic_matrix_2d init_shear_y(float factor) noexcept;

					// \ref{\iotwod.\matrixtwod.modifiers}, modifiers:
					constexpr basic_matrix_2d& translate(const basic_point_2d<GraphicsMath>& v) noexcept;
					constexpr basic_matrix_2d& scale(const basic_point_2d<GraphicsMath>& v) noexcept;
					basic_matrix_2d& rotate(float radians) noexcept;
					basic_matrix_2d& rotate(float radians, const basic_point_2d<GraphicsMath>& origin) noexcept;
					basic_matrix_2d& reflect(float radians) noexcept;
					constexpr basic_matrix_2d& shear_x(float factor) noexcept;
					constexpr basic_matrix_2d& shear_y(float factor) noexcept;

					// \ref{\iotwod.\matrixtwod.observers}, observers:
					constexpr bool is_finite() const noexcept;
					constexpr bool is_invertible() const noexcept;
					constexpr float determinant() const noexcept;
					constexpr basic_matrix_2d inverse() const noexcept;
					constexpr basic_point_2d<GraphicsMath> transform_pt(const basic_point_2d<GraphicsMath>& pt) const noexcept;

					constexpr basic_matrix_2d& operator*=(const basic_matrix_2d& other) noexcept;
				};

				template <class GraphicsMath>
				class basic_display_point {
				public:
					using _Data_type = typename GraphicsMath::display_point_data_type;
				private:
					_Data_type _Data;
				public:
					constexpr const _Data_type& _Get_data() const noexcept;
					constexpr basic_display_point(const _Data_type& val) noexcept;

					// \ref{\iotwod.\pointtwod.cons}, constructors:
					constexpr basic_display_point() noexcept;
					constexpr basic_display_point(int xval, int yval) noexcept;

					constexpr void x(int val) noexcept;
					constexpr void y(int val) noexcept;
					constexpr int x() const noexcept;
					constexpr int y() const noexcept;
				};

				template <class GraphicsMath>
				constexpr bool operator==(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				constexpr bool operator!=(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				constexpr basic_point_2d<GraphicsMath> operator+(const basic_point_2d<GraphicsMath>& val) noexcept;
				template <class GraphicsMath>
				constexpr basic_point_2d<GraphicsMath> operator+(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				constexpr basic_point_2d<GraphicsMath> operator-(const basic_point_2d<GraphicsMath>& val) noexcept;
				template <class GraphicsMath>
				constexpr basic_point_2d<GraphicsMath> operator-(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				constexpr basic_point_2d<GraphicsMath> operator*(const basic_point_2d<GraphicsMath>& lhs, float rhs) noexcept;
				template <class GraphicsMath>
				constexpr basic_point_2d<GraphicsMath> operator*(float lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				constexpr basic_point_2d<GraphicsMath> operator*(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				constexpr basic_point_2d<GraphicsMath> operator/(const basic_point_2d<GraphicsMath>& lhs, float rhs) noexcept;
				template <class GraphicsMath>
				constexpr basic_point_2d<GraphicsMath> operator/(float lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				constexpr basic_point_2d<GraphicsMath> operator/(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;

				//using point_2d = typename basic_linear_algebra<_Point_2d_float_impl, _Matrix_2d_float_impl>::point_2d;

				template <class GraphicsMath>
				constexpr basic_matrix_2d<GraphicsMath> operator*(const basic_matrix_2d<GraphicsMath>& lhs, const basic_matrix_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				constexpr basic_point_2d<GraphicsMath> operator*(const basic_point_2d<GraphicsMath>& lhs, const basic_matrix_2d<GraphicsMath>& rhs) noexcept;

				template <class GraphicsMath>
				constexpr bool operator==(const basic_matrix_2d<GraphicsMath>& lhs, const basic_matrix_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				constexpr bool operator!=(const basic_matrix_2d<GraphicsMath>& lhs, const basic_matrix_2d<GraphicsMath>& rhs) noexcept;

				template <class GraphicsMath>
				constexpr bool operator==(const basic_display_point<GraphicsMath>& lhs, const basic_display_point<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				constexpr bool operator!=(const basic_display_point<GraphicsMath>& lhs, const basic_display_point<GraphicsMath>& rhs) noexcept;

				//using matrix_2d = typename basic_linear_algebra<_Point_2d_float_impl, _Matrix_2d_float_impl>::matrix_2d;

				struct _Linear_algebra_float_impl {
					// point_2d 
					struct _Point_2d_data {
						float _X;
						float _Y;
					};

					using point_2d_data_type = _Point_2d_data;

					static point_2d_data_type create_point_2d() noexcept;
					static point_2d_data_type create_point_2d(float x, float y) noexcept;

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

					// matrix_2d
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

					constexpr static matrix_2d_data_type create_matrix_2d() noexcept;
					constexpr static matrix_2d_data_type create_matrix_2d(float v00, float v01, float v10, float v11, float v20, float v21) noexcept;
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

					// \ref{\iotwod.\matrixtwod.staticfactories}, static factory functions:
					constexpr static matrix_2d_data_type init_identity() noexcept;

					constexpr static matrix_2d_data_type init_translate(const point_2d_data_type& value) noexcept;

					constexpr static matrix_2d_data_type init_scale(const point_2d_data_type& value) noexcept;

					static matrix_2d_data_type init_rotate(float radians) noexcept;

					static matrix_2d_data_type init_rotate(float radians, const point_2d_data_type& origin) noexcept;

					static matrix_2d_data_type init_reflect(float radians) noexcept;

					constexpr static matrix_2d_data_type init_shear_x(float factor) noexcept;

					constexpr static matrix_2d_data_type init_shear_y(float factor) noexcept;

					// \ref{\iotwod.\matrixtwod.modifiers}, modifiers:
					constexpr static void translate(matrix_2d_data_type& mtx, const point_2d_data_type& v) noexcept;
					constexpr static void scale(matrix_2d_data_type& mtx, const point_2d_data_type& v) noexcept;
					static void rotate(matrix_2d_data_type& mtx, float radians) noexcept;
					static void rotate(matrix_2d_data_type& mtx, float radians, const point_2d_data_type& origin) noexcept;
					static void reflect(matrix_2d_data_type& mtx, float radians) noexcept;
					constexpr static void shear_x(matrix_2d_data_type& mtx, float factor) noexcept;
					constexpr static void shear_y(matrix_2d_data_type& mtx, float factor) noexcept;

					// \ref{\iotwod.\matrixtwod.observers}, observers:
					constexpr static bool is_finite(const matrix_2d_data_type& mtx) noexcept;
					constexpr static bool is_invertible(const matrix_2d_data_type& mtx) noexcept;
					constexpr static float determinant(const matrix_2d_data_type& mtx) noexcept;
					constexpr static matrix_2d_data_type inverse(const matrix_2d_data_type& mtx) noexcept;
					constexpr static point_2d_data_type transform_pt(const matrix_2d_data_type& mtx, const point_2d_data_type& pt) noexcept;

					constexpr static matrix_2d_data_type multiply(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept;

					constexpr static bool equal(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept;
					constexpr static bool not_equal(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept;

					// display_point
					struct _Display_point_data {
						int x;
						int y;
					};

					using display_point_data_type = _Display_point_data;
					
					constexpr static display_point_data_type create_display_point();
					constexpr static display_point_data_type create_display_point(int x, int y) noexcept;
					constexpr static void x(display_point_data_type& data, int x) noexcept;
					constexpr static void y(display_point_data_type& data, int y) noexcept;

					constexpr static int x(const display_point_data_type& data) noexcept;
					constexpr static int y(const display_point_data_type& data) noexcept;

					constexpr static bool equal(const display_point_data_type& lhs, const display_point_data_type& rhs) noexcept;
					constexpr static bool not_equal(const display_point_data_type& lhs, const display_point_data_type& rhs) noexcept;

					// bounding_box
					struct _Bounding_box_data {
						float x;
						float y;
						float width;
						float height;
					};

					using bounding_box_data_type = _Bounding_box_data;

					constexpr static bounding_box_data_type create_bounding_box() noexcept;
					constexpr static bounding_box_data_type create_bounding_box(float x, float y, float width, float height) noexcept;
					constexpr static void x(bounding_box_data_type& bbox, float val) noexcept;
					constexpr static void y(bounding_box_data_type& bbox, float val) noexcept;
					constexpr static void width(bounding_box_data_type& bbox, float val) noexcept;
					constexpr static void height(bounding_box_data_type& bbox, float val) noexcept;
					constexpr static void top_left(bounding_box_data_type& bbox, const point_2d_data_type& val) noexcept;
					constexpr static void bottom_right(bounding_box_data_type& bbox, const point_2d_data_type& val) noexcept;

					constexpr static float x(const bounding_box_data_type& bbox) noexcept;
					constexpr static float y(const bounding_box_data_type& bbox) noexcept;
					constexpr static float width(const bounding_box_data_type& bbox) noexcept;
					constexpr static float height(const bounding_box_data_type& bbox) noexcept;
					constexpr static point_2d_data_type top_left(const bounding_box_data_type& bbox) noexcept;
					constexpr static point_2d_data_type bottom_right(const bounding_box_data_type& bbox) noexcept;

					constexpr static bool equal(const bounding_box_data_type& lhs, const bounding_box_data_type& rhs) noexcept;
					constexpr static bool not_equal(const bounding_box_data_type& lhs, const bounding_box_data_type& rhs) noexcept;

					// circle
					struct _Circle_data {
						float x;
						float y;
						float radius;
					};

					using circle_data_type = _Circle_data;
					constexpr static circle_data_type create_circle() noexcept;
					constexpr static circle_data_type create_circle(const point_2d_data_type& ctr, float rad) noexcept;

					constexpr static void center(circle_data_type& data, const point_2d_data_type& ctr) noexcept;
					constexpr static void radius(circle_data_type& data, float r) noexcept;

					constexpr static point_2d_data_type center(const circle_data_type& data) noexcept;
					constexpr static float radius(const circle_data_type& data) noexcept;

					constexpr static bool equal(const circle_data_type& lhs, const circle_data_type& rhs) noexcept;
					constexpr static bool not_equal(const circle_data_type& lhs, const circle_data_type& rhs) noexcept;
				};
			}
		}
	}
}