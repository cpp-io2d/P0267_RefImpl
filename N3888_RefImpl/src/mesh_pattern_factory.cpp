#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

mesh_pattern_factory::mesh_pattern_factory()
	: _Lock()
	, _Pattern_type(pattern_type::mesh)
	, _Extend(extend::default_extend)
	, _Filter(filter::default_filter)
	, _Matrix(matrix_2d::init_identity())
	, _Has_current_patch()
	, _Current_patch_index()
	, _Current_patch_side_count()
	, _Current_patch_initial_point()
	, _Patches() {
}

mesh_pattern_factory::mesh_pattern_factory(const mesh_pattern_factory& other)
	: _Lock()
	, _Pattern_type()
	, _Extend()
	, _Filter()
	, _Matrix()
	, _Has_current_patch()
	, _Current_patch_index()
	, _Current_patch_side_count()
	, _Current_patch_initial_point()
	, _Patches() {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Pattern_type = other._Pattern_type;
	_Extend = other._Extend;
	_Filter = other._Filter;
	_Matrix = other._Matrix;
	_Has_current_patch = other._Has_current_patch;
	_Current_patch_index = other._Current_patch_index;
	_Current_patch_side_count = other._Current_patch_side_count;
	_Current_patch_initial_point = other._Current_patch_initial_point;
	_Patches = other._Patches;
}

mesh_pattern_factory& mesh_pattern_factory::operator=(const mesh_pattern_factory& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Pattern_type = other._Pattern_type;
		_Extend = other._Extend;
		_Filter = other._Filter;
		_Matrix = other._Matrix;
		_Has_current_patch = other._Has_current_patch;
		_Current_patch_index = other._Current_patch_index;
		_Current_patch_side_count = other._Current_patch_side_count;
		_Current_patch_initial_point = other._Current_patch_initial_point;
		_Patches = other._Patches;
	}
	return *this;
}

mesh_pattern_factory::mesh_pattern_factory(mesh_pattern_factory&& other)
	: _Lock()
	, _Pattern_type()
	, _Extend()
	, _Filter()
	, _Matrix()
	, _Has_current_patch()
	, _Current_patch_index()
	, _Current_patch_side_count()
	, _Current_patch_initial_point()
	, _Patches() {
	lock_guard<decltype(other._Lock)> olg(other._Lock);
	_Pattern_type = move(other._Pattern_type);
	_Extend = move(other._Extend);
	_Filter = move(other._Filter);
	_Matrix = move(other._Matrix);
	_Has_current_patch = move(other._Has_current_patch);
	_Current_patch_index = move(other._Current_patch_index);
	_Current_patch_side_count = move(other._Current_patch_side_count);
	_Current_patch_initial_point = move(other._Current_patch_initial_point);
	_Patches = move(other._Patches);
}

mesh_pattern_factory& mesh_pattern_factory::operator=(mesh_pattern_factory&& other) {
	if (this != &other) {
		lock_guard<decltype(other._Lock)> olg(other._Lock);
		lock_guard<decltype(_Lock)> lg(_Lock);
		_Pattern_type = move(other._Pattern_type);
		_Extend = move(other._Extend);
		_Filter = move(other._Filter);
		_Matrix = move(other._Matrix);
		_Has_current_patch = move(other._Has_current_patch);
		_Current_patch_index = move(other._Current_patch_index);
		_Current_patch_side_count = move(other._Current_patch_side_count);
		_Current_patch_initial_point = move(other._Current_patch_initial_point);
		_Patches = move(other._Patches);
	}
	return *this;
}

void mesh_pattern_factory::set_extend(extend e) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Extend = e;
}

extend mesh_pattern_factory::get_extend() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Extend;
}

void mesh_pattern_factory::set_filter(filter f) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Filter = f;
}

filter mesh_pattern_factory::get_filter() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Filter;
}

void mesh_pattern_factory::set_matrix(const matrix_2d& m) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Matrix = m;
}


matrix_2d mesh_pattern_factory::get_matrix() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Matrix;
}

void mesh_pattern_factory::begin_patch() {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (_Has_current_patch) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}
	_Has_current_patch = true;
	_Current_patch_side_count = 0;
	_Current_patch_initial_point = { };
	_Patches.push_back(_Patch());
	_Current_patch_index = static_cast<unsigned int>(_Patches.size()) - 1U;
}

void mesh_pattern_factory::begin_edit_patch(unsigned int patch_num) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (_Has_current_patch) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}

	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}

	_Has_current_patch = true;
	_Current_patch_side_count = 0;
	_Current_patch_initial_point = { };
	_Patch p;
	_Patches[patch_num] = p;
	_Current_patch_index = patch_num;
}

void mesh_pattern_factory::end_patch() {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (!_Has_current_patch) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}
	if (_Current_patch_side_count < 4) {
		line_to(_Current_patch_initial_point);
	}
	_Has_current_patch = false;
}

void mesh_pattern_factory::move_to(const point& pt) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (!_Has_current_patch || _Current_patch_side_count > 0) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}
	_Current_patch_initial_point = pt;
	auto& patch = _Patches.at(_Current_patch_index);
	get<0>(patch).move_to(pt);
}

void mesh_pattern_factory::line_to(const point& pt) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (!_Has_current_patch || _Current_patch_side_count >= 4) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}

	if (_Current_patch_side_count == 0) {
		move_to(pt);
	}
	else {
		_Current_patch_side_count++;
		auto& patch = _Patches.at(_Current_patch_index);
		get<0>(patch).line_to(pt);
	}
}

void mesh_pattern_factory::curve_to(const point& pt0, const point& pt1, const point& pt2) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (!_Has_current_patch || _Current_patch_side_count >= 4) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}

	if (_Current_patch_side_count == 0) {
		move_to(pt0);
	}

	_Current_patch_side_count++;
	auto& patch = _Patches.at(_Current_patch_index);
	get<0>(patch).curve_to(pt0, pt1, pt2);
}

void mesh_pattern_factory::set_control_point(unsigned int point_num, const point& pt) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (!_Has_current_patch) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}
	if (point_num > 3) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	auto& patch = _Patches.at(_Current_patch_index);
	get<1>(patch)[point_num] = pt;
}

void mesh_pattern_factory::set_corner_color_rgba(unsigned int corner_num, const rgba_color& color) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (!_Has_current_patch) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}
	if (corner_num > 3) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	auto& patch = _Patches.at(_Current_patch_index);
	get<2>(patch)[corner_num] = color;
}

unsigned int mesh_pattern_factory::get_patch_count() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return static_cast<unsigned int>(_Patches.size());
}

path_factory mesh_pattern_factory::get_path_factory(unsigned int patch_num) const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	const auto& patch = _Patches[patch_num];
	return get<0>(patch);
}

bool mesh_pattern_factory::get_control_point(unsigned int patch_num, unsigned int point_num, point& controlPoint) const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	const auto& patch = _Patches[patch_num];
	const auto& controlPoints = get<1>(patch);
	const auto& iter = controlPoints.find(point_num);
	if (iter == controlPoints.cend()) {
		return false;
	}
	controlPoint = (*iter).second;
	return true;
}

bool mesh_pattern_factory::get_corner_color_rgba(unsigned int patch_num, unsigned int corner_num, rgba_color& color) const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	const auto& patch = _Patches[patch_num];
	const auto& cornerColors = get<2>(patch);
	const auto& iter = cornerColors.find(corner_num);
	if (iter == cornerColors.cend()) {
		return false;
	}
	color = (*iter).second;
	return true;
}
