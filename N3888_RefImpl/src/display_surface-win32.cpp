#include "io2d.h"
#include "xio2dhelpers.h"
#include "xcairoenumhelpers.h"
#include "cairo-win32.h"

using namespace std;
using namespace std::experimental::io2d;

inline void _Throw_system_error_for_GetLastError(DWORD getLastErrorValue, const char* message) {
	if (message != nullptr) {
		// Note: C-style cast because system_error requires an int but GetLastError returns a DWORD (i.e. unsigned long) but ordinary WinError.h values never exceed the max value of an int.
		throw system_error((int)getLastErrorValue, system_category(), message);
	}
	else {
		throw system_error((int)getLastErrorValue, system_category());
	}
}

namespace {
	void _ResizeWindowToClientArea(HWND hwnd, int width, int height) {
		RECT clientRect;
		RECT windowRect;
		GetWindowRect(hwnd, &windowRect);
		GetClientRect(hwnd, &clientRect);
		auto crWidth = clientRect.right - clientRect.left;
		auto crHeight = clientRect.bottom - clientRect.top;
		auto wrWidth = windowRect.right - windowRect.left;
		auto wrHeight = windowRect.bottom - windowRect.top;

		if (crWidth != width || crHeight != height) {
			// Record the desired client window size
			RECT rc;
			rc.top = rc.left = 0;
			rc.right = width;
			rc.bottom = height;

			// Adjust the window size for correct device size
			AdjustWindowRect(&rc, (WS_OVERLAPPEDWINDOW | WS_VISIBLE), FALSE);

			//LONG lwidth = rc.right - rc.left;
			LONG lheight = rc.bottom - rc.top;

			width = std::max(1L, (width - crWidth) + wrWidth);
			height = std::max(lheight - height, (height - crHeight) + wrHeight);
			SetWindowPos(hwnd, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
			PostMessageW(hwnd, WM_PAINT, (WPARAM)0, (LPARAM)0);
		}
	}
}

namespace std {
	namespace experimental {
		namespace io2d {
#if _Inline_namespace_conditional_support_test
			inline namespace v1 {
#endif
				LRESULT CALLBACK _RefImplWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
					LONG_PTR objPtr = GetWindowLongPtrW(hwnd, _Display_surface_ptr_window_data_byte_offset);

					if (objPtr == 0) {
						return(DefWindowProcW(hwnd, msg, wparam, lparam));
					}
					else {
						return reinterpret_cast<display_surface*>(objPtr)->_Window_proc(hwnd, msg, wparam, lparam);
					}
				}
#if _Inline_namespace_conditional_support_test
			}
#endif
		}
	}
}

const wchar_t* _Refimpl_window_class_name = L"_RefImplWndwCls";

ATOM _MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex{ };

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = _RefImplWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(display_surface*);
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = _Refimpl_window_class_name;
	wcex.hIconSm = nullptr;

	return RegisterClassEx(&wcex);
}

LRESULT display_surface::_Window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_CREATE:
	{
		_ResizeWindowToClientArea(hwnd, _Width, _Height);
		// Automatically return 0 to allow the window to proceed in the
		// creation process.
		return(0);
	} break;

	case WM_CLOSE:
	{
		// This message is sent when a window or an application should
		// terminate.
	} break;

	case WM_DESTROY:
	{
		// This message is sent when a window has been destroyed.
		PostQuitMessage(0);
		return(0);
	} break;

	case WM_SIZE:
	{
		int width = LOWORD(lparam);
		int height = HIWORD(lparam);
		_Width = static_cast<int>(width);
		_Height = static_cast<int>(height);

		// Call user size change function.
		if (_Size_change_fn != nullptr) {
			_Size_change_fn(*this);
		}
	} break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hwnd, &ps);
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);
		if (clientRect.right - clientRect.left != _Width || clientRect.bottom - clientRect.top != _Height) {
			// If there is a size mismatch we skip painting and resize the window instead.
			EndPaint(hwnd, &ps);
			_ResizeWindowToClientArea(hwnd, _Width, _Height);
			break;
		}

		if (_Win32_surface.get() == nullptr) {
			EndPaint(hwnd, &ps);
			break;
		}
		// Run user draw function:
		if (_Draw_fn != nullptr) {
			_Draw_fn(*this);
		}
		cairo_surface_flush(_Surface.get());
		cairo_set_source_surface(_Win32_context.get(), _Surface.get(), 0.0, 0.0);
		cairo_paint(_Win32_context.get());
		EndPaint(hwnd, &ps);
	} break;
	}

	return(DefWindowProc(hwnd, msg, wparam, lparam));
}

