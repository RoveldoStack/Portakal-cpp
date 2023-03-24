#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{

	class Job;

	/// <summary>
	/// Platform agnostic thread implementation
	/// </summary>
	class PORTAKAL_API PlatformThread
	{
	public:
		/// <summary>
		/// Creates a thread and assings a job
		/// </summary>
		/// <typeparam name="TClass"></typeparam>
		/// <typeparam name="...TParameters"></typeparam>
		/// <param name="stackSize"></param>
		/// <param name="...parameters"></param>
		/// <returns></returns>
		template<typename TClass,typename... TParameters>
		static PlatformThread* Create(const unsigned int stackSize,TParameters... parameters)
		{
			Job* pJob = new TClass(parameters...);

			return Dispatch(stackSize,pJob);
		}

		/// <summary>
		/// Creates a thread for the existing job
		/// </summary>
		/// <typeparam name="TClass"></typeparam>
		/// <param name="pJob"></param>
		/// <param name="stackSize"></param>
		/// <returns></returns>
		static PlatformThread* Create(Job* pJob,const unsigned int stackSize)
		{
			return Dispatch(stackSize, pJob);
		}

		/// <summary>
		/// Waits the current thread for specified amount
		/// </summary>
		/// <param name="waitAmount"></param>
		static void SleepCurrentThread(const unsigned long long waitAmount);

	private:

		/// <summary>
		/// Dispatches new thread
		/// </summary>
		/// <param name="stackSize"></param>
		/// <param name="pJob"></param>
		/// <returns></returns>
		static PlatformThread* Dispatch(const unsigned int stackSize,Job* pJob);
	public:
		PlatformThread(const unsigned int stackSize, Job* pJob);
		virtual ~PlatformThread();

		/// <summary>
		/// Returns the underlying job
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Job* GetJob() const noexcept { return mJob; }

		/// <summary>
		/// Returns the allocated stack size for this thread
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetStackSize() const noexcept { return mStackSize; }

		/// <summary>
		/// Waits for this thread to finsih
		/// </summary>
		void WaitForFinish();

		/// <summary>
		/// Terminates the thread
		/// </summary>
		void Terminate();

	protected:
		virtual void WaitForFinishCore() = 0;
		virtual void TerminateCore() = 0;
	private:
		Job* mJob;
		unsigned int mStackSize;
		bool mRunning;

	};
}