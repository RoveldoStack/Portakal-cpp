#include "PlatformClipboard.h"

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Clipboard.h>
typedef Portakal::Win32Clipboard PlatformAbstraction;
#endif
namespace Portakal
{
	void PlatformClipboard::SetClipboard(const String& data)
	{
		PlatformAbstraction::SetClipboard(data);
	}
	String PlatformClipboard::GetClipboard()
	{
		return PlatformAbstraction::GetClipboard();
	}
}