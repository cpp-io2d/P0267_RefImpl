
#ifndef _WIN32RENDERWINDOW_
#define _WIN32RENDERWINDOW_

#define WIN32_LEAN_AND_MEAN			 // Exclude rarely-used stuff from Windows headers
#define NOMINMAX
#include <windows.h>
#include <string>
#include "io2d.h"
#include <memory>

class Win32RenderWindow
{
public:

	Win32RenderWindow(unsigned int width, unsigned int height, const std::wstring& caption);
	~Win32RenderWindow();

	HWND GetHandle();

	LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	void ShowSaveAsPNGDialog();

	::std::shared_ptr<::std::experimental::io2d::image_surface>& GetSurface();

private:
	HWND handle;
	unsigned int m_width;
	unsigned int m_height;
	::std::shared_ptr<::std::experimental::io2d::image_surface> m_imageSurface;
};

#endif // _WIN32RENDERWINDOW_