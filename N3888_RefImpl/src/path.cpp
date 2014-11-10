#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

path::path(const path_factory& pb)
: _Data(new vector<unique_ptr<path_data>>)
, _Has_current_point()
, _Current_point()
, _Extents() {
	lock_guard<recursive_mutex> lg(pb._Lock);
	for (const auto& item : pb.get_data_ref()) {
		auto type = item->type();
		switch (type) {
		case std::experimental::io2d::path_data_type::move_to:
		{
			auto dataItem = dynamic_cast<move_to_path_data*>(item.get());
			_Data->emplace_back(new move_to_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::line_to:
		{
			auto dataItem = dynamic_cast<line_to_path_data*>(item.get());
			_Data->emplace_back(new line_to_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::curve_to:
		{
			auto dataItem = dynamic_cast<curve_to_path_data*>(item.get());
			_Data->emplace_back(new curve_to_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::new_sub_path:
		{
			auto dataItem = dynamic_cast<new_sub_path_path_data*>(item.get());
			_Data->emplace_back(new new_sub_path_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::close_path:
		{
			auto dataItem = dynamic_cast<close_path_path_data*>(item.get());
			_Data->emplace_back(new close_path_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::rel_move_to:
		{
			auto dataItem = dynamic_cast<rel_move_to_path_data*>(item.get());
			_Data->emplace_back(new rel_move_to_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::rel_line_to:
		{
			auto dataItem = dynamic_cast<rel_line_to_path_data*>(item.get());
			_Data->emplace_back(new rel_line_to_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::rel_curve_to:
		{
			auto dataItem = dynamic_cast<rel_curve_to_path_data*>(item.get());
			_Data->emplace_back(new rel_curve_to_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::arc:
		{
			auto dataItem = dynamic_cast<arc_path_data*>(item.get());
			_Data->emplace_back(new arc_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			auto dataItem = dynamic_cast<arc_negative_path_data*>(item.get());
			_Data->emplace_back(new arc_negative_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::change_matrix:
		{
			auto dataItem = dynamic_cast<change_matrix_path_data*>(item.get());
			_Data->emplace_back(new change_matrix_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::change_origin:
		{
			auto dataItem = dynamic_cast<change_origin_path_data*>(item.get());
			_Data->emplace_back(new change_origin_path_data(*dataItem));
		} break;
		default:
			assert("Unknown path_data_type" && false);
			break;
		}
	}
	_Has_current_point = pb._Has_current_point;
	_Current_point = pb._Current_point;
	_Last_move_to_point = pb._Last_move_to_point;
	_Extents = pb.get_path_extents();
}

path::path(path&& other)
: _Data(move(other._Data))
, _Has_current_point(move(other._Has_current_point))
, _Current_point(move(other._Current_point))
, _Last_move_to_point(move(other._Last_move_to_point))
, _Extents(move(other._Extents)) {
}

path& path::operator=(path&& other) {
	if (this != &other) {
		_Data = move(other._Data);
		_Has_current_point = move(other._Has_current_point);
		_Current_point = move(other._Current_point);
		_Last_move_to_point = move(other._Last_move_to_point);
		_Extents = move(other._Extents);
	}
	return *this;
}

vector<unique_ptr<path_data>> path::get_data() const {
	vector<unique_ptr<path_data>> result;
	for (const auto& item : *_Data) {
		auto type = item->type();
		switch (type) {
		case std::experimental::io2d::path_data_type::move_to:
		{
			auto dataItem = dynamic_cast<move_to_path_data*>(item.get());
			result.emplace_back(new move_to_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::line_to:
		{
			auto dataItem = dynamic_cast<line_to_path_data*>(item.get());
			result.emplace_back(new line_to_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::curve_to:
		{
			auto dataItem = dynamic_cast<curve_to_path_data*>(item.get());
			result.emplace_back(new curve_to_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::new_sub_path:
		{
			auto dataItem = dynamic_cast<new_sub_path_path_data*>(item.get());
			result.emplace_back(new new_sub_path_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::close_path:
		{
			auto dataItem = dynamic_cast<close_path_path_data*>(item.get());
			result.emplace_back(new close_path_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::rel_move_to:
		{
			auto dataItem = dynamic_cast<rel_move_to_path_data*>(item.get());
			result.emplace_back(new rel_move_to_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::rel_line_to:
		{
			auto dataItem = dynamic_cast<rel_line_to_path_data*>(item.get());
			result.emplace_back(new rel_line_to_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::rel_curve_to:
		{
			auto dataItem = dynamic_cast<rel_curve_to_path_data*>(item.get());
			result.emplace_back(new rel_curve_to_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::arc:
		{
			auto dataItem = dynamic_cast<arc_path_data*>(item.get());
			result.emplace_back(new arc_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::arc_negative:
		{
			auto dataItem = dynamic_cast<arc_negative_path_data*>(item.get());
			result.emplace_back(new arc_negative_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::change_matrix:
		{
			auto dataItem = dynamic_cast<change_matrix_path_data*>(item.get());
			result.emplace_back(new change_matrix_path_data(*dataItem));
		} break;
		case std::experimental::io2d::path_data_type::change_origin:
		{
			auto dataItem = dynamic_cast<change_origin_path_data*>(item.get());
			result.emplace_back(new change_origin_path_data(*dataItem));
		} break;
		default:
			assert("Unknown path_data_type" && false);
			break;
		}
	}
	return result;
}

const vector<unique_ptr<path_data>>& path::get_data_ref() const {
	return *_Data;
}

rectangle path::get_path_extents() const {
	return _Extents;
}
