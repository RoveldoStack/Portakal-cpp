#pragma once
#include <Runtime/Job/Job.h>
#include <Runtime/Platform/PlatformMutex.h>
#include <Runtime/Event/Delegate.h>

namespace Portakal
{
	/// <summary>
	/// Job specialized for JobPools to use
	/// DO NOT USE THIS JOB Standalone
	/// </summary>
	class PORTAKAL_API JobPoolJob final : public Job
	{
	public:
		JobPoolJob(const Delegate<void, JobPoolJob*>& signalDelegate);
		virtual ~JobPoolJob() override;

		/// <summary>
		/// Submits new job
		/// </summary>
		/// <param name="pJob"></param>
		void SubmitJob(Job* pJob);

		void WaitForExit();
		virtual void Run() override;
	private:
		PlatformMutex* mMutex;
		Delegate<void, JobPoolJob*> mSignalDelegate;
		Job* mCurrentJob;
		bool mExitCall;
	};

}