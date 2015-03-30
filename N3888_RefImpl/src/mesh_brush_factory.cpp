#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

mesh_brush_factory::mesh_brush_factory() noexcept
	: _Has_current_patch()
	, _Current_patch_index()
	, _Current_patch_side_count()
	, _Current_patch_initial_point()
	, _Has_current_point()
	, _Patches() {
}

mesh_brush_factory::mesh_brush_factory(mesh_brush_factory&& other) noexcept
	: _Has_current_patch()
	, _Current_patch_index()
	, _Current_patch_side_count()
	, _Current_patch_initial_point()
	, _Has_current_point()
	, _Patches() {
	_Has_current_patch = move(other._Has_current_patch);
	_Has_current_point = move(other._Has_current_point);
	_Current_patch_index = move(other._Current_patch_index);
	_Current_patch_side_count = move(other._Current_patch_side_count);
	_Current_patch_initial_point = move(other._Current_patch_initial_point);
	_Patches = move(other._Patches);
}

mesh_brush_factory& mesh_brush_factory::operator=(mesh_brush_factory&& other) noexcept {
	if (this != &other) {
		_Has_current_patch = move(other._Has_current_patch);
		_Has_current_point = move(other._Has_current_point);
		_Current_patch_index = move(other._Current_patch_index);
		_Current_patch_side_count = move(other._Current_patch_side_count);
		_Current_patch_initial_point = move(other._Current_patch_initial_point);
		_Patches = move(other._Patches);
	}
	return *this;
}

void mesh_brush_factory::begin_patch() {
	if (_Has_current_patch) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}
	_Patches.push_back(_Patch());
	_Has_current_patch = true;
	_Has_current_point = false;
	_Current_patch_side_count = 0;
	_Current_patch_initial_point = { };
	_Current_patch_index = static_cast<unsigned int>(_Patches.size()) - 1U;
}

void mesh_brush_factory::begin_patch(error_code& ec) noexcept {
	if (_Has_current_patch) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return;
	}
	try {
		_Patches.push_back(_Patch());
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Has_current_patch = true;
	_Has_current_point = false;
	_Current_patch_side_count = 0;
	_Current_patch_initial_point = { };
	_Current_patch_index = static_cast<unsigned int>(_Patches.size()) - 1U;
	ec.clear();
}

void mesh_brush_factory::begin_replace_patch(unsigned int patch_num) {
	if (_Has_current_patch) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}

	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}

	_Has_current_patch = true;
	_Has_current_point = false;
	_Current_patch_side_count = 0;
	_Current_patch_initial_point = { };
	_Patch p;
	_Patches[patch_num] = p;
	_Current_patch_index = patch_num;
}

void mesh_brush_factory::begin_replace_patch(unsigned int patch_num, error_code& ec) noexcept {
	if (_Has_current_patch) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return;
	}

	if (patch_num >= _Patches.size()) {
		ec = make_error_code(CAIRO_STATUS_INVALID_INDEX);
		return;
	}
	_Patch p;
	_Patches[patch_num] = p;
	_Has_current_patch = true;
	_Has_current_point = false;
	_Current_patch_side_count = 0;
	_Current_patch_initial_point = { };
	_Current_patch_index = patch_num;
	ec.clear();
}

void mesh_brush_factory::end_patch() {
	if (!_Has_current_patch) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}
	if (_Current_patch_side_count < 4) {
		line_to(_Current_patch_initial_point);
	}
	_Has_current_patch = false;
	_Has_current_point = false;
}

void mesh_brush_factory::end_patch(error_code& ec) noexcept {
	if (!_Has_current_patch) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return;
	}
	if (_Current_patch_side_count < 4) {
		line_to(_Current_patch_initial_point, ec);
		if (static_cast<bool>(ec)) {
			return;
		}
	}
	_Has_current_patch = false;
	_Has_current_point = false;
	ec.clear();
}

void mesh_brush_factory::move_to(const point& pt) {
	if (!_Has_current_patch || _Current_patch_side_count > 0) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}
	auto& patch = _Patches.at(_Current_patch_index);
	_Current_patch_initial_point = pt;
	get<0>(patch).move_to(pt);
	_Has_current_point = true;
}

