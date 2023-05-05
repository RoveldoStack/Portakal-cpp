#include "ReflectionModule.h"
#include <Runtime/Reflection/ReflectionAPI.h>

namespace Portakal
{
	void ReflectionModule::OnInitialize()
	{
		mAPI = new ReflectionAPI();
	}
	void ReflectionModule::OnFinalize()
	{
		delete mAPI;
		mAPI = nullptr;
	}
	void ReflectionModule::OnPreTick()
	{

	}
	void ReflectionModule::OnTick()
	{

	}
	void ReflectionModule::OnPostTick()
	{

	}
	void ReflectionModule::PreValidate()
	{

	}
	void ReflectionModule::PostValidate()
	{

	}
	void ReflectionModule::OnEvent(WindowEvent* pEvent)
	{

	}
}