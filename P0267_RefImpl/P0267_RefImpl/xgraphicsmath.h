#pragma once

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				template <class GraphicsMath>
				class basic_point_2d {
				public:
					using data_type = typename GraphicsMath::point_2d_data_type;
				private:
					data_type _Data;
				public:
					const data_type& data() const noexcept;
					data_type& data() noexcept;

					// \ref{\iotwod.\pointtwod.cons}, constructors:
					basic_point_2d() noexcept;
					basic_point_2d(float xval, float yval) noexcept;
					basic_point_2d(const typename GraphicsMath::point_2d_data_type& data) noexcept;

					void x(float val) noexcept;
					void y(float val) noexcept;
					float x() const noexcept;
					float y() const noexcept;

					// \ref{\iotwod.\pointtwod.observers}, observers:
					float dot(const basic_point_2d& other) const noexcept;
					float magnitude() const noexcept;
					float magnitude_squared() const noexcept;
					float angular_direction() const noexcept;
					basic_point_2d to_unit() const noexcept;
					//basic_point_2d zero() noexcept;

					// \ref{\iotwod.\pointtwod.member.ops}, member operators:
					basic_point_2d& operator+=(const basic_point_2d& rhs) noexcept;
					basic_point_2d& operator+=(float rhs) noexcept;
					basic_point_2d& operator-=(const basic_point_2d& rhs) noexcept;
					basic_point_2d& operator-=(float rhs) noexcept;
					basic_point_2d& operator*=(const basic_point_2d& rhs) noexcept;
					basic_point_2d& operator*=(float rhs) noexcept;
					basic_point_2d& operator/=(const basic_point_2d& rhs) noexcept;
					basic_point_2d& operator/=(float rhs) noexcept;
				};

				template <class GraphicsMath>
				bool operator==(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> operator+(const basic_point_2d<GraphicsMath>& val) noexcept;
				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> operator+(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> operator-(const basic_point_2d<GraphicsMath>& val) noexcept;
				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> operator-(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> operator*(const basic_point_2d<GraphicsMath>& lhs, float rhs) noexcept;
				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> operator*(float lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> operator*(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> operator/(const basic_point_2d<GraphicsMath>& lhs, float rhs) noexcept;
				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> operator/(float lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> operator/(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept;

				template <class GraphicsMath>
				class basic_matrix_2d {
				public:
					using data_type = typename GraphicsMath::matrix_2d_data_type;
				private:
					data_type _Data;
				public:
					const data_type& data() const noexcept;
					data_type& data() noexcept;

					basic_matrix_2d() noexcept;
					basic_matrix_2d(float v00, float v01, float v10, float v11, float v20, float v21) noexcept;
					basic_matrix_2d(const typename GraphicsMath::matrix_2d_data_type& val) noexcept;

					void m00(float val) noexcept;
					void m01(float val) noexcept;
					void m10(float val) noexcept;
					void m11(float val) noexcept;
					void m20(float val) noexcept;
					void m21(float val) noexcept;

					float m00() const noexcept;
					float m01() const noexcept;
					float m10() const noexcept;
					float m11() const noexcept;
					float m20() const noexcept;
					float m21() const noexcept;

					// \ref{\iotwod.\matrixtwod.staticfactories}, static factory functions:
					static basic_matrix_2d create_translate(const basic_point_2d<GraphicsMath>& val) noexcept;
					static basic_matrix_2d create_scale(const basic_point_2d<GraphicsMath>& val) noexcept;
					static basic_matrix_2d create_rotate(float radians) noexcept;
					static basic_matrix_2d create_rotate(float radians, const basic_point_2d<GraphicsMath>& origin) noexcept;
					static basic_matrix_2d create_reflect(float radians) noexcept;
					static basic_matrix_2d create_shear_x(float factor) noexcept;
					static basic_matrix_2d create_shear_y(float factor) noexcept;

					// \ref{\iotwod.\matrixtwod.modifiers}, modifiers:
					basic_matrix_2d& translate(const basic_point_2d<GraphicsMath>& v) noexcept;
					basic_matrix_2d& scale(const basic_point_2d<GraphicsMath>& v) noexcept;
					basic_matrix_2d& rotate(float radians) noexcept;
					basic_matrix_2d& rotate(float radians, const basic_point_2d<GraphicsMath>& origin) noexcept;
					basic_matrix_2d& reflect(float radians) noexcept;
					basic_matrix_2d& shear_x(float factor) noexcept;
					basic_matrix_2d& shear_y(float factor) noexcept;

					// \ref{\iotwod.\matrixtwod.observers}, observers:
					bool is_finite() const noexcept;
					bool is_invertible() const noexcept;
					float determinant() const noexcept;
					basic_matrix_2d inverse() const noexcept;
					basic_point_2d<GraphicsMath> transform_pt(const basic_point_2d<GraphicsMath>& pt) const noexcept;

					basic_matrix_2d& operator*=(const basic_matrix_2d& other) noexcept;
				};

				template <class GraphicsMath>
				basic_matrix_2d<GraphicsMath> operator*(const basic_matrix_2d<GraphicsMath>& lhs, const basic_matrix_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> operator*(const basic_point_2d<GraphicsMath>& lhs, const basic_matrix_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				bool operator==(const basic_matrix_2d<GraphicsMath>& lhs, const basic_matrix_2d<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const basic_matrix_2d<GraphicsMath>& lhs, const basic_matrix_2d<GraphicsMath>& rhs) noexcept;

				template <class GraphicsMath>
				class basic_display_point {
				public:
					using data_type = typename GraphicsMath::display_point_data_type;
				private:
					data_type _Data;
				public:
					const data_type& data() const noexcept;
					data_type& data() noexcept;

					// \ref{\iotwod.\pointtwod.cons}, constructors:
					basic_display_point() noexcept;
					basic_display_point(int xval, int yval) noexcept;
					basic_display_point(const typename GraphicsMath::display_point_data_type& val) noexcept;

					void x(int val) noexcept;
					void y(int val) noexcept;
					int x() const noexcept;
					int y() const noexcept;
				};

				template <class GraphicsMath>
				bool operator==(const basic_display_point<GraphicsMath>& lhs, const basic_display_point<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const basic_display_point<GraphicsMath>& lhs, const basic_display_point<GraphicsMath>& rhs) noexcept;

				template <class GraphicsMath>
				class basic_bounding_box {
				public:
					using data_type = typename GraphicsMath::bounding_box_data_type;
				private:
					data_type _Data;
				public:
					const data_type& data() const noexcept;
					data_type& data() noexcept;
					basic_bounding_box() noexcept;
					basic_bounding_box(float x, float y, float width, float height) noexcept;
					basic_bounding_box(const basic_point_2d<GraphicsMath>& tl, const basic_point_2d<GraphicsMath>& br) noexcept;
					basic_bounding_box(const typename GraphicsMath::bounding_box_data_type& val) noexcept;

					void x(float val) noexcept;
					void y(float val) noexcept;
					void width(float val) noexcept;
					void height(float val) noexcept;
					void top_left(const basic_point_2d<GraphicsMath>& val) noexcept;
					void bottom_right(const basic_point_2d<GraphicsMath>& val) noexcept;

					float x() const noexcept;
					float y() const noexcept;
					float width() const noexcept;
					float height() const noexcept;
					basic_point_2d<GraphicsMath> top_left() const noexcept;
					basic_point_2d<GraphicsMath> bottom_right() const noexcept;
				};

				template <class GraphicsMath>
				bool operator==(const basic_bounding_box<GraphicsMath>& lhs, const basic_bounding_box<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const basic_bounding_box<GraphicsMath>& lhs, const basic_bounding_box<GraphicsMath>& rhs) noexcept;

				template <class GraphicsMath>
				class basic_circle {
					using data_type = typename GraphicsMath::circle_data_type;
				private:
					data_type _Data;
				public:
					const data_type& data() const noexcept;
					data_type& data() noexcept;

					basic_circle() noexcept;
					basic_circle(const basic_point_2d<GraphicsMath>& ctr, float rad) noexcept;
					basic_circle(const typename GraphicsMath::circle_data_type& val) noexcept;

					void center(const basic_point_2d<GraphicsMath>& ctr) noexcept;
					void radius(float r) noexcept;

					basic_point_2d<GraphicsMath> center() const noexcept;
					float radius() const noexcept;
				};

				template <class GraphicsMath>
				bool operator==(const basic_circle<GraphicsMath>& lhs, const basic_circle<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const basic_circle<GraphicsMath>& lhs, const basic_circle<GraphicsMath>& rhs) noexcept;

				// Standalone math functions

				template <class GraphicsMath>
				float angle_for_point(const basic_point_2d<GraphicsMath>& ctr, const basic_point_2d<GraphicsMath>& pt) noexcept;

				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> point_for_angle(float ang, float rad = 1.0f) noexcept;

				template <class GraphicsMath>
				basic_point_2d<GraphicsMath> point_for_angle(float ang, const basic_point_2d<GraphicsMath>& rad) noexcept;

				template <class GraphicsMath>
                basic_point_2d<GraphicsMath> arc_start(const basic_point_2d<GraphicsMath>& ctr, float sang, const basic_point_2d<GraphicsMath>& rad, const basic_matrix_2d<GraphicsMath>& m = {}) noexcept;

				template <class GraphicsMath>
                basic_point_2d<GraphicsMath> arc_center(const basic_point_2d<GraphicsMath>& cpt, float sang, const basic_point_2d<GraphicsMath>& rad, const basic_matrix_2d<GraphicsMath>& m = {}) noexcept;

				template <class GraphicsMath>
                basic_point_2d<GraphicsMath> arc_end(const basic_point_2d<GraphicsMath>& cpt, float eang, const basic_point_2d<GraphicsMath>& rad, const basic_matrix_2d<GraphicsMath>& m = {}) noexcept;
			}
		}
	}
}
