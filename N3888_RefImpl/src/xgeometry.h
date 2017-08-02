#pragma once

namespace std::experimental::io2d {
	inline namespace v1 {

		class bounding_box {
			float _X = 0.0F;
			float _Y = 0.0F;
			float _Width = 0.0F;
			float _Height = 0.0F;
		public:
			constexpr bounding_box() noexcept { }
			constexpr bounding_box(float x, float y, float width, float height) noexcept
				: _X(x)
				, _Y(y)
				, _Width(width)
				, _Height(height) {
			}
			constexpr bounding_box(const point_2d& tl, const point_2d& br) noexcept
				: _X(tl.x)
				, _Y(tl.y)
				, _Width(::std::max(0.0F, br.x - tl.x))
				, _Height(::std::max(0.0F, br.y - tl.y)) {
			}

			constexpr void x(float value) noexcept {
				_X = value;
			}
			constexpr void y(float value) noexcept {
				_Y = value;
			}
			constexpr void width(float value) noexcept {
				_Width = value;
			}
			constexpr void height(float value) noexcept {
				_Height = value;
			}
			constexpr void top_left(const point_2d& value) noexcept {
				_X = value.x;
				_Y = value.y;
			}
			constexpr void bottom_right(const point_2d& value) noexcept {
				_Width = max(0.0F, value.x - _X);
				_Height = max(0.0F, value.y - _Y);
			}

			constexpr float x() const noexcept;
			constexpr float y() const noexcept;
			constexpr float width() const noexcept;
			constexpr float height() const noexcept;
			constexpr float left() const noexcept;
			constexpr float right() const noexcept;
			constexpr float top() const noexcept;
			constexpr float bottom() const noexcept;
			constexpr point_2d top_left() const noexcept;
			constexpr point_2d bottom_right() const noexcept;

			friend constexpr bool operator==(const bounding_box& lhs, const bounding_box& rhs) noexcept;
		};

		inline constexpr float bounding_box::x() const noexcept {
			return _X;
		}

		inline constexpr float bounding_box::y() const noexcept {
			return _Y;
		}

		inline constexpr float bounding_box::width() const noexcept {
			return _Width;
		}

		inline constexpr float bounding_box::height() const noexcept {
			return _Height;
		}

		inline constexpr float bounding_box::left() const noexcept {
			return _X;
		}

		inline constexpr float bounding_box::right() const noexcept {
			return _X + _Width;
		}

		inline constexpr float bounding_box::top() const noexcept {
			return _Y;
		}

		inline constexpr float bounding_box::bottom() const noexcept {
			return _Y + _Height;
		}

		inline constexpr point_2d bounding_box::top_left() const noexcept {
			return{ _X, _Y };
		}

		inline constexpr point_2d bounding_box::bottom_right() const noexcept {
			return{ _X + _Width, _Y + _Height };
		}

		class circle {
			point_2d _Center;
			float _Radius;
		public:
			constexpr circle() noexcept
				: _Center()
				, _Radius() {}
			constexpr circle(const point_2d& ctr, float r) noexcept
				: _Center(ctr)
				, _Radius(r) {}

			constexpr void center(const point_2d& ctr) noexcept {
				_Center = ctr;
			}
			constexpr void radius(float r) noexcept {
				_Radius = r;
			}

			constexpr point_2d center() const noexcept {
				return _Center;
			}
			constexpr float radius() const noexcept {
				return _Radius;
			}

			constexpr bool operator==(const circle& rhs) noexcept {
				return _Center == rhs._Center && _Radius == rhs._Radius;
			}
			constexpr bool operator!=(const circle& rhs) noexcept {
				return !((*this) == rhs);
			}
		};

		class bounding_box;
		constexpr bool operator==(const bounding_box& lhs, const bounding_box& rhs)
			noexcept {
			return lhs._X == rhs._X && lhs._Y == rhs._Y && lhs._Width == rhs._Width && lhs._Height == rhs._Height;
		}
		constexpr bool operator!=(const bounding_box& lhs, const bounding_box& rhs)
			noexcept {
			return !(lhs == rhs);
		}
		class circle;
		constexpr bool operator==(const circle& lhs, const circle& rhs) noexcept;
		constexpr bool operator!=(const circle& lhs, const circle& rhs) noexcept;

	}
}