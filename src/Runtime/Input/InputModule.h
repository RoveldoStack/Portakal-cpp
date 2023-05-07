#pragma once
#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	class InputAPI;

	/// <summary>
	/// The module which authors the ownership of the InputAPI
	/// </summary>
	PCLASS();
	class PORTAKAL_API InputModule : public ApplicationModule
	{
		GENERATE_CLASS(InputModule);
		GENERATE_APPLICATION_MODULE(false, false, false);
	public:
		InputModule() = default;
		~InputModule() = default;

		// Inherited via ApplicationModule
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPreTick() override;
		virtual void OnTick() override;
		virtual void OnPostTick() override;
		virtual void PreValidate() override;
		virtual void PostValidate() override;
		virtual void OnEvent(WindowEvent* pEvent) override;
	private:
		InputAPI* mAPI;

		
	};

#include "InputModule.reflect.h"
}