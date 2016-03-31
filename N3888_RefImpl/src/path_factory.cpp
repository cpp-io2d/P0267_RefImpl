#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"
#include <algorithm>
#include <limits>

using namespace std;
using namespace std::experimental::io2d;

path_factory::path_factory(path_factory&& other) noexcept
	: _Data()
	, _Has_current_point()
	, _Current_point()
	, _Transform_matrix()
	, _Origin() {
	_Data = move(other._Data);
	_Has_current_point = move(other._Has_current_point);
	_Current_point = move(other._Current_point);
	_Last_move_to_point = move(other._Last_move_to_point);
	_Transform_matrix = move(other._Transform_matrix);
	_Origin = move(other._Origin);
}

path_factory& path_factory::operator=(path_factory&& other) noexcept {
	if (this != &other) {
		_Data = move(other._Data);
		_Has_current_point = move(other._Has_current_point);
		_Current_point = move(other._Current_point);
		_Last_move_to_point = move(other._Last_move_to_point);
		_Transform_matrix = move(other._Transform_matrix);
		_Origin = move(other._Origin);
	}
	return *this;
}

void path_factory::append(const path_factory& p) {
	for (const auto& item : p._Data) {
		_Data.push_back(item);
	}
	_Has_current_point = p._Has_current_point;
	_Current_point = p._Current_point;
	_Last_move_to_point = p._Last_move_to_point;
}

void path_factory::append(const path_factory& p, error_code& ec) noexcept {
	try {
		_Data.reserve(_Data.size() + p._Data.size());
	}
	catch (const length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	for (const auto& item : p._Data) {
		_Data.push_back(item);
	}
	_Has_current_point = p._Has_current_point;
	_Current_point = p._Current_point;
	_Last_move_to_point = p._Last_move_to_point;
	ec.clear();
}

void path_factory::append(const vector<path_data_item>& p) {
	// Validate data.
	matrix_2d transformMatrix = _Transform_matrix;
	vector_2d origin = _Origin;
	bool hasCurrentPoint = _Has_current_point;
	vector_2d currentPoint = _Current_point;
	// Used to establish the proper current point when a close_path is encountered.
	vector_2d lastMoveToPoint = _Last_move_to_point;

	for (const auto& item : p) {
		auto type = item.type();
		switch (type) {
		case std::experimental::io2d::path_data_type::move_to:
		{
			currentPoint = item.get<experimental::io2d::path_data_item::move_to>().to();
			hasCurrentPoint = true;
			lastMoveToPoint = currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::line_to:
		{
			currentPoint = item.get<experimental::io2d::path_data_item::line_to>().to();
			if (!hasCurrentPoint) {
				lastMoveToPoint = currentPoint;
				hasCurrentPoint = true;
			}
		} break;
		case std::experimental::io2d::path_data_type::curve_to:
		{
			auto dataItem = item.get<experimental::io2d::path_data_item::curve_to>();
			if (!hasCurrentPoint) {
				lastMoveToPoint = dataItem.control_point_1();
				hasCurrentPoint = true;
			}
			currentPoint = dataItem.end_point();
		} break;
		case std::experimental::io2d::path_data_type::new_sub_path:
		{
			hasCurrentPoint = false;
		} break;
		case std::experimental::io2d::path_data_type::close_path:
		{
			if (hasCurrentPoint) {
				currentPoint = lastMoveToPoint;
			}
		} break;
		case std::experimental::io2d::path_data_type::rel_move_to:
		{
			if (!hasCurrentPoint) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
			}
			currentPoint = item.get<experimental::io2d::path_data_item::rel_move_to>().to() + currentPoint;
			lastMoveToPoint = currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::rel_line_to:
		{
			if (!hasCurrentPoint) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
			}
			currentPoint = item.get<experimental::io2d::path_data_item::rel_line_to>().to() + currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::rel_curve_to:
		{
			if (!hasCurrentPoint) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
			}
			currentPoint = item.get<experimental::io2d::path_data_item::rel_curve_to>().end_point() + currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::arc:
		{
			auto dataItem = item.get<experimental::io2d::path_data_item::arc>();
			auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), false, hasCurrentPoint, currentPoint);
			if (data.size() > 0) {
				const auto& lastItem = *data.crbegin();
				if (lastItem.type() == path_data_type::curve_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::path_data_item::curve_to>().end_point();
				}
				else if (lastItem.type() == path_data_type::line_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::path_data_item::line_to>().to();
				}
				else if (lastItem.type() == path_data_type::move_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::path_data_item::move_to>().to();
					lastMoveToPoint = _Current_point;
				}
				else {
					assert("_Get_arc_as_beziers returned unexpected path_data value." && false);
				}
			}
		} break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			auto dataItem = item.get<experimental::io2d::path_data_item::arc_negative>();
			auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), true, hasCurrentPoint, currentPoint);
			if (data.size() > 0) {
				const auto& lastItem = *data.crbegin();
				if (lastItem.type() == path_data_type::curve_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::path_data_item::curve_to>().end_point();
				}
				else if (lastItem.type() == path_data_type::line_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::path_data_item::line_to>().to();
				}
				else if (lastItem.type() == path_data_type::move_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::path_data_item::move_to>().to();
					lastMoveToPoint = _Current_point;
				}
				else {
					assert("_Get_arc_as_beziers returned unexpected path_data value." && false);
				}
			}
		} break;
		case std::experimental::io2d::path_data_type::change_matrix:
		{
			transformMatrix = item.get<experimental::io2d::path_data_item::change_matrix>().matrix();
		} break;
		case std::experimental::io2d::path_data_type::change_origin:
		{
			origin = item.get<experimental::io2d::path_data_item::change_origin>().origin();
		} break;
		default:
		{
			assert(false && "Unknown path_data_type.");
		} break;
		}
	}

	_Data.reserve(_Data.size() + p.size());

	// Add items
	for (const auto& item : p) {
		_Data.push_back(item);
	}

	_Has_current_point = hasCurrentPoint;
	_Current_point = currentPoint;
	_Last_move_to_point = lastMoveToPoint;
	_Transform_matrix = transformMatrix;
	_Origin = origin;
}

