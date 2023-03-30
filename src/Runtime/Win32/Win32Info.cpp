#include "Win32Info.h"
#include <Windows.h>
namespace Portakal
{
	unsigned int Win32Info::GetCpuThreadCount()
	{
		SYSTEM_INFO info = {};
		GetSystemInfo(&info);
		return info.dwNumberOfProcessors;
	}
}