#include "Platform.h"

namespace Portakal
{
	PlatformType Platform::GetCurrentPlatform()
	{
#ifdef PORTAKAL_OS_WINDOWS
		return PlatformType::Windows;
#else
		return PlatformType::Linux;
#endif

	}
}