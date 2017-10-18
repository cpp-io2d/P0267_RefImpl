#pragma once

#ifndef _IO2D_
#define _IO2D_

#define __cpp_lib_experimental_io2d 201710

#include <memory>
#include <functional>
#include <utility>
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
#include "xgraphicsmathfloat.h"

#include "xio2d_impl.h"
#include "xbrushes_impl.h"
#include "xsurfaces_impl.h"
#include "xsurfacesprops_impl.h"
#include "xgraphicsmath_impl.h"
#include "xgraphicsmathfloat_impl.h"

#endif
