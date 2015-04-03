#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

void _Free_manual_cairo_path(cairo_path_t* path) noexcept;
void _Free_manual_cairo_path(cairo_path_t* path) noexcept {
	if (path != nullptr) {
		if (path->data != nullptr) {
			delete[] path->data;
			path->data = nullptr;
			path->status = CAIRO_STATUS_NULL_POINTER;
		}
		delete path;
		path = nullptr;
	}
}

path::native_handle_type path::native_handle() const noexcept {
	return _Cairo_path.get();
}

path::path(const path_factory& pb, const surface& /*sf*/)
: _Data(new vector<path_data_item>)
, _Cairo_path(new cairo_path_t, &_Free_manual_cairo_path)
, _Has_current_point()
, _Current_point()
, _Extents() {
	auto matrix = matrix_2d::init_identity();
	point origin{ };
	bool hasCurrentPoint = false;
	// Untransformed because we use it to add to raw relative points for transformation.
	point currentPoint{ };
	// Transformed because we need to know where the transformed last move to point is when we receive a close path instruction and the matrix and origin may have since changed such that we wouldn't be able to calculate it correctly anymore.
	point lastMoveToPoint{ };
	const auto& pathData = pb.data_ref();
	auto pdSize = pathData.size();
	vector<cairo_path_data_t> vec;
	for (unsigned int i = 0; i < pdSize; i++) {
		const auto& item = pathData[i];
		cairo_path_data_t cpdItem{ };
		auto pdt = item.type();
		switch (pdt) {
		case std::experimental::io2d::path_data_type::move_to:
		{
			currentPoint = item.get<move_to>().to();
			auto pt = matrix.transform_point(currentPoint - origin) + origin;
			cpdItem.header.type = CAIRO_PATH_MOVE_TO;
			cpdItem.header.length = 2;
			vec.push_back(cpdItem);
			cpdItem = { };
			cpdItem.point = { pt.x(), pt.y() };
			vec.push_back(cpdItem);
			hasCurrentPoint = true;
			lastMoveToPoint = pt;
		} break;
		case std::experimental::io2d::path_data_type::line_to:
		{
			currentPoint = item.get<line_to>().to();
			auto pt = matrix.transform_point(currentPoint - origin) + origin;
			if (hasCurrentPoint) {
				cpdItem.header.type = CAIRO_PATH_LINE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt.x(), pt.y() };
				vec.push_back(cpdItem);
			}
			else {
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt.x(), pt.y() };
				vec.push_back(cpdItem);
				hasCurrentPoint = true;
				lastMoveToPoint = pt;
			}
		} break;
		case std::experimental::io2d::path_data_type::curve_to:
		{
			auto dataItem = item.get<curve_to>();
			auto pt1 = matrix.transform_point(dataItem.control_point_1() - origin) + origin;
			auto pt2 = matrix.transform_point(dataItem.control_point_2() - origin) + origin;
			auto pt3 = matrix.transform_point(dataItem.end_point() - origin) + origin;
			if (!hasCurrentPoint) {
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt1.x(), pt1.y() };
				vec.push_back(cpdItem);
				currentPoint = dataItem.control_point_1();
				lastMoveToPoint = pt1;
				hasCurrentPoint = true;
			}
			cpdItem.header.type = CAIRO_PATH_CURVE_TO;
			cpdItem.header.length = 4;
			vec.push_back(cpdItem);
			cpdItem = { };
			cpdItem.point = { pt1.x(), pt1.y() };
			vec.push_back(cpdItem);
			cpdItem = { };
			cpdItem.point = { pt2.x(), pt2.y() };
			vec.push_back(cpdItem);
			cpdItem = { };
			cpdItem.point = { pt3.x(), pt3.y() };
			vec.push_back(cpdItem);
			currentPoint = dataItem.end_point();
		} break;
		case std::experimental::io2d::path_data_type::new_sub_path:
		{
			hasCurrentPoint = false;
		} break;
		case std::experimental::io2d::path_data_type::close_path:
		{
			if (hasCurrentPoint) {
				cpdItem.header.type = CAIRO_PATH_CLOSE_PATH;
				cpdItem.header.length = 1;
				vec.push_back(cpdItem);
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { lastMoveToPoint.x(), lastMoveToPoint.y() };
				vec.push_back(cpdItem);
				// Calculate the untransformed current point from the transformed lastMoveToPoint.
				auto inverseMatrix = matrix_2d(matrix).invert();
				currentPoint = inverseMatrix.transform_point(lastMoveToPoint - origin) + origin;
			}
		} break;
		case std::experimental::io2d::path_data_type::rel_move_to:
		{
			if (!hasCurrentPoint) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
			}
			currentPoint = item.get<rel_move_to>().to() + currentPoint;
			auto pt = matrix.transform_point(currentPoint - origin) + origin;
			cpdItem.header.type = CAIRO_PATH_MOVE_TO;
			cpdItem.header.length = 2;
			vec.push_back(cpdItem);
			cpdItem = { };
			cpdItem.point = { pt.x(), pt.y() };
			vec.push_back(cpdItem);
			hasCurrentPoint = true;
			lastMoveToPoint = pt;
		} break;
		case std::experimental::io2d::path_data_type::rel_line_to:
		{
			if (!hasCurrentPoint) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
			}
			currentPoint = item.get<rel_line_to>().to() + currentPoint;
			auto pt = matrix.transform_point(currentPoint - origin) + origin;
			cpdItem.header.type = CAIRO_PATH_LINE_TO;
			cpdItem.header.length = 2;
			vec.push_back(cpdItem);
			cpdItem = { };
			cpdItem.point = { pt.x(), pt.y() };
			vec.push_back(cpdItem);
		} break;
		case std::experimental::io2d::path_data_type::rel_curve_to:
		{
			if (!hasCurrentPoint) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
			}
			auto existingCurrentPoint = currentPoint;
			auto dataItem = item.get<rel_curve_to>();
			auto pt1 = matrix.transform_point(dataItem.control_point_1() + existingCurrentPoint - origin) + origin;
			auto pt2 = matrix.transform_point(dataItem.control_point_2() + existingCurrentPoint - origin) + origin;
			auto pt3 = matrix.transform_point(dataItem.end_point() + existingCurrentPoint - origin) + origin;
			if (!hasCurrentPoint) {
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt1.x(), pt1.y() };
				vec.push_back(cpdItem);
				currentPoint = dataItem.control_point_1() + existingCurrentPoint;
				lastMoveToPoint = pt1;
				hasCurrentPoint = true;
			}
			cpdItem.header.type = CAIRO_PATH_CURVE_TO;
			cpdItem.header.length = 4;
			vec.push_back(cpdItem);
			cpdItem = { };
			cpdItem.point = { pt1.x(), pt1.y() };
			vec.push_back(cpdItem);
			cpdItem = { };
			cpdItem.point = { pt2.x(), pt2.y() };
			vec.push_back(cpdItem);
			cpdItem = { };
			cpdItem.point = { pt3.x(), pt3.y() };
			vec.push_back(cpdItem);
			currentPoint = dataItem.end_point() + existingCurrentPoint;
		} break;
		case std::experimental::io2d::path_data_type::arc:
		{
			auto dataItem = item.get<arc>();
			auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), false, hasCurrentPoint, currentPoint, origin, matrix);
			for (const auto& arcItem : data) {
				switch (arcItem.type()) {
				case std::experimental::io2d::path_data_type::move_to:
				{
					currentPoint = arcItem.get<move_to>().to();
					auto pt = matrix.transform_point(currentPoint - origin) + origin;
					cpdItem.header.type = CAIRO_PATH_MOVE_TO;
					cpdItem.header.length = 2;
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { pt.x(), pt.y() };
					vec.push_back(cpdItem);
					hasCurrentPoint = true;
					lastMoveToPoint = pt;
				} break;
				case std::experimental::io2d::path_data_type::line_to:
				{
					currentPoint = arcItem.get<line_to>().to();
					auto pt = matrix.transform_point(currentPoint - origin) + origin;
					if (hasCurrentPoint) {
						cpdItem.header.type = CAIRO_PATH_LINE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt.x(), pt.y() };
						vec.push_back(cpdItem);
					}
					else {
						cpdItem.header.type = CAIRO_PATH_MOVE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt.x(), pt.y() };
						vec.push_back(cpdItem);
						hasCurrentPoint = true;
						lastMoveToPoint = pt;
					}
				} break;
				case std::experimental::io2d::path_data_type::curve_to:
				{
					auto curveItem = arcItem.get<curve_to>();
					auto pt1 = matrix.transform_point(curveItem.control_point_1() - origin) + origin;
					auto pt2 = matrix.transform_point(curveItem.control_point_2() - origin) + origin;
					auto pt3 = matrix.transform_point(curveItem.end_point() - origin) + origin;
					if (!hasCurrentPoint) {
						cpdItem.header.type = CAIRO_PATH_MOVE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt1.x(), pt1.y() };
						vec.push_back(cpdItem);
						currentPoint = curveItem.control_point_1();
						lastMoveToPoint = pt1;
						hasCurrentPoint = true;
					}
					cpdItem.header.type = CAIRO_PATH_CURVE_TO;
					cpdItem.header.length = 4;
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { pt1.x(), pt1.y() };
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { pt2.x(), pt2.y() };
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { pt3.x(), pt3.y() };
					vec.push_back(cpdItem);
					currentPoint = curveItem.end_point();
				} break;
				case path_data_type::new_sub_path:
				{
					assert("Unexpected value path_data_type::new_sub_path." && false);
				} break;
				case path_data_type::close_path:
				{
					assert("Unexpected value path_data_type::close_path." && false);
				} break;
				case path_data_type::rel_move_to:
				{
					assert("Unexpected value path_data_type::rel_move_to." && false);
				} break;
				case path_data_type::rel_line_to:
				{
					assert("Unexpected value path_data_type::rel_line_to." && false);
				} break;
				case path_data_type::rel_curve_to:
				{
					assert("Unexpected value path_data_type::rel_curve_to." && false);
				} break;
				case path_data_type::arc:
				{
					assert("Unexpected value path_data_type::arc." && false);
				} break;
				case path_data_type::arc_negative:
				{
					assert("Unexpected value path_data_type::arc_negative." && false);
				} break;
				case path_data_type::change_origin:
				{
					// Ignore, it's just spitting out the value we handed it.
				} break;
				case path_data_type::change_matrix:
				{
					// Ignore, it's just spitting out the value we handed it.
				} break;
				default:
					assert("Unexpected path_data_type in arc." && false);
					break;
				}
			}
			currentPoint = _Rotate_point_absolute_angle(dataItem.center(), dataItem.radius(), dataItem.angle_2(), true);
			hasCurrentPoint = true;
		}
		break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			auto dataItem = item.get<arc_negative>();
			auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), true, hasCurrentPoint, currentPoint, origin, matrix);
			for (const auto& arcItem : data) {
				switch (arcItem.type()) {
				case std::experimental::io2d::path_data_type::move_to:
				{
					currentPoint = arcItem.get<move_to>().to();
					auto pt = matrix.transform_point(currentPoint - origin) + origin;
					cpdItem.header.type = CAIRO_PATH_MOVE_TO;
					cpdItem.header.length = 2;
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { pt.x(), pt.y() };
					vec.push_back(cpdItem);
					hasCurrentPoint = true;
					lastMoveToPoint = pt;
				} break;
				case std::experimental::io2d::path_data_type::line_to:
				{
					currentPoint = arcItem.get<line_to>().to();
					auto pt = matrix.transform_point(currentPoint - origin) + origin;
					if (hasCurrentPoint) {
						cpdItem.header.type = CAIRO_PATH_LINE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt.x(), pt.y() };
						vec.push_back(cpdItem);
					}
					else {
						cpdItem.header.type = CAIRO_PATH_MOVE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt.x(), pt.y() };
						vec.push_back(cpdItem);
						hasCurrentPoint = true;
						lastMoveToPoint = pt;
					}
				} break;
				case std::experimental::io2d::path_data_type::curve_to:
				{
					auto curveItem = arcItem.get<curve_to>();
					auto pt1 = matrix.transform_point(curveItem.control_point_1() - origin) + origin;
					auto pt2 = matrix.transform_point(curveItem.control_point_2() - origin) + origin;
					auto pt3 = matrix.transform_point(curveItem.end_point() - origin) + origin;
					if (!hasCurrentPoint) {
						cpdItem.header.type = CAIRO_PATH_MOVE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt1.x(), pt1.y() };
						vec.push_back(cpdItem);
						currentPoint = curveItem.control_point_1();
						lastMoveToPoint = pt1;
						hasCurrentPoint = true;
					}
					cpdItem.header.type = CAIRO_PATH_CURVE_TO;
					cpdItem.header.length = 4;
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { pt1.x(), pt1.y() };
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { pt2.x(), pt2.y() };
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { pt3.x(), pt3.y() };
					vec.push_back(cpdItem);
					currentPoint = curveItem.end_point();
				} break;
				case path_data_type::new_sub_path:
				{
					assert("Unexpected value path_data_type::new_sub_path." && false);
				} break;
				case path_data_type::close_path:
				{
					assert("Unexpected value path_data_type::close_path." && false);
				} break;
				case path_data_type::rel_move_to:
				{
					assert("Unexpected value path_data_type::rel_move_to." && false);
				} break;
				case path_data_type::rel_line_to:
				{
					assert("Unexpected value path_data_type::rel_line_to." && false);
				} break;
				case path_data_type::rel_curve_to:
				{
					assert("Unexpected value path_data_type::rel_curve_to." && false);
				} break;
				case path_data_type::arc:
				{
					assert("Unexpected value path_data_type::arc." && false);
				} break;
				case path_data_type::arc_negative:
				{
					assert("Unexpected value path_data_type::arc_negative." && false);
				} break;
				case path_data_type::change_origin:
				{
					// Ignore, it's just spitting out the value we handed it.
				} break;
				case path_data_type::change_matrix:
				{
					// Ignore, it's just spitting out the value we handed it.
				} break;
				default:
					assert("Unexpected path_data_type in arc." && false);
					break;
				}
			}
			currentPoint = _Rotate_point_absolute_angle(dataItem.center(), dataItem.radius(), dataItem.angle_2());
			hasCurrentPoint = true;
		}
		break;
		case std::experimental::io2d::path_data_type::change_matrix:
		{
			matrix = item.get<change_matrix>().matrix();
		} break;
		case std::experimental::io2d::path_data_type::change_origin:
		{
			origin = item.get<change_origin>().origin();
		} break;
		default:
		{
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
		} break;
		}
	}

	_Cairo_path->num_data = static_cast<int>(vec.size());
	const auto numDataST = vec.size();
	_Cairo_path->data = new cairo_path_data_t[numDataST];
	for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
		_Cairo_path->data[currItemIndex] = vec[currItemIndex];
	}
	_Cairo_path->status = CAIRO_STATUS_SUCCESS;

	for (const auto& item : pb.data_ref()) {
		_Data->push_back(item);
	}

	_Has_current_point = pb._Has_current_point;
	_Current_point = pb._Current_point;
	_Last_move_to_point = pb._Last_move_to_point;
	_Extents = pb.path_extents();
}

