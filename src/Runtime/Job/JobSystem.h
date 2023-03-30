#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Platform/PlatformThread.h>
#include <Runtime/Platform/PlatformCriticalSection.h>
#include <Runtime/Job/Job.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Job/WorkerThreadJob.h>

namespace Portakal
{
	class PORTAKAL_API JobSystem final
	{
	private:
		static JobSystem* sSystem;
	public:
		static void Initialize();
		static void Schedule(Job* pJob);
	public:

	private:
		JobSystem();
		~JobSystem();

		void OnSignalJobFinished(Job* pJob,const unsigned int workerID);
		void _Schedule(Job* pJob);
	private:
		struct WorkerThreadData
		{
			WorkerThreadJob* mWorkerJob;
			PlatformThread* pThread;
		};
	private:
		Array<WorkerThreadData> mWorkers;
		Array<Job*> mJobQueue;
		PlatformCriticalSection* mBarrier;
	};
}