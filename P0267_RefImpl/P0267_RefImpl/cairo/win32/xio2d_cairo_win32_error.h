#pragma once
namespace std {
	namespace experimental {
		namespace io2d {
			inline namespace v1 {
				namespace _Cairo {
					[[noreturn]]
					inline void _Throw_system_error_for_GetLastError(DWORD getLastErrorValue, const char* message) {
						if (message != nullptr) {
							// Updated Note: Changed to static_cast due to 4.7F/3 [conv.integral]. // Old Note: C-style cast because system_error requires an int but GetLastError returns a DWORD (i.e. unsigned long) but ordinary WinError.h values never exceed the max value of an int.
							throw system_error(static_cast<int>(getLastErrorValue), system_category(), message);
						}
						else {
							throw system_error(static_cast<int>(getLastErrorValue), system_category());
						}
					}
				}
			}
		}
	}
}
