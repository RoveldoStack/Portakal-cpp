#pragma once
#include <Runtime/Platform/PlatformMutex.h>
#include <Windows.h>

namespace Portakal
{
	class PORTAKAL_API Win32Mutex : public PlatformMutex
	{
	public:
		Win32Mutex();
		virtual ~Win32Mutex() override;

	private:
		// Inherited via PlatformMutex
		virtual bool Lock(const unsigned long long waitTime) override;
		virtual bool TryLock() override;
		virtual bool Release() override;

	private:
		HANDLE mHandle;

	};
}