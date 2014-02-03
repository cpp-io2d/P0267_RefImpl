
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
using namespace std::experimental::drawing;
using namespace Microsoft::WRL;

Win32RenderWindow::Win32RenderWindow(unsigned int width, unsigned int height, const std::wstring& caption) :
	handle( 0 )
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

	if ( handle != 0 ) {
		// Set in the "extra" bytes the pointer to the 'this' pointer
		// so it can handle messages for itself.
		SetWindowLongPtr( handle, 0, (LONG_PTR)this);

		// Initially display the window
		ShowWindow(handle, SW_SHOWNORMAL);
		UpdateWindow(handle);
	}

	// Create the initial surface for drawing to.
	g_psurface = unique_ptr<surface>(new surface(move(make_surface(format::argb32, lwidth, lheight))));
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


LRESULT Win32RenderWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_CREATE:
		{
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
			auto width = lparam & 0xFFFF;
			auto height = (lparam & 0xFFFF0000) >> 16;

			g_psurface = unique_ptr<surface>(new surface(move(make_surface(format::argb32, width, height))));

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
			//g_doNotPaint = true; // Don't paint while resizing to avoid flicker.
			return DefWindowProc(handle, msg, wparam, lparam);
		} break;

		case WM_EXITSIZEMOVE:
		{
			//g_doNotPaint = false;
			return DefWindowProc(handle, msg, wparam, lparam);
		} break;

		case WM_PAINT:
		{
			//if (!g_doNotPaint) {
			//	OnPaint(handle, msg, wparam, lparam);
			//}
			PAINTSTRUCT ps;
			HDC hdc;

			// Flush to ensure that it is drawn to the window.
			hdc = BeginPaint(handle, &ps); 
			g_psurface->flush();

			auto surface = make_surface(cairo_win32_surface_create(hdc));
			auto ctxt = context(surface);
			ctxt.set_source_surface(*g_psurface, 0.0, 0.0);
			ctxt.paint();
			surface.flush();
			EndPaint(handle, &ps);
		} break;
	}

	return(DefWindowProc(hwnd, msg, wparam, lparam));

}

void Win32RenderWindow::ShowSaveAsPNGDialog() {

	ComPtr<IFileSaveDialog> fsd;
	throw_if_failed_hresult<logic_error>(
		CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&fsd)), "Failed call to CoCreateInstance for IFileSaveDialog.");

	FILEOPENDIALOGOPTIONS fodOptions{};
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
