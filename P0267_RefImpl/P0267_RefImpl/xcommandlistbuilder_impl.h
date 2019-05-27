#pragma once

#include "xsurfaces.h"
#include <vector>
#include <utility>

namespace std::experimental::io2d {
	inline namespace v1 {
		template<class GraphicsSurfaces, class Allocator>
		inline const typename basic_command_list_builder<GraphicsSurfaces, Allocator>::data_type& basic_command_list_builder<GraphicsSurfaces, Allocator>::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::data_type& basic_command_list_builder<GraphicsSurfaces, Allocator>::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void io2d::v1::basic_command_list_builder<GraphicsSurfaces, Allocator>::clear_cmd(const typename basic_commands<GraphicsSurfaces>::clear& c) {
			_Data.emplace_back(c);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::flush(const typename basic_commands<GraphicsSurfaces>::flush& f) {
			_Data.emplace_back(f);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::mark_dirty(const typename basic_commands<GraphicsSurfaces>::mark_dirty& md) {
			_Data.emplace_back(md);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::paint(const typename basic_commands<GraphicsSurfaces>::paint& p) {
			_Data.emplace_back(p);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::stroke(const typename basic_commands<GraphicsSurfaces>::stroke& s) {
			_Data.emplace_back(s);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::fill(const typename basic_commands<GraphicsSurfaces>::fill& f) {
			_Data.emplace_back(f);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::mask(const typename basic_commands<GraphicsSurfaces>::mask& m) {
			_Data.emplace_back(m);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::draw_text(const typename basic_commands<GraphicsSurfaces>::draw_text& dt) {
			_Data.emplace_back(dt);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::clear_cmd() noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::clear>);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::clear_cmd(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::clear>, sfc);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::flush() noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::flush>);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::flush(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::flush>, sfc);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::mark_dirty() noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::mark_dirty>);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::mark_dirty(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::mark_dirty>, sfc);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::mark_dirty(const basic_bounding_box<graphics_math_type>& ext) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::mark_dirty>, ext);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::mark_dirty(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_bounding_box<graphics_math_type>& ext) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::mark_dirty>, sfc, ext);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::paint>, b, bp, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::paint(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::paint>, sfc, b, bp, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::stroke>, b, ip, bp, sp, d, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::stroke(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::stroke>, sfc, b, ip, bp, sp, d, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		template<class InputIterator>
		inline void io2d::v1::basic_command_list_builder<GraphicsSurfaces, Allocator>::stroke(const basic_brush<GraphicsSurfaces>& b, InputIterator first, InputIterator last, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::stroke>, b, first, last, bp, sp, d, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		template<class InputIterator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::stroke(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, InputIterator first, InputIterator last, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::stroke>, sfc, b, first, last, bp, sp, d, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::fill>, b, ip, bp, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::fill(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::fill>, sfc, b, ip, bp, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		template<class InputIterator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::fill(const basic_brush<GraphicsSurfaces>& b, InputIterator first, InputIterator last, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::fill>, b, first, last, bp, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		template<class InputIterator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::fill(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, InputIterator first, InputIterator last, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::fill>, sfc, b, first, last, bp, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_mask_props<GraphicsSurfaces>>& mp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::mask>, b, mb, bp, mp, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::mask(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_mask_props<GraphicsSurfaces>>& mp, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::mask>, sfc, b, mb, bp, mp, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::draw_text(const basic_point_2d<graphics_math_type>& pt, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const optional<basic_text_props<GraphicsSurfaces>>& tp, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::draw_text>, pt, b, font, text, tp, bp, sp, d, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::draw_text(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_point_2d<graphics_math_type>& pt, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const optional<basic_text_props<GraphicsSurfaces>>& tp, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::draw_text>, sfc, pt, b, font, text, tp, bp, sp, d, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::draw_text(const basic_bounding_box<graphics_math_type>& bb, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const optional<basic_text_props<GraphicsSurfaces>>& tp, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::draw_text>, bb, b, font, text, tp, bp, sp, d, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::draw_text(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_bounding_box<graphics_math_type>& bb, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const optional<basic_text_props<GraphicsSurfaces>>& tp, const optional<basic_brush_props<GraphicsSurfaces>>& bp, const optional<basic_stroke_props<GraphicsSurfaces>>& sp, const optional<basic_dashes<GraphicsSurfaces>>& d, const optional<basic_render_props<GraphicsSurfaces>>& rp, const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept {
			_Data.emplace_back(in_place_type<typename basic_commands<GraphicsSurfaces>::draw_text>, sfc, bb, b, font, text, tp, bp, sp, d, rp, cl);
		}
		template<class GraphicsSurfaces, class Allocator>
		inline basic_command_list_builder<GraphicsSurfaces, Allocator>::basic_command_list_builder() noexcept(noexcept(Allocator()))
			: basic_command_list_builder(Allocator) { }
		template<class GraphicsSurfaces, class Allocator>
		inline basic_command_list_builder<GraphicsSurfaces, Allocator>::basic_command_list_builder(const Allocator& a) noexcept
			: _Data(a) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_command_list_builder<GraphicsSurfaces, Allocator>::basic_command_list_builder(size_type n, const Allocator& a)
			: _Data(n, a) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_command_list_builder<GraphicsSurfaces, Allocator>::basic_command_list_builder(size_type n, const value_type& value, const Allocator& a)
			: _Data(n, value, a) {
		}

		template <class GraphicsSurfaces, class Allocator>
		template<class InputIterator>
		inline basic_command_list_builder<GraphicsSurfaces, Allocator>::basic_command_list_builder(InputIterator first, InputIterator last, const Allocator& a)
			: _Data(first, last, a) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_command_list_builder<GraphicsSurfaces, Allocator>::~basic_command_list_builder() { }

		template <class GraphicsSurfaces, class Allocator>
		template<class InputIterator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::assign(InputIterator first, InputIterator last) {
			_Data.assign(first, last);
		}

		template <class GraphicsSurfaces, class Allocator>
		template<class ...Args>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::reference basic_command_list_builder<GraphicsSurfaces, Allocator>::emplace_back(Args&& ...args) {
			return _Data.emplace_back(forward<Args>(args)...);
		}

		template <class GraphicsSurfaces, class Allocator>
		template<class ...Args>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::emplace(const_iterator position, Args&& ...args) {
			return _Data.emplace(position, forward<Args>(args)...);
		}

		template <class GraphicsSurfaces, class Allocator>
		template<class InputIterator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::insert(const_iterator position, InputIterator first, InputIterator last) {
			return _Data.template insert<InputIterator>(position, first, last);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_command_list_builder<GraphicsSurfaces, Allocator>::basic_command_list_builder(const basic_command_list_builder& pf)
			: _Data(pf._Data) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_command_list_builder<GraphicsSurfaces, Allocator>::basic_command_list_builder(basic_command_list_builder&& pf) noexcept
			: _Data(move(pf._Data)) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_command_list_builder<GraphicsSurfaces, Allocator>::basic_command_list_builder(const basic_command_list_builder& pf, const Allocator& a)
			: _Data(pf._Data, a) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_command_list_builder<GraphicsSurfaces, Allocator>::basic_command_list_builder(basic_command_list_builder&& pf, const Allocator& a)
			: _Data(move(pf._Data), a) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_command_list_builder<GraphicsSurfaces, Allocator>::basic_command_list_builder(initializer_list<value_type> il, const Allocator& a)
			: _Data(il, a) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_command_list_builder<GraphicsSurfaces, Allocator>& basic_command_list_builder<GraphicsSurfaces, Allocator>::operator=(const basic_command_list_builder& x) {
			_Data = x._Data;
			return *this;
		}
		template <class GraphicsSurfaces, class Allocator>
		inline basic_command_list_builder<GraphicsSurfaces, Allocator>& basic_command_list_builder<GraphicsSurfaces, Allocator>::operator=(basic_command_list_builder&& x) noexcept(allocator_traits<Allocator>::propagate_on_container_move_assignment::value || allocator_traits<Allocator>::is_always_equal::value) {
			::std::swap(_Data, x._Data);
			return *this;
		}
		template <class GraphicsSurfaces, class Allocator>
		inline basic_command_list_builder<GraphicsSurfaces, Allocator>& basic_command_list_builder<GraphicsSurfaces, Allocator>::operator=(initializer_list<value_type> il) {
			_Data.clear();
			for (const auto& item : il) {
				_Data.push_back(item);
			}
			return *this;
		}
		template <class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::assign(size_type n, const value_type& u) {
			_Data.assign(n, u);
		}
		template <class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::assign(initializer_list<value_type> il) {
			_Data.assign(il);
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::allocator_type basic_command_list_builder<GraphicsSurfaces, Allocator>::get_allocator() const noexcept {
			return _Data.allocator_type();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::begin() noexcept {
			return _Data.begin();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::const_iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::begin() const noexcept {
			return _Data.begin();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::const_iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::cbegin() const noexcept {
			return _Data.cbegin();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::end() noexcept {
			return _Data.end();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::const_iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::end() const noexcept {
			return _Data.end();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::const_iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::cend() const noexcept {
			return _Data.cend();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::reverse_iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::rbegin() noexcept {
			return _Data.rbegin();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::const_reverse_iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::rbegin() const noexcept {
			return _Data.rbegin();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::const_reverse_iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::crbegin() const noexcept {
			return _Data.crbegin();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::reverse_iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::rend() noexcept {
			return _Data.rend();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::const_reverse_iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::rend() const noexcept {
			return _Data.rend();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::const_reverse_iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::crend() const noexcept {
			return _Data.crend();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline bool basic_command_list_builder<GraphicsSurfaces, Allocator>::empty() const noexcept {
			return _Data.empty();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::size_type basic_command_list_builder<GraphicsSurfaces, Allocator>::size() const noexcept {
			return _Data.size();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::size_type basic_command_list_builder<GraphicsSurfaces, Allocator>::max_size() const noexcept {
			return _Data.max_size();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::size_type basic_command_list_builder<GraphicsSurfaces, Allocator>::capacity() const noexcept {
			return _Data.capacity();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::resize(size_type sz) {
			_Data.resize(sz);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::resize(size_type sz, const value_type& c) {
			_Data.resize(sz, c);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::reserve(size_type n) {
			_Data.reserve(n);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::shrink_to_fit() {
			_Data.shrink_to_fit();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::reference basic_command_list_builder<GraphicsSurfaces, Allocator>::operator[](size_type n) {
			return _Data[n];
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::const_reference basic_command_list_builder<GraphicsSurfaces, Allocator>::operator[](size_type n) const {
			return _Data[n];
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::const_reference basic_command_list_builder<GraphicsSurfaces, Allocator>::at(size_type n) const {
			return _Data.at(n);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::reference basic_command_list_builder<GraphicsSurfaces, Allocator>::at(size_type n) {
			return _Data.at(n);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::reference basic_command_list_builder<GraphicsSurfaces, Allocator>::front() {
			return _Data.front();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::const_reference basic_command_list_builder<GraphicsSurfaces, Allocator>::front() const {
			return _Data.front();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::reference basic_command_list_builder<GraphicsSurfaces, Allocator>::back() {
			return _Data.back();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::const_reference basic_command_list_builder<GraphicsSurfaces, Allocator>::back() const {
			return _Data.back();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::push_back(const value_type& x) {
			_Data.push_back(x);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::push_back(value_type&& x) {
			_Data.push_back(move(x));
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::pop_back() {
			_Data.pop_back();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::insert(const_iterator position, const value_type& x) {
			return _Data.insert(position, x);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::insert(const_iterator position, value_type&& x) {
			return _Data.insert(position, x);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::insert(const_iterator position, size_type n, const value_type& x) {
			return _Data.insert(position, n, x);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::insert(const_iterator position, initializer_list<value_type> il) {
			return _Data.insert(position, il);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::erase(const_iterator position) {
			return _Data.erase(position);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_command_list_builder<GraphicsSurfaces, Allocator>::iterator basic_command_list_builder<GraphicsSurfaces, Allocator>::erase(const_iterator first, const_iterator last) {
			return _Data.erase(first, last);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::swap(basic_command_list_builder& pf) noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value || allocator_traits<Allocator>::is_always_equal::value) {
			::std::swap(_Data, pf._Data);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_command_list_builder<GraphicsSurfaces, Allocator>::clear() noexcept {
			_Data.clear();
		}


		template <class GraphicsSurfaces, class Allocator>
		inline bool operator==(const basic_command_list_builder<GraphicsSurfaces, Allocator>& lhs, const basic_command_list_builder<GraphicsSurfaces, Allocator>& rhs) noexcept {
			if (lhs.size() != rhs.size()) {
				return false;
			}
			//return equal(_Data.cbegin(), _Data.cend(), rhs._Data.cbegin(), rhs._Data.cend());
			const auto& lhsData = lhs.data();
			const auto& rhsData = rhs.data();
			auto lhsEnd = lhsData.end();
			auto rhsEnd = rhsData.end();
			auto lhsIter = lhsData.begin();
			auto rhsIter = rhsData.begin();
			for (; lhsIter != lhsEnd &&
				rhsIter != rhsEnd; ++lhsIter, ++rhsIter) {
				assert(lhsIter != lhsEnd && "Unexpected basic_command_list_builder op== size mismatch. rhs greater than lhs.");
				assert(rhsIter != rhsEnd && "Unexpected basic_command_list_builder op== size mismatch. lhs greater than rhs.");
				if (*lhsIter != *rhsIter) {
					return false;
				}
			}
			return true;
		}

		template <class GraphicsSurfaces, class Allocator>
		inline bool operator!=(const basic_command_list_builder<GraphicsSurfaces, Allocator>& lhs, const basic_command_list_builder<GraphicsSurfaces, Allocator>& rhs) noexcept {
			return !(lhs == rhs);
		}

		template<class GraphicsSurfaces, class Allocator>
		inline void swap(basic_command_list_builder<GraphicsSurfaces, Allocator>& lhs, basic_command_list_builder<GraphicsSurfaces, Allocator>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
			lhs.swap(rhs);
		}
	}
}