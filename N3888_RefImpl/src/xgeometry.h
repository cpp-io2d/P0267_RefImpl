#pragma once

namespace std::experimental::io2d {
	inline namespace v1 {

		class bounding_box {
			float _X = 0.0F;
			float _Y = 0.0F;
			float _Width = 0.0F;
			float _Height = 0.0F;
		public:
			constexpr bounding_box() noexcept;
			constexpr bounding_box(float x, float y, float width, float height) noexcept;
			constexpr bounding_box(point_2d tl, point_2d br) noexcept;

			constexpr void x(float val) noexcept;
			constexpr void y(float val) noexcept;
			constexpr void width(float val) noexcept;
			constexpr void height(float val) noexcept;
			constexpr void top_left(point_2d val) noexcept;
			constexpr void bottom_right(point_2d val) noexcept;

			constexpr float x() const noexcept;
			constexpr float y() const noexcept;
			constexpr float width() const noexcept;
			constexpr float height() const noexcept;
			constexpr point_2d top_left() const noexcept;
			constexpr point_2d bottom_right() const noexcept;

			friend constexpr bool operator==(const bounding_box& lhs, const bounding_box& rhs) noexcept;
		};

		constexpr bool operator==(const bounding_box& lhs, const bounding_box& rhs) noexcept;
		constexpr bool operator!=(const bounding_box& lhs, const bounding_box& rhs) noexcept;

		class circle {
			point_2d _Center;
			float _Radius;
		public:
			constexpr circle() noexcept;
			constexpr circle(point_2d ctr, float rad) noexcept;

			constexpr void center(point_2d ctr) noexcept;
			constexpr void radius(float r) noexcept;

			constexpr point_2d center() const noexcept;
			constexpr float radius() const noexcept;

			constexpr bool operator==(const circle& rhs) noexcept;
            constexpr bool operator!=(const circle& rhs) noexcept;
		};

		constexpr bool operator==(const circle& lhs, const circle& rhs) noexcept;
		constexpr bool operator!=(const circle& lhs, const circle& rhs) noexcept;

	}
}