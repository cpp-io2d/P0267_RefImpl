
#include "Win32RenderWindow.h"
#include "resource.h"
#include <Unknwn.h>
#include <ShObjIdl.h>
#include <KnownFolders.h>
#include <shellapi.h>
#include "throw_helpers.h"
#include "cairo.h"
#include "cairo-win32.h"
#include <memory>
#include <functional>
#include <atomic>
#include <wrl.h>

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;
using namespace Microsoft::WRL;

Win32RenderWindow::Win32RenderWindow(unsigned int width, unsigned int height, const std::wstring& caption) :
handle(nullptr),
m_width(width),
m_height(height),
m_imageSurface(nullptr)
{
	// Record the desired client window size
	RECT rc;
	rc.top = rc.left = 0;
	rc.right = width;
	rc.bottom = height;

	// Adjust the window size for correct device size
	AdjustWindowRect(&rc, (WS_OVERLAPPEDWINDOW | WS_VISIBLE), FALSE);

	long lwidth = rc.right - rc.left;
	long lheight = rc.bottom - rc.top;

	long lleft = 10;
	long ltop = 10;


	// Create an instance of the window
	handle = CreateWindowEx(
		NULL,								// extended style
		L"N3888_RefImpl", 					// class name
		caption.c_str(),					// instance title
		(WS_OVERLAPPEDWINDOW | WS_VISIBLE),	// window style
		lleft, ltop,						// initial x, y
		lwidth,								// initial width
		lheight,							// initial height
		NULL,								// handle to parent 
		NULL,								// handle to menu
		NULL,								// instance of this application
		NULL);								// extra creation parms

	if (handle == nullptr) {
		throw_get_last_error<logic_error>("Failed call to CreateWindowEx.");
	}

	// Create the initial surface for drawing to.
	m_imageSurface = make_shared<image_surface>(format::argb32, width, height);
	// Set in the "extra" bytes the pointer to the 'this' pointer
	// so it can handle messages for itself.
	SetWindowLongPtr(handle, 0, (LONG_PTR)this);

	// Initially display the window
	ShowWindow(handle, SW_SHOWNORMAL);
	UpdateWindow(handle);
}

Win32RenderWindow::~Win32RenderWindow()
{
	if (handle != 0)
	{
		DestroyWindow(handle);
		handle = 0;
	}
}


HWND Win32RenderWindow::GetHandle()
{
	return(handle);
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
	case WM_NOTIFY:
	{
		PNMLINK pnmLink = reinterpret_cast<PNMLINK>(lParam);
		if ((pnmLink->hdr.idFrom == IDC_SYSLINK1) || (pnmLink->hdr.idFrom == IDC_SYSLINK2)) {
			switch (pnmLink->hdr.code)
			{
			case NM_CLICK:
				// Intentional fall-through.
			case NM_RETURN:
			{
				auto shExecResult = reinterpret_cast<int>(ShellExecute(nullptr, L"open", pnmLink->item.szUrl, nullptr, nullptr, SW_SHOW));
				if (shExecResult <= 32) {
					wstringstream err;
					err << L"Error calling ShellExecute while trying to open the link. Return code: " << to_wstring(shExecResult) << "." << endl;
					MessageBox(hDlg, err.str().c_str(), L"Error opening link", MB_OK | MB_ICONEXCLAMATION);
				}
			}
				return (INT_PTR)TRUE;
			}
		}
	}
		break;
	}
	return (INT_PTR)FALSE;
}

inline void RenderSourceARGB32ToDestRGB24(unsigned int srcWidth, unsigned int srcHeight, unsigned int destWidth, unsigned int destHeight, const vector<unsigned char>& srcData, unsigned int srcStride, vector<unsigned char>& destData, unsigned int destStride) {
	if (srcWidth == destWidth && srcHeight == destHeight) {
		for (auto y = 0U; y < destHeight; y++) {
			for (auto x = 0U; x < destWidth; x++) {
				auto destIdx = y * destStride + x * 3;
				auto srcIdx = y * srcStride + x * 4;
				auto srcAlpha = srcData[srcIdx + 3] / 255.0;
				//destData[destIdx + 0] = static_cast<unsigned char>(::std::min(1.0, ((srcData[destIdx + 0] / 255.0) + ((destData[srcIdx + 0] / 255.0) * (1.0 - srcAlpha))) / srcAlpha) * 255.0);
				//destData[destIdx + 1] = static_cast<unsigned char>(::std::min(1.0, ((srcData[destIdx + 1] / 255.0) + ((destData[srcIdx + 1] / 255.0) * (1.0 - srcAlpha))) / srcAlpha) * 255.0);
				//destData[destIdx + 2] = static_cast<unsigned char>(::std::min(1.0, ((srcData[destIdx + 2] / 255.0) + ((destData[srcIdx + 2] / 255.0) * (1.0 - srcAlpha))) / srcAlpha) * 255.0);
				destData[destIdx + 0] = static_cast<unsigned char>(::std::min(1.0, (((srcData[destIdx + 0] / 255.0) * srcAlpha) + ((destData[srcIdx + 0] / 255.0) * (1.0 - srcAlpha))) / srcAlpha) * 255.0);
				destData[destIdx + 1] = static_cast<unsigned char>(::std::min(1.0, (((srcData[destIdx + 1] / 255.0) * srcAlpha) + ((destData[srcIdx + 1] / 255.0) * (1.0 - srcAlpha))) / srcAlpha) * 255.0);
				destData[destIdx + 2] = static_cast<unsigned char>(::std::min(1.0, (((srcData[destIdx + 2] / 255.0) * srcAlpha) + ((destData[srcIdx + 2] / 255.0) * (1.0 - srcAlpha))) / srcAlpha) * 255.0);
			}
		}
	}
	else {
		// We need to perform sampling
	}
}

