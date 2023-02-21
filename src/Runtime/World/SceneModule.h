#pragma once
#include <Runtime/Application/Application.h>

namespace Portakal
{
	class SceneAPI;

	/// <summary>
	/// An application module which autors the core scene components
	/// </summary>
	class PORTAKAL_API SceneModule : public ApplicationModule
	{
		GENERATE_CLASS(SceneModule);
		GENERATE_APPLICATION_MODULE(true, false, false);
	public:
		SceneModule() = default;
		~SceneModule() = default;

		virtual void OnInitialize() override;
		virtual void OnFinalize() override;
		virtual void OnPreTick() override;
		virtual void OnTick() override;
		virtual void OnPostTick() override;
		virtual void PreValidate() override;
		virtual void PostValidate() override;
		virtual void OnEvent(WindowEvent* pEvent) override;
	private:
		SceneAPI* mAPI;
	};

	START_GENERATE_TYPE(SceneModule);
	START_TYPE_PROPERTIES(SceneModule);
	REGISTER_BASE_TYPE(ApplicationModule);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(SceneModule);
	END_GENERATE_TYPE(SceneModule);
}