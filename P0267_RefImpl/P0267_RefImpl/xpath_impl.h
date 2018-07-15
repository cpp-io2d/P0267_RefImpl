#pragma once
#include "xpath.h"
#include <vector>
#include <chrono>

namespace std::experimental::io2d {
	inline namespace v1 {
		template<class GraphicsSurfaces>
		inline const typename basic_figure_items<GraphicsSurfaces>::abs_new_figure::data_type& basic_figure_items<GraphicsSurfaces>::abs_new_figure::data() const noexcept {
			return _Data;
		}

		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_new_figure::data_type& basic_figure_items<GraphicsSurfaces>::abs_new_figure::data() noexcept {
			return _Data;
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_new_figure::abs_new_figure()
			: _Data(GraphicsSurfaces::paths::create_abs_new_figure()) {
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_new_figure::abs_new_figure(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt)
			: _Data(GraphicsSurfaces::paths::create_abs_new_figure(pt)) {
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_new_figure::abs_new_figure(const abs_new_figure& other)
			: _Data(GraphicsSurfaces::paths::copy_abs_new_figure(other._Data)) {
		}

		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_new_figure& basic_figure_items<GraphicsSurfaces>::abs_new_figure::operator=(const abs_new_figure& other) {
			if (this != &other) {
				_Data = GraphicsSurfaces::paths::copy_abs_new_figure(other._Data);
			}
			return *this;
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_new_figure::abs_new_figure(abs_new_figure&& other) noexcept
			: _Data(GraphicsSurfaces::paths::move_abs_new_figure(move(other._Data))) {
		}

		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_new_figure& basic_figure_items<GraphicsSurfaces>::abs_new_figure::operator=(abs_new_figure&& other) noexcept {
			if (this != &other) {
				_Data = move(GraphicsSurfaces::paths::move_abs_new_figure(move(other._Data)));
			}
            return *this;
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_new_figure::~abs_new_figure() noexcept {
			GraphicsSurfaces::paths::destroy(_Data);
		}

		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::abs_new_figure::at(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept {
			GraphicsSurfaces::paths::at(_Data, pt);
		}

		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::abs_new_figure::at() const noexcept {
			return GraphicsSurfaces::paths::at(_Data);
		}

        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::abs_new_figure::operator==(const abs_new_figure& rhs) const noexcept {
            return at() == rhs.at();
        }

        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::abs_new_figure::operator!=(const abs_new_figure& rhs) const noexcept {
            return !(*this == rhs);
        }
                
		template<class GraphicsSurfaces>
		inline const typename basic_figure_items<GraphicsSurfaces>::rel_new_figure::data_type& basic_figure_items<GraphicsSurfaces>::rel_new_figure::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_new_figure::data_type& basic_figure_items<GraphicsSurfaces>::rel_new_figure::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_new_figure::rel_new_figure() noexcept
			: _Data(GraphicsSurfaces::paths::create_rel_new_figure()) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_new_figure::rel_new_figure(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept
			: _Data(GraphicsSurfaces::paths::create_rel_new_figure(pt)) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_new_figure::rel_new_figure(const rel_new_figure& other)
			: _Data(GraphicsSurfaces::paths::copy_rel_new_figure(other._Data)) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_new_figure& basic_figure_items<GraphicsSurfaces>::rel_new_figure::operator=(const rel_new_figure& other) {
			if (this != &other) {
				GraphicsSurfaces::paths::copy_rel_new_figure(other._Data);
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_new_figure::rel_new_figure(rel_new_figure&& other) noexcept
			: _Data(move(GraphicsSurfaces::paths::move_rel_new_figure(move(other._Data)))) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_new_figure& basic_figure_items<GraphicsSurfaces>::rel_new_figure::operator=(rel_new_figure&& other) noexcept {
			if (this != &other) {
				_Data = move(GraphicsSurfaces::paths::move_rel_new_figure(move(other._Data)));
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_new_figure::~rel_new_figure() noexcept {
			GraphicsSurfaces::paths::destroy(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::rel_new_figure::at(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept {
			GraphicsSurfaces::paths::at(_Data, pt);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::rel_new_figure::at() const noexcept {
			return GraphicsSurfaces::paths::at(_Data);
		}
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::rel_new_figure::operator==(const rel_new_figure& rhs) const noexcept {
            return at() == rhs.at();
        }
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::rel_new_figure::operator!=(const rel_new_figure& rhs) const noexcept {
            return !(*this == rhs);
        }        
        
		template<class GraphicsSurfaces>
		inline const typename basic_figure_items<GraphicsSurfaces>::close_figure::data_type& basic_figure_items<GraphicsSurfaces>::close_figure::data() const noexcept {
			return _Data;
		}

		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::close_figure::data_type& basic_figure_items<GraphicsSurfaces>::close_figure::data() noexcept {
			return _Data;
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::close_figure::close_figure() noexcept
			: _Data(GraphicsSurfaces::paths::create_close_figure()) {
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::close_figure::close_figure(const close_figure& other)
			: _Data(GraphicsSurfaces::paths::copy_close_figure(other._Data)) {
		}

		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::close_figure& basic_figure_items<GraphicsSurfaces>::close_figure::operator=(const close_figure& other) {
			if (this != &other) {
				_Data = GraphicsSurfaces::paths::copy_close_figure(other._Data);
			}
			return *this;
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::close_figure::close_figure(close_figure&& other) noexcept
			: _Data(move(GraphicsSurfaces::paths::move_close_figure(move(other._Data)))) {
		}

		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::close_figure& basic_figure_items<GraphicsSurfaces>::close_figure::operator=(close_figure&& other) noexcept {
			if (this != &other) {
				_Data = move(GraphicsSurfaces::paths::move_close_figure(move(other._Data)));
			}
			return *this;
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::close_figure::~close_figure() noexcept {
			GraphicsSurfaces::paths::destroy(_Data);
		}
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::close_figure::operator==(const close_figure& rhs) const noexcept {
            return true;
        }
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::close_figure::operator!=(const close_figure& rhs) const noexcept {
            return !(*this == rhs);
        }                
                
		template<class GraphicsSurfaces>
		inline const typename basic_figure_items<GraphicsSurfaces>::abs_matrix::data_type& basic_figure_items<GraphicsSurfaces>::abs_matrix::data() const noexcept {
			return _Data;
		}

		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_matrix::data_type& basic_figure_items<GraphicsSurfaces>::abs_matrix::data() noexcept {
			return _Data;
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_matrix::abs_matrix() noexcept
			: _Data(GraphicsSurfaces::paths::create_abs_matrix()) {
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_matrix::abs_matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept
			: _Data(GraphicsSurfaces::paths::create_abs_matrix(m)) {
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_matrix::abs_matrix(const abs_matrix& other)
			: _Data(GraphicsSurfaces::paths::copy_abs_matrix(other._Data)) {
		}

		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_matrix& basic_figure_items<GraphicsSurfaces>::abs_matrix::operator=(const abs_matrix& other) {
			if (this != &other) {
				_Data = GraphicsSurfaces::paths::copy_abs_matrix(other._Data);
			}
			return *this;
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_matrix::abs_matrix(abs_matrix&& other) noexcept
			: _Data(move(GraphicsSurfaces::paths::move_abs_matrix(move(other._Data)))) {
		}

		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_matrix& basic_figure_items<GraphicsSurfaces>::abs_matrix::operator=(abs_matrix&& other) noexcept {
			if (this != &other) {
				_Data = move(GraphicsSurfaces::paths::move_abs_matrix(move(other._Data)));
			}
			return *this;
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_matrix::~abs_matrix() noexcept {
			GraphicsSurfaces::paths::destroy(_Data);
		}

		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::abs_matrix::matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept {
			GraphicsSurfaces::paths::matrix(_Data, m);
		}

		template<class GraphicsSurfaces>
		inline basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::abs_matrix::matrix() const noexcept {
			return GraphicsSurfaces::paths::matrix(_Data);
		}

        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::abs_matrix::operator==(const abs_matrix& rhs) const noexcept {
            return matrix() == rhs.matrix();
        }
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::abs_matrix::operator!=(const abs_matrix& rhs) const noexcept {
            return !(*this == rhs);
        }             
                
		template<class GraphicsSurfaces>
		inline const typename basic_figure_items<GraphicsSurfaces>::rel_matrix::data_type& basic_figure_items<GraphicsSurfaces>::rel_matrix::data() const noexcept {
			return _Data;
		}

		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_matrix::data_type& basic_figure_items<GraphicsSurfaces>::rel_matrix::data() noexcept {
			return _Data;
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_matrix::rel_matrix() noexcept
			: _Data(GraphicsSurfaces::paths::create_rel_matrix()) {
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_matrix::rel_matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept
			: _Data(GraphicsSurfaces::paths::create_rel_matrix(m)) {
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_matrix::rel_matrix(const rel_matrix& other)
			: _Data(GraphicsSurfaces::paths::copy_rel_matrix(other._Data)) {
		}

		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_matrix& basic_figure_items<GraphicsSurfaces>::rel_matrix::operator=(const rel_matrix& other) {
			if (this != &other) {
				_Data = GraphicsSurfaces::paths::copy_rel_matrix(other._Data);
			}
			return *this;
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_matrix::rel_matrix(rel_matrix&& other) noexcept
			: _Data(move(GraphicsSurfaces::paths::move_rel_matrix(move(other._Data)))) {
		}

		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_matrix& basic_figure_items<GraphicsSurfaces>::rel_matrix::operator=(rel_matrix&& other) noexcept {
			if (this != &other) {
				_Data = move(GraphicsSurfaces::paths::move_rel_matrix(move(other._Data)));
			}
			return *this;
		}

		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_matrix::~rel_matrix() noexcept {
			GraphicsSurfaces::paths::destroy(_Data);
		}

		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::rel_matrix::matrix(const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) noexcept {
			GraphicsSurfaces::paths::matrix(_Data, m);
		}

		template<class GraphicsSurfaces>
		inline basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::rel_matrix::matrix() const noexcept {
			return GraphicsSurfaces::paths::matrix(_Data);
		}

        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::rel_matrix::operator==(const rel_matrix& rhs) const noexcept {
            return matrix() == rhs.matrix();
        }
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::rel_matrix::operator!=(const rel_matrix& rhs) const noexcept {
            return !(*this == rhs);
        }               

		template<class GraphicsSurfaces>
		inline const typename basic_figure_items<GraphicsSurfaces>::revert_matrix::data_type& basic_figure_items<GraphicsSurfaces>::revert_matrix::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::revert_matrix::data_type& basic_figure_items<GraphicsSurfaces>::revert_matrix::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::revert_matrix::revert_matrix() noexcept
			: _Data(GraphicsSurfaces::paths::create_revert_matrix()) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::revert_matrix::revert_matrix(const revert_matrix& other)
			: _Data(GraphicsSurfaces::paths::copy_revert_matrix(other._Data)) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::revert_matrix& basic_figure_items<GraphicsSurfaces>::revert_matrix::operator=(const revert_matrix& other) {
			if (this != &other) {
				_Data = GraphicsSurfaces::paths::copy_revert_matrix(other._Data);
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::revert_matrix::revert_matrix(revert_matrix&& other) noexcept
			: _Data(move(GraphicsSurfaces::paths::move_revert_matrix(move(other._Data)))) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::revert_matrix& basic_figure_items<GraphicsSurfaces>::revert_matrix::operator=(revert_matrix&& other) noexcept {
			if (this != &other) {
				_Data = move(GraphicsSurfaces::paths::move_revert_matrix(move(other._Data)));
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::revert_matrix::~revert_matrix() noexcept {
			GraphicsSurfaces::paths::destroy(_Data);
		}
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::revert_matrix::operator==(const revert_matrix& rhs) const noexcept {
            return true;
        }
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::revert_matrix::operator!=(const revert_matrix& rhs) const noexcept {
            return !(*this == rhs);
        }

		template<class GraphicsSurfaces>
		inline const typename basic_figure_items<GraphicsSurfaces>::abs_line::data_type& basic_figure_items<GraphicsSurfaces>::abs_line::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_line::data_type& basic_figure_items<GraphicsSurfaces>::abs_line::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_line::abs_line() noexcept
			: _Data(GraphicsSurfaces::paths::create_abs_line()) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_line::abs_line(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept
			: _Data(GraphicsSurfaces::paths::create_abs_line(pt)) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_line::abs_line(const abs_line& other)
			: _Data(GraphicsSurfaces::paths::copy_abs_line(other._Data)) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_line& basic_figure_items<GraphicsSurfaces>::abs_line::operator=(const abs_line& other) {
			if (this != &other) {
				_Data = GraphicsSurfaces::paths::copy_abs_line(other._Data);
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_line::abs_line(abs_line&& other) noexcept
			: _Data(move(GraphicsSurfaces::paths::move_abs_line(move(other._Data)))) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_line& basic_figure_items<GraphicsSurfaces>::abs_line::operator=(abs_line&& other) noexcept {
			if (this != &other) {
				_Data = move(GraphicsSurfaces::paths::move_abs_line(move(other._Data)));
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_line::~abs_line() noexcept {
			GraphicsSurfaces::paths::destroy(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::abs_line::to(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept {
			GraphicsSurfaces::paths::to(_Data, pt);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::abs_line::to() const noexcept {
			return GraphicsSurfaces::paths::to(_Data);
		}

        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::abs_line::operator==(const abs_line& rhs) const noexcept {
            return to() == rhs.to();
        }
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::abs_line::operator!=(const abs_line& rhs) const noexcept {
            return !(*this == rhs);
        }        

		template<class GraphicsSurfaces>
		inline const typename basic_figure_items<GraphicsSurfaces>::rel_line::data_type& std::experimental::io2d::v1::basic_figure_items<GraphicsSurfaces>::rel_line::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_line::data_type& basic_figure_items<GraphicsSurfaces>::rel_line::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_line::rel_line() noexcept
			: _Data(GraphicsSurfaces::paths::create_rel_line()) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_line::rel_line(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept
			: _Data(GraphicsSurfaces::paths::create_rel_line(pt)) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_line::rel_line(const rel_line& other)
			: _Data(GraphicsSurfaces::paths::copy_rel_line(other._Data)) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_line& basic_figure_items<GraphicsSurfaces>::rel_line::operator=(const rel_line& other) {
			if (this != &other) {
				_Data = GraphicsSurfaces::paths::copy_rel_line(other._Data);
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_line::rel_line(rel_line&& other) noexcept
			: _Data(move(GraphicsSurfaces::paths::move_rel_line(move(other._Data)))) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_line& basic_figure_items<GraphicsSurfaces>::rel_line::operator=(rel_line&& other) noexcept {
			if (this != &other) {
				_Data = move(GraphicsSurfaces::paths::move_rel_line(move(other._Data)));
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_line::~rel_line() noexcept {
			GraphicsSurfaces::paths::destroy(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::rel_line::to(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& pt) noexcept {
			GraphicsSurfaces::paths::to(_Data, pt);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::rel_line::to() const noexcept {
			return GraphicsSurfaces::paths::to(_Data);
		}

        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::rel_line::operator==(const rel_line& rhs) const noexcept {
            return to() == rhs.to();
        }
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::rel_line::operator!=(const rel_line& rhs) const noexcept {
            return !(*this == rhs);
        }
        
		template<class GraphicsSurfaces>
		inline const typename basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::data_type& basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::data_type& basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::abs_quadratic_curve() noexcept
			: _Data(GraphicsSurfaces::paths::create_abs_quadratic_curve()) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::abs_quadratic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept
			: _Data(GraphicsSurfaces::paths::create_abs_quadratic_curve(cpt, ept)) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::abs_quadratic_curve(const abs_quadratic_curve& other)
			: _Data(GraphicsSurfaces::paths::copy_abs_quadratic_curve(other._Data)) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve& basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::operator=(const abs_quadratic_curve& other) {
			if (this != &other) {
				_Data = GraphicsSurfaces::paths::copy_abs_quadratic_curve(other._Data);
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::abs_quadratic_curve(abs_quadratic_curve&& other) noexcept
			: _Data(move(GraphicsSurfaces::paths::move_abs_quadratic_curve(move(other._Data)))) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve& basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::operator=(abs_quadratic_curve&& other) noexcept {
			if (this != &other) {
				_Data = move(GraphicsSurfaces::paths::move_abs_quadratic_curve(move(other._Data)));
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::~abs_quadratic_curve() noexcept {
			GraphicsSurfaces::paths::destroy(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::control_pt(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt) noexcept {
			GraphicsSurfaces::paths::control_pt(_Data, cpt);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::end_pt(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept {
			GraphicsSurfaces::paths::end_pt(_Data, ept);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::control_pt() const noexcept {
			return GraphicsSurfaces::paths::control_pt(_Data);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::end_pt() const noexcept {
			return GraphicsSurfaces::paths::end_pt(_Data);
		}

        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::operator==(const abs_quadratic_curve& rhs) const noexcept {
            return control_pt() == rhs.control_pt() && end_pt() == rhs.end_pt();
        }
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::operator!=(const abs_quadratic_curve& rhs) const noexcept {
            return !(*this == rhs);
        }        
        
		template<class GraphicsSurfaces>
		inline const typename basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::data_type& basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::data_type& basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::rel_quadratic_curve() noexcept
			: _Data(GraphicsSurfaces::paths::create_rel_quadratic_curve()) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::rel_quadratic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept
			: _Data(GraphicsSurfaces::paths::create_rel_quadratic_curve(cpt, ept)) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::rel_quadratic_curve(const rel_quadratic_curve& other)
			: _Data(GraphicsSurfaces::paths::copy_rel_quadratic_curve(other._Data)) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve& basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::operator=(const rel_quadratic_curve& other) {
			if (this != &other) {
				_Data = GraphicsSurfaces::paths::copy_rel_quadratic_curve(other._Data);
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::rel_quadratic_curve(rel_quadratic_curve&& other) noexcept
			: _Data(move(GraphicsSurfaces::paths::move_rel_quadratic_curve(move(other._Data)))) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve& basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::operator=(rel_quadratic_curve&& other) noexcept {
			if (this != &other) {
				_Data = move(GraphicsSurfaces::paths::move_rel_quadratic_curve(move(other._Data)));
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::~rel_quadratic_curve() noexcept {
			GraphicsSurfaces::paths::destroy(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::control_pt(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt) noexcept {
			GraphicsSurfaces::paths::control_pt(_Data, cpt);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::end_pt(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept {
			GraphicsSurfaces::paths::end_pt(_Data, ept);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::control_pt() const noexcept {
			return GraphicsSurfaces::paths::control_pt(_Data);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::end_pt() const noexcept {
			return GraphicsSurfaces::paths::end_pt(_Data);
		}

        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::operator==(const rel_quadratic_curve& rhs) const noexcept {
            return control_pt() == rhs.control_pt() && end_pt() == rhs.end_pt();
        }
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::operator!=(const rel_quadratic_curve& rhs) const noexcept {
            return !(*this == rhs);
        }             
        
		template<class GraphicsSurfaces>
		inline const typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::data_type& basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::data_type& basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::abs_cubic_curve() noexcept
			: _Data(GraphicsSurfaces::paths::create_abs_cubic_curve()) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::abs_cubic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt1, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt2, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept
			: _Data(GraphicsSurfaces::paths::create_abs_cubic_curve(cpt1, cpt2, ept)) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::abs_cubic_curve(const abs_cubic_curve& other)
			: _Data(GraphicsSurfaces::paths::copy_abs_cubic_curve(other._Data)) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve& basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::operator=(const abs_cubic_curve& other) {
			if (this != &other) {
				_Data = GraphicsSurfaces::paths::copy_abs_cubic_curve(other._Data);
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::abs_cubic_curve(abs_cubic_curve&& other) noexcept
			: _Data(move(GraphicsSurfaces::paths::move_abs_cubic_curve(move(other._Data)))) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve& basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::operator=(abs_cubic_curve&& other) noexcept {
			if (this != &other) {
				_Data = move(GraphicsSurfaces::paths::move_abs_cubic_curve(move(other._Data)));
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::~abs_cubic_curve() noexcept {
			GraphicsSurfaces::paths::destroy(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::control_pt1(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt) noexcept {
			GraphicsSurfaces::paths::control_pt1(_Data, cpt);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::control_pt2(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt) noexcept {
			GraphicsSurfaces::paths::control_pt2(_Data, cpt);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::end_pt(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept {
			GraphicsSurfaces::paths::end_pt(_Data, ept);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::control_pt1() const noexcept {
			return GraphicsSurfaces::paths::control_pt1(_Data);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::control_pt2() const noexcept {
			return GraphicsSurfaces::paths::control_pt2(_Data);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::end_pt() const noexcept {
			return GraphicsSurfaces::paths::end_pt(_Data);
		}

        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::operator==(const abs_cubic_curve& rhs) const noexcept {
            return control_pt1() == rhs.control_pt1() && control_pt2() == rhs.control_pt2() && end_pt() == rhs.end_pt();
        }
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::operator!=(const abs_cubic_curve& rhs) const noexcept {
            return !(*this == rhs);
        }

		template<class GraphicsSurfaces>
		inline const typename basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::data_type& std::experimental::io2d::v1::basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::data_type& basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::rel_cubic_curve() noexcept
			: _Data(GraphicsSurfaces::paths::create_rel_cubic_curve()) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::rel_cubic_curve(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt1, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt2, const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept
			: _Data(GraphicsSurfaces::paths::create_rel_cubic_curve(cpt1, cpt2, ept)) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::rel_cubic_curve(const rel_cubic_curve& other)
			: _Data(GraphicsSurfaces::paths::copy_rel_cubic_curve(other._Data)) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_cubic_curve& basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::operator=(const rel_cubic_curve& other) {
			if (this != &other) {
				_Data = GraphicsSurfaces::paths::copy_rel_cubic_curve(other._Data);
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::rel_cubic_curve(rel_cubic_curve&& other) noexcept
			: _Data(move(GraphicsSurfaces::paths::move_rel_cubic_curve(move(other._Data)))) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::rel_cubic_curve& basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::operator=(rel_cubic_curve&& other) noexcept {
			if (this != &other) {
				_Data = move(GraphicsSurfaces::paths::move_rel_cubic_curve(move(other._Data)));
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::~rel_cubic_curve() noexcept {
			GraphicsSurfaces::paths::destroy(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::control_pt1(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt) noexcept {
			GraphicsSurfaces::paths::control_pt1(_Data, cpt);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::control_pt2(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt) noexcept {
			GraphicsSurfaces::paths::control_pt2(_Data, cpt);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::end_pt(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& ept) noexcept {
			GraphicsSurfaces::paths::end_pt(_Data, ept);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::control_pt1() const noexcept {
			return GraphicsSurfaces::paths::control_pt1(_Data);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::control_pt2() const noexcept {
			return GraphicsSurfaces::paths::control_pt2(_Data);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::end_pt() const noexcept {
			return GraphicsSurfaces::paths::end_pt(_Data);
		}

        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::operator==(const rel_cubic_curve& rhs) const noexcept {
            return control_pt1() == rhs.control_pt1() && control_pt2() == rhs.control_pt2() && end_pt() == rhs.end_pt();
        }
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::operator!=(const rel_cubic_curve& rhs) const noexcept {
            return !(*this == rhs);
        }        
        
		template<class GraphicsSurfaces>
		inline const typename basic_figure_items<GraphicsSurfaces>::arc::data_type& std::experimental::io2d::v1::basic_figure_items<GraphicsSurfaces>::arc::data() const noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::arc::data_type& basic_figure_items<GraphicsSurfaces>::arc::data() noexcept {
			return _Data;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::arc::arc() noexcept
			: _Data(GraphicsSurfaces::paths::create_arc()) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::arc::arc(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& rad, float rot, float sang) noexcept
			: _Data(GraphicsSurfaces::paths::create_arc(rad, rot, sang)) {
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::arc::arc(const arc& other)
			: _Data(GraphicsSurfaces::paths::copy_arc(other._Data)) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::arc& basic_figure_items<GraphicsSurfaces>::arc::operator=(const arc& other) {
			if (this != &other) {
				_Data = GraphicsSurfaces::paths::copy_arc(other._Data);
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::arc::arc(arc&& other) noexcept
			: _Data(move(GraphicsSurfaces::paths::move_arc(move(other._Data)))) {
		}
		template<class GraphicsSurfaces>
		inline typename basic_figure_items<GraphicsSurfaces>::arc& basic_figure_items<GraphicsSurfaces>::arc::operator=(arc&& other) noexcept {
			if (this != &other) {
				_Data = move(GraphicsSurfaces::paths::move_arc(move(other._Data)));
			}
			return *this;
		}
		template<class GraphicsSurfaces>
		inline basic_figure_items<GraphicsSurfaces>::arc::~arc() noexcept {
			GraphicsSurfaces::paths::destroy(_Data);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::arc::radius(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& rad) noexcept {
			GraphicsSurfaces::paths::radius(_Data, rad);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::arc::rotation(float rot) noexcept {
			GraphicsSurfaces::paths::rotation(_Data, rot);
		}
		template<class GraphicsSurfaces>
		inline void basic_figure_items<GraphicsSurfaces>::arc::start_angle(float radians) noexcept {
			GraphicsSurfaces::paths::start_angle(_Data, radians);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::arc::radius() const noexcept {
			return GraphicsSurfaces::paths::radius(_Data);
		}
		template<class GraphicsSurfaces>
		inline float basic_figure_items<GraphicsSurfaces>::arc::rotation() const noexcept {
			return GraphicsSurfaces::paths::rotation(_Data);
		}
		template<class GraphicsSurfaces>
		inline float basic_figure_items<GraphicsSurfaces>::arc::start_angle() const noexcept {
			return GraphicsSurfaces::paths::start_angle(_Data);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::arc::center(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt, const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) const noexcept {
			return GraphicsSurfaces::paths::center(_Data, cpt, m);
		}
		template<class GraphicsSurfaces>
		inline basic_point_2d<typename GraphicsSurfaces::graphics_math_type> basic_figure_items<GraphicsSurfaces>::arc::end_pt(const basic_point_2d<typename GraphicsSurfaces::graphics_math_type>& cpt, const basic_matrix_2d<typename GraphicsSurfaces::graphics_math_type>& m) const noexcept {
			return GraphicsSurfaces::paths::end_pt(_Data, cpt, m);
		}

        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::arc::operator==(const arc& rhs) const noexcept {
            return radius() == rhs.radius() && rotation() == rhs.rotation() && start_angle() == rhs.start_angle();
        }
        
        template<class GraphicsSurfaces>
        inline bool basic_figure_items<GraphicsSurfaces>::arc::operator!=(const arc& rhs) const noexcept {
            return !(*this == rhs);
        }

		template <class GraphicsSurfaces, class Allocator>
		::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item> _Interpret_path_items(const basic_path_builder<GraphicsSurfaces, Allocator>&);

		template<class GraphicsSurfaces>
		inline const typename basic_interpreted_path<GraphicsSurfaces>::data_type& basic_interpreted_path<GraphicsSurfaces>::data() const noexcept {
			return _Data;
		}

		template<class GraphicsSurfaces>
		inline typename basic_interpreted_path<GraphicsSurfaces>::data_type& basic_interpreted_path<GraphicsSurfaces>::data() noexcept {
			return _Data;
		}

		template <class GraphicsSurfaces>
		inline basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path() noexcept
			: _Data(GraphicsSurfaces::paths::create_interpreted_path()) { }

		template <class GraphicsSurfaces>
		inline basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path(const basic_bounding_box<graphics_math_type>& bb)
			: _Data (GraphicsSurfaces::paths::create_interpreted_path(bb)) { }

		template <class GraphicsSurfaces>
		template <class Allocator>
		inline basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path(const basic_path_builder<GraphicsSurfaces, Allocator>& pb)
			: _Data(GraphicsSurfaces::paths::create_interpreted_path(begin(pb), end(pb))) { }

		template <class GraphicsSurfaces>
		template <class ForwardIterator>
		inline basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path(ForwardIterator first, ForwardIterator last)
			: _Data(GraphicsSurfaces::paths::create_interpreted_path(first, last)) { }

		template<class GraphicsSurfaces>
		inline basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path(initializer_list<typename basic_figure_items<GraphicsSurfaces>::figure_item> il)
			: _Data(GraphicsSurfaces::paths::create_interpreted_path(begin(il), end(il))) {
		}

		template<class GraphicsSurfaces>
		inline basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path(const basic_interpreted_path& val) {
			_Data = GraphicsSurfaces::paths::copy_interpreted_path(val._Data);
		}

		template<class GraphicsSurfaces>
		inline basic_interpreted_path<GraphicsSurfaces>& basic_interpreted_path<GraphicsSurfaces>::operator=(const basic_interpreted_path& val) {
			_Data = GraphicsSurfaces::paths::copy_interpreted_path(val._Data);
			return *this;
		}

		template<class GraphicsSurfaces>
		inline basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path(basic_interpreted_path&& val) noexcept {
			if (this != &val) {
				_Data = move(GraphicsSurfaces::paths::move_interpreted_path(move(val._Data)));
			}
		}

		template<class GraphicsSurfaces>
		inline basic_interpreted_path<GraphicsSurfaces>& basic_interpreted_path<GraphicsSurfaces>::operator=(basic_interpreted_path&& val) noexcept {
			if (this != &val) {
				_Data = move(GraphicsSurfaces::paths::move_interpreted_path(move(val._Data)));
			}
			return *this;
		}

		template<class GraphicsSurfaces>
		inline basic_interpreted_path<GraphicsSurfaces>::~basic_interpreted_path() noexcept {
			GraphicsSurfaces::paths::destroy(_Data);
		}
	}
}
