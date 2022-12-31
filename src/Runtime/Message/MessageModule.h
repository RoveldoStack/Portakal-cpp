#pragma once
#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	class MessageAPI;

	class PORTAKAL_API MessageModule : public ApplicationModule
	{
	public:
		MessageModule() = default;
		~MessageModule() = default;

		GENERATE_APPLICATION_MODULE(false, false, false);

		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPreTick() override {}
		virtual void OnTick() override {}
		virtual void OnPostTick() override {}
		virtual void PreValidate() override {}
		virtual void PostValidate() override {}
		virtual void OnEvent(WindowEvent* pEvent) override {}
	private:
		MessageAPI* _api;
	};
}