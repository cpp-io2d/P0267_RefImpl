#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

path_data_item::path_data_item(path_data_item&& other) noexcept
	: _Has_data(move(other._Has_data))
	, _Data(move(other._Data))
	, _Type(move(other._Type)) {
}

path_data_item& path_data_item::operator=(path_data_item&& other) noexcept {
	if (this != &other) {
		_Has_data = move(other._Has_data);
		_Data = move(other._Data);
		_Type = move(other._Type);
	}
	return *this;
};

path_data_item::path_data_item(const arc& value) noexcept
	: _Has_data()
	, _Data()
	, _Type() {
	_Has_data = true;
	_Data.arc.angle1 = value.angle_1();
	_Data.arc.angle2 = value.angle_2();
	_Data.arc.centerX = value.center().x();
	_Data.arc.centerY = value.center().y();
	_Data.arc.radius = value.radius();
	_Type = value.type();
}

path_data_item::path_data_item(const arc_negative& value) noexcept
	: _Has_data()
	, _Data()
	, _Type() {
	_Has_data = true;
	_Data.arc.angle1 = value.angle_1();
	_Data.arc.angle2 = value.angle_2();
	_Data.arc.centerX = value.center().x();
	_Data.arc.centerY = value.center().y();
	_Data.arc.radius = value.radius();
	_Type = value.type();
}

path_data_item::path_data_item(const change_matrix& value) noexcept
	: _Has_data()
	, _Data()
	, _Type() {
	_Has_data = true;
	_Data.matrix.m00 = value.matrix().m00();
	_Data.matrix.m01 = value.matrix().m01();
	_Data.matrix.m10 = value.matrix().m10();
	_Data.matrix.m11 = value.matrix().m11();
	_Data.matrix.m20 = value.matrix().m20();
	_Data.matrix.m21 = value.matrix().m21();
	_Type = value.type();
}

path_data_item::path_data_item(const change_origin& value) noexcept
	: _Has_data()
	, _Data()
	, _Type() {
	_Has_data = true;
	_Data.point.x = value.origin().x();
	_Data.point.y = value.origin().y();
	_Type = value.type();
}

path_data_item::path_data_item(const close_path& value) noexcept
	: _Has_data()
	, _Data()
	, _Type() {
	_Has_data = true;
	_Type = value.type();
}

path_data_item::path_data_item(const curve_to& value) noexcept
	: _Has_data()
	, _Data()
	, _Type() {
	_Has_data = true;
	_Data.curve.cpt1x = value.control_point_1().x();
	_Data.curve.cpt1y = value.control_point_1().y();
	_Data.curve.cpt2x = value.control_point_2().x();
	_Data.curve.cpt2y = value.control_point_2().y();
	_Data.curve.eptx = value.end_point().x();
	_Data.curve.epty = value.end_point().y();
	_Type = value.type();
}

path_data_item::path_data_item(const rel_curve_to& value) noexcept
	: _Has_data()
	, _Data()
	, _Type() {
	_Has_data = true;
	_Data.curve.cpt1x = value.control_point_1().x();
	_Data.curve.cpt1y = value.control_point_1().y();
	_Data.curve.cpt2x = value.control_point_2().x();
	_Data.curve.cpt2y = value.control_point_2().y();
	_Data.curve.eptx = value.end_point().x();
	_Data.curve.epty = value.end_point().y();
	_Type = value.type();
}

path_data_item::path_data_item(const new_sub_path& value) noexcept
	: _Has_data()
	, _Data()
	, _Type() {
	_Has_data = true;
	_Type = value.type();
}

path_data_item::path_data_item(const line_to& value) noexcept
	: _Has_data()
	, _Data()
	, _Type() {
	_Has_data = true;
	_Data.point.x = value.to().x();
	_Data.point.y = value.to().y();
	_Type = value.type();
}

path_data_item::path_data_item(const move_to& value) noexcept
	: _Has_data()
	, _Data()
	, _Type() {
	_Has_data = true;
	_Data.point.x = value.to().x();
	_Data.point.y = value.to().y();
	_Type = value.type();
}

path_data_item::path_data_item(const rel_line_to& value) noexcept
	: _Has_data()
	, _Data()
	, _Type() {
	_Has_data = true;
	_Data.point.x = value.to().x();
	_Data.point.y = value.to().y();
	_Type = value.type();
}

path_data_item::path_data_item(const rel_move_to& value) noexcept
	: _Has_data()
	, _Data()
	, _Type() {
	_Has_data = true;
	_Data.point.x = value.to().x();
	_Data.point.y = value.to().y();
	_Type = value.type();
}

void path_data_item::assign(const arc& value) noexcept {
	_Has_data = true;
	_Data.arc.angle1 = value.angle_1();
	_Data.arc.angle2 = value.angle_2();
	_Data.arc.centerX = value.center().x();
	_Data.arc.centerY = value.center().y();
	_Data.arc.radius = value.radius();
	_Type = value.type();
}

