#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

device::native_handle_type device::native_handle() const {
	return _Device.get();
}

device::device(device::native_handle_type nh) : _Device() {
	_Device = shared_ptr<cairo_device_t>(nh, &cairo_device_destroy);
	_Throw_if_failed_cairo_status_t(cairo_device_status(_Device.get()));
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
	cairo_device_flush(_Device.get());
}

void device::acquire() {
	_Throw_if_failed_cairo_status_t(cairo_device_acquire(_Device.get()));
}

void device::release() {
	cairo_device_release(_Device.get());
}
