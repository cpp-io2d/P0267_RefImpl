#pragma once
#include "xpath.h"
#include <vector>
#include <chrono>

namespace std::experimental::io2d {
	inline namespace v1 {
		template<class GraphicsSurfaces>
		inline const typename basic_figure_items<GraphicsSurfaces>::abs_new_figure::_Data_type& basic_figure_items<GraphicsSurfaces>::abs_new_figure::_Get_data() const noexcept {
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
		inline const typename basic_figure_items<GraphicsSurfaces>::rel_new_figure::_Data_type& basic_figure_items<GraphicsSurfaces>::rel_new_figure::_Get_data() const noexcept {
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
		inline const typename basic_figure_items<GraphicsSurfaces>::close_figure::_Data_type& basic_figure_items<GraphicsSurfaces>::close_figure::_Get_data() const noexcept {
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
		inline const typename basic_figure_items<GraphicsSurfaces>::abs_matrix::_Data_type& basic_figure_items<GraphicsSurfaces>::abs_matrix::_Get_data() const noexcept {
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
		inline const typename basic_figure_items<GraphicsSurfaces>::rel_matrix::_Data_type& basic_figure_items<GraphicsSurfaces>::rel_matrix::_Get_data() const noexcept {
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
		inline const typename basic_figure_items<GraphicsSurfaces>::revert_matrix::_Data_type& basic_figure_items<GraphicsSurfaces>::revert_matrix::_Get_data() const noexcept {
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
		inline const typename basic_figure_items<GraphicsSurfaces>::abs_line::_Data_type& basic_figure_items<GraphicsSurfaces>::abs_line::_Get_data() const noexcept {
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
		inline const typename basic_figure_items<GraphicsSurfaces>::rel_line::_Data_type& std::experimental::io2d::v1::basic_figure_items<GraphicsSurfaces>::rel_line::_Get_data() const noexcept {
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
		inline const typename basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::_Data_type& basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve::_Get_data() const noexcept {
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
		inline const typename basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::_Data_type& basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve::_Get_data() const noexcept {
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
		inline const typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::_Data_type& basic_figure_items<GraphicsSurfaces>::abs_cubic_curve::_Get_data() const noexcept {
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
		inline const typename basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::_Data_type& std::experimental::io2d::v1::basic_figure_items<GraphicsSurfaces>::rel_cubic_curve::_Get_data() const noexcept {
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
		inline const typename basic_figure_items<GraphicsSurfaces>::arc::_Data_type& std::experimental::io2d::v1::basic_figure_items<GraphicsSurfaces>::arc::_Get_data() const noexcept {
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


		template <class GraphicsSurfaces, class Allocator>
		::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item> _Interpret_path_items(const basic_path_builder<GraphicsSurfaces, Allocator>&);

		template<class GraphicsSurfaces>
		inline const typename basic_interpreted_path<GraphicsSurfaces>::_Data_type& basic_interpreted_path<GraphicsSurfaces>::_Get_data() const noexcept {
			return _Data;
		}

		template <class GraphicsSurfaces>
		inline basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path() noexcept
			: _Data(GraphicsSurfaces::paths::create_interpreted_path()) { }

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

		template <class GraphicsSurfaces, class _TItem>
		struct _Path_item_interpret_visitor {
			constexpr static float twoThirds = 2.0F / 3.0F;

			template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_new_figure>, _Path_data_abs_new_figure> = _Path_data_abs_new_figure_val>
			static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>& closePoint, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
				const auto pt = m.transform_pt({ 0.0F, 0.0F }) + item.at();
				v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_new_figure>, pt);
				currentPoint = pt;
				closePoint = pt;
			}

			template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_new_figure>, _Path_data_rel_new_figure> = _Path_data_rel_new_figure_val>
			static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>& closePoint, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
				auto amtx = m;
				amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
				const auto pt = currentPoint + item.at() * amtx;
				v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_new_figure>, pt);
				currentPoint = pt;
				closePoint = pt;
			}

			template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::close_figure>, _Path_data_close_path> = _Path_data_close_path_val>
			static void _Interpret(const T&, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>&, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>& closePoint, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
				const auto& item = v.rbegin();
				auto idx = item->index();
				if (idx == 3 || idx == 10) {
					return; // degenerate path
				}
				v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::close_figure>);
				v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_new_figure>,
					closePoint);
				currentPoint = closePoint;
			}
			template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_matrix>, _Path_data_abs_matrix> = _Path_data_abs_matrix_val>
			static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>&, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>&, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>& matrices) noexcept {
				matrices.push(m);
				m = item.matrix();
			}
			template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_matrix>, _Path_data_rel_matrix> = _Path_data_rel_matrix_val>
			static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>&, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>&, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>& matrices) noexcept {
				const auto updateM = m * item.matrix();
				matrices.push(m);
				m = updateM;
			}
			template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::revert_matrix>, _Path_data_revert_matrix> = _Path_data_revert_matrix_val>
			static void _Interpret(const T&, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>&, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>&, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>& matrices) noexcept {
				if (matrices.empty()) {
					m = basic_matrix_2d<GraphicsMath>{};
				}
				else {
					m = matrices.top();
					matrices.pop();
				}
			}
			template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
			static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
				const auto pt1 = m.transform_pt(item.control_pt1() - currentPoint) + currentPoint;
				const auto pt2 = m.transform_pt(item.control_pt2() - currentPoint) + currentPoint;
				const auto pt3 = m.transform_pt(item.end_pt() - currentPoint) + currentPoint;
				if (currentPoint == pt1&& pt1 == pt2&& pt2 == pt3) {
					return; // degenerate path segment
				}
				v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve>, pt1,
					pt2, pt3);
				currentPoint = pt3;
			}
			template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
			static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
				const auto pt = m.transform_pt(item.to() - currentPoint) + currentPoint;
				if (currentPoint == pt) {
					return; // degenerate path segment
				}
				v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_line>, pt);
				currentPoint = pt;
			}
			template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
			static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
				// Turn it into a cubic curve since cairo doesn't have quadratic curves.
				const auto controlPt = m.transform_pt(item.control_pt() - currentPoint) + currentPoint;
				const auto endPt = m.transform_pt(item.end_pt() - currentPoint) + currentPoint;
				if (currentPoint == controlPt&& controlPt == endPt) {
					return; // degenerate path segment
				}
				const auto beginPt = currentPoint;
				basic_point_2d<GraphicsMath> cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y() - beginPt.y()) * twoThirds) + beginPt.y() };
				basic_point_2d<GraphicsMath> cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y() - endPt.y()) * twoThirds) + endPt.y() };
				v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve>, cpt1, cpt2, endPt);
				currentPoint = endPt;
			}

			template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::arc>, _Path_data_arc> = _Path_data_arc_val>
			static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
				const float rot = item.rotation();
				const float oneThousandthOfADegreeInRads = pi<float> / 180'000.0F;
				if (abs(rot) < oneThousandthOfADegreeInRads) {
					// Return if the rotation is less than one thousandth of one degree; it's a degenerate path segment.
					return;
				}
				const auto clockwise = (rot < 0.0F) ? true : false;
				const basic_point_2d<GraphicsMath> rad = item.radius();
				auto startAng = item.start_angle();
				const auto origM = m;
				m = basic_matrix_2d<GraphicsMath>::init_scale(rad);
				auto centerOffset = (point_for_angle<GraphicsMath>(two_pi<float> -startAng) * rad);
				centerOffset.y(-centerOffset.y());
				auto ctr = currentPoint - centerOffset;

				basic_point_2d<GraphicsMath> pt0, pt1, pt2, pt3;
				int bezCount = 1;
				float theta = rot;

				while (abs(theta) > half_pi<float>) {
					theta /= 2.0F;
					bezCount += bezCount;
				}

				float phi = (theta / 2.0F);
				const auto cosPhi = cos(-phi);
				const auto sinPhi = sin(-phi);

				pt0.x(cosPhi);
				pt0.y(-sinPhi);
				pt3.x(pt0.x());
				pt3.y(-pt0.y());
				pt1.x((4.0F - cosPhi) / 3.0F);
				pt1.y(-(((1.0F - cosPhi) * (3.0F - cosPhi)) / (3.0F * sinPhi)));
				pt2.x(pt1.x());
				pt2.y(-pt1.y());
				auto rotCntrCwFn = [](const basic_point_2d<GraphicsMath>& pt, float a) -> basic_point_2d<GraphicsMath> {
					auto result = basic_point_2d<GraphicsMath>{ pt.x() * cos(a) - pt.y() * sin(a),
						pt.x() * sin(a) + pt.y() * cos(a) };
					result.x(_Round_floating_point_to_zero(result.x()));
					result.y(_Round_floating_point_to_zero(result.y()));
					return result;
				};
				auto rotCwFn = [](const basic_point_2d<GraphicsMath>& pt, float a) -> basic_point_2d<GraphicsMath> {
					auto result = basic_point_2d<GraphicsMath>{ pt.x() * cos(a) - pt.y() * sin(a),
						-(pt.x() * sin(a) + pt.y() * cos(a)) };
					result.x(_Round_floating_point_to_zero(result.x()));
					result.y(_Round_floating_point_to_zero(result.y()));
					return result;
				};

				startAng = two_pi<float> -startAng;

				if (clockwise) {
					pt0 = rotCwFn(pt0, phi);
					pt1 = rotCwFn(pt1, phi);
					pt2 = rotCwFn(pt2, phi);
					pt3 = rotCwFn(pt3, phi);
					auto shflPt = pt3;
					pt3 = pt0;
					pt0 = shflPt;
					shflPt = pt2;
					pt2 = pt1;
					pt1 = shflPt;
				}
				else {
					pt0 = rotCntrCwFn(pt0, phi);
					pt1 = rotCntrCwFn(pt1, phi);
					pt2 = rotCntrCwFn(pt2, phi);
					pt3 = rotCntrCwFn(pt3, phi);
					pt0.y(-pt0.y());
					pt1.y(-pt1.y());
					pt2.y(-pt2.y());
					pt3.y(-pt3.y());
					auto shflPt = pt3;
					pt3 = pt0;
					pt0 = shflPt;
					shflPt = pt2;
					pt2 = pt1;
					pt1 = shflPt;
				}
				auto currTheta = startAng;
				const auto calcAdjustedCurrPt = ((ctr + (rotCntrCwFn(pt0, currTheta) * m)) * origM);
				auto adjustVal = calcAdjustedCurrPt - currentPoint;
				basic_point_2d<GraphicsMath> tempCurrPt;
				for (; bezCount > 0; bezCount--) {
					const auto rapt0 = m.transform_pt(rotCntrCwFn(pt0, currTheta));
					const auto rapt1 = m.transform_pt(rotCntrCwFn(pt1, currTheta));
					const auto rapt2 = m.transform_pt(rotCntrCwFn(pt2, currTheta));
					const auto rapt3 = m.transform_pt(rotCntrCwFn(pt3, currTheta));
					auto cpt0 = ctr + rapt0;
					auto cpt1 = ctr + rapt1;
					auto cpt2 = ctr + rapt2;
					auto cpt3 = ctr + rapt3;
					cpt0 = origM.transform_pt(cpt0);
					cpt1 = origM.transform_pt(cpt1);
					cpt2 = origM.transform_pt(cpt2);
					cpt3 = origM.transform_pt(cpt3);
					cpt0 -= adjustVal;
					cpt1 -= adjustVal;
					cpt2 -= adjustVal;
					cpt3 -= adjustVal;
					currentPoint = cpt3;
					v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve>, cpt1, cpt2, cpt3);
					currTheta -= theta;
				}
				m = origM;
			}

			template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
			static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
				auto amtx = m;
				amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
				const auto pt1 = item.control_pt1() * amtx;
				const auto pt2 = item.control_pt2() * amtx;
				const auto pt3 = item.end_pt()* amtx;
				if (currentPoint == pt1 && pt1 == pt2 && pt2 == pt3) {
					return; // degenerate path segment
				}
				v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve>, currentPoint + pt1, currentPoint + pt1 + pt2, currentPoint + pt1 + pt2 + pt3);
				currentPoint = currentPoint + pt1 + pt2 + pt3;
			}

			template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
			static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
				auto amtx = m;
				amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
				const auto pt = currentPoint + item.to() * amtx;
				if (currentPoint == pt) {
					return; // degenerate path segment
				}
				v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_line>, pt);
				currentPoint = pt;
			}

			template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsSurfaces>::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
			static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
				auto amtx = m;
				amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
				const auto controlPt = currentPoint + item.control_pt() * amtx;
				const auto endPt = currentPoint + item.control_pt() * amtx + item.end_pt() * amtx;
				const auto beginPt = currentPoint;
				if (currentPoint == controlPt&& controlPt == endPt) {
					return; // degenerate path segment
				}
				const basic_point_2d<GraphicsMath>& cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y() - beginPt.y()) * twoThirds) + beginPt.y() };
				const basic_point_2d<GraphicsMath>& cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y() - endPt.y()) * twoThirds) + endPt.y() };
				v.emplace_back(::std::in_place_type<typename basic_figure_items<GraphicsSurfaces>::abs_cubic_curve>, cpt1, cpt2, endPt);
				currentPoint = endPt;
			}
		};

		template <class GraphicsSurfaces, class ForwardIterator>
		inline ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item> _Interpret_path_items(ForwardIterator first, ForwardIterator last);

		template <class GraphicsSurfaces, class Allocator>
		inline ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item> _Interpret_path_items(const basic_path_builder<GraphicsSurfaces, Allocator>& pf) {
			return _Interpret_path_items<GraphicsSurfaces>(begin(pf), end(pf));
		}

		template <class GraphicsSurfaces, class ForwardIterator>
		inline ::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item> _Interpret_path_items(ForwardIterator first, ForwardIterator last) {
			using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
			basic_matrix_2d<graphics_math_type> m;
			basic_point_2d<graphics_math_type> currentPoint; // Tracks the untransformed current point.
			basic_point_2d<graphics_math_type> closePoint;   // Tracks the transformed close point.
			::std::stack<basic_matrix_2d<graphics_math_type>> matrices;
			::std::vector<typename basic_figure_items<GraphicsSurfaces>::figure_item> v;

			for (auto val = first; val != last; val++) {
				::std::visit([&m, &currentPoint, &closePoint, &matrices, &v](auto&& item) {
					using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
					_Path_item_interpret_visitor<GraphicsSurfaces, T>::template _Interpret<typename GraphicsSurfaces::graphics_math_type, T>(item, v, m, currentPoint, closePoint, matrices);
				}, *val);
			}
			return v;
		}
	}
}
