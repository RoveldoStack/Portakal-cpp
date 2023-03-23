#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class PORTAKAL_API PlatformMutex
	{
	public:
		static PlatformMutex* Create();
	public:
		PlatformMutex() = default;
		virtual ~PlatformMutex() = default;

		FORCEINLINE virtual bool TryLock() = 0;
		FORCEINLINE virtual void Lock(const unsigned long long waitTime) = 0;
		FORCEINLINE virtual void Release() = 0;
	};
}