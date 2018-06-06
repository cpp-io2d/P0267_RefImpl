//#include "io2d.h"
#include "xcairo.h"
#include "xio2d_cairo_sdl2_main.h"
#include "xgraphicsmathfloat.h"
#include <mutex>

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Cairo {

		using boo = _Cairo_graphics_surfaces<std::experimental::io2d::v1::_Graphics_math_float_impl>;
		using biff = _Cairo_graphics_surfaces<std::experimental::io2d::v1::_Graphics_math_float_impl>::surfaces::output_surface_data_type;
		using bam = basic_output_surface<boo>;

		template <> template <>
		void _Cairo_graphics_surfaces <_Graphics_math_float_impl>::surfaces::_Render_to_native_surface <
			_Cairo::_Cairo_graphics_surfaces <_Graphics_math_float_impl>::surfaces::_Output_surface_data*,
			basic_output_surface <_Cairo::_Cairo_graphics_surfaces <_Graphics_math_float_impl>>
		>
		(
			_Cairo::_Cairo_graphics_surfaces <_Graphics_math_float_impl>::surfaces::_Output_surface_data * & osdp,
			basic_output_surface <_Cairo::_Cairo_graphics_surfaces <_Graphics_math_float_impl>> & sfc
		)
		{
			auto& osd = *osdp;
			const cairo_filter_t cairoFilter = CAIRO_FILTER_GOOD;
			auto& data = osd.data;
			double displayWidth = static_cast<double>(data.display_dimensions.x());
			double displayHeight = static_cast<double>(data.display_dimensions.y());
			double backBufferWidth = static_cast<double>(data.back_buffer.dimensions.x());
			double backBufferHeight = static_cast<double>(data.back_buffer.dimensions.y());
			auto backBufferSfc = data.back_buffer.surface.get();
			auto displaySfc = data.display_surface.get();
			auto displayContext = data.display_context.get();
			cairo_surface_flush(backBufferSfc);
			cairo_set_operator(displayContext, CAIRO_OPERATOR_SOURCE);
			if (osd.user_scaling_callback != nullptr) {
				bool letterbox = false;
				auto userRect = osd.user_scaling_callback(sfc, letterbox);
				if (letterbox) {
					if (data._Letterbox_brush == nullopt) {
						cairo_set_source_rgb(displayContext, 0.0, 0.0, 0.0);
						cairo_paint(displayContext);
					}
					else {
						auto pttn = data._Letterbox_brush.value().data().brush.get();
						if (data._Letterbox_brush_props == nullopt) {
							cairo_pattern_set_extend(pttn, CAIRO_EXTEND_NONE);
							cairo_pattern_set_filter(pttn, CAIRO_FILTER_GOOD);
							cairo_matrix_t cPttnMatrix;
							cairo_matrix_init_identity(&cPttnMatrix);
							cairo_pattern_set_matrix(pttn, &cPttnMatrix);
							cairo_set_source(displayContext, pttn);
							cairo_paint(displayContext);
						}
						else {
							const basic_brush_props<_Cairo_graphics_surfaces<std::experimental::io2d::v1::_Graphics_math_float_impl>>& props = data._Letterbox_brush_props.value();
							cairo_pattern_set_extend(pttn, _Extend_to_cairo_extend_t(props.wrap_mode()));
							cairo_pattern_set_filter(pttn, _Filter_to_cairo_filter_t(props.filter()));
							cairo_matrix_t cPttnMatrix;
							const auto& m = props.brush_matrix();
							cairo_matrix_init(&cPttnMatrix, m.m00(), m.m01(), m.m10(), m.m11(), m.m20(), m.m21());
							cairo_pattern_set_matrix(pttn, &cPttnMatrix);
							cairo_set_source(displayContext, pttn);
							cairo_paint(displayContext);
						}
					}
				}
				cairo_matrix_t ctm;
				cairo_matrix_init_scale(&ctm, 1.0 / displayWidth / static_cast<double>(userRect.width()), 1.0 / displayHeight / static_cast<double>(userRect.height()));
				cairo_matrix_translate(&ctm, -static_cast<double>(userRect.x()), -static_cast<double>(userRect.y()));
				unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(backBufferSfc), &cairo_pattern_destroy);
				auto patPtr = pat.get();
				cairo_pattern_set_matrix(patPtr, &ctm);
				cairo_pattern_set_extend(patPtr, CAIRO_EXTEND_NONE);
				cairo_pattern_set_filter(patPtr, cairoFilter);
				cairo_set_source(displayContext, patPtr);
				cairo_paint(displayContext);
			}
			else {
				
				// Calculate the destRect values.
				switch (data.scl) {
					case std::experimental::io2d::scaling::letterbox:
					{
						_Render_for_scaling_uniform_or_letterbox(osd);
					} break;
					case std::experimental::io2d::scaling::uniform:
					{
						_Render_for_scaling_uniform_or_letterbox(osd);
					} break;
					
					case std::experimental::io2d::scaling::fill_uniform:
					{
						// Maintain aspect ratio and center, but overflow if needed rather than letterboxing.
						if (backBufferWidth == displayWidth && backBufferHeight == displayHeight) {
							cairo_set_source_surface(displayContext, backBufferSfc, 0.0, 0.0);
							cairo_paint(displayContext);
						}
						else {
							auto widthRatio = displayWidth / backBufferWidth;
							auto heightRatio = displayHeight / backBufferHeight;
							if (widthRatio < heightRatio) {
								cairo_set_source_rgb(displayContext, 0.0, 0.0, 0.0);
								cairo_paint(displayContext);
								cairo_matrix_t ctm;
								cairo_matrix_init_scale(&ctm, 1.0 / heightRatio, 1.0 / heightRatio);
								cairo_matrix_translate(&ctm, trunc(abs((displayWidth - (backBufferWidth * heightRatio)) / 2.0)), 0.0);
								unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(backBufferSfc), &cairo_pattern_destroy);
								auto patPtr = pat.get();
								cairo_pattern_set_matrix(patPtr, &ctm);
								cairo_pattern_set_extend(patPtr, CAIRO_EXTEND_NONE);
								cairo_pattern_set_filter(patPtr, cairoFilter);
								cairo_set_source(displayContext, patPtr);
								cairo_paint(displayContext);
							}
							else {
								cairo_set_source_rgb(displayContext, 0.0, 0.0, 0.0);
								cairo_paint(displayContext);
								cairo_matrix_t ctm;
								cairo_matrix_init_scale(&ctm, 1.0 / widthRatio, 1.0 / widthRatio);
								cairo_matrix_translate(&ctm, 0.0, trunc(abs((displayHeight - (backBufferHeight * widthRatio)) / 2.0)));
								unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(backBufferSfc), &cairo_pattern_destroy);
								auto patPtr = pat.get();
								cairo_pattern_set_matrix(patPtr, &ctm);
								cairo_pattern_set_extend(patPtr, CAIRO_EXTEND_NONE);
								cairo_pattern_set_filter(patPtr, cairoFilter);
								cairo_set_source(displayContext, patPtr);
								cairo_paint(displayContext);
							}
						}
					} break;
					case std::experimental::io2d::scaling::fill_exact:
					{
						// Maintain aspect ratio and center, but overflow if needed rather than letterboxing.
						if (backBufferWidth == displayWidth && backBufferHeight == displayHeight) {
							cairo_set_source_surface(displayContext, backBufferSfc, 0.0, 0.0);
							cairo_paint(displayContext);
						}
						else {
							auto widthRatio = displayWidth / backBufferWidth;
							auto heightRatio = displayHeight / backBufferHeight;
							cairo_matrix_t ctm;
							cairo_matrix_init_scale(&ctm, 1.0 / widthRatio, 1.0 / heightRatio);
							unique_ptr<cairo_pattern_t, decltype(&cairo_pattern_destroy)> pat(cairo_pattern_create_for_surface(backBufferSfc), &cairo_pattern_destroy);
							auto patPtr = pat.get();
							cairo_pattern_set_matrix(patPtr, &ctm);
							cairo_pattern_set_extend(patPtr, CAIRO_EXTEND_NONE);
							cairo_pattern_set_filter(patPtr, cairoFilter);
							cairo_set_source(displayContext, patPtr);
							cairo_paint(displayContext);
						}
					} break;
					case std::experimental::io2d::scaling::none:
					{
						cairo_set_source_surface(displayContext, backBufferSfc, 0.0, 0.0);
						cairo_paint(displayContext);
					} break;
					default:
					{
						assert("Unexpected _Scaling value." && false);
					} break;
				}
			}
			
			//     cairo_restore(_Native_context.get());
			// This call to cairo_surface_flush is needed for Win32 surfaces to update.
			cairo_surface_flush(displaySfc);
			cairo_set_source_rgb(displayContext, 0.0, 0.0, 0.0);

			SDL_SetRenderDrawColor(data.renderer, 0, 0, 0, 255);
			SDL_RenderClear(data.renderer);

			// Copy Cairo canvas to SDL2 texture
			unsigned char * src = cairo_image_surface_get_data(displaySfc);
			// std::vector<uint32_t> srcV;
			// srcV.resize((int)backBufferWidth * (int)backBufferHeight, 0xff00ff00);
			// unsigned char * src = (unsigned char *) &srcV[0];

			const int pitch = (int)backBufferWidth * 4;    // '4' == 4 bytes per pixel
			SDL_UpdateTexture(data.texture, nullptr, src, pitch);
			SDL_RenderCopy(data.renderer, data.texture, nullptr, nullptr);

			// Present latest image
			SDL_RenderPresent(data.renderer);
		}

		template <>
		bool _Is_active<std::experimental::io2d::v1::_Graphics_math_float_impl>(_Cairo_graphics_surfaces<std::experimental::io2d::v1::_Graphics_math_float_impl>::surfaces::_Display_surface_data_type& data) noexcept
		{
			if (SDL_QuitRequested()) {
				return false;
			}
			if (data.window == nullptr || data.renderer == nullptr) {
				return false;
			}
			return true;
		}

		template <>
		int _Cairo_graphics_surfaces<std::experimental::io2d::v1::_Graphics_math_float_impl>::surfaces::begin_show(biff& osd, bam* instance, bam& sfc)
		{
			_Display_surface_data_type &data = osd->data;

			//
			// Let SDL create:
			//  1. a window
			//  2. an SDL renderer, which will be used to help draw Cairo-rendered content to the desired display(s)
			//

#if __LINUX__
				SDL_SetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION, "0");
