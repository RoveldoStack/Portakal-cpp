#pragma once
#include <Runtime/Platform/PlatformMessageBoxFlags.h>

namespace Portakal
{
	class PORTAKAL_API Win32MessageUtils
	{
	public:
		Win32MessageUtils() = delete;
		~Win32MessageUtils() = delete;

		FORCEINLINE static unsigned int GetWin32Flags(const PlatformMessageBoxFlags flags);
	};
}