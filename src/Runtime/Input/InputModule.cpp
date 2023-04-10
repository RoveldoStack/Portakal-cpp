#include "InputModule.h"
#include <Runtime/Input/InputAPI.h>

namespace Portakal
{
	void InputModule::OnInitialize()
	{
		mAPI = new InputAPI();
	}
	void InputModule::OnFinalize()
	{
		delete mAPI;
		mAPI = nullptr;

	}
	void InputModule::OnPreTick()
	{
	}
	void InputModule::OnTick()
	{
	}
	void InputModule::OnPostTick()
	{
	}
	void InputModule::PreValidate()
	{
	}
	void InputModule::PostValidate()
	{
	}
	void InputModule::OnEvent(WindowEvent* pEvent)
	{
	}
}