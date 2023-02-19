#pragma once
#include <Runtime/Message/IMessageListener.h>

namespace Portakal
{
	/// <summary>
	/// Console message listener implementation
	/// </summary>
	class PORTAKAL_API ConsoleMessageListener : public IMessageListener
	{
	public:
		virtual void OnMessageReceived(const String& message, const MessageType type) override;
	};
}