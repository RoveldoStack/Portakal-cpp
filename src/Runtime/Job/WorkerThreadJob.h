#pragma once
#include <Runtime/Job/Job.h>
#include <Runtime/Event/Delegate.h>

namespace Portakal
{
	class PORTAKAL_API WorkerThreadJob : public Job
	{
	public:
		WorkerThreadJob(const Delegate<void, Job*, const unsigned int>& jobFinishedSignal,const unsigned int index);
		~WorkerThreadJob();

		FORCEINLINE bool HasWork();
		void SubmitJob(Job* pJob);
		void Terminate();

		void Lock();
		void Release();
	private:
		virtual void Run() override;

	private:
		Delegate<void, Job*,const unsigned int> mJobFinishedSignal;
		PlatformCriticalSection* mCriticalSection;
		Job* mCurrentJob;
		bool mTerminated;
		bool mHasWork;
		const unsigned int mIndex;
	};
}