#include "Win32Thread.h"
#include <Runtime/Job/IJob.h>

namespace Portakal
{
	void Win32Thread::DispatchThread(void* pTarget)
	{
		IJob* pJob = (IJob*)pTarget;
		pJob->Run();
	}
	Win32Thread::Win32Thread(const unsigned int stackSize,IJob* pJob) : PlatformThread(stackSize,pJob), mHandle(NULL)
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