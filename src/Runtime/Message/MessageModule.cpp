#include "MessageModule.h"
#include <Runtime/Message/MessageAPI.h>
#include <Runtime/Message/ConsoleMessageListener.h>

namespace Portakal
{
	void MessageModule::OnInitialize()
	{
		mAPI = new MessageAPI();

		/*
		* Register default message
		*/
		MessageAPI::RegisterListener(new ConsoleMessageListener());

	}
	void MessageModule::OnFinalize()
	{
		delete mAPI;
		mAPI = nullptr;
	}
}