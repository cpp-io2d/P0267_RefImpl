#include "drawing.h"
#include "xdrawinghelpers.h"

using namespace std;
using namespace std::experimental::drawing;

font_face::native_handle_type font_face::native_handle() const {
	return _Font_face.get();
}

font_face::font_face(font_face&& other) {
	_Font_face = move(other._Font_face);
	other._Font_face = nullptr;
}

font_face& font_face::operator=(font_face&& other) {
	if (this != &other) {
		_Font_face = move(other._Font_face);
		other._Font_face = nullptr;
	}
	return *this;
}

font_face::font_face(font_face::native_handle_type nh) {
    _Font_face = shared_ptr<QFont>(nh);
}

font_face::~font_face() {
}
