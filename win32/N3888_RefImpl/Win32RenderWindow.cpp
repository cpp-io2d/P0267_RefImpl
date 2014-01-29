
#include "Win32RenderWindow.h"

LRESULT CALLBACK InternalWindowProc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	LONG_PTR ObjPtr = GetWindowLongPtr(hwnd, 0);

	if (ObjPtr == 0) {
        return( DefWindowProc( hwnd, msg, wparam, lparam ) );
	} else {
	    return( reinterpret_cast<Win32RenderWindow*>(ObjPtr)->WindowProc(hwnd, msg, wparam, lparam) );
	}
}



Win32RenderWindow::Win32RenderWindow(unsigned int width, unsigned int height, const std::wstring& caption) :
	handle( 0 )
{
	WNDCLASSEX wc;

	// Setup the window class
	memset(&wc, 0, sizeof(wc));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = InternalWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = sizeof(this);
	wc.hInstance = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"N3888_RefImpl";
	wc.hIconSm = LoadIcon(NULL, IDI_ASTERISK);
	

	// Register the window class
	RegisterClassEx(&wc);

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
		wc.lpszClassName, 					// class name
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


}

Win32RenderWindow::~Win32RenderWindow()
{
	if (handle != 0)
	{
		DestroyWindow(handle);
		handle = 0;
	}
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

		case WM_PAINT:
		{
			// This message is handled by the default handler to avoid a 
			// repeated sending of the message.  This results in the ability
			// to process all pending messages at once without getting stuck
			// in an eternal loop.
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
			//EvtWindowResizePtr pEvent = EvtWindowResizePtr(new EvtWindowResize(hwnd, wparam, lparam));
			//EvtManager.ProcessEvent(pEvent);
		} break;

	}

	return(DefWindowProc(hwnd, msg, wparam, lparam));

}