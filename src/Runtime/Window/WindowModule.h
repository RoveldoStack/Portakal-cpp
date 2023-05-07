#pragma once
#include <Runtime/Application/ApplicationModule.h>
#include <Runtime/Window/WindowCreateDesc.h>

namespace Portakal
{
	/// <summary>
	/// Module create params
	/// </summary>
	struct PORTAKAL_API WindowModuleParams
	{
		Array<WindowCreateDesc> CreateDescs;
	};

	class WindowAPI;
	class Window;

	/// <summary>
	/// An application module for authoring the core window related operations
	/// </summary>
	PCLASS();
	class PORTAKAL_API WindowModule : public ApplicationModule
	{
		GENERATE_CLASS(WindowModule);
		GENERATE_APPLICATION_MODULE(false, false, false);
	public:
		WindowModule(const WindowModuleParams params) : mParams(params) {}
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
		const WindowModuleParams mParams;
		Array<Window*> mWindows;
		WindowAPI* mAPI;
	};
#include "WindowModule.reflect.h"
}