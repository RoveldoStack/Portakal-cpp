#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class PORTAKAL_API PlatformTime
	{
	public:
		PlatformTime() = delete;
		~PlatformTime() = delete;

		FORCEINLINE static unsigned long long GetCurrentTimeAsNanoseconds();
	};
}