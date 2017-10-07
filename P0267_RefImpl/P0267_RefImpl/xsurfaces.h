#pragma once
#include "xsurfaces_enums.h"

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {

				template <class GraphicsMath>
				class basic_render_props {
				//public:
				//	using matrix_2d_type = typename GraphicsMath::matrix_2d;
				//private:
					antialias _Antialiasing = antialias::good;
					basic_matrix_2d<GraphicsMath> _Matrix;// = matrix_2d::init_identity(); // Transformation matrix
					compositing_op _Compositing = compositing_op::over;
				public:
					constexpr basic_render_props() noexcept;
					constexpr explicit basic_render_props(antialias a, const basic_matrix_2d<GraphicsMath>& m = basic_matrix_2d<GraphicsMath>{}, compositing_op co = compositing_op::over) noexcept;
					constexpr void antialiasing(antialias a) noexcept;
					constexpr void compositing(compositing_op co) noexcept;
					constexpr void surface_matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept;
					constexpr antialias antialiasing() const noexcept;
					constexpr compositing_op compositing() const noexcept;
					constexpr basic_matrix_2d<GraphicsMath> surface_matrix() const noexcept;
				};

				template <class GraphicsMath>
				class basic_brush_props {
				//public:
				//	using matrix_2d_type = typename GraphicsMath::matrix_2d;
				//private:
					experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::none;
					experimental::io2d::filter _Filter = experimental::io2d::filter::good;
					experimental::io2d::fill_rule _Fill_rule = experimental::io2d::fill_rule::winding;
					basic_matrix_2d<GraphicsMath> _Matrix;

				public:
					constexpr basic_brush_props(io2d::wrap_mode w = io2d::wrap_mode::none, io2d::filter fi = io2d::filter::good, io2d::fill_rule fr = io2d::fill_rule::winding, const basic_matrix_2d<GraphicsMath>& m = basic_matrix_2d<GraphicsMath>{}) noexcept;
					constexpr void filter(io2d::filter fi) noexcept;
					constexpr void wrap_mode(io2d::wrap_mode w) noexcept;
					constexpr void fill_rule(io2d::fill_rule fr) noexcept;
					constexpr void brush_matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept;
					constexpr io2d::filter filter() const noexcept;
					constexpr io2d::wrap_mode wrap_mode() const noexcept;
					constexpr io2d::fill_rule fill_rule() const noexcept;
					constexpr basic_matrix_2d<GraphicsMath> brush_matrix() const noexcept;
				};

				template <class SurfaceHandler>
				class basic_clip_props {
					interpreted_path<SurfaceHandler> _Clip;
					experimental::io2d::fill_rule _Fill_rule = experimental::io2d::fill_rule::winding;
				public:
					// surplus to paper
					template <class GraphicsMath>
					explicit basic_clip_props(const basic_bounding_box<GraphicsMath>& r, experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding);

					basic_clip_props() noexcept = default;
					template <class GraphicsMath, class Allocator>
					explicit basic_clip_props(const path_builder<GraphicsMath, Allocator>& pb, experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding);
					explicit basic_clip_props(const interpreted_path<SurfaceHandler>& pg, experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding) noexcept;
					template <class GraphicsMath, class Allocator>
					void clip(const path_builder<GraphicsMath, Allocator>& pb);
					void clip(const interpreted_path<SurfaceHandler>& pg) noexcept;
					void fill_rule(experimental::io2d::fill_rule fr) noexcept;
					interpreted_path<SurfaceHandler> clip() const noexcept;
					experimental::io2d::fill_rule fill_rule() const noexcept;
				};

				class stroke_props {
					float _Line_width = 2.0F;
					float _Miter_limit = 10.0F;
					experimental::io2d::line_cap _Line_cap = experimental::io2d::line_cap::none;
					experimental::io2d::line_join _Line_join = experimental::io2d::line_join::miter;
					//optional<dashes> _Dashes;
				public:
					constexpr stroke_props() noexcept;
					constexpr explicit stroke_props(float w, io2d::line_cap lc = io2d::line_cap::none, io2d::line_join lj = io2d::line_join::miter, float ml = 10.0f) noexcept;
					constexpr void line_width(float w) noexcept;
					constexpr void line_cap(experimental::io2d::line_cap lc) noexcept;
					constexpr void line_join(experimental::io2d::line_join lj) noexcept;
					constexpr void miter_limit(float ml) noexcept;
					constexpr float line_width() const noexcept;
					constexpr experimental::io2d::line_cap line_cap() const noexcept;
					constexpr experimental::io2d::line_join line_join() const noexcept;
					constexpr float miter_limit() const noexcept;
					constexpr float max_miter_limit() const noexcept;
				};

				template <class GraphicsMath>
				class mask_props {
					experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::repeat;
					experimental::io2d::filter _Filter = experimental::io2d::filter::good;
					basic_matrix_2d<GraphicsMath> _Matrix = basic_matrix_2d<GraphicsMath>{};

				public:
					// surplus to paper
					constexpr mask_props(const mask_props&) noexcept = default;
					constexpr mask_props& operator=(const mask_props&) noexcept = default;
					mask_props(mask_props&&) noexcept = default;
					mask_props& operator=(mask_props&&) noexcept = default;

					constexpr mask_props(experimental::io2d::wrap_mode w = experimental::io2d::wrap_mode::repeat, experimental::io2d::filter fi = experimental::io2d::filter::good, const basic_matrix_2d<GraphicsMath>& m = basic_matrix_2d<GraphicsMath>{}) noexcept;
					constexpr void wrap_mode(experimental::io2d::wrap_mode w) noexcept;
					constexpr void filter(experimental::io2d::filter fi) noexcept;
					constexpr void mask_matrix(const basic_matrix_2d<GraphicsMath>& m) noexcept;
					constexpr experimental::io2d::wrap_mode wrap_mode() const noexcept;
					constexpr experimental::io2d::filter filter() const noexcept;
					constexpr basic_matrix_2d<GraphicsMath> mask_matrix() const noexcept;
				};

				template <class GraphicsMath, class T>
				class display_surface;

				struct display_point
				{
					constexpr display_point() noexcept;
					constexpr display_point(int x, int y) noexcept;

					int x;
					int y;
				};

				template <class T>
				class handler {
					T _Handler_impl;

				public:
					template <class GraphicsMath, class U>
					handler(display_surface<GraphicsMath, U>& ds, int preferredDisplayWidth, int preferredDisplayHeight, refresh_rate rr, float desiredFramerate);
					template <class GraphicsMath, class U>
					handler(display_surface<GraphicsMath, U>& ds, int preferredDisplayWidth, int preferredDisplayHeight, refresh_rate rr, float desiredFramerate, error_code& ec);
					int begin_show();
					void end_show();
					void display_dimensions(display_point dp);
					void display_dimensions(display_point dp, error_code& ec) noexcept;
					void refresh_rate(experimental::io2d::refresh_rate rr) noexcept;
					bool desired_frame_rate(float fps) noexcept;
					display_point display_dimensions() const noexcept;
					experimental::io2d::refresh_rate refresh_rate() const noexcept;
					float desired_frame_rate() const noexcept;
					float elapsed_draw_time() const noexcept;
				};

				class dashes {

				};
				//tuple<dashes, offset>
				//using dashes = ::std::tuple<::std::vector<float>, float>;

				class mapped_surface;

				class surface_base {
				public:
					using native_handle_type = typename T::renderer_surface_native_handles;

				protected:
					surface(::std::experimental::io2d::format fmt, int width, int height);
					surface(native_handle_type nh, ::std::experimental::io2d::format fmt);

					::std::unique_ptr<typename T::renderer_surface> _Surface_impl;

				public:
					const auto& native_handle() const { return _Surface_impl; }
					void clear();
					surface() = delete;

					void flush();
					void flush(error_code& ec) noexcept;
					void mark_dirty();
					void mark_dirty(error_code& ec) noexcept;
					template <class GraphicsMath>
					void mark_dirty(const typename basic_geometry<GraphicsMath>::bounding_box& extents);
					template <class GraphicsMath>
					void mark_dirty(const typename basic_geometry<GraphicsMath>::bounding_box& extents, error_code& ec) noexcept;
					template <class GraphicsMath, class T>
					void paint(const brush<T>& b, const optional<brush_props<GraphicsMath>>& bp = nullopt, const optional<render_props<GraphicsMath>>& rp = nullopt, const optional<clip_props<T>>& cl = nullopt);
					template <class Allocator>
					void stroke(const brush<GraphicsMath, T>& b, const path_builder<GraphicsMath, Allocator>& pb, const optional<brush_props<GraphicsMath>>& bp = nullopt, const optional<stroke_props>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<render_props<GraphicsMath>>& rp = nullopt, const optional<clip_props<T>>& cl = nullopt);
					void stroke(const brush<GraphicsMath, T>& b, const interpreted_path<T>& pg, const optional<brush_props<GraphicsMath>>& bp = nullopt, const optional<stroke_props>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<render_props<GraphicsMath>>& rp = nullopt, const optional<clip_props<T>>& cl = nullopt);
					template <class Allocator>
					void fill(const brush<GraphicsMath, T>& b, const path_builder<GraphicsMath, Allocator>& pb, const optional<brush_props<GraphicsMath>>& bp = nullopt, const optional<render_props<GraphicsMath>>& rp = nullopt, const optional<clip_props<T>>& cl = nullopt);
					void fill(const brush<GraphicsMath, T>& b, const interpreted_path<T>& pg, const optional<brush_props<GraphicsMath>>& bp = nullopt, const optional<render_props<GraphicsMath>>& rp = nullopt, const optional<clip_props<T>>& cl = nullopt);
					void mask(const brush<GraphicsMath, T>& b, const brush<GraphicsMath, T>& mb, const optional<brush_props<GraphicsMath>>& bp = nullopt, const optional<mask_props<GraphicsMath>>& mp = nullopt, const optional<render_props<GraphicsMath>>& rp = nullopt, const optional<clip_props<T>>& cl = nullopt);
				};

				class image_surface : public surface<GraphicsMath, T> {
					typename T::renderer_image_surface _Image_surface_impl;

				public:
					const auto& native_handle() const { return _Image_surface_impl; }
					image_surface(io2d::format fmt, int width, int height);
#ifdef _Filesystem_support_test
					image_surface(filesystem::path f, image_file_format i, io2d::format fmt);
					image_surface(filesystem::path f, image_file_format i, io2d::format fmt, error_code& ec) noexcept;
#else
					image_surface(::std::string f, experimental::io2d::format fmt, image_file_format idf);
					image_surface(::std::string f, image_file_format i, io2d::format fmt, error_code& ec) noexcept;
#endif
					image_surface(image_surface&&) = default;
					image_surface& operator=(image_surface&&) = default;
#ifdef _Filesystem_support_test
					void save(filesystem::path p, image_file_format i);
					void save(filesystem::path p, image_file_format i, error_code& ec) noexcept;
#else
					void save(::std::string f, image_file_format i);
					void save(::std::string f, image_file_format i, error_code& ec) noexcept;
#endif
					void map(const function<void(mapped_surface<GraphicsMath, T>&)>& action);
					void map(const function<void(mapped_surface<GraphicsMath, T>&, error_code&)>& action, error_code& ec);
					static int max_width() noexcept;
					static int max_height() noexcept;
					io2d::format format() const noexcept;
					int width() const noexcept;
					int height() const noexcept;
				};

				constexpr bool operator==(const display_point& lhs, const display_point& rhs) noexcept;
				constexpr bool operator!=(const display_point& lhs, const display_point& rhs) noexcept;

				class display_surface : public surface<GraphicsMath, T> {
					typename T::renderer_display_surface _Display_surface_impl;

				public:
					auto& native_handle() { return _Display_surface_impl; }
					display_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, io2d::scaling scl = io2d::scaling::letterbox);
					display_surface(int preferredWidth, int preferredHeight, io2d::format preferredFormat, error_code& ec, io2d::scaling scl = io2d::scaling::letterbox) noexcept;
					template <class U>
					void make_native_surface(U&&);						// Should only be invoked by the handler
					void make_impl_surface();							// Should only be invoked by the handler
					void draw_callback(const function<void(display_surface& sfc)>& fn);
					void invoke_draw_callback(display_point dp);		// Should only be invoked by the handler
					void size_change_callback(const function<void(display_surface& sfc)>& fn);
					void invoke_size_change_callback();					// Should only be invoked by the handler
					void dimensions(display_point dp);
					void dimensions(display_point dp, error_code& ec) noexcept;
					void scaling(experimental::io2d::scaling scl) noexcept;
					void user_scaling_callback(const function<experimental::io2d::bounding_box<GraphicsMath>(const display_surface&, bool&)>& fn);
					void letterbox_brush(const optional<brush<GraphicsMath, T>>& b, const optional<brush_props<GraphicsMath>> = nullopt) noexcept;
					void auto_clear(bool val) noexcept;
					void redraw_required() noexcept;
					bool reset_redraw_request() noexcept;				// Should only be invoked by the handler
					experimental::io2d::format format() const noexcept;
					display_point dimensions() const noexcept;
					experimental::io2d::scaling scaling() const noexcept;
					function<experimental::io2d::bounding_box<GraphicsMath>(const display_surface&, bool&)> user_scaling_callback() const;
					function<experimental::io2d::bounding_box<GraphicsMath>(const display_surface&, bool&)> user_scaling_callback(error_code& ec) const noexcept;
					optional<brush<GraphicsMath, T>> letterbox_brush() const noexcept;
					optional<brush_props<GraphicsMath>> letterbox_brush_props() const noexcept;
					bool auto_clear() const noexcept;
				};

				class mapped_surface {
					friend typename T::renderer_image_surface;
					typename T::renderer_mapped_surface _Mapped_surface_impl;

					mapped_surface(typename surface<GraphicsMath, T>::native_handle_type nh, typename surface<GraphicsMath, T>::native_handle_type map_of);
					mapped_surface(typename surface<GraphicsMath, T>::native_handle_type nh, typename surface<GraphicsMath, T>::native_handle_type map_of, ::std::error_code& ec) noexcept;

				public:
					const auto& native_handle() const { return _Mapped_surface_impl; }
					void commit_changes();
					void commit_changes(error_code& ec) noexcept;
					unsigned char* data();
					unsigned char* data(error_code& ec) noexcept;
					const unsigned char* data() const;
					const unsigned char* data(error_code& ec) const noexcept;
					experimental::io2d::format format() const noexcept;
					int width() const noexcept;
					int height() const noexcept;
					int stride() const noexcept;
				};
			}
		}
	}
}