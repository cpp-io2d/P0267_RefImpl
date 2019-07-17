#include <mutex>
#include "xio2d_qt_win32_main.h"

static ::std::once_flag _Create_qguiapplication_once_flag;

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Qt_io2d {
			void _Qt_gui_app_init(::std::unique_ptr<QGuiApplication>& gui_app) {
				::std::call_once(_Create_qguiapplication_once_flag, [&gui_app]() {
					// Must have a QGuiApplication before using anything related to Qt's GUI module (e.g. QRasterWindow).
					int argc = 0;
					gui_app = make_unique<QGuiApplication>(argc, nullptr);
					});
			}
		}
	}
}

#if defined BUILD_IO2D_API_DLL
BOOL WINAPI DllMain(_In_ HINSTANCE /*hinstDLL*/, _In_ DWORD /*fdwReason*/, _In_ LPVOID /*lpvReserved*/)
{
	return TRUE;
}
#endif
