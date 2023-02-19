#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Platform/PlatformMessageBoxFlags.h>

namespace Portakal
{
	/// <summary>
	/// Platform agnostic message box management class
	/// </summary>
	class PORTAKAL_API PlatformMessage
	{
	public:
		PlatformMessage() = delete;
		~PlatformMessage() = delete;

		/// <summary>
		/// Shows a message box
		/// </summary>
		/// <param name="title"></param>
		/// <param name="message"></param>
		/// <param name="flags"></param>
		static void ShowMessageBox(const String& title,const String& message,const PlatformMessageBoxFlags flags = PlatformMessageBoxFlags::None);
	};
}