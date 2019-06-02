#pragma once
#include "xio2d.h"
#include "xsurfaces_enums.h"
#include "xsurfaces.h"
#include "xpath.h"
#include "xtext.h"
#include "xgraphicsmath.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		template <class GraphicsSurfaces>
		struct basic_commands {
			using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;

			class clear {
			public:
				using data_type = typename GraphicsSurfaces::surfaces::clear_data_type;
			private:
				data_type _Data;
			public:
				const data_type& data() const noexcept;
				data_type& data() noexcept;

				clear() noexcept;
				clear(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc) noexcept;

				void surface(const optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>& sfc) noexcept;
				// Note: these non-const, non-reference optional returns are intentional. They are potentially constructs from the backend that the backend is not obligated to keep around. The backend can store data however it wants and will coerce it to an optional if requested. The backend is required to keep a copy of non-optional objects, hence their different treatment (for now).
				optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> surface() const noexcept;
			};

			class flush {
			public:
				using data_type = typename GraphicsSurfaces::surfaces::flush_data_type;
			private:
				data_type _Data;
			public:
				const data_type& data() const noexcept;
				data_type& data() noexcept;

				void surface(const optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>& sfc) noexcept;
				optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> surface() const noexcept;

				flush() noexcept;
				flush(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc) noexcept;
			};

			class mark_dirty {
			public:
				using data_type = typename GraphicsSurfaces::surfaces::mark_dirty_data_type;
			private:
				data_type _Data;
			public:
				const data_type& data() const noexcept;
				data_type& data() noexcept;

				void surface(const optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>& sfc) noexcept;
				optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> surface() const noexcept;

				mark_dirty() noexcept;
				mark_dirty(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc) noexcept;
				mark_dirty(const basic_bounding_box<graphics_math_type>& ext) noexcept;
				mark_dirty(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_bounding_box<graphics_math_type>& ext) noexcept;

				void extents(const optional<basic_bounding_box<graphics_math_type>>& ext) noexcept;
				optional<basic_bounding_box<graphics_math_type>> extents() const noexcept;
			};

			class paint {
			public:
				using data_type = typename GraphicsSurfaces::surfaces::paint_data_type;
			private:
				data_type _Data;
			public:
				const data_type& data() const noexcept;
				data_type& data() noexcept;

				void surface(const optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>& sfc) noexcept;
				const optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> surface() const noexcept;

				paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
				paint(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;

				void brush(const basic_brush<GraphicsSurfaces>& b) noexcept;
				// Not returning optional since this must always exist.
				const basic_brush<GraphicsSurfaces>& brush() const noexcept;

				void brush_props(const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept;
				optional<basic_brush_props<GraphicsSurfaces>> brush_props() const noexcept;

				void render_props(const optional<basic_render_props<GraphicsSurfaces>>& rp) noexcept;
				optional<basic_render_props<GraphicsSurfaces>> render_props() const noexcept;

				void clip_props(const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept;
				optional<basic_clip_props<GraphicsSurfaces>> clip_props() const noexcept;
			};

			class stroke {
			public:
				using data_type = typename GraphicsSurfaces::surfaces::stroke_data_type;
			private:
				data_type _Data;
			public:
				const data_type& data() const noexcept;
				data_type& data() noexcept;

				void surface(const optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>& sfc) noexcept;
				optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> surface() const noexcept;

				stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
				stroke(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
				template <class InputIterator>
				stroke(const basic_brush<GraphicsSurfaces>& b, InputIterator first, InputIterator last, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
				template <class InputIterator>
				stroke(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, InputIterator first, InputIterator last, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;

				void brush(const basic_brush<GraphicsSurfaces>& b) noexcept;
				// Not returning optional since this must always exist.
				const basic_brush<GraphicsSurfaces>& brush() const noexcept;
				void path(const basic_interpreted_path<GraphicsSurfaces>& p) noexcept;
				template <class InputIterator>
				void path(InputIterator first, InputIterator last) noexcept;
				const basic_interpreted_path<GraphicsSurfaces>& path() const noexcept;
				void brush_props(const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept;
				optional<basic_brush_props<GraphicsSurfaces>> brush_props() const noexcept;
				void stroke_props(const basic_stroke_props<GraphicsSurfaces>& sp) noexcept;
				optional<basic_stroke_props<GraphicsSurfaces>> stroke_props() const noexcept;
				void dashes(const optional<basic_dashes<GraphicsSurfaces>>& d) noexcept;
				optional<basic_dashes<GraphicsSurfaces>> dashes() const noexcept;
				void render_props(const optional<basic_render_props<GraphicsSurfaces>>& rp) noexcept;
				optional<basic_render_props<GraphicsSurfaces>> render_props() const noexcept;
				void clip_props(const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept;
				optional<basic_clip_props<GraphicsSurfaces>> clip_props() const noexcept;
			};
			class fill {
			public:
				using data_type = typename GraphicsSurfaces::surfaces::fill_data_type;
			private:
				data_type _Data;
			public:
				const data_type& data() const noexcept;
				data_type& data() noexcept;

				void surface(optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept;
				optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> surface() const noexcept;

				fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
				fill(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
				template <class InputIterator>
				fill(const basic_brush<GraphicsSurfaces>& b, InputIterator first, InputIterator last, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
				template <class InputIterator>
				fill(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, InputIterator first, InputIterator last, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;

				void brush(const basic_brush<GraphicsSurfaces>& b) noexcept;
				// Not returning optional since this must always exist.
				const basic_brush<GraphicsSurfaces>& brush() const noexcept;
				void path(const basic_interpreted_path<GraphicsSurfaces>& p) noexcept;
				template <class InputIterator>
				void path(InputIterator first, InputIterator last) noexcept;
				const basic_interpreted_path<GraphicsSurfaces>& path() const noexcept;
				void brush_props(const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept;
				optional<basic_brush_props<GraphicsSurfaces>> brush_props() const noexcept;
				void render_props(const optional<basic_render_props<GraphicsSurfaces>>& rp) noexcept;
				optional<basic_render_props<GraphicsSurfaces>> render_props() const noexcept;
				void clip_props(const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept;
				optional<basic_clip_props<GraphicsSurfaces>> clip_props() const noexcept;
			};
			class mask {
			public:
				using data_type = typename GraphicsSurfaces::surfaces::mask_data_type;
			private:
				data_type _Data;
			public:
				const data_type& data() const noexcept;
				data_type& data() noexcept;

				void surface(optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept;
				optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> surface() const noexcept;

				mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_mask_props<GraphicsSurfaces>>& mp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
				mask(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_mask_props<GraphicsSurfaces>>& mp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;

				void brush(basic_brush<GraphicsSurfaces>& b) noexcept;
				const basic_brush<GraphicsSurfaces>& brush() const noexcept;

				void mask_brush(basic_brush<GraphicsSurfaces>& mb) noexcept;
				const basic_brush<GraphicsSurfaces>& mask_brush() const noexcept;

				void brush_props(const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept;
				optional<basic_brush_props<GraphicsSurfaces>> brush_props() const noexcept;

				void mask_props(optional<basic_mask_props<GraphicsSurfaces>> mp) noexcept;
				optional<basic_mask_props<GraphicsSurfaces>> mask_props() const noexcept;

				void render_props(const optional<basic_render_props<GraphicsSurfaces>>& rp) noexcept;
				optional<basic_render_props<GraphicsSurfaces>> render_props() const noexcept;

				void clip_props(const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept;
				optional<basic_clip_props<GraphicsSurfaces>> clip_props() const noexcept;
			};

			// void draw_text(const basic_point_2d<graphics_math_type>& pt, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const optional<basic_text_props<GraphicsSurfaces>>& tp = nullopt, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			// void draw_text(const basic_bounding_box<graphics_math_type>& bb, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const optional<basic_text_props<GraphicsSurfaces>>& tp = nullopt, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt);
			class draw_text {
			public:
				using data_type = typename GraphicsSurfaces::surfaces::draw_text_data_type;
			private:
				data_type _Data;
			public:
				const data_type& data() const noexcept;
				data_type& data() noexcept;

				void surface(optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept;
				optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> surface() const noexcept;

				draw_text(const basic_point_2d<graphics_math_type>& pt, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const optional<basic_text_props<GraphicsSurfaces>>& tp = nullopt, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
				draw_text(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_point_2d<graphics_math_type>& pt, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const optional<basic_text_props<GraphicsSurfaces>>& tp = nullopt, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
				draw_text(const basic_bounding_box<graphics_math_type>& bb, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const optional<basic_text_props<GraphicsSurfaces>>& tp = nullopt, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
				draw_text(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_bounding_box<graphics_math_type>& bb, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const optional<basic_text_props<GraphicsSurfaces>>& tp = nullopt, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;

				void location(const basic_point_2d<graphics_math_type>& pt) noexcept;
				void location(const basic_bounding_box<graphics_math_type>& bb) noexcept;
				variant<basic_point_2d<graphics_math_type>, basic_bounding_box<graphics_math_type>> location() const noexcept;
				void brush(const basic_brush<GraphicsSurfaces>& b) noexcept;
				const basic_brush<GraphicsSurfaces>& brush() const noexcept;
				void font(const basic_font<GraphicsSurfaces>& f) noexcept;
				const basic_font<GraphicsSurfaces>& font() const noexcept;
				void text(const string& t) noexcept;
				const string& text() const noexcept;
				void text_props(const optional<basic_text_props<GraphicsSurfaces>>& tp) noexcept;
				optional<basic_text_props<GraphicsSurfaces>> text_props() const noexcept;
				void stroke_props(const optional<basic_stroke_props<GraphicsSurfaces>>& sp) noexcept;
				optional<basic_stroke_props<GraphicsSurfaces>> stroke_props() const noexcept;
				void dashes(const optional<basic_dashes<GraphicsSurfaces>>& d) noexcept;
				optional<basic_dashes<GraphicsSurfaces>> dashes() const noexcept;
				void brush_props(const optional<basic_brush_props<GraphicsSurfaces>>& bp) noexcept;
				optional<basic_brush_props<GraphicsSurfaces>> brush_props() const noexcept;
				void render_props(const optional<basic_render_props<GraphicsSurfaces>>& rp) noexcept;
				optional<basic_render_props<GraphicsSurfaces>> render_props() const noexcept;
				void clip_props(const optional<basic_clip_props<GraphicsSurfaces>>& cl) noexcept;
				optional<basic_clip_props<GraphicsSurfaces>> clip_props() const noexcept;
			};

			// Allows the user to run additional functions such as when the user knows the backend and wishes to modify it in ways not otherwise supported by a different command.
			class run_function {
			public:
				using data_type = typename GraphicsSurfaces::surfaces::run_function_data_type;
			private:
				data_type _Data;
			public:
				const data_type& data() const noexcept;
				data_type& data() noexcept;

				run_function(const function<void(basic_image_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>& fn, void* user_data, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept;
				run_function(const function<void(basic_output_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>& fn, void* user_data, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept;
				run_function(const function<void(basic_unmanaged_output_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>& fn, void* user_data, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> sfc) noexcept;
				run_function(const run_function& other) = default;
				run_function& operator=(const run_function& other) = default;
				run_function(run_function&& other) noexcept = default;
				run_function& operator=(run_function&& other) noexcept = default;

				void surface(const optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>& sfc) noexcept;
				optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>> surface() const noexcept;

				void func(const function<void(basic_image_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>& fn) noexcept;
				void func(const function<void(basic_output_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>& fn) noexcept;
				void func(const function<void(basic_unmanaged_output_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>& fn) noexcept;
				const variant<function<void(basic_image_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>, function<void(basic_output_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>, function<void(basic_unmanaged_output_surface<GraphicsSurfaces>&, optional<reference_wrapper<basic_image_surface<GraphicsSurfaces>>>, void*)>>& func() const noexcept;

				void user_data(void* ud) noexcept;
				void* user_data() const noexcept;
			};

			using command_item = variant<clear, flush, mark_dirty, paint, stroke, fill, mask, draw_text, run_function>;
		};

		template <class GraphicsSurfaces, class Allocator = ::std::allocator<typename basic_commands<GraphicsSurfaces>::command_item>>
		class basic_command_list_builder {
		public:
			using data_type = ::std::vector<typename basic_commands<GraphicsSurfaces>::command_item, Allocator>;
			using graphics_math_type = typename GraphicsSurfaces::graphics_math_type;
		private:
			data_type _Data;
		public:
			const data_type& data() const noexcept;
			data_type& data() noexcept;
			using value_type = typename basic_commands<GraphicsSurfaces>::command_item;
			using allocator_type = Allocator;
			using reference = value_type &;
			using const_reference = const value_type &;
			using size_type = typename ::std::vector<value_type>::size_type;
			using difference_type = typename ::std::vector<value_type>::difference_type;
			using iterator = typename ::std::vector<value_type>::iterator;
			using const_iterator = typename ::std::vector<value_type>::const_iterator;
			using reverse_iterator = std::reverse_iterator<iterator>;
			using const_reverse_iterator = std::reverse_iterator<const_iterator>;

			// using command_item = variant<clear, flush, mark_dirty, paint, stroke, fill, mask, draw_text>;

			void clear_cmd(const typename basic_commands<GraphicsSurfaces>::clear& c);
			void flush(const typename basic_commands<GraphicsSurfaces>::flush& f);
			void mark_dirty(const typename basic_commands<GraphicsSurfaces>::mark_dirty& md);
			void paint(const typename basic_commands<GraphicsSurfaces>::paint& p);
			void stroke(const typename basic_commands<GraphicsSurfaces>::stroke& s);
			void fill(const typename basic_commands<GraphicsSurfaces>::fill& f);
			void mask(const typename basic_commands<GraphicsSurfaces>::mask& m);
			void draw_text(const typename basic_commands<GraphicsSurfaces>::draw_text& dt);

			void clear_cmd() noexcept;
			void clear_cmd(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc) noexcept;
			void flush() noexcept;
			void flush(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc) noexcept;
			void mark_dirty() noexcept;
			void mark_dirty(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc) noexcept;
			void mark_dirty(const basic_bounding_box<graphics_math_type>& ext) noexcept;
			void mark_dirty(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_bounding_box<graphics_math_type>& ext) noexcept;
			void paint(const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void paint(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void stroke(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void stroke(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void stroke(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void stroke(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			template <class InputIterator>
			void stroke(const basic_brush<GraphicsSurfaces>& b, InputIterator first, InputIterator last, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			template <class InputIterator>
			void stroke(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, InputIterator first, InputIterator last, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void fill(const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void fill(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, const basic_interpreted_path<GraphicsSurfaces>& ip, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void fill(const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void fill(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, const basic_path_builder<GraphicsSurfaces>& pb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			template <class InputIterator>
			void fill(const basic_brush<GraphicsSurfaces>& b, InputIterator first, InputIterator last, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			template <class InputIterator>
			void fill(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, InputIterator first, InputIterator last, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void mask(const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_mask_props<GraphicsSurfaces>>& mp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void mask(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_brush<GraphicsSurfaces>& b, const basic_brush<GraphicsSurfaces>& mb, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_mask_props<GraphicsSurfaces>>& mp = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void draw_text(const basic_point_2d<graphics_math_type>& pt, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const optional<basic_text_props<GraphicsSurfaces>>& tp = nullopt, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void draw_text(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_point_2d<graphics_math_type>& pt, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const optional<basic_text_props<GraphicsSurfaces>>& tp = nullopt, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void draw_text(const basic_bounding_box<graphics_math_type>& bb, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const optional<basic_text_props<GraphicsSurfaces>>& tp = nullopt, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;
			void draw_text(reference_wrapper<basic_image_surface<GraphicsSurfaces>> sfc, const basic_bounding_box<graphics_math_type>& pt, const basic_brush<GraphicsSurfaces>& b, const basic_font<GraphicsSurfaces>& font, const string& text, const optional<basic_text_props<GraphicsSurfaces>>& tp = nullopt, const optional<basic_brush_props<GraphicsSurfaces>>& bp = nullopt, const optional<basic_stroke_props<GraphicsSurfaces>>& sp = nullopt, const optional<basic_dashes<GraphicsSurfaces>>& d = nullopt, const optional<basic_render_props<GraphicsSurfaces>>& rp = nullopt, const optional<basic_clip_props<GraphicsSurfaces>>& cl = nullopt) noexcept;

			basic_command_list_builder() noexcept(noexcept(Allocator()));
			explicit basic_command_list_builder(const Allocator& a) noexcept;
			explicit basic_command_list_builder(size_type n, const Allocator& a = Allocator());
			basic_command_list_builder(size_type n, const value_type& value,
				const Allocator& a = Allocator());
			template <class InputIterator>
			basic_command_list_builder(InputIterator first, InputIterator last,
				const Allocator& a = Allocator());
			basic_command_list_builder(const basic_command_list_builder& x);
			basic_command_list_builder(basic_command_list_builder&&) noexcept;
			basic_command_list_builder(const basic_command_list_builder&, const Allocator&);
			basic_command_list_builder(basic_command_list_builder&&, const Allocator&);
			basic_command_list_builder(initializer_list<value_type>, const Allocator & = Allocator());
			~basic_command_list_builder();
			basic_command_list_builder& operator=(const basic_command_list_builder& x);
			basic_command_list_builder& operator=(basic_command_list_builder&& x)
				noexcept(
					allocator_traits<Allocator>::propagate_on_container_move_assignment::value
					||
					allocator_traits<Allocator>::is_always_equal::value);
			basic_command_list_builder& operator=(initializer_list<value_type>);
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last);
			void assign(size_type n, const value_type& u);
			void assign(initializer_list<value_type>);
			allocator_type get_allocator() const noexcept;
			// 10.5.6, iterators:
			iterator begin() noexcept;
			const_iterator begin() const noexcept;
			const_iterator cbegin() const noexcept;
			iterator end() noexcept;
			const_iterator end() const noexcept;
			const_iterator cend() const noexcept;
			reverse_iterator rbegin() noexcept;
			const_reverse_iterator rbegin() const noexcept;
			const_reverse_iterator crbegin() const noexcept;
			reverse_iterator rend() noexcept;
			const_reverse_iterator rend() const noexcept;
			const_reverse_iterator crend() const noexcept;
			// 10.5.4, capacity
			bool empty() const noexcept;
			size_type size() const noexcept;
			size_type max_size() const noexcept;
			size_type capacity() const noexcept;
			void resize(size_type sz);
			void resize(size_type sz, const value_type& c);
			void reserve(size_type n);
			void shrink_to_fit();
			// element access:
			reference operator[](size_type n);
			const_reference operator[](size_type n) const;
			const_reference at(size_type n) const;
			reference at(size_type n);
			reference front();
			const_reference front() const;
			reference back();
			const_reference back() const;

			// 10.5.5, modifiers:
			template <class... Args>
			reference emplace_back(Args&& ... args);
			void push_back(const value_type& x);
			void push_back(value_type&& x);
			void pop_back();
			template <class... Args>
			iterator emplace(const_iterator position, Args&& ... args);
			iterator insert(const_iterator position, const value_type& x);
			iterator insert(const_iterator position, value_type&& x);
			iterator insert(const_iterator position, size_type n, const value_type& x);
			template <class InputIterator>
			iterator insert(const_iterator position, InputIterator first, InputIterator last);
			iterator insert(const_iterator position,
				initializer_list<value_type> il);
			iterator erase(const_iterator position);
			iterator erase(const_iterator first, const_iterator last);
			void swap(basic_command_list_builder&)
				noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value
					|| allocator_traits<Allocator>::is_always_equal::value);
			void clear() noexcept;
		};

		template <class GraphicsSurfaces, class Allocator>
		bool operator==(const basic_command_list_builder<GraphicsSurfaces, Allocator>& lhs, const basic_command_list_builder<GraphicsSurfaces, Allocator>& rhs) noexcept;
		template <class GraphicsSurfaces, class Allocator>
		bool operator!=(const basic_command_list_builder<GraphicsSurfaces, Allocator>& lhs, const basic_command_list_builder<GraphicsSurfaces, Allocator>& rhs) noexcept;
		template <class GraphicsSurfaces, class Allocator>
		void swap(basic_command_list_builder<GraphicsSurfaces, Allocator>& lhs, basic_command_list_builder<GraphicsSurfaces, Allocator>& rhs) noexcept(noexcept(lhs.swap(rhs)));
	}
}