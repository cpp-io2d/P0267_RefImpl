#pragma once

#include "xio2d.h"

#include <memory>
#include <functional>
#include <exception>
#include <vector>
#include <string>
#include <algorithm>
#include <system_error>
#include <cstdint>
#include <atomic>
#include <variant>
#include <optional>
#include <cmath>
#include <type_traits>
#include <initializer_list>
#include <cmath>

#ifdef _Filesystem_support_test
#include <filesystem>
#endif

namespace std::experimental::io2d {
	inline namespace v1 {

		inline cairo_interpreted_path::_Native_handle_type cairo_interpreted_path::_Native_handle() const noexcept {
			return _Cairo_path.get();
		}

		constexpr cairo_interpreted_path::cairo_interpreted_path() noexcept
			: _Cairo_path(nullptr)
		{}

		template <class Allocator>
		inline cairo_interpreted_path::cairo_interpreted_path(const path_builder<Allocator>& pf)
			: _Cairo_path(new cairo_path_t, [](cairo_path_t*) {
			// This deleter intentionally left blank. The dtor will deal with this.
		}) {
			auto processedVec = _Interpret_path_items<Allocator>(pf);
			::std::vector<cairo_path_data_t> vec;
			point_2d lastMoveToPoint;
			for (const auto& val : processedVec) {
				::std::visit([&vec, &lastMoveToPoint](auto&& item) {
					using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
					_Path_group_perform_visit<T>::template _Perform<T>(vec, item, lastMoveToPoint);
				}, val);
			}
			_Cairo_path->num_data = static_cast<int>(vec.size());
			const auto numDataST = vec.size();
			_Cairo_path->data = new cairo_path_data_t[numDataST];
			for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
				_Cairo_path->data[currItemIndex] = vec[currItemIndex];
			}
			_Cairo_path->status = CAIRO_STATUS_SUCCESS;
		}

		template <class ForwardIterator>
		inline cairo_interpreted_path::cairo_interpreted_path(ForwardIterator first, ForwardIterator last)
			: _Cairo_path(new cairo_path_t, [](cairo_path_t*) {
			// This deleter intentionally left blank. The dtor will deal with this.
		}) {
			auto processedVec = _Interpret_path_items<ForwardIterator>(first, last);
			::std::vector<cairo_path_data_t> vec;
			point_2d lastMoveToPoint;
			for (const auto& val : processedVec) {
				::std::visit([&vec, &lastMoveToPoint](auto&& item) {
					using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
					_Path_group_perform_visit<T>::template _Perform<T>(vec, item, lastMoveToPoint);
				}, val);
			}
			_Cairo_path->num_data = static_cast<int>(vec.size());
			const auto numDataST = vec.size();
			_Cairo_path->data = new cairo_path_data_t[numDataST];
			for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
				_Cairo_path->data[currItemIndex] = vec[currItemIndex];
			}
			_Cairo_path->status = CAIRO_STATUS_SUCCESS;
		}

		inline cairo_interpreted_path::cairo_interpreted_path(const cairo_interpreted_path& other) noexcept
			: _Cairo_path(other._Cairo_path) {}

		inline cairo_interpreted_path& cairo_interpreted_path::operator=(const cairo_interpreted_path& other) noexcept {
			_Cairo_path = other._Cairo_path;
			return *this;
		}

		inline cairo_interpreted_path::cairo_interpreted_path(cairo_interpreted_path&& other) noexcept
			: _Cairo_path(move(other._Cairo_path)) {
			other._Cairo_path = nullptr;
		}

		inline cairo_interpreted_path& cairo_interpreted_path::operator=(cairo_interpreted_path&& other) noexcept {
			if (this != &other) {
				_Cairo_path = move(other._Cairo_path);
				other._Cairo_path = nullptr;
			}
			return *this;
		}

		inline cairo_interpreted_path::~cairo_interpreted_path() noexcept {
			auto path = _Cairo_path.get();
			if (path != nullptr) {
				if (path->data != nullptr) {
					delete[] path->data;
					path->data = nullptr;
					path->status = CAIRO_STATUS_NULL_POINTER;
				}
				delete path;
				path = nullptr;
				_Cairo_path = nullptr;
			}
		}
	}
}