#pragma once
#include <Runtime/Application/ApplicationModule.h>
#include <Editor/Renderer/ImGuiRenderer.h>

namespace Portakal
{
	class ImGuiAPI;

	class PORTAKAL_API ImGuiExecutorModule : public ApplicationModule
	{
		GENERATE_CLASS(ImGuiExecutorModule);
		GENERATE_APPLICATION_MODULE(true, true, false);
	public:
		ImGuiExecutorModule();
		~ImGuiExecutorModule();

		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPreTick() override;
		virtual void OnTick() override;
		virtual void OnPostTick() override;
		virtual void PreValidate() override;
		virtual void PostValidate() override;
		virtual void OnEvent(WindowEvent* pEvent) override;

	private:
		ImGuiRenderer* mRenderer;
		ImGuiAPI* mAPI;
	};

	START_GENERATE_TYPE(ImGuiExecutorModule);
	START_TYPE_PROPERTIES(ImGuiExecutorModule);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(ImGuiExecutorModule);
	END_GENERATE_TYPE(ImGuiExecutorModule);
}