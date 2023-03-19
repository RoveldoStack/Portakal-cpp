#pragma once
#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	class ResourceAPI;
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
	};

	START_GENERATE_TYPE(ResourceModule);
	START_TYPE_PROPERTIES(ResourceModule);
	REGISTER_BASE_TYPE(ApplicationModule);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(ResourceModule);
	END_GENERATE_TYPE(ResourceModule);
}