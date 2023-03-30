#include "JobSystem.h"
#include <Runtime/Platform/PlatformInfo.h>
#include <Runtime/Job/WorkerThreadJob.h>
#include <thread>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	JobSystem* JobSystem::sSystem = nullptr;

	void JobSystem::Initialize()
	{
		sSystem = new JobSystem();
	}
	void JobSystem::Schedule(Job* pJob)
	{
		if (sSystem == nullptr)
			return;

		sSystem->_Schedule(pJob);
	}
	JobSystem::JobSystem()
	{
		/*
		* Create worker threads
		*/
		const unsigned int workerThreadCount = PlatformInfo::GetCpuThreadCount() / 2;
		const unsigned int other = std::thread::hardware_concurrency();
		for (unsigned int i = 0; i < workerThreadCount; i++)
		{
			WorkerThreadData data = {};
			data.mWorkerJob = new WorkerThreadJob(GENERATE_MEMBER_DELEGATE2(this,JobSystem::OnSignalJobFinished,void,Job*,const unsigned int),i);
			data.pThread = PlatformThread::Create(data.mWorkerJob,2);
			mWorkers.Add(data);
		}
		mBarrier = PlatformCriticalSection::Create();
	}
	JobSystem::~JobSystem()
	{

	}
	void JobSystem::OnSignalJobFinished(Job* pJob, const unsigned int workerID)
	{
		pJob->_MarkFinished();

		/*
		* Check if there are jobs in the queue
		*/
		mBarrier->Lock();
		if (mJobQueue.GetCursor() > 0)
		{
			WorkerThreadData& worker = mWorkers[workerID];

			Job* pNextJob = mJobQueue[0];
			pNextJob->_SetWorkingState(true);

			worker.mWorkerJob->SubmitJob(pNextJob);
			mJobQueue.RemoveIndex(0);
		}
		mBarrier->Release();
	}
	void JobSystem::_Schedule(Job* pJob)
	{
		mBarrier->Lock();
		/*
		* If queue is not empty then simply register job to the queue
		*/
		if (mJobQueue.GetCursor() > 0)
		{
			mJobQueue.Add(pJob);
			mBarrier->Release();
			return;
		}
		mBarrier->Release();

		/*
		* Iterate workers and assing job
		*/
		for (unsigned int i = 0; i < mWorkers.GetCursor(); i++)
		{
			WorkerThreadData& worker = mWorkers[i];

			worker.mWorkerJob->Lock();
			if (!worker.mWorkerJob->HasWork())
			{
				worker.mWorkerJob->SubmitJob(pJob);
				worker.mWorkerJob->Release();
				return;
			}
			worker.mWorkerJob->Release();
		}

		/*
		* If code execution reached this path then it means there is no idle worker thread
		*/
		mBarrier->Lock();
		mJobQueue.Add(pJob);
		mBarrier->Release();
	}
}