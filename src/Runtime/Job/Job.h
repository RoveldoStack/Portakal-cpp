#pragma once
#include <Runtime/Platform/PlatformThread.h>

namespace Portakal
{
	class PlatformThread;
	class PlatformCriticalSection;
	/// <summary>
	/// Simple executable job on other threads
	/// </summary>
	class PORTAKAL_API Job
	{
		friend class PlatformThread;
		friend class JobSystem;
	public:
		Job();
		virtual ~Job() = default;

		FORCEINLINE bool IsWorking();
		FORCEINLINE bool IsFinished();

		/// <summary>
		/// Job run method
		/// </summary>
		virtual void Run() = 0;

		/// <summary>
		/// Returns the owned thread
		/// </summary>
		/// <returns></returns>
		FORCEINLINE PlatformThread* GetOwnerThread() const noexcept { return mOwnerThread; }
	private:
		void _SetOwnerThread(PlatformThread* pThread) { mOwnerThread = pThread; }
		void _SetWorkingState(const bool bState);
		void _MarkFinished();
	private:
		PlatformThread* mOwnerThread;
		PlatformCriticalSection* mCriticalSection;
		bool mWorking;
		bool mFinished;
	};
}