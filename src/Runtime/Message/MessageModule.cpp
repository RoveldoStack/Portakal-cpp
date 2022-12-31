#include "MessageModule.h"
#include <Runtime/Message/MessageAPI.h>

namespace Portakal
{
	void MessageModule::OnInitialize()
	{
		_api = new MessageAPI();
	}
	void MessageModule::OnFinalize()
	{
		delete _api;
		_api = nullptr;
	}
}