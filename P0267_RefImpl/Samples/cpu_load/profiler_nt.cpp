#include "profiler.h"
#include <assert.h>
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <Winternl.h>
#pragma comment(lib, "ntdll.lib")

static int CPUs()
{
	SYSTEM_BASIC_INFORMATION info;
	NtQuerySystemInformation(SystemBasicInformation, &info, sizeof(info), NULL);
	return info.NumberOfProcessors;
}

static SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION EmptyInfo()
{
	SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION i;
	memset(&i, 0, sizeof(i));
	return i;
}

std::vector<float> GetCPUsLoad()
{
	using Info = SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;
	static const auto cpus = CPUs();
	
	static std::vector<Info> current(cpus, EmptyInfo()), prior(cpus, EmptyInfo());
	ULONG ret_len = 0;
	auto res = NtQuerySystemInformation(SystemProcessorPerformanceInformation, current.data(), sizeof(Info)*cpus, &ret_len);
	if( res != 0 )
		return {};
	assert(ret_len / sizeof(Info) == cpus);

	std::vector<float> result(cpus);
	for (auto i = 0; i < cpus; ++i) {
		auto load = current[i].KernelTime.QuadPart + current[i].UserTime.QuadPart - prior[i].KernelTime.QuadPart - prior[i].UserTime.QuadPart;
		auto total = load + current[i].IdleTime.QuadPart - prior[i].IdleTime.QuadPart;
		result[i] = float(load) / float(total);
	}
	std::swap(current, prior);
	return result;
}
