#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	typedef void(*THREAD_START_ADDRESS)(void);
	class IJob;
	class PORTAKAL_API PlatformThread
	{
	public:
		template<typename TClass,typename... TParameters>
		static PlatformThread* Create(const unsigned int stackSize,TParameters... parameters)
		{
			TClass* pJob = new TClass(parameters...);

			return Create(stackSize,pJob);
		}

		static void WaitCurrentThread(const unsigned long long waitAmount);

	private:
		static PlatformThread* Create(const unsigned int stackSize,IJob* pJob);
	public:
		PlatformThread(const unsigned int stackSize,IJob* pJob) : mJob(pJob),mStackSize(stackSize), mRunning(false) {}
		virtual ~PlatformThread();

		FORCEINLINE IJob* GetJob() const noexcept { return mJob; }
		FORCEINLINE unsigned int GetStackSize() const noexcept { return mStackSize; }

		void WaitForFinish();
		void Terminate();

	protected:
		virtual void WaitForFinishCore() = 0;
		virtual void TerminateCore() = 0;
	private:
		IJob* mJob;
		unsigned int mStackSize;
		bool mRunning;

	};
}