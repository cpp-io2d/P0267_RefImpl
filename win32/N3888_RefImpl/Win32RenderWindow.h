
#ifndef _WIN32RENDERWINDOW_
#define _WIN32RENDERWINDOW_

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>

class Win32RenderWindow
{
public:

	Win32RenderWindow( unsigned int width, unsigned int height );
	~Win32RenderWindow();

	LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	HWND handle;
};

#endif // _WIN32RENDERWINDOW_