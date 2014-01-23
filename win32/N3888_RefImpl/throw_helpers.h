#pragma once

#include <sstream>
#include <string>
#include <memory>

template <class exception_type>
inline void throw_if_failed_hresult(HRESULT hr, const char* msg) {
	if (FAILED(hr)) {
		std::stringstream str;
		str << msg << " HR = 0x" << std::hex << std::uppercase << hr;
		throw exception_type(str.str());
	}
}

template <class exception_type>
inline void throw_if_null(void* ptr, const char* msg) {
	if (ptr == nullptr) {
		throw exception_type(msg);
	}
}

template <class exception_type>
inline void throw_get_last_error(const char* backupMessage) {
	auto errorCode = GetLastError();
	const auto strCount = 0xFFFF;
	::std::unique_ptr<char[]> str(new char[strCount]);
	ZeroMemory(str.get(), strCount * sizeof(char));

	// Note: Intentionally using the A version to get a char* string for the exception.
	auto char_count = FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		str.get(),
		strCount,
		nullptr
		);

	if (char_count == 0) {
		std::stringstream error_str;
		error_str << backupMessage << " Error code: " << errorCode;
		throw exception_type(error_str.str());
	}
	else {
		throw exception_type(std::string(str.get()));
	}
}