display_surface::native_handle_type display_surface::native_handle() const {
	return{ { _Surface.get(), _Context.get() }, _Hwnd, { _Win32_surface.get(), _Win32_context.get() } };
}

display_surface::display_surface(display_surface&& other)
	: surface(move(other))
	, _Width(move(other._Width))
	, _Height(move(other._Height))
	, _Display_width(move(other._Display_width))
	, _Display_height(move(other._Display_height))
	, _Draw_fn(move(other._Draw_fn))
	, _Size_change_fn(move(other._Size_change_fn))
	, _Hwnd(move(other._Hwnd))
	, _Win32_surface(move(other._Win32_surface))
	, _Win32_context(move(other._Win32_context)) {
	other._Draw_fn = nullptr;
	other._Size_change_fn = nullptr;
	other._Hwnd = nullptr;
}

display_surface& display_surface::operator=(display_surface&& other) {
	if (this != &other) {
		surface::operator=(move(other));
		_Width = move(other._Width);
		_Height = move(other._Height);
		_Display_width = move(other._Display_width);
		_Display_height = move(other._Display_height);
		_Draw_fn = move(other._Draw_fn);
		_Size_change_fn = move(other._Size_change_fn);
		_Hwnd = move(other._Hwnd);
		_Win32_surface = move(other._Win32_surface);
		_Win32_context = move(other._Win32_context);

		other._Hwnd = nullptr;
		other._Draw_fn = nullptr;
		other._Size_change_fn = nullptr;
	}

	return *this;
}

once_flag _Window_class_registered_flag;

display_surface::display_surface(int preferredWidth, int preferredHeight, experimental::io2d::format preferredFormat)
	: surface({ nullptr, nullptr }, preferredFormat, _Cairo_content_t_to_content(_Cairo_content_t_for_cairo_format_t(_Format_to_cairo_format_t(preferredFormat))))
	, _Width(preferredWidth)
	, _Height(preferredHeight)
	, _Display_width(preferredWidth)
	, _Display_height(preferredHeight)
	, _Draw_fn()
	, _Size_change_fn()
	, _Hwnd(nullptr)
	, _Win32_surface(nullptr, &cairo_surface_destroy)
	, _Win32_context(nullptr, &cairo_destroy) {
	call_once(_Window_class_registered_flag, _MyRegisterClass, static_cast<HINSTANCE>(GetModuleHandleW(nullptr)));
	// Record the desired client window size
	RECT rc;
	rc.top = rc.left = 0;
	rc.right = preferredWidth;
	rc.bottom = preferredHeight;

	// Adjust the window size for correct device size
	if (!AdjustWindowRect(&rc, (WS_OVERLAPPEDWINDOW | WS_VISIBLE), FALSE)) {
		_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to AdjustWindowRect in display_surface::display_surface(int, int, format).");
	}

	long lwidth = rc.right - rc.left;
	long lheight = rc.bottom - rc.top;

	long lleft = 10;
	long ltop = 10;


	// Create an instance of the window
	_Hwnd = CreateWindowEx(
		NULL,								// extended style
		_Refimpl_window_class_name,			// class name
		L"",								// instance title
		(WS_OVERLAPPEDWINDOW | WS_VISIBLE),	// window style
		lleft, ltop,						// initial x, y
		lwidth,								// initial width
		lheight,							// initial height
		NULL,								// handle to parent
		NULL,								// handle to menu
		NULL,								// instance of this application
		NULL);								// extra creation parms

	if (_Hwnd == nullptr) {
		_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to CreateWindowEx in display_surface::display_surface(int, int, format)");
	}

	SetLastError(ERROR_SUCCESS);
	// Set in the "extra" bytes the pointer to the 'this' pointer
	// so it can handle messages for itself.
	if (!SetWindowLongPtrW(_Hwnd, _Display_surface_ptr_window_data_byte_offset, (LONG_PTR)this)) {
		DWORD lastError = GetLastError();
		if (lastError != ERROR_SUCCESS) {
			_Throw_system_error_for_GetLastError(lastError, "Failed call to SetWindowLongPtrW(HWND, int, LONG_PTR) in display_surface::display_surface(int, int, format)");
		}
	}

	// Initially display the window
	ShowWindow(_Hwnd, SW_SHOWNORMAL);
	UpdateWindow(_Hwnd);

	// We are using CS_OWNDC to keep a steady HDC for the Win32 window.
	auto hdc = GetDC(_Hwnd);
	try {
		_Win32_surface = unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)>(cairo_win32_surface_create(hdc), &cairo_surface_destroy);
		_Win32_context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Win32_surface.get()), &cairo_destroy);

		// We render to the fixed size surface.
		_Surface = unique_ptr<cairo_surface_t, function<void(cairo_surface_t*)>>(cairo_image_surface_create(_Format_to_cairo_format_t(_Format), _Width, _Height), &cairo_surface_destroy);
		_Context = unique_ptr<cairo_t, decltype(&cairo_destroy)>(cairo_create(_Surface.get()), &cairo_destroy);
	}
	catch (...) {
		// Release the DC to avoid a handle leak.
		ReleaseDC(_Hwnd, hdc);
		throw;
	}

	// Release the DC to avoid a handle leak.
	ReleaseDC(_Hwnd, hdc);
}

