#include "Win32Message.h"
#include <Runtime/Win32/Win32MessageUtils.h>

#include <Windows.h>
namespace Portakal
{
	void Win32Message::ShowMessageBox(const String& title, const String& message,const PlatformMessageBoxFlags flags)
	{
		MessageBox(NULL, *message, *title, (UINT)Win32MessageUtils::GetWin32Flags(flags));
	}
}