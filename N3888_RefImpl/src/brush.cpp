#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"

using namespace std;
using namespace std::experimental::io2d;

brush::native_handle_type brush::native_handle() const noexcept {
	return _Brush.get();
}

brush::brush(brush::native_handle_type nh) noexcept
	: _Brush(nh, &cairo_pattern_destroy)
	, _Brush_type(_Cairo_pattern_type_t_to_brush_type(cairo_pattern_get_type(nh)))
	, _Extend(::std::experimental::io2d::extend::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
}

brush::brush(brush&& other) noexcept
	: _Brush(move(other._Brush))
	, _Brush_type(move(other._Brush_type))
	, _Extend(move(other._Extend))
	, _Filter(move(other._Filter))
	, _Matrix(move(other._Matrix)) {
	other._Brush = nullptr;
}

brush& brush::operator=(brush&& other) noexcept {
	if (this != &other) {
		_Brush = move(other._Brush);
		_Brush_type = move(other._Brush_type);
		_Extend = move(other._Extend);
		_Filter = move(other._Filter);
		_Matrix = move(other._Matrix);
		other._Brush = nullptr;
	}

	return *this;
}

brush::brush(const solid_color_brush_factory& f)
: _Brush()
, _Brush_type(brush_type::solid_color)
, _Extend(::std::experimental::io2d::extend::none)
, _Filter(::std::experimental::io2d::filter::good)
, _Matrix(matrix_2d::init_identity()) {
	auto color = f.color();
	_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_rgba(color.r(), color.g(), color.b(), color.a()), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
}

brush::brush(const solid_color_brush_factory& f, error_code& ec) noexcept
	: _Brush()
	, _Brush_type(brush_type::solid_color)
	, _Extend(::std::experimental::io2d::extend::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
	auto color = f.color();
	try {
		_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_rgba(color.r(), color.g(), color.b(), color.a()), &cairo_pattern_destroy);
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		return;
	}

	auto status = cairo_pattern_status(_Brush.get());
	if (status != CAIRO_STATUS_SUCCESS) {
		ec = _Cairo_status_t_to_std_error_code(status);
		_Brush.reset();
		return;
	}
	ec.clear();
}

brush::brush(const linear_brush_factory& f)
	: _Brush()
	, _Brush_type(brush_type::linear)
	, _Extend(::std::experimental::io2d::extend::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
	vector_2d lpt0 = f.begin_point();
	vector_2d lpt1 = f.end_point();
	_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_linear(lpt0.x(), lpt0.y(), lpt1.x(), lpt1.y()), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

	auto count = f.color_stop_count();
	for (unsigned int i = 0; i < count; i++) {
		auto stop = f.color_stop(i);
		double& offset = get<0>(stop);
		rgba_color& color = get<1>(stop);
		cairo_pattern_add_color_stop_rgba(_Brush.get(), offset, color.r(), color.g(), color.b(), color.a());
	}
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
}

brush::brush(const linear_brush_factory& f, error_code& ec) noexcept
	: _Brush()
	, _Brush_type(brush_type::linear)
	, _Extend(::std::experimental::io2d::extend::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
	vector_2d lpt0 = f.begin_point();
	vector_2d lpt1 = f.end_point();
	try {
		_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_linear(lpt0.x(), lpt0.y(), lpt1.x(), lpt1.y()), &cairo_pattern_destroy);
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		_Brush.reset();
		return;
	}

	auto status = cairo_pattern_status(_Brush.get());
	if (status != CAIRO_STATUS_SUCCESS) {
		ec = _Cairo_status_t_to_std_error_code(status);
		_Brush.reset();
		return;
	}

	auto count = f.color_stop_count();
	for (unsigned int i = 0; i < count; i++) {
		auto stop = f.color_stop(i);
		double& offset = get<0>(stop);
		rgba_color& color = get<1>(stop);
		cairo_pattern_add_color_stop_rgba(_Brush.get(), offset, color.r(), color.g(), color.b(), color.a());
	}
	status = cairo_pattern_status(_Brush.get());
	if (status != CAIRO_STATUS_SUCCESS) {
		ec = _Cairo_status_t_to_std_error_code(status);
		_Brush.reset();
		return;
	}
	ec.clear();
}