void path_factory::append(const vector<path_data_item>& p, error_code& ec) noexcept {
	// Validate data.
	matrix_2d transformMatrix = _Transform_matrix;
	vector_2d origin = _Origin;
	bool hasCurrentPoint = _Has_current_point;
	vector_2d currentPoint = _Current_point;
	// Used to establish the proper current point when a close_path is encountered.
	vector_2d lastMoveToPoint = _Last_move_to_point;

	for (const auto& item : p) {
		auto type = item.type();
		switch (type) {
		case std::experimental::io2d::path_data_type::move_to:
		{
			currentPoint = item.get<experimental::io2d::path_data_item::move_to>().to();
			hasCurrentPoint = true;
			lastMoveToPoint = currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::line_to:
		{
			currentPoint = item.get<experimental::io2d::path_data_item::line_to>().to();
			if (!hasCurrentPoint) {
				lastMoveToPoint = currentPoint;
				hasCurrentPoint = true;
			}
		} break;
		case std::experimental::io2d::path_data_type::curve_to:
		{
			auto dataItem = item.get<experimental::io2d::path_data_item::curve_to>();
			if (!hasCurrentPoint) {
				lastMoveToPoint = dataItem.control_point_1();
				hasCurrentPoint = true;
			}
			currentPoint = dataItem.end_point();
		} break;
		case std::experimental::io2d::path_data_type::new_sub_path:
		{
			hasCurrentPoint = false;
		} break;
		case std::experimental::io2d::path_data_type::close_path:
		{
			if (hasCurrentPoint) {
				currentPoint = lastMoveToPoint;
			}
		} break;
		case std::experimental::io2d::path_data_type::rel_move_to:
		{
			if (!hasCurrentPoint) {
				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
				return;
			}
			currentPoint = item.get<experimental::io2d::path_data_item::rel_move_to>().to() + currentPoint;
			lastMoveToPoint = currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::rel_line_to:
		{
			if (!hasCurrentPoint) {
				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
				return;
			}
			currentPoint = item.get<experimental::io2d::path_data_item::rel_line_to>().to() + currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::rel_curve_to:
		{
			if (!hasCurrentPoint) {
				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
				return;
			}
			currentPoint = item.get<experimental::io2d::path_data_item::rel_curve_to>().end_point() + currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::arc:
		{
			auto dataItem = item.get<experimental::io2d::path_data_item::arc>();
			auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), ec, false, hasCurrentPoint, currentPoint);
			if (static_cast<bool>(ec)) {
				return;
			}
			if (data.size() > 0) {
				const auto& lastItem = *data.crbegin();
				if (lastItem.type() == path_data_type::curve_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::path_data_item::curve_to>().end_point();
				}
				else if (lastItem.type() == path_data_type::line_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::path_data_item::line_to>().to();
				}
				else if (lastItem.type() == path_data_type::move_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::path_data_item::move_to>().to();
					lastMoveToPoint = _Current_point;
				}
				else {
					assert("_Get_arc_as_beziers returned unexpected path_data value." && false);
				}
			}
		} break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			auto dataItem = item.get<experimental::io2d::path_data_item::arc_negative>();
			auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), ec, true, hasCurrentPoint, currentPoint);
			if (static_cast<bool>(ec)) {
				return;
			}
			if (data.size() > 0) {
				const auto& lastItem = *data.crbegin();
				if (lastItem.type() == path_data_type::curve_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::path_data_item::curve_to>().end_point();
				}
				else if (lastItem.type() == path_data_type::line_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::path_data_item::line_to>().to();
				}
				else if (lastItem.type() == path_data_type::move_to) {
					hasCurrentPoint = true;
					currentPoint = lastItem.get<experimental::io2d::path_data_item::move_to>().to();
					lastMoveToPoint = _Current_point;
				}
				else {
					assert("_Get_arc_as_beziers returned unexpected path_data value." && false);
				}
			}
		} break;
		case std::experimental::io2d::path_data_type::change_matrix:
		{
			transformMatrix = item.get<experimental::io2d::path_data_item::change_matrix>().matrix();
		} break;
		case std::experimental::io2d::path_data_type::change_origin:
		{
			origin = item.get<experimental::io2d::path_data_item::change_origin>().origin();
		} break;
		default:
		{
			assert(false && "Unknown path_data_type.");
		} break;
		}
	}

	try {
		_Data.reserve(_Data.size() + p.size());
	}
	catch (const length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}

	// Add items
	for (const auto& item : p) {
		_Data.push_back(item);
	}

	_Has_current_point = hasCurrentPoint;
	_Current_point = currentPoint;
	_Last_move_to_point = lastMoveToPoint;
	_Transform_matrix = transformMatrix;
	_Origin = origin;
	ec.clear();
}

