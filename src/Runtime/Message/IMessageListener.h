#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Message/MessageType.h>

namespace Portakal
{
	class PORTAKAL_API IMessageListener
	{
	public:
		FORCEINLINE virtual void OnMessageReceived(const String& message, const MessageType type) = 0;
	};
}