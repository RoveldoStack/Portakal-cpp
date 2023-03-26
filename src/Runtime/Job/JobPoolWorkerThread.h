#pragma once
#include <Runtime/Job/Job.h>
#include <Runtime/Platform/PlatformCriticalSection.h>
#include <Runtime/Event/Delegate.h>

namespace Portakal
{
	class JobFiber;
	/// <summary>
	/// Job specialized for JobPools to use
	/// DO NOT USE THIS JOB Standalone
	/// </summary>
	class PORTAKAL_API JobPoolWorkerThread final : public Job
	{
	public:
		JobPoolWorkerThread();
		virtual ~JobPoolWorkerThread() override;

		void SetJobFinishedDelegate(const Delegate<void, JobPoolWorkerThread*,Job*>& signalDelegate);
		void SetFiberJobFinishedDelegate(const Delegate<void, JobPoolWorkerThread*, JobFiber*,Job*>& signalDelegate);

		/// <summary>
		/// Submits new job
		/// </summary>
		/// <param name="pJob"></param>
		void SubmitJob(Job* pJob);
		void SubmitFiberJob(Job* pJob, JobFiber* pFiber);

		void WaitForExit();
		virtual void Run() override;
	private:
		PlatformCriticalSection* mCriticalSection;
		Delegate<void, JobPoolWorkerThread*,Job*> mJobSignalDelegate;
		Delegate<void, JobPoolWorkerThread*,JobFiber*,Job*> mFiberJobSignalDelegate;
		Job* mCurrentJob;
		JobFiber* mFiber;
		bool mExitCall;
	};

}