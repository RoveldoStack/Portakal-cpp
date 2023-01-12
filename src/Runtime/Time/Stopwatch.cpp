#include "Stopwatch.h"
#include <Runtime/Platform/PlatformTime.h>

namespace Portakal
{
	unsigned long long Stopwatch::GetAsNanoseconds() const noexcept
	{
		return _lastDifference;
	}
	float Stopwatch::GetAsMilliseconds() const noexcept
	{
		return _lastDifference / 10000.0f;;
	}
	void Stopwatch::Mark()
	{
		if (_markedTime != 0)
		{
			const unsigned long long time = PlatformTime::GetCurrentTimeAsNanoseconds();
			_lastDifference = time - _markedTime;
			_markedTime = 0;
		}
		else
		{
			_markedTime = PlatformTime::GetCurrentTimeAsNanoseconds();
		}
	}
	void Stopwatch::Reset()
	{
		_markedTime = 0;
		_lastDifference = 0;
	}
}
