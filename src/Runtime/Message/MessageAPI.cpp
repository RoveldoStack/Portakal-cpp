#include "MessageAPI.h"
#include <Runtime/Message/IMessageListener.h>

namespace Portakal
{
	Array<IMessageListener*> MessageAPI::sListeners;

	void MessageAPI::RegisterListener(IMessageListener* pListener)
	{
		sListeners.Add(pListener);
	}
	void MessageAPI::RemoveListener(IMessageListener* pListener)
	{
		sListeners.Remove(pListener);
	}
	void MessageAPI::BroadcastMessage(const String& message)
	{
		for (unsigned int i = 0; i < sListeners.GetCursor(); i++)
			sListeners[i]->OnMessageReceived(message, MessageType::Information);
	}
}