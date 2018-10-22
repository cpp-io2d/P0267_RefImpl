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
			// Helpers to set state when rendering

			template <class GraphicsMath>
			inline void _Set_render_props(cairo_t* context, const basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>& r) {
				const auto& props = r;
				const auto m = props.surface_matrix();
				cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
				cairo_set_antialias(context, _Antialias_to_cairo_antialias_t(props.antialiasing()));
				cairo_set_matrix(context, &cm);
				cairo_set_operator(context, _Compositing_operator_to_cairo_operator_t(props.compositing()));
			}

			template <class GraphicsMath>
			inline void _Set_clip_props(cairo_t* context, const basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>& c) {
				cairo_reset_clip(context);
				const auto& props = c.data();
				if (props.clip.has_value()) {
					cairo_fill_rule_t fr = cairo_get_fill_rule(context);
					cairo_set_fill_rule(context, _Fill_rule_to_cairo_fill_rule_t(props.fr));
					cairo_new_path(context);

					cairo_append_path(context, props.clip.value().data().path.get());
					cairo_clip(context);
					// Restore saved state
					cairo_set_fill_rule(context, fr);
				}
			}

			template <class GraphicsMath>
			inline void _Set_stroke_props(cairo_t* context, const basic_stroke_props<_Cairo_graphics_surfaces<GraphicsMath>>& s, float miterMax, const basic_dashes<_Cairo_graphics_surfaces<GraphicsMath>>& ds) {
				const auto& props = s.data();
				cairo_set_line_width(context, props._Line_width);
				cairo_set_line_cap(context, _Line_cap_to_cairo_line_cap_t(props._Line_cap));
				cairo_set_line_join(context, _Line_join_to_cairo_line_join_t(props._Line_join));
				cairo_set_miter_limit(context, ::std::min<float>(miterMax, props._Miter_limit));

				const auto& d = ds.data();
				const auto& dFloatVal = d.pattern;
				vector<double> dashAsDouble(dFloatVal.size());
				for (const auto& val : dFloatVal) {
					dashAsDouble.push_back(static_cast<double>(val));
				}
				cairo_set_dash(context, dashAsDouble.data(), _Container_size_to_int(dashAsDouble), static_cast<double>(d.offset));
				if (cairo_status(context) == CAIRO_STATUS_INVALID_DASH) {
					_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_DASH);
				}
			}

			template <class GraphicsMath>
			inline void _Set_brush_props(cairo_t* context, const basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>& bp, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b) {
				const auto& props = bp;
				auto p = b.data().brush.get();
				cairo_pattern_set_extend(p, _Extend_to_cairo_extend_t(props.wrap_mode()));
				cairo_pattern_set_filter(p, _Filter_to_cairo_filter_t(props.filter()));
				const auto& m = props.brush_matrix();
				cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
				cairo_pattern_set_matrix(p, &cm);
				cairo_set_fill_rule(context, _Fill_rule_to_cairo_fill_rule_t(props.fill_rule()));
				//}
			}

			template <class GraphicsSurfaces>
			inline void _Set_mask_props(const basic_mask_props<GraphicsSurfaces>& mp, const basic_brush<GraphicsSurfaces>& b) {
				const auto& props = mp;
				auto p = b.data().brush.get();
				cairo_pattern_set_extend(p, _Extend_to_cairo_extend_t(props.wrap_mode()));
				cairo_pattern_set_filter(p, _Filter_to_cairo_filter_t(props.filter()));
				const auto& m = props.mask_matrix();
				cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
				cairo_pattern_set_matrix(p, &cm);
			}

			template<class GraphicsMath>
			inline basic_display_point<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::max_dimensions() noexcept {
				return basic_display_point<GraphicsMath>(16384, 16384); // This takes up 1 GB of RAM, you probably don't want to do this. 2048x2048 is the max size for hardware that meets 9_1 specs (i.e. quite low powered or really old). Probably much more reasonable.
			}

			template <class GraphicsMath>
			inline basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::copy_surface(basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>>& sfc) noexcept {
				basic_image_surface<_Cairo_graphics_surfaces> retSfc(sfc.format(), sfc.dimensions().x(), sfc.dimensions().y());
				auto srcSfc = cairo_surface_map_to_image(sfc.data().surface.get(), nullptr);
				auto destSfc = cairo_surface_map_to_image(retSfc.data().surface.get(), nullptr);
				auto srcSize = cairo_image_surface_get_height(srcSfc) * cairo_image_surface_get_stride(srcSfc);
				auto srcData = cairo_image_surface_get_data(srcSfc);
				auto destData = cairo_image_surface_get_data(destSfc);
				memcpy(destData, srcData, srcSize);
				cairo_surface_unmap_image(retSfc.data().surface.get(), destSfc);
				cairo_surface_unmap_image(sfc.data().surface.get(), srcSfc);
				return retSfc;
			}

			template <class GraphicsMath>
			inline basic_image_surface<_Cairo_graphics_surfaces<GraphicsMath>> _Cairo_graphics_surfaces<GraphicsMath>::surfaces::copy_surface(basic_output_surface<_Cairo_graphics_surfaces>& sfc) noexcept {
				basic_image_surface<_Cairo_graphics_surfaces> retSfc(sfc.format(), sfc.dimensions().x(), sfc.dimensions().y());
				auto srcSfc = cairo_surface_map_to_image(sfc.data().surface.get(), nullptr);
				auto destSfc = cairo_surface_map_to_image(retSfc.data().surface.get(), nullptr);
				auto srcSize = cairo_image_surface_get_height(srcSfc) * cairo_image_surface_get_stride(srcSfc);
				auto srcData = cairo_image_surface_get_data(srcSfc);
				auto destData = cairo_image_surface_get_data(destSfc);
				memcpy(destData, srcData, srcSize);
				cairo_surface_unmap_image(retSfc.data().surface.get(), destSfc);
				cairo_surface_unmap_image(sfc.data().surface.get(), srcSfc);
				return retSfc;
			}
		}
	}
}

#include "xcairo_surfaces_image_impl.h"
