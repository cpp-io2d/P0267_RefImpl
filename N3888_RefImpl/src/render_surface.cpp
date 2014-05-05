#include "drawing.h"
#include "xdrawinghelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::drawing;

//render_surface::render_surface(format fmt, int width, int height)
//: image_surface(nullptr) {
//    _Surface = shared_ptr<cairo_surface_t>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), &cairo_surface_destroy);
//    _Throw_if_failed_status(_Cairo_status_t_to_status(cairo_surface_status(_Surface.get())));
//}
//
//void render_surface::set_data(vector<unsigned char>& data) {
//    auto expected_size = static_cast<size_t>(get_stride() * get_height());
//    if (data.size() != static_cast<uint64_t>(expected_size)) {
//        throw drawing_exception(::std::experimental::drawing::status::invalid_stride);
//    }
//    if (_Surface.get() == nullptr) {
//        throw drawing_exception(::std::experimental::drawing::status::null_pointer);
//    }
//    auto imageData = cairo_image_surface_get_data(_Surface.get());
//    if (imageData == nullptr) {
//        throw drawing_exception(::std::experimental::drawing::status::null_pointer);
//    }
//    ::std::memcpy(imageData, data.data(), expected_size);
//}
//
