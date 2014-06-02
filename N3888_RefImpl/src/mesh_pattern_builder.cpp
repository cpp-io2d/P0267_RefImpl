#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

mesh_pattern_builder::mesh_pattern_builder()
: _Pattern_type(pattern_type::mesh)
, _Extend(extend::default_extend)
, _Filter(filter::default_filter)
, _Matrix(matrix::init_identity())
, _Has_current_patch()
, _Current_patch_index()
, _Current_patch_side_count()
, _Current_patch_initial_point()
, _Patches() {
}

mesh_pattern_builder::mesh_pattern_builder(mesh_pattern_builder&& other)
: _Pattern_type(move(other._Pattern_type))
, _Extend(move(other._Extend))
, _Filter(move(other._Filter))
, _Matrix(move(other._Matrix))
, _Has_current_patch(move(other._Has_current_patch))
, _Current_patch_index(move(other._Current_patch_index))
, _Current_patch_side_count(move(other._Current_patch_side_count))
, _Current_patch_initial_point(move(other._Current_patch_initial_point))
, _Patches(move(other._Patches)) {
}

mesh_pattern_builder& mesh_pattern_builder::operator=(mesh_pattern_builder&& other) {
	if (this != &other) {
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

pattern mesh_pattern_builder::get_pattern() {
	auto pat = cairo_pattern_create_mesh();
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));

	cairo_pattern_set_extend(pat, _Extend_to_cairo_extend_t(_Extend));
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));
	cairo_pattern_set_filter(pat, _Filter_to_cairo_filter_t(_Filter));
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));
	cairo_matrix_t mtrx{ _Matrix.xx, _Matrix.yx, _Matrix.xy, _Matrix.yy, _Matrix.x0, _Matrix.y0 };
	cairo_pattern_set_matrix(pat, &mtrx);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_pattern_status(pat)));

	for (const auto& patch : _Patches) {
		cairo_mesh_pattern_begin_patch(pat);
		const auto& pathData = get<0>(patch).get_data_ref();
		for (int i = 0; i < pathData.size(); i += pathData[i].header.length) {
			auto type = pathData[i].header.type;
			switch (type) {
			case std::experimental::drawing::path_data_type::move_to:
				cairo_mesh_pattern_move_to(pat, pathData[i + 1].point.x, pathData[i + 1].point.y);
				break;
			case std::experimental::drawing::path_data_type::line_to:
				cairo_mesh_pattern_line_to(pat, pathData[i + 1].point.x, pathData[i + 1].point.y);
				break;
			case std::experimental::drawing::path_data_type::curve_to:
				cairo_mesh_pattern_curve_to(pat, pathData[i + 1].point.x, pathData[i + 1].point.y, pathData[i + 2].point.x, pathData[i + 2].point.y, pathData[i + 3].point.x, pathData[i + 3].point.y);
				break;
			case std::experimental::drawing::path_data_type::new_sub_path:
				_Throw_if_failed_status(status::invalid_mesh_construction);
				break;
			case std::experimental::drawing::path_data_type::close_path:
				_Throw_if_failed_status(status::invalid_mesh_construction);
				break;
			default:
				_Throw_if_failed_status(status::invalid_mesh_construction);
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
	return pattern(pat);
}

void mesh_pattern_builder::set_extend(extend e) {
	_Extend = e;
}

extend mesh_pattern_builder::get_extend() {
	return _Extend;
}

void mesh_pattern_builder::set_filter(filter f) {
	_Filter = f;
}

filter mesh_pattern_builder::get_filter() {
	return _Filter;
}

void mesh_pattern_builder::set_matrix(const matrix& m) {
	_Matrix = m;
}

matrix mesh_pattern_builder::get_matrix() {
	return _Matrix;
}

void mesh_pattern_builder::begin_patch() {
	if (_Has_current_patch) {
		_Throw_if_failed_status(status::invalid_mesh_construction);
	}
	_Has_current_patch = true;
	_Current_patch_side_count = 0;
	_Current_patch_initial_point = { };
	_Patches.push_back(_Patch());
	_Current_patch_index = static_cast<unsigned int>(_Patches.size()) - 1U;
}

void mesh_pattern_builder::begin_edit_patch(unsigned int patch_num) {
	if (_Has_current_patch) {
		_Throw_if_failed_status(status::invalid_mesh_construction);
	}

	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_status(status::invalid_index);
	}

	_Has_current_patch = true;
	_Current_patch_side_count = 0;
	_Current_patch_initial_point = { };
	_Patch p;
	_Patches[patch_num] = p;
	_Current_patch_index = patch_num;
}

void mesh_pattern_builder::end_patch() {
	if (!_Has_current_patch) {
		_Throw_if_failed_status(status::invalid_mesh_construction);
	}
	if (_Current_patch_side_count < 4) {
		line_to(_Current_patch_initial_point);
	}
	_Has_current_patch = false;
}

void mesh_pattern_builder::move_to(const point& pt) {
	if (!_Has_current_patch || _Current_patch_side_count > 0) {
		_Throw_if_failed_status(status::invalid_mesh_construction);
	}
	_Current_patch_initial_point = pt;
	auto& patch = _Patches.at(_Current_patch_index);
	get<0>(patch).move_to(pt);
}

void mesh_pattern_builder::line_to(const point& pt) {
	if (!_Has_current_patch || _Current_patch_side_count >= 4) {
		_Throw_if_failed_status(status::invalid_mesh_construction);
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
	if (!_Has_current_patch || _Current_patch_side_count >= 4) {
		_Throw_if_failed_status(status::invalid_mesh_construction);
	}

	if (_Current_patch_side_count == 0) {
		move_to(pt0);
	}

	_Current_patch_side_count++;
	auto& patch = _Patches.at(_Current_patch_index);
	get<0>(patch).curve_to(pt0, pt1, pt2);
}

void mesh_pattern_builder::set_control_point(unsigned int point_num, const point& pt) {
	if (!_Has_current_patch) {
		_Throw_if_failed_status(status::invalid_mesh_construction);
	}
	if (point_num > 3) {
		_Throw_if_failed_status(status::invalid_index);
	}
	auto& patch = _Patches.at(_Current_patch_index);
	get<1>(patch)[point_num] = pt;
}

void mesh_pattern_builder::set_corner_color_rgba(unsigned int corner_num, const rgba_color& color) {
	if (!_Has_current_patch) {
		_Throw_if_failed_status(status::invalid_mesh_construction);
	}
	if (corner_num > 3) {
		_Throw_if_failed_status(status::invalid_index);
	}
	auto& patch = _Patches.at(_Current_patch_index);
	get<2>(patch)[corner_num] = color;
}

void mesh_pattern_builder::get_patch_count(unsigned int& count) {
	count = static_cast<unsigned int>(_Patches.size());
}

path mesh_pattern_builder::get_path(unsigned int patch_num) {
	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_status(status::invalid_index);
	}
	auto& patch = _Patches[patch_num];
	return get<0>(patch).get_path();
}

path_builder mesh_pattern_builder::get_path_builder(unsigned int patch_num) {
	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_status(status::invalid_index);
	}
	const auto& patch = _Patches[patch_num];
	return get<0>(patch);
}

point mesh_pattern_builder::get_control_point(unsigned int patch_num, unsigned int point_num) {
	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_status(status::invalid_index);
	}
	const auto& patch = _Patches[patch_num];
	const auto& controlPoints = get<1>(patch);
	const auto& iter = controlPoints.find(point_num);
	if (iter == controlPoints.cend()) {
		_Throw_if_failed_status(status::invalid_index);
	}
	return (*iter).second;
}

rgba_color mesh_pattern_builder::get_corner_color_rgba(unsigned int patch_num, unsigned int corner_num) {
	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_status(status::invalid_index);
	}
	const auto& patch = _Patches[patch_num];
	const auto& cornerColors = get<2>(patch);
	const auto& iter = cornerColors.find(corner_num);
	if (iter == cornerColors.cend()) {
		_Throw_if_failed_status(status::invalid_index);
	}
	return (*iter).second;
}
