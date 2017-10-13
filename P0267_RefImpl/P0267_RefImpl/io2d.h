#pragma once

#ifndef _IO2D_
#define _IO2D_

#define __cpp_lib_experimental_io2d 201710

#include <memory>
#include <functional>
#include <exception>
#include <vector>
#include <string>
#include <algorithm>
#include <system_error>
#include <cstdint>
#include <atomic>
#include <variant>
#include <optional>
#include <cmath>
#include <type_traits>
#include <initializer_list>
#include <cmath>
#include <chrono>

#include "xio2d.h"

#if defined(_Filesystem_support_test)
#include <filesystem>
#endif

#include "xcolor.h"
#include "xlinear_algebra.h"
#include "xtext.h"
#include "xpath.h"
#include "xbrushes.h"
#include "xsurfaces.h"
#include "xinput.h"

//namespace std {
//	namespace experimental {
//		namespace io2d {
//			inline namespace v1 {
//				//int format_stride_for_width(format fmt, int width) noexcept;
//
//				//template <class GraphicsMath, class T>
//				//display_surface<GraphicsMath, T> make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, scaling scl = scaling::letterbox);
//
//				//template <class GraphicsMath, class T>
//				//display_surface<GraphicsMath, T> make_display_surface(int preferredWidth, int preferredHeight, format preferredFormat, error_code& ec, scaling scl = scaling::letterbox) noexcept;
//
//				//template <class GraphicsMath, class T, class U>
//				//handler<T> make_handler(display_surface<GraphicsMath, U>&, int preferredDisplayWidth, int preferredDisplayHeight, refresh_rate rr = refresh_rate::as_fast_as_possible, float fps = 30.0f);
//
//				//template <class GraphicsMath, class T, class U>
//				//handler<T> make_handler(display_surface<GraphicsMath, U>&, int preferredDisplayWidth, int preferredDisplayHeight, error_code& ec, refresh_rate rr = refresh_rate::as_fast_as_possible, float fps = 30.0f) noexcept;
//
//				//template <class GraphicsMath, class T>
//				//image_surface<GraphicsMath, T> make_image_surface(format format, int width, int height);
//
//				//template <class GraphicsMath, class T>
//				//image_surface<GraphicsMath, T> make_image_surface(format format, int width, int height, error_code& ec) noexcept;
//
//				//template <class GraphicsMath, class T>
//				//image_surface<GraphicsMath, T> copy_image_surface(image_surface<GraphicsMath, T>& sfc) noexcept;
//
//			}
//		}
//	}
//}

#include "xio2d_impl.h"
#include "xsurfaces_impl.h"
#include "xsurfacesprops_impl.h"
#endif
