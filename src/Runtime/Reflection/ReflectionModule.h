#pragma once
#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	class AppDomain;
	class PORTAKAL_API ReflectionModule : public ApplicationModule
	{
		GENERATE_CLASS(ReflectionModule);
		GENERATE_APPLICATION_MODULE(false, false, true);
	public:
		ReflectionModule() : mTargetDomain(nullptr) {}
		~ReflectionModule() = default;

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
		AppDomain* mTargetDomain;
	};

#include "ReflectionModule.reflect.h"
}