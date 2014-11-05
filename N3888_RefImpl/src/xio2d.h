#pragma once

#ifndef _XIO2D_
#define _XIO2D_

#if defined(_WIN32_WINNT)
// Implementation detail headers
#include "cairo.h"
#else
#include <cairo.h>
#endif

#include <map>
#include <cassert>
#include <cstdint>
#include <tuple>
#include <mutex>
#include <cmath>

// Designed to be used to conditionally define compiler support for inline namespaces using a #if
#define _Inline_namespace_conditional_support_test ((__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190021510))

// Designed to be used to conditionally define compiler support for UDLs using a #if
#define _User_defined_literal_conditional_support_test ((__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190022203))

// Designed to be used to conditionally define compiler support for noexcept using a #if
#define _Noexcept_conditional_support_test ((__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190022203))

// Designed to be used to conditionally define compiler support for constexpr using a #if
#define _Constexpr_conditional_support_test ((__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190022203))
#endif
