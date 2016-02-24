#pragma once
#ifndef THROW_HELPERS_H
#define THROW_HELPERS_H

#include <sstream>
#include <string>
#include <memory>

template <class exception_type>
inline void throw_if_null(void* ptr, const char* msg) {
	if (ptr == nullptr) {
		throw exception_type(msg);
	}
}

#if defined(_WIN32_WINNT)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

template <class exception_type>
inline HRESULT throw_if_failed_hresult(HRESULT hr, const char* msg) {
	if (FAILED(hr)) {
		std::stringstream str;
		str << msg << " HR = 0x" << std::hex << std::uppercase << hr;
		throw exception_type(str.str());
	}
	return hr;
}

// Returns the system error message as a string or, if there is no message, the result of calling ::std::to_string on errorCode.
inline ::std::string last_error_string(DWORD errorCode = GetLastError(), bool* foundSystemMessage = nullptr) {
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
		if (foundSystemMessage != nullptr) {
			*foundSystemMessage = false;
		}
		return ::std::to_string(errorCode);
	}
	else {
		if (foundSystemMessage != nullptr) {
			*foundSystemMessage = true;
		}
		return ::std::string(str.get());
	}
}

template <class exception_type>
inline void throw_get_last_error(const char* backupMessage, DWORD errorCode = GetLastError()) {
	bool foundMessage;
	auto error_message = last_error_string(errorCode, &foundMessage);
	if (foundMessage) {
		throw exception_type(error_message);
	}
	else {
		::std::stringstream error_str;
		error_str << backupMessage << " Error code: " << error_message;
		throw exception_type(error_str.str());
	}
}

#endif

#endif