bool path_factory::has_current_point() const noexcept {
	return _Has_current_point;
}

vector_2d path_factory::current_point() const {
	if (!_Has_current_point) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
	}
	return _Current_point;
}

vector_2d path_factory::current_point(error_code& ec) const noexcept {
	if (!_Has_current_point) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
		return vector_2d{ };
	}
	ec.clear();
	return _Current_point;
}

void path_factory::new_sub_path() {
	_Data.emplace_back(experimental::io2d::path_data_item::new_sub_path());
	_Has_current_point = false;
}

void path_factory::new_sub_path(error_code& ec) noexcept {
	try {
		_Data.emplace_back(experimental::io2d::path_data_item::new_sub_path());
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Has_current_point = false;
	ec.clear();
}

void path_factory::close_path() {
	if (_Has_current_point) {
		_Data.emplace_back(experimental::io2d::path_data_item::close_path());
		_Current_point = _Last_move_to_point;
	}
}

void path_factory::close_path(error_code& ec) noexcept {
	try {
		_Data.emplace_back(experimental::io2d::path_data_item::close_path());
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	if (_Has_current_point) {
		_Current_point = _Last_move_to_point;
	}
	ec.clear();
}

void path_factory::arc(const vector_2d& center, double radius, double angle1, double angle2) {
	_Data.emplace_back(std::experimental::io2d::path_data_item::arc(center, radius, angle1, angle2));
	// Update the current point.
	if (!_Has_current_point) {
		_Last_move_to_point = _Rotate_point_absolute_angle(center, radius, angle1);
		_Has_current_point = true;
	}
	_Current_point = _Rotate_point_absolute_angle(center, radius, angle2);
}

void path_factory::arc(const vector_2d& center, double radius, double angle1, double angle2, error_code& ec) noexcept {
	try {
		_Data.emplace_back(std::experimental::io2d::path_data_item::arc(center, radius, angle1, angle2));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}

	if (!_Has_current_point) {
		_Last_move_to_point = _Rotate_point_absolute_angle(center, radius, angle1);
	}
	_Current_point = _Rotate_point_absolute_angle(center, radius, angle2);

	ec.clear();
}

void path_factory::arc_negative(const vector_2d& center, double radius, double angle1, double angle2) {
	_Data.emplace_back(std::experimental::io2d::path_data_item::arc_negative(center, radius, angle1, angle2));
	// Update the current point.
	if (!_Has_current_point) {
		_Last_move_to_point = _Rotate_point_absolute_angle(center, radius, angle1, false);
	}
	_Current_point = _Rotate_point_absolute_angle(center, radius, angle2, false);
}

void path_factory::arc_negative(const vector_2d& center, double radius, double angle1, double angle2, error_code& ec) noexcept {
	try {
		_Data.emplace_back(std::experimental::io2d::path_data_item::arc_negative(center, radius, angle1, angle2));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}

	// Update the current point.
	if (!_Has_current_point) {
		_Last_move_to_point = _Rotate_point_absolute_angle(center, radius, angle1, false);
	}
	_Current_point = _Rotate_point_absolute_angle(center, radius, angle2, false);

	ec.clear();
}

void path_factory::curve_to(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2) {
	if (!_Has_current_point) {
		_Data.reserve(_Data.size() + 2U);
		move_to(pt0);
	}
	_Data.emplace_back(std::experimental::io2d::path_data_item::curve_to(pt0, pt1, pt2));
	_Has_current_point = true;
	_Current_point = pt2;
}

void path_factory::curve_to(const vector_2d& pt0, const vector_2d& pt1, const vector_2d& pt2, error_code& ec) noexcept {
	if (!_Has_current_point) {
		try {
			_Data.reserve(_Data.size() + 2U);
		}
		catch (const length_error&) {
			ec = make_error_code(errc::not_enough_memory);
			return;
		}
		catch (const bad_alloc&) {
			ec = make_error_code(errc::not_enough_memory);
			return;
		}
		move_to(pt0, ec);
		if (static_cast<bool>(ec)) {
			return;
		}
	}
	try {
		_Data.emplace_back(std::experimental::io2d::path_data_item::curve_to(pt0, pt1, pt2));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Has_current_point = true;
	_Current_point = pt2;
	ec.clear();
}

void path_factory::line_to(const vector_2d& pt) {
	_Data.emplace_back(std::experimental::io2d::path_data_item::line_to(pt));
	if (!_Has_current_point) {
		_Last_move_to_point = pt;
		_Has_current_point = true;
	}
	_Current_point = pt;
}

void path_factory::line_to(const vector_2d& pt, error_code& ec) noexcept {
	try {
		_Data.emplace_back(std::experimental::io2d::path_data_item::line_to(pt));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	if (!_Has_current_point) {
		_Last_move_to_point = pt;
		_Has_current_point = true;
	}
	_Current_point = pt;
	ec.clear();
}

void path_factory::move_to(const vector_2d& pt) {
	_Data.emplace_back(std::experimental::io2d::path_data_item::move_to(pt));
	_Has_current_point = true;
	_Current_point = pt;
}

void path_factory::move_to(const vector_2d& pt, error_code& ec) noexcept {
	try {
		_Data.emplace_back(std::experimental::io2d::path_data_item::move_to(pt));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Has_current_point = true;
	_Current_point = pt;
	ec.clear();
}

void path_factory::rectangle(const experimental::io2d::rectangle& r, bool cw) {
	_Data.reserve(_Data.size() + 5U);

	if (cw) {
		// Create a clockwise winding order rectangle.
		move_to({ r.x(), r.y() });
		rel_line_to({ r.width(), 0.0 });
		rel_line_to({ 0.0, r.height() });
		rel_line_to({ -r.width(), 0.0 });
		close_path();
	}
	else {
		// Create a counterclockwise winding order rectangle.
		move_to({ r.x(), r.y() });
		rel_line_to({ 0.0, r.height() });
		rel_line_to({ r.width(), 0.0 });
		rel_line_to({ 0.0, -r.height() });
		close_path();
	}
}

void path_factory::rectangle(const experimental::io2d::rectangle& r, error_code& ec, bool cw) noexcept {
	try {
		_Data.reserve(_Data.size() + 5U);
	}
	catch (const length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}

	if (cw) {
		// Create a clockwise winding order rectangle.
		assert(!static_cast<bool>(ec));
		// We already reserved space for these so there should be no errors, hence the asserts to check for violations of that assumption.
		move_to({ r.x(), r.y() }, ec);
		assert(!static_cast<bool>(ec));
		rel_line_to({ r.width(), 0.0 }, ec);
		assert(!static_cast<bool>(ec));
		rel_line_to({ 0.0, r.height() }, ec);
		assert(!static_cast<bool>(ec));
		rel_line_to({ -r.width(), 0.0 }, ec);
		assert(!static_cast<bool>(ec));
		close_path(ec);
		assert(!static_cast<bool>(ec));
		ec.clear();
	}
	else {
		// Create a counterclockwise winding order rectangle.
		assert(!static_cast<bool>(ec));
		// We already reserved space for these so there should be no errors, hence the asserts to check for violations of that assumption.
		move_to({ r.x(), r.y() }, ec);
		assert(!static_cast<bool>(ec));
		rel_line_to({ 0.0, r.height() }, ec);
		assert(!static_cast<bool>(ec));
		rel_line_to({ r.width(), 0.0 }, ec);
		assert(!static_cast<bool>(ec));
		rel_line_to({ 0.0, -r.height() }, ec);
		assert(!static_cast<bool>(ec));
		close_path(ec);
		assert(!static_cast<bool>(ec));
		ec.clear();
	}
}

void path_factory::rel_curve_to(const vector_2d& dpt0, const vector_2d& dpt1, const vector_2d& dpt2) {
	if (!_Has_current_point) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
	}
	_Data.emplace_back(std::experimental::io2d::path_data_item::rel_curve_to(dpt0, dpt1, dpt2));
	_Has_current_point = true;
	_Current_point = _Current_point + dpt2;
}

void path_factory::rel_curve_to(const vector_2d& dpt0, const vector_2d& dpt1, const vector_2d& dpt2, error_code& ec) noexcept {
	if (!_Has_current_point) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
		return;
	}
	try {
		_Data.emplace_back(std::experimental::io2d::path_data_item::rel_curve_to(dpt0, dpt1, dpt2));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Has_current_point = true;
	_Current_point = _Current_point + dpt2;
	ec.clear();
}

void path_factory::rel_line_to(const vector_2d& dpt) {
	if (!_Has_current_point) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
	}
	_Data.emplace_back(std::experimental::io2d::path_data_item::rel_line_to(dpt));
	_Has_current_point = true;
	_Current_point = _Current_point + dpt;
}

void path_factory::rel_line_to(const vector_2d& dpt, error_code& ec) noexcept {
	if (!_Has_current_point) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
		return;
	}
	try {
		_Data.emplace_back(std::experimental::io2d::path_data_item::rel_line_to(dpt));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
	}
	_Has_current_point = true;
	_Current_point = _Current_point + dpt;
	ec.clear();
}

void path_factory::rel_move_to(const vector_2d& dpt) {
	if (!_Has_current_point) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
	}
	_Data.emplace_back(std::experimental::io2d::path_data_item::rel_move_to(dpt));
	_Has_current_point = true;
	_Current_point = _Current_point + dpt;
}

void path_factory::rel_move_to(const vector_2d& dpt, error_code& ec) noexcept {
	if (!_Has_current_point) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
		return;
	}
	try {
		_Data.emplace_back(std::experimental::io2d::path_data_item::rel_move_to(dpt));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Has_current_point = true;
	_Current_point = _Current_point + dpt;
	ec.clear();
}

void path_factory::change_matrix(const matrix_2d& m) {
	_Data.emplace_back(std::experimental::io2d::path_data_item::change_matrix(m));
	_Transform_matrix = m;
}

void path_factory::change_matrix(const matrix_2d& m, error_code& ec) noexcept {
	try {
		_Data.emplace_back(std::experimental::io2d::path_data_item::change_matrix(m));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Transform_matrix = m;
	ec.clear();
}

matrix_2d path_factory::current_matrix() const noexcept {
	return _Transform_matrix;
}

void path_factory::change_origin(const vector_2d& pt) {
	_Data.emplace_back(std::experimental::io2d::path_data_item::change_origin(pt));
	_Origin = pt;
}

void path_factory::change_origin(const vector_2d& pt, error_code& ec) noexcept {
	try {
		_Data.emplace_back(std::experimental::io2d::path_data_item::change_origin(pt));
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	_Origin = pt;
	ec.clear();
}

vector_2d path_factory::current_origin() const noexcept {
	return _Origin;
}

vector<path_data_item> path_factory::data() const {
	vector<path_data_item> result;
	for (const auto& item : _Data) {
		result.push_back(item);
	}
	return result;
}

vector<path_data_item> path_factory::data(error_code& ec) const noexcept {
	vector<path_data_item> result;
	try {
		result.reserve(_Data.size());
	}
	catch (const length_error&) {
		ec = make_error_code(errc::not_enough_memory);
		// Relies on C++17 noexcept guarantee for vector default ctor (N4258, adopted 2014-11).
		return vector<path_data_item>();
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		// Relies on C++17 noexcept guarantee for vector default ctor (N4258, adopted 2014-11).
		return vector<path_data_item>();
	}
	for (const auto& item : _Data) {
		result.push_back(item);
	}
	ec.clear();
	return result;
}

path_data_item path_factory::data_item(unsigned int index) const {
	return _Data.at(index);
}

path_data_item path_factory::data_item(unsigned int index, error_code& ec) const noexcept {
	try {
		return _Data.at(index);
	}
	catch (const out_of_range&) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_INDEX);
		return path_data_item{ };
	}
}

const vector<path_data_item>& path_factory::data_ref() const noexcept {
	return _Data;
}

::std::experimental::io2d::rectangle path_factory::path_extents() const {
	//
	// The code in this function should be fixed now. Needs testing.
	//

	vector_2d pt0;
	vector_2d pt1;

	matrix_2d currMatrix = matrix_2d::init_identity();
	vector_2d currOrigin;

	bool hasCurrentPoint = false;
	bool hasExtents = false;

	vector_2d lastMoveToPoint;
	vector_2d transformedCurrentPoint;
	vector_2d currentPoint;

	// pt0 will hold min values; pt1 will hold max values.
	for (auto i = 0U; i < _Data.size(); i++) {
		const auto& item = _Data[i];
		auto type = item.type();
		switch (type)
		{
		case std::experimental::io2d::path_data_type::move_to:
		{
			currentPoint = item.get<experimental::io2d::path_data_item::move_to>().to();
			lastMoveToPoint = currentPoint;
			transformedCurrentPoint = currMatrix.transform_point(currentPoint - currOrigin) + currOrigin;
			hasCurrentPoint = true;
		} break;
		case std::experimental::io2d::path_data_type::line_to:
		{
			currentPoint = item.get<experimental::io2d::path_data_item::line_to>().to();
			auto itemPt = currMatrix.transform_point(currentPoint - currOrigin) + currOrigin;
			if (!hasCurrentPoint) {
				transformedCurrentPoint = itemPt;
				lastMoveToPoint = currentPoint;
				hasCurrentPoint = true;
			}
			else {
				// Path extents include lines (even degenerate ones).
				if (!hasExtents) {
					hasExtents = true;
					pt0.x(min(transformedCurrentPoint.x(), itemPt.x()));
					pt0.y(min(transformedCurrentPoint.y(), itemPt.y()));
					pt1.x(max(transformedCurrentPoint.x(), itemPt.x()));
					pt1.y(max(transformedCurrentPoint.y(), itemPt.y()));
				}
				else {
					pt0.x(min(min(pt0.x(), transformedCurrentPoint.x()), itemPt.x()));
					pt0.y(min(min(pt0.y(), transformedCurrentPoint.y()), itemPt.y()));
					pt1.x(max(max(pt1.x(), transformedCurrentPoint.x()), itemPt.x()));
					pt1.y(max(max(pt1.y(), transformedCurrentPoint.y()), itemPt.y()));
				}
				transformedCurrentPoint = itemPt;
			}
		} break;
		case std::experimental::io2d::path_data_type::curve_to:
		{
			vector_2d cte0{ };
			vector_2d cte1{ };
			auto dataItem = item.get<experimental::io2d::path_data_item::curve_to>();
			auto itemPt1 = currMatrix.transform_point(dataItem.control_point_1() - currOrigin) + currOrigin;
			auto itemPt2 = currMatrix.transform_point(dataItem.control_point_2() - currOrigin) + currOrigin;
			auto itemPt3 = currMatrix.transform_point(dataItem.end_point() - currOrigin) + currOrigin;
			if (!hasCurrentPoint) {
				currentPoint = dataItem.control_point_1();
				lastMoveToPoint = currentPoint;
				transformedCurrentPoint = itemPt1;
				hasCurrentPoint = true;
			}
			_Curve_to_extents(transformedCurrentPoint, itemPt1, itemPt2, itemPt3, cte0, cte1);
			if (!hasExtents) {
				hasExtents = true;
				pt0.x(min(cte0.x(), cte1.x()));
				pt0.y(min(cte0.y(), cte1.y()));
				pt1.x(max(cte0.x(), cte1.x()));
				pt1.y(max(cte0.y(), cte1.y()));
			}
			else {
				pt0.x(min(min(pt0.x(), cte0.x()), cte1.x()));
				pt0.y(min(min(pt0.y(), cte0.y()), cte1.y()));
				pt1.x(max(max(pt1.x(), cte0.x()), cte1.x()));
				pt1.y(max(max(pt1.y(), cte0.y()), cte1.y()));
			}
			transformedCurrentPoint = itemPt3;
			currentPoint = dataItem.end_point();
		}
		break;
		case std::experimental::io2d::path_data_type::new_sub_path:
			hasCurrentPoint = false;
			break;
		case std::experimental::io2d::path_data_type::close_path:
			// Close path cannot change the path extents since it either does nothing or it adds a line from an existing point to an existing point.
			if (hasCurrentPoint) {
				auto inverseMatrix = matrix_2d(currMatrix).invert();
				currentPoint = inverseMatrix.transform_point(lastMoveToPoint - currOrigin) + currOrigin;
				transformedCurrentPoint = currMatrix.transform_point(currentPoint - currOrigin) + currOrigin;
				lastMoveToPoint = currentPoint;
			}
			break;
		case std::experimental::io2d::path_data_type::rel_move_to:
			assert(hasCurrentPoint);
			currentPoint = item.get<experimental::io2d::path_data_item::rel_move_to>().to() + currentPoint;
			lastMoveToPoint = currentPoint;
			transformedCurrentPoint = currMatrix.transform_point(currentPoint - currOrigin) + currOrigin;
			break;
		case std::experimental::io2d::path_data_type::rel_line_to:
		{
			assert(hasCurrentPoint);
			auto itemPt = currMatrix.transform_point((item.get<experimental::io2d::path_data_item::rel_line_to>().to() + currentPoint) - currOrigin) + currOrigin;
			if (!hasExtents) {
				hasExtents = true;
				pt0.x(min(transformedCurrentPoint.x(), itemPt.x()));
				pt0.y(min(transformedCurrentPoint.y(), itemPt.y()));
				pt1.x(max(transformedCurrentPoint.x(), itemPt.x()));
				pt1.y(max(transformedCurrentPoint.y(), itemPt.y()));
			}
			else {
				pt0.x(min(min(pt0.x(), transformedCurrentPoint.x()), itemPt.x()));
				pt0.y(min(min(pt0.y(), transformedCurrentPoint.y()), itemPt.y()));
				pt1.x(max(max(pt1.x(), transformedCurrentPoint.x()), itemPt.x()));
				pt1.y(max(max(pt1.y(), transformedCurrentPoint.y()), itemPt.y()));
			}
			currentPoint = item.get<experimental::io2d::path_data_item::rel_line_to>().to() + currentPoint;
			transformedCurrentPoint = itemPt;
		} break;
		case std::experimental::io2d::path_data_type::rel_curve_to:
		{
			assert(hasCurrentPoint);
			vector_2d cte0{ };
			vector_2d cte1{ };
			auto dataItem = item.get<experimental::io2d::path_data_item::rel_curve_to>();
			auto itemPt1 = currMatrix.transform_point((dataItem.control_point_1() + currentPoint) - currOrigin) + currOrigin;
			auto itemPt2 = currMatrix.transform_point((dataItem.control_point_2() + currentPoint) - currOrigin) + currOrigin;
			auto itemPt3 = currMatrix.transform_point((dataItem.end_point() + currentPoint) - currOrigin) + currOrigin;
			_Curve_to_extents(currentPoint, itemPt1, itemPt2, itemPt3, cte0, cte1);
			if (!hasExtents) {
				hasExtents = true;
				pt0.x(min(cte0.x(), cte1.x()));
				pt0.y(min(cte0.y(), cte1.y()));
				pt1.x(max(cte0.x(), cte1.x()));
				pt1.y(max(cte0.y(), cte1.y()));
			}
			else {
				pt0.x(min(min(pt0.x(), cte0.x()), cte1.x()));
				pt0.y(min(min(pt0.y(), cte0.y()), cte1.y()));
				pt1.x(max(max(pt1.x(), cte0.x()), cte1.x()));
				pt1.y(max(max(pt1.y(), cte0.y()), cte1.y()));
			}
			currentPoint = dataItem.end_point() + currentPoint;
			transformedCurrentPoint = itemPt3;
		}
		break;
		case std::experimental::io2d::path_data_type::arc:
		{
			auto dataItem = item.get<experimental::io2d::path_data_item::arc>();
			_Get_arc_extents(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), false, hasCurrentPoint, currentPoint, transformedCurrentPoint, lastMoveToPoint, hasExtents, pt0, pt1, currOrigin, currMatrix);
		} break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			auto dataItem = item.get<experimental::io2d::path_data_item::arc_negative>();
			_Get_arc_extents(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), true, hasCurrentPoint, currentPoint, transformedCurrentPoint, lastMoveToPoint, hasExtents, pt0, pt1, currOrigin, currMatrix);
		} break;
		case std::experimental::io2d::path_data_type::change_matrix:
		{
			currMatrix = item.get<experimental::io2d::path_data_item::change_matrix>().matrix();
		} break;
		case std::experimental::io2d::path_data_type::change_origin:
		{
			currOrigin = item.get<experimental::io2d::path_data_item::change_origin>().origin();
		} break;
		default:
		{
			assert("Unknown path_data_type in path_data." && false);
		} break;
		}
	}
	return{ pt0.x(), pt0.y(), pt1.x() - pt0.x(), pt1.y() - pt0.y() };
}

