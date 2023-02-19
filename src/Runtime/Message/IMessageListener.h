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
		/// <summary>
		/// Called on when a message is broadcasted
		/// </summary>
		/// <param name="message"></param>
		/// <param name="type"></param>
		FORCEINLINE virtual void OnMessageReceived(const String& message, const MessageType type) = 0;
	};
}