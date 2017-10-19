#pragma once
#include <utility>
#include "xlinear_algebra.h"
namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				enum class _Path_data_abs_new_figure {};
				constexpr static _Path_data_abs_new_figure _Path_data_abs_new_figure_val = {};
				enum class _Path_data_rel_new_figure {};
				constexpr static _Path_data_rel_new_figure _Path_data_rel_new_figure_val = {};
				enum class _Path_data_close_path {};
				constexpr static _Path_data_close_path _Path_data_close_path_val = {};
				enum class _Path_data_abs_matrix {};
				constexpr static _Path_data_abs_matrix _Path_data_abs_matrix_val = {};
				enum class _Path_data_rel_matrix {};
				constexpr static _Path_data_rel_matrix _Path_data_rel_matrix_val = {};
				enum class _Path_data_revert_matrix {};
				constexpr static _Path_data_revert_matrix _Path_data_revert_matrix_val = {};
				enum class _Path_data_abs_cubic_curve {};
				constexpr static _Path_data_abs_cubic_curve _Path_data_abs_cubic_curve_val = {};
				enum class _Path_data_abs_line {};
				constexpr static _Path_data_abs_line _Path_data_abs_line_val = {};
				enum class _Path_data_abs_quadratic_curve {};
				constexpr static _Path_data_abs_quadratic_curve _Path_data_abs_quadratic_curve_val = {};
				enum class _Path_data_arc {};
				constexpr static _Path_data_arc _Path_data_arc_val = {};
				enum class _Path_data_rel_cubic_curve {};
				constexpr static _Path_data_rel_cubic_curve _Path_data_rel_cubic_curve_val = {};
				enum class _Path_data_rel_line {};
				constexpr static _Path_data_rel_line _Path_data_rel_line_val = {};
				enum class _Path_data_rel_quadratic_curve {};
				constexpr static _Path_data_rel_quadratic_curve _Path_data_rel_quadratic_curve_val = {};

				template <class GraphicsMath>
				struct basic_figure_items {
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
						basic_point_2d<GraphicsMath> _Data = {};
						friend bool operator==(const abs_new_figure&, const abs_new_figure&) noexcept;
					public:
						abs_new_figure() noexcept;
						explicit abs_new_figure(const basic_point_2d<GraphicsMath>& pt) noexcept;
						void at(const basic_point_2d<GraphicsMath>& pt) noexcept;
						basic_point_2d<GraphicsMath> at() const noexcept;
					};

					class rel_new_figure {
						basic_point_2d<GraphicsMath> _Data = {};
						friend bool operator==(const rel_new_figure&, const rel_new_figure&) noexcept;
					public:
						rel_new_figure() noexcept;
						explicit rel_new_figure(const basic_point_2d<GraphicsMath>& pt) noexcept;
						void at(const basic_point_2d<GraphicsMath>& pt) noexcept;
						basic_point_2d<GraphicsMath> at() const noexcept;
					};

					class close_figure {
						friend bool operator==(const close_figure&, const close_figure&) noexcept;
					public:
						close_figure() noexcept;
					};

					class abs_matrix {
						basic_matrix_2d<GraphicsMath> _Matrix;
						friend bool operator==(const abs_matrix&, const abs_matrix&) noexcept;
					public:
						abs_matrix() noexcept;
						explicit abs_matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept;
						void matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept;
						basic_matrix_2d<GraphicsMath> matrix() const noexcept;
					};

					class rel_matrix {
						basic_matrix_2d<GraphicsMath> _Matrix;
						friend bool operator==(const rel_matrix&, const rel_matrix&) noexcept;
					public:
						rel_matrix() noexcept;
						explicit rel_matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept;
						void matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept;
						basic_matrix_2d<GraphicsMath> matrix() const noexcept;
					};

					class revert_matrix {
						friend bool operator==(const revert_matrix&, const revert_matrix&) noexcept;
					public:
						revert_matrix() noexcept;
					};

					class abs_line {
						basic_point_2d<GraphicsMath> _Data = {};
						friend bool operator==(const abs_line&, const abs_line&) noexcept;
					public:
						abs_line() noexcept;
						explicit abs_line(const basic_point_2d<GraphicsMath>& pt) noexcept;
						void to(const basic_point_2d<GraphicsMath>& pt) noexcept;
						basic_point_2d<GraphicsMath> to() const noexcept;
					};

					class rel_line {
						basic_point_2d<GraphicsMath> _Data = {};
						friend bool operator==(const rel_line&, const rel_line&) noexcept;
					public:
						rel_line() noexcept;
						explicit rel_line(const basic_point_2d<GraphicsMath>& pt) noexcept;
						void to(const basic_point_2d<GraphicsMath>& pt) noexcept;
						basic_point_2d<GraphicsMath> to() const noexcept;
					};

					class abs_quadratic_curve {
						basic_point_2d<GraphicsMath> _Control_pt = {};
						basic_point_2d<GraphicsMath> _End_pt = {};
						friend bool operator==(const abs_quadratic_curve&, const abs_quadratic_curve&) noexcept;
					public:
						abs_quadratic_curve() noexcept;
						abs_quadratic_curve(const basic_point_2d<GraphicsMath>& cpt, const basic_point_2d<GraphicsMath>& ept) noexcept;
						void control_pt(const basic_point_2d<GraphicsMath>& cpt) noexcept;
						void end_pt(const basic_point_2d<GraphicsMath>& ept) noexcept;
						basic_point_2d<GraphicsMath> control_pt() const noexcept;
						basic_point_2d<GraphicsMath> end_pt() const noexcept;
					};

					class rel_quadratic_curve {
						basic_point_2d<GraphicsMath> _Control_pt = {};
						basic_point_2d<GraphicsMath> _End_pt = {};
						friend bool operator==(const rel_quadratic_curve&, const rel_quadratic_curve&) noexcept;
					public:
						rel_quadratic_curve() noexcept;
						rel_quadratic_curve(const basic_point_2d<GraphicsMath>& cpt, const basic_point_2d<GraphicsMath>& ept) noexcept;
						void control_pt(const basic_point_2d<GraphicsMath>& cpt) noexcept;
						void end_pt(const basic_point_2d<GraphicsMath>& ept) noexcept;
						basic_point_2d<GraphicsMath> control_pt() const noexcept;
						basic_point_2d<GraphicsMath> end_pt() const noexcept;
					};

					class abs_cubic_curve {
						basic_point_2d<GraphicsMath> _Control_pt1 = {};
						basic_point_2d<GraphicsMath> _Control_pt2 = {};
						basic_point_2d<GraphicsMath> _End_pt = {};
						friend bool operator==(const abs_cubic_curve&, const abs_cubic_curve&) noexcept;
					public:
						abs_cubic_curve() noexcept;
						abs_cubic_curve(const basic_point_2d<GraphicsMath>& cpt1, const basic_point_2d<GraphicsMath>& cpt2, const basic_point_2d<GraphicsMath>& ept) noexcept;
						void control_pt1(const basic_point_2d<GraphicsMath>& cpt) noexcept;
						void control_pt2(const basic_point_2d<GraphicsMath>& cpt) noexcept;
						void end_pt(const basic_point_2d<GraphicsMath>& ept) noexcept;
						basic_point_2d<GraphicsMath> control_pt1() const noexcept;
						basic_point_2d<GraphicsMath> control_pt2() const noexcept;
						basic_point_2d<GraphicsMath> end_pt() const noexcept;
					};

					class rel_cubic_curve {
						basic_point_2d<GraphicsMath> _Control_pt1 = {};
						basic_point_2d<GraphicsMath> _Control_pt2 = {};
						basic_point_2d<GraphicsMath> _End_pt = {};
						friend bool operator==(const rel_cubic_curve&, const rel_cubic_curve&) noexcept;
					public:
						rel_cubic_curve() noexcept;
						rel_cubic_curve(const basic_point_2d<GraphicsMath>& cpt1, const basic_point_2d<GraphicsMath>& cpt2, const basic_point_2d<GraphicsMath>& ept) noexcept;
						void control_pt1(const basic_point_2d<GraphicsMath>& cpt) noexcept;
						void control_pt2(const basic_point_2d<GraphicsMath>& cpt) noexcept;
						void end_pt(const basic_point_2d<GraphicsMath>& ept) noexcept;
						basic_point_2d<GraphicsMath> control_pt1() const noexcept;
						basic_point_2d<GraphicsMath> control_pt2() const noexcept;
						basic_point_2d<GraphicsMath> end_pt() const noexcept;
					};

					class arc {
						basic_point_2d<GraphicsMath> _Radius;
						float _Rotation;
						float _Start_angle;

						friend bool operator==(const arc&, const arc&) noexcept;
					public:
						arc() noexcept;
						arc(const basic_point_2d<GraphicsMath>& rad, float rot, float sang) noexcept;
						void radius(const basic_point_2d<GraphicsMath>& rad) noexcept;
						void rotation(float rot) noexcept;
						void start_angle(float radians) noexcept;
						basic_point_2d<GraphicsMath> radius() const noexcept;
						float rotation() const noexcept;
						float start_angle() const noexcept;
						basic_point_2d<GraphicsMath> center(const basic_point_2d<GraphicsMath>& cpt, const basic_matrix_2d<GraphicsMath>& m = basic_matrix_2d<GraphicsMath>{}) const noexcept;
						basic_point_2d<GraphicsMath> end_pt(const basic_point_2d<GraphicsMath>& cpt, const basic_matrix_2d<GraphicsMath>& m = basic_matrix_2d<GraphicsMath>{}) const noexcept;
					};

					using figure_item = variant<abs_cubic_curve, abs_line, abs_matrix,
						abs_new_figure, abs_quadratic_curve, arc, close_figure,
						rel_cubic_curve, rel_line, rel_matrix, rel_new_figure, rel_quadratic_curve,
						revert_matrix>;
				};

				template <class GraphicsMath>
				bool operator==(const typename basic_figure_items<GraphicsMath>::abs_new_figure& lhs, const typename basic_figure_items<GraphicsMath>::abs_new_figure& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const typename basic_figure_items<GraphicsMath>::abs_new_figure& lhs, const typename basic_figure_items<GraphicsMath>::abs_new_figure& rhs) noexcept;
				template <class GraphicsMath>
				bool operator==(const typename basic_figure_items<GraphicsMath>::rel_new_figure& lhs, const typename basic_figure_items<GraphicsMath>::rel_new_figure& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const typename basic_figure_items<GraphicsMath>::rel_new_figure& lhs, const typename basic_figure_items<GraphicsMath>::rel_new_figure& rhs) noexcept;

				template <class GraphicsMath>
				bool operator==(const typename basic_figure_items<GraphicsMath>::close_figure&, const typename basic_figure_items<GraphicsMath>::close_figure&) noexcept;
				template <class GraphicsMath>
				bool operator!=(const typename basic_figure_items<GraphicsMath>::close_figure&, const typename basic_figure_items<GraphicsMath>::close_figure&) noexcept;

				template <class GraphicsMath>
				bool operator==(const typename basic_figure_items<GraphicsMath>::abs_matrix& lhs, const typename basic_figure_items<GraphicsMath>::abs_matrix& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const typename basic_figure_items<GraphicsMath>::abs_matrix& lhs, const typename basic_figure_items<GraphicsMath>::abs_matrix& rhs) noexcept;

				template <class GraphicsMath>
				bool operator==(const typename basic_figure_items<GraphicsMath>::rel_matrix& lhs, const typename basic_figure_items<GraphicsMath>::rel_matrix& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const typename basic_figure_items<GraphicsMath>::rel_matrix& lhs, const typename basic_figure_items<GraphicsMath>::rel_matrix& rhs) noexcept;

				template <class GraphicsMath>
				bool operator==(const typename basic_figure_items<GraphicsMath>::revert_matrix& lhs, const typename basic_figure_items<GraphicsMath>::revert_matrix& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const typename basic_figure_items<GraphicsMath>::revert_matrix& lhs, const typename basic_figure_items<GraphicsMath>::revert_matrix& rhs) noexcept;

				template <class GraphicsMath>
				bool operator==(const typename basic_figure_items<GraphicsMath>::abs_line& lhs, const typename basic_figure_items<GraphicsMath>::abs_line& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const typename basic_figure_items<GraphicsMath>::abs_line& lhs, const typename basic_figure_items<GraphicsMath>::abs_line& rhs) noexcept;

				template <class GraphicsMath>
				bool operator==(const typename basic_figure_items<GraphicsMath>::rel_line& lhs, const typename basic_figure_items<GraphicsMath>::rel_line& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const typename basic_figure_items<GraphicsMath>::rel_line& lhs, const typename basic_figure_items<GraphicsMath>::rel_line& rhs) noexcept;

				template <class GraphicsMath>
				bool operator==(const typename basic_figure_items<GraphicsMath>::abs_quadratic_curve& lhs, const typename basic_figure_items<GraphicsMath>::abs_quadratic_curve& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const typename basic_figure_items<GraphicsMath>::abs_quadratic_curve& lhs, const typename basic_figure_items<GraphicsMath>::abs_quadratic_curve& rhs) noexcept;

				template <class GraphicsMath>
				bool operator==(const typename basic_figure_items<GraphicsMath>::rel_quadratic_curve& lhs, const typename basic_figure_items<GraphicsMath>::rel_quadratic_curve& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const typename basic_figure_items<GraphicsMath>::rel_quadratic_curve& lhs, const typename basic_figure_items<GraphicsMath>::rel_quadratic_curve& rhs) noexcept;

				template <class GraphicsMath>
				bool operator==(const typename basic_figure_items<GraphicsMath>::abs_cubic_curve& lhs, const typename basic_figure_items<GraphicsMath>::abs_cubic_curve& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const typename basic_figure_items<GraphicsMath>::abs_cubic_curve& lhs, const typename basic_figure_items<GraphicsMath>::abs_cubic_curve& rhs) noexcept;

				template <class GraphicsMath>
				bool operator==(const typename basic_figure_items<GraphicsMath>::rel_cubic_curve& lhs, const typename basic_figure_items<GraphicsMath>::rel_cubic_curve& rhs) noexcept;
				template <class GraphicsMath>
				bool operator!=(const typename basic_figure_items<GraphicsMath>::rel_cubic_curve& lhs, const typename basic_figure_items<GraphicsMath>::rel_cubic_curve& rhs) noexcept;

				template <class GraphicsMath>
				bool operator==(const typename basic_figure_items<GraphicsMath>::arc&, const typename basic_figure_items<GraphicsMath>::arc&) noexcept;
				template <class GraphicsMath>
				bool operator!=(const typename basic_figure_items<GraphicsMath>::arc&, const typename basic_figure_items<GraphicsMath>::arc&) noexcept;

				template <class GraphicsMath, class Allocator = ::std::allocator<typename basic_figure_items<GraphicsMath>::figure_item>>
				class basic_path_builder {
					::std::vector<typename basic_figure_items<GraphicsMath>::figure_item, Allocator> _Data;
				public:
					using value_type = typename basic_figure_items<GraphicsMath>::figure_item;
					using allocator_type = Allocator;
					using reference = value_type&;
					using const_reference = const value_type&;
					using size_type = typename ::std::vector<value_type>::size_type;
					using difference_type = typename ::std::vector<value_type>::difference_type;
					using iterator = typename ::std::vector<value_type>::iterator;
					using const_iterator = typename ::std::vector<value_type>::const_iterator;
					using reverse_iterator = std::reverse_iterator<iterator>;
					using const_reverse_iterator = std::reverse_iterator<const_iterator>;

					basic_path_builder() noexcept(noexcept(Allocator()));
					explicit basic_path_builder(const Allocator&) noexcept;
					explicit basic_path_builder(size_type n, const Allocator& = Allocator());
					basic_path_builder(size_type n, const value_type& value,
						const Allocator& = Allocator());
					template <class InputIterator>
					basic_path_builder(InputIterator first, InputIterator last,
						const Allocator& = Allocator());
					basic_path_builder(const basic_path_builder& x);
					basic_path_builder(basic_path_builder&&) noexcept;
					basic_path_builder(const basic_path_builder&, const Allocator&);
					basic_path_builder(basic_path_builder&&, const Allocator&);
					basic_path_builder(initializer_list<value_type>, const Allocator& = Allocator());
					~basic_path_builder();
					basic_path_builder& operator=(const basic_path_builder& x);
					basic_path_builder& operator=(basic_path_builder&& x)
						noexcept(
							allocator_traits<Allocator>::propagate_on_container_move_assignment::value
							||
							allocator_traits<Allocator>::is_always_equal::value);
					basic_path_builder& operator=(initializer_list<value_type>);
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
					void new_figure(const basic_point_2d<GraphicsMath>& pt) noexcept;
					void rel_new_figure(const basic_point_2d<GraphicsMath>& pt) noexcept;
					void close_figure() noexcept;
					void matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept;
					void rel_matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept;
					void revert_matrix() noexcept;
					void line(const basic_point_2d<GraphicsMath>& pt) noexcept;
					void rel_line(const basic_point_2d<GraphicsMath>& dpt) noexcept;
					void quadratic_curve(const basic_point_2d<GraphicsMath>& pt0, const basic_point_2d<GraphicsMath>& pt2)
						noexcept;
					void rel_quadratic_curve(const basic_point_2d<GraphicsMath>& pt0, const basic_point_2d<GraphicsMath>& pt2)
						noexcept;
					void cubic_curve(const basic_point_2d<GraphicsMath>& pt0, const basic_point_2d<GraphicsMath>& pt1,
						const basic_point_2d<GraphicsMath>& pt2) noexcept;
					void rel_cubic_curve(const basic_point_2d<GraphicsMath>& dpt0, const basic_point_2d<GraphicsMath>& dpt1,
						const basic_point_2d<GraphicsMath>& dpt2) noexcept;
					void arc(const basic_point_2d<GraphicsMath>& rad, float rot, float sang = pi<float>)
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
					void swap(basic_path_builder&)
						noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value
							|| allocator_traits<Allocator>::is_always_equal::value);
					void clear() noexcept;
				private:
					friend bool operator==(const basic_path_builder&, const basic_path_builder&) noexcept;
				};

				template <class GraphicsMath, class Allocator>
				bool operator==(const basic_path_builder<GraphicsMath, Allocator>& lhs, const basic_path_builder<GraphicsMath, Allocator>& rhs) noexcept;
				template <class GraphicsMath, class Allocator>
				bool operator!=(const basic_path_builder<GraphicsMath, Allocator>& lhs, const basic_path_builder<GraphicsMath, Allocator>& rhs) noexcept;
				template <class GraphicsMath, class Allocator>
				void swap(basic_path_builder<GraphicsMath, Allocator>& lhs, basic_path_builder<GraphicsMath, Allocator>& rhs) noexcept(noexcept(lhs.swap(rhs)));
				// 8.17.8, specialized algorithms:
				/*		template <class Allocator>
				void swap(path_builder<Allocator>& lhs, path_builder<Allocator>& rhs)
				noexcept(noexcept(lhs.swap(rhs))) {
				lhs.swap(rhs);
				}*/ // compiler error prevents forward declaration

				template <class GraphicsSurfaces>
				class basic_interpreted_path {
				public:
					using _Data_type = typename GraphicsSurfaces::interpreted_path_data_type;

				private:
					_Data_type _Data;

				public:
					const _Data_type& _Get_data() const noexcept;
					// Note: Can default construct. It will just be empty. To be useful it would need to be assigned to.
					basic_interpreted_path() noexcept;

					template <class GraphicsMath, class Allocator>
					explicit basic_interpreted_path(const basic_path_builder<GraphicsMath, Allocator>& pb);

					template <class ForwardIterator>
					basic_interpreted_path(ForwardIterator first, ForwardIterator last);

					basic_interpreted_path(const basic_interpreted_path&);
					basic_interpreted_path& operator=(const basic_interpreted_path&);
					basic_interpreted_path(basic_interpreted_path&&) noexcept;
					basic_interpreted_path& operator=(basic_interpreted_path&&) noexcept;

					~basic_interpreted_path() noexcept;
				};
			}
		}
	}
}