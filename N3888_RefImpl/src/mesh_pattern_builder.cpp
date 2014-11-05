#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

mesh_pattern_builder::mesh_pattern_builder()
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

mesh_pattern_builder::mesh_pattern_builder(const mesh_pattern_builder& other)
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

mesh_pattern_builder& mesh_pattern_builder::operator=(const mesh_pattern_builder& other) {
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

mesh_pattern_builder::mesh_pattern_builder(mesh_pattern_builder&& other)
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

mesh_pattern_builder& mesh_pattern_builder::operator=(mesh_pattern_builder&& other) {
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

pattern mesh_pattern_builder::get_pattern() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	unique_ptr<cairo_pattern_t, function<void(cairo_pattern_t*)>> upPat(cairo_pattern_create_mesh(), &cairo_pattern_destroy);
	auto pat = upPat.get();
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat));

	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(_Extend));
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(_Filter));
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat));
	cairo_matrix_t mtrx{ _Matrix.m00, _Matrix.m01, _Matrix.m10, _Matrix.m11, _Matrix.m20, _Matrix.m21 };
	cairo_pattern_set_matrix(pat, &mtrx);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat));

	for (const auto& patch : _Patches) {
		cairo_mesh_pattern_begin_patch(pat);
		const auto& pathData = get<0>(patch).get_data_ref();
		auto pdSize = pathData.size();
		for (unsigned int i = 0; i < pdSize; i++) {
			const auto& item = pathData[i];
			auto type = item.type;
			switch (type)
			{
			case std::experimental::io2d::path_data_type::move_to:
			{
				cairo_mesh_pattern_move_to(pat, item.data.move.x, item.data.move.y);
			}
				break;
			case std::experimental::io2d::path_data_type::line_to:
			{
				cairo_mesh_pattern_line_to(pat, item.data.line.x, item.data.line.y);
			}
				break;
			case std::experimental::io2d::path_data_type::curve_to:
			{
				cairo_mesh_pattern_curve_to(pat, item.data.curve.pt1.x, item.data.curve.pt1.y, item.data.curve.pt2.x, item.data.curve.pt2.y, item.data.curve.pt3.x, item.data.curve.pt3.y);
			}
				break;
			case std::experimental::io2d::path_data_type::new_sub_path:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			}
				break;
			case std::experimental::io2d::path_data_type::close_path:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			}
				break;
			case std::experimental::io2d::path_data_type::rel_move_to:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			}
				break;
			case std::experimental::io2d::path_data_type::rel_line_to:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			}
				break;
			case std::experimental::io2d::path_data_type::rel_curve_to:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			}
				break;
			case std::experimental::io2d::path_data_type::arc:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			}
				break;
			case std::experimental::io2d::path_data_type::arc_negative:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			}
				break;
			case std::experimental::io2d::path_data_type::change_matrix:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			}
				break;
			case std::experimental::io2d::path_data_type::change_origin:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			}
				break;
			default:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			}
				break;
			}
		}
		const auto& controlPoints = get<1>(patch);
		for (const auto& pt : controlPoints) {
			cairo_mesh_pattern_set_control_point(pat, pt.first, pt.second.x, pt.second.y);
		}
		const auto& cornerColors = get<2>(patch);
		for (const auto& cc : cornerColors) {
			cairo_mesh_pattern_set_corner_color_rgba(pat, cc.first, cc.second.r, cc.second.g, cc.second.b, cc.second.a);
		}
		cairo_mesh_pattern_end_patch(pat);
	}
	auto pttn = pattern(pat);
	upPat.release(); // Release the pattern only after it has been safely transferred to pttn.
	return pttn;
}

void mesh_pattern_builder::set_extend(extend e) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Extend = e;
}

extend mesh_pattern_builder::get_extend() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Extend;
}

void mesh_pattern_builder::set_filter(filter f) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Filter = f;
}

filter mesh_pattern_builder::get_filter() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Filter;
}

void mesh_pattern_builder::set_matrix(const matrix_2d& m) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	_Matrix = m;
}


matrix_2d mesh_pattern_builder::get_matrix() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return _Matrix;
}

void mesh_pattern_builder::begin_patch() {
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

void mesh_pattern_builder::begin_edit_patch(unsigned int patch_num) {
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

void mesh_pattern_builder::end_patch() {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (!_Has_current_patch) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}
	if (_Current_patch_side_count < 4) {
		line_to(_Current_patch_initial_point);
	}
	_Has_current_patch = false;
}

void mesh_pattern_builder::move_to(const point& pt) {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (!_Has_current_patch || _Current_patch_side_count > 0) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}
	_Current_patch_initial_point = pt;
	auto& patch = _Patches.at(_Current_patch_index);
	get<0>(patch).move_to(pt);
}

void mesh_pattern_builder::line_to(const point& pt) {
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

void mesh_pattern_builder::curve_to(const point& pt0, const point& pt1, const point& pt2) {
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

void mesh_pattern_builder::set_control_point(unsigned int point_num, const point& pt) {
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

void mesh_pattern_builder::set_corner_color_rgba(unsigned int corner_num, const rgba_color& color) {
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

unsigned int mesh_pattern_builder::get_patch_count() const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	return static_cast<unsigned int>(_Patches.size());
}

path mesh_pattern_builder::get_path(unsigned int patch_num) const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	auto& patch = _Patches[patch_num];
	return get<0>(patch).get_path();
}

path_builder mesh_pattern_builder::get_path_builder(unsigned int patch_num) const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	const auto& patch = _Patches[patch_num];
	return get<0>(patch);
}

point mesh_pattern_builder::get_control_point(unsigned int patch_num, unsigned int point_num) const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	const auto& patch = _Patches[patch_num];
	const auto& controlPoints = get<1>(patch);
	const auto& iter = controlPoints.find(point_num);
	if (iter == controlPoints.cend()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	return (*iter).second;
}

rgba_color mesh_pattern_builder::get_corner_color_rgba(unsigned int patch_num, unsigned int corner_num) const {
	lock_guard<decltype(_Lock)> lg(_Lock);
	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	const auto& patch = _Patches[patch_num];
	const auto& cornerColors = get<2>(patch);
	const auto& iter = cornerColors.find(corner_num);
	if (iter == cornerColors.cend()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	return (*iter).second;
}
