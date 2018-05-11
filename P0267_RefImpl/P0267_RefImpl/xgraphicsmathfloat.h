#pragma once

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				struct _Graphics_math_float_impl {
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

					static matrix_2d_data_type create_matrix_2d() noexcept;
					static matrix_2d_data_type create_matrix_2d(float v00, float v01, float v10, float v11, float v20, float v21) noexcept;
					static void m00(matrix_2d_data_type& mtx, float val) noexcept;
					static void m01(matrix_2d_data_type& mtx, float val) noexcept;
					static void m10(matrix_2d_data_type& mtx, float val) noexcept;
					static void m11(matrix_2d_data_type& mtx, float val) noexcept;
					static void m20(matrix_2d_data_type& mtx, float val) noexcept;
					static void m21(matrix_2d_data_type& mtx, float val) noexcept;
					static float m00(const matrix_2d_data_type& mtx) noexcept;
					static float m01(const matrix_2d_data_type& mtx) noexcept;
					static float m10(const matrix_2d_data_type& mtx) noexcept;
					static float m11(const matrix_2d_data_type& mtx) noexcept;
					static float m20(const matrix_2d_data_type& mtx) noexcept;
					static float m21(const matrix_2d_data_type& mtx) noexcept;

					// \ref{\iotwod.\matrixtwod.staticfactories}, static factory functions:
					static matrix_2d_data_type create_translate(const point_2d_data_type& value) noexcept;

					static matrix_2d_data_type create_scale(const point_2d_data_type& value) noexcept;

					static matrix_2d_data_type create_rotate(float radians) noexcept;

					static matrix_2d_data_type create_rotate(float radians, const point_2d_data_type& origin) noexcept;

					static matrix_2d_data_type create_reflect(float radians) noexcept;

					static matrix_2d_data_type create_shear_x(float factor) noexcept;

					static matrix_2d_data_type create_shear_y(float factor) noexcept;

					// \ref{\iotwod.\matrixtwod.modifiers}, modifiers:
					static void translate(matrix_2d_data_type& mtx, const point_2d_data_type& v) noexcept;
					static void scale(matrix_2d_data_type& mtx, const point_2d_data_type& v) noexcept;
					static void rotate(matrix_2d_data_type& mtx, float radians) noexcept;
					static void rotate(matrix_2d_data_type& mtx, float radians, const point_2d_data_type& origin) noexcept;
					static void reflect(matrix_2d_data_type& mtx, float radians) noexcept;
					static void shear_x(matrix_2d_data_type& mtx, float factor) noexcept;
					static void shear_y(matrix_2d_data_type& mtx, float factor) noexcept;

					// \ref{\iotwod.\matrixtwod.observers}, observers:
					static bool is_finite(const matrix_2d_data_type& mtx) noexcept;
					static bool is_invertible(const matrix_2d_data_type& mtx) noexcept;
					static float determinant(const matrix_2d_data_type& mtx) noexcept;
					static matrix_2d_data_type inverse(const matrix_2d_data_type& mtx) noexcept;
					static point_2d_data_type transform_pt(const matrix_2d_data_type& mtx, const point_2d_data_type& pt) noexcept;

					static matrix_2d_data_type multiply(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept;

					static bool equal(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept;
					static bool not_equal(const matrix_2d_data_type& lhs, const matrix_2d_data_type& rhs) noexcept;

					// display_point
					struct _Display_point_data {
						int x;
						int y;
					};

					using display_point_data_type = _Display_point_data;

					static display_point_data_type create_display_point() noexcept;
					static display_point_data_type create_display_point(int x, int y) noexcept;
					static void x(display_point_data_type& data, int x) noexcept;
					static void y(display_point_data_type& data, int y) noexcept;

					static int x(const display_point_data_type& data) noexcept;
					static int y(const display_point_data_type& data) noexcept;

					static bool equal(const display_point_data_type& lhs, const display_point_data_type& rhs) noexcept;
					static bool not_equal(const display_point_data_type& lhs, const display_point_data_type& rhs) noexcept;

					// bounding_box
					struct _Bounding_box_data {
						float x;
						float y;
						float width;
						float height;
					};

					using bounding_box_data_type = _Bounding_box_data;

					static bounding_box_data_type create_bounding_box() noexcept;
					static bounding_box_data_type create_bounding_box(float x, float y, float width, float height) noexcept;
					static void x(bounding_box_data_type& bbox, float val) noexcept;
					static void y(bounding_box_data_type& bbox, float val) noexcept;
					static void width(bounding_box_data_type& bbox, float val) noexcept;
					static void height(bounding_box_data_type& bbox, float val) noexcept;
					static void top_left(bounding_box_data_type& bbox, const point_2d_data_type& val) noexcept;
					static void bottom_right(bounding_box_data_type& bbox, const point_2d_data_type& val) noexcept;

					static float x(const bounding_box_data_type& bbox) noexcept;
					static float y(const bounding_box_data_type& bbox) noexcept;
					static float width(const bounding_box_data_type& bbox) noexcept;
					static float height(const bounding_box_data_type& bbox) noexcept;
					static point_2d_data_type top_left(const bounding_box_data_type& bbox) noexcept;
					static point_2d_data_type bottom_right(const bounding_box_data_type& bbox) noexcept;

					static bool equal(const bounding_box_data_type& lhs, const bounding_box_data_type& rhs) noexcept;
					static bool not_equal(const bounding_box_data_type& lhs, const bounding_box_data_type& rhs) noexcept;

					// circle
					struct _Circle_data {
						float x;
						float y;
						float radius;
					};

					using circle_data_type = _Circle_data;
					static circle_data_type create_circle() noexcept;
					static circle_data_type create_circle(const point_2d_data_type& ctr, float rad) noexcept;

					static void center(circle_data_type& data, const point_2d_data_type& ctr) noexcept;
					static void radius(circle_data_type& data, float r) noexcept;

					static point_2d_data_type center(const circle_data_type& data) noexcept;
					static float radius(const circle_data_type& data) noexcept;

					static bool equal(const circle_data_type& lhs, const circle_data_type& rhs) noexcept;
					static bool not_equal(const circle_data_type& lhs, const circle_data_type& rhs) noexcept;

					static point_2d_data_type point_for_angle(float ang, float mgn) noexcept;
					static point_2d_data_type point_for_angle(float ang, const point_2d_data_type& rad) noexcept;
					static float angle_for_point(const point_2d_data_type& ctr, const point_2d_data_type& pt) noexcept;
					static point_2d_data_type arc_start(const point_2d_data_type& ctr, float sang, const point_2d_data_type& rad, const matrix_2d_data_type& m) noexcept;
					static point_2d_data_type arc_center(const point_2d_data_type& cpt, float sang, const point_2d_data_type& rad, const matrix_2d_data_type& m) noexcept;
					static point_2d_data_type arc_end(const point_2d_data_type& cpt, float eang, const point_2d_data_type& rad, const matrix_2d_data_type& m) noexcept;
				};
			}
		}
	}
}