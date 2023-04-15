#include "Win32Clipboard.h"
#include <Windows.h>
#include <Runtime/Memory/Memory.h>

namespace Portakal
{
	void Win32Clipboard::SetClipboard(const String& data)
	{
		OpenClipboard(NULL);
		EmptyClipboard();

		HGLOBAL globalMemory = GlobalAlloc(GMEM_MOVEABLE, data.GetCursor() + 1);
		Memory::Copy(data.GetSource(),GlobalLock(globalMemory),data.GetCursor() +1);
		GlobalUnlock(globalMemory);

		SetClipboardData(CF_TEXT,globalMemory);
		CloseClipboard();
	}
	String Win32Clipboard::GetClipboard()
	{
		OpenClipboard(NULL);
		const HANDLE handle = GetClipboardData(CF_TEXT);

		GlobalLock(handle);
		const String value = (char*)handle;
		GlobalUnlock(handle);

		return value;
	}
}