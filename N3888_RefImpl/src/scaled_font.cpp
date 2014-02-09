#include "drawing.h"
#include "xdrawinghelpers.h"

using namespace std;
using namespace std::experimental::drawing;

scaled_font::native_handle_type scaled_font::native_handle() const {
	return _Scaled_font.get();
}

scaled_font::scaled_font(scaled_font&& other) {
	_Scaled_font = move(other._Scaled_font);
	other._Scaled_font = nullptr;
}

scaled_font& scaled_font::operator=(scaled_font&& other) {
	if (this != &other) {
		_Scaled_font = move(other._Scaled_font);
		other._Scaled_font = nullptr;
	}
	return *this;
}

scaled_font::scaled_font(scaled_font::native_handle_type nh) {
	_Scaled_font = shared_ptr<cairo_scaled_font_t>(nh, &cairo_scaled_font_destroy);
}
