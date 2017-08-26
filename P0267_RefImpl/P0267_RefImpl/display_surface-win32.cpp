#include "io2d.h"
#include "xdiagnostics.h"
#include "xinclwindows_h.h"

#include <chrono>
#include <sstream>
#include <string>
#include <iomanip>
#include <deque>
#include <numeric>

using namespace std;
using namespace std::chrono;
using namespace std::experimental::io2d;

windows::windows_handler_impl::windows_handler_impl(int preferredDisplayWidth, int preferredDisplayHeight, experimental::io2d::refresh_rate rr, float fps)
	: _Display_dimensions(preferredDisplayWidth, preferredDisplayHeight)
	, _Refresh_rate(rr)
	, _Desired_frame_rate(fps)
	, _Window_style(WS_OVERLAPPEDWINDOW | WS_VISIBLE)
	, _Hwnd(nullptr)
{
	if (fps <= _Minimum_frame_rate || !isfinite(fps)) {
		throw system_error(make_error_code(errc::argument_out_of_domain));
	}
	// Record the desired client window size
	if (preferredDisplayWidth <= 0 || preferredDisplayHeight <= 0) {
		throw invalid_argument("Invalid parameter.");
	}
}

windows::windows_handler_impl::~windows_handler_impl() {
	if (_Hwnd != nullptr) {
		assert(_Hwnd == nullptr);
		DestroyWindow(_Hwnd);
		_Hwnd = nullptr;
	}
}

void windows::windows_handler_impl::resize_window(display_point dp) const {
	RECT clientRect;
	RECT windowRect;
	GetWindowRect(_Hwnd, &windowRect);
	GetClientRect(_Hwnd, &clientRect);
	auto crWidth = clientRect.right - clientRect.left;
	auto crHeight = clientRect.bottom - clientRect.top;
	auto wrWidth = windowRect.right - windowRect.left;
	auto wrHeight = windowRect.bottom - windowRect.top;

	if (crWidth != dp.x || crHeight != dp.y) {
		auto new_width = std::max((wrWidth - crWidth) + 1L, (dp.x - crWidth) + wrWidth);
		auto new_height = std::max((wrHeight - crHeight) + 1L, (dp.y - crHeight) + wrHeight);
		// Resize the window.
		if (!SetWindowPos(_Hwnd, 0, 0, 0, new_width, new_height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS)) {
			_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to SetWindowPos.");
		}

		if (!PostMessageW(_Hwnd, WM_PAINT, static_cast<WPARAM>(0), static_cast<LPARAM>(0))) {
			_Throw_system_error_for_GetLastError(GetLastError(), "Failed call to PostMessageW.");
		}
	}
}

windows::windows_handler_impl::context windows::windows_handler_impl::make_context() const
{
	return context(_Hwnd);
}

void windows::windows_handler_impl::refresh_rate(experimental::io2d::refresh_rate rr) noexcept {
	if (rr == experimental::io2d::refresh_rate::fixed && _Refresh_rate != rr) {
		_Elapsed_draw_time = 0.0F;
	}
	_Refresh_rate = rr;
}

bool windows::windows_handler_impl::desired_frame_rate(float fps) noexcept {
	if (!isfinite(fps)) {
		return true;
	}
	if (fps < _Minimum_frame_rate) {
		_Desired_frame_rate = _Minimum_frame_rate;
		return true;
	}
	if (fps > _Maximum_frame_rate) {
		_Desired_frame_rate = _Maximum_frame_rate;
		return true;
	}
	_Desired_frame_rate = fps;

	return false;
}

experimental::io2d::refresh_rate windows::windows_handler_impl::refresh_rate() const noexcept {
	return _Refresh_rate;
}

float windows::windows_handler_impl::desired_frame_rate() const noexcept {
	return _Desired_frame_rate;
}

float windows::windows_handler_impl::elapsed_draw_time() const noexcept {
	return _Elapsed_draw_time / 1'000'000.0F;
}
