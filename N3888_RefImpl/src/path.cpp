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

path::path(const path_factory& pb)
: path(pb.data_ref()) {
}

path::path(const vector<path_data_item>& pathData)
: _Data(new vector<path_data_item>)
, _Cairo_path(new cairo_path_t, &_Free_manual_cairo_path) {
	auto matrix = matrix_2d::init_identity();
	vector_2d origin{ };
	bool hasCurrentPoint = false;
	// Untransformed because we use it to add to raw relative points for transformation.
	vector_2d currentPoint{ };
	// Transformed because we need to know where the transformed last move to point is when we receive a close path instruction and the matrix and origin may have since changed such that we wouldn't be able to calculate it correctly anymore.
	vector_2d lastMoveToPoint{ };
	auto pdSize = pathData.size();
	vector<cairo_path_data_t> vec;
	for (unsigned int i = 0; i < pdSize; i++) {
		const auto& item = pathData[i];
		cairo_path_data_t cpdItem{ };
		auto pdt = item.type();
		switch (pdt) {
		case std::experimental::io2d::path_data_type::move_to:
		{
			currentPoint = item.get<path_data_item::move_to>().to();
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
			currentPoint = item.get<path_data_item::line_to>().to();
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
			auto dataItem = item.get<path_data_item::curve_to>();
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
				lastMoveToPoint = currentPoint;
			}
		} break;
		case std::experimental::io2d::path_data_type::rel_move_to:
		{
			if (!hasCurrentPoint) {
				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NO_CURRENT_POINT);
			}
			currentPoint = item.get<path_data_item::rel_move_to>().to() + currentPoint;
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
			currentPoint = item.get<path_data_item::rel_line_to>().to() + currentPoint;
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
			auto dataItem = item.get<path_data_item::rel_curve_to>();
			auto pt1 = matrix.transform_point(dataItem.control_point_1() + currentPoint - origin) + origin;
			auto pt2 = matrix.transform_point(dataItem.control_point_2() + currentPoint - origin) + origin;
			auto pt3 = matrix.transform_point(dataItem.end_point() + currentPoint - origin) + origin;
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
			currentPoint = dataItem.end_point() + currentPoint;
		} break;
		case std::experimental::io2d::path_data_type::arc:
		{
			auto ad = item.get<path_data_item::arc>();
			auto ctr = ad.center();
			auto rad = ad.radius();
			auto ang1 = ad.angle_1();
			auto ang2 = ad.angle_2();
			while (ang2 < ang1) {
#if _Variable_templates_conditional_support_test
                                ang2 += two_pi<double>;
#else
				ang2 += two_pi<double>();
#endif
			}
			vector_2d pt0, pt1, pt2, pt3;
			int bezCount = 1;
			double theta = ang2 - ang1;
			double phi;
#if _Variable_templates_conditional_support_test
			while (theta >= half_pi<double>) {
				theta /= 2.0;
				bezCount += bezCount;
			}
#else
			while (theta >= half_pi<double>()) {
				theta /= 2.0;
				bezCount += bezCount;
			}
#endif
			phi = theta / 2.0;
			auto cosPhi = cos(phi);
			auto sinPhi = sin(phi);
			pt0.x(cosPhi);
			pt0.y(-sinPhi);
			pt3.x(pt0.x());
			pt3.y(-pt0.y());
			pt1.x((4.0 - cosPhi) / 3.0);
			pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
			pt2.x(pt1.x());
			pt2.y(-pt1.y());
			phi = -phi;
			auto rotCwFn = [](const vector_2d& pt, double a) -> vector_2d {
				return{ pt.x() * cos(a) + pt.y() * sin(a),
					-(pt.x() * -sin(a) + pt.y() * cos(a)) };
			};
			pt0 = rotCwFn(pt0, phi);
			pt1 = rotCwFn(pt1, phi);
			pt2 = rotCwFn(pt2, phi);
			pt3 = rotCwFn(pt3, phi);

			auto currTheta = ang1;
			const auto startPt =
				ctr + rotCwFn({ pt0.x() * rad, pt0.y() * rad }, currTheta);
			if (hasCurrentPoint) {
				auto pt = matrix.transform_point(startPt - origin) + origin;
				cpdItem.header.type = CAIRO_PATH_LINE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt.x(), pt.y() };
				vec.push_back(cpdItem);
				currentPoint = startPt;
			}
			else {
				auto pt = matrix.transform_point(startPt - origin) + origin;
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt.x(), pt.y() };
				vec.push_back(cpdItem);
				currentPoint = startPt;
				hasCurrentPoint = true;
				lastMoveToPoint = pt;
			}
			for (; bezCount > 0; bezCount--) {
				auto cpt1 = ctr + rotCwFn({ pt1.x() * rad, pt1.y() * rad }, currTheta);
				auto cpt2 = ctr + rotCwFn({ pt2.x() * rad, pt2.y() * rad }, currTheta);
				auto cpt3 = ctr + rotCwFn({ pt3.x() * rad, pt3.y() * rad }, currTheta);
				currentPoint = cpt3;
				cpt1 = matrix.transform_point(cpt1 - origin) + origin;
				cpt2 = matrix.transform_point(cpt2 - origin) + origin;
				cpt3 = matrix.transform_point(cpt3 - origin) + origin;
				cpdItem.header.type = CAIRO_PATH_CURVE_TO;
				cpdItem.header.length = 4;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { cpt1.x(), cpt1.y() };
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { cpt2.x(), cpt2.y() };
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { cpt3.x(), cpt3.y() };
				vec.push_back(cpdItem);
				currTheta += theta;
			}