display_surface::~display_surface() {
	if (_Hwnd != nullptr) {
		DestroyWindow(_Hwnd);
		_Hwnd = nullptr;
	}
}

void display_surface::draw_fn(const ::std::function<void(display_surface& sfc)>& fn) {
	_Draw_fn = fn;
}

void display_surface::size_change_fn(const ::std::function<void(display_surface& sfc)>& fn) {
	_Size_change_fn = fn;
}

void display_surface::width(int w) {
	throw system_error(make_error_code(errc::not_supported));
}

void display_surface::height(int h) {
	throw system_error(make_error_code(errc::not_supported));
}

void display_surface::size(const point& s) {
	throw system_error(make_error_code(errc::not_supported));
}

void display_surface::display_width(int w) {
	throw system_error(make_error_code(errc::not_supported));
}

void display_surface::display_height(int h) {
	throw system_error(make_error_code(errc::not_supported));
}

format display_surface::format() const {
	return _Format;
}

int display_surface::width() const {
	return _Width;
}

int display_surface::height() const {
	return _Height;
}

int display_surface::join() {
	MSG msg{ };
	msg.message = WM_NULL;

	while (msg.message != WM_QUIT)
	{
		if (!PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			//InvalidateRect(_Hwnd, nullptr, FALSE);
			//UpdateWindow(_Hwnd);

			if (_Win32_surface.get() != nullptr) {
				RECT clientRect;
				GetClientRect(_Hwnd, &clientRect);
				if (clientRect.right - clientRect.left != _Width || clientRect.bottom - clientRect.top != _Height) {
					// If there is a size mismatch we skip painting and resize the window instead.
					_ResizeWindowToClientArea(_Hwnd, _Width, _Height);
					break;
				}
				else {
					// Run user draw function:
					if (_Draw_fn != nullptr) {
						_Draw_fn(*this);
					}

					cairo_surface_flush(_Surface.get());
					cairo_set_source_surface(_Win32_context.get(), _Surface.get(), 0.0, 0.0);
					cairo_paint(_Win32_context.get());
					cairo_surface_flush(_Win32_surface.get());
				}
			}
		}
		else {
			if (msg.message != WM_QUIT) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	return (int)msg.wParam;
}

int display_surface::display_width() const {
	return _Display_width;
}

int display_surface::display_height() const {
	return _Display_height;
}
