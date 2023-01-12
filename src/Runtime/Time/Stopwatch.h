#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class PORTAKAL_API Stopwatch
	{
	public:
		Stopwatch() : _markedTime(0) {}
		~Stopwatch() = default;

		FORCEINLINE unsigned long long GetAsNanoseconds() const noexcept;
		FORCEINLINE float GetAsMilliseconds() const noexcept;

		void Mark();
		void Reset();
	private:
		unsigned long long _markedTime;
		unsigned long long _lastDifference;
	};
}