#include "io2d.h"
#include <cairo-win32.h>
#include <chrono>
#include <sstream>
#include <string>
#include <iomanip>
#include <deque>
#include <numeric>
#include "xdiagnostics.h"

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;

[[noreturn]]
inline void _Throw_system_error_for_GetLastError(DWORD getLastErrorValue, const char* message) {
	if (message != nullptr) {
		// Updated Note: Changed to static_cast due to 4.7/3 [conv.integral]. // Old Note: C-style cast because system_error requires an int but GetLastError returns a DWORD (i.e. unsigned long) but ordinary WinError.h values never exceed the max value of an int.
		throw system_error(static_cast<int>(getLastErrorValue), system_category(), message);
	}
	else {
		throw system_error(static_cast<int>(getLastErrorValue), system_category());
	}
}

namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				LRESULT CALLBACK _RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
					LONG_PTR objPtr = GetWindowLongPtrW(hwnd, _Display_surface_ptr_window_data_byte_offset);

					if (objPtr == 0) {
						return DefWindowProcW(hwnd, msg, wparam, lparam);
					}
					else {
						return reinterpret_cast<display_surface*>(objPtr)->_Window_proc(hwnd, msg, wparam, lparam);
					}
				}
			}
		}
	}
}

namespace {
	const wchar_t* _Refimpl_window_class_name = L"_RefImplWndwCls";
}

ATOM _MyRegisterClass(HINSTANCE);
ATOM _MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex{ };

	wcex.cbSize = sizeof(WNDCLASSEX);
	// We want to keep a DC so we don't have to constantly recreate the native cairo device.
	// We want CS_HREDRAW and CS_VREDRAW so we get a refresh of the whole window if the client area changes due to movement or size adjustment.
	wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = ::std::experimental::io2d::_RefImplWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(display_surface*);
	wcex.hInstance = hInstance;
	wcex.hIcon = static_cast<HICON>(nullptr);
	wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wcex.lpszMenuName = static_cast<LPCWSTR>(nullptr);
	wcex.lpszClassName = _Refimpl_window_class_name;
	wcex.hIconSm = static_cast<HICON>(nullptr);

	return RegisterClassEx(&wcex);
}

void display_surface::_Make_native_surface_and_context() {
	auto hdc = GetDC(_Hwnd);
	try {
		_Native_surface = unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_win32_surface_create(hdc), &cairo_surface_destroy);
		_Native_context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Native_surface.get()), &cairo_destroy);
		_Throw_if_failed_cairo_status_t(cairo_surface_status(_Native_surface.get()));
		_Throw_if_failed_cairo_status_t(cairo_status(_Native_context.get()));
	}
	catch (...) {
		// Release the DC to avoid a handle leak.
		ReleaseDC(_Hwnd, hdc);
		throw;
	}
	// Release the DC to avoid a handle leak.
	ReleaseDC(_Hwnd, hdc);
}


void display_surface::_Resize_window() {
	RECT clientRect;
	RECT windowRect;
	GetWindowRect(_Hwnd, &windowRect);
	GetClientRect(_Hwnd, &clientRect);
	auto crWidth = clientRect.right - clientRect.left;
	auto crHeight = clientRect.bottom - clientRect.top;
	auto wrWidth = windowRect.right - windowRect.left;
	auto wrHeight = windowRect.bottom - windowRect.top;

	if (crWidth != _Display_width || crHeight != _Display_height) {
		auto width = std::max((wrWidth - crWidth) + 1L, (_Display_width - crWidth) + wrWidth);
		auto height = std::max((wrHeight - crHeight) + 1L, (_Display_height - crHeight) + wrHeight);
		// Resize the window.
		if (!SetWindowPos(_Hwnd, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS)) {
			_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to SetWindowPos.");
		}

		if (!PostMessageW(_Hwnd, WM_PAINT, static_cast<WPARAM>(0), static_cast<LPARAM>(0))) {
			_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to PostMessageW.");
		}
	}
}

