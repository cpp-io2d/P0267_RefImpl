#pragma once
#include "drawing.h"

inline void _Throw_if_failed_status(::std::experimental::drawing::status s) {
	if (s != ::std::experimental::drawing::status::success) {
		throw ::std::experimental::drawing::drawing_exception(s);
	}
}

inline int _Double_to_int(double value, bool truncate = false) {
    if (truncate) {
        return static_cast<int>(value);
    }
    return value >= 0.0 ? (static_cast<int>(value + 0.5)) : (static_cast<int>(value - 0.5));
}

