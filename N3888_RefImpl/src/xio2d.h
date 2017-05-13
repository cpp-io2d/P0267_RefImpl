#pragma once

#ifndef _XIO2D_
#define _XIO2D_

#include <cairo.h>
#include <map>
#include <cassert>
#include <cstdint>
#include <tuple>
#include <mutex>
#include <cmath>
#include <utility>
#include <stack>
#include <array>
#include <sstream>
#include <ios>

#if ((defined(_MSC_VER) && ((_MSC_VER >= 1910) || (defined(__clang__) && (_MSC_VER >= 1900)))) || defined(HAVE_FILESYSTEM))
#define _Filesystem_support_test
#endif
// Designed to be used to conditionally define compiler support for inline namespaces using a #if
//define _Inline_namespace_conditional_support_test ((__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190022609))

// Designed to be used to conditionally define compiler support for UDLs using a #if
//define _User_defined_literal_conditional_support_test ((__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190022203))

// Designed to be used to conditionally define compiler support for noexcept using a #if
//define _Noexcept_conditional_support_test ((__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190022203))

// Designed to be used to conditionally define compiler support for constexpr using a #if
//define _Constexpr_conditional_support_test ((__cplusplus >= 201103L) || (_MSC_FULL_VER >= 190022203))

//define _Variable_templates_conditional_support_test ((__cplusplus >= 201402L) || _MSC_FULL_VER >= 190023918)
#endif
