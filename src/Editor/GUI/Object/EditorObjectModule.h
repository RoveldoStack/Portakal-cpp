#pragma once
#include <Runtime/Application/ApplicationModule.h>

namespace Portakal
{
	class EditorObjectAPI;
	PCLASS();
	class PORTAKAL_API EditorObjectModule : public ApplicationModule
	{
		GENERATE_CLASS(EditorObjectModule);
		GENERATE_APPLICATION_MODULE(false, false, false);
	public:
		EditorObjectModule() = default;
		~EditorObjectModule() = default;

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
		EditorObjectAPI* mAPI;
	};

	#include "EditorObjectModule.reflect.h"
}