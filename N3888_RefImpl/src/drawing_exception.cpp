
#include "drawing.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

drawing_exception::drawing_exception() noexcept : _Status(experimental::drawing::status::success) { }

drawing_exception::drawing_exception(experimental::drawing::status s) noexcept : _Status(s) { }

drawing_exception::~drawing_exception() noexcept { }

const char * drawing_exception::what() const noexcept {
	return cairo_status_to_string(_Status_to_cairo_status_t(_Status));
}

::std::experimental::drawing::status drawing_exception::status() const noexcept {
	return _Status;
}
