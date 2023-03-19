#include "MessageModule.h"
#include <Runtime/Message/MessageAPI.h>
#include <Runtime/Message/ConsoleMessageListener.h>

namespace Portakal
{
	IMessageListener* pListener = nullptr;
	void MessageModule::OnInitialize()
	{
		/*
		* Register default message
		*/
		pListener = new ConsoleMessageListener();
		MessageAPI::RegisterListener(new ConsoleMessageListener());

	}
	void MessageModule::OnFinalize()
	{
		MessageAPI::RemoveListener(pListener);
		delete pListener;
		pListener = nullptr;
	}
}