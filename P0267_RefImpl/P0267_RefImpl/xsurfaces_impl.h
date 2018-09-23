#pragma once

#include "xsurfaces.h"

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				// image_surface

				template <class GraphicsSurfaces>
				inline typename basic_image_surface<GraphicsSurfaces>::data_type& basic_image_surface<GraphicsSurfaces>::data() noexcept {
					return _Data;
				}
				template <class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>::basic_image_surface(io2d::format fmt, int width, int height)
					: _Data(GraphicsSurfaces::surfaces::create_image_surface(fmt, width, height)) {
				}

#ifdef _Filesystem_support_test
				template <class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>::basic_image_surface(filesystem::path f, image_file_format iff, io2d::format fmt)
					: _Data(GraphicsSurfaces::surfaces::create_image_surface(f, iff, fmt)) {
				}
				template <class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>::basic_image_surface(filesystem::path f, image_file_format iff, io2d::format fmt, error_code& ec) noexcept
					: _Data(GraphicsSurfaces::surfaces::create_image_surface(f, iff, fmt, ec)) {
				}
#else
				template <class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>::basic_image_surface(::std::string f, image_file_format iff, io2d::format fmt)
					: _Data(GraphicsSurfaces::surfaces::create_image_surface(f, iff, fmt)) {
				}
				template <class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>::basic_image_surface(::std::string f, image_file_format iff, io2d::format fmt, error_code& ec) noexcept
					: _Data(GraphicsSurfaces::surfaces::create_image_surface(f, iff, fmt, ec)) {
				}
#endif
				template<class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>::basic_image_surface(basic_image_surface&& val) noexcept 
					: _Data(move(GraphicsSurfaces::surfaces::move_image_surface(move(val._Data)))) {
				}

				template<class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>& basic_image_surface<GraphicsSurfaces>::operator=(basic_image_surface&& val) noexcept {
					if (this != &val) {
						_Data = move(GraphicsSurfaces::surfaces::move_image_surface(move(val._Data)));
					}
					return *this;
				}

				template<class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces>::~basic_image_surface() noexcept {
					GraphicsSurfaces::surfaces::destroy(_Data);
				}