void mesh_brush_factory::move_to(const point& pt, error_code& ec) noexcept {
	if (!_Has_current_patch || _Current_patch_side_count > 0) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return;
	}
	try {
		auto& patch = _Patches.at(_Current_patch_index);
		_Current_patch_initial_point = pt;
		get<0>(patch).move_to(pt);
		_Has_current_point = true;
	}
	catch (const out_of_range&) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return;
	}
	ec.clear();
}

void mesh_brush_factory::line_to(const point& pt) {
	if (!_Has_current_patch || _Current_patch_side_count >= 4) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}

	if (!_Has_current_point) {
		move_to(pt);
	}
	else {
		auto& patch = _Patches.at(_Current_patch_index);
		get<0>(patch).line_to(pt);
		_Current_patch_side_count++;
	}
}

void mesh_brush_factory::line_to(const point& pt, error_code& ec) noexcept {
	if (!_Has_current_patch || _Current_patch_side_count >= 4) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return;
	}

	if (!_Has_current_point) {
		move_to(pt, ec);
		if (static_cast<bool>(ec)) {
			return;
		}
	}
	else {
		try {
			auto& patch = _Patches.at(_Current_patch_index);
			get<0>(patch).line_to(pt);
			_Current_patch_side_count++;
		}
		catch (const out_of_range&) {
			ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
			return;
		}
	}
	ec.clear();
}

void mesh_brush_factory::curve_to(const point& pt0, const point& pt1, const point& pt2) {
	if (!_Has_current_patch || _Current_patch_side_count >= 4) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}

	if (!_Has_current_point) {
		move_to(pt0);
	}

	_Current_patch_side_count++;
	auto& patch = _Patches.at(_Current_patch_index);
	get<0>(patch).curve_to(pt0, pt1, pt2);
}

void mesh_brush_factory::curve_to(const point& pt0, const point& pt1, const point& pt2, error_code& ec) noexcept {
	if (!_Has_current_patch || _Current_patch_side_count >= 4) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return;
	}

	if (!_Has_current_point) {
		move_to(pt0, ec);
		if (static_cast<bool>(ec)) {
			return;
		}
	}

	try {
		auto& patch = _Patches.at(_Current_patch_index);
		_Current_patch_side_count++;
		get<0>(patch).curve_to(pt0, pt1, pt2);
	}
	catch (const out_of_range&) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return;
	}
	ec.clear();
}

void mesh_brush_factory::control_point(unsigned int point_num, const point& pt) {
	if (!_Has_current_patch) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}
	if (point_num > 3) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	auto& patch = _Patches.at(_Current_patch_index);
	get<1>(patch)[point_num] = make_tuple(true, pt);
}

void mesh_brush_factory::control_point(unsigned int point_num, const point& pt, error_code& ec) noexcept {
	if (!_Has_current_patch) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return;
	}
	if (point_num > 3) {
		ec = make_error_code(CAIRO_STATUS_INVALID_INDEX);
		return;
	}

	try {
		auto& patch = _Patches.at(_Current_patch_index);
		get<1>(patch)[point_num] = make_tuple(true, pt);
	}
	catch (const out_of_range&) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return;
	}
	ec.clear();
}

void mesh_brush_factory::corner_color_rgba(unsigned int corner_num, const rgba_color& color) {
	if (!_Has_current_patch) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
	}
	if (corner_num > 3) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	auto& patch = _Patches.at(_Current_patch_index);
	get<2>(patch)[corner_num] = make_tuple(true, color);
}

void mesh_brush_factory::corner_color_rgba(unsigned int corner_num, const rgba_color& color, error_code& ec) noexcept {
	if (!_Has_current_patch) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return;
	}
	if (corner_num > 3) {
		ec = make_error_code(CAIRO_STATUS_INVALID_INDEX);
		return;
	}

	try {
		auto& patch = _Patches.at(_Current_patch_index);
		get<2>(patch)[corner_num] = make_tuple(true, color);
	}
	catch (const out_of_range&) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return;
	}
	ec.clear();
}

