#pragma once

namespace std {
	namespace experimental {
		namespace io2d {
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

				template <class GraphicsSurfaces>
				class basic_brush {
				public:
					using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
					using _Data_type = GraphicsSurfaces::brush_data_type;
				private:
					_Data_type _Data;
				public:
					const _Data_type& _Get_data() const noexcept;

					explicit basic_brush(const rgba_color& c);

					template <class InputIterator>
					basic_brush(const basic_point_2d<graphics_math_type>& begin, const basic_point_2d<graphics_math_type>& end, InputIterator first, InputIterator last);

					basic_brush(const basic_point_2d<graphics_math_type>& begin, const basic_point_2d<graphics_math_type>& end, ::std::initializer_list<gradient_stop> il);

					template <class InputIterator>
					basic_brush(const basic_circle<graphics_math_type>& start, const basic_circle<graphics_math_type>& end, InputIterator first, InputIterator last);

					basic_brush(const basic_circle<graphics_math_type>& start, const basic_circle<graphics_math_type>& end, ::std::initializer_list<gradient_stop> il);

					basic_brush(basic_image_surface<GraphicsSurfaces>&& img);

					brush_type type() const noexcept;
				};
			}
		}
	}
}