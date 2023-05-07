#pragma once
#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	class ResourceAPI;
	PCLASS();
	class PORTAKAL_API ResourceModule : public ApplicationModule
	{
		GENERATE_CLASS(ResourceModule);
		GENERATE_APPLICATION_MODULE(false, false, false);
	public:
		ResourceModule();
		~ResourceModule();

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
		ResourceAPI* mAPI;
	};

#include "ResourceModule.reflect.h"
}