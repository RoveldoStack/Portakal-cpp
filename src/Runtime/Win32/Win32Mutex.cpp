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
	bool Win32Mutex::Release()
	{
		return ReleaseMutex(mHandle);
	}
	bool Win32Mutex::Lock(const unsigned long long waitTime)
	{
		return WaitForSingleObject(mHandle, waitTime == WAIT_INFINITE ? INFINITE : waitTime) != WAIT_FAILED;
	}
}