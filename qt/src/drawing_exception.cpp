
#include "drawing.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

drawing_exception::drawing_exception() noexcept : _Status(status::success) { }

drawing_exception::drawing_exception(status s) noexcept : _Status(s) { }

drawing_exception::~drawing_exception() noexcept { }

const char * drawing_exception::what() const noexcept {
	// TODO: FIX
	//return cairo_status_to_string(_Status_to_cairo_status_t(_Status));
	return "";
}

status drawing_exception::get_status() const noexcept {
	return _Status;
}
