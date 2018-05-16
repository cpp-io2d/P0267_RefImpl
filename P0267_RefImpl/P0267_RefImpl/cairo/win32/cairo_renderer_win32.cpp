//#include "io2d.h"
// #include "xcairo.h"
#include "xio2d_cairo_win32_main.h"
#include <mutex>

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Cairo {
			LRESULT CALLBACK _RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

			static once_flag _Window_class_registered_flag;
			void _RegisterWindowClass() {
				::std::call_once(_Window_class_registered_flag, []() {
					WNDCLASSEX wcex{};

					wcex.cbSize = sizeof(WNDCLASSEX);
					// We want to keep a DC so we don't have to constantly recreate the native cairo device.
					// We want CS_HREDRAW and CS_VREDRAW so we get a refresh of the whole window if the client area changes due to movement or size adjustment.
					wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
					wcex.lpfnWndProc = _RefImplWindowProc;
					wcex.cbClsExtra = 0;
					wcex.cbWndExtra = sizeof(LONG_PTR);
					wcex.hInstance = static_cast<HINSTANCE>(GetModuleHandleW(nullptr));
					wcex.hIcon = static_cast<HICON>(nullptr);
					wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
					wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
					wcex.lpszMenuName = static_cast<LPCWSTR>(nullptr);
					wcex.lpszClassName = _Refimpl_window_class_name;
					wcex.hIconSm = static_cast<HICON>(nullptr);

					return RegisterClassEx(&wcex);
				});
			}

			LRESULT CALLBACK _RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
				LONG_PTR objPtr = GetWindowLongPtrW(hwnd, 0);

				if (objPtr == 0) {
					return DefWindowProcW(hwnd, msg, wParam, lParam);
				}
				else {
					// Run the class-specific window proc code
					auto outputSfc = reinterpret_cast<basic_output_surface<_Cairo_graphics_surfaces<_Graphics_math_float_impl>>*>(objPtr);

					const static auto lrZero = static_cast<LRESULT>(0);
					switch (msg) {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunreachable-code-break"
#endif
					case WM_CREATE:
					{
						outputSfc->display_dimensions(outputSfc->data()->data.display_dimensions);
						// Return 0 to allow the window to proceed in the creation process.
						return lrZero;
					} break;
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunreachable-code-break"
#endif
					case WM_CLOSE:
					{
						// This message is sent when a window or an application should
						// terminate.
						if (!DestroyWindow(hwnd)) {
							_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to DestroyWindow when processing WM_CLOSE.");
						}
						outputSfc->data()->data.hwnd = nullptr;
						return lrZero;
					} break;

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunreachable-code-break"
#endif
					case WM_DESTROY:
					{
						// This message is sent when a window has been destroyed.
						PostQuitMessage(0);
						return lrZero;
					} break;
#ifdef __clang__
#pragma clang diagnostic pop
#endif

					case WM_SIZE:
					{
						auto dimensions = basic_display_point<_Graphics_math_float_impl>(LOWORD(lParam), HIWORD(lParam));
						auto& data = *outputSfc->data();
						if (data.data.display_dimensions != dimensions) {
							data.data.display_dimensions = dimensions;

							// Call user size change function.

							if (data.size_change_callback != nullptr) {
								data.size_change_callback(*outputSfc);
							}
							//_Display_surface.invoke_size_change_callback();
						}
					} break;

					case WM_PAINT:
					{
						auto& data = *outputSfc->data();
						auto& displayDimensions = data.data.display_dimensions;
						PAINTSTRUCT ps;
						HDC hdc;
						hdc = BeginPaint(hwnd, &ps);
						RECT clientRect;
						GetClientRect(hwnd, &clientRect);
						if (clientRect.right - clientRect.left != displayDimensions.x() || clientRect.bottom - clientRect.top != displayDimensions.y()) {
							// If there is a size mismatch we skip painting and resize the window instead.
							EndPaint(hwnd, &ps);
							outputSfc->display_dimensions(displayDimensions);
							break;
						}

						data.draw_callback(*outputSfc);
						_Cairo_graphics_surfaces<_Graphics_math_float_impl>::surfaces::_Render_to_native_surface(outputSfc->data(), *outputSfc);

						EndPaint(hwnd, &ps);
					} break;
					}
					return DefWindowProc(hwnd, msg, wParam, lParam);

				}
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