//			currentPoint = _Rotate_point_absolute_angle(ad.center(), ad.radius(), ad.angle_2(), true);
		}
		break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			auto ad = item.get<path_data_item::arc_negative>();
			auto ctr = ad.center();
			auto rad = ad.radius();
			auto ang1 = ad.angle_1();
			auto ang2 = ad.angle_2();
			while (ang2 > ang1) {
#if _Variable_templates_conditional_support_test
                                ang2 -= two_pi<double>;
#else
				ang2 -= two_pi<double>();
#endif
			}
			vector_2d pt0, pt1, pt2, pt3;
			int bezCount = 1;
			double theta = ang1 - ang2;
			double phi;
#if _Variable_templates_conditional_support_test
			while (theta >= half_pi<double>) {
				theta /= 2.0;
				bezCount += bezCount;
			}
#else
			while (theta >= half_pi<double>()) {
				theta /= 2.0;
				bezCount += bezCount;
			}
#endif
			phi = theta / 2.0;
			auto cosPhi = cos(phi);
			auto sinPhi = sin(phi);
			pt0.x(cosPhi);
			pt0.y(-sinPhi);
			pt3.x(pt0.x());
			pt3.y(-pt0.y());
			pt1.x((4.0 - cosPhi) / 3.0);
			pt1.y(-(((1.0 - cosPhi) * (3.0 - cosPhi)) / (3.0 * sinPhi)));
			pt2.x(pt1.x());
			pt2.y(-pt1.y());
			auto rotCwFn = [](const vector_2d& pt, double a) -> vector_2d {
				return{ pt.x() * cos(a) + pt.y() * sin(a),
					-(pt.x() * -sin(a) + pt.y() * cos(a)) };
			};
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
			auto currTheta = ang1;
			const auto startPt =
				ctr + rotCwFn({ pt0.x() * rad, pt0.y() * rad }, currTheta);
			if (hasCurrentPoint) {
				auto pt = matrix.transform_point(startPt - origin) + origin;
				cpdItem.header.type = CAIRO_PATH_LINE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt.x(), pt.y() };
				vec.push_back(cpdItem);
				currentPoint = startPt;
			}
			else {
				auto pt = matrix.transform_point(startPt - origin) + origin;
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { pt.x(), pt.y() };
				vec.push_back(cpdItem);
				currentPoint = startPt;
				hasCurrentPoint = true;
				lastMoveToPoint = pt;
			}
			for (; bezCount > 0; bezCount--) {
				auto cpt1 = ctr + rotCwFn({ pt1.x() * rad, pt1.y() * rad }, currTheta);
				auto cpt2 = ctr + rotCwFn({ pt2.x() * rad, pt2.y() * rad }, currTheta);
				auto cpt3 = ctr + rotCwFn({ pt3.x() * rad, pt3.y() * rad }, currTheta);
				currentPoint = cpt3;
				cpt1 = matrix.transform_point(cpt1 - origin) + origin;
				cpt2 = matrix.transform_point(cpt2 - origin) + origin;
				cpt3 = matrix.transform_point(cpt3 - origin) + origin;
				cpdItem.header.type = CAIRO_PATH_CURVE_TO;
				cpdItem.header.length = 4;
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { cpt1.x(), cpt1.y() };
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { cpt2.x(), cpt2.y() };
				vec.push_back(cpdItem);
				cpdItem = { };
				cpdItem.point = { cpt3.x(), cpt3.y() };
				vec.push_back(cpdItem);
				currTheta -= theta;
			}

			//auto dataItem = item.get<arc_negative>();
			//auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), true, hasCurrentPoint, currentPoint, origin, matrix);
			//for (const auto& arcItem : data) {
			//	switch (arcItem.type()) {
			//	case std::experimental::io2d::path_data_type::move_to:
			//	{
			//		currentPoint = arcItem.get<move_to>().to();
			//		auto pt = matrix.transform_point(currentPoint - origin) + origin;
			//		cpdItem.header.type = CAIRO_PATH_MOVE_TO;
			//		cpdItem.header.length = 2;
			//		vec.push_back(cpdItem);
			//		cpdItem = { };
			//		cpdItem.point = { pt.x(), pt.y() };
			//		vec.push_back(cpdItem);
			//		hasCurrentPoint = true;
			//		lastMoveToPoint = pt;
			//	} break;
			//	case std::experimental::io2d::path_data_type::line_to:
			//	{
			//		currentPoint = arcItem.get<line_to>().to();
			//		auto pt = matrix.transform_point(currentPoint - origin) + origin;
			//		if (hasCurrentPoint) {
			//			cpdItem.header.type = CAIRO_PATH_LINE_TO;
			//			cpdItem.header.length = 2;
			//			vec.push_back(cpdItem);
			//			cpdItem = { };
			//			cpdItem.point = { pt.x(), pt.y() };
			//			vec.push_back(cpdItem);
			//		}
			//		else {
			//			cpdItem.header.type = CAIRO_PATH_MOVE_TO;
			//			cpdItem.header.length = 2;
			//			vec.push_back(cpdItem);
			//			cpdItem = { };
			//			cpdItem.point = { pt.x(), pt.y() };
			//			vec.push_back(cpdItem);
			//			hasCurrentPoint = true;
			//			lastMoveToPoint = pt;
			//		}
			//	} break;
			//	case std::experimental::io2d::path_data_type::curve_to:
			//	{
			//		auto curveItem = arcItem.get<curve_to>();
			//		auto pt1 = matrix.transform_point(curveItem.control_point_1() - origin) + origin;
			//		auto pt2 = matrix.transform_point(curveItem.control_point_2() - origin) + origin;
			//		auto pt3 = matrix.transform_point(curveItem.end_point() - origin) + origin;
			//		if (!hasCurrentPoint) {
			//			cpdItem.header.type = CAIRO_PATH_MOVE_TO;
			//			cpdItem.header.length = 2;
			//			vec.push_back(cpdItem);
			//			cpdItem = { };
			//			cpdItem.point = { pt1.x(), pt1.y() };
			//			vec.push_back(cpdItem);
			//			currentPoint = curveItem.control_point_1();
			//			lastMoveToPoint = pt1;
			//			hasCurrentPoint = true;
			//		}
			//		cpdItem.header.type = CAIRO_PATH_CURVE_TO;
			//		cpdItem.header.length = 4;
			//		vec.push_back(cpdItem);
			//		cpdItem = { };
			//		cpdItem.point = { pt1.x(), pt1.y() };
			//		vec.push_back(cpdItem);
			//		cpdItem = { };
			//		cpdItem.point = { pt2.x(), pt2.y() };
			//		vec.push_back(cpdItem);
			//		cpdItem = { };
			//		cpdItem.point = { pt3.x(), pt3.y() };
			//		vec.push_back(cpdItem);
			//		currentPoint = curveItem.end_point();
			//	} break;
			//	case path_data_type::new_sub_path:
			//	{
			//		assert("Unexpected value path_data_type::new_sub_path." && false);
			//	} break;
			//	case path_data_type::close_path:
			//	{
			//		assert("Unexpected value path_data_type::close_path." && false);
			//	} break;
			//	case path_data_type::rel_move_to:
			//	{
			//		assert("Unexpected value path_data_type::rel_move_to." && false);
			//	} break;
			//	case path_data_type::rel_line_to:
			//	{
			//		assert("Unexpected value path_data_type::rel_line_to." && false);
			//	} break;
			//	case path_data_type::rel_curve_to:
			//	{
			//		assert("Unexpected value path_data_type::rel_curve_to." && false);
			//	} break;
			//	case path_data_type::arc:
			//	{
			//		assert("Unexpected value path_data_type::arc." && false);
			//	} break;
			//	case path_data_type::arc_negative:
			//	{
			//		assert("Unexpected value path_data_type::arc_negative." && false);
			//	} break;
			//	case path_data_type::change_origin:
			//	{
			//		// Ignore, it's just spitting out the value we handed it.
			//	} break;
			//	case path_data_type::change_matrix:
			//	{
			//		// Ignore, it's just spitting out the value we handed it.
			//	} break;
			//	default:
			//		assert("Unexpected path_data_type in arc." && false);
			//		break;
			//	}
			//}
			//currentPoint = _Rotate_point_absolute_angle(ad.center(), ad.radius(), ad.angle_2());
			//hasCurrentPoint = true;
		}
		break;
		case std::experimental::io2d::path_data_type::change_matrix:
		{
			matrix = item.get<path_data_item::change_matrix>().matrix();
		} break;
		case std::experimental::io2d::path_data_type::change_origin:
		{
			origin = item.get<path_data_item::change_origin>().origin();
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

	for (const auto& item : pathData) {
		_Data->push_back(item);
	}
}

