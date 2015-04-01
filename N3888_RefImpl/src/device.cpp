#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

device::native_handle_type device::native_handle() const noexcept {
	return _Device.get();
}

device::device(device::native_handle_type nh) : _Device() {
	_Device = shared_ptr<cairo_device_t>(nh, &cairo_device_destroy);
	_Throw_if_failed_cairo_status_t(cairo_device_status(_Device.get()));
}

device::device(device::native_handle_type nh, error_code& ec) noexcept : _Device() {
	_Device = shared_ptr<cairo_device_t>(nh, &cairo_device_destroy);
	if (cairo_device_status(_Device.get()) != CAIRO_STATUS_SUCCESS) {
		ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_DEVICE_ERROR);
	}
	else {
		ec.clear();
	}
}

device::device(device&& other) noexcept {
	_Device = move(other._Device);
	other._Device = nullptr;
}

device& device::operator=(device&& other) noexcept {
	if (this != &other) {
		_Device = move(other._Device);
		other._Device = nullptr;
	}
	return *this;
}

void device::flush() noexcept {
	cairo_device_flush(_Device.get());
}

void device::lock() {
	_Throw_if_failed_cairo_status_t(cairo_device_acquire(_Device.get()));
}

void device::lock(error_code& ec) noexcept {
	if (cairo_device_acquire(_Device.get()) != CAIRO_STATUS_SUCCESS) {
		ec = make_error_code(errc::resource_unavailable_try_again);
	}
	else {
		ec.clear();
	}
}

void device::unlock() noexcept {
	cairo_device_release(_Device.get());
}
