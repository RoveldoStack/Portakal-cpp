#include "JobPool.h"
#include <Runtime/Platform/PlatformMutex.h>
#include <Runtime/Message/MessageAPI.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Job/JobPoolJob.h>

namespace Portakal
{
	
	JobPool::JobPool(const unsigned int threadCount) : mThreadCount(threadCount)
	{
		ASSERT(threadCount != 0, "JobPool", "Illegal JobPool thread count: %d", threadCount);

		/*
		* Create mutex
		*/
		mMutex = PlatformMutex::Create();

		/*
		* Create threads
		*/
		for (unsigned int i = 0; i < threadCount; i++)
		{
			JobPoolJob* pJob = new JobPoolJob(GENERATE_MEMBER_DELEGATE(this, JobPool::SignalThreadJobFinished, void, JobPoolJob*));

			PlatformThread::Create(pJob, 2);

			mIdleThreads.Add(pJob);
		}
	}
	JobPool::~JobPool()
	{

	}
	unsigned int JobPool::GetPoolSize()
	{
		return mThreadCount;
	}
	unsigned int JobPool::GetBusyThreadCount()
	{
		mMutex->Lock(WAIT_INFINITE);
		const unsigned int value = mBusyThreads.GetCursor();
		mMutex->Release();

		return value;
	}
	unsigned int JobPool::GetIdleThreadCount()
	{
		mMutex->Lock(WAIT_INFINITE);
		const unsigned int value = mIdleThreads.GetCursor();
		mMutex->Release();

		return value;
	}
	void JobPool::SubmitJob(Job* pJob)
	{
		mMutex->Lock(WAIT_INFINITE);
		if (mIdleThreads.GetCursor() == 0)
		{
			mQueuedJobs.Add(pJob);
		}
		else
		{
			JobPoolJob* pThread = mIdleThreads[0];
			pThread->SubmitJob(pJob);

			mIdleThreads.RemoveIndex(0);
			
		}
		mMutex->Release();
	}

	void JobPool::SignalThreadJobFinished(JobPoolJob* pThread)
	{
		mMutex->Lock(WAIT_INFINITE);

		mBusyThreads.Remove(pThread);

		if (mQueuedJobs.GetCursor() > 0)
		{
			pThread->SubmitJob(mQueuedJobs[0]);
			mQueuedJobs.RemoveIndex(0);
		}
		else
		{
			mIdleThreads.Add(pThread);
		}

		mMutex->Release();
	}
}