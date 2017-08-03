#pragma once

namespace std::experimental::io2d {
	inline namespace v1 {

		namespace figure_items {

			class abs_new_figure {
				point_2d _Data = {};
			public:
				constexpr abs_new_figure() noexcept {}

				constexpr abs_new_figure(const point_2d& pt) noexcept
					: _Data(pt) {}

				constexpr void at(const point_2d& pt) noexcept {
					_Data = pt;
				}

				constexpr point_2d at() const noexcept {
					return _Data;
				}

				constexpr bool operator==(const abs_new_figure& rhs) const noexcept {
					return _Data == rhs._Data;
				}

				constexpr bool operator!=(const abs_new_figure& rhs) const noexcept {
					return !((*this) == rhs);
				}
			};

			constexpr bool operator==(const abs_new_figure&, const abs_new_figure&)
				noexcept;
			constexpr bool operator!=(const abs_new_figure&, const abs_new_figure&)
				noexcept;

			class rel_new_figure {
				point_2d _Data = {};
			public:
				constexpr rel_new_figure() noexcept {}

				constexpr rel_new_figure(const point_2d& pt) noexcept
					: _Data(pt) {}

				constexpr void at(const point_2d& pt) noexcept {
					_Data = pt;
				}

				constexpr point_2d at() const noexcept {
					return _Data;
				}

				constexpr bool operator==(const rel_new_figure& rhs) const noexcept {
					return _Data == rhs._Data;
				}

				constexpr bool operator!=(const rel_new_figure& rhs) const noexcept {
					return !((*this) == rhs);
				}
			};

			constexpr bool operator==(const rel_new_figure&, const rel_new_figure&)
				noexcept;
			constexpr bool operator!=(const rel_new_figure&, const rel_new_figure&)
				noexcept;

			class close_figure {
			public:
				constexpr close_figure() noexcept {}

				constexpr bool operator==(const close_figure&) const noexcept {
					return true;
				}

				constexpr bool operator!=(const close_figure& rhs) const noexcept {
					return !((*this) == rhs);
				}
			};

			constexpr bool operator==(const close_figure&, const close_figure&) noexcept;
			constexpr bool operator!=(const close_figure&, const close_figure&) noexcept;

			class abs_matrix {
				matrix_2d _Matrix;
			public:
				constexpr explicit abs_matrix(const matrix_2d& m) noexcept
					: _Matrix(m) {
				}
				constexpr abs_matrix() noexcept {}

				constexpr void matrix(const matrix_2d& value) noexcept {
					_Matrix = value;
				}
				constexpr matrix_2d matrix() const noexcept {
					return _Matrix;
				}

				constexpr bool operator==(const abs_matrix& rhs) const noexcept {
					return _Matrix == rhs._Matrix;
				}

				constexpr bool operator!=(const abs_matrix& rhs) const noexcept {
					return !((*this) == rhs);
				}
			};

			constexpr bool operator==(const abs_matrix&, const abs_matrix&) noexcept;
			constexpr bool operator!=(const abs_matrix&, const abs_matrix&) noexcept;

			class rel_matrix {
				matrix_2d _Matrix;
			public:
				constexpr explicit rel_matrix(const matrix_2d& m) noexcept
					: _Matrix(m) {
				}
				constexpr rel_matrix() noexcept {}

				constexpr void matrix(const matrix_2d& value) noexcept {
					_Matrix = value;
				}
				constexpr matrix_2d matrix() const noexcept {
					return _Matrix;
				}

				constexpr bool operator==(const rel_matrix& rhs) const noexcept {
					return _Matrix == rhs._Matrix;
				}

				constexpr bool operator!=(const rel_matrix& rhs) const noexcept {
					return !((*this) == rhs);
				}
			};

			constexpr bool operator==(const rel_matrix&, const rel_matrix&) noexcept;
			constexpr bool operator!=(const rel_matrix&, const rel_matrix&) noexcept;

			class revert_matrix {
			public:
				constexpr revert_matrix() noexcept {}

				constexpr bool operator==(const revert_matrix&) const noexcept {
					return true;
				}

				constexpr bool operator!=(const revert_matrix&) const noexcept {
					return false;
				}
			};

			constexpr bool operator==(const revert_matrix&, const revert_matrix&)
				noexcept;
			constexpr bool operator!=(const revert_matrix&, const revert_matrix&)
				noexcept;

			class abs_line {
				point_2d _Data = {};
			public:
				constexpr explicit abs_line(const point_2d& to) noexcept
					: _Data(to) {
				}
				constexpr abs_line() noexcept {}

				constexpr void to(const point_2d& value) noexcept {
					_Data = value;
				}

				constexpr point_2d to() const noexcept {
					return _Data;
				}

				constexpr bool operator==(const abs_line& rhs) const noexcept {
					return _Data == rhs._Data;
				}

				constexpr bool operator!=(const abs_line& rhs) const noexcept {
					return !((*this) == rhs);
				}
			};

			constexpr bool operator==(const abs_line&, const abs_line&) noexcept;
			constexpr bool operator!=(const abs_line&, const abs_line&) noexcept;

			class rel_line {
				point_2d _Data = {};
			public:
				constexpr explicit rel_line(const point_2d& to) noexcept
					: _Data(to) {
				}
				constexpr rel_line() noexcept {}

				constexpr void to(const point_2d& value) noexcept {
					_Data = value;
				}

				constexpr point_2d to() const noexcept {
					return _Data;
				}

				constexpr bool operator==(const rel_line& rhs) const noexcept {
					return _Data == rhs._Data;
				}

				constexpr bool operator!=(const rel_line& rhs) const noexcept {
					return !((*this) == rhs);
				}
			};

			constexpr bool operator==(const rel_line&, const rel_line&) noexcept;
			constexpr bool operator!=(const rel_line&, const rel_line&) noexcept;

			class abs_quadratic_curve {
				point_2d _Control_pt = {};
				point_2d _End_pt = {};
			public:
				constexpr abs_quadratic_curve(const point_2d& cp, const point_2d& ep) noexcept
					: _Control_pt(cp)
					, _End_pt(ep) {
				}
				constexpr abs_quadratic_curve() noexcept {}

				constexpr void control_point(const point_2d& value) noexcept {
					_Control_pt = value;
				}
				constexpr void end_point(const point_2d& value) noexcept {
					_End_pt = value;
				}

				constexpr point_2d control_point() const noexcept {
					return _Control_pt;
				}
				constexpr point_2d end_point() const noexcept {
					return _End_pt;
				}

				constexpr bool operator==(const abs_quadratic_curve& rhs) const noexcept {
					return (_Control_pt == rhs._Control_pt) &&
						(_End_pt == rhs._End_pt);
				}

				constexpr bool operator!=(const abs_quadratic_curve& rhs) const noexcept {
					return !((*this) == rhs);
				}
			};

			constexpr bool operator==(const abs_quadratic_curve&,
				const abs_quadratic_curve&) noexcept;
			constexpr bool operator!=(const abs_quadratic_curve&,
				const abs_quadratic_curve&) noexcept;

			class rel_quadratic_curve {
				point_2d _Control_pt = {};
				point_2d _End_pt = {};
			public:
				constexpr rel_quadratic_curve(const point_2d& cp, const point_2d& ep) noexcept
					: _Control_pt(cp)
					, _End_pt(ep) {
				}
				constexpr rel_quadratic_curve() noexcept {}

				constexpr void control_point(const point_2d& value) noexcept {
					_Control_pt = value;
				}
				constexpr void end_point(const point_2d& value) noexcept {
					_End_pt = value;
				}

				constexpr point_2d control_point() const noexcept {
					return _Control_pt;
				}
				constexpr point_2d end_point() const noexcept {
					return _End_pt;
				}

				constexpr bool operator==(const rel_quadratic_curve& rhs) const noexcept {
					return (_Control_pt == rhs._Control_pt) &&
						(_End_pt == rhs._End_pt);
				}

				constexpr bool operator!=(const rel_quadratic_curve& rhs) const noexcept {
					return !((*this) == rhs);
				}
			};

			constexpr bool operator==(const rel_quadratic_curve&,
				const rel_quadratic_curve&) noexcept;
			constexpr bool operator!=(const rel_quadratic_curve&,
				const rel_quadratic_curve&) noexcept;

			class abs_cubic_curve {
				point_2d _Control_pt1 = {};
				point_2d _Control_pt2 = {};
				point_2d _End_pt = {};
			public:
				constexpr abs_cubic_curve(const point_2d& controlPoint1, const point_2d& controlPoint2, const point_2d& endPoint) noexcept
					: _Control_pt1(controlPoint1)
					, _Control_pt2(controlPoint2)
					, _End_pt(endPoint) {
				}
				constexpr abs_cubic_curve() noexcept {}

				constexpr void control_point_1(const point_2d& value) noexcept {
					_Control_pt1 = value;
				}
				constexpr void control_point_2(const point_2d& value) noexcept {
					_Control_pt2 = value;
				}
				constexpr void end_point(const point_2d& value) noexcept {
					_End_pt = value;
				}

				constexpr point_2d control_point_1() const noexcept {
					return _Control_pt1;
				}
				constexpr point_2d control_point_2() const noexcept {
					return _Control_pt2;
				}
				constexpr point_2d end_point() const noexcept {
					return _End_pt;
				}

				constexpr bool operator==(const abs_cubic_curve& rhs) const noexcept {
					return (_Control_pt1 == rhs._Control_pt1) &&
						(_Control_pt2 == rhs._Control_pt2) &&
						(_End_pt == rhs._End_pt);
				}

				constexpr bool operator!=(const abs_cubic_curve& rhs) const noexcept {
					return !((*this) == rhs);
				}
			};

			constexpr bool operator==(const abs_cubic_curve&, const abs_cubic_curve&)
				noexcept;
			constexpr bool operator!=(const abs_cubic_curve&, const abs_cubic_curve&)
				noexcept;

			class rel_cubic_curve {
				point_2d _Control_pt1 = {};
				point_2d _Control_pt2 = {};
				point_2d _End_pt = {};
			public:
				constexpr rel_cubic_curve(const point_2d& controlPoint1, const point_2d& controlPoint2, const point_2d& endPoint) noexcept
					: _Control_pt1(controlPoint1)
					, _Control_pt2(controlPoint2)
					, _End_pt(endPoint) {
				}
				constexpr rel_cubic_curve() noexcept {}

				constexpr void control_point_1(const point_2d& value) noexcept {
					_Control_pt1 = value;
				}
				constexpr void control_point_2(const point_2d& value) noexcept {
					_Control_pt2 = value;
				}
				constexpr void end_point(const point_2d& value) noexcept {
					_End_pt = value;
				}

				constexpr point_2d control_point_1() const noexcept {
					return _Control_pt1;
				}
				constexpr point_2d control_point_2() const noexcept {
					return _Control_pt2;
				}
				constexpr point_2d end_point() const noexcept {
					return _End_pt;
				}

				constexpr bool operator==(const rel_cubic_curve& rhs) const noexcept {
					return (_Control_pt1 == rhs._Control_pt1) &&
						(_Control_pt2 == rhs._Control_pt2) &&
						(_End_pt == rhs._End_pt);
				}

				constexpr bool operator!=(const rel_cubic_curve& rhs) const noexcept {
					return !((*this) == rhs);
				}
			};

			constexpr bool operator==(const rel_cubic_curve&, const rel_cubic_curve&)
				noexcept;
			constexpr bool operator!=(const rel_cubic_curve&, const rel_cubic_curve&)
				noexcept;

			class arc {
				point_2d _Radius;
				float _Rotation;
				float _Start_angle;
			public:
				constexpr arc() noexcept
					: arc(point_2d{ 10.0F, 10.0F }, pi<float>, pi<float>) { }
				constexpr arc(const point_2d& rad, float rot, float sang = pi<float>) noexcept
					: _Radius(rad)
					, _Rotation(rot)
					, _Start_angle(sang) {
				}

				constexpr void radius(const point_2d& rad) noexcept {
					_Radius = rad;
				}
				constexpr void rotation(float rot) noexcept {
					_Rotation = rot;
				}
				constexpr void start_angle(float sang) noexcept {
					_Start_angle = sang;
				}

				constexpr point_2d radius() const noexcept {
					return _Radius;
				}
				constexpr float rotation() const noexcept {
					return _Rotation;
				}
				constexpr float start_angle() const noexcept {
					return _Start_angle;
				}

				point_2d center(point_2d cpt, const matrix_2d& m) const noexcept {
					auto lmtx = m;
					lmtx.m20 = 0.0F; lmtx.m21 = 0.0F; // Eliminate translation.
					auto centerOffset = point_for_angle(two_pi<float> -_Start_angle, _Radius);
					centerOffset.y = -centerOffset.y;
					return cpt - centerOffset * lmtx;
				}

				point_2d end_pt(point_2d cpt, const matrix_2d& m) const noexcept {
					auto lmtx = m;
					auto tfrm = matrix_2d::init_rotate(_Start_angle + _Rotation);
					lmtx.m20 = 0.0F; lmtx.m21 = 0.0F; // Eliminate translation.
					auto pt = (_Radius * tfrm);
					pt.y = -pt.y;
					return cpt + pt * lmtx;
				}

				constexpr bool operator==(const arc& rhs) const noexcept {
					return (_Radius == rhs._Radius) &&
						(_Rotation == rhs._Rotation) &&
						(_Start_angle == rhs._Start_angle);
				}

				constexpr bool operator!=(const arc& rhs) const noexcept {
					return !((*this) == rhs);
				}
			};

			constexpr bool operator==(const arc&, const arc&) noexcept;
			constexpr bool operator!=(const arc&, const arc&) noexcept;

			using figure_item = variant<abs_cubic_curve, abs_line, abs_matrix,
				abs_new_figure, abs_quadratic_curve, arc, close_figure,
				rel_cubic_curve, rel_line, rel_matrix, rel_new_figure, rel_quadratic_curve,
				revert_matrix>;
		}

		template <class Allocator = allocator<figure_items::figure_item>>
		class path_builder {
			::std::vector<figure_items::figure_item, Allocator> _Data;
		public:
			using value_type = figure_items::figure_item;
			using allocator_type = Allocator;
			using reference = value_type&;
			using const_reference = const value_type&;
			using size_type = ::std::vector<figure_items::figure_item>::size_type;
			using difference_type = ::std::vector<figure_items::figure_item>::difference_type;
			using iterator = ::std::vector<figure_items::figure_item>::iterator;
			using const_iterator = ::std::vector<figure_items::figure_item>::const_iterator;
			using reverse_iterator = std::reverse_iterator<iterator>;
			using const_reverse_iterator = std::reverse_iterator<const_iterator>;

			path_builder() noexcept(noexcept(Allocator())) :
				path_builder(Allocator()) { }
			explicit path_builder(const Allocator& a) noexcept;
			explicit path_builder(size_type n, const Allocator& a = Allocator());
			path_builder(size_type n, const value_type& value,
				const Allocator& a = Allocator());
			template <class InputIterator>
			path_builder(InputIterator first, InputIterator last,
				const Allocator& = Allocator());
			path_builder(const path_builder& pf);
			path_builder(path_builder&& pf) noexcept;
			path_builder(const path_builder& pf, const Allocator& a);
			path_builder(path_builder&& pf, const Allocator& a);
			path_builder(initializer_list<value_type> il, const Allocator& a = Allocator());
			~path_builder() { }
			path_builder& operator=(const path_builder& x);
			path_builder& operator=(path_builder&& x)
				noexcept(
					allocator_traits<Allocator>::propagate_on_container_move_assignment::value
					|| allocator_traits<Allocator>::is_always_equal::value);
			path_builder& operator=(initializer_list<value_type> il);
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last);
			void assign(size_type n, const value_type& u);
			void assign(initializer_list<value_type> il);
			allocator_type get_allocator() const noexcept;

			iterator begin() noexcept;
			const_iterator begin() const noexcept;
			const_iterator cbegin() const noexcept;
			iterator end() noexcept;
			const_iterator end() const noexcept;
			const_iterator cend() const noexcept;
			reverse_iterator rbegin() noexcept;
			const_reverse_iterator rbegin() const noexcept;
			const_reverse_iterator crbegin() const noexcept;
			reverse_iterator rend() noexcept;
			const_reverse_iterator rend() const noexcept;
			const_reverse_iterator crend() const noexcept;

			bool empty() const noexcept;
			size_type size() const noexcept;
			size_type max_size() const noexcept;
			size_type capacity() const noexcept;
			void resize(size_type sz);
			void resize(size_type sz, const value_type& c);
			void reserve(size_type n);
			void shrink_to_fit();

			reference operator[](size_type n);
			const_reference operator[](size_type n) const;
			const_reference at(size_type n) const;
			reference at(size_type n);
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;

			// Modifiers
			void new_path(const point_2d& v) noexcept;
			void rel_new_figure(const point_2d& v) noexcept;
			void close_figure() noexcept;
			void matrix(const matrix_2d& m) noexcept;
			void rel_matrix(const matrix_2d& m) noexcept;
			void revert_matrix() noexcept;
			void arc(const point_2d& radius, float rot, float sang = pi<float>) noexcept;
			void cubic_curve(const point_2d& pt0, const point_2d& pt1,
				const point_2d& pt2) noexcept;
			void line(const point_2d& pt) noexcept;
			void quadratic_curve(const point_2d& pt0, const point_2d& pt1)
				noexcept;
			void rel_cubic_curve(const point_2d& dpt0, const point_2d& dpt1,
				const point_2d& dpt2) noexcept;
			void rel_line(const point_2d& dpt) noexcept;
			void rel_quadratic_curve(const point_2d& dpt0, const point_2d& dpt1)
				noexcept;
			template <class... Args>
			reference emplace_back(Args&&... args);
			void push_back(const value_type& x);
			void push_back(value_type&& x);
			void pop_back();

			template <class... Args>
			iterator emplace(const_iterator position, Args&&... args);
			iterator insert(const_iterator position, const value_type& x);
			iterator insert(const_iterator position, value_type&& x);
			iterator insert(const_iterator position, size_type n, const value_type& x);
			template <class InputIterator>
			iterator insert(const_iterator position, InputIterator first,
				InputIterator last);
			iterator insert(const_iterator position,
				initializer_list<value_type> il);
			iterator erase(const_iterator position);
			iterator erase(const_iterator first, const_iterator last);
			void swap(path_builder&)
				noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value
					|| allocator_traits<Allocator>::is_always_equal::value);
			void clear() noexcept;

