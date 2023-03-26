#pragma once
#include <Runtime/Platform/PlatformCriticalSection.h>
#include <Windows.h>

namespace Portakal
{
	class PORTAKAL_API Win32CriticalSection : public PlatformCriticalSection
	{
	public:
		Win32CriticalSection();
		virtual ~Win32CriticalSection() override;

		// Inherited via PlatformCriticalSection
		virtual bool TryLock() override;
		virtual void Lock() override;
		virtual void Release() override;
	private:
		CRITICAL_SECTION mSection;
	};
}