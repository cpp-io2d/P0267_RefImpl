#pragma once
#include "drawing.h"

inline void _Throw_if_failed_status(::std::experimental::drawing::status s) {
	if (s != ::std::experimental::drawing::status::success) {
		throw ::std::experimental::drawing::drawing_exception(s);
	}
}
