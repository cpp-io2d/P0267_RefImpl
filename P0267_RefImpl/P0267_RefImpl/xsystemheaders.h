#pragma once

// This flag allows the user to include system headers on their own.
// By default Windows.h is included after NOMINMAX and WIN32_LEAN_AND_MEAN are defined.
// For the implementation to work on WIN32, NOMINMAX must be defined. Other options
// are possible.
#if !defined(NO_SYSTEM_HEADERS)

#if defined(USE_XCB)
#include <xcb/xcb.h>

#elif defined(USE_XLIB)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <cairo/cairo-xlib.h>

#elif defined(_WIN32) || defined(_WIN64)
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#endif
