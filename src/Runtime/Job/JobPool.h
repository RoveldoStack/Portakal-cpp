#pragma once
#include <Runtime/Job/Job.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Platform/PlatformThread.h>
#include <Runtime/Platform/PlatformCriticalSection.h>
#include <Runtime/Event/Delegate.h>
#include <Runtime/Job/JobFiber.h>

namespace Portakal
{
	class JobPoolWorkerThread;

	/// <summary>
	/// Job pool authoring class
	/// </summary>
	class PORTAKAL_API JobPool
	{
	public:
		JobPool(const unsigned int threadCount);
		~JobPool();

		/// <summary>
		/// Returns the total poolsize
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetPoolSize();

		/// <summary>
		/// Returns the current busy thread count
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetBusyThreadCount();

		/// <summary>
		/// Returns the current idle thread count
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetIdleThreadCount();

		/// <summary>
		/// Submits templates jobs
		/// </summary>
		/// <typeparam name="TClass"></typeparam>
		/// <typeparam name="...TParameters"></typeparam>
		/// <param name="...parameters"></param>
		template<typename TClass,typename... TParameters>
		TClass* SubmitJob(TParameters... parameters)
		{
			TClass* pJob = new TClass(parameters...);

			SubmitTargetJob(pJob);

			return pJob;
		}

		/// <summary>
		/// Submits external jobs, but takes the ownership of the job
		/// </summary>
		/// <param name="pJob"></param>
		Job* SubmitTargetJob(Job* pJob);

		/// <summary>
		/// Submits anew fiber
		/// </summary>
		/// <param name="pFiber"></param>
		void SubmitJobFiber(JobFiber* pFiber);
	private:
		struct FiberEntry
		{
			JobFiber* pFiber;
			Array<JobPoolWorkerThread*> IdleThreads;
			Array<JobPoolWorkerThread*> BusyThreads;
		};
	private:
		void SignalThreadJobFinished(JobPoolWorkerThread* pThread,Job* pJob);
		void SignalFiberThreadJobFinished(JobPoolWorkerThread* pThread,JobFiber* pFiber,Job* pJob);
		void DispatchFiber(JobFiber* pFiber);
		FiberEntry* GetFiberEntry(JobFiber* pFiber);
		void RemoveFiberEntry(JobFiber* pFiber);
		void PopulateFibers();
	
	private:
		Array<JobPoolWorkerThread*> mBusyThreads;
		Array<JobPoolWorkerThread*> mIdleThreads;
		Array<Job*> mQueuedJobs;
		Array<FiberEntry> mFibers;
		Delegate<void,PlatformThread*> mSignalDelegate;
		PlatformCriticalSection* mCriticalSection;
		const unsigned int mThreadCount;
	};
}