brush::brush(const radial_brush_factory& f)
	: _Brush()
	, _Brush_type(brush_type::radial)
	, _Extend(::std::experimental::io2d::extend::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
	auto points = f.radial_circles();
	vector_2d& center0 = get<0>(points);
	double& radius0 = get<1>(points);
	vector_2d& center1 = get<2>(points);
	double& radius1 = get<3>(points);
	_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(center0.x(), center0.y(), radius0, center1.x(), center1.y(), radius1), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));

	auto count = f.color_stop_count();
	for (unsigned int i = 0; i < count; i++) {
		auto stop = f.color_stop(i);
		double& offset = get<0>(stop);
		rgba_color& color = get<1>(stop);
		cairo_pattern_add_color_stop_rgba(_Brush.get(), offset, color.r(), color.g(), color.b(), color.a());
	}
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
}

brush::brush(const radial_brush_factory& f, error_code& ec) noexcept
	: _Brush()
	, _Brush_type(brush_type::radial)
	, _Extend(::std::experimental::io2d::extend::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
	auto points = f.radial_circles();
	vector_2d& center0 = get<0>(points);
	double& radius0 = get<1>(points);
	vector_2d& center1 = get<2>(points);
	double& radius1 = get<3>(points);
	try {
		_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(center0.x(), center0.y(), radius0, center1.x(), center1.y(), radius1), &cairo_pattern_destroy);
	}
	catch (const bad_alloc&) {
		ec = make_error_code(errc::not_enough_memory);
		_Brush.reset();
		return;
	}

	auto status = cairo_pattern_status(_Brush.get());
	if (status != CAIRO_STATUS_SUCCESS) {
		ec = _Cairo_status_t_to_std_error_code(status);
		_Brush.reset();
		return;
	}

	auto count = f.color_stop_count();
	for (unsigned int i = 0; i < count; i++) {
		auto stop = f.color_stop(i);
		double& offset = get<0>(stop);
		rgba_color& color = get<1>(stop);
		cairo_pattern_add_color_stop_rgba(_Brush.get(), offset, color.r(), color.g(), color.b(), color.a());
	}
	status = cairo_pattern_status(_Brush.get());
	if (status != CAIRO_STATUS_SUCCESS) {
		ec = _Cairo_status_t_to_std_error_code(status);
		_Brush.reset();
		return;
	}
	ec.clear();
}

