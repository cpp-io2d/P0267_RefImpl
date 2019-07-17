#pragma once

#include "xqt_headers.h"
#include <cassert>
#include "xpath.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <system_error>
#include <cstring>
#include <chrono>

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Qt_io2d {
			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Qt_graphics_surfaces<GraphicsMath>::brushes::create_brush(const rgba_color& c) {
				brush_data_type data;
				data.brushType = brush_type::solid_color;
				data.brush = make_shared<QBrush>(QColor::fromRgbF(c.r(), c.g(), c.b(), c.a()));
				return data;
			}
			template<class GraphicsMath>
			template<class InputIterator>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Qt_graphics_surfaces<GraphicsMath>::brushes::create_brush(const basic_point_2d<GraphicsMath>& begin, const basic_point_2d<GraphicsMath>& end, InputIterator first, InputIterator last) {
				brush_data_type data;
				data.brushType = brush_type::linear;
				QLinearGradient lg = QLinearGradient(begin.x(), begin.y(), end.x(), end.y());
				for (auto it = first; it != last; ++it) {
					auto stop = *it;
					lg.setColorAt(stop.offset(), QColor::fromRgbF(stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a()));
				}
				lg.setSpread(QGradient::ReflectSpread);
				data.brush = make_shared<QBrush>(lg);
				return data;
			}
			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Qt_graphics_surfaces<GraphicsMath>::brushes::create_brush(const basic_point_2d<GraphicsMath>& b, const basic_point_2d<GraphicsMath>& e, ::std::initializer_list<gradient_stop> il) {
				return create_brush(b, e, ::std::begin(il), ::std::end(il));
			}
			template<class GraphicsMath>
			template<class InputIterator>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Qt_graphics_surfaces<GraphicsMath>::brushes::create_brush(const basic_circle<GraphicsMath>& start, const basic_circle<GraphicsMath>& end, InputIterator first, InputIterator last) {
				brush_data_type data;
				data.brushType = brush_type::radial;
				QRadialGradient rg = QRadialGradient(start.center().x(), start.center().y(), start.radius(), end.center().x(), end.center().y(), end.radius());
				for (auto it = first; it != last; ++it) {
					auto stop = *it;
					rg.setColorAt(stop.offset(), QColor::fromRgbF(stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a()));
				}
				data.brush = make_shared<QBrush>(rg);
				return data;
			}
			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Qt_graphics_surfaces<GraphicsMath>::brushes::create_brush(const basic_circle<GraphicsMath>& s, const basic_circle<GraphicsMath>& e, ::std::initializer_list<gradient_stop> il) {
				return create_brush(s, e, ::std::begin(il), ::std::end(il));
			}
			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Qt_graphics_surfaces<GraphicsMath>::brushes::create_brush(basic_image_surface<_Graphics_surfaces_type>&& img) {
				using img_sfc_data_type = typename _Qt_graphics_surfaces<GraphicsMath>::surfaces::image_surface_data_type;
				brush_data_type data;
				// The surface is dying and I want to steal some of its data, ergo const_cast.
				img_sfc_data_type& imgData = const_cast<img_sfc_data_type&>(img.data());
				//data.imageSurface = shared_ptr<cairo_surface_t>(imgData.surface.release(), &cairo_surface_destroy);
				data.brush = make_shared<QBrush>(imgData.surface);
				data.brushType = brush_type::surface;
				return data;
			}
			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Qt_graphics_surfaces<GraphicsMath>::brushes::copy_brush(const brush_data_type& data) {
				return data;
			}
			template<class GraphicsMath>
			inline typename _Qt_graphics_surfaces<GraphicsMath>::brushes::brush_data_type _Qt_graphics_surfaces<GraphicsMath>::brushes::move_brush(brush_data_type&& data) noexcept {
				return data;
			}

			template<class GraphicsMath>
			inline void _Qt_graphics_surfaces<GraphicsMath>::brushes::destroy(brush_data_type& /*data*/) noexcept {
				// Do nothing; it destroys itself via the shared_ptr's.
			}

			template<class GraphicsMath>
			inline brush_type _Qt_graphics_surfaces<GraphicsMath>::brushes::get_brush_type(const brush_data_type& data) noexcept {
				return data.brushType;
			}
		}
	}
}
