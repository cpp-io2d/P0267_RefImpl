#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

device::native_handle_type device::native_handle() const {
	return _Device.get();
}

device::device(device::native_handle_type nh) : _Device() {

    _Device = shared_ptr<QPaintEngine>(nh);
}

device::device(device&& other) {
	_Device = move(other._Device);
	other._Device = nullptr;
}

device& device::operator=(device&& other) {
	if (this != &other) {
		_Device = move(other._Device);
		other._Device = nullptr;
	}
	return *this;
}

void device::flush() {
}

void device::acquire() {
}

void device::release() {
}
