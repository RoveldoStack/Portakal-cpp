#pragma once
#include <Runtime/Job/Job.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Platform/PlatformThread.h>
#include <Runtime/Platform/PlatformMutex.h>
#include <Runtime/Event/Delegate.h>

namespace Portakal
{
	class JobPoolJob;

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
		void Submit(TParameters... parameters)
		{
			TClass* pJob = new TClass(parameters...);

			SubmitJob(pJob);
		}

		/// <summary>
		/// Submits external jobs, but takes the ownership of the jbo
		/// </summary>
		/// <param name="pJob"></param>
		void SubmitJob(Job* pJob);
	private:
		void SignalThreadJobFinished(JobPoolJob* pThread);
	private:
		Array<JobPoolJob*> mBusyThreads;
		Array<JobPoolJob*> mIdleThreads;
		Array<Job*> mQueuedJobs;
		Delegate<void,PlatformThread*> mSignalDelegate;
		PlatformMutex* mMutex;
		const unsigned int mThreadCount;
	};
}