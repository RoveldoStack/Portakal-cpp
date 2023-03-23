#include "PlatformThread.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Thread.h>
typedef Portakal::Win32Thread PlatformAbstraction;
#endif

namespace Portakal
{
	PlatformThread* PlatformThread::Create(const unsigned int stackSize,IJob* pJob)
	{
		return new PlatformAbstraction(stackSize,pJob);
	}
	void PlatformThread::WaitCurrentThread(const unsigned long long waitAmount)
	{
		PlatformAbstraction::WaitCurrentThread(waitAmount);
	}
	
	PlatformThread::~PlatformThread()
	{
		if (mRunning)
			Terminate();

		mRunning = false;

		delete mJob;
		mJob = nullptr;
	}
	void PlatformThread::WaitForFinish()
	{
		WaitForFinishCore();
		mRunning = false;
	}
	void PlatformThread::Terminate()
	{
		TerminateCore();
		mRunning = false;
	}
}