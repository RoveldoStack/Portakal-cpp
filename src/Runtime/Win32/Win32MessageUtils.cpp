#include "Win32MessageUtils.h"
#include <Windows.h>

namespace Portakal
{
	unsigned int Win32MessageUtils::GetWin32Flags(const PlatformMessageBoxFlags flags)
	{
		unsigned int result = (unsigned int)PlatformMessageBoxFlags::None;
		
		if (flags & PlatformMessageBoxFlags::Help)
			result |= MB_HELP;
		if (flags & PlatformMessageBoxFlags::IconAtRisk)
			result |= MB_ICONASTERISK;
		if (flags & PlatformMessageBoxFlags::IconExclamation)
			result |= MB_ICONEXCLAMATION;
		if (flags & PlatformMessageBoxFlags::IconInformation)
			result |= MB_ICONINFORMATION;
		if (flags & PlatformMessageBoxFlags::IconQuestion)
			result |= MB_ICONQUESTION;
		if (flags & PlatformMessageBoxFlags::IconStop)
			result |= MB_ICONSTOP;
		if (flags & PlatformMessageBoxFlags::IconWarning)
			result |= MB_ICONWARNING;
		if (flags & PlatformMessageBoxFlags::OK)
			result |= MB_OK;

		return result;
	}
}