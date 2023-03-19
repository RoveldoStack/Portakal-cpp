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
	public:
		static void RegisterListener(IMessageListener* pListener);
		static void RemoveListener(IMessageListener* pListener);

		static void BroadcastMessage(const String& message);
	private:
		static Array<IMessageListener*> sListeners;
	public:
		MessageAPI() = delete;
		~MessageAPI() = delete;

	};

#define BROADCAST_MESSAGE(message) MessageAPI::BroadcastMessage(message);
}