#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API PlatformClipboard
	{
	public:
		static void SetClipboard(const String& data);
		static String GetClipboard();
	public:
		PlatformClipboard() = delete;
		~PlatformClipboard() = delete;
	};
}