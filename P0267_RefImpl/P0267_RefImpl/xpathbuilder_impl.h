#pragma once

#include "xpath.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::new_figure(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& v) noexcept {
			_Data.emplace_back(in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_new_figure>, v);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::rel_new_figure(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& v) noexcept {
			_Data.emplace_back(in_place_type<typename basic_figure_items<GraphicsSurfaces>::rel_new_figure>, v);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::close_figure() noexcept {
			_Data.emplace_back(in_place_type<typename basic_figure_items<GraphicsSurfaces>::close_figure>);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept {
			_Data.emplace_back(in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_matrix>, m);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::rel_matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept {
			_Data.emplace_back(in_place_type<typename basic_figure_items<GraphicsSurfaces>::rel_matrix>, m);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::revert_matrix() noexcept {
			_Data.emplace_back(in_place_type<typename basic_figure_items<GraphicsSurfaces>::revert_matrix>);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::arc(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& rad, float rot, const float sang) noexcept {
			_Data.emplace_back(in_place_type<typename basic_figure_items<GraphicsSurfaces>::arc>, rad, rot, sang);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::cubic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt0, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt1, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt2) noexcept {
			_Data.emplace_back(in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve>, pt0, pt1, pt2);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::line(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept {
			_Data.emplace_back(in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_line>, pt);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::quadratic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt0, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt1) noexcept {
			_Data.emplace_back(in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve>, pt0, pt1);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::rel_cubic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& dpt0, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& dpt1, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& dpt2) noexcept {
			_Data.emplace_back(in_place_type<typename basic_figure_items<GraphicsSurfaces>::rel_cubic_curve>, dpt0, dpt1, dpt2);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::rel_line(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& dpt) noexcept {
			_Data.emplace_back(in_place_type<typename basic_figure_items<GraphicsSurfaces>::rel_line>, dpt);
		}

		template<class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::rel_quadratic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& dpt0, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& dpt1) noexcept {
			_Data.emplace_back(in_place_type<typename basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve>, dpt0, dpt1);
		}

		template<class GraphicsSurfaces, class Allocator>
		inline const typename basic_path_builder<GraphicsSurfaces, Allocator>::data_type& basic_path_builder<GraphicsSurfaces, Allocator>::data() const noexcept {
			return _Data;
		}

		template<class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::data_type& basic_path_builder<GraphicsSurfaces, Allocator>::data() noexcept {
			return _Data;
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_path_builder<GraphicsSurfaces, Allocator>::basic_path_builder() noexcept(noexcept(Allocator())) :
			basic_path_builder(Allocator()) { }

		template <class GraphicsSurfaces, class Allocator>
		inline basic_path_builder<GraphicsSurfaces, Allocator>::basic_path_builder(const Allocator &a) noexcept
			: _Data(a) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_path_builder<GraphicsSurfaces, Allocator>::basic_path_builder(size_type n, const Allocator & a)
			: _Data(n, a) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_path_builder<GraphicsSurfaces, Allocator>::basic_path_builder(size_type n, const value_type & value, const Allocator& a)
			: _Data(n, value, a) {
		}

		template <class GraphicsSurfaces, class Allocator>
		template<class InputIterator>
		inline basic_path_builder<GraphicsSurfaces, Allocator>::basic_path_builder(InputIterator first, InputIterator last, const Allocator& a)
			: _Data(first, last, a) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_path_builder<GraphicsSurfaces, Allocator>::~basic_path_builder() { }

		template <class GraphicsSurfaces, class Allocator>
		template<class InputIterator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::assign(InputIterator first, InputIterator last) {
			_Data.assign(first, last);
		}

		template <class GraphicsSurfaces, class Allocator>
		template<class ...Args>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::reference basic_path_builder<GraphicsSurfaces, Allocator>::emplace_back(Args && ...args) {
			return _Data.emplace_back(forward<Args>(args)...);
		}

		template <class GraphicsSurfaces, class Allocator>
		template<class ...Args>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::iterator basic_path_builder<GraphicsSurfaces, Allocator>::emplace(const_iterator position, Args&& ...args) {
			return _Data.emplace(position, forward<Args>(args)...);
		}

		template <class GraphicsSurfaces, class Allocator>
		template<class InputIterator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::iterator basic_path_builder<GraphicsSurfaces, Allocator>::insert(const_iterator position, InputIterator first, InputIterator last) {
			return _Data.template insert<InputIterator>(position, first, last);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_path_builder<GraphicsSurfaces, Allocator>::basic_path_builder(const basic_path_builder& pf)
			: _Data(pf._Data) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_path_builder<GraphicsSurfaces, Allocator>::basic_path_builder(basic_path_builder&& pf) noexcept
			: _Data(move(pf._Data)) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_path_builder<GraphicsSurfaces, Allocator>::basic_path_builder(const basic_path_builder& pf, const Allocator & a)
			: _Data(pf._Data, a) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_path_builder<GraphicsSurfaces, Allocator>::basic_path_builder(basic_path_builder&& pf, const Allocator & a)
			: _Data(move(pf._Data), a) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_path_builder<GraphicsSurfaces, Allocator>::basic_path_builder(initializer_list<value_type> il, const Allocator & a)
			: _Data(il, a) {
		}

		template <class GraphicsSurfaces, class Allocator>
		inline basic_path_builder<GraphicsSurfaces, Allocator>& basic_path_builder<GraphicsSurfaces, Allocator>::operator=(const basic_path_builder& x) {
			_Data = x._Data;
			return *this;
		}
		template <class GraphicsSurfaces, class Allocator>
		inline basic_path_builder<GraphicsSurfaces, Allocator>& basic_path_builder<GraphicsSurfaces, Allocator>::operator=(basic_path_builder&& x) noexcept(allocator_traits<Allocator>::propagate_on_container_move_assignment::value || allocator_traits<Allocator>::is_always_equal::value) {
			::std::swap(_Data, x._Data);
			return *this;
		}
		template <class GraphicsSurfaces, class Allocator>
		inline basic_path_builder<GraphicsSurfaces, Allocator>& basic_path_builder<GraphicsSurfaces, Allocator>::operator=(initializer_list<value_type> il) {
			_Data.clear();
			for (const auto& item : il) {
				_Data.push_back(item);
			}
			return *this;
		}
		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::assign(size_type n, const value_type& u) {
			_Data.assign(n, u);
		}
		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::assign(initializer_list<value_type> il) {
			_Data.assign(il);
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::allocator_type basic_path_builder<GraphicsSurfaces, Allocator>::get_allocator() const noexcept {
			return _Data.allocator_type();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::iterator basic_path_builder<GraphicsSurfaces, Allocator>::begin() noexcept {
			return _Data.begin();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::const_iterator basic_path_builder<GraphicsSurfaces, Allocator>::begin() const noexcept {
			return _Data.begin();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::const_iterator basic_path_builder<GraphicsSurfaces, Allocator>::cbegin() const noexcept {
			return _Data.cbegin();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::iterator basic_path_builder<GraphicsSurfaces, Allocator>::end() noexcept {
			return _Data.end();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::const_iterator basic_path_builder<GraphicsSurfaces, Allocator>::end() const noexcept {
			return _Data.end();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::const_iterator basic_path_builder<GraphicsSurfaces, Allocator>::cend() const noexcept {
			return _Data.cend();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::reverse_iterator basic_path_builder<GraphicsSurfaces, Allocator>::rbegin() noexcept {
			return _Data.rbegin();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::const_reverse_iterator basic_path_builder<GraphicsSurfaces, Allocator>::rbegin() const noexcept {
			return _Data.rbegin();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::const_reverse_iterator basic_path_builder<GraphicsSurfaces, Allocator>::crbegin() const noexcept {
			return _Data.crbegin();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::reverse_iterator basic_path_builder<GraphicsSurfaces, Allocator>::rend() noexcept {
			return _Data.rend();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::const_reverse_iterator basic_path_builder<GraphicsSurfaces, Allocator>::rend() const noexcept {
			return _Data.rend();
		}
		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::const_reverse_iterator basic_path_builder<GraphicsSurfaces, Allocator>::crend() const noexcept {
			return _Data.crend();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline bool basic_path_builder<GraphicsSurfaces, Allocator>::empty() const noexcept {
			return _Data.empty();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::size_type basic_path_builder<GraphicsSurfaces, Allocator>::size() const noexcept {
			return _Data.size();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::size_type basic_path_builder<GraphicsSurfaces, Allocator>::max_size() const noexcept {
			return _Data.max_size();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::size_type basic_path_builder<GraphicsSurfaces, Allocator>::capacity() const noexcept {
			return _Data.capacity();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::resize(size_type sz) {
			_Data.resize(sz);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::resize(size_type sz, const value_type& c) {
			_Data.resize(sz, c);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::reserve(size_type n) {
			_Data.reserve(n);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::shrink_to_fit() {
			_Data.shrink_to_fit();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::reference basic_path_builder<GraphicsSurfaces, Allocator>::operator[](size_type n) {
			return _Data[n];
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::const_reference basic_path_builder<GraphicsSurfaces, Allocator>::operator[](size_type n) const {
			return _Data[n];
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::const_reference basic_path_builder<GraphicsSurfaces, Allocator>::at(size_type n) const {
			return _Data.at(n);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::reference basic_path_builder<GraphicsSurfaces, Allocator>::at(size_type n) {
			return _Data.at(n);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::reference basic_path_builder<GraphicsSurfaces, Allocator>::front() {
			return _Data.front();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::const_reference basic_path_builder<GraphicsSurfaces, Allocator>::front() const {
			return _Data.front();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::reference basic_path_builder<GraphicsSurfaces, Allocator>::back() {
			return _Data.back();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::const_reference basic_path_builder<GraphicsSurfaces, Allocator>::back() const {
			return _Data.back();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::push_back(const value_type& x) {
			_Data.push_back(x);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::push_back(value_type&& x) {
			_Data.push_back(move(x));
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::pop_back() {
			_Data.pop_back();
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::iterator basic_path_builder<GraphicsSurfaces, Allocator>::insert(const_iterator position, const value_type& x) {
			return _Data.insert(position, x);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::iterator basic_path_builder<GraphicsSurfaces, Allocator>::insert(const_iterator position, value_type&& x) {
			return _Data.insert(position, x);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::iterator basic_path_builder<GraphicsSurfaces, Allocator>::insert(const_iterator position, size_type n, const value_type& x) {
			return _Data.insert(position, n, x);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::iterator basic_path_builder<GraphicsSurfaces, Allocator>::insert(const_iterator position, initializer_list<value_type> il) {
			return _Data.insert(position, il);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::iterator basic_path_builder<GraphicsSurfaces, Allocator>::erase(const_iterator position) {
			return _Data.erase(position);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline typename basic_path_builder<GraphicsSurfaces, Allocator>::iterator basic_path_builder<GraphicsSurfaces, Allocator>::erase(const_iterator first, const_iterator last) {
			return _Data.erase(first, last);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::swap(basic_path_builder &pf) noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value || allocator_traits<Allocator>::is_always_equal::value) {
			::std::swap(_Data, pf._Data);
		}

		template <class GraphicsSurfaces, class Allocator>
		inline void basic_path_builder<GraphicsSurfaces, Allocator>::clear() noexcept {
			_Data.clear();
		}


		template <class GraphicsSurfaces, class Allocator>
		inline bool operator==(const basic_path_builder<GraphicsSurfaces, Allocator>& lhs, const basic_path_builder<GraphicsSurfaces, Allocator>& rhs) noexcept {
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
				assert(lhsIter != lhsEnd && "Unexpected basic_path_builder op== size mismatch. rhs greater than lhs.");
				assert(rhsIter != rhsEnd && "Unexpected basic_path_builder op== size mismatch. lhs greater than rhs.");
				if (*lhsIter != *rhsIter) {
					return false;
				}
			}
			return true;
		}
        
        template <class GraphicsSurfaces, class Allocator>
        inline bool operator!=(const basic_path_builder<GraphicsSurfaces, Allocator>& lhs, const basic_path_builder<GraphicsSurfaces, Allocator>& rhs) noexcept {
            return !(lhs == rhs);
        }

		template<class GraphicsSurfaces, class Allocator>
		inline void swap(basic_path_builder<GraphicsSurfaces, Allocator>& lhs, basic_path_builder<GraphicsSurfaces, Allocator>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
			lhs.swap(rhs);
		}
	}
}
