#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Platform/PlatformMessageBoxFlags.h>

namespace Portakal
{
	class PORTAKAL_API PlatformMessage
	{
	public:
		PlatformMessage() = delete;
		~PlatformMessage() = delete;

		static void ShowMessageBox(const String& title,const String& message,const PlatformMessageBoxFlags flags = PlatformMessageBoxFlags::None);
	};
}