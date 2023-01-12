#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class PORTAKAL_API Win32Time
	{
	public:
		Win32Time() = delete;
		~Win32Time() = delete;

		FORCEINLINE static unsigned long long GetCurrentTimeAsNanoseconds();
	};
}