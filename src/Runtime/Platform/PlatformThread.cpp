#include "PlatformThread.h"
#include <Runtime/Job/Job.h>

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Thread.h>
typedef Portakal::Win32Thread PlatformAbstraction;
#endif

namespace Portakal
{
	PlatformThread* PlatformThread::Dispatch(const unsigned int stackSize,Job* pJob)
	{
		return new PlatformAbstraction(stackSize,pJob);
	}
	void PlatformThread::SleepCurrentThread(const unsigned long long waitAmount)
	{
		PlatformAbstraction::WaitCurrentThread(waitAmount);
	}
	
	PlatformThread::PlatformThread(const unsigned int stackSize, Job* pJob) : mJob(pJob), mStackSize(stackSize), mRunning(false)
	{
		pJob->_SetOwnerThread(this);
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