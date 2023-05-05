#include "MessageAPI.h"
#include <Runtime/Message/IMessageListener.h>

namespace Portakal
{
	void MessageAPI::RegisterListener(IMessageListener* pListener)
	{
		MessageAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return;

		pAPI->mListeners.Add(pListener);
	}
	void MessageAPI::RemoveListener(IMessageListener* pListener)
	{
		MessageAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return;

		pAPI->mListeners.Remove(pListener);
	}
	void MessageAPI::BroadcastMessage(const String& message)
	{
		MessageAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return;

		for (unsigned int i = 0; i < pAPI->mListeners.GetCursor(); i++)
			pAPI->mListeners[i]->OnInfoRecieved(message);
	}
	MessageAPI::MessageAPI()
	{

	}
	MessageAPI::~MessageAPI()
	{

	}
}