path::path(const path_factory& pb, const surface& /*sf*/, error_code& ec) noexcept
	: _Data()
	, _Cairo_path()
	, _Has_current_point()
	, _Current_point()
	, _Extents() {
	try {
		_Data = make_shared<vector<path_data_item>>();
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	auto p_cairoPath = new (nothrow) cairo_path_t;
	if (p_cairoPath == nullptr) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}
	try {
		_Cairo_path = shared_ptr<cairo_path_t>(p_cairoPath, &_Free_manual_cairo_path);
	}
	catch (const exception& ex) {
		assert(ex.what());
		ec = make_error_code(io2d_error::invalid_status);
		return;
	}
	auto matrix = matrix_2d::init_identity();
	point origin{ };
	bool hasCurrentPoint = false;
	// Untransformed because we use it to add to raw relative points for transformation.
	point currentPoint{ };
	// Transformed because we need to know where the transformed last move to point is when we receive a close path instruction and the matrix and origin may have since changed such that we wouldn't be able to calculate it correctly anymore.
	point lastMoveToPoint{ };
	const auto& pathData = pb.data_ref();
	auto pdSize = pathData.size();
	try {
		vector<cairo_path_data_t> vec;
		for (unsigned int i = 0; i < pdSize; i++) {
			const auto& item = pathData[i];
			cairo_path_data_t cpdItem{ };
			auto pdt = item.type();
			switch (pdt) {
			case std::experimental::io2d::path_data_type::move_to:
			{
				currentPoint = item.get<move_to>().to();
				auto pt = matrix.transform_point(currentPoint - origin) + origin;
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt.x(), pt.y() };
				vec.push_back(cpdItem);
				hasCurrentPoint = true;
				lastMoveToPoint = pt;
			} break;
			case std::experimental::io2d::path_data_type::line_to:
			{
				currentPoint = item.get<line_to>().to();
				auto pt = matrix.transform_point(currentPoint - origin) + origin;
				if (hasCurrentPoint) {
					cpdItem.header.type = CAIRO_PATH_LINE_TO;
					cpdItem.header.length = 2;
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { pt.x(), pt.y() };
					vec.push_back(cpdItem);
				}
				else {
					cpdItem.header.type = CAIRO_PATH_MOVE_TO;
					cpdItem.header.length = 2;
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { pt.x(), pt.y() };
					vec.push_back(cpdItem);
					hasCurrentPoint = true;
					lastMoveToPoint = pt;
				}
			} break;
			case std::experimental::io2d::path_data_type::curve_to:
			{
				auto dataItem = item.get<curve_to>();
				auto pt1 = matrix.transform_point(dataItem.control_point_1() - origin) + origin;
				auto pt2 = matrix.transform_point(dataItem.control_point_2() - origin) + origin;
				auto pt3 = matrix.transform_point(dataItem.end_point() - origin) + origin;
				if (!hasCurrentPoint) {
					cpdItem.header.type = CAIRO_PATH_MOVE_TO;
					cpdItem.header.length = 2;
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { pt1.x(), pt1.y() };
					vec.push_back(cpdItem);
					currentPoint = dataItem.control_point_1();
					lastMoveToPoint = pt1;
					hasCurrentPoint = true;
				}
				cpdItem.header.type = CAIRO_PATH_CURVE_TO;
				cpdItem.header.length = 4;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt1.x(), pt1.y() };
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt2.x(), pt2.y() };
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt3.x(), pt3.y() };
				vec.push_back(cpdItem);
				currentPoint = dataItem.end_point();
			} break;
			case std::experimental::io2d::path_data_type::new_sub_path:
			{
				hasCurrentPoint = false;
			} break;
			case std::experimental::io2d::path_data_type::close_path:
			{
				if (hasCurrentPoint) {
					cpdItem.header.type = CAIRO_PATH_CLOSE_PATH;
					cpdItem.header.length = 1;
					vec.push_back(cpdItem);
					cpdItem.header.type = CAIRO_PATH_MOVE_TO;
					cpdItem.header.length = 2;
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { lastMoveToPoint.x(), lastMoveToPoint.y() };
					vec.push_back(cpdItem);
					// Calculate the untransformed current point from the transformed lastMoveToPoint.
					auto inverseMatrix = matrix_2d(matrix).invert();
					currentPoint = inverseMatrix.transform_point(lastMoveToPoint - origin) + origin;
				}
			} break;
			case std::experimental::io2d::path_data_type::rel_move_to:
			{
				if (!hasCurrentPoint) {
					_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
				}
				currentPoint = item.get<rel_move_to>().to() + currentPoint;
				auto pt = matrix.transform_point(currentPoint - origin) + origin;
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt.x(), pt.y() };
				vec.push_back(cpdItem);
				hasCurrentPoint = true;
				lastMoveToPoint = pt;
			} break;
			case std::experimental::io2d::path_data_type::rel_line_to:
			{
				if (!hasCurrentPoint) {
					_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
				}
				currentPoint = item.get<rel_line_to>().to() + currentPoint;
				auto pt = matrix.transform_point(currentPoint - origin) + origin;
				if (hasCurrentPoint) {
					cpdItem.header.type = CAIRO_PATH_LINE_TO;
					cpdItem.header.length = 2;
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { pt.x(), pt.y() };
					vec.push_back(cpdItem);
				}
				else {
					cpdItem.header.type = CAIRO_PATH_MOVE_TO;
					cpdItem.header.length = 2;
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { pt.x(), pt.y() };
					vec.push_back(cpdItem);
					hasCurrentPoint = true;
					lastMoveToPoint = pt;
				}
			} break;
			case std::experimental::io2d::path_data_type::rel_curve_to:
			{
				if (!hasCurrentPoint) {
					_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
				}
				auto existingCurrentPoint = currentPoint;
				auto dataItem = item.get<rel_curve_to>();
				auto pt1 = matrix.transform_point(dataItem.control_point_1() + existingCurrentPoint - origin) + origin;
				auto pt2 = matrix.transform_point(dataItem.control_point_2() + existingCurrentPoint - origin) + origin;
				auto pt3 = matrix.transform_point(dataItem.end_point() + existingCurrentPoint - origin) + origin;
				if (!hasCurrentPoint) {
					cpdItem.header.type = CAIRO_PATH_MOVE_TO;
					cpdItem.header.length = 2;
					vec.push_back(cpdItem);
					cpdItem = { };
					cpdItem.point = { pt1.x(), pt1.y() };
					vec.push_back(cpdItem);
					currentPoint = dataItem.control_point_1() + existingCurrentPoint;
					lastMoveToPoint = pt1;
					hasCurrentPoint = true;
				}
				cpdItem.header.type = CAIRO_PATH_CURVE_TO;
				cpdItem.header.length = 4;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt1.x(), pt1.y() };
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt2.x(), pt2.y() };
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt3.x(), pt3.y() };
				vec.push_back(cpdItem);
				currentPoint = dataItem.end_point() + existingCurrentPoint;
			} break;
			case std::experimental::io2d::path_data_type::arc:
			{
				auto dataItem = item.get<arc>();
				auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), false, hasCurrentPoint, currentPoint, origin, matrix);
				for (const auto& arcItem : data) {
					switch (arcItem.type()) {
					case std::experimental::io2d::path_data_type::move_to:
					{
						currentPoint = arcItem.get<move_to>().to();
						auto pt = matrix.transform_point(currentPoint - origin) + origin;
						cpdItem.header.type = CAIRO_PATH_MOVE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt.x(), pt.y() };
						vec.push_back(cpdItem);
						hasCurrentPoint = true;
						lastMoveToPoint = pt;
					} break;
					case std::experimental::io2d::path_data_type::line_to:
					{
						currentPoint = arcItem.get<line_to>().to();
						auto pt = matrix.transform_point(currentPoint - origin) + origin;
						if (hasCurrentPoint) {
							cpdItem.header.type = CAIRO_PATH_LINE_TO;
							cpdItem.header.length = 2;
							vec.push_back(cpdItem);
							cpdItem = { };
							cpdItem.point = { pt.x(), pt.y() };
							vec.push_back(cpdItem);
						}
						else {
							cpdItem.header.type = CAIRO_PATH_MOVE_TO;
							cpdItem.header.length = 2;
							vec.push_back(cpdItem);
							cpdItem = { };
							cpdItem.point = { pt.x(), pt.y() };
							vec.push_back(cpdItem);
							hasCurrentPoint = true;
							lastMoveToPoint = pt;
						}
					} break;
					case std::experimental::io2d::path_data_type::curve_to:
					{
						auto curveItem = arcItem.get<curve_to>();
						auto pt1 = matrix.transform_point(curveItem.control_point_1() - origin) + origin;
						auto pt2 = matrix.transform_point(curveItem.control_point_2() - origin) + origin;
						auto pt3 = matrix.transform_point(curveItem.end_point() - origin) + origin;
						if (!hasCurrentPoint) {
							cpdItem.header.type = CAIRO_PATH_MOVE_TO;
							cpdItem.header.length = 2;
							vec.push_back(cpdItem);
							cpdItem = { };
							cpdItem.point = { pt1.x(), pt1.y() };
							vec.push_back(cpdItem);
							currentPoint = curveItem.control_point_1();
							lastMoveToPoint = pt1;
							hasCurrentPoint = true;
						}
						cpdItem.header.type = CAIRO_PATH_CURVE_TO;
						cpdItem.header.length = 4;
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt1.x(), pt1.y() };
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt2.x(), pt2.y() };
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt3.x(), pt3.y() };
						vec.push_back(cpdItem);
						currentPoint = curveItem.end_point();
					} break;
					case path_data_type::new_sub_path:
					{
						assert("Unexpected value path_data_type::new_sub_path." && false);
					} break;
					case path_data_type::close_path:
					{
						assert("Unexpected value path_data_type::close_path." && false);
					} break;
					case path_data_type::rel_move_to:
					{
						assert("Unexpected value path_data_type::rel_move_to." && false);
					} break;
					case path_data_type::rel_line_to:
					{
						assert("Unexpected value path_data_type::rel_line_to." && false);
					} break;
					case path_data_type::rel_curve_to:
					{
						assert("Unexpected value path_data_type::rel_curve_to." && false);
					} break;
					case path_data_type::arc:
					{
						assert("Unexpected value path_data_type::arc." && false);
					} break;
					case path_data_type::arc_negative:
					{
						assert("Unexpected value path_data_type::arc_negative." && false);
					} break;
					case path_data_type::change_origin:
					{
						// Ignore, it's just spitting out the value we handed it.
					} break;
					case path_data_type::change_matrix:
					{
						// Ignore, it's just spitting out the value we handed it.
					} break;
					default:
						assert("Unexpected path_data_type in arc." && false);
						break;
					}
				}
				currentPoint = _Rotate_point_absolute_angle(dataItem.center(), dataItem.radius(), dataItem.angle_2(), true);
				hasCurrentPoint = true;
			}
			break;
			case std::experimental::io2d::path_data_type::arc_negative:
			{
				auto dataItem = item.get<arc_negative>();
				auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), true, hasCurrentPoint, currentPoint, origin, matrix);
				for (const auto& arcItem : data) {
					switch (arcItem.type()) {
					case std::experimental::io2d::path_data_type::move_to:
					{
						currentPoint = arcItem.get<move_to>().to();
						auto pt = matrix.transform_point(currentPoint - origin) + origin;
						cpdItem.header.type = CAIRO_PATH_MOVE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt.x(), pt.y() };
						vec.push_back(cpdItem);
						hasCurrentPoint = true;
						lastMoveToPoint = pt;
					} break;
					case std::experimental::io2d::path_data_type::line_to:
					{
						currentPoint = arcItem.get<line_to>().to();
						auto pt = matrix.transform_point(currentPoint - origin) + origin;
						if (hasCurrentPoint) {
							cpdItem.header.type = CAIRO_PATH_LINE_TO;
							cpdItem.header.length = 2;
							vec.push_back(cpdItem);
							cpdItem = { };
							cpdItem.point = { pt.x(), pt.y() };
							vec.push_back(cpdItem);
						}
						else {
							cpdItem.header.type = CAIRO_PATH_MOVE_TO;
							cpdItem.header.length = 2;
							vec.push_back(cpdItem);
							cpdItem = { };
							cpdItem.point = { pt.x(), pt.y() };
							vec.push_back(cpdItem);
							hasCurrentPoint = true;
							lastMoveToPoint = pt;
						}
					} break;
					case std::experimental::io2d::path_data_type::curve_to:
					{
						auto curveItem = arcItem.get<curve_to>();
						auto pt1 = matrix.transform_point(curveItem.control_point_1() - origin) + origin;
						auto pt2 = matrix.transform_point(curveItem.control_point_2() - origin) + origin;
						auto pt3 = matrix.transform_point(curveItem.end_point() - origin) + origin;
						if (!hasCurrentPoint) {
							cpdItem.header.type = CAIRO_PATH_MOVE_TO;
							cpdItem.header.length = 2;
							vec.push_back(cpdItem);
							cpdItem = { };
							cpdItem.point = { pt1.x(), pt1.y() };
							vec.push_back(cpdItem);
							currentPoint = curveItem.control_point_1();
							lastMoveToPoint = pt1;
							hasCurrentPoint = true;
						}
						cpdItem.header.type = CAIRO_PATH_CURVE_TO;
						cpdItem.header.length = 4;
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt1.x(), pt1.y() };
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt2.x(), pt2.y() };
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt3.x(), pt3.y() };
						vec.push_back(cpdItem);
						currentPoint = curveItem.end_point();
					} break;
					case path_data_type::new_sub_path:
					{
						assert("Unexpected value path_data_type::new_sub_path." && false);
					} break;
					case path_data_type::close_path:
					{
						assert("Unexpected value path_data_type::close_path." && false);
					} break;
					case path_data_type::rel_move_to:
					{
						assert("Unexpected value path_data_type::rel_move_to." && false);
					} break;
					case path_data_type::rel_line_to:
					{
						assert("Unexpected value path_data_type::rel_line_to." && false);
					} break;
					case path_data_type::rel_curve_to:
					{
						assert("Unexpected value path_data_type::rel_curve_to." && false);
					} break;
					case path_data_type::arc:
					{
						assert("Unexpected value path_data_type::arc." && false);
					} break;
					case path_data_type::arc_negative:
					{
						assert("Unexpected value path_data_type::arc_negative." && false);
					} break;
					case path_data_type::change_origin:
					{
						// Ignore, it's just spitting out the value we handed it.
					} break;
					case path_data_type::change_matrix:
					{
						// Ignore, it's just spitting out the value we handed it.
					} break;
					default:
						assert("Unexpected path_data_type in arc." && false);
						break;
					}
				}
				currentPoint = _Rotate_point_absolute_angle(dataItem.center(), dataItem.radius(), dataItem.angle_2());
				hasCurrentPoint = true;
			}
			break;
			case std::experimental::io2d::path_data_type::change_matrix:
			{
				matrix = item.get<change_matrix>().matrix();
			} break;
			case std::experimental::io2d::path_data_type::change_origin:
			{
				origin = item.get<change_origin>().origin();
			} break;
			default:
			{
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
			} break;
			}
		}

		_Cairo_path->num_data = static_cast<int>(vec.size());
		const auto numDataST = vec.size();
		_Cairo_path->data = new cairo_path_data_t[numDataST];
		for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
			_Cairo_path->data[currItemIndex] = vec[currItemIndex];
		}
		_Cairo_path->status = CAIRO_STATUS_SUCCESS;

		for (const auto& item : pb.data_ref()) {
			_Data->push_back(item);
		}
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		_Data.reset();
		_Cairo_path.reset();
		return;
	}
	_Has_current_point = pb._Has_current_point;
	_Current_point = pb._Current_point;
	_Last_move_to_point = pb._Last_move_to_point;
	_Extents = pb.path_extents();
	ec.clear();
}

