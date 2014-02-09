#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include "resource.h"
#include "targetver.h"
#include <Unknwn.h>
#include <ShObjIdl.h>
#include <KnownFolders.h>
#include <shellapi.h>

#include <stdexcept>
#include "throw_helpers.h"

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int, HWND&);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

namespace not_proposed {
	class timer {
		bool m_supportsHPC;
		LARGE_INTEGER m_frequencyHPC;
		LARGE_INTEGER m_startCountHPC;
		LARGE_INTEGER m_lastCountHPC;
		ULONGLONG m_startTickCount64;
		ULONGLONG m_lastTickCount64;
		double m_elapsedTime;
		double m_totalTime;

	public:
		timer()
			: m_supportsHPC()
			, m_frequencyHPC()
			, m_startCountHPC()
			, m_lastCountHPC()
			, m_startTickCount64()
			, m_lastTickCount64()
			, m_elapsedTime()
			, m_totalTime() {
			reset();
		}

		void reset() {
			// Though it's highly unlikely, it's not impossible that the computer doesn't support a high-resolution
			// performance counter, which is required for this API.
			m_supportsHPC = ::QueryPerformanceFrequency(&m_frequencyHPC) != 0;

			if (m_supportsHPC) {
				// If this returns zero there's a runtime error of some sort per the API.
				if (::QueryPerformanceCounter(&m_startCountHPC) == 0) {
					throw_get_last_error<::std::runtime_error>("Failed call to QueryPerformanceCounter.");
				}
				m_lastCountHPC = m_startCountHPC;
			}
			else {
				// Fall back to the inaccurate timer.
				m_lastTickCount64 = m_startTickCount64 = ::GetTickCount64();
			}
		}

		// Returns elapsed time since last call to Update or Reset.
		void update() {
			if (m_supportsHPC) {
				LARGE_INTEGER currentCountHPC;
				if (QueryPerformanceCounter(&currentCountHPC) == 0) {
					throw_get_last_error<::std::runtime_error>("Failed call to QueryPerformanceCounter.");
				}
				const double millisecondsPerSecond = 1000.0;
				m_elapsedTime = (static_cast<double>(currentCountHPC.QuadPart - m_lastCountHPC.QuadPart) / static_cast<double>(m_frequencyHPC.QuadPart)) * millisecondsPerSecond;
				m_totalTime += m_elapsedTime;
				m_lastCountHPC = currentCountHPC;
			}
			else {
				auto currentTickCount = ::GetTickCount64();
				if (currentTickCount < m_lastTickCount64) {
					currentTickCount = m_lastTickCount64;
				}
				m_elapsedTime = static_cast<double>(currentTickCount - m_lastTickCount64);
				m_totalTime += m_elapsedTime;
				m_lastTickCount64 = currentTickCount;
			}
		}

		double get_elapsed_time() {
			return m_elapsedTime;
		}

		double get_total_time() {
			return m_totalTime;
		}
	};
}