void ResizeWindowToClientArea(HWND hwnd, int width, int height) {
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

		width = std::max(200L, (width - crWidth) + wrWidth);
		height = std::max(lheight - height, (height - crHeight) + wrHeight);
		SetWindowPos(hwnd, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
		PostMessageW(hwnd, WM_PAINT, (WPARAM)0, (LPARAM)0);
	}
}

LRESULT Win32RenderWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		ResizeWindowToClientArea(hwnd, m_width, m_height);
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
		m_width = static_cast<unsigned int>(width);
		m_height = static_cast<unsigned int>(height);
		m_imageSurface = make_shared<image_surface>(format::argb32, width, height);

	} break;

	case WM_COMMAND:
	{
		int wmId, wmEvent;

		wmId = LOWORD(wparam);
		wmEvent = HIWORD(wparam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
		{
			auto aboutResult = DialogBox(0, MAKEINTRESOURCE(IDD_ABOUTBOX), handle, About);
			if (aboutResult <= 0) {
				throw_get_last_error<logic_error>("Failed call to DialogBox.");
			}
		} break;

		case ID_EDIT_SCREENCAPTURE:
			ShowSaveAsPNGDialog();
			break;

		case IDM_EXIT:
			DestroyWindow(handle);
			break;

		default:
			return DefWindowProc(handle, msg, wparam, lparam);
		} break;
	} break;

	case WM_ENTERSIZEMOVE:
	{
		return DefWindowProc(handle, msg, wparam, lparam);
	} break;

	case WM_EXITSIZEMOVE:
	{
		return DefWindowProc(handle, msg, wparam, lparam);
	} break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;

		// Flush to ensure that it is drawn to the window.
		hdc = BeginPaint(handle, &ps);
		RECT clientRect;
		GetClientRect(hwnd, &clientRect);
		if (clientRect.right - clientRect.left != static_cast<int>(m_width) || clientRect.bottom - clientRect.top != static_cast<int>(m_height)) {
			EndPaint(hwnd, &ps);
			ResizeWindowToClientArea(hwnd, m_width, m_height);
			break;
		}
		m_imageSurface->flush();

		// cairo_win32_surface_create always returns an rgb24 surface so we need to manually blend the source to the dest since cairo doesn't.
		auto destSurf = make_surface({ cairo_win32_surface_create(hdc), nullptr });
		destSurf.set_pattern(solid_color_pattern_builder(rgba_color::black).get_pattern());
		destSurf.paint();
		destSurf.flush();

		auto& srcSurf = *m_imageSurface;

		srcSurf.save();
		srcSurf.reset_clip();
		{
			auto destImgSurf = destSurf.map_to_image();
			auto srcImgSurf = m_imageSurface->map_to_image();
			auto destFormat = destImgSurf.get_format();
			auto srcFormat = srcImgSurf.get_format();
			if (destFormat != format::rgb24 || srcFormat != format::argb32) {
				srcSurf.unmap_image(srcImgSurf);
				destSurf.unmap_image(destImgSurf);
				int quitCode = 0;
				if (destFormat == format::rgb24) {
					MessageBoxW(hwnd, L"Source format was not format::argb32.", L"Source format error", MB_OK);
					quitCode = 0x10000000 | static_cast<int>(srcFormat);
				}
				else {
					if (srcFormat == format::rgb24) {
						MessageBoxW(hwnd, L"Destination format was not format::rgb24.", L"Destination format error", MB_OK);
						quitCode = 0x20000000 | static_cast<int>(destFormat);
					}
					else {
						MessageBoxW(hwnd, L"Source format was not format::argb32 and destination format was not format::rgb24.", L"Source and destination format error", MB_OK);
						quitCode = 0x40000000 | static_cast<int>(srcFormat) | (static_cast<int>(destFormat) << 4);
					}
				}
				PostQuitMessage(quitCode);
				break;
			}
			auto srcData = srcImgSurf.get_data();
			auto destData = destImgSurf.get_data();
			RenderSourceARGB32ToDestRGB24(static_cast<unsigned int>(srcImgSurf.get_width()), static_cast<unsigned int>(srcImgSurf.get_height()),
				static_cast<unsigned int>(destImgSurf.get_width()), static_cast<unsigned int>(destImgSurf.get_height()),
				srcData, static_cast<unsigned int>(srcImgSurf.get_stride()), destData, static_cast<unsigned int>(destImgSurf.get_stride()));
			destImgSurf.set_data(destData);
			srcSurf.unmap_image(srcImgSurf);
			destSurf.unmap_image(destImgSurf);
		}
		srcSurf.restore();
		//m_imageSurface->write_to_png("D:\\michael\\00testgrph01.png");
		//rs.set_pattern(solid_color_pattern_builder(rgba_color::black).get_pattern());
		//rs.paint();
		//rs.paint(*m_imageSurface);
		destSurf.flush();
		EndPaint(handle, &ps);
	} break;
	}

	return(DefWindowProc(hwnd, msg, wparam, lparam));

}

void Win32RenderWindow::ShowSaveAsPNGDialog() {

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
		HANDLE hFile = CreateFileW(wfilename.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (hFile == INVALID_HANDLE_VALUE) {
			throw_get_last_error<runtime_error>("Failed call to CreateFileW.");
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
		m_imageSurface->write_to_file(mbFileName);
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

shared_ptr<image_surface>& Win32RenderWindow::GetSurface() {
	return m_imageSurface;
}