LRESULT display_surface::_Window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	const static auto lrZero = static_cast<LRESULT>(0);
	switch (msg) {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunreachable-code-break"
#endif
	case WM_CREATE:
	{
		_Resize_window();
		// Return 0 to allow the window to proceed in the creation process.
		return lrZero;
	} break;
#ifdef __clang__
#pragma clang diagnostic pop
#endif
	case WM_CLOSE:
	{
		// This message is sent when a window or an application should
		// terminate.
		if (!DestroyWindow(hwnd)) {
			_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to DestroyWindow when processing WM_CLOSE.");
		}
		_Hwnd = nullptr;
		return lrZero;
	} break;

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
		int width = LOWORD(lparam);
		int height = HIWORD(lparam);

		if (_Display_width != width || _Display_height != height) {
			display_dimensions(width, height);

			// Call user size change function.
			if (_Size_change_fn != nullptr) {
				(*_Size_change_fn)(*this);
			}
		}
	} break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hwnd, &ps);
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);
		if (clientRect.right - clientRect.left != _Display_width || clientRect.bottom - clientRect.top != _Display_height) {
			// If there is a size mismatch we skip painting and resize the window instead.
			EndPaint(hwnd, &ps);
			_Resize_window();
			break;
		}

		if (_Native_surface.get() == nullptr) {
			EndPaint(hwnd, &ps);
			break;
		}
		// Run user draw function:
		if (_Draw_fn != nullptr) {
			if (_Auto_clear) {
				clear();
			}
			(*_Draw_fn)(*this);
		}

		_Render_to_native_surface();

		EndPaint(hwnd, &ps);
	} break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

display_surface::native_handle_type display_surface::native_handle() const {
	return{ { _Surface.get(), _Context.get() }, _Hwnd, { _Native_surface.get(), _Native_context.get() } };
}

namespace {
	once_flag _Window_class_registered_flag;
}

display_surface::display_surface(int preferredWidth, int preferredHeight, experimental::io2d::format preferredFormat, experimental::io2d::scaling scl, experimental::io2d::refresh_rate rr, double desiredFramerate)
	: display_surface(preferredWidth, preferredHeight, preferredFormat, preferredWidth, preferredHeight, scl, rr, desiredFramerate) {
}

display_surface::display_surface(int preferredWidth, int preferredHeight, experimental::io2d::format preferredFormat, int preferredDisplayWidth, int preferredDisplayHeight, experimental::io2d::scaling scl, experimental::io2d::refresh_rate rr, double fps)
	: surface({ nullptr, nullptr }, preferredFormat)
	, _Display_width(preferredDisplayWidth)
	, _Display_height(preferredDisplayHeight)
	, _Scaling(scl)
	, _Width(preferredWidth)
	, _Height(preferredHeight)
	, _Draw_fn()
	, _Size_change_fn()
	, _User_scaling_fn()
	, _Auto_clear(false)
	, _Window_style(WS_OVERLAPPEDWINDOW | WS_VISIBLE)
	, _Hwnd(nullptr)
	, _Refresh_rate(rr)
	, _Desired_frame_rate(fps)
	, _Redraw_requested(true)
	, _Native_surface(nullptr, &cairo_surface_destroy)
	, _Native_context(nullptr, &cairo_destroy)
	, _Letterbox_brush()
	, _Default_brush(rgba_color::transparent_black) {
	call_once(_Window_class_registered_flag, _MyRegisterClass, static_cast<HINSTANCE>(GetModuleHandleW(nullptr)));

	// Record the desired client window size
	if (preferredDisplayWidth <= 0 || preferredDisplayHeight <= 0 || preferredWidth <= 0 || preferredHeight <= 0 || preferredFormat == experimental::io2d::format::invalid) {
		throw invalid_argument("Invalid parameter.");
	}
	if (fps <= _Minimum_frame_rate || !isfinite(fps)) {
		throw system_error(make_error_code(errc::argument_out_of_domain));
	}
//	RECT rc;
//	rc.top = rc.left = 0;
//	rc.right = preferredDisplayWidth;
//	rc.bottom = preferredDisplayHeight;
//
//	// Adjust the window size for correct device size
//	if (!AdjustWindowRect(&rc, (WS_OVERLAPPEDWINDOW | WS_VISIBLE), FALSE)) {
//		_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to AdjustWindowRect in display_surface::display_surface(int, int, format, int, int, scaling).");
//	}
//
//	long lwidth = rc.right - rc.left;
//	long lheight = rc.bottom - rc.top;
//
//	long lleft = 10;
//	long ltop = 10;
//
//
//	// Create an instance of the window
//	_Hwnd = CreateWindowEx(
//		static_cast<DWORD>(0),				// extended style
//		_Refimpl_window_class_name,			// class name
//		L"",								// instance title
//		(WS_OVERLAPPEDWINDOW | WS_VISIBLE),	// window style
//		lleft, ltop,						// initial x, y
//		lwidth,								// initial width
//		lheight,							// initial height
//		static_cast<HWND>(nullptr),			// handle to parent
//		static_cast<HMENU>(nullptr),		// handle to menu
//		static_cast<HINSTANCE>(nullptr),	// instance of this application
//		static_cast<LPVOID>(nullptr));		// extra creation parms
//
//	if (_Hwnd == nullptr) {
//		_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to CreateWindowEx in display_surface::display_surface(int, int, format, int, int, scaling)");
//	}
//
//	SetLastError(ERROR_SUCCESS);
//	// Set in the "extra" bytes the pointer to the 'this' pointer
//	// so it can handle messages for itself.
//	// I know that the C-style cast works and have not had a chance to come up with a safer C++-style cast that I can be sure also works so I'm disabling the warning.
//#ifdef _WIN32
//#ifdef __clang__
//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Wold-style-cast"
//#endif
//#endif
//
//	if (!SetWindowLongPtrW(_Hwnd, _Display_surface_ptr_window_data_byte_offset, (LONG_PTR)this)) {
//		// I know that the C-style cast works and have not had a chance to come up with a safer C++-style cast that I can be sure also works so I'm disabling the warning.
//#ifdef _WIN32
//#ifdef __clang__
//#pragma clang diagnostic pop
//#endif
//#endif
//		DWORD lastError = GetLastError();
//		if (lastError != ERROR_SUCCESS) {
//			_Throw_system_error_for_GetLastError(lastError, "Failed call to SetWindowLongPtrW(HWND, int, LONG_PTR) in display_surface::display_surface(int, int, format, int, int, scaling)");
//		}
//	}
//
//	// Initially display the window
//	ShowWindow(_Hwnd, SW_SHOWNORMAL);
//	UpdateWindow(_Hwnd);
//
//	// We are using CS_OWNDC to keep a steady HDC for the Win32 window.
//	_Make_native_surface_and_context();
//
//	// We render to the fixed size surface.
//	_Surface = unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(_Format), _Width, _Height), &cairo_surface_destroy);
//	_Context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy);
//	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
//	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));
}

