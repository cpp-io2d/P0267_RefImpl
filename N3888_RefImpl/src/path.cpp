#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

//path_group::native_handle_type path_group::native_handle() const noexcept {
//	return _Cairo_path.get();
//}
//
//path_group::path_group(const path_factory& pb)
//: path_group(pb.data_ref()) {
//}
//

	//
	//path_group::path_group(const path_factory& pb, error_code& ec) noexcept
	//	: path_group(pb.data_ref(), ec) {
	//}

	//path_group::path_group(const vector<path_data_item>& pathData, error_code& ec) noexcept
	//	: _Data()
	//	, _Cairo_path() {
	//	try {
	//		_Data = make_shared<vector<path_data_item>>();
	//	}
	//	catch (const bad_alloc&) {
	//		ec = make_error_code(errc::not_enough_memory);
	//		return;
	//	}
	//	auto p_cairoPath = new (nothrow) cairo_path_t;
	//	if (p_cairoPath == nullptr) {
	//		ec = make_error_code(errc::not_enough_memory);
	//		return;
	//	}
	//	try {
	//		_Cairo_path = shared_ptr<cairo_path_t>(p_cairoPath, &_Free_manual_cairo_path);
	//		p_cairoPath = nullptr;
	//	}
	//	catch (const exception& ex) {
	//		// The constructor we use ensures that our custom deleter is called on p_cairoPath in the event of an exception.
	//		assert(ex.what());
	//		ec = make_error_code(io2d_error::invalid_status);
	//		return;
	//	}
	//	auto matrix = matrix_2d::init_identity();
	//	vector_2d origin{ };
	//	bool hasCurrentPoint = false;
	//	// Untransformed because we use it to add to raw relative points for transformation.
	//	vector_2d currentPoint{ };
	//	// Transformed because we need to know where the transformed last move to point is when we receive a close path_group instruction and the matrix and origin may have since changed such that we wouldn't be able to calculate it correctly anymore.
	//	vector_2d lastMoveToPoint{ };
	//	auto pdSize = pathData.size();
	//	try {
	//		vector<cairo_path_data_t> vec;
	//		for (unsigned int i = 0; i < pdSize; i++) {
	//			const auto& item = pathData[i];
	//			cairo_path_data_t cpdItem{ };
	//			auto pdt = item.type();
	//			switch (pdt) {
	//			case std::experimental::io2d::path_data_type::path_abs_move:
	//			{
	//				currentPoint = item.get<path_abs_move>().to();
	//				auto pt = matrix.transform_point(currentPoint - origin) + origin;
	//				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
	//				cpdItem.header.length = 2;
	//				vec.push_back(cpdItem);
	//				cpdItem = { };
	//				cpdItem.point = { pt.x(), pt.y() };
	//				vec.push_back(cpdItem);
	//				hasCurrentPoint = true;
	//				lastMoveToPoint = pt;
	//			} break;
	//			case std::experimental::io2d::path_data_type::path_abs_line:
	//			{
	//				currentPoint = item.get<path_abs_line>().to();
	//				auto pt = matrix.transform_point(currentPoint - origin) + origin;
	//				if (hasCurrentPoint) {
	//					cpdItem.header.type = CAIRO_PATH_LINE_TO;
	//					cpdItem.header.length = 2;
	//					vec.push_back(cpdItem);
	//					cpdItem = { };
	//					cpdItem.point = { pt.x(), pt.y() };
	//					vec.push_back(cpdItem);
	//				}
	//				else {
	//					cpdItem.header.type = CAIRO_PATH_MOVE_TO;
	//					cpdItem.header.length = 2;
	//					vec.push_back(cpdItem);
	//					cpdItem = { };
	//					cpdItem.point = { pt.x(), pt.y() };
	//					vec.push_back(cpdItem);
	//					hasCurrentPoint = true;
	//					lastMoveToPoint = pt;
	//				}
	//			} break;
	//			case std::experimental::io2d::path_data_type::path_curve:
	//			{
	//				auto dataItem = item.get<path_curve>();
	//				auto pt1 = matrix.transform_point(dataItem.control_point_1() - origin) + origin;
	//				auto pt2 = matrix.transform_point(dataItem.control_point_2() - origin) + origin;
	//				auto pt3 = matrix.transform_point(dataItem.end_point() - origin) + origin;
	//				if (!hasCurrentPoint) {
	//					cpdItem.header.type = CAIRO_PATH_MOVE_TO;
	//					cpdItem.header.length = 2;
	//					vec.push_back(cpdItem);
	//					cpdItem = { };
	//					cpdItem.point = { pt1.x(), pt1.y() };
	//					vec.push_back(cpdItem);
	//					currentPoint = dataItem.control_point_1();
	//					lastMoveToPoint = pt1;
	//					hasCurrentPoint = true;
	//				}
	//				cpdItem.header.type = CAIRO_PATH_CURVE_TO;
	//				cpdItem.header.length = 4;
	//				vec.push_back(cpdItem);
	//				cpdItem = { };
	//				cpdItem.point = { pt1.x(), pt1.y() };
	//				vec.push_back(cpdItem);
	//				cpdItem = { };
	//				cpdItem.point = { pt2.x(), pt2.y() };
	//				vec.push_back(cpdItem);
	//				cpdItem = { };
	//				cpdItem.point = { pt3.x(), pt3.y() };
	//				vec.push_back(cpdItem);
	//				currentPoint = dataItem.end_point();
	//			} break;
	//			case std::experimental::io2d::path_data_type::path_new_sub_path:
	//			{
	//				hasCurrentPoint = false;
	//			} break;
	//			case std::experimental::io2d::path_data_type::path_close_path:
	//			{
	//				if (hasCurrentPoint) {
	//					cpdItem.header.type = CAIRO_PATH_CLOSE_PATH;
	//					cpdItem.header.length = 1;
	//					vec.push_back(cpdItem);
	//					cpdItem.header.type = CAIRO_PATH_MOVE_TO;
	//					cpdItem.header.length = 2;
	//					vec.push_back(cpdItem);
	//					cpdItem = { };
	//					cpdItem.point = { lastMoveToPoint.x(), lastMoveToPoint.y() };
	//					vec.push_back(cpdItem);
	//					// Calculate the untransformed current point from the transformed lastMoveToPoint.
	//					auto inverseMatrix = matrix_2d(matrix).invert(ec);
	//					if (static_cast<bool>(ec)) {
	//						_Data.reset();
	//						_Cairo_path.reset();
	//						return;
	//					}
	//					currentPoint = inverseMatrix.transform_point(lastMoveToPoint - origin) + origin;
	//					lastMoveToPoint = currentPoint;
	//				}
	//			} break;
	//			case std::experimental::io2d::path_data_type::path_rel_move:
	//			{
	//				if (!hasCurrentPoint) {
	//					ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
	//					_Data.reset();
	//					_Cairo_path.reset();
	//					return;
	//				}
	//				currentPoint = item.get<path_rel_move>().to() + currentPoint;
	//				auto pt = matrix.transform_point(currentPoint - origin) + origin;
	//				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
	//				cpdItem.header.length = 2;
	//				vec.push_back(cpdItem);
	//				cpdItem = { };
	//				cpdItem.point = { pt.x(), pt.y() };
	//				vec.push_back(cpdItem);
	//				hasCurrentPoint = true;
	//				lastMoveToPoint = pt;
	//			} break;
	//			case std::experimental::io2d::path_data_type::path_rel_line:
	//			{
	//				if (!hasCurrentPoint) {
	//					ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
	//					_Data.reset();
	//					_Cairo_path.reset();
	//					return;
	//				}
	//				currentPoint = item.get<path_rel_line>().to() + currentPoint;
	//				auto pt = matrix.transform_point(currentPoint - origin) + origin;
	//				cpdItem.header.type = CAIRO_PATH_LINE_TO;
	//				cpdItem.header.length = 2;
	//				vec.push_back(cpdItem);
	//				cpdItem = { };
	//				cpdItem.point = { pt.x(), pt.y() };
	//				vec.push_back(cpdItem);
	//			} break;
	//			case std::experimental::io2d::path_data_type::path_rel_cubic_curve:
	//			{
	//				if (!hasCurrentPoint) {
	//					ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
	//					_Data.reset();
	//					_Cairo_path.reset();
	//					return;
	//				}
	//				auto dataItem = item.get<path_rel_cubic_curve>();
	//				auto pt1 = matrix.transform_point(dataItem.control_point_1() + currentPoint - origin) + origin;
	//				auto pt2 = matrix.transform_point(dataItem.control_point_2() + currentPoint - origin) + origin;
	//				auto pt3 = matrix.transform_point(dataItem.end_point() + currentPoint - origin) + origin;
	//				cpdItem.header.type = CAIRO_PATH_CURVE_TO;
	//				cpdItem.header.length = 4;
	//				vec.push_back(cpdItem);
	//				cpdItem = { };
	//				cpdItem.point = { pt1.x(), pt1.y() };
	//				vec.push_back(cpdItem);
	//				cpdItem = { };
	//				cpdItem.point = { pt2.x(), pt2.y() };
	//				vec.push_back(cpdItem);
	//				cpdItem = { };
	//				cpdItem.point = { pt3.x(), pt3.y() };
	//				vec.push_back(cpdItem);
	//				currentPoint = dataItem.end_point() + currentPoint;
	//			} break;
	//			case std::experimental::io2d::path_data_type::path_arc:
	//			{
	//				auto dataItem = item.get<path_arc>();
	//				auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), ec, false, hasCurrentPoint, currentPoint, origin, matrix);
	//				if (static_cast<bool>(ec)) {
	//					_Data.reset();
	//					_Cairo_path.reset();
	//					return;
	//				}
	//				for (const auto& path_arcItem : data) {
	//					switch (path_arcItem.type()) {
	//					case std::experimental::io2d::path_data_type::path_abs_move:
	//					{
	//						currentPoint = path_arcItem.get<path_abs_move>().to();
	//						auto pt = matrix.transform_point(currentPoint - origin) + origin;
	//						cpdItem.header.type = CAIRO_PATH_MOVE_TO;
	//						cpdItem.header.length = 2;
	//						vec.push_back(cpdItem);
	//						cpdItem = { };
	//						cpdItem.point = { pt.x(), pt.y() };
	//						vec.push_back(cpdItem);
	//						hasCurrentPoint = true;
	//						lastMoveToPoint = pt;
	//					} break;
	//					case std::experimental::io2d::path_data_type::path_abs_line:
	//					{
	//						currentPoint = path_arcItem.get<path_abs_line>().to();
	//						auto pt = matrix.transform_point(currentPoint - origin) + origin;
	//						if (hasCurrentPoint) {
	//							cpdItem.header.type = CAIRO_PATH_LINE_TO;
	//							cpdItem.header.length = 2;
	//							vec.push_back(cpdItem);
	//							cpdItem = { };
	//							cpdItem.point = { pt.x(), pt.y() };
	//							vec.push_back(cpdItem);
	//						}
	//						else {
	//							cpdItem.header.type = CAIRO_PATH_MOVE_TO;
	//							cpdItem.header.length = 2;
	//							vec.push_back(cpdItem);
	//							cpdItem = { };
	//							cpdItem.point = { pt.x(), pt.y() };
	//							vec.push_back(cpdItem);
	//							hasCurrentPoint = true;
	//							lastMoveToPoint = pt;
	//						}
	//					} break;
	//					case std::experimental::io2d::path_data_type::path_curve:
	//					{
	//						auto curveItem = path_arcItem.get<path_curve>();
	//						auto pt1 = matrix.transform_point(curveItem.control_point_1() - origin) + origin;
	//						auto pt2 = matrix.transform_point(curveItem.control_point_2() - origin) + origin;
	//						auto pt3 = matrix.transform_point(curveItem.end_point() - origin) + origin;
	//						if (!hasCurrentPoint) {
	//							cpdItem.header.type = CAIRO_PATH_MOVE_TO;
	//							cpdItem.header.length = 2;
	//							vec.push_back(cpdItem);
	//							cpdItem = { };
	//							cpdItem.point = { pt1.x(), pt1.y() };
	//							vec.push_back(cpdItem);
	//							currentPoint = curveItem.control_point_1();
	//							lastMoveToPoint = pt1;
	//							hasCurrentPoint = true;
	//						}
	//						cpdItem.header.type = CAIRO_PATH_CURVE_TO;
	//						cpdItem.header.length = 4;
	//						vec.push_back(cpdItem);
	//						cpdItem = { };
	//						cpdItem.point = { pt1.x(), pt1.y() };
	//						vec.push_back(cpdItem);
	//						cpdItem = { };
	//						cpdItem.point = { pt2.x(), pt2.y() };
	//						vec.push_back(cpdItem);
	//						cpdItem = { };
	//						cpdItem.point = { pt3.x(), pt3.y() };
	//						vec.push_back(cpdItem);
	//						currentPoint = curveItem.end_point();
	//					} break;
	//					case path_data_type::path_new_sub_path:
	//					{
	//						assert("Unexpected value path_data_type::path_new_sub_path." && false);
	//					} break;
	//					case path_data_type::path_close_path:
	//					{
	//						assert("Unexpected value path_data_type::path_close_path." && false);
	//					} break;
	//					case path_data_type::path_rel_move:
	//					{
	//						assert("Unexpected value path_data_type::path_rel_move." && false);
	//					} break;
	//					case path_data_type::path_rel_line:
	//					{
	//						assert("Unexpected value path_data_type::path_rel_line." && false);
	//					} break;
	//					case path_data_type::path_rel_cubic_curve:
	//					{
	//						assert("Unexpected value path_data_type::path_rel_cubic_curve." && false);
	//					} break;
	//					case path_data_type::path_arc:
	//					{
	//						assert("Unexpected value path_data_type::path_arc." && false);
	//					} break;
	//					case path_data_type::path_arc_negative:
	//					{
	//						assert("Unexpected value path_data_type::path_arc_negative." && false);
	//					} break;
	//					case path_data_type::path_change_origin:
	//					{
	//						// Ignore, it's just spitting out the value we handed it.
	//					} break;
	//					case path_data_type::path_change_matrix:
	//					{
	//						// Ignore, it's just spitting out the value we handed it.
	//					} break;
	//					default:
	//						assert("Unexpected path_data_type in path_arc." && false);
	//						break;
	//					}
	//				}
	//				currentPoint = _Rotate_point_absolute_angle(dataItem.center(), dataItem.radius(), dataItem.angle_2(), true);
	//				hasCurrentPoint = true;
	//			}
	//			break;
	//			case std::experimental::io2d::path_data_type::path_arc_negative:
	//			{
	//				auto dataItem = item.get<path_arc_negative>();
	//				auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), ec, true, hasCurrentPoint, currentPoint, origin, matrix);
	//				if (static_cast<bool>(ec)) {
	//					_Data.reset();
	//					_Cairo_path.reset();
	//					return;
	//				}
	//				for (const auto& path_arcItem : data) {
	//					switch (path_arcItem.type()) {
	//					case std::experimental::io2d::path_data_type::path_abs_move:
	//					{
	//						currentPoint = path_arcItem.get<path_abs_move>().to();
	//						auto pt = matrix.transform_point(currentPoint - origin) + origin;
	//						cpdItem.header.type = CAIRO_PATH_MOVE_TO;
	//						cpdItem.header.length = 2;
	//						vec.push_back(cpdItem);
	//						cpdItem = { };
	//						cpdItem.point = { pt.x(), pt.y() };
	//						vec.push_back(cpdItem);
	//						hasCurrentPoint = true;
	//						lastMoveToPoint = pt;
	//					} break;
	//					case std::experimental::io2d::path_data_type::path_abs_line:
	//					{
	//						currentPoint = path_arcItem.get<path_abs_line>().to();
	//						auto pt = matrix.transform_point(currentPoint - origin) + origin;
	//						if (hasCurrentPoint) {
	//							cpdItem.header.type = CAIRO_PATH_LINE_TO;
	//							cpdItem.header.length = 2;
	//							vec.push_back(cpdItem);
	//							cpdItem = { };
	//							cpdItem.point = { pt.x(), pt.y() };
	//							vec.push_back(cpdItem);
	//						}
	//						else {
	//							cpdItem.header.type = CAIRO_PATH_MOVE_TO;
	//							cpdItem.header.length = 2;
	//							vec.push_back(cpdItem);
	//							cpdItem = { };
	//							cpdItem.point = { pt.x(), pt.y() };
	//							vec.push_back(cpdItem);
	//							hasCurrentPoint = true;
	//							lastMoveToPoint = pt;
	//						}
	//					} break;
	//					case std::experimental::io2d::path_data_type::path_curve:
	//					{
	//						auto curveItem = path_arcItem.get<path_curve>();
	//						auto pt1 = matrix.transform_point(curveItem.control_point_1() - origin) + origin;
	//						auto pt2 = matrix.transform_point(curveItem.control_point_2() - origin) + origin;
	//						auto pt3 = matrix.transform_point(curveItem.end_point() - origin) + origin;
	//						if (!hasCurrentPoint) {
	//							cpdItem.header.type = CAIRO_PATH_MOVE_TO;
	//							cpdItem.header.length = 2;
	//							vec.push_back(cpdItem);
	//							cpdItem = { };
	//							cpdItem.point = { pt1.x(), pt1.y() };
	//							vec.push_back(cpdItem);
	//							currentPoint = curveItem.control_point_1();
	//							lastMoveToPoint = pt1;
	//							hasCurrentPoint = true;
	//						}
	//						cpdItem.header.type = CAIRO_PATH_CURVE_TO;
	//						cpdItem.header.length = 4;
	//						vec.push_back(cpdItem);
	//						cpdItem = { };
	//						cpdItem.point = { pt1.x(), pt1.y() };
	//						vec.push_back(cpdItem);
	//						cpdItem = { };
	//						cpdItem.point = { pt2.x(), pt2.y() };
	//						vec.push_back(cpdItem);
	//						cpdItem = { };
	//						cpdItem.point = { pt3.x(), pt3.y() };
	//						vec.push_back(cpdItem);
	//						currentPoint = curveItem.end_point();
	//					} break;
	//					case path_data_type::path_new_sub_path:
	//					{
	//						assert("Unexpected value path_data_type::path_new_sub_path." && false);
	//					} break;
	//					case path_data_type::path_close_path:
	//					{
	//						assert("Unexpected value path_data_type::path_close_path." && false);
	//					} break;
	//					case path_data_type::path_rel_move:
	//					{
	//						assert("Unexpected value path_data_type::path_rel_move." && false);
	//					} break;
	//					case path_data_type::path_rel_line:
	//					{
	//						assert("Unexpected value path_data_type::path_rel_line." && false);
	//					} break;
	//					case path_data_type::path_rel_cubic_curve:
	//					{
	//						assert("Unexpected value path_data_type::path_rel_cubic_curve." && false);
	//					} break;
	//					case path_data_type::path_arc:
	//					{
	//						assert("Unexpected value path_data_type::path_arc." && false);
	//					} break;
	//					case path_data_type::path_arc_negative:
	//					{
	//						assert("Unexpected value path_data_type::path_arc_negative." && false);
	//					} break;
	//					case path_data_type::path_change_origin:
	//					{
	//						// Ignore, it's just spitting out the value we handed it.
	//					} break;
	//					case path_data_type::path_change_matrix:
	//					{
	//						// Ignore, it's just spitting out the value we handed it.
	//					} break;
	//					default:
	//						assert("Unexpected path_data_type in path_arc." && false);
	//						break;
	//					}
	//				}
	//				currentPoint = _Rotate_point_absolute_angle(dataItem.center(), dataItem.radius(), dataItem.angle_2());
	//				hasCurrentPoint = true;
	//			}
	//			break;
	//			case std::experimental::io2d::path_data_type::path_change_matrix:
	//			{
	//				matrix = item.get<path_change_matrix>().matrix();
	//			} break;
	//			case std::experimental::io2d::path_data_type::path_change_origin:
	//			{
	//				origin = item.get<path_change_origin>().origin();
	//			} break;
	//#ifdef __clang__
	//#pragma clang diagnostic push
	//#pragma clang diagnostic ignored "-Wunreachable-code-break"
	//#endif
	//			default:
	//			{
	//				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_PATH_DATA);
	//				_Data.reset();
	//				_Cairo_path.reset();
	//				return;
	//			} break;
	//#ifdef __clang__
	//#pragma clang diagnostic pop
	//#endif
	//			}
	//		}
	//
	//		_Cairo_path->num_data = static_cast<int>(vec.size());
	//		const auto numDataST = vec.size();
	//		_Cairo_path->data = new cairo_path_data_t[numDataST];
	//		for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
	//			_Cairo_path->data[currItemIndex] = vec[currItemIndex];
	//		}
	//		_Cairo_path->status = CAIRO_STATUS_SUCCESS;
	//
	//		for (const auto& item : pathData) {
	//			_Data->push_back(item);
	//		}
	//	}
	//	catch (const bad_alloc&) {
	//		ec = make_error_code(errc::not_enough_memory);
	//		_Data.reset();
	//		_Cairo_path.reset();
	//		return;
	//	}
	//	ec.clear();
	//}
	//
	//path_group::path_group(path_group&& other) noexcept
	//	: _Data(move(other._Data))
	//	, _Cairo_path(move(other._Cairo_path)) {
	//}
	//

	//vector<path_data_item> path_group::data() const {
	//	vector<path_data_item> result;
	//	for (const auto& item : *_Data) {
	//		result.push_back(item);
	//	}
	//	return result;
	//}
	//
	//vector<path_data_item> path_group::data(error_code& ec) const noexcept {
	//	// Relies on C++17 noexcept guarantee for vector default ctor (N4258, adopted 2014-11).
	//	vector<path_data_item> result;
	//	try {
	//		for (const auto& item : *_Data) {
	//			result.push_back(item);
	//		}
	//		ec.clear();
	//		return result;
	//	}
	//	catch (const bad_alloc&) {
	//		ec = make_error_code(errc::not_enough_memory);
	//		return result;
	//	}
	//}
	//
	//const vector<path_data_item>& path_group::data_ref() const noexcept {
	//	return *_Data;
	//}
