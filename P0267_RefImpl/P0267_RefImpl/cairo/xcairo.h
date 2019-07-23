#pragma once

#ifndef _XCAIRO_
#define _XCAIRO_

#include <cairo.h>
#include "xio2d.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Cairo {
			_IO2D_API void _Init_graphics_magic();

			constexpr const wchar_t* _Refimpl_window_class_name = L"_P0267RefImplCairoRenderer_FF2B4C8D-0AB8-4343-AA02-6D0857E9FA21";

			template <class GraphicsMath>
			struct _Cairo_graphics_surfaces {
				using graphics_math_type = GraphicsMath;
				using _Graphics_surfaces_type = _Cairo_graphics_surfaces;
				using graphics_surfaces_type = _Cairo_graphics_surfaces;

				struct additional_image_file_formats {
					const static int _Base = 10000;
					const static image_file_format bmp = static_cast<image_file_format>(_Base + 0);
					const static image_file_format tga = static_cast<image_file_format>(_Base + 1);
					const static image_file_format dib = static_cast<image_file_format>(_Base + 2);
					const static image_file_format gif = static_cast<image_file_format>(_Base + 3);
					const static image_file_format pcx = static_cast<image_file_format>(_Base + 4);
					const static image_file_format pbm = static_cast<image_file_format>(_Base + 5);
					const static image_file_format pgm = static_cast<image_file_format>(_Base + 6);
					const static image_file_format ppm = static_cast<image_file_format>(_Base + 7);
					const static image_file_format psd = static_cast<image_file_format>(_Base + 8);
					const static image_file_format xbm = static_cast<image_file_format>(_Base + 10);
					const static image_file_format xpm = static_cast<image_file_format>(_Base + 11);

					struct read_only {
						const static int _Base = 20000;
						const static image_file_format xcf = static_cast<image_file_format>(_Base + 0);
						const static image_file_format ico = static_cast<image_file_format>(_Base + 1);
					};

					struct write_only {
						const static int _Base = 30000;
						// None
					};
				};

				struct paths {
					struct _Abs_new_figure_data {
						basic_point_2d<GraphicsMath> pt;
					};
					using abs_new_figure_data_type = _Abs_new_figure_data;
					static abs_new_figure_data_type create_abs_new_figure();
					static abs_new_figure_data_type create_abs_new_figure(const basic_point_2d<GraphicsMath>& pt);
					static abs_new_figure_data_type copy_abs_new_figure(const abs_new_figure_data_type& data);
					static abs_new_figure_data_type move_abs_new_figure(abs_new_figure_data_type&& data) noexcept;
					static void destroy(abs_new_figure_data_type& data) noexcept;
					static void at(abs_new_figure_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static basic_point_2d<GraphicsMath> at(const abs_new_figure_data_type& data) noexcept;

					struct _Rel_new_figure_data {
						basic_point_2d<GraphicsMath> pt;
					};
					using rel_new_figure_data_type = _Rel_new_figure_data;
					static rel_new_figure_data_type create_rel_new_figure();
					static rel_new_figure_data_type create_rel_new_figure(const basic_point_2d<GraphicsMath>& pt);
					static rel_new_figure_data_type copy_rel_new_figure(const rel_new_figure_data_type& data);
					static rel_new_figure_data_type move_rel_new_figure(rel_new_figure_data_type&& data) noexcept;
					static void destroy(rel_new_figure_data_type& data) noexcept;
					static void at(rel_new_figure_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static basic_point_2d<GraphicsMath> at(const rel_new_figure_data_type& data) noexcept;

					struct _Close_figure_data {
					};
					using close_figure_data_type = _Close_figure_data;
					static close_figure_data_type create_close_figure();
					static close_figure_data_type copy_close_figure(const close_figure_data_type& data);
					static close_figure_data_type move_close_figure(close_figure_data_type&& data) noexcept;
					static void destroy(close_figure_data_type& data) noexcept;

					struct _Abs_matrix_data {
						basic_matrix_2d<GraphicsMath> m;
					};
					using abs_matrix_data_type = _Abs_matrix_data;
					static abs_matrix_data_type create_abs_matrix();
					static abs_matrix_data_type create_abs_matrix(const basic_matrix_2d<GraphicsMath>& m);
					static abs_matrix_data_type copy_abs_matrix(const abs_matrix_data_type& data);
					static abs_matrix_data_type move_abs_matrix(abs_matrix_data_type&& data) noexcept;
					static void destroy(abs_matrix_data_type& data) noexcept;
					static void matrix(abs_matrix_data_type& data, const basic_matrix_2d<GraphicsMath>& m);
					static basic_matrix_2d<GraphicsMath> matrix(const abs_matrix_data_type& data) noexcept;

					struct _Rel_matrix_data {
						basic_matrix_2d<GraphicsMath> m;
					};
					using rel_matrix_data_type = _Rel_matrix_data;
					static rel_matrix_data_type create_rel_matrix();
					static rel_matrix_data_type create_rel_matrix(const basic_matrix_2d<GraphicsMath>& m);
					static rel_matrix_data_type copy_rel_matrix(const rel_matrix_data_type& data);
					static rel_matrix_data_type move_rel_matrix(rel_matrix_data_type&& data) noexcept;
					static void destroy(rel_matrix_data_type& data) noexcept;
					static void matrix(rel_matrix_data_type& data, const basic_matrix_2d<GraphicsMath>& m);
					static basic_matrix_2d<GraphicsMath> matrix(const rel_matrix_data_type& data) noexcept;

					struct _Revert_matrix_data {
					};
					using revert_matrix_data_type = _Revert_matrix_data;
					static revert_matrix_data_type create_revert_matrix();
					static revert_matrix_data_type copy_revert_matrix(const revert_matrix_data_type& data);
					static revert_matrix_data_type move_revert_matrix(revert_matrix_data_type&& data) noexcept;
					static void destroy(revert_matrix_data_type& data) noexcept;

					struct _Abs_cubic_curve_data {
						basic_point_2d<GraphicsMath> cpt1;
						basic_point_2d<GraphicsMath> cpt2;
						basic_point_2d<GraphicsMath> ept;
					};
					using abs_cubic_curve_data_type = _Abs_cubic_curve_data;
					static abs_cubic_curve_data_type create_abs_cubic_curve();
					static abs_cubic_curve_data_type create_abs_cubic_curve(const basic_point_2d<GraphicsMath>& cpt1, const basic_point_2d<GraphicsMath>& cpt2, const basic_point_2d<GraphicsMath>& ept);
					static abs_cubic_curve_data_type copy_abs_cubic_curve(const abs_cubic_curve_data_type& data);
					static abs_cubic_curve_data_type move_abs_cubic_curve(abs_cubic_curve_data_type&& data) noexcept;
					static void destroy(abs_cubic_curve_data_type& data) noexcept;
					static void control_pt1(abs_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static void control_pt2(abs_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static void end_pt(abs_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static basic_point_2d<GraphicsMath> control_pt1(const abs_cubic_curve_data_type& data) noexcept;
					static basic_point_2d<GraphicsMath> control_pt2(const abs_cubic_curve_data_type& data) noexcept;
					static basic_point_2d<GraphicsMath> end_pt(const abs_cubic_curve_data_type& data) noexcept;

					struct _Abs_line_data {
						basic_point_2d<GraphicsMath> pt;
					};
					using abs_line_data_type = _Abs_line_data;
					static abs_line_data_type create_abs_line();
					static abs_line_data_type create_abs_line(const basic_point_2d<GraphicsMath>& pt);
					static abs_line_data_type copy_abs_line(const abs_line_data_type& data);
					static abs_line_data_type move_abs_line(abs_line_data_type&& data) noexcept;
					static void destroy(abs_line_data_type& data) noexcept;
					static void to(abs_line_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static basic_point_2d<GraphicsMath> to(const abs_line_data_type& data) noexcept;

					struct _Abs_quadratic_curve_data {
						basic_point_2d<GraphicsMath> cpt;
						basic_point_2d<GraphicsMath> ept;
					};
					using abs_quadratic_curve_data_type = _Abs_quadratic_curve_data;
					static abs_quadratic_curve_data_type create_abs_quadratic_curve();
					static abs_quadratic_curve_data_type create_abs_quadratic_curve(const basic_point_2d<GraphicsMath>& cpt, const basic_point_2d<GraphicsMath>& ept);
					static abs_quadratic_curve_data_type copy_abs_quadratic_curve(const abs_quadratic_curve_data_type& data);
					static abs_quadratic_curve_data_type move_abs_quadratic_curve(abs_quadratic_curve_data_type&& data) noexcept;
					static void destroy(abs_quadratic_curve_data_type& data) noexcept;
					static void control_pt(abs_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static void end_pt(abs_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static basic_point_2d<GraphicsMath> control_pt(const abs_quadratic_curve_data_type& data) noexcept;
					static basic_point_2d<GraphicsMath> end_pt(const abs_quadratic_curve_data_type& data);

					struct _Arc_data {
						basic_point_2d<GraphicsMath> radius;
						float rotation = {};
						float startAngle = {};
					};
					using arc_data_type = _Arc_data;
					static arc_data_type create_arc();
					static arc_data_type create_arc(const basic_point_2d<GraphicsMath>& rad, float rot, float sang);
					static arc_data_type copy_arc(const arc_data_type& data);
					static arc_data_type move_arc(arc_data_type&& data) noexcept;
					static void destroy(arc_data_type& data) noexcept;
					static void radius(arc_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static void rotation(arc_data_type& data, float rot);
					static void start_angle(arc_data_type& data, float sang);
					static basic_point_2d<GraphicsMath> radius(const arc_data_type& data) noexcept;
					static float rotation(const arc_data_type& data) noexcept;
					static float start_angle(const arc_data_type& data) noexcept;
					static basic_point_2d<GraphicsMath> center(const arc_data_type& data, const basic_point_2d<GraphicsMath>& cpt, const basic_matrix_2d<GraphicsMath>& m) noexcept;
					static basic_point_2d<GraphicsMath> end_pt(const arc_data_type& data, const basic_point_2d<GraphicsMath>& cpt, const basic_matrix_2d<GraphicsMath>& m) noexcept;

					struct _Rel_cubic_curve_data {
						basic_point_2d<GraphicsMath> cpt1;
						basic_point_2d<GraphicsMath> cpt2;
						basic_point_2d<GraphicsMath> ept;
					};
					using rel_cubic_curve_data_type = _Rel_cubic_curve_data;
					static rel_cubic_curve_data_type create_rel_cubic_curve();
					static rel_cubic_curve_data_type create_rel_cubic_curve(const basic_point_2d<GraphicsMath>& cpt1, const basic_point_2d<GraphicsMath>& cpt2, const basic_point_2d<GraphicsMath>& ept);
					static rel_cubic_curve_data_type copy_rel_cubic_curve(const rel_cubic_curve_data_type& data);
					static rel_cubic_curve_data_type move_rel_cubic_curve(rel_cubic_curve_data_type&& data) noexcept;
					static void destroy(rel_cubic_curve_data_type& data) noexcept;
					static void control_pt1(rel_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static void control_pt2(rel_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static void end_pt(rel_cubic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static basic_point_2d<GraphicsMath> control_pt1(const rel_cubic_curve_data_type& data) noexcept;
					static basic_point_2d<GraphicsMath> control_pt2(const rel_cubic_curve_data_type& data) noexcept;
					static basic_point_2d<GraphicsMath> end_pt(const rel_cubic_curve_data_type& data) noexcept;

					struct _Rel_line_data {
						basic_point_2d<GraphicsMath> pt;
					};
					using rel_line_data_type = _Rel_line_data;
					static rel_line_data_type create_rel_line();
					static rel_line_data_type create_rel_line(const basic_point_2d<GraphicsMath>& pt);
					static rel_line_data_type copy_rel_line(const rel_line_data_type& data);
					static rel_line_data_type move_rel_line(rel_line_data_type&& data) noexcept;
					static void destroy(rel_line_data_type& data) noexcept;
					static void to(rel_line_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static basic_point_2d<GraphicsMath> to(const rel_line_data_type& data) noexcept;

					struct _Rel_quadratic_curve_data {
						basic_point_2d<GraphicsMath> cpt;
						basic_point_2d<GraphicsMath> ept;
					};
					using rel_quadratic_curve_data_type = _Rel_quadratic_curve_data;
					static rel_quadratic_curve_data_type create_rel_quadratic_curve();
					static rel_quadratic_curve_data_type create_rel_quadratic_curve(const basic_point_2d<GraphicsMath>& cpt, const basic_point_2d<GraphicsMath>& ept);
					static rel_quadratic_curve_data_type copy_rel_quadratic_curve(const rel_quadratic_curve_data_type& data);
					static rel_quadratic_curve_data_type move_rel_quadratic_curve(rel_quadratic_curve_data_type&& data) noexcept;
					static void destroy(rel_quadratic_curve_data_type& data) noexcept;
					static void control_pt(rel_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static void end_pt(rel_quadratic_curve_data_type& data, const basic_point_2d<GraphicsMath>& pt);
					static basic_point_2d<GraphicsMath> control_pt(const rel_quadratic_curve_data_type& data) noexcept;
					static basic_point_2d<GraphicsMath> end_pt(const rel_quadratic_curve_data_type& data) noexcept;


					// interpreted_path

					struct _Interpreted_path_data {
						::std::shared_ptr<cairo_path_t> path;
					};
					using interpreted_path_data_type = _Interpreted_path_data;

					static interpreted_path_data_type create_interpreted_path() noexcept;
					static interpreted_path_data_type create_interpreted_path(const basic_bounding_box<graphics_math_type>& bb);
					static interpreted_path_data_type create_interpreted_path(initializer_list<typename basic_figure_items<graphics_surfaces_type>::figure_item> il);
					template <class ForwardIterator>
					static interpreted_path_data_type create_interpreted_path(ForwardIterator first, ForwardIterator last);
					static interpreted_path_data_type copy_interpreted_path(const interpreted_path_data_type&);
					static interpreted_path_data_type move_interpreted_path(interpreted_path_data_type&&) noexcept;
					static void destroy(interpreted_path_data_type&) noexcept;
				};


				// brush

				struct brushes {
					struct _Brush_data {
						::std::shared_ptr<cairo_surface_t> imageSurface;
						::std::shared_ptr<cairo_pattern_t> brush;
						brush_type brushType;
					};
					using brush_data_type = _Brush_data;

					static brush_data_type create_brush(const rgba_color& c);
					template <class InputIterator>
					static brush_data_type create_brush(const basic_point_2d<GraphicsMath>& begin, const basic_point_2d<GraphicsMath>& end, InputIterator first, InputIterator last);
					static brush_data_type create_brush(const basic_point_2d<GraphicsMath>& begin, const basic_point_2d<GraphicsMath>& end, ::std::initializer_list<gradient_stop> il);
					template <class InputIterator>
					static brush_data_type create_brush(const basic_circle<GraphicsMath>& start, const basic_circle<GraphicsMath>& end, InputIterator first, InputIterator last);
					static brush_data_type create_brush(const basic_circle<GraphicsMath>& start, const basic_circle<GraphicsMath>& end, ::std::initializer_list<gradient_stop> il);
					static brush_data_type create_brush(basic_image_surface<_Graphics_surfaces_type>&& img);
					static brush_data_type copy_brush(const brush_data_type& data);
					static brush_data_type move_brush(brush_data_type&& data) noexcept;
					static void destroy(brush_data_type& data) noexcept;
					static brush_type get_brush_type(const brush_data_type& data) noexcept;
				};

				struct surface_state_props {
					// render_props
					struct _Render_props_data {
						antialias _Antialiasing = antialias::good;
						basic_matrix_2d<GraphicsMath> _Matrix;// = matrix_2d::init_identity(); // Transformation matrix
						compositing_op _Compositing = compositing_op::over;
					};

					using render_props_data_type = _Render_props_data;

					static render_props_data_type create_render_props(antialias aa, basic_matrix_2d<GraphicsMath> m, compositing_op co) noexcept;
					static render_props_data_type copy_render_props(const render_props_data_type& data);
					static render_props_data_type move_render_props(render_props_data_type&& data) noexcept;
					static void destroy(render_props_data_type& data) noexcept;
					static void antialiasing(render_props_data_type& data, antialias aa) noexcept;
					static void surface_matrix(render_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept;
					static void compositing(render_props_data_type& data, io2d::compositing_op co) noexcept;
					static antialias antialiasing(const render_props_data_type& data) noexcept;
					static basic_matrix_2d<GraphicsMath> surface_matrix(const render_props_data_type& data) noexcept;
					static compositing_op compositing(const render_props_data_type& data) noexcept;

					// brush_props

					struct _Brush_props_data {
						experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::pad;
						experimental::io2d::filter _Filter = experimental::io2d::filter::good;
						experimental::io2d::fill_rule _Fill_rule = experimental::io2d::fill_rule::winding;
						basic_matrix_2d<GraphicsMath> _Matrix;
					};

					using brush_props_data_type = _Brush_props_data;

					static brush_props_data_type create_brush_props(io2d::wrap_mode wm, io2d::filter f, io2d::fill_rule, const basic_matrix_2d<GraphicsMath>& m) noexcept;
					static brush_props_data_type copy_brush_props(const brush_props_data_type& data);
					static brush_props_data_type move_brush_props(brush_props_data_type&& data) noexcept;
					static void destroy(brush_props_data_type& data) noexcept;
					static void wrap_mode(brush_props_data_type& data, io2d::wrap_mode wm) noexcept;
					static void filter(brush_props_data_type& data, io2d::filter f) noexcept;
					static void fill_rule(brush_props_data_type& data, io2d::fill_rule fr) noexcept;
					static void brush_matrix(brush_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept;
					static io2d::wrap_mode wrap_mode(const brush_props_data_type& data) noexcept;
					static io2d::filter filter(const brush_props_data_type& data) noexcept;
					static io2d::fill_rule fill_rule(const brush_props_data_type& data) noexcept;
					static basic_matrix_2d<GraphicsMath> brush_matrix(const brush_props_data_type& data) noexcept;

					// clip_props
					struct _Clip_props_data {
						optional<basic_interpreted_path<_Graphics_surfaces_type>> clip;
						io2d::fill_rule fr;
					};

					using clip_props_data_type = _Clip_props_data;

					static clip_props_data_type create_clip_props() noexcept;
					static clip_props_data_type create_clip_props(const basic_bounding_box<GraphicsMath>& bbox, io2d::fill_rule fr) noexcept;
					template <class Allocator>
					static clip_props_data_type create_clip_props(const basic_path_builder<_Graphics_surfaces_type, Allocator>& pb, io2d::fill_rule fr);
					static clip_props_data_type create_clip_props(const basic_interpreted_path<_Graphics_surfaces_type> ip, io2d::fill_rule fr) noexcept;
					static clip_props_data_type copy_clip_props(const clip_props_data_type& data);
					static clip_props_data_type move_clip_props(clip_props_data_type&& data) noexcept;
					static void destroy(clip_props_data_type& data) noexcept;

					static void clip(clip_props_data_type& data, const basic_bounding_box<GraphicsMath>& bbox) noexcept;
					template <class Allocator>
					static void clip(clip_props_data_type& data, const basic_path_builder<_Graphics_surfaces_type, Allocator>& pb);
					static void clip(clip_props_data_type& data, const basic_interpreted_path<_Graphics_surfaces_type>& ip) noexcept;
					static void fill_rule(clip_props_data_type& data, io2d::fill_rule fr) noexcept;
					static typename _Graphics_surfaces_type::paths::interpreted_path_data_type clip(const clip_props_data_type& data) noexcept;
					static io2d::fill_rule fill_rule(const clip_props_data_type& data) noexcept;

					// stroke_props

					struct _Stroke_props_data {
						float _Line_width = 2.0F;
						float _Miter_limit = 10.0F;
						experimental::io2d::line_cap _Line_cap = experimental::io2d::line_cap::none;
						experimental::io2d::line_join _Line_join = experimental::io2d::line_join::miter;
					};

					using stroke_props_data_type = _Stroke_props_data;

					static stroke_props_data_type create_stroke_props(float lw, io2d::line_cap lc, io2d::line_join, float ml) noexcept;
					static stroke_props_data_type copy_stroke_props(const stroke_props_data_type& data);
					static stroke_props_data_type move_stroke_props(stroke_props_data_type&& data) noexcept;
					static void destroy(stroke_props_data_type& data) noexcept;
					static void line_width(stroke_props_data_type& data, float lw) noexcept;
					static void line_cap(stroke_props_data_type& data, io2d::line_cap lc) noexcept;
					static void line_join(stroke_props_data_type& data, io2d::line_join lj) noexcept;
					static void miter_limit(stroke_props_data_type& data, float ml) noexcept;
					static float line_width(const stroke_props_data_type& data) noexcept;
					static io2d::line_cap line_cap(const stroke_props_data_type& data) noexcept;
					static io2d::line_join line_join(const stroke_props_data_type& data) noexcept;
					static float miter_limit(const stroke_props_data_type& data) noexcept;
					static float max_miter_limit() noexcept;

					// mask_props

					struct _Mask_props_data {
						experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::repeat;
						experimental::io2d::filter _Filter = experimental::io2d::filter::good;
						basic_matrix_2d<GraphicsMath> _Matrix = basic_matrix_2d<GraphicsMath>{};
					};

					using mask_props_data_type = _Mask_props_data;

					static mask_props_data_type create_mask_props(io2d::wrap_mode wm, io2d::filter f, const basic_matrix_2d<GraphicsMath>& m) noexcept;
					static mask_props_data_type copy_mask_props(const mask_props_data_type& data);
					static mask_props_data_type move_mask_props(mask_props_data_type&& data) noexcept;
					static void destroy(mask_props_data_type& data) noexcept;
					static void wrap_mode(mask_props_data_type& data, io2d::wrap_mode wm) noexcept;
					static void filter(mask_props_data_type& data, io2d::filter f) noexcept;
					static void mask_matrix(mask_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept;
					static io2d::wrap_mode wrap_mode(const mask_props_data_type& data) noexcept;
					static io2d::filter filter(const mask_props_data_type& data) noexcept;
					static basic_matrix_2d<GraphicsMath> mask_matrix(const mask_props_data_type& data) noexcept;

					// dashes
					struct _Dashes_data {
						float offset;
						::std::vector<float> pattern;
					};

					using dashes_data_type = _Dashes_data;
					static dashes_data_type create_dashes() noexcept;
					template <class ForwardIterator>
					static dashes_data_type create_dashes(float offset, ForwardIterator first, ForwardIterator last);
					static dashes_data_type create_dashes(float offset, ::std::initializer_list<float> il);
					static dashes_data_type copy_dashes(const dashes_data_type& data);
					static dashes_data_type move_dashes(dashes_data_type&& data) noexcept;
					static void destroy(dashes_data_type& data) noexcept;
				};

				struct surfaces {
					// image_surface

					static basic_display_point<GraphicsMath> max_dimensions() noexcept;

					struct _Image_surface_data {
						::std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> surface{ nullptr, &cairo_surface_destroy };
						::std::unique_ptr<cairo_t, decltype(&cairo_destroy)> context{ nullptr, &cairo_destroy };
						basic_display_point<GraphicsMath> dimensions;
						io2d::format format;
						unsigned int ppi = 96;
					};

					using image_surface_data_type = _Image_surface_data;

					static image_surface_data_type create_image_surface(io2d::format fmt, int width, int height);
					static image_surface_data_type create_image_surface(filesystem::path p, image_file_format iff, io2d::format fmt);
					static image_surface_data_type create_image_surface(filesystem::path p, image_file_format iff, io2d::format fmt, ::std::error_code& ec) noexcept;
					static image_surface_data_type move_image_surface(image_surface_data_type&& data) noexcept;
					static void destroy(image_surface_data_type& data) noexcept;
					static void save(image_surface_data_type& data, filesystem::path p, image_file_format iff);
					static void save(image_surface_data_type& data, filesystem::path p, image_file_format iff, error_code& ec) noexcept;

					static io2d::format format(const image_surface_data_type& data) noexcept;
					static basic_display_point<GraphicsMath> dimensions(const image_surface_data_type& data) noexcept;
					static void ppi(image_surface_data_type& data, unsigned int val) noexcept;
					static unsigned int ppi(const image_surface_data_type& data) noexcept;

					static void clear(image_surface_data_type& data);
					static void paint(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
					static void stroke(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_stroke_props<_Graphics_surfaces_type>& sp, const basic_dashes<_Graphics_surfaces_type>& d, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
					static void fill(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
					static void mask(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush<_Graphics_surfaces_type>& mb, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_mask_props<_Graphics_surfaces_type>& mp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
					static void draw_text(image_surface_data_type& data, const basic_point_2d<GraphicsMath>& pt, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& font, const string& text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl);
					static void draw_text(image_surface_data_type& data, const basic_bounding_box<GraphicsMath>& bb, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& font, const string& text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl);
					template <class InputIterator>
					static ::std::future<void> command_list(image_surface_data_type& data, basic_image_surface<graphics_surfaces_type>& sfc, InputIterator first, InputIterator last);
					static _Interchange_buffer _Copy_to_interchange_buffer(image_surface_data_type& data, _Interchange_buffer::pixel_layout layout, _Interchange_buffer::alpha_mode alpha);

					// display surfaces
					struct _Display_surface_data_type;
					struct _Output_surface_data;
					struct _Unmanaged_output_surface_data;
					using output_surface_data_type = _Output_surface_data *;
					using unmanaged_output_surface_data_type = _Unmanaged_output_surface_data *;

					template <class OutputDataType, class OutputSurfaceType>
					static void _Render_to_native_surface(OutputDataType& osd, OutputSurfaceType& sfc);

					static basic_display_point<GraphicsMath> max_display_dimensions() noexcept;
					// unmanaged_output_surface functions


					struct _UnmanagedSurfaceContext;
					using unmanaged_surface_context_type = _UnmanagedSurfaceContext;

					static unmanaged_output_surface_data_type create_unmanaged_output_surface();
					static unmanaged_output_surface_data_type create_unmanaged_output_surface(unmanaged_surface_context_type& context, int preferredWidth, int preferredHeight, io2d::format preferredFormat, io2d::scaling scl);
					static unmanaged_output_surface_data_type move_unmanaged_output_surface(unmanaged_output_surface_data_type&& data) noexcept;
					static void destroy(unmanaged_output_surface_data_type& data) noexcept;

					static bool has_draw_callback(const unmanaged_output_surface_data_type& data) noexcept;
					static void invoke_draw_callback(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc);
					static void draw_to_output(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc);
					static bool has_size_change_callback(const unmanaged_output_surface_data_type& data) noexcept;
					static void invoke_size_change_callback(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc);
					static bool has_user_scaling_callback(const unmanaged_output_surface_data_type& data) noexcept;
					static basic_bounding_box<GraphicsMath> invoke_user_scaling_callback(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc, bool& useLetterboxBrush);
					static void display_dimensions(unmanaged_output_surface_data_type& data, const basic_display_point<GraphicsMath>& val);

					//static void flush(unmanaged_output_surface_data_type& data);
					//static void flush(unmanaged_output_surface_data_type& data, error_code& ec) noexcept;
					//static void mark_dirty(unmanaged_output_surface_data_type& data);
					//static void mark_dirty(unmanaged_output_surface_data_type& data, error_code& ec) noexcept;
					//static void mark_dirty(unmanaged_output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents);
					//static void mark_dirty(unmanaged_output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents, error_code& ec) noexcept;
					static void clear(unmanaged_output_surface_data_type& data);
					static void paint(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
					static void stroke(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_stroke_props<_Graphics_surfaces_type>& sp, const basic_dashes<_Graphics_surfaces_type>& d, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
					static void fill(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& pg, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
					static void mask(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush<_Graphics_surfaces_type>& mb, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_mask_props<_Graphics_surfaces_type>& mp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
					static void draw_text(unmanaged_output_surface_data_type& data, const basic_point_2d<GraphicsMath>& pt, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& font, const string& text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl);
					static void draw_text(unmanaged_output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& bb, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& font, const string& text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl);
					static void draw_callback(unmanaged_output_surface_data_type& data, function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)>);
					static void size_change_callback(unmanaged_output_surface_data_type& data, function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)>);
					static void user_scaling_callback(unmanaged_output_surface_data_type& data, function<basic_bounding_box<GraphicsMath>(const basic_unmanaged_output_surface<_Graphics_surfaces_type>&, bool&)>);
					static void dimensions(unmanaged_output_surface_data_type& data, const basic_display_point<GraphicsMath>& val);
					static void scaling(unmanaged_output_surface_data_type& data, io2d::scaling val);
					static void letterbox_brush(unmanaged_output_surface_data_type& data, const optional<basic_brush<_Graphics_surfaces_type>>& val, const optional<basic_brush_props<_Graphics_surfaces_type>>& bp) noexcept;
					static void letterbox_brush_props(unmanaged_output_surface_data_type& data, const basic_brush_props<_Graphics_surfaces_type>& val);
					static void auto_clear(unmanaged_output_surface_data_type& data, bool val);
					static void redraw_required(unmanaged_output_surface_data_type& data, bool val);

					template <class InputIterator>
					static void command_list(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<graphics_surfaces_type>& sfc, InputIterator first, InputIterator last);
					static io2d::format format(const unmanaged_output_surface_data_type& data) noexcept;
					static basic_display_point<GraphicsMath> dimensions(const unmanaged_output_surface_data_type& data) noexcept;
					static basic_display_point<GraphicsMath> display_dimensions(const unmanaged_output_surface_data_type& data) noexcept;
					static io2d::scaling scaling(unmanaged_output_surface_data_type& data) noexcept;
					static ::std::optional<basic_brush<_Graphics_surfaces_type>> letterbox_brush(const unmanaged_output_surface_data_type& data) noexcept;
					static basic_brush_props<_Graphics_surfaces_type> letterbox_brush_props(const unmanaged_output_surface_data_type& data) noexcept;
					static bool auto_clear(const unmanaged_output_surface_data_type& data) noexcept;
					static bool redraw_required(const unmanaged_output_surface_data_type& data) noexcept;

					// output_surface functions

					static output_surface_data_type create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, io2d::scaling scl, io2d::refresh_style rr, float fps);
					static output_surface_data_type create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, error_code& ec, io2d::scaling scl, io2d::refresh_style rr, float fps) noexcept;
					static output_surface_data_type create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, io2d::scaling scl, io2d::refresh_style rr, float fps);
					static output_surface_data_type create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, error_code& ec, io2d::scaling scl, io2d::refresh_style rr, float fps) noexcept;

					static output_surface_data_type move_output_surface(output_surface_data_type&& data) noexcept;
					static void destroy(output_surface_data_type& data) noexcept;

					static int begin_show(output_surface_data_type& data, basic_output_surface<_Graphics_surfaces_type>* instance, basic_output_surface<_Graphics_surfaces_type>& sfc);
					static void end_show(output_surface_data_type& data);
					static void refresh_style(output_surface_data_type& data, io2d::refresh_style val);
					static void desired_frame_rate(output_surface_data_type& data, float val);
					static void display_dimensions(output_surface_data_type& data, const basic_display_point<GraphicsMath>& val);
					static io2d::refresh_style refresh_style(const output_surface_data_type& data) noexcept;
					static float desired_frame_rate(const output_surface_data_type& data) noexcept;

					// rendering functions
					//static void flush(output_surface_data_type& data);
					//static void flush(output_surface_data_type& data, error_code& ec) noexcept;
					//static void mark_dirty(output_surface_data_type& data);
					//static void mark_dirty(output_surface_data_type& data, error_code& ec) noexcept;
					//static void mark_dirty(output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents);
					//static void mark_dirty(output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents, error_code& ec) noexcept;
					static void clear(output_surface_data_type& data);
					static void paint(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
					static void stroke(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_stroke_props<_Graphics_surfaces_type>& sp, const basic_dashes<_Graphics_surfaces_type>& d, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
					static void fill(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& pg, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
					static void mask(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush<_Graphics_surfaces_type>& mb, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_mask_props<_Graphics_surfaces_type>& mp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl);
					static void draw_text(output_surface_data_type& data, const basic_point_2d<GraphicsMath>& pt, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& font, const string& text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl);
					static void draw_text(output_surface_data_type& data, const basic_bounding_box<GraphicsMath>& bb, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& font, const string& text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl);

					// display_surface common functions
					template <class InputIterator>
					static void command_list(output_surface_data_type& data, basic_output_surface<graphics_surfaces_type>& sfc, InputIterator first, InputIterator last);
					static void draw_callback(output_surface_data_type& data, function<void(basic_output_surface<_Graphics_surfaces_type>&)>);
					static void size_change_callback(output_surface_data_type& data, function<void(basic_output_surface<_Graphics_surfaces_type>&)>);
					static void user_scaling_callback(output_surface_data_type& data, function<basic_bounding_box<GraphicsMath>(const basic_output_surface<_Graphics_surfaces_type>&, bool&)>);
					static void dimensions(output_surface_data_type& data, const basic_display_point<GraphicsMath>& val);
					static void scaling(output_surface_data_type& data, io2d::scaling val);
					static void letterbox_brush(output_surface_data_type& data, const optional<basic_brush<_Graphics_surfaces_type>>& val, const optional<basic_brush_props<_Graphics_surfaces_type>>& bp) noexcept;
					static void letterbox_brush_props(output_surface_data_type& data, const basic_brush_props<_Graphics_surfaces_type>& val);
					static void auto_clear(output_surface_data_type& data, bool val);
					static void redraw_required(output_surface_data_type& data, bool val);

					static io2d::format format(const output_surface_data_type& data) noexcept;
					static basic_display_point<GraphicsMath> dimensions(const output_surface_data_type& data) noexcept;
					static basic_display_point<GraphicsMath> display_dimensions(const output_surface_data_type& data) noexcept;
					static io2d::scaling scaling(output_surface_data_type& data) noexcept;
					static ::std::optional<basic_brush<_Graphics_surfaces_type>> letterbox_brush(const output_surface_data_type& data) noexcept;
					static basic_brush_props<_Graphics_surfaces_type> letterbox_brush_props(const output_surface_data_type& data) noexcept;
					static bool auto_clear(const output_surface_data_type& data) noexcept;
					static bool redraw_required(const output_surface_data_type& data) noexcept;

					static basic_image_surface<_Graphics_surfaces_type> copy_surface(basic_image_surface<_Graphics_surfaces_type>& sfc) noexcept;
					static basic_image_surface<_Graphics_surfaces_type> copy_surface(basic_output_surface<_Graphics_surfaces_type>& sfc) noexcept;
					// Note: basic_unmanaged_output_surface intentionally not provided.

					// basic_commands functions

					// clear
					struct _Clear_data {
						::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>> sfc;
					};

					using clear_data_type = _Clear_data;

					static clear_data_type create_clear() noexcept;
					static clear_data_type create_clear(::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>> sfc) noexcept;
					static void surface(clear_data_type& data, const ::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>>& sfc) noexcept;
					static ::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>> surface(const clear_data_type& data) noexcept;

					// paint
					struct _Paint_data {
						::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>> sfc;
						basic_brush<graphics_surfaces_type> b;
						basic_brush_props<graphics_surfaces_type> bp;
						basic_render_props<graphics_surfaces_type> rp;
						basic_clip_props<graphics_surfaces_type> cl;
					};

					using paint_data_type = _Paint_data;

					static paint_data_type create_paint(const basic_brush<graphics_surfaces_type>& b, const basic_brush_props<graphics_surfaces_type>& bp, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;
					static paint_data_type create_paint(::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>> sfc, const basic_brush<graphics_surfaces_type>& b, const basic_brush_props<graphics_surfaces_type>& bp, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;

					static void surface(paint_data_type& data, const ::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>>& sfc) noexcept;
					static ::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>> surface(const paint_data_type& data) noexcept;
					static void brush(paint_data_type& data, const basic_brush<graphics_surfaces_type>& b) noexcept;
					static basic_brush<graphics_surfaces_type> brush(const paint_data_type& data) noexcept;
					static void brush_props(paint_data_type& data, const basic_brush_props<graphics_surfaces_type>& bp) noexcept;
					static basic_brush_props<graphics_surfaces_type> brush_props(const paint_data_type& data) noexcept;
					static void render_props(paint_data_type& data, const basic_render_props<graphics_surfaces_type>& rp) noexcept;
					static basic_render_props<graphics_surfaces_type> render_props(const paint_data_type& data) noexcept;
					static void clip_props(paint_data_type& data, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;
					static basic_clip_props<graphics_surfaces_type> clip_props(const paint_data_type& data) noexcept;

					// stroke
					struct _Stroke_data {
						::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>> sfc;
						basic_brush<graphics_surfaces_type> b;
						basic_interpreted_path<graphics_surfaces_type> ip;
						basic_brush_props<graphics_surfaces_type> bp;
						basic_stroke_props<graphics_surfaces_type> sp;
						basic_dashes<graphics_surfaces_type> d;
						basic_render_props<graphics_surfaces_type> rp;
						basic_clip_props<graphics_surfaces_type> cl;
					};

					using stroke_data_type = _Stroke_data;

					static stroke_data_type create_stroke(const basic_brush<graphics_surfaces_type>& b, const basic_interpreted_path<graphics_surfaces_type>& ip, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;
					static stroke_data_type create_stroke(reference_wrapper<basic_image_surface<graphics_surfaces_type>> sfc, const basic_brush<graphics_surfaces_type>& b, const basic_interpreted_path<graphics_surfaces_type>& ip, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;

					static void surface(stroke_data_type& data, const ::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>>& sfc) noexcept;
					static optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>> surface(const stroke_data_type& data) noexcept;

					static void brush(stroke_data_type& data, const basic_brush<graphics_surfaces_type>& b) noexcept;
					static basic_brush<graphics_surfaces_type> brush(const stroke_data_type& data) noexcept;
					static void path(stroke_data_type& data, const basic_interpreted_path<graphics_surfaces_type>& ip) noexcept;
					static basic_interpreted_path<graphics_surfaces_type> path(const stroke_data_type& data) noexcept;
					static void stroke_props(stroke_data_type& data, const basic_stroke_props<graphics_surfaces_type>& sp) noexcept;
					static basic_stroke_props<graphics_surfaces_type> stroke_props(const stroke_data_type& data) noexcept;
					static void dashes(stroke_data_type& data, const basic_dashes<graphics_surfaces_type>& d) noexcept;
					static basic_dashes<graphics_surfaces_type> dashes(const stroke_data_type& data) noexcept;
					static void brush_props(stroke_data_type& data, const basic_brush_props<graphics_surfaces_type>& bp) noexcept;
					static basic_brush_props<graphics_surfaces_type> brush_props(const stroke_data_type& data) noexcept;
					static void render_props(stroke_data_type& data, const basic_render_props<graphics_surfaces_type>& rp) noexcept;
					static basic_render_props<graphics_surfaces_type> render_props(const stroke_data_type& data) noexcept;
					static void clip_props(stroke_data_type& data, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;
					static basic_clip_props<graphics_surfaces_type> clip_props(const stroke_data_type& data) noexcept;

					// fill
					struct _Fill_data {
						::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>> sfc;
						basic_brush<graphics_surfaces_type> b;
						basic_interpreted_path<graphics_surfaces_type> ip;
						basic_brush_props<graphics_surfaces_type> bp;
						basic_render_props<graphics_surfaces_type> rp;
						basic_clip_props<graphics_surfaces_type> cl;
					};

					using fill_data_type = _Fill_data;

					static fill_data_type create_fill(const basic_brush<graphics_surfaces_type>& b, const basic_interpreted_path<graphics_surfaces_type>& ip, const basic_brush_props<graphics_surfaces_type>& bp, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;
					static fill_data_type create_fill(reference_wrapper<basic_image_surface<graphics_surfaces_type>> sfc, const basic_brush<graphics_surfaces_type>& b, const basic_interpreted_path<graphics_surfaces_type>& ip, const basic_brush_props<graphics_surfaces_type>& bp, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;

					static void surface(fill_data_type& data, const ::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>>& sfc) noexcept;
					static optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>> surface(const fill_data_type& data) noexcept;

					static void brush(fill_data_type& data, const basic_brush<graphics_surfaces_type>& b) noexcept;
					static basic_brush<graphics_surfaces_type> brush(const fill_data_type& data) noexcept;
					static void path(fill_data_type& data, const basic_interpreted_path<graphics_surfaces_type>& ip) noexcept;
					static basic_interpreted_path<graphics_surfaces_type> path(const fill_data_type& data) noexcept;
					static void brush_props(fill_data_type& data, const basic_brush_props<graphics_surfaces_type>& bp) noexcept;
					static basic_brush_props<graphics_surfaces_type> brush_props(const fill_data_type& data) noexcept;
					static void render_props(fill_data_type& data, const basic_render_props<graphics_surfaces_type>& rp) noexcept;
					static basic_render_props<graphics_surfaces_type> render_props(const fill_data_type& data) noexcept;
					static void clip_props(fill_data_type& data, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;
					static basic_clip_props<graphics_surfaces_type> clip_props(const fill_data_type& data) noexcept;

					// mask
					struct _Mask_data {
						::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>> sfc;
						basic_brush<graphics_surfaces_type> b;
						basic_brush<graphics_surfaces_type> mb;
						basic_brush_props<graphics_surfaces_type> bp;
						basic_mask_props<graphics_surfaces_type> mp;
						basic_render_props<graphics_surfaces_type> rp;
						basic_clip_props<graphics_surfaces_type> cl;
					};

					using mask_data_type = _Mask_data;

					static mask_data_type create_mask(const basic_brush<graphics_surfaces_type>& b, const basic_brush<graphics_surfaces_type>& mb, const basic_brush_props<graphics_surfaces_type>& bp, const basic_mask_props<graphics_surfaces_type>& mp, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;
					static mask_data_type create_mask(reference_wrapper<basic_image_surface<graphics_surfaces_type>> sfc, const basic_brush<graphics_surfaces_type>& b, const basic_brush<graphics_surfaces_type>& mb, const basic_brush_props<graphics_surfaces_type>& bp, const basic_mask_props<graphics_surfaces_type>& mp, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;

					static void surface(mask_data_type& data, const ::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>>& sfc) noexcept;
					static optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>> surface(const mask_data_type& data) noexcept;

					static void brush(mask_data_type& data, const basic_brush<graphics_surfaces_type>& b) noexcept;
					static basic_brush<graphics_surfaces_type> brush(const mask_data_type& data) noexcept;
					static void mask_brush(mask_data_type& data, const basic_brush<graphics_surfaces_type>& mb) noexcept;
					static basic_brush<graphics_surfaces_type> mask_brush(const mask_data_type& data) noexcept;
					static void brush_props(mask_data_type& data, const basic_brush_props<graphics_surfaces_type>& bp) noexcept;
					static basic_brush_props<graphics_surfaces_type> brush_props(const mask_data_type& data) noexcept;
					static void mask_props(mask_data_type& data, const basic_mask_props<graphics_surfaces_type>& mp) noexcept;
					static basic_mask_props<graphics_surfaces_type> mask_props(const mask_data_type& data) noexcept;
					static void render_props(mask_data_type& data, const basic_render_props<graphics_surfaces_type>& rp) noexcept;
					static basic_render_props<graphics_surfaces_type> render_props(const mask_data_type& data) noexcept;
					static void clip_props(mask_data_type& data, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;
					static basic_clip_props<graphics_surfaces_type> clip_props(const mask_data_type& data) noexcept;

					// draw_text
					struct _Draw_text_data {
						::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>> sfc;
						::std::variant<basic_point_2d<graphics_math_type>, basic_bounding_box<graphics_math_type>> loc;
						basic_brush<graphics_surfaces_type> b;
						basic_font<graphics_surfaces_type> f;
						::std::string text;
						basic_text_props<graphics_surfaces_type> tp;
						basic_brush_props<graphics_surfaces_type> bp;
						basic_stroke_props<graphics_surfaces_type> sp;
						basic_dashes<graphics_surfaces_type> d;
						basic_render_props<graphics_surfaces_type> rp;
						basic_clip_props<graphics_surfaces_type> cl;
					};

					using draw_text_data_type = _Draw_text_data;

					static draw_text_data_type create_draw_text(const basic_point_2d<graphics_math_type>& pt, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& f, ::std::string text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;
					static draw_text_data_type create_draw_text(reference_wrapper<basic_image_surface<graphics_surfaces_type>> sfc, const basic_point_2d<graphics_math_type>& pt, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& f, ::std::string text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;
					static draw_text_data_type create_draw_text(const basic_bounding_box<graphics_math_type>& bb, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& f, ::std::string text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;
					static draw_text_data_type create_draw_text(reference_wrapper<basic_image_surface<graphics_surfaces_type>> sfc, const basic_bounding_box<graphics_math_type>& bb, const basic_brush<graphics_surfaces_type>& b, const basic_font<graphics_surfaces_type>& f, ::std::string text, const basic_text_props<graphics_surfaces_type>& tp, const basic_brush_props<graphics_surfaces_type>& bp, const basic_stroke_props<graphics_surfaces_type>& sp, const basic_dashes<graphics_surfaces_type>& d, const basic_render_props<graphics_surfaces_type>& rp, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;

					static void surface(draw_text_data_type& data, const ::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>>& sfc) noexcept;
					static optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>> surface(const draw_text_data_type& data) noexcept;

					static void location(draw_text_data_type& data, const basic_point_2d<graphics_math_type>& pt) noexcept;
					static void location(draw_text_data_type& data, const basic_bounding_box<graphics_math_type>& bb) noexcept;
					static ::std::variant<basic_point_2d<graphics_math_type>, basic_bounding_box<graphics_math_type>> location(const draw_text_data_type& data) noexcept;
					static void brush(draw_text_data_type& data, const basic_brush<graphics_surfaces_type>& b) noexcept;
					static basic_brush<graphics_surfaces_type> brush(const draw_text_data_type& data) noexcept;
					static void font(draw_text_data_type& data, const basic_font<graphics_surfaces_type>& f) noexcept;
					static basic_font<graphics_surfaces_type> font(const draw_text_data_type& data) noexcept;
					static void text(draw_text_data_type& data, ::std::string te) noexcept;
					static ::std::string text(const draw_text_data_type& data) noexcept;
					static void text_props(draw_text_data_type& data, const basic_text_props<graphics_surfaces_type>& tp) noexcept;
					static basic_text_props<graphics_surfaces_type> text_props(const draw_text_data_type& data) noexcept;
					static void brush_props(draw_text_data_type& data, const basic_brush_props<graphics_surfaces_type>& bp) noexcept;
					static basic_brush_props<graphics_surfaces_type> brush_props(const draw_text_data_type& data) noexcept;
					static void stroke_props(draw_text_data_type& data, const basic_stroke_props<graphics_surfaces_type>& sp) noexcept;
					static basic_stroke_props<graphics_surfaces_type> stroke_props(const draw_text_data_type& data) noexcept;
					static void dashes(draw_text_data_type& data, const basic_dashes<graphics_surfaces_type>& d) noexcept;
					static basic_dashes<graphics_surfaces_type> dashes(const draw_text_data_type& data) noexcept;
					static void render_props(draw_text_data_type& data, const basic_render_props<graphics_surfaces_type>& rp) noexcept;
					static basic_render_props<graphics_surfaces_type> render_props(const draw_text_data_type& data) noexcept;
					static void clip_props(draw_text_data_type& data, const basic_clip_props<graphics_surfaces_type>& cl) noexcept;
					static basic_clip_props<graphics_surfaces_type> clip_props(const draw_text_data_type& data) noexcept;

					// run_function
					struct _Run_function_data {
						::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>> sfc;
						::std::variant<::std::function<void(basic_image_surface<graphics_surfaces_type>&, optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>>, void*)>, ::std::function<void(basic_output_surface<graphics_surfaces_type>&, optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>>, void*)>, ::std::function<void(basic_unmanaged_output_surface<graphics_surfaces_type>&, optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>>, void*)>> func;
						void* user_data;
					};

					using run_function_data_type = _Run_function_data;

					static run_function_data_type create_run_function(const ::std::function<void(basic_image_surface<graphics_surfaces_type>&, optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>>, void*)>& fn, void* user_data, optional< reference_wrapper<basic_image_surface<graphics_surfaces_type>>> sfc) noexcept;
					static run_function_data_type create_run_function(const ::std::function<void(basic_output_surface<graphics_surfaces_type>&, optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>>, void*)>& fn, void* user_data, optional< reference_wrapper<basic_image_surface<graphics_surfaces_type>>> sfc) noexcept;
					static run_function_data_type create_run_function(const ::std::function<void(basic_unmanaged_output_surface<graphics_surfaces_type>&, optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>>, void*)>& fn, void* user_data, optional< reference_wrapper<basic_image_surface<graphics_surfaces_type>>> sfc) noexcept;

					static void surface(run_function_data_type& data, const ::std::optional<::std::reference_wrapper<basic_image_surface<graphics_surfaces_type>>>& sfc) noexcept;
					static optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>> surface(const run_function_data_type& data) noexcept;

					static void func(run_function_data_type& data, const ::std::function<void(basic_image_surface<graphics_surfaces_type>&, optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>>, void*)>& fn) noexcept;
					static void func(run_function_data_type& data, const ::std::function<void(basic_output_surface<graphics_surfaces_type>&, optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>>, void*)>& fn) noexcept;
					static void func(run_function_data_type& data, const ::std::function<void(basic_unmanaged_output_surface<graphics_surfaces_type>&, optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>>, void*)>& fn) noexcept;
					static const variant<function<void(basic_image_surface<graphics_surfaces_type>&, optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>>, void*)>, function<void(basic_output_surface<graphics_surfaces_type>&, optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>>, void*)>, function<void(basic_unmanaged_output_surface<graphics_surfaces_type>&, optional<reference_wrapper<basic_image_surface<graphics_surfaces_type>>>, void*)>>& func(const run_function_data_type& data) noexcept;

					static void user_data(run_function_data_type& data, void* user_data);
					static void* user_data(const run_function_data_type& data);
					//end surfaces
				};

				struct text {
					struct _Font_data {

					};

					using font_data_type = _Font_data;

					struct _Text_props_data {
						float scl;
						font_size_units fsu;
						float fontsize;
						bool kern;
						font_antialias aa;
						font_stretching stretch;
						bool strike_through;
						font_line fl;
					};

					using text_props_data_type = _Text_props_data;

					static text_props_data_type create_text_props(float scl, font_size_units fsu, float fontsize, bool kern, font_antialias aa, font_stretching stretch, bool strike_through, font_line fl) noexcept;


				};
			};
		}
	}
}

#include "xcairo_brushes_impl.h"
#include "xcairo_command_list_impl.h"
#include "xcairo_paths_impl.h"
#include "xcairo_surface_state_props_impl.h"
#include "xcairo_surfaces_image_impl.h"
#include "xcairo_surfaces_impl.h"
#include "xcairo_text_impl.h"

#endif
