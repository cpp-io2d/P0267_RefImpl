#pragma once

#ifndef _XDRAWING_
#define _XDRAWING_

#if defined(_WIN32_WINNT)
// Implementation detail headers
#include "cairo.h"
#else
#include <cairo.h>
#endif

#include <map>
#include <cassert>
#include <atomic>
#include <cstdint>
#include <tuple>

#endif
