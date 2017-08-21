#pragma once

#ifndef _XIO2D_
#define _XIO2D_

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
namespace std::experimental::io2d {
	inline namespace v1 {
		enum class _Round_floating_point_to_zero_sfinae {};
		constexpr _Round_floating_point_to_zero_sfinae _Round_floating_point_to_zero_sfinae_val{};

		template <class T, enable_if_t<is_floating_point_v<T>, _Round_floating_point_to_zero_sfinae> = _Round_floating_point_to_zero_sfinae_val>
		constexpr T _Round_floating_point_to_zero(const T v) noexcept {
			if ((v > static_cast<T>(0.0F) && v < numeric_limits<T>::epsilon() * 1000.0F) ||
				(v < static_cast<T>(0.0F) && -v < numeric_limits<T>::epsilon() * 1000.0F)) {
				return (v > static_cast<T>(0.0F)) ? static_cast<T>(0.0F) : static_cast<T>(-0.0F);
			}
			return v;
		}
	}
}
