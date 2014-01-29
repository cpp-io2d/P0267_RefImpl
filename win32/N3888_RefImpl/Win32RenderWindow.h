
#ifndef _WIN32RENDERWINDOW_
#define _WIN32RENDERWINDOW_

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <string>

class Win32RenderWindow
{
public:

	Win32RenderWindow( unsigned int width, unsigned int height, const std::wstring& caption );
	~Win32RenderWindow();

	LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	HWND handle;
};

#endif // _WIN32RENDERWINDOW_