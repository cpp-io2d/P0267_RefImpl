#pragma once

#include "xpath.h"

namespace std::experimental::io2d::v1 {
	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::new_figure(const basic_point_2d<GraphicsMath>& v) noexcept {
		_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::abs_new_figure>, v);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::rel_new_figure(const basic_point_2d<GraphicsMath>& v) noexcept {
		_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::rel_new_figure>, v);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::close_figure() noexcept {
		_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::close_figure>);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept {
		_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::abs_matrix>, m);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::rel_matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept {
		_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::rel_matrix>, m);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::revert_matrix() noexcept {
		_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::revert_matrix>);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::arc(const basic_point_2d<GraphicsMath>& rad, float rot, const float sang) noexcept {
		_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::arc>, rad, rot, sang);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::cubic_curve(const basic_point_2d<GraphicsMath>& pt0, const basic_point_2d<GraphicsMath>& pt1, const basic_point_2d<GraphicsMath>& pt2) noexcept {
		_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::abs_cubic_curve>, pt0, pt1, pt2);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::line(const basic_point_2d<GraphicsMath>& pt) noexcept {
		_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::abs_line>, pt);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::quadratic_curve(const basic_point_2d<GraphicsMath>& pt0, const basic_point_2d<GraphicsMath>& pt1) noexcept {
		_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::abs_quadratic_curve>, pt0, pt1);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::rel_cubic_curve(const basic_point_2d<GraphicsMath>& dpt0, const basic_point_2d<GraphicsMath>& dpt1, const basic_point_2d<GraphicsMath>& dpt2) noexcept {
		_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::rel_cubic_curve>, dpt0, dpt1, dpt2);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::rel_line(const basic_point_2d<GraphicsMath>& dpt) noexcept {
		_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::rel_line>, dpt);
	}

	template<class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::rel_quadratic_curve(const basic_point_2d<GraphicsMath>& dpt0, const basic_point_2d<GraphicsMath>& dpt1) noexcept {
		_Data.emplace_back(in_place_type<basic_figure_items<GraphicsMath>::rel_quadratic_curve>, dpt0, dpt1);
	}

	template <class GraphicsMath, class Allocator>
	inline basic_path_builder<GraphicsMath, Allocator>::basic_path_builder() noexcept(noexcept(Allocator())) :
		basic_path_builder(Allocator()) { }

	template <class GraphicsMath, class Allocator>
	inline basic_path_builder<GraphicsMath, Allocator>::basic_path_builder(const Allocator &a) noexcept
		: _Data(a) {
	}

	template <class GraphicsMath, class Allocator>
	inline basic_path_builder<GraphicsMath, Allocator>::basic_path_builder(size_type n, const Allocator & a)
		: _Data(n, a) {
	}

	template <class GraphicsMath, class Allocator>
	inline basic_path_builder<GraphicsMath, Allocator>::basic_path_builder(size_type n, const value_type & value, const Allocator& a)
		: _Data(n, value, a) {
	}

	template <class GraphicsMath, class Allocator>
	template<class InputIterator>
	inline basic_path_builder<GraphicsMath, Allocator>::basic_path_builder(InputIterator first, InputIterator last, const Allocator& a)
		: _Data(first, last, a) {
	}

	template <class GraphicsMath, class Allocator>
	inline basic_path_builder<GraphicsMath, Allocator>::~basic_path_builder() { }

	template <class GraphicsMath, class Allocator>
	template<class InputIterator>
	inline void basic_path_builder<GraphicsMath, Allocator>::assign(InputIterator first, InputIterator last) {
		_Data.assign(first, last);
	}

	template <class GraphicsMath, class Allocator>
	template<class ...Args>
	inline typename basic_path_builder<GraphicsMath, Allocator>::reference basic_path_builder<GraphicsMath, Allocator>::emplace_back(Args && ...args) {
		return _Data.emplace_back(forward<Args>(args)...);
	}

	template <class GraphicsMath, class Allocator>
	template<class ...Args>
	inline typename basic_path_builder<GraphicsMath, Allocator>::iterator basic_path_builder<GraphicsMath, Allocator>::emplace(const_iterator position, Args&& ...args) {
		return _Data.emplace(position, forward<Args>(args)...);
	}

	template <class GraphicsMath, class Allocator>
	template<class InputIterator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::iterator basic_path_builder<GraphicsMath, Allocator>::insert(const_iterator position, InputIterator first, InputIterator last) {
		return _Data.template insert<InputIterator>(position, first, last);
	}

	template <class GraphicsMath, class Allocator>
	inline basic_path_builder<GraphicsMath, Allocator>::basic_path_builder(const basic_path_builder& pf)
		: _Data(pf._Data) {
	}

	template <class GraphicsMath, class Allocator>
	inline basic_path_builder<GraphicsMath, Allocator>::basic_path_builder(basic_path_builder&& pf) noexcept
		: _Data(move(pf._Data)) {
	}

	template <class GraphicsMath, class Allocator>
	inline basic_path_builder<GraphicsMath, Allocator>::basic_path_builder(const basic_path_builder& pf, const Allocator & a)
		: _Data(pf._Data, a) {
	}

	template <class GraphicsMath, class Allocator>
	inline basic_path_builder<GraphicsMath, Allocator>::basic_path_builder(basic_path_builder&& pf, const Allocator & a)
		: _Data(move(pf._Data), a) {
	}

	template <class GraphicsMath, class Allocator>
	inline basic_path_builder<GraphicsMath, Allocator>::basic_path_builder(initializer_list<value_type> il, const Allocator & a)
		: _Data(il, a) {
	}

	template <class GraphicsMath, class Allocator>
	inline basic_path_builder<GraphicsMath, Allocator>& basic_path_builder<GraphicsMath, Allocator>::operator=(const basic_path_builder& x) {
		_Data = x._Data;
		return *this;
	}
	template <class GraphicsMath, class Allocator>
	inline basic_path_builder<GraphicsMath, Allocator>& basic_path_builder<GraphicsMath, Allocator>::operator=(basic_path_builder&& x) noexcept(allocator_traits<Allocator>::propagate_on_container_move_assignment::value || allocator_traits<Allocator>::is_always_equal::value) {
		::std::swap(_Data, x._Data);
		return *this;
	}
	template <class GraphicsMath, class Allocator>
	inline basic_path_builder<GraphicsMath, Allocator>& basic_path_builder<GraphicsMath, Allocator>::operator=(initializer_list<value_type> il) {
		_Data.clear();
		for (const auto& item : il) {
			_Data.push_back(item);
		}
		return *this;
	}
	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::assign(size_type n, const value_type& u) {
		_Data.assign(n, u);
	}
	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::assign(initializer_list<value_type> il) {
		_Data.assign(il);
	}
	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::allocator_type basic_path_builder<GraphicsMath, Allocator>::get_allocator() const noexcept {
		return _Data.allocator_type();
	}
	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::iterator basic_path_builder<GraphicsMath, Allocator>::begin() noexcept {
		return _Data.begin();
	}
	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::const_iterator basic_path_builder<GraphicsMath, Allocator>::begin() const noexcept {
		return _Data.begin();
	}
	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::const_iterator basic_path_builder<GraphicsMath, Allocator>::cbegin() const noexcept {
		return _Data.cbegin();
	}
	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::iterator basic_path_builder<GraphicsMath, Allocator>::end() noexcept {
		return _Data.end();
	}
	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::const_iterator basic_path_builder<GraphicsMath, Allocator>::end() const noexcept {
		return _Data.end();
	}
	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::const_iterator basic_path_builder<GraphicsMath, Allocator>::cend() const noexcept {
		return _Data.cend();
	}
	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::reverse_iterator basic_path_builder<GraphicsMath, Allocator>::rbegin() noexcept {
		return _Data.rbegin();
	}
	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::const_reverse_iterator basic_path_builder<GraphicsMath, Allocator>::rbegin() const noexcept {
		return _Data.rbegin();
	}
	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::const_reverse_iterator basic_path_builder<GraphicsMath, Allocator>::crbegin() const noexcept {
		return _Data.crbegin();
	}
	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::reverse_iterator basic_path_builder<GraphicsMath, Allocator>::rend() noexcept {
		return _Data.rend();
	}
	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::const_reverse_iterator basic_path_builder<GraphicsMath, Allocator>::rend() const noexcept {
		return _Data.rend();
	}
	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::const_reverse_iterator basic_path_builder<GraphicsMath, Allocator>::crend() const noexcept {
		return _Data.crend();
	}

	template <class GraphicsMath, class Allocator>
	inline bool basic_path_builder<GraphicsMath, Allocator>::empty() const noexcept {
		return _Data.empty();
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::size_type basic_path_builder<GraphicsMath, Allocator>::size() const noexcept {
		return _Data.size();
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::size_type basic_path_builder<GraphicsMath, Allocator>::max_size() const noexcept {
		return _Data.max_size();
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::size_type basic_path_builder<GraphicsMath, Allocator>::capacity() const noexcept {
		return _Data.capacity();
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::resize(size_type sz) {
		_Data.resize(sz);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::resize(size_type sz, const value_type& c) {
		_Data.resize(sz, c);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::reserve(size_type n) {
		_Data.reserve(n);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::shrink_to_fit() {
		_Data.shrink_to_fit();
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::reference basic_path_builder<GraphicsMath, Allocator>::operator[](size_type n) {
		return _Data[n];
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::const_reference basic_path_builder<GraphicsMath, Allocator>::operator[](size_type n) const {
		return _Data[n];
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::const_reference basic_path_builder<GraphicsMath, Allocator>::at(size_type n) const {
		return _Data.at(n);
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::reference basic_path_builder<GraphicsMath, Allocator>::at(size_type n) {
		return _Data.at(n);
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::reference basic_path_builder<GraphicsMath, Allocator>::front() {
		return _Data.front();
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::const_reference basic_path_builder<GraphicsMath, Allocator>::front() const {
		return _Data.front();
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::reference basic_path_builder<GraphicsMath, Allocator>::back() {
		return _Data.back();
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::const_reference basic_path_builder<GraphicsMath, Allocator>::back() const {
		return _Data.back();
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::push_back(const value_type& x) {
		_Data.push_back(x);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::push_back(value_type&& x) {
		_Data.push_back(move(x));
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::pop_back() {
		_Data.pop_back();
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::iterator basic_path_builder<GraphicsMath, Allocator>::insert(const_iterator position, const value_type& x) {
		return _Data.insert(position, x);
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::iterator basic_path_builder<GraphicsMath, Allocator>::insert(const_iterator position, value_type&& x) {
		return _Data.insert(position, x);
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::iterator basic_path_builder<GraphicsMath, Allocator>::insert(const_iterator position, size_type n, const value_type& x) {
		return _Data.insert(position, n, x);
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::iterator basic_path_builder<GraphicsMath, Allocator>::insert(const_iterator position, initializer_list<value_type> il) {
		return _Data.insert(position, il);
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::iterator basic_path_builder<GraphicsMath, Allocator>::erase(const_iterator position) {
		return _Data.erase(position);
	}

	template <class GraphicsMath, class Allocator>
	inline typename basic_path_builder<GraphicsMath, Allocator>::iterator basic_path_builder<GraphicsMath, Allocator>::erase(const_iterator first, const_iterator last) {
		return _Data.erase(first, last);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::swap(basic_path_builder &pf) noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value || allocator_traits<Allocator>::is_always_equal::value) {
		::std::swap(_Data, pf._Data);
	}

	template <class GraphicsMath, class Allocator>
	inline void basic_path_builder<GraphicsMath, Allocator>::clear() noexcept {
		_Data.clear();
	}


	template <class GraphicsMath, class Allocator>
	inline bool operator==(const basic_path_builder<GraphicsMath, Allocator>& lhs, const basic_path_builder<GraphicsMath, Allocator>& rhs) noexcept {
		if (lhs.size() != rhs.size()) {
			return false;
		}
		//return equal(_Data.cbegin(), _Data.cend(), rhs._Data.cbegin(), rhs._Data.cend());
		auto lhsEnd = lhs._Data.end();
		auto rhsEnd = rhs._Data.end();
		auto lhsIter = lhs._Data.begin();
		auto rhsIter = rhs._Data.begin();
		for (; lhsIter != lhsEnd &&
			rhsIter != rhsEnd; ++lhsIter, ++rhsIter) {
			assert(lhsIter != lhsEnd && "Unexpected basic_path_builder op== size mismatch. rhs greater than lhs.");
			assert(rhsIter != rhsEnd && "Unexpected basic_path_builder op== size mismatch. lhs greater than rhs.");
			if (*lhsIter != *rhsIter) {
				return false;
			}
		}
		//const size_t dataSize = _Data.size();
		//for (size_t i = 0; i < dataSize; i++) {
		//	if (_Data.at(i) != rhs._Data.at(i)) {
		//		return false;
		//	}
		//}
		return true;
	}

	template<class GraphicsMath, class Allocator>
	inline void swap(basic_path_builder<GraphicsMath, Allocator>& lhs, basic_path_builder<GraphicsMath, Allocator>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
		lhs.swap(rhs);
	}
}