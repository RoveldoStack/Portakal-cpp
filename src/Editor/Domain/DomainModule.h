#pragma once
#include <Runtime/Application/Application.h>

namespace Portakal
{
	class DomainAPI;

	/// <summary>
	/// Application module which authors the domain components
	/// </summary>
	class PORTAKAL_API DomainModule : public ApplicationModule
	{
	public:
		DomainModule();
		~DomainModule() = default;

		GENERATE_APPLICATION_MODULE(false, false, true);
	private:
		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPreTick() override;
		virtual void OnTick() override;
		virtual void OnPostTick() override;
		virtual void PreValidate() override;
		virtual void PostValidate() override;
		virtual void OnEvent(WindowEvent* pEvent) override;
	private:
		DomainAPI* mAPI;
	};
}