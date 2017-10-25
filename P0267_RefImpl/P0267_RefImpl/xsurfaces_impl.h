#pragma once

#include "xsurfaces.h"

#if defined(_WIN32) || defined(_WIN64)
#include "xinclwindows_h.h"
#endif

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				// dashes

				template<class GraphicsSurfaces>
				inline const typename basic_dashes<GraphicsSurfaces>::_Data_type& basic_dashes<GraphicsSurfaces>::_Get_data() const noexcept {
					return _Data;
				}

				template <class GraphicsSurfaces>
				inline basic_dashes<GraphicsSurfaces>::basic_dashes() noexcept
					: _Data(GraphicsSurfaces::create_dashes()) {}
				template <class GraphicsSurfaces>
				template <class ForwardIterator>
				inline basic_dashes<GraphicsSurfaces>::basic_dashes(float offset, ForwardIterator first, ForwardIterator last)
					: _Data(GraphicsSurfaces::create_dashes(offset, first, last)) {}
				template <class GraphicsSurfaces>
				inline basic_dashes<GraphicsSurfaces>::basic_dashes(float offset, ::std::initializer_list<float> il)
					: _Data(GraphicsSurfaces::create_dashes(offset, il)) {}

				// image_surface

				template <class GraphicsSurfaces>
				inline typename basic_image_surface<GraphicsSurfaces>::_Data_type& basic_image_surface<GraphicsSurfaces>::_Get_data() noexcept {
					return _Data;
				}
				template <class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>::basic_image_surface(io2d::format fmt, int width, int height)
					: _Data(GraphicsSurfaces::create_image_surface(fmt, width, height)) {
				}

#ifdef _Filesystem_support_test
				template <class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>::basic_image_surface(filesystem::path f, image_file_format iff, io2d::format fmt)
					: _Data(GraphicsSurfaces::create_image_surface(f, iff, fmt)) {
				}
				template <class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>::basic_image_surface(filesystem::path f, image_file_format iff, io2d::format fmt, error_code& ec) noexcept
					: _Data(GraphicsSurfaces::create_image_surface(f, iff, fmt, ec)) {
				}
#else
				template <class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>::basic_image_surface(::std::string f, image_file_format iff, io2d::format fmt)
					: _Data(GraphicsSurfaces::create_image_surface(f, iff, fmt)) {
				}
				template <class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>::basic_image_surface(::std::string f, image_file_format iff, io2d::format fmt, error_code& ec) noexcept
					: _Data(GraphicsSurfaces::create_image_surface(f, iff, fmt, ec)) {
				}
#endif
				template<class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>::basic_image_surface(basic_image_surface&& val) noexcept 
					: _Data(move(GraphicsSurfaces::move_image_surface(move(val._Data)))) {
				}

				template<class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>& basic_image_surface<GraphicsSurfaces>::operator=(basic_image_surface&& val) noexcept {
					if (this != &val) {
						_Data = move(GraphicsSurfaces::move_image_surface(move(val._Data)));
					}
					return *this;
				}

				template<class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>::~basic_image_surface() noexcept {
					GraphicsSurfaces::destroy(_Data);
				}

#ifdef _Filesystem_support_test
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::save(filesystem::path p, image_file_format iff) {
					GraphicsSurfaces::save(_Data, p, iff);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::save(filesystem::path p, image_file_format iff, error_code& ec) noexcept {
					GraphicsSurfaces::save(_Data, p, iff, ec);
				}
#else
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::save(::std::string p, image_file_format iff) {
					GraphicsSurfaces::save(_Data, p, iff);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::save(::std::string p, image_file_format iff, error_code& ec) noexcept {
					GraphicsSurfaces::save(_Data, p, iff, ec);
				}
#endif

				template<class GraphicsSurfaces>
				inline basic_display_point<typename basic_image_surface<GraphicsSurfaces>::graphics_math_type> basic_image_surface<GraphicsSurfaces>::max_dimensions() noexcept {
					return GraphicsSurfaces::max_dimensions();
				}
				template <class GraphicsSurfaces>
				inline io2d::format basic_image_surface<GraphicsSurfaces>::format() const noexcept {
					return GraphicsSurfaces::format(_Data);
				}
				template<class GraphicsSurfaces>
				inline basic_display_point<typename basic_image_surface<GraphicsSurfaces>::graphics_math_type> basic_image_surface<GraphicsSurfaces>::dimensions() const noexcept {
					return GraphicsSurfaces::dimensions(_Data);
				}

				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::clear() {
					GraphicsSurfaces::clear(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::flush() {
					GraphicsSurfaces::flush(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::flush(error_code& ec) noexcept {
					GraphicsSurfaces::flush(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::mark_dirty() {
					GraphicsSurfaces::mark_dirty(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::mark_dirty(error_code& ec) noexcept {
					GraphicsSurfaces::mark_dirty(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents) {
					GraphicsSurfaces::mark_dirty(_Data, extents);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents, error_code& ec) noexcept {
					GraphicsSurfaces::mark_dirty(_Data, extents, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::paint(_Data, b, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void basic_image_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<typename GraphicsSurfaces::graphics_math_type, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::stroke(_Data, b, basic_interpreted_path<GraphicsSurfaces>(pb), (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (sp == nullopt ? basic_stroke_props<GraphicsSurfaces>() : sp.value()), (d == nullopt ? basic_dashes<GraphicsSurfaces>() : d.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::stroke(_Data, b, ip, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (sp == nullopt ? basic_stroke_props<GraphicsSurfaces>() : sp.value()), (d == nullopt ? basic_dashes<GraphicsSurfaces>() : d.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void basic_image_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<typename GraphicsSurfaces::graphics_math_type, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::fill(_Data, b, basic_interpreted_path<GraphicsSurfaces>(pb), (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::fill(_Data, b, ip, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_mask_props<GraphicsSurfaces>>& mp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::mask(_Data, b, mb, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (mp == nullopt ? basic_brush_props<GraphicsSurfaces>() : mp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}

				template<class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces> copy_image_surface(basic_image_surface<GraphicsSurfaces>& sfc) noexcept {
					basic_image_surface<GraphicsSurfaces> retSfc(sfc.format(), sfc.dimensions().x(), sfc.dimensions().y());
					auto srcSfc = cairo_surface_map_to_image(sfc._Get_data().surface.get(), nullptr);
					auto destSfc = cairo_surface_map_to_image(retSfc._Get_data().surface.get(), nullptr);
					auto srcSize = cairo_image_surface_get_height(srcSfc) * cairo_image_surface_get_stride(srcSfc);
					auto srcData = cairo_image_surface_get_data(srcSfc);
					auto destData = cairo_image_surface_get_data(destSfc);
					memcpy(destData, srcData, srcSize);
					cairo_surface_unmap_image(retSfc._Get_data().surface.get(), destSfc);
					cairo_surface_unmap_image(sfc._Get_data().surface.get(), srcSfc);
					return retSfc;
				}

				// output surface

				template <class GraphicsSurfaces>
				inline basic_output_surface<GraphicsSurfaces>::basic_output_surface(int preferredWidth,
					int preferredHeight, io2d::format preferredFormat, io2d::scaling scl,
					io2d::refresh_rate rr, float fps)
					: _Data(move(GraphicsSurfaces::create_output_surface(preferredWidth, preferredHeight, preferredFormat, scl, rr, fps))) {}
				template <class GraphicsSurfaces>
				inline basic_output_surface<GraphicsSurfaces>::basic_output_surface(int preferredWidth,
					int preferredHeight, io2d::format preferredFormat, error_code& ec, io2d::scaling scl,
					io2d::refresh_rate rr, float fps) noexcept
					: _Data(move(GraphicsSurfaces::create_output_surface(preferredWidth, preferredHeight, preferredFormat, ec, scl, rr, fps))) {}
				template <class GraphicsSurfaces>
				inline basic_output_surface<GraphicsSurfaces>::basic_output_surface(int preferredWidth,
					int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth,
					int preferredDisplayHeight, io2d::scaling scl, io2d::refresh_rate rr, float fps)
					: _Data(move(GraphicsSurfaces::create_output_surface(preferredWidth, preferredHeight, preferredFormat, preferredDisplayWidth, preferredDisplayHeight, scl, rr, fps))) {}
				template <class GraphicsSurfaces>
				inline basic_output_surface<GraphicsSurfaces>::basic_output_surface(int preferredWidth,
					int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth,
					int preferredDisplayHeight, error_code& ec, io2d::scaling scl, io2d::refresh_rate rr,
					float fps) noexcept
					: _Data(move(GraphicsSurfaces::create_output_surface(preferredWidth, preferredHeight, preferredFormat, preferredDisplayWidth, preferredDisplayHeight, ec, scl, rr, fps))) {}

				template <class GraphicsSurfaces>
				inline basic_output_surface<GraphicsSurfaces>::~basic_output_surface() noexcept {
					GraphicsSurfaces::destroy(_Data);
				}

				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::redraw_required() noexcept {
					GraphicsSurfaces::redraw_required(_Data);
				}
				template <class GraphicsSurfaces>
				inline typename GraphicsSurfaces::show_return_data_type basic_output_surface<GraphicsSurfaces>::begin_show() {
					return GraphicsSurfaces::begin_show(_Data, this, *this);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::end_show() {
					GraphicsSurfaces::end_show(_Data);
				}

				template <class GraphicsSurfaces>
				inline typename basic_output_surface<GraphicsSurfaces>::_Data_type& basic_output_surface<GraphicsSurfaces>::_Get_data() noexcept {
					return _Data;
				}

				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::clear() {
					GraphicsSurfaces::clear(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::flush() {
					GraphicsSurfaces::flush(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::flush(error_code& ec) noexcept {
					GraphicsSurfaces::flush(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::mark_dirty() {
					GraphicsSurfaces::mark_dirty(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::mark_dirty(error_code& ec) noexcept {
					GraphicsSurfaces::mark_dirty(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents) {
					GraphicsSurfaces::mark_dirty(_Data, extents);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents, error_code& ec) noexcept {
					GraphicsSurfaces::mark_dirty(_Data, extents, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::paint(_Data, b, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void basic_output_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<typename GraphicsSurfaces::graphics_math_type, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::stroke(_Data, b, basic_interpreted_path<GraphicsSurfaces>(pb), (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (sp == nullopt ? basic_stroke_props<GraphicsSurfaces>() : sp.value()), (d == nullopt ? basic_dashes<GraphicsSurfaces>() : d.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::stroke(_Data, b, ip, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (sp == nullopt ? basic_stroke_props<GraphicsSurfaces>() : sp.value()), (d == nullopt ? basic_dashes<GraphicsSurfaces>() : d.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void basic_output_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<typename GraphicsSurfaces::graphics_math_type, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::fill(_Data, b, basic_interpreted_path<GraphicsSurfaces>(pb), (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::fill(_Data, b, ip, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_mask_props<GraphicsSurfaces>>& mp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::mask(_Data, b, mb, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (mp == nullopt ? basic_brush_props<GraphicsSurfaces>() : mp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}

				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::draw_callback(const function<void(basic_output_surface& sfc)>& fn) {
					GraphicsSurfaces::draw_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::size_change_callback(const function<void(basic_output_surface& sfc)>& fn) {
					GraphicsSurfaces::size_change_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::dimensions(basic_display_point<graphics_math_type> dp) {
					GraphicsSurfaces::dimensions(_Data, dp);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::dimensions(basic_display_point<graphics_math_type> dp, error_code& ec) noexcept {
					GraphicsSurfaces::dimensions(_Data, dp, ec);
				}
				template<class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::display_dimensions(basic_display_point<graphics_math_type> dp) {
					GraphicsSurfaces::display_dimensions(_Data, dp);
				}
				template<class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::display_dimensions(basic_display_point<graphics_math_type> dp, error_code & ec) noexcept {
					GraphicsSurfaces::display_dimensions(_Data, dp, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::scaling(experimental::io2d::scaling scl) noexcept {
					GraphicsSurfaces::scaling(_Data, scl);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::user_scaling_callback(const function<basic_bounding_box<graphics_math_type>(const basic_output_surface&, bool&)>& fn) {
					GraphicsSurfaces::user_scaling_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::letterbox_brush(const optional<basic_brush<GraphicsSurfaces>>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept {
					GraphicsSurfaces::letterbox_brush(_Data, b, bp);
				}
				template<class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::letterbox_brush_props(const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept {
					GraphicsSurfaces::letterbox_brush_props(_Data, bp);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::auto_clear(bool val) noexcept {
					GraphicsSurfaces::auto_clear(_Data, val);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::redraw_required(bool val) noexcept {
					GraphicsSurfaces::redraw_required(_Data, val);
				}
				template <class GraphicsSurfaces>
				inline io2d::format basic_output_surface<GraphicsSurfaces>::format() const noexcept {
					return GraphicsSurfaces::format(_Data);
				}
				template <class GraphicsSurfaces>
				inline basic_display_point<typename basic_output_surface<GraphicsSurfaces>::graphics_math_type> basic_output_surface<GraphicsSurfaces>::dimensions() const noexcept {
					return GraphicsSurfaces::dimensions(_Data);
				}
				template <class GraphicsSurfaces>
				inline basic_display_point<typename basic_output_surface<GraphicsSurfaces>::graphics_math_type> basic_output_surface<GraphicsSurfaces>::max_dimensions() const noexcept {
					return GraphicsSurfaces::max_dimensions(_Data);
				}
				template<class GraphicsSurfaces>
				inline basic_display_point<typename basic_output_surface<GraphicsSurfaces>::graphics_math_type> basic_output_surface<GraphicsSurfaces>::display_dimensions() const noexcept {
					return GraphicsSurfaces::display_dimensions(_Data);
				}
				template<class GraphicsSurfaces>
				inline basic_display_point<typename basic_output_surface<GraphicsSurfaces>::graphics_math_type> basic_output_surface<GraphicsSurfaces>::max_display_dimensions() const noexcept {
					return GraphicsSurfaces::max_display_dimensions(_Data);
				}
				template <class GraphicsSurfaces>
				inline io2d::scaling basic_output_surface<GraphicsSurfaces>::scaling() const noexcept {
					return GraphicsSurfaces::scaling(_Data);
				}
				template <class GraphicsSurfaces>
				inline optional<basic_brush<GraphicsSurfaces>> basic_output_surface<GraphicsSurfaces>::letterbox_brush() const noexcept {
					return GraphicsSurfaces::letterbox_brush(_Data);
				}
				template <class GraphicsSurfaces>
				inline optional<basic_brush_props<GraphicsSurfaces>> basic_output_surface<GraphicsSurfaces>::letterbox_brush_props() const noexcept {
					return GraphicsSurfaces::letterbox_brush_props(_Data);
				}
				template <class GraphicsSurfaces>
				inline bool basic_output_surface<GraphicsSurfaces>::auto_clear() const noexcept {
					return GraphicsSurfaces::auto_clear(_Data);
				}


				// unmanaged output surface

				template <class GraphicsSurfaces>
				inline basic_unmanaged_output_surface<GraphicsSurfaces>::basic_unmanaged_output_surface(data_type&& data) noexcept
					: _Data(move(data)) {
				}

				template <class GraphicsSurfaces>
				inline basic_unmanaged_output_surface<GraphicsSurfaces>::basic_unmanaged_output_surface(basic_unmanaged_output_surface&& val) noexcept {
					_Data = move(GraphicsSurfaces::move_unmanaged_output_surface(move(val._Data)));
				}
				template <class GraphicsSurfaces>
				inline basic_unmanaged_output_surface<GraphicsSurfaces>& basic_unmanaged_output_surface<GraphicsSurfaces>::operator=(basic_unmanaged_output_surface&& val) noexcept {
					if (this != &val) {
						_Data = move(GraphicsSurfaces::move_unmanaged_output_surface(move(val._Data)));
					}
					return *this;
				}
				template <class GraphicsSurfaces>
				inline basic_unmanaged_output_surface<GraphicsSurfaces>::~basic_unmanaged_output_surface() noexcept {
					GraphicsSurfaces::destroy(_Data);
				}

				template<class GraphicsSurfaces>
				inline bool basic_unmanaged_output_surface<GraphicsSurfaces>::has_draw_callback() const noexcept {
					return GraphicsSurfaces::has_draw_callback(_Data);
				}

				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::invoke_draw_callback() {
					GraphicsSurfaces::invoke_draw_callback(_Data, *this);
				}
				template<class GraphicsSurfaces>
				inline bool basic_unmanaged_output_surface<GraphicsSurfaces>::has_size_change_callback() const noexcept {
					return GraphicsSurfaces::has_size_change_callback(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::invoke_size_change_callback() {
					GraphicsSurfaces::invoke_size_change_callback(_Data, *this);
				}
				template<class GraphicsSurfaces>
				inline bool basic_unmanaged_output_surface<GraphicsSurfaces>::has_user_scaling_callback() const noexcept {
					return GraphicsSurfaces::has_user_scaling_callback(_Data);
				}
				template <class GraphicsSurfaces>
				inline basic_bounding_box<typename GraphicsSurfaces::graphics_math_type> basic_unmanaged_output_surface<GraphicsSurfaces>::invoke_user_scaling_callback(bool& useLetterboxBrush) {
					GraphicsSurfaces::invoke_user_scaling_callback(_Data, *this, useLetterboxBrush);
				}

				template<class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::draw_to_output() {
					GraphicsSurfaces::draw_to_output(_Data, *this);
				}

				template <class GraphicsSurfaces>
				inline typename basic_unmanaged_output_surface<GraphicsSurfaces>::_Data_type& basic_unmanaged_output_surface<GraphicsSurfaces>::_Get_data() noexcept {
					return _Data;
				}

				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::clear() {
					GraphicsSurfaces::clear(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::flush() {
					GraphicsSurfaces::flush(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::flush(error_code& ec) noexcept {
					GraphicsSurfaces::flush(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::mark_dirty() {
					GraphicsSurfaces::mark_dirty(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::mark_dirty(error_code& ec) noexcept {
					GraphicsSurfaces::mark_dirty(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents) {
					GraphicsSurfaces::mark_dirty(_Data, extents);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents, error_code& ec) noexcept {
					GraphicsSurfaces::mark_dirty(_Data, extents, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::paint(_Data, b, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<typename GraphicsSurfaces::graphics_math_type, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::stroke(_Data, b, basic_interpreted_path<GraphicsSurfaces>(pb), (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (sp == nullopt ? basic_stroke_props<GraphicsSurfaces>() : sp.value()), (d == nullopt ? basic_dashes<GraphicsSurfaces>() : d.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::stroke(_Data, b, ip, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (sp == nullopt ? basic_stroke_props<GraphicsSurfaces>() : sp.value()), (d == nullopt ? basic_dashes<GraphicsSurfaces>() : d.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<typename GraphicsSurfaces::graphics_math_type, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::fill(_Data, b, basic_interpreted_path<GraphicsSurfaces>(pb), (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::fill(_Data, b, ip, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_mask_props<GraphicsSurfaces>>& mp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::mask(_Data, b, mb, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (mp == nullopt ? basic_brush_props<GraphicsSurfaces>() : mp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}

				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::draw_callback(const function<void(basic_unmanaged_output_surface& sfc)>& fn) {
					GraphicsSurfaces::draw_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::size_change_callback(const function<void(basic_unmanaged_output_surface& sfc)>& fn) {
					GraphicsSurfaces::size_change_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::dimensions(basic_display_point<graphics_math_type> dp) {
					GraphicsSurfaces::dimensions(_Data, dp);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::dimensions(basic_display_point<graphics_math_type> dp, error_code& ec) noexcept {
					GraphicsSurfaces::dimensions(_Data, dp, ec);
				}
				template<class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::display_dimensions(basic_display_point<graphics_math_type> dp) {
					GraphicsSurfaces::display_dimensions(_Data, dp);
				}
				template<class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::display_dimensions(basic_display_point<graphics_math_type> dp, error_code & ec) noexcept {
					GraphicsSurfaces::display_dimensions(_Data, dp, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::scaling(experimental::io2d::scaling scl) noexcept {
					GraphicsSurfaces::scaling(_Data, scl);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::user_scaling_callback(const function<basic_bounding_box<graphics_math_type>(const basic_unmanaged_output_surface&, bool&)>& fn) {
					GraphicsSurfaces::user_scaling_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::letterbox_brush(const optional<basic_brush<GraphicsSurfaces>>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept {
					GraphicsSurfaces::letterbox_brush(_Data, b, bp);
				}
				template<class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::letterbox_brush_props(const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept {
					GraphicsSurfaces::letterbox_brush_props(_Data, bp);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::auto_clear(bool val) noexcept {
					GraphicsSurfaces::auto_clear(_Data, val);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::redraw_required(bool val) noexcept {
					GraphicsSurfaces::redraw_required(_Data, val);
				}
				template <class GraphicsSurfaces>
				inline io2d::format basic_unmanaged_output_surface<GraphicsSurfaces>::format() const noexcept {
					return GraphicsSurfaces::format(_Data);
				}
				template <class GraphicsSurfaces>
				inline basic_display_point<typename basic_unmanaged_output_surface<GraphicsSurfaces>::graphics_math_type> basic_unmanaged_output_surface<GraphicsSurfaces>::dimensions() const noexcept {
					return GraphicsSurfaces::dimensions(_Data);
				}
				template <class GraphicsSurfaces>
				inline basic_display_point<typename basic_unmanaged_output_surface<GraphicsSurfaces>::graphics_math_type> basic_unmanaged_output_surface<GraphicsSurfaces>::max_dimensions() const noexcept {
					return GraphicsSurfaces::max_dimensions(_Data);
				}
				template<class GraphicsSurfaces>
				inline basic_display_point<typename basic_unmanaged_output_surface<GraphicsSurfaces>::graphics_math_type> basic_unmanaged_output_surface<GraphicsSurfaces>::display_dimensions() const noexcept {
					return GraphicsSurfaces::display_dimensions(_Data);
				}
				template<class GraphicsSurfaces>
				inline basic_display_point<typename basic_unmanaged_output_surface<GraphicsSurfaces>::graphics_math_type> basic_unmanaged_output_surface<GraphicsSurfaces>::max_display_dimensions() const noexcept {
					return GraphicsSurfaces::max_display_dimensions(_Data);
				}
				template <class GraphicsSurfaces>
				inline io2d::scaling basic_unmanaged_output_surface<GraphicsSurfaces>::scaling() const noexcept {
					return GraphicsSurfaces::scaling(_Data);
				}
				template <class GraphicsSurfaces>
				inline optional<basic_brush<GraphicsSurfaces>> basic_unmanaged_output_surface<GraphicsSurfaces>::letterbox_brush() const noexcept {
					return GraphicsSurfaces::letterbox_brush(_Data);
				}
				template <class GraphicsSurfaces>
				inline optional<basic_brush_props<GraphicsSurfaces>> basic_unmanaged_output_surface<GraphicsSurfaces>::letterbox_brush_props() const noexcept {
					return GraphicsSurfaces::letterbox_brush_props(_Data);
				}
				template <class GraphicsSurfaces>
				inline bool basic_unmanaged_output_surface<GraphicsSurfaces>::auto_clear() const noexcept {
					return GraphicsSurfaces::auto_clear(_Data);
				}
			}
		}
	}
}
