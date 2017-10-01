#pragma once

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				template <class GraphicsMath>
					class basic_bounding_box {
					public:
						using data_type = typename GraphicsMath::bounding_box_data_type;
					private:
						data_type _Data;
						//float _X = 0.0F;
						//float _Y = 0.0F;
						//float _Width = 0.0F;
						//float _Height = 0.0F;
					public:
						constexpr basic_bounding_box() noexcept;
						constexpr basic_bounding_box(float x, float y, float width, float height) noexcept;
\
						constexpr void x(float val) noexcept;
						constexpr void y(float val) noexcept;
						constexpr void width(float val) noexcept;
						constexpr void height(float val) noexcept;
						template <class LinearAlgebra>
						constexpr void top_left(float top, float left) noexcept;
						template <class LinearAlgebra>
						constexpr void bottom_right(const typename LinearAlgebra::point_2d_type& val) noexcept;

						constexpr float x() const noexcept;
						constexpr float y() const noexcept;
						constexpr float width() const noexcept;
						constexpr float height() const noexcept;
						constexpr typename Geometry::point_2d top_left() const noexcept;
						constexpr typename Geometry::point_2d bottom_right() const noexcept;

						friend constexpr bool operator==(const bounding_box& lhs, const bounding_box& rhs) noexcept;
					};

					class circle {
						using data_type = typename Geometry::circle_data_type;
					private:
						data_type _Data;
						//float _X;
						//float _Y;
						//float _Radius;
						friend constexpr bool operator==(const circle&, const circle&) noexcept;
					public:
						constexpr circle() noexcept;
						constexpr circle(const typename Geometry::point_2d& ctr, float rad) noexcept;

						constexpr void center(const typename Geometry::point_2d& ctr) noexcept;
						constexpr void radius(float r) noexcept;

						constexpr typename Geometry::point_2d center() const noexcept;
						constexpr float radius() const noexcept;
					};
				template <class Geometry>
				constexpr bool operator==(const typename basic_geometry<Geometry>::bounding_box& lhs, const typename basic_geometry<Geometry>::bounding_box& rhs) noexcept;
				template <class Geometry>
				constexpr bool operator!=(const typename basic_geometry<Geometry>::bounding_box& lhs, const typename basic_geometry<Geometry>::bounding_box& rhs) noexcept;
				template <class Geometry>
				constexpr bool operator==(const typename basic_geometry<Geometry>::circle& lhs, const typename basic_geometry<Geometry>::circle& rhs) noexcept;
				template <class Geometry>
				constexpr bool operator!=(const typename basic_geometry<Geometry>::circle& lhs, const typename basic_geometry<Geometry>::circle& rhs) noexcept;
			}
		}
	}
}