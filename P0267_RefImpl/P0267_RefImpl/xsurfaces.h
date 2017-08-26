#pragma once

namespace std::experimental::io2d {
	inline namespace v1 {

		enum class antialias {
			none,
			fast,
			good,
			best
		};

		enum class fill_rule {
			winding,
			even_odd
		};

		enum class line_cap {
			none,
			round,
			square
		};

		enum class line_join {
			miter,
			round,
			bevel
		};

		enum class compositing_op {
			over,
			clear,
			source,
			in,
			out,
			atop,
			dest,
			dest_over,
			dest_in,
			dest_out,
			dest_atop,
			xor_op,
			add,
			saturate,
			multiply,
			screen,
			overlay,
			darken,
			lighten,
			color_dodge,
			color_burn,
			hard_light,
			soft_light,
			difference,
			exclusion,
			hsl_hue,
			hsl_saturation,
			hsl_color,
			hsl_luminosity
		};

		enum class format {
			invalid,
			argb32,
			rgb24,
			a8,
			rgb16_565,
			rgb30
		};

		enum class scaling {
			letterbox,      // Same as uniform except that the display_surface is cleared using the letterbox brush first
			uniform,        // Maintain aspect ratio and center as needed, ignoring side areas that are not drawn to
			fill_uniform,   // Maintain aspect ratio but fill entire display (some content may not be shown)
			fill_exact,     // Ignore aspect ratio and use (possibly non-uniform) scale to fill exactly
			none            // Do not scale.
		};

		enum class refresh_rate {
			as_needed,
			as_fast_as_possible,
			fixed
		};

		enum class image_file_format {
			unknown,
			png,
			jpeg,
			tiff
		};

		class render_props {
			antialias _Antialiasing = antialias::good;
			matrix_2d _Matrix;// = matrix_2d::init_identity(); // Transformation matrix
			compositing_op _Compositing = compositing_op::over;
		public:
			constexpr render_props() noexcept;
			constexpr explicit render_props(antialias a, const matrix_2d& m = matrix_2d{}, compositing_op co = compositing_op::over) noexcept;
			constexpr void antialiasing(antialias a) noexcept;
			constexpr void compositing(compositing_op co) noexcept;
			constexpr void surface_matrix(const matrix_2d& m) noexcept;
			constexpr antialias antialiasing() const noexcept;
			constexpr compositing_op compositing() const noexcept;
			constexpr matrix_2d surface_matrix() const noexcept;
		};

		class brush_props {
			experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::none;
			experimental::io2d::filter _Filter = experimental::io2d::filter::good;
			experimental::io2d::fill_rule _Fill_rule = experimental::io2d::fill_rule::winding;
			matrix_2d _Matrix;

		public:
			constexpr brush_props(io2d::wrap_mode w = io2d::wrap_mode::none, io2d::filter fi = io2d::filter::good, io2d::fill_rule fr = io2d::fill_rule::winding, matrix_2d m = matrix_2d{}) noexcept;
			constexpr void filter(io2d::filter fi) noexcept;
			constexpr void wrap_mode(io2d::wrap_mode w) noexcept;
			constexpr void fill_rule(io2d::fill_rule fr) noexcept;
			constexpr void brush_matrix(const matrix_2d& m) noexcept;
			constexpr io2d::filter filter() const noexcept;
			constexpr io2d::wrap_mode wrap_mode() const noexcept;
			constexpr io2d::fill_rule fill_rule() const noexcept;
			constexpr matrix_2d brush_matrix() const noexcept;
		};

		template <class T>
		class clip_props {
			interpreted_path<T> _Clip;
			experimental::io2d::fill_rule _Fill_rule = experimental::io2d::fill_rule::winding;
		public:
			// surplus to paper
			explicit clip_props(const bounding_box& r, experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding);

			clip_props() noexcept = default;
			template <class Allocator>
			explicit clip_props(const path_builder<Allocator>& pb, experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding);
			explicit clip_props(const interpreted_path<T>& pg, experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding) noexcept;
			template <class Allocator>
			void clip(const path_builder<Allocator>& pb);
			void clip(const interpreted_path<T>& pg) noexcept;
			void fill_rule(experimental::io2d::fill_rule fr) noexcept;
			interpreted_path<T> clip() const noexcept;
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

		class mask_props {
			experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::repeat;
			experimental::io2d::filter _Filter = experimental::io2d::filter::good;
			matrix_2d _Matrix = matrix_2d{};

		public:
			// surplus to paper
			constexpr mask_props(const mask_props&) noexcept = default;
			constexpr mask_props& operator=(const mask_props&) noexcept = default;
			mask_props(mask_props&&) noexcept = default;
			mask_props& operator=(mask_props&&) noexcept = default;

			constexpr mask_props(experimental::io2d::wrap_mode w = experimental::io2d::wrap_mode::repeat, experimental::io2d::filter fi = experimental::io2d::filter::good, matrix_2d m = matrix_2d{}) noexcept;
			constexpr void wrap_mode(experimental::io2d::wrap_mode w) noexcept;
			constexpr void filter(experimental::io2d::filter fi) noexcept;
			constexpr void mask_matrix(const matrix_2d& m) noexcept;
			constexpr experimental::io2d::wrap_mode wrap_mode() const noexcept;
			constexpr experimental::io2d::filter filter() const noexcept;
			constexpr matrix_2d mask_matrix() const noexcept;
		};

		template <class T>
		class display_surface;

		struct display_point
		{
			constexpr display_point() noexcept;
			constexpr display_point(int x, int y) noexcept;

			int x;
			int y;
		};

		template <class T>
		class handler
		{
			typename T _Handler_impl;

		public:
			template <class U>
			handler(display_surface<U>& ds, int preferredDisplayWidth, int preferredDisplayHeight, refresh_rate rr, float desiredFramerate);
			template <class U>
			handler(display_surface<U>& ds, int preferredDisplayWidth, int preferredDisplayHeight, refresh_rate rr, float desiredFramerate, error_code& ec);
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

		//tuple<dashes, offset>
		using dashes = ::std::tuple<::std::vector<float>, float>;

		template <class T>
		class mapped_surface;

		template <class T>
		class surface {
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
			void mark_dirty(const bounding_box& extents);
			void mark_dirty(const bounding_box& extents, error_code& ec) noexcept;
			void paint(const brush<T>& b, const optional<brush_props>& bp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props<T>>& cl = nullopt);
			template <class Allocator>
			void stroke(const brush<T>& b, const path_builder<Allocator>& pb, const optional<brush_props>& bp = nullopt, const optional<stroke_props>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props<T>>& cl = nullopt);
			void stroke(const brush<T>& b, const interpreted_path<T>& pg, const optional<brush_props>& bp = nullopt, const optional<stroke_props>& sp = nullopt, const optional<dashes>& d = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props<T>>& cl = nullopt);
			template <class Allocator>
			void fill(const brush<T>& b, const path_builder<Allocator>& pb, const optional<brush_props>& bp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props<T>>& cl = nullopt);
			void fill(const brush<T>& b, const interpreted_path<T>& pg, const optional<brush_props>& bp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props<T>>& cl = nullopt);
			void mask(const brush<T>& b, const brush<T>& mb, const optional<brush_props>& bp = nullopt, const optional<mask_props>& mp = nullopt, const optional<render_props>& rp = nullopt, const optional<clip_props<T>>& cl = nullopt);
		};

		template <class T>
		class image_surface : public surface<T> {
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
			void map(const function<void(mapped_surface<T>&)>& action);
			void map(const function<void(mapped_surface<T>&, error_code&)>& action, error_code& ec);
			static int max_width() noexcept;
			static int max_height() noexcept;
			io2d::format format() const noexcept;
			int width() const noexcept;
			int height() const noexcept;
		};

		constexpr bool operator==(const display_point& lhs, const display_point& rhs) noexcept;
		constexpr bool operator!=(const display_point& lhs, const display_point& rhs) noexcept;

		template <class T>
		class display_surface : public surface<T> {
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
			void user_scaling_callback(const function<experimental::io2d::bounding_box(const display_surface&, bool&)>& fn);
			void letterbox_brush(const optional<brush<T>>& b, const optional<brush_props> = nullopt) noexcept;
			void auto_clear(bool val) noexcept;
			void redraw_required() noexcept;
			bool reset_redraw_request() noexcept;				// Should only be invoked by the handler
			experimental::io2d::format format() const noexcept;
			display_point dimensions() const noexcept;
			experimental::io2d::scaling scaling() const noexcept;
			function<experimental::io2d::bounding_box(const display_surface&, bool&)> user_scaling_callback() const;
			function<experimental::io2d::bounding_box(const display_surface&, bool&)> user_scaling_callback(error_code& ec) const noexcept;
			optional<brush<T>> letterbox_brush() const noexcept;
			optional<brush_props> letterbox_brush_props() const noexcept;
			bool auto_clear() const noexcept;
		};

		template <class T>
		class mapped_surface {
			friend typename T::renderer_image_surface;
			typename T::renderer_mapped_surface _Mapped_surface_impl;

			mapped_surface(typename surface<T>::native_handle_type nh, typename surface<T>::native_handle_type map_of);
			mapped_surface(typename surface<T>::native_handle_type nh, typename surface<T>::native_handle_type map_of, ::std::error_code& ec) noexcept;

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