			// Observers
			::std::experimental::io2d::bounding_box path_extents() const;

			bool operator==(const path_builder& rhs) const noexcept {
				if (size() != rhs.size()) {
					return false;
				}
				//return equal(_Data.cbegin(), _Data.cend(), rhs._Data.cbegin(), rhs._Data.cend());
				auto lhsEnd = _Data.end();
				auto rhsEnd = rhs._Data.end();
				auto lhsIter = _Data.begin();
				auto rhsIter = rhs._Data.begin();
				for (; lhsIter != lhsEnd &&
					rhsIter != rhsEnd; ++lhsIter, ++rhsIter) {
					assert(lhsIter != lhsEnd && "Unexpected path_builder op== size mismatch. rhs greater than lhs.");
					assert(rhsIter != rhsEnd && "Unexpected path_builder op== size mismatch. lhs greater than rhs.");
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
			bool operator!=(const path_builder& rhs) const noexcept {
				return !((*this) == rhs);
			}
		};

		// 8.17.8, specialized algorithms:
		template <class Allocator>
		void swap(path_builder<Allocator>& lhs, path_builder<Allocator>& rhs)
			noexcept(noexcept(lhs.swap(rhs))) {
			lhs.swap(rhs);
		}

		template <class Allocator>
		bool operator==(const path_builder<Allocator>& lhs,
			const path_builder<Allocator>& rhs) noexcept;
		template <class Allocator>
		bool operator!=(const path_builder<Allocator>& lhs,
			const path_builder<Allocator>& rhs) noexcept;

		template <class Allocator>
		void swap(path_builder<Allocator>& lhs, path_builder<Allocator>& rhs)
			noexcept(noexcept(lhs.swap(rhs)));

		class path_group {
			::std::shared_ptr<cairo_path_t> _Cairo_path;
		public:
			using native_handle_type = cairo_path*;
			// Note: Can default construct. It will just be empty. To be useful it would need to be assigned to.
			path_group() noexcept = default;
			template <class Allocator>
			explicit path_group(const path_builder<Allocator>& p);
			template <class Allocator>
			path_group(const path_builder<Allocator>& p, std::error_code& ec) noexcept;

			native_handle_type native_handle() {
				return _Cairo_path.get();
			}
			const cairo_path* native_handle() const {
				return _Cairo_path.get();
			}
		};

	}
}