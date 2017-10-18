#pragma once
#include "xlinear_algebra.h"

namespace std::experimental::io2d::v1 {
	template<class GraphicsMath>
	inline const typename basic_point_2d<GraphicsMath>::_Data_type& basic_point_2d<GraphicsMath>::_Get_data() const noexcept {
		return _Data;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath>::basic_point_2d() noexcept
		: _Data(GraphicsMath::create_point_2d()) {}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath>::basic_point_2d(float xval, float yval) noexcept
		: _Data(GraphicsMath::create_point_2d(xval, yval)) {
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath>::basic_point_2d(const typename GraphicsMath::point_2d_data_type& data) noexcept
		: _Data(data) {
	}
	template <class GraphicsMath>
	inline void basic_point_2d<GraphicsMath>::x(float xval) noexcept {
		GraphicsMath::x(_Data, xval);
	}
	template <class GraphicsMath>
	inline void basic_point_2d<GraphicsMath>::y(float yval) noexcept {
		GraphicsMath::y(_Data, yval);
	}
	template <class GraphicsMath>
	inline float basic_point_2d<GraphicsMath>::x() const noexcept {
		return GraphicsMath::y(_Data);
	}
	template <class GraphicsMath>
	inline float basic_point_2d<GraphicsMath>::y() const noexcept {
		return GraphicsMath::y(_Data);
	}
	template <class GraphicsMath>
	inline float basic_point_2d<GraphicsMath>::magnitude() const noexcept {
		return GraphicsMath::magnitude(_Data);
	}
	template <class GraphicsMath>
	inline float basic_point_2d<GraphicsMath>::magnitude_squared() const noexcept {
		return GraphicsMath::magnitude_squared(_Data);
	}
	template <class GraphicsMath>
	inline float basic_point_2d<GraphicsMath>::dot(const basic_point_2d<GraphicsMath>& other) const noexcept {
		return GraphicsMath::dot(_Data, other._Data);
	}
	template <class GraphicsMath>
	inline float basic_point_2d<GraphicsMath>::angular_direction() const noexcept {
		return GraphicsMath::angular_direction(_Data);
	}
	//template <class GraphicsMath>
	//inline basic_point_2d<GraphicsMath> basic_point_2d<GraphicsMath>::zero() noexcept {
	//	return basic_point_2d();
	//}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_point_2d<GraphicsMath>::to_unit() const noexcept {
		return point_2d(GraphicsMath::to_unit(_Data));
	}
	template <class GraphicsMath>
	inline bool operator==(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
		return GraphicsMath::equal(lhs._Get_data(), rhs._Get_data());
	}
	template <class GraphicsMath>
	inline bool operator!=(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
		return GraphicsMath::not_equal(lhs._Get_data(), rhs._Get_data());
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator+(const basic_point_2d<GraphicsMath>& lhs) noexcept {
		return lhs;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator+(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::add(lhs._Get_data(), rhs._Get_data()));
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator+(const basic_point_2d<GraphicsMath>& lhs, float rhs) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::add(lhs._Get_data(), rhs));
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator+(float lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::add(lhs, rhs._Get_data()));
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator+=(const basic_point_2d<GraphicsMath>& rhs) noexcept {
		_Data = GraphicsMath::add(_Data, rhs._Data);
		return *this;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator+=(float rhs) noexcept {
		_Data = GraphicsMath::add(_Data, rhs);
		return *this;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator-(const basic_point_2d<GraphicsMath>& lhs) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::negate(lhs._Get_data()));
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator-(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::subtract(lhs._Get_data(), rhs._Get_data()));
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator-(const basic_point_2d<GraphicsMath>& lhs, float rhs) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::subtract(lhs._Get_data(), rhs));
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator-(float lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::subtract(lhs, rhs._Get_data()));
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator-=(const basic_point_2d<GraphicsMath>& rhs) noexcept {
		_Data = GraphicsMath::subtract(_Data, rhs._Get_data());
		return *this;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator-=(float rhs) noexcept {
		_Data = GraphicsMath::subtract(_Data, rhs);
		return *this;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator*=(float rhs) noexcept {
		_Data = GraphicsMath::multiply(_Data, rhs);
		return *this;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator*=(const basic_point_2d<GraphicsMath>& rhs) noexcept {
		_Data = GraphicsMath::multiply(_Data, rhs._Get_data());
		return *this;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator*(const basic_point_2d<GraphicsMath>& lhs, float rhs) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::multiply(lhs._Get_data(), rhs));
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator*(float lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::multiply(lhs, rhs._Get_data()));
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator*(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::multiply(lhs._Get_data(), rhs._Get_data()));
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator/=(float rhs) noexcept {
		_Data = GraphicsMath::divide(_Data, rhs);
		return *this;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath>& basic_point_2d<GraphicsMath>::operator/=(const basic_point_2d<GraphicsMath>& rhs) noexcept {
		_Data = GraphicsMath::divide(_Data, rhs._Get_data());
		return *this;
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator/(const basic_point_2d<GraphicsMath>& lhs, float rhs) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::divide(lhs._Get_data(), rhs));
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator/(float lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::divide(lhs, rhs._Get_data()));
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator/(const basic_point_2d<GraphicsMath>& lhs, const basic_point_2d<GraphicsMath>& rhs) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::divide(lhs._Get_data(), rhs._Get_data()));
	}

	//
	// basic_linear_algebra::matrix_2d
	//

	template <class GraphicsMath>
	inline const typename basic_matrix_2d<GraphicsMath>::_Data_type& basic_matrix_2d<GraphicsMath>::_Get_data() const noexcept {
		return _Data;
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath>::basic_matrix_2d() noexcept
		: _Data(GraphicsMath::init_identity()) {}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath>::basic_matrix_2d(float v00, float v01, float v10, float v11, float v20, float v21) noexcept
		: _Data(GraphicsMath::init_values(v00, v01, v10, v11, v20, v21)) {
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath>::basic_matrix_2d(const typename GraphicsMath::matrix_2d_data_type& val) noexcept
		: _Data(val) {
	}
	template <class GraphicsMath>
	inline void basic_matrix_2d<GraphicsMath>::m00(float val) noexcept {
		GraphicsMath::m00(val);
	}
	template <class GraphicsMath>
	inline void basic_matrix_2d<GraphicsMath>::m01(float val) noexcept {
		GraphicsMath::m01(val);
	}
	template <class GraphicsMath>
	inline void basic_matrix_2d<GraphicsMath>::m10(float val) noexcept {
		GraphicsMath::m10(_Data, val);
	}
	template <class GraphicsMath>
	inline void basic_matrix_2d<GraphicsMath>::m11(float val) noexcept {
		GraphicsMath::m11(val);
	}
	template <class GraphicsMath>
	inline void basic_matrix_2d<GraphicsMath>::m20(float val) noexcept {
		GraphicsMath::m20(val);
	}
	template <class GraphicsMath>
	inline void basic_matrix_2d<GraphicsMath>::m21(float val) noexcept {
		GraphicsMath::m21(val);
	}
	template <class GraphicsMath>
	inline float basic_matrix_2d<GraphicsMath>::m00() const noexcept {
		return GraphicsMath::m00();
	}
	template <class GraphicsMath>
	inline float basic_matrix_2d<GraphicsMath>::m01() const noexcept {
		return GraphicsMath::m01();
	}
	template <class GraphicsMath>
	inline float basic_matrix_2d<GraphicsMath>::m10() const noexcept {
		return GraphicsMath::m10();
	}
	template <class GraphicsMath>
	inline float basic_matrix_2d<GraphicsMath>::m11() const noexcept {
		return GraphicsMath::m11();
	}
	template <class GraphicsMath>
	inline float basic_matrix_2d<GraphicsMath>::m20() const noexcept {
		return GraphicsMath::m20();
	}
	template <class GraphicsMath>
	inline float basic_matrix_2d<GraphicsMath>::m21() const noexcept {
		return GraphicsMath::m21();
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::init_translate(const basic_point_2d<GraphicsMath>& value) noexcept {
		return basic_matrix_2d<GraphicsMath>(GraphicsMath::init_translate(value));
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::init_scale(const basic_point_2d<GraphicsMath>& value) noexcept {
		return basic_matrix_2d<GraphicsMath>(GraphicsMath::init_scale(value));
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::init_rotate(float radians) noexcept {
		return basic_matrix_2d<GraphicsMath>(GraphicsMath::init_rotate(radians));
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::init_rotate(float radians, const basic_point_2d<GraphicsMath>& origin) noexcept {
		return basic_matrix_2d<GraphicsMath>(GraphicsMath::init_rotate(radians, origin));
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::init_reflect(float radians) noexcept {
		return basic_matrix_2d<GraphicsMath>(GraphicsMath::init_reflect(radians));
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::init_shear_x(float factor) noexcept {
		return basic_matrix_2d<GraphicsMath>(GraphicsMath::init_shear_x(factor));
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::init_shear_y(float factor) noexcept {
		return basic_matrix_2d<GraphicsMath>(GraphicsMath::init_shear_y(factor));
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::translate(const basic_point_2d<GraphicsMath>& val) noexcept {
		GraphicsMath::translate(_Data, val);
		return *this;
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::scale(const basic_point_2d<GraphicsMath>& val) noexcept {
		GraphicsMath::scale(_Data, val);
		return *this;
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::rotate(float radians) noexcept {
		GraphicsMath::rotate(_Data, radians);
		return *this;
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::rotate(float radians, const basic_point_2d<GraphicsMath>& origin) noexcept {
		GraphicsMath::rotate(_Data, radians, origin);
		return *this;
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::reflect(float radians) noexcept {
		GraphicsMath::reflect(_Data, radians);
		return *this;
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::shear_x(float factor) noexcept {
		GraphicsMath::shear_x(_Data, factor);
		return *this;
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::shear_y(float factor) noexcept {
		GraphicsMath::shear_y(_Data, factor);
		return *this;
	}
	template <class GraphicsMath>
	inline bool basic_matrix_2d<GraphicsMath>::is_invertible() const noexcept {
		return GraphicsMath::is_invertible(_Data);
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::inverse() const noexcept {
		return GraphicsMath::inverse(_Data);
	}
	template <class GraphicsMath>
	inline bool basic_matrix_2d<GraphicsMath>::is_finite() const noexcept {
		return GraphicsMath::is_finite(_Data);
	}
	template <class GraphicsMath>
	inline float basic_matrix_2d<GraphicsMath>::determinant() const noexcept {
		return GraphicsMath::determinant(_Data);
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_matrix_2d<GraphicsMath>::transform_pt(const basic_point_2d<GraphicsMath>& pt) const noexcept {
		return GraphicsMath::transform_pt(_Data, pt);
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath>& basic_matrix_2d<GraphicsMath>::operator*=(const basic_matrix_2d<GraphicsMath>& rhs) noexcept {
		_Data = GraphicsMath::multiply(_Data, rhs._Data);
		return *this;
	}
	template <class GraphicsMath>
	inline basic_matrix_2d<GraphicsMath> operator*(const basic_matrix_2d<GraphicsMath>& lhs, const basic_matrix_2d<GraphicsMath>& rhs) noexcept {
		return basic_matrix_2d<GraphicsMath>(GraphicsMath::multiply(lhs._Get_data(), rhs._Get_data()));
	}
	template <class GraphicsMath>
	inline bool operator==(const basic_matrix_2d<GraphicsMath>& lhs, const basic_matrix_2d<GraphicsMath>& rhs) noexcept {
		return GraphicsMath::equal(lhs._Get_data(), rhs._Get_data());
	}
	template <class GraphicsMath>
	inline bool operator!=(const basic_matrix_2d<GraphicsMath>& lhs, const basic_matrix_2d<GraphicsMath>& rhs) noexcept {
		return GraphicsMath::not_equal(lhs._Get_data(), rhs._Get_data());
	}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> operator*(const basic_point_2d<GraphicsMath>& pt, const basic_matrix_2d<GraphicsMath>& m) noexcept {
		return GraphicsMath::transform_pt(m, pt);
	}

	// basic_display_point
	template <class GraphicsMath>
	inline const typename basic_display_point<GraphicsMath>::_Data_type& basic_display_point<GraphicsMath>::_Get_data() const noexcept {
		return _Data;
	}
	template <class GraphicsMath>
	inline basic_display_point<GraphicsMath>::basic_display_point() noexcept
		: _Data(GraphicsMath::create_display_point()) {
	}
	template <class GraphicsMath>
	inline basic_display_point<GraphicsMath>::basic_display_point(int x, int y) noexcept
		: _Data(GraphicsMath::create_display_point(x, y)) {
	}
	template <class GraphicsMath>
	inline basic_display_point<GraphicsMath>::basic_display_point(const typename GraphicsMath::display_point_data_type& val) noexcept
		: _Data(val) {
	}
	template <class GraphicsMath>
	inline void basic_display_point<GraphicsMath>::x(int val) noexcept {
		GraphicsMath::x(_Data, val);
	}
	template <class GraphicsMath>
	inline void basic_display_point<GraphicsMath>::y(int val) noexcept {
		GraphicsMath::y(_Data, val);
	}
	template <class GraphicsMath>
	inline int basic_display_point<GraphicsMath>::x() const noexcept {
		return GraphicsMath::x(_Data);
	}
	template <class GraphicsMath>
	inline int basic_display_point<GraphicsMath>::y() const noexcept {
		return GraphicsMath::y(_Data);
	}
	template <class GraphicsMath>
	inline bool operator==(const basic_display_point<GraphicsMath>& lhs, const basic_display_point<GraphicsMath>& rhs) noexcept {
		return GraphicsMath::equal(lhs._Get_data(), rhs._Get_data());
	}
	template <class GraphicsMath>
	inline bool operator!=(const basic_display_point<GraphicsMath>& lhs, const basic_display_point<GraphicsMath>& rhs) noexcept {
		return GraphicsMath::not_equal(lhs._Get_data(), rhs._Get_data());
	}

	//template <class GraphicsMath>
	//inline basic_point_2d<GraphicsMath> arc_start(const basic_point_2d<GraphicsMath>& ctr, float sang, const basic_point_2d<GraphicsMath>& rad) noexcept {
	//	auto lmtx = basic_matrix_2d<GraphicsMath>();
	//	lmtx.m20(0.0f); lmtx.m21(0.0f); // Eliminate translation.
	//	auto pt = point_for_angle<GraphicsMath>(sang, rad);
	//	return ctr + pt * lmtx;
	//}
	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> point_for_angle(float ang, float mgn) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::point_for_angle(ang, mgn));
	}

	template <class GraphicsMath>
	basic_point_2d<GraphicsMath> point_for_angle(float ang, const basic_point_2d<GraphicsMath>& rad) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::point_for_angle(ang, rad._Get_data()));
	}

	template <class GraphicsMath>
	float angle_for_point(const basic_point_2d<GraphicsMath>& ctr, const basic_point_2d<GraphicsMath>& pt) noexcept {
		return GraphicsMath::angle_for_point(ctr._Get_data(), pt._Get_data());
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> arc_start(const basic_point_2d<GraphicsMath>& ctr, float sang, const basic_point_2d<GraphicsMath>& rad, const basic_matrix_2d<GraphicsMath>& m) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::arc_start(ctr._Get_data(), sang, rad._Get_data(), m._Get_data()));
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> arc_center(const basic_point_2d<GraphicsMath>& cpt, float sang, const basic_point_2d<GraphicsMath>& rad, const basic_matrix_2d<GraphicsMath>& m) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::arc_center(cpt._Get_data(), sang, rad._Get_data(), m._Get_data()));
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> arc_end(const basic_point_2d<GraphicsMath>& cpt, float eang, const basic_point_2d<GraphicsMath>& rad, const basic_matrix_2d<GraphicsMath>& m) noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::arc_end(cpt._Get_data(), eang, rad._Get_data(), m._Get_data()));
	}

	// GraphicsMath

	template<class GraphicsMath>
	inline const typename basic_bounding_box<GraphicsMath>::_Data_type& basic_bounding_box<GraphicsMath>::_Get_data() const noexcept {
		return _Data;
	}

	template <class GraphicsMath>
	inline basic_bounding_box<GraphicsMath>::basic_bounding_box() noexcept
		: _Data(GraphicsMath::create_bounding_box()) { }
	template <class GraphicsMath>
	inline basic_bounding_box<GraphicsMath>::basic_bounding_box(float x, float y, float w, float h) noexcept
		: _Data(GraphicsMath::create_bounding_box(x, y, w, h)) { }
	template <class GraphicsMath>
	inline basic_bounding_box<GraphicsMath>::basic_bounding_box(const basic_point_2d<GraphicsMath>& tl, const basic_point_2d<GraphicsMath>& br) noexcept
		: _Data(GraphicsMath::create_bounding_box(tl.x(), tl.y(), ::std::max(0.0f, br.x() - tl.x()), ::std::max(0.0f, br.y() - tl.y()))) { }
	template <class GraphicsMath>
	inline basic_bounding_box<GraphicsMath>::basic_bounding_box(const typename GraphicsMath::bounding_box_data_type& val) noexcept
		: _Data(val) { }
	template <class GraphicsMath>
	inline void basic_bounding_box<GraphicsMath>::x(float value) noexcept {
		GraphicsMath::x(_Data, value);
	}
	template <class GraphicsMath>
	inline void basic_bounding_box<GraphicsMath>::y(float value) noexcept {
		GraphicsMath::y(_Data, value);
	}
	template <class GraphicsMath>
	inline void basic_bounding_box<GraphicsMath>::width(float value) noexcept {
		GraphicsMath::width(_Data, value);
	}
	template <class GraphicsMath>
	inline void basic_bounding_box<GraphicsMath>::height(float value) noexcept {
		GraphicsMath::height(_Data, value);
	}
	template <class GraphicsMath>
	inline void basic_bounding_box<GraphicsMath>::top_left(const basic_point_2d<GraphicsMath>& value) noexcept {
		GraphicsMath::top_left(_Data, value);
	}
	template <class GraphicsMath>
	inline void basic_bounding_box<GraphicsMath>::bottom_right(const basic_point_2d<GraphicsMath>& value) noexcept {
		GraphicsMath::bottom_right(_Data, value._Get_data());
	}

	template <class GraphicsMath>
	inline float basic_bounding_box<GraphicsMath>::x() const noexcept {
		return GraphicsMath::x(_Data);
	}

	template <class GraphicsMath>
	inline float basic_bounding_box<GraphicsMath>::y() const noexcept {
		return GraphicsMath::y(_Data);
	}

	template <class GraphicsMath>
	inline float basic_bounding_box<GraphicsMath>::width() const noexcept {
		return GraphicsMath::width(_Data);
	}

	template <class GraphicsMath>
	inline float basic_bounding_box<GraphicsMath>::height() const noexcept {
		return GraphicsMath::height(_Data);
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_bounding_box<GraphicsMath>::top_left() const noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::top_left(_Data));
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_bounding_box<GraphicsMath>::bottom_right() const noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::bottom_right(_Data));
	}

	template <class GraphicsMath>
	inline bool operator==(const basic_bounding_box<GraphicsMath>& lhs, const basic_bounding_box<GraphicsMath>& rhs)
		noexcept {
		return GraphicsMath::equal(lhs._Get_data(), rhs._Get_data());
	}
	template <class GraphicsMath>
	inline bool operator!=(const basic_bounding_box<GraphicsMath>& lhs, const basic_bounding_box<GraphicsMath>& rhs)
		noexcept {
		return GraphicsMath::not_equal(lhs._Get_data(), rhs._Get_data());
	}

	
	// basic_circle

	template <class GraphicsMath>
	inline const typename basic_circle<GraphicsMath>::_Data_type& basic_circle<GraphicsMath>::_Get_data() const noexcept {
		return _Data;
	}
	template <class GraphicsMath>
	inline basic_circle<GraphicsMath>::basic_circle() noexcept
		: _Data(GraphicsMath::create_circle()) {}
	template <class GraphicsMath>
	inline basic_circle<GraphicsMath>::basic_circle(const basic_point_2d<GraphicsMath>& ctr, float r) noexcept
		: _Data(GraphicsMath::create_circle(ctr._Get_data(), r)) {}
	template <class GraphicsMath>
	inline basic_circle<GraphicsMath>::basic_circle(const typename GraphicsMath::circle_data_type& val) noexcept
		: _Data(val) {}
	template <class GraphicsMath>
	inline void basic_circle<GraphicsMath>::center(const basic_point_2d<GraphicsMath>& ctr) noexcept {
		GraphicsMath::center(_Data, ctr._Get_data());
	}
	template <class GraphicsMath>
	inline void basic_circle<GraphicsMath>::radius(float r) noexcept {
		GraphicsMath::radius(_Data, r);
	}

	template <class GraphicsMath>
	inline basic_point_2d<GraphicsMath> basic_circle<GraphicsMath>::center() const noexcept {
		return basic_point_2d<GraphicsMath>(GraphicsMath::center(_Data));
	}
	template <class GraphicsMath>
	inline float basic_circle<GraphicsMath>::radius() const noexcept {
		return GraphicsMath::radius(_Data);
	}

	template <class GraphicsMath>
	inline bool operator==(const basic_circle<GraphicsMath>& lhs, const basic_circle<GraphicsMath>& rhs) noexcept {
		return GraphicsMath::equal(lhs._Get_data(), rhs._Get_data());
	}
	template <class GraphicsMath>
	inline bool operator!=(const basic_circle<GraphicsMath>& lhs, const basic_circle<GraphicsMath>& rhs) noexcept {
		return GraphicsMath::not_equal(lhs._Get_data(), rhs._Get_data());
	}

}