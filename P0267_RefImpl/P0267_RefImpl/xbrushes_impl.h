#pragma once
#include "xbrushes.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		inline constexpr gradient_stop::gradient_stop() noexcept
			: _Offset(0.0F)
			, _Color(rgba_color{}) {}
		inline constexpr gradient_stop::gradient_stop(float offset, const rgba_color& color)
			: _Offset(offset)
			, _Color(color) {}

		inline constexpr void gradient_stop::offset(float value) noexcept {
			_Offset = value;
		}
		inline constexpr void gradient_stop::color(const rgba_color& value) noexcept {
			_Color = value;
		}

		inline constexpr float gradient_stop::offset() const noexcept {
			return _Offset;
		}
		inline constexpr rgba_color gradient_stop::color() const noexcept {
			return _Color;
		}

		inline constexpr bool operator==(const gradient_stop& lhs, const gradient_stop& rhs) noexcept {
			return lhs._Offset == rhs._Offset && lhs._Color == rhs._Color;
		}

		template<class GraphicsSurfaces>
		inline const typename basic_brush<GraphicsSurfaces>::data_type& basic_brush<GraphicsSurfaces>::data() const noexcept {
			return _Data;
		}

		template<class GraphicsSurfaces>
		inline typename basic_brush<GraphicsSurfaces>::data_type& basic_brush<GraphicsSurfaces>::data() noexcept {
			return _Data;
		}

		template<class GraphicsSurfaces>
		inline basic_brush<GraphicsSurfaces>::basic_brush(const rgba_color & c)
			: _Data(GraphicsSurfaces::brushes::create_brush(c)) {
		}
		template<class GraphicsSurfaces>
		inline basic_brush<GraphicsSurfaces>::basic_brush(const basic_point_2d<graphics_math_type>& begin, const basic_point_2d<graphics_math_type>& end, ::std::initializer_list<gradient_stop> il)
			: _Data(GraphicsSurfaces::brushes::create_brush(begin, end, il)) {
		}
		template<class GraphicsSurfaces>
		template<class InputIterator>
		inline std::experimental::io2d::v1::basic_brush<GraphicsSurfaces>::basic_brush(const basic_point_2d<graphics_math_type>& begin, const basic_point_2d<graphics_math_type>& end, InputIterator first, InputIterator last)
			: _Data(GraphicsSurfaces::brushes::create_brush(begin, end, first, last)) {
		}
		template<class GraphicsSurfaces>
		inline basic_brush<GraphicsSurfaces>::basic_brush(const basic_circle<graphics_math_type>& start, const basic_circle<graphics_math_type>& end, ::std::initializer_list<gradient_stop> il)
			: _Data(GraphicsSurfaces::brushes::create_brush(start, end, il)) {
		}
		template<class GraphicsSurfaces>
		template<class InputIterator>
		inline basic_brush<GraphicsSurfaces>::basic_brush(const basic_circle<graphics_math_type>& start, const basic_circle<graphics_math_type>& end, InputIterator first, InputIterator last)
			: _Data(GraphicsSurfaces::brushes::create_brush(start, end, first, last)) {
		}
		template<class GraphicsSurfaces>
		inline basic_brush<GraphicsSurfaces>::basic_brush(basic_image_surface<GraphicsSurfaces>&& img)
			: _Data(GraphicsSurfaces::brushes::create_brush(move(img))) {
		}
		template<class GraphicsSurfaces>
		inline brush_type basic_brush<GraphicsSurfaces>::type() const noexcept {
			return GraphicsSurfaces::brushes::get_brush_type(_Data);
		}
	}
}
