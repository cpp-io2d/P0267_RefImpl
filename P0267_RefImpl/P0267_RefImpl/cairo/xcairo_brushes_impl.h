#pragma once

#include "xcairo_helpers.h"
#include "xsystemheaders.h"
#include <cassert>
#if defined(_WIN32) || defined(_WIN64)
#include <cairo-win32.h>
#endif
#include "xpath.h"
#include <iostream>
#include <sstream>
#include <iomanip>

#ifdef _IO2D_Has_Magick
#include <magick/api.h>
#endif

#include <system_error>
#include <cstring>
#include <chrono>

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Cairo {
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::brushes::create_brush(const rgba_color& c) {
				brush_data_type data;
				data.imageSurface = nullptr;
				data.brushType = brush_type::solid_color;
				data.brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_rgba(c.r(), c.g(), c.b(), c.a()), &cairo_pattern_destroy);
				return data;
			}
			template<class GraphicsMath>
			template<class InputIterator>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::brushes::create_brush(const basic_point_2d<GraphicsMath>& begin, const basic_point_2d<GraphicsMath>& end, InputIterator first, InputIterator last) {
				brush_data_type data;
				data.brushType = brush_type::linear;
				data.imageSurface = nullptr;
				data.brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_linear(begin.x(), begin.y(), end.x(), end.y()), &cairo_pattern_destroy);
				_Throw_if_failed_cairo_status_t(cairo_pattern_status(data.brush.get()));

				for (auto it = first; it != last; ++it) {
					auto stop = *it;
					cairo_pattern_add_color_stop_rgba(data.brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
				}
				_Throw_if_failed_cairo_status_t(cairo_pattern_status(data.brush.get()));
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::brushes::create_brush(const basic_point_2d<GraphicsMath>& b, const basic_point_2d<GraphicsMath>& e, ::std::initializer_list<gradient_stop> il) {
				return create_brush(b, e, ::std::begin(il), ::std::end(il));
			}
			template<class GraphicsMath>
			template<class InputIterator>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::brushes::create_brush(const basic_circle<GraphicsMath>& start, const basic_circle<GraphicsMath>& end, InputIterator first, InputIterator last) {
				brush_data_type data;
				data.imageSurface = nullptr;
				data.brushType = brush_type::radial;
				data.brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(start.center().x(), start.center().y(), start.radius(), end.center().x(), end.center().y(), end.radius()), &cairo_pattern_destroy);
				_Throw_if_failed_cairo_status_t(cairo_pattern_status(data.brush.get()));
				for (auto it = first; it != last; ++it) {
					auto stop = *it;
					cairo_pattern_add_color_stop_rgba(data.brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
				}
				_Throw_if_failed_cairo_status_t(cairo_pattern_status(data.brush.get()));
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::brushes::create_brush(const basic_circle<GraphicsMath>& s, const basic_circle<GraphicsMath>& e, ::std::initializer_list<gradient_stop> il) {
				return create_brush(s, e, ::std::begin(il), ::std::end(il));
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::brushes::create_brush(basic_image_surface<_Graphics_surfaces_type>&& img) {
				using img_sfc_data_type = typename _Cairo_graphics_surfaces<GraphicsMath>::surfaces::image_surface_data_type;
				brush_data_type data;
				// The surface is dying and I want to steal some of its data, ergo const_cast.
				img_sfc_data_type& imgData = const_cast<img_sfc_data_type&>(img.data());
				data.imageSurface = shared_ptr<cairo_surface_t>(imgData.surface.release(), &cairo_surface_destroy);
				data.brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_for_surface(data.imageSurface.get()), &cairo_pattern_destroy);
				data.brushType = brush_type::surface;
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::brushes::copy_brush(const brush_data_type& data) {
				return data;
			}
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::brushes::move_brush(brush_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::brushes::destroy(brush_data_type& /*data*/) noexcept {
				// Do nothing; it destroys itself via the shared_ptr's.
			}

			template<class GraphicsMath>
			inline brush_type _Cairo_graphics_surfaces<GraphicsMath>::brushes::get_brush_type(const brush_data_type& data) noexcept {
				return data.brushType;
			}
		}
	}
}
