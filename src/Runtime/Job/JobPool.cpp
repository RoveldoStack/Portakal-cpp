#include "JobPool.h"
#include <Runtime/Platform/PlatformMutex.h>
#include <Runtime/Message/MessageAPI.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Job/JobPoolWorkerThread.h>

namespace Portakal
{
	
	JobPool::JobPool(const unsigned int threadCount) : mThreadCount(threadCount)
	{
		ASSERT(threadCount != 0, "JobPool", "Illegal JobPool thread count: %d", threadCount);

		/*
		* Create mutex
		*/
		mCriticalSection = PlatformCriticalSection::Create();

		/*
		* Create threads
		*/
		for (unsigned int i = 0; i < threadCount; i++)
		{
			JobPoolWorkerThread* pJob = new JobPoolWorkerThread();
			pJob->SetJobFinishedDelegate(GENERATE_MEMBER_DELEGATE2(this, JobPool::SignalThreadJobFinished, void, JobPoolWorkerThread*,Job*));
			pJob->SetFiberJobFinishedDelegate(GENERATE_MEMBER_DELEGATE3(this, JobPool::SignalFiberThreadJobFinished, void, JobPoolWorkerThread*, JobFiber*,Job*));

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
		unsigned int value = 0;
		mCriticalSection->Lock();
		value = mBusyThreads.GetCursor();
		mCriticalSection->Release();
		return value;
	}
	unsigned int JobPool::GetIdleThreadCount()
	{
		unsigned int value = 0;

		mCriticalSection->Lock();
		value = mIdleThreads.GetCursor();
		mCriticalSection->Release();
	
		return value;
	}
	void JobPool::SubmitTargetJob(Job* pJob)
	{
		/*
		* Validate for finished state
		*/
		if (pJob->IsFinished())
			return;

		mCriticalSection->Lock();
		if (mIdleThreads.GetCursor() == 0)
		{
			mQueuedJobs.Add(pJob);
		}
		else
		{
			JobPoolWorkerThread* pThread = mIdleThreads[0];

			pJob->_SetWorkingState(true);

			pThread->SubmitJob(pJob);

			mIdleThreads.RemoveIndex(0);
			mBusyThreads.Add(pThread);
		}
		mCriticalSection->Release();
	}

	void JobPool::SubmitJobFiber(JobFiber* pFiber)
	{
		/*
		* Validate if this pool can support the given fiber
		*/
		const unsigned int fiberVerticalSize = pFiber->GetJobPathMaxVerticalSize();
		if (fiberVerticalSize > mThreadCount)
		{
			LOG("JobPool", "Couldnt submit job fiber because this JobPool cannot support this vertical size of the given fiber");
			return;
		}

		/*
		* Try dispatch fiber
		*/
		mCriticalSection->Lock();

		/*
		* Collect idle threads
		*/
		mFibers.Add({ pFiber,{},{}});
		
		/*
		* Try populate fibers
		*/
		PopulateFibers();

		mCriticalSection->Release();
	}

	void JobPool::SignalThreadJobFinished(JobPoolWorkerThread* pThread,Job* pTargetJob)
	{
		/*
		* Try lock
		*/
		mCriticalSection->Lock();

		/*
		* Set new job state
		*/
		pTargetJob->_SetWorkingState(false);
		pTargetJob->_MarkFinished();

		/*
		* Remove the worker thread from the busy list
		*/
		mBusyThreads.Remove(pThread);
		mIdleThreads.Add(pThread);

		/*
		* Try populate fibers first
		*/
		PopulateFibers();

		/*
		* Check if there are queued waiting jobs for a idle thread
		*/
		if (mQueuedJobs.GetCursor() > 0 && mIdleThreads.GetCursor() > 0)
		{
			Job* pJob = mQueuedJobs[0];
			pJob->_SetWorkingState(true);

			pThread->SubmitJob(pJob);

			mQueuedJobs.RemoveIndex(0);
		}

		mCriticalSection->Release();
	}
	void JobPool::SignalFiberThreadJobFinished(JobPoolWorkerThread* pThread, JobFiber* pFiber,Job* pJob)
	{
		mCriticalSection->Lock();

		/*
		* Report to fiber that the current node job finished
		*/
		const bool bNodeFinished = pFiber->_ReportJobFinished(pJob);

		/*
		* Recalculate the max vertical size
		* This required in order to provide best performance within the job system
		* This helps to minimize the unused worker threads
		*/
		const bool bVerticalSizeChanged = pFiber->_RecalculateMaxVerticalSize();

		/*
		* Exchange worker threads inside the entry
		*/
		FiberEntry* pEntry = GetFiberEntry(pFiber);
		pEntry->BusyThreads.Remove(pThread);
		pEntry->IdleThreads.Add(pThread);

		/*
		* Validate if the max vertical size changed so release the last finished worker thread
		* This adds the unused worker thread back to idle pool
		*/
		ASSERT(pEntry != nullptr, "JobPool", "Illegal operation, FiberEntry returned nullptr!");
		if (bVerticalSizeChanged)
		{
			/*
			* Exchange the worker thread between idle and busy thread pools
			*/
			mIdleThreads.Add(pThread);
			mBusyThreads.Remove(pThread);

			pEntry->IdleThreads.Remove(pThread);
		}

		/*
		* Try populate other fibers
		*/
		if (bVerticalSizeChanged)
			PopulateFibers();

		/*
		* Try run standalone job
		*/
		for (unsigned int i = 0; i < mIdleThreads.GetCursor() && mQueuedJobs.GetCursor() != 0; i++)
		{
			JobPoolWorkerThread* pWorkerThread = mIdleThreads[0];

			pWorkerThread->SubmitJob(mQueuedJobs[0]);

			mIdleThreads.RemoveIndex(0);
			mBusyThreads.Add(pWorkerThread);

			mQueuedJobs.RemoveIndex(0);
			i--;
		}

		/*
		* Get and validate new node
		*/
		const Array<Job*> node = pFiber->CollectCurrentNode();
		if (node.GetCursor() == 0) // this fiber is finished
		{
			/*
			* Mark fiber not working anymore
			*/
			pFiber->_SetWorkingState(false);

			/*
			* Mark fiber is finished
			*/
			pFiber->_MarkFinished();

			RemoveFiberEntry(pFiber);

			mCriticalSection->Release();

			return;
		}

		/*
		* There are still nodes to finish for this fiber
		* Register new jobs
		*/
		if (bNodeFinished)
		{
			DispatchFiber(pFiber);
		}

		mCriticalSection->Release();
	}
	void JobPool::DispatchFiber(JobFiber* pTargetFiber)
	{
		FiberEntry* pEntry = GetFiberEntry(pTargetFiber);
		ASSERT(pEntry != nullptr, "JobPool", "Illegal fiber entry");

		const Array<Job*> node = pTargetFiber->CollectCurrentNode();
		for (unsigned int i = 0; i < node.GetCursor(); i++)
		{
			JobPoolWorkerThread* pWorkerThread = pEntry->IdleThreads[0];

			pWorkerThread->SubmitFiberJob(node[i], pTargetFiber);

			pEntry->IdleThreads.RemoveIndex(0);
			pEntry->BusyThreads.Add(pWorkerThread);

		}
	}
	JobPool::FiberEntry* JobPool::GetFiberEntry(JobFiber* pFiber)
	{
		for(unsigned int i = 0;i<mFibers.GetCursor();i++)
		{
			if (mFibers[i].pFiber == pFiber)
				return &mFibers[i];
		}

		ASSERT(false, "JobPool", "Returned nullptr fiber entry");
		return nullptr;
	}
	void JobPool::RemoveFiberEntry(JobFiber* pFiber)
	{
		for (unsigned int i = 0; i < mFibers.GetCursor(); i++)
		{
			if (mFibers[i].pFiber == pFiber)
			{
				mFibers.RemoveIndex(i);
				return;
			}
		}
	}
	void JobPool::PopulateFibers()
	{
		for (unsigned int fiberIndex = 0; fiberIndex < mFibers.GetCursor(); fiberIndex++)
		{
			FiberEntry& entry = mFibers[fiberIndex];
			if (entry.pFiber->IsFinished())
				continue;
			if (entry.pFiber->IsWorking())
				continue;

			/*
			* Validate if working
			* IF not working then check for idle pool
			*/
			unsigned int requiredWorkerCount = entry.pFiber->GetJobPathMaxVerticalSize() - entry.IdleThreads.GetCursor();

			for (unsigned int threadIndex = 0; threadIndex < mIdleThreads.GetCursor() && requiredWorkerCount != 0; threadIndex++)
			{
				JobPoolWorkerThread* pWorkerThread = mIdleThreads[0];

				entry.IdleThreads.Add(pWorkerThread);

				mBusyThreads.Add(pWorkerThread);

				mIdleThreads.RemoveIndex(0);

				requiredWorkerCount--;
				threadIndex--;
			}

			/*
			* Fiber is ready for dispatch
			*/
			if (requiredWorkerCount == 0)
			{
				entry.pFiber->_SetWorkingState(true);
				DispatchFiber(entry.pFiber);
			}
		}
	}
}