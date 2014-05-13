#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

path_builder::path_builder(path_builder&& other)
: _Data(move(other._Data))
, _Has_current_point(move(other._Has_current_point))
, _Current_point(move(other._Current_point)) {
}

path_builder& path_builder::operator=(path_builder&& other) {
    if (this != &other) {
        _Data = move(other._Data);
        _Has_current_point = move(other._Has_current_point);
        _Current_point = move(other._Current_point);
    }
    return *this;
}

path path_builder::get_path() const {
    return path(*this);
}

path path_builder::get_path_flat() const {
    throw runtime_error("Not implemented yet.");
}

bool path_builder::has_current_point() {
    return _Has_current_point;
}

void path_builder::append_path(const path& p) {
    const auto& data = p.get_data_ref();
    for (const auto& item : data) {
        _Data.push_back(item);
    }
}

void path_builder::append_path(const path_builder& p) {
    for (const auto& item : p._Data) {
        _Data.push_back(item);
    }
}

point path_builder::get_current_point() {
    assert(has_current_point());
    return point((*_Data.crend()).point);
}

void path_builder::new_sub_path() {
    path_data pd{ };
    pd.header.type = path_data_type::new_sub_path;
    pd.header.length = 1;
    _Data.push_back(pd);
}

void path_builder::close_path() {
    path_data pd{ };
    pd.header.type = path_data_type::close_path;
    pd.header.length = 1;
    _Data.push_back(pd);
}

void path_builder::arc(const point& center, double radius, double angle1, double angle2) {
    path_data pd{ };
    pd.header.type = path_data_type::arc;
    pd.header.length = 5;
    _Data.push_back(pd);
    pd = { };
    pd.point = center;
    _Data.push_back(pd);
    pd = { };
    pd.value = radius;
    _Data.push_back(pd);
    pd = { };
    pd.value = angle1;
    _Data.push_back(pd);
    pd = { };
    pd.value = angle2;
    _Data.push_back(pd);
}

void path_builder::arc_negative(const point& center, double radius, double angle1, double angle2) {
    path_data pd{ };
    pd.header.type = path_data_type::arc_negative;
    pd.header.length = 5;
    _Data.push_back(pd);
    pd = { };
    pd.point = center;
    _Data.push_back(pd);
    pd = { };
    pd.value = radius;
    _Data.push_back(pd);
    pd = { };
    pd.value = angle1;
    _Data.push_back(pd);
    pd = { };
    pd.value = angle2;
    _Data.push_back(pd);
}

void path_builder::curve_to(const point& pt0, const point& pt1, const point& pt2) {
    path_data pd;
    pd.header.type = path_data_type::curve_to;
    pd.header.length = 4;
    _Data.push_back(pd);
    pd = { };
    pd.point = pt0;
    _Data.push_back(pd);
    pd.point = pt1;
    _Data.push_back(pd);
    pd.point = pt2;
    _Data.push_back(pd);
    _Has_current_point = true;
    _Current_point = pt2;
}

void path_builder::line_to(const point& pt) {
    path_data pd;
    pd.header.type = path_data_type::line_to;
    pd.header.length = 2;
    _Data.push_back(pd);
    pd = { };
    pd.point = pt;
    _Data.push_back(pd);
    _Has_current_point = true;
    _Current_point = pt;
}

void path_builder::move_to(const point& pt) {
    path_data pd;
    pd.header.type = path_data_type::move_to;
    pd.header.length = 2;
    _Data.push_back(pd);
    pd = { };
    pd.point = pt;
    _Data.push_back(pd);
    _Has_current_point = true;
    _Current_point = pt;
}

void path_builder::rectangle(const experimental::drawing::rectangle& rect) {
    move_to({ rect.x, rect.y });
    rel_line_to({ rect.width, 0.0 });
    rel_line_to({ 0.0, rect.height });
    rel_line_to({ -rect.width, 0.0 });
    close_path();
}

void path_builder::rel_curve_to(const point& dpt0, const point& dpt1, const point& dpt2) {
    if (!_Has_current_point) {
        throw drawing_exception(status::no_current_point);
    }
    curve_to(dpt0 + _Current_point, dpt1 + _Current_point, dpt2 + _Current_point);
}

void path_builder::rel_line_to(const point& dpt) {
    if (!_Has_current_point) {
        throw drawing_exception(status::no_current_point);
    }
    line_to(dpt + _Current_point);
}

void path_builder::rel_move_to(const point& dpt) {
    if (!_Has_current_point) {
        throw drawing_exception(status::no_current_point);
    }
    move_to(dpt + _Current_point);
}

vector<path_data> path_builder::get_data() const {
    return vector<path_data>(_Data);
}

const vector<path_data>& path_builder::get_data_ref() const {
    return _Data;
}

vector<path_data>& path_builder::get_data_ref() {
    return _Data;
}

void path_builder::get_path_extents(point& pt0, point& pt1) const {
    throw runtime_error("Not implemented yet.");
}
