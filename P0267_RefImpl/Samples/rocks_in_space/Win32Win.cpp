#include "Win32Win.h"
#include <mutex>
#include <system_error>

namespace
{
	[[noreturn]]
	void throw_system_error_for_GetLastError(DWORD getLastErrorValue, const char* message) {
		if (message != nullptr) {
			// Updated Note: Changed to static_cast due to 4.7F/3 [conv.integral]. // Old Note: C-style cast because system_error requires an int but GetLastError returns a DWORD (i.e. unsigned long) but ordinary WinError.h values never exceed the max value of an int.
			throw std::system_error(static_cast<int>(getLastErrorValue), std::system_category(), message);
		}
		else {
			throw std::system_error(static_cast<int>(getLastErrorValue), std::system_category());
		}
	}

	static std::once_flag winClassRegistered;
	const wchar_t* winClassName = L"RocksInSpaceWinClass";
}

LRESULT CALLBACK DefaultWindowProc(HWND, UINT, WPARAM, LPARAM);
void RegisterWindowClass();

void RegisterWindowClass() {
	::std::call_once(winClassRegistered, []() {
		WNDCLASSEX wcex{};

		wcex.cbSize = sizeof(WNDCLASSEX);
		// We want to keep a DC so we don't have to constantly recreate the native cairo device.
		// We want CS_HREDRAW and CS_VREDRAW so we get a refresh of the whole window if the client area changes due to movement or size adjustment.
		wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = rocks_in_space::DefaultWindowProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = static_cast<HINSTANCE>(GetModuleHandleW(nullptr));
		wcex.hIcon = static_cast<HICON>(nullptr);
		wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
		wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
		wcex.lpszMenuName = static_cast<LPCWSTR>(nullptr);
		wcex.lpszClassName = winClassName;
		wcex.hIconSm = static_cast<HICON>(nullptr);

		return RegisterClassEx(&wcex);
	});
}

LRESULT CALLBACK rocks_in_space::DefaultWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	LONG_PTR objPtr = GetWindowLongPtrW(hwnd, 0);
	if (msg == WM_CREATE) {
		CREATESTRUCT* create = reinterpret_cast<CREATESTRUCT*>(lParam);
		// Return 0 to allow the window to proceed in the creation process.
		static_cast<rocks_in_space::Win32Win*>(create->lpCreateParams)->OnWmCreate(hwnd);
		return static_cast<LRESULT>(0);
	}
	if (objPtr == 0) {
		return DefWindowProcW(hwnd, msg, wParam, lParam);
	}
	else {
		// Run the class-specific window proc code
		auto win32Win = reinterpret_cast<rocks_in_space::Win32Win*>(objPtr);
		return win32Win->WindowProc(hwnd, msg, wParam, lParam);
	}
}

void rocks_in_space::Win32Win::OnWmCreate(HWND hwnd)
{
	SetLastError(ERROR_SUCCESS);
	if (SetWindowLongPtrW(hwnd, 0, reinterpret_cast<LONG_PTR>(this)) == 0) {
		// SetWindowLongPtr is weird in terms of how it fails. See its documentation. Hence this weird check.
		DWORD lastError = GetLastError();
		if (lastError != ERROR_SUCCESS) {
			throw_system_error_for_GetLastError(lastError, "Failed call to SetWindowLongPtrW(HWND, int, LONG_PTR) in cairo_display_surface::cairo_display_surface(int, int, format, int, int, scaling)");
		}
	}
	m_hwnd = hwnd;
	m_hdc = GetDC(m_hwnd);
	default_graphics_surfaces::surfaces::unmanaged_surface_context_type unmanaged_context;
	unmanaged_context.hInstance = m_hInstance;
	unmanaged_context.hwnd = m_hwnd;
	unmanaged_context.hdc = m_hdc;
	m_outputSfc = std::experimental::io2d::unmanaged_output_surface(default_graphics_surfaces::surfaces::create_unmanaged_output_surface(unmanaged_context, m_w, m_h, m_fmt, m_scl));
	m_outputSfc.display_dimensions(display_point{ m_w, m_h });
	m_outputSfc.draw_callback([&](std::experimental::io2d::unmanaged_output_surface& uos) { m_game.update<std::experimental::io2d::unmanaged_output_surface>(uos); });
	m_canDraw = true;
}

