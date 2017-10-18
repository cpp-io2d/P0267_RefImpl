#pragma once

#include "xcairo.h"
#include "xcairo_helpers.h"
#include "xinclwindows_h.h"
#include <cassert>
#if defined(_WIN32) || defined(_WIN64)
#include <cairo-win32.h>
#endif
#include "xpath.h"

namespace std::experimental::io2d::v1 {
	namespace _Cairo {
		// cairo_interpreted_path

		template <class _TItem, class GraphicsMath>
		struct _Path_group_perform_visit {
			template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_new_figure>, _Path_data_abs_new_figure> = _Path_data_abs_new_figure_val>
			 static void _Perform(::std::vector<cairo_path_data_t>& vec, const typename basic_figure_items<GraphicsMath>::abs_new_figure& item, basic_point_2d<GraphicsMath>& lastMoveToPoint) noexcept {
				cairo_path_data_t cpdItem{};
				auto pt = item.at();
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt.x(), pt.y() };
				lastMoveToPoint = pt;
				vec.push_back(cpdItem);
			}

			template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_line>, _Path_data_abs_line> = _Path_data_abs_line_val>
			 static void _Perform(::std::vector<cairo_path_data_t>& vec, const typename basic_figure_items<GraphicsMath>::abs_line& item, basic_point_2d<GraphicsMath>&) noexcept {
				cairo_path_data_t cpdItem{};
				auto pt = item.to();
				cpdItem.header.type = CAIRO_PATH_LINE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt.x(), pt.y() };
				vec.push_back(cpdItem);
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_cubic_curve>, _Path_data_abs_cubic_curve> = _Path_data_abs_cubic_curve_val>
			 static void _Perform(::std::vector<cairo_path_data_t>& vec, const typename basic_figure_items<GraphicsMath>::abs_cubic_curve& item, basic_point_2d<GraphicsMath>&) noexcept {
				cairo_path_data_t cpdItem{};
				auto pt1 = item.control_pt1();
				auto pt2 = item.control_pt2();
				auto pt3 = item.end_pt();
				cpdItem.header.type = CAIRO_PATH_CURVE_TO;
				cpdItem.header.length = 4;
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt1.x(), pt1.y() };
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt2.x(), pt2.y() };
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { pt3.x(), pt3.y() };
				vec.push_back(cpdItem);
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_quadratic_curve>, _Path_data_abs_quadratic_curve> = _Path_data_abs_quadratic_curve_val>
			 static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsMath>::abs_quadratic_curve&, basic_point_2d<GraphicsMath>&) noexcept {
				assert(false && "Abs quadratic curves should have been transformed into cubic curves already.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_new_figure>, _Path_data_rel_new_figure> = _Path_data_rel_new_figure_val>
			 static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsMath>::rel_new_figure&, basic_point_2d<GraphicsMath>&) noexcept {
				assert(false && "Rel new path instructions should have been eliminated.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::close_figure>, _Path_data_close_path> = _Path_data_close_path_val>
			 static void _Perform(::std::vector<cairo_path_data_t>& vec, const typename basic_figure_items<GraphicsMath>::close_figure&, basic_point_2d<GraphicsMath>& lastMoveToPoint) noexcept {
				cairo_path_data_t cpdItem{};
				cpdItem.header.type = CAIRO_PATH_CLOSE_PATH;
				cpdItem.header.length = 1;
				vec.push_back(cpdItem);
				cpdItem.header.type = CAIRO_PATH_MOVE_TO;
				cpdItem.header.length = 2;
				vec.push_back(cpdItem);
				cpdItem = {};
				cpdItem.point = { lastMoveToPoint.x(), lastMoveToPoint.y() };
				vec.push_back(cpdItem);
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_line>, _Path_data_rel_line> = _Path_data_rel_line_val>
			 static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsMath>::rel_line&, basic_point_2d<GraphicsMath>&) noexcept {
				assert(false && "Rel line should have been transformed into non-relative.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_cubic_curve>, _Path_data_rel_cubic_curve> = _Path_data_rel_cubic_curve_val>
			 static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsMath>::rel_cubic_curve&, basic_point_2d<GraphicsMath>&) noexcept {
				assert(false && "Rel curve should have been transformed into non-relative.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_quadratic_curve>, _Path_data_rel_quadratic_curve> = _Path_data_rel_quadratic_curve_val>
			 static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsMath>::rel_quadratic_curve&, basic_point_2d<GraphicsMath>&) noexcept {
				assert(false && "Rel quadratic curves should have been transformed into cubic curves.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::arc>, _Path_data_arc> = _Path_data_arc_val>
			 static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsMath>::arc&, basic_point_2d<GraphicsMath>&) noexcept {
				assert(false && "Arcs should have been transformed into cubic curves.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::abs_matrix>, _Path_data_abs_matrix> = _Path_data_abs_matrix_val>
			 static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsMath>::abs_matrix&, basic_point_2d<GraphicsMath>&) noexcept {
				assert(false && "Abs matrix should have been eliminated.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::rel_matrix>, _Path_data_rel_matrix> = _Path_data_rel_matrix_val>
			 static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsMath>::rel_matrix&, basic_point_2d<GraphicsMath>&) noexcept {
				assert(false && "Rel matrix should have been eliminated.");
			}
			template <class T, ::std::enable_if_t<::std::is_same_v<T, typename basic_figure_items<GraphicsMath>::revert_matrix>, _Path_data_revert_matrix> = _Path_data_revert_matrix_val>
			 static void _Perform(::std::vector<cairo_path_data_t>&, const typename basic_figure_items<GraphicsMath>::revert_matrix&, basic_point_2d<GraphicsMath>&) noexcept {
				assert(false && "Revert matrix should have been eliminated.");
			}
		};

		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::interpreted_path_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_interpreted_path() noexcept {
			interpreted_path_data_type result;
			result.path = nullptr;
		}
		template<class GraphicsMath>
		template<class Allocator>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::interpreted_path_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_interpreted_path(const basic_path_builder<GraphicsMath, Allocator>& pb) {
			return _Cairo_graphics_surfaces<GraphicsMath>::template create_interpreted_path<typename basic_path_builder<GraphicsMath, Allocator>::const_iterator>(begin(pb), end(pb));
		}
		template<class GraphicsMath>
		template<class ForwardIterator>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::interpreted_path_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_interpreted_path(ForwardIterator first, ForwardIterator last) {
			interpreted_path_data_type result;
			auto cairoPathT = new cairo_path_t;
			if (cairoPathT == nullptr) {
				throw bad_alloc();
			}
			result.path = shared_ptr<cairo_path_t>(cairoPathT, [](cairo_path_t* path) {
				if (path != nullptr) {
					if (path->data != nullptr) {
						delete[] path->data;
						path->data = nullptr;
						path->status = CAIRO_STATUS_NULL_POINTER;
					}
					delete path;
					path = nullptr;
				}
			});

			auto processedVec = _Interpret_path_items<ForwardIterator>(first, last);
			::std::vector<cairo_path_data_t> vec;
			basic_point_2d<GraphicsMath> lastMoveToPoint;
			for (const auto& val : processedVec) {
				::std::visit([&vec, &lastMoveToPoint](auto&& item) {
					using T = ::std::remove_cv_t<::std::remove_reference_t<decltype(item)>>;
					_Path_group_perform_visit<T, GraphicsMath>::template _Perform<T>(vec, item, lastMoveToPoint);
				}, val);
			}
			result.path->num_data = static_cast<int>(vec.size());
			const auto numDataST = vec.size();
			result.path->data = new cairo_path_data_t[numDataST];
			for (size_t currItemIndex = 0; currItemIndex < numDataST; currItemIndex++) {
				result.path->data[currItemIndex] = vec[currItemIndex];
			}
			result.path->status = CAIRO_STATUS_SUCCESS;
			return result;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::interpreted_path_data_type _Cairo_graphics_surfaces<GraphicsMath>::copy_interpreted_path(const interpreted_path_data_type& data) {
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::interpreted_path_data_type _Cairo_graphics_surfaces<GraphicsMath>::move_interpreted_path(interpreted_path_data_type&& data) noexcept {
			return data;
		}

		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::destroy_interpreted_path(interpreted_path_data_type &) noexcept {
			// Do nothing, the shared_ptr deletes for us.
		}

		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_brush(const rgba_color& c) {
			brush_data_type data;
			data.imageSurface = nullptr;
			data.brushType = brush_type::solid_color;
			data.brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_rgba(c.r(), c.g(), c.b(), c.a()), &cairo_pattern_destroy);
			return data;
		}
		template<class GraphicsMath>
		template<class InputIterator>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_brush(const basic_point_2d<GraphicsMath>& begin, const basic_point_2d<GraphicsMath>& end, InputIterator first, InputIterator last) {
			brush_data_type data;
			data.brushType = brush_type::linear;
			data.imageSurface = nullptr;
			data.brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_linear(begin.x(), begin.y(), end.x(), end.y()), &cairo_pattern_destroy);
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(data.brush.get()));

			for (auto it = first; it != last; ++it) {
				auto stop = *it;
				cairo_pattern_add_color_stop_rgba(data.brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
			}
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(data.brush.get()));
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_brush(const basic_point_2d<GraphicsMath>& b, const basic_point_2d<GraphicsMath>& e, ::std::initializer_list<gradient_stop> il) {
			return create_brush(b, e, ::std::begin(il), ::std::end(il));
		}
		template<class GraphicsMath>
		template<class InputIterator>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_brush(const basic_circle<GraphicsMath>& start, const basic_circle<GraphicsMath>& end, InputIterator first, InputIterator last) {
			brush_data_type data;
			data.imageSurface = nullptr;
			data.brushType = brush_type::radial_gradient;
			data.brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_radial(start.center().x, start.center().y(), start.radius(), end.center().x(), end.center().y(), end.radius()), &cairo_pattern_destroy);
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(data.brush.get()));
			for (auto it = first; it != last; ++it) {
				auto stop = *it;
				cairo_pattern_add_color_stop_rgba(data.brush.get(), stop.offset(), stop.color().r(), stop.color().g(), stop.color().b(), stop.color().a());
			}
			_Throw_if_failed_cairo_status_t(cairo_pattern_status(data.brush.get()));
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_brush(const basic_circle<GraphicsMath>& s, const basic_circle<GraphicsMath>& e, ::std::initializer_list<gradient_stop> il) {
			return create_brush(s, e, ::std::begin(il), ::std::end(il));
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_brush(basic_image_surface<_Graphics_surfaces_type>&& img) {
			brush_data_type data;
			// The surface is dying and I want to steal some of its data, ergo const_cast.
			image_surface_data_type& imgData = const_cast<image_surface_data_type&>(img._Get_data());
			data.imageSurface = shared_ptr<cairo_surface_t>(imgData._Surface.release(), &cairo_surface_destroy);
			data.brush = shared_ptr<cairo_pattern_t>(cairo_pattern_create_for_surface(data.imageSurface.get()), &cairo_pattern_destroy);
			data.brushType = brush_type::surface;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::copy_brush(const brush_data_type& data) {
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::brush_data_type _Cairo_graphics_surfaces<GraphicsMath>::move_brush(brush_data_type&& data) noexcept {
			return data;
		}

		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::destroy(brush_data_type & data) noexcept {
			// Do nothing; it destroys itself via the shared_ptr's.
		}

		template<class GraphicsMath>
		inline brush_type _Cairo_graphics_surfaces<GraphicsMath>::get_brush_type(const brush_data_type& data) noexcept {
			return data.brushType;
		}

		// render props
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::render_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_render_props(antialias aa, basic_matrix_2d<GraphicsMath> m, compositing_op co) noexcept {
			render_props_data_type data;
			data._Antialiasing = aa;
			data._Matrix = m;
			data._Compositing = co;
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::render_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::copy_render_props(const render_props_data_type& data) {
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::render_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::move_render_props(render_props_data_type&& data) noexcept {
			return data;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::destroy(render_props_data_type& data) noexcept {
			// Do nothing.
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::antialiasing(render_props_data_type& data, antialias aa) noexcept {
			data._Antialiasing = aa;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::surface_matrix(render_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept {
			data._Matrix = m;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::compositing(render_props_data_type& data, io2d::compositing_op co) noexcept {
			data.Compositing = co;
		}
		template<class GraphicsMath>
		inline antialias _Cairo_graphics_surfaces<GraphicsMath>::antialiasing(const render_props_data_type& data) noexcept {
			return data._Antialiasing;
		}
		template<class GraphicsMath>
		inline basic_matrix_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::surface_matrix(const render_props_data_type& data) noexcept {
			return data._Matrix;
		}
		template<class GraphicsMath>
		inline  compositing_op _Cairo_graphics_surfaces<GraphicsMath>::compositing(const render_props_data_type & data) noexcept {
			return data._Compositing;
		}
		template<class GraphicsMath>
		inline  typename _Cairo_graphics_surfaces<GraphicsMath>::brush_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_brush_props(io2d::wrap_mode wm, io2d::filter f, io2d::fill_rule fr, const basic_matrix_2d<GraphicsMath>& m) noexcept {
			brush_props_data_type data;
			data._Wrap_mode = wm;
			data._Filter = f;
			data._Fill_rule = fr;
			data._Matrix = m;
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::brush_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::copy_brush_props(const brush_props_data_type & data) {
			return brush_props_data_type();
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::brush_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::move_brush_props(brush_props_data_type&& data) noexcept {
			return data;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::destroy(brush_props_data_type & data) noexcept {
			// Do nothing.
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::wrap_mode(brush_props_data_type & data, io2d::wrap_mode wm) noexcept {
			data._Wrap_mode = wm;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::filter(brush_props_data_type & data, io2d::filter f) noexcept {
			data._Filter = f;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::fill_rule(brush_props_data_type & data, io2d::fill_rule fr) noexcept {
			data._Fill_rule = fr;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::brush_matrix(brush_props_data_type & data, const basic_matrix_2d<GraphicsMath>& m) noexcept {
			data._Matrix = m;
		}
		template<class GraphicsMath>
		inline io2d::wrap_mode _Cairo_graphics_surfaces<GraphicsMath>::wrap_mode(const brush_props_data_type & data) noexcept {
			return data._Wrap_mode;
		}
		template<class GraphicsMath>
		inline io2d::filter _Cairo_graphics_surfaces<GraphicsMath>::filter(const brush_props_data_type & data) noexcept {
			return data._Filter;
		}
		template<class GraphicsMath>
		inline io2d::fill_rule _Cairo_graphics_surfaces<GraphicsMath>::fill_rule(const brush_props_data_type & data) noexcept {
			return data._Fill_rule;
		}
		template<class GraphicsMath>
		inline basic_matrix_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::brush_matrix(const brush_props_data_type & data) noexcept {
			return data._Matrix;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::clip_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_clip_props() noexcept {
			clip_props_data_type data;
			data.clip = basic_interpreted_path<_Graphics_surfaces_type>();
			data.fr = io2d::fill_rule::winding;
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::clip_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_clip_props(const basic_bounding_box<GraphicsMath>& bbox, io2d::fill_rule fr) noexcept {
			clip_props_data_type data;
			clip(data, bbox);
			data.fr = io2d::fill_rule::winding;
			return data;
		}
		template<class GraphicsMath>
		template<class Allocator>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::clip_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_clip_props(const basic_path_builder<GraphicsMath, Allocator>& pb, io2d::fill_rule fr) {
			clip_props_data_type data;
			data.clip = basic_interpreted_path<_Graphics_surfaces_type>(pb);
			data.fr = io2d::fill_rule::winding;
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::clip_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_clip_props(const basic_interpreted_path<_Graphics_surfaces_type> ip, io2d::fill_rule fr) noexcept {
			clip_props_data_type data;
			data.clip = ip;
			data.fr = fr;
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::clip_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::copy_clip_props(const clip_props_data_type& data) {
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::clip_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::move_clip_props(clip_props_data_type&& data) noexcept {
			return data;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::destroy(clip_props_data_type& data) noexcept {
			// Do nothing.
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::clip(clip_props_data_type& data, const basic_bounding_box<GraphicsMath>& bbox) noexcept {
			basic_path_builder<GraphicsMath> pb;
			basic_point_2d<GraphicsMath> point(bbox.x(), bbox.y());
			pb.new_figure(point);
			point.x(bbox.width());
			point.y(0.0f);
			pb.rel_line(point);
			point.x(0.0f);
			point.y(bbox.height());
			pb.rel_line(point);
			point.x(-bbox.width());
			point.y(0.0f);
			pb.rel_line(point);
			pb.close_figure();
			data.clip = basic_interpreted_path<_Graphics_surfaces_type>(pb);
		}
		template<class GraphicsMath>
		template<class Allocator>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::clip(clip_props_data_type& data, const basic_path_builder<GraphicsMath, Allocator>& pb) {
			data.clip = basic_interpreted_path<_Graphics_surfaces_type>(pb)
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::clip(clip_props_data_type& data, const basic_interpreted_path<_Graphics_surfaces_type>& ip) noexcept {
			data.clip = ip;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::fill_rule(clip_props_data_type& data, io2d::fill_rule fr) noexcept {
			data.fr = fr;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::interpreted_path_data_type _Cairo_graphics_surfaces<GraphicsMath>::clip(const clip_props_data_type& data) noexcept {
			return data.clip;
		}
		template<class GraphicsMath>
		inline io2d::fill_rule _Cairo_graphics_surfaces<GraphicsMath>::fill_rule(const clip_props_data_type& data) noexcept {
			return data.fr;
		}

		// stroke props
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::stroke_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_stroke_props(float lw, io2d::line_cap lc, io2d::line_join lj, float ml) noexcept {
			stroke_props_data_type data;
			data._Line_width = lw;
			data._Miter_limit = ::std::min(ml, max_miter_limit());
			data._Line_cap = lc;
			data._Line_join = lj;
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::stroke_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::copy_stroke_props(const stroke_props_data_type& data) {
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::stroke_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::move_stroke_props(stroke_props_data_type && data) noexcept {
			return data;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::destroy(stroke_props_data_type& data) noexcept {
			// Do nothing.
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::line_width(stroke_props_data_type& data, float lw) noexcept {
			data._Line_width = lw;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::line_cap(stroke_props_data_type& data, io2d::line_cap lc) noexcept {
			data._Line_cap = lc;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::line_join(stroke_props_data_type& data, io2d::line_join lj) noexcept {
			data._Line_join = lj;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::miter_limit(stroke_props_data_type& data, float ml) noexcept {
			data._Miter_limit = ::std::min(ml, max_miter_limit());
		}
		template<class GraphicsMath>
		inline float _Cairo_graphics_surfaces<GraphicsMath>::line_width(const stroke_props_data_type& data) noexcept {
			return data._Line_width;
		}
		template<class GraphicsMath>
		inline io2d::line_cap _Cairo_graphics_surfaces<GraphicsMath>::line_cap(const stroke_props_data_type& data) noexcept {
			return data._Line_cap;
		}
		template<class GraphicsMath>
		inline io2d::line_join _Cairo_graphics_surfaces<GraphicsMath>::line_join(const stroke_props_data_type& data) noexcept {
			return data._Line_join;
		}
		template<class GraphicsMath>
		inline float _Cairo_graphics_surfaces<GraphicsMath>::miter_limit(const stroke_props_data_type& data) noexcept {
			return data._Miter_limit;
		}
		template<class GraphicsMath>
		inline float _Cairo_graphics_surfaces<GraphicsMath>::max_miter_limit() noexcept {
			return 10000.0F;
		}

		// mask props
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::mask_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_mask_props(io2d::wrap_mode wm, io2d::filter f, const basic_matrix_2d<GraphicsMath>& m) noexcept {
			mask_props_data_type data;
			data._Wrap_mode = wm;
			data._Filter = f;
			data._Matrix = m;
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::mask_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::copy_mask_props(const mask_props_data_type& data) {
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::mask_props_data_type _Cairo_graphics_surfaces<GraphicsMath>::move_mask_props(mask_props_data_type&& data) noexcept {
			return data;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::destroy(mask_props_data_type& data) noexcept {
			// Do nothing.
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::wrap_mode(mask_props_data_type& data, io2d::wrap_mode wm) noexcept {
			data._Wrap_mode = wm;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::filter(mask_props_data_type& data, io2d::filter f) noexcept {
			data._Filter = f;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::mask_matrix(mask_props_data_type& data, const basic_matrix_2d<GraphicsMath>& m) noexcept {
			data._Matrix = m;
		}
		template<class GraphicsMath>
		inline io2d::wrap_mode _Cairo_graphics_surfaces<GraphicsMath>::wrap_mode(const mask_props_data_type& data) noexcept {
			return data._Wrap_mode;
		}
		template<class GraphicsMath>
		inline io2d::filter _Cairo_graphics_surfaces<GraphicsMath>::filter(const mask_props_data_type& data) noexcept {
			return data._Filter;
		}
		template<class GraphicsMath>
		inline basic_matrix_2d<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::mask_matrix(const mask_props_data_type& data) noexcept {
			return data._Matrix;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::dashes_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_dashes() noexcept {
			dashes_data_type data;
			data.offset = 0.0f;
			return data;
		}
		template<class GraphicsMath>
		template<class ForwardIterator>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::dashes_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_dashes(float offset, ForwardIterator first, ForwardIterator last) {
			dashes_data_type data;
			data.offset = offset;
			data.pattern.insert(data.pattern.end(), first, last);
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::dashes_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_dashes(float offset, ::std::initializer_list<float> il) {
			dashes_data_type data;
			data.offset = offset;
			data.pattern.insert(data.pattern.end(), il);
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::dashes_data_type _Cairo_graphics_surfaces<GraphicsMath>::copy_dashes(const dashes_data_type& data) {
			return data;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::dashes_data_type _Cairo_graphics_surfaces<GraphicsMath>::move_dashes(dashes_data_type&& data) noexcept {
			return data;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::destroy(dashes_data_type& data) noexcept {
			// Do nothing.
		}

		// Helpers to set state when rendering

		template <class GraphicsMath>
		inline void _Set_render_props(cairo_t* context, const optional<basic_render_props<_Cairo_graphics_surfaces<GraphicsMath>>>& r) {
			if (r == nullopt) {
				cairo_set_antialias(context, _Antialias_to_cairo_antialias_t(antialias::good));
				cairo_identity_matrix(context);
				cairo_set_operator(context, CAIRO_OPERATOR_OVER);
			}
			else {
				const auto& props = r.value();
				const auto m = props.surface_matrix();
				cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
				cairo_set_antialias(context, _Antialias_to_cairo_antialias_t(props.antialiasing()));
				cairo_set_matrix(context, &cm);
				cairo_set_operator(context, _Compositing_operator_to_cairo_operator_t(props.compositing()));
			}
		}

		template <class GraphicsMath>
		inline void _Set_clip_props(cairo_t* context, const optional<basic_clip_props<_Cairo_graphics_surfaces<GraphicsMath>>>& c) {
			cairo_reset_clip(context);
			if (c != nullopt) {
				// Save state
				cairo_fill_rule_t fr = cairo_get_fill_rule(context);
				//unique_ptr<cairo_path_t, decltype(&cairo_path_destroy)> op(cairo_copy_path(context), &cairo_path_destroy);
				// Set clip
				const auto& props = c.value()._Get_data();
				cairo_set_fill_rule(context, _Fill_rule_to_cairo_fill_rule_t(props.fill_rule()));
				cairo_new_path(context);
				cairo_append_path(context, props.clip()._Get_data().get());
				cairo_clip(context);
				// Restore saved state
				cairo_set_fill_rule(context, fr);
				//cairo_new_path(context);
				//cairo_append_path(context, op.get());
			}
		}

		template <class GraphicsMath>
		inline void _Set_stroke_props(cairo_t* context, const optional<basic_stroke_props<_Cairo_graphics_surfaces<GraphicsMath>>>& s, float miterMax, const optional<basic_dashes<_Cairo_graphics_surfaces<GraphicsMath>>>& ds) {
			if (s == nullopt) {
				cairo_set_line_width(context, 2.0);
				cairo_set_line_cap(context, CAIRO_LINE_CAP_BUTT);
				cairo_set_line_join(context, CAIRO_LINE_JOIN_MITER);
				cairo_set_miter_limit(context, 10.0);
			}
			else {
				const auto& props = s.value()._Get_data();
				cairo_set_line_width(context, props.line_width());
				cairo_set_line_cap(context, _Line_cap_to_cairo_line_cap_t(props.line_cap()));
				cairo_set_line_join(context, _Line_join_to_cairo_line_join_t(props.line_join()));
				cairo_set_miter_limit(context, ::std::min<float>(miterMax, props.miter_limit()));
			}
			if (ds == nullopt) {
				cairo_set_dash(context, nullptr, 0, 0.0);
			}
			else {
				const auto& d = ds.value()._Get_data();
				const auto& dFloatVal = d.pattern;
				vector<double> dashAsDouble(dFloatVal.size());
				for (const auto& val : dFloatVal) {
					dashAsDouble.push_back(static_cast<double>(val));
				}
				cairo_set_dash(context, dashAsDouble.data(), _Container_size_to_int(dashAsDouble), static_cast<double>(d.offset));
				if (cairo_status(context) == CAIRO_STATUS_INVALID_DASH) {
					_Throw_if_failed_cairo_status_t(CAIRO_STATUS_INVALID_DASH);
				}
			}
		}

		template <class GraphicsMath>
		inline void _Set_brush_props(cairo_t* context, const optional<basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>>& bp, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b) {
			if (bp == nullopt) {
				const auto p = b._Get_data().brush.get();
				cairo_pattern_set_extend(p, CAIRO_EXTEND_NONE);
				cairo_pattern_set_filter(p, CAIRO_FILTER_BILINEAR);
				cairo_pattern_set_matrix(p, &_Cairo_identity_matrix);
				cairo_set_fill_rule(context, CAIRO_FILL_RULE_WINDING);
			}
			else {
				const auto& props = bp.value();
				auto p = b._Get_data().brush.get();
				cairo_pattern_set_extend(p, _Extend_to_cairo_extend_t(props.wrap_mode()));
				cairo_pattern_set_filter(p, _Filter_to_cairo_filter_t(props.filter()));
				const auto& m = props.brush_matrix();
				cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
				cairo_pattern_set_matrix(p, &cm);
				cairo_set_fill_rule(context, _Fill_rule_to_cairo_fill_rule_t(props.fill_rule()));
			}
		}

		template <class GraphicsMath>
		inline void _Set_mask_props(const optional<basic_mask_props<_Cairo_graphics_surfaces<GraphicsMath>>>& mp, const basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>& b) {
			if (mp == nullopt) {
				auto p = b._Get_data().brush.get();
				cairo_pattern_set_extend(p, CAIRO_EXTEND_NONE);
				cairo_pattern_set_filter(p, CAIRO_FILTER_GOOD);
				cairo_pattern_set_matrix(p, &_Cairo_identity_matrix);
			}
			else {
				const auto& props = mp.value();
				auto p = b._Get_data().brush.get();
				cairo_pattern_set_extend(p, _Extend_to_cairo_extend_t(props.wrap_mode()));
				cairo_pattern_set_filter(p, _Filter_to_cairo_filter_t(props.filter()));
				const auto& m = props.mask_matrix();
				cairo_matrix_t cm{ m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21() };
				cairo_pattern_set_matrix(p, &cm);
			}
		}

		// image_surface

		template<class GraphicsMath>
		inline basic_display_point<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::max_dimensions() noexcept {
			return basic_display_point<GraphicsMath>(16384, 16384); // This takes up 1 GB of RAM, you probably don't want to do this. 2048x2048 is the max size for hardware that meets 9_1 specs (i.e. quite low powered or really old). Probably much more reasonable.
		}

		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::image_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_image_surface(io2d::format fmt, int width, int height) {
			image_surface_data_type data;
			data.surface = ::std::move(unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(fmt), width, height), &cairo_surface_destroy));
			data.context = ::std::move(unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(data.surface.get()), &cairo_destroy));
			data.dimensions.x(width);
			data.dimensions.y(height);
			data.format = fmt;
			return data;
		}

#if defined(_Filesystem_support_test)
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::image_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_image_surface(filesystem::path p, image_file_format iff) {
			throw ::std::system_error(::std::make_error_code(::std::errc::not_supported));
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::image_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_image_surface(filesystem::path p, image_file_format iff, ::std::error_code & ec) noexcept {
			ec = ::std::make_error_code(::std::errc::not_supported);
			return image_surface_data_type();
		}
#else
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::image_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_image_surface(::std::string p, image_file_format iff) {
			throw ::std::system_error(::std::make_error_code(::std::errc::not_supported));
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::image_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_image_surface(::std::string p, image_file_format iff, ::std::error_code & ec) noexcept {
			ec = ::std::make_error_code(::std::errc::not_supported);
			return image_surface_data_type();
		}
#endif
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::image_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::move_image_surface(image_surface_data_type&& data) noexcept {
			return data;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::destroy(image_surface_data_type& data) noexcept {
			// Do nothing.
		}
#if defined(_Filesystem_support_test)
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::save(image_surface_data_type& data, filesystem::path p, image_file_format iff) {
			throw ::std::system_error(::std::make_error_code(::std::errc::not_supported));
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::save(image_surface_data_type& data, filesystem::path p, image_file_format iff, error_code& ec) noexcept {
			ec = ::std::make_error_code(::std::errc::not_supported);
			return;
		}
#else
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::save(image_surface_data_type& data, ::std::string p, image_file_format iff) {
			throw ::std::system_error(::std::make_error_code(::std::errc::not_supported));
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::save(image_surface_data_type& data, ::std::string p, image_file_format iff, error_code& ec) noexcept {
			ec = ::std::make_error_code(::std::errc::not_supported));
			return;
		}
#endif
		template<class GraphicsMath>
		inline io2d::format _Cairo_graphics_surfaces<GraphicsMath>::format(const image_surface_data_type& data) noexcept {
			return data.format;
		}
		template<class GraphicsMath>
		inline basic_display_point<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::dimensions(const image_surface_data_type & data) noexcept {
			return data.dimensions;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::clear(image_surface_data_type& data) {
			auto ctx = data.context.get();
			cairo_save(ctx);
			cairo_set_operator(ctx, CAIRO_OPERATOR_CLEAR);
			cairo_set_source_rgba(ctx, 1.0, 1.0, 1.0, 1.0);
			cairo_paint(ctx);
			cairo_restore(ctx);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::flush(image_surface_data_type& data) {
			cairo_surface_flush(data._Surface.get());
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::flush(image_surface_data_type& data, error_code& ec) noexcept {
			cairo_surface_flush(data._Surface.get());
			ec.clear();
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::mark_dirty(image_surface_data_type& data) {
			cairo_surface_mark_dirty(data._Surface.get());
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::mark_dirty(image_surface_data_type& data, error_code& ec) noexcept {
			cairo_surface_mark_dirty(data._Surface.get());
			ec.clear();
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::mark_dirty(image_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents) {
			cairo_surface_mark_dirty_rectangle(_Surface.get(), _Float_to_int(extents.x()), _Float_to_int(extents.y()), _Float_to_int(extents.width()), _Float_to_int(extents.height()));
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::mark_dirty(image_surface_data_type& data, const basic_bounding_box<GraphicsMath>& extents, error_code& ec) noexcept {
			cairo_surface_mark_dirty_rectangle(_Surface.get(), _Float_to_int(extents.x()), _Float_to_int(extents.y()), _Float_to_int(extents.width()), _Float_to_int(extents.height()));
			ec.clear();
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::paint(image_surface_data_type & data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
			auto context = data.context.get();
			_Set_render_props(context, rp);
			_Set_clip_props(context, cl);
			_Set_brush_props(context, bp, b);
			cairo_set_source(context, b._Native_handle());
			cairo_paint(context);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::stroke(image_surface_data_type & data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush<_Graphics_surfaces_type>& bp, const basic_stroke_props<_Graphics_surfaces_type>& sp, const basic_dashes<_Graphics_surfaces_type>& d, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
			auto context = data.context.get();
			_Set_render_props(context, rp);
			_Set_clip_props(context, cl);
			_Set_brush_props(context, bp, b);
			_Set_stroke_props(context, sp, _Line_join_miter_miter_limit, d);
			cairo_set_source(context, b._Get_data().brush.get());
			cairo_new_path(context);
			cairo_append_path(context, ip._Get_data().path.get());
			cairo_stroke(context);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::fill(image_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
			auto context = data.context.get();
			_Set_render_props(context, rp);
			_Set_clip_props(context, cl);
			_Set_brush_props(context, bp, b);
			cairo_set_source(context, b._Get_data().brush.get());
			cairo_new_path(context);
			cairo_append_path(context, ip._Get_data().path.get());
			cairo_fill(context);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::mask(image_surface_data_type & data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush<_Graphics_surfaces_type>& mb, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_mask_props<_Graphics_surfaces_type>& mp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
			auto context = data.context.get();
			_Set_render_props(context, rp);
			_Set_clip_props(context, cl);
			_Set_brush_props(context, bp, b);
			_Set_mask_props(mp, mb);
			cairo_set_source(context, b._Get_data().brush.get());
			cairo_new_path(context);
			cairo_mask(context, mb._Get_data().brush.get());
		}


		// helper functions for output surfaces

		template <class GraphicsMath>
		inline void _Create_display_surface_and_context(typename _Cairo_graphics_surfaces<GraphicsMath>::_Display_surface_data_type& data) {
			if (data.hwnd != 0) {
				data.display_surface = ::std::move(::std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_win32_surface_create(data.hdc), &cairo_surface_destroy));
				auto sfc = data.display_surface.get();
				_Throw_if_failed_cairo_status_t(cairo_surface_status(sfc));
				data.display_context = ::std::move(::std::unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(sfc), &cairo_destroy));
				_Throw_if_failed_cairo_status_t(cairo_status(data.display_context.get()));
			}
		}

		template <class GraphicsSurfaces>
		inline void _Ds_clear(typename GraphicsSurfaces::_Display_surface_data_type& data) {
			GraphicsSurfaces::clear(data.back_buffer);
		}
		template <class GraphicsSurfaces>
		inline void _Ds_paint(typename GraphicsSurfaces::_Display_surface_data_type& data, const basic_brush<GraphicsSurfaces>& b, const basic_brush_props<GraphicsSurfaces>& bp, const basic_render_props<GraphicsSurfaces>& rp, const basic_clip_props<GraphicsSurfaces>& cl) {
			GraphicsSurfaces::paint(data.back_buffer, b, bp, rp, cl);
		}
		template <class GraphicsSurfaces>
		inline void _Ds_stroke(typename GraphicsSurfaces::_Display_surface_data_type& data, const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const basic_brush<GraphicsSurfaces>& bp, const basic_stroke_props<GraphicsSurfaces>& sp, const basic_dashes<GraphicsSurfaces>& d, const basic_render_props<GraphicsSurfaces>& rp, const basic_clip_props<GraphicsSurfaces>& cl) {
			GraphicsSurfaces::stroke(data.back_buffer, b, ip, bp, sp, d, rp, cl);
		}
		template <class GraphicsSurfaces>
		inline void _Ds_fill(typename GraphicsSurfaces::_Display_surface_data_type& data, const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const basic_brush_props<GraphicsSurfaces>& bp, const basic_render_props<GraphicsSurfaces>& rp, const basic_clip_props<GraphicsSurfaces>& cl) {
			GraphicsSurfaces::fill(data.back_buffer, b, ip, bp, rp, cl);
		}
		template <class GraphicsSurfaces>
		inline void _Ds_mask(typename GraphicsSurfaces::_Display_surface_data_type& data, const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const basic_brush_props<GraphicsSurfaces>& bp, const basic_mask_props<GraphicsSurfaces>& mp, const basic_render_props<GraphicsSurfaces>& rp, const basic_clip_props<GraphicsSurfaces>& cl) {
			GraphicsSurfaces::mask(data.back_buffer, b, mb, bp, mp, rp, cl);
		}
		template <class GraphicsSurfaces>
		inline void _Ds_dimensions(typename GraphicsSurfaces::_Display_surface_data_type& data, const basic_display_point<typename GraphicsSurfaces::graphics_math_type>& val) {
			if (val != data.back_buffer.dimensions) {
				// Recreate the render target that is drawn to the displayed surface
				data.back_buffer = ::std::move(GraphicsSurfaces::create_image_surface(data.back_buffer.format, val.x(), val.y()));
			}
		}
		template <class GraphicsSurfaces>
		inline void _Ds_scaling(typename GraphicsSurfaces::_Display_surface_data_type& data, io2d::scaling val) {
			data.scl = val;
		}
		template <class GraphicsSurfaces>
		inline void _Ds_letterbox_brush(typename GraphicsSurfaces::_Display_surface_data_type& data, const optional<basic_brush<GraphicsSurfaces>>& val, const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept {
			data.letterbox_brush_is_default = !val.has_value();
			data._Letterbox_brush = (val.has_value() ? val.value() : data._Default_letterbox_brush);
			data._Letterbox_brush_props = (bp.has_value() ? bp.value() : basic_brush_props<GraphicsSurfaces>());

		}
		template <class GraphicsSurfaces>
		inline void _Ds_letterbox_brush_props(typename GraphicsSurfaces::_Display_surface_data_type& data, const basic_brush_props<GraphicsSurfaces>& val) {
			data._Letterbox_brush_props = val;
		}
		template <class GraphicsSurfaces>
		inline void _Ds_auto_clear(typename GraphicsSurfaces::_Display_surface_data_type& data, bool val) {
			data.auto_clear = val;
		}
		template <class GraphicsSurfaces>
		inline void _Ds_redraw_required(typename GraphicsSurfaces::_Display_surface_data_type& data, bool val) {
			data.redraw_required = val;
		}
		template <class GraphicsSurfaces>
		inline io2d::format _Ds_format(const typename GraphicsSurfaces::_Display_surface_data_type& data) noexcept {
			return data.back_buffer.format;
		}
		template <class GraphicsSurfaces>
		inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> _Ds_dimensions(const typename GraphicsSurfaces::_Display_surface_data_type& data) noexcept {
			return data.back_buffer.dimensions;
		}
		template <class GraphicsSurfaces>
		inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> _Ds_max_dimensions() noexcept {
			return GraphicsSurfaces::max_dimensions();
		}
		template <class GraphicsSurfaces>
		inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> _Ds_display_dimensions(const typename GraphicsSurfaces::_Display_surface_data_type& data) noexcept {
			return data.display_dimensions;
		}
		template <class GraphicsSurfaces>
		inline basic_display_point<typename GraphicsSurfaces::graphics_math_type> _Ds_max_display_dimensions() noexcept {
			return GraphicsSurface::max_display_dimensions();
		}
		template <class GraphicsSurfaces>
		inline io2d::scaling _Ds_scaling(typename GraphicsSurfaces::_Display_surface_data_type& data) noexcept {
			return data.scl;
		}
		template <class GraphicsSurfaces>
		inline optional<basic_brush<GraphicsSurfaces>> _Ds_letterbox_brush(const typename GraphicsSurfaces::_Display_surface_data_type& data) noexcept {
			return (data.letterbox_brush_is_default ? optional<basic_brush<GraphicsSurfaces>>() : optional<basic_brush<GraphicsSurfaces>>(data._Letterbox_brush));
		}
		template <class GraphicsSurfaces>
		inline basic_brush_props<GraphicsSurfaces> _Ds_letterbox_brush_props(const typename GraphicsSurfaces::_Display_surface_data_type& data) noexcept {
			return data._Letterbox_brush_props;
		}
		template <class GraphicsSurfaces>
		inline bool _Ds_auto_clear(const typename GraphicsSurfaces::_Display_surface_data_type& data) noexcept {
			return data.auto_clear;
		}
		template <class GraphicsSurfaces>
		inline bool _Ds_redraw_required(const typename GraphicsSurfaces::_Display_surface_data_type& data) noexcept {
			return data.redraw_required;
		}


		// unmanaged output surface functions

		template<class GraphicsMath>
		inline basic_display_point<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::max_display_dimensions() noexcept {
			return basic_display_point<GraphicsMath>(16384, 16384); // This takes up 1 GB of RAM, you probably don't want to do this. 2048x2048 is the max size for hardware that meets 9_1 specs (i.e. quite low powered or really old). Probably much more reasonable.
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::unmanaged_output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_unmanaged_output_surface(HINSTANCE hInstance, HWND hwnd, HDC hdc, int preferredWidth, int preferredHeight, io2d::format preferredFormat) {
			unmanaged_output_surface_data_type uosd;
			_Display_surface_data_type& data = uosd.data;
			data.hInstance = hInstance;
			data.hwnd = hwnd;
			data.hdc = hdc;
			// WNDCLASS names can be a max of 256 chars and needs an extra char for null terminator, hence 257.
			WCHAR wndClassName[257] = {};
			if (GetClassName(hwnd, wndClassName, ARRAYSIZE(wndClassName)) == 0) {
				_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to GetClassName.");
			}
			WNDCLASS wndClass = {};
			if (GetClassInfo(hInstance, wndClassName, &wndClass) == 0) {
				_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to GetClassInfo.");
			}
			// If this is false we need to create the display_surface and display_context every time the draw callback is invoked.
			data.hasOwnDC = (wndClass.style & CS_OWNDC) != 0;
			data.unmanaged = true;
			if (data.hasOwnDC) {
				if (hdc == nullptr) {
					data.hdc = GetDC(hwnd);
				}
				_Create_display_surface_and_context<GraphicsMath>(data);
			}
			data._Letterbox_brush = basic_brush<_Cairo_graphics_surfaces>(rgba_color::black());
			RECT clientRect = {};
			if (GetClientRect(hwnd, &clientRect) == 0) {
				_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to GetClientRect.");
			}
			data.display_dimensions.x(clientRect.right);
			data.display_dimensions.y(clientRect.bottom);
			data.back_buffer = ::std::move(create_image_surface(preferredFormat, preferredWidth, preferredHeight));
			return uosd;
		}
		template <class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::unmanaged_output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::move_unmanaged_output_surface(unmanaged_output_surface_data_type&& data) noexcept {
			data.data.back_buffer = ::std::move(move_image_surface(::std::move(data.data.back_buffer)));
			return data;
		}
		template <class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::destroy(unmanaged_output_surface_data_type& data) noexcept {
			destroy(data.data.back_buffer);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::invoke_draw_callback(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc) {
			data.data.draw_callback(sfc);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::invoke_size_change_callback(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc) {
			data.data.size_change_callback(sfc);
		}
		template<class GraphicsMath>
		inline basic_bounding_box<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::invoke_user_scaling_callback(unmanaged_output_surface_data_type& data, basic_unmanaged_output_surface<_Graphics_surfaces_type>& sfc, bool& useLetterboxBrush) {
			useLetterboxBrush = false;
			return data.data.user_scaling_callback(sfc, useLetterboxBrush)
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::display_dimensions(unmanaged_output_surface_data_type& data, const basic_display_point<GraphicsMath>& val) {
			_Ds_display_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val);
			_Create_display_surface_and_context(data.data);
			data.data.redraw_required = true;
			// This is unmanaged so we don't deal with resizing the user-visible output (e.g. a window).
		}

		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::clear(unmanaged_output_surface_data_type& data) {
			_Ds_clear<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template <class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::paint(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
			_Ds_paint<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, b, bp, rp, cl);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::stroke(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush<_Graphics_surfaces_type>& bp, const basic_stroke_props<_Graphics_surfaces_type>& sp, const basic_dashes<_Graphics_surfaces_type>& d, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
			_Ds_stroke<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, b, ip, bp, sp, d, rp, cl);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::fill(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
			_Ds_fill<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, b, ip, bp, rp, cl);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::mask(unmanaged_output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush<_Graphics_surfaces_type>& mb, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_mask_props<_Graphics_surfaces_type>& mp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
			_Ds_mask<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, b, mb, bp, mp, rp, cl);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::draw_callback(unmanaged_output_surface_data_type& data, function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)> fn) {
			data.draw_callback = fn;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::size_change_callback(unmanaged_output_surface_data_type& data, function<void(basic_unmanaged_output_surface<_Graphics_surfaces_type>&)> fn) {
			data.size_change_callback = fn;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::user_scaling_callback(unmanaged_output_surface_data_type& data, function<basic_bounding_box<GraphicsMath>(const basic_unmanaged_output_surface<_Graphics_surfaces_type>&, bool&)> fn) {
			data.user_scaling_callback = fn;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::dimensions(unmanaged_output_surface_data_type& data, const basic_display_point<GraphicsMath>& val) {
			_Ds_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::scaling(unmanaged_output_surface_data_type& data, io2d::scaling val) {
			_Ds_scaling<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::letterbox_brush(unmanaged_output_surface_data_type& data, const optional<basic_brush<_Graphics_surfaces_type>>& val, const optional<basic_brush_props<_Graphics_surfaces_type>>& bp) noexcept {
			_Ds_letterbox_brush<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val, bp);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::letterbox_brush_props(unmanaged_output_surface_data_type& data, const basic_brush_props<_Graphics_surfaces_type>& val) {
			_Ds_letterbox_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::auto_clear(unmanaged_output_surface_data_type& data, bool val) {
			_Ds_auto_clear<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::redraw_required(unmanaged_output_surface_data_type& data, bool val) {
			_Ds_redraw_required<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val);
		}
		template<class GraphicsMath>
		inline io2d::format _Cairo_graphics_surfaces<GraphicsMath>::format(const unmanaged_output_surface_data_type& data) noexcept {
			return _Ds_format<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template<class GraphicsMath>
		inline basic_display_point<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::dimensions(const unmanaged_output_surface_data_type& data) noexcept {
			return _Ds_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template<class GraphicsMath>
		inline basic_display_point<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::display_dimensions(const unmanaged_output_surface_data_type& data) noexcept {
			return _Ds_display_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template<class GraphicsMath>
		inline io2d::scaling _Cairo_graphics_surfaces<GraphicsMath>::scaling(unmanaged_output_surface_data_type& data) noexcept {
			return _Ds_scaling<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template<class GraphicsMath>
		inline optional<basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::letterbox_brush(const unmanaged_output_surface_data_type& data) noexcept {
			return _Ds_letterbox_brush<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template<class GraphicsMath>
		inline basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>> _Cairo_graphics_surfaces<GraphicsMath>::letterbox_brush_props(const unmanaged_output_surface_data_type& data) noexcept {
			return _Ds_letterbox_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template<class GraphicsMath>
		inline bool _Cairo_graphics_surfaces<GraphicsMath>::auto_clear(const unmanaged_output_surface_data_type& data) noexcept {
			return _Ds_auto_clear<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template<class GraphicsMath>
		inline bool _Cairo_graphics_surfaces<GraphicsMath>::redraw_required(const unmanaged_output_surface_data_type& data) noexcept {
			return _Ds_redraw_required<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}

		// output surface functions

		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, io2d::scaling scl, io2d::refresh_rate rr, float fps) {
			output_surface_data_type result;
			_Display_surface_win32_data& data = result.data;
			data.display_dimensions.x(preferredWidth);
			data.display_dimensions.y(preferredHeight);
			data.rr = rr;
			data.refresh_rate = fps;
			data.scl = scl;
			data.back_buffer.format = preferredFormat;
			data.back_buffer.dimensions.x(preferredWidth);
			data.back_buffer.dimensions.y(preferredHeight);
			return result;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, error_code& ec, io2d::scaling scl, io2d::refresh_rate rr, float fps) noexcept {
			output_surface_data_type result;
			_Display_surface_win32_data& data = result.data;
			data.display_dimensions.x(preferredWidth);
			data.display_dimensions.y(preferredHeight);
			data.rr = rr;
			data.refresh_rate = fps;
			data.scl = scl;
			data.back_buffer.format = preferredFormat;
			data.back_buffer.dimensions.x(preferredWidth);
			data.back_buffer.dimensions.y(preferredHeight);
			ec.clear()
			return result;
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, io2d::scaling scl, io2d::refresh_rate rr, float fps) {
			output_surface_data_type result;
			_Display_surface_win32_data& data = result.data;
			data.display_dimensions.x(preferredDisplayWidth);
			data.display_dimensions.y(preferredDisplayHeight);
			data.rr = rr;
			data.refresh_rate = fps;
			data.scl = scl;
			data.back_buffer.format = preferredFormat;
			data.back_buffer.dimensions.x(preferredWidth);
			data.back_buffer.dimensions.y(preferredHeight);
			return result;
		}
		template <class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::create_output_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, error_code& ec, io2d::scaling scl, io2d::refresh_rate rr, float fps) noexcept {
			output_surface_data_type result;
			_Display_surface_win32_data& data = result.data;
			data.display_dimensions.x(preferredDisplayWidth);
			data.display_dimensions.y(preferredDisplayHeight);
			data.rr = rr;
			data.refresh_rate = fps;
			data.scl = scl;
			data.back_buffer.format = preferredFormat;
			data.back_buffer.dimensions.x(preferredWidth);
			data.back_buffer.dimensions.y(preferredHeight);
			ec.clear();
			return result;
		}
		template <class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::output_surface_data_type _Cairo_graphics_surfaces<GraphicsMath>::move_output_surface(output_surface_data_type&& data) noexcept {
			data.data.back_buffer = ::std::move(move_image_surface(::std::move(data.data.back_buffer)));
			return data;
		}
		template <class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::destroy(output_surface_data_type& data) noexcept {
			destroy(data.data.back_buffer);
		}
		template<class GraphicsMath>
		inline typename _Cairo_graphics_surfaces<GraphicsMath>::show_return_data_type _Cairo_graphics_surfaces<GraphicsMath>::begin_show(output_surface_data_type& osd, basic_output_surface<_Cairo_graphics_surfaces<GraphicsMath>>* instance, basic_output_surface<_Cairo_graphics_surfaces<GraphicsMath>>& sfc) {
			_Display_surface_data_type& data = osd.data;
			RECT rc;
			rc.top = 0;
			rc.left = 0;
			rc.right = data.display_dimensions.x();
			rc.bottom = data.display_dimensions.y();

			// Adjust the window size for correct device size
			if (!AdjustWindowRect(&rc, (WS_OVERLAPPEDWINDOW | WS_VISIBLE), FALSE)) {
				_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to AdjustWindowRect in cairo_display_surface::cairo_display_surface(int, int, format, int, int, scaling).");
			}

			long lwidth = rc.right - rc.left;
			long lheight = rc.bottom - rc.top;

			long lleft = 10;
			long ltop = 10;


			// Create an instance of the window
			data.hwnd = CreateWindowEx(
				static_cast<DWORD>(0),				// extended style
				_Refimpl_window_class_name,			// class name
				L"",								// instance title
				(WS_OVERLAPPEDWINDOW | WS_VISIBLE),	// window style
				lleft, ltop,						// initial x, y
				lwidth,								// initial width
				lheight,							// initial height
				static_cast<HWND>(nullptr),			// handle to parent
				static_cast<HMENU>(nullptr),		// handle to menu
				static_cast<HINSTANCE>(nullptr),	// instance of this application
				static_cast<LPVOID>(nullptr));		// extra creation parms

			if (data.hwnd == nullptr) {
				_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to CreateWindowEx.");
			}

			SetLastError(ERROR_SUCCESS);
			if (SetWindowLongPtrW(data.hwnd, 0, static_cast<LONG_PTR>(instance)) == 0) {
				// SetWindowLongPtr is weird in terms of how it fails. See its documentation. Hence this weird check.
				DWORD lastError = GetLastError();
				if (lastError != ERROR_SUCCESS) {
					_Throw_system_error_for_GetLastError(lastError, "Failed call to SetWindowLongPtrW(HWND, int, LONG_PTR) in cairo_display_surface::cairo_display_surface(int, int, format, int, int, scaling)");
				}
			}
			data.hasOwnDC = true;
			data.hdc = GetDC(hwnd);

			_Create_display_surface_and_context<GraphicsMath>(data);

			data._Default_letterbox_brush = basic_brush<_Cairo_graphics_surfaces>(rgba_color::black());
			data._Letterbox_brush = data._Default_letterbox_brush;

			data.back_buffer = ::std::move(create_image_surface(data.back_buffer.format, data.back_buffer.dimensions.x(), data.back_buffer.dimensions.y()));

			// Initially display the window
			ShowWindow(data.hwnd, SW_SHOWNORMAL);
			UpdateWindow(data.hwnd);

			MSG msg{};
			msg.message = WM_NULL;
			//			if (_Display_surface.native_handle()._Draw_fn == nullptr) {
			//				throw system_error(make_error_code(errc::operation_would_block));
			//			}
			_Impl._Elapsed_draw_time = 0.0F;
#ifdef _IO2D_WIN32FRAMERATE
			auto previousTime = steady_clock::now();
			long long int elapsedDrawNanoseconds = 0LL;
			int updateTitleCounter = -1;
			deque<chrono::nanoseconds> elapsedNanoseconds(static_cast<size_t>(30), 33'333'333ns);
#endif
			while (msg.message != WM_QUIT) {
#ifdef _IO2D_WIN32FRAMERATE
				auto currentTime = steady_clock::now();
				auto elapsedTimeIncrement = static_cast<float>(duration_cast<nanoseconds>(currentTime - previousTime).count());
				_Elapsed_draw_time += elapsedTimeIncrement;
				elapsedDrawNanoseconds += duration_cast<nanoseconds>(currentTime - previousTime).count();
				previousTime = currentTime;
#endif
				if (!PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
					RECT clientRect;
					GetClientRect(_Impl._Hwnd, &clientRect);
					if (clientRect.right - clientRect.left != data.display_dimensions.x() || clientRect.bottom - clientRect.top != data.display_dimensions.y()) {
						// If there is a size mismatch we skip painting and resize the window instead.
						display_dimensions(data, data.display_dimensions);
						if (data.display_dimensions != data.dimensions) {
							invoke_size_change_callback(sfc);
						}
						continue;
					}
					else {
						bool redraw = true;
						if (data.rr == io2d::refresh_rate::as_needed) {
							redraw = data.redraw_required;
							data.redraw_required = false;
						}

						const auto desiredElapsed = 1'000'000'000.0F / data.refresh_fps;
#ifdef _IO2D_WIN32FRAMERATE
						const long long desiredElapsedNanoseconds = static_cast<long long>(1'000'000'000.00F / _Desired_frame_rate);
#endif
						if (data.rr == io2d::refresh_rate::fixed) {
							// desiredElapsed is the amount of time, in nanoseconds, that must have passed before we should redraw.
							redraw = data.elapsed_draw_time >= desiredElapsed;
						}
						if (redraw) {
							// Run user draw function:
							invoke_draw_callback(sfc);

#ifdef _IO2D_WIN32FRAMERATE
							elapsedNanoseconds.pop_front();
							elapsedNanoseconds.push_back(chrono::nanoseconds(elapsedDrawNanoseconds));
#endif
							if (data.rr == experimental::io2d::refresh_rate::fixed) {
								while (data.elapsed_draw_time >= desiredElapsed) {
									data.elapsed_draw_time -= desiredElapsed;
								}
#ifdef _IO2D_WIN32FRAMERATE
								while (elapsedDrawNanoseconds >= desiredElapsedNanoseconds) {
									elapsedDrawNanoseconds -= desiredElapsedNanoseconds;
								}
#endif
							}
							else {
								data.elapsed_draw_time = 0.0F;
#ifdef _IO2D_WIN32FRAMERATE
								elapsedDrawNanoseconds = 0LL;
#endif
							}
						}
					}
				}
				else {
					if (msg.message != WM_QUIT) {
						TranslateMessage(&msg);
						DispatchMessage(&msg);

						if (msg.message == WM_PAINT) {
							const auto desiredElapsed = 1'000'000'000.0F / data.refresh_fps;
#ifdef _IO2D_WIN32FRAMERATE
							elapsedNanoseconds.pop_front();
							elapsedNanoseconds.push_back(chrono::nanoseconds(elapsedDrawNanoseconds));

							const long long desiredElapsedNanoseconds = static_cast<long long>(1'000'000'000.00F / _Desired_frame_rate);
#endif
							if (data.rr == io2d::refresh_rate::fixed) {
								while (data.elapsed_draw_time >= desiredElapsed) {
									data.elapsed_draw_time -= desiredElapsed;
								}
#ifdef _IO2D_WIN32FRAMERATE
								while (elapsedDrawNanoseconds >= desiredElapsedNanoseconds) {
									elapsedDrawNanoseconds -= desiredElapsedNanoseconds;
								}
#endif
							}
							else {
								data.elapsed_draw_time = 0.0F;
#ifdef _IO2D_WIN32FRAMERATE
								elapsedDrawNanoseconds = 0LL;
#endif
							}
						}
					}
				}

#ifdef _IO2D_WIN32FRAMERATE
				if (updateTitleCounter == -1) {
					SetWindowText(msg.hwnd, L"FPS: ");
				}
				updateTitleCounter++;
				if (updateTitleCounter == 50 && msg.hwnd == 0) {
					updateTitleCounter--;
				}
				if (updateTitleCounter == 50 && msg.hwnd != 0) {
					unsigned long long sumNanoElapsed = 0LL;
					for (auto iter = begin(elapsedNanoseconds), last = end(elapsedNanoseconds); iter != last; iter++) {
						const auto val = *iter;
						sumNanoElapsed += val.count();
					}
					auto avgNanoFrameTime = (sumNanoElapsed / elapsedNanoseconds.size());
					const auto fpsNano = 1'000'000'000.0F / avgNanoFrameTime;
					wstringstream fpsStr;
					fpsStr << "FPS: " << fixed << setprecision(5) << fpsNano;
					wstring fpsStr_Str;
					fpsStr_Str = fpsStr.str();
					const wchar_t* fpsStrWindowText = fpsStr_Str.c_str();
					if (!SetWindowText(msg.hwnd, fpsStrWindowText)) {
						_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to SetWindowText.");
					}
					updateTitleCounter = 0;
				}
#endif
			}
			data.elapsed_draw_time = 0.0F;
			show_return_data_type result;
			result.result = msg.wParam;
			return result;
		}

		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::end_show(output_surface_data_type& data) {
			PostQuitMessage(0);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::refresh_rate(output_surface_data_type& data, io2d::refresh_rate val) {
			data.data.rr = val;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::desired_frame_rate(output_surface_data_type& data, float val) {
			const float oneFramePerHour = 1.0f / (60.0f * 60.0f); // If you need a lower framerate than this, use as_needed and control the refresh by writing a timer that will trigger a refresh at your desired interval.
			const float maxFPS = 120.0f; // It's unlikely to find a display output that operates higher than this.
			data.data.refresh_fps = ::std::min(::std::max(val, oneFramePerHour), maxFPS);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::display_dimensions(output_surface_data_type& data, const basic_display_point<GraphicsMath>& val) {
			data.data.display_dimensions = val;
			if (data.data.hwnd != 0) {
				// Change window size then call _Ds_display_dimensions, I think.
				RECT clientRect;
				RECT windowRect;
				GetWindowRect(data.data.hwnd, &windowRect);
				GetClientRect(data.data.hwnd, &clientRect);
				auto crWidth = clientRect.right - clientRect.left;
				auto crHeight = clientRect.bottom - clientRect.top;
				auto wrWidth = windowRect.right - windowRect.left;
				auto wrHeight = windowRect.bottom - windowRect.top;
				auto displayWidth = val.x();
				auto displayHeight = val.y();
				if (crWidth != displayWidth || crHeight != displayHeight) {
					auto width = std::max((wrWidth - crWidth) + 1L, (displayWidth - crWidth) + wrWidth);
					auto height = std::max((wrHeight - crHeight) + 1L, (displayHeight - crHeight) + wrHeight);
					// Resize the window.
					if (!SetWindowPos(data.data.hwnd, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS)) {
						_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to SetWindowPos.");
					}

					if (!PostMessageW(data.data.hwnd, WM_PAINT, static_cast<WPARAM>(0), static_cast<LPARAM>(0))) {
						_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to PostMessageW.");
					}
				}
			}
			//_Ds_display_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val);
			_Create_display_surface_and_context<GraphicsMath>(data.data);
			data.data.redraw_required = true;
		}
		template<class GraphicsMath>
		inline io2d::refresh_rate _Cairo_graphics_surfaces<GraphicsMath>::refresh_rate(const output_surface_data_type& data) noexcept {
			return data.data.rr;
		}
		template<class GraphicsMath>
		inline float _Cairo_graphics_surfaces<GraphicsMath>::desired_frame_rate(const output_surface_data_type& data) noexcept {
			return data.data.refresh_fps;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::clear(output_surface_data_type& data) {
			_Ds_clear<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template <class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::paint(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
			_Ds_paint<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, b, bp, rp, cl);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::stroke(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush<_Graphics_surfaces_type>& bp, const basic_stroke_props<_Graphics_surfaces_type>& sp, const basic_dashes<_Graphics_surfaces_type>& d, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
			_Ds_stroke<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, b, ip, bp, sp, d, rp, cl);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::fill(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_interpreted_path<_Graphics_surfaces_type>& ip, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
			_Ds_fill<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, b, ip, bp, rp, cl);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::mask(output_surface_data_type& data, const basic_brush<_Graphics_surfaces_type>& b, const basic_brush<_Graphics_surfaces_type>& mb, const basic_brush_props<_Graphics_surfaces_type>& bp, const basic_mask_props<_Graphics_surfaces_type>& mp, const basic_render_props<_Graphics_surfaces_type>& rp, const basic_clip_props<_Graphics_surfaces_type>& cl) {
			_Ds_mask<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, b, mb, bp, mp, rp, cl);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::draw_callback(output_surface_data_type& data, function<void(basic_output_surface<_Graphics_surfaces_type>&)> fn) {
			data.draw_callback = fn;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::size_change_callback(output_surface_data_type& data, function<void(basic_output_surface<_Graphics_surfaces_type>&)> fn) {
			data.size_change_callback = fn;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::user_scaling_callback(output_surface_data_type& data, function<basic_bounding_box<GraphicsMath>(const basic_output_surface<_Graphics_surfaces_type>&, bool&)> fn) {
			data.user_scaling_callback = fn;
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::dimensions(output_surface_data_type& data, const basic_display_point<GraphicsMath>& val) {
			_Ds_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::scaling(output_surface_data_type& data, io2d::scaling val) {
			_Ds_scaling<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::letterbox_brush(output_surface_data_type& data, const optional<basic_brush<_Graphics_surfaces_type>>& val, const optional<basic_brush_props<_Graphics_surfaces_type>>& bp) noexcept {
			_Ds_letterbox_brush<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val, bp);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::letterbox_brush_props(output_surface_data_type& data, const basic_brush_props<_Graphics_surfaces_type>& val) {
			_Ds_letterbox_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::auto_clear(output_surface_data_type& data, bool val) {
			_Ds_auto_clear<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val);
		}
		template<class GraphicsMath>
		inline void _Cairo_graphics_surfaces<GraphicsMath>::redraw_required(output_surface_data_type& data, bool val) {
			_Ds_redraw_required<_Cairo_graphics_surfaces<GraphicsMath>>(data.data, val);
		}
		template<class GraphicsMath>
		inline io2d::format _Cairo_graphics_surfaces<GraphicsMath>::format(const output_surface_data_type& data) noexcept {
			return _Ds_format<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template<class GraphicsMath>
		inline basic_display_point<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::dimensions(const output_surface_data_type& data) noexcept {
			return _Ds_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template<class GraphicsMath>
		inline basic_display_point<GraphicsMath> _Cairo_graphics_surfaces<GraphicsMath>::display_dimensions(const output_surface_data_type& data) noexcept {
			return _Ds_display_dimensions<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template<class GraphicsMath>
		inline io2d::scaling _Cairo_graphics_surfaces<GraphicsMath>::scaling(output_surface_data_type& data) noexcept {
			return _Ds_scaling<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template<class GraphicsMath>
		inline optional<basic_brush<_Cairo_graphics_surfaces<GraphicsMath>>> _Cairo_graphics_surfaces<GraphicsMath>::letterbox_brush(const output_surface_data_type& data) noexcept {
			return _Ds_letterbox_brush<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template<class GraphicsMath>
		inline basic_brush_props<_Cairo_graphics_surfaces<GraphicsMath>> _Cairo_graphics_surfaces<GraphicsMath>::letterbox_brush_props(const output_surface_data_type& data) noexcept {
			return _Ds_letterbox_brush_props<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template<class GraphicsMath>
		inline bool _Cairo_graphics_surfaces<GraphicsMath>::auto_clear(const output_surface_data_type& data) noexcept {
			return _Ds_auto_clear<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
		template<class GraphicsMath>
		inline bool _Cairo_graphics_surfaces<GraphicsMath>::redraw_required(const output_surface_data_type& data) noexcept {
			return _Ds_redraw_required<_Cairo_graphics_surfaces<GraphicsMath>>(data.data);
		}
	}
}