void path_data_item::assign(const arc_negative& value) noexcept {
	_Has_data = true;
	_Data.arc.angle1 = value.angle_1();
	_Data.arc.angle2 = value.angle_2();
	_Data.arc.centerX = value.center().x();
	_Data.arc.centerY = value.center().y();
	_Data.arc.radius = value.radius();
	_Type = value.type();
}

void path_data_item::assign(const change_matrix& value) noexcept {
	_Has_data = true;
	_Data.matrix.m00 = value.matrix().m00();
	_Data.matrix.m01 = value.matrix().m01();
	_Data.matrix.m10 = value.matrix().m10();
	_Data.matrix.m11 = value.matrix().m11();
	_Data.matrix.m20 = value.matrix().m20();
	_Data.matrix.m21 = value.matrix().m21();
	_Type = value.type();
}

void path_data_item::assign(const change_origin& value) noexcept {
	_Has_data = true;
	_Data.point.x = value.origin().x();
	_Data.point.y = value.origin().y();
	_Type = value.type();
}

void path_data_item::assign(const close_path& value) noexcept {
	_Has_data = true;
	_Type = value.type();
}

void path_data_item::assign(const curve_to& value) noexcept {
	_Has_data = true;
	_Data.curve.cpt1x = value.control_point_1().x();
	_Data.curve.cpt1y = value.control_point_1().y();
	_Data.curve.cpt2x = value.control_point_2().x();
	_Data.curve.cpt2y = value.control_point_2().y();
	_Data.curve.eptx = value.end_point().x();
	_Data.curve.epty = value.end_point().y();
	_Type = value.type();
}

void path_data_item::assign(const rel_curve_to& value) noexcept {
	_Has_data = true;
	_Data.curve.cpt1x = value.control_point_1().x();
	_Data.curve.cpt1y = value.control_point_1().y();
	_Data.curve.cpt2x = value.control_point_2().x();
	_Data.curve.cpt2y = value.control_point_2().y();
	_Data.curve.eptx = value.end_point().x();
	_Data.curve.epty = value.end_point().y();
	_Type = value.type();
}

void path_data_item::assign(const new_sub_path& value) noexcept {
	_Has_data = true;
	_Type = value.type();
}

void path_data_item::assign(const line_to& value) noexcept {
	_Has_data = true;
	_Data.point.x = value.to().x();
	_Data.point.y = value.to().y();
	_Type = value.type();
}

void path_data_item::assign(const move_to& value) noexcept {
	_Has_data = true;
	_Data.point.x = value.to().x();
	_Data.point.y = value.to().y();
	_Type = value.type();
}

void path_data_item::assign(const rel_line_to& value) noexcept {
	_Has_data = true;
	_Data.point.x = value.to().x();
	_Data.point.y = value.to().y();
	_Type = value.type();
}

void path_data_item::assign(const rel_move_to& value) noexcept {
	_Has_data = true;
	_Data.point.x = value.to().x();
	_Data.point.y = value.to().y();
	_Type = value.type();
}

bool path_data_item::has_data() const noexcept {
	return _Has_data;
}

path_data_type path_data_item::type() const {
	if (!_Has_data) {
		throw system_error(make_error_code(errc::operation_not_permitted));
	}
	return _Type;
}

path_data_type path_data_item::type(::std::error_code& ec) const noexcept {
	if (!_Has_data) {
		ec = make_error_code(errc::operation_not_permitted);
		return path_data_type::close_path;
	}
	return _Type;
}