display_surface::~display_surface() {
	if (_Hwnd != nullptr) {
		assert(_Hwnd == nullptr);
		DestroyWindow(_Hwnd);
		_Hwnd = nullptr;
	}
}

int display_surface::begin_show() {
	RECT rc;
	rc.top = rc.left = 0;
	rc.right = _Display_width;
	rc.bottom = _Display_height;

	// Adjust the window size for correct device size
	if (!AdjustWindowRect(&rc, (WS_OVERLAPPEDWINDOW | WS_VISIBLE), FALSE)) {
		_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to AdjustWindowRect in display_surface::display_surface(int, int, format, int, int, scaling).");
	}

	long lwidth = rc.right - rc.left;
	long lheight = rc.bottom - rc.top;

	long lleft = 10;
	long ltop = 10;


	// Create an instance of the window
	_Hwnd = CreateWindowEx(
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

	if (_Hwnd == nullptr) {
		_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to CreateWindowEx in display_surface::display_surface(int, int, format, int, int, scaling)");
	}

	SetLastError(ERROR_SUCCESS);
	// Set in the "extra" bytes the pointer to the 'this' pointer
	// so it can handle messages for itself.
	// I know that the C-style cast works and have not had a chance to come up with a safer C++-style cast that I can be sure also works so I'm disabling the warning.
#ifdef _WIN32
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
#endif
#endif

	if (!SetWindowLongPtrW(_Hwnd, _Display_surface_ptr_window_data_byte_offset, (LONG_PTR)this)) {
		// I know that the C-style cast works and have not had a chance to come up with a safer C++-style cast that I can be sure also works so I'm disabling the warning.
#ifdef _WIN32
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#endif
		DWORD lastError = GetLastError();
		if (lastError != ERROR_SUCCESS) {
			_Throw_system_error_for_GetLastError(lastError, "Failed call to SetWindowLongPtrW(HWND, int, LONG_PTR) in display_surface::display_surface(int, int, format, int, int, scaling)");
		}
	}

	// Initially display the window
	ShowWindow(_Hwnd, SW_SHOWNORMAL);
	UpdateWindow(_Hwnd);

	// We are using CS_OWNDC to keep a steady HDC for the Win32 window.
	_Make_native_surface_and_context();

	// We render to the fixed size surface.
	_Surface = unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_image_surface_create(_Format_to_cairo_format_t(_Format), _Width, _Height), &cairo_surface_destroy);
	_Context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy);
	_Throw_if_failed_cairo_status_t(cairo_surface_status(_Surface.get()));
	_Throw_if_failed_cairo_status_t(cairo_status(_Context.get()));

	MSG msg{ };
	msg.message = WM_NULL;
	if (_Draw_fn == nullptr) {
		throw system_error(make_error_code(errc::operation_would_block));
	}
	_Elapsed_draw_time = 0.0;
