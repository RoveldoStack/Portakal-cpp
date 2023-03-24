#include "JobPoolJob.h"
#include <Runtime/Message/MessageAPI.h>

namespace Portakal
{
	JobPoolJob::JobPoolJob(const Delegate<void, JobPoolJob*>& signalDelegate)
	{
		mMutex = PlatformMutex::Create();
		mSignalDelegate = signalDelegate;
		mExitCall = false;
		mCurrentJob = nullptr;
	}
	JobPoolJob::~JobPoolJob()
	{
		delete mMutex;
		mMutex = nullptr;
		mCurrentJob = nullptr;
	}
	void JobPoolJob::SubmitJob(Job* pJob)
	{
		mMutex->Lock(WAIT_INFINITE);
		if (mCurrentJob != nullptr)
		{
			MessageAPI::BroadcastMessage("Cannot assing a new job to a thread in the job pool when that job-thread hasnt finished the former job yet!");
		}
		else
		{
			mCurrentJob = pJob;
		}
		mMutex->Release();
	}
	void JobPoolJob::WaitForExit()
	{
		mMutex->Lock(WAIT_INFINITE);
		mExitCall = true;
		mMutex->Release();
	}
	void JobPoolJob::Run()
	{
		/*
		* Job run loop
		*/
		while (!mExitCall)
		{
			mMutex->Lock(WAIT_INFINITE);

			/*
			* First validate if there's a valid job
			*/
			if (mCurrentJob == nullptr)
			{
				mMutex->Release();
				continue;
			}

			/*
			* Run the current job
			*/
			mCurrentJob->Run();

			/*
			* Delete upon finishing the job
			*/
			delete mCurrentJob;
			mCurrentJob = nullptr;

			mMutex->Release();

			/*
			* Signal that this job is finished
			*/
			mSignalDelegate.Invoke(this);
		}
	}
}