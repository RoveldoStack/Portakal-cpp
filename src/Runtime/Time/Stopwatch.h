#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class PORTAKAL_API Stopwatch
	{
	public:
		Stopwatch() : mMarkedTime(0) {}
		~Stopwatch() = default;

		FORCEINLINE unsigned long long GetAsNanoseconds() const noexcept;
		FORCEINLINE float GetAsMilliseconds() const noexcept;

		void Mark();
		void Reset();
	private:
		unsigned long long mMarkedTime;
		unsigned long long mLastDifference;
	};
}