LRESULT CALLBACK rocks_in_space::Win32Win::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	const static auto lrZero = static_cast<LRESULT>(0);
	switch (msg) {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunreachable-code-break"
#endif
	case WM_CREATE:
	{
		m_hdc = GetDC(m_hwnd);
		default_graphics_surfaces::surfaces::unmanaged_surface_context_type unmanaged_context;
		unmanaged_context.hInstance = m_hInstance;
		unmanaged_context.hwnd = m_hwnd;
		unmanaged_context.hdc = m_hdc;
		m_outputSfc = std::experimental::io2d::unmanaged_output_surface(default_graphics_surfaces::surfaces::create_unmanaged_output_surface(unmanaged_context, m_w, m_h, m_fmt, m_scl));
		m_outputSfc.display_dimensions(display_point{ m_w, m_h });
		m_outputSfc.draw_callback([&](std::experimental::io2d::unmanaged_output_surface& uos) { m_game.update<std::experimental::io2d::unmanaged_output_surface>(uos); });
		m_canDraw = true;
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
		m_canDraw = false;
		// This message is sent when a window or an application should
		// terminate.
		if (!DestroyWindow(hwnd)) {
			throw_system_error_for_GetLastError(GetLastError(), "Failed call to DestroyWindow when processing WM_CLOSE.");
		}
		m_hwnd = nullptr;
		m_outputSfc.data()->data.hwnd = m_hwnd;
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
		m_canDraw = false;
		// This message is sent when a window has been destroyed.
		PostQuitMessage(0);
		return lrZero;
	} break;
#ifdef __clang__
#pragma clang diagnostic pop
#endif

	case WM_SIZE:
	{
		m_outputSfc.display_dimensions(display_point(LOWORD(lParam), HIWORD(lParam)));
	} break;

	case WM_PAINT:
	{
		if (m_canDraw) {
			PAINTSTRUCT ps;

			BeginPaint(hwnd, &ps);
			RECT clientRect;
			GetClientRect(hwnd, &clientRect);
			int width = clientRect.right - clientRect.left;
			int height = clientRect.bottom - clientRect.top;
			const auto& data = *m_outputSfc.data();
			if (width != data.data.display_dimensions.x() || height != data.data.display_dimensions.y()) {
				//if (width != m_outputSfc.display_dimensions().x() || height != m_outputSfc.display_dimensions().y()) {
				// If there is a size mismatch we skip painting and resize the window instead.
				EndPaint(hwnd, &ps);
				m_outputSfc.display_dimensions(display_point{ width, height });
				break;
			}

			if (m_outputSfc.has_draw_callback() && m_canDraw) {
				m_outputSfc.clear();
				m_outputSfc.invoke_draw_callback();
				m_outputSfc.draw_to_output();
			}

			EndPaint(hwnd, &ps);
		}
	} break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);

}

rocks_in_space::Win32Win::Win32Win(HINSTANCE hinst, int w, int h, format fmt, scaling scl)
	: m_hInstance(hinst)
	, m_hwnd(nullptr)
	, m_hdc(nullptr)
	, m_w(w)
	, m_h(h)
	, m_fmt(fmt)
	, m_scl(scl)
	, m_game()
	, m_outputSfc(default_graphics_surfaces::surfaces::create_unmanaged_output_surface())
{
	RegisterWindowClass();
}

int rocks_in_space::Win32Win::Run()
{
	RECT rc;
	rc.top = m_x;
	rc.left = m_y;
	rc.right = m_x+ m_w;
	rc.bottom = m_y + m_h;

	// Adjust the window size for correct device size
	if (!AdjustWindowRect(&rc, (WS_OVERLAPPEDWINDOW | WS_VISIBLE), FALSE)) {
		throw_system_error_for_GetLastError(GetLastError(), "Failed call to AdjustWindowRect.");
	}

	long lwidth = rc.right - rc.left;
	long lheight = rc.bottom - rc.top;

	long lleft = 10;
	long ltop = 10;

	const wchar_t* winTitle = L"RocksInSpace with Existing Window!";

	// Create an instance of the window
	m_hwnd = CreateWindowEx(
		static_cast<DWORD>(0),				// extended style
		winClassName,						// class name
		winTitle,							// instance title
		(WS_OVERLAPPEDWINDOW | WS_VISIBLE),	// window style
		lleft, ltop,						// initial x, y
		lwidth,								// initial width
		lheight,							// initial height
		static_cast<HWND>(nullptr),			// handle to parent
		static_cast<HMENU>(nullptr),		// handle to menu
		static_cast<HINSTANCE>(nullptr),	// instance of this application
		static_cast<LPVOID>(this));			// extra creation parms

	if (m_hwnd == nullptr) {
		throw_system_error_for_GetLastError(GetLastError(), "Failed call to CreateWindowEx.");
	}

	SetLastError(ERROR_SUCCESS);
	if (SetWindowLongPtrW(m_hwnd, 0, reinterpret_cast<LONG_PTR>(this)) == 0) {
		// SetWindowLongPtr is weird in terms of how it fails. See its documentation. Hence this weird check.
		DWORD lastError = GetLastError();
		if (lastError != ERROR_SUCCESS) {
			throw_system_error_for_GetLastError(lastError, "Failed call to SetWindowLongPtrW(HWND, int, LONG_PTR) in cairo_display_surface::cairo_display_surface(int, int, format, int, int, scaling)");
		}
	}

	// Initially display the window
	ShowWindow(m_hwnd, SW_SHOWNORMAL);
	UpdateWindow(m_hwnd);

	MSG msg{};
	msg.message = WM_NULL;

	while (msg.message != WM_QUIT)
	{
		if (!PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
		{
			RECT clientRect;
			GetClientRect(m_hwnd, &clientRect);
			int width = clientRect.right - clientRect.left;
			int height = clientRect.bottom - clientRect.top;
			const auto& data = *m_outputSfc.data();
			if (width != data.data.display_dimensions.x() || height != data.data.display_dimensions.y())
				//if (width != m_outputSfc.display_dimensions().x() || height != m_outputSfc.display_dimensions().y())
			{
				// If there is a size mismatch we skip painting and resize the window instead.
				auto displayDimensions = display_point{ width, height };
				m_outputSfc.display_dimensions(displayDimensions);
				
				if (display_point{ width, height } != data.data.display_dimensions)//m_outputSfc.dimensions())
				{
					if (m_outputSfc.has_size_change_callback())
					{
						m_outputSfc.invoke_size_change_callback();
					}
				}
				continue;
			}
			else
			{
				if (m_canDraw && m_outputSfc.has_draw_callback())
				{
					m_outputSfc.clear();
					m_outputSfc.invoke_draw_callback();
					m_outputSfc.draw_to_output();
				}
			}
		}
		else
		{
			if (msg.message != WM_QUIT)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	return static_cast<int>(msg.wParam);
}
