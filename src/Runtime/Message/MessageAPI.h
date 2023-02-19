#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Message/MessageType.h>

namespace Portakal
{
	class IMessageListener;

	/// <summary>
	/// API for handling the messages throught the application
	/// </summary>
	class PORTAKAL_API MessageAPI
	{
	private:
		static MessageAPI* _api;
	public:

		/// <summary>
		/// Broadcasts a message
		/// </summary>
		/// <param name="message"></param>
		/// <param name="type"></param>
		static void BroadcastMessage(const String& message, const MessageType type = MessageType::Information);

		/// <summary>
		/// Registers anew listener
		/// </summary>
		/// <param name="pListener"></param>
		static void RegisterListener(IMessageListener* pListener);

		/// <summary>
		/// Removes the existing listener
		/// </summary>
		/// <param name="pListener"></param>
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