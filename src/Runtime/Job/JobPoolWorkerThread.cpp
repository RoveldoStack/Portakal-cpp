#include "JobPoolWorkerThread.h"
#include <Runtime/Message/MessageAPI.h>
#include <Runtime/Job/JobFiber.h>

namespace Portakal
{
	JobPoolWorkerThread::JobPoolWorkerThread()
	{
		mCriticalSection = PlatformCriticalSection::Create();
		mExitCall = false;
		mCurrentJob = nullptr;
		mFiber = nullptr;
	}
	JobPoolWorkerThread::~JobPoolWorkerThread()
	{
		delete mCriticalSection;
		mCriticalSection = nullptr;
		mCurrentJob = nullptr;
	}
	void JobPoolWorkerThread::SetJobFinishedDelegate(const Delegate<void, JobPoolWorkerThread*,Job*>& signalDelegate)
	{
		mJobSignalDelegate = signalDelegate;
	}
	void JobPoolWorkerThread::SetFiberJobFinishedDelegate(const Delegate<void, JobPoolWorkerThread*, JobFiber*,Job*>& signalDelegate)
	{
		mFiberJobSignalDelegate = signalDelegate;
	}
	void JobPoolWorkerThread::SubmitJob(Job* pJob)
	{
		mCriticalSection->Lock();

		if (mCurrentJob != nullptr)
		{
			MessageAPI::BroadcastMessage("Cannot assing a new job to a thread in the job pool when that job-thread hasnt finished the former job yet!");
		}
		else
		{
			mCurrentJob = pJob;
		}

		mCriticalSection->Release();
	}
	void JobPoolWorkerThread::SubmitFiberJob(Job* pJob, JobFiber* pFiber)
	{
		mCriticalSection->Lock();

		if (mCurrentJob != nullptr)
		{
			MessageAPI::BroadcastMessage("Cannot assing a new job to a thread in the job pool when that job-thread hasnt finished the former job yet!");
			mCriticalSection->Release();
			return;
		}
		if (mFiber != nullptr)
		{
			MessageAPI::BroadcastMessage("Cannot assing a new job to a thread in the job pool when that job-thread hasnt finished the former job yet(Fiber)!");
			mCriticalSection->Release();
			return;
		}

		mCurrentJob = pJob;
		mFiber = pFiber;

		mCriticalSection->Release();
	}
	void JobPoolWorkerThread::WaitForExit()
	{
		mCriticalSection->Lock();
		mExitCall = true;
		mCriticalSection->Release();
	}
	void JobPoolWorkerThread::Run()
	{
		/*
		* Job run loop
		*/
		while (!mExitCall)
		{
			mCriticalSection->Lock();

			/*
			* First validate if there's a valid job
			*/
			if (mCurrentJob == nullptr)
			{
				mCriticalSection->Release();
				continue;
			}

			/*
			* Run the current job
			*/
			mCurrentJob->Run();
			bool bWasFiber = false;
			JobFiber* pFiber = mFiber;
			Job* pJob = mCurrentJob;
			if (mFiber != nullptr) //its a fiber job
			{
				bWasFiber = true;
			}
			else // it's a normal job
			{

			}

			mCurrentJob = nullptr;
			mFiber = nullptr;

			mCriticalSection->Release();

			/*
			* Signal that this job is finished
			*/
			if (bWasFiber)
				mFiberJobSignalDelegate.Invoke(this,pFiber, pJob);
			else 
				mJobSignalDelegate.Invoke(this,pJob);
		}
	}
}