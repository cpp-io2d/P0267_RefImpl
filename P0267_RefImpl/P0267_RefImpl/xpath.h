#pragma once

namespace std::experimental::io2d {
	inline namespace v1 {

		namespace figure_items {
			class abs_new_figure;
			class rel_new_figure;
			class close_figure;
			class abs_matrix;
			class rel_matrix;
			class revert_matrix;
			class abs_cubic_curve;
			class abs_line;
			class abs_quadratic_curve;
			class arc;
			class rel_cubic_curve;
			class rel_line;
			class rel_quadratic_curve;

			class abs_new_figure {
				point_2d _Data = {};
				friend constexpr bool operator==(const abs_new_figure&, const abs_new_figure&) noexcept;
			public:
				constexpr abs_new_figure() noexcept;
				constexpr explicit abs_new_figure(point_2d pt) noexcept;
				constexpr void at(point_2d pt) noexcept;
				constexpr point_2d at() const noexcept;
			};

			constexpr bool operator==(const abs_new_figure& lhs, const abs_new_figure& rhs) noexcept;
			constexpr bool operator!=(const abs_new_figure& lhs, const abs_new_figure& rhs) noexcept;

			class rel_new_figure {
				point_2d _Data = {};
				friend constexpr bool operator==(const rel_new_figure&, const rel_new_figure&) noexcept;
			public:
				constexpr rel_new_figure() noexcept;
				constexpr explicit rel_new_figure(point_2d pt) noexcept;
				constexpr void at(point_2d pt) noexcept;
				constexpr point_2d at() const noexcept;
			};

			constexpr bool operator==(const rel_new_figure& lhs, const rel_new_figure& rhs) noexcept;
			constexpr bool operator!=(const rel_new_figure& lhs, const rel_new_figure& rhs) noexcept;

			class close_figure {
				friend constexpr bool operator==(const close_figure&, const close_figure&) noexcept;
			public:
				constexpr close_figure() noexcept;
			};

			constexpr bool operator==(const close_figure&, const close_figure&) noexcept;
			constexpr bool operator!=(const close_figure&, const close_figure&) noexcept;

			class abs_matrix {
				matrix_2d _Matrix;
				friend constexpr bool operator==(const abs_matrix&, const abs_matrix&) noexcept;
			public:
				constexpr abs_matrix() noexcept;
				constexpr explicit abs_matrix(const matrix_2d& m) noexcept;
				constexpr void matrix(const matrix_2d& m) noexcept;
				constexpr matrix_2d matrix() const noexcept;
			};

			constexpr bool operator==(const abs_matrix& lhs, const abs_matrix& rhs) noexcept;
			constexpr bool operator!=(const abs_matrix& lhs, const abs_matrix& rhs) noexcept;

			class rel_matrix {
				matrix_2d _Matrix;
				friend constexpr bool operator==(const rel_matrix&, const rel_matrix&) noexcept;
			public:
				constexpr rel_matrix() noexcept;
				constexpr explicit rel_matrix(const matrix_2d& m) noexcept;
				constexpr void matrix(const matrix_2d& m) noexcept;
				constexpr matrix_2d matrix() const noexcept;
			};

			constexpr bool operator==(const rel_matrix& lhs, const rel_matrix& rhs) noexcept;
			constexpr bool operator!=(const rel_matrix& lhs, const rel_matrix& rhs) noexcept;

			class revert_matrix {
				friend constexpr bool operator==(const revert_matrix&, const revert_matrix&) noexcept;
			public:
				constexpr revert_matrix() noexcept;
			};

			constexpr bool operator==(const revert_matrix& lhs, const revert_matrix& rhs) noexcept;
			constexpr bool operator!=(const revert_matrix& lhs, const revert_matrix& rhs) noexcept;

			class abs_line {
				point_2d _Data = {};
				friend constexpr bool operator==(const abs_line&, const abs_line&) noexcept;
			public:
				constexpr abs_line() noexcept;
				constexpr explicit abs_line(point_2d pt) noexcept;
				constexpr void to(point_2d pt) noexcept;
				constexpr point_2d to() const noexcept;
			};

			constexpr bool operator==(const abs_line& lhs, const abs_line& rhs) noexcept;
			constexpr bool operator!=(const abs_line& lhs, const abs_line& rhs) noexcept;

			class rel_line {
				point_2d _Data = {};
				friend constexpr bool operator==(const rel_line&, const rel_line&) noexcept;
			public:
				constexpr rel_line() noexcept;
				constexpr explicit rel_line(point_2d pt) noexcept;
				constexpr void to(point_2d pt) noexcept;
				constexpr point_2d to() const noexcept;
			};

			constexpr bool operator==(const rel_line& lhs, const rel_line& rhs) noexcept;
			constexpr bool operator!=(const rel_line& lhs, const rel_line& rhs) noexcept;

			class abs_quadratic_curve {
				point_2d _Control_pt = {};
				point_2d _End_pt = {};
				friend constexpr bool operator==(const abs_quadratic_curve&, const abs_quadratic_curve&) noexcept;
			public:
				constexpr abs_quadratic_curve() noexcept;
				constexpr abs_quadratic_curve(point_2d cpt, point_2d ept) noexcept;
				constexpr void control_pt(point_2d cpt) noexcept;
				constexpr void end_pt(point_2d ept) noexcept;
				constexpr point_2d control_pt() const noexcept;
				constexpr point_2d end_pt() const noexcept;
			};

			constexpr bool operator==(const abs_quadratic_curve& lhs, const abs_quadratic_curve& rhs) noexcept;
			constexpr bool operator!=(const abs_quadratic_curve& lhs, const abs_quadratic_curve& rhs) noexcept;

			class rel_quadratic_curve {
				point_2d _Control_pt = {};
				point_2d _End_pt = {};
				friend constexpr bool operator==(const rel_quadratic_curve&, const rel_quadratic_curve&) noexcept;
			public:
				constexpr rel_quadratic_curve() noexcept;
				constexpr rel_quadratic_curve(point_2d cpt, point_2d ept) noexcept;
				constexpr void control_pt(point_2d cpt) noexcept;
				constexpr void end_pt(point_2d ept) noexcept;
				constexpr point_2d control_pt() const noexcept;
				constexpr point_2d end_pt() const noexcept;
			};

			constexpr bool operator==(const rel_quadratic_curve& lhs, const rel_quadratic_curve& rhs) noexcept;
			constexpr bool operator!=(const rel_quadratic_curve& lhs, const rel_quadratic_curve& rhs) noexcept;

			class abs_cubic_curve {
				point_2d _Control_pt1 = {};
				point_2d _Control_pt2 = {};
				point_2d _End_pt = {};
				friend constexpr bool operator==(const abs_cubic_curve&, const abs_cubic_curve&) noexcept;
			public:
				constexpr abs_cubic_curve() noexcept;
				constexpr abs_cubic_curve(point_2d cpt1, point_2d cpt2, point_2d ept) noexcept;
				constexpr void control_pt1(point_2d cpt) noexcept;
				constexpr void control_pt2(point_2d cpt) noexcept;
				constexpr void end_pt(point_2d ept) noexcept;
				constexpr point_2d control_pt1() const noexcept;
				constexpr point_2d control_pt2() const noexcept;
				constexpr point_2d end_pt() const noexcept;
			};

			constexpr bool operator==(const abs_cubic_curve& lhs, const abs_cubic_curve& rhs) noexcept;
			constexpr bool operator!=(const abs_cubic_curve& lhs, const abs_cubic_curve& rhs) noexcept;

			class rel_cubic_curve {
				point_2d _Control_pt1 = {};
				point_2d _Control_pt2 = {};
				point_2d _End_pt = {};
				friend constexpr bool operator==(const rel_cubic_curve&, const rel_cubic_curve&) noexcept;
			public:
				constexpr rel_cubic_curve() noexcept;
				constexpr rel_cubic_curve(point_2d cpt1, point_2d cpt2, point_2d ept) noexcept;
				constexpr void control_pt1(point_2d cpt) noexcept;
				constexpr void control_pt2(point_2d cpt) noexcept;
				constexpr void end_pt(point_2d ept) noexcept;
				constexpr point_2d control_pt1() const noexcept;
				constexpr point_2d control_pt2() const noexcept;
				constexpr point_2d end_pt() const noexcept;
			};

			constexpr bool operator==(const rel_cubic_curve& lhs, const rel_cubic_curve& rhs) noexcept;
			constexpr bool operator!=(const rel_cubic_curve& lhs, const rel_cubic_curve& rhs) noexcept;

			class arc {
				point_2d _Radius;
				float _Rotation;
				float _Start_angle;

				friend constexpr bool operator==(const arc&, const arc&) noexcept;
			public:
				constexpr arc() noexcept;
				constexpr arc(point_2d rad, float rot, float sang) noexcept;
				constexpr void radius(point_2d rad) noexcept;
				constexpr void rotation(float rot) noexcept;
				constexpr void start_angle(float radians) noexcept;
				constexpr point_2d radius() const noexcept;
				constexpr float rotation() const noexcept;
				constexpr float start_angle() const noexcept;
				point_2d center(point_2d cpt, const matrix_2d& m = matrix_2d{}) const noexcept;
				point_2d end_pt(point_2d cpt, const matrix_2d& m = matrix_2d{}) const noexcept;
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

			path_builder() noexcept(noexcept(Allocator()));
			explicit path_builder(const Allocator&) noexcept;
			explicit path_builder(size_type n, const Allocator& = Allocator());
			path_builder(size_type n, const value_type& value,
				const Allocator& = Allocator());
			template <class InputIterator>
			path_builder(InputIterator first, InputIterator last,
				const Allocator& = Allocator());
			path_builder(const path_builder& x);
			path_builder(path_builder&&) noexcept;
			path_builder(const path_builder&, const Allocator&);
			path_builder(path_builder&&, const Allocator&);
			path_builder(initializer_list<value_type>, const Allocator& = Allocator());
			~path_builder();
			path_builder& operator=(const path_builder& x);
			path_builder& operator=(path_builder&& x)
				noexcept(
					allocator_traits<Allocator>::propagate_on_container_move_assignment::value
					||
					allocator_traits<Allocator>::is_always_equal::value);
			path_builder& operator=(initializer_list<value_type>);
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last);
			void assign(size_type n, const value_type& u);
			void assign(initializer_list<value_type>);
			allocator_type get_allocator() const noexcept;
			// 10.5.6, iterators:
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
			// 10.5.4, capacity
			bool empty() const noexcept;
			size_type size() const noexcept;
			size_type max_size() const noexcept;
			size_type capacity() const noexcept;
			void resize(size_type sz);
			void resize(size_type sz, const value_type& c);
			void reserve(size_type n);
			void shrink_to_fit();
			// element access:
			reference operator[](size_type n);
			const_reference operator[](size_type n) const;
			const_reference at(size_type n) const;
			reference at(size_type n);
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;
			// 10.5.5, modifiers:
			void new_figure(point_2d pt) noexcept;
			void rel_new_figure(point_2d pt) noexcept;
			void close_figure() noexcept;
			void matrix(const matrix_2d& m) noexcept;
			void rel_matrix(const matrix_2d& m) noexcept;
			void revert_matrix() noexcept;
			void line(point_2d pt) noexcept;
			void rel_line(point_2d dpt) noexcept;
			void quadratic_curve(point_2d pt0, point_2d pt2)
				noexcept;
			void rel_quadratic_curve(point_2d pt0, point_2d pt2)
				noexcept;
			void cubic_curve(point_2d pt0, point_2d pt1,
				point_2d pt2) noexcept;
			void rel_cubic_curve(point_2d dpt0, point_2d dpt1,
				point_2d dpt2) noexcept;
			void arc(point_2d rad, float rot, float sang = pi<float>)
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
			iterator insert(const_iterator position, InputIterator first, InputIterator last);
			iterator insert(const_iterator position,
				initializer_list<value_type> il);
			iterator erase(const_iterator position);
			iterator erase(const_iterator first, const_iterator last);
			void swap(path_builder&)
				noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value
					|| allocator_traits<Allocator>::is_always_equal::value);
			void clear() noexcept;
		};

		template <class Allocator>
		bool operator==(const path_builder<Allocator>& lhs, const path_builder<Allocator>& rhs) noexcept;
		template <class Allocator>
		bool operator!=(const path_builder<Allocator>& lhs, const path_builder<Allocator>& rhs) noexcept;

		// 8.17.8, specialized algorithms:
		/*		template <class Allocator>
		void swap(path_builder<Allocator>& lhs, path_builder<Allocator>& rhs)
		noexcept(noexcept(lhs.swap(rhs))) {
		lhs.swap(rhs);
		}*/ // compiler error prevents forward declaration

		template <class T>
		class interpreted_path {
			typename T::renderer_interpreted_path _Path_impl;

		public:
			const auto& native_handle() const { return _Path_impl; }

			// Note: Can default construct. It will just be empty. To be useful it would need to be assigned to.
			constexpr interpreted_path() noexcept;

			template <class Allocator>
			explicit interpreted_path(const path_builder<Allocator>& p);

			template <class ForwardIterator>
			interpreted_path(ForwardIterator first, ForwardIterator last);
		};
	}
}