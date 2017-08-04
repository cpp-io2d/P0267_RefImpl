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

				constexpr abs_new_figure(const point_2d& pt) noexcept;

				constexpr void at(const point_2d& pt) noexcept;

				constexpr point_2d at() const noexcept;
			};

			constexpr bool operator==(const abs_new_figure&, const abs_new_figure&)
				noexcept;
			constexpr bool operator!=(const abs_new_figure&, const abs_new_figure&)
				noexcept;

			class rel_new_figure {
				point_2d _Data = {};
				friend constexpr bool operator==(const rel_new_figure&, const rel_new_figure&) noexcept;
			public:
				constexpr rel_new_figure() noexcept;

				constexpr rel_new_figure(const point_2d& pt) noexcept;

				constexpr void at(const point_2d& pt) noexcept;

				constexpr point_2d at() const noexcept;
			};

			constexpr bool operator==(const rel_new_figure&, const rel_new_figure&)
				noexcept;
			constexpr bool operator!=(const rel_new_figure&, const rel_new_figure&)
				noexcept;

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
				constexpr explicit abs_matrix(const matrix_2d& m) noexcept;
				constexpr abs_matrix() noexcept;

				constexpr void matrix(const matrix_2d& value) noexcept;
				constexpr matrix_2d matrix() const noexcept;
			};

			constexpr bool operator==(const abs_matrix&, const abs_matrix&) noexcept;
			constexpr bool operator!=(const abs_matrix&, const abs_matrix&) noexcept;

			class rel_matrix {
				matrix_2d _Matrix;
				friend constexpr bool operator==(const rel_matrix&, const rel_matrix&) noexcept;
			public:
				constexpr explicit rel_matrix(const matrix_2d& m) noexcept;
				constexpr rel_matrix() noexcept;

				constexpr void matrix(const matrix_2d& value) noexcept;
				constexpr matrix_2d matrix() const noexcept;
			};

			constexpr bool operator==(const rel_matrix&, const rel_matrix&) noexcept;
			constexpr bool operator!=(const rel_matrix&, const rel_matrix&) noexcept;

			class revert_matrix {
				friend constexpr bool operator==(const revert_matrix&, const revert_matrix&) noexcept;
			public:
				constexpr revert_matrix() noexcept;
			};

			constexpr bool operator==(const revert_matrix&, const revert_matrix&)
				noexcept;
			constexpr bool operator!=(const revert_matrix&, const revert_matrix&)
				noexcept;

			class abs_line {
				point_2d _Data = {};
				friend constexpr bool operator==(const abs_line&, const abs_line&) noexcept;
			public:
				constexpr explicit abs_line(const point_2d& to) noexcept;
				constexpr abs_line() noexcept;

				constexpr void to(const point_2d& value) noexcept;

				constexpr point_2d to() const noexcept;
			};

			constexpr bool operator==(const abs_line&, const abs_line&) noexcept;
			constexpr bool operator!=(const abs_line&, const abs_line&) noexcept;

			class rel_line {
				point_2d _Data = {};
				friend constexpr bool operator==(const rel_line&, const rel_line&) noexcept;
			public:
				constexpr explicit rel_line(const point_2d& to) noexcept;
				constexpr rel_line() noexcept;

				constexpr void to(const point_2d& value) noexcept;

				constexpr point_2d to() const noexcept;
			};

			constexpr bool operator==(const rel_line&, const rel_line&) noexcept;
			constexpr bool operator!=(const rel_line&, const rel_line&) noexcept;

			class abs_quadratic_curve {
				point_2d _Control_pt = {};
				point_2d _End_pt = {};
				friend constexpr bool operator==(const abs_quadratic_curve&, const abs_quadratic_curve&) noexcept;
			public:
				constexpr abs_quadratic_curve(const point_2d& cp, const point_2d& ep) noexcept;
				constexpr abs_quadratic_curve() noexcept;

				constexpr void control_point(const point_2d& value) noexcept;
				constexpr void end_point(const point_2d& value) noexcept;

				constexpr point_2d control_point() const noexcept;
				constexpr point_2d end_point() const noexcept;
			};

			constexpr bool operator==(const abs_quadratic_curve&,
				const abs_quadratic_curve&) noexcept;
			constexpr bool operator!=(const abs_quadratic_curve&,
				const abs_quadratic_curve&) noexcept;

			class rel_quadratic_curve {
				point_2d _Control_pt = {};
				point_2d _End_pt = {};
				friend constexpr bool operator==(const rel_quadratic_curve&, const rel_quadratic_curve&) noexcept;
			public:
				constexpr rel_quadratic_curve(const point_2d& cp, const point_2d& ep) noexcept;
				constexpr rel_quadratic_curve() noexcept;

				constexpr void control_point(const point_2d& value) noexcept;
				constexpr void end_point(const point_2d& value) noexcept;

				constexpr point_2d control_point() const noexcept;
				constexpr point_2d end_point() const noexcept;
			};

			constexpr bool operator==(const rel_quadratic_curve&,
				const rel_quadratic_curve&) noexcept;
			constexpr bool operator!=(const rel_quadratic_curve&,
				const rel_quadratic_curve&) noexcept;

			class abs_cubic_curve {
				point_2d _Control_pt1 = {};
				point_2d _Control_pt2 = {};
				point_2d _End_pt = {};
				friend constexpr bool operator==(const abs_cubic_curve&, const abs_cubic_curve&) noexcept;
			public:
				constexpr abs_cubic_curve(const point_2d& controlPoint1, const point_2d& controlPoint2, const point_2d& endPoint) noexcept;
				constexpr abs_cubic_curve() noexcept;

				constexpr void control_point_1(const point_2d& value) noexcept;
				constexpr void control_point_2(const point_2d& value) noexcept;
				constexpr void end_point(const point_2d& value) noexcept;

				constexpr point_2d control_point_1() const noexcept;
				constexpr point_2d control_point_2() const noexcept;
				constexpr point_2d end_point() const noexcept;
			};

			constexpr bool operator==(const abs_cubic_curve&, const abs_cubic_curve&)
				noexcept;
			constexpr bool operator!=(const abs_cubic_curve&, const abs_cubic_curve&)
				noexcept;

			class rel_cubic_curve {
				point_2d _Control_pt1 = {};
				point_2d _Control_pt2 = {};
				point_2d _End_pt = {};
				friend constexpr bool operator==(const rel_cubic_curve&, const rel_cubic_curve&) noexcept;
			public:
				constexpr rel_cubic_curve(const point_2d& controlPoint1, const point_2d& controlPoint2, const point_2d& endPoint) noexcept;
				constexpr rel_cubic_curve() noexcept;

				constexpr void control_point_1(const point_2d& value) noexcept;
				constexpr void control_point_2(const point_2d& value) noexcept;
				constexpr void end_point(const point_2d& value) noexcept;

				constexpr point_2d control_point_1() const noexcept;
				constexpr point_2d control_point_2() const noexcept;
				constexpr point_2d end_point() const noexcept;
			};

			constexpr bool operator==(const rel_cubic_curve&, const rel_cubic_curve&)
				noexcept;
			constexpr bool operator!=(const rel_cubic_curve&, const rel_cubic_curve&)
				noexcept;

			class arc {
				point_2d _Radius;
				float _Rotation;
				float _Start_angle;

				friend constexpr bool operator==(const arc&, const arc&) noexcept;
			public:
				constexpr arc() noexcept;
				constexpr arc(const point_2d& rad, float rot, float sang = pi<float>) noexcept;

				constexpr void radius(const point_2d& rad) noexcept;
				constexpr void rotation(float rot) noexcept;
				constexpr void start_angle(float sang) noexcept;

				constexpr point_2d radius() const noexcept;
				constexpr float rotation() const noexcept;
				constexpr float start_angle() const noexcept;

				point_2d center(point_2d cpt, const matrix_2d& m) const noexcept;

				point_2d end_pt(point_2d cpt, const matrix_2d& m) const noexcept;
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
			~path_builder();
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

			bool operator==(const path_builder& rhs) const noexcept;
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