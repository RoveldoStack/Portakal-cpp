#include "ApplicationModule.h"
#include <Runtime/Application/Application.h>
namespace Portakal
{
	void ApplicationModule::PostValidationRequest()
	{
		GetOwnerApplication()->PostValidateRequest();
	}
	void ApplicationModule::PostQuitMessage(const String& message)
	{
		GetOwnerApplication()->PostQuitMessage(message);
	}
}