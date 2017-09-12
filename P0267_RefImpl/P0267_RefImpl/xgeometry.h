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
			template <class T>
			constexpr bounding_box(basic_point_2d<T> tl, basic_point_2d<T> br) noexcept;

			constexpr void x(float val) noexcept;
			constexpr void y(float val) noexcept;
			constexpr void width(float val) noexcept;
			constexpr void height(float val) noexcept;
			template <class T>
			constexpr void top_left(basic_point_2d<T> val) noexcept;
			template <class T>
			constexpr void bottom_right(basic_point_2d<T> val) noexcept;

			constexpr float x() const noexcept;
			constexpr float y() const noexcept;
			constexpr float width() const noexcept;
			constexpr float height() const noexcept;
			template <class T>
			constexpr basic_point_2d<T> top_left() const noexcept;
			template <class T>
			constexpr basic_point_2d<T> bottom_right() const noexcept;

			friend constexpr bool operator==(const bounding_box& lhs, const bounding_box& rhs) noexcept;
		};

		constexpr bool operator==(const bounding_box& lhs, const bounding_box& rhs) noexcept;
		constexpr bool operator!=(const bounding_box& lhs, const bounding_box& rhs) noexcept;

		class circle {
			template <class T>
			basic_point_2d<T> _Center;
			float _Radius;
		public:
			constexpr circle() noexcept;
			template <class T>
			constexpr circle(const basic_point_2d<T>& ctr, float rad) noexcept;

			template <class T>
			constexpr void center(const basic_point_2d<T>& ctr) noexcept;
			constexpr void radius(float r) noexcept;

			template <class T>
			constexpr basic_point_2d<T> center() const noexcept;
			constexpr float radius() const noexcept;

			constexpr bool operator==(const circle& rhs) noexcept;
            constexpr bool operator!=(const circle& rhs) noexcept;
		};

		constexpr bool operator==(const circle& lhs, const circle& rhs) noexcept;
		constexpr bool operator!=(const circle& lhs, const circle& rhs) noexcept;
	}
}