#pragma once
#include <Runtime/Application/ApplicationModule.h>
#include <Runtime/Window/WindowCreateDesc.h>

namespace Portakal
{
	struct PORTAKAL_API WindowModuleParams
	{
		Array<WindowCreateDesc> CreateDescs;
	};

	class WindowAPI;
	class PORTAKAL_API WindowModule : public ApplicationModule
	{
		GENERATE_CLASS(WindowModule);
		GENERATE_APPLICATION_MODULE(false, false, false);
	public:
		WindowModule(const WindowModuleParams params) : _params(params) {}
		WindowModule() = default;
		~WindowModule() = default;

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
		const WindowModuleParams _params;
		WindowAPI* _api;

		
	};
	START_GENERATE_TYPE(WindowModule);

	START_TYPE_PROPERTIES(WindowModule);
		REGISTER_BASE_TYPE(ApplicationModule);
	END_TYPE_PROPERTIES;

	CONCRETE_TYPE(WindowModule);
	END_GENERATE_TYPE(WindowModule);
}