#endif

				if (SDL_Init(SDL_INIT_VIDEO) != 0) {
					throw system_error(make_error_code(std::errc::io_error), "Failed call to SDL_Init.");
				}

				data.window = SDL_CreateWindow(
					"",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					data.display_dimensions.x(),
					data.display_dimensions.y(),
					SDL_WINDOW_SHOWN
				);
				// printf("data.window: %p\n", data.window);
				if (!data.window) {
					throw system_error(make_error_code(std::errc::io_error), "Failed call to SDL_CreateWindow.");
				}

				data.renderer = SDL_CreateRenderer(
					data.window,
					-1,
					SDL_RENDERER_SOFTWARE
				);
				// printf("data.renderer: %p\n", data.renderer);
				if (!data.renderer) {
					throw system_error(make_error_code(std::errc::io_error), "Failed call to SDL_CreateRenderer.");
				}

				_Create_display_surface_and_context<std::experimental::io2d::v1::_Graphics_math_float_impl>(data);

				data._Default_letterbox_brush = basic_brush<_Cairo_graphics_surfaces>(rgba_color::black);
				data._Letterbox_brush = data._Default_letterbox_brush;

				data.back_buffer = ::std::move(create_image_surface(data.back_buffer.format, data.back_buffer.dimensions.x(), data.back_buffer.dimensions.y()));

				data.elapsed_draw_time = 0.0f;

				data.redraw_required = true;

				// printf("entering loop\n");
				while (_Is_active<std::experimental::io2d::v1::_Graphics_math_float_impl>(data))
				{
					SDL_Event ev;
					while (SDL_PollEvent(&ev)) {}

					bool redraw = true;
					if (data.rr == io2d::refresh_style::as_needed) {
						redraw = data.redraw_required;
						data.redraw_required = false;
					}

					const auto desiredElapsed = 1'000'000'000.0F / data.refresh_fps;
					if (data.rr == io2d::refresh_style::fixed) {
						// desiredElapsed is the amount of time, in nanoseconds, that must have passed before we should redraw.
						redraw = data.elapsed_draw_time >= desiredElapsed;
					}
					if (redraw) {
						// Run user draw function:
						// printf("draw!\n");
						osd->draw_callback(sfc);
						_Render_to_native_surface(osd, sfc);
						if (data.rr == experimental::io2d::refresh_style::fixed) {
							while (data.elapsed_draw_time >= desiredElapsed) {
								data.elapsed_draw_time -= desiredElapsed;
							}
						}
						else {
							data.elapsed_draw_time = 0.0F;
						}
					}

					// Try to delay by a negligible amount of time.  On some platforms, this can help with responsiveness.
					SDL_Delay(0);
				}
				data.elapsed_draw_time = 0.0F;
				return 0;
			}
     

			int _handle_sdl2_event(void *userdata, SDL_Event *event) {
				switch (event->type) {
				// 	case WM_CREATE:
				// 	{
				// 		outputSfc->display_dimensions(outputSfc->data()->data.display_dimensions);
				// 		// Return 0 to allow the window to proceed in the creation process.
				// 		return lrZero;
				// 	} break;
				// 	case WM_CLOSE:
				// 	{
				// 		// This message is sent when a window or an application should
				// 		// terminate.
				// 		if (!DestroyWindow(hwnd)) {
				// 			_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to DestroyWindow when processing WM_CLOSE.");
				// 		}
				// 		outputSfc->data()->data.hwnd = nullptr;
				// 		return lrZero;
				// 	} break;
				// 	case WM_DESTROY:
				// 	{
				// 		// This message is sent when a window has been destroyed.
				// 		PostQuitMessage(0);
				// 		return lrZero;
				// 	} break;
				// 	case WM_SIZE:
				// 	{
				// 		auto dimensions = basic_display_point<_Graphics_math_float_impl>(LOWORD(lParam), HIWORD(lParam));
				// 		auto& data = *outputSfc->data();
				// 		if (data.data.display_dimensions != dimensions) {
				// 			data.data.display_dimensions = dimensions;

				// 			// Call user size change function.

				// 			if (data.size_change_callback != nullptr) {
				// 				data.size_change_callback(*outputSfc);
				// 			}
				// 			//_Display_surface.invoke_size_change_callback();
				// 		}
				// 	} break;

				// 	case WM_PAINT:
				// 	{
				// 		auto& data = *outputSfc->data();
				// 		auto& displayDimensions = data.data.display_dimensions;
				// 		PAINTSTRUCT ps;
				// 		HDC hdc;
				// 		hdc = BeginPaint(hwnd, &ps);
				// 		RECT clientRect;
				// 		GetClientRect(hwnd, &clientRect);
				// 		if (clientRect.right - clientRect.left != displayDimensions.x() || clientRect.bottom - clientRect.top != displayDimensions.y()) {
				// 			// If there is a size mismatch we skip painting and resize the window instead.
				// 			EndPaint(hwnd, &ps);
				// 			outputSfc->display_dimensions(displayDimensions);
				// 			break;
				// 		}

				// 		data.draw_callback(*outputSfc);
				// 		_Cairo_graphics_surfaces<_Graphics_math_float_impl>::surfaces::_Render_to_native_surface(outputSfc->data(), *outputSfc);

				// 		EndPaint(hwnd, &ps);
				// 	} break;
				}

				return 1;
			}
		}
	}
}

#if defined BUILD_IO2D_API_DLL
BOOL WINAPI DllMain( _In_ HINSTANCE /*hinstDLL*/, _In_ DWORD /*fdwReason*/, _In_ LPVOID /*lpvReserved*/ )
{
	return TRUE;
}
#endif