unique_ptr<path_data> path_data_item::get() const {
	if (!_Has_data) {
		throw system_error(make_error_code(errc::operation_not_permitted));
	}

	switch (_Type) {
	case std::experimental::io2d::path_data_type::move_to:
	{
		return make_unique<std::experimental::io2d::move_to>(point{ _Data.point.x, _Data.point.y });
	} break;
	case std::experimental::io2d::path_data_type::line_to:
	{
		return make_unique<std::experimental::io2d::line_to>(point{ _Data.point.x, _Data.point.y });
	} break;
	case std::experimental::io2d::path_data_type::curve_to:
	{
		return make_unique<std::experimental::io2d::curve_to>(point{ _Data.curve.cpt1x, _Data.curve.cpt1y }, point{ _Data.curve.cpt2x, _Data.curve.cpt2y }, point{ _Data.curve.eptx, _Data.curve.epty });
	} break;
	case std::experimental::io2d::path_data_type::new_sub_path:
	{
		return make_unique<std::experimental::io2d::new_sub_path>();
	} break;
	case std::experimental::io2d::path_data_type::close_path:
	{
		return make_unique<std::experimental::io2d::close_path>();
	} break;
	case std::experimental::io2d::path_data_type::rel_move_to:
	{
		return make_unique<std::experimental::io2d::rel_move_to>(point{ _Data.point.x, _Data.point.y });
	} break;
	case std::experimental::io2d::path_data_type::rel_line_to:
	{
		return make_unique<std::experimental::io2d::rel_line_to>(point{ _Data.point.x, _Data.point.y });
	} break;
	case std::experimental::io2d::path_data_type::rel_curve_to:
	{
		return make_unique<std::experimental::io2d::rel_curve_to>(point{ _Data.curve.cpt1x, _Data.curve.cpt1y }, point{ _Data.curve.cpt2x, _Data.curve.cpt2y }, point{ _Data.curve.eptx, _Data.curve.epty });
	} break;
	case std::experimental::io2d::path_data_type::arc:
	{
		return make_unique<std::experimental::io2d::arc>(point{ _Data.arc.centerX, _Data.arc.centerY }, _Data.arc.radius, _Data.arc.angle1, _Data.arc.angle2);
	} break;
	case std::experimental::io2d::path_data_type::arc_negative:
	{
		return make_unique<std::experimental::io2d::arc_negative>(point{ _Data.arc.centerX, _Data.arc.centerY }, _Data.arc.radius, _Data.arc.angle1, _Data.arc.angle2);
	} break;
	case std::experimental::io2d::path_data_type::change_matrix:
	{
		return make_unique<std::experimental::io2d::change_matrix>(matrix_2d{ _Data.matrix.m00, _Data.matrix.m01, _Data.matrix.m10, _Data.matrix.m11, _Data.matrix.m20, _Data.matrix.m21 });
	} break;
	case std::experimental::io2d::path_data_type::change_origin:
	{
		return make_unique<std::experimental::io2d::change_origin>(point{ _Data.point.x, _Data.point.y });
	} break;
	default:
		assert("Unknown path_data_type" && false);
		throw system_error(_Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_PATH_DATA));
	}
}

unique_ptr<path_data> path_data_item::get(::std::error_code& ec) const noexcept {
	const static close_path errorResult;
	if (!_Has_data) {
		ec = make_error_code(errc::operation_not_permitted);
		return nullptr;
	}
	try {
		ec.clear();
		switch (_Type) {
		case std::experimental::io2d::path_data_type::move_to:
		{
			return make_unique<std::experimental::io2d::move_to>(point{ _Data.point.x, _Data.point.y });
		} break;
		case std::experimental::io2d::path_data_type::line_to:
		{
			return make_unique<std::experimental::io2d::line_to>(point{ _Data.point.x, _Data.point.y });
		} break;
		case std::experimental::io2d::path_data_type::curve_to:
		{
			return make_unique<std::experimental::io2d::curve_to>(point{ _Data.curve.cpt1x, _Data.curve.cpt1y }, point{ _Data.curve.cpt2x, _Data.curve.cpt2y }, point{ _Data.curve.eptx, _Data.curve.epty });
		} break;
		case std::experimental::io2d::path_data_type::new_sub_path:
		{
			return make_unique<std::experimental::io2d::new_sub_path>();
		} break;
		case std::experimental::io2d::path_data_type::close_path:
		{
			return make_unique<std::experimental::io2d::close_path>();
		} break;
		case std::experimental::io2d::path_data_type::rel_move_to:
		{
			return make_unique<std::experimental::io2d::rel_move_to>(point{ _Data.point.x, _Data.point.y });
		} break;
		case std::experimental::io2d::path_data_type::rel_line_to:
		{
			return make_unique<std::experimental::io2d::rel_line_to>(point{ _Data.point.x, _Data.point.y });
		} break;
		case std::experimental::io2d::path_data_type::rel_curve_to:
		{
			return make_unique<std::experimental::io2d::rel_curve_to>(point{ _Data.curve.cpt1x, _Data.curve.cpt1y }, point{ _Data.curve.cpt2x, _Data.curve.cpt2y }, point{ _Data.curve.eptx, _Data.curve.epty });
		} break;
		case std::experimental::io2d::path_data_type::arc:
		{
			return make_unique<std::experimental::io2d::arc>(point{ _Data.arc.centerX, _Data.arc.centerY }, _Data.arc.radius, _Data.arc.angle1, _Data.arc.angle2);
		} break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			return make_unique<std::experimental::io2d::arc_negative>(point{ _Data.arc.centerX, _Data.arc.centerY }, _Data.arc.radius, _Data.arc.angle1, _Data.arc.angle2);
		} break;
		case std::experimental::io2d::path_data_type::change_matrix:
		{
			return make_unique<std::experimental::io2d::change_matrix>(matrix_2d{ _Data.matrix.m00, _Data.matrix.m01, _Data.matrix.m10, _Data.matrix.m11, _Data.matrix.m20, _Data.matrix.m21 });
		} break;
		case std::experimental::io2d::path_data_type::change_origin:
		{
			return make_unique<std::experimental::io2d::change_origin>(point{ _Data.point.x, _Data.point.y });
		} break;
		default:
			assert("Unknown path_data_type" && false);
			ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_PATH_DATA);
			return nullptr;
		}
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return nullptr;
	}
}
