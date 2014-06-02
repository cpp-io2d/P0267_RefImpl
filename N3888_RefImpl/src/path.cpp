#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

path::path(const path_builder& pb)
: _Data(pb._Data)
, _Has_current_point(pb._Has_current_point)
, _Current_point(pb._Current_point)
, _Extents_pt0(pb._Extents_pt0)
, _Extents_pt1(pb._Extents_pt1) {
}

path::path(path&& other)
: _Data(move(other._Data))
, _Has_current_point(move(other._Has_current_point))
, _Current_point(move(other._Current_point))
, _Extents_pt0(move(other._Extents_pt0))
, _Extents_pt1(move(other._Extents_pt0)) {
}

path& path::operator=(path&& other) {
	if (this != &other) {
		_Data = move(other._Data);
		_Has_current_point = move(other._Has_current_point);
		_Current_point = move(other._Current_point);
		_Extents_pt0 = move(other._Extents_pt0);
		_Extents_pt1 = move(other._Extents_pt1);
	}
	return *this;
}

vector<path_data> path::get_data() const {
	return vector<path_data>(_Data);
}

const vector<path_data>& path::get_data_ref() const {
	return _Data;
}

void path::get_path_extents(point& pt0, point& pt1) const {
	pt0 = _Extents_pt0;
	pt1 = _Extents_pt1;
}
