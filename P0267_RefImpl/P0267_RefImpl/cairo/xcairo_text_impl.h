#pragma once

#include "xcairo_helpers.h"
#include "xsystemheaders.h"
#include <cassert>
#if defined(_WIN32) || defined(_WIN64)
#include <cairo-win32.h>
#endif

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Cairo {
			// surface draw_text functions
			//template<class GraphicsMath>
			//inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_text(image_surface_data_type& data, const basic_point_2d<GraphicsMath>& pt, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& font, const string& text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) {
			//	throw ::std::system_error(make_error_code(errc::not_supported), "draw_text is not yet implemented.");
			//}
			//template<class GraphicsMath>
			//inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_text(image_surface_data_type& data, const basic_bounding_box<GraphicsMath>& bb, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& font, const string& text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) {
			//	throw ::std::system_error(make_error_code(errc::not_supported), "draw_text is not yet implemented.");
			//}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_text(image_surface_data_type& /*data*/, const basic_point_2d<GraphicsMath>& /*pt*/, const basic_brush<graphics_surfaces_type>& /*b*/, const basic_font<graphics_surfaces_type>& /*font*/, const string& /*text*/, const basic_text_props<graphics_surfaces_type>& /*tp*/, const basic_brush_props<graphics_surfaces_type>& /*bp*/, const basic_stroke_props<graphics_surfaces_type>& /*sp*/, const basic_dashes<graphics_surfaces_type>& /*d*/, const basic_render_props<graphics_surfaces_type>& /*rp*/, const basic_clip_props<graphics_surfaces_type>& /*cl*/) {
				throw ::std::system_error(make_error_code(errc::not_supported), "draw_text is not yet implemented.");
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_text(image_surface_data_type& /*data*/, const basic_bounding_box<GraphicsMath>& /*bb*/, const basic_brush<graphics_surfaces_type>& /*b*/, const basic_font<graphics_surfaces_type>& /*font*/, const string& /*text*/, const basic_text_props<graphics_surfaces_type>& /*tp*/, const basic_brush_props<graphics_surfaces_type>& /*bp*/, const basic_stroke_props<graphics_surfaces_type>& /*sp*/, const basic_dashes<graphics_surfaces_type>& /*d*/, const basic_render_props<graphics_surfaces_type>& /*rp*/, const basic_clip_props<graphics_surfaces_type>& /*cl*/) {
				throw ::std::system_error(make_error_code(errc::not_supported), "draw_text is not yet implemented.");
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_text(output_surface_data_type& /*data*/, const basic_point_2d<GraphicsMath>& /*pt*/, const basic_brush<graphics_surfaces_type>& /*b*/, const basic_font<graphics_surfaces_type>& /*font*/, const string& /*text*/, const basic_text_props<graphics_surfaces_type>& /*tp*/, const basic_brush_props<graphics_surfaces_type>& /*bp*/, const basic_stroke_props<graphics_surfaces_type>& /*sp*/, const basic_dashes<graphics_surfaces_type>& /*d*/, const basic_render_props<graphics_surfaces_type>& /*rp*/, const basic_clip_props<graphics_surfaces_type>& /*cl*/) {
				throw ::std::system_error(make_error_code(errc::not_supported), "draw_text is not yet implemented.");
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_text(output_surface_data_type& /*data*/, const basic_bounding_box<GraphicsMath>& /*bb*/, const basic_brush<graphics_surfaces_type>& /*b*/, const basic_font<graphics_surfaces_type>& /*font*/, const string& /*text*/, const basic_text_props<graphics_surfaces_type>& /*tp*/, const basic_brush_props<graphics_surfaces_type>& /*bp*/, const basic_stroke_props<graphics_surfaces_type>& /*sp*/, const basic_dashes<graphics_surfaces_type>& /*d*/, const basic_render_props<graphics_surfaces_type>& /*rp*/, const basic_clip_props<graphics_surfaces_type>& /*cl*/) {
				throw ::std::system_error(make_error_code(errc::not_supported), "draw_text is not yet implemented.");
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_text(unmanaged_output_surface_data_type& /*data*/, const basic_point_2d<GraphicsMath>& /*pt*/, const basic_brush<graphics_surfaces_type>& /*b*/, const basic_font<graphics_surfaces_type>& /*font*/, const string& /*text*/, const basic_text_props<graphics_surfaces_type>& /*tp*/, const basic_brush_props<graphics_surfaces_type>& /*bp*/, const basic_stroke_props<graphics_surfaces_type>& /*sp*/, const basic_dashes<graphics_surfaces_type>& /*d*/, const basic_render_props<graphics_surfaces_type>& /*rp*/, const basic_clip_props<graphics_surfaces_type>& /*cl*/) {
				throw ::std::system_error(make_error_code(errc::not_supported), "draw_text is not yet implemented.");
			}
			template<class GraphicsMath>
			inline void _Cairo_graphics_surfaces<GraphicsMath>::surfaces::draw_text(unmanaged_output_surface_data_type& /*data*/, const basic_bounding_box<GraphicsMath>& /*bb*/, const basic_brush<graphics_surfaces_type>& /*b*/, const basic_font<graphics_surfaces_type>& /*font*/, const string& /*text*/, const basic_text_props<graphics_surfaces_type>& /*tp*/, const basic_brush_props<graphics_surfaces_type>& /*bp*/, const basic_stroke_props<graphics_surfaces_type>& /*sp*/, const basic_dashes<graphics_surfaces_type>& /*d*/, const basic_render_props<graphics_surfaces_type>& /*rp*/, const basic_clip_props<graphics_surfaces_type>& /*cl*/) {
				throw ::std::system_error(make_error_code(errc::not_supported), "draw_text is not yet implemented.");
			}

			// text_props
			template<class GraphicsMath>
			inline typename _Cairo_graphics_surfaces<GraphicsMath>::text::text_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::text::create_text_props(float scl, font_size_units fsu, float fontsize, bool kern, font_hinting hint, font_antialias aa, font_stretching stretch, bool strike_through, font_line fl) noexcept {
				text_props_data_type result;
				result.scl = scl;
				result.fsu = fsu;
				result.fontsize = fontsize;
				result.kern = kern;
				result.hint = hint;
				result.aa = aa;
				result.stretch = stretch;
				result.strike_through = strike_through;
				result.fl = fl;
				return result;
			}
		}
	}
}