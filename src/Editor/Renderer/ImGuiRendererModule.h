#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	class CommandList;
	class GraphicsDevice;

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

	START_GENERATE_TYPE(ImGuiRendererModule);
	START_TYPE_PROPERTIES(ImGuiRendererModule);
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(ImGuiRendererModule);
	END_GENERATE_TYPE(ImGuiRendererModule);
}