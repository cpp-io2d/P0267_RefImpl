#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

const char* io2d_error_category::name() const {
	return "io2d";
}

::std::string io2d_error_category::message(int errVal) const {
	auto ev = _Cairo_status_t_to_io2d_error(static_cast<cairo_status_t>(errVal));
	switch (ev) {
	case io2d_error::success:
		return "The operation completed successfully.";
	case io2d_error::no_memory:
		return "The operation failed due to insufficient memory.";
	case io2d_error::invalid_restore:
		return "A call was made to surface::restore for which no prior call to surface::save was made.";
	case io2d_error::invalid_pop_group:
		return "A call was made to surface::pop_group or surface::pop_group_to_source for which no prior call to surface::push_group was made.";
	case io2d_error::no_current_point:
		return "The operation requires a current point but no current point was set. This is usually the result of a call to path_factory::rel_curve_to, path_factory::rel_line_to, or  path_factory::rel_move_to and can be corrected by first establishing a current point with a non-\"rel\" member function call such as path_factory::move_to.";
	case io2d_error::invalid_matrix:
		return "A matrix_2d that the operation depends on is invalid. To be valid a matrix_2d must be invertible.";
	case io2d_error::invalid_status:
		return "An internal error has occurred.";
	case io2d_error::null_pointer:
		return "A null pointer value was unexpectedly encountered.";
	case io2d_error::invalid_string:
		return "A UTF-8 string value was expected but the string is not a valid UTF-8 string.";
	case io2d_error::invalid_path_data:
		return "Invalid data was encountered in a path or a path_factory object.";
	case io2d_error::read_error:
		return "An error occurred while attempting to read data from an input stream.";
	case io2d_error::write_error:
		return "An error occurred while attempting to write data to an output stream.";
	case io2d_error::surface_finished:
		return "An attempt was made to use or manipulate a surface object or surface-derived object which is no longer valid.";
	case io2d_error::surface_type_mismatch:
		return "An operation was attempted on a surface that does not support it.";
	case io2d_error::pattern_type_mismatch:
		return "An operation was attempted on a pattern that does not support it.";
	case io2d_error::invalid_content:
		return "An invalid content value was passed as an argument.";
	case io2d_error::invalid_format:
		return "An invalid format value was passed as an argument.";
	case io2d_error::invalid_visual:
		return "Invalid visual.";
	case io2d_error::file_not_found:
		return "File not found.";
	case io2d_error::invalid_dash:
		return "An invalid dash value was specified in a call to surface::set_dashes.";
	case io2d_error::invalid_dsc_comment:
		return "Invalid dsc comment.";
	case io2d_error::invalid_index:
		return "Invalid index.";
	case io2d_error::clip_not_representable:
		return "A call was made to surface::get_clip_rectangles when the surface object's current clipping region could not be represented with rectangles.";
	case io2d_error::temp_file_error:
		return "Temp file error.";
	case io2d_error::invalid_stride:
		return "An invalid stride value was used. Surface formats may require padding at the end of each row of pixel data depending on the implementation and the current graphics chipset, if any.Use format_stride_for_width to obtain the correct stride value.";
	case io2d_error::font_type_mismatch:
		return "Font type mismatch.";
	case io2d_error::user_font_immutable:
		return "User font immutable.";
	case io2d_error::user_font_error:
		return "User font error.";
	case io2d_error::negative_count:
		return "Negative count.";
	case io2d_error::invalid_clusters:
		return "A call was made to surface::show_text_glyphs with a std::vector<text_clusters> argument that does not properly map the UTF-8 std::string code points to the std::vector<glyph> glyphs.";
	case io2d_error::invalid_slant:
		return "Invalid slant.";
	case io2d_error::invalid_weight:
		return "Invalid weight.";
	case io2d_error::invalid_size:
		return "The input value for a size parameter is incorrect.";
	case io2d_error::user_font_not_implemented:
		return "User fonts are not implemented.";
	case io2d_error::device_type_mismatch:
		return "Device type mismatch.";
	case io2d_error::device_error:
		return "The operation failed. The device encountered an error.";
	case io2d_error::invalid_mesh_construction:
		return "A mesh construction operation on a mesh_pattern_factory object failed. Mesh construction operations are only permitted in between a call to either mesh_pattern_factory::begin_patch or mesh_pattern_factory::begin_edit_patch and mesh_pattern_factory::end_patch.";
	case io2d_error::device_finished:
		return "Device finished.";
	case io2d_error::last_value:
		return "This value is unused.";
	default:
		return "Unknown value";
	}
}

bool io2d_error_category::equivalent(int code, const ::std::error_condition& condition) const {
	return (*this == condition.category())
		&& (static_cast<cairo_status_t>(code) == _Io2d_error_to_cairo_status_t(static_cast<io2d_error>(condition.value())));
}

bool io2d_error_category::equivalent(const ::std::error_code& code, int condition) const {
	// Make sure the error_code's category is of type io2d_error_category
	return (*this == code.category())
		// Make sure the error_code's value (which should be a cairo_status_t) maps to the condition (casted to io2d_error).
		&& (_Cairo_status_t_to_io2d_error(static_cast<cairo_status_t>(code.value())) == static_cast<io2d_error>(condition));
}
