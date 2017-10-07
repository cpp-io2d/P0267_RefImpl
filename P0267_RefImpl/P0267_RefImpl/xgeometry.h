#pragma once

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				template <class GraphicsMath>
				class basic_bounding_box {
				public:
					using data_type = typename GraphicsMath::bounding_box_data_type;
					//using point_2d_data_type = typename GraphicsMath::point_2d_data_type;
				private:
					data_type _Data;
					//float _X = 0.0F;
					//float _Y = 0.0F;
					//float _Width = 0.0F;
					//float _Height = 0.0F;
				public:
					constexpr basic_bounding_box() noexcept;
					constexpr basic_bounding_box(float x, float y, float width, float height) noexcept;

					constexpr void x(float val) noexcept;
					constexpr void y(float val) noexcept;
					constexpr void width(float val) noexcept;
					constexpr void height(float val) noexcept;
					constexpr void top_left(const basic_point_2d<GraphicsMath>& val) noexcept;
					constexpr void bottom_right(const basic_point_2d<GraphicsMath>& val) noexcept;

					constexpr float x() const noexcept;
					constexpr float y() const noexcept;
					constexpr float width() const noexcept;
					constexpr float height() const noexcept;
					constexpr basic_point_2d<GraphicsMath> top_left() const noexcept;
					constexpr basic_point_2d<GraphicsMath> bottom_right() const noexcept;

					friend constexpr bool operator==(const basic_bounding_box& lhs, const basic_bounding_box& rhs) noexcept;
				};

				template <class GraphicsMath>
				constexpr bool operator==(const basic_bounding_box<GraphicsMath>& lhs, const basic_bounding_box<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				constexpr bool operator!=(const basic_bounding_box<GraphicsMath>& lhs, const basic_bounding_box<GraphicsMath>& rhs) noexcept;

				template <class GraphicsMath>
				class basic_circle {
					using data_type = typename GraphicsMath::circle_data_type;
					//using point_2d_data_type = typename GraphicsMath::point_2d_data_type;
				private:
					data_type _Data;
					//float _X;
					//float _Y;
					//float _Radius;
					friend constexpr bool operator==(const basic_circle&, const basic_circle&) noexcept;
				public:
					constexpr basic_circle() noexcept;
					constexpr basic_circle(const basic_point_2d<GraphicsMath>& ctr, float rad) noexcept;

					constexpr void center(const basic_point_2d<GraphicsMath>& ctr) noexcept;
					constexpr void radius(float r) noexcept;

					constexpr basic_point_2d<GraphicsMath> center() const noexcept;
					constexpr float radius() const noexcept;
				};

				template <class GraphicsMath>
				constexpr bool operator==(const basic_circle<GraphicsMath>& lhs, const basic_circle<GraphicsMath>& rhs) noexcept;
				template <class GraphicsMath>
				constexpr bool operator!=(const basic_circle<GraphicsMath>& lhs, const basic_circle<GraphicsMath>& rhs) noexcept;
			}
		}
	}
}