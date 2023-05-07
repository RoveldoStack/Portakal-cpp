#pragma once

#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	class CommandList;
	class GraphicsDevice;

	/// <summary>
	/// An application which authors the finalization rendering of the imgui commands
	/// </summary>
	PCLASS();
	class PORTAKAL_API ImGuiRendererModule : public ApplicationModule
	{
		GENERATE_CLASS(ImGuiRendererModule);
		GENERATE_APPLICATION_MODULE(true, true, false);
	public:
		ImGuiRendererModule();
		~ImGuiRendererModule();

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
		CommandList* mCmdList;
		GraphicsDevice* mDevice;

	};

#include "ImGuiRendererModule.reflect.h"
}