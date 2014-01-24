// entrypoint-win32.cpp : Defines the entry point for the application.
//

#include "entrypoint-win32.h"

#include "cairo.h"
#include "cairo-win32.h"

#include <memory>
#include <functional>
#include <wrl.h>
#include "throw_helpers.h"
#include "drawing.h"

using namespace Microsoft::WRL;
using namespace std;
using namespace std::experimental;
using namespace std::experimental::drawing;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
unique_ptr<surface> g_psurface;

// Everything in the Draw function should be portable C++ code.
void Draw(surface& surface) {
	// Create a context that will draw to our surface.
	auto context = drawing::context(surface);

	// The is a demonstration of how a raster_source_pattern works. We create one that is 100px x 100px
	auto pattern = raster_source_pattern(nullptr, content::color_alpha, 100, 100);
	pattern.set_acquire(
		[pattern](void*, experimental::drawing::surface& target, const rectangle_int& extents) -> experimental::drawing::surface
	{
		auto result = experimental::drawing::image_surface(target, format::rgb24, extents.width - extents.x, extents.height - extents.y);
		vector<unsigned char> data;
		const auto dataSize = result.get_stride() * result.get_height();
		data.resize(dataSize);
		for (auto i = 0; i < dataSize; i += 4) {
			data[i + 0] = 255ui8;
			data[i + 1] = 0ui8;
			data[i + 2] = 0ui8;
			data[i + 3] = 0ui8;
		}
		result.set_data(data);
		return result;
	},
		nullptr
		);
	pattern.set_extend(extend::repeat);
	context.set_source(pattern);
	context.paint();

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

	//surface.finish();
}

void OnPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(message);
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(hWnd, &ps);

	// To enable screenshot saving, we are using a global unique_ptr surface. I did not rewrite the boilerplate
	// Win32 code so that it'd be a class, hence the globals. Note that this would not work without using CS_OWNDC
	// when registering the window class since we could get a different HDC each time without that flag.
	if (g_psurface == nullptr) {
		g_psurface = unique_ptr<surface>(new surface(move(make_surface(cairo_win32_surface_create(hdc)))));
	}

	// Draw to the off-screen buffer.
	Draw(*g_psurface);

	// Flush to ensure that it is drawn to the window.
	g_psurface->flush();

	EndPaint(hWnd, &ps);
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

	HWND hWnd;
	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow, hWnd)) {
		CoUninitialize();
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_N3888_REFIMPL));

	// Main message loop:
	while (msg.message != WM_QUIT) {
		if (!PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			// No message so redraw the window.
			RedrawWindow(hWnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
		}
		else {
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEX wcex{ };

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_N3888_REFIMPL));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_N3888_REFIMPL);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND& hWnd) {
	//HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd) {
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

void ShowSaveAsPNGDialog() {
	ComPtr<IFileSaveDialog> fsd;
	throw_if_failed_hresult<logic_error>(
		CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&fsd)), "Failed call to CoCreateInstance for IFileSaveDialog.");

	FILEOPENDIALOGOPTIONS fodOptions{ };
	throw_if_failed_hresult<logic_error>(
		fsd->GetOptions(&fodOptions), "Failed call to IFileDialog::GetOptions.");
	throw_if_failed_hresult<logic_error>(
		fsd->SetOptions(fodOptions | FOS_FORCEFILESYSTEM | FOS_OVERWRITEPROMPT | FOS_PATHMUSTEXIST), "Failed call to IFileDialog::SetOptions.");

	const COMDLG_FILTERSPEC filterSpec[] = {
		{ L"PNG", L".png" }
	};
	throw_if_failed_hresult<logic_error>(
		fsd->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec), "Failed call to IFileDialog::SetFileTypes.");
	throw_if_failed_hresult<logic_error>(
		fsd->SetFileTypeIndex(1U), "Failed call to IFileDialog::SetFileTypeIndex.");
	throw_if_failed_hresult<logic_error>(
		fsd->SetDefaultExtension(L"png"), "Failed call to IFileDialog::SetDefaultExtension.");

	ComPtr<IKnownFolderManager> kfm;
	throw_if_failed_hresult<logic_error>(
		CoCreateInstance(CLSID_KnownFolderManager, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&kfm)), "Failed call to CoCreateInstance for IKnownFolderManager.");
	ComPtr<IKnownFolder> picturesKnownFolder;
	throw_if_failed_hresult<logic_error>(
		kfm->GetFolder(FOLDERID_Pictures, &picturesKnownFolder), "Failed call to IKnownFolderManager::GetFolder.");
	ComPtr<IShellItem> picturesShellItem;
	throw_if_failed_hresult<logic_error>(
		picturesKnownFolder->GetShellItem(0, IID_PPV_ARGS(&picturesShellItem)), "Failed call to IKnownFolder::GetShellItem.");

	throw_if_failed_hresult<logic_error>(
		fsd->SetDefaultFolder(picturesShellItem.Get()), "Failed call to IFileDialog::SetDefaultFolder.");

	HRESULT hr;
	hr = fsd->Show(nullptr);
	if (SUCCEEDED(hr)) {
		// The user picked a file.
		ComPtr<IShellItem> result;
		throw_if_failed_hresult<logic_error>(
			fsd->GetResult(&result), "Failed call to IFileDialog::GetResult.");
		wstring wfilename;
		PWSTR pwstrFilename = nullptr;
		throw_if_failed_hresult<logic_error>(
			result->GetDisplayName(SIGDN_FILESYSPATH, &pwstrFilename), "Failed call to IShellItem::GetDisplayName.");
		try {
			wfilename = pwstrFilename;
			CoTaskMemFree(pwstrFilename);
		}
		catch (...) {
			CoTaskMemFree(pwstrFilename);
			throw;
		}
		HANDLE hFile = CreateFile2(wfilename.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, CREATE_ALWAYS, nullptr);
		if (hFile == INVALID_HANDLE_VALUE) {
			throw_get_last_error<runtime_error>("Failed call to CreateFile2.");
		}
		if (CloseHandle(hFile) == 0) {
			throw_get_last_error<runtime_error>("Failed call to CloseHandle.");
		}
		auto bufferSize = GetShortPathNameW(wfilename.c_str(), nullptr, 0);
		wstring wshortfilename;
		wshortfilename.resize(bufferSize);
		if (GetShortPathNameW(wfilename.c_str(), &wshortfilename[0], bufferSize) == 0) {
			throw_get_last_error<runtime_error>("Failed call to GetShortPathNameW.");
		}
		char defaultChar = '*';
		BOOL usedDefault = FALSE;
		auto mbBufferSize = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wshortfilename.c_str(), -1, nullptr, 0, &defaultChar, &usedDefault);
		string mbFileName;
		usedDefault = FALSE;
		mbFileName.resize(mbBufferSize);
		if (WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, wshortfilename.c_str(), -1, &mbFileName[0], mbBufferSize, &defaultChar, &usedDefault) == 0) {
			throw_get_last_error<runtime_error>("Failed call to WideCharToMultiByte.");
		}
		if (usedDefault != FALSE) {
			throw runtime_error("Could not convert short filename string to multibyte from wide character.");
		}
		g_psurface->write_to_png(mbFileName);
	}
	else {
		if (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED)) {
			// Do nothing. The user clicked cancel.
		}
		else {
			throw_if_failed_hresult<logic_error>(hr, "Failed call to IModalWindow::Show.");
		}
	}

}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int wmId, wmEvent;

	switch (message) {
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId) {
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_EDIT_SCREENCAPTURE:
			ShowSaveAsPNGDialog();
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		OnPaint(hWnd, message, wParam, lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