unsigned int mesh_brush_factory::patch_count() const noexcept {
	return static_cast<unsigned int>(_Patches.size());
}

path_factory mesh_brush_factory::path_factory(unsigned int patch_num) const {
	if (patch_num >= _Patches.size()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	const auto& patch = _Patches[patch_num];
	return get<0>(patch);
}

// Note: This and various other code relies on C++17's provision that the default vector ctor is noexcept (N4258, adopted 2014-11).
path_factory mesh_brush_factory::path_factory(unsigned int patch_num, error_code& ec) const noexcept {
	if (patch_num >= _Patches.size()) {
		ec = make_error_code(CAIRO_STATUS_INVALID_INDEX);
		return ::std::experimental::io2d::path_factory{};
	}
	try {
		const auto& patch = _Patches[patch_num];
		auto factory = get<0>(patch);
		ec.clear();
		return factory;
	}
	catch (const out_of_range&) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return ::std::experimental::io2d::path_factory{};
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return ::std::experimental::io2d::path_factory{};
	}
}

// Note: This returns a bool and uses an out parameter because it's valid to have a control point which has not been assigned a value.
bool mesh_brush_factory::control_point(unsigned int patch_num, unsigned int point_num, point& controlPoint) const {
	if (patch_num >= _Patches.size() || point_num > 3) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	const auto& patch = _Patches[patch_num];
	const auto& controlPoints = get<1>(patch);
	const auto& controlPointTuple = controlPoints[point_num];
	if (!get<0>(controlPointTuple)) {
		return false;
	}
	controlPoint = get<1>(controlPointTuple);
	return true;
}

// Note: This returns a bool and uses an out parameter because it's valid to have a control point which has not been assigned a value.
bool mesh_brush_factory::control_point(unsigned int patch_num, unsigned int point_num, point& controlPoint, error_code& ec) const noexcept {
	if (patch_num >= _Patches.size() || point_num > 3) {
		ec = make_error_code(CAIRO_STATUS_INVALID_INDEX);
		return false;
	}
	try {
		const auto& patch = _Patches[patch_num];
		const auto& controlPoints = get<1>(patch);
		const auto& controlPointTuple = controlPoints[point_num];
		if (!get<0>(controlPointTuple)) {
			ec.clear();
			return false;
		}
		controlPoint = get<1>(controlPointTuple);
		ec.clear();
		return true;
	}
	catch (const out_of_range&) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return false;
	}
}

// Note: This returns a bool and uses an out parameter because it's valid to have a corner which has not been assigned a color.
bool mesh_brush_factory::corner_color_rgba(unsigned int patch_num, unsigned int corner_num, rgba_color& color) const {
	if (patch_num >= _Patches.size() || corner_num > 3) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_INDEX);
	}
	const auto& patch = _Patches[patch_num];
	const auto& cornerColors = get<2>(patch);
	const auto& cornerColorTuple = cornerColors[corner_num];
	if (!get<0>(cornerColorTuple)) {
		return false;
	}
	color = get<1>(cornerColorTuple);
	return true;
}

// Note: This returns a bool and uses an out parameter because it's valid to have a corner which has not been assigned a color.
bool mesh_brush_factory::corner_color_rgba(unsigned int patch_num, unsigned int corner_num, rgba_color& color, error_code& ec) const noexcept {
	if (patch_num >= _Patches.size() || corner_num > 3) {
		ec = make_error_code(CAIRO_STATUS_INVALID_INDEX);
		return false;
	}
	try {
		const auto& patch = _Patches[patch_num];
		const auto& cornerColors = get<2>(patch);
		const auto& cornerColorTuple = cornerColors[corner_num];
		if (!get<0>(cornerColorTuple)) {
			ec.clear();
			return false;
		}
		color = get<1>(cornerColorTuple);
		ec.clear();
		return true;
	}
	catch (const out_of_range&) {
		ec = make_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
		return false;
	}
}
