#include "Win32Time.h"
#include <Windows.h>

namespace Portakal
{
	unsigned long long Win32Time::GetCurrentTimeAsNanoseconds()
	{
		FILETIME fileTime = {};
		GetSystemTimePreciseAsFileTime(&fileTime);
		ULARGE_INTEGER value;

		value.LowPart = fileTime.dwLowDateTime;
		value.HighPart = fileTime.dwHighDateTime;

		__int64 time = value.QuadPart;

		return time;
	}
}