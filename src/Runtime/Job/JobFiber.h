#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Job/Job.h>
#include <Runtime/Platform/PlatformCriticalSection.h>

namespace Portakal
{
	class PORTAKAL_API JobFiber
	{
		friend class JobPool;
	public:
		JobFiber();
		~JobFiber();

		FORCEINLINE unsigned int GetJobPathMaxVerticalSize() { return mMaxVerticalSize; }
		FORCEINLINE bool IsWorking();
		FORCEINLINE bool IsFinished();
		FORCEINLINE unsigned int GetJobPathHorizontalSize();
		Array<Job*> CollectCurrentNode() noexcept;


		void RegisterNode(const Array<Job*>& jobs);
	private:
		bool _ReportJobFinished(Job* pJob);
		bool _RecalculateMaxVerticalSize();
		void _SetWorkingState(const bool bState);
		void _MarkFinished();
	private:
		Array<Array<Job*>> mJobPath;
		PlatformCriticalSection* mCriticalSection;
		unsigned int mMaxVerticalSize;
		bool mWorking;
		bool mFinished;
	};
}