#ifdef _IO2D_WIN32FRAMERATE
	auto previousTime = steady_clock::now();
	long long int elapsedDrawNanoseconds = 0LL;
	int updateTitleCounter = -1;
	deque<chrono::nanoseconds> elapsedNanoseconds(static_cast<size_t>(30), 33'333'333ns);
#endif
	while (msg.message != WM_QUIT) {
#ifdef _IO2D_WIN32FRAMERATE
		auto currentTime = steady_clock::now();
		auto elapsedTimeIncrement = static_cast<double>(duration_cast<nanoseconds>(currentTime - previousTime).count());
		_Elapsed_draw_time += elapsedTimeIncrement;
		elapsedDrawNanoseconds += duration_cast<nanoseconds>(currentTime - previousTime).count();
		previousTime = currentTime;
#endif
		if (!PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (_Native_surface.get() != nullptr) {
				RECT clientRect;
				GetClientRect(_Hwnd, &clientRect);
				if (clientRect.right - clientRect.left != _Display_width || clientRect.bottom - clientRect.top != _Display_height) {
					// If there is a size mismatch we skip painting and resize the window instead.
					auto dw = _Display_width;
					auto dh = _Display_height;
					_Resize_window();
					_Make_native_surface_and_context();
					if (dw != _Display_width || dh != _Display_height) {
						if (_Size_change_fn != nullptr) {
							(*_Size_change_fn)(*this);
						}
					}
					continue;
				}
				else {
					bool redraw = true;
					if (_Refresh_rate == experimental::io2d::refresh_rate::as_needed) {
						redraw = _Redraw_requested;
						_Redraw_requested = false;
					}

					const auto desiredElapsed = 1'000'000'000.0 / _Desired_frame_rate;
#ifdef _IO2D_WIN32FRAMERATE
					const long long desiredElapsedNanoseconds = static_cast<long long>(1'000'000'000.00 / _Desired_frame_rate);
#endif
					if (_Refresh_rate == experimental::io2d::refresh_rate::fixed) {
						// desiredElapsed is the amount of time, in nanoseconds, that must have passed before we should redraw.
						redraw = _Elapsed_draw_time >= desiredElapsed;
					}
					if (redraw) {
						// Run user draw function:
						if (_Draw_fn != nullptr) {
							if (_Auto_clear) {
								clear();
							}
							(*_Draw_fn)(*this);
						}
						else {
							throw system_error(make_error_code(errc::operation_would_block));
						}
						_Render_to_native_surface();

#ifdef _IO2D_WIN32FRAMERATE
						elapsedNanoseconds.pop_front();
						elapsedNanoseconds.push_back(chrono::nanoseconds(elapsedDrawNanoseconds));
#endif
						if (_Refresh_rate == experimental::io2d::refresh_rate::fixed) {
							while (_Elapsed_draw_time >= desiredElapsed) {
								_Elapsed_draw_time -= desiredElapsed;
							}
#ifdef _IO2D_WIN32FRAMERATE
							while (elapsedDrawNanoseconds >= desiredElapsedNanoseconds) {
								elapsedDrawNanoseconds -= desiredElapsedNanoseconds;
							}
#endif
						}
						else {
							_Elapsed_draw_time = 0.0;
#ifdef _IO2D_WIN32FRAMERATE
							elapsedDrawNanoseconds = 0LL;
#endif
						}
					}
				}
			}
		}
		else {
			if (msg.message != WM_QUIT) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				if (msg.message == WM_PAINT) {
					const auto desiredElapsed = 1'000'000'000.0 / _Desired_frame_rate;
#ifdef _IO2D_WIN32FRAMERATE
					elapsedNanoseconds.pop_front();
					elapsedNanoseconds.push_back(chrono::nanoseconds(elapsedDrawNanoseconds));

					const long long desiredElapsedNanoseconds = static_cast<long long>(1'000'000'000.00 / _Desired_frame_rate);
#endif
					if (_Refresh_rate == experimental::io2d::refresh_rate::fixed) {
						while (_Elapsed_draw_time >= desiredElapsed) {
							_Elapsed_draw_time -= desiredElapsed;
						}
#ifdef _IO2D_WIN32FRAMERATE
						while (elapsedDrawNanoseconds >= desiredElapsedNanoseconds) {
							elapsedDrawNanoseconds -= desiredElapsedNanoseconds;
						}
#endif
					}
					else {
						_Elapsed_draw_time = 0.0;
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
			const auto fpsNano = 1'000'000'000.0 / avgNanoFrameTime;
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
	_Elapsed_draw_time = 0.0;
	return static_cast<int>(msg.wParam);
}

void display_surface::end_show() noexcept {
	PostQuitMessage(0);
}
