#pragma once

#include "xsurfaces.h"

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				// dashes
				template <class GraphicsSurfaces>
				inline base_dashes<GraphicsSurfaces>::base_dashes() noexcept
					: _Data(GraphicsSurfaces::create_dashes()) {}
				template <class GraphicsSurfaces>
				template <class ForwardIterator>
				inline base_dashes<GraphicsSurfaces>::base_dashes(float offset, ForwardIterator first, ForwardIterator last)
					: _Data(GraphicsSurfaces::create_dashes<ForwardIterator>(offset, first, last)) {}
				template <class GraphicsSurfaces>
				inline base_dashes<GraphicsSurfaces>::base_dashes(float offset, ::std::initializer_list<float> il)
					: _Data(GraphicsSurfaces::create_dashes(offset, il)) {}

				// image_surface

				template <class GraphicsSurfaces>
				inline const typename base_image_surface<GraphicsSurfaces>::_Data_type base_image_surface<GraphicsSurfaces>::_Get_data() const noexcept {
					return _Data;
				}
				template <class GraphicsSurfaces>
				inline base_image_surface<GraphicsSurfaces>::base_image_surface(io2d::format fmt, int width, int height)
					: _Data(GraphicsSurfaces::create_image_surface(fmt, width, height)) {
				}

#ifdef _Filesystem_support_test
				template <class GraphicsSurfaces>
				inline base_image_surface<GraphicsSurfaces>::base_image_surface(filesystem::path f, image_file_format iff, io2d::format fmt)
					: _Data(GraphicsSurfaces::create_image_surface(f, iff, fmt)) {
				}
				template <class GraphicsSurfaces>
				inline base_image_surface<GraphicsSurfaces>::base_image_surface(filesystem::path f, image_file_format iff, io2d::format fmt, error_code& ec) noexcept
					: _Data(GraphicsSurfaces::create_image_surface(f, iff, fmt, ec)) {
				}
#else
				template <class GraphicsSurfaces>
				inline base_image_surface<GraphicsSurfaces>::base_image_surface(::std::string f, image_file_format iff, io2d::format fmt)
					: _Data(GraphicsSurfaces::create_image_surface(f, iff, fmt)) {
				}
				template <class GraphicsSurfaces>
				inline base_image_surface<GraphicsSurfaces>::base_image_surface(::std::string f, image_file_format iff, io2d::format fmt, error_code& ec) noexcept
					: _Data(GraphicsSurfaces::create_image_surface(f, iff, fmt, ec)) {
				}
#endif

#ifdef _Filesystem_support_test
				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::save(filesystem::path p, image_file_format iff) {
					GraphicsSurfaces::save(_Data, p, iff);
				}
				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::save(filesystem::path p, image_file_format iff, error_code& ec) noexcept {
					GraphicsSurfaces::save(_Data, p, iff, ec);
				}
#else
				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::save(::std::string p, image_file_format iff) {
					GraphicsSurfaces::save(_Data, p, iff);
				}
				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::save(::std::string p, image_file_format iff, error_code& ec) noexcept {
					GraphicsSurfaces::save(_Data, p, iff, ec);
				}
