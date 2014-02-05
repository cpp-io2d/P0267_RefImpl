// entrypoint-win32.cpp : Defines the entry point for the application.
//

#include "entrypoint-win32.h"

#include "cairo.h"
#include "cairo-win32.h"

#include <memory>
#include <functional>
#include <atomic>
#include <wrl.h>
#include "throw_helpers.h"
#include "drawing.h"
#include "Win32RenderWindow.h"
#include "sample_draw.h"

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

using namespace Microsoft::WRL;
using namespace std;
using namespace std::experimental;
using namespace std::experimental::drawing;

#define MAX_LOADSTRING 100


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR lpCmdLine,
	_In_ int nCmdShow
	) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
	
	throw_if_failed_hresult<runtime_error>(
		CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED), "Failed call to CoInitializeEx."
		);
	MSG msg{ };
	msg.message = WM_NULL;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_N3888_REFIMPL, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);


	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_N3888_REFIMPL));

	Win32RenderWindow window(800, 600, L"N3888_RefImpl Main Window");

	// Main message loop:
	while (msg.message != WM_QUIT) 
	{
		if (!PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			// Draw to the off-screen buffer.
			sample_draw sampleDraw;
			auto& renderTarget = *window.GetSurface();
			auto rtCtxt = context(renderTarget);
			sampleDraw(rtCtxt, static_cast<double>(GetTickCount64()));

			// Flush to ensure that it is drawn to the window.
			window.GetSurface()->flush();
			auto hdc = GetDC(window.GetHandle());
			{
				auto surface = make_surface(cairo_win32_surface_create(hdc));
				auto ctxt = context(surface);
				ctxt.set_source_surface(*window.GetSurface(), 0.0, 0.0);
				ctxt.paint();
				surface.flush();
			}
			ReleaseDC(window.GetHandle(), hdc);
		}
		else
		{
			if (msg.message != WM_QUIT) {
				if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}
	CoUninitialize();
	return (int)msg.wParam;
}

//
// FUNCTION: CommonWindowProc
//
// PURPOSE: Provides a simple message processor which attempts to call the handler member
//          of the Win32RenderWindow class.
//

LRESULT CALLBACK CommonWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	LONG_PTR ObjPtr = GetWindowLongPtr(hwnd, 0);

	if (ObjPtr == 0) {
		return(DefWindowProc(hwnd, msg, wparam, lparam));
	}
	else {
		return(reinterpret_cast<Win32RenderWindow*>(ObjPtr)->WindowProc(hwnd, msg, wparam, lparam));
	}
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex{ };

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = 0;
	wcex.lpfnWndProc = CommonWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(Win32RenderWindow*);
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_N3888_REFIMPL));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_N3888_REFIMPL);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}