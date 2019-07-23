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
#include "xqt_helpers.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Qt_io2d {
			// Helpers to set state when rendering

			template <class GraphicsMath>
			inline void _Set_render_props(QPainter& painter, const basic_render_props<_Qt_graphics_surfaces<GraphicsMath>>& r) {
				const auto& props = r;
				const auto m = props.surface_matrix();
				QTransform qtm = QTransform(m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21());
				painter.setWorldTransform(qtm);
				// Clear all render hint flags; antialias::best uses all render hint flags that are used in _Antialias_to_qpainter_renderhints so this clears all of them.
				painter.setRenderHints(_Antialias_to_qpainter_renderhints(antialias::best), false);
				if (props.antialiasing() != antialias::none) {
					// Set appropriate render hint flags. If the request was for antialias::none then the render hint flags state is already correct because of the previous clearing of all flags.
					painter.setRenderHints(_Antialias_to_qpainter_renderhints(props.antialiasing()), true);
				}
				// Note: Not all compositing operators are supported; specifically, saturate and the hsl_* operators are not supported in Qt. Will need to explore how to handle them later. saturate should probably be eliminated from the proposal, but the hsl_* are needed for proper PDF support so they are a harder issue. Might need to do them manually. Ugh.
				painter.setCompositionMode(_Compositing_operator_to_qpainter_compositionmode(props.compositing()));
			}

			template <class GraphicsMath>
			inline void _Set_clip_props(QPainter& painter, const basic_clip_props<_Qt_graphics_surfaces<GraphicsMath>>& c) {
				const auto& props = c.data();
				if (props.boxclip.has_value()) {
					auto boxclip = props.boxclip.value();
					painter.setClipRect(static_cast<int>(boxclip.x()), static_cast<int>(boxclip.y()), static_cast<int>(boxclip.width()), static_cast<int>(boxclip.height()));
					//cairo_fill_rule_t fr = cairo_get_fill_rule(context);
					//cairo_set_fill_rule(context, _Fill_rule_to_cairo_fill_rule_t(props.fr));
					//cairo_new_path(context);

					//cairo_append_path(context, props.clip.value().data().path.get());
					//cairo_clip(context);
					//// Restore saved state
					//cairo_set_fill_rule(context, fr);
				}
				else {
					if (props.pathclip.has_value()) {
						auto path = QPainterPath(*(props.pathclip.value().data().path));
						//auto fillrule = path.fillRule();
						path.setFillRule(_Fill_rule_to_qt_fillrule(props.fr));
						painter.setClipPath(path);
						//path.setFillRule(fillrule);
					}
					else {
						painter.setClipping(false);
					}
				}
			}

			template <class GraphicsMath>
			inline QPainterPath _Set_stroke_props(QPainter& painter, QPainterPath& path, const basic_brush<_Qt_graphics_surfaces<GraphicsMath>>& b, const basic_stroke_props<_Qt_graphics_surfaces<GraphicsMath>>& s, float miterMax, const basic_dashes<_Qt_graphics_surfaces<GraphicsMath>>& ds) {
				const auto& props = s.data();
				QPen pen = QPen(*(b.data().brush), props._Line_width, (ds.data().pattern.empty() ? Qt::SolidLine : Qt::CustomDashLine), _Line_cap_to_qt_pencapstyle(props._Line_cap), _Line_join_to_qt_penjoinstyle(props._Line_join));
				if (props._Line_join == line_join::miter) {
					pen.setMiterLimit(::std::min<float>(miterMax, props._Miter_limit));
				}
				if (pen.style() == Qt::CustomDashLine) {
					const auto& d = ds.data();
					//const auto& dPattern = d.pattern;
					pen.setDashOffset(d.offset);
					QVector<qreal> dashPattern;
					auto lw = props._Line_width;
					for (const auto& val : d.pattern) {
						dashPattern.push_back(val / lw);
					}
					pen.setDashPattern(dashPattern);
				}
				pen.setBrush(*(b.data().brush));
				QPainterPathStroker stroker(pen);
				//stroker.setCapStyle(pen.capStyle());
				//stroker.setJoinStyle(pen.joinStyle());
				//stroker.setMiterLimit(pen.miterLimit());
				//stroker.setStyle(pen.style());
				//if (stroker.style == Qt::CustomDashLine) {
				//	stroker.setDashOffset(pen.dashOffset());
				//	stroker.setDashPattern(pen.dashPattern());
				//}
				//stroker.setWidth(pen.widthF());
				auto result = stroker.createStroke(path);
				result.setFillRule(Qt::WindingFill);
				pen.setWidth(0);
				pen.setStyle(Qt::NoPen);
				painter.setPen(pen);
				return result;
			}

			template <class GraphicsMath>
			inline void _Set_brush_props(QPainter& painter, const basic_brush<_Qt_graphics_surfaces<GraphicsMath>>& brush, const basic_brush_props<_Qt_graphics_surfaces<GraphicsMath>>& bp) {
				const auto& props = bp;
				// TODO: For now, wrap_mode and filter are both ignored; need to fix this. Our filter converter in xqt_helpers.h only works when we know in advance the size the QBrush's underlying QImage will be scaled to such that we can pull the QImage out, scale it with the appropriate filter, then use brush.setTextureImage to replace the original. Maybe this can be done by checking the matrix to see if it does scaling and if so we'll scale it ourselves and then zero out the matrix's scaling? wrap_mode will probably have to be done manually along the lines of how it's done in the coregraphics backend.
				// We now support wrap modes for gradient brushes. They don't matter for solid color brushes. All that's left is surface brushes.
				auto nonConstBrush = const_cast<basic_brush<_Qt_graphics_surfaces<GraphicsMath>>&>(brush);
				if (nonConstBrush.type() == brush_type::linear) {
					QLinearGradient gradient = nonConstBrush.data().linearGradient.value();
					gradient.setSpread(_Wrap_mode_to_qgradient_spread(bp.wrap_mode()));
					auto& brushPtr = nonConstBrush.data().brush;
					auto updatedBrush = make_shared<QBrush>(gradient);
					brushPtr.swap(updatedBrush);
				}
				if (nonConstBrush.type() == brush_type::radial) {
					QRadialGradient gradient = nonConstBrush.data().radialGradient.value();
					gradient.setSpread(_Wrap_mode_to_qgradient_spread(bp.wrap_mode()));
					auto& brushPtr = nonConstBrush.data().brush;
					auto updatedBrush = make_shared<QBrush>(gradient);
					brushPtr.swap(updatedBrush);
				}
				const auto& m = props.brush_matrix();
				QMatrix matrix{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
				nonConstBrush.data().brush->setMatrix(matrix);
				painter.setBrush(*(nonConstBrush.data().brush));
				painter.setBrushOrigin(QPointF(-m.m20(), -m.m21()));
			}

			template <class GraphicsSurfaces>
			inline void _Set_mask_props(const basic_mask_props<GraphicsSurfaces>& mp, const basic_brush<GraphicsSurfaces>& mb) {
				// TODO: Qt doesn't have a direct mask function so it'll need to be implemented using an additional "working space" image_surface that we can use to draw the mask image/brush (alpha only, all other channels zeroed out) then draw the image to that using probably the dest_over or dest_atop compositing_op, then draw the result to the original surface using over. Need to fiddle around with it to get the right operators.
				basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type> maskMatrix = mp.mask_matrix();
				QMatrix m(maskMatrix.m00(), maskMatrix.m01(), maskMatrix.m10(), maskMatrix.m11(), maskMatrix.m20(), maskMatrix.m21());
				mb.data().brush->setMatrix(m);
				// TODO: For now, wrap_mode and filter are both ignored; need to fix this. Our filter converter in xqt_helpers.h only works when we know in advance the size the QBrush's underlying QImage will be scaled to such that we can pull the QImage out, scale it with the appropriate filter, then use brush.setTextureImage to replace the original. Maybe this can be done by checking the matrix to see if it does scaling and if so we'll scale it ourselves and then zero out the matrix's scaling? wrap_mode will probably have to be done manually along the lines of how it's done in the coregraphics

				//const auto& props = mp;
				//auto p = b.data().brush.get();
				//cairo_pattern_set_extend(p, _Extend_to_cairo_extend_t(props.wrap_mode()));
				//cairo_pattern_set_filter(p, _Filter_to_cairo_filter_t(props.filter()));
				//const auto& m = props.mask_matrix();
				//cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
				//cairo_pattern_set_matrix(p, &cm);
			}

			template<class GraphicsMath>
			inline basic_display_point<GraphicsMath> _Qt_graphics_surfaces<GraphicsMath>::surfaces::max_dimensions() noexcept {
				return basic_display_point<GraphicsMath>(16384, 16384); // This takes up 1 GB of RAM, you probably don't want to do this. 2048x2048 is the max size for hardware that meets 9_1 specs (i.e. quite low powered or really old). Probably much more reasonable.
			}

			// TODO: Once these copy_surface functions are done, the rest should be fine as-is since it's just command lists calling io2d API functions on surfaces.
			template <class GraphicsMath>
			inline basic_image_surface<_Qt_graphics_surfaces<GraphicsMath>> _Qt_graphics_surfaces<GraphicsMath>::surfaces::copy_surface(basic_image_surface<_Qt_graphics_surfaces<GraphicsMath>>& sfc) noexcept {

				basic_image_surface<_Qt_graphics_surfaces> retSfc(sfc.format(), sfc.dimensions().x(), sfc.dimensions().y());
				retSfc.data().ppi = sfc.data().ppi;
				retSfc.data().surface = sfc.data().surface.copy();
				//auto srcSfc = cairo_surface_map_to_image(sfc.data().surface.get(), nullptr);
				//auto destSfc = cairo_surface_map_to_image(retSfc.data().surface.get(), nullptr);
				//auto srcSize = cairo_image_surface_get_height(srcSfc) * cairo_image_surface_get_stride(srcSfc);
				//auto srcData = cairo_image_surface_get_data(srcSfc);
				//auto destData = cairo_image_surface_get_data(destSfc);
				//memcpy(destData, srcData, srcSize);
				//cairo_surface_unmap_image(retSfc.data().surface.get(), destSfc);
				//cairo_surface_unmap_image(sfc.data().surface.get(), srcSfc);
				return retSfc;
			}

			template <class GraphicsMath>
			inline basic_image_surface<_Qt_graphics_surfaces<GraphicsMath>> _Qt_graphics_surfaces<GraphicsMath>::surfaces::copy_surface(basic_output_surface<_Qt_graphics_surfaces>& sfc) noexcept {
				// TODO: implement this once output_surface is implemented.
				throw ::std::runtime_error("Not yet implemented.");

				//basic_image_surface<_Qt_graphics_surfaces> retSfc(sfc.format(), sfc.dimensions().x(), sfc.dimensions().y());
				//retSfc.data().ppi = sfc.data().ppi;
				//auto srcSfc = cairo_surface_map_to_image(sfc.data().surface.get(), nullptr);
				//auto destSfc = cairo_surface_map_to_image(retSfc.data().surface.get(), nullptr);
				//auto srcSize = cairo_image_surface_get_height(srcSfc) * cairo_image_surface_get_stride(srcSfc);
				//auto srcData = cairo_image_surface_get_data(srcSfc);
				//auto destData = cairo_image_surface_get_data(destSfc);
				//memcpy(destData, srcData, srcSize);
				//cairo_surface_unmap_image(retSfc.data().surface.get(), destSfc);
				//cairo_surface_unmap_image(sfc.data().surface.get(), srcSfc);
				//return retSfc;
			}

			// image surface command list

			template <class GraphicsSurfaces, class TItem>
			struct _Command_list_image_surface_visitor {
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::clear>, int> = 0>
				static void interpret(const T & item, basic_image_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().clear();
					}
					else {
						sfc.clear();
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::paint>, int> = 0>
				static void interpret(const T & item, basic_image_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().paint(item.brush(), item.brush_props(), item.render_props(), item.clip_props());
					}
					else {
						sfc.paint(item.brush(), item.brush_props(), item.render_props(), item.clip_props());
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::stroke>, int> = 0>
				static void interpret(const T & item, basic_image_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().stroke(item.brush(), item.path(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
					}
					else {
						sfc.stroke(item.brush(), item.path(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::fill>, int> = 0>
				static void interpret(const T & item, basic_image_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().fill(item.brush(), item.path(), item.brush_props(), item.render_props(), item.clip_props());
					}
					else {
						sfc.fill(item.brush(), item.path(), item.brush_props(), item.render_props(), item.clip_props());
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::mask>, int> = 0>
				static void interpret(const T & item, basic_image_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().mask(item.brush(), item.mask_brush(), item.brush_props(), item.mask_props(), item.render_props(), item.clip_props());
					}
					else {
						sfc.mask(item.brush(), item.mask_brush(), item.brush_props(), item.mask_props(), item.render_props(), item.clip_props());
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::draw_text>, int> = 0>
				static void interpret(const T & item, basic_image_surface<GraphicsSurfaces> & sfc) noexcept {
					if (::std::holds_alternative<basic_point_2d<typename GraphicsSurfaces::graphics_math_type>>(item.location())) {
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> pt = ::std::get<basic_point_2d<typename GraphicsSurfaces::graphics_math_type>>(item.location());
						if (item.surface()) {
							item.surface().value().get().draw_text(pt, item.brush(), item.font(), item.text(), item.text_props(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
						}
						else {
							sfc.draw_text(pt, item.brush(), item.font(), item.text(), item.text_props(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
						}
					}
					else {
						basic_bounding_box<typename GraphicsSurfaces::graphics_math_type> bb = ::std::get<basic_bounding_box<typename GraphicsSurfaces::graphics_math_type>>(item.location());
						if (item.surface()) {
							item.surface().value().get().draw_text(bb, item.brush(), item.font(), item.text(), item.text_props(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
						}
						else {
							sfc.draw_text(bb, item.brush(), item.font(), item.text(), item.text_props(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
						}
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::run_function>, int> = 0>
				static void interpret(const T & item, basic_image_surface<GraphicsSurfaces> & sfc) noexcept {
					(::std::get<function<void(basic_image_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>>(item.func()))(sfc, item.surface(), item.user_data());
				}
			};

			template <class GraphicsMath, class InputIterator>
			inline ::std::future<void> _Process_command_list_image_surface(basic_image_surface<_Qt_graphics_surfaces<GraphicsMath>>& sfc, InputIterator first, InputIterator last) {
				::std::promise<void> temp_prms;
				auto ftr = temp_prms.get_future();

				::std::thread thr([prms = ::std::move(temp_prms), &sfc, first, last]() mutable {
					for (auto val = first; val != last; val++) {
						::std::visit([&sfc](auto&& item) {
							using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
							_Command_list_image_surface_visitor<_Qt_graphics_surfaces<GraphicsMath>, T>::template interpret<T>(item, sfc);
							}, *val);
					}
					prms.set_value();
				});
				thr.detach();
				return ftr;
			}



			// output surface command list

			template <class GraphicsSurfaces, class TItem>
			struct _Command_list_output_surface_visitor {
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::clear>, int> = 0>
				static void interpret(const T & item, basic_output_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().clear();
					}
					else {
						sfc.clear();
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::paint>, int> = 0>
				static void interpret(const T & item, basic_output_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().paint(item.brush(), item.brush_props(), item.render_props(), item.clip_props());
					}
					else {
						sfc.paint(item.brush(), item.brush_props(), item.render_props(), item.clip_props());
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::stroke>, int> = 0>
				static void interpret(const T & item, basic_output_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().stroke(item.brush(), item.path(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
					}
					else {
						sfc.stroke(item.brush(), item.path(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::fill>, int> = 0>
				static void interpret(const T & item, basic_output_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().fill(item.brush(), item.path(), item.brush_props(), item.render_props(), item.clip_props());
					}
					else {
						sfc.fill(item.brush(), item.path(), item.brush_props(), item.render_props(), item.clip_props());
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::mask>, int> = 0>
				static void interpret(const T & item, basic_output_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().mask(item.brush(), item.mask_brush(), item.brush_props(), item.mask_props(), item.render_props(), item.clip_props());
					}
					else {
						sfc.mask(item.brush(), item.mask_brush(), item.brush_props(), item.mask_props(), item.render_props(), item.clip_props());
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::draw_text>, int> = 0>
				static void interpret(const T & item, basic_output_surface<GraphicsSurfaces> & sfc) noexcept {
					if (::std::holds_alternative<basic_point_2d<typename GraphicsSurfaces::graphics_math_type>>(item.location())) {
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> pt = ::std::get<basic_point_2d<typename GraphicsSurfaces::graphics_math_type>>(item.location());
						if (item.surface()) {
							item.surface().value().get().draw_text(pt, item.brush(), item.font(), item.text(), item.text_props(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
						}
						else {
							sfc.draw_text(pt, item.brush(), item.font(), item.text(), item.text_props(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
						}
					}
					else {
						basic_bounding_box<typename GraphicsSurfaces::graphics_math_type> bb = ::std::get<basic_bounding_box<typename GraphicsSurfaces::graphics_math_type>>(item.location());
						if (item.surface()) {
							item.surface().value().get().draw_text(bb, item.brush(), item.font(), item.text(), item.text_props(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
						}
						else {
							sfc.draw_text(bb, item.brush(), item.font(), item.text(), item.text_props(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
						}
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::run_function>, int> = 0>
				static void interpret(const T & item, basic_output_surface<GraphicsSurfaces> & sfc) noexcept {
					(::std::get<function<void(basic_output_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>>(item.func()))(sfc, item.surface(), item.user_data());
				}
			};

			template <class GraphicsMath, class InputIterator>
			inline void _Process_command_list_output_surface(basic_output_surface<_Qt_graphics_surfaces<GraphicsMath>>& sfc, InputIterator first, InputIterator last) {
				for (auto val = first; val != last; val++) {
					::std::visit([&sfc](auto&& item) {
						using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
						_Command_list_output_surface_visitor<_Qt_graphics_surfaces<GraphicsMath>, T>::template interpret<T>(item, sfc);
						}, *val);
				}
			}

			// unmanaged surface command list

			template <class GraphicsSurfaces, class TItem>
			struct _Command_list_unmanaged_output_surface_visitor {
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::clear>, int> = 0>
				static void interpret(const T & item, basic_unmanaged_output_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().clear();
					}
					else {
						sfc.clear();
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::paint>, int> = 0>
				static void interpret(const T & item, basic_unmanaged_output_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().paint(item.brush(), item.brush_props(), item.render_props(), item.clip_props());
					}
					else {
						sfc.paint(item.brush(), item.brush_props(), item.render_props(), item.clip_props());
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::stroke>, int> = 0>
				static void interpret(const T & item, basic_unmanaged_output_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().stroke(item.brush(), item.path(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
					}
					else {
						sfc.stroke(item.brush(), item.path(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::fill>, int> = 0>
				static void interpret(const T & item, basic_unmanaged_output_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().fill(item.brush(), item.path(), item.brush_props(), item.render_props(), item.clip_props());
					}
					else {
						sfc.fill(item.brush(), item.path(), item.brush_props(), item.render_props(), item.clip_props());
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::mask>, int> = 0>
				static void interpret(const T & item, basic_unmanaged_output_surface<GraphicsSurfaces> & sfc) noexcept {
					if (item.surface()) {
						item.surface().value().get().mask(item.brush(), item.mask_brush(), item.brush_props(), item.mask_props(), item.render_props(), item.clip_props());
					}
					else {
						sfc.mask(item.brush(), item.mask_brush(), item.brush_props(), item.mask_props(), item.render_props(), item.clip_props());
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::draw_text>, int> = 0>
				static void interpret(const T & item, basic_unmanaged_output_surface<GraphicsSurfaces> & sfc) noexcept {
					if (::std::holds_alternative<basic_point_2d<typename GraphicsSurfaces::graphics_math_type>>(item.location())) {
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> pt = ::std::get<basic_point_2d<typename GraphicsSurfaces::graphics_math_type>>(item.location());
						if (item.surface()) {
							item.surface().value().get().draw_text(pt, item.brush(), item.font(), item.text(), item.text_props(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
						}
						else {
							sfc.draw_text(pt, item.brush(), item.font(), item.text(), item.text_props(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
						}
					}
					else {
						basic_bounding_box<typename GraphicsSurfaces::graphics_math_type> bb = ::std::get<basic_bounding_box<typename GraphicsSurfaces::graphics_math_type>>(item.location());
						if (item.surface()) {
							item.surface().value().get().draw_text(bb, item.brush(), item.font(), item.text(), item.text_props(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
						}
						else {
							sfc.draw_text(bb, item.brush(), item.font(), item.text(), item.text_props(), item.brush_props(), item.stroke_props(), item.dashes(), item.render_props(), item.clip_props());
						}
					}
				}
				template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_commands<GraphicsSurfaces>::run_function>, int> = 0>
				static void interpret(const T & item, basic_unmanaged_output_surface<GraphicsSurfaces> & sfc) noexcept {
					(::std::get<function<void(basic_unmanaged_output_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>>(item.func()))(sfc, item.surface(), item.user_data());
				}
			};

			template <class GraphicsMath, class InputIterator>
			inline void _Process_command_list_unmanaged_output_surface(basic_unmanaged_output_surface<_Qt_graphics_surfaces<GraphicsMath>>& sfc, InputIterator first, InputIterator last) {
				for (auto val = first; val != last; val++) {
					::std::visit([&sfc](auto&& item) {
						using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
						_Command_list_output_surface_visitor<_Qt_graphics_surfaces<GraphicsMath>, T>::template interpret<T>(item, sfc);
						}, *val);
				}
			}
		}
	}
}

#include "xqt_surfaces_image_impl.h"
