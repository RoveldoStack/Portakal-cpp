#include "Win32Mutex.h"

namespace Portakal
{
	Win32Mutex::Win32Mutex()
	{
		mHandle = CreateMutex(NULL, FALSE, NULL);
	}
	Win32Mutex::~Win32Mutex()
	{
		CloseHandle(mHandle);
	}
	bool Win32Mutex::TryLock()
	{
		return WaitForSingleObject(mHandle, 0) == WAIT_OBJECT_0;
	}
	void Win32Mutex::Release()
	{
		ReleaseMutex(mHandle);
	}
	MutexLockResult Win32Mutex::Lock(const unsigned long long waitTime)
	{
		const DWORD result = WaitForSingleObject(mHandle,waitTime == WAIT_INFINITE ? INFINITE :  waitTime);

		switch (result)
		{
		case WAIT_OBJECT_0:
			return MutexLockResult::Signaled;
		case WAIT_TIMEOUT:
			return MutexLockResult::Timeout;
		case WAIT_FAILED:
			return MutexLockResult::Invalid;
		default:
			return MutexLockResult::Invalid;
			break;
		}
	}
}