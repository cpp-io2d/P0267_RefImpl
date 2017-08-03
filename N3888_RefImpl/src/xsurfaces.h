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
			bevel,
			miter_or_bevel
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
			constexpr render_props() noexcept {}
			constexpr explicit render_props(antialias a, const matrix_2d& m = matrix_2d{},
				compositing_op co = compositing_op::over) noexcept
				: _Antialiasing(a)
				, _Matrix(m)
				, _Compositing(co) {}

			constexpr void antialiasing(antialias a) noexcept {
				_Antialiasing = a;
			}
			constexpr void compositing(compositing_op co) noexcept {
				_Compositing = co;
			}
			constexpr void surface_matrix(const matrix_2d& m) noexcept {
				_Matrix = m;
			}

			constexpr antialias antialiasing() const noexcept {
				return _Antialiasing;
			}
			constexpr compositing_op compositing() const noexcept {
				return _Compositing;
			}
			constexpr matrix_2d surface_matrix() const noexcept {
				return _Matrix;
			}
		};

		class brush_props {
			experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::none;
			experimental::io2d::filter _Filter = experimental::io2d::filter::bilinear;
			experimental::io2d::fill_rule _Fill_rule = experimental::io2d::fill_rule::winding;
			matrix_2d _Matrix;

		public:
			constexpr brush_props() noexcept {}
			constexpr brush_props(experimental::io2d::wrap_mode w,
				experimental::io2d::filter fi = experimental::io2d::filter::bilinear,
				experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding,
				matrix_2d m = matrix_2d{}) noexcept
				: _Wrap_mode(w)
				, _Filter(fi)
				, _Fill_rule(fr)
				, _Matrix(m) {
			}

			constexpr void filter(experimental::io2d::filter fi) noexcept {
				_Filter = fi;
			}
			constexpr void wrap_mode(experimental::io2d::wrap_mode w) noexcept {
				_Wrap_mode = w;
			}
			constexpr void fill_rule(experimental::io2d::fill_rule fr) noexcept {
				_Fill_rule = fr;
			}
			constexpr void matrix(const matrix_2d& m) noexcept {
				_Matrix = m;
			}

			constexpr experimental::io2d::filter filter() const noexcept {
				return _Filter;
			}
			constexpr experimental::io2d::wrap_mode wrap_mode() const noexcept {
				return _Wrap_mode;
			}
			constexpr experimental::io2d::fill_rule fill_rule() const noexcept {
				return _Fill_rule;
			}
			constexpr matrix_2d matrix() const noexcept {
				return _Matrix;
			}
		};

		class clip_props {
			path_group _Clip;
			experimental::io2d::fill_rule _Fill_rule = experimental::io2d::fill_rule::winding;
		public:
			clip_props() noexcept = default;
			template <class Allocator>
			explicit clip_props(const path_builder<Allocator> &pf,
				experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding)
				: _Clip(path_group(pf))
				, _Fill_rule(fr) { }

			explicit clip_props(const path_group& pg,
				experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding) noexcept
				: _Clip(pg)
				, _Fill_rule(fr) { }

			explicit clip_props(const bounding_box& r,
				experimental::io2d::fill_rule fr = experimental::io2d::fill_rule::winding)
				: _Clip()
				, _Fill_rule(fr) {
				path_builder<> clip;
				clip.new_path(r.top_left());
				clip.rel_line({ r.width(), 0.0F });
				clip.rel_line({ 0.0F, r.height() });
				clip.rel_line({ -r.width(), 0.0F });
				clip.close_figure();
				_Clip = path_group(clip);
			}

			template <class Allocator>
			void clip(const path_builder<Allocator>& pf) {
				_Clip = path_group(pf);
			}

			void clip(const path_group& pg) noexcept {
				_Clip = pg;
			}

			void fill_rule(experimental::io2d::fill_rule fr) {
				_Fill_rule = fr;
			}

			path_group clip() const noexcept {
				return _Clip;
			}

			experimental::io2d::fill_rule fill_rule() const noexcept {
				return _Fill_rule;
			}
		};

		class stroke_props {
			float _Line_width = 2.0F;
			float _Miter_limit = 10.0F;
			experimental::io2d::line_cap _Line_cap = experimental::io2d::line_cap::none;
			experimental::io2d::line_join _Line_join = experimental::io2d::line_join::miter;
			//optional<dashes> _Dashes;
		public:
			constexpr stroke_props() noexcept {}
			constexpr explicit stroke_props(float w,
				experimental::io2d::line_cap lc = experimental::io2d::line_cap::none,
				experimental::io2d::line_join lj = experimental::io2d::line_join::miter,
				float ml = 10.0F) noexcept
				: _Line_width(w)
				, _Miter_limit(ml)
				, _Line_cap(lc)
				, _Line_join(lj) {}

			constexpr void line_width(float w) noexcept {
				_Line_width = w;
			}
			constexpr void line_cap(experimental::io2d::line_cap lc) noexcept {
				_Line_cap = lc;
			}
			constexpr void line_join(experimental::io2d::line_join lj) noexcept {
				_Line_join = lj;
			}
			constexpr void miter_limit(float ml) noexcept {
				_Miter_limit = ml;
			}

			constexpr float line_width() const noexcept {
				return _Line_width;
			}
			constexpr experimental::io2d::line_cap line_cap() const noexcept {
				return _Line_cap;
			}
			constexpr experimental::io2d::line_join line_join() const noexcept {
				return _Line_join;
			}
			constexpr float miter_limit() const noexcept {
				return _Miter_limit;
			}
		};

		class mask_props {
			experimental::io2d::wrap_mode _Wrap_mode = experimental::io2d::wrap_mode::repeat;
			experimental::io2d::filter _Filter = experimental::io2d::filter::good;
			matrix_2d _Matrix = matrix_2d{};

		public:
			constexpr mask_props(experimental::io2d::wrap_mode w = experimental::io2d::wrap_mode::repeat,
				experimental::io2d::filter fi = experimental::io2d::filter::good,
				matrix_2d m = matrix_2d{}) noexcept
				: _Wrap_mode(w)
				, _Filter(fi)
				, _Matrix(m) {
			}
			constexpr mask_props(const mask_props&) noexcept = default;
			constexpr mask_props& operator=(const mask_props&) noexcept = default;
			mask_props(mask_props&&) noexcept = default;
			mask_props& operator=(mask_props&&) noexcept = default;

			constexpr void wrap_mode(experimental::io2d::wrap_mode w) noexcept {
				_Wrap_mode = w;
			}
			constexpr void filter(experimental::io2d::filter fi) noexcept {
				_Filter = fi;
			}
			constexpr void matrix(const matrix_2d& m) noexcept {
				_Matrix = m;
			}

			constexpr experimental::io2d::wrap_mode wrap_mode() const noexcept {
				return _Wrap_mode;
			}
			constexpr experimental::io2d::filter filter() const noexcept {
				return _Filter;
			}
			constexpr matrix_2d matrix() const noexcept {
				return _Matrix;
			}
		};

	}
}