#pragma once
#include <Runtime/Application/ApplicationModule.h>
#include <Runtime/Graphics/GraphicsModuleParams.h>

namespace Portakal
{
	class GraphicsDeviceAPI;

	/// <summary>
	/// An application modules designed to author the core graphics related stuff
	/// </summary>
	class PORTAKAL_API GraphicsModule : public ApplicationModule
	{
		GENERATE_CLASS(GraphicsModule,Virtual);
		GENERATE_APPLICATION_MODULE(false, false, false);
	public:
		GraphicsModule(const GraphicsModuleParams& params) : mParams(params),mAPI(nullptr) {}
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
		const GraphicsModuleParams mParams;
		GraphicsDeviceAPI* mAPI;
	};


#include "GraphicsModule.reflect.h"
}