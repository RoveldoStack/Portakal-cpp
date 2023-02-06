#include "Stopwatch.h"
#include <Runtime/Platform/PlatformTime.h>

namespace Portakal
{
	unsigned long long Stopwatch::GetAsNanoseconds() const noexcept
	{
		return mLastDifference;
	}
	float Stopwatch::GetAsMilliseconds() const noexcept
	{
		return mLastDifference / 10000.0f;;
	}
	void Stopwatch::Mark()
	{
		if (mMarkedTime != 0)
		{
			const unsigned long long time = PlatformTime::GetCurrentTimeAsNanoseconds();
			mLastDifference = time - mMarkedTime;
			mMarkedTime = 0;
		}
		else
		{
			mMarkedTime = PlatformTime::GetCurrentTimeAsNanoseconds();
		}
	}
	void Stopwatch::Reset()
	{
		mMarkedTime = 0;
		mLastDifference = 0;
	}
}
