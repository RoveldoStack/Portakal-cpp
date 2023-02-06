#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Message/MessageType.h>

namespace Portakal
{
	class IMessageListener;
	class PORTAKAL_API MessageAPI
	{
	private:
		static MessageAPI* _api;
	public:
		static void BroadcastMessage(const String& message, const MessageType type = MessageType::Information);
		static void RegisterListener(IMessageListener* pListener);
		static void RemoveListener(IMessageListener* pListener);
	public:
		MessageAPI();
		~MessageAPI();

		void RegisterListenerInternal(IMessageListener* pListener);
		void RemoveListenerInternal(IMessageListener* pListener);
		void BroadcastMessageInternal(const String& message, const MessageType type = MessageType::Information);

	private:
		Array<IMessageListener*> mListeners;
	};

#define BROADCAST_MESSAGE(message) MessageAPI::BroadcastMessage(message);
}