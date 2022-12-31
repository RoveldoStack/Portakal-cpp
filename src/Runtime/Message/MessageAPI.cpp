#include "MessageAPI.h"
#include <Runtime/Message/IMessageListener.h>

namespace Portakal
{
	MessageAPI* MessageAPI::_api = nullptr;

	void MessageAPI::BroadcastMessage(const String& message, const MessageType type)
	{
		_api->BroadcastMessageInternal(message, type);
	}
	void MessageAPI::RegisterListener(IMessageListener* pListener)
	{
		_api->RegisterListenerInternal(pListener);
	}
	void MessageAPI::RemoveListener(IMessageListener* pListener)
	{
		_api->RemoveListenerInternal(pListener);
	}
	MessageAPI::MessageAPI()
	{
		_api = this;
	}
	MessageAPI::~MessageAPI()
	{
		_api = nullptr;

		for (int i = 0; i < _listeners.GetCursor(); i++)
		{
			delete _listeners[i];
		}
		_listeners.Clear();
	}

	void MessageAPI::BroadcastMessageInternal(const String& message, const MessageType type)
	{
		for (int i = 0; i < _listeners.GetCursor(); i++)
		{
			_listeners[i]->OnMessageReceived(message, type);
		}
	}
	void MessageAPI::RegisterListenerInternal(IMessageListener* pListener)
	{
		_listeners.Add(pListener);
	}
	void MessageAPI::RemoveListenerInternal(IMessageListener* pListener)
	{
		_listeners.Remove(pListener);
	}
}