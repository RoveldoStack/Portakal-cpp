#include "Job.h"
#include <Runtime/Platform/PlatformCriticalSection.h>

namespace Portakal
{
	Job::Job() : mOwnerThread(nullptr),mCriticalSection(nullptr),mFinished(false),mWorking(false)
	{
		mCriticalSection = PlatformCriticalSection::Create();
	}
	bool Job::IsWorking()
	{
		mCriticalSection->Lock();
		const bool state = mWorking;
		mCriticalSection->Create();

		return state;
	}
	bool Job::IsFinished()
	{
		mCriticalSection->Lock();
		const bool state = mFinished;
		mCriticalSection->Release();

		return state;
	}
	void Job::_SetWorkingState(const bool bState)
	{
		mCriticalSection->Lock();
		mWorking = bState;
		mCriticalSection->Release();
	}
	void Job::_MarkFinished()
	{
		mCriticalSection->Lock();
		mFinished = true;
		mWorking = false;
		mCriticalSection->Release();
	}
}