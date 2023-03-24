#pragma once
#include <Runtime/Platform/PlatformThread.h>
#include <Windows.h>

namespace Portakal
{
	class PORTAKAL_API Win32Thread : public PlatformThread
	{
	public:
		static void WaitCurrentThread(const unsigned long long waitAmount);
	private:
		static void DispatchThread(void* pSelf);
	public:
		Win32Thread(const unsigned int stackSize,Job* pJob);
		~Win32Thread() = default;


		// Inherited via PlatformThread
		virtual void WaitForFinishCore() override;

		virtual void TerminateCore() override;
	private:
		HANDLE mHandle;
	};
}