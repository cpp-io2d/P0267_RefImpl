#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

void _Free_manual_cairo_path(cairo_path_t* path) {
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

path::native_handle_type path::native_handle() const {
	return _Cairo_path.get();
}

path::path(const path_factory& pb, const surface& /*sf*/)
	: _Data(new vector<unique_ptr<path_data>>)
	, _Cairo_path(new cairo_path_t, &_Free_manual_cairo_path)
	, _Has_current_point()
	, _Current_point()
	, _Extents() {
	lock_guard<recursive_mutex> lg(pb._Lock);
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
		auto pdt = item->type();
		switch (pdt) {
		case std::experimental::io2d::path_data_type::move_to:
		{
			currentPoint = dynamic_cast<move_to*>(item.get())->to();
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
			currentPoint = dynamic_cast<line_to*>(item.get())->to();
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
			auto dataItem = dynamic_cast<curve_to*>(item.get());
			auto pt1 = matrix.transform_point(dataItem->control_point_1() - origin) + origin;
			auto pt2 = matrix.transform_point(dataItem->control_point_2() - origin) + origin;
			auto pt3 = matrix.transform_point(dataItem->end_point() - origin) + origin;
			if (!hasCurrentPoint) {
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt1.x(), pt1.y() };
				vec.push_back(cpdItem);
				currentPoint = dataItem->control_point_1();
				lastMoveToPoint = pt3;
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
			currentPoint = dataItem->end_point();
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
			currentPoint = dynamic_cast<rel_move_to*>(item.get())->to() + currentPoint;
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
			currentPoint = dynamic_cast<rel_line_to*>(item.get())->to() + currentPoint;
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
			auto dataItem = dynamic_cast<rel_curve_to*>(item.get());
			auto pt1 = matrix.transform_point(dataItem->control_point_1() + existingCurrentPoint - origin) + origin;
			auto pt2 = matrix.transform_point(dataItem->control_point_2() + existingCurrentPoint - origin) + origin;
			auto pt3 = matrix.transform_point(dataItem->end_point() + existingCurrentPoint - origin) + origin;
			if (!hasCurrentPoint) {
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt1.x(), pt1.y() };
				vec.push_back(cpdItem);
				currentPoint = dataItem->control_point_1() + existingCurrentPoint;
				lastMoveToPoint = pt3;
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
			currentPoint = dataItem->end_point() + existingCurrentPoint;
		} break;
		case std::experimental::io2d::path_data_type::arc:
		{
			auto dataItem = dynamic_cast<arc*>(item.get());
			auto data = _Get_arc_as_beziers(dataItem->center(), dataItem->radius(), dataItem->angle_1(), dataItem->angle_2(), false, hasCurrentPoint, currentPoint, origin, matrix);
			for (const auto& arcItem : data) {
				switch (arcItem->type()) {
				case std::experimental::io2d::path_data_type::move_to:
				{
					currentPoint = dynamic_cast<move_to*>(arcItem.get())->to();
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
					currentPoint = dynamic_cast<line_to*>(arcItem.get())->to();
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
					auto dataItem = dynamic_cast<curve_to*>(arcItem.get());
					auto pt1 = matrix.transform_point(dataItem->control_point_1() - origin) + origin;
					auto pt2 = matrix.transform_point(dataItem->control_point_2() - origin) + origin;
					auto pt3 = matrix.transform_point(dataItem->end_point() - origin) + origin;
					if (!hasCurrentPoint) {
						cpdItem.header.type = CAIRO_PATH_MOVE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt1.x(), pt1.y() };
						vec.push_back(cpdItem);
						currentPoint = dataItem->control_point_1();
						lastMoveToPoint = pt3;
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
					currentPoint = dataItem->end_point();
				} break;
				case path_data_type::change_origin:
				{
					// Ignore, it's just spitting out the value we handed it.
				} break;
				case path_data_type::change_matrix:
				{
					// Ignore, it's just spitting out the value we handed it.
				} break;
				case path_data_type::new_sub_path:
				{
					hasCurrentPoint = false;
				} break;
				default:
					assert("Unexpected path_data_type in arc." && false);
					break;
				}
			}
			currentPoint = _Rotate_point_absolute_angle(dataItem->center(), dataItem->radius(), dataItem->angle_2(), true);
			hasCurrentPoint = true;
		}
		break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			auto dataItem = dynamic_cast<arc_negative*>(item.get());
			auto data = _Get_arc_as_beziers(dataItem->center(), dataItem->radius(), dataItem->angle_1(), dataItem->angle_2(), true, hasCurrentPoint, currentPoint, origin, matrix);
			for (const auto& arcItem : data) {
				switch (arcItem->type()) {
				case std::experimental::io2d::path_data_type::move_to:
				{
					currentPoint = dynamic_cast<move_to*>(arcItem.get())->to();
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
					currentPoint = dynamic_cast<line_to*>(arcItem.get())->to();
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
					auto dataItem = dynamic_cast<curve_to*>(arcItem.get());
					auto pt1 = matrix.transform_point(dataItem->control_point_1() - origin) + origin;
					auto pt2 = matrix.transform_point(dataItem->control_point_2() - origin) + origin;
					auto pt3 = matrix.transform_point(dataItem->end_point() - origin) + origin;
					if (!hasCurrentPoint) {
						cpdItem.header.type = CAIRO_PATH_MOVE_TO;
						cpdItem.header.length = 2;
						vec.push_back(cpdItem);
						cpdItem = { };
						cpdItem.point = { pt1.x(), pt1.y() };
						vec.push_back(cpdItem);
						currentPoint = dataItem->control_point_1();
						lastMoveToPoint = pt3;
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
					currentPoint = dataItem->end_point();
				} break;
				case path_data_type::change_origin:
				{
					// Ignore, it's just spitting out the value we handed it.
				} break;
				case path_data_type::change_matrix:
				{
					// Ignore, it's just spitting out the value we handed it.
				} break;
				case path_data_type::new_sub_path:
				{
					hasCurrentPoint = false;
				} break;
				default:
					assert("Unexpected path_data_type in arc." && false);
					break;
				}
			}
			currentPoint = _Rotate_point_absolute_angle(dataItem->center(), dataItem->radius(), dataItem->angle_2());
			hasCurrentPoint = true;
		}
		break;
		case std::experimental::io2d::path_data_type::change_matrix:
		{
			matrix = dynamic_cast<change_matrix*>(item.get())->matrix();
		} break;
		case std::experimental::io2d::path_data_type::change_origin:
		{
			origin = dynamic_cast<change_origin*>(item.get())->origin();
		} break;
		default:
		{
			_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_PATH_DATA);
		} break;
		}
	}

	_Cairo_path->num_data = static_cast<int>(vec.size());
	_Cairo_path->data = new cairo_path_data_t[static_cast<::std::size_t>(_Cairo_path->num_data)];
	for (auto currItemIndex = 0; currItemIndex < _Cairo_path->num_data; currItemIndex++) {
		_Cairo_path->data[currItemIndex] = vec[currItemIndex];
	}
	_Cairo_path->status = CAIRO_STATUS_SUCCESS;

	for (const auto& item : pb.data_ref()) {
		auto type = item->type();
		switch (type) {
		case std::experimental::io2d::path_data_type::move_to:
		{
			auto dataItem = dynamic_cast<move_to*>(item.get());
			_Data->push_back(make_unique<move_to>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::line_to:
		{
			auto dataItem = dynamic_cast<line_to*>(item.get());
			_Data->push_back(make_unique<line_to>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::curve_to:
		{
			auto dataItem = dynamic_cast<curve_to*>(item.get());
			_Data->push_back(make_unique<curve_to>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::new_sub_path:
		{
			auto dataItem = dynamic_cast<new_sub_path*>(item.get());
			_Data->push_back(make_unique<new_sub_path>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::close_path:
		{
			auto dataItem = dynamic_cast<close_path*>(item.get());
			_Data->push_back(make_unique<close_path>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::rel_move_to:
		{
			auto dataItem = dynamic_cast<rel_move_to*>(item.get());
			_Data->push_back(make_unique<rel_move_to>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::rel_line_to:
		{
			auto dataItem = dynamic_cast<rel_line_to*>(item.get());
			_Data->push_back(make_unique<rel_line_to>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::rel_curve_to:
		{
			auto dataItem = dynamic_cast<rel_curve_to*>(item.get());
			_Data->push_back(make_unique<rel_curve_to>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::arc:
		{
			auto dataItem = dynamic_cast<arc*>(item.get());
			_Data->push_back(make_unique<arc>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			auto dataItem = dynamic_cast<arc_negative*>(item.get());
			_Data->push_back(make_unique<arc_negative>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::change_matrix:
		{
			auto dataItem = dynamic_cast<change_matrix*>(item.get());
			_Data->push_back(make_unique<change_matrix>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::change_origin:
		{
			auto dataItem = dynamic_cast<change_origin*>(item.get());
			_Data->push_back(make_unique<change_origin>(*dataItem));
		} break;
		default:
			assert("Unknown path_data_type" && false);
			break;
		}
	}
	_Has_current_point = pb._Has_current_point;
	_Current_point = pb._Current_point;
	_Last_move_to_point = pb._Last_move_to_point;
	_Extents = pb.path_extents();
}

path::path(path&& other)
	: _Data(move(other._Data))
	, _Cairo_path(move(other._Cairo_path))
	, _Has_current_point(move(other._Has_current_point))
	, _Current_point(move(other._Current_point))
	, _Last_move_to_point(move(other._Last_move_to_point))
	, _Extents(move(other._Extents)) {
}

path& path::operator=(path&& other) {
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

vector<unique_ptr<path_data>> path::data() const {
	vector<unique_ptr<path_data>> result;
	for (const auto& item : *_Data) {
		auto type = item->type();
		switch (type) {
		case std::experimental::io2d::path_data_type::move_to:
		{
			auto dataItem = dynamic_cast<move_to*>(item.get());
			result.push_back(make_unique<move_to>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::line_to:
		{
			auto dataItem = dynamic_cast<line_to*>(item.get());
			result.push_back(make_unique<line_to>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::curve_to:
		{
			auto dataItem = dynamic_cast<curve_to*>(item.get());
			result.push_back(make_unique<curve_to>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::new_sub_path:
		{
			auto dataItem = dynamic_cast<new_sub_path*>(item.get());
			result.push_back(make_unique<new_sub_path>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::close_path:
		{
			auto dataItem = dynamic_cast<close_path*>(item.get());
			result.push_back(make_unique<close_path>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::rel_move_to:
		{
			auto dataItem = dynamic_cast<rel_move_to*>(item.get());
			result.push_back(make_unique<rel_move_to>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::rel_line_to:
		{
			auto dataItem = dynamic_cast<rel_line_to*>(item.get());
			result.push_back(make_unique<rel_line_to>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::rel_curve_to:
		{
			auto dataItem = dynamic_cast<rel_curve_to*>(item.get());
			result.push_back(make_unique<rel_curve_to>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::arc:
		{
			auto dataItem = dynamic_cast<arc*>(item.get());
			result.push_back(make_unique<arc>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			auto dataItem = dynamic_cast<arc_negative*>(item.get());
			result.push_back(make_unique<arc_negative>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::change_matrix:
		{
			auto dataItem = dynamic_cast<change_matrix*>(item.get());
			result.push_back(make_unique<change_matrix>(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::change_origin:
		{
			auto dataItem = dynamic_cast<change_origin*>(item.get());
			result.push_back(make_unique<change_origin>(*dataItem));
		} break;
		default:
			assert("Unknown path_data_type" && false);
			break;
		}
	}
	return result;
}

const vector<unique_ptr<path_data>>& path::data_ref() const {
	return *_Data;
}

rectangle path::path_extents() const {
	return _Extents;
}