void path_factory::clear() noexcept {
	_Data.clear();
	_Has_current_point = false;
	_Current_point = { };
	_Transform_matrix = matrix_2d::init_identity();
	_Origin = { };
}

void path_factory::add_text(const font_resource& fr, const string& utf8, const vector_2d& pt) {
	auto gr = fr.make_glyph_run(utf8, pt);
	auto ext = gr.extents();
	double w = ext.width();
	double h = ext.height();
	cairo_matrix_t cm{};
	cairo_matrix_init_translate(&cm, -(pt.x() + ext.x_bearing()), -(pt.y() + ext.y_bearing()));
	unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> upimgSfc(
		cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _Double_to_int(w + 0.5), _Double_to_int(h + 0.5)), &cairo_surface_destroy
		);
	unique_ptr<cairo_t, decltype(&cairo_destroy)> upctxt(cairo_create(upimgSfc.get()), &cairo_destroy);
	cairo_set_matrix(upctxt.get(), &cm);
	cairo_new_path(upctxt.get());
	cairo_set_scaled_font(upctxt.get(), fr._Scaled_font.get());
	cairo_glyph_path(upctxt.get(), gr._Cairo_glyphs.get(), static_cast<int>(gr.glyphs().size()));
	unique_ptr<cairo_path_t, decltype(&cairo_path_destroy)> uppth(cairo_copy_path(upctxt.get()), &cairo_path_destroy);
	append(_Cairo_path_data_t_array_to_path_data_item_vector(*(uppth.get())));
}

