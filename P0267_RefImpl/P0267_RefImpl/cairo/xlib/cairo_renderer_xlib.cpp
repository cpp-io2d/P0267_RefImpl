#include "xio2d_cairo_xlib_main.h"

namespace std::experimental::io2d {
	inline namespace v1 {
		namespace _Cairo {
            
            using output_surface = basic_output_surface<_Cairo::_Cairo_graphics_surfaces<_Graphics_math_float_impl>>;

			int _Xlib_unmanaged_close_display(Display*) {
				// Do nothing. We don't own the display.
				return 0;
			}

			Bool _X11_if_xev_pred(::Display* display, ::XEvent* xev, XPointer arg) {
				assert(display != nullptr && xev != nullptr && arg != nullptr);
				auto sfc = reinterpret_cast<output_surface*>(arg);
				// If the display_surface window is invalid, we will never get a match so return False.
				if (sfc->data()->data.wndw == None) {
					return False;
				}
				// Need to check for ExposureMask xevs, StructureNotifyMask xevs, and unmaskable xevs.
				switch (xev->type) {
				// ExposureMask xevs:
				case Expose:
				{
					if (xev->xexpose.window == sfc->data()->data.wndw) {
						return True;
					}
				} break;
				// StructureNotifyMask xevs:
				case CirculateNotify:
				{
					if (xev->xcirculate.window == sfc->data()->data.wndw) {
						return True;
					}
				} break;
				case ConfigureNotify:
				{
					if (xev->xconfigure.window == sfc->data()->data.wndw) {
						return True;
					}
				} break;
				case DestroyNotify:
				{
					if (xev->xdestroywindow.window == sfc->data()->data.wndw) {
						return True;
					}
				} break;
				case GravityNotify:
				{
					if (xev->xgravity.window == sfc->data()->data.wndw) {
						return True;
					}
				} break;
				case MapNotify:
				{
					if (xev->xmap.window == sfc->data()->data.wndw) {
						return True;
					}
				} break;
				case ReparentNotify:
				{
					if (xev->xreparent.window == sfc->data()->data.wndw) {
						return True;
					}
				} break;
				case UnmapNotify:
				{
					if (xev->xunmap.window == sfc->data()->data.wndw) {
						return True;
					}
				} break;
				// Might get them even though unrequested xevs (see http://www.x.org/releases/X11R7.7/doc/libX11/libX11/libX11.html#Event_Masks ):
				case GraphicsExpose:
				{
					if (xev->xgraphicsexpose.drawable == static_cast<Drawable>(sfc->data()->data.wndw)) {
						return True;
					}
				} break;
				case NoExpose:
				{
					if (xev->xnoexpose.drawable == static_cast<Drawable>(sfc->data()->data.wndw)) {
						return True;
					}
				} break;
				// Unmasked xevs
				case ClientMessage:
				{
					if (xev->xclient.window == sfc->data()->data.wndw) {
						return True;
					}
				} break;
				case MappingNotify:
				{
					if (xev->xmapping.window == sfc->data()->data.wndw) {
						return True;
					}
				} break;
				case SelectionClear:
				{
					if (xev->xselectionclear.window == sfc->data()->data.wndw) {
						return True;
					}
				} break;
				case SelectionNotify:
				{
					if (xev->xselection.requestor == sfc->data()->data.wndw) {
						return True;
					}
				} break;
				case SelectionRequest:
				{
					if (xev->xselectionrequest.owner == sfc->data()->data.wndw) {
						return True;
					}
				} break;
				default:
				{
					// Per the X protocol, types 64 through 127 are reserved for extensions.
					// We only care about non-extension xevs since we likely should be aware of those and should handle them.
					// So we only return True if it is not an extension xev.
					if (xev->type < 64 || xev->type > 127) {
						// Return True so we can inspect it in the xev loop for diagnostic purposes.
						return True;
					}
					return false;
				}
				}
				return False;
			}
		}
	}
}
