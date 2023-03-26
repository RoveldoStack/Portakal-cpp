#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class PORTAKAL_API PlatformCriticalSection
	{
	public:
		static PlatformCriticalSection* Create();
	public:
		PlatformCriticalSection() = default;
		virtual ~PlatformCriticalSection() = default;

		FORCEINLINE virtual bool TryLock() = 0;
		FORCEINLINE virtual void Lock() = 0;
		FORCEINLINE virtual void Release() = 0;
	private:

	};
}