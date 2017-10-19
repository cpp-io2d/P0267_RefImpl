#pragma once
#include "xpath.h"
#include <vector>

namespace std::experimental::io2d::v1 {
	template<class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::abs_new_figure::abs_new_figure() noexcept
		: _Data() { }

	template<class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::abs_new_figure::abs_new_figure(const basic_point_2d<GraphicsMath>& pt) noexcept
		: _Data(pt) {
	}
	template<class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::abs_new_figure::at(const basic_point_2d<GraphicsMath>& pt) noexcept {
		_Data = pt;
	}
	template<class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::abs_new_figure::at() const noexcept {
		return _Data;
	}
	template<class GraphicsMath>
	inline bool operator==(const typename basic_figure_items<GraphicsMath>::abs_new_figure& lhs, const typename basic_figure_items<GraphicsMath>::abs_new_figure& rhs) noexcept {
		return lhs._Data == rhs._Data;
	}
	template<class GraphicsMath>
	inline bool operator!=(const typename basic_figure_items<GraphicsMath>::abs_new_figure& lhs, const typename basic_figure_items<GraphicsMath>::abs_new_figure& rhs) noexcept {
		return !(lhs == rhs);
	}

	template<class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::rel_new_figure::rel_new_figure() noexcept {}

	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::rel_new_figure::rel_new_figure(const basic_point_2d<GraphicsMath>& pt) noexcept
		: _Data(pt) {}

	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::rel_new_figure::at(const basic_point_2d<GraphicsMath>& pt) noexcept {
		_Data = pt;
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::rel_new_figure::at() const noexcept {
		return _Data;
	}

	template <class GraphicsMath>
	inline bool operator==(const typename basic_figure_items<GraphicsMath>::rel_new_figure& lhs, const typename basic_figure_items<GraphicsMath>::rel_new_figure& rhs) noexcept {
		return lhs._Data == rhs._Data;
	}

	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::close_figure::close_figure() noexcept {}

	template <class GraphicsMath>
	inline bool operator==(const typename basic_figure_items<GraphicsMath>::close_figure&, const typename basic_figure_items<GraphicsMath>::close_figure&) noexcept {
		return true;
	}

	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::abs_matrix::abs_matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept
		: _Matrix(m) {
	}
	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::abs_matrix::abs_matrix() noexcept {}

	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::abs_matrix::matrix(const basic_matrix_2d<GraphicsMath>& value) noexcept {
		_Matrix = value;
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath> basic_figure_items<GraphicsMath>::abs_matrix::matrix() const noexcept {
		return _Matrix;
	}

	template <class GraphicsMath>
	inline bool operator==(const typename basic_figure_items<GraphicsMath>::abs_matrix& lhs, const typename basic_figure_items<GraphicsMath>::abs_matrix& rhs) noexcept {
		return lhs._Matrix == rhs._Matrix;
	}

	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::rel_matrix::rel_matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept
		: _Matrix(m) {
	}
	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::rel_matrix::rel_matrix() noexcept {}

	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::rel_matrix::matrix(const basic_matrix_2d<GraphicsMath>& value) noexcept {
		_Matrix = value;
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath> basic_figure_items<GraphicsMath>::rel_matrix::matrix() const noexcept {
		return _Matrix;
	}

	template <class GraphicsMath>
	inline bool operator==(const typename basic_figure_items<GraphicsMath>::rel_matrix& lhs, const typename basic_figure_items<GraphicsMath>::rel_matrix& rhs) noexcept {
		return lhs._Matrix == rhs._Matrix;
	}

	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::revert_matrix::revert_matrix() noexcept {}

	template <class GraphicsMath>
	inline bool operator==(const typename basic_figure_items<GraphicsMath>::revert_matrix&, const typename basic_figure_items<GraphicsMath>::revert_matrix&) noexcept {
		return true;
	}

	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::abs_line::abs_line(const basic_point_2d<GraphicsMath>& to) noexcept
		: _Data(to) {
	}
	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::abs_line::abs_line() noexcept {}

	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::abs_line::to(const basic_point_2d<GraphicsMath>& value) noexcept {
		_Data = value;
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::abs_line::to() const noexcept {
		return _Data;
	}

	template <class GraphicsMath>
	inline bool operator==(const typename basic_figure_items<GraphicsMath>::abs_line& lhs, const typename basic_figure_items<GraphicsMath>::abs_line& rhs) noexcept {
		return lhs._Data == rhs._Data;
	}

	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::rel_line::rel_line(const basic_point_2d<GraphicsMath>& to) noexcept
		: _Data(to) {
	}
	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::rel_line::rel_line() noexcept {}

	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::rel_line::to(const basic_point_2d<GraphicsMath>& value) noexcept {
		_Data = value;
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::rel_line::to() const noexcept {
		return _Data;
	}

	template <class GraphicsMath>
	inline bool operator==(const typename basic_figure_items<GraphicsMath>::rel_line& lhs, const typename basic_figure_items<GraphicsMath>::rel_line& rhs) noexcept {
		return lhs._Data == rhs._Data;
	}

	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::abs_quadratic_curve::abs_quadratic_curve(const basic_point_2d<GraphicsMath>& cp, const basic_point_2d<GraphicsMath>& ep) noexcept
		: _Control_pt(cp)
		, _End_pt(ep) {
	}
	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::abs_quadratic_curve::abs_quadratic_curve() noexcept {}

	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::abs_quadratic_curve::control_pt(const basic_point_2d<GraphicsMath>& value) noexcept {
		_Control_pt = value;
	}
	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::abs_quadratic_curve::end_pt(const basic_point_2d<GraphicsMath>& value) noexcept {
		_End_pt = value;
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::abs_quadratic_curve::control_pt() const noexcept {
		return _Control_pt;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::abs_quadratic_curve::end_pt() const noexcept {
		return _End_pt;
	}

	template <class GraphicsMath>
	inline bool operator==(const typename basic_figure_items<GraphicsMath>::abs_quadratic_curve& lhs, const typename basic_figure_items<GraphicsMath>::abs_quadratic_curve& rhs) noexcept {
		return (lhs._Control_pt == rhs._Control_pt) &&
			(lhs._End_pt == rhs._End_pt);
	}

	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::rel_quadratic_curve::rel_quadratic_curve(const basic_point_2d<GraphicsMath>& cp, const basic_point_2d<GraphicsMath>& ep) noexcept
		: _Control_pt(cp)
		, _End_pt(ep) {
	}
	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::rel_quadratic_curve::rel_quadratic_curve() noexcept {}

	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::rel_quadratic_curve::control_pt(const basic_point_2d<GraphicsMath>& value) noexcept {
		_Control_pt = value;
	}
	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::rel_quadratic_curve::end_pt(const basic_point_2d<GraphicsMath>& value) noexcept {
		_End_pt = value;
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::rel_quadratic_curve::control_pt() const noexcept {
		return _Control_pt;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::rel_quadratic_curve::end_pt() const noexcept {
		return _End_pt;
	}

	template <class GraphicsMath>
	inline bool operator==(const typename basic_figure_items<GraphicsMath>::rel_quadratic_curve& lhs, const typename basic_figure_items<GraphicsMath>::rel_quadratic_curve& rhs) noexcept {
		return (lhs._Control_pt == rhs._Control_pt) &&
			(lhs._End_pt == rhs._End_pt);
	}

	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::abs_cubic_curve::abs_cubic_curve(const basic_point_2d<GraphicsMath>& controlPoint1, const basic_point_2d<GraphicsMath>& controlPoint2, const basic_point_2d<GraphicsMath>& endPoint) noexcept
		: _Control_pt1(controlPoint1)
		, _Control_pt2(controlPoint2)
		, _End_pt(endPoint) {
	}
	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::abs_cubic_curve::abs_cubic_curve() noexcept {}

	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::abs_cubic_curve::control_pt1(const basic_point_2d<GraphicsMath>& value) noexcept {
		_Control_pt1 = value;
	}
	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::abs_cubic_curve::control_pt2(const basic_point_2d<GraphicsMath>& value) noexcept {
		_Control_pt2 = value;
	}
	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::abs_cubic_curve::end_pt(const basic_point_2d<GraphicsMath>& value) noexcept {
		_End_pt = value;
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::abs_cubic_curve::control_pt1() const noexcept {
		return _Control_pt1;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::abs_cubic_curve::control_pt2() const noexcept {
		return _Control_pt2;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::abs_cubic_curve::end_pt() const noexcept {
		return _End_pt;
	}

	template <class GraphicsMath>
	inline bool operator==(const typename basic_figure_items<GraphicsMath>::abs_cubic_curve& lhs, const typename basic_figure_items<GraphicsMath>::abs_cubic_curve& rhs) noexcept {
		return (lhs._Control_pt1 == rhs._Control_pt1) &&
			(lhs._Control_pt2 == rhs._Control_pt2) &&
			(lhs._End_pt == rhs._End_pt);
	}

	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::rel_cubic_curve::rel_cubic_curve(const basic_point_2d<GraphicsMath>& controlPoint1, const basic_point_2d<GraphicsMath>& controlPoint2, const basic_point_2d<GraphicsMath>& endPoint) noexcept
		: _Control_pt1(controlPoint1)
		, _Control_pt2(controlPoint2)
		, _End_pt(endPoint) {
	}
	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::rel_cubic_curve::rel_cubic_curve() noexcept {}

	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::rel_cubic_curve::control_pt1(const basic_point_2d<GraphicsMath>& value) noexcept {
		_Control_pt1 = value;
	}
	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::rel_cubic_curve::control_pt2(const basic_point_2d<GraphicsMath>& value) noexcept {
		_Control_pt2 = value;
	}
	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::rel_cubic_curve::end_pt(const basic_point_2d<GraphicsMath>& value) noexcept {
		_End_pt = value;
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::rel_cubic_curve::control_pt1() const noexcept {
		return _Control_pt1;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::rel_cubic_curve::control_pt2() const noexcept {
		return _Control_pt2;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::rel_cubic_curve::end_pt() const noexcept {
		return _End_pt;
	}

	template <class GraphicsMath>
	inline bool operator==(const typename basic_figure_items<GraphicsMath>::rel_cubic_curve& lhs, const typename basic_figure_items<GraphicsMath>::rel_cubic_curve& rhs) noexcept {
		return (lhs._Control_pt1 == rhs._Control_pt1) &&
			(lhs._Control_pt2 == rhs._Control_pt2) &&
			(lhs._End_pt == rhs._End_pt);
	}

	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::arc::arc() noexcept
		: arc(basic_point_2d<GraphicsMath>{ 10.0F, 10.0F }, pi<float>, pi<float>) { }
	template <class GraphicsMath>
	inline basic_figure_items<GraphicsMath>::arc::arc(const basic_point_2d<GraphicsMath>& rad, float rot, float sang) noexcept
		: _Radius(rad)
		, _Rotation(rot)
		, _Start_angle(sang) {
	}

	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::arc::radius(const basic_point_2d<GraphicsMath>& rad) noexcept {
		_Radius = rad;
	}
	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::arc::rotation(float rot) noexcept {
		_Rotation = rot;
	}
	template <class GraphicsMath>
	inline void basic_figure_items<GraphicsMath>::arc::start_angle(float sang) noexcept {
		_Start_angle = sang;
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::arc::radius() const noexcept {
		return _Radius;
	}
	template <class GraphicsMath>
	inline float basic_figure_items<GraphicsMath>::arc::rotation() const noexcept {
		return _Rotation;
	}
	template <class GraphicsMath>
	inline float basic_figure_items<GraphicsMath>::arc::start_angle() const noexcept {
		return _Start_angle;
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::arc::center(const basic_point_2d<GraphicsMath>& cpt, const basic_matrix_2d<GraphicsMath>& m) const noexcept {
		auto lmtx = m;
		lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
		auto centerOffset = point_for_angle<GraphicsMath>(two_pi<float> -_Start_angle, _Radius);
		centerOffset.y(-centerOffset.y());
		return cpt - centerOffset * lmtx;
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_figure_items<GraphicsMath>::arc::end_pt(const basic_point_2d<GraphicsMath>& cpt, const basic_matrix_2d<GraphicsMath>& m) const noexcept {
		auto lmtx = m;
		auto tfrm = matrix_2d::init_rotate(_Start_angle + _Rotation);
		lmtx.m20(0.0F); lmtx.m21(0.0F); // Eliminate translation.
		auto pt = (_Radius * tfrm);
		pt.y(-pt.y());
		return cpt + pt * lmtx;
	}

	template <class GraphicsMath>
	inline bool operator==(const typename basic_figure_items<GraphicsMath>::arc& lhs, const typename basic_figure_items<GraphicsMath>::arc& rhs) noexcept {
		return (lhs._Radius == rhs._Radius) &&
			(lhs._Rotation == rhs._Rotation) &&
			(lhs._Start_angle == rhs._Start_angle);
	}

	template <class GraphicsMath>
	inline bool operator!=(const typename basic_figure_items<GraphicsMath>::arc& lhs, const typename basic_figure_items<GraphicsMath>::arc& rhs) noexcept {
		return !(lhs == rhs);
	}

	template <class GraphicsMath, class Allocator>
	::std::vector<typename basic_figure_items<GraphicsMath>::figure_item> _Interpret_path_items(const basic_path_builder<GraphicsMath, Allocator>&);

	template<class GraphicsSurfaces>
	inline const typename basic_interpreted_path<GraphicsSurfaces>::_Data_type& basic_interpreted_path<GraphicsSurfaces>::_Get_data() const noexcept {
		return _Data;
	}

	template <class GraphicsSurfaces>
	inline basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path() noexcept
		: _Data(GraphicsSurfaces::create_interpreted_path()) { }

	template<class GraphicsSurfaces>
	inline basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path(const basic_interpreted_path& val) {
		_Data = GraphicsSurfaces::copy_interpreted_path(val._Data);
	}

	template<class GraphicsSurfaces>
	inline basic_interpreted_path<GraphicsSurfaces>& basic_interpreted_path<GraphicsSurfaces>::operator=(const basic_interpreted_path& val) {
		_Data = GraphicsSurfaces::copy_interpreted_path(val._Data);
		return *this;
	}

	template<class GraphicsSurfaces>
	inline basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path(basic_interpreted_path&& val) noexcept {
		if (this != &val) {
			_Data = move(GraphicsSurfaces::move_interpreted_path(move(val._Data)));
		}
	}

	template<class GraphicsSurfaces>
	inline basic_interpreted_path<GraphicsSurfaces>& basic_interpreted_path<GraphicsSurfaces>::operator=(basic_interpreted_path&& val) noexcept {
		if (this != &val) {
			_Data = move(GraphicsSurfaces::move_interpreted_path(move(val._Data)));
		}
		return *this;
	}

	template<class GraphicsSurfaces>
	inline basic_interpreted_path<GraphicsSurfaces>::~basic_interpreted_path() noexcept {
		GraphicsSurfaces::destroy(_Data);
	}

	template <class GraphicsSurfaces>
	template <class GraphicsMath, class Allocator>
	inline basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path(const basic_path_builder<GraphicsMath, Allocator>& pb)
		: _Data(GraphicsSurfaces::create_interpreted_path(pb)) { }

	template <class GraphicsSurfaces>
	template <class ForwardIterator>
	inline basic_interpreted_path<GraphicsSurfaces>::basic_interpreted_path(ForwardIterator first, ForwardIterator last)
		: _Data(GraphicsSurfaces::create_interpreted_path(first, last)) { }

	template <class _TItem>
	struct _Path_item_interpret_visitor {
		constexpr static float twoThirds = 2.0F / 3.0F;

		template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_new_figure>, _Path_data_abs_new_figure> = _Path_data_abs_new_figure_val>
		static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>& closePoint, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
			const auto pt = m.transform_pt({ 0.0F, 0.0F }) + item.at();
			v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_new_figure>, pt);
			currentPoint = pt;
			closePoint = pt;
		}

		template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_new_figure>, _Path_data_rel_new_figure> = _Path_data_rel_new_figure_val>
		static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>& closePoint, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
			auto amtx = m;
			amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
			const auto pt = currentPoint + item.at() * amtx;
			v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_new_figure>, pt);
			currentPoint = pt;
			closePoint = pt;
		}

		template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::close_figure>, _Path_data_close_path> = _Path_data_close_path_val>
		static void _Interpret(const T&, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, basic_matrix_2d<GraphicsMath>&, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>& closePoint, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
			const auto& item = v.rbegin();
			auto idx = item->index();
			if (idx == 3 || idx == 10) {
				return; // degenerate path
			}
			v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::close_figure>);
			v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_new_figure>,
				closePoint);
			currentPoint = closePoint;
		}
		template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_matrix>, _Path_data_abs_matrix> = _Path_data_abs_matrix_val>
		static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>&, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>&, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>& matrices) noexcept {
			matrices.push(m);
			m = item.matrix();
		}
		template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_matrix>, _Path_data_rel_matrix> = _Path_data_rel_matrix_val>
		static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>&, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>&, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>& matrices) noexcept {
			const auto updateM = m * item.matrix();
			matrices.push(m);
			m = updateM;
		}
		template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::revert_matrix>, _Path_data_revert_matrix> = _Path_data_revert_matrix_val>
		static void _Interpret(const T&, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>&, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>&, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>& matrices) noexcept {
			if (matrices.empty()) {
				m = matrix_2d{};
			}
			else {
				m = matrices.top();
				matrices.pop();
			}
		}
		template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
		static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
			const auto pt1 = m.transform_pt(item.control_pt1() - currentPoint) + currentPoint;
			const auto pt2 = m.transform_pt(item.control_pt2() - currentPoint) + currentPoint;
			const auto pt3 = m.transform_pt(item.end_pt() - currentPoint) + currentPoint;
			if (currentPoint == pt1 && pt1 == pt2 && pt2 == pt3) {
				return; // degenerate path segment
			}
			v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_cubic_curve>, pt1,
				pt2, pt3);
			currentPoint = pt3;
		}
		template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
		static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
			const auto pt = m.transform_pt(item.to() - currentPoint) + currentPoint;
			if (currentPoint == pt) {
				return; // degenerate path segment
			}
			v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_line>, pt);
			currentPoint = pt;
		}
		template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
		static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
			// Turn it into a cubic curve since cairo doesn't have quadratic curves.
			const auto controlPt = m.transform_pt(item.control_pt() - currentPoint) + currentPoint;
			const auto endPt = m.transform_pt(item.end_pt() - currentPoint) + currentPoint;
			if (currentPoint == controlPt && controlPt == endPt) {
				return; // degenerate path segment
			}
			const auto beginPt = currentPoint;
			basic_point_2d<GraphicsMath> cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y() - beginPt.y()) * twoThirds) + beginPt.y() };
			basic_point_2d<GraphicsMath> cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y() - endPt.y()) * twoThirds) + endPt.y() };
			v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_cubic_curve>, cpt1, cpt2, endPt);
			currentPoint = endPt;
		}

		template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::arc>, _Path_data_arc> = _Path_data_arc_val>
		static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
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
			m = matrix_2d::init_scale(rad);
			auto centerOffset = (point_for_angle<GraphicsMath>(two_pi<float> - startAng) * rad);
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
				v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_cubic_curve>, cpt1, cpt2, cpt3);
				currTheta -= theta;
			}
			m = origM;
		}

		template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
		static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
			auto amtx = m;
			amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
			const auto pt1 = item.control_pt1() * amtx;
			const auto pt2 = item.control_pt2() * amtx;
			const auto pt3 = item.end_pt()* amtx;
			if (currentPoint == pt1 && pt1 == pt2 && pt2 == pt3) {
				return; // degenerate path segment
			}
			v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_cubic_curve>, currentPoint + pt1, currentPoint + pt1 + pt2, currentPoint + pt1 + pt2 + pt3);
			currentPoint = currentPoint + pt1 + pt2 + pt3;
		}

		template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
		static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
			auto amtx = m;
			amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
			const auto pt = currentPoint + item.to() * amtx;
			if (currentPoint == pt) {
				return; // degenerate path segment
			}
			v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_line>, pt);
			currentPoint = pt;
		}

		template <class GraphicsMath, class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
		static void _Interpret(const T& item, ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item>& v, basic_matrix_2d<GraphicsMath>& m, basic_point_2d<GraphicsMath>& currentPoint, basic_point_2d<GraphicsMath>&, stack<basic_matrix_2d<GraphicsMath>>&) noexcept {
			auto amtx = m;
			amtx.m20(0.0F); amtx.m21(0.0F); // obliterate translation since this is relative.
			const auto controlPt = currentPoint + item.control_pt() * amtx;
			const auto endPt = currentPoint + item.control_pt() * amtx + item.end_pt() * amtx;
			const auto beginPt = currentPoint;
			if (currentPoint == controlPt && controlPt == endPt) {
				return; // degenerate path segment
			}
			const basic_point_2d<GraphicsMath>& cpt1 = { ((controlPt.x() - beginPt.x()) * twoThirds) + beginPt.x(), ((controlPt.y() - beginPt.y()) * twoThirds) + beginPt.y() };
			const basic_point_2d<GraphicsMath>& cpt2 = { ((controlPt.x() - endPt.x()) * twoThirds) + endPt.x(), ((controlPt.y() - endPt.y()) * twoThirds) + endPt.y() };
			v.emplace_back(::std::in_place_type<basic_figure_items<GraphicsMath>::abs_cubic_curve>, cpt1, cpt2, endPt);
			currentPoint = endPt;
		}
	};

	template <class GraphicsMath, class ForwardIterator>
	inline ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item> _Interpret_path_items(ForwardIterator first, ForwardIterator last);

	template <class GraphicsMath, class Allocator>
	inline ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item> _Interpret_path_items(const basic_path_builder<GraphicsMath, Allocator>& pf) {
		return _Interpret_path_items<GraphicsMath>(begin(pf), end(pf));
	}

	template <class GraphicsMath, class ForwardIterator>
	inline ::std::vector<typename basic_figure_items<GraphicsMath>::figure_item> _Interpret_path_items(ForwardIterator first, ForwardIterator last) {
		basic_matrix_2d<GraphicsMath> m;
		basic_point_2d<GraphicsMath> currentPoint; // Tracks the untransformed current point.
		basic_point_2d<GraphicsMath> closePoint;   // Tracks the transformed close point.
		::std::stack<basic_matrix_2d<GraphicsMath>> matrices;
		::std::vector<typename basic_figure_items<GraphicsMath>::figure_item> v;

		for (auto val = first; val != last; val++) {
			::std::visit([&m, &currentPoint, &closePoint, &matrices, &v](auto&& item) {
				using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
				_Path_item_interpret_visitor<T>::template _Interpret<GraphicsMath, T>(item, v, m, currentPoint, closePoint, matrices);
			}, *val);
		}
		return v;
	}
}
