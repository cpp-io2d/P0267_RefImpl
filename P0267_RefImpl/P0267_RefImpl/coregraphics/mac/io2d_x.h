#ifndef _IO2D_X_
#define _IO2D_X_

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

#define HAVE_FILESYSTEM
#include <experimental/filesystem>
namespace std::filesystem {
    using path = ::std::experimental::filesystem::path;
}

#include "../../xio2d.h"
#include "../../xbrushes.h"
#include "../../xcolor.h"
#include "../../xdiagnostics.h"
#include "../../xgraphicsmath.h"
#include "../../xgraphicsmathfloat.h"
#include "../../xinput.h"
#include "../../xio2d.h"
#include "../../xpath.h"
#include "../../xsurfaces_enums.h"
#include "../../xsurfaces.h"
#include "../../xtext.h"

#include "../../xbrushes_impl.h"
#include "../../xgraphicsmath_impl.h"
#include "../../xgraphicsmathfloat_impl.h"
#include "../../xio2d_impl.h"
#include "../../xpath_impl.h"
#include "../../xpathbuilder_impl.h"
#include "../../xsurfaces_impl.h"
#include "../../xsurfacesprops_impl.h"

#endif

