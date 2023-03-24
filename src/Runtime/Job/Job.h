#pragma once
#include <Runtime/Platform/PlatformThread.h>

namespace Portakal
{
	class PlatformThread;
	/// <summary>
	/// Simple executable job on other threads
	/// </summary>
	class PORTAKAL_API Job
	{
		friend class PlatformThread;
	public:
		Job() : mOwnerThread(nullptr) {}
		virtual ~Job() = default;

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
	private:
		PlatformThread* mOwnerThread;
	};
}