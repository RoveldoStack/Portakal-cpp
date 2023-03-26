#include "Win32CriticalSection.h"

namespace Portakal
{
	Win32CriticalSection::Win32CriticalSection()
	{
		InitializeCriticalSection(&mSection);
	}
	Win32CriticalSection::~Win32CriticalSection()
	{
		DeleteCriticalSection(&mSection);
	}
	bool Win32CriticalSection::TryLock()
	{
		return TryEnterCriticalSection(&mSection);
	}
	void Win32CriticalSection::Lock()
	{
		EnterCriticalSection(&mSection);
	}
	void Win32CriticalSection::Release()
	{
		LeaveCriticalSection(&mSection);
	}
}