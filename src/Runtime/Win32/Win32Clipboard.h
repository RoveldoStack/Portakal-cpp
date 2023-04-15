#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API Win32Clipboard
	{
	public:
		static void SetClipboard(const String& data);
		static String GetClipboard();
	public:
		Win32Clipboard() = delete;
		~Win32Clipboard() = delete;
	};
}