//brush::brush(const mesh_brush_factory& f)
//	: _Brush()
//	, _Brush_type(brush_type::mesh)
//	, _Extend(::std::experimental::io2d::extend::none)
//	, _Filter(::std::experimental::io2d::filter::good)
//	, _Matrix(matrix_2d::init_identity()) {
//	_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_mesh(), &cairo_pattern_destroy);
//	auto pat = _Brush.get();
//	_Throw_if_failed_cairo_status_t(cairo_pattern_status(pat));
//
//	auto count = f.patch_count();
//	for (auto patchNum = 0U; patchNum < count; patchNum++) {
//		cairo_mesh_pattern_begin_patch(pat);
//		auto pathFactory = f.path_factory(patchNum);
//		const auto& pathData = pathFactory.data_ref();
//		auto pdSize = pathData.size();
//		for (unsigned int pdIndex = 0; pdIndex < pdSize; pdIndex++) {
//			const auto& item = pathData[pdIndex];
//			auto type = item.type();
//			switch (type) {
//			case std::experimental::io2d::path_data_type::move_to:
//			{
//				auto pt = item.get<path_data_item::move_to>().to();
//				cairo_mesh_pattern_move_to(pat, pt.x(), pt.y());
//			} break;
//			case std::experimental::io2d::path_data_type::line_to:
//			{
//				auto pt = item.get<path_data_item::line_to>().to();
//				cairo_mesh_pattern_line_to(pat, pt.x(), pt.y());
//			} break;
//			case std::experimental::io2d::path_data_type::curve_to:
//			{
//				auto dataItem = item.get<path_data_item::curve_to>();
//				cairo_mesh_pattern_curve_to(pat, dataItem.control_point_1().x(), dataItem.control_point_1().y(), dataItem.control_point_2().x(), dataItem.control_point_2().y(), dataItem.end_point().x(), dataItem.end_point().y());
//			} break;
//			case std::experimental::io2d::path_data_type::new_sub_path:
//			{
//				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//			} break;
//			case std::experimental::io2d::path_data_type::close_path:
//			{
//				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//			} break;
//			case std::experimental::io2d::path_data_type::rel_move_to:
//			{
//				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//			} break;
//			case std::experimental::io2d::path_data_type::rel_line_to:
//			{
//				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//			} break;
//			case std::experimental::io2d::path_data_type::rel_curve_to:
//			{
//				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//			} break;
//			case std::experimental::io2d::path_data_type::arc:
//			{
//				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//			} break;
//			case std::experimental::io2d::path_data_type::arc_negative:
//			{
//				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//			} break;
//			case std::experimental::io2d::path_data_type::change_matrix:
//			{
//				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//			} break;
//			case std::experimental::io2d::path_data_type::change_origin:
//			{
//				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//			} break;
//			default:
//			{
//				_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//			} break;
//			}
//		}
//
//		for (auto pointNum = 0U; pointNum < 4U; pointNum++) {
//			vector_2d pt;
//			if (f.control_point(patchNum, pointNum, pt)) {
//				cairo_mesh_pattern_set_control_point(pat, pointNum, pt.x(), pt.y());
//			}
//		}
//		for (auto cornerNum = 0U; cornerNum < 4U; cornerNum++) {
//			rgba_color color;
//			if (f.corner_color(patchNum, cornerNum, color)) {
//				cairo_mesh_pattern_set_corner_color_rgba(pat, cornerNum, color.r(), color.g(), color.b(), color.a());
//			}
//		}
//		cairo_mesh_pattern_end_patch(pat);
//	}
//	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
//}
//
//brush::brush(const mesh_brush_factory& f, error_code& ec) noexcept
//	: _Brush()
//	, _Brush_type(brush_type::mesh)
//	, _Extend(::std::experimental::io2d::extend::none)
//	, _Filter(::std::experimental::io2d::filter::good)
//	, _Matrix(matrix_2d::init_identity()) {
//	_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_mesh(), &cairo_pattern_destroy);
//	auto pat = _Brush.get();
//	auto status = cairo_pattern_status(pat);
//	if (status != CAIRO_STATUS_SUCCESS) {
//		ec = _Cairo_status_t_to_std_error_code(status);
//		_Brush.reset();
//		return;
//	}
//
//	auto count = f.patch_count();
//	for (auto patchNum = 0U; patchNum < count; patchNum++) {
//		cairo_mesh_pattern_begin_patch(pat);
//		auto pathFactory = f.path_factory(patchNum, ec);
//		if (static_cast<bool>(ec)) {
//			_Brush.reset();
//			return;
//		}
//		const auto& pathData = pathFactory.data_ref();
//		auto pdSize = pathData.size();
//		for (unsigned int pdIndex = 0; pdIndex < pdSize; pdIndex++) {
//			const auto& item = pathData[pdIndex];
//			auto type = item.type();
//			switch (type) {
//			case std::experimental::io2d::path_data_type::move_to:
//			{
//				auto pt = item.get<path_data_item::move_to>().to();
//				cairo_mesh_pattern_move_to(pat, pt.x(), pt.y());
//			} break;
//			case std::experimental::io2d::path_data_type::line_to:
//			{
//				auto pt = item.get<path_data_item::line_to>().to();
//				cairo_mesh_pattern_line_to(pat, pt.x(), pt.y());
//			} break;
//			case std::experimental::io2d::path_data_type::curve_to:
//			{
//				auto dataItem = item.get<path_data_item::curve_to>();
//				cairo_mesh_pattern_curve_to(pat, dataItem.control_point_1().x(), dataItem.control_point_1().y(), dataItem.control_point_2().x(), dataItem.control_point_2().y(), dataItem.end_point().x(), dataItem.end_point().y());
//			} break;
//			case std::experimental::io2d::path_data_type::new_sub_path:
//			{
//				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//				_Brush.reset();
//			} return;
//			case std::experimental::io2d::path_data_type::close_path:
//			{
//				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//				_Brush.reset();
//			} return;
//			case std::experimental::io2d::path_data_type::rel_move_to:
//			{
//				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//				_Brush.reset();
//			} return;
//			case std::experimental::io2d::path_data_type::rel_line_to:
//			{
//				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//				_Brush.reset();
//			} return;
//			case std::experimental::io2d::path_data_type::rel_curve_to:
//			{
//				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//				_Brush.reset();
//			} return;
//			case std::experimental::io2d::path_data_type::arc:
//			{
//				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//				_Brush.reset();
//			} return;
//			case std::experimental::io2d::path_data_type::arc_negative:
//			{
//				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//				_Brush.reset();
//			} return;
//			case std::experimental::io2d::path_data_type::change_matrix:
//			{
//				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//				_Brush.reset();
//			} return;
//			case std::experimental::io2d::path_data_type::change_origin:
//			{
//				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//				_Brush.reset();
//			} return;
//			default:
//			{
//				ec = _Cairo_status_t_to_std_error_code(CAIRO_STATUS_INVALID_MESH_CONSTRUCTION);
//				_Brush.reset();
//			} return;
//			}
//		}
//
//		for (auto pointNum = 0U; pointNum < 4U; pointNum++) {
//			vector_2d pt;
//			if (f.control_point(patchNum, pointNum, pt, ec)) {
//				if (static_cast<bool>(ec)) {
//					_Brush.reset();
//					return;
//				}
//				cairo_mesh_pattern_set_control_point(pat, pointNum, pt.x(), pt.y());
//			}
//			if (static_cast<bool>(ec)) {
//				_Brush.reset();
//				return;
//			}
//		}
//		for (auto cornerNum = 0U; cornerNum < 4U; cornerNum++) {
//			rgba_color color;
//			if (f.corner_color(patchNum, cornerNum, color, ec)) {
//				if (static_cast<bool>(ec)) {
//					_Brush.reset();
//					return;
//				}
//				cairo_mesh_pattern_set_corner_color_rgba(pat, cornerNum, color.r(), color.g(), color.b(), color.a());
//			}
//			if (static_cast<bool>(ec)) {
//				_Brush.reset();
//				return;
//			}
//		}
//		cairo_mesh_pattern_end_patch(pat);
//	}
//	status = cairo_pattern_status(pat);
//	if (status != CAIRO_STATUS_SUCCESS) {
//		ec = _Cairo_status_t_to_std_error_code(status);
//		_Brush.reset();
//		return;
//	}
//	ec.clear();
//}