#endif

				template <class GraphicsSurfaces>
				inline static int base_image_surface<GraphicsSurfaces>::max_width() noexcept {
					return GraphicsSurfaces::max_width(_Data);
				}
				template <class GraphicsSurfaces>
				inline static int base_image_surface<GraphicsSurfaces>::max_height() noexcept {
					return GraphicsSurfaces::max_height(_Data);
				}
				template <class GraphicsSurfaces>
				inline io2d::format base_image_surface<GraphicsSurfaces>::format() const noexcept {
					return GraphicsSurfaces::format(_Data);
				}
				template <class GraphicsSurfaces>
				inline int base_image_surface<GraphicsSurfaces>::width() const noexcept {
					return GraphicsSurface::width(_Data);
				}
				template <class GraphicsSurfaces>
				inline int base_image_surface<GraphicsSurfaces>::height() const noexcept {
					return GraphicsSurface::height(_Data);
				}

				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::clear() {
					GraphicsSurface::clear(_Data);
				}
				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::flush() {
					GraphicsSurface::flush(_Data)
				}
				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::flush(error_code& ec) noexcept {
					GraphicsSurface::flush(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::mark_dirty() {
					GraphicsSurface::mark_dirty(_Data);
				}
				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::mark_dirty(error_code& ec) noexcept {
					GraphicsSurface::mark_dirty(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents) {
					GraphicsSurface::mark_dirty(_Data, extents);
				}
				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents, error_code& ec) noexcept {
					GraphicsSurface::mark_dirty(_Data, extents, ec);
				}
				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurface::paint(_Data, b, bp, rp, cl);
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void base_image_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<dashes>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurface::stroke(_Data, b, pb, bp, sp, d, rp, cl);
				}
				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<dashes>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurface::stroke(_Data, b, ip, bp, sp, d, rp, cl);
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void base_image_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurface::fill(_Data, b, pb, bp, rp, cl);
				}
				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurface::fill(_Data, b, ip, bp, rp, cl);
				}
				template <class GraphicsSurfaces>
				inline void base_image_surface<GraphicsSurfaces>::mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_mask_props<GraphicsSurfaces>>& mp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurface::mask(_Data, b, mb, bp, mp, rp, cl);
				}

				// display_surface
				template <class GraphicsSurfaces>
				inline base_display_surface<GraphicsSurfaces>::base_display_surface(_Data_type&& data)
					: _Data(data) {
				}
				template <class GraphicsSurfaces>
				inline base_display_surface<GraphicsSurfaces>::~base_display_surface() noexcept {
					GraphicsSurfaces::destroy(_Data);
				}

				template <class GraphicsSurfaces>
				inline const typename base_display_surface<GraphicsSurfaces>::_Data_type& base_display_surface<GraphicsSurfaces>::_Get_data() const noexcept {
					return _Data;
				}
				template <class GraphicsSurfaces>
				inline static int base_display_surface<GraphicsSurfaces>::max_width() noexcept {
					return GraphicsSurfaces::max_width(_Data);
				}
				template <class GraphicsSurfaces>
				inline static int base_display_surface<GraphicsSurfaces>::max_height() noexcept {
					return GraphicsSurfaces::max_height(_Data);
				}
				template <class GraphicsSurfaces>
				inline io2d::format base_display_surface<GraphicsSurfaces>::format() const noexcept {
					return GraphicsSurfaces::format(_Data);
				}
				template <class GraphicsSurfaces>
				inline int base_display_surface<GraphicsSurfaces>::width() const noexcept {
					return GraphicsSurface::width(_Data);
				}
				template <class GraphicsSurfaces>
				inline int base_display_surface<GraphicsSurfaces>::height() const noexcept {
					return GraphicsSurface::height(_Data);
				}

				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::clear() {
					GraphicsSurface::clear(_Data);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::flush() {
					GraphicsSurface::flush(_Data)
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::flush(error_code& ec) noexcept {
					GraphicsSurface::flush(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::mark_dirty() {
					GraphicsSurface::mark_dirty(_Data);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::mark_dirty(error_code& ec) noexcept {
					GraphicsSurface::mark_dirty(_Data, ec);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents) {
					GraphicsSurface::mark_dirty(_Data, extents);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::mark_dirty(const basic_bounding_box<graphics_math_type>& extents, error_code& ec) noexcept {
					GraphicsSurface::mark_dirty(_Data, extents, ec);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurface::paint(_Data, b, bp, rp, cl);
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void base_display_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<dashes>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurface::stroke(_Data, b, pb, bp, sp, d, rp, cl);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<dashes>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurface::stroke(_Data, b, ip, bp, sp, d, rp, cl);
				}
				template <class GraphicsSurfaces>
				template <class Allocator>
				inline void base_display_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces, Allocator>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurface::fill(_Data, b, pb, bp, rp, cl);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurface::fill(_Data, b, ip, bp, rp, cl);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_mask_props<GraphicsSurfaces>>& mp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) {
					GraphicsSurface::mask(_Data, b, mb, bp, mp, rp, cl);
				}

				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::draw_callback(const function<void(display_surface& sfc)>& fn) {
					GraphicsSurfaces::draw_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::size_change_callback(const function<void(display_surface& sfc)>& fn) {
					GraphicsSurfaces::size_change_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::dimensions(basic_display_point<graphics_math_type> dp) {
					GraphicsSurfaces::dimensions(_Data, dp);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::dimensions(basic_display_point<graphics_math_type> dp, error_code& ec) noexcept {
					GraphicsSurfaces::dimensions(_Data, dp, ec);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::scaling(experimental::io2d::scaling scl) noexcept {
					GraphicsSurfaces::scaling(_Data, scl);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::user_scaling_callback(const function<basic_bounding_box<graphics_math_type>(const display_surface&, bool&)>& fn) {
					GraphicsSurfaces::user_scaling_callback(_Data, fn);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::letterbox_brush(const optional<basic_brush<GraphicsSurfaces>>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept {
					GraphicsSurfaces::letterbox_brush(_Data, b, bp);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::letterbox_brush_props(const optional < basic_brush_props<GraphicsSurfaces>& bp) noexcept {
					GraphicsSurfaces::letterbox_brush_props(_Data, bp);
				}
				template <class GraphicsSurfaces>
				inline void base_display_surface<GraphicsSurfaces>::auto_clear(bool val) noexcept {
					GraphicsSurfaces::auto_clear(_Data, val);
				}
				template <class GraphicsSurfaces>
				inline io2d::format base_display_surface<GraphicsSurfaces>::format() const noexcept {
					return GraphicsSurfaces::format(_Data);
				}
				template <class GraphicsSurfaces>
				inline basic_display_point<graphics_math_type> base_display_surface<GraphicsSurfaces>::dimensions() const noexcept {
					return GraphicsSurfaces::dimensions(_Data);
				}
				template <class GraphicsSurfaces>
				inline io2d::scaling base_display_surface<GraphicsSurfaces>::scaling() const noexcept {
					return GraphicsSurfaces::scaling(_Data);
				}
				template <class GraphicsSurfaces>
				inline optional<basic_brush<GraphicsSurfaces>> base_display_surface<GraphicsSurfaces>::letterbox_brush() const noexcept {
					return GraphicsSurfaces::letterbox_brush(_Data);
				}
				template <class GraphicsSurfaces>
				inline optional<basic_brush_props<GraphicsSurfaces>> base_display_surface<GraphicsSurfaces>::letterbox_brush_props() const noexcept {
					return return GraphicsSurfaces::letterbox_brush_props(_Data);
				}
				template <class GraphicsSurfaces>
				inline bool base_display_surface<GraphicsSurfaces>::auto_clear() const noexcept {
					return GraphicsSurfaces::auto_clear(_Data);
				}

				// output surface

				template <class GraphicsSurfaces>
				inline base_output_surface<GraphicsSurfaces>::base_output_surface(int preferredWidth,
					int preferredHeight, io2d::format preferredFormat, io2d::scaling scl,
					io2d::refresh_rate rr, float fps)
					: base_display_surface<GraphicsSurfaces>(move(create_display_surface(preferredWidth, preferredHeight, preferredFormat, scl, rr, fps))) {}
				template <class GraphicsSurfaces>
				inline base_output_surface<GraphicsSurfaces>::base_output_surface(int preferredWidth,
					int preferredHeight, io2d::format preferredFormat, error_code& ec, io2d::scaling scl,
					io2d::refresh_rate rr, float fps) noexcept
					: base_display_surface<GraphicsSurfaces>(move(create_display_surface(preferredWidth, preferredHeight, preferredFormat, ec, scl, rr, fps))) {}
				template <class GraphicsSurfaces>
				inline base_output_surface<GraphicsSurfaces>::base_output_surface(int preferredWidth,
					int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth,
					int preferredDisplayHeight, io2d::scaling scl, io2d::refresh_rate rr, float fps)
					: base_display_surface<GraphicsSurfaces>(move(create_display_surface(preferredWidth, preferredHeight, preferredFormat, preferredDisplayWidth, preferredDisplayHeight, scl, rr, fps))) {}
				template <class GraphicsSurfaces>
				inline base_output_surface<GraphicsSurfaces>::base_output_surface(int preferredWidth,
					int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth,
					int preferredDisplayHeight, error_code& ec, io2d::scaling scl, io2d::refresh_rate rr,
					float fps) noexcept
					: base_display_surface<GraphicsSurfaces>(move(create_display_surface(preferredWidth, preferredHeight, preferredFormat, preferredDisplayWidth, preferredDisplayHeight, ec, scl, rr, fps))) {}

				template <class GraphicsSurfaces>
				inline base_output_surface<GraphicsSurfaces>::~base_output_surface() noexcept {
				}

				template <class GraphicsSurfaces>
				inline void base_output_surface<GraphicsSurfaces>::redraw_required() noexcept {
					GraphicsSurfaces::redraw_required(_Data);
				}
				template <class GraphicsSurfaces>
				inline typename GraphicsSurfaces::show_return_data_type base_output_surface<GraphicsSurfaces>::begin_show() {
					return GraphicsSurfaces::begin_show(_Data);
				}
				template <class GraphicsSurfaces>
				inline void base_output_surface<GraphicsSurfaces>::end_show() {
					GraphicsSurfaces::end_show(_Data);
				}


				// unmanaged output surface
				template <class GraphicsSurfaces>
				inline base_unmanaged_output_surface<GraphicsSurfaces>::base_unmanaged_output_surface(HWND hwnd, HDC hdc, int preferredWidth, int preferredHeight, format preferredFormat)
					: _Data(move(GraphicsSurfaces::create_display_surface(hwnd, hdc, preferredWidth, preferredHeight, preferredFormat))) {
				}
				template <class GraphicsSurfaces>
				inline base_unmanaged_output_surface<GraphicsSurfaces>::~base_unmanaged_output_surface() noexcept { }

				template <class GraphicsSurfaces>
				inline void base_unmanaged_output_surface<GraphicsSurfaces>::invoke_draw_callback(const optional<basic_clip_props<GraphicsSurfaces>>& clip) {
					GraphicsSurfaces::invoke_draw_callback(_Data, clip);
				}
				template <class GraphicsSurfaces>
				inline void base_unmanaged_output_surface<GraphicsSurfaces>::invoke_size_change_callback() {
					GraphicsSurfaces::invoke_size_change_callback(_Data);
				}
				template <class GraphicsSurfaces>
				inline bool base_unmanaged_output_surface<GraphicsSurfaces>::reset_redraw_request() noexcept {
					GraphicsSurfaces::reset_redraw_request(_Data);
				}
			}
		}
	}
}
