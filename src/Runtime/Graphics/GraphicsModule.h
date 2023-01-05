#pragma once
#include <Runtime/Application/ApplicationModule.h>
#include <Runtime/Graphics/GraphicsModuleParams.h>

namespace Portakal
{
	class GraphicsDeviceAPI;

	class PORTAKAL_API GraphicsModule : public ApplicationModule
	{
		GENERATE_CLASS(GraphicsModule);
		GENERATE_APPLICATION_MODULE(false, false, false);
	public:
		GraphicsModule(const GraphicsModuleParams& params) : _params(params),_api(nullptr) {}
		~GraphicsModule() = default;

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
		const GraphicsModuleParams _params;
		GraphicsDeviceAPI* _api;
	};
}