path::path(const path_factory& pb, error_code& ec) noexcept
	: path(pb.data_ref(), ec) {
}

path::path(const vector<path_data_item>& pathData, error_code& ec) noexcept
	: _Data()
	, _Cairo_path() {
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
		p_cairoPath = nullptr;
	}
	catch (const exception& ex) {
		// The constructor we use ensures that our custom deleter is called on p_cairoPath in the event of an exception.
		assert(ex.what());
		ec = make_error_code(io2d_error::invalid_status);
		return;
	}
	auto matrix = matrix_2d::init_identity();
	vector_2d origin{ };
	bool hasCurrentPoint = false;
	// Untransformed because we use it to add to raw relative points for transformation.
	vector_2d currentPoint{ };
	// Transformed because we need to know where the transformed last move to point is when we receive a close path instruction and the matrix and origin may have since changed such that we wouldn't be able to calculate it correctly anymore.
	vector_2d lastMoveToPoint{ };
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
				currentPoint = item.get<path_data_item::move_to>().to();
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
				currentPoint = item.get<path_data_item::line_to>().to();
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
				auto dataItem = item.get<path_data_item::curve_to>();
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
					auto inverseMatrix = matrix_2d(matrix).invert(ec);
					if (static_cast<bool>(ec)) {
						_Data.reset();
						_Cairo_path.reset();
						return;
					}
					currentPoint = inverseMatrix.transform_point(lastMoveToPoint - origin) + origin;
					lastMoveToPoint = currentPoint;
				}
			} break;
			case std::experimental::io2d::path_data_type::rel_move_to:
			{
				if (!hasCurrentPoint) {
					ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
					_Data.reset();
					_Cairo_path.reset();
					return;
				}
				currentPoint = item.get<path_data_item::rel_move_to>().to() + currentPoint;
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
					ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
					_Data.reset();
					_Cairo_path.reset();
					return;
				}
				currentPoint = item.get<path_data_item::rel_line_to>().to() + currentPoint;
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
					ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_NO_CURRENT_POINT);
					_Data.reset();
					_Cairo_path.reset();
					return;
				}
				auto dataItem = item.get<path_data_item::rel_curve_to>();
				auto pt1 = matrix.transform_point(dataItem.control_point_1() + currentPoint - origin) + origin;
				auto pt2 = matrix.transform_point(dataItem.control_point_2() + currentPoint - origin) + origin;
				auto pt3 = matrix.transform_point(dataItem.end_point() + currentPoint - origin) + origin;
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
				currentPoint = dataItem.end_point() + currentPoint;
			} break;
			case std::experimental::io2d::path_data_type::arc:
			{
				auto dataItem = item.get<path_data_item::arc>();
				auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), ec, false, hasCurrentPoint, currentPoint, origin, matrix);
				if (static_cast<bool>(ec)) {
					_Data.reset();
					_Cairo_path.reset();
					return;
				}
				for (const auto& arcItem : data) {
					switch (arcItem.type()) {
					case std::experimental::io2d::path_data_type::move_to:
					{
						currentPoint = arcItem.get<path_data_item::move_to>().to();
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
						currentPoint = arcItem.get<path_data_item::line_to>().to();
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
						auto curveItem = arcItem.get<path_data_item::curve_to>();
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
				auto dataItem = item.get<path_data_item::arc_negative>();
				auto data = _Get_arc_as_beziers(dataItem.center(), dataItem.radius(), dataItem.angle_1(), dataItem.angle_2(), ec, true, hasCurrentPoint, currentPoint, origin, matrix);
				if (static_cast<bool>(ec)) {
					_Data.reset();
					_Cairo_path.reset();
					return;
				}
				for (const auto& arcItem : data) {
					switch (arcItem.type()) {
					case std::experimental::io2d::path_data_type::move_to:
					{
						currentPoint = arcItem.get<path_data_item::move_to>().to();
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
						currentPoint = arcItem.get<path_data_item::line_to>().to();
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
						auto curveItem = arcItem.get<path_data_item::curve_to>();
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
				matrix = item.get<path_data_item::change_matrix>().matrix();
			} break;
			case std::experimental::io2d::path_data_type::change_origin:
			{
				origin = item.get<path_data_item::change_origin>().origin();
			} break;
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunreachable-code-break"
#endif
			default:
			{
				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_PATH_DATA);
				_Data.reset();
				_Cairo_path.reset();
				return;
			} break;
#ifdef __clang__
#pragma clang diagnostic pop
#endif
			}
		}

		_Cairo_path->num_data = static_cast<int>(vec.size());
		const auto numDataST = vec.size();
		_Cairo_path->data = new cairo_path_data_t[numDataST];
		for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
			_Cairo_path->data[currItemIndex] = vec[currItemIndex];
		}
		_Cairo_path->status = CAIRO_STATUS_SUCCESS;

		for (const auto& item : pathData) {
			_Data->push_back(item);
		}
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		_Data.reset();
		_Cairo_path.reset();
		return;
	}
	ec.clear();
}

path::path(path&& other) noexcept
	: _Data(move(other._Data))
	, _Cairo_path(move(other._Cairo_path)) {
}

path& path::operator=(path&& other) noexcept {
	if (this != &other) {
		_Data = move(other._Data);
		_Cairo_path = move(other._Cairo_path);
	}
	return *this;
}

//vector<path_data_item> path::data() const {
//	vector<path_data_item> result;
//	for (const auto& item : *_Data) {
//		result.push_back(item);
//	}
//	return result;
//}
//
//vector<path_data_item> path::data(error_code& ec) const noexcept {
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
//const vector<path_data_item>& path::data_ref() const noexcept {
//	return *_Data;
//}
