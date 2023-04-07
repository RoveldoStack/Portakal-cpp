#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Message/MessageType.h>

namespace Portakal
{
	/// <summary>
	/// General message listener interface
	/// </summary>
	class PORTAKAL_API IMessageListener
	{
	public:
		FORCEINLINE virtual void OnInfoRecieved(const String& message) = 0;
		FORCEINLINE virtual void OnWarningRecieved(const String& message) = 0;
		FORCEINLINE virtual void OnErrorRecieved(const String& message) = 0;
	};
}