#pragma once
#include <utility>
#include "xgraphicsmath.h"
namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
                
				template <class GraphicsSurfaces>
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
					public:
						using data_type = typename GraphicsSurfaces::paths::abs_new_figure_data_type;
					private:
						data_type _Data;
					public:
						const data_type& data() const noexcept;
						data_type& data() noexcept;

						abs_new_figure();
						explicit abs_new_figure(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt);
						abs_new_figure(const abs_new_figure& other);
						abs_new_figure& operator=(const abs_new_figure& other);
						abs_new_figure(abs_new_figure&& other) noexcept;
						abs_new_figure& operator=(abs_new_figure&& other) noexcept;
						~abs_new_figure() noexcept;
						void at(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> at() const noexcept;
                        bool operator==(const abs_new_figure& rhs) const noexcept;
                        bool operator!=(const abs_new_figure& rhs) const noexcept;
					};

					class rel_new_figure {
					public:
						using data_type = typename GraphicsSurfaces::paths::rel_new_figure_data_type;
					private:
						data_type _Data;
					public:
						const data_type& data() const noexcept;
						data_type& data() noexcept;

						rel_new_figure() noexcept;
						explicit rel_new_figure(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept;
						rel_new_figure(const rel_new_figure& other);
						rel_new_figure& operator=(const rel_new_figure& other);
						rel_new_figure(rel_new_figure&& other) noexcept;
						rel_new_figure& operator=(rel_new_figure&& other) noexcept;
						~rel_new_figure() noexcept;
						void at(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> at() const noexcept;
                        bool operator==(const rel_new_figure& rhs) const noexcept;
                        bool operator!=(const rel_new_figure& rhs) const noexcept;                        
					};

					class close_figure {
					public:
						using data_type = typename GraphicsSurfaces::paths::close_figure_data_type;
					private:
						data_type _Data;
					public:
						const data_type& data() const noexcept;
						data_type& data() noexcept;

						close_figure() noexcept;
						close_figure(const close_figure& other);
						close_figure& operator=(const close_figure& other);
						close_figure(close_figure&& other) noexcept;
						close_figure& operator=(close_figure&& other) noexcept;
						~close_figure() noexcept;
                        bool operator==(const close_figure& rhs) const noexcept;
                        bool operator!=(const close_figure& rhs) const noexcept;
					};

					class abs_matrix {
					public:
						using data_type = typename GraphicsSurfaces::paths::abs_matrix_data_type;
					private:
						data_type _Data;
					public:
						const data_type& data() const noexcept;
						data_type& data() noexcept;

						abs_matrix() noexcept;
						explicit abs_matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept;
						abs_matrix(const abs_matrix& other);
						abs_matrix& operator=(const abs_matrix& other);
						abs_matrix(abs_matrix&& other) noexcept;
						abs_matrix& operator=(abs_matrix&& other) noexcept;
						~abs_matrix() noexcept;
						void matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept;
						basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type> matrix() const noexcept;
                        bool operator==(const abs_matrix& rhs) const noexcept;
                        bool operator!=(const abs_matrix& rhs) const noexcept;                        
					};

					class rel_matrix {
					public:
						using data_type = typename GraphicsSurfaces::paths::rel_matrix_data_type;
					private:
						data_type _Data;
					public:
						const data_type& data() const noexcept;
						data_type& data() noexcept;

						rel_matrix() noexcept;
						explicit rel_matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept;
						rel_matrix(const rel_matrix& other);
						rel_matrix& operator=(const rel_matrix& other);
						rel_matrix(rel_matrix&& other) noexcept;
						rel_matrix& operator=(rel_matrix&& other) noexcept;
						~rel_matrix() noexcept;
						void matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept;
						basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type> matrix() const noexcept;
                        bool operator==(const rel_matrix& rhs) const noexcept;
                        bool operator!=(const rel_matrix& rhs) const noexcept;
					};

					class revert_matrix {
					public:
						using data_type = typename GraphicsSurfaces::paths::revert_matrix_data_type;
					private:
						data_type _Data;
					public:
						const data_type& data() const noexcept;
						data_type& data() noexcept;

						revert_matrix() noexcept;
						revert_matrix(const revert_matrix& other);
						revert_matrix& operator=(const revert_matrix& other);
						revert_matrix(revert_matrix&& other) noexcept;
						revert_matrix& operator=(revert_matrix&& other) noexcept;
						~revert_matrix() noexcept;
                        bool operator==(const revert_matrix& rhs) const noexcept;
                        bool operator!=(const revert_matrix& rhs) const noexcept;                        
					};

					class abs_line {
					public:
						using data_type = typename GraphicsSurfaces::paths::abs_line_data_type;
					private:
						data_type _Data;
					public:
						const data_type& data() const noexcept;
						data_type& data() noexcept;

						abs_line() noexcept;
						explicit abs_line(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept;
						abs_line(const abs_line& other);
						abs_line& operator=(const abs_line& other);
						abs_line(abs_line&& other) noexcept;
						abs_line& operator=(abs_line&& other) noexcept;
						~abs_line() noexcept;
						void to(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> to() const noexcept;
                        bool operator==(const abs_line& rhs) const noexcept;
                        bool operator!=(const abs_line& rhs) const noexcept;
					};

					class rel_line {
					public:
						using data_type = typename GraphicsSurfaces::paths::rel_line_data_type;
					private:
						data_type _Data;
					public:
						const data_type& data() const noexcept;
						data_type& data() noexcept;

						rel_line() noexcept;
						explicit rel_line(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept;
						rel_line(const rel_line& other);
						rel_line& operator=(const rel_line& other);
						rel_line(rel_line&& other) noexcept;
						rel_line& operator=(rel_line&& other) noexcept;
						~rel_line() noexcept;
						void to(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> to() const noexcept;
                        bool operator==(const rel_line& rhs) const noexcept;
                        bool operator!=(const rel_line& rhs) const noexcept;                        
					};

					class abs_quadratic_curve {
					public:
						using data_type = typename GraphicsSurfaces::paths::abs_quadratic_curve_data_type;
					private:
						data_type _Data;
					public:
						const data_type& data() const noexcept;
						data_type& data() noexcept;

						abs_quadratic_curve() noexcept;
						abs_quadratic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept;
						abs_quadratic_curve(const abs_quadratic_curve& other);
						abs_quadratic_curve& operator=(const abs_quadratic_curve& other);
						abs_quadratic_curve(abs_quadratic_curve&& other) noexcept;
						abs_quadratic_curve& operator=(abs_quadratic_curve&& other) noexcept;
						~abs_quadratic_curve() noexcept;
						void control_pt(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt) noexcept;
						void end_pt(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> control_pt() const noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> end_pt() const noexcept;
                        bool operator==(const abs_quadratic_curve& rhs) const noexcept;
                        bool operator!=(const abs_quadratic_curve& rhs) const noexcept;                                                
					};

					class rel_quadratic_curve {
					public:
						using data_type = typename GraphicsSurfaces::paths::rel_quadratic_curve_data_type;
					private:
						data_type _Data;
					public:
						const data_type& data() const noexcept;
						data_type& data() noexcept;

						rel_quadratic_curve() noexcept;
						rel_quadratic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept;
						rel_quadratic_curve(const rel_quadratic_curve& other);
						rel_quadratic_curve& operator=(const rel_quadratic_curve& other);
						rel_quadratic_curve(rel_quadratic_curve&& other) noexcept;
						rel_quadratic_curve& operator=(rel_quadratic_curve&& other) noexcept;
						~rel_quadratic_curve() noexcept;
						void control_pt(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt) noexcept;
						void end_pt(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> control_pt() const noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> end_pt() const noexcept;
                        bool operator==(const rel_quadratic_curve& rhs) const noexcept;
                        bool operator!=(const rel_quadratic_curve& rhs) const noexcept;
					};

					class abs_cubic_curve {
					public:
						using data_type = typename GraphicsSurfaces::paths::abs_cubic_curve_data_type;
					private:
						data_type _Data;
					public:
						const data_type& data() const noexcept;
						data_type& data() noexcept;

						abs_cubic_curve() noexcept;
						abs_cubic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt1, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt2, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept;
						abs_cubic_curve(const abs_cubic_curve& other);
						abs_cubic_curve& operator=(const abs_cubic_curve& other);
						abs_cubic_curve(abs_cubic_curve&& other) noexcept;
						abs_cubic_curve& operator=(abs_cubic_curve&& other) noexcept;
						~abs_cubic_curve() noexcept;
						void control_pt1(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt) noexcept;
						void control_pt2(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt) noexcept;
						void end_pt(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> control_pt1() const noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> control_pt2() const noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> end_pt() const noexcept;
                        bool operator==(const abs_cubic_curve& rhs) const noexcept;
                        bool operator!=(const abs_cubic_curve& rhs) const noexcept;
					};

					class rel_cubic_curve {
					public:
						using data_type = typename GraphicsSurfaces::paths::rel_cubic_curve_data_type;
					private:
						data_type _Data;
					public:
						const data_type& data() const noexcept;
						data_type& data() noexcept;

						rel_cubic_curve() noexcept;
						rel_cubic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt1, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt2, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept;
						rel_cubic_curve(const rel_cubic_curve& other);
						rel_cubic_curve& operator=(const rel_cubic_curve& other);
						rel_cubic_curve(rel_cubic_curve&& other) noexcept;
						rel_cubic_curve& operator=(rel_cubic_curve&& other) noexcept;
						~rel_cubic_curve() noexcept;
						void control_pt1(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt) noexcept;
						void control_pt2(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt) noexcept;
						void end_pt(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> control_pt1() const noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> control_pt2() const noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> end_pt() const noexcept;
                        bool operator==(const rel_cubic_curve& rhs) const noexcept;
                        bool operator!=(const rel_cubic_curve& rhs) const noexcept;                        
					};

					class arc {
					public:
						using data_type = typename GraphicsSurfaces::paths::arc_data_type;
					private:
						data_type _Data;
					public:
						const data_type& data() const noexcept;
						data_type& data() noexcept;

						arc() noexcept;
						arc(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& rad, float rot, float sang) noexcept;
						arc(const arc& other);
						arc& operator=(const arc& other);
						arc(arc&& other) noexcept;
						arc& operator=(arc&& other) noexcept;
						~arc() noexcept;
						void radius(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& rad) noexcept;
						void rotation(float rot) noexcept;
						void start_angle(float radians) noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> radius() const noexcept;
						float rotation() const noexcept;
						float start_angle() const noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> center(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt, const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m = basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>{}) const noexcept;
						basic_point_2d<typename GraphicsSurfaces::graphics_math_type> end_pt(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt, const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m = basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>{}) const noexcept;
                        bool operator==(const arc& rhs) const noexcept;
                        bool operator!=(const arc& rhs) const noexcept;
					};

					using figure_item = variant<abs_cubic_curve, abs_line, abs_matrix,
						abs_new_figure, abs_quadratic_curve, arc, close_figure,
						rel_cubic_curve, rel_line, rel_matrix, rel_new_figure, rel_quadratic_curve,
						revert_matrix>;
				};

				template <class GraphicsSurfaces, class Allocator = ::std::allocator<typename basic_figure_items<GraphicsSurfaces>::figure_item>>
				class basic_path_builder {
				public:
					using data_type = ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item, Allocator>;
					//using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
				private:
					data_type _Data;
				public:
					const data_type& data() const noexcept;
					data_type& data() noexcept;
					using value_type = typename basic_figure_items<GraphicsSurfaces>::figure_item;
					using allocator_type = Allocator;
					using reference = value_type&;
					using const_reference = const value_type&;
					using size_type = typename ::std::vector<value_type>::size_type;
					using difference_type = typename ::std::vector<value_type>::difference_type;
					using iterator = typename ::std::vector<value_type>::iterator;
					using const_iterator = typename ::std::vector<value_type>::const_iterator;
					using reverse_iterator = std::reverse_iterator<iterator>;
					using const_reverse_iterator = std::reverse_iterator<const_iterator>;

					void new_figure(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept;
					void rel_new_figure(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept;
					void close_figure() noexcept;
					void matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept;
					void rel_matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept;
					void revert_matrix() noexcept;
					void line(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept;
					void rel_line(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& dpt) noexcept;
					void quadratic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt0, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt2)
						noexcept;
					void rel_quadratic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt0, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt2)
						noexcept;
					void cubic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt0, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt1,
						const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt2) noexcept;
					void rel_cubic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& dpt0, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& dpt1,
						const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& dpt2) noexcept;
					void arc(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& rad, float rot, float sang = pi<float>)
						noexcept;

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
				};

				template <class GraphicsSurfaces, class Allocator>
				bool operator==(const basic_path_builder<GraphicsSurfaces, Allocator>& lhs, const basic_path_builder<GraphicsSurfaces, Allocator>& rhs) noexcept;
				template <class GraphicsSurfaces, class Allocator>
				bool operator!=(const basic_path_builder<GraphicsSurfaces, Allocator>& lhs, const basic_path_builder<GraphicsSurfaces, Allocator>& rhs) noexcept;
				template <class GraphicsSurfaces, class Allocator>
				void swap(basic_path_builder<GraphicsSurfaces, Allocator>& lhs, basic_path_builder<GraphicsSurfaces, Allocator>& rhs) noexcept(noexcept(lhs.swap(rhs)));
				// 8.17.8, specialized algorithms:
				/*		template <class Allocator>
				void swap(path_builder<Allocator>& lhs, path_builder<Allocator>& rhs)
				noexcept(noexcept(lhs.swap(rhs))) {
				lhs.swap(rhs);
				}*/ // compiler error prevents forward declaration

				template <class GraphicsSurfaces>
				class basic_interpreted_path {
				public:
					using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;

					using data_type = typename GraphicsSurfaces::paths::interpreted_path_data_type;

				private:
					data_type _Data;

				public:
					const data_type& data() const noexcept;
					data_type& data() noexcept;
					// Note: Can default construct. It will just be empty. To be useful it would need to be assigned to.
					basic_interpreted_path() noexcept;

					basic_interpreted_path(const basic_bounding_box<graphics_math_type>& bb);

					template <class Allocator>
					explicit basic_interpreted_path(const basic_path_builder<GraphicsSurfaces, Allocator>& pb);

					template <class ForwardIterator>
					basic_interpreted_path(ForwardIterator first, ForwardIterator last);

					explicit basic_interpreted_path(initializer_list<typename basic_figure_items<GraphicsSurfaces>::figure_item> il);

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
