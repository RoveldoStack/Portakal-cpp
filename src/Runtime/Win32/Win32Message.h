#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Platform/PlatformMessageBoxFlags.h>

namespace Portakal
{
	class PORTAKAL_API Win32Message
	{
	public:
		Win32Message() = delete;
		~Win32Message() = delete;

		static void ShowMessageBox(const String& title,const String& message,const PlatformMessageBoxFlags flags);
	};
}