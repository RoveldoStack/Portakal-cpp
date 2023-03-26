#include "JobFiber.h"

namespace Portakal
{
    JobFiber::JobFiber() : mMaxVerticalSize(0),mWorking(false),mFinished(false)
    {
        mCriticalSection = PlatformCriticalSection::Create();
    }
    JobFiber::~JobFiber()
    {

    }
    bool JobFiber::IsWorking()
    {
        mCriticalSection->Lock();
        const bool bState = mWorking;
        mCriticalSection->Release();

        return bState;
    }
    bool JobFiber::IsFinished()
    {
        mCriticalSection->Lock();
        const bool bState = mFinished;
        mCriticalSection->Release();

        return bState;
    }
    unsigned int JobFiber::GetJobPathHorizontalSize()
    {
        unsigned int horizontalSize = 0;

        mCriticalSection->Lock();
        horizontalSize = mJobPath.GetCursor();
        mCriticalSection->Release();

        return horizontalSize;
    }
    Array<Job*> JobFiber::CollectCurrentNode() noexcept
    {
        Array<Job*> jobsOut;

        mCriticalSection->Lock();

        if (mJobPath.GetCursor() == 0)
        {
            mCriticalSection->Release();
            return jobsOut;
        }
        jobsOut = mJobPath[0];

        mCriticalSection->Release();

        return jobsOut;
    }
    void JobFiber::RegisterNode(const Array<Job*>& jobs)
    {
        mCriticalSection->Lock();
        if (jobs.GetCursor() > mMaxVerticalSize)
            mMaxVerticalSize = jobs.GetCursor();

        mJobPath.Add(jobs);
        mCriticalSection->Release();
    }
    bool JobFiber::_ReportJobFinished(Job* pJob)
    {
        mCriticalSection->Lock();

        if (mJobPath.GetCursor() == 0)
        {
            mCriticalSection->Release();
            return true;
        }

        /*
        * Remove the job from the current node
        */
        mJobPath[0].Remove(pJob);

        /*
        * If the node is finished then remove it from the path
        */
        if (mJobPath[0].GetCursor() == 0)
        {
            mJobPath.RemoveIndex(0);
            mCriticalSection->Release();
            return true;
        }

        mCriticalSection->Release();

        return false;
    }
    bool JobFiber::_RecalculateMaxVerticalSize()
    {
        mCriticalSection->Lock();

        const unsigned int formerMax = mMaxVerticalSize;

        unsigned int max = 0;
        for (unsigned int i = 0; i < mJobPath.GetCursor(); i++)
        {
            if (mJobPath[i].GetCursor() > max)
                max = mJobPath[i].GetCursor();
        }
        mMaxVerticalSize = max;

        mCriticalSection->Release();

        return formerMax != max;
    }
    void JobFiber::_SetWorkingState(const bool bState)
    {
        mCriticalSection->Lock();
        mWorking = bState;
        mCriticalSection->Release();
    }
    void JobFiber::_MarkFinished()
    {
        mCriticalSection->Lock();
        mFinished = true;
        mCriticalSection->Release();
    }
}