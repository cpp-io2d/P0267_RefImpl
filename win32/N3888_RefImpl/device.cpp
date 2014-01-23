#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

device::native_handle_type device::native_handle() const {
	return _Device.get();
}

device::device(device::native_handle_type nh) : _Device(), _User_data_map(new ::std::map<user_data_key, ::std::shared_ptr<void>>) {
	_Device = shared_ptr<cairo_device_t>(nh, &cairo_device_destroy);
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_device_status(_Device.get())));
}

device::device(device&& other) {
	_Device = move(other._Device);
	_User_data_map = move(other._User_data_map);
	other._Device = nullptr;
	other._User_data_map = nullptr;
}

device& device::operator=(device&& other) {
	if (this != &other) {
		_Device = move(other._Device);
		_User_data_map = move(other._User_data_map);
		other._Device = nullptr;
		other._User_data_map = nullptr;
	}
	return *this;
}

status device::status() {
	return _Cairo_status_t_to_status(cairo_device_status(_Device.get()));
}

void device::finish() {
	cairo_device_finish(_Device.get());
}

void device::flush() {
	cairo_device_flush(_Device.get());
}

void device::set_user_data(const user_data_key& key, shared_ptr<void>& value) {
	assert((sizeof(void *) >= sizeof(int_fast64_t)) || ((sizeof(void *) == 4) && (key._Get_value() <= INT32_MAX)));
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_device_set_user_data(_Device.get(), reinterpret_cast<cairo_user_data_key_t*>(key._Get_value()), value.get(), nullptr)));
	(*_User_data_map.get())[key] = value;
}

shared_ptr<void>& device::get_user_data(const user_data_key& key) {
	return (*_User_data_map.get())[key];
}

void device::acquire() {
	_Throw_if_failed_status(_Cairo_status_t_to_status(cairo_device_acquire(_Device.get())));
}

void device::release() {
	cairo_device_release(_Device.get());
}
