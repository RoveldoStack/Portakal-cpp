#include "Win32Thread.h"
#include <Runtime/Job/Job.h>

namespace Portakal
{
	void Win32Thread::DispatchThread(void* pTarget)
	{
		Job* pJob = (Job*)pTarget;
		pJob->Run();
	}
	Win32Thread::Win32Thread(const unsigned int stackSize,Job* pJob) : PlatformThread(stackSize,pJob), mHandle(NULL)
	{
		mHandle = CreateThread(NULL, 2, (LPTHREAD_START_ROUTINE)Win32Thread::DispatchThread, pJob, NULL, NULL);
	}
	void Win32Thread::WaitCurrentThread(const unsigned long long waitAmount)
	{
		Sleep(waitAmount);
	}
	
	void Win32Thread::WaitForFinishCore()
	{
		WaitForSingleObject(mHandle, INFINITE);
	}
	void Win32Thread::TerminateCore()
	{
		TerminateThread(mHandle, INFINITE);
	}
}