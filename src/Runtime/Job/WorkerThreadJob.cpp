#include "WorkerThreadJob.h"
#include <Runtime/Platform/PlatformCriticalSection.h>
#include <Runtime/Assert/Assert.h>
#include <Windows.h>

namespace Portakal
{
	WorkerThreadJob::WorkerThreadJob(const Delegate<void, Job*, const unsigned int>& jobFinishedSignal, const unsigned int index)
		:mTerminated(false)
		,mCurrentJob(nullptr)
		,mIndex(index)
		,mJobFinishedSignal(jobFinishedSignal)
		,mHasWork(false)
	{
		mCriticalSection = PlatformCriticalSection::Create();
	}
	WorkerThreadJob::~WorkerThreadJob()
	{
		delete mCriticalSection;
		mCriticalSection = nullptr;
		mCurrentJob = nullptr;
	}
	bool WorkerThreadJob::HasWork()
	{

		const bool bHasWork = mHasWork;

		return bHasWork;
	}
	void WorkerThreadJob::SubmitJob(Job* pJob)
	{
		ASSERT(mCurrentJob == nullptr, "WorkerThreadJob", "Illegal operation, you cannot assing job to a WorkerThread which already has a job");
		mCurrentJob = pJob;
	}
	void WorkerThreadJob::Terminate()
	{
		mTerminated = true;
	}
	void WorkerThreadJob::Lock()
	{
		mCriticalSection->Lock();
	}
	void WorkerThreadJob::Release()
	{
		mCriticalSection->Release();
	}
	void WorkerThreadJob::Run()
	{
		while (true)
		{
			mCriticalSection->Lock();

			/*
			* If there's no job reset the loop
			*/
			if (mCurrentJob == nullptr)
			{
				mHasWork = false;
				mCriticalSection->Release();
				continue;
			}

			/*
			* There is some job, execute it
			*/
			mHasWork = true;
			mCriticalSection->Release();
			mCurrentJob->Run();
			mCriticalSection->Lock();
			mHasWork = false;

			Job* pJob = mCurrentJob;
			mCurrentJob = nullptr;

			mCriticalSection->Release();

			mJobFinishedSignal.Invoke(pJob, mIndex);
		}
	}
}