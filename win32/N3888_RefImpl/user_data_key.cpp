#include "drawing.h"

using namespace std;
using namespace std::experimental::drawing;

atomic<int_fast64_t> user_data_key::_Cnt = 0;

user_data_key::user_data_key() : _Val(++_Cnt) { }

user_data_key::user_data_key(user_data_key&& other) {
	_Val = move(other._Val);
	other._Val = 0;
}

user_data_key& user_data_key::operator=(user_data_key&& other) {
	if (this != &other) {
		_Val = move(other._Val);
		other._Val = 0;
	}
	return *this;
}

int_fast64_t user_data_key::_Get_value() const {
	return _Val;
}
