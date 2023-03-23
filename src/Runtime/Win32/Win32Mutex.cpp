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
	void Win32Mutex::Lock(const unsigned long long waitTime)
	{
		WaitForSingleObject(mHandle, waitTime);
	}
}