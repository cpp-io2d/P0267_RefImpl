#include "io2d.h"

using namespace std;
using namespace std::experimental::io2d;

const char* io2d_error_category::name() const noexcept {
	return "io2d";
}

::std::string io2d_error_category::message(int errVal) const {
	io2d_error ev;
	if (_Cairo_status_t_to_io2d_error(static_cast<cairo_status_t>(errVal), ev)) {
		assert(false && "The provided errVal has no error message associated with it.");
	}
	switch (ev) {
	case io2d_error::success:
		return "The operation completed successfully.";
	case io2d_error::invalid_restore:
		return "A call was made to surface::restore for which no prior call to surface::save was made.";
	case io2d_error::invalid_matrix:
		return "A matrix_2d that the operation depends on is invalid. To be valid a matrix_2d must be invertible.";
	case io2d_error::invalid_status:
		return "An internal error has occurred.";
	case io2d_error::null_pointer:
		return "A null pointer value was unexpectedly encountered.";
	case io2d_error::invalid_string:
		return "A UTF-8 string value was expected but the string is not a valid UTF-8 string.";
	case io2d_error::invalid_path_data:
		return "Invalid data was encountered in a path_group or a path_builder object.";
	case io2d_error::read_error:
		return "An error occurred while attempting to read data from an input stream.";
	case io2d_error::write_error:
		return "An error occurred while attempting to write data to an output stream.";
	case io2d_error::surface_finished:
		return "An attempt was made to use or manipulate a surface object or surface-derived object which is no longer valid.";
	case io2d_error::invalid_dash:
		return "An invalid dash value was specified in a call to surface::dashes.";
	case io2d_error::invalid_index:
		return "An invalid index value was specified.";
	case io2d_error::clip_not_representable:
		return "A call was made to surface::clip_rectangles when the surface object's current clipping region could not be represented with rectangles.";
	case io2d_error::invalid_stride:
		return "An invalid stride value was used. Surface formats may require padding at the end of each row of pixel data depending on the implementation and the current graphics chipset, if any.Use format_stride_for_width to obtain the correct stride value.";
	case io2d_error::user_font_immutable:
		return "User font immutable.";
	case io2d_error::user_font_error:
		return "User font error.";
	case io2d_error::invalid_clusters:
		return "A call was made to surface::show_text_glyphs with a std::vector<text_clusters> argument that does not properly map the UTF-8 std::string code points to the std::vector<glyph> glyphs.";
	case io2d_error::device_error:
		return "The operation failed. The device encountered an error.";
	case io2d_error::invalid_mesh_construction:
		return "A mesh construction operation on a mesh_brush_factory object failed. Mesh construction operations are only permitted in between a call to either mesh_brush_factory::begin_patch or mesh_brush_factory::begin_replace_patch and mesh_brush_factory::end_patch.";
	default:
		return "Unknown value";
	}
}

bool io2d_error_category::equivalent(int code, const ::std::error_condition& condition) const noexcept {
	return (*this == condition.category())
		&& (static_cast<cairo_status_t>(code) == _Io2d_error_to_cairo_status_t(static_cast<io2d_error>(condition.value())));
}

bool io2d_error_category::equivalent(const ::std::error_code& code, int condition) const noexcept {
	io2d_error value;
	auto result = _Cairo_status_t_to_io2d_error(static_cast<cairo_status_t>(code.value()), value);
	// Make sure the error_code's category is of type io2d_error_category
	return (*this == code.category())
		// Make sure the error_code's value (which should be a cairo_status_t) maps to the condition (casted to io2d_error).
		&& result && value == static_cast<io2d_error>(condition);
}