path::path(path&& other) noexcept
	: _Data(move(other._Data))
	, _Cairo_path(move(other._Cairo_path))
	, _Has_current_point(move(other._Has_current_point))
	, _Current_point(move(other._Current_point))
	, _Last_move_to_point(move(other._Last_move_to_point))
	, _Extents(move(other._Extents)) {
}

path& path::operator=(path&& other) noexcept {
	if (this != &other) {
		_Data = move(other._Data);
		_Cairo_path = move(other._Cairo_path);
		_Has_current_point = move(other._Has_current_point);
		_Current_point = move(other._Current_point);
		_Last_move_to_point = move(other._Last_move_to_point);
		_Extents = move(other._Extents);
	}
	return *this;
}

vector<path_data_item> path::data() const {
	vector<path_data_item> result;
	for (const auto& item : *_Data) {
		result.push_back(item);
	}
	return result;
}

vector<path_data_item> path::data(error_code& ec) const noexcept {
	// Relies on C++17 noexcept default ctor.
	vector<path_data_item> result;
	try {
		for (const auto& item : *_Data) {
			result.push_back(item);
		}
		ec.clear();
		return result;
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return result;
	}
}

const vector<path_data_item>& path::data_ref() const noexcept {
	return *_Data;
}

rectangle path::path_extents() const noexcept {
	return _Extents;
}