void path_factory::add_glyph_run(const font_resource& fr, const glyph_run& gr) {
	auto ext = gr.extents();
	double w = ext.width();
	double h = ext.height();
	cairo_matrix_t cm{};
	cairo_matrix_init_translate(&cm, -(gr.position().x() + ext.x_bearing()), -(gr.position().y() + ext.y_bearing()));
	unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> upimgSfc(
		cairo_image_surface_create(CAIRO_FORMAT_ARGB32, _Double_to_int(w + 0.5), _Double_to_int(h + 0.5)), &cairo_surface_destroy
		);
	unique_ptr<cairo_t, decltype(&cairo_destroy)> upctxt(cairo_create(upimgSfc.get()), &cairo_destroy);
	cairo_set_matrix(upctxt.get(), &cm);
	cairo_new_path(upctxt.get());
	cairo_set_scaled_font(upctxt.get(), fr._Scaled_font.get());
	cairo_glyph_path(upctxt.get(), gr._Cairo_glyphs.get(), static_cast<int>(gr.glyphs().size()));
	unique_ptr<cairo_path_t, decltype(&cairo_path_destroy)> uppth(cairo_copy_path(upctxt.get()), &cairo_path_destroy);
	append(_Cairo_path_data_t_array_to_path_data_item_vector(*(uppth.get())));
}