brush::brush(surface_brush_factory& f)
	: _Brush()
	, _Brush_type(brush_type::surface)
	, _Extend(::std::experimental::io2d::extend::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
	if (!f.has_surface()) {
		_Throw_if_failed_cairo_status_t(CAIRO_STATUS_NULL_POINTER);
	}
	auto brushSurface = _Surface_create_image_surface_copy(*f._Surface.get());
	_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_for_surface(brushSurface.native_handle().csfce), &cairo_pattern_destroy);
	_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
}

brush::brush(surface_brush_factory& f, error_code& ec) noexcept
	: _Brush()
	, _Brush_type(brush_type::surface)
	, _Extend(::std::experimental::io2d::extend::none)
	, _Filter(::std::experimental::io2d::filter::good)
	, _Matrix(matrix_2d::init_identity()) {
	// I haven't implemented noexcept in image_surface yet...
	ec = make_error_code(errc::not_supported);

	//auto brushSurface = _Surface_create_image_surface_copy(f._Surface);
	//_Brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_for_surface(brushSurface.native_handle().csfce), &cairo_pattern_destroy);
	//_Throw_if_failed_cairo_status_t(cairo_pattern_status(_Brush.get()));
}

void brush::extend(::std::experimental::io2d::extend e) noexcept {
	_Extend = e;
}

void brush::filter(::std::experimental::io2d::filter f) noexcept {
	_Filter = f;
}

void brush::matrix(const matrix_2d& m) noexcept {
	_Matrix = m;
}

::std::experimental::io2d::extend brush::extend() const noexcept {
	return _Extend;
}

::std::experimental::io2d::filter brush::filter() const noexcept {
	return _Filter;
}

matrix_2d brush::matrix() const noexcept {
	return _Matrix;
}

brush_type brush::type() const noexcept {
	return _Brush_type;
}
