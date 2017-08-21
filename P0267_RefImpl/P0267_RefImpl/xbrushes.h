#pragma once

namespace std::experimental::io2d {
	inline namespace v1 {

		enum class wrap_mode {
			none,
			repeat,
			reflect,
			pad
		};

		enum class filter {
			fast,
			good,
			best,
			nearest,
			bilinear
		};

		enum class brush_type {
			solid_color,
			surface,
			linear,
			radial
		};

		class gradient_stop {
		private:
			float _Offset;
			rgba_color _Color;
			friend constexpr bool operator==(const gradient_stop& lhs, const gradient_stop& rhs) noexcept;
		public:
			constexpr gradient_stop() noexcept;
			constexpr gradient_stop(float offset, const rgba_color& color);

			constexpr void offset(float value) noexcept;
			constexpr void color(const rgba_color& value) noexcept;

			constexpr float offset() const noexcept;
			constexpr rgba_color color() const noexcept;
		};

		constexpr bool operator==(const gradient_stop& lhs, const gradient_stop& rhs)
			noexcept;
		constexpr bool operator!=(const gradient_stop& lhs, const gradient_stop& rhs)
			noexcept;

		template <class T>
		class brush {
			typename T::renderer_brush _Brush_impl;

		public:
			const auto& native_handle() const { return _Brush_impl; }

			explicit brush(const rgba_color& c);

			template <class InputIterator>
			brush(const point_2d& begin, const point_2d& end, InputIterator first, InputIterator last);

			brush(const point_2d& begin, const point_2d& end, ::std::initializer_list<gradient_stop> il);

			template <class InputIterator>
			brush(const circle& start, const circle& end, InputIterator first, InputIterator last);

			brush(const circle& start, const circle& end, ::std::initializer_list<gradient_stop> il);

			brush_type type() const noexcept;
		};

	}
}