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

// Everything in the Draw function should be portable C++ code.
void Draw(surface& surface) {
	// Create a context that will draw to our surface.
	auto context = drawing::context(surface);

	// The is a demonstration of how a raster_source_pattern works. We create one that is 100px x 100px
	//auto pattern = raster_source_pattern(nullptr, content::color_alpha, 100, 100);
	//pattern.set_acquire(
	//	[pattern](void*, experimental::drawing::surface& target, const rectangle_int& extents) -> experimental::drawing::surface
	//{
	//	auto result = experimental::drawing::image_surface(target, format::rgb24, extents.width - extents.x, extents.height - extents.y);
	//	vector<unsigned char> data;
	//	const auto dataSize = result.get_stride() * result.get_height();
	//	data.resize(dataSize);
	//	for (auto i = 0; i < dataSize; i += 4) {
	//		data[i + 0] = 255ui8;
	//		data[i + 1] = 0ui8;
	//		data[i + 2] = 0ui8;
	//		data[i + 3] = 0ui8;
	//	}
	//	result.set_data(data);
	//	return result;
	//},
	//	nullptr
	//	);
	//pattern.set_extend(extend::repeat);
	//context.set_source(pattern);
	//context.paint();

	context.save();
	auto scp = solid_color_pattern(0.0, 0.0, 1.0);
	context.set_source(scp);
	context.paint();
	context.restore();

	context.save();
	const int width = 100;
	const int height = 100;
	const format fmt = format::rgb24;
	const int stride = format_stride_for_width(fmt, width);
	vector<unsigned char> data;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < stride; x++) {
			auto byte = x % 4;
			switch (byte)
			{
			case 0:
				data.push_back(0x7Fui8);
				break;
			case 1:
				data.push_back(0xFFui8);
				break;
			case 2:
				data.push_back(0ui8);
				break;
			case 3:
				data.push_back(0ui8);
				break;
			default:
				throw logic_error("We're MODing by 4, how do we have a value outside of [0,3]?");
			}
		}
	}
	auto imageSurfaceFromData = image_surface(data, fmt, width, height, stride);
	context.set_source_surface(imageSurfaceFromData, 400.0, 400.0);
	context.move_to(400.0, 400.0);
	context.rel_line_to(100.0, 0.0);
	context.rel_line_to(0.0, 100.0);
	context.rel_line_to(-100.0, 0.0);
	context.close_path();
	context.fill();
	imageSurfaceFromData.finish();
	context.restore();

	context.save();
	auto surfaceForContext2 = image_surface(format::argb32, 100, 100);
	auto context2 = drawing::context(surfaceForContext2);
	context2.set_source_rgba(0.5, 0.5, 0.5, 0.5);
	context2.set_compositing_operator(compositing_operator::clear);
	context2.paint_with_alpha(0.0);
	context2.set_source_rgba(0.5, 0.5, 0.5, 0.5);
	context2.set_compositing_operator(compositing_operator::add);
	context2.paint();
	surfaceForContext2.flush();
	context.set_source_surface(surfaceForContext2, 600.0, 400.0);
	context.move_to(600.0, 400.0);
	context.rel_line_to(100.0, 0.0);
	context.rel_line_to(0.0, 100.0);
	context.rel_line_to(-100.0, 0.0);
	context.close_path();
	context.fill();
	context.set_source_surface(surfaceForContext2, 650.0, 400.0);
	context.move_to(650.0, 400.0);
	context.rel_line_to(100.0, 0.0);
	context.rel_line_to(0.0, 100.0);
	context.rel_line_to(-100.0, 0.0);
	context.close_path();
	context.fill();
	context.restore();

	context.save();
	auto subsurface = drawing::surface(surface, 10.5, 11.0, 50.0, 50.0);
	auto subcontext = drawing::context(subsurface);
	subcontext.set_source_rgb(0.0, 0.0, 0.0);
	subcontext.move_to(2.0, 2.0);
	subcontext.rel_line_to(48.0, 0.0);
	subcontext.set_line_width(3.0);
	subcontext.set_line_cap(line_cap::butt);
	subcontext.stroke();
	context.restore();

	context.save();
	matrix m;
	m.init_translate(300.0, 400.0);
	const double two_pi = 3.1415926535897932 * 2.0;
	m.rotate(two_pi * ((GetTickCount64() % 4000) / 4000.0));
	context.set_matrix(m);
	context.new_path();
	context.move_to(-100.0, 0.0);
	context.line_to(100.0, 0.0);
	context.line_to(0.0, 200.0);
	context.close_path();
	context.set_line_width(3.0);
	context.set_dash({ 0.0, 10.0 }, 0.0);
	context.set_line_cap(line_cap::round);

	// Create a copy of the path because when we call fill it clears from the context.
	auto path = context.copy_path();
	context.set_source_rgb(1.0, 0.0, 0.0);
	context.fill();

	// Use the same path so that we can outline it.
	context.append_path(path);
	context.set_source_rgb(0.0, 0.0, 0.0);
	context.stroke();
	context.restore();

	context.set_source_rgb(1.0, 1.0, 1.0);
	context.move_to(100.0, 100.0);
	context.select_font_face("Segoe UI", font_slant::normal, font_weight::normal);
	context.set_font_size(30.0);
	context.show_text("Hello C++!");
}


int WINAPI wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR lpCmdLine,
	_In_ int nCmdShow
	) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

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

	Win32RenderWindow window( 320, 240, L"N3888_RefImpl Main Window" );

	// Main message loop:
	while (msg.message != WM_QUIT) 
	{
		if (!PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {

			// Draw to the off-screen buffer.
			Draw(*window.g_psurface);

			// Flush to ensure that it is drawn to the window.
			window.g_psurface->flush();
			auto hdc = GetDC(window.GetHandle());
			{
				auto surface = make_surface(cairo_win32_surface_create(hdc));
				auto ctxt = context(surface);
				ctxt.set_source_surface(*window.g_psurface, 0.0, 0.0);
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