#ifdef _Filesystem_support_test
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::save(filesystem::path p, image_file_format iff) {
					GraphicsSurfaces::surfaces::save(_Data, p, iff);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::save(filesystem::path p, image_file_format iff, error_code& ec) noexcept {
					GraphicsSurfaces::surfaces::save(_Data, p, iff, ec);
				}
#else
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::save(::std::string p, image_file_format iff) {
					GraphicsSurfaces::surfaces::save(_Data, p, iff);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::save(::std::string p, image_file_format iff, error_code& ec) noexcept {
					GraphicsSurfaces::surfaces::save(_Data, p, iff, ec);
				}
#endif

				template<class GraphicsSurfaces>
				inline basic_display_point<typename basic_image_surface<GraphicsSurfaces>::graphics_math_type> basic_image_surface<GraphicsSurfaces>::max_dimensions() noexcept {
					return GraphicsSurfaces::surfaces::max_dimensions();
				}
				template <class GraphicsSurfaces>
				inline io2d::format basic_image_surface<GraphicsSurfaces>::format() const noexcept {
					return GraphicsSurfaces::surfaces::format(_Data);
				}
				template<class GraphicsSurfaces>
				inline basic_display_point<typename basic_image_surface<GraphicsSurfaces>::graphics_math_type> basic_image_surface<GraphicsSurfaces>::dimensions() const noexcept {
					return GraphicsSurfaces::surfaces::dimensions(_Data);
				}

				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::clear() {
					GraphicsSurfaces::surfaces::clear(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::flush() {
					GraphicsSurfaces::surfaces::flush(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::flush(error_code& ec) noexcept {
					GraphicsSurfaces::surfaces::flush(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::mark_dirty() {
					GraphicsSurfaces::surfaces::mark_dirty(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::mark_dirty(error_code& ec) noexcept {
					GraphicsSurfaces::surfaces::mark_dirty(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents) {
					GraphicsSurfaces::surfaces::mark_dirty(_Data, extents);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents, error_code& ec) noexcept {
					GraphicsSurfaces::surfaces::mark_dirty(_Data, extents, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::paint(_Data, b, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void basic_image_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::stroke(_Data, b, basic_interpreted_path<GraphicsSurfaces>(pb), (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (sp == nullopt ? basic_stroke_props<GraphicsSurfaces>() : sp.value()), (d == nullopt ? basic_dashes<GraphicsSurfaces>() : d.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::stroke(_Data, b, ip, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (sp == nullopt ? basic_stroke_props<GraphicsSurfaces>() : sp.value()), (d == nullopt ? basic_dashes<GraphicsSurfaces>() : d.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void basic_image_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::fill(_Data, b, basic_interpreted_path<GraphicsSurfaces>(pb), (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::fill(_Data, b, ip, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_image_surface<GraphicsSurfaces>::mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_mask_props<GraphicsSurfaces>>& mp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::mask(_Data, b, mb, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (mp == nullopt ? basic_mask_props<GraphicsSurfaces>() : mp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}

				template<class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces> copy_surface(basic_image_surface<GraphicsSurfaces>& sfc) noexcept {
					return GraphicsSurfaces::surfaces::copy_surface(sfc);
				}

				template<class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces> copy_surface(basic_output_surface<GraphicsSurfaces>& sfc) noexcept {
					return GraphicsSurfaces::surfaces::copy_surface(sfc);
				}

				template<class GraphicsSurfaces>
				inline basic_image_surface<GraphicsSurfaces> copy_surface(basic_unmanaged_output_surface<GraphicsSurfaces>& sfc) noexcept {
					return GraphicsSurfaces::surfaces::copy_surface(sfc);
				}

				// output surface

				template <class GraphicsSurfaces>
				inline basic_output_surface<GraphicsSurfaces>::basic_output_surface(int preferredWidth,
					int preferredHeight, io2d::format preferredFormat, io2d::scaling scl,
					io2d::refresh_style rr, float fps)
					: _Data(move(GraphicsSurfaces::surfaces::create_output_surface(preferredWidth, preferredHeight, preferredFormat, scl, rr, fps))) {}
				template <class GraphicsSurfaces>
				inline basic_output_surface<GraphicsSurfaces>::basic_output_surface(int preferredWidth,
					int preferredHeight, io2d::format preferredFormat, error_code& ec, io2d::scaling scl,
					io2d::refresh_style rr, float fps) noexcept
					: _Data(move(GraphicsSurfaces::surfaces::create_output_surface(preferredWidth, preferredHeight, preferredFormat, ec, scl, rr, fps))) {}
				template <class GraphicsSurfaces>
				inline basic_output_surface<GraphicsSurfaces>::basic_output_surface(int preferredWidth,
					int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth,
					int preferredDisplayHeight, io2d::scaling scl, io2d::refresh_style rr, float fps)
					: _Data(move(GraphicsSurfaces::surfaces::create_output_surface(preferredWidth, preferredHeight, preferredFormat, preferredDisplayWidth, preferredDisplayHeight, scl, rr, fps))) {}
				template <class GraphicsSurfaces>
				inline basic_output_surface<GraphicsSurfaces>::basic_output_surface(int preferredWidth,
					int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth,
					int preferredDisplayHeight, error_code& ec, io2d::scaling scl, io2d::refresh_style rr,
					float fps) noexcept
					: _Data(move(GraphicsSurfaces::surfaces::create_output_surface(preferredWidth, preferredHeight, preferredFormat, preferredDisplayWidth, preferredDisplayHeight, ec, scl, rr, fps))) {}

				template <class GraphicsSurfaces>
				inline basic_output_surface<GraphicsSurfaces>::~basic_output_surface() noexcept {
					GraphicsSurfaces::surfaces::destroy(_Data);
				}

				template<class GraphicsSurfaces>
				inline basic_output_surface<GraphicsSurfaces>::basic_output_surface(basic_output_surface&& other) noexcept
					: _Data(move(GraphicsSurfaces::surfaces::move_output_surface(move(other._Data)))) {
				}

				template<class GraphicsSurfaces>
				inline basic_output_surface<GraphicsSurfaces>& basic_output_surface<GraphicsSurfaces>::operator=(basic_output_surface&& other) noexcept {
					if (this != &other) {
						_Data = move(GraphicsSurfaces::surfaces::move_output_surface(move(other._Data)));
					}
					return *this;
				}

				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::redraw_required() noexcept {
					GraphicsSurfaces::surfaces::redraw_required(_Data);
				}
				template <class GraphicsSurfaces>
				inline int basic_output_surface<GraphicsSurfaces>::begin_show() {
					return GraphicsSurfaces::surfaces::begin_show(_Data, this, *this);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::end_show() {
					GraphicsSurfaces::surfaces::end_show(_Data);
				}

				template <class GraphicsSurfaces>
				inline typename basic_output_surface<GraphicsSurfaces>::data_type& basic_output_surface<GraphicsSurfaces>::data() noexcept {
					return _Data;
				}

				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::clear() {
					GraphicsSurfaces::surfaces::clear(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::flush() {
					GraphicsSurfaces::surfaces::flush(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::flush(error_code& ec) noexcept {
					GraphicsSurfaces::surfaces::flush(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::mark_dirty() {
					GraphicsSurfaces::surfaces::mark_dirty(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::mark_dirty(error_code& ec) noexcept {
					GraphicsSurfaces::surfaces::mark_dirty(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents) {
					GraphicsSurfaces::surfaces::mark_dirty(_Data, extents);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents, error_code& ec) noexcept {
					GraphicsSurfaces::surfaces::mark_dirty(_Data, extents, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::paint(_Data, b, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void basic_output_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::stroke(_Data, b, basic_interpreted_path<GraphicsSurfaces>(pb), (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (sp == nullopt ? basic_stroke_props<GraphicsSurfaces>() : sp.value()), (d == nullopt ? basic_dashes<GraphicsSurfaces>() : d.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::stroke(_Data, b, ip, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (sp == nullopt ? basic_stroke_props<GraphicsSurfaces>() : sp.value()), (d == nullopt ? basic_dashes<GraphicsSurfaces>() : d.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void basic_output_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::fill(_Data, b, basic_interpreted_path<GraphicsSurfaces>(pb), (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::fill(_Data, b, ip, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_mask_props<GraphicsSurfaces>>& mp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::mask(_Data, b, mb, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (mp == nullopt ? basic_mask_props<GraphicsSurfaces>() : mp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}

				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::draw_callback(const function<void(basic_output_surface& sfc)>& fn) {
					GraphicsSurfaces::surfaces::draw_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::size_change_callback(const function<void(basic_output_surface& sfc)>& fn) {
					GraphicsSurfaces::surfaces::size_change_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::dimensions(basic_display_point<graphics_math_type> dp) {
					GraphicsSurfaces::surfaces::dimensions(_Data, dp);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::dimensions(basic_display_point<graphics_math_type> dp, error_code& ec) noexcept {
					GraphicsSurfaces::surfaces::dimensions(_Data, dp, ec);
				}
				template<class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::display_dimensions(basic_display_point<graphics_math_type> dp) {
					GraphicsSurfaces::surfaces::display_dimensions(_Data, dp);
				}
				template<class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::display_dimensions(basic_display_point<graphics_math_type> dp, error_code & ec) noexcept {
					GraphicsSurfaces::surfaces::display_dimensions(_Data, dp, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::scaling(experimental::io2d::scaling scl) noexcept {
					GraphicsSurfaces::surfaces::scaling(_Data, scl);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::user_scaling_callback(const function<basic_bounding_box<graphics_math_type>(const basic_output_surface&, bool&)>& fn) {
					GraphicsSurfaces::surfaces::user_scaling_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::letterbox_brush(const optional<basic_brush<GraphicsSurfaces>>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept {
					GraphicsSurfaces::surfaces::letterbox_brush(_Data, b, bp);
				}
				template<class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::letterbox_brush_props(const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept {
					GraphicsSurfaces::surfaces::letterbox_brush_props(_Data, bp);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::auto_clear(bool val) noexcept {
					GraphicsSurfaces::surfaces::auto_clear(_Data, val);
				}
				template <class GraphicsSurfaces>
				inline void basic_output_surface<GraphicsSurfaces>::redraw_required(bool val) noexcept {
					GraphicsSurfaces::surfaces::redraw_required(_Data, val);
				}
				template <class GraphicsSurfaces>
				inline io2d::format basic_output_surface<GraphicsSurfaces>::format() const noexcept {
					return GraphicsSurfaces::surfaces::format(_Data);
				}
				template <class GraphicsSurfaces>
				inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> basic_output_surface<GraphicsSurfaces>::dimensions() const noexcept {
					return GraphicsSurfaces::surfaces::dimensions(_Data);
				}
				template <class GraphicsSurfaces>
				inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> basic_output_surface<GraphicsSurfaces>::max_dimensions() const noexcept {
					return GraphicsSurfaces::surfaces::max_dimensions();
				}
				template<class GraphicsSurfaces>
				inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> basic_output_surface<GraphicsSurfaces>::display_dimensions() const noexcept {
					return GraphicsSurfaces::surfaces::display_dimensions(_Data);
				}
				template<class GraphicsSurfaces>
				inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> basic_output_surface<GraphicsSurfaces>::max_display_dimensions() const noexcept {
					return GraphicsSurfaces::surfaces::max_display_dimensions();
				}
				template <class GraphicsSurfaces>
				inline io2d::scaling basic_output_surface<GraphicsSurfaces>::scaling() const noexcept {
					return GraphicsSurfaces::surfaces::scaling(_Data);
				}
				template <class GraphicsSurfaces>
				inline optional<basic_brush<GraphicsSurfaces>> basic_output_surface<GraphicsSurfaces>::letterbox_brush() const noexcept {
					return GraphicsSurfaces::surfaces::letterbox_brush(_Data);
				}
				template <class GraphicsSurfaces>
				inline optional<basic_brush_props<GraphicsSurfaces>> basic_output_surface<GraphicsSurfaces>::letterbox_brush_props() const noexcept {
					return GraphicsSurfaces::surfaces::letterbox_brush_props(_Data);
				}
				template <class GraphicsSurfaces>
				inline bool basic_output_surface<GraphicsSurfaces>::auto_clear() const noexcept {
					return GraphicsSurfaces::surfaces::auto_clear(_Data);
				}


				// unmanaged output surface

				template <class GraphicsSurfaces>
				inline basic_unmanaged_output_surface<GraphicsSurfaces>::basic_unmanaged_output_surface(data_type&& data) noexcept
					: _Data(move(data)) {
				}

				template <class GraphicsSurfaces>
				inline basic_unmanaged_output_surface<GraphicsSurfaces>::basic_unmanaged_output_surface(basic_unmanaged_output_surface&& val) noexcept {
					_Data = move(GraphicsSurfaces::surfaces::move_unmanaged_output_surface(move(val._Data)));
				}
				template <class GraphicsSurfaces>
				inline basic_unmanaged_output_surface<GraphicsSurfaces>& basic_unmanaged_output_surface<GraphicsSurfaces>::operator=(basic_unmanaged_output_surface&& val) noexcept {
					if (this != &val) {
						_Data = move(GraphicsSurfaces::surfaces::move_unmanaged_output_surface(move(val._Data)));
					}
					return *this;
				}
				template <class GraphicsSurfaces>
				inline basic_unmanaged_output_surface<GraphicsSurfaces>::~basic_unmanaged_output_surface() noexcept {
					GraphicsSurfaces::surfaces::destroy(_Data);
				}

				template<class GraphicsSurfaces>
				inline bool basic_unmanaged_output_surface<GraphicsSurfaces>::has_draw_callback() const noexcept {
					return GraphicsSurfaces::surfaces::has_draw_callback(_Data);
				}

				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::invoke_draw_callback() {
					GraphicsSurfaces::surfaces::invoke_draw_callback(_Data, *this);
				}
				template<class GraphicsSurfaces>
				inline bool basic_unmanaged_output_surface<GraphicsSurfaces>::has_size_change_callback() const noexcept {
					return GraphicsSurfaces::surfaces::has_size_change_callback(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::invoke_size_change_callback() {
					GraphicsSurfaces::surfaces::invoke_size_change_callback(_Data, *this);
				}
				template<class GraphicsSurfaces>
				inline bool basic_unmanaged_output_surface<GraphicsSurfaces>::has_user_scaling_callback() const noexcept {
					return GraphicsSurfaces::surfaces::has_user_scaling_callback(_Data);
				}
				template <class GraphicsSurfaces>
				inline basic_bounding_box<typename GraphicsSurfaces::graphics_math_type> basic_unmanaged_output_surface<GraphicsSurfaces>::invoke_user_scaling_callback(bool& useLetterboxBrush) {
					GraphicsSurfaces::surfaces::invoke_user_scaling_callback(_Data, *this, useLetterboxBrush);
				}

				template<class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::draw_to_output() {
					GraphicsSurfaces::surfaces::draw_to_output(_Data, *this);
				}

				template <class GraphicsSurfaces>
				inline typename basic_unmanaged_output_surface<GraphicsSurfaces>::data_type& basic_unmanaged_output_surface<GraphicsSurfaces>::data() noexcept {
					return _Data;
				}

				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::clear() {
					GraphicsSurfaces::surfaces::clear(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::flush() {
					GraphicsSurfaces::surfaces::flush(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::flush(error_code& ec) noexcept {
					GraphicsSurfaces::surfaces::flush(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::mark_dirty() {
					GraphicsSurfaces::surfaces::mark_dirty(_Data);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::mark_dirty(error_code& ec) noexcept {
					GraphicsSurfaces::surfaces::mark_dirty(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents) {
					GraphicsSurfaces::surfaces::mark_dirty(_Data, extents);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents, error_code& ec) noexcept {
					GraphicsSurfaces::surfaces::mark_dirty(_Data, extents, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::paint(_Data, b, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::stroke(_Data, b, basic_interpreted_path<GraphicsSurfaces>(pb), (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (sp == nullopt ? basic_stroke_props<GraphicsSurfaces>() : sp.value()), (d == nullopt ? basic_dashes<GraphicsSurfaces>() : d.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::stroke(_Data, b, ip, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (sp == nullopt ? basic_stroke_props<GraphicsSurfaces>() : sp.value()), (d == nullopt ? basic_dashes<GraphicsSurfaces>() : d.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::fill(_Data, b, basic_interpreted_path<GraphicsSurfaces>(pb), (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::fill(_Data, b, ip, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_mask_props<GraphicsSurfaces>>& mp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurfaces::surfaces::mask(_Data, b, mb, (bp == nullopt ? basic_brush_props<GraphicsSurfaces>() : bp.value()), (mp == nullopt ? basic_mask_props<GraphicsSurfaces>() : mp.value()), (rp == nullopt ? basic_render_props<GraphicsSurfaces>() : rp.value()), (cl == nullopt ? basic_clip_props<GraphicsSurfaces>() : cl.value()));
				}

				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::draw_callback(const function<void(basic_unmanaged_output_surface& sfc)>& fn) {
					GraphicsSurfaces::surfaces::draw_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::size_change_callback(const function<void(basic_unmanaged_output_surface& sfc)>& fn) {
					GraphicsSurfaces::surfaces::size_change_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::dimensions(basic_display_point<graphics_math_type> dp) {
					GraphicsSurfaces::surfaces::dimensions(_Data, dp);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::dimensions(basic_display_point<graphics_math_type> dp, error_code& ec) noexcept {
					GraphicsSurfaces::surfaces::dimensions(_Data, dp, ec);
				}
				template<class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::display_dimensions(basic_display_point<graphics_math_type> dp) {
					GraphicsSurfaces::surfaces::display_dimensions(_Data, dp);
				}
				template<class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::display_dimensions(basic_display_point<graphics_math_type> dp, error_code & ec) noexcept {
					GraphicsSurfaces::surfaces::display_dimensions(_Data, dp, ec);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::scaling(experimental::io2d::scaling scl) noexcept {
					GraphicsSurfaces::surfaces::scaling(_Data, scl);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::user_scaling_callback(const function<basic_bounding_box<graphics_math_type>(const basic_unmanaged_output_surface&, bool&)>& fn) {
					GraphicsSurfaces::surfaces::user_scaling_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::letterbox_brush(const optional<basic_brush<GraphicsSurfaces>>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept {
					GraphicsSurfaces::surfaces::letterbox_brush(_Data, b, bp);
				}
				template<class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::letterbox_brush_props(const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept {
					GraphicsSurfaces::surfaces::letterbox_brush_props(_Data, bp);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::auto_clear(bool val) noexcept {
					GraphicsSurfaces::surfaces::auto_clear(_Data, val);
				}
				template <class GraphicsSurfaces>
				inline void basic_unmanaged_output_surface<GraphicsSurfaces>::redraw_required(bool val) noexcept {
					GraphicsSurfaces::surfaces::redraw_required(_Data, val);
				}
				template <class GraphicsSurfaces>
				inline io2d::format basic_unmanaged_output_surface<GraphicsSurfaces>::format() const noexcept {
					return GraphicsSurfaces::surfaces::format(_Data);
				}
				template <class GraphicsSurfaces>
				inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> basic_unmanaged_output_surface<GraphicsSurfaces>::dimensions() const noexcept {
					return GraphicsSurfaces::surfaces::dimensions(_Data);
				}
				template <class GraphicsSurfaces>
				inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> basic_unmanaged_output_surface<GraphicsSurfaces>::max_dimensions() const noexcept {
					return GraphicsSurfaces::surfaces::max_dimensions();
				}
				template<class GraphicsSurfaces>
				inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> basic_unmanaged_output_surface<GraphicsSurfaces>::display_dimensions() const noexcept {
					return GraphicsSurfaces::surfaces::display_dimensions(_Data);
				}
				template<class GraphicsSurfaces>
				inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> basic_unmanaged_output_surface<GraphicsSurfaces>::max_display_dimensions() const noexcept {
					return GraphicsSurfaces::surfaces::max_display_dimensions();
				}
				template <class GraphicsSurfaces>
				inline io2d::scaling basic_unmanaged_output_surface<GraphicsSurfaces>::scaling() const noexcept {
					return GraphicsSurfaces::surfaces::scaling(_Data);
				}
				template <class GraphicsSurfaces>
				inline optional<basic_brush<GraphicsSurfaces>> basic_unmanaged_output_surface<GraphicsSurfaces>::letterbox_brush() const noexcept {
					return GraphicsSurfaces::surfaces::letterbox_brush(_Data);
				}
				template <class GraphicsSurfaces>
				inline optional<basic_brush_props<GraphicsSurfaces>> basic_unmanaged_output_surface<GraphicsSurfaces>::letterbox_brush_props() const noexcept {
					return GraphicsSurfaces::surfaces::letterbox_brush_props(_Data);
				}
				template <class GraphicsSurfaces>
				inline bool basic_unmanaged_output_surface<GraphicsSurfaces>::auto_clear() const noexcept {
					return GraphicsSurfaces::surfaces::auto_clear(_Data);
				}
			}
		}
	}
}
