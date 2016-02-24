#include "io2d.h"
#include "xio2dhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

font_face::native_handle_type font_face::native_handle() const noexcept {
	return _Font_face.get();
}

font_face::font_face(font_face&& other) noexcept {
	_Font_face = move(other._Font_face);
	other._Font_face = nullptr;
}

font_face& font_face::operator=(font_face&& other) noexcept {
	if (this != &other) {
		_Font_face = move(other._Font_face);
		other._Font_face = nullptr;
	}
	return *this;
}

font_face::font_face(font_face::native_handle_type nh) {
	_Font_face = shared_ptr<cairo_font_face_t>(nh, &cairo_font_face_destroy);
}

font_face::font_face(font_face::native_handle_type nh, error_code& ec) noexcept {
	try {
		_Font_face = shared_ptr<cairo_font_face_t>(nh, &cairo_font_face_destroy);
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
	}
	catch (const exception&) {
		ec = make_error_code(errc::resource_unavailable_try_again);
	}
	ec.clear();
}

font_face::~font_face() {
}
