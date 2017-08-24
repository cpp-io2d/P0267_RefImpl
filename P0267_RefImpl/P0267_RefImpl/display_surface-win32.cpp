#include "io2d.h"
#include "xdiagnostics.h"
#include "xinclwindows_h.h"

#include <chrono>
#include <sstream>
#include <string>
#include <iomanip>
#include <deque>
#include <numeric>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;
using namespace std::experimental::io2d::v1::cairo;

[[noreturn]]
inline void _Throw_system_error_for_GetLastError(DWORD getLastErrorValue, const char* message) {
	if (message != nullptr) {
		// Updated Note: Changed to static_cast due to 4.7F/3 [conv.integral]. // Old Note: C-style cast because system_error requires an int but GetLastError returns a DWORD (i.e. unsigned long) but ordinary WinError.h values never exceed the max value of an int.
		throw system_error(static_cast<int>(getLastErrorValue), system_category(), message);
	}
	else {
		throw system_error(static_cast<int>(getLastErrorValue), system_category());
	}
}

namespace {
	once_flag _Window_class_registered_flag;
	const wchar_t* _Refimpl_window_class_name = L"_RefImplWndwCls";
}

windows::windows_handler::windows_handler(experimental::io2d::refresh_rate rr, float fps)
	: _Surface(nullptr)
	, _Refresh_rate(rr)
	, _Desired_frame_rate(fps)
	, _Window_style(WS_OVERLAPPEDWINDOW | WS_VISIBLE)
	, _Hwnd(nullptr)
{
	if (fps <= _Minimum_frame_rate || !isfinite(fps)) {
		throw system_error(make_error_code(errc::argument_out_of_domain));
	}
	call_once(_Window_class_registered_flag, [](){
		WNDCLASSEX wcex{};

		wcex.cbSize = sizeof(WNDCLASSEX);
		// We want to keep a DC so we don't have to constantly recreate the native cairo device.
		// We want CS_HREDRAW and CS_VREDRAW so we get a refresh of the whole window if the client area changes due to movement or size adjustment.
		wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = windows_handler::_RefImplWindowProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(cairo_display_surface*);
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

windows::windows_handler::~windows_handler() {
	if (_Hwnd != nullptr) {
		assert(_Hwnd == nullptr);
		DestroyWindow(_Hwnd);
		_Hwnd = nullptr;
	}
}

float windows::windows_handler::elapsed_draw_time() const noexcept {
	return _Elapsed_draw_time / 1'000'000.0F;
}

void windows::windows_handler::refresh_rate(experimental::io2d::refresh_rate rr) noexcept {
	if (rr == experimental::io2d::refresh_rate::fixed && _Refresh_rate != rr) {
		_Elapsed_draw_time = 0.0F;
	}
	_Refresh_rate = rr;
}

experimental::io2d::refresh_rate windows::windows_handler::refresh_rate() const noexcept {
	return _Refresh_rate;
}

bool windows::windows_handler::desired_frame_rate(float fps) noexcept {
	if (!isfinite(fps)) {
		return true;
	}
	if (fps < _Minimum_frame_rate) {
		_Desired_frame_rate = _Minimum_frame_rate;
		return true;
	}
	if (fps > _Maximum_frame_rate) {
		_Desired_frame_rate = _Maximum_frame_rate;
		return true;
	}
	_Desired_frame_rate = fps;

	return false;
}

float windows::windows_handler::desired_frame_rate() const noexcept {
	return _Desired_frame_rate;
}

int windows::windows_handler::begin_show(display_surface<cairo_renderer>& ds) {
	_Display_surface = &ds;
	_Surface = &ds.native_handle();

	RECT rc;
	rc.top = rc.left = 0;
	rc.right = _Surface->display_width();
	rc.bottom = _Surface->display_height();

	// Adjust the window size for correct device size
	if (!AdjustWindowRect(&rc, (WS_OVERLAPPEDWINDOW | WS_VISIBLE), FALSE)) {
		_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to AdjustWindowRect in cairo_display_surface::cairo_display_surface(int, int, format, int, int, scaling).");
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
		_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to CreateWindowEx in cairo_display_surface::cairo_display_surface(int, int, format, int, int, scaling)");
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
			_Throw_system_error_for_GetLastError(lastError, "Failed call to SetWindowLongPtrW(HWND, int, LONG_PTR) in cairo_display_surface::cairo_display_surface(int, int, format, int, int, scaling)");
		}
	}

	// Initially display the window
	ShowWindow(_Hwnd, SW_SHOWNORMAL);
	UpdateWindow(_Hwnd);

	// We are using CS_OWNDC to keep a steady HDC for the Win32 window.
	_Surface->_Make_native_surface_and_context(context(_Hwnd));
	_Surface->_Make_impl_surface_and_context();

	MSG msg{ };
	msg.message = WM_NULL;
	if (_Surface->_Draw_fn == nullptr) {
		throw system_error(make_error_code(errc::operation_would_block));
	}
	_Elapsed_draw_time = 0.0F;
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
			if (_Surface->_Native_surface.get() != nullptr) {
				RECT clientRect;
				GetClientRect(_Hwnd, &clientRect);
				if (clientRect.right - clientRect.left != _Surface->display_width() || clientRect.bottom - clientRect.top != _Surface->display_height()) {
					// If there is a size mismatch we skip painting and resize the window instead.
					auto dw = _Surface->display_width();
					auto dh = _Surface->display_height();
					resize_window(dw, dh);
					_Surface->_Make_native_surface_and_context(context(_Hwnd));
					if (dw != _Surface->display_width() || dh != _Surface->display_height()) {
						if (_Surface->_Size_change_fn != nullptr) {
							(*_Surface->_Size_change_fn)(*_Display_surface);
						}
					}
					continue;
				}
				else {
					bool redraw = true;
					if (_Refresh_rate == experimental::io2d::refresh_rate::as_needed) {
						redraw = _Surface->_Redraw_requested;
						_Surface->_Redraw_requested = false;
					}

					const auto desiredElapsed = 1'000'000'000.0F / _Desired_frame_rate;
#ifdef _IO2D_WIN32FRAMERATE
					const long long desiredElapsedNanoseconds = static_cast<long long>(1'000'000'000.00F / _Desired_frame_rate);
#endif
					if (_Refresh_rate == experimental::io2d::refresh_rate::fixed) {
						// desiredElapsed is the amount of time, in nanoseconds, that must have passed before we should redraw.
						redraw = _Elapsed_draw_time >= desiredElapsed;
					}
					if (redraw) {
						// Run user draw function:
						if (_Surface->_Draw_fn != nullptr) {
							if (_Surface->_Auto_clear) {
								_Surface->_Cairo_surface->clear();
							}
							(*_Surface->_Draw_fn)(*_Display_surface);
						}
						else {
							throw system_error(make_error_code(errc::operation_would_block));
						}
						_Surface->_Render_to_native_surface(*_Display_surface);

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
							_Elapsed_draw_time = 0.0F;
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
					const auto desiredElapsed = 1'000'000'000.0F / _Desired_frame_rate;
#ifdef _IO2D_WIN32FRAMERATE
					elapsedNanoseconds.pop_front();
					elapsedNanoseconds.push_back(chrono::nanoseconds(elapsedDrawNanoseconds));

					const long long desiredElapsedNanoseconds = static_cast<long long>(1'000'000'000.00F / _Desired_frame_rate);
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
						_Elapsed_draw_time = 0.0F;
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
	_Elapsed_draw_time = 0.0F;
	return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK windows::windows_handler::_RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	LONG_PTR objPtr = GetWindowLongPtrW(hwnd, _Display_surface_ptr_window_data_byte_offset);

	if (objPtr == 0) {
		return DefWindowProcW(hwnd, msg, wparam, lparam);
	}
	else {
		return reinterpret_cast<windows::windows_handler*>(objPtr)->_Window_proc(hwnd, msg, wparam, lparam);
	}
}

LRESULT windows::windows_handler::_Window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	const static auto lrZero = static_cast<LRESULT>(0);
	switch (msg) {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunreachable-code-break"
#endif
	case WM_CREATE:
	{
		resize_window(_Surface->display_width(), _Surface->display_height());
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

		if (_Surface->width() != width || _Surface->height() != height) {
			_Surface->display_dimensions(*this, width, height);

			// Call user size change function.
			if (_Surface->_Size_change_fn != nullptr) {
				(*(_Surface->_Size_change_fn))(*(_Display_surface));
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
		if (clientRect.right - clientRect.left != _Surface->display_width() || clientRect.bottom - clientRect.top != _Surface->display_height()) {
			// If there is a size mismatch we skip painting and resize the window instead.
			EndPaint(hwnd, &ps);
			resize_window(_Surface->display_width(), _Surface->display_height());
			break;
		}

		if (_Surface->_Native_surface.get() == nullptr) {
			EndPaint(hwnd, &ps);
			break;
		}
		// Run user draw function:
		if (_Surface->_Draw_fn != nullptr) {
			if (_Surface->_Auto_clear) {
				_Surface->_Cairo_surface->clear();
			}
			(*_Surface->_Draw_fn)(*_Display_surface);
		}

		_Surface->_Render_to_native_surface(*_Display_surface);

		EndPaint(hwnd, &ps);
	} break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void windows::windows_handler::resize_window(LONG width, LONG height) const {
	RECT clientRect;
	RECT windowRect;
	GetWindowRect(_Hwnd, &windowRect);
	GetClientRect(_Hwnd, &clientRect);
	auto crWidth = clientRect.right - clientRect.left;
	auto crHeight = clientRect.bottom - clientRect.top;
	auto wrWidth = windowRect.right - windowRect.left;
	auto wrHeight = windowRect.bottom - windowRect.top;

	if (crWidth != width || crHeight != height) {
		auto new_width = std::max((wrWidth - crWidth) + 1L, (width - crWidth) + wrWidth);
		auto new_height = std::max((wrHeight - crHeight) + 1L, (height - crHeight) + wrHeight);
		// Resize the window.
		if (!SetWindowPos(_Hwnd, 0, 0, 0, new_width, new_height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS)) {
			_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to SetWindowPos.");
		}

		if (!PostMessageW(_Hwnd, WM_PAINT, static_cast<WPARAM>(0), static_cast<LPARAM>(0))) {
			_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to PostMessageW.");
		}
	}
}

void windows::windows_handler::end_show() {
	PostQuitMessage(0);
}

windows::windows_handler::context windows::windows_handler::make_context() const
{
	return context